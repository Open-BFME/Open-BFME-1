#!/usr/bin/env python3
"""Claim an editor source family and retain a WorldBuilder worker run.

Claims are shared across Git worktrees. SIGKILL retains the claim: stop the
recorded worker process group, then explicitly release it from its worktree.
"""
import argparse
from contextlib import contextmanager
import datetime
import json
import os
from pathlib import Path
import re
import shutil
import signal
import sqlite3
import subprocess
import sys
import time
import uuid

from targets import load_target


def now():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def run_path(target, run_id):
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_.-]{0,95}", run_id):
        raise ValueError("run ID must be 1–96 letters, numbers, dots, hyphens or underscores")
    return target.build_root / "fleet" / "runs" / run_id


def require_target_environment(target):
    if os.environ.get("BFME_TARGET", target.target_id) != target.target_id:
        raise ValueError("BFME_TARGET disagrees with the explicit WorldBuilder command")
    if os.environ.get("BFME_TARGET_SHA256", target.expected_sha256) != target.expected_sha256:
        raise ValueError("BFME_TARGET_SHA256 disagrees with the WorldBuilder image; packet is stale")


def database(target):
    require_target_environment(target)
    common = subprocess.check_output(["git", "rev-parse", "--git-common-dir"],
                                     cwd=target.root, text=True).strip()
    path = (target.root / common).resolve() / "fleet" / target.target_id / "claims.sqlite"
    path.parent.mkdir(parents=True, exist_ok=True)
    db = sqlite3.connect(path, timeout=30)
    db.execute("CREATE TABLE IF NOT EXISTS claims (source TEXT PRIMARY KEY, "
               "run_id TEXT UNIQUE NOT NULL, binary_sha256 TEXT NOT NULL, "
               "packet_sha256 TEXT NOT NULL, started TEXT NOT NULL, "
               "worktree TEXT NOT NULL, run_directory TEXT NOT NULL)")
    return db


def claim(target, candidate_id, run_id, expected_packet=None):
    from worldbuilder import open_candidates
    require_target_environment(target)
    target.verify_hash()
    candidates = open_candidates(target)
    selected = [p for p in candidates if p["id"] == candidate_id]
    if len(selected) != 1:
        raise ValueError(f"candidate {candidate_id!r} is absent, already landed or ambiguous")
    packet = selected[0]
    source = packet["source"]
    if not source.startswith(("worldbuilder/", "worldbuilder/")):
        raise ValueError("pilot workers may edit only WorldBuilder-exclusive sources; shared engine donors are read-only")
    if ".." in Path(source).parts or Path(source).is_absolute():
        raise ValueError(f"invalid source ownership path: {source}")
    digest = packet["packet_sha256"]
    if expected_packet is not None and digest != expected_packet:
        raise ValueError("stale packet: candidate evidence changed before claim")
    directory = run_path(target, run_id)
    db = database(target)
    try:
        db.execute("BEGIN IMMEDIATE")
        db.execute("INSERT INTO claims VALUES (?,?,?,?,?,?,?)",
                   (source, run_id, target.expected_sha256, digest, now(),
                    str(target.root.resolve()), str(directory.resolve())))
        directory.mkdir(parents=True, exist_ok=False)
        brief = {"target": target.target_id, "binary_sha256": target.expected_sha256,
                 "run_id": run_id, "source": source, "packet_sha256": digest,
                 "started": now(), "model": os.environ.get("BFME_MODEL"),
                 "git_head": subprocess.check_output(["git", "rev-parse", "HEAD"],
                                                     cwd=target.root, text=True).strip(),
                 "candidates": [p for p in candidates if p["source"] == source]}
        (directory / "brief.json").write_text(json.dumps(brief, indent=2) + "\n")
        db.commit()
        return brief
    except BaseException:
        db.rollback()
        raise
    finally:
        db.close()


def release(target, run_id, reason):
    require_target_environment(target)
    directory = run_path(target, run_id)
    if not reason.strip():
        raise ValueError("release needs a reason establishing that the worker stopped")
    with database(target) as db:
        db.execute("BEGIN IMMEDIATE")
        row = db.execute("SELECT binary_sha256,worktree,run_directory FROM claims WHERE run_id=?",
                         (run_id,)).fetchone()
        if row is None:
            raise ValueError(f"no active claim for {run_id}")
        if row[0] != target.expected_sha256:
            raise ValueError("claim belongs to another binary hash")
        if row[1] != str(target.root.resolve()) or row[2] != str(directory.resolve()):
            raise ValueError(f"claim belongs to worktree {row[1]}; release it from that worktree")
        (directory / "release.json").write_text(json.dumps({"released": now(), "reason": reason}, indent=2) + "\n")
        db.execute("DELETE FROM claims WHERE run_id=?", (run_id,))


class WorkerInterrupted(Exception):
    def __init__(self, signum):
        self.signum = signum
        super().__init__(f"received signal {signum}")


