"""The naming lane counts only judge-runner votes (decision record, pillar 5).

A vote agrees a name only when tools/judges.py called an allowlisted judge and a
signed receipt binds the session's votes to it. `next --model X` / `submit`
proposals, votes from non-allowlisted models and hand-written agreed rows never
land a name. No model is called: the CLIs are faked at their process boundary.
"""
import argparse
import collections
import json
import os
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import judges  # noqa: E402
import name_lane  # noqa: E402

REL, IDENT = "game/a.cpp", "m_bfmeSlot1A"
KEY = f"{REL}|member||{IDENT}"
ANSWER = {IDENT: "m_ladderSlot"}


@pytest.fixture
def lane(tmp_path, monkeypatch):
    rev = tmp_path / "reverse"
    rev.mkdir()
    for name, path in (("VOTES", "name_votes.csv"), ("AGREED", "name_agreed.csv"),
                       ("RECEIPTS", "name_vote_receipts.jsonl")):
        monkeypatch.setattr(name_lane, name, rev / path)
    monkeypatch.setitem(name_lane.COLUMNS, rev / "name_votes.csv", ["key", "hash", "model", "session", "date"])
    monkeypatch.setitem(name_lane.COLUMNS, rev / "name_agreed.csv", ["key", "name", "models", "status", "date"])
    monkeypatch.setattr(name_lane, "SESSIONS", tmp_path / "sessions")
    monkeypatch.setattr(name_lane, "ledger_rows", lambda: {REL: []})
    monkeypatch.setattr(name_lane, "type_counts", lambda: collections.Counter())
    monkeypatch.setattr(name_lane, "ea_labelled", lambda: {})
    monkeypatch.setattr(name_lane, "servable", lambda *a: True)
    monkeypatch.setattr(name_lane, "read", lambda rel: f"struct S {{ int {IDENT}; }};\n")
    monkeypatch.setattr(name_lane, "owned", lambda *a: [("member", "", IDENT), ("member", "", "m_bfmeSlot2B"),
                                                        ("member", "", "m_bfmeSlot3C")])   # `next` wants 3 open
    monkeypatch.setattr(name_lane, "spelling", lambda name, kind: name)
    monkeypatch.setattr(name_lane, "commit", lambda paths, message: SimpleNamespace(returncode=0))
    monkeypatch.setenv("CODEX_HOME", str(tmp_path / "codex"))
    monkeypatch.setenv("JUDGE_LOG_DIR", str(tmp_path / "log"))
    monkeypatch.delenv("JUDGE_RUNNERS", raising=False)
    keyfile = tmp_path / "runner.key"
    keyfile.write_text(os.urandom(32).hex())
    monkeypatch.setenv("JUDGE_RUNNER_KEY", str(keyfile))
    return tmp_path


def fake_cli(tmp_path, answer, codex_model="gpt-6.1-sol", claude_model="claude-opus-5-5"):
    """judges.judge_call with the CLI faked: Codex records `codex_model`, Claude reports `claude_model`."""
    real = judges.judge_call

    def runner(cmd, **kw):
        reply = json.dumps(answer)
        if "codex" in Path(cmd[0]).name:
            thread = os.urandom(4).hex()
            path = tmp_path / "codex" / "sessions" / f"rollout-x-{thread}.jsonl"
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(json.dumps({"type": "turn_context", "payload": {"model": codex_model}}).replace(" ", ""))
            events = [{"type": "thread.started", "thread_id": thread},
                      {"type": "item.completed", "item": {"type": "agent_message", "text": reply}}]
            return subprocess.CompletedProcess(cmd, 0, "\n".join(json.dumps(e) for e in events), "")
        out = {"result": reply, "modelUsage": {claude_model: {"outputTokens": 5}}}
        return subprocess.CompletedProcess(cmd, 0, json.dumps(out), "")
    return lambda judge, prompt, **kw: real(judge, prompt, runner=runner, **kw)


def ask(judge):
    return name_lane.cmd_ask(argparse.Namespace(judge=judge, file=None, count=1))


def propose(lane, model, answer=ANSWER):
    """The self-declared path: `next --model MODEL`, then `submit`."""
    name_lane.cmd_next(argparse.Namespace(model=model, file=None, count=1, list_only=False))
    session = next(lane.joinpath("sessions").glob("*.json")).stem
    path = lane / "answer.json"
    path.write_text(json.dumps(answer))
    name_lane.cmd_submit(argparse.Namespace(answer=str(path), session=session))


