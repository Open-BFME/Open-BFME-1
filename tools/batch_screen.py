"""Screen EVERY marker on a destination with ONE compile.

marker_screen.py answers a single (donor, symbol) question and pays two compiles
for it, so a destination carrying 65 markers costs 130 builds. But a marker is a
COMMENT: it cannot change what the compiler emits. So the destination's object
already contains every body those markers name, and one compile answers all of
them.

That is the whole idea, and it is what made a 273-destination sweep affordable --
roughly 270 builds instead of 2,000. The sweep it paid for is also the reason to
be careful with the answer: of ~3,000 markers screened that way, ~2,000 named no
ledger row at all, ~490 were real misses, and 46 MATCH verdicts collapsed to 16
distinct symbols. A MATCH is rare and worth acting on; the rest is inventory.

THIS TOOL NEVER WRITES. marker_screen has to clear a marker and restore it, and
its tests exist because an interrupted screen that leaves the marker cleared is
worse than a failed one. Here there is nothing to restore, because nothing is
edited -- not the source, not the ledger. Keep it that way: the moment this
starts editing to get a better answer it needs marker_screen's restore
machinery, and it is no longer the cheap tool.

A destination whose COMPILE fails is reported once, on its own line. It is not
reported as N failing markers: one broken TU is one fact, and printing it 65
times buries the destinations that did compile.

Usage:
  python3 tools/batch_screen.py <destination.cpp> [more.cpp ...]
  python3 tools/batch_screen.py --all          # every destination carrying a marker
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402

MARKER = re.compile(r"^\s*//\s*(\S+)\s+present-unmatched\b", re.MULTILINE)


def resolve(names, symbol):
    """A third of markers name their symbol WITHOUT its signature -- `??0Foo@@`
    rather than the full mangled name -- and those match no ledger key directly.
    Resolve by prefix, but only when the answer is unambiguous: overloads share
    an abbreviated label, and picking one of two would be a guess dressed as a
    lookup."""
    if symbol in names:
        return symbol
    if not symbol.endswith("@@"):
        return None
    hits = [n for n in names if n.startswith(symbol)]
    if len(hits) == 1:
        return hits[0]
    return "ambiguous" if hits else None


def markers(dest):
    text = (B.ROOT / dest).read_text(encoding="utf-8", errors="replace")
    return MARKER.findall(text)


def screen(dest, rows=None, symbol_map=None):
    """Yield (symbol, verdict, detail) for every marker on one destination.

    verdict is one of: MATCH, miss, no-row, ambiguous, error. `detail` carries
    the miss count, the owning donor, or the failure text.
    """
    rows = B.load_function_rows() if rows is None else rows
    by_name = {r["name"]: r for r in rows}
    labels = markers(dest)
    if not labels:
        return

    resolved = []
    for label in labels:
        full = resolve(by_name, label)
        resolved.append((label, full))
    wanted = {f for _, f in resolved if f and f != "ambiguous"}

    source = B.ROOT / dest
    output = B.obj_path(source)
    try:
        B.compile_source(source, output)
    except BaseException as exc:            # noqa: BLE001 - reported, not swallowed
        yield (dest, "compile-error", str(exc).splitlines()[0][:200])
        return
    if symbol_map is None:
        symbol_map = B.load_symbol_map()

    for label, full in resolved:
        if full is None:
            yield (label, "no-row", "")
            continue
        if full == "ambiguous":
            yield (label, "ambiguous", "truncated label matches more than one row")
            continue
        row = dict(by_name[full])
        owner = row["source"]
        row["source"] = dest
        try:
            patch = B.compile_function(row, symbol_map, output)
        except BaseException as exc:        # noqa: BLE001
            yield (full, "error", str(exc).splitlines()[0][:160])
            continue
        if patch["bytes"] == patch["target"]:
            # How many rows would move with this donor: every row it owns that a
            # marker on THIS destination names. One means --only can land it as
            # it stands; more means --symbols, or a donor that is not all green.
            moves = sum(1 for r in rows if r["source"] == owner and r["name"] in wanted)
            yield (full, "MATCH", "donor=%s moves=%d" % (owner, moves))
        else:
            n = sum(1 for a, b in zip(patch["bytes"], patch["target"]) if a != b)
            yield (full, "miss", str(n))


def destinations():
    out = set()
    for path in sorted((B.ROOT / "Code").rglob("*.cpp")):
        rel = path.relative_to(B.ROOT).as_posix()
        if MARKER.search(path.read_text(encoding="utf-8", errors="replace")):
            out.add(rel)
    return sorted(out)


def main(argv):
    dests = destinations() if argv[:1] == ["--all"] else argv
    if not dests:
        print(__doc__.strip().splitlines()[-2])
        return 1
    tally = {}
    rows = B.load_function_rows()
    symbol_map = B.load_symbol_map()
    for dest in dests:
        n = len(markers(dest))
        print("%s: %d marker(s), one compile" % (dest, n))
        for name, verdict, detail in screen(dest, rows, symbol_map):
            if verdict == "compile-error":
                print("  DESTINATION DID NOT COMPILE: %s" % detail)
            elif verdict == "MATCH":
                print("  %-58s MATCH  %s" % (name[:58], detail))
            elif verdict == "miss":
                print("  %-58s miss(%s)" % (name[:58], detail))
            else:
                print("  %-58s %s %s" % (name[:58], verdict, detail))
            tally[verdict] = tally.get(verdict, 0) + 1
    print("\nverdicts: " + ", ".join("%s=%d" % kv for kv in sorted(tally.items())))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
