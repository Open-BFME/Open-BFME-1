#!/usr/bin/env python3
"""Rename address-derived source files whose ledger rows already carry a real name.

788 files are called things like `Rva0071C0E0Whatever.cpp` while the only rows they
own are already spelled `?updateSway@W3DShrubBuffer@@QAEXXZ`. The identity is
settled; only the file name still hides it. That makes this the one rename lane
with NO naming judgement in it, so it belongs in a script rather than in an agent
at four minutes a file -- and a script can refuse the ambiguous cases uniformly
instead of each agent inventing its own answer.

The refusals are the point. This tool renames a file only when the new name follows
from rows it already owns; anything else is left for a human or an agent with
evidence. It never invents a name, never merges files, and never touches a row's
`name` column.

  python3 tools/rename_addressed_sources.py --plan [--under DIR] [--limit N]
  python3 tools/rename_addressed_sources.py --apply --limit 20 [--under DIR]

--apply stages nothing and commits nothing: it does `git mv` and rewrites the
ledger, then you gate and commit the batch yourself. Keep batches small; every
renamed path is a cold compile, which is exactly what makes the gate meaningful.
"""
import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ledger_io
import merge_cluster as mc
import readability_metric as rm
from portable_lock import lock, unlock

ROOT = Path(__file__).resolve().parents[1]

# The families the tree uses for "I do not know what this is yet". Kept in step
# with readability_metric.PLACEHOLDER, which is what scores the Ident axis.
ADDRESSED = re.compile(
    r'^(?:Rva|Gen_?|gen|Bfme|S\d|Q\d|Y\d|Open\d|Glo|Made|D|promoted__)[0-9A-Fa-f]{3,}',
    re.I)
SPELLED = re.compile(
    r'^Bfme(?:One|Two|Three|Four|Five|Six|Seven|Eight|Nine|Ten|Eleven|Twelve|'
    r'Thirteen|Fourteen|Fifteen|Sixteen|Seventeen|Eighteen|Nineteen|Twenty|'
    r'Thirty|Forty|Fifty|Sixty|Seventy|Eighty|Ninety|Hundred)', re.I)

# Any name from a family the tree uses for "not identified yet", hex or not. A
# proposed file name matching this is not an improvement, whatever the ledger row
# happens to be spelled.
PLACEHOLDER_FAMILY = re.compile(
    r'^_?(?:Rva|Gen_?|gen|Bfme|Made|Glo|Open\d|promoted__|[SQY]\d|d_|dup_|sub_|uw_)',
    re.I)
# An embedded address is just as opaque as a leading one: `get_007164b0` and
# `Register_Rva009723C0_Prototype` both pass the prefix test above and neither is
# an answer. What makes a token an address is a long hex run CONTAINING A DIGIT --
# requiring the digit is what keeps real words out, since `Facade` and `Decade`
# are six hex characters each and no more address-like than `Cull`.
HEX_RUN = re.compile(r'[0-9A-Fa-f]{6,}')


def opaque(stem):
    """True when this basename still hides what the file holds."""
    if PLACEHOLDER_FAMILY.match(stem):
        return True
    return any(any(c.isdigit() for c in run) for run in HEX_RUN.findall(stem))

IDENT = r'[A-Za-z_][A-Za-z0-9_]*'
METHOD = re.compile(r'^\?(%s)@(%s)@@' % (IDENT, IDENT))          # ?method@Class@@
FREE = re.compile(r'^\?(%s)@@Y' % IDENT)                          # ?fn@@YA...
CTOR = re.compile(r'^\?\?0(%s)@@' % IDENT)                        # ??0Class@@
DTOR = re.compile(r'^\?\?1(%s)@@' % IDENT)                        # ??1Class@@
PLAIN = re.compile(r'^_?(%s)$' % IDENT)                           # extern "C"


def identity(name):
    """(class_or_None, member) for a mangled name, or None when this tool must
    not guess. Operators, templates (?$) and the compiler's own glue (??_G and
    friends) all land in the None branch deliberately: their spelling does not
    make a filename anybody wants, and a wrong guess here is silent."""
    for pattern, kind in ((CTOR, "ctor"), (DTOR, "dtor")):
        hit = pattern.match(name)
        if hit:
            return hit.group(1), kind
    hit = METHOD.match(name)
    if hit:
        return hit.group(2), hit.group(1)
    hit = FREE.match(name)
    if hit:
        return None, hit.group(1)
    hit = PLAIN.match(name)
    if hit:
        return None, hit.group(1)
    return None


def proposal(rows):
    """The basename these rows justify, or (None, reason)."""
    ids = [identity(n) for n in rows]
    if any(i is None for i in ids):
        return None, "a row's mangled name is an operator, template or compiler glue"
    classes = {c for c, _ in ids if c}
    if len(classes) > 1:
        return None, "rows span %d classes (%s)" % (len(classes), ", ".join(sorted(classes)))
    if len(rows) == 1:
        owner, member = ids[0]
        return ("%s_%s" % (owner, member)) if owner else member, None
    if not classes:
        return None, "several free functions with no shared owner"
    return sorted(classes)[0], None


