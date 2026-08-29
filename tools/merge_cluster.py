#!/usr/bin/env python3
"""Collapse a `readable body of` sibling cluster into one translation unit.

A cluster is the set of files carrying `// readable body of <symbol>: <DEST>` --
bodies that belong in DEST but currently sit one to a file. 1,227 such markers
name 280 destinations across 1,017 files and the largest cluster runs to 62
files, so draining one is many commits, not one. That is why `--only` is
required on `--apply`: a whole-cluster merge is unreviewable, unrebaseable
against a repo taking continuous pushes, and would repoint rows for bodies the
merged TU does not contain.

The marker is the SOLE source of truth for membership. Ledgered siblings without
one are out of scope and `--plan` lists them under "un-clustered siblings" so
they are visible rather than silently omitted.

This tool does the mechanical halves and neither judgement call:

  --list          destinations with two or more files, largest cluster first.
  --plan DEST     the cluster's files, the declarations every sibling shares
                  (free to hoist), the ones that differ (a human reconciles
                  them), and the member declarations that outright contradict.
  --apply DEST --into PATH --only FILE...
                  repoint the rows those donors own at PATH, delete the donors
                  with nothing left, and `git add` the result.

`--apply` does NOT synthesise the merged body. A guessed union of shims
byte-matches while being wrong, which is the one failure ./build.sh cannot see;
writing the merged TU is the step between `--plan` and `--apply`.

24 files carry bodies for more than one destination (`ini_parsers.cpp` for ten),
so a cluster is not a set of files a merge may consume whole. Selection is by
ROW, never by file: a marker names a symbol, so the rows that move are the ones
this donor owns whose symbol one of its markers for THIS destination names.
Everything else stays, and a donor that still owns a row keeps its file -- whether
what holds it back is a marker for another destination or a row no marker claims
at all. Deleting such a donor would leave its remaining rows naming a path that no
longer exists, which is the single way this tool could lose code. `--plan` prints
the marked share against the rows owned so a partial donor is visible first.

Usage:
  python3 tools/merge_cluster.py --list [--root DIR]
  python3 tools/merge_cluster.py --plan DEST [--only FILE...] [--root DIR]
  python3 tools/merge_cluster.py --apply DEST --into PATH --only FILE... [--root DIR]
"""
import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

import ledger_io
from portable_lock import lock, unlock

DEFAULT_ROOT = Path(__file__).resolve().parents[1]
LEDGER = "reverse/functions.csv"
LOCK = "reverse/.add_match.lock"
LEDGER_COLUMNS = ["name", "export_rva", "target_rva", "target_size", "source",
                  "status", "notes"]
SOURCE_AT = LEDGER_COLUMNS.index("source")
NAME_AT = LEDGER_COLUMNS.index("name")
SIZE_AT = LEDGER_COLUMNS.index("target_size")
SRC_EXT = (".cpp", ".c", ".h", ".inl")

MARKER = re.compile(r"^\s*//\s*readable body of\s+(\S.*?)\s*:\s*(\S+)\s*$")
# A line is a MARKER CANDIDATE only when a comment opener is immediately
# followed by the phrase. Prose that merely mentions `readable body of` mid
# sentence is not a candidate -- a note explaining the marker convention once
# hard-failed --list, --plan and --apply tree-wide, blocking every lane, because
# any line holding the phrase had to parse as a marker. Malformed markers must
# still fail loudly (a dropped marker silently loses a body from its cluster),
# so this narrows WHAT COUNTS as an attempted marker rather than softening the
# failure: a trailing `code; // readable body of X: Y` is still a candidate and
# still fails, because MARKER requires the comment to start the line.
CANDIDATE = re.compile(r"//\s*readable body of\b")
CLASS_OPEN = re.compile(r"^(?:class|struct)\s+(\w+)\b")
# A data member: no call parens, no initialiser, ends at the semicolon. Function
# declarations are excluded on purpose -- siblings differing there are overloads
# (`iterate_TeamInstanceList()` and its const twin), which is a reconciliation,
# not a contradiction.
DATA_MEMBER = re.compile(r"^[A-Za-z_][\w\s:*&<>]*?\b(\w+)\s*(?:\[[^\]]*\])?\s*;$")
TYPEDEF = re.compile(r"^typedef\s+.+?\b(\w+)\s*(?:\[[^\]]*\])?\s*;$")
KEYWORD = re.compile(r"^(?:return|delete|throw|goto|break|continue|using|friend)\b")


