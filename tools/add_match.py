#!/usr/bin/env python3
"""Append ONE matched row to targets/game/reverse/functions.csv, safely.

Hand-edited rows have caused LF damage, wrong column counts, and overlapping
claims. This tool validates each claim against the ledger and appends it with
CRLF endings. It removes the source's `// <name> present-unmatched` marker and
checks the bytes with `./build.sh`. It restores the source and ledger when the
build fails. Rows survive without verification only when a caller passes
`--no-verify`.

Usage:
  python3 tools/add_match.py <mangled-name> <target_rva> <target_size> <source> \\
      [--notes TEXT] [--replace-existing] [--no-verify] [--root DIR]

`--replace-existing` safely repoints the symbol's one existing ledger row before
verification.  `--replace-rva` does the same keyed on the ADDRESS instead of the
name, which is the only way to convert a machine byte-dump: a real conversion
changes the name (`?d_000a8940@@YAXXZ` -> `?addr@SpikeAccessor@@QAEPADXZ`), so
--replace-existing cannot find the row it needs to retire. It accepts scaffold
rows at the same range. With identity and boundary evidence, it can also retire
a matched wrong identity when the old range lies inside the corrected full
body. Verification restores the old row if it fails.
A verified same-source identity correction also carries exact existing
gen-funclet parent references in that transaction; compiler labels stay unchanged.
`--replace-archive-import OLD_NAME` is a separate verified provider repair:
only an existing vendored archive's six-byte private dispatch thunk, table
field, and independently matched initializer may replace a gen-import row.
"""
if __name__ == "__main__":
    from target_guard import require_game_cli
    require_game_cli("add_match.py")

import argparse
import csv
import io
import os
import re
import subprocess
import sys
from pathlib import Path

import ledger_io
from portable_lock import lock

DEFAULT_ROOT = Path(__file__).resolve().parents[1]

MARKER_RE = re.compile(r"^\s*//\s*(\S+)\s+present-unmatched\b")
COMPILED_SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx"}
BOUNDARY_ENV = {
    "name": "ADDMATCH_BOUNDARY_NAME",
    "rva": "ADDMATCH_BOUNDARY_RVA",
    "source": "ADDMATCH_BOUNDARY_SOURCE",
}
BOUNDARY_BATCH_FILE_ENV = "ADDMATCH_BOUNDARY_BATCH_FILE"


SCAFFOLD_NOTE = re.compile(r"(?:gen-dump|gen-thunk)\s*(?:$|[;,])")


def replaceable_scaffold(row):
    """Only supported placeholders, never arbitrary generated/unwind claims."""
    notes = row["notes"].lstrip()
    # Whole token, as build.is_scaffold_row reads it: a row of real C++ whose
    # note begins "gen-dump conversion; ..." is a claim, not a placeholder.
    if SCAFFOLD_NOTE.match(notes):
        return True
    kind = notes.split(";", 1)[0]
    return ((kind == "gen-tgrid" and
             re.fullmatch(r"game/gen_small/tgrid_\d+\.cpp", row["source"]) is not None)
            or (kind == "gen-shim" and
                re.fullmatch(r"game/gen_small/(?:fam|fun)_\d+\.cpp", row["source"]) is not None)
            or gen_dtor_scaffold(row))


# Approved by the project lead 2026-10-15: two kinds of game/gen_small/ claim may be
# repointed to real C++ elsewhere, as gen-dump dumps already are. A gen-dtor row is a
# placeholder deleting destructor of a synthetic Gen_dtor* class (no identity, so
# --replace-rva alone retires it, like gen-dump). A hand-written U3*/W3* TU's row
# carries a name, so retiring it is an identity correction (--correct-identity).
GEN_DTOR_SOURCE = re.compile(r"game/gen_small/dtorsv?_\d+\.cpp")
HAND_GEN_SMALL_SOURCE = re.compile(r"game/gen_small/[UW]3\w*\.cpp")
GENERATED_ROOTS = ("game/gen_small/", "game/gen_asm/", "game/masm_dumps/")


def gen_dtor_scaffold(row):
    """A generator-written deleting destructor in game/gen_small/dtors*_NNN.cpp."""
    return (row["notes"].lstrip().split(";", 1)[0] == "gen-dtor" and
            GEN_DTOR_SOURCE.fullmatch(row["source"]) is not None)


def hand_gen_small_claim(row):
    """A hand-written (not generator-output) claim in a game/gen_small/ U3*/W3* TU."""
    if HAND_GEN_SMALL_SOURCE.fullmatch(row["source"]) is None:
        return False
    parts = [part.strip() for part in row["notes"].split(";")]
    return not any(part.startswith(("gen-", "vendored=", "object-symbol=")) or
                   "identity=generated" in part for part in parts)


# A gen-dtor successor names the real class whose destructor the body calls.
DTOR_SUCCESSOR = re.compile(r"\?\?_[GE](?P<cls>.+)@@[A-Z]AEPAXI@Z")
GEN_DTOR_NAME = re.compile(r"\?\?_[GE](?P<cls>Gen_dtorv?_[0-9a-f]{8})@@UAEPAXI@Z")


def generated_spelling(name):
    """A generator's own spelling (Gen_*, dup_*, ?d_/?j_ placeholders) anywhere in NAME.
    Address-derived Rva* names stay allowed for hand-written rows (AGENTS.md)."""
    return re.search(r"Gen_|dup_|(?:^|[@?$])[dj]i?_[0-9a-fA-F]{8}", name) is not None


def opaque_class(cls):
    """An address-derived or generator class spelling: never a proven identity."""
    return (re.search(r"Gen_|dup_|(?:^|[@?$])[dj]_[0-9a-fA-F]{8}", cls) is not None or
            any(re.search(r"\d", run) for run in re.findall(r"[0-9A-Fa-f]{8,}", cls)))


def gen_dtor_successor_problem(root, replaced, name, rows):
    """Why NAME cannot replace the gen-dtor placeholder REPLACED, or None.

    The placeholder's only identity is the destructor it calls, which the gate
    resolves through a symbols.csv pin (??1Gen_dtor*_X). A real successor must be
    ??_G/??_E of a real (not address-derived) class C whose destructor ??1C is a
    MATCHED ledger row placed at that pinned address, directly or behind a
    matched ILT row's target=: a pin-only ??1C would byte-match a wrong class."""
    successor = DTOR_SUCCESSOR.fullmatch(name)
    if successor is None or name[3] != replaced["name"][3]:
        return (f"{name} is not a {replaced['name'][:4]}<Class>@@?AEPAXI@Z deleting destructor "
                f"like the {replaced['name']} placeholder it replaces")
    cls = successor.group("cls")
    if opaque_class(cls):
        return (f"{cls} is an address-derived or generator class name; a gen-dtor "
                "placeholder is only replaced by the deleting destructor of a real class")
    placeholder = GEN_DTOR_NAME.fullmatch(replaced["name"])
    if placeholder is None:
        # Out of scope: a gen-dtor row already renamed to a real class (EA renames,
        # e.g. ??_EAssetManagerImpl...) has no Gen_dtor pin to prove its destructor.
        return (f"{replaced['name']} is not a Gen_dtor placeholder name; renamed gen-dtor "
                "rows are out of scope for this path")
    pin_name = f"??1{placeholder.group('cls')}@@UAE@XZ"
    pins = set()
    symbols = Path(root) / "targets/game/reverse" / "symbols.csv"
    if symbols.exists():
        with symbols.open(encoding="utf-8", newline="") as handle:
            for pin in csv.DictReader(handle):
                if pin.get("name") == pin_name:
                    try:
                        pins.add(int(pin["address"], 16))
                    except (KeyError, TypeError, ValueError):
                        continue
    if len(pins) != 1:
        return (f"{len(pins)} symbols.csv pins {pin_name}; exactly one must say which "
                "destructor the placeholder calls")
    behind = set(pins)
    for row in rows:
        # Only a matched 5-byte ILT thunk row's target= says where a call lands.
        ilt = (row["size"] == 5 and
               (re.fullmatch(r"\?j_[0-9a-fA-F]{8}@@YAXXZ", row["name"]) is not None or
                row["notes"].lstrip().split(";", 1)[0] == "gen-thunk"))
        if row["status"] == "matched" and row["rva"] in pins and ilt:
            target = re.search(r"(?:^|;)target=0x([0-9A-Fa-f]{8})(?:;|$)", row["notes"])
            if target:
                behind.add(int(target.group(1), 16))
    dtor = re.compile(r"\?\?1" + re.escape(cls) + r"@@[A-Z]AE@XZ")
    if not any(row["status"] == "matched" and dtor.fullmatch(row["name"]) and
               row["rva"] in behind for row in rows):
        return (f"no matched functions.csv row ??1{cls}@@?AE@XZ sits at the destructor the "
                f"placeholder calls ({', '.join(f'0x{a:08X}' for a in sorted(pins))} or the "
                "body its ILT row targets); land or prove that destructor first")
    return None


