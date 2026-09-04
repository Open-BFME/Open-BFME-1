"""Regression and failure-path coverage for the conversion throughput tools."""
import csv
import json
from pathlib import Path
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import brief
import class_context
import experiment_store as experiments
import fleet_report
import fleet_run
import probe
import re_log
import shape_search
import source_donors


@pytest.mark.parametrize("left,right,expected", [
    ("b8 01 00 00 00 c3", "b8 02 00 00 00 c3", "operand-change"),
    ("89 c1 c3", "01 c1 c3", "instruction-change"),
    ("89 c1 c3", "89 d3 c3", "register-mirror"),
    ("89 c1 85 c0 c3", "89 d3 85 c0 c3", "instruction-change"),
    ("90 c3", "90 c3", "exact"),
    ("90 c3", "c3", "length-delta"),
])
def test_diagnoses_evidence_not_default_register_mirror(left, right, expected):
    left, right = bytes.fromhex(left), bytes.fromhex(right)
    assert probe.classify(probe.disasm(left), probe.disasm(right), left, right) == expected


def test_latest_verdicts_do_not_treat_evidence_addresses_as_targets(tmp_path):
    log = tmp_path / "attempts.log"
    log.write_text("one\t0x1000\t8\trefuted\tcallee 0x2000\n"
                   "two\t0x1000\t8\tblocked\ttype unknown\n"
                   "one\t0x1000\t8\tvoid\twrong name\n"
                   "two\t0x1000\t8\tevidence\tannotation 0x3000\n")
    result = re_log.latest_records(log)
    assert list(result) == [0x1000]
    assert result[0x1000][0:4] == ["two", "0x1000", "8", "blocked"]


def test_class_note_retains_slot_table_and_refuses_missing_context():
    assert brief.picker_note("RVAS: 0x1000\nNOTE: Foo\nslot 0: landed\nslot 1: dump\n") == "Foo\nslot 0: landed\nslot 1: dump"
    with pytest.raises(ValueError):
        brief.picker_note("RVAS: 0x1000\n")


def test_class_header_parser_skips_forward_declarations_and_balances_inline_bodies():
    assert class_context.class_virtuals('class Foo; class Other { virtual int Wrong(); };', 'Foo') is None
    assert class_context.class_virtuals('class Foo : public Base { virtual ~Foo() {} /* } */ virtual int Next() { return 1; } };', 'Foo') == ['~Foo', 'Next']


def test_outcome_dedup_keeps_target_callee_and_addend_identity(tmp_path):
    source = tmp_path / "test.cpp"
    source.write_text("int f();")
    db = tmp_path / "outcomes.sqlite"
    def record(target=b"target", name="_callee", data=b"\xe8\0\0\0\0"):
        return experiments.record_result(source, "_f", 0x1000, target, data, [(1, 0x14, name)], db)
    assert record()["seen_before"] == 0
    source.write_text("int f(void);")
    assert record()["seen_before"] == 1
    assert record(name="_different")["seen_before"] == 0
    assert record(target=b"new target")["seen_before"] == 0
    assert record(data=b"\xe8\1\0\0\0")["seen_before"] == 0
    with pytest.raises(ValueError):
        experiments.record_result(source, "_f", 0, b"x", b"x", [(0, 0x14, "bad")], db)


@pytest.fixture
def compiler(tmp_path, monkeypatch):
    monkeypatch.setattr(experiments.build, "ROOT", tmp_path)
    code = tmp_path / "Code"
    code.mkdir()
    source = code / "test.cpp"
    source.write_text("int f() { return 1; }")
    state = dict(calls=0, compiler="a", deps=True, fail=False, flags=[], env={})
    monkeypatch.setattr(experiments, "compiler_identity", lambda _: state["compiler"])
    monkeypatch.setattr(experiments.build, "compiler_command", lambda s, o: (["cl"] + state["flags"], state["env"]))
    monkeypatch.setattr(experiments.build, "compile_is_current", lambda s, o: state["deps"])
    def compile_source(s, o):
        state["calls"] += 1
        if state["fail"]:
            raise RuntimeError("compile error")
        o.write_bytes(s.read_bytes())
    monkeypatch.setattr(experiments.build, "compile_source", compile_source)
    return source, state


