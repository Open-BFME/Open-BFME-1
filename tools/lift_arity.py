#!/usr/bin/env python3
"""Does a lift's body read more stack arguments than its name declares?

The named __emit lifts (tools/lift_lane.py) came with their names, and the
first finisher round found 4 of 11 wrong (2026-09-25) although stack cleanup
agreed with them: a cdecl caller cleans up, so `ret` says nothing about arity.
Ghidra's decompiler infers the parameters a body actually READS. A body that
reads more stack slots than its decorated name declares cannot be that
function. Measured 2026-09-26 on this project: 1 of 260 correctly landed rows
(a by-value Vector2 counted as one parameter; by-value records are now left
undecided) against 39 of 332 lifts, including both known misnamed cdecl lifts
(0x009004A0 declares 0, reads 6; 0x0023E5F0 declares 0, reads 3). The reverse
(reads fewer) is no evidence: an unused parameter is invisible to the
decompiler.

Needs a running GhidraSQL server on the BFME project (tools/ghidrasql_serve.cmd).
The result is tracked, so hosts without Ghidra read it:

  python3 tools/lift_arity.py                     # rewrite targets/game/reverse/lift_arity.csv
  python3 tools/lift_arity.py --calibrate 300     # also score N landed rows, print the FP rate

lift_lane.identity_warnings reads the CSV and warns in every brief.
"""
import argparse
import csv
import json
import random
import re
import sys
import urllib.request
from pathlib import Path

import audit_ret_arity as A

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "targets/game/reverse/lift_arity.csv"
FIELDS = ["name", "target_rva", "declared_slots", "inferred_slots", "verdict"]
IMAGE_BASE = 0x400000
PLACEHOLDER = re.compile(r"^\?(d|dup|j|b)_[0-9a-fA-F]{8}@@")
WIDE = re.compile(r"\b(double|longlong|ulonglong|undefined8|longdouble|float10)\b")


def declared_slots(sym):
    """4-byte stack slots the decorated name declares, or None when undecidable
    (template grammar, back-references, by-value records of unknown size)."""
    # ?d_/?dup_/?j_ placeholders carry a dummy `void()` signature on purpose:
    # they assert no identity, so there is no declared arity to contradict (all
    # three calibration hits on landed rows were ?dup_ placeholders).
    if PLACEHOLDER.match(sym):
        return None
    m = re.search(r"@@([A-Z])", sym)
    if not m or "?$" in sym:
        return None
    lead = m.group(1)
    pos = m.end() if (lead == "Y" or lead in A.STATIC_MEMBER) else m.end() + 1
    if pos >= len(sym) or sym[pos] not in A.CONVENTIONS:
        return None
    i = pos + 1
    try:
        if re.match(r"\?\?[01]", sym) and i < len(sym) and sym[i] == "@":
            i += 1
        else:
            i = A.skip_type(sym, i)
        if sym[i:i + 2] == "XZ":
            return 0
        slots = 0
        while i < len(sym) and sym[i] not in "@Z":
            if sym[i].isdigit():
                return None                    # back-reference: type unknown here
            size, _, i = A.arg_size(sym, i)
            slots += (size + 3) // 4
        return slots
    except (ValueError, KeyError, IndexError):
        return None


def inferred_slots(signature):
    """Stack slots in a decompiled signature line; ECX (`this`) is a register."""
    m = re.search(r"\((.*)\)\s*$", signature)
    if not m:
        return None
    slots = 0
    for param in m.group(1).split(","):
        param = param.strip()
        if not param or param == "void" or "ECX" in param:
            continue
        slots += 2 if WIDE.search(param) else 1
    return slots


def query(url, sql):
    req = urllib.request.Request(url, data=sql.encode("utf-8"), method="POST")
    with urllib.request.urlopen(req, timeout=600) as resp:
        data = json.loads(resp.read().decode("utf-8"))
    res = data["results"][-1]
    if not res.get("success"):
        raise RuntimeError(res.get("error"))
    return [dict(zip(res["columns"], row)) for row in res["rows"]]


def signature(url, rva):
    rows = query(url, f"SELECT text FROM pseudocode WHERE func_addr = {rva + IMAGE_BASE} "
                      "AND completed = 1 AND is_fallback = 0;")
    for line in (rows[0]["text"] if rows else "").splitlines():
        line = line.strip()
        if line and not line.startswith("/*"):
            return line
    return None


def verdict(declared, inferred):
    if declared is None or inferred is None:
        return "undecided"
    return "reads-more" if inferred > declared else "consistent"


def judge(url, name, rva):
    declared = declared_slots(name)
    inferred = inferred_slots(signature(url, rva) or "") if declared is not None else None
    return declared, inferred, verdict(declared, inferred)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--url", default="http://127.0.0.1:8081/query")
    ap.add_argument("--calibrate", type=int, default=0,
                    help="also judge N random landed C++ rows and print how many read-more")
    args = ap.parse_args(argv)

    import eligibility
    import lift_lane

    try:
        query(args.url, "SELECT 1;")
    except OSError as error:
        raise SystemExit(f"lift_arity: no GhidraSQL server at {args.url} ({error}); "
                         "start tools/ghidrasql_serve.cmd first")
    rows = eligibility.load_rows()
    lifts = lift_lane.lift_rows(rows)
    out = []
    for (name, rva_text) in sorted(lifts, key=lambda k: k[1]):
        declared, inferred, v = judge(args.url, name, int(rva_text, 16))
        out.append({"name": name, "target_rva": rva_text, "declared_slots": "" if declared is None else declared,
                    "inferred_slots": "" if inferred is None else inferred, "verdict": v})
    with OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(out)
    flagged = [r for r in out if r["verdict"] == "reads-more"]
    print(f"lift_arity: {len(out)} lifts, {len(flagged)} read more stack slots than their "
          f"name declares, {sum(r['verdict'] == 'undecided' for r in out)} undecided -> "
          f"{OUT.relative_to(ROOT).as_posix()}")

    if args.calibrate:
        landed = [r for r in rows if r.get("status") == "matched"
                  and (r.get("target_rva") or "").startswith("0x")
                  and r.get("source", "").endswith(".cpp") and not r["source"].startswith("game/gen_")
                  and (r["name"], r["target_rva"]) not in lifts and not eligibility.is_dump_row(r)
                  and declared_slots(r["name"]) is not None]
        random.seed(7)
        sample = random.sample(landed, min(args.calibrate, len(landed)))
        judged = [judge(args.url, r["name"], int(r["target_rva"], 16)) for r in sample]
        decided = [j for j in judged if j[2] != "undecided"]
        wrong = sum(j[2] == "reads-more" for j in decided)
        print(f"calibration: {wrong} of {len(decided)} landed rows read more "
              f"({100 * wrong / max(len(decided), 1):.1f}%)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
