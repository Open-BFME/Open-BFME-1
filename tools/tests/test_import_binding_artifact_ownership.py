"""Pure workflow/provenance integration; no native compiler or byte-gate proof.

The actual tracked registry paths collide under a basename artifact key. These
tests keep artifact routing, planning, verification and file I/O real while
supplying small source/ledger/COFF inputs and replacing external tool runs.
"""
import csv
import json
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import import_binding as ib  # noqa: E402


DOWNLOAD = "game/Libraries/Source/WWVegas/WWDownload/registry.cpp"
WWLIB = "game/Libraries/Source/WWVegas/WWLib/registry.cpp"
SOURCES = (DOWNLOAD, WWLIB)


@pytest.fixture
def workflow(monkeypatch, tmp_path):
    """Run the actual commands against isolated inputs and synthetic objects."""
    monkeypatch.setattr(ib, "ROOT", tmp_path)
    monkeypatch.setattr(ib, "OUT", tmp_path / "build/import_binding")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "BUILD_DIR", tmp_path / "build/match")
    ledger = tmp_path / "targets/game/reverse/functions.csv"
    ledger.parent.mkdir(parents=True)
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    fields = ("name", "target_rva", "target_size", "source", "status", "notes")
    with ledger.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields)
        writer.writeheader()
        for index, source in enumerate(SOURCES):
            path = tmp_path / source
            path.parent.mkdir(parents=True)
            path.write_text(f"int owner{index}() {{ return {index}; }}\n", encoding="ascii")
            writer.writerow(dict(name=f"_owner{index}", target_rva=f"0x{0x1000 + index:08X}",
                                 target_size="1", source=source, status="matched", notes=""))
    # No imports are needed to test artifact ownership. The real plan and
    # verify_object inspect valid, distinct COFF files with no symbols.
    monkeypatch.setattr(ib, "load_context", lambda: (ib.Imports({}, []), {}))

    def compile_source(source, obj):
        source = source.relative_to(tmp_path).as_posix()
        obj.parent.mkdir(parents=True, exist_ok=True)
        stamp = SOURCES.index(source) + 1
        obj.write_bytes(struct.pack("<HHIIIHH", 0x14C, 0, stamp, 20, 0, 0, 0)
                        + struct.pack("<I", 4))
        return True, "synthetic compilation", None

    monkeypatch.setattr(build, "try_compile_source", compile_source)

    def byte_gate(command, **kwargs):
        assert command[1] == str(tmp_path / "tools/build.py")
        source = tmp_path / command[-1]
        compile_source(source, build.obj_path(source))
        return SimpleNamespace(returncode=0, stdout="synthetic byte-gate result\n")

    monkeypatch.setattr(ib.subprocess, "run", byte_gate)
    linked = []

    def strict_link(obj, imports, work, label):
        work.mkdir(parents=True, exist_ok=True)
        data = obj.read_bytes()
        linked.append((obj, work, label, data))
        return True, data.hex(), [], []

    monkeypatch.setattr(ib, "strict_link", strict_link)
    return SimpleNamespace(root=tmp_path, linked=linked)


def check(source):
    assert ib.cmd_check(SimpleNamespace(source=source)) == 0
    return json.loads((ib.work_dir(source) / "receipt.json").read_text(encoding="utf-8"))


def measure(workflow):
    path = workflow.root / "measure.json"
    path.write_text(json.dumps({"objects": {
        build.obj_path(workflow.root / source).name: {
            "imports": {f"__imp__owner{index}": "alias:wrong-name"}, "duplicate_thunks": []}
        for index, source in enumerate(SOURCES)
    }}), encoding="utf-8")
    return SimpleNamespace(measure=str(path))


def test_actual_registry_paths_have_distinct_artifact_directories(workflow):
    assert ib.work_dir(DOWNLOAD) != ib.work_dir(WWLIB)
    assert ib.work_dir(DOWNLOAD) == ib.OUT / build.obj_path(workflow.root / DOWNLOAD).stem
    assert ib.work_dir(WWLIB) == ib.OUT / build.obj_path(workflow.root / WWLIB).stem


