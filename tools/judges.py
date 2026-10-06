#!/usr/bin/env python3
"""Allowlisted LLM judges: the one runner every LLM verdict or vote goes through.

WHY. An LLM verdict (an audit finding, a vote in a naming lane) is only worth
something if we know which model produced it. A `model=` field written by the
worker that ran the model, or a "model" the answer claims for itself, is
whatever that worker wanted it to be. So a verdict counts only when THIS
runner launched the model and read the answering model from the CLI's own
record (decision record, pillar 5).

CONTRACT. Open-BFME-1 and Open-BFME-2 each carry their own copy of this file,
judges.json and tools/tests/test_judges.py (no tool is shared between the
repos, BFME2 PLAN.md decision 3); keep the three identical in both repos.

ALLOWLIST. tools/judges.json, a protected path (changes need a
`Verifier-Change:` trailer), is the only list of judges in the repo:
  judges[]   id, family, rank (strength, for escalation), command (argv;
             {workdir} and {prompt_file} are substituted), stdin (pipe the
             prompt), reply (codex-json | claude-json: how to read the answer),
             answer_model (codex-rollout | claude-json: where the CLI records
             which model answered) and accept (model ids that may answer for
             this judge).
  panel, proposers, timeout_s   defaults for the audit (tools/audit/panel.py).
A host may override the COMMAND of a listed judge (JUDGE_RUNNERS=<json file>:
{id: {"command": [...]}}) because CLIs differ per host; it can never add a
judge or change what it accepts.

RUNNER. judge_call() launches the command itself, in an empty scratch
directory (the judge cannot read the repo), and takes the answering model from
the CLI's own record, never from the reply:
  codex-rollout  ~/.codex/sessions/**/rollout-*-<thread>.jsonl, the turn's model;
                 the thread id comes from `codex exec --json` events.
  claude-json    `claude -p --output-format json` reports usage per model.

RECORD. Every call appends to build/judges/calls.jsonl (JUDGE_LOG_DIR
overrides) and returns a record: the judge invoked, its family, the answering
model, sha256 of argv, prompt and reply, exit, timing, host, any model the
reply names for itself (claimed_model, diagnostic only) and `counted`. With
JUDGE_RUNNER_KEY=<hex key file, readable by the runner host only> the record
is HMAC-signed.

COUNTING. counted(record) is the in-process rule: an allowlisted judge whose
recorded answering model that judge accepts. A record read back from a file or
a commit counts only through verify_record(record, key): the same rule plus a
valid signature. Nothing else counts: not a `model=` note, not a reply's
"model", not a record with the model relabelled.

  from judges import judge_call, counted, verify_record
  python3 tools/judges.py list
  python3 tools/judges.py call JUDGE < prompt.txt
"""
import argparse
import glob
import hashlib
import hmac
import json
import os
import re
import shutil
import socket
import subprocess
import sys
import tempfile
import time
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG = Path(__file__).resolve().with_name("judges.json")
REPLIES = ("codex-json", "claude-json")
ANSWER_MODELS = ("codex-rollout", "claude-json")
FIELDS = ("id", "family", "rank", "command", "stdin", "reply", "answer_model", "accept")
CLAIM = re.compile(r"\bmodel\"?\s*[=:]\s*[\"']?([A-Za-z0-9][A-Za-z0-9._:\[\]-]*)", re.IGNORECASE)


class JudgeRefused(RuntimeError):
    """The model is not an allowlisted judge, or judges.json is malformed."""


class JudgeResult:
    def __init__(self, record, reply):
        self.record, self.reply = record, reply

    @property
    def counted(self):
        return self.record["counted"]


# ------------------------------------------------------------------ allowlist

