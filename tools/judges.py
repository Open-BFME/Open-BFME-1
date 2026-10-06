#!/usr/bin/env python3
"""Allowlisted LLM judges, called by the runner itself.

WHY. An LLM verdict (an audit finding, a vote in the naming lane) is only
worth something if we know which model produced it. A `model=` field written
by the worker that ran the model is whatever that worker wanted it to be. So
a verdict counts only when THIS runner invoked the model: the model id in the
record is the allowlist key the runner called, never a value read from the
answer or from the caller's metadata (decision record, pillar 5).

ALLOWLIST. tools/judges.json (a protected path: changing it needs a
`Verifier-Change:` trailer) lists the judge models, their family and the
command that runs each one with the prompt on stdin. A host may override the
COMMAND of a listed model (JUDGE_RUNNERS=<json file>: {model: {"command":
[...]}}) because CLIs differ per host; it can never add a model.

RECORD. Every call appends to <log_dir>/calls.jsonl: the model invoked, its
family, sha256 of the argv, prompt and answer, exit code, timing, host, any
model name the answer claims (`claimed_model`, audit only) and whether that
claim disagrees. With JUDGE_RUNNER_KEY=<key file> (readable by the runner
host only) the record is HMAC-signed; verify_record() is how other tools
accept a verdict.

  from judges import judge_call
  result = judge_call("gpt-6.1-sol", prompt)      # result.model, result.output, result.record
  python3 tools/judges.py list
  python3 tools/judges.py call MODEL < prompt.txt
"""
import argparse
import hashlib
import hmac
import json
import os
import re
import socket
import subprocess
import sys
import time
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
JUDGES = Path(__file__).resolve().with_name("judges.json")
CLAIM = re.compile(r"\bmodel\s*[=:]\s*[\"']?([A-Za-z0-9][A-Za-z0-9._:-]*)", re.IGNORECASE)


class JudgeRefused(RuntimeError):
    """The model is not an allowlisted judge, or has no runnable command."""


class JudgeResult:
    def __init__(self, model, output, record):
        self.model, self.output, self.record = model, output, record


def allowlist(path=JUDGES):
    return json.loads(Path(path).read_text(encoding="utf-8"))["judges"]


def _canonical(obj):
    return json.dumps(obj, sort_keys=True, separators=(",", ":")).encode()


def sign_record(record, key):
    body = {k: v for k, v in record.items() if k != "mac"}
    return hmac.new(key, _canonical(body), hashlib.sha256).hexdigest()


def verify_record(record, key, path=JUDGES):
    """True for a record this runner signed, naming an allowlisted model."""
    return (bool(record.get("mac")) and record.get("model") in allowlist(path)
            and hmac.compare_digest(record["mac"], sign_record(record, key)))


def _key():
    path = os.environ.get("JUDGE_RUNNER_KEY")
    return bytes.fromhex(Path(path).read_text(encoding="ascii").strip()) if path else None


def command_for(model, path=JUDGES, runners=None):
    judges = allowlist(path)
    if model not in judges:
        raise JudgeRefused(f"{model!r} is not an allowlisted judge ({', '.join(sorted(judges))})")
    runners = runners if runners is not None else (
        json.loads(Path(os.environ["JUDGE_RUNNERS"]).read_text(encoding="utf-8"))
        if os.environ.get("JUDGE_RUNNERS") else {})
    command = (runners.get(model) or {}).get("command") or judges[model].get("command")
    if not command:
        raise JudgeRefused(f"no command configured for judge {model!r}")
    return judges[model], list(command)


def judge_call(model, prompt, path=JUDGES, runners=None, log_dir=None, timeout=1800):
    """Run allowlisted `model` on `prompt`; the record names the model this
    runner invoked, whatever the answer says about itself."""
    entry, command = command_for(model, path, runners)
    started = time.time()
    try:
        got = subprocess.run(command, input=prompt.encode(), capture_output=True, timeout=timeout)
        code, output = got.returncode, got.stdout.decode(errors="replace")
    except (OSError, subprocess.TimeoutExpired) as error:
        code, output = 127 if isinstance(error, OSError) else 124, ""
    claims = sorted({m.lower() for m in CLAIM.findall(output)})
    record = dict(id=uuid.uuid4().hex, model=model, family=entry.get("family"),
                  command_sha256=hashlib.sha256(_canonical(command)).hexdigest(),
                  prompt_sha256=hashlib.sha256(prompt.encode()).hexdigest(),
                  output_sha256=hashlib.sha256(output.encode()).hexdigest(), exit=code,
                  started=started, seconds=round(time.time() - started, 2),
                  host=socket.gethostname(), claimed_model=claims or None,
                  claim_disagrees=bool(claims) and claims != [model.lower()])
    key = _key()
    if key:
        record["mac"] = sign_record(record, key)
    log = Path(log_dir) if log_dir else ROOT / "build" / "judges"
    log.mkdir(parents=True, exist_ok=True)
    with (log / "calls.jsonl").open("a", encoding="utf-8") as handle:
        handle.write(json.dumps(dict(record, output=output)) + "\n")
    return JudgeResult(model, output, record)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    sub.add_parser("list")
    call = sub.add_parser("call")
    call.add_argument("model")
    args = ap.parse_args(argv)
    if args.action == "list":
        for model, entry in sorted(allowlist().items()):
            print(f"{model}\t{entry.get('family')}\t{' '.join(entry.get('command') or [])}")
        return 0
    try:
        result = judge_call(args.model, sys.stdin.read())
    except JudgeRefused as error:
        print(f"judges: {error}", file=sys.stderr)
        return 2
    print(result.output)
    print(json.dumps(result.record), file=sys.stderr)
    return 0 if result.record["exit"] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