def gen_small_repoint(row):
    """Does retiring ROW take the narrow game/gen_small/ repoint path?"""
    return gen_dtor_scaffold(row) or hand_gen_small_claim(row)


def vendored_row(row):
    """A vendored=<lib> row carries the upstream library's own identity."""
    return any(part.strip().startswith("vendored=") for part in row["notes"].split(";"))


# Owner directive 2026-10-08: the D3DX9 region is paused and off-limits.
D3DX_PAUSED = (0x009F9B82, 0x00AD5401)
# A token ends at whitespace or markdown/prose punctuation, never inside a name.
TOKEN_EDGE = r"\s`'\"()\[\]<>,;|*"


def evidence_names(text, token, *, case_insensitive=False):
    """TOKEN appears in TEXT as a whole token, not a substring of a longer one."""
    edge = f"[{TOKEN_EDGE}]"
    pattern = f"(?:^|(?<={edge})){re.escape(token)}(?=$|{edge}|[.:](?:$|{edge}))"
    return re.search(pattern, text, re.IGNORECASE if case_insensitive else 0) is not None


def correctable_claim(old, old_name, new_name, evidence_text):
    """May --correct-identity retire OLD (named OLD_NAME) for NEW_NAME?

    A matched real-source claim qualifies as before. A matched vendored=<lib> row
    (approved by the project lead 2026-10-15) qualifies only with identity
    evidence that names its 0xRVA and both exact (case-sensitive) names as whole
    tokens, outside the paused D3DX9 region: vendored rows carry the upstream's
    real identities, so the proof must show retail disagrees at that address.
    A hand-written claim in a game/gen_small/ U3*/W3* TU (same approval) needs the
    same token-exact evidence."""
    if any(not n or re.search(r"\s", n) for n in (old_name, new_name)):
        return False
    if old["name"] != old_name or old_name == new_name or old["status"] != "matched":
        return False
    if replaceable_scaffold(old):
        return False
    if (old["source"].startswith("game/") and
            not old["source"].startswith(("game/gen_small/", "game/gen_asm/"))):
        return True
    if not (vendored_row(old) or hand_gen_small_claim(old)):
        return False
    if D3DX_PAUSED[0] <= old["rva"] <= D3DX_PAUSED[1]:
        return False
    text = evidence_text or ""
    return (evidence_names(text, f"0x{old['rva']:08X}", case_insensitive=True) and
            evidence_names(text, old_name) and evidence_names(text, new_name))


def fail(*lines):
    for line in lines:
        print(f"add_match: {line}", file=sys.stderr)
    raise SystemExit(1)


