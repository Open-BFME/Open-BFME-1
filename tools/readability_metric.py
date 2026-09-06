#!/usr/bin/env python3
"""Seven-axis readability index over the tracked C++ under Code/, cached per blob.

Six axes are the audit's; SrcIdent is the seventh and was added because the other
six could not see the thing that actually happened to the tree. Each is a
percentage where 100 is fully legible and they are printed with the table (see
LEGEND).

SrcIdent is Ident's counterpart over SOURCE TEXT rather than ledger names, and the
two disagree about the direction the tree moved: between 71d0effcb (22 Aug) and
this tree Ident rose 14.92 -> 18.82 while SrcIdent fell 80.36 -> 63.06. Renaming a
row moves Ident; inventing `Rva0026C320Owner` inside a body moves neither Ident nor
anything else the audit measured, and the conversion lane invents them by the
thousand -- 4,518 of the 12,231 measured .cpp now hold at least one. Neither figure
has to be taken on trust: `--at <rev>` prints the whole table at any revision.

An axis is a scoreboard, so it must not be movable by an edit a reader cannot tell
from the original. Two of them were, and the fix differs by axis:

  * Iface's ANON_SLOT was a closed vocabulary, so `vNN` -> `vslotNN` -- a sed --
    was worth +30.46 pp. A vocabulary cannot be defended by extending it, so the
    test is now the name's SHAPE, which the rename does not change.
  * Types' pad vocabulary has no shape to test: `char m_slack[8]` and
    `char m_name[8]` are the same declaration, and only the diff says which one is
    a rename. So --staged refuses a commit that renames pad members in place, and
    the same check refuses a commit that renames alias ledger rows in place, where
    the same argument holds for the same reason (staged_swaps, TOKEN_SWAP_BUDGET).

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
  python3 tools/readability_metric.py --at REV       # the same table at a revision
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
# A cold cache means scanning every tracked source, which is minutes with no
# output -- indistinguishable from a hang, and that is exactly how it gets read:
# a fresh worktree's first --staged run was mistaken for a blocked build lock and
# cost two killed commits before anyone suspected this tool. So a full scan says
# so, once. A commit touches a handful of files, so a miss count above this is a
# cold or wholesale-stale cache rather than ordinary work.
#
# The notice goes to stderr and nowhere else: stdout is parsed -- the trailer
# lands verbatim in commit messages and the table is asserted on -- so it stays
# byte-identical whether the cache is warm or cold.
SCAN_NOTICE_MIN = 100

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
AXES = ("Body", "Ident", "Types", "Iface", "Local", "SSoT", "SrcIdent")
LEGEND = """Body     = % of lines that are C++, not raw __emit/__asm
Ident    = % of functions whose LEDGER NAME is semantic, not address-derived
Types    = % of struct members that are named fields, not char pad[N]
Iface    = % of virtual slots that carry a name, not a stem plus a bare index
Local    = % of functions that share a file with at least one sibling
SSoT     = % of type references resolved through a header, not a TU-local shim body
SrcIdent = % of .cpp/.c whose TEXT invents no address-derived identifier"""
COLUMN = max(len(name) for name in AXES) + 1

# Bumped whenever a pattern below changes. Cache entries hold scan() and
# scan_ledger() OUTPUT keyed by blob hash, and a blob hash cannot see a change to
# the code that read it, so without a bump a regex fix is invisible on every tree
# that already has a warm cache -- which is every tree that has ever run this. The
# fix lands, the number does not move, and the natural reading is that the fix was
# wrong. 1 -> 2 carries the PLACEHOLDER left-edge fix, the ANON_SLOT shape rule,
# the pad/named double count and the new src_addressed counter.
CACHE_VERSION = 2
# git cat-file --batch is fed in chunks so a cold --staged run never holds the
# whole 60 MB of sources in one buffer.
BLOB_CHUNK = 512

# \b is the wrong LEFT edge inside a mangled name, and this is the third defect of
# that family: the two before it were the wrong right edge (see git log). MSVC's
# special-name prefixes all END IN A WORD CHARACTER -- `??0` constructor, `??1`
# destructor, `??4`, `??_G`, `??$` -- and so do its type tags (`@U`, `@PAV`,
# `$$CBU`), so there is no boundary in front of the class name that follows and
# `??0Rva006D51B0@@QAE@II@Z` scored as a real name. 2,982 rows, Ident 20.72 ->
# 18.82. Each alternative is a FIXED width because Python's lookbehind demands it,
# which is why the type tag is spelled out at one, two and three characters.
EDGE = (r'(?:\b'                            # an ordinary word boundary, or
        r'|(?<=\?\?[\w$])'                  # ??0Foo ??1Foo ??4Foo ??$Foo
        r'|(?<=\?\?_[\w$])'                 # ??_GFoo ??_EFoo
        r'|(?<=[@$](?-i:[A-Z]))'            # @UFoo
        r'|(?<=[@$](?-i:[A-Z]{2}))'         # @AAUFoo
        r'|(?<=[@$](?-i:[A-Z]{3})))')       # @PAVFoo $$CBUFoo

# The \b after the hex is why the two CamelCase lines exist. `Rva001EFF60`
# ends on a boundary and counts; `Rva0026C320Owner` -- the far commoner shape,
# and the one the file names use -- does not, so 4,278 address-derived rows were
# scoring as semantic names and Ident read 2.65 pp better than the tree was. The
# suffix must start with an ASCII capital, spelled (?-i:[A-Z]) because re.I
# would otherwise let any letter close the hex run; that is also why Gen needs
# six hex digits before a capital where Rva needs four. `GenCab...` is three hex
# digits followed by a capital, and Gen is a real word stem.
_ADDRESSED = (
    EDGE + r'(?:d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]{4,8}\b'
    r'|' + EDGE + r'Rva[0-9A-Fa-f]{6,8}\b'
    r'|' + EDGE + r'gen[0-9A-Fa-f]{6,8}\b'
    r'|' + EDGE + r'Gen_?[0-9A-Fa-f]{3,8}\b'
    r'|' + EDGE + r'Rva[0-9A-Fa-f]{4,8}(?-i:[A-Z])'
    r'|' + EDGE + r'Gen_?[0-9A-Fa-f]{6,8}(?-i:[A-Z])')
# Invented but not address-derived. These are word SHAPES, so over prose they hit
# ordinary comments -- "the shim header", "a stub for now" -- which is why
# SrcIdent, which reads file text rather than ledger names, uses ADDRESSED alone.
_INVENTED = (
    EDGE + r'Bfme(?:Conv|Thing|Owner|Tiny|Seed|Virtual)\w*\b'
    r'|' + EDGE + r'\w*(?:Thunk|Shim|Stub|Trampoline)\b')
ADDRESSED = re.compile("(?:%s)" % _ADDRESSED, re.I)
PLACEHOLDER = re.compile("(?:%s|%s)" % (_ADDRESSED, _INVENTED), re.I)

# The extent is captured because staged_swaps needs it: `char m_pad[8]` renamed to
# `char m_slack[8]` is the same eight bytes under a word the vocabulary happens not
# to list, and same-type-same-extent is what tells that apart from a real split.
PAD_MEMBER = re.compile(
    r'\b(char|BYTE|unsigned char)\s+\w*(?:pad|unk|unknown|reserved|filler)\w*\s*'
    r'\[([^\]]*)\]',
    re.I)
# Horizontal whitespace only. \s matches a newline, so the class used to run
# from one line across every line below it hunting for an `m_`, which both
# counted members the intervening lines had already disqualified and made the
# scan quadratic in file size -- one 42 KB source cost 2.3 s and a full run never
# finished, which is why build/readability/ was always empty. `[X]*[ \t]` is the
# same language as `[X]*[ \t]+` when [ \t] is inside X, so only the newline goes.
#
# The lookahead's \b is why scan() has to subtract: `m_pad` has no boundary before
# `pad`, so `unsigned char m_pad[0x38];` matches this AND PAD_MEMBER and was
# counted in both terms of the Types ratio -- 6,609 of the 10,522 pad members,
# worth Types 81.28 -> 78.78. Widening the lookahead to catch `m_pad` would also
# throw away `int m_chunkSize;` (`unk` inside `chunk`), so the overlap is removed
# where it is known to be one, in scan().
NAMED_MEMBER = re.compile(
    r'^[ \t]*(?!.*\b(?:pad|unk|reserved|filler))([A-Za-z_][\w:<>*& \t]*)[ \t]m_\w+[ \t]*'
    r'(?:\[([^\]]*)\])?[ \t]*;', re.M)
VIRTUAL_SLOT = re.compile(r'virtual\b[^;{()]*?(\w+)\s*\(')
# Deliberately vocabulary-free. This was `(?:v|pad|slot|vf|unk)\d{1,3}` -- a closed
# list -- so `vNN` -> `vslotNN` left every slot exactly as anonymous as it was and
# moved Iface +30.46 pp, and the tree had already wandered off the list without
# anyone gaming it: `bfmeSlot0`, `unused04`, `reserved113`, `s0`, and 40 slots
# already spelled `vslotNN` are 14,188 occurrences the list did not see, Iface
# 69.54 -> 48.55. A stem plus a bare index carries nothing the index does not,
# whatever the stem is spelled, so the SHAPE is the test and a rename cannot
# escape it. Cost, counted over the 141 stems this newly catches: the only ones
# that could be real words (action, query, send, value, read) are ~25 of 67,612.
ANON_SLOT = re.compile(r'[A-Za-z_]{1,8}\d{1,3}')
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
            # A declaration both patterns match is padding, not a named field, and
            # counting it in both terms of the ratio flattered Types by 2.50 pp.
            "named_members": sum(1 for hit in NAMED_MEMBER.finditer(text)
                                 if not PAD_MEMBER.search(hit.group(0))),
            "virt_all": len(slots),
            "virt_anon": sum(1 for name in slots if ANON_SLOT.fullmatch(name)),
            "tu_class_bodies": len(TU_CLASS_BODY.findall(text)),
            "src_addressed": len(ADDRESSED.findall(text))}


# Counters a header must not contribute: a class body opened in a header is the
# header doing its job, and an address-derived name in a header is one declaration
# rather than one body written around it.
TU_ONLY = ("tu_class_bodies", "src_addressed")


def add(counter, path, counts):
    """Fold one file's counters into its area, applying the path-dependent part."""
    tu = path.endswith(TU_EXT)
    for key, value in counts.items():
        if key not in TU_ONLY or tu:
            counter[key] += value
    counter["files"] += 1
    counter["cpp_files"] += int(tu)
    counter["src_addressed_files"] += int(tu and counts["src_addressed"] > 0)


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
    """The seven percentages. NaN where the area has no denominator for that axis;
    Iface is 100 with no virtual slots at all, since none of them is anonymous."""
    return (pct(counter["asm_lines"], counter["lines"]),
            pct(counter["fns_ph"], counter["fns"]),
            pct(counter["pad_members"],
                counter["pad_members"] + counter["named_members"]),
            pct(counter["virt_anon"], counter["virt_all"]) if counter["virt_all"] else 100.0,
            pct(counter["solo_files"], counter["ledger_files"]),
            pct(counter["tu_class_bodies"],
                counter["tu_class_bodies"] + counter["cpp_files"]),
            pct(counter["src_addressed_files"], counter["cpp_files"]))


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


