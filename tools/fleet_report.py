#!/usr/bin/env python3
"""Report immutable runs and published ledger-attributed bytes; freeze a trial set.

--ref defaults to origin/master (local ref; fetch first for current results).
No transcript byte count is treated as token usage, cost, or a fresh byte gate.
--freeze N copies a deterministic, size-stratified set of partials to build/.
"""
import argparse
import csv
import hashlib
import io
import json
from pathlib import Path
import re
import subprocess
import uuid

import build
import re_log


def published(rows):
    by_run = {}
    for row in rows:
        source = row.get("source", "")
        run = re.search(r"(?:^|\s)run=([A-Za-z0-9_-]+)(?:\s|$)", row.get("notes", ""))
        if (not run or row.get("status") != "matched" or source.startswith("Code/gen_")
                or not source.startswith("Code/") or not source.endswith((".cpp", ".c"))):
            continue
        start, size = int(row["target_rva"], 16), int(row["target_size"])
        by_run.setdefault(run[1], []).append((start, start + size))
    result = {}
    for run, spans in by_run.items():
        total, end = 0, -1
        for lo, hi in sorted(spans):
            total += max(0, hi - max(lo, end))
            end = max(end, hi)
        result[run] = total
    return result


def freeze(count):
    if count < 1:
        raise ValueError("freeze count must be positive")
    buckets = {"small": [], "mid": [], "large": []}
    latest = re_log.latest_records()
    with build.FUNCTIONS.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if not row.get("source", "").endswith(".asm"):
                continue
            rva, size = int(row["target_rva"], 16), int(row["target_size"])
            stash = re_log.stash_for(rva)
            if not stash:
                continue
            bucket = "small" if size < 300 else "mid" if size < 1000 else "large"
            buckets[bucket].append((rva, size, stash, latest.get(rva)))
    for bucket in buckets.values():
        bucket.sort(key=lambda item: hashlib.sha256(str(item[0]).encode()).digest())
    directory = build.ROOT / "build/evaluation_sets" / uuid.uuid4().hex
    directory.mkdir(parents=True)
    examples = []
    while len(examples) < count and any(buckets.values()):
        for bucket in buckets.values():
            if not bucket or len(examples) >= count:
                continue
            rva, size, (path, score), attempt = bucket.pop()
            body = path.read_bytes()
            name = f"0x{rva:08x}.cpp"
            (directory / name).write_bytes(body)
            examples.append(dict(rva=f"0x{rva:08x}", size=size, source=name, author_score=score,
                                 sha256=hashlib.sha256(body).hexdigest(), attempt=attempt))
    manifest = dict(exe_sha256=hashlib.sha256(build.EXE.read_bytes()).hexdigest(),
                    acceptance="none; frozen starting candidates", examples=examples)
    (directory / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    return directory, len(examples)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--ref", default="origin/master")
    ap.add_argument("--freeze", type=int)
    a = ap.parse_args()
    if a.freeze is not None:
        path, count = freeze(a.freeze)
        print(f"Froze {count} starting bodies at {path}")
        return
    revision = subprocess.check_output(["git", "rev-parse", "--verify", a.ref + "^{commit}"],
                                       cwd=build.ROOT, text=True).strip()
    ledger = subprocess.check_output(["git", "show", revision + ":reverse/functions.csv"],
                                    cwd=build.ROOT).decode("utf-8")
    accepted = published(csv.DictReader(io.StringIO(ledger)))
    runs = []
    for path in sorted((build.ROOT / "build/fleet_runs").glob("*/record.json")):
        record = json.loads(path.read_text(encoding="utf-8"))
        runs.append({key: record.get(key) for key in ("id", "engine", "seat", "status", "seconds", "exit_code", "usage")})
        runs[-1]["published_ledger_bytes"] = accepted.get(record["id"], 0)
    blockers = {}
    for rva, fields in re_log.latest_records().items():
        for blocker in re.findall(r"(?:^|\s)blocker=([^\s]+)", fields[4]):
            blockers.setdefault(blocker, set()).add(f"0x{rva:08x}")
    print(json.dumps(dict(ref=revision, metric="published ledger attribution; not a fresh byte verification or compute cost",
                          runs=runs, blockers={k: sorted(v) for k, v in sorted(blockers.items(), key=lambda kv: -len(kv[1]))}), indent=2))


if __name__ == "__main__":
    main()