def config(path=CONFIG):
    """judges.json, checked against the schema. A malformed list refuses every judge."""
    try:
        cfg = json.loads(Path(path).read_text(encoding="utf-8"))
    except (OSError, ValueError) as exc:
        raise JudgeRefused(f"cannot read the judge allowlist {path}: {exc}") from exc
    judges = cfg.get("judges")
    if not isinstance(judges, list) or not judges:
        raise JudgeRefused(f"{path}: `judges` must be a non-empty list of judge entries")
    seen = set()
    for j in judges:
        missing = [f for f in FIELDS if not isinstance(j, dict) or f not in j]
        if missing:
            raise JudgeRefused(f"{path}: judge entry {j!r} lacks {', '.join(missing)}")
        if j["id"] in seen or j["reply"] not in REPLIES or j["answer_model"] not in ANSWER_MODELS \
                or not j["accept"] or not j["command"]:
            raise JudgeRefused(f"{path}: judge {j['id']!r} is duplicated or has an unknown reply/answer_model")
        seen.add(j["id"])
    return cfg


def allowlist(cfg=None):
    """{judge id: entry}."""
    return {j["id"]: j for j in (cfg or config())["judges"]}


def judge(judge_id, cfg=None):
    judges = allowlist(cfg)
    if judge_id not in judges:
        raise JudgeRefused(f"{judge_id!r} is not an allowlisted judge ({', '.join(sorted(judges))})")
    return judges[judge_id]


def allowed(model, path=CONFIG):
    """Is `model` one of the allowlisted judge ids (case-insensitive)? Fails closed."""
    try:
        return (model or "").strip().lower() in {j.lower() for j in allowlist(config(path))}
    except JudgeRefused:
        return False


def accepted(entry, answered):
    """Does the CLI-recorded answering model belong to this judge's allowlist entry?"""
    if not answered:
        return False
    models = answered if isinstance(answered, list) else str(answered).split(",")
    return any(any(m == a or m.startswith(a + "-") or m.startswith(a + "[") for a in entry["accept"])
               for m in models)


def _runners():
    path = os.environ.get("JUDGE_RUNNERS")
    return json.loads(Path(path).read_text(encoding="utf-8")) if path else {}


def command_for(entry, runners=None):
    """The argv for a listed judge: the host override's command, else judges.json's."""
    runners = _runners() if runners is None else runners
    return list((runners.get(entry["id"]) or {}).get("command") or entry["command"])


# ------------------------------------------------------------------ the CLI's own record

def codex_reply(stdout):
    thread, text = None, ""
    for line in stdout.splitlines():
        try:
            event = json.loads(line)
        except ValueError:
            continue
        if not isinstance(event, dict):
            continue
        if event.get("type") == "thread.started":
            thread = event.get("thread_id")
        item = event.get("item") or {}
        if event.get("type") == "item.completed" and item.get("type") == "agent_message":
            text = item.get("text", "")
    return thread, text


