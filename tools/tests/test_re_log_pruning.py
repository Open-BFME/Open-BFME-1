"""A pathname-only historical sweep is not byte or identity evidence."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import re_log
import eligibility
import list_naked_candidates as queue
import next_work

SYM = "?updateAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z"
RVA = 0x00497140
PRUNING = (
    "Superseded by the ledger: this symbol is matched from Code/Thunk.cpp, "
    "a real source, so the standing 'no-match' verdict is stale. "
    "Recorded by the tree-wide pruning pass that cross-referenced every logged "
    "symbol against its current ledger SOURCE PATH -- matched from a real .cpp "
    "means recovered, matched from gen_asm or gen_small means still open."
)


def row(status, evidence="measured evidence", rva=RVA, symbol=SYM):
    return f"{symbol}\t0x{rva:08X}\t233\t{status}\t{evidence}\r\n"


@pytest.fixture
def log(tmp_path, monkeypatch):
    path = tmp_path / "re_attempts.log"
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", path)
    re_log._reset()
    yield path
    re_log._reset()


@pytest.mark.parametrize("status", sorted(re_log.DEAD_END_STATUSES))
def test_pruning_does_not_release_a_measured_dead_end(log, status):
    log.write_text(row(status) + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == status
    assert re_log.latest_records()[RVA][3] == status
    assert re_log.is_dead_end(SYM, RVA)
    kept, suppressed = queue.drop_logged([{"symbol": SYM, "rva": hex(RVA)}])
    assert kept == [] and suppressed == 1


@pytest.mark.parametrize("status", sorted(re_log.DEFERRED_STATUSES))
def test_pruning_preserves_deferrals_and_banks(log, status):
    log.write_text(row(status) + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == status
    assert re_log.latest_records()[RVA][3] == status
    assert re_log.is_deferred(SYM, RVA)
    assert re_log.attempts(SYM) == 1
    items = [{"symbol": SYM, "rva": hex(RVA)}]
    assert queue.drop_logged(items) == (items, 0)


@pytest.mark.parametrize("status", ["converted", "solved", "landed", "partial"])
def test_later_actual_verdict_still_wins(log, status):
    log.write_text(row("no-boundary") + row("converted", PRUNING) + row(status))
    assert re_log.standing_status(SYM, RVA) == status
    assert re_log.latest_records()[RVA][3] == status
    assert not re_log.is_dead_end(SYM, RVA)


def test_pruning_alone_does_not_invent_a_verdict(log):
    log.write_text(row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) is None
    assert re_log.latest_records() == {}


def test_pruning_preserves_an_earlier_actual_conversion(log):
    log.write_text(row("no-match") + row("converted", "actual byte proof")
                   + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == "converted"
    assert re_log.latest_records()[RVA][4] == "actual byte proof"


def test_other_symbol_at_same_rva_keeps_its_own_verdict(log):
    other = "?independent@@YAXXZ"
    log.write_text(row("no-boundary") + row("landed", symbol=other)
                   + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == "no-boundary"
    assert re_log.standing_status(other, RVA) == "landed"
    assert re_log.latest_records()[RVA][0] == other


def test_three_field_boundary_finding_survives_pruning(log):
    log.write_text(f"{SYM}\tno-match\tmeasured extent\n" + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA, boundary_moved=True) == "no-match"
    assert re_log.latest_records() == {}


def test_new_boundary_remains_available(log):
    log.write_text(row("no-boundary") + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA + 16, boundary_moved=True) is None


def test_void_still_retracts_only_prior_exact_boundary(log):
    log.write_text(row("no-boundary") + row("converted", PRUNING)
                   + row("void") + row("partial", rva=RVA + 16))
    assert re_log.standing_status(SYM, RVA, boundary_moved=True) is None
    assert set(re_log.latest_records()) == {RVA + 16}


def test_later_refutation_can_close_an_actual_conversion(log):
    log.write_text(row("converted") + row("identity-suspect")
                   + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == "identity-suspect"
    assert re_log.latest_records()[RVA][3] == "identity-suspect"


@pytest.mark.parametrize("evidence", [
    "clean C++ compiled and matched from Code/Thunk.cpp",
    "SOURCE PATH checked alongside actual compiled bytes",
    PRUNING.replace("Recorded by the tree-wide pruning pass", "Independently verified"),
    "Independent conversion supersedes the old attempt. " + PRUNING,
])
def test_only_the_specific_path_only_pass_is_reclassified(log, evidence):
    log.write_text(row("no-match") + row("converted", evidence))
    assert re_log.standing_status(SYM, RVA) == "converted"
    assert re_log.latest_records()[RVA][3] == "converted"


@pytest.mark.parametrize("legacy", [False, True])
def test_both_queues_preserve_boundary_findings(log, legacy):
    prior = f"{SYM}\tno-match\tmeasured extent\n" if legacy else row("no-match")
    log.write_text(prior + row("converted", PRUNING))
    assert queue.drop_logged([{"symbol": SYM, "rva": hex(RVA)}]) == ([], 1)
    assert next_work.drop_logged([{"function": SYM, "target_rva": hex(RVA)}]) == ([], 1)
    records = re_log.latest_records()
    if legacy:
        assert not records
    else:
        assert records[RVA][3] == "no-match"
        moved = [{"function": SYM, "target_rva": hex(RVA + 16),
                  "hint": "drift-corrected"}]
        assert next_work.drop_logged(moved) == (moved, 0)


@pytest.mark.parametrize("status", ["converted", "partial", "blocked"])
def test_both_queues_keep_later_genuine_verdicts(log, status):
    log.write_text(row("no-match") + row("converted", PRUNING) + row(status))
    naked = [{"symbol": SYM, "rva": hex(RVA)}]
    structural = [{"function": SYM, "target_rva": hex(RVA)}]
    assert queue.drop_logged(naked) == (naked, 0)
    assert next_work.drop_logged(structural) == (structural, 0)
    assert re_log.latest_records()[RVA][3] == status
    if status in re_log.DEFERRED_STATUSES:
        assert structural[0]["deferred_attempts"] == 1


@pytest.mark.parametrize("placeholder_rows", [0, 1])
def test_naked_queue_counts_deferred_work_by_rva_after_name_change(log, placeholder_rows):
    placeholder = "?d_00497140@@YAXXZ"
    lines = [row("blocked", symbol=placeholder)] if placeholder_rows else []
    lines += [row("partial", symbol=SYM), row("blocked", symbol=SYM)]
    log.write_text("".join(lines))
    candidate = {"symbol": placeholder, "rva": hex(RVA)}
    assert eligibility.attempt_counts().get(RVA) == 2 + placeholder_rows
    assert queue.drop_logged([candidate]) == ([candidate], 0)
    assert candidate["deferred_attempts"] == 2 + placeholder_rows
    if placeholder_rows == 0:
        candidate.update(score=0, size=233, path="Code/gen_asm/test.asm", line=1)
        selected, meta = queue.select_candidate([candidate])
        assert selected is candidate
        assert meta["exhausted"] is True


def test_naked_queue_keeps_three_field_symbol_only_deferral(log):
    log.write_text(f"{SYM}\tblocked\tunknown boundary\n")
    candidate = {"symbol": SYM, "rva": hex(RVA)}
    assert queue.drop_logged([candidate]) == ([candidate], 0)
    assert candidate["deferred_attempts"] == 1


def test_naked_queue_retires_placeholder_after_other_name_refutes_rva(log):
    placeholder = "?d_00497140@@YAXXZ"
    log.write_text(row("blocked", symbol=placeholder)
                   + row("no-match", symbol=SYM))
    assert eligibility.latest_verdicts()[RVA] == "no-match"
    assert queue.drop_logged([{"symbol": placeholder, "rva": hex(RVA)}]) == ([], 1)


def test_naked_queue_uses_symbol_only_finding_without_rva_verdict(log):
    log.write_text(f"{SYM}\tno-match\tmeasured symbol finding\n")
    assert queue.drop_logged([{"symbol": SYM, "rva": hex(RVA)}]) == ([], 1)


def test_naked_queue_later_exact_partial_releases_symbol_only_dead_end(log):
    log.write_text(f"{SYM}\tno-match\told symbol finding\n" + row("partial"))
    candidate = {"symbol": SYM, "rva": hex(RVA)}
    assert queue.drop_logged([candidate]) == ([candidate], 0)
    assert candidate["deferred_attempts"] == 1


def test_naked_queue_voided_refutation_does_not_retire_after_rename(log):
    placeholder = "?d_00497140@@YAXXZ"
    log.write_text(row("no-match", symbol=SYM)
                   + row("void", symbol=SYM)
                   + row("blocked", symbol=placeholder))
    candidate = {"symbol": placeholder, "rva": hex(RVA)}
    assert queue.drop_logged([candidate]) == ([candidate], 0)
    assert candidate["deferred_attempts"] >= 1


def test_naked_queue_quick_look_remains_untried(log):
    log.write_text(row("blocked", "t=2min no named caller"))
    candidate = {"symbol": SYM, "rva": hex(RVA), "score": 0, "size": 233,
                 "path": "Code/gen_asm/test.asm", "line": 1}
    assert eligibility.attempt_counts().get(RVA, 0) == 0
    assert queue.drop_logged([candidate]) == ([candidate], 0)
    assert "deferred_attempts" not in candidate
    selected, meta = queue.select_candidate([candidate])
    assert selected is candidate
    assert meta["exhausted"] is False


def test_naked_queue_skips_latest_short_boundary_suspect_across_names(log):
    placeholder = "?d_00497140@@YAXXZ"
    log.write_text(row("blocked", "t=3min starts inside another live body",
                       symbol=SYM))
    candidate = {"symbol": placeholder, "rva": hex(RVA)}
    assert eligibility.attempt_counts().get(RVA, 0) == 0
    assert eligibility.boundary_suspect(RVA)
    assert queue.drop_logged([candidate]) == ([], 1)


def test_naked_queue_reopens_after_later_nonboundary_verdict(log):
    placeholder = "?d_00497140@@YAXXZ"
    log.write_text(row("blocked", "t=3min starts inside another live body",
                       symbol=SYM) + row("partial", "new entry witness and banked body",
                                         symbol=placeholder))
    candidate = {"symbol": placeholder, "rva": hex(RVA)}
    assert not eligibility.boundary_suspect(RVA)
    assert queue.drop_logged([candidate]) == ([candidate], 0)


def test_naked_queue_does_not_hide_other_rva_after_boundary_finding(log):
    log.write_text(row("blocked", "t=3min starts inside another live body"))
    candidate = {"symbol": SYM, "rva": hex(RVA + 16)}
    assert queue.drop_logged([candidate]) == ([candidate], 0)