def test_compile_cache_reuses_only_intact_matching_inputs(compiler):
    source, state = compiler
    obj, reused = experiments.compile_cached(source)
    assert not reused
    assert experiments.compile_cached(source)[1]
    obj.write_bytes(b"tampered")
    assert not experiments.compile_cached(source)[1]
    state["deps"] = False
    assert not experiments.compile_cached(source)[1]
    state["deps"] = True
    state["compiler"] = "new compiler"
    assert not experiments.compile_cached(source)[1]
    state["flags"] = ["-Od"]
    assert not experiments.compile_cached(source)[1]
    state["env"] = {"CL": "/DNEW=1"}
    assert not experiments.compile_cached(source)[1]
    assert not experiments.compile_cached(source)[1]


def test_new_header_and_corrupt_receipt_invalidate_cache(compiler):
    source, _ = compiler
    obj, _ = experiments.compile_cached(source)
    (source.parent / "shadow.h").write_text("// newly shadowing a header")
    assert not experiments.compile_cached(source)[1]
    obj.with_name("cache.json").write_text("{")
    assert not experiments.compile_cached(source)[1]


def test_unknown_include_root_never_reuses(compiler):
    source, state = compiler
    state["env"] = {"INCLUDE": str(source.parent / "missing")}
    assert not experiments.compile_cached(source)[1]
    assert not experiments.compile_cached(source)[1]


def test_failed_compile_is_preserved_but_not_reused(compiler):
    source, state = compiler
    state["fail"] = True
    for _ in range(2):
        with pytest.raises(RuntimeError):
            experiments.compile_cached(source)
    assert state["calls"] == 2
    assert len(list((source.parent.parent / "build/experiments").glob("*/failure-*.json"))) == 2


def test_concurrent_cache_requests_compile_once(compiler):
    source, state = compiler
    with ThreadPoolExecutor(2) as executor:
        results = list(executor.map(experiments.compile_cached, [source, source]))
    assert state["calls"] == 1
    assert sorted(reused for _, reused in results) == [False, True]


def test_claims_are_all_or_nothing_and_owner_release_is_scoped(tmp_path):
    fleet_run.claim(tmp_path, "first", [("0x1000", 8)])
    with pytest.raises(RuntimeError):
        fleet_run.claim(tmp_path, "second", [("0x2000", 8), ("0x1000", 8)])
    assert fleet_run.active_rvas(tmp_path) == {"0x1000"}
    fleet_run.release(tmp_path, "second", "failed acquisition")
    assert fleet_run.active_rvas(tmp_path) == {"0x1000"}
    fleet_run.release(tmp_path, "first", "worker exited")
    assert not fleet_run.active_rvas(tmp_path)


def test_real_worker_exit_status_run_env_and_old_logs_survive(tmp_path):
    brief_path = tmp_path / "brief.txt"
    brief_path.write_text("TARGETS:\n- 0x00001000 8B foo\n")
    log = tmp_path / "worker.log"
    log.write_text("old transcript")
    command = [sys.executable, "-c", "import os,sys; print(os.environ['BFME_RUN_ID']); sys.exit(7)"]
    for _ in range(2):
        assert fleet_run.execute(tmp_path, brief_path, log, "test", "1", command) == 7
    records = list((tmp_path / "build/fleet_runs").glob("*/record.json"))
    assert len(records) == 2
    for path in records:
        result = json.loads(path.read_text())
        assert result["exit_code"] == 7
        assert result["id"] in path.with_name("output.log").read_text()
        assert path.with_name("brief.txt").read_bytes() == brief_path.read_bytes()
    assert any(p.read_text() == "old transcript" for p in tmp_path.glob("worker.log.before-*"))
    assert not fleet_run.active_rvas(tmp_path)


def test_missing_executable_releases_claim_and_records_failure(tmp_path):
    brief_path = tmp_path / "brief.txt"
    brief_path.write_text("- 0x00001000 8B foo\n")
    with pytest.raises(FileNotFoundError):
        fleet_run.execute(tmp_path, brief_path, tmp_path / "log", "test", "1", [str(tmp_path / "missing")])
    assert not fleet_run.active_rvas(tmp_path)
    record = json.loads(next((tmp_path / "build/fleet_runs").glob("*/record.json")).read_text())
    assert record["status"] == "failed"


def test_run_tag_cannot_inject_rows(monkeypatch):
    monkeypatch.setenv("BFME_RUN_ID", "abc-123")
    assert fleet_run.run_tag("note") == "note run=abc-123"
    monkeypatch.setenv("BFME_RUN_ID", "abc,\nforged")
    assert fleet_run.run_tag("note") == "note"


