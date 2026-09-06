"""The four ledger states, the two things the tool refuses to guess, and a real file.

pin_status is a reporting layer over find_declared_unmatched's definition parser,
so the tests here are about the one thing it adds: deciding, per definition, what
reverse/functions.csv actually says about that body. Two of them are the reason
the tool exists at all --

  * an OVERLOAD's matched row is not this body's verification. `Widget::Draw(int)`
    is matched; `Widget::Draw(float)` is a verbatim ZH copy. They share the needle
    `?Draw@Widget@`, so the mangled-substring rule find_declared_unmatched uses
    reports the unverified body as matched. That is the defect the whole tool is
    pointed at, and test_a_siblings_matched_row_is_not_this_bodys_verification is
    the only thing that catches it;
  * when nothing distinguishes the overloads -- no annotation, fewer rows than
    bodies -- the answer is `ambiguous`, never `matched`. A tool that quietly says
    "verified" over a ZH copy is worse than no tool.

The fixture ledger deliberately mixes \\r\\r\\n, \\r\\n and bare \\n terminators.
functions.csv does the same (tools/ledger_io.py:1-14) and every naive split has
silently dropped or invented rows there; here a naive split moves Paint and Tick
off their states.
"""
import importlib.util
import io
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
sys.path.insert(0, str(TOOLS))


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


pin_status = _load("pin_status")

SOURCE = "Code/Widget.cpp"
LEDGER_PATH = "reverse/functions.csv"

WIDGET_CPP = """// ?Draw@Widget@@QAEXH@Z
void Widget::Draw( int n )
{
}

// ?Draw@Widget@@QAEXM@Z present-unmatched
void Widget::Draw( float f )
{
}

// ?Paint@Widget@@QAEXXZ present-unmatched
void Widget::Paint( void )
{
}

// ?Tick@Widget@@QAEXXZ present-unmatched
void Widget::Tick( void )
{
}

void Widget::Blend( float a )
{
}

void Widget::Blend( int a )
{
}

void Widget::Missing( void )
{
}

static int helper( int a )
{
        return a;
}
"""


def ledger(extra=()):
    """Four rows plus whatever a test adds, one per terminator this file mixes."""
    rows = [
        (b"name,export_rva,target_rva,target_size,source,status,notes", b"\r\n"),
        # matched, and named by THIS source -- the only `matched` in the fixture.
        (f"?Draw@Widget@@QAEXH@Z,,0x00401000,16,{SOURCE},matched,".encode(), b"\r\r\n"),
        # matched, but the row names another TU: `row-elsewhere`.
        (b"?Paint@Widget@@QAEXXZ,,0x00401020,16,Code/Other.cpp,matched,", b"\n"),
        # a row exists whose status is not matched: `unmatched`.
        (f"?Tick@Widget@@QAEXXZ,,0x00401040,16,{SOURCE},unmatched,".encode(), b"\r\n"),
        # one row against the file's TWO un-annotated Blend bodies.
        (f"?Blend@Widget@@QAEXM@Z,,0x00401060,16,{SOURCE},matched,".encode(), b"\r\r\n"),
    ] + list(extra)
    return b"".join(payload + terminator for payload, terminator in rows)


def world(tmp_path, source=WIDGET_CPP, rows=()):
    root = (tmp_path / "repo").resolve()
    (root / "Code").mkdir(parents=True)
    (root / "reverse").mkdir()
    (root / SOURCE).write_text(source)
    (root / LEDGER_PATH).write_bytes(ledger(rows))
    return root


def states(root):
    """{Class::method: [state, ...]} in file order, plus the printed summary."""
    out = io.StringIO()
    pin_status.run([SOURCE], out=out, ledger=root / LEDGER_PATH, root=root)
    text = (root / SOURCE).read_text()
    defs = pin_status.classify(
        pin_status.definitions(text),
        pin_status.read_rows(*pin_status.screen(pin_status.definitions(text)),
                             path=root / LEDGER_PATH),
        SOURCE)
    by_name = {}
    for definition in defs:
        by_name.setdefault(definition.display, []).append(definition.state)
    return by_name, out.getvalue()


def test_a_siblings_matched_row_is_not_this_bodys_verification(tmp_path):
    """The RED one. Draw(int) is matched from this file; Draw(float) is a ZH copy
    with a present-unmatched marker and NO row. They share one needle, so the
    substring rule alone reports the ZH copy as verified."""
    root = world(tmp_path)
    by_name, _summary = states(root)
    assert by_name["Widget::Draw"] == ["matched", "no-row"]

    # ...and the needle on its own really would have called the second one
    # matched, which is what makes the annotation load-bearing rather than decor.
    text = (root / SOURCE).read_text()
    rows = pin_status.read_rows(*pin_status.screen(pin_status.definitions(text)),
                                path=root / LEDGER_PATH)
    zh_copy = pin_status.definitions(text)[1]
    assert zh_copy.annotation == "?Draw@Widget@@QAEXM@Z"
    zh_copy.annotation = None
    assert pin_status.candidates(zh_copy, rows) == ["?Draw@Widget@@QAEXH@Z"]


