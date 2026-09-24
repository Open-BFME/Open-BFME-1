"""Regressions for the finish lane's diagnostic cache and queue order."""

from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import time

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import finish_measure  # noqa: E402
import experiment_store  # noqa: E402


@pytest.fixture
def proof(monkeypatch):
    monkeypatch.setattr(finish_measure, "hypothesis",
                        lambda rva, path: finish_measure.body_hash(path))
    monkeypatch.setattr(experiment_store, "validated_object_receipt", lambda path: "object")
    def entry(path, **fields):
        return dict(fields, version=finish_measure.VERSION,
                    fingerprint=finish_measure.body_hash(path), receipt="object",
                    path=str(path), at=time.time())
    return entry


def _stash(tmp_path, name, symbol, body):
    path = tmp_path / name
    path.write_text(f"// {symbol}\n// partial score=0.95 date=2026-09-24\n{body}\n")
    return path


def test_failed_or_zero_quality_measurement_does_not_beat_unmeasured(tmp_path, proof):
    failed = _stash(tmp_path, "failed.cpp", "?failed@@YAXXZ", "int f;")
    zero = _stash(tmp_path, "zero.cpp", "?zero@@YAXXZ", "int z;")
    fresh = _stash(tmp_path, "fresh.cpp", "?fresh@@YAXXZ", "int v;")
    cache = {
        "0x00000010": proof(failed, compiles=False, quality=0.0),
        "0x00000020": proof(zero, compiles=True, quality=0.0, retail=100, first=0),
    }
    pending = finish_measure.rank_key(cache, 0x30, fresh, 0.95, 100)
    assert pending < finish_measure.rank_key(cache, 0x10, failed, 0.95, 100)
    assert pending < finish_measure.rank_key(cache, 0x20, zero, 0.95, 100)


def test_changed_stash_symbol_invalidates_measurement(tmp_path, proof):
    path = _stash(tmp_path, "body.cpp", "?old@@YAXXZ", "int f;")
    cache = {"0x00000010": proof(path, compiles=True, quality=0.9)}
    assert finish_measure.current(cache, 0x10, path)
    path.write_text(path.read_text().replace("?old@@YAXXZ", "?new@@YAXXZ"))
    assert finish_measure.current(cache, 0x10, path) is None


def test_four_target_selection_keeps_one_unmeasured_exploration_slot(tmp_path, proof):
    candidates = []
    cache = {}
    for n in range(1, 6):
        path = _stash(tmp_path, f"{n}.cpp", f"?f{n}@@YAXXZ", f"int f{n};")
        candidates.append((0.95, 100, f"0x{n:08x}", path))
        cache[f"0x{n:08x}"] = proof(path, compiles=True, quality=0.99 - n / 100)
    fresh = _stash(tmp_path, "fresh.cpp", "?fresh@@YAXXZ", "int fresh;")
    candidates.append((0.98, 100, "0x00000006", fresh))
    selected = finish_measure.select(candidates, cache, 4)
    assert [c[2] for c in selected] == ["0x00000001", "0x00000002", "0x00000003", "0x00000006"]


def test_hypothesis_tracks_target_row_symbol_and_probe_logic(tmp_path, monkeypatch):
    import build
    root = tmp_path
    (root / "reverse").mkdir()
    (root / "tools").mkdir()
    for name in ("finish_measure.py", "probe.py", "build.py", "experiment_store.py"):
        shutil.copy2(finish_measure.ROOT / "tools" / name, root / "tools" / name)
    ledger = root / "reverse/functions.csv"
    header = "name,export_rva,target_rva,target_size,source,status,notes\n"
    row = "?d_0041AE50@@YAXXZ,,0x0041AE50,396,Code/gen_asm/test.asm,matched,\n"
    ledger.write_text(header + row)
    path = _stash(root, "body.cpp", "?old@@YAXXZ", "int f;")
    monkeypatch.setattr(finish_measure, "ROOT", root)
    first = finish_measure.hypothesis(0x0041AE50, path)
    path.write_text(path.read_text().replace("score=0.95", "score=0.99"))
    assert finish_measure.hypothesis(0x0041AE50, path) == first
    path.write_text(path.read_text().replace("?old@@YAXXZ", "?new@@YAXXZ"))
    symbol = finish_measure.hypothesis(0x0041AE50, path)
    assert symbol != first
    ledger.write_text(header + row.replace("?d_0041AE50", "?dup_0041AE50"))
    changed_row = finish_measure.hypothesis(0x0041AE50, path)
    assert changed_row != symbol
    with (root / "tools/probe.py").open("a") as stream:
        stream.write("\n# changed probe logic\n")
    changed_probe = finish_measure.hypothesis(0x0041AE50, path)
    assert changed_probe != changed_row
    real_offset = build.rva_to_file_offset
    monkeypatch.setattr(build, "rva_to_file_offset",
                        lambda sections, rva: real_offset(sections, rva) + 1)
    assert finish_measure.hypothesis(0x0041AE50, path) != changed_probe


def test_transient_failure_retries_without_a_stash_edit(tmp_path, monkeypatch, proof):
    monkeypatch.setattr(finish_measure, "CACHE", tmp_path / "cache.json")
    path = _stash(tmp_path, "retry.cpp", "?retry@@YAXXZ", "int f;")
    now = [100000.0]
    monkeypatch.setattr(finish_measure.time, "time", lambda: now[0])
    answers = iter([{"compiles": False, "quality": 0.0, "note": "missing prerequisite"},
                    {"compiles": True, "quality": 0.9, "retail": 100, "ours": 100}])
    calls = []
    def measure(rva, source):
        calls.append(rva)
        return next(answers)
    monkeypatch.setattr(finish_measure, "measure", measure)
    first = finish_measure.ensure([(0x10, path)], budget=1)
    assert first["0x00000010"]["compiles"] is False
    finish_measure.ensure([(0x10, path)], budget=1)
    assert len(calls) == 1
    now[0] += finish_measure.RETRY_SECONDS + 1
    second = finish_measure.ensure([(0x10, path)], budget=1)
    assert len(calls) == 2 and second["0x00000010"]["quality"] == 0.9
    assert finish_measure.current(second, 0x10, path)


