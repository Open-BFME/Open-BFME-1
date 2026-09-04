#!/usr/bin/env python3
"""Run one worker with an immutable brief, transcript and actual exit status.

The caller supplies a bounded command (seat.sh uses timeout). Runs share an
atomic RVA claim table across lanes. Claims never expire silently: after a
supervisor crash an operator must establish the worker stopped, then release
the named run with --release RUN --reason TEXT. Existing legacy workers do not
participate; deploy at a fleet restart, not by overwriting a running script.
"""
import argparse
import csv
import datetime
import hashlib
import json
import os
from pathlib import Path
import re
import sqlite3
import subprocess
import sys
import time
import uuid

ROOT = Path(__file__).resolve().parents[1]
TARGET = re.compile(r"^- (0x[0-9a-fA-F]+) (\d+)B", re.M)
DIFF = re.compile(r"^(diff --git |index [0-9a-f]+\.\.|\+\+\+ |--- |@@ |[-+])")


def connect(root):
    (root / "build").mkdir(exist_ok=True)
    db = sqlite3.connect(root / "build/fleet_runs.sqlite", timeout=60)
    db.execute("CREATE TABLE IF NOT EXISTS claims (rva TEXT PRIMARY KEY, run TEXT, started REAL)")
    db.execute("CREATE TABLE IF NOT EXISTS releases (run TEXT, at REAL, reason TEXT)")
    return db


def claim(root, run, targets):
    with connect(root) as db:
        db.execute("BEGIN IMMEDIATE")
        for rva, _ in targets:
            owner = db.execute("SELECT run FROM claims WHERE rva=?", (rva,)).fetchone()
            if owner:
                raise RuntimeError(f"{rva} is already owned by run {owner[0]}")
            db.execute("INSERT INTO claims VALUES (?,?,?)", (rva, run, time.time()))


def active_rvas(root):
    with connect(root) as db:
        return {row[0] for row in db.execute("SELECT rva FROM claims")}


def run_tag(text):
    """Attach provenance without letting an environment value corrupt a ledger."""
    run = os.environ.get("BFME_RUN_ID", "")
    if run and re.fullmatch(r"[A-Za-z0-9_-]{1,80}", run):
        text = re.sub(r"(?:^|\s)run=\S+", "", text).strip()
        return (text + " run=" + run).strip()
    return text


def stash_fingerprint(rva):
    import re_log
    stash = re_log.stash_for(rva)
    if not stash:
        return "none"
    # A higher self-reported score or a new date is not a new source hypothesis.
    body = b"\n".join(stash[0].read_bytes().splitlines()[2:])
    return hashlib.sha256(body).hexdigest()


def retry_allowed(root, rva, before):
    import re_log
    current = stash_fingerprint(rva)
    record = re_log.latest_records(root / "reverse/re_attempts.log").get(rva)
    stash = re_log.stash_for(rva)
    if current in ("none", before) or not record or record[3] != "partial" or stash[1] < .5:
        return False
    with (root / "reverse/functions.csv").open(newline="", encoding="utf-8") as ledger:
        return any(int(row["target_rva"], 16) == rva and row["source"].endswith(".asm")
                   for row in csv.DictReader(ledger) if row.get("target_rva"))


def release(root, run, reason):
    with connect(root) as db:
        db.execute("DELETE FROM claims WHERE run=?", (run,))
        db.execute("INSERT INTO releases VALUES (?,?,?)", (run, time.time(), reason))


def save(path, data):
    tmp = path.with_suffix(".tmp")
    tmp.write_text(json.dumps(data, indent=2), encoding="utf-8")
    os.replace(tmp, path)


def execute(root, brief, legacy_log, engine, seat, command):
    body = Path(brief).read_bytes()
    targets = [(r.lower(), int(n)) for r, n in TARGET.findall(body.decode("utf-8-sig"))]
    if not targets or len({r for r, _ in targets}) != len(targets):
        raise ValueError("brief must contain unique live TARGETS lines")
    run = datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%dT%H%M%SZ-") + uuid.uuid4().hex[:12]
    directory = root / "build/fleet_runs" / run
    directory.mkdir(parents=True)
    (directory / "brief.txt").write_bytes(body)
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=root, capture_output=True, text=True)
    record = dict(id=run, engine=engine, seat=seat, source_head=head.stdout.strip(),
                  brief_sha256=hashlib.sha256(body).hexdigest(), targets=targets,
                  start=time.time(), status="starting", legacy_log=str(legacy_log),
                  usage=None, usage_note="No token or cost attribution from plain-text output")
    save(directory / "record.json", record)
    claimed = False
    child = None
    try:
        claim(root, run, targets)
        claimed = True
        record["status"] = "running"
        save(directory / "record.json", record)
        # The compatibility path becomes a pointer; preserve any old transcript.
        pointer = Path(legacy_log)
        pointer.parent.mkdir(parents=True, exist_ok=True)
        if pointer.exists():
            pointer.rename(pointer.with_name(pointer.name + ".before-" + run))
        pointer.write_text(f"run={run}\n{directory / 'output.log'}\n", encoding="utf-8")
        print(f"fleet run {run}: {directory}", flush=True)
        with (directory / "output.log").open("w", encoding="utf-8") as log:
            child = subprocess.Popen(command, cwd=root, env=dict(os.environ, BFME_RUN_ID=run),
                                     stdin=subprocess.DEVNULL, stdout=subprocess.PIPE,
                                     stderr=subprocess.STDOUT)
            record["pid"] = child.pid
            save(directory / "record.json", record)
            # Bound memory even if a tool emits a multi-megabyte single line.
            while chunk := child.stdout.readline(65536):
                line = chunk.decode("utf-8", errors="replace")
                if not DIFF.match(line):
                    log.write(line.rstrip("\r\n")[:400] + "\n")
                    log.flush()
            code = child.wait()
        record.update(status="finished", exit_code=code)
        return code
    except BaseException as error:
        record.update(status="interrupted" if child and child.poll() is None else "failed",
                      error=str(error))
        raise
    finally:
        record.update(end=time.time())
        record["seconds"] = record["end"] - record["start"]
        save(directory / "record.json", record)
        # A detached surviving child still owns its bodies. Do not time it out
        # of the registry and hand them to another worker.
        if claimed and (child is None or child.poll() is not None):
            release(root, run, "worker exited")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--brief", type=Path)
    ap.add_argument("--log", type=Path)
    ap.add_argument("--engine", default="manual")
    ap.add_argument("--seat", default="manual")
    ap.add_argument("--release")
    ap.add_argument("--reason")
    ap.add_argument("--fingerprint", type=lambda s: int(s, 16))
    ap.add_argument("--can-retry", type=lambda s: int(s, 16))
    ap.add_argument("--before")
    ap.add_argument("command", nargs=argparse.REMAINDER)
    a = ap.parse_args()
    if a.fingerprint is not None:
        print(stash_fingerprint(a.fingerprint))
        return
    if a.can_retry is not None:
        if not a.before:
            ap.error("--can-retry requires --before fingerprint")
        sys.exit(0 if retry_allowed(ROOT, a.can_retry, a.before) else 1)
    if a.release:
        if not a.reason:
            ap.error("--release requires --reason after verifying the worker has stopped")
        release(ROOT, a.release, a.reason)
        return
    command = a.command[1:] if a.command[:1] == ["--"] else a.command
    if not a.brief or not a.log or not command:
        ap.error("--brief, --log and a bounded command after -- are required")
    sys.exit(execute(ROOT, a.brief, a.log, a.engine, a.seat, command))


if __name__ == "__main__":
    main()
