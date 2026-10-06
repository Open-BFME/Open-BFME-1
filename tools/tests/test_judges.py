"""The judge contract (decision record, pillar 5), identical in Open-BFME-1 and Open-BFME-2.

Only tools/judges.json's judges run; a verdict counts only when tools/judges.py
launched the model and the CLI's own record names a model the judge accepts;
self-declared models never count; judges.json cannot change without a
Verifier-Change trailer. No model is called: the CLIs are faked at their
process boundary, which is exactly where the real ones plug in.
"""
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))
import judges  # noqa: E402
import protected_paths  # noqa: E402

DECISION_RECORD = {"gpt-6-astra", "gpt-6.1-sol", "claude-opus-5-5", "claude-fable-5-1"}
VERDICT = '{"verdict": "clean", "defects": [], "model": "gpt-6.1-sol"} model=gpt-6.1-sol'


@pytest.fixture(autouse=True)
def isolated(tmp_path, monkeypatch):
    monkeypatch.setenv("CODEX_HOME", str(tmp_path / "codex"))
    monkeypatch.setenv("JUDGE_LOG_DIR", str(tmp_path / "log"))
    monkeypatch.delenv("JUDGE_RUNNER_KEY", raising=False)
    monkeypatch.delenv("JUDGE_RUNNERS", raising=False)


def fake_codex(thread, reply, calls=None):
    events = [{"type": "thread.started", "thread_id": thread},
              {"type": "item.completed", "item": {"type": "agent_message", "text": reply}}]

    def runner(cmd, **kw):
        if calls is not None:
            calls.append(cmd)
        return subprocess.CompletedProcess(cmd, 0, "\n".join(json.dumps(e) for e in events), "")
    return runner


def fake_claude(models, reply):
    def runner(cmd, **kw):
        out = {"result": reply, "modelUsage": {m: {"outputTokens": 10} for m in models}}
        return subprocess.CompletedProcess(cmd, 0, json.dumps(out), "")
    return runner


def rollout(thread, model):
    """What Codex itself writes for a thread: the model that ran its turns."""
    path = Path(os.environ["CODEX_HOME"]) / "sessions" / "2026" / "10" / "06" / f"rollout-x-{thread}.jsonl"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps({"type": "turn_context", "payload": {"model": model}}).replace(" ", "") + "\n")


def key_file(tmp_path, monkeypatch):
    path = tmp_path / "runner.key"
    path.write_text(os.urandom(32).hex())
    monkeypatch.setenv("JUDGE_RUNNER_KEY", str(path))
    return bytes.fromhex(path.read_text())


# --- the allowlist ------------------------------------------------------------------

def test_the_shipped_allowlist_is_the_decision_record_s_four_models():
    cfg = judges.config()
    assert set(judges.allowlist(cfg)) == DECISION_RECORD
    assert {j["family"] for j in cfg["judges"]} == {"openai", "anthropic"}
    for j in cfg["judges"]:
        assert j["accept"] == [j["id"]]                 # no judge accepts another model's answer
    named = set(cfg["panel"]["first"]) | set(cfg["panel"]["escalate"]) | set(cfg["proposers"])
    assert named <= DECISION_RECORD


def test_a_malformed_allowlist_refuses_every_judge(tmp_path):
    bad = tmp_path / "judges.json"
    bad.write_text(json.dumps({"judges": ["gpt-6.1-sol"]}))            # a bare-name list: no accept rule
    with pytest.raises(judges.JudgeRefused):
        judges.config(bad)
    assert not judges.allowed("gpt-6.1-sol", bad)                      # fails closed
    assert not judges.allowed("gpt-6.1-sol", tmp_path / "absent.json")
    assert judges.allowed("GPT-6.1-sol") and not judges.allowed("gpt-6.1-sol-mini")


# --- a non-allowlisted model is ignored -------------------------------------------

def test_a_model_outside_the_allowlist_never_runs(tmp_path):
    calls = []
    for model in ("gpt-4o-mini", "grok", "claude-opus", ""):
        with pytest.raises(judges.JudgeRefused):
            judges.judge_call(model, "x", runner=fake_codex("t0", VERDICT, calls))
        assert not judges.allowed(model)
    assert calls == [] and not (tmp_path / "log" / "calls.jsonl").exists()


def test_host_runners_change_commands_but_cannot_add_judges(tmp_path):
    runners = {"gpt-6.1-sol": {"command": ["my-codex", "-"]}, "gpt-4o-mini": {"command": ["x"]}}
    assert judges.command_for(judges.judge("gpt-6.1-sol"), runners) == ["my-codex", "-"]
    with pytest.raises(judges.JudgeRefused):
        judges.judge_call("gpt-4o-mini", "x", runners=runners, runner=fake_codex("t0", VERDICT))


def test_a_listed_judge_answered_by_another_model_does_not_count():
    rollout("t1", "gpt-5-mini")                    # the CLI fell back to / was pointed at another model
    got = judges.judge_call("gpt-6.1-sol", "p", runner=fake_codex("t1", VERDICT))
    assert got.record["answering_model"] == "gpt-5-mini" and not got.counted


# --- a self-declared model never counts -------------------------------------------

def test_a_model_the_reply_claims_for_itself_never_counts():
    got = judges.judge_call("gpt-6.1-sol", "p", runner=fake_codex("t2", VERDICT))   # no rollout: no CLI record
    assert got.record["answering_model"] is None and not got.counted
    assert "gpt-6.1-sol" in got.record["claimed_model"]                            # kept as a diagnostic only


