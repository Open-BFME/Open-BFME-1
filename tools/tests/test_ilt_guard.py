#!/usr/bin/env python3
"""ilt_guard: new contradicted real names are refused; placeholders, unchanged rows, untestable
addresses and baseline keys pass; the baseline only shrinks."""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import ilt_guard as G  # noqa: E402
import ilt_oracle as O  # noqa: E402

pytestmark = pytest.mark.skipif(not O.WINDOWS.exists(), reason="no frozen window file")
STL = ("??$?5DV?$char_traits@D@_STL@@V?$allocator@D@1@@_STL@@YAAAV?$basic_istream@DV?$char_traits@D@_STL@@@0@"
       "AAV10@AAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@0@@Z")
HEADER = "name,export_rva,target_rva,target_size,source,status,notes"


def fake_diff(monkeypatch, minus, plus, pins=("", "")):
    def git(*args):
        if args[0] == "diff":
            m, p = (minus, plus) if args[-1].endswith("functions.csv") else pins
            return "".join(f"-{l}\n" for l in m.splitlines()) + "".join(f"+{l}\n" for l in p.splitlines())
        raise AssertionError(args)
    monkeypatch.setattr(G, "git", git)


def row(name, rva, source="game/x.cpp"):
    return f'"{name}",,0x{rva:08X},424,{source},matched,'


def test_positive_control_wrong_decoration_is_refused(monkeypatch):
    # today's hook accepts this: a confirmed STLport row renamed to a __stdcall spelling
    fake_diff(monkeypatch, row(STL, 0x0053C820), row(STL.replace("YAAAV", "YGAAV"), 0x0053C820))
    bad, _ = G.problems(G.changed(["--cached", "HEAD"]), O.oracle(), set())
    assert len(bad) == 1 and "0x0053C820" in bad[0]


def test_new_pin_with_contradicted_real_name_is_refused(monkeypatch):
    fake_diff(monkeypatch, "", "", pins=("", "?update@Wrong@@UAEXXZ,0x0053C820,"))
    assert len(G.problems(G.changed(["--cached", "HEAD"]), O.oracle(), set())[0]) == 1


def test_negative_controls_pass(monkeypatch):
    cases = [
        ("", row(STL, 0x0053C820)),                                         # right name, new row
        (row(STL, 0x0053C820), row(STL, 0x0053C820, "game/moved.cpp")),     # unchanged name, repointed
        (row(STL, 0x0053C820), row("?b_0053c820@@YAXXZ", 0x0053C820)),      # placeholder: exempt
        ("", row("?update@Wrong@@UAEXXZ", 0x00C1FC1D)),                     # library region: untestable
    ]
    for minus, plus in cases:
        fake_diff(monkeypatch, minus, plus)
        assert G.problems(G.changed(["--cached", "HEAD"]), O.oracle(), set())[0] == [], (minus, plus)


def test_baseline_key_exempts_an_existing_contradicted_name(monkeypatch):
    wrong = STL.replace("YAAAV", "YGAAV")
    fake_diff(monkeypatch, "", row(wrong, 0x0053C820))
    exempt = {G.key("functions", 0x0053C820, wrong)}
    assert G.problems(G.changed(["--cached", "HEAD"]), O.oracle(), exempt)[0] == []


def test_consistent_names_are_counted_not_verified(monkeypatch):
    fake_diff(monkeypatch, "", row(STL, 0x0053C820))
    bad, consistent = G.problems(G.changed(["--cached", "HEAD"]), O.oracle(), set())
    assert bad == [] and consistent == 1


def test_baseline_growth_is_refused(monkeypatch, capsys):
    head = G.HEADER + "functions\t0x00000001\t?a@@YAXXZ\n"
    staged = head + "functions\t0x00000002\t?b@@YAXXZ\n"

    def git(*args):
        if args[0] == "show":
            return head if args[1].startswith("HEAD:") else staged
        return ""
    monkeypatch.setattr(G, "git", git)
    assert G.main(["--staged"]) == 1
    assert "may only shrink" in capsys.readouterr().err