def fail(*lines):
    for line in lines:
        print(f"merge_cluster: {line}", file=sys.stderr)
    raise SystemExit(1)


# ------------------------------------------------------------------ markers ---

def markers(path):
    """[(symbol, destination)] declared by one file, in file order.

    A line carrying the phrase that does not parse is a typo'd marker, and a
    typo'd marker silently drops a body out of its cluster -- so say so."""
    out = []
    for number, line in enumerate(read_text(path).split("\n"), 1):
        if not CANDIDATE.search(line):
            continue
        match = MARKER.match(line)
        if match is None:
            fail(f"{path}:{number} carries `readable body of` but does not parse as "
                 f"`// readable body of <symbol>: <path>`: {line.strip()}")
        out.append((match.group(1), match.group(2)))
    return out


def read_text(path):
    try:
        raw = path.read_bytes()
    except OSError as exc:
        fail(f"cannot read {path}: {exc}")
    return raw.decode("utf-8", "replace").replace("\r\n", "\n").replace("\r", "\n")


def scan(root):
    """(destination -> [repo-relative source], source -> [(symbol, destination)]).

    Walks the tree rather than asking git: a fixture root under tmp_path has the
    same cluster semantics as the real one, and the marker -- not the index -- is
    what defines membership."""
    code = root / "Code"
    if not code.is_dir():
        fail(f"no Code/ directory under {root}")
    clusters, declared = {}, {}
    for parent, _dirs, names in os.walk(code):
        for name in sorted(names):
            if not name.endswith(SRC_EXT):
                continue
            path = Path(parent) / name
            if b"readable body of" not in path.read_bytes():
                continue
            rel = path.relative_to(root).as_posix()
            found = markers(path)
            declared[rel] = found
            for _symbol, dest in found:
                clusters.setdefault(dest, set()).add(rel)
    return ({dest: sorted(files) for dest, files in clusters.items()}, declared)


# ------------------------------------------------------------------- ledger ---

def records(path):
    """Yield (number, payload, terminator) without holding the 22 MB ledger.

    A record ends at the first \\n and the payload is everything before its
    \\r run, so the file's mixed \\r\\r\\n / \\r\\n / \\n terminators come back
    verbatim and go back out unchanged (tools/ledger_io.py:1-14)."""
    with open(path, "rb") as handle:
        for number, line in enumerate(handle, 1):
            match = ledger_io.TERM.search(line)
            if match is None:
                fail(f"{path} line {number} has no terminator (truncated last row?)")
            yield number, line[:match.start()], match.group(0)