def announce_scan(missing, total):
    """One stderr line before a full scan, so silence is never the only signal."""
    if missing > SCAN_NOTICE_MIN:
        print(f"readability: cold cache, scanning {missing} of {total} sources "
              f"(slow once; cached under build/readability/ for later runs)",
              file=sys.stderr)


def measure_worktree(root, cache):
    """(area -> counters, tracked source count) for the files on disk."""
    paths = tracked_sources(root)
    hashes = worktree_hashes(root, [*paths, LEDGER])
    announce_scan(sum(1 for path in paths if hashes[path] not in cache.files),
                  len(paths))
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


def partial_blobs(root, only):
    """The blob map a partial commit of `only` would leave behind.

    `--staged` compares the WHOLE index against HEAD, so on a partial commit --
    `git commit <paths>` while other work sits staged -- it attributes the held
    work to the commit being made. That misreported a trailer once. This takes
    the index blob for the committed paths and HEAD's for everything else, which
    is what the tree will actually look like.
    """
    head, index = listed_blobs(root, "HEAD"), listed_blobs(root, None)
    def selected(path):
        return any(path == sel or path.startswith(sel.rstrip("/") + "/")
                   for sel in only)
    merged = {p: sha for p, sha in head.items() if not selected(p)}
    merged.update({p: sha for p, sha in index.items() if selected(p)})
    if merged == head:
        fail(f"--only selects nothing staged: {', '.join(only)}")
    return merged


