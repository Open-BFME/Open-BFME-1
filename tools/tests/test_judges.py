"""Allowlisted judges: only listed models run, and the record names the model
the runner invoked, never the one the answer claims."""
import json
import os
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import judges  # noqa: E402

ECHO = [sys.executable, "-c",
        "import sys; p = sys.stdin.read(); print('verdict: ok for ' + p.strip() + ' model=gpt-6-astra')"]


def test_the_shipped_allowlist_is_the_decision_record_s_four_models():
    assert sorted(judges.allowlist()) == ["claude-fable-5-1", "claude-opus-5-5", "gpt-6-astra",
                                          "gpt-6.1-sol"]
    assert {e["family"] for e in judges.allowlist().values()} == {"openai", "anthropic"}


def test_a_model_outside_the_allowlist_never_runs(tmp_path):
    for model in ("gpt-4o-mini", "some-weak-model", ""):
        with pytest.raises(judges.JudgeRefused):
            judges.judge_call(model, "x", runners={model: {"command": ECHO}}, log_dir=tmp_path)
    assert not (tmp_path / "calls.jsonl").exists()                 # nothing ran, nothing logged


def test_the_record_names_the_invoked_model_not_the_claimed_one(tmp_path, monkeypatch):
    key = tmp_path / "runner.key"
    key.write_text(os.urandom(32).hex())
    monkeypatch.setenv("JUDGE_RUNNER_KEY", str(key))
    result = judges.judge_call("claude-opus-5-5", "row 0x00401000",
                               runners={"claude-opus-5-5": {"command": ECHO}}, log_dir=tmp_path)
    record = result.record
    assert record["model"] == "claude-opus-5-5" and record["family"] == "anthropic"
    assert record["claimed_model"] == ["gpt-6-astra"] and record["claim_disagrees"]
    assert "row 0x00401000" in result.output and record["exit"] == 0
    secret = bytes.fromhex(key.read_text())
    assert judges.verify_record(record, secret)
    assert not judges.verify_record(dict(record, model="gpt-6-astra"), secret)   # relabelled
    assert not judges.verify_record(dict(record, mac=None), secret)               # unsigned
    logged = json.loads((tmp_path / "calls.jsonl").read_text().splitlines()[-1])
    assert logged["id"] == record["id"] and logged["output"] == result.output


def test_host_runners_change_commands_but_cannot_add_judges(tmp_path):
    runners = {"gpt-6.1-sol": {"command": ECHO}, "gpt-4o-mini": {"command": ECHO}}
    entry, command = judges.command_for("gpt-6.1-sol", runners=runners)
    assert command == ECHO and entry["family"] == "openai"
    with pytest.raises(judges.JudgeRefused):
        judges.command_for("gpt-4o-mini", runners=runners)
    failing = judges.judge_call("gpt-6.1-sol", "x", runners={"gpt-6.1-sol": {
        "command": [sys.executable, "-c", "import sys; sys.exit(3)"]}}, log_dir=tmp_path)
    assert failing.record["exit"] == 3 and failing.record["model"] == "gpt-6.1-sol"
    missing = judges.judge_call("gpt-6.1-sol", "x", runners={"gpt-6.1-sol": {
        "command": ["no-such-binary-for-judges-test"]}}, log_dir=tmp_path)
    assert missing.record["exit"] == 127
