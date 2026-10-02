"""Census receipts and commit labels include the actual header inputs."""
import json
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as census
from test_build_include_inventory import _fixture


def test_new_shadowing_shim_header_invalidates_census_object(tmp_path, monkeypatch):
    source, obj, early, original, _, _ = _fixture(tmp_path, monkeypatch)
    assert census.object_current(source, obj)
    (early / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    assert original.read_text() == "#define PACKET_RANGE 6\n"
    assert not census.object_current(source, obj)


def test_selected_refuses_changed_tracked_reference_header(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    header = root / "inputs/reference/shims/Common/Test.h"
    header.parent.mkdir(parents=True)
    header.write_text("#define VALUE 1\n")
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    subprocess.run(["git", "-C", str(root), "add", "inputs/reference/shims/Common/Test.h"], check=True)
    subprocess.run(["git", "-C", str(root), "-c", "user.name=Test", "-c", "user.email=test@example.invalid",
                    "commit", "-qm", "fixture"], check=True)
    commit = subprocess.check_output(["git", "-C", str(root), "rev-parse", "HEAD"], text=True).strip()
    header.write_text("#define VALUE 2\n")
    monkeypatch.setattr(census, "ROOT", root)
    monkeypatch.setattr(census, "read_history", lambda: [{"commit": commit}])
    monkeypatch.setattr(census, "verify_data_objects", lambda: pytest.fail("passed the commit-input guard"))
    with pytest.raises(SystemExit, match="this tree differs"):
        census.selected_main()
    monkeypatch.setattr(census, "verify_data_objects", lambda: None)
    with pytest.raises(SystemExit, match="uncommitted source or ledger edits"):
        census.record({"missing": 0}, [])


def test_fresh_build_does_not_skip_currency_after_long_link(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    monkeypatch.setattr(census, "verify_data_objects", lambda: None)
    monkeypatch.setattr(census.subprocess, "run", lambda *a, **k: SimpleNamespace(stdout="", returncode=0))
    monkeypatch.setattr(census, "objects", lambda rows: ([obj], []))
    monkeypatch.setattr(census, "_object_sources", lambda rows: {obj: source})
    monkeypatch.setattr(census, "object_current", lambda *a, **k: False)
    with pytest.raises(SystemExit, match="not current"):
        census.record({"missing": 0}, [], fresh=True)


def test_inventory_change_during_currency_check_refuses_snapshot(monkeypatch):
    monkeypatch.setattr(census.build, "_inventory_cache_still_current", lambda cache: False)
    with pytest.raises(SystemExit, match="changed while checking"):
        census.stale_objects([], {})


def test_fresh_uncacheable_compile_passes_census_currency(tmp_path, monkeypatch):
    from test_census_receipts import fixture
    import census_receipts
    source, header, obj, _, _, _ = fixture(tmp_path, monkeypatch)
    receipts = census_receipts.Receipts(tmp_path / "proof.json")
    assert census.build.try_compile_source(source, obj, input_proof=receipts)[0]
    monkeypatch.setattr(census, "_INPUT_RECEIPTS", receipts)
    assert census.stale_objects([obj], {obj: source}) == []
    header.write_text("#define VALUE 18\n")
    assert census.stale_objects([obj], {obj: source}) == [obj]


def test_skipped_checkout_root_tu_gets_a_receipt_and_ignores_root_scratch(tmp_path, monkeypatch):
    import census_receipts

    root = tmp_path / "project"
    source = root / "game" / "unit.cpp"
    header = source.parent / "unit.h"
    output = root / "build" / "unit.obj"
    source.parent.mkdir(parents=True)
    output.parent.mkdir(parents=True)
    source.write_text('#include "unit.h"\n')
    header.write_text("#define VALUE 1\n")
    output.write_bytes(b"compiled object")
    sidecar = census.build._deps_sidecar(output)
    sidecar.write_text(json.dumps({"search_roots": [".", "@ROOT_PARENT@/include"]}))
    monkeypatch.setattr(census.build, "ROOT", root)

    receipts = census_receipts.Receipts(root / "compile_inputs.json")
    monkeypatch.setattr(census, "_INPUT_RECEIPTS", receipts)
    monkeypatch.setattr(census.build, "compile_is_current", lambda *a, **k: False)
    before = census.build._directory_inventory(root)
    (root / "mission_objective.cod").write_text("assembly listing\n")
    assert census.build._directory_inventory(root) != before
    assert census.stale_objects([output], {output: source}) == [output]

    calls = []

    def compile_rows(rows, sources, *, input_proof):
        calls.append((rows, sources, input_proof))
        assert not sidecar.exists()
        sidecar.write_text(json.dumps({"search_roots": [".", "@ROOT_PARENT@/include"]}))
        key = str(output.resolve())
        input_proof.entries[key] = {"source": str(source.resolve()),
                                    "object": census_receipts.digest(output),
                                    "input": {}, "command": []}

    monkeypatch.setattr(census.build, "compile_rows", compile_rows)
    census._refresh_missing_search_root_receipts(["ledger"], {source: output}, receipts)
    assert calls == [(["ledger"], [source], receipts)]

    baseline = header.read_bytes()
    object_hash = census_receipts.digest(output)
    monkeypatch.setattr(receipts, "current",
                        lambda src, obj: header.read_bytes() == baseline
                        and census_receipts.digest(obj) == object_hash)
    monkeypatch.setattr(census.build, "compile_is_current",
                        lambda *a, **k: pytest.fail("broad root inventory should be bypassed"))
    assert census.stale_objects([output], {output: source}) == []

    header.write_text("#define VALUE 2\n")
    assert census.stale_objects([output], {output: source}) == [output]


def test_fresh_checkout_root_receipt_survives_root_addition_but_checks_inputs(tmp_path, monkeypatch):
    from test_census_receipts import fixture
    import census_receipts

    source, header, output, _, _, _ = fixture(tmp_path, monkeypatch)
    receipts = census_receipts.Receipts(tmp_path / "compile_inputs.json")
    assert census.build.try_compile_source(source, output, input_proof=receipts)[0]
    census.build._deps_sidecar(output).write_text(json.dumps({"search_roots": ["."]}))
    monkeypatch.setattr(census, "_INPUT_RECEIPTS", receipts)
    monkeypatch.setattr(census.build, "compile_is_current",
                        lambda *a, **k: pytest.fail("broad root inventory should be bypassed"))

    before = census.build._directory_inventory(tmp_path)
    (tmp_path / "mission_objective.cod").write_text("assembly listing\n")
    assert census.build._directory_inventory(tmp_path) != before
    assert census.stale_objects([output], {output: source}) == []

    header.write_text("#define VALUE 18\n")
    assert census.stale_objects([output], {output: source}) == [output]


def test_inventory_change_during_fresh_proof_is_refused(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    monkeypatch.setattr(census, "object_current", lambda *a, **k: False)
    monkeypatch.setattr(census, "input_receipts", lambda: SimpleNamespace(current=lambda *a: True))
    stable = iter([True, False])
    monkeypatch.setattr(census.build, "_inventory_cache_still_current", lambda cache: next(stable))
    with pytest.raises(SystemExit, match="changed while checking"):
        census.stale_objects([obj], {obj: source})
