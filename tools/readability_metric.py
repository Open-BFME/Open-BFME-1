#!/usr/bin/env python3
"""Six-axis readability index over the tracked C++ under Code/, cached per blob.

The six axes are the audit's, unchanged; each is a percentage where 100 is fully
legible and they are printed with the table (see LEGEND).

Scope is the eight areas in ORDER, which is what the audit measured. The ALL row
is their sum, NOT a walk of everything under Code/, so the table also prints how
many tracked sources sit outside them -- a total that silently swallowed a new
top-level area would read as progress.

Scanning all 8,826 sources takes minutes, far too slow to run per commit, so each
file's counters are cached under build/readability/ keyed by its git blob hash.
The hashes come from `git hash-object`, which is why a warm run opens no source
file at all; and because the key is the content hash, index and HEAD blobs reuse
the worktree's entries wherever the content is identical, which is what makes
--staged cheap enough for the commit gate.

--staged names only the axes whose delta survives the rounding it prints at. A
commit that drops one file shifts every denominator by a thousandth of a point,
and four axes reported as "-0.00 pp" make a one-axis commit read as a four-axis
one -- which matters, because this line is the per-commit record of what moved.

Usage:
  python3 tools/readability_metric.py [--root DIR]   # per-area table
  python3 tools/readability_metric.py --staged       # commit trailer, index vs HEAD
"""
import argparse
import collections
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import ledger_io

DEFAULT_ROOT = Path(__file__).resolve().parents[1]
LEDGER = "reverse/functions.csv"
LEDGER_COLUMNS = ["name", "export_rva", "target_rva", "target_size", "source",
                  "status", "notes"]
SRC_EXT = (".cpp", ".c", ".h", ".inl")
TU_EXT = (".cpp", ".c")
FLAT_AREAS = ("gen_asm", "gen_small", "masm_dumps", "stlport")
ORDER = ["Code/GameEngine/Source/Common",
         "Code/GameEngine/Source/GameLogic",
         "Code/GameEngine/Source/GameClient",
         "Code/GameEngine/Source/GameNetwork",
         "Code/GameEngineDevice/Source/W3DDevice",
         "Code/Libraries/Source/WWVegas",
         "Code/gen_small",
         "Code/gen_asm"]
AXES = ("Body", "Ident", "Types", "Iface", "Local", "SSoT")
LEGEND = """Body  = % of lines that are C++, not raw __emit/__asm
Ident = % of functions whose name is semantic, not address-derived
Types = % of struct members that are named fields, not char pad[N]
Iface = % of virtual slots that carry a name, not vNN/padNN
Local = % of functions that share a file with at least one sibling
SSoT  = % of type references resolved through a header, not a TU-local shim body"""

CACHE_VERSION = 1
# git cat-file --batch is fed in chunks so a cold --staged run never holds the
# whole 60 MB of sources in one buffer.
BLOB_CHUNK = 512

PLACEHOLDER = re.compile(
    r'(?:\b(?:d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]{4,8}\b'
    r'|\bRva[0-9A-Fa-f]{6,8}\b|\bgen[0-9A-Fa-f]{6,8}\b|\bGen_?[0-9A-Fa-f]{3,8}\b'
    r'|\bBfme(?:Conv|Thing|Owner|Tiny|Seed|Virtual)\w*\b'
    r'|\b\w*(?:Thunk|Shim|Stub|Trampoline)\b)', re.I)
PAD_MEMBER = re.compile(
    r'\b(?:char|BYTE|unsigned char)\s+\w*(?:pad|unk|unknown|reserved|filler)\w*\s*\[',
    re.I)
NAMED_MEMBER = re.compile(
    r'^\s*(?!.*\b(?:pad|unk|reserved|filler))[A-Za-z_][\w:<>*&\s]*\s+m_\w+\s*'
    r'(?:\[[^\]]*\])?\s*;', re.M)
VIRTUAL_SLOT = re.compile(r'virtual\b[^;{()]*?(\w+)\s*\(')
ANON_SLOT = re.compile(r'(?:v|pad|slot|vf|unk)\d{1,3}')
TU_CLASS_BODY = re.compile(r'^[ \t]*(?:class|struct)\s+\w+\s*(?::[^;{]*)?\{', re.M)
ASM_LINE = ("__emit", "__asm", "db ", ".byte")


def fail(message):
    raise SystemExit(f"readability_metric: {message}")


# ---------------------------------------------------------------- scanning ---