def test_probe_process_error_is_not_a_qualified_compile_result(tmp_path, monkeypatch):
    path = _stash(tmp_path, "broken.cpp", "?f@@YAXXZ", "int f;")
    monkeypatch.setattr(finish_measure.subprocess, "run",
                        lambda *args, **kwargs: SimpleNamespace(
                            returncode=1, stdout="size     ours=10 retail=10\n",
                            stderr="ModuleNotFoundError: No module named capstone"))
    result = finish_measure.measure(0x10, path)
    assert result["compiles"] is False
    assert "capstone" in result["note"]


def test_stash_mutation_during_probe_is_not_published(tmp_path, monkeypatch, proof):
    monkeypatch.setattr(finish_measure, "CACHE", tmp_path / "cache.json")
    path = _stash(tmp_path, "mutating.cpp", "?f@@YAXXZ", "int f;")
    def measure(rva, source):
        path.write_text(path.read_text().replace("int f;", "int g;"))
        return {"compiles": False, "quality": 0.0}
    monkeypatch.setattr(finish_measure, "measure", measure)
    assert finish_measure.ensure([(0x10, path)], budget=1) == {}
    assert finish_measure.load() == {}


def test_late_transient_result_cannot_replace_verified_measurement(tmp_path, monkeypatch, proof):
    monkeypatch.setattr(finish_measure, "CACHE", tmp_path / "cache.json")
    path = _stash(tmp_path, "body.cpp", "?f@@YAXXZ", "int f;")
    key = "0x00000010"
    positive = proof(path, compiles=True, quality=0.9)
    negative = proof(path, compiles=False, quality=0.0, note="temporary compiler failure")
    finish_measure.save({key: positive})
    finish_measure.save({key: negative})
    assert finish_measure.load()[key]["quality"] == 0.9


def test_concurrent_cache_processes_merge_distinct_entries(tmp_path):
    cache = tmp_path / "measurements.json"
    script = tmp_path / "writer.py"
    script.write_text(
        "from pathlib import Path\nimport sys,time\n"
        f"sys.path.insert(0, {str(Path(finish_measure.__file__).parent)!r})\n"
        "import finish_measure as f\n"
        "f.CACHE = Path(sys.argv[1])\n"
        "f.hypothesis = lambda rva, path: f.body_hash(path)\n"
        "rva = int(sys.argv[2], 16); path = Path(sys.argv[3])\n"
        "key = f'0x{rva:08x}'\n"
        "entry = dict(version=f.VERSION, fingerprint=f.body_hash(path), compiles=False, "
        "quality=0.0, path=str(path), at=time.time())\n"
        "f.save({key: entry})\n")
    jobs = []
    for n in range(1, 9):
        path = _stash(tmp_path, f"{n}.cpp", f"?f{n}@@YAXXZ", f"int f{n};")
        jobs.append(subprocess.Popen([sys.executable, str(script), str(cache), f"0x{n:08x}", str(path)],
                                     stdout=subprocess.PIPE, stderr=subprocess.PIPE))
    results = [job.communicate(timeout=20) for job in jobs]
    assert all(job.returncode == 0 for job in jobs), results
    assert len(finish_measure.json.loads(cache.read_text())) == 8


def test_real_compiler_receipt_invalidates_used_header_only(monkeypatch):
    import build
    if sys.platform != "win32" and shutil.which("wine") is None:
        pytest.skip("Wine/MSVC probe unavailable")
    try:
        toolchain = build.vc71_root()
    except (OSError, SystemExit):
        pytest.skip("MSVC 7.1 toolchain unavailable")
    if not (toolchain / "Vc7/bin/cl.exe").exists():
        pytest.skip("MSVC 7.1 compiler unavailable")
    (finish_measure.ROOT / "build").mkdir(exist_ok=True)
    with (tempfile.TemporaryDirectory(dir=finish_measure.ROOT / "build") as directory,
          tempfile.TemporaryDirectory(dir=finish_measure.ROOT / "build") as cache_directory):
        root = Path(directory)
        path = root / "probe.cpp"
        header = root / "dep.h"
        header.write_text("#define VALUE 1\n")
        unrelated = root / "unrelated.h"
        unrelated.write_text("// first\n")
        path.write_text("// ?probe@@YAHXZ\n// partial score=0.95 date=2026-09-24\n"
                        "#include \"dep.h\"\nint probe() { return VALUE; }\n")
        monkeypatch.setattr(finish_measure, "CACHE", Path(cache_directory) / "measurements.json")
        first = finish_measure.ensure([(0x0041AE50, path)], budget=1)
        assert first["0x0041ae50"]["compiles"] is True
        assert finish_measure.current(first, 0x0041AE50, path)
        unrelated.write_text("// changed contents\n")
        assert finish_measure.current(first, 0x0041AE50, path)
        header.write_text("#define VALUE 2\n")
        assert finish_measure.current(first, 0x0041AE50, path) is None
        second = finish_measure.ensure([(0x0041AE50, path)], budget=1)
        assert second["0x0041ae50"]["compiles"] is True
        assert finish_measure.current(second, 0x0041AE50, path)