def test_indistinguishable_overloads_are_ambiguous_never_matched(tmp_path):
    """Two un-annotated Blend bodies, one matched row. Which body it verifies is
    not knowable from the mangled name, so neither may be called verified."""
    by_name, _summary = states(world(tmp_path))
    assert by_name["Widget::Blend"] == ["ambiguous", "ambiguous"]


def test_an_overload_group_resolves_when_it_cannot_be_wrong(tmp_path):
    """The other half of that rule: give the second Blend its own matched row from
    this source and every body in the group is verified whichever way they pair."""
    second = (f"?Blend@Widget@@QAEXH@Z,,0x00401080,16,{SOURCE},matched,".encode(),
              b"\n")
    by_name, _summary = states(world(tmp_path, rows=[second]))
    assert by_name["Widget::Blend"] == ["matched", "matched"]


def test_the_other_three_states(tmp_path):
    by_name, _summary = states(world(tmp_path))
    assert by_name["Widget::Paint"] == ["row-elsewhere"]   # matched, another TU
    assert by_name["Widget::Tick"] == ["unmatched"]        # row, status not matched
    assert by_name["Widget::Missing"] == ["no-row"]        # nothing claims it


def test_the_summary_counts_every_definition_and_owns_up_to_the_free_function(tmp_path):
    """7 member definitions: 1 matched, 1 row-elsewhere, 1 unmatched, 2 no-row,
    2 ambiguous. `helper` is a free function -- the shared parser does not read
    it, so it is counted as unparsed rather than guessed at."""
    _by_name, summary = states(world(tmp_path))
    assert summary.splitlines()[-1] == (
        "  1 of 7 definitions carry a verified row (row-elsewhere 1, unmatched 1, "
        "no-row 2, ambiguous 2); unparsed: 1 definitions")


def test_a_torn_ledger_record_stops_the_run_instead_of_vanishing(tmp_path):
    """A short record is a torn read, not a row to skip: skipping it would drop a
    matched row and print `no-row` over a verified body."""
    root = world(tmp_path, rows=[(b"?Half@Widget@@QAEXXZ,,0x004010A0", b"\r\n")])
    with pytest.raises(SystemExit) as raised:
        states(root)
    assert "expected 7 fields, read 3" in str(raised.value)


def test_a_row_behind_each_terminator_is_read(tmp_path):
    """Paint's row ends with a bare \\n and Draw's with \\r\\r\\n. A reader that
    split on "\\r\\n" would lose one and merge the other into its neighbour."""
    raw = ledger()
    assert b"\r\r\n" in raw and b",matched,\n" in raw
    by_name, _summary = states(world(tmp_path))
    assert by_name["Widget::Draw"][0] == "matched"
    assert by_name["Widget::Paint"] == ["row-elsewhere"]


# Measured on GameLogic.cpp at the commit that added this file. Conversions move
# these -- `matched` up, `no-row` down -- so the assertion is directional: a drop
# in matched, or a rise in no-row, is the tool regressing, not the tree changing.
GAMELOGIC = "Code/GameEngine/Source/GameLogic/System/GameLogic.cpp"
MEASURED = {"matched": 9, "row-elsewhere": 15, "unmatched": 0, "no-row": 37,
            "ambiguous": 0}
DEFINITIONS = 61


@pytest.mark.skipif(not (ROOT / GAMELOGIC).exists(), reason="needs the real tree")
def test_the_real_gamelogic_numbers(tmp_path):
    out = io.StringIO()
    counts = pin_status.run([GAMELOGIC], show_lines=False, out=out)[GAMELOGIC]
    assert sum(counts.values()) <= DEFINITIONS + 20   # the file only grows slowly
    assert counts["matched"] >= MEASURED["matched"], out.getvalue()
    assert counts["no-row"] <= MEASURED["no-row"], out.getvalue()


@pytest.mark.skipif(not (ROOT / GAMELOGIC).exists(), reason="needs the real tree")
def test_the_setgamepaused_signature_the_tool_was_built_for():
    """GameLogic.cpp defines ZH's two-argument setGamePaused. BFME's takes three
    (PopupSaveLoad.cpp's matched row says so), a shipped mod README names the
    symbol, and nothing in the file says the body is unverified. It must not
    report matched -- BfmeGameLogicPause::setGamePaused, which IS matched, is a
    different class and must not be mistaken for it."""
    text = (ROOT / GAMELOGIC).read_text(encoding="utf-8")
    defs = pin_status.definitions(text)
    rows = pin_status.read_rows(*pin_status.screen(defs))
    pin_status.classify(defs, rows, GAMELOGIC)
    paused = [d for d in defs if d.display == "GameLogic::setGamePaused"]
    assert [d.state for d in paused] == ["no-row"]
    assert paused[0].annotation == "?setGamePaused@GameLogic@@QAEX_N0@Z"