def decode(raw):
    """Bytes -> the same text the audit's `open(f, errors="replace").read()` saw:
    UTF-8 with replacement, then universal-newline translation."""
    return raw.decode("utf-8", "replace").replace("\r\n", "\n").replace("\r", "\n")


def scan(text):
    """One source file's raw counters. Depends on content only -- never on the
    path -- so the result is cacheable under the blob hash and shared by every
    path holding that content. tu_class_bodies is counted for every file and
    discarded by add() for non-TU ones, which keeps that property."""
    lines = text.split("\n")
    slots = VIRTUAL_SLOT.findall(text)
    return {"lines": len(lines),
            "asm_lines": sum(1 for line in lines if line.strip().startswith(ASM_LINE)),
            "pad_members": len(PAD_MEMBER.findall(text)),
            "named_members": len(NAMED_MEMBER.findall(text)),
            "virt_all": len(slots),
            "virt_anon": sum(1 for name in slots if ANON_SLOT.fullmatch(name)),
            "tu_class_bodies": len(TU_CLASS_BODY.findall(text))}


def add(counter, path, counts):
    """Fold one file's counters into its area, applying the path-dependent part:
    a class body opened in a header is the header doing its job, not a TU-local
    shim, so only .cpp/.c contribute to the SSoT axis."""
    tu = path.endswith(TU_EXT)
    for key, value in counts.items():
        if key != "tu_class_bodies" or tu:
            counter[key] += value
    counter["files"] += 1
    counter["cpp_files"] += int(tu)


def scan_ledger(raw):
    """area -> {fns, fns_ph, ledger_files, solo_files} from reverse/functions.csv.

    Records come through ledger_io because the ledger mixes \\r\\r\\n, \\r\\n and
    bare \\n terminators and every naive split has silently dropped or invented
    rows (tools/ledger_io.py:1-14)."""
    records = ledger_io.split_records(raw)
    header = ledger_io.fields(records[0][0]) if records else []
    if header != LEDGER_COLUMNS:
        fail(f"ledger header is {header}, expected {LEDGER_COLUMNS}")
    name_at, source_at = header.index("name"), header.index("source")
    areas = collections.defaultdict(collections.Counter)
    per_source = collections.Counter()
    for number, (payload, _) in enumerate(records[1:], start=2):
        row = ledger_io.fields(payload)
        if len(row) != len(LEDGER_COLUMNS):
            fail(f"ledger row {number} has {len(row)} fields, expected "
                 f"{len(LEDGER_COLUMNS)}: {row[:3]}")
        source = row[source_at]
        if not source.startswith("Code/"):
            continue
        counter = areas[area(source)]
        counter["fns"] += 1
        if PLACEHOLDER.search(row[name_at]):
            counter["fns_ph"] += 1
        per_source[source] += 1
    for source, claimed in per_source.items():
        counter = areas[area(source)]
        counter["ledger_files"] += 1
        counter["solo_files"] += int(claimed == 1)
    return {name: dict(counter) for name, counter in areas.items()}


def area(path):
    parts = path.split("/")
    if parts[1] in FLAT_AREAS:
        return "Code/" + parts[1]
    return "/".join(parts[:4]) if len(parts) > 3 else "/".join(parts[:3])


# ------------------------------------------------------------------- axes ----

def pct(part, whole):
    return 100.0 * (1 - part / whole) if whole else float("nan")


def axes(counter):
    """The six percentages. NaN where the area has no denominator for that axis;
    Iface is 100 with no virtual slots at all, since none of them is anonymous."""
    return (pct(counter["asm_lines"], counter["lines"]),
            pct(counter["fns_ph"], counter["fns"]),
            pct(counter["pad_members"],
                counter["pad_members"] + counter["named_members"]),
            pct(counter["virt_anon"], counter["virt_all"]) if counter["virt_all"] else 100.0,
            pct(counter["solo_files"], counter["ledger_files"]),
            pct(counter["tu_class_bodies"],
                counter["tu_class_bodies"] + counter["cpp_files"]))


def totals(areas):
    total = collections.Counter()
    for name in ORDER:
        total.update(areas.get(name) or {})
    return total


def pp(delta):
    """The trailer's one and only rendering of a delta -- moved() decides with it
    too, so what is printed and what is suppressed can never disagree."""
    return f"{delta:+.2f}"


