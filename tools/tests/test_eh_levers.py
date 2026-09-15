#!/usr/bin/env python3
"""eh_levers turns the mechanical EH levers into shape_search choices."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import eh_levers  # noqa: E402
import shape_search  # noqa: E402

SOURCE = """// ?foo@@YAXXZ
// partial score=0.90 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc-
#include "Common/AsciiString.h"
#include <map>
class GameWindow {
public:
\tWinInstanceData *winGetInstanceData(void);
\tInt winGetSize(Int *width, Int *height) const;
\tvirtual void setClipRegion(IRegion2D *region);
\tvoid already(void) throw();
\tvoid *operator new(size_t);
};
void foo(GameWindow *w)
{
\tif (w->winGetSize(0, 0))
\t\treturn;
}
"""


def levers(choices):
    return [c["lever"] for c in choices]


def test_throw_choices_target_bare_declarations_only():
    cs = eh_levers.choices_for(SOURCE, ("throw",), max_throw=10)
    befores = [c["before"].strip() for c in cs]
    assert "WinInstanceData *winGetInstanceData(void);" in befores
    assert "Int winGetSize(Int *width, Int *height) const;" in befores
    assert "virtual void setClipRegion(IRegion2D *region);" in befores
    assert all("already" not in b and "operator" not in b and "return" not in b for b in befores)
    assert all("\n" not in c["before"] for c in cs)
    const = next(c for c in cs if "const;" in c["before"])
    assert const["after"][0].strip().endswith("const throw();")


def test_ehsc_toggles_the_cl_line():
    cs = eh_levers.choices_for(SOURCE, ("ehsc",))
    assert levers(cs) == ["ehsc"] and cs[0]["after"] == ["// cl: /DNDEBUG /MD /EHsc"]
    flipped = SOURCE.replace("/EHsc-", "/EHsc")
    assert eh_levers.choices_for(flipped, ("ehsc",))[0]["after"] == ["// cl: /DNDEBUG /MD /EHsc-"]


def test_prefix_levers_merge_into_one_non_overlapping_choice():
    cs = eh_levers.choices_for(SOURCE, ("stlp", "nodelete"))
    assert levers(cs) == ["stlp+nodelete"]
    assert len(cs[0]["after"]) == 3
    assert cs[0]["before"] == '#include "Common/AsciiString.h"'


def test_choices_are_valid_for_shape_search():
    cs = eh_levers.choices_for(SOURCE, max_throw=2)
    for c in cs:
        c.pop("lever")
    produced = list(shape_search.variants(SOURCE, cs))
    assert len(produced) == 2 * 2 * 2 * 4
    assert produced[0][1] == SOURCE
