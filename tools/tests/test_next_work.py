#!/usr/bin/env python3
"""Tests for tools/next_work.py against the live repo data plus a corrupt-ledger
fixture. Stdlib only, no pytest needed:

    python3 tools/tests/test_next_work.py
"""
import csv
import importlib.util
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "next_work.py"
POOL = 7

SPEC = importlib.util.spec_from_file_location("next_work", TOOL)
NEXT_WORK = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(NEXT_WORK)


def run(args=(), slot=None, pool=None, cwd=ROOT):
    env = {k: v for k, v in os.environ.items() if k not in ("AGENT_SLOT", "AGENT_POOL")}
    if slot is not None:
        env["AGENT_SLOT"] = str(slot)
    if pool is not None:
        env["AGENT_POOL"] = str(pool)
    return subprocess.run(
        [sys.executable, str(cwd / "tools" / "next_work.py"), *args],
        env=env, cwd=cwd, capture_output=True, text=True, timeout=60, check=False)


def get_json(slot=None, pool=None, extra=()):
    proc = run(["--json", *extra], slot=slot, pool=pool)
    assert proc.returncode == 0, f"--json run failed (rc {proc.returncode}):\n{proc.stderr}"
    return json.loads(proc.stdout)  # test 4: must parse


def test_plain_run():
    proc = run()
    assert proc.returncode == 0, f"plain run failed (rc {proc.returncode}):\n{proc.stderr}"
    for needle in ("== 0. ledger health ==", "== 1. drift quick wins",
                   "== 2. structural reconciliation",
                   "== 3. Ghidra-anchored absent functions",
                   "== 4. rest of the ladder ==",
                   "tools/land_ambiguous.py", "tools/list_naked_candidates.py"):
        assert needle in proc.stdout, f"plain output missing {needle!r}"
    print("PASS plain run: all sections present")


def test_partition():
    full = get_json()
    full_funcs = {c["function"] for c in full["drift_quick_wins"]}
    full_ghidra = {c["function"] for c in full["ghidra_absent"]}

    seen_funcs, seen_ghidra = set(), set()
    for slot in range(1, POOL + 1):
        part = get_json(slot=slot, pool=POOL)
        funcs = {c["function"] for c in part["drift_quick_wins"]}
        ghidra = {c["function"] for c in part["ghidra_absent"]}
        assert not funcs & seen_funcs, f"slot {slot} drift items overlap another slot"
        assert not ghidra & seen_ghidra, f"slot {slot} Ghidra items overlap another slot"
        seen_funcs |= funcs
        seen_ghidra |= ghidra
    assert seen_funcs == full_funcs, (
        f"union of slot drift sets != unfiltered set "
        f"(missing {full_funcs - seen_funcs}, extra {seen_funcs - full_funcs})")
    assert seen_ghidra == full_ghidra, (
        f"union of slot Ghidra sets != unfiltered set "
        f"(missing {full_ghidra - seen_ghidra}, extra {seen_ghidra - full_ghidra})")

    anyrun = get_json(slot=3, pool=POOL, extra=["--any"])
    assert {c["function"] for c in anyrun["ghidra_absent"]} == full_ghidra, (
        "--any must undo the Ghidra filter")

    bad = run(["--json"], slot=0, pool=POOL)
    assert bad.returncode != 0 and "AGENT_SLOT" in bad.stderr, "slot 0 must fail loudly"
    print(f"PASS partition: {POOL} slots disjoint, union == unfiltered "
          f"({len(full_funcs)} drift, {len(full_ghidra)} Ghidra items)")


