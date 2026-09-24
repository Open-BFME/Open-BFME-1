"""Regressions for the finish lane's diagnostic cache and queue order."""

from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import finish_measure  # noqa: E402


def _stash(tmp_path, name, symbol, body):
    path = tmp_path / name
    path.write_text(f"// {symbol}\n// partial score=0.95 date=2026-09-24\n{body}\n")
    return path


def test_failed_or_zero_quality_measurement_does_not_beat_unmeasured(tmp_path):
    failed = _stash(tmp_path, "failed.cpp", "?failed@@YAXXZ", "int f;")
    zero = _stash(tmp_path, "zero.cpp", "?zero@@YAXXZ", "int z;")
    fresh = _stash(tmp_path, "fresh.cpp", "?fresh@@YAXXZ", "int v;")
    cache = {
        "0x00000010": {"hash": finish_measure.body_hash(failed), "compiles": False, "quality": 0.0},
        "0x00000020": {"hash": finish_measure.body_hash(zero), "compiles": True,
                       "quality": 0.0, "retail": 100, "first": 0},
    }
    pending = finish_measure.rank_key(cache, 0x30, fresh, 0.95, 100)
    assert pending < finish_measure.rank_key(cache, 0x10, failed, 0.95, 100)
    assert pending < finish_measure.rank_key(cache, 0x20, zero, 0.95, 100)


def test_changed_stash_symbol_invalidates_measurement(tmp_path):
    path = _stash(tmp_path, "body.cpp", "?old@@YAXXZ", "int f;")
    cache = {"0x00000010": {"hash": finish_measure.body_hash(path),
                            "compiles": True, "quality": 0.9}}
    assert finish_measure.current(cache, 0x10, path)
    path.write_text(path.read_text().replace("?old@@YAXXZ", "?new@@YAXXZ"))
    assert finish_measure.current(cache, 0x10, path) is None


def test_four_target_selection_keeps_one_unmeasured_exploration_slot(tmp_path):
    candidates = []
    cache = {}
    for n in range(1, 6):
        path = _stash(tmp_path, f"{n}.cpp", f"?f{n}@@YAXXZ", f"int f{n};")
        candidates.append((0.95, 100, f"0x{n:08x}", path))
        cache[f"0x{n:08x}"] = {"hash": finish_measure.body_hash(path),
                                "compiles": True, "quality": 0.99 - n / 100}
    fresh = _stash(tmp_path, "fresh.cpp", "?fresh@@YAXXZ", "int fresh;")
    candidates.append((0.98, 100, "0x00000006", fresh))
    selected = finish_measure.select(candidates, cache, 4)
    assert [c[2] for c in selected] == ["0x00000001", "0x00000002", "0x00000003", "0x00000006"]
