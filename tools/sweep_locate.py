#!/usr/bin/env python3
"""Batch-run tools/locate.py --emit over many tracked sources, safely.

Ad-hoc shell loops around locate.py died overnight when a wrapping tool call
timed out: locate --emit appends ledger rows even when the wrapper is killed,
so runs ended mid-sweep with unrecorded progress and uncommitted appends. This
tool owns the loop instead: per-file subprocess timeouts (the sweep survives a
stuck compile), progress recorded in a state file after every file, and a
resume mode that skips work already done at the current commit.

State: reverse/zh_sweep/locate_state.json (gitignored)
  {"ref": <HEAD sha of last run>, "done": {path: {"emitted": n, "ts_ref": sha}}}
Entries are only trusted at the sha they were made at — locate results depend
on the ledger, so a new commit invalidates them (--resume re-scans).

Usage:
  python3 tools/sweep_locate.py [--src-glob 'src/**/*.cpp'] [--min-size N]
                                [--limit N] [--resume] [--timeout SECONDS]
"""
import argparse
import concurrent.futures
import json
import os
import re
import subprocess
import sys
from pathlib import Path

# sweeps run under wrappers that die/kill (that is why this tool exists);
# line-buffer stdout so progress printed so far survives a SIGKILL instead of
# vanishing in a full block buffer
sys.stdout.reconfigure(line_buffering=True)

ROOT = Path(__file__).resolve().parents[1]
STATE_PATH = ROOT / "reverse" / "zh_sweep" / "locate_state.json"
LOCATE = ROOT / "tools" / "locate.py"
EMIT_RE = re.compile(r"emitted (\d+) row\(s\) to functions\.csv")


def fail(*lines):
    for line in lines:
        print(f"sweep_locate: {line}", file=sys.stderr)
    raise SystemExit(1)


def git(*argv):
    out = subprocess.run(["git", "-C", str(ROOT), *argv], capture_output=True, text=True)
    if out.returncode != 0:
        fail(f"git {' '.join(argv)} failed: {out.stderr.strip()}")
    return out.stdout


def load_state():
    if not STATE_PATH.exists():
        return {"ref": None, "done": {}}
    try:
        state = json.loads(STATE_PATH.read_text(encoding="utf-8"))
        if not isinstance(state.get("done"), dict):
            raise ValueError("missing 'done' dict")
    except (json.JSONDecodeError, ValueError) as exc:
        fail(f"{STATE_PATH} is corrupt ({exc}) — a sweep died mid-write? "
             "Inspect it, then delete it to start fresh (resume data only, no ledger rows)")
    return state


def save_state(state):
    # written after EVERY file so a killed sweep loses at most the in-flight file
    tmp = STATE_PATH.with_suffix(".json.tmp")
    tmp.write_text(json.dumps(state, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, STATE_PATH)


def run_locate(path, min_size, timeout):
    command = [sys.executable, str(LOCATE), path, "--emit"]
    if min_size is not None:
        command += ["--min-size", str(min_size)]
    try:
        proc = subprocess.run(command, cwd=ROOT, capture_output=True, text=True,
                              timeout=timeout)
    except subprocess.TimeoutExpired:
        return "timeout", None, None
    output = proc.stdout + proc.stderr
    if proc.returncode != 0:
        return "error", None, output
    match = EMIT_RE.search(output)
    return "ok", int(match.group(1)) if match else 0, output


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--src-glob", default="src/**/*.cpp",
                        help="git pathspec selecting tracked sources (default: src/**/*.cpp)")
    parser.add_argument("--min-size", type=int, default=None,
                        help="forwarded to locate.py --min-size")
    parser.add_argument("--limit", type=int, default=None,
                        help="process at most N files this run (after --resume skips)")
    parser.add_argument("--resume", action="store_true",
                        help="skip files already swept at the current HEAD sha")
    parser.add_argument("--timeout", type=float, default=300,
                        help="per-file locate.py timeout in seconds (default 300)")
    args = parser.parse_args()

    sha = git("rev-parse", "HEAD").strip()
    sources = sorted(line for line in git("ls-files", "--", args.src_glob).splitlines() if line)
    if not sources:
        fail(f"--src-glob '{args.src_glob}' matches no tracked sources")

    state = load_state()
    if args.resume and state["ref"] and state["ref"] != sha:
        print(f"sweep_locate: HEAD moved {state['ref'][:12]} -> {sha[:12]}; "
              "stale entries will be re-scanned (locate results depend on the ledger)")
    state["ref"] = sha

    todo, prior_timeouts = [], []
    for path in sources:
        entry = state["done"].get(path)
        if args.resume and entry and entry.get("ts_ref") == sha:
            if entry.get("timeout"):
                prior_timeouts.append(path)
            continue
        todo.append(path)
    skipped = len(sources) - len(todo)
    if prior_timeouts:
        print(f"sweep_locate: {len(prior_timeouts)} file(s) TIMED OUT at this ref and are "
              "being skipped — rerun without --resume or raise --timeout to retry:")
        for path in prior_timeouts:
            print(f"  timeout(previous): {path}")
    if args.limit is not None:
        todo = todo[:args.limit]

    print(f"sweep_locate: {len(sources)} source(s) matched, {skipped} skipped (--resume), "
          f"{len(todo)} to scan, timeout {args.timeout:.0f}s/file, 2 workers")

    emitted_files, timeouts, errors = [], [], []
    total_rows = 0
    scanned = 0
    # 2 workers max: locate compiles under wine and the host is shared — more
    # would oversubscribe it (and raise the odds of interleaved --emit appends)
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
        futures = {pool.submit(run_locate, path, args.min_size, args.timeout): path
                   for path in todo}
        for future in concurrent.futures.as_completed(futures):
            path = futures[future]
            status, rows, output = future.result()
            scanned += 1
            if status == "timeout":
                timeouts.append(path)
                state["done"][path] = {"timeout": True, "ts_ref": sha}
                print(f"  TIMEOUT after {args.timeout:.0f}s: {path} (recorded; continuing)")
            elif status == "error":
                errors.append((path, output))
                print(f"  ERROR: {path} (locate.py failed; not marked done)")
            else:
                state["done"][path] = {"emitted": rows, "ts_ref": sha}
                if rows:
                    total_rows += rows
                    emitted_files.append((path, rows))
                    print(f"  {path}: emitted {rows} row(s)")
            save_state(state)

    print(f"\nsweep_locate: summary @ {sha[:12]}: {scanned} scanned, "
          f"{len(emitted_files)} file(s) emitted {total_rows} row(s), "
          f"{len(timeouts)} timeout(s), {len(errors)} error(s), {skipped} resume-skipped")
    for path in timeouts:
        print(f"  TIMEOUT: {path}")
    for path, output in errors:
        tail = "\n    ".join(output.strip().splitlines()[-4:])
        print(f"  ERROR: {path}\n    {tail}")

    if total_rows:
        # locate --emit already appended these rows — they are in the working
        # tree NOW, whether or not anything else happens. Gate + commit them.
        print(f"\nsweep_locate: {total_rows} row(s) were APPENDED to the ledgers — validating:")
        check = subprocess.run([sys.executable, str(ROOT / "tools" / "check_csv.py")], cwd=ROOT)
        if check.returncode != 0:
            fail("check_csv FAILED — fix the ledgers (tools/dedup_csv.py) before committing")
        print("sweep_locate: now verify and commit: ./build.sh, then commit "
              "reverse/functions.csv + reverse/symbols.csv")
    if errors:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