def codex_model(thread):
    """The model Codex recorded for the thread's turns, from its own session rollout."""
    if not thread:
        return None
    home = os.environ.get("CODEX_HOME") or os.path.join(os.path.expanduser("~"), ".codex")
    files = glob.glob(os.path.join(home, "sessions", "**", f"rollout-*{thread}.jsonl"), recursive=True)
    models = set()
    for path in files:
        with open(path, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                if '"turn_context"' in line or '"model"' in line:
                    models.update(re.findall(r'"model":"([^"]+)"', line))
    return sorted(models)[0] if len(models) == 1 else (",".join(sorted(models)) or None)


def claude_reply(stdout):
    try:
        data = json.loads(stdout)
    except ValueError:
        return None, ""
    if not isinstance(data, dict):
        return None, ""
    usage = data.get("modelUsage") or {}
    answered = [m for m, u in usage.items() if (u or {}).get("outputTokens", 1)]
    return answered or None, data.get("result", "")


# ------------------------------------------------------------------ signing

def _canonical(obj):
    return json.dumps(obj, sort_keys=True, separators=(",", ":")).encode()


def runner_key():
    path = os.environ.get("JUDGE_RUNNER_KEY")
    return bytes.fromhex(Path(path).read_text(encoding="ascii").strip()) if path else None


def sign(obj, key):
    return hmac.new(key, _canonical({k: v for k, v in obj.items() if k != "mac"}), hashlib.sha256).hexdigest()


def signed(obj, key):
    """True when `obj` carries a valid runner signature."""
    return bool(key) and isinstance(obj.get("mac"), str) and hmac.compare_digest(obj["mac"], sign(obj, key))


# ------------------------------------------------------------------ the runner

def counted(record, cfg=None):
    """The rule: an allowlisted judge, and the CLI recorded a model that judge accepts."""
    try:
        entry = allowlist(cfg).get(record.get("judge"))
    except JudgeRefused:
        return False
    return bool(entry) and record.get("exit") == 0 and accepted(entry, record.get("answering_model"))


def verify_record(record, key, cfg=None):
    """A record read back from disk or a commit: signed by a runner holding `key`, and counted."""
    return signed(record, key) and counted(record, cfg)


def judge_call(judge_id, prompt, cfg=None, runners=None, runner=subprocess.run, log_dir=None, timeout=None):
    """Run allowlisted `judge_id` on `prompt`. Raises JudgeRefused for anything not on the list."""
    cfg = cfg or config()
    entry = judge(judge_id, cfg)
    command = command_for(entry, runners)
    timeout = timeout or cfg.get("timeout_s", 420)
    started = time.time()
    code, stdout, error = None, "", None
    with tempfile.TemporaryDirectory(prefix="judge-") as work:
        prompt_file = Path(work) / "prompt.txt"
        prompt_file.write_text(prompt, encoding="utf-8")
        argv = [part.replace("{workdir}", work).replace("{prompt_file}", str(prompt_file)) for part in command]
        argv[0] = shutil.which(argv[0]) or argv[0]  # npm shims are codex.cmd on Windows
        try:
            proc = runner(argv, input=prompt if entry.get("stdin", True) else None, capture_output=True,
                          text=True, encoding="utf-8", errors="replace", timeout=timeout, cwd=work)
            code, stdout = proc.returncode, proc.stdout or ""
            if code:
                error = f"exit {code}: {(proc.stderr or '')[-300:]}"
        except (OSError, subprocess.TimeoutExpired) as exc:
            code = 124 if isinstance(exc, subprocess.TimeoutExpired) else 127
            error = f"{type(exc).__name__}: {exc}"[:300]
    if entry["reply"] == "codex-json":
        thread, reply = codex_reply(stdout)
    else:
        thread, reply = None, claude_reply(stdout)[1]
    if entry["answer_model"] == "codex-rollout":
        answered = codex_model(thread)
    else:
        answered = claude_reply(stdout)[0]
    claims = sorted({m.lower() for m in CLAIM.findall(reply)})
    record = dict(id=uuid.uuid4().hex, judge=entry["id"], family=entry["family"],
                  answering_model=",".join(answered) if isinstance(answered, list) else answered,
                  command_sha256=hashlib.sha256(_canonical(command)).hexdigest(),
                  prompt_sha256=hashlib.sha256(prompt.encode()).hexdigest(),
                  reply_sha256=hashlib.sha256(reply.encode()).hexdigest(), exit=code, error=error,
                  started=round(started, 3), seconds=round(time.time() - started, 2),
                  host=socket.gethostname(), claimed_model=claims or None)
    record["counted"] = counted(record, cfg)
    key = runner_key()
    if key:
        record["mac"] = sign(record, key)
    log = Path(log_dir or os.environ.get("JUDGE_LOG_DIR") or ROOT / "build" / "judges")
    log.mkdir(parents=True, exist_ok=True)
    with (log / "calls.jsonl").open("a", encoding="utf-8") as handle:
        handle.write(json.dumps(dict(record, reply=reply)) + "\n")
    return JudgeResult(record, reply)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    sub.add_parser("list")
    sub.add_parser("call").add_argument("judge")
    args = ap.parse_args(argv)
    try:
        if args.action == "list":
            for j in config()["judges"]:
                print(f"{j['id']:18} family={j['family']:9} rank={j['rank']} accept={','.join(j['accept'])}")
            return 0
        result = judge_call(args.judge, sys.stdin.read())
    except JudgeRefused as error:
        print(f"judges: {error}", file=sys.stderr)
        return 2
    print(result.reply)
    print(json.dumps(result.record), file=sys.stderr)
    return 0 if result.counted else 1


if __name__ == "__main__":
    sys.exit(main())