def parse_ledger(raw):
    """Strict parse: any malformed row means the ledger is already corrupt and
    our duplicate/overlap validations cannot be trusted — refuse to append."""
    text = raw.decode("utf-8", errors="replace")
    rows = []
    for i, r in enumerate(csv.reader(io.StringIO(text)), start=1):
        if i == 1 or not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            fail(f"functions.csv line {i} has {len(r)} fields, expected 7: {r[:3]}...",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        name, _export, target_rva, target_size, source, status, notes = r
        try:
            rva = int(target_rva, 16)
        except ValueError:
            fail(f"functions.csv line {i} ({name}): unparseable target_rva '{target_rva}'",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        try:
            size = int(target_size) if target_size else 0
        except ValueError:
            fail(f"functions.csv line {i} ({name}): unparseable target_size '{target_size}'",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        rows.append({"line": i, "name": name, "rva": rva, "size": size,
                     "source": source, "status": status, "notes": notes})
    return rows


def ledger_key(fields):
    """Return the semantic identity used when rewriting one ledger row."""
    if len(fields) < 3:
        return None
    try:
        return fields[0], int(fields[2], 16)
    except ValueError:
        return None


def retarget_funclet_parents(raw, rows, old, name, rva, size, source, *, verified):
    """Carry exact dependent parent tokens with a verified same-body rename.

    Labels and funclet identities stay untouched. Plan this before any write;
    the normal whole-source build and existing full-blob rollback still decide.
    """
    if (old["source"] != source or old["rva"] != rva or old["size"] != size
            or old["status"] != "matched"
            or not source.startswith("game/") or source.startswith(GENERATED_ROOTS)
            or Path(source).suffix.lower() not in COMPILED_SOURCE_SUFFIXES):
        return raw, 0
    parent = f"parent={old['name']}"
    edits = {}
    for row in rows:
        tokens = row["notes"].split(";")
        if (row["source"] != source or row["status"] != "matched"
                or "gen-funclet" not in tokens or parent not in tokens):
            continue
        objects = [t[len("object-symbol="):] for t in tokens if t.startswith("object-symbol=")]
        if len(objects) > 1:
            fail(f"{row['name']}: ambiguous funclet object-symbol tokens; nothing changed")
        symbol = objects[0] if objects else row["name"]
        if re.fullmatch(r"\$L\d+", symbol) is None:
            continue  # Not a native compiler-label funclet.
        if sum(t.startswith("parent=") for t in tokens) != 1:
            fail(f"{row['name']}: ambiguous funclet parent tokens; nothing changed")
        key = row["name"], row["rva"]
        if key in edits:
            fail(f"{row['name']}: duplicate dependent funclet identity; nothing changed")
        edits[key] = ";".join(f"parent={name}" if t == parent else t for t in tokens)
    if not edits:
        return raw, 0
    if not verified:
        fail("--no-verify cannot retarget dependent funclet parents; nothing changed")
    if any(c in token for token in (old["name"], name) for c in ";="):
        fail("a funclet parent name contains a note-token delimiter; nothing changed")
    if sum(row["name"] == old["name"] for row in rows) != 1:
        fail(f"{old['name']}: ambiguous parent identity; nothing changed")
    out, seen = [], set()
    for payload, term in ledger_io.split_records(raw):
        fields = ledger_io.fields(payload)
        key = ledger_key(fields)
        if key in edits:
            if key in seen or len(fields) != 7 or ",".join(fields).encode("utf-8") != payload:
                fail("dependent funclet row cannot be rewritten losslessly; nothing changed")
            fields[6] = edits[key]
            payload = ",".join(fields).encode("utf-8")
            seen.add(key)
        out.append(payload + term)
    if seen != edits.keys():
        fail("dependent funclet row disappeared during planning; nothing changed")
    return b"".join(out), len(edits)


def strip_marker(source_path, name):
    """Remove the `// <token> present-unmatched` line whose token is the full
    mangled name or a prefix of it (markers are often truncated at a @@, e.g.
    `// ?getUnicodeString@Dict@@ present-unmatched`). Byte-level line surgery so
    the file's own line endings survive untouched. Returns new bytes or None."""
    raw = source_path.read_bytes()
    lines = raw.splitlines(keepends=True)
    exact, prefix = [], []
    for index, line in enumerate(lines):
        match = MARKER_RE.match(line.decode("utf-8", errors="replace"))
        if not match:
            continue
        token = match.group(1)
        if token == name:
            exact.append(index)
        elif name.startswith(token):
            prefix.append(index)
    candidates = exact or prefix
    if not candidates:
        return None
    victim = candidates[0]
    stripped = lines[victim].rstrip(b"\r\n").decode("utf-8", errors="replace")
    print(f"add_match: stripping marker at {source_path.name}:{victim + 1}: {stripped.strip()}")
    return b"".join(lines[:victim] + lines[victim + 1:])


def lookup_export_rva(root, name):
    exports = root / "targets/game/reverse" / "exports.csv"
    if not exports.exists():
        # exports.csv is generated (gitignored); its absence only costs the
        # optional export_rva column, so say so instead of silently omitting
        print("add_match: note: targets/game/reverse/exports.csv not present — export_rva left empty")
        return ""
    with exports.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row["kind"] == "code" and row["name"] == name:
                return row["rva"]
    return ""


def verification_environment(source_path, source_rel, name, rva):
    """Pass one new compiled-source claim to build.py's boundary guard.

    The normal build has to keep accepting the existing ledger, including rows
    whose historical extent was never checked this way.  add_match is the
    narrow point at which a row is new, so the request is carried in a
    short-lived child environment rather than becoming a global build rule.
    Assembly and archive rows are intentionally left without a request: their
    bytes are an explicit non-C++ representation, not a compiler epilogue that
    this guard can judge.
    """
    environment = os.environ.copy()
    for variable in BOUNDARY_ENV.values():
        environment.pop(variable, None)
    environment.pop(BOUNDARY_BATCH_FILE_ENV, None)
    if source_path.suffix.lower() in COMPILED_SOURCE_SUFFIXES:
        environment[BOUNDARY_ENV["name"]] = name
        environment[BOUNDARY_ENV["rva"]] = f"0x{rva:08X}"
        environment[BOUNDARY_ENV["source"]] = source_rel
    return environment


def batch_boundary_requests(claims, source_rel):
    """Every new compiled claim the source-scoped build must boundary-check."""
    return [
        {"name": claim["name"], "rva": claim["rva"], "source": claim["source"]}
        for claim in claims
        if claim["source"] == source_rel
        and Path(claim["source"]).suffix.lower() in COMPILED_SOURCE_SUFFIXES
    ]


def batch_verification_environment(request_path):
    """Point build.py at a batch request file without bloating its environment."""
    environment = os.environ.copy()
    for variable in BOUNDARY_ENV.values():
        environment.pop(variable, None)
    environment.pop(BOUNDARY_BATCH_FILE_ENV, None)
    if request_path is not None:
        environment[BOUNDARY_BATCH_FILE_ENV] = str(request_path)
    return environment


def emptied_generated_sources(root, retired, rows, adding=()):
    """game/gen_small/ TUs that retiring the RETIRED rows leaves owning nothing.

    build.verify_source_claims and check_csv's orphan check refuse any game/ .cpp
    with zero matched rows (functions.csv or data_rows.csv), and the delta path
    never checks a source that only LOST rows: 5c065afaba moved the last two rows
    out of W3AtlConversionHolderCtors.cpp and every full gate went red until
    e6e493867a deleted it. A generated TU that owns nothing is deleted with the
    --replace-rva (any kind: gen-dtor, hand-written, gen-shim, gen-tgrid,
    gen-dump, gen-thunk) that emptied it; ADDING are the sources the same change
    claims rows in. Rows of any other status, function or data, still naming the
    file would point at a missing source, so that case is refused before anything
    is written."""
    retired_keys = {(row["name"], row["rva"]) for row in retired}
    data_csv = Path(root) / "targets/game/reverse" / "data_rows.csv"
    data = []
    if data_csv.exists():
        with data_csv.open(encoding="utf-8", newline="") as handle:
            data = list(csv.DictReader(handle))
    emptied = []
    for source in sorted({row["source"] for row in retired}):
        if not source.casefold().startswith("game/gen_small/") or source in adding:
            continue
        remaining = [row for row in rows if row["source"] == source
                     and (row["name"], row["rva"]) not in retired_keys]
        data_rows_here = [row for row in data if row.get("source") == source]
        if (any(row["status"] == "matched" for row in remaining) or
                any(row.get("status") == "matched" for row in data_rows_here)):
            continue
        others = sorted([row["name"] for row in remaining] +
                        [row.get("name", "?") for row in data_rows_here])
        if others:
            fail(f"--replace-rva moves the last matched row out of {source}, which must "
                 f"then be deleted, but {len(others)} unmatched function/data row(s) "
                 f"still name it: {', '.join(others[:5])}",
                 "settle those rows first (repoint or retire them), then repoint this one")
        emptied.append(source)
    return emptied


def delete_emptied_sources(root, emptied, tool="add_match"):
    """Delete each emptied generated TU; say how to stage it and how to undo it."""
    for rel in emptied:
        path = Path(root) / rel
        if path.exists():
            path.unlink()
            print(f"{tool}: deleted {rel}: this change moved its last matched row out "
                  "(source claims and check_csv refuse a game/ .cpp that owns no row). "
                  f"Stage it with `git rm --cached {rel}`; if you abandon this landing, "
                  f"restore it with `git checkout -- {rel}`")


def orphaned_caller_selectors(root, replaced):
    """Exact build selectors for matched rows whose call into REPLACED loses its target.

    A retired game/gen_small/ name stays defined by its frozen TU (that file is never
    edited), but the resolver only knows ledger rows and symbols.csv pins: a matched
    caller compiled against the old name would turn red in someone else's gate. Run
    after the ledger is rewritten; the same question the commit hook asks
    (delta_sources), asked early so a failure here restores the ledger."""
    import build
    import delta_sources
    if Path(root).resolve() != Path(build.ROOT).resolve():
        fail("the game/gen_small/ repoint reads the live build state; it cannot run "
             "against a test --root")
    rows = build.load_all_function_rows()
    pins = set()
    with build.SYMBOLS.open(encoding="utf-8", newline="") as handle:
        for pin in csv.DictReader(handle):
            try:
                pins.add((pin["name"], int(pin["address"], 16)))
            except (KeyError, TypeError, ValueError):
                continue
    deleted = {(replaced["name"], replaced["rva"])}
    return [delta_sources.row_selector(rows[index]) for index in
            delta_sources.affected_row_indices(deleted, pins, rows,
                                               "gen_small repoint candidate losses")]


def census_gen_small_problem(root, index):
    """Why the census INDEX cannot vouch for game/gen_small/ as it is now, or None.

    The files are frozen against hand edits, not against tool renames (EA renames
    rewrite them), so the census must have been taken at a commit whose
    game/gen_small/ equals the working tree's."""
    meta = index.get("meta") if isinstance(index, dict) else None
    commit = meta.get("commit") if isinstance(meta, dict) else None
    if not isinstance(commit, str) or not re.fullmatch(r"[0-9a-fA-F]{7,40}", commit):
        return ("the link census index records no commit; cannot trust its game/gen_small/ "
                "definitions (rebuild it: python3 tools/link_census.py --build --history)")
    known = subprocess.run(["git", "cat-file", "-e", f"{commit}^{{commit}}"], cwd=root,
                           capture_output=True)
    if known.returncode != 0:
        return f"the link census commit {commit} is unknown here; refresh the census first"
    same = subprocess.run(["git", "diff", "--quiet", commit, "--", "game/gen_small"],
                          cwd=root, capture_output=True)
    if same.returncode != 0:
        return (f"game/gen_small/ changed since the link census at {commit}: its definitions "
                "are stale; refresh the census first")
    return None


def gen_small_definers(root, name):
    """Census objects of game/gen_small/ TUs that define NAME (strong or COMDAT).

    game/gen_small/ files are frozen (never edited), so the last link census's
    definitions for them stay exact; the retired row's own TU is re-read fresh by
    frozen_tu_defines. A COMDAT copy in ANY linked generated TU could fold with,
    and win over, the verified body."""
    import build
    import link_check
    if Path(root).resolve() != Path(build.ROOT).resolve():
        fail("the game/gen_small/ repoint reads the live build state; it cannot run "
             "against a test --root")
    index = link_check.load_index()
    problem = census_gen_small_problem(root, index)
    if problem:
        fail(problem)
    objects = index["objects"]
    found = set(index["strong"].get(name, ()))
    found.update(entry[0] for entry in index["comdat"].get(name, ()))
    return sorted(objects[i] for i in found if objects[i].startswith("game_gen_small_"))


def frozen_tu_defines(root, source_rel, name):
    """True when the frozen game/gen_small/ TU's (just verified) object defines NAME.

    The old file keeps compiling for its other rows. If it also emitted the new
    name, the link would hold two definitions and COMDAT selection could pick the
    generated copy over the verified one. A missing object is not evidence of
    safety."""
    import build
    if Path(root).resolve() != Path(build.ROOT).resolve():
        fail("the game/gen_small/ repoint reads the live build state; it cannot run "
             "against a test --root")
    obj = build.obj_path(Path(root) / source_rel)
    if not obj.exists():
        fail(f"no object for {source_rel} after verification; cannot prove it does not "
             f"also define {name}")
    stat = obj.stat()
    _data, _sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    return any(symbol["name"] == name and symbol["section"] > 0 for symbol in symbols)


def remove_stash(rva, root):
    """Drop the banked attempt for `rva` now that real C++ owns the address.

    Only ever called after verification passes: the revert paths above restore
    the tree, and a stash deleted there would take the next agent's head start
    with it. tools/add_match_batch.py writes the ledger on its own and does NOT
    call this, so a batch landing leaves its stash for check_csv to flag.
    """
    stash = Path(root) / "targets/game/reverse" / "attempts" / f"0x{rva:08x}.cpp"
    if stash.exists():
        stash.unlink()
        print(f"add_match: cleared banked attempt {stash.relative_to(Path(root)).as_posix()}")


LANDED_BY = "landed-by=add_match"


def landing_recorded(raw, name, rva, size, source_rel):
    """True when this exact landing is the STANDING verdict at rva in RAW (the
    attempt log's bytes): re-running a landing never writes a second row. A
    landing that a later verdict at that address superseded (a `blocked` after
    it, a void) is not standing, so the re-landing is recorded again --
    otherwise the later deferral would stay the last word on a matched body."""
    import re_log
    records, _resolved = re_log.indexed_records_text(raw.decode("utf-8", "replace"))
    standing = records.get(rva)
    if standing is None:
        return False
    fields = standing[1]
    return (fields[0] == name and fields[3] == "landed" and fields[2] == str(size)
            and fields[4].startswith(f"{LANDED_BY} source={source_rel} "))


def drop_uncommitted_landing(root, log, raw, rva):
    """A same-session re-landing at RVA (--replace-existing at a new size, a
    --replace-rva rename) supersedes this session's own earlier add_match
    `landed` line: drop such a line that HEAD's log does not hold yet, so the
    commit carries one landing, not an orphan check_csv would refuse.

    Bytes in, bytes out, split on LF only: the log holds a mid-line CR (the
    ?getPath00083DD0@ScreenshotGlobalData row) and may hold invalid UTF-8,
    and every line but the dropped one must stay byte-identical.

    Known residuals (review round 3): one add_match session per worktree (a
    second session's uncommitted landing at the same RVA is dropped too); a
    git revert of a same-extent --replace-existing re-landing is refused by
    check_csv (the parent still carries the same key); a hand-deleted landed
    line inside a commit that also renames its row passes check_csv; and
    blocked-on= must name the start of a functions.csv row, so a blocker
    with no row is carved first."""
    committed = subprocess.run(["git", "-C", str(root), "show",
                                "HEAD:targets/game/reverse/re_attempts.log"], capture_output=True)
    held = set(committed.stdout.split(b"\n")) if committed.returncode == 0 else set()
    lines = raw.split(b"\n")
    kept, dropped = [], 0
    marker = (LANDED_BY + " ").encode()
    for index, line in enumerate(lines):
        fields = line.split(b"\t")
        mine = False
        if len(fields) >= 5 and fields[3] == b"landed" and fields[4].startswith(marker):
            try:
                mine = int(fields[1], 16) == rva
            except ValueError:
                mine = False
        if mine and index < len(lines) - 1 and line not in held:
            dropped += 1
            continue
        kept.append(line)
    if not dropped:
        return raw
    new_raw = b"\n".join(kept)
    ledger_io.atomic_write_bytes(log, new_raw)
    print(f"add_match: replaced this session's uncommitted `landed` line for 0x{rva:08X}")
    return new_raw


def landing_evidence(rva, size, source_rel, notes):
    """The `landed` row's evidence: who landed what, at which extent, with the
    ledger notes (model=, identity-correction=, ...) as the evidence trail."""
    model = re.search(r"(?:^|;)model=([^;\s]+)", notes or "")
    clean = " ".join((notes or "").replace(";", "; ").split())
    return (f"{LANDED_BY} source={source_rel} extent=0x{rva:08X}..0x{rva + size:08X} "
            f"size={size}B model={model.group(1) if model else 'unrecorded'} ; notes: {clean or '-'}")


def record_landing(root, name, rva, size, source_rel, notes, *, text=None):
    """Append the `landed` verdict for a verified row (approved by the project
    lead 2026-10-16; ported from Open-BFME-2 4ebbfc02b2). Workers forgot it, so
    the log's last word on a landed body stayed an old `blocked`, and the
    deferrals waiting on it never learned their wall was gone
    (eligibility.released_rvas). Written through re_log.append (LF, one line,
    append-only) only after verification; idempotent. Returns the log text
    after the call (bytes), or None when nothing could be recorded. TEXT is a
    previous call's return value (add_match_batch reads the log once)."""
    import re_log
    log = Path(root) / "targets/game/reverse" / "re_attempts.log"
    if not log.exists():
        return None
    raw = log.read_bytes() if text is None else text
    raw = drop_uncommitted_landing(root, log, raw, rva)
    if landing_recorded(raw, name, rva, size, source_rel):
        print(f"add_match: `landed` for {name} @ 0x{rva:08X} already in re_attempts.log")
        return raw
    evidence = landing_evidence(rva, size, source_rel, notes)
    re_log.append(name, f"0x{rva:08X}", str(size), "landed", evidence, path=log)
    print(f"add_match: recorded `landed` in targets/game/reverse/re_attempts.log -- stage it "
          "with the ledger")
    return raw + f"{name}\t0x{rva:08X}\t{size}\tlanded\t{evidence}\n".encode("utf-8")


def report_waiting(rva, path=None, root=None):
    """Print the standing deferrals this landing concerns: those naming it in
    blocked-on= (released once all their blockers landed), and, as a report
    only, those whose free text mentions the address. Under --root it reads
    that root's log and ledger."""
    import eligibility
    import re_log
    records, _resolved = re_log.indexed_records(path)
    named, mentioned = [], []
    pattern = re.compile(rf"(?<![0-9A-Fa-f])(?:0x)?0*{rva:X}(?![0-9A-Fa-f])", re.IGNORECASE)
    for at, (_index, fields) in sorted(records.items()):
        if at == rva or fields[3] not in re_log.DEFERRED_STATUSES:
            continue
        if rva in re_log.blocked_on(fields[4]):
            named.append((at, fields))
        elif pattern.search(fields[4]):
            mentioned.append((at, fields))
    rows = None
    if named and root is not None:
        rows = eligibility.load_rows(Path(root) / "targets/game/reverse" / "functions.csv")
    released = eligibility.released_rvas(path, rows=rows, root=root) if named else {}
    for at, fields in named:
        state = ("released: served as untried again" if at in released
                 else "still waits on another blocked-on= body")
        print(f"add_match: {fields[0]} @ 0x{at:08X} ({fields[3]}) named this body in blocked-on=; {state}")
    for at, fields in mentioned[:10]:
        print(f"add_match: {fields[0]} @ 0x{at:08X} ({fields[3]}) mentions this address; if it "
              f"waited on it, re-record it with blocked-on=0x{rva:08X}")


def replacement_tombstone_record(replaced, successor_name, successor_rva,
                                 successor_size, successor_source, *, verified,
                                 boundary_evidence=None, identity_evidence=None):
    """Render one durable replacement record for deleted_rows.csv.

    A branch forked before the conversion can merge the removed functions.csv
    line back without a conflict. check_csv treats this append-only record as
    the authoritative deletion and rejects that resurrection.
    """
    proof = "gate-required claim" if verified else "verification-deferred claim"
    if boundary_evidence:
        if replaceable_scaffold(replaced):
            kind = replaced["notes"].lstrip().split(";", 1)[0]
            reason = (
                f"{kind} scaffold retired because its {replaced['size']}-byte extent at "
                f"0x{replaced['rva']:08X} was wrong. The real identity {successor_name} is a "
                f"{proof} from {successor_source} over the corrected {successor_size}-byte "
                f"range at the same start. Boundary evidence: {boundary_evidence}"
            )
        else:
            reason = (
                f"{replaced['name']} at 0x{replaced['rva']:08X}/{replaced['size']}B was "
                f"retired because that range sits inside the full {successor_name} body "
                f"at 0x{successor_rva:08X}/{successor_size}B. The {proof} uses "
                f"{successor_source}. Boundary evidence: {boundary_evidence}"
            )
    elif replaceable_scaffold(replaced):
        kind = replaced["notes"].lstrip().split(";", 1)[0]
        reason = (
            f"{kind} scaffold placeholder superseded by the real identity of these bytes: "
            f"{successor_name}, a {proof} from {successor_source} over the same "
            f"{replaced['size']}-byte range. The {replaced['source']} scaffold reproduces "
            "those bytes but carries no identity."
        )
    else:
        reason = (
            f"claim superseded by the {proof} for {successor_name} at "
            f"0x{successor_rva:08X}/{successor_size}B from {successor_source}. The prior "
            f"claim at 0x{replaced['rva']:08X}/{replaced['size']}B from "
            f"{replaced['source']} was retired."
        )
    if identity_evidence and (vendored_row(replaced) or hand_gen_small_claim(replaced)):
        reason += (f" Identity evidence: {identity_evidence}. "
                   f"Prior notes: {replaced['notes']}")
    elif gen_dtor_scaffold(replaced):
        reason += f" Prior notes: {replaced['notes']}"
    buffer = io.StringIO()
    csv.writer(buffer, lineterminator="\n").writerow(
        [replaced["name"], f"0x{replaced['rva']:08X}", reason])
    return buffer.getvalue().encode("utf-8")


def validate_tombstone_append_target(raw, path):
    """Refuse an append that could glue onto a torn or headerless CSV record."""
    if not raw.endswith(b"\n"):
        fail(f"{path} does not end with a newline; refusing a torn tombstone append")
    header = raw.split(b"\n", 1)[0].rstrip(b"\r")
    if header != b"name,target_rva,reason":
        fail(f"{path} has an invalid deletion-ledger header")
    try:
        text = raw.decode("utf-8")
        list(csv.reader(io.StringIO(text), strict=True))
    except (UnicodeError, csv.Error) as error:
        fail(f"{path} is not valid CSV: {error}",
             "repair the deletion ledger before appending another tombstone")


def append_replacement_tombstone(path, replaced, successor_name, successor_rva,
                                 successor_size, successor_source, *, verified,
                                 boundary_evidence=None, identity_evidence=None):
    """Atomically append one replacement record to the deletion ledger."""
    record = replacement_tombstone_record(
        replaced, successor_name, successor_rva, successor_size, successor_source,
        verified=verified, boundary_evidence=boundary_evidence,
        identity_evidence=identity_evidence)
    raw = path.read_bytes()
    validate_tombstone_append_target(raw, path)
    ledger_io.atomic_write_bytes(path, raw + record)


# A compiler-made symbol C++ cannot spell: `_$E8` (a dynamic initializer), `$L123`
# (an EH funclet label), `__ehhandler$...`, `??__E...`. A row for one of these can
# only bind through `object-symbol=`, so that alias is not an escape hatch.
COMPILER_LABEL = re.compile(r"(?:^|;)\s*object-symbol=(?:_?\$[A-Za-z]\w*|__ehhandler\$\S*|"
                            r"__unwindfunclet\$\S*|__catch\$\S*|\?\?__[EF]\S*)\s*(?:;|$)")
LEDGER_REL = "targets/game/reverse/functions.csv"


def admit_compiler_label_alias(root, notes, rva, ledger_before, retired_rva=None):
    """After verification: admit this row's object-symbol= in the escape-hatch register
    (tools/hatch_counters.py) when it names a compiler label. Any other new alias row,
    and any typed into functions.csv by hand, stays counted growth the register refuses
    once enforced. Only the register lines of the rows this run lands (RVA, and the
    RETIRED_RVA a replacement drops) are rewritten, plus admissions an earlier tool run
    left pending in this working tree (bound to the ledger's previous blob, which this
    append changed, so they are re-stamped). Every other line stays byte for byte."""
    import hatch_counters
    if Path(hatch_counters.ROOT).resolve() != Path(root).resolve():
        return                                  # a test-only --root has no register
    label = bool(COMPILER_LABEL.search(notes or ""))
    before = hatch_counters.blob_id(LEDGER_REL, ledger_before)
    scope = {f"0x{rva:08X}"} | ({f"0x{retired_rva:08X}"} if retired_rva is not None else set())
    if not label and retired_rva is None:
        register = Path(root) / hatch_counters.BASELINE
        pending = re.search(rb"(?m)^object_symbol\t" + re.escape(LEDGER_REL.encode()) +
                            rb"\t[^\n]*\tallow=" + re.escape(before.encode()) + rb"[ \t]*$",
                            register.read_bytes() if register.exists() else b"")
        if not pending:
            return                              # nothing to admit or carry forward
    hatch_counters.admit(LEDGER_REL, "add_match: verified row bound to a compiler label",
                         tokens={f"0x{rva:08X}"} if label else set(),
                         before=before, scope=scope)


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("name", help="decorated (mangled) symbol name")
    parser.add_argument("target_rva", help="RVA of the function body, hex (0x...)")
    parser.add_argument("target_size", help="function size in bytes, decimal")
    parser.add_argument("source", help="repo-relative source path (src/...)")
    parser.add_argument("--notes", default="", help="notes column text (no commas)")
    parser.add_argument("--model", default="",
                        help="model that wrote the body (recorded as model= in notes; a fleet "
                             "worker gets it from BFME_MODEL). Required: landings with no "
                             "model cannot be counted per lane.")
    parser.add_argument("--icf-owner", help="refused: retail has no identical-code folding, "
                        "so a body takes one name (python3 tools/one_identity.py)")
    parser.add_argument("--replace-existing", action="store_true",
                        help="replace the symbol's one existing row instead of rejecting it; "
                             "the old row is restored if verification fails")
    parser.add_argument("--replace-rva", metavar="RVA",
                        help="retire the scaffold or corrected identity at this address "
                             "and claim it under the new name; the old row is restored "
                             "if verification fails")
    parser.add_argument("--replace-archive-import", metavar="OLD_NAME",
                        help="with --replace-rva and --identity-evidence, replace one "
                             "generated private dispatch thunk with its verified existing archive symbol")
    parser.add_argument("--correct-identity", metavar="OLD_NAME",
                        help="with --replace-rva, retire this matched real-name claim "
                             "when independent evidence proves the replacement identity")
    parser.add_argument("--identity-evidence", metavar="PATH",
                        help="targets/game/reverse/identity_evidence/*.md proof required by "
                             "--correct-identity or --replace-archive-import")
    parser.add_argument("--boundary-evidence",
                        help="with --replace-rva, record why the claimed extent was wrong; "
                             "a real-identity correction may replace a contained interior "
                             "span with its full body")
    parser.add_argument("--no-verify", action="store_true",
                        help="skip ./build.sh verification (row lands UNVERIFIED — "
                             "verify before committing)")
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                        help="TEST-ONLY: operate on a copy of the repo rooted here "
                             "instead of the live ledger (default: repo root)")
    args = parser.parse_args()
    if args.icf_owner:
        fail(f"--icf-owner {args.icf_owner}: retail was linked without identical-code "
             f"folding, so every body has exactly one identity",
             "python3 tools/one_identity.py prints the evidence; when the existing name is "
             "wrong, replace it with --replace-rva, --correct-identity and --identity-evidence")
    if args.correct_identity and args.replace_archive_import:
        fail("--correct-identity and --replace-archive-import are alternatives")
    if bool(args.correct_identity or args.replace_archive_import) != bool(args.identity_evidence):
        fail("an identity replacement and --identity-evidence must be passed together")
    if args.replace_archive_import and (not args.replace_rva or args.replace_existing
                                       or args.boundary_evidence or args.no_verify):
        fail("--replace-archive-import requires verified --replace-rva at the same extent; "
             "no --replace-existing, --boundary-evidence or --no-verify")
    if args.correct_identity and (not args.replace_rva or args.replace_existing):
        fail("--correct-identity requires --replace-rva and cannot be combined with "
             "--replace-existing")
    if args.boundary_evidence is not None:
        if not args.replace_rva:
            fail("--boundary-evidence requires --replace-rva")
        if not args.boundary_evidence.strip():
            fail("--boundary-evidence must not be empty")
        if set(args.boundary_evidence) & set("\r\n"):
            fail("--boundary-evidence must be one line")
    from fleet_run import MODEL_TOKEN, fenced, host_tag, run_tag
    lost = fenced()
    if lost:
        fail(f"this fleet run lost its shared claim ({lost})",
             "another worker owns the body now; nothing from this run may land")
    args.notes = run_tag(args.notes)
    # ~80% of the 637 landings between efdc0c4dd7 and 9c9c8b35d0 had no model
    # anywhere, so nobody could say which seats were worth paying for.
    # Record, don't trust: model= is what the caller claims; launched= keeps
    # the model the fleet runner LAUNCHED (BFME_MODEL) whenever the two
    # differ, and host= names the machine. These receipt keys are RESERVED:
    # a model=/launched=/host= typed into --notes is read as the caller's
    # claim and rewritten, never allowed to stand in for the receipt (review
    # 2026-09-29: notes model=X masked a launch/claim disagreement). None of
    # it is authenticated.
    receipt_key = re.compile(r"(?:^|(?<=[\s;]))(model|launched|host)=([^\s;]*)")
    typed = dict(receipt_key.findall(args.notes))
    notes = receipt_key.sub("", args.notes)
    notes = re.sub(r";(?:\s*;)+", ";", re.sub(r"[ \t]{2,}", " ", notes)).strip(" ;")
    launched = os.environ.get("BFME_MODEL", "")
    noted = typed.get("model", "") if typed.get("model", "") != "MODEL" else ""
    model = args.model or noted or launched
    tags = []
    if model:
        if not MODEL_TOKEN.fullmatch(model):
            fail(f"--model {model!r} is not a model token")
        tags.append(f"model={model}")
    if model and launched and launched != model and MODEL_TOKEN.fullmatch(launched):
        tags.append(f"launched={launched}")
    host = host_tag()
    if host:
        tags.append(f"host={host}")
    args.notes = ";".join(([notes] if notes else []) + tags)
    if args.root.resolve() == DEFAULT_ROOT.resolve() and not model:
        fail("a landing needs its model: pass --model <model> (fleet workers get BFME_MODEL "
             "from fleet_run)")

    root = args.root.resolve()
    evidence_text = None
    if args.identity_evidence:
        evidence_rel = Path(args.identity_evidence)
        if (evidence_rel.is_absolute() or ".." in evidence_rel.parts or
                evidence_rel.parts[:4] != ("targets", "game", "reverse", "identity_evidence") or
                evidence_rel.suffix != ".md"):
            fail("--identity-evidence must be a repo-relative "
                 "targets/game/reverse/identity_evidence/*.md path")
        evidence = root / evidence_rel
        evidence_text = evidence.read_text(encoding="utf-8") if evidence.is_file() else ""
        if not evidence_text.strip():
            fail(f"--identity-evidence {evidence_rel} is missing or empty")
        evidence_key = "archive-import-evidence" if args.replace_archive_import else "identity-correction"
        args.notes = f"{evidence_key}={evidence_rel.as_posix()};{args.notes}"
    functions_csv = root / "targets/game/reverse" / "functions.csv"
    deleted_csv = root / "targets/game/reverse" / "deleted_rows.csv"
    if not functions_csv.exists():
        fail(f"no ledger at {functions_csv}")

    name = args.name
    try:
        rva = int(args.target_rva, 16)
        from fleet_run import mark_touched
        mark_touched(rva)
    except ValueError:
        fail(f"target_rva '{args.target_rva}' is not hex (expected e.g. 0x00812340)")
    try:
        size = int(args.target_size)
    except ValueError:
        fail(f"target_size '{args.target_size}' is not a decimal byte count")
    if size <= 0:
        fail(f"target_size must be positive, got {size}")

    source_rel = args.source.lstrip("./") if not Path(args.source).is_absolute() else None
    if source_rel is None:
        try:
            source_rel = Path(args.source).resolve().relative_to(root).as_posix()
        except ValueError:
            fail(f"source {args.source} is not under {root}")
    source_path = root / source_rel
    if not source_path.exists():
        fail(f"source does not exist: {source_path}",
             "a ledger row must never point at a missing file")

    for label, value in [("name", name), ("source", source_rel), ("--notes", args.notes)]:
        bad = set(value) & set(',"\r\n')
        if bad:
            fail(f"{label} contains {sorted(bad)} — functions.csv rows are raw "
                 "comma-joined fields with no quoting, this would corrupt the ledger")

    # Exclusive lock across validate->append->verify so concurrent agents cannot
    # interleave appends or double-claim, and so revert-on-failure cannot clobber
    # a row someone else appended meanwhile.
    lock_file = (root / "targets/game/reverse" / ".add_match.lock").open("a")
    lock(lock_file, exclusive=True,
         wait_notice="add_match: waiting for ledger lock (another add_match is running)...")

    raw = functions_csv.read_bytes()
    if b"\r\n" not in raw[:200]:
        fail("functions.csv has lost its CRLF line endings — restore it from git "
             "before appending (see python3 tools/check_csv.py)")
    if not raw.endswith(b"\n"):
        fail("functions.csv does not end with a newline (truncated last row?) — "
             "fix the ledger before appending")

    rows = parse_ledger(raw)
    claims = [row for row in rows if row["name"] == name]
    replaced = None
    emptied_tus = []   # game/gen_small/ TUs this --replace-rva leaves with no matched row
    if args.replace_rva:
        if args.replace_existing:
            fail("--replace-rva and --replace-existing are alternatives: one keys "
                 "on the address, the other on the name")
        try:
            old_rva = int(args.replace_rva, 16)
        except ValueError:
            fail(f"--replace-rva '{args.replace_rva}' is not hex")
        at_rva = [row for row in rows if row["rva"] == old_rva]
        if len(at_rva) != 1:
            fail(f"--replace-rva 0x{old_rva:08X} matches {len(at_rva)} rows; "
                 "it retires exactly one")
        if args.replace_archive_import:
            old = at_rva[0]
            if old["name"] != args.replace_archive_import or rva != old_rva or size != old["size"]:
                fail("--replace-archive-import must name the exact old row and preserve its extent")
            import archive_import
            try:
                route = archive_import.verify(root, old, name, source_rel, args.notes, rows)
                for key in ("archive_sha256", "member_sha256"):
                    token = {"archive_sha256": "archive-import-sha256",
                             "member_sha256": "archive-import-member-sha256"}[key]
                    if any(part.startswith(token + "=") for part in args.notes.split(";")):
                        fail(f"{token} is generated from the verified archive, not a caller override")
                    args.notes += f";{token}={route[key]}"
            except (ValueError, OSError, KeyError, IndexError) as error:
                fail(f"archive-import proof rejected: {error}")
        elif args.correct_identity:
            old = at_rva[0]
            if not correctable_claim(old, args.correct_identity, name, evidence_text):
                fail(f"--correct-identity {args.correct_identity} does not name a "
                     f"matched real-source claim at 0x{old_rva:08X}",
                     "a vendored=<lib> row is correctable only when the identity "
                     "evidence names its 0xRVA, its old name and the new name")
        elif not replaceable_scaffold(at_rva[0]):
            fail(f"--replace-rva 0x{old_rva:08X} is {at_rva[0]['name']} "
                 f"({at_rva[0]['source']}), not a supported generated scaffold row",
                 "a real identity correction requires --correct-identity "
                 "and --identity-evidence")
        if old_rva != rva:
            old_end = old_rva + at_rva[0]["size"]
            new_end = rva + size
            contained_identity = (
                bool(args.correct_identity) and bool(args.boundary_evidence) and
                rva < old_rva and old_end <= new_end)
            if not contained_identity:
                fail(f"--replace-rva must preserve the prior claim's start "
                     f"0x{old_rva:08X}; new claim starts at 0x{rva:08X}",
                     "a different start needs identity and boundary evidence for a "
                     "matched row fully contained in the corrected body")
        if at_rva[0]["size"] != size and not args.boundary_evidence:
            fail(f"--replace-rva must preserve the prior claim's exact range "
                 f"0x{old_rva:08X}/{at_rva[0]['size']}B; new claim is "
                 f"0x{rva:08X}/{size}B",
                 "pass --boundary-evidence only when retail disassembly proves the "
                 "claimed extent itself was wrong")
        if at_rva[0]["size"] == size and old_rva == rva and args.boundary_evidence:
            fail("--boundary-evidence needs a changed extent or start; "
                 "this replacement already preserves the old range")
        replaced = at_rva[0]
        if gen_small_repoint(replaced):
            # Same proof bar as a gen_asm dump, and no wider: real compiled C++
            # outside every generated root, the exact old extent, a real build.
            # The path is judged as the filesystem resolves it: no '.'/'..' or
            # symlink detour, and case-folded for case-insensitive hosts.
            try:
                canonical = source_path.resolve().relative_to(root).as_posix()
            except ValueError:
                canonical = None
            folded = source_rel.casefold()
            given = (source_rel.split("/") if Path(args.source).is_absolute()
                     else re.split(r"[\\/]", args.source))
            if given[:1] == ["."]:
                given = given[1:]               # one leading ./ is the usual spelling
            if (canonical != source_rel or any(part in (".", "..", "") for part in given)
                    or not folded.startswith("game/")
                    or folded.startswith(tuple(r.casefold() for r in GENERATED_ROOTS))
                    or source_path.suffix.lower() not in COMPILED_SOURCE_SUFFIXES):
                fail(f"--replace-rva 0x{old_rva:08X} retires {replaced['source']}; its "
                     f"successor must be real C++ under game/ outside "
                     f"{', '.join(GENERATED_ROOTS)}, not {source_rel}")
            if args.boundary_evidence or args.no_verify:
                fail("a game/gen_small/ repoint keeps the old extent and is byte-verified: "
                     "no --boundary-evidence or --no-verify")
            if generated_spelling(name):
                fail(f"{name} is a generator spelling (Gen_, dup_, ?d_/?j_); a game/gen_small/ "
                     "claim is only replaced by a real or address-derived (Rva*) name")
            if gen_dtor_scaffold(replaced):
                problem = gen_dtor_successor_problem(root, replaced, name, rows)
                if problem:
                    fail(problem)
        emptied_tus = emptied_generated_sources(root, [replaced], rows, adding={source_rel})
    if args.replace_existing:
        if not claims:
            # 36 named __emit lifts carry a truncated decoration such as
            # ?init@ShellGameLoadScreen@@: the full mangled name matched no row,
            # so converters fell back to object-symbol= notes or an identity
            # correction for what is only the rest of the same decoration.
            claims = [row for row in rows
                      if row["rva"] == rva and row["status"] == "matched"
                      and row["name"].endswith("@@") and len(name) > len(row["name"])
                      and name.startswith(row["name"])]
            if len(claims) == 1:
                args.notes = (f"{args.notes};completes-decoration={claims[0]['name']}"
                              if args.notes else f"completes-decoration={claims[0]['name']}")
        if len(claims) != 1:
            fail(f"--replace-existing requires exactly one existing row for {name}; "
                 f"found {len(claims)}")
        replaced = claims[0]
        if (replaced["source"].casefold().startswith("game/gen_small/") and
                source_rel != replaced["source"]):
            fail(f"--replace-existing would move {name} out of {replaced['source']}, which "
                 "keeps defining it: a generated copy that could win the link",
                 "a game/gen_small/ claim moves to real C++ only through --replace-rva "
                 "(and --correct-identity for a named hand-written row)")
    elif claims:
        addresses = ", ".join(f"0x{row['rva']:08X} ({row['source']}, {row['status']})"
                              for row in claims)
        fail(f"{name} is already in the ledger at {addresses}",
             "one name = one address; use --replace-existing only when deliberately "
             "repointing that claim")

    needs_tombstone = (replaced is not None and
                       (args.replace_rva is not None or
                        (replaced["name"], replaced["rva"]) != (name, rva)))
    if needs_tombstone and not deleted_csv.exists():
        fail(f"no deletion ledger at {deleted_csv}",
             "a ledger identity cannot be retired durably without a tombstone")

    new_end = rva + size
    for row in rows:
        if row is replaced:
            continue
        if row["rva"] == rva:
            fail(f"target_rva 0x{rva:08X} is already claimed by {row['name']} "
                 f"({row['source']}, {row['status']}, line {row['line']})")
        if row["status"] == "matched" and row["rva"] < new_end and rva < row["rva"] + row["size"]:
            fail(f"range [0x{rva:08X}, 0x{new_end:08X}) overlaps matched row "
                 f"{row['name']} [0x{row['rva']:08X}, 0x{row['rva'] + row['size']:08X}) "
                 f"({row['source']}, line {row['line']})")
    export_rva = lookup_export_rva(root, name)
    ledger_row = f"{name},{export_rva},0x{rva:08X},{size},{source_rel},matched,{args.notes}"

    replacement_raw, retargeted_parents = raw, 0
    if args.correct_identity:
        replacement_raw, retargeted_parents = retarget_funclet_parents(
            raw, rows, replaced, name, rva, size, source_rel, verified=not args.no_verify)

    saved_source = source_path.read_bytes()
    saved_deleted = deleted_csv.read_bytes() if needs_tombstone else None

    def restore():
        # Source first leaves at worst a stale unmatched marker on the still-live
        # new row. Restoring the ledger first could silently erase an ordinary
        # append while its marker was still stripped. A replacement tombstone is
        # last, so the restored old row stays loudly condemned until rollback ends.
        ledger_io.atomic_write_bytes(source_path, saved_source)
        ledger_io.atomic_write_bytes(functions_csv, raw)
        if saved_deleted is not None:
            ledger_io.atomic_write_bytes(deleted_csv, saved_deleted)

    try:
        new_source = None if source_path.suffix.lower() == ".lib" else strip_marker(source_path, name)

        if replaced is not None:
            # Drop the old row by CONTENT, not by line number. parse_ledger numbers
            # csv records while raw.splitlines() counts physical lines, and the two
            # disagree whenever a row carries a stray CR (the ledger is currently
            # written with \r\r\n): indexing physical lines with a record number
            # deletes an unrelated row and silently glues its neighbours together.
            # parse_ledger already guaranteed exactly one row for this name.
            # Drop it through ledger_io, which keeps each record's own terminator:
            # the ledger mixes \r\r\n, \r\n and bare \n, so splitting on \r\n glues a
            # bare-\n row onto its neighbour and deletes both.
            key = (replaced["name"], replaced["rva"])
            new_raw, dropped = ledger_io.rewrite(
                replacement_raw, lambda f: ledger_key(f) != key)
            if dropped != 1:
                fail(f"internal error: {dropped} ledger rows match {key} — "
                     "expected exactly one")
            # Tombstone first: if the process dies between the two writes,
            # check_csv loudly rejects the still-live old row. The reverse order
            # would leave a silent deletion that a later union merge can resurrect.
            if needs_tombstone:
                append_replacement_tombstone(
                    deleted_csv, replaced, name, rva, size, source_rel,
                    verified=not args.no_verify,
                    boundary_evidence=args.boundary_evidence,
                    identity_evidence=args.identity_evidence)
            ledger_io.atomic_write_bytes(
                functions_csv, new_raw + ledger_row.encode("utf-8") + b"\r\n")
            print(f"add_match: replaced row {replaced['line']}: "
                  f"0x{replaced['rva']:08X}/{replaced['size']}B {replaced['source']}")
            print(f"add_match: with: {ledger_row}")
            if retargeted_parents:
                print(f"add_match: retargeted {retargeted_parents} dependent funclet parent token(s)")
        else:
            ledger_io.atomic_write_bytes(
                functions_csv, raw + ledger_row.encode("utf-8") + b"\r\n")
            print(f"add_match: appended: {ledger_row}")
        # Marker removal is deliberately last. A hard kill before the ledger
        # writes leaves the source untouched; a kill after them leaves only a
        # stale comment, never a silently unrecorded body.
        if new_source is not None:
            ledger_io.atomic_write_bytes(source_path, new_source)
    except BaseException:
        restore()
        print("add_match: write failed — ledger and marker changes REVERTED", file=sys.stderr)
        raise

    if args.no_verify:
        print("add_match: --no-verify: row is UNVERIFIED — run "
              f"./build.sh {source_rel} before committing")
        return

    build_sh = root / "build.sh"
    if not build_sh.exists():
        # revert: an unverifiable row must not survive
        restore()
        fail(f"no build.sh at {root} — cannot verify; append reverted")

    if sys.platform == "win32":
        verify_cmd = [sys.executable, str(root / "tools" / "build.py"), source_rel]
        verify_label = f"{sys.executable} tools/build.py {source_rel}"
    else:
        verify_cmd = [str(build_sh), source_rel]
        verify_label = f"./build.sh {source_rel}"
    frozen_tu = None
    if replaced is not None and args.replace_rva and gen_small_repoint(replaced):
        # The frozen TU still compiles for its remaining rows: re-verify them, and
        # every matched caller of the retired name, in the same build.
        try:
            extra = orphaned_caller_selectors(root, replaced)
        except BaseException:
            restore()
            print("add_match: caller check failed — append and marker strip REVERTED",
                  file=sys.stderr)
            raise
        if any(row["source"] == replaced["source"] and row["status"] == "matched"
               for row in rows if row is not replaced):
            frozen_tu = replaced["source"]
            extra.append(frozen_tu)
        verify_cmd += extra
        verify_label += "".join(f" {item}" for item in extra)
    print(f"add_match: verifying: {verify_label}")
    verify_env = verification_environment(source_path, source_rel, name, rva)
    try:
        result = subprocess.run(verify_cmd, cwd=root, env=verify_env)
    except BaseException:
        restore()
        print("add_match: interrupted — append and marker strip REVERTED", file=sys.stderr)
        raise
    if result.returncode != 0:
        restore()
        fail(f"verification failed (exit {result.returncode}) — append and "
             "marker strip REVERTED; nothing was changed")
    if replaced is not None and args.replace_rva and gen_small_repoint(replaced):
        try:
            definers = gen_small_definers(root, name)
            if frozen_tu is not None and frozen_tu_defines(root, frozen_tu, name):
                definers.append(frozen_tu)
        except BaseException:
            restore()
            raise
        if definers:
            restore()
            fail(f"{', '.join(definers)} also define(s) {name}: a generated copy could win "
                 "the link over the verified body — append and marker strip REVERTED")
    # Last, after every check that reads the frozen TU or the census of it.
    delete_emptied_sources(root, emptied_tus)
    print("add_match: verified OK — row is live")
    admit_compiler_label_alias(root, args.notes, rva, raw,
                               None if replaced is None else replaced["rva"])
    if replaced is not None:
        import gate_writers             # a verified relabel of an existing row (pre-commit shadow check)
        gate_writers.stamp("eh_label", raw, functions_csv.read_bytes(), root=root)
    remove_stash(rva, args.root)
    try:
        record_landing(root, name, rva, size, source_rel, args.notes)
    except (Exception, SystemExit) as error:   # the row is verified; never revert it over the log
        print(f"add_match: COULD NOT record `landed` ({error}); record it with "
              f"tools/re_log.py record {name} 0x{rva:08X} {size} landed <evidence>", file=sys.stderr)
    try:                                       # a report: its failure must not invite a re-record
        report_waiting(rva, root / "targets/game/reverse" / "re_attempts.log", root)
    except (Exception, SystemExit) as error:
        print(f"add_match: could not list the deferrals waiting on 0x{rva:08X} ({error}); "
              "the landing itself is recorded", file=sys.stderr)
    # Verified HERE is not landed: the commit may never be pushed, or be
    # rejected. Releasing now (force, anyone's claim -- the old behaviour) let
    # another worker take a body whose conversion was still unpublished. Queue
    # the exact row; `claims.py release --landed` (fleet_run runs it when a
    # seat ends) releases the claim once origin/master holds that row, and an
    # unsettled claim simply expires.
    if os.environ.get("BFME_CLAIMS", "on") != "off" and root == DEFAULT_ROOT.resolve():
        import claims
        claims.queue_landed(rva, ledger_row, root=root)
        print("add_match: claim kept until the row is on origin/master; after your push run "
              "`python3 tools/claims.py release --landed`")


if __name__ == "__main__":
    main()
