#!/usr/bin/env python3
"""Which already-built objects DEFINE a symbol -- i.e. where a row could live.

Why this exists: a ledger row can be green only because a converted body calls
an accessor that RETAIL INLINES AWAY at that site. Write the body correctly and
MSVC stops emitting the inline function's COMDAT, and the row goes red -- the
fold is blocked by ledger OWNERSHIP, not by anything about the body. That has
happened seven times in the merge lane so far.

The fix, when there is one, is to repoint the row at a translation unit that
genuinely emits the symbol. Finding that TU by hand means guessing from grep
and then paying an add_match verification per guess; two of the four guesses
made that way were wrong, and each wrong one costs a full TU build.

This answers it directly instead. Every object under build/match is already
compiled, so the symbol table is right there: report every object that defines
the name, and the source each was built from. Nothing is compiled and nothing is
written.

    python3 tools/find_emitter.py '?getAction@Script@@QBEPAVScriptAction@@XZ'

A caller that does NOT appear here calls the symbol but does not emit it --
which is exactly the case that wasted a build on GameLogic.cpp for
Script::setAction. Emitting is what the ledger needs; calling is not enough.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build


def sources_by_object():
    """{obj path -> source path} for every source in the tree.

    Built by computing obj_path() FORWARD over the tree rather than decoding an
    object's name backwards: the encoding joins path parts with "_" and file
    names contain underscores too, so the reverse is ambiguous. The ledger's own
    rows are not enough either -- a TU that merely EMITS a symbol usually has no
    row claiming it, and those are precisely the ones worth finding.
    """
    out = {}
    for src in build.ROOT.joinpath("Code").rglob("*.cpp"):
        try:
            out[str(build.obj_path(src))] = str(src.relative_to(build.ROOT))
        except Exception:
            continue
    return out


def emitters(symbol):
    """Every built object whose symbol table defines `symbol`."""
    hits = []
    for obj in sorted(build.BUILD_DIR.glob("*.obj")):
        try:
            stat = obj.stat()
            _data, _sections, symbols = build._object_layout(
                str(obj), stat.st_mtime_ns, stat.st_size)
        except Exception:
            continue
        for s in symbols:
            if s["name"] == symbol and s["section"] > 0:
                hits.append(str(obj))
                break
    return hits


def main(argv):
    if len(argv) != 1:
        raise SystemExit("usage: find_emitter.py <mangled-symbol>")
    symbol = argv[0]
    owners = sources_by_object()
    hits = emitters(symbol)
    if not hits:
        print("%s: NO built object defines it." % symbol)
        print("  Nothing in the tree emits this symbol as things stand, so a row")
        print("  claiming it has no home. Either a body has to keep referencing it,")
        print("  or the row itself is wrong.")
        return 1
    known = [owners[o] for o in hits if o in owners]
    other = len(hits) - len(known)
    if not known:
        print("%s: %d object(s) define it, but NONE is a source in the tree." % (symbol, len(hits)))
        print("  Those are harvest or scratch objects, which cannot own a ledger row.")
        return 1
    print("%s is emitted by %d source(s) in the tree:" % (symbol, len(known)))
    for src in sorted(known):
        print("  %s" % src)
    if other:
        print("  (%d further object(s) define it but are harvest/scratch artefacts)" % other)
    print()
    print("Repoint with: python3 tools/add_match.py '%s' <rva> <size> <source> \\" % symbol)
    print("                  --replace-existing --notes '...'")
    print("It byte-verifies and reverts itself if the source does not reproduce it.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
