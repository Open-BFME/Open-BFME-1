"""marker_screen clears a destination's marker to measure a donor, so the one
thing it must never do is leave that marker cleared. A destination missing its
marker makes the NEXT build report a stale-annotation pass that never compared
a byte -- the trap docs/lessons.md records -- so an interrupted screen is worse
than a failed one."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import marker_screen  # noqa: E402


def _dest(tmp_path, donor, symbol):
    """screen() resolves its destination as ROOT / dest, and pathlib lets an
    ABSOLUTE dest win, which is how these tests point it at tmp_path without
    patching anything."""
    path = tmp_path / "Dest.cpp"
    marker = "// byte-exact reconstruction: %s\n// %s present-unmatched\n" % (donor, symbol)
    path.write_bytes(("above\n" + marker + "below\n").encode("utf-8"))
    return path, marker


def test_an_exception_mid_screen_restores_the_marker(tmp_path, monkeypatch):
    donor, symbol = "d.cpp", "?f@C@@QAEXXZ"
    path, marker = _dest(tmp_path, donor, symbol)
    before = path.read_bytes()

    def boom(*a, **k):
        raise RuntimeError("build died")
    monkeypatch.setattr(marker_screen, "_screen_cleared", boom)
    with pytest.raises(RuntimeError):
        marker_screen.screen(donor, str(path), symbol)

    assert path.read_bytes() == before, "marker not restored after an exception"
    assert marker in path.read_bytes().decode("utf-8")


def test_a_keyboardinterrupt_also_restores(tmp_path, monkeypatch):
    """BaseException, not Exception -- a Ctrl-C mid-build must restore too."""
    donor, symbol = "d.cpp", "?f@C@@QAEXXZ"
    path, marker = _dest(tmp_path, donor, symbol)
    before = path.read_bytes()

    def interrupted(*a, **k):
        raise KeyboardInterrupt
    monkeypatch.setattr(marker_screen, "_screen_cleared", interrupted)
    with pytest.raises(KeyboardInterrupt):
        marker_screen.screen(donor, str(path), symbol)

    assert path.read_bytes() == before, "marker not restored after Ctrl-C"


def test_a_missing_marker_pair_is_reported_and_nothing_is_written(tmp_path, monkeypatch):
    path = tmp_path / "Dest.cpp"
    path.write_bytes(b"no marker here\n")
    before = path.read_bytes()
    assert marker_screen.screen("d.cpp", str(path), "?f@C@@QAEXXZ") == "no-marker-pair"
    assert path.read_bytes() == before


def test_a_truncated_marker_resolves_against_the_rows_its_donor_owns(monkeypatch):
    """A third of the markers name a symbol without its signature. Looking one up
    in functions.csv directly finds nothing, which is how a 23-donor family screen
    missed a 24th member -- so resolution has to go through the DONOR's rows."""
    monkeypatch.setattr(marker_screen, "_rows", {
        "??0Foo@@QAE@PAVThing@@@Z": ("0x1", "10", "donor.cpp"),
        "??0Foo@@QAE@XZ": ("0x2", "20", "elsewhere.cpp"),
    })
    monkeypatch.setattr(marker_screen, "_by_source", {
        "donor.cpp": ["??0Foo@@QAE@PAVThing@@@Z"],
        "elsewhere.cpp": ["??0Foo@@QAE@XZ"],
    })
    # the other overload is a prefix match too, and is correctly not a candidate
    assert marker_screen.resolve("donor.cpp", "??0Foo@@") == "??0Foo@@QAE@PAVThing@@@Z"
    assert marker_screen.resolve("nobody.cpp", "??0Foo@@") is None
    assert marker_screen.resolve("donor.cpp", "??0Foo@@QAE@PAVThing@@@Z") == "??0Foo@@QAE@PAVThing@@@Z"


def test_a_truncated_marker_matching_two_of_the_donors_rows_is_not_guessed(monkeypatch):
    monkeypatch.setattr(marker_screen, "_rows", {
        "??0Foo@@QAE@H@Z": ("0x1", "10", "donor.cpp"),
        "??0Foo@@QAE@XZ": ("0x2", "20", "donor.cpp"),
    })
    monkeypatch.setattr(marker_screen, "_by_source",
                        {"donor.cpp": ["??0Foo@@QAE@H@Z", "??0Foo@@QAE@XZ"]})
    assert marker_screen.resolve("donor.cpp", "??0Foo@@") == "ambiguous"


def test_an_unresolved_symbol_still_gets_its_marker_restored(tmp_path, monkeypatch):
    """The row lookup must not gate the restore -- that is the invariant above."""
    donor, symbol = "d.cpp", "?nosuch@C@@QAEXXZ"
    path, marker = _dest(tmp_path, donor, symbol)
    before = path.read_bytes()
    monkeypatch.setattr(marker_screen, "_screen_cleared",
                        lambda *a, **k: (_ for _ in ()).throw(RuntimeError("boom")))
    with pytest.raises(RuntimeError):
        marker_screen.screen(donor, str(path), symbol)
    assert path.read_bytes() == before
