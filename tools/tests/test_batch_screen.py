"""batch_screen answers every marker on a destination from ONE compile.

Its safety property is the opposite of marker_screen's. marker_screen must
restore a marker it cleared; batch_screen must never have cleared one, because
a marker is a comment and cannot change what the compiler emits. The first test
below is the whole contract: if this tool ever starts editing to get a better
answer, it needs marker_screen's restore machinery and these tests should fail
loudly rather than be relaxed.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import batch_screen  # noqa: E402


def _dest(tmp_path, *labels):
    path = tmp_path / "Dest.cpp"
    body = "above\n" + "".join("// %s present-unmatched\n" % l for l in labels) + "below\n"
    path.write_bytes(body.encode("utf-8"))
    return path


def _row(name, source="donor.cpp"):
    return {"name": name, "export_rva": "", "target_rva": "0x00001000",
            "target_size": "8", "source": source, "status": "matched", "notes": ""}


def _patch_build(monkeypatch, *, compiled=b"same", target=b"same", boom=None):
    """Stand in for the compiler. `boom` makes compile_source raise, which is
    how the compile-error path is exercised without a toolchain."""
    def compile_source(source, output):
        if boom:
            raise boom
    monkeypatch.setattr(batch_screen.B, "compile_source", compile_source)
    monkeypatch.setattr(batch_screen.B, "obj_path", lambda s: Path("/dev/null"))
    monkeypatch.setattr(batch_screen.B, "load_symbol_map", lambda: {})
    monkeypatch.setattr(batch_screen.B, "compile_function",
                        lambda row, sm, out: {"bytes": compiled, "target": target})


def test_it_never_writes_to_the_destination(tmp_path, monkeypatch):
    """The contract. A marker is a comment, so there is nothing to clear and
    nothing to restore -- and an interrupted run cannot leave a file damaged."""
    path = _dest(tmp_path, "?f@C@@QAEXXZ")
    before = path.read_bytes()
    _patch_build(monkeypatch)
    list(batch_screen.screen(str(path), [_row("?f@C@@QAEXXZ")]))
    assert path.read_bytes() == before


def test_a_dead_compile_is_one_line_not_one_per_marker(tmp_path, monkeypatch):
    """A destination that does not build is ONE fact. Reporting it once per
    marker buries every destination that did compile."""
    path = _dest(tmp_path, "?a@C@@QAEXXZ", "?b@C@@QAEXXZ", "?c@C@@QAEXXZ")
    _patch_build(monkeypatch, boom=RuntimeError("cl.exe exploded\nsecond line"))
    out = list(batch_screen.screen(str(path), [_row("?a@C@@QAEXXZ")]))
    assert len(out) == 1
    assert out[0][1] == "compile-error"
    assert "second line" not in out[0][2], "only the first line of the failure"


def test_a_truncated_label_resolves_only_when_unambiguous(tmp_path, monkeypatch):
    rows = [_row("??0Foo@@QAE@XZ")]
    path = _dest(tmp_path, "??0Foo@@")
    _patch_build(monkeypatch)
    assert list(batch_screen.screen(str(path), rows))[0][:2] == ("??0Foo@@QAE@XZ", "MATCH")

    rows.append(_row("??0Foo@@QAE@ABV0@@Z"))
    out = list(batch_screen.screen(str(path), rows))
    assert out[0][1] == "ambiguous", "two overloads share the label; picking one is a guess"


def test_an_unknown_label_is_reported_not_skipped(tmp_path, monkeypatch):
    """~2,000 of ~3,000 markers name no ledger row at all. That is the single
    largest bucket in the queue and the tool must say so rather than drop it."""
    path = _dest(tmp_path, "?nosuch@C@@QAEXXZ")
    _patch_build(monkeypatch)
    out = list(batch_screen.screen(str(path), [_row("?other@C@@QAEXXZ")]))
    assert out == [("?nosuch@C@@QAEXXZ", "no-row", "")]


def test_a_miss_reports_its_byte_count(tmp_path, monkeypatch):
    path = _dest(tmp_path, "?f@C@@QAEXXZ")
    _patch_build(monkeypatch, compiled=b"abcd", target=b"abZd")
    out = list(batch_screen.screen(str(path), [_row("?f@C@@QAEXXZ")]))
    assert out[0][1] == "miss" and out[0][2] == "1"


def test_moves_counts_only_rows_a_marker_here_names(tmp_path, monkeypatch):
    """`moves` is what decides whether --only can land a MATCH as it stands.
    It must count the donor's rows THIS destination marks, not every row the
    donor owns -- the miscount that turned another lane's eleven ready rows
    into two."""
    path = _dest(tmp_path, "?f@C@@QAEXXZ")
    rows = [_row("?f@C@@QAEXXZ"), _row("?unmarked@C@@QAEXXZ")]  # same donor.cpp
    _patch_build(monkeypatch)
    out = list(batch_screen.screen(str(path), rows))
    assert out[0][1] == "MATCH"
    assert out[0][2].endswith("moves=1"), out[0][2]