def test_worktree_partition_config():
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as tmp:
        tmp = Path(tmp)
        (tmp / ".git").mkdir()
        config = tmp / ".git" / "openbfme-worker.json"
        config.write_text('{"slot": 3, "pool": 8}\n', encoding="utf-8")
        assert NEXT_WORK.partition_env(tmp) == (3, 8)
        config.write_text('{"slot": 9, "pool": 8}\n', encoding="utf-8")
        try:
            NEXT_WORK.partition_env(tmp)
        except SystemExit as exc:
            assert "1 <= AGENT_SLOT" in str(exc)
        else:
            raise AssertionError("out-of-range worker configuration must fail")
    print("PASS worktree partition config: private slot loaded and validated")


def test_json_shape(data):
    for key in ("ledger", "slot", "pool", "filtered", "drift_quick_wins",
                "structural", "ghidra_meta", "ghidra_absent", "pointers"):
        assert key in data, f"--json output missing key {key!r}"
    print(f"PASS --json: parses, all keys present, {len(data['drift_quick_wins'])} drift wins, "
          f"{len(data['structural'])} structural, {len(data['ghidra_absent'])} Ghidra candidates")


def test_ghidra_candidates_validated(data):
    claimed_names, claimed_rvas = set(), set()
    with (ROOT / "reverse" / "functions.csv").open(newline="") as fh:
        for row in csv.DictReader(fh):
            claimed_names.add(row["name"])
            if row["target_rva"]:
                claimed_rvas.add(int(row["target_rva"], 16))
    for c in data["ghidra_absent"]:
        assert c["function"] not in claimed_names, f"matched function leaked into queue: {c}"
        assert int(c["target_rva"], 16) not in claimed_rvas, f"claimed RVA leaked: {c}"
        assert (ROOT / c["source"]).exists(), f"missing candidate source: {c}"
        assert c["target_size"] > 0 and c["anchors"], f"candidate lacks Ghidra evidence: {c}"
        assert c["confidence"] in ("high", "medium"), f"bad confidence: {c}"
        assert c["command"].startswith("python3 tools/explain_mismatch.py "), c["command"]
    attempts = [c["attempts"] for c in data["ghidra_absent"]]
    assert attempts == sorted(attempts), "attempted Ghidra work must follow fresh candidates"
    print(f"PASS Ghidra queue validated: {len(data['ghidra_absent'])} unclaimed candidates")


def test_corrupt_ledger():
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as tmp:
        tmp = Path(tmp)
        (tmp / "tools").mkdir()
        (tmp / "reverse" / "zh_sweep").mkdir(parents=True)
        (tmp / "src" / "zh").mkdir(parents=True)
        for name in ("next_work.py", "check_csv.py"):
            (tmp / "tools" / name).write_bytes((ROOT / "tools" / name).read_bytes())
        (tmp / "src" / "zh" / "stub.cpp").write_text("// stub\n")
        row = "?Foo@@QAEXXZ,,0x00400000,16,src/zh/stub.cpp,matched,\r\n"
        (tmp / "reverse" / "functions.csv").write_bytes(
            b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
            + (row + row).encode())  # duplicated row = the corruption under test
        (tmp / "reverse" / "symbols.csv").write_text("name,address,notes\n")
        (tmp / "reverse" / "zh_sweep" / "drift_report.csv").write_text(
            "function,source,size,candidate_rva,aligned_pct,class,first_diff,hint,votes\n")
        proc = run(cwd=tmp)
        out = proc.stdout + proc.stderr
        assert proc.returncode == 2, f"corrupt ledger must exit 2, got {proc.returncode}:\n{out}"
        assert "dedup_csv" in out, f"corrupt-ledger output must point at dedup_csv:\n{out}"
        assert "LEDGER CORRUPT" in out, f"missing fix banner:\n{out}"
        assert "drift quick wins" not in out, "sections must not print when the ledger is corrupt"
    print("PASS corrupt ledger: exit 2, dedup_csv fix instructions, no sections")


def main():
    (ROOT / "build").mkdir(exist_ok=True)
    test_plain_run()
    data = get_json()
    test_json_shape(data)
    test_ghidra_candidates_validated(data)
    test_partition()
    test_worktree_partition_config()
    test_corrupt_ledger()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