def test_no_repair_apply_control_belongs_only_to_that_source(workflow):
    original = (workflow.root / DOWNLOAD).read_bytes()
    assert ib.cmd_apply(SimpleNamespace(source=DOWNLOAD, model="")) == 0
    control = (ib.work_dir(DOWNLOAD) / "before.obj").read_bytes()
    assert control == build.obj_path(workflow.root / DOWNLOAD).read_bytes()
    assert (workflow.root / DOWNLOAD).read_bytes() == original
    assert not (ib.work_dir(DOWNLOAD) / "plan.json").exists()

    receipt = check(WWLIB)
    assert receipt["source"] == WWLIB
    assert "before_strict_link" not in receipt
    assert [label for _, _, label, _ in workflow.linked] == ["after"]
    assert (ib.work_dir(DOWNLOAD) / "before.obj").read_bytes() == control


def test_distinct_plans_controls_and_receipts_survive_other_source_checks(workflow):
    plans, controls = {}, {}
    for index, source in enumerate(SOURCES):
        assert ib.cmd_apply(SimpleNamespace(source=source, model="")) == 0
        work = ib.work_dir(source)
        controls[source] = (work / "before.obj").read_bytes()
        # Persist deterministic reference plans through the same JSON input
        # seam used by check; their distinct values must stay with their TU.
        plans[source] = [["bind", f"__imp__owner{index}", {"to": f"__imp__bound{index}"}]]
        (work / "plan.json").write_text(json.dumps(plans[source]), encoding="utf-8")

    for source in SOURCES:
        receipt = check(source)
        assert receipt["source"] == source
        assert receipt["steps"] == plans[source]
        assert receipt["before_strict_link"]["output"] == controls[source].hex()
    assert controls[DOWNLOAD] != controls[WWLIB]
    for source in SOURCES:
        work = ib.work_dir(source)
        assert json.loads((work / "plan.json").read_text(encoding="utf-8")) == plans[source]
        receipt = json.loads((work / "receipt.json").read_text(encoding="utf-8"))
        assert receipt["source"] == source
        assert receipt["steps"] == plans[source]
        assert (work / "before.obj").read_bytes() == controls[source]


@pytest.mark.parametrize("artifact", ("receipt.json", "refused.txt"))
@pytest.mark.parametrize("done_source", SOURCES)
def test_next_completion_or_refusal_only_suppresses_its_source(workflow, capsys, artifact, done_source):
    work = ib.work_dir(done_source)
    work.mkdir(parents=True)
    (work / artifact).write_text("{}\n", encoding="utf-8")
    assert ib.cmd_next(measure(workflow)) == 0
    remaining = next(source for source in SOURCES if source != done_source)
    assert capsys.readouterr().out.splitlines()[0] == remaining


def test_check_ignores_legacy_basename_artifacts(workflow):
    legacy = ib.OUT / "registry"
    legacy.mkdir(parents=True)
    (legacy / "plan.json").write_text("not a valid plan", encoding="utf-8")
    (legacy / "before.obj").write_bytes(b"not a COFF object")
    (legacy / "receipt.json").write_text("legacy receipt", encoding="utf-8")
    receipt = check(WWLIB)
    assert receipt["steps"] == []
    assert "before_strict_link" not in receipt
    assert (legacy / "receipt.json").read_text(encoding="utf-8") == "legacy receipt"


@pytest.mark.parametrize("artifact", ("receipt.json", "refused.txt"))
def test_next_ignores_legacy_basename_completion(workflow, capsys, artifact):
    legacy = ib.OUT / "registry"
    legacy.mkdir(parents=True)
    (legacy / artifact).write_text("{}\n", encoding="utf-8")
    assert ib.cmd_next(measure(workflow)) == 0
    first_object = min(build.obj_path(workflow.root / source).name for source in SOURCES)
    expected = ib.source_of_objects()[first_object]
    assert capsys.readouterr().out.splitlines()[0] == expected
