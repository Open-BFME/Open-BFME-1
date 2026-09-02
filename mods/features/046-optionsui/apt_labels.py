#!/usr/bin/env python3
"""Relabel the Options screen for the Open-BFME build.

The visible labels are `$`-prefixed tokens inside Options.apt that the runtime
resolves against the string table -- but a string with NO `$` renders literally,
so a replacement needs no CSF entry.

The movie is a memory image addressed by file offset, so a replacement may not
be longer than the slot the original sits in (its own bytes plus the padding
before the next string). Every substitution below is checked against that and
the build fails rather than shifting anything.

    python3 apt_labels.py <retail apt/options.big> <output .big>
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[3] / "tools"))
import bigpack  # noqa: E402

# Only the three checkboxes 046-optionsui actually takes over are renamed.
# Relabelling a widget whose meaning we do NOT take over would be a lie: it
# would still do the thing its old label said.
LABELS = {
    b"$EnableHealthBars":      b"Camera: rotate",
    b"$ShowUnitDecals":        b"Camera: tilt",
    b"$AlternativeMouseSetUp": b"Camera: free zoom",
    b"$OPTIONS":               b"OPEN-BFME",
}


def slots(movie, tokens):
    """-> {token: bytes available}, from where each token starts to the next."""
    found = sorted((movie.find(t), t) for t in tokens if movie.find(t) >= 0)
    out = {}
    for i, (off, tok) in enumerate(found):
        nxt = found[i + 1][0] if i + 1 < len(found) else off + len(tok) + 1
        out[tok] = nxt - off
    return out


def relabel(movie, labels):
    # Measure every string in the pool, not just the ones being replaced, so a
    # slot is never overstated by a neighbour that happens not to be listed.
    anchors = sorted(set(labels) | _neighbours(movie, labels))
    room = slots(movie, anchors)
    for tok, new in labels.items():
        off = movie.find(tok)
        if off < 0:
            raise SystemExit(f"{tok.decode()} is not in this movie")
        have = room[tok]
        if len(new) + 1 > have:
            raise SystemExit(f"{new.decode()!r} needs {len(new)+1} bytes but "
                             f"{tok.decode()} only has {have}")
        movie = movie[:off] + new + b"\0" * (have - len(new)) + movie[off + have:]
    return movie


def _neighbours(movie, labels):
    """Every `$token` in the pool, so slot sizes are measured against reality."""
    out, i = set(), 0
    while True:
        i = movie.find(b"$", i)
        if i < 0:
            return out
        j = i
        while j < len(movie) and 32 <= movie[j] < 127:
            j += 1
        if 2 < j - i < 40 and movie[j] == 0:
            out.add(movie[i:j])
        i = j + 1


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    files = bigpack.read(sys.argv[1])
    magic, align, gap, bias = bigpack.conventions_of(sys.argv[1])
    out = []
    for name, blob in files:
        if name == "Options.apt":
            before = blob
            blob = relabel(blob, LABELS)
            if len(blob) != len(before):
                raise SystemExit("the movie changed length; that is never correct here")
            for tok, new in LABELS.items():
                print(f"  {tok.decode():24} -> {new.decode()}")
        out.append((name, blob))
    n = bigpack.write(sys.argv[2], out, magic=magic, align=align, gap=gap,
                      header_bias=bias)
    print(f"wrote {sys.argv[2]} ({n} bytes)")


if __name__ == "__main__":
    main()