def ledger_rows(root):
    """source -> [name] for every matched, hand-written row. One streamed pass:
    AGENTS.md forbids loading functions.csv wholesale, and it is 161k rows."""
    raw = mc.ledger_path(root).read_bytes()
    owned = {}
    for payload, _term in ledger_io.split_records(raw)[1:]:
        parts = ledger_io.fields(payload)
        if len(parts) < 6:
            continue
        source = parts[mc.SOURCE_AT]
        if not source.startswith("Code/") or not source.endswith(".cpp"):
            continue
        if "/gen_asm/" in source or "/gen_small/" in source or "/masm_dumps/" in source:
            continue
        if parts[5] != "matched":
            continue
        owned.setdefault(source, []).append(parts[0])
    return owned


def candidates(root, under):
    owned = ledger_rows(root)
    taken = {s.lower() for s in owned}
    picked, refused = [], []
    for source in sorted(owned):
        base = os.path.basename(source)[:-4]
        if not (ADDRESSED.match(base) or SPELLED.match(base)):
            continue
        if under and not source.startswith(under):
            continue
        names = owned[source]
        placeholders = [n for n in names if rm.PLACEHOLDER.search(n)]
        if placeholders:
            refused.append((source, "row still placeholder-named: %s" % placeholders[0]))
            continue
        stem, why = proposal(names)
        if stem is None:
            refused.append((source, why))
            continue
        # The new name has to be an IMPROVEMENT, and checking the row against
        # PLACEHOLDER is not enough to know that. `??0Rva006D51B0@@QAE@II@Z` is a
        # constructor of an address-named class, but the `??0` prefix ends in a
        # digit, so there is no word boundary before `Rva` and PLACEHOLDER never
        # fires -- the row reads as semantic and the rename produces
        # `Rva006D51B0_ctor.cpp`, which hides exactly as much as it did before.
        # Judging the proposed stem instead is independent of that blind spot:
        # whatever the row is called, a name from a placeholder family is not an
        # answer. This refuses `Bfme5BasedListCtor.cpp -> Gen_000FDA80.cpp` too,
        # which the row check let through and which is strictly worse.
        if opaque(stem):
            refused.append((source, "proposed name %s is itself a placeholder" % stem))
            continue
        target = "%s/%s.cpp" % (os.path.dirname(source), stem)
        # Case-insensitive, because .githooks/pre-commit rejects two tracked paths
        # that differ only in case: they cannot both check out on Windows/macOS.
        if target.lower() in taken or (root / target).exists():
            refused.append((source, "target %s already exists" % target))
            continue
        taken.add(target.lower())
        picked.append((source, target, len(names)))
    return picked, refused


def apply(root, picked):
    """Move the files and repoint their rows, holding the lock every ledger writer
    holds. Without it a read-modify-write of the whole 22 MB ledger silently drops
    any row another agent appended in between -- and this tree takes continuous
    concurrent pushes, so that window is the normal state, not a rare race. Streamed
    record by record into a sibling temp file, the same shape merge_cluster uses."""
    path = mc.ledger_path(root)
    moves = dict((old, new) for old, new, _ in picked)
    handle = (root / mc.LOCK).open("a")
    lock(handle, exclusive=True,
         wait_notice="rename_addressed_sources: waiting for the ledger lock...")
    scratch = path.with_name("%s.%d.tmp" % (path.name, os.getpid()))
    changed = 0
    try:
        with open(scratch, "wb") as out:
            for number, payload, term in mc.records(path):
                if number > 1:
                    row = ledger_io.fields(payload)
                    if row and row[mc.SOURCE_AT] in moves:
                        payload = mc.repoint(payload, number, moves[row[mc.SOURCE_AT]])
                        changed += 1
                out.write(payload + term)
        for old, new in moves.items():
            subprocess.run(["git", "-C", str(root), "mv", old, new], check=True)
            # git mv stages both paths and this worktree is shared with other
            # agents; an unstaged rename is the caller's to commit, a staged one
            # is something a sibling's commit can carry away.
            subprocess.run(["git", "-C", str(root), "restore", "--staged", old, new],
                           check=True)
        os.replace(scratch, path)
    finally:
        if scratch.exists():
            scratch.unlink()
        unlock(handle)
        handle.close()
    return changed


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--apply", action="store_true",
                        help="perform the renames (default: print the plan only)")
    parser.add_argument("--under", default="", metavar="DIR",
                        help="restrict to sources under this repo-relative directory")
    parser.add_argument("--limit", type=int, default=0, metavar="N",
                        help="take at most N files, so a batch stays gateable")
    parser.add_argument("--show-refusals", action="store_true")
    args = parser.parse_args(argv)

    picked, refused = candidates(ROOT, args.under)
    if args.limit:
        picked = picked[:args.limit]

    for old, new, rows in picked:
        print("%s -> %s   (%d row%s)" % (old, new, rows, "" if rows == 1 else "s"))
    print("\n%d renameable, %d refused%s" %
          (len(picked), len(refused), " (--show-refusals to list)" if refused else ""))
    if args.show_refusals:
        for source, why in refused:
            print("  REFUSED %s: %s" % (source, why))

    if args.apply and picked:
        changed = apply(ROOT, picked)
        print("\napplied: %d file(s) moved, %d ledger row(s) repointed" %
              (len(picked), changed))
        print("now gate them:  ./build.sh %s" %
              " ".join(new for _, new, _ in picked[:8]) +
              (" ..." if len(picked) > 8 else ""))
    return 0


if __name__ == "__main__":
    sys.exit(main())