def measure_blobs(root, revision, cache, blobs=None):
    """area -> counters for a tree git already holds: HEAD, or the staged index."""
    if blobs is None:
        blobs = listed_blobs(root, revision)
    label = revision or "the index"
    if LEDGER not in blobs:
        fail(f"{label} has no {LEDGER}")
    sources = {path: sha for path, sha in blobs.items() if path.endswith(SRC_EXT)}
    wanted = sorted({sha for sha in sources.values() if sha not in cache.files})
    announce_scan(len(wanted), len(sources))
    for sha, raw in read_blobs(root, wanted):
        cache.put(cache.files, sha, scan(decode(raw)))
    ledger_sha = blobs[LEDGER]
    if ledger_sha not in cache.ledgers:
        for _, raw in read_blobs(root, [ledger_sha]):
            cache.put(cache.ledgers, ledger_sha, scan_ledger(raw))
    scanned = [(path, cache.files[sha]) for path, sha in sorted(sources.items())]
    return fold(collections.defaultdict(collections.Counter), scanned,
                cache.ledgers[ledger_sha])


# ------------------------------------------------------------------- guard ---
#
# Two axes can be moved by a rename that leaves the tree exactly as legible as it
# was, and neither can be defended by a better pattern -- there is no way to read
# `char m_slack[8]` and know whether it names eight bytes or hides them, and a
# `?dup_` row upgraded to a real name looks the same whether or not evidence
# backed it. The DIFF says which, because a swap keeps the thing being named:
# same source for a ledger row, same base type and extent for a member.
#
# The budget is measured, not chosen. Over the last 600 commits touching the
# ledger, 622 rows left an alias name and every single one of them ALSO moved to a
# new source -- that is the gen_asm dump -> real C++ lane, which is the default
# work and must not be touched. Exactly one renamed a row in place: 553094eb6,
# ?dup_00217620 -> ??1CollideModule@@UAE@XZ. Over the last 800 commits touching
# Code/, exactly one made a same-type same-extent pad rename inside one file. So four leaves both lanes daylight, while the sweeps this exists to stop --
# 13,329 alias rows (+8.49 pp of Ident), 10,522 pad members (+18.72 pp of Types) --
# would need thousands of commits, each of them gated and byte-verified.
TOKEN_SWAP_BUDGET = 4
ALIAS_ROW = re.compile(r'\b(?:d|dup|sub|uw|j)_[0-9A-Fa-f]{4,8}\b', re.I)
NAME_AT, RVA_AT, SOURCE_AT = 0, 2, 4
# The arriving side of a pad rename is ANY array member of the same type and
# extent, not just an `m_` one: `char pad[8]` -> `char slack[8]` leaves the ratio
# altogether rather than crossing it, and still lifts Types. Reading NAMED_MEMBER
# here would have caught 6,603 of the tree's 10,519 pad members and let the other
# 3,916 -- the ones with no `m_` -- through.
ARRAY_MEMBER = re.compile(r'^[ \t]*([A-Za-z_][\w:<>*& \t]*?)[ \t]+\w+[ \t]*'
                          r'\[([^\]]*)\][ \t]*;')