@contextmanager
def worker_signals():
    def interrupted(signum, _frame):
        raise WorkerInterrupted(signum)
    previous = {sig: signal.signal(sig, interrupted) for sig in (signal.SIGINT, signal.SIGTERM)}
    try:
        yield
    finally:
        for sig, handler in previous.items():
            signal.signal(sig, handler)


def group_running(pgid):
    output = subprocess.check_output(["ps", "-A", "-o", "pgid=,stat="], text=True)
    return any(int(group) == pgid and not status.startswith("Z")
               for group, status in (line.split() for line in output.splitlines() if line.strip()))


def stop_worker_group(process):
    # Reaping only the launcher can leave its compiler or agent children editing leased files.
    for sig in (signal.SIGTERM, signal.SIGKILL):
        try:
            os.killpg(process.pid, sig)
        except ProcessLookupError:
            process.wait()
            return
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline:
            process.poll()
            if not group_running(process.pid):
                process.wait()
                return
            time.sleep(0.05)
    raise ValueError(f"worker process group {process.pid} is still alive; claim retained")


def run(target, candidate_id, run_id, command, expected_packet=None):
    require_target_environment(target)
    if not command:
        raise ValueError("run needs a worker command after --")
    if os.name != "posix" or sys.platform == "win32":
        raise ValueError("run requires POSIX process groups; use claim/release with an externally supervised worker on Windows")
    if shutil.which("ps") is None:
        raise ValueError("run requires ps to verify that the worker process group stopped")
    with worker_signals():
        return run_claimed(target, candidate_id, run_id, command, expected_packet)


def run_claimed(target, candidate_id, run_id, command, expected_packet):
    claim(target, candidate_id, run_id, expected_packet)
    directory = run_path(target, run_id)
    env = os.environ.copy()
    env.update(BFME_TARGET=target.target_id, BFME_TARGET_SHA256=target.expected_sha256,
               BFME_RUN_ID=run_id, BFME_WORK_PACKET=str(directory / "brief.json"))
    result = {"command": command, "started": now(), "target": target.target_id,
              "binary_sha256": target.expected_sha256, "run_id": run_id}
    process = None
    try:
        with (directory / "worker.log").open("wb") as output:
            process = subprocess.Popen(command, cwd=target.root, env=env,
                                       stdout=output, stderr=subprocess.STDOUT, start_new_session=True)
            result["pid"] = process.pid
            (directory / "process.json").write_text(json.dumps(result, indent=2) + "\n")
            result["exit_code"] = process.wait()
    except BaseException as exc:
        result["error"] = f"{type(exc).__name__}: {exc}"
        raise
    finally:
        stopped = False
        try:
            if process is not None:
                stop_worker_group(process)
                result["exit_code"] = process.returncode
            stopped = True
        except BaseException as exc:
            result["cleanup_error"] = f"{type(exc).__name__}: {exc}"
            raise
        finally:
            result["finished"] = now()
            (directory / "result.json").write_text(json.dumps(result, indent=2) + "\n")
            if stopped:
                release(target, run_id, "worker process group stopped or worker failed to start")
    return result


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    command = []
    if argv[:1] == ["run"] and "--" in argv:
        separator = argv.index("--")
        command, argv = argv[separator + 1:], argv[:separator]
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="operation", required=True)
    for name in ("claim", "run"):
        p = sub.add_parser(name)
        p.add_argument("candidate")
        p.add_argument("--run-id", default=None)
        p.add_argument("--packet-sha256")
    p = sub.add_parser("release")
    p.add_argument("run_id")
    p.add_argument("--reason", required=True)
    sub.add_parser("claims")
    args = parser.parse_args(argv)
    try:
        target = load_target("worldbuilder")
        require_target_environment(target)
        if args.operation == "release":
            release(target, args.run_id, args.reason)
            print(f"{target.target_id}: released {args.run_id}")
        elif args.operation == "claims":
            with database(target) as db:
                print(json.dumps([dict(zip(("source", "run_id", "binary_sha256", "packet_sha256", "started", "worktree", "run_directory"), row))
                                  for row in db.execute("SELECT * FROM claims ORDER BY started")], indent=2))
        else:
            run_id = args.run_id or uuid.uuid4().hex
            if args.operation == "claim":
                print(json.dumps(claim(target, args.candidate, run_id, args.packet_sha256), indent=2))
            else:
                result = run(target, args.candidate, run_id, command, args.packet_sha256)
                print(json.dumps(result, indent=2))
                return result["exit_code"]
    except WorkerInterrupted as exc:
        parser.exit(128 + exc.signum, f"WorldBuilder fleet: {exc}\n")
    except (ValueError, OSError, sqlite3.Error, subprocess.CalledProcessError) as exc:
        parser.exit(1, f"WorldBuilder fleet: {exc}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