def ledger_index(root, wanted):
    """source -> [symbol name] for each source in `wanted`, streamed once."""
    path = ledger_path(root)
    owned = {source: [] for source in wanted}
    for number, payload, _term in records(path):
        if number == 1:
            check_header(payload, path)
            continue
        row = ledger_io.fields(payload)
        if not row:
            continue
        if len(row) != len(LEDGER_COLUMNS):
            fail(f"{path} line {number} has {len(row)} fields, expected "
                 f"{len(LEDGER_COLUMNS)}: {row[:3]}",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        if row[SOURCE_AT] in owned:
            owned[row[SOURCE_AT]].append(row[NAME_AT])
    return owned


# An ILT thunk is 5 bytes of jmp. A donor whose every row is thunk-sized holds no
# body at all -- folding it DELETES the destination's readable body and leaves a
# forwarding stub. That is a net loss whenever the jump target is still an
# unconverted dump, and the file count says the opposite, so say it here rather
# than let --plan present it like an ordinary merge.
THUNK_BYTES = 8


def thunk_donors(root, wanted):
    """Sources in `wanted` whose every ledger row is thunk-sized."""
    sizes = {source: [] for source in wanted}
    for number, payload, _term in records(ledger_path(root)):
        if number == 1:
            continue
        row = ledger_io.fields(payload)
        if not row or len(row) != len(LEDGER_COLUMNS):
            continue
        if row[SOURCE_AT] in sizes:
            try:
                sizes[row[SOURCE_AT]].append(int(row[SIZE_AT]))
            except ValueError:
                sizes[row[SOURCE_AT]].append(THUNK_BYTES + 1)
    return {s for s, got in sizes.items() if got and max(got) <= THUNK_BYTES}


def ledger_path(root):
    path = root / LEDGER
    if not path.exists():
        fail(f"no ledger at {path}")
    return path


def check_header(payload, path):
    header = ledger_io.fields(payload)
    if header != LEDGER_COLUMNS:
        fail(f"{path} header is {header}, expected {LEDGER_COLUMNS}")


def repoint(payload, number, new_source):
    """Rebuild one record's bytes with a different `source`, changing nothing else.

    Only `notes` is ever quoted (286 rows hold a comma there), and it is last, so
    a 6-way split isolates `source` byte for byte -- no csv writer, which would
    re-quote fields and rewrite terminators the ledger legitimately mixes."""
    parts = payload.split(b",", len(LEDGER_COLUMNS) - 1)
    if len(parts) != len(LEDGER_COLUMNS):
        fail(f"ledger line {number} splits into {len(parts)} raw fields, expected "
             f"{len(LEDGER_COLUMNS)}: {payload[:80]!r}")
    parsed = ledger_io.fields(payload)
    if [p.decode("utf-8", "replace") for p in parts[:SOURCE_AT + 2]] != parsed[:SOURCE_AT + 2]:
        fail(f"ledger line {number} has a comma or quote inside a leading field; a "
             f"byte-level rewrite cannot address its source column: {payload[:80]!r}")
    parts[SOURCE_AT] = new_source.encode("utf-8")
    return b",".join(parts)


# ------------------------------------------------------------- declarations ---

def declarations(text):
    """Every declaration line, whitespace-normalised, so siblings can be diffed.

    Comment-only and blank lines are dropped; this is the audit's own measure of
    "what these files say", which is what the common/differing split reports."""
    keep = []
    for line in text.split("\n"):
        stripped = line.strip()
        if not stripped or stripped.startswith("//"):
            continue
        keep.append(re.sub(r"\s+", " ", stripped))
    return keep


def declared_members(text):
    """(class, member) -> declaration text, for direct data members and typedefs.

    Only the lines at a class body's own brace depth are considered, so a
    statement inside an inline method is never mistaken for a member. The trailing
    comment is kept in the text on purpose: `// +0x274` versus `// +0x280` on the
    same field is precisely the contradiction two siblings must not carry into
    one TU."""
    out, depth, pending, stack = {}, 0, None, []
    for line in text.split("\n"):
        stripped = line.strip()
        code = re.sub(r"\s+", " ", stripped.split("//")[0].strip())
        whole = re.sub(r"\s+", " ", stripped)
        scope = stack[-1][0] if stack and depth == stack[-1][1] else None
        if stripped and not stripped.startswith("//"):
            name = member_name(code, inside_class=scope is not None)
            if name is not None and (scope is not None or not stack):
                out.setdefault((scope or "", name), whole)
        opener = CLASS_OPEN.match(code)
        if opener and not code.endswith(";"):
            pending = opener.group(1)
        for char in code:
            if char == "{":
                depth += 1
                if pending is not None:
                    stack.append((pending, depth))
                    pending = None
            elif char == "}":
                if stack and stack[-1][1] == depth:
                    stack.pop()
                depth -= 1
    return out


def member_name(code, inside_class):
    """The identifier a data-member or typedef line declares, else None."""
    if not code.endswith(";") or KEYWORD.match(code):
        return None
    typedef = TYPEDEF.match(code)
    if typedef:
        return typedef.group(1)
    if not inside_class or "(" in code or ")" in code or "=" in code:
        return None
    match = DATA_MEMBER.match(code)
    return match.group(1) if match else None


def conflicts(root, files):
    """[(class, member, {file: declaration})] where siblings contradict each other."""
    seen = {}
    for rel in files:
        for key, text in declared_members(read_text(root / rel)).items():
            seen.setdefault(key, {})[rel] = text
    out = []
    for (scope, name), byfile in sorted(seen.items()):
        if len(set(byfile.values())) > 1:
            out.append((scope, name, byfile))
    return out


# -------------------------------------------------------------------- modes ---

def do_list(root):
    clusters, declared = scan(root)
    multi = {dest: files for dest, files in clusters.items() if len(files) > 1}
    # Marker LINES and cluster MEMBERSHIPS are different totals -- a file naming
    # two destinations is two lines and one member of each cluster -- so print
    # both rather than one number that answers whichever question you had.
    print(f"{sum(len(found) for found in declared.values())} marker line(s) in "
          f"{len(declared)} file(s) name {len(clusters)} destination(s); "
          f"{len(multi)} destination(s) hold two or more files, "
          f"{len(set().union(*multi.values()))} files in all")
    for dest, files in sorted(multi.items(), key=lambda item: (-len(item[1]), item[0])):
        print(f"{len(files):>4}  {dest}")
    return 0


def do_plan(root, dest, only):
    clusters, declared = scan(root)
    files = clusters.get(dest)
    if not files:
        fail(f"no file carries a `readable body of ...: {dest}` marker")
    chosen = check_only(root, only, files, dest) if only else files
    owned = ledger_index(root, set(chosen) | {dest})

    lines = [read_text(root / rel).count("\n") for rel in chosen]   # what wc -l counts
    print(f"cluster {dest}: {len(files)} file(s) carry a marker, "
          f"{len(owned[dest])} row(s) already land there")
    print(f"planning {len(chosen)} of them, {sum(lines)} lines:")
    sets = [set(declarations(read_text(root / rel))) for rel in chosen]
    common = set.intersection(*sets)
    # Rows owned vs rows a marker actually sends here. These are usually equal;
    # when they are not, --apply moves only the marked ones and keeps the donor,
    # and seeing "2 of 20" BEFORE applying is what tells you the file is a
    # partial donor rather than a whole one. Without it the only way to know was
    # `grep -c ',<donor>,' reverse/functions.csv` by hand.
    for rel, own, count in zip(chosen, sets, lines):
        marked = [n for n in owned[rel] if claims(declared[rel], dest, n)]
        share = (f"{len(marked)} of {len(owned[rel])} row(s) marked for {dest}"
                 if len(marked) != len(owned[rel]) else f"{len(owned[rel])} row(s)")
        print(f"  {rel}  ({count} lines, {share}, "
              f"{len(own - common)} unique declaration(s))")
    partial = [(rel, [n for n in owned[rel] if claims(declared[rel], dest, n)])
               for rel in chosen]
    partial = [(rel, marked) for rel, marked in partial if len(marked) != len(owned[rel])]
    if partial:
        print(f"  {len(partial)} PARTIAL donor(s) — --apply moves only the marked rows "
              f"and keeps the file:")
        for rel, marked in partial:
            for name in sorted(set(owned[rel]) - set(marked)):
                print(f"      {rel} keeps {name}")
    thunks = thunk_donors(root, set(chosen))
    if thunks:
        print(f"  {len(thunks)} THUNK-ONLY donor(s) — every row is <= {THUNK_BYTES} bytes, so the")
        print(f"      donor holds no body. Folding one DELETES {dest}'s readable body and")
        print(f"      leaves a forwarding stub. Decode the jump target first: if it is still")
        print(f"      an unconverted dump, the destination is the only readable statement of")
        print(f"      that function and the merge is a net loss the file count will not show.")
        for rel in sorted(thunks):
            print(f"      {rel}")
    print(f"  declarations common to ALL {len(chosen)} (free to hoist): {len(common)}")
    differing = sorted(set.union(*sets) - common)
    print(f"  declarations needing reconciliation: {len(differing)}")
    for text in differing:
        print(f"      {text}")

    clashes = conflicts(root, chosen)
    print(f"  members declared differently by two siblings (must be reconciled "
          f"before --apply): {len(clashes)}")
    for scope, name, byfile in clashes:
        print(f"      {scope + '::' if scope else ''}{name}")
        for rel, text in sorted(byfile.items()):
            print(f"        {rel}: {text}")

    stray = unclustered(root, files, declared, dest)
    print(f"  un-clustered siblings (ledgered, no marker for this destination, "
          f"out of scope): {len(stray)}")
    for rel in stray:
        print(f"      {rel}")
    return 0


def unclustered(root, files, declared, dest):
    """Ledgered files sitting beside a cluster member and named like one, which
    carry no marker for `dest`. They are out of scope by design; printing them is
    what keeps "the cluster" from quietly meaning "the part of it with markers"."""
    prefixes = set()
    for rel in files:
        stem = Path(rel).name
        if "_" in stem:
            prefixes.add((str(Path(rel).parent), stem.split("_", 1)[0] + "_"))
    candidates = set()
    for parent, prefix in prefixes:
        for path in sorted((root / parent).iterdir()):
            rel = path.relative_to(root).as_posix()
            if (path.name.startswith(prefix) and path.name.endswith(SRC_EXT)
                    and rel not in files
                    and dest not in [d for _s, d in declared.get(rel, [])]):
                candidates.add(rel)
    owned = ledger_index(root, candidates)
    return sorted(rel for rel in candidates if owned[rel])


def do_apply(root, dest, into, only):
    clusters, declared = scan(root)
    files = clusters.get(dest)
    if not files:
        fail(f"no file carries a `readable body of ...: {dest}` marker")
    chosen = check_only(root, only, files, dest)
    into_rel = relative(root, into)
    if not (root / into_rel).exists():
        fail(f"--into {into_rel} does not exist on disk",
             "write the merged translation unit first: --apply repoints rows and "
             "deletes donors, it never synthesises a body")
    if into_rel in chosen:
        fail(f"--into {into_rel} is also named by --only; a file cannot be its own donor")

    clashes = conflicts(root, chosen)
    if clashes:
        detail = []
        for scope, name, byfile in clashes:
            detail.append(f"  {scope + '::' if scope else ''}{name}")
            for rel, text in sorted(byfile.items()):
                detail.append(f"    {rel}: {text}")
        fail(f"{len(clashes)} member(s) are declared differently by the siblings being "
             f"merged — one TU cannot hold both:", *detail,
             "reconcile them in the merged file and re-run (python3 tools/merge_cluster.py "
             f"--plan {dest} --only ...)")

    owned = ledger_index(root, set(chosen))
    moving, keep_donor = {}, {}
    for rel in chosen:
        elsewhere = sorted({d for _s, d in declared[rel] if d != dest})
        # A marker names a SYMBOL, so the rows bound for `dest` are the rows this
        # donor owns whose symbol one of its markers for `dest` names -- always,
        # not only when the donor also serves another destination. Selecting by
        # donor file alone moved every row a donor owned: 2 markers on
        # SkirmishBattleHonorsLoyalGames.cpp repointed all 20 of its rows and
        # deleted it, orphaning 18 bodies. The build caught it, but the tool
        # promised this in its own docstring and did the opposite.
        names = [name for name in owned[rel] if claims(declared[rel], dest, name)]
        if not names:
            fail(f"--only names {rel}, which owns no ledger row bound for {dest}",
                 "its marker and the ledger disagree; fix one before merging")
        moving[rel] = set(names)
        # Rows no marker assigns here stay, and a donor still owning one keeps its
        # file -- the same protection a donor bound for a second destination
        # already had, at row granularity rather than file granularity. Deleting
        # it would leave those rows naming a path that does not exist.
        left = [name for name in owned[rel] if name not in moving[rel]]
        if elsewhere or left:
            keep_donor[rel] = (elsewhere, left)
    for rel in moving:
        if rel not in files:
            fail(f"row owner {rel} is not in the cluster for {dest}")

    written = rewrite_ledger(root, moving, into_rel)
    expected = sum(len(names) for names in moving.values())
    if written != expected:
        fail(f"repointed {written} row(s) but {expected} were selected — the ledger "
             "changed under the lock; re-run after python3 tools/check_csv.py")

    stripped = {rel: strip_markers(root / rel, dest) for rel in sorted(keep_donor)}
    removed = sorted(rel for rel in chosen if rel not in keep_donor)
    for rel in removed:
        (root / rel).unlink()

    print(f"merge_cluster: {dest} -> {into_rel}")
    for rel in sorted(moving):
        for name in sorted(moving[rel]):
            print(f"  repointed {name}")
            print(f"            from {rel}")
    print(f"  deleted {len(removed)} donor(s) with nothing left:")
    for rel in removed:
        print(f"      {rel}")
    print(f"  kept {len(keep_donor)} donor(s) that still own rows:")
    for rel, (elsewhere, left) in sorted(keep_donor.items()):
        why = []
        if left:
            why.append(f"{len(left)} row(s) no marker sends to {dest}")
        if elsewhere:
            why.append(f"still bound for {', '.join(elsewhere)}")
        print(f"      {rel} ({stripped[rel]} marker line(s) dropped, {'; '.join(why)})")
    remaining = [rel for rel in files if rel not in removed]
    print(f"  cluster now: {len(remaining)} file(s) still carry a marker for {dest}")
    stage(root, [into_rel, LEDGER, *removed, *sorted(keep_donor)])
    return 0


def claims(found, dest, name):
    """Does one of this file's markers for `dest` name the ledger symbol `name`?

    Markers are often written truncated at an `@@` (`?parseSoundsList@INI@@` for
    `?parseSoundsList@INI@@SAXPAV1@PAX1PBX@Z`), the same prefix rule
    tools/add_match.py:strip_marker applies."""
    return any(d == dest and (symbol == name or name.startswith(symbol))
               for symbol, d in found)


def check_only(root, only, files, dest):
    chosen = []
    for entry in only:
        rel = relative(root, entry)
        if rel not in files:
            fail(f"--only names {rel}, which carries no "
                 f"`readable body of ...: {dest}` marker",
                 "the marker is the only definition of cluster membership; "
                 f"python3 tools/merge_cluster.py --plan {dest} lists the members")
        if rel in chosen:
            fail(f"--only names {rel} twice")
        chosen.append(rel)
    return chosen


def relative(root, entry):
    path = Path(entry)
    if not path.is_absolute():
        return path.as_posix().lstrip("./")
    try:
        return path.resolve().relative_to(root).as_posix()
    except ValueError:
        fail(f"{entry} is not under {root}")


def rewrite_ledger(root, moving, into_rel):
    """Repoint the selected rows in place, under the lock every ledger writer holds.

    Streamed record by record into a sibling temp file and renamed over, so a
    22 MB ledger is never held whole and a crash cannot leave a half-written one.
    """
    path = ledger_path(root)
    handle = (root / LOCK).open("a")
    lock(handle, exclusive=True,
         wait_notice="merge_cluster: waiting for ledger lock (another writer is running)...")
    scratch = path.with_name(f"{path.name}.{os.getpid()}.tmp")
    written = 0
    try:
        with open(scratch, "wb") as out:
            for number, payload, term in records(path):
                if number > 1:
                    row = ledger_io.fields(payload)
                    if row and row[SOURCE_AT] in moving and row[NAME_AT] in moving[row[SOURCE_AT]]:
                        payload = repoint(payload, number, into_rel)
                        written += 1
                out.write(payload + term)
        os.replace(scratch, path)
    finally:
        if scratch.exists():
            scratch.unlink()
        unlock(handle)
        handle.close()
    return written


def strip_markers(path, dest):
    """Drop only this destination's marker lines from a donor that stays.

    Byte-level line surgery so the file's own line endings survive untouched."""
    lines = path.read_bytes().splitlines(keepends=True)
    kept = []
    for line in lines:
        match = MARKER.match(line.decode("utf-8", "replace").rstrip("\r\n"))
        if match and match.group(2) == dest:
            continue
        kept.append(line)
    path.write_bytes(b"".join(kept))
    return len(lines) - len(kept)


def stage(root, paths):
    done = subprocess.run(["git", "-C", str(root), "add", "--", *dict.fromkeys(paths)],
                          capture_output=True, text=True)
    if done.returncode:
        fail(f"the merge is on disk but `git add` failed: {done.stderr.strip()}",
             "stage it yourself: git add -- " + " ".join(dict.fromkeys(paths)))
    print("  staged: " + " ".join(dict.fromkeys(paths)))


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--list", action="store_true",
                      help="destinations with two or more files, largest cluster first")
    mode.add_argument("--plan", metavar="DEST",
                      help="report one cluster's files and their declarations")
    mode.add_argument("--apply", metavar="DEST",
                      help="repoint --only's rows at --into and delete the drained donors")
    parser.add_argument("--into", metavar="PATH",
                        help="the merged translation unit, which must already exist")
    parser.add_argument("--only", nargs="+", default=[], metavar="FILE",
                        help="the cluster members this merge consumes (required "
                             "with --apply; narrows the report with --plan)")
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                        help="repository to operate on (default: this repo)")
    args = parser.parse_args(argv)
    root = args.root.resolve()

    if args.list:
        if args.only or args.into:
            fail("--list takes neither --only nor --into")
        return do_list(root)
    if args.plan is not None:
        if args.into:
            fail("--into belongs to --apply, not --plan")
        return do_plan(root, args.plan, args.only)
    if not args.into:
        fail("--apply needs --into PATH naming the merged translation unit")
    if not args.only:
        fail("--apply needs --only FILE...: it is required, not optional",
             "clusters run to 62 files; merging one whole in a single commit is "
             "unreviewable and would repoint rows for bodies the merged TU does "
             "not contain")
    return do_apply(root, args.apply, args.into, args.only)


if __name__ == "__main__":
    sys.exit(main())
