#!/usr/bin/env python3
"""Inspect old seats.log ghosts; cut over only after every old seat has stopped.

Dry-run by default. --apply requires --stopped-fleet and the exact SHA printed
by a dry run. This tool never changes a run claim or a worker record.
"""
import argparse
from contextlib import closing
import hashlib
import json
import os
from pathlib import Path
import sqlite3
import sys
import time
import uuid

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eligibility  # noqa: E402
from portable_lock import lock  # noqa: E402


def snapshot(root):
    build = root / "build"
    log_path = build / "fleet_logs/seats.log"
    marker = build / "fleet_legacy_cutover.json"
    raw = log_path.read_bytes() if log_path.exists() else b""
    db_path = build / "fleet_runs.sqlite"
    claim_count = 0
    if db_path.exists():
        try:
            with closing(sqlite3.connect(f"file:{db_path}?mode=ro", uri=True)) as db:
                claim_count = db.execute("SELECT count(*) FROM claims").fetchone()[0]
        except sqlite3.Error as error:
            raise RuntimeError(f"cannot establish run-claim state: {error}") from error
    return dict(log_sha256=hashlib.sha256(raw).hexdigest(),
                outstanding=sorted(eligibility.legacy_busy_tokens(root, log_path)),
                claim_count=claim_count, cutover_marker=marker.exists())


def reconcile(root, apply=False, stopped_fleet=False, expected_sha=None):
    root = Path(root)
    build = root / "build"
    log_path = build / "fleet_logs/seats.log"
    marker = build / "fleet_legacy_cutover.json"
    if not apply:
        return snapshot(root)
    build.mkdir(exist_ok=True)
    with (build / ".fleet_claims.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        report = snapshot(root)
        before_sha = report["log_sha256"]
        outstanding = report["outstanding"]
        claim_count = report["claim_count"]
        if not stopped_fleet or not expected_sha:
            raise ValueError("apply requires --stopped-fleet and --log-sha from a dry run")
        if before_sha != expected_sha:
            raise ValueError("seats.log changed since dry run; inspect and retry")
        if claim_count:
            raise RuntimeError("run claims remain; establish worker liveness before cutover")
        if marker.exists():
            if outstanding:
                raise RuntimeError("old-style assignments appeared after cutover; stop that controller")
            return report  # already cut over, with no new legacy assignments
        log_path.parent.mkdir(parents=True, exist_ok=True)
        with log_path.open("ab") as stream:
            for token in outstanding:
                stream.write(f"{time.strftime('%H:%M')} seat reconciliation done {token}\n".encode())
            stream.flush()
            os.fsync(stream.fileno())
        closed = log_path.read_bytes()
        data = dict(closed_log_bytes=len(closed),
                    closed_log_sha256=hashlib.sha256(closed).hexdigest(),
                    applied_at=time.time(), outstanding_closed=outstanding)
        temporary = marker.with_name(marker.name + "." + uuid.uuid4().hex + ".tmp")
        temporary.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
        os.replace(temporary, marker)
        report["applied"] = True
        return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--stopped-fleet", action="store_true")
    parser.add_argument("--log-sha")
    args = parser.parse_args()
    print(json.dumps(reconcile(Path.cwd(), args.apply, args.stopped_fleet, args.log_sha), indent=2))


if __name__ == "__main__":
    main()