def moved(before, after):
    """True only where the delta survives the precision the trailer prints at.

    Dropping a single file shifts every axis's denominator, moving each by about
    a thousandth of a point; printed as "-0.00 pp" those make a commit that moved
    one axis read as one that moved four. NaN means the axis had no denominator
    on that side: two NaNs did not move, one NaN is a real change and is named."""
    if before != before and after != after:
        return False
    return pp(after - before) not in ("+0.00", "-0.00")


# ------------------------------------------------------------------- cache ---

class Cache:
    """Scan results under build/readability/, keyed by git blob hash.

    The key IS the content hash, so a stale entry can never be served: content
    that changed hashes to a different key and is rescanned. An entry found under
    a hash that is not the file's current one is therefore never consulted."""

    def __init__(self, root):
        self.path = root / "build" / "readability" / "counts.json"
        self.files, self.ledgers, self.dirty = {}, {}, False
        if not self.path.exists():
            return
        try:
            with open(self.path) as handle:
                stored = json.load(handle)
        except (OSError, ValueError) as exc:
            fail(f"cache {self.path} is unreadable ({exc}); delete it and re-run")
        if stored.get("version") == CACHE_VERSION:
            self.files, self.ledgers = stored["files"], stored["ledgers"]

    def save(self):
        if not self.dirty:
            return
        self.path.parent.mkdir(parents=True, exist_ok=True)
        scratch = self.path.with_name(f"{self.path.name}.{os.getpid()}.tmp")
        with open(scratch, "w") as handle:
            json.dump({"version": CACHE_VERSION, "files": self.files,
                       "ledgers": self.ledgers}, handle)
        os.replace(scratch, self.path)

    def put(self, table, key, value):
        table[key] = value
        self.dirty = True
        return value


# --------------------------------------------------------------------- git ---

def git(root, *args, stdin=None):
    done = subprocess.run(["git", "-C", str(root), *args], input=stdin,
                          capture_output=True)
    if done.returncode:
        fail(f"`git {' '.join(args)}` failed in {root}: "
             f"{done.stderr.decode('utf-8', 'replace').strip()}")
    return done.stdout


def tracked_sources(root):
    listing = git(root, "ls-files", "-z", "--", "Code").decode()
    return [path for path in listing.split("\0") if path.endswith(SRC_EXT)]


def worktree_hashes(root, paths):
    """path -> blob hash of the file ON DISK. git does the reading, which is what
    lets a warm run answer without opening a single source file."""
    if not paths:
        return {}
    done = subprocess.run(["git", "-C", str(root), "hash-object", "--stdin-paths"],
                          input="\n".join(paths).encode() + b"\n", capture_output=True)
    hashes = done.stdout.split()
    if done.returncode or len(hashes) != len(paths):
        blamed = paths[len(hashes)] if len(hashes) < len(paths) else "?"
        fail(f"cannot hash {root / blamed}: "
             f"{done.stderr.decode('utf-8', 'replace').strip()}")
    return {path: sha.decode() for path, sha in zip(paths, hashes)}


def read_blobs(root, shas):
    """Yield (sha, bytes) for each blob, a chunk of BLOB_CHUNK per git process."""
    for start in range(0, len(shas), BLOB_CHUNK):
        chunk = shas[start:start + BLOB_CHUNK]
        data = git(root, "cat-file", "--batch", stdin="\n".join(chunk).encode())
        at = 0
        for sha in chunk:
            end = data.index(b"\n", at)
            head = data[at:end].split()
            if len(head) != 3 or head[1] != b"blob":
                fail(f"git cat-file returned {data[at:end]!r} for {sha}, "
                     "expected a blob")
            size = int(head[2])
            yield sha, data[end + 1:end + 1 + size]
            at = end + size + 2


def listed_blobs(root, revision):
    """path -> blob for the sources and the ledger, at `revision` or in the index.

    `git ls-files -s` prints `<mode> <blob> <stage>` and `git ls-tree -r` prints
    `<mode> <type> <blob>`, so the blob sits in a different column in each."""
    blobs = {}
    if revision is None:
        listing = git(root, "ls-files", "-s", "-z", "--", "Code", LEDGER).decode()
    else:
        listing = git(root, "ls-tree", "-r", "-z", revision, "--", "Code", LEDGER).decode()
    for record in listing.split("\0"):
        if not record:
            continue
        meta, _, path = record.partition("\t")
        _mode, second, third = meta.split()
        if revision is None:
            if third != "0":
                fail(f"{path} is unmerged in the index (stage {third}); resolve "
                     "the conflict before measuring")
            blobs[path] = second
        else:
            if second != "blob":
                fail(f"{revision}:{path} is a {second}, not a blob")
            blobs[path] = third
    return blobs


