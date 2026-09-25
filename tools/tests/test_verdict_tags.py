"""Every verdict names its model, every real deferral its blocker.

Measured 2026-09-25 over 3,807 new verdict rows: 3,011 named no usable model
and 901 blocked/partial rows had no blocker=, so neither lane yield nor shared
blockers could be measured. fleet_run now exports the model it launched and
re_log refuses a row that still has none.
"""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import fleet_run  # noqa: E402
import re_log  # noqa: E402

SYM = "?Sym@@QAEXXZ"


@pytest.fixture
def log(tmp_path, monkeypatch):
    path = tmp_path / "re_attempts.log"
    path.write_text("", encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", path)
    monkeypatch.delenv("BFME_MODEL", raising=False)
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.delenv("BFME_RUN_DIR", raising=False)
    re_log._reset()
    yield path
    re_log._reset()


def record(*args):
    try:
        re_log._record(list(args))
    except SystemExit as refusal:
        return str(refusal)
    return None


def test_a_verdict_without_a_model_is_refused(log):
    refusal = record(SYM, "0x00401000", "16", "no-match", "not a boundary t=20")
    assert refusal and "model=" in refusal
    assert log.read_text(encoding="utf-8") == ""


def test_the_placeholder_model_is_not_a_model(log):
    assert "model=" in record(SYM, "0x00401000", "16", "no-match", "x model=MODEL")


def test_bfme_model_tags_the_row(log, monkeypatch):
    monkeypatch.setenv("BFME_MODEL", "gpt-6-astra")
    assert record(SYM, "0x00401000", "16", "no-match", "not a boundary t=20") is None
    assert "model=gpt-6-astra" in log.read_text(encoding="utf-8")


def test_an_explicit_model_wins_over_the_environment(log, monkeypatch):
    monkeypatch.setenv("BFME_MODEL", "gpt-6-luna")
    assert record(SYM, "0x00401000", "16", "no-match", "x model=claude-opus-5-5") is None
    text = log.read_text(encoding="utf-8")
    assert "model=claude-opus-5-5" in text and "gpt-6-luna" not in text


def test_a_real_blocked_session_needs_a_blocker(log):
    refusal = record(SYM, "0x00401000", "16", "blocked", "layout unknown t=40 model=m")
    assert refusal and "blocker=" in refusal
    assert record(SYM, "0x00401000", "16", "blocked", "t=40 model=m blocker=layout/x") is None


def test_a_quick_look_may_omit_the_blocker(log):
    # eligibility.quick_look does not count these as attempts; demanding a
    # blocker would turn every glance into one
    assert record(SYM, "0x00401000", "16", "blocked", "no named caller t=3 model=m") is None


def test_a_refused_partial_leaves_no_bank_behind(log, tmp_path, monkeypatch):
    attempts = re_log._stash_path(0x00401000).parent   # beside the tmp log
    body = tmp_path / "body.cpp"
    body.write_text("int f() { return 1; }\n", encoding="utf-8")
    refusal = record(SYM, "0x00401000", "16", "partial", "close t=40 model=m",
                     "--stash", str(body), "--score", "0.9")
    assert refusal and "blocker=" in refusal
    assert not attempts.exists() or not any(attempts.iterdir())


@pytest.mark.parametrize("command, model", [
    (["codex", "exec", "-m", "gpt-6-astra", "-"], "gpt-6-astra"),
    (["codex", "exec", "--model", "gpt-6-sol", "-"], "gpt-6-sol"),
    (["claude", "--model=claude-opus-5-5"], "claude-opus-5-5"),
    (["codex", "exec", "-"], ""),
    (["codex", "-m", "bad model;rm"], ""),
])
def test_launched_model(command, model):
    assert fleet_run.launched_model(command) == model