def shape(kind, extent):
    """(base type, extent) with whitespace and case flattened, so the two sides of
    a rename compare as the declaration a reader sees rather than as text."""
    return " ".join(kind.split()).lower(), " ".join(extent.split())


def staged_diff(root, only):
    """The staged change, one line per changed line. --only narrows it exactly as
    it narrows the trailer, so a partial commit is judged on what it carries."""
    return git(root, "diff", "--cached", "--unified=0", "--no-color", "HEAD",
               "--", *(only or ["Code", LEDGER])).decode("utf-8", "replace")


def staged_swaps(diff):
    """(alias row renames, per-file pad renames) that keep the thing being named.

    Diff lines only: a swap is a paired removal and addition, so no other part of
    either file matters, and a commit that touches neither costs nothing."""
    before, after = {}, {}
    pads = collections.defaultdict(collections.Counter)
    arrivals = collections.defaultdict(collections.Counter)
    path = None
    for line in diff.split("\n"):
        if line.startswith("+++ b/"):
            path = line[6:]
            continue
        if not line or line[0] not in "+-" or line[:3] in ("+++", "---"):
            continue
        body, added = line[1:], line[0] == "+"
        if path == LEDGER:
            row = body.rstrip("\r").split(",")
            if len(row) > SOURCE_AT:
                (after if added else before)[row[RVA_AT]] = row
        elif path:
            pad = PAD_MEMBER.search(body)
            if pad and not added:
                pads[path][shape(pad.group(1), pad.group(2))] += 1
            elif added and not pad:
                hit = ARRAY_MEMBER.match(body)
                if hit:
                    arrivals[path][shape(hit.group(1), hit.group(2))] += 1
    renames = [(rva, was[NAME_AT], after[rva][NAME_AT])
               for rva, was in sorted(before.items())
               if rva in after
               and was[SOURCE_AT] == after[rva][SOURCE_AT]
               and ALIAS_ROW.search(was[NAME_AT])
               and not ALIAS_ROW.search(after[rva][NAME_AT])]
    swaps = [(path, key, min(count, arrivals[path][key]))
             for path, counter in sorted(pads.items())
             for key, count in sorted(counter.items())
             if arrivals[path][key]]
    return renames, swaps