# ---------------------------------------------------------------- measuring ---

def read_file(path):
    try:
        with open(path, "rb") as handle:
            return handle.read()
    except OSError as exc:
        fail(f"cannot read {path}: {exc}")


def fold(areas, sources, ledger):
    for path, counts in sources:
        add(areas[area(path)], path, counts)
    for name, counter in ledger.items():
        areas[name].update(counter)
    return areas


def measure_worktree(root, cache):
    """(area -> counters, tracked source count) for the files on disk."""
    paths = tracked_sources(root)
    hashes = worktree_hashes(root, [*paths, LEDGER])
    scanned = []
    for path in paths:
        sha = hashes[path]
        counts = cache.files.get(sha)
        if counts is None:
            counts = cache.put(cache.files, sha, scan(decode(read_file(root / path))))
        scanned.append((path, counts))
    ledger_sha = hashes[LEDGER]
    ledger = cache.ledgers.get(ledger_sha)
    if ledger is None:
        ledger = cache.put(cache.ledgers, ledger_sha,
                           scan_ledger(read_file(root / LEDGER)))
    return fold(collections.defaultdict(collections.Counter), scanned, ledger), len(paths)


def measure_blobs(root, revision, cache):
    """area -> counters for a tree git already holds: HEAD, or the staged index."""
    blobs = listed_blobs(root, revision)
    label = revision or "the index"
    if LEDGER not in blobs:
        fail(f"{label} has no {LEDGER}")
    sources = {path: sha for path, sha in blobs.items() if path.endswith(SRC_EXT)}
    wanted = sorted({sha for sha in sources.values() if sha not in cache.files})
    for sha, raw in read_blobs(root, wanted):
        cache.put(cache.files, sha, scan(decode(raw)))
    ledger_sha = blobs[LEDGER]
    if ledger_sha not in cache.ledgers:
        for _, raw in read_blobs(root, [ledger_sha]):
            cache.put(cache.ledgers, ledger_sha, scan_ledger(raw))
    scanned = [(path, cache.files[sha]) for path, sha in sorted(sources.items())]
    return fold(collections.defaultdict(collections.Counter), scanned,
                cache.ledgers[ledger_sha])


# ------------------------------------------------------------------ output ---

def row(name, values):
    cells = "".join(f"{value:>7.0f}" if value == value else f"{'-':>7}"
                    for value in values)
    scored = [value for value in values if value == value]
    return f"{name:44}{cells}{sum(scored) / len(scored):>7.0f}"


def table(areas, tracked):
    head = f"{'area':44}" + "".join(f"{name:>7}" for name in (*AXES, "BRI"))
    lines = [head, "-" * len(head)]
    measured = 0
    for name in ORDER:
        counter = areas.get(name)
        if not counter:
            continue
        measured += counter["files"]
        lines.append(row(name, axes(counter)))
    lines += ["-" * len(head), row("ALL Code/", axes(totals(areas))), "",
              f"{tracked - measured} of {tracked} tracked sources are outside the "
              f"measured areas and in no row above.", "", LEGEND]
    return "\n".join(lines)


def trailer(before, after):
    """The line a commit carries. The files term is always there when it changed
    -- a commit that only drops files moved something real -- and a commit that
    moved nothing says so rather than printing a bare `readability:`."""
    parts = [f"{name} {was:.1f} -> {now:.1f} ({pp(now - was)} pp)"
             for name, was, now in zip(AXES, axes(before), axes(after))
             if moved(was, now)]
    files = after["files"] - before["files"]
    if not parts and not files:
        return "readability: no measurable change"
    parts.append(f"files {files:+d}")
    return "readability: " + ", ".join(parts)


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=f"{__doc__}\n{LEGEND}",
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                        help="repository to measure (default: this repo)")
    parser.add_argument("--staged", action="store_true",
                        help="print only the commit trailer, staged index vs HEAD")
    args = parser.parse_args(argv)
    root = args.root.resolve()
    cache = Cache(root)
    if args.staged:
        line = trailer(totals(measure_blobs(root, "HEAD", cache)),
                       totals(measure_blobs(root, None, cache)))
    else:
        areas, tracked = measure_worktree(root, cache)
        line = table(areas, tracked)
    cache.save()
    print(line)
    return 0


if __name__ == "__main__":
    sys.exit(main())
