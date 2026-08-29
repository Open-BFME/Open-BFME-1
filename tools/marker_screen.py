#!/usr/bin/env python3
"""Measure how far a cluster donor's destination is from retail, without landing it.

`merge_cluster.py --plan` says which donors a destination owns; it cannot say
which of them are one instruction away and which are a different function. That
distinction decides the whole work item, and reading the two bodies to find it
costs far more than measuring it: the destination usually already contains a
readable body, and the only question is what the compiler does with it.

So: clear the destination's `present-unmatched` marker for one symbol, require
the destination's own rows to stay green, then hand the row's RVA and size to
explain_mismatch with `--source <destination>`. Two compiles, no judgement, and
the file is restored unless it matched. Nothing is applied and the ledger is
never touched, so a miss costs nothing to abandon.

Three verdicts are worth acting on and the rest are triage:

  MATCH            the destination already produces retail's bytes and the row
                   is pointing at the donor for no reason. `--apply` and commit.
                   Two turned up in one afternoon: INI::parseObjectCreationList
                   and DX8Wrapper::Set_Shader.
  miss(1..6)       a layout or slot difference, which a TU-local view reaches.
                   This is where the work is.
  DEST-RED         the marker was load-bearing, or the destination is red for a
                   reason of its own. Look before assuming it is yours.

Two verdicts are dead ends and both are free, before any compile runs:

  OBJECT-SYMBOL    the row's notes pin it to a spelling that is not its name and
                   build.py reads THAT out of the object. If the destination
                   cannot emit it -- an ICF twin's name, a donor-private wrapper
                   -- no source change will help. 1,662 of 4,402 cluster-donor
                   rows carry one of these notes.
  no-marker-pair   the destination has no `byte-exact reconstruction:` +
                   `present-unmatched` pair for this symbol, so there is nothing
                   to consume. Sometimes it means the destination has no body at
                   all and the marker is asking for authoring, not repointing.
  ambiguous-marker a truncated marker matching more than one row the donor owns.
                   Twelve of these; they need the marker spelled out, not a guess.

A THIRD of the markers name their symbol WITHOUT its signature -- `??0Foo@@`
rather than `??0Foo@@QAE@PAVThing@@PBVModuleData@@@Z`. 302 of 1035, and they are
invisible to any tool that looks a marker up in functions.csv directly, which is
how a 23-donor "family" screen missed a 24th member whose marker happened to be
truncated. Resolution is unambiguous almost always: take the rows the DONOR owns
whose symbol starts with the marker's spelling, and if exactly one matches, that
is it. That is what `resolve` below does, and it is why --queue reports 1023 and
not 721.

A match prints "OK: bytes match" and NO Disassembly section, so do not detect one
by counting diff lines -- an errored run also has zero.

Usage:
  python3 tools/marker_screen.py <donor> <destination> <symbol>
  python3 tools/marker_screen.py --queue          # every donor, smallest first
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

_rows = {}
_notes = {}
for _line in open(ROOT / "reverse" / "functions.csv", "rb"):
    _f = _line.decode("utf-8", "replace").split(",")
    if len(_f) > 5 and _f[2].startswith("0x"):
        _rows[_f[0]] = (_f[2], _f[3], _f[4])
        _notes[_f[0]] = ",".join(_f[5:])


_by_source = {}
for _sym, (_rva, _size, _src) in _rows.items():
    _by_source.setdefault(_src, []).append(_sym)


def resolve(donor, symbol):
    """The full mangled name a marker means, or None / 'ambiguous'.

    A marker may name its symbol without the signature, and a third of them do.
    Only rows the DONOR owns are candidates, which is what keeps the prefix from
    matching an unrelated overload in another file."""
    if symbol in _rows:
        return symbol
    if not symbol.endswith("@@"):
        return None
    candidates = [s for s in _by_source.get(donor, []) if s.startswith(symbol)]
    if len(candidates) == 1:
        return candidates[0]
    return "ambiguous" if candidates else None


def markers():
    """Every (donor, destination, symbol) the markers name, smallest row first."""
    out = subprocess.run(["grep", "-rn", "readable body of ", "Code/"],
                         cwd=ROOT, capture_output=True, text=True).stdout
    pat = re.compile(r"^(.*?):\d+:// readable body of (\S+): (\S+)\s*$")
    seen, found = set(), []
    for line in out.splitlines():
        m = pat.match(line)
        if not m:
            continue
        donor, symbol, dest = m.group(1), m.group(2), m.group(3)
        full = resolve(donor, symbol)
        if not full or full == "ambiguous":
            continue
        row = _rows[full]
        if row[2] != donor:
            continue          # the donor does not own the row; not ours to move
        key = (donor, dest, symbol)
        if key in seen:
            continue
        seen.add(key)
        try:
            size = int(row[1])
        except ValueError:
            continue
        found.append((size, donor, dest, symbol))
    found.sort()
    return found


def screen(donor, dest, symbol):
    full = resolve(donor, symbol)
    if full == "ambiguous":
        return "ambiguous-marker"
    # An unresolved symbol is NOT a reason to bail here. The marker check and the
    # restore below are what this function must get right whatever the ledger
    # says, so the row is required only where the RVA is actually used.
    if full:
        note = re.search(r"object-symbol=([^;\r\n]*)", _notes.get(full, ""))
        if note and note.group(1) != full:
            return "OBJECT-SYMBOL: " + note.group(1)

    path = ROOT / dest
    original = path.read_bytes()
    text = original.decode("utf-8")
    marker = "// byte-exact reconstruction: %s\n// %s present-unmatched\n" % (donor, symbol)
    if text.count(marker) != 1:
        return "no-marker-pair"
    # read_bytes/write_bytes throughout: thirteen destinations hold CRLF blocks
    # inside otherwise-LF files and read_text would rewrite every one of them.
    path.write_bytes(text.replace(marker, "", 1).encode("utf-8"))
    # Every exit below either restores `original` or returns MATCH, which leaves
    # the clear in place on purpose. But a build timeout or a Ctrl-C between here
    # and those exits would strand the destination WITHOUT its marker, and a
    # missing marker is the state that makes the next build report a
    # stale-annotation pass that never compared a byte. So restore on any
    # unwind and re-raise.
    try:
        return _screen_cleared(path, original, dest, full)
    except BaseException:
        path.write_bytes(original)
        raise


def _screen_cleared(path, original, dest, full):
    built = subprocess.run(["./build.sh", dest], cwd=ROOT,
                           capture_output=True, text=True, timeout=1800)
    if "Functions: OK" not in built.stdout:
        path.write_bytes(original)
        failed = re.search(r"^  FAIL.*", built.stdout, re.M)
        return "DEST-RED: " + (failed.group(0).strip() if failed else "build error")

    if not full:
        path.write_bytes(original)
        return "no-row"
    rva, size, _ = _rows[full]
    diffed = subprocess.run(["python3", "tools/explain_mismatch.py", full,
                             "--rva", rva, "--size", size, "--source", dest],
                            cwd=ROOT, capture_output=True, text=True, timeout=1800)
    if "OK: bytes match" in diffed.stdout:
        return "MATCH"                       # left edited on purpose: go apply it
    path.write_bytes(original)
    body = diffed.stdout.split("Disassembly:", 1)[-1]
    diffs = len([l for l in body.split("\n") if l.startswith("!=")])
    if not diffs:
        tail = (diffed.stdout.strip() or diffed.stderr.strip()).split("\n")[-1]
        return "no-diff-shown: " + tail[:120]
    return "miss(%d)" % diffs


def main(argv):
    if argv[:1] == ["--queue"]:
        for size, donor, dest, symbol in markers():
            print("%5d\t%s\t%s\t%s" % (size, donor, dest, symbol))
        return 0
    if len(argv) != 3:
        raise SystemExit(__doc__)
    print(screen(*argv))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
