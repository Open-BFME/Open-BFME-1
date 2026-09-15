#!/usr/bin/env python3
"""The evidence pack must see through the incremental-link thunks and attach
string xrefs to the body that CONTAINS the referencing instruction.

Measured 2026-09-15 on 60 random anonymous dump bodies >= 300 B: direct E8
sites reached 3 of them; folding thunk-mediated sites reached 38. String xrefs
keyed by function start attached to ~4% of sites; keyed by owner they attach
wherever the site sits inside a claimed body. Both are retail facts, so the
assertions below hold regardless of which rows have landed."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "fleet"))
import context_pack  # noqa: E402

# 0x0006F200: 215-byte body whose only callers reach it through ILT thunks and
# whose body references the "GRAYSCALE"/"SOLID" literals.
RVA = 0x0006F200


def test_callers_fold_thunk_mediated_sites():
    lines = context_pack.pack(RVA)
    callers = [l for l in lines if l.lstrip().startswith("callers (")]
    assert callers, lines
    assert "via ILT thunk" in callers[0]


def test_strings_attach_by_containing_body():
    lines = context_pack.pack(RVA)
    strings = [l for l in lines if l.lstrip().startswith("strings:")]
    assert strings, lines
    assert "GRAYSCALE" in strings[0]


def test_thunk_map_is_built_once_and_large():
    context_pack._load()
    assert len(context_pack._thunks_of) > 10000