def test_retry_requires_changed_source_not_a_larger_claimed_score(tmp_path, monkeypatch):
    path = tmp_path / "stash.cpp"
    path.write_text("// name\n// partial score=0.5 date=2026-09-04\nint f(){return 1;}")
    monkeypatch.setattr(re_log, "stash_for", lambda _: (path, .9))
    before = fleet_run.stash_fingerprint(0x1000)
    path.write_text("// name\n// partial score=0.9 date=2026-09-05\nint f(){return 1;}")
    assert fleet_run.stash_fingerprint(0x1000) == before
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/re_attempts.log").write_text("name\t0x1000\t8\tpartial\tbanked\n")
    ledger = tmp_path / "reverse/functions.csv"
    ledger.write_text("target_rva,source\n0x1000,Code/a.asm\n")
    assert not fleet_run.retry_allowed(tmp_path, 0x1000, before)
    path.write_text("// name\n// partial score=0.9 date=2026-09-05\nint f(){return 2;}")
    assert fleet_run.retry_allowed(tmp_path, 0x1000, before)
    ledger.write_text("target_rva,source\n0x1000,Code/a.cpp\n")
    assert not fleet_run.retry_allowed(tmp_path, 0x1000, before)


def test_variants_are_finite_nonoverlapping_and_do_not_inject_asm():
    choices = [{"before": "return 1", "after": ["return 2", "return 2"]}]
    assert [s for _, s in shape_search.variants("int f(){return 1;}", choices)] == ["int f(){return 1;}", "int f(){return 2;}"]
    with pytest.raises(ValueError):
        list(shape_search.variants("return 1", [{"before": "return 1", "after": []}, {"before": "1", "after": ["2"]}]))
    with pytest.raises(ValueError):
        list(shape_search.variants("return 1", [{"before": "return 1", "after": ["__asm ret"]}]))


def test_search_preserves_best_and_stops_on_plateau(tmp_path, monkeypatch):
    monkeypatch.setattr(shape_search.build, "ROOT", tmp_path)
    monkeypatch.setattr(shape_search.build, "read_target_bytes", lambda r, s: b"12345678")
    source = tmp_path / "test.cpp"
    source.write_text("int f(){return 1;}")
    scores = iter([.9, .8, .8, .99])
    def evaluate(*_):
        score = next(scores)
        return dict(score=score, shape=str(score), masked_shape_equal=False)
    path, result = shape_search.search(source, "_f", 0, 8,
        [{"before": "return 1", "after": ["return 2", "return 3", "return 4"]}],
        plateau=2, evaluator=evaluate)
    assert len(result["trials"]) == 3
    assert (path / result["best"]).read_text() == source.read_text() == "int f(){return 1;}"
    assert result["trials"][2]["new_shape"] is False
    assert result["acceptance"].startswith("none")


def test_report_deduplicates_aliases_and_excludes_dumps():
    def row(rva, size, source="Code/Test.cpp", run="r1"):
        return dict(target_rva=rva, target_size=str(size), source=source, status="matched", notes="run=" + run)
    rows = [row("0x1000", 10), row("0x1000", 10), row("0x1008", 5), row("0x2000", 30, "Code/gen_asm/a.asm")]
    assert fleet_report.published(rows) == {"r1": 13}


def test_donor_lookup_rejects_changed_source_and_image(tmp_path, monkeypatch):
    monkeypatch.setattr(source_donors.build, "ROOT", tmp_path)
    source = tmp_path / "test.cpp"
    source.write_text("int f(){return 1;}")
    image = tmp_path / "game.exe"
    image.write_bytes(b"retail")
    monkeypatch.setattr(source_donors.build, "EXE", image)
    index = tmp_path / "donors.json"
    monkeypatch.setattr(source_donors, "INDEX", index)
    monkeypatch.setattr(source_donors, "shape", lambda *_: "shape")
    index.write_text(json.dumps(dict(max_size=100, exe=source_donors.sha(image), shapes={"shape": [dict(source="test.cpp", source_sha256=source_donors.sha(source))]})))
    assert len(source_donors.lookup(0, 8)) == 1
    source.write_text("changed")
    assert not source_donors.lookup(0, 8)
    image.write_bytes(b"other retail")
    assert not source_donors.lookup(0, 8)