def agreed():
    return [a for a in name_lane.table(name_lane.AGREED) if a["status"] == "agreed"]


def test_two_runner_attested_judges_from_two_vendors_agree_a_name(lane, monkeypatch, capsys):
    monkeypatch.setattr(name_lane.judges, "judge_call", fake_cli(lane, ANSWER))
    ask("gpt-6.1-sol")
    assert not agreed()                                         # one vendor is not agreement
    ask("claude-opus-5-5")
    assert [(a["key"], a["name"], a["models"]) for a in agreed()] == [
        (KEY, "m_ladderSlot", "claude-opus-5-5+gpt-6.1-sol")]
    assert set(name_lane.landable()) == {KEY}
    receipts = name_lane.receipts()
    assert [r["judge"] for r in receipts] == ["gpt-6.1-sol", "claude-opus-5-5"]
    assert all(judges.verify_record(r, judges.runner_key()) for r in receipts)


def test_self_declared_proposals_never_agree_a_name(lane, capsys):
    propose(lane, "gpt-6.1-sol")
    propose(lane, "claude-opus")
    propose(lane, "grok")
    assert len(name_lane.table(name_lane.VOTES)) == 3 and not agreed()
    assert name_lane.receipts() == [] and name_lane.landable() == {}
    assert "never counts" in capsys.readouterr().out


def test_a_non_allowlisted_model_cannot_vote_through_the_runner(lane, monkeypatch):
    monkeypatch.setattr(name_lane.judges, "judge_call", fake_cli(lane, ANSWER))
    for model in ("grok", "gemini-3", "claude-opus"):
        with pytest.raises(SystemExit):
            ask(model)
    assert name_lane.table(name_lane.VOTES) == []


def test_a_judge_the_cli_says_another_model_answered_for_records_nothing(lane, monkeypatch, capsys):
    monkeypatch.setattr(name_lane.judges, "judge_call", fake_cli(lane, ANSWER, codex_model="gpt-5-mini"))
    ask("gpt-6.1-sol")
    assert name_lane.table(name_lane.VOTES) == [] and "no counted answer" in capsys.readouterr().out


def test_without_the_runner_key_nothing_is_attested(lane, monkeypatch):
    monkeypatch.setattr(name_lane.judges, "judge_call", fake_cli(lane, ANSWER))
    ask("gpt-6.1-sol")
    ask("claude-opus-5-5")
    monkeypatch.delenv("JUDGE_RUNNER_KEY")
    assert name_lane.landable() == {}
    with pytest.raises(SystemExit):
        ask("claude-fable-5-1")


def test_forged_receipts_and_hand_written_agreed_rows_land_nothing(lane, monkeypatch):
    propose(lane, "gpt-6.1-sol")
    propose(lane, "claude-opus-5-5")
    votes = name_lane.table(name_lane.VOTES)
    with name_lane.RECEIPTS.open("a") as f:                     # receipts a worker could write itself
        for v in votes:
            fake = {"judge": v["model"], "family": "x", "answering_model": v["model"], "exit": 0,
                    "session": v["session"], "votes": name_lane.votes_digest([v]), "mac": "0" * 64}
            f.write(json.dumps(fake) + "\n")
    name_lane.append(name_lane.AGREED, [{"key": KEY, "name": "m_ladderSlot", "models": "claude-opus-5-5+gpt-6.1-sol",
                                         "status": "agreed", "date": "2026-10-06"}])
    assert name_lane.attested_sessions(votes) == {} and name_lane.landable() == {}
    monkeypatch.setattr(name_lane, "owned", lambda *a: (_ for _ in ()).throw(AssertionError("apply must skip it")))
    assert name_lane.cmd_apply(argparse.Namespace(retry_blocked=True)) == 0


def test_a_receipt_covers_exactly_its_session_s_votes(lane, monkeypatch):
    monkeypatch.setattr(name_lane.judges, "judge_call", fake_cli(lane, ANSWER))
    ask("gpt-6.1-sol")
    session = name_lane.table(name_lane.VOTES)[0]["session"]
    name_lane.append(name_lane.VOTES, [{"key": f"{REL}|member||m_other", "hash": "h", "model": "gpt-6.1-sol",
                                        "session": session, "date": "2026-10-06"}])   # smuggled into the session
    assert name_lane.attested_sessions(name_lane.table(name_lane.VOTES)) == {}