def test_a_hand_written_or_relabelled_record_never_counts(tmp_path, monkeypatch):
    key = key_file(tmp_path, monkeypatch)
    forged = {"judge": "gpt-6.1-sol", "family": "openai", "answering_model": "gpt-6.1-sol", "exit": 0,
              "counted": True}                                           # what a worker could write as model=
    assert not judges.verify_record(forged, key)
    assert not judges.verify_record(dict(forged, mac="0" * 64), key)
    rollout("t3", "gpt-6-astra")
    real = judges.judge_call("gpt-6-astra", "p", runner=fake_codex("t3", VERDICT)).record
    assert judges.verify_record(real, key)
    assert not judges.verify_record(dict(real, judge="gpt-6.1-sol"), key)              # relabelled judge
    assert not judges.verify_record(dict(real, answering_model="claude-opus-5-5"), key)
    assert not judges.verify_record(real, os.urandom(32))                              # another key
    assert not judges.verify_record(real, None)                                        # nothing to check with


# --- an allowlisted, runner-attested verdict counts -------------------------------

def test_an_attested_codex_verdict_counts_and_is_logged(tmp_path):
    calls = []
    rollout("t4", "gpt-6.1-sol")
    got = judges.judge_call("gpt-6.1-sol", "row 0x00401000", runner=fake_codex("t4", VERDICT, calls))
    assert got.counted and got.record["judge"] == "gpt-6.1-sol" and got.record["family"] == "openai"
    assert "--json" in calls[0] and calls[0][-1] == "-"                     # judges.json's own command
    assert '"verdict": "clean"' in got.reply and "mac" not in got.record      # unsigned without a key
    logged = json.loads((tmp_path / "log" / "calls.jsonl").read_text().splitlines()[-1])
    assert logged["id"] == got.record["id"] and logged["reply"] == got.reply


def test_an_attested_claude_verdict_counts():
    got = judges.judge_call("claude-opus-5-5", "p", runner=fake_claude(["claude-opus-5-5[1m]"], VERDICT))
    assert got.counted and got.record["answering_model"] == "claude-opus-5-5[1m]"
    other = judges.judge_call("claude-opus-5-5", "p", runner=fake_claude(["claude-haiku-4"], VERDICT))
    assert not other.counted


def test_a_failed_launch_never_counts():
    def missing(cmd, **kw):
        raise FileNotFoundError(cmd[0])
    got = judges.judge_call("gpt-6.1-sol", "p", runner=missing)
    assert got.record["exit"] == 127 and not got.counted


# --- judges.json is a protected path ----------------------------------------------

def test_the_runner_and_its_allowlist_are_protected_paths():
    assert {"tools/judges.json", "tools/judges.py"} <= set(protected_paths.protected(
        ["tools/judges.json", "tools/judges.py", "game/a.cpp"]))
    hook = (REPO / ".githooks" / "commit-msg").read_text(encoding="utf-8")
    assert "protected_paths.py" in hook and "--commit-msg" in hook


def git(cwd, *args):
    return subprocess.run(["git", "-c", "core.hooksPath=no-hooks", *args], cwd=cwd, capture_output=True,
                          text=True, check=True)


def test_the_commit_msg_hook_refuses_a_judges_json_edit_without_the_trailer(tmp_path):
    repo = tmp_path / "repo"
    (repo / "tools").mkdir(parents=True)
    git(tmp_path, "init", "-q", str(repo))
    git(repo, "config", "user.name", "t")
    git(repo, "config", "user.email", "t@example.com")
    shutil.copy(TOOLS / "protected_paths.py", repo / "tools" / "protected_paths.py")
    shutil.copy(TOOLS / "judges.json", repo / "tools" / "judges.json")
    git(repo, "add", ".")
    git(repo, "commit", "-q", "-m", "base")
    widened = judges.config(repo / "tools" / "judges.json")
    widened["judges"].append(dict(widened["judges"][0], id="gpt-4o-mini", accept=["gpt-4o-mini"]))
    (repo / "tools" / "judges.json").write_text(json.dumps(widened))
    git(repo, "add", "tools/judges.json")

    def hook(message):
        """.githooks/commit-msg: HEAD's checker, never the working copy's, on the staged change."""
        (repo / "MSG").write_text(message)
        checker = git(repo, "show", "HEAD:tools/protected_paths.py").stdout
        return subprocess.run([sys.executable, "-", "--commit-msg", str(repo / "MSG")], input=checker,
                              cwd=repo, capture_output=True, text=True)

    refused = hook("add a judge\n")
    assert refused.returncode == 1 and "tools/judges.json" in refused.stderr
    assert hook("add a judge\n\nVerifier-Change: owner adds a judge after review\n").returncode == 0


def test_moving_judges_json_out_of_the_protected_paths_is_refused_too(tmp_path):
    repo = tmp_path / "repo"
    (repo / "tools").mkdir(parents=True)
    git(tmp_path, "init", "-q", str(repo))
    git(repo, "config", "user.name", "t")
    git(repo, "config", "user.email", "t@example.com")
    shutil.copy(TOOLS / "protected_paths.py", repo / "tools" / "protected_paths.py")
    shutil.copy(TOOLS / "judges.json", repo / "tools" / "judges.json")
    git(repo, "add", ".")
    git(repo, "commit", "-q", "-m", "base")
    git(repo, "mv", "tools/judges.json", "judges.json")          # git sees a rename: only the new name
    (repo / "MSG").write_text("tidy\n")
    checker = git(repo, "show", "HEAD:tools/protected_paths.py").stdout
    got = subprocess.run([sys.executable, "-", "--commit-msg", str(repo / "MSG")], input=checker, cwd=repo,
                         capture_output=True, text=True)
    assert got.returncode == 1 and "tools/judges.json" in got.stderr