def refusals(renames, swaps):
    """One line per refused sweep, naming a case so it can be checked by hand."""
    out = []
    if len(renames) > TOKEN_SWAP_BUDGET:
        rva, was, now = renames[0]
        out.append(f"{len(renames)} ledger rows swap an alias name for a semantic "
                   f"one without moving the row's source (budget "
                   f"{TOKEN_SWAP_BUDGET}); an alias carries no identity to "
                   f"recover, so a sweep of them is Ident with nothing behind it. "
                   f"First: {rva} {was} -> {now}")
    total = sum(count for _path, _key, count in swaps)
    if total > TOKEN_SWAP_BUDGET:
        path, (kind, extent), _count = swaps[0]
        out.append(f"{total} pad members are renamed into fields of the same type "
                   f"and extent (budget {TOKEN_SWAP_BUDGET}); the bytes are as "
                   f"unnamed as they were. First: {path} {kind}[{extent}]")
    return out


# ------------------------------------------------------------------ output ---

def row(name, values):
    cells = "".join(f"{value:>{COLUMN}.0f}" if value == value else f"{'-':>{COLUMN}}"
                    for value in values)
    scored = [value for value in values if value == value]
    return f"{name:44}{cells}{sum(scored) / len(scored):>{COLUMN}.0f}"


def table(areas, tracked):
    head = f"{'area':44}" + "".join(f"{name:>{COLUMN}}" for name in (*AXES, "BRI"))
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
    parser.add_argument("--at", metavar="REV",
                        help="table for a committed revision instead of the "
                             "worktree, so a figure quoted from history stays "
                             "reproducible")
    parser.add_argument("--only", nargs="+", default=[], metavar="PATH",
                        help="with --staged, attribute only these paths to the "
                             "commit and take everything else from HEAD -- for a "
                             "partial commit made while other work is staged")
    args = parser.parse_args(argv)
    root = args.root.resolve()
    cache = Cache(root)
    refused = []
    if args.only and not args.staged:
        fail("--only belongs to --staged")
    if args.at and args.staged:
        fail("--at reads a committed revision; --staged reads the index")
    if args.staged:
        after = partial_blobs(root, args.only) if args.only else None
        line = trailer(totals(measure_blobs(root, "HEAD", cache)),
                       totals(measure_blobs(root, None, cache, after)))
        refused = refusals(*staged_swaps(staged_diff(root, args.only)))
    elif args.at:
        blobs = listed_blobs(root, args.at)
        areas = measure_blobs(root, args.at, cache, blobs)
        line = table(areas, sum(1 for path in blobs if path.endswith(SRC_EXT)))
    else:
        areas, tracked = measure_worktree(root, cache)
        line = table(areas, tracked)
    cache.save()
    # The trailer still goes to stdout on a refusal: it is the evidence for the
    # refusal, and a caller that captures stdout should see the number it earned.
    print(line)
    for reason in refused:
        print(f"readability: REFUSED -- {reason}", file=sys.stderr)
    return 2 if refused else 0


if __name__ == "__main__":
    sys.exit(main())
