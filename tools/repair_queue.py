#!/usr/bin/env python3
"""Queue items with a machine pass test, and where new code goes (FIX_PLAN_v2 rule 7).

tools/next_work.py serves these as tiers; this module builds them.

  repair  gate debt: one keyed baseline line = one row a gate check excuses
          (BFME2 reverse/gate_baseline.txt; BFME1 body_guard_baseline.csv and
          full_gate_baseline.txt). The item names the check and the row's source.
          PASS TEST: `repair_queue.py pass-test LINE` deletes the line and runs the
          row's own gate (tools/build.py SOURCE); a failure puts the line back.
          Exit 0 = the row passes the check and the line stays deleted: commit it
          with the fix. Repairs are credited: progress_v2 shows the debt shrinking.
          Also served: tools/match_tiers.py tier C rows (<reverse>/match_tiers.csv;
          pass: a regrade no longer puts the row in C) and diffexec logic/binding
          divergences (build/diffexec/results.json or REPAIR_DIFFEXEC, JSON or JSONL;
          pass: `tools/diffexec.py --row RVA` exits 0). Twin-body findings are left out.
  link    BFME2: rows the last link cycle did not place at their retail RVA, or
          placed but not self-strict, with the reason (build/link_cycle/
          link_status.csv, or REPAIR_LINK_STATUS). PASS TEST: the next cycle reports
          the row placed=1 self_strict=1 (`tools/link_cycle.py --measure-only`).
  dest    for a NEW match: the translation unit the row belongs in. EA evidence of
          the source file first (BFME1 ea_evidence.csv `file` rows), then address
          contiguity: the unit both neighbouring rows come from, else the nearest
          neighbour's unit within DEST_WINDOW. Generated, dump and address-named
          one-function files are never offered; with no known neighbour the answer
          says so instead of inviting a fresh one-function file.

  python3 tools/repair_queue.py repair [--limit N]
  python3 tools/repair_queue.py link [--limit N]
  python3 tools/repair_queue.py dest 0xRVA
  python3 tools/repair_queue.py pass-test "<baseline line>"
  python3 tools/repair_queue.py verify-removed     # pre-commit, when a debt line is deleted:
                                                   # builds each such row's source not already staged
"""
import argparse
import bisect
import csv
import io
import os
import re
import subprocess
import sys
from functools import lru_cache
from pathlib import Path

# The hooks run HEAD's copy through stdin (an edit cannot approve itself): no __file__ then.
ROOT = Path(os.environ.get("REPAIR_ROOT")
            or (Path(__file__).resolve().parents[1] if "__file__" in globals() else Path.cwd()))
BFME1 = (ROOT / "targets" / "game" / "reverse").is_dir()
REV = "targets/game/reverse" if BFME1 else "reverse"
LEDGER = f"{REV}/functions.csv"
EVIDENCE = f"{REV}/ea_evidence.csv"
SOURCE_PREFIX = "game/" if BFME1 else "Code/"
NOT_A_HOME = ("game/gen_small/", "game/gen_asm/", "game/masm_dumps/", "Code/gen_small/", "Code/gen_asm/",
              "Code/masm_dumps/")
ADDRESS_FILE = re.compile(r"(?i)(?=(?:[0-9a-f]*\d){3})[0-9a-f]{6,8}")
DEST_WINDOW = 0x4000
LINK_STATUS = os.environ.get("REPAIR_LINK_STATUS") or str(ROOT / "build" / "link_cycle" / "link_status.csv")
FILE_ROUTES = ("wb1", "zh", "wb1-run", "retail-run", "wb2", "wb2-run")

CHECKS = {
    "strnul": "a string literal ends before retail's; write the whole literal",
    "ltable": "a jump-table entry or same-section pointer lands on the wrong case; fix the case mapping",
    "tail": "compiled bytes past the row's extent differ from retail; fix the tail (or the extent)",
    "truncated": "the compiled body is longer than the row and retail agrees; raise the extent",
    "genalias": "a gen-alias row's masked call is not a twin of its callee; call the real callee",
    "alias-row": "an object-symbol= alias still resolves callers; give the row its real body or name",
    "static": "TU-local data the body reads ($SG string, local static, const table) differs from retail",
    "dir32": "a DIR32 name does not resolve by retail address",
    "full-gate": "the row is red in the full gate",
}


def _read(rel):
    path = ROOT / rel
    return path.read_text(encoding="utf-8", errors="replace") if path.exists() else ""


@lru_cache(maxsize=1)
def ledger():
    """(rows by rva, sorted [(rva, size, source)] of real homes)."""
    by_rva, homes = {}, []
    for row in csv.DictReader(io.StringIO(_read(LEDGER))):
        if row.get("status") != "matched" or not row.get("target_rva"):
            continue
        rva = int(row["target_rva"], 16)
        by_rva.setdefault(rva, []).append(row)
        source = row["source"]
        if is_home(source):
            homes.append((rva, int(row["target_size"] or 0), source))
    homes.sort()
    return by_rva, homes


def is_home(source):
    """A unit a new row may be added to: real source, not generated, a dump, a .lib, or an
    address-named one-function file."""
    return (source.startswith(SOURCE_PREFIX) and not source.startswith(NOT_A_HOME)
            and source.lower().endswith((".cpp", ".c", ".cc", ".cxx"))
            and not ADDRESS_FILE.search(Path(source).stem))


# ---------------------------------------------------------------- repair tier

def baseline_files():
    if BFME1:
        return ((f"{REV}/body_guard_baseline.csv", "csv"), (f"{REV}/full_gate_baseline.txt", "full"))
    return ((f"{REV}/gate_baseline.txt", "keyed"),)


def parse_debt():
    """[(path, line, check, rva or None, name, detail)] for every baseline line."""
    out = []
    for path, kind in baseline_files():
        text = _read(path)
        if kind == "csv":
            body = [l for l in text.splitlines() if l.strip()]
            for line, row in zip(body[1:], csv.DictReader(io.StringIO("\n".join(body)))):
                out.append((path, line, row["check"], int(row["target_rva"], 16), row["name"], row.get("detail", "")))
        for line in text.splitlines():
            if not line.strip() or line.startswith("#") or kind == "csv":
                continue
            if kind == "keyed":
                check, rva, name = (line.split(None, 2) + ["", ""])[:3]
                out.append((path, line, check, int(rva, 16), name.strip(), ""))
            else:                                   # BFME1 full gate: `name (source)`
                m = re.match(r"(\S+) \((.+)\)$", line.strip())
                if m:
                    out.append((path, line, "full-gate", None, m[1], m[2]))
    return out


def repair_items():
    """Gate-debt rows, each with its check, the row's source and a pass test."""
    by_rva, _ = ledger()
    items = []
    for path, line, check, rva, name, detail in parse_debt():
        rows = by_rva.get(rva, []) if rva is not None else []
        row = next((r for r in rows if r["name"] == name), rows[0] if rows else None)
        # A dir32 key names the referenced datum; its source is the unit that spells it.
        source = row["source"] if row and check != "dir32" else (detail if check == "full-gate" else "")
        size = int(row["target_size"]) if row and check != "dir32" else 0
        items.append({
            "tier": "repair", "check": check, "target_rva": f"0x{rva:08X}" if rva is not None else "",
            "function": name, "source": source or "(git grep -l the name)", "size": size, "credit": size,
            "why": detail or CHECKS.get(check, check), "baseline": path, "baseline_line": line,
            "pass_test": f"python3 tools/repair_queue.py pass-test {shell_quote(line)}",
        })
    items.sort(key=lambda item: (item["check"] == "dir32", -item["size"]))
    return items


MATCH_TIERS = f"{REV}/match_tiers.csv"
DIFFEXEC = os.environ.get("REPAIR_DIFFEXEC") or str(ROOT / "build" / "diffexec" / "results.json")


def diffexec_items(path=None):
    """diffexec logic/binding divergences (a list, {"rows"|"results": [...]} or JSONL),
    `(twin bodies)` findings left out: the code is equal, only the name differs."""
    import json
    path = Path(path or DIFFEXEC)
    if not path.exists():
        return []
    text = path.read_text(encoding="utf-8-sig", errors="replace")
    try:
        data = json.loads(text)
        rows = data if isinstance(data, list) else data.get("rows") or data.get("results") or []
    except ValueError:
        rows = [json.loads(l) for l in text.splitlines() if l.strip().startswith("{")]
    items = []
    for r in rows:
        verdict = str(r.get("verdict", r.get("class", ""))).lower()
        rva = r.get("target_rva", r.get("rva"))
        if verdict not in ("logic", "binding") or "twin bodies" in str(r.get("reason", "")) or rva is None:
            continue
        rva = rva if isinstance(rva, str) else f"0x{int(rva):08X}"
        items.append({
            "tier": "repair", "check": f"diffexec-{verdict}", "target_rva": rva, "function": r.get("name", ""),
            "source": r.get("source", ""), "size": int(r.get("size") or 0), "credit": int(r.get("size") or 0),
            "why": str(r.get("reason", ""))[:300], "baseline": "", "baseline_line": "",
            "pass_test": f"python3 tools/diffexec.py --row {rva}  (exit 0: no logic/binding divergence)",
        })
    return items


def tier_c_items(seen=()):
    """match_tiers.py tier C rows (contradicted) not already served from a baseline line."""
    seen = set(seen)
    items = []
    for r in csv.DictReader(io.StringIO(_read(MATCH_TIERS))):
        if r.get("tier") != "C" or (r["target_rva"].upper(), r["name"]) in seen:
            continue
        items.append({
            "tier": "repair", "check": "tier-C", "target_rva": r["target_rva"], "function": r["name"],
            "source": r["source"], "size": int(r["target_size"] or 0), "credit": int(r["target_size"] or 0),
            "why": r.get("reasons", "")[:300], "baseline": "", "baseline_line": "",
            "pass_test": "python3 tools/match_tiers.py --out build/match_tiers.csv: the row is no longer tier C",
        })
    return items


def all_repair_items():
    """Gate debt, then match_tiers tier C and diffexec divergences not already listed."""
    items = repair_items()
    seen = {(i["target_rva"].upper(), i["function"]) for i in items}
    extra = [i for i in diffexec_items() if (i["target_rva"].upper(), i["function"]) not in seen]
    seen |= {(i["target_rva"].upper(), i["function"]) for i in extra}
    extra += tier_c_items(seen)
    return items + sorted(extra, key=lambda i: -i["size"])


def shell_quote(text):
    return "'" + text.replace("'", "'\"'\"'") + "'"


def locate_source(name):
    got = subprocess.run(["git", "grep", "-l", "-F", "--", name, SOURCE_PREFIX], cwd=ROOT,
                         capture_output=True, text=True)
    files = got.stdout.split()
    return files[0] if files else None


def pass_test(line, build_cmd=None):
    """Delete LINE from its baseline and run the row's own gate; restore the line on
    failure. Returns (ok, message)."""
    item = next((i for i in repair_items() if i["baseline_line"].strip() == line.strip()), None)
    if item is None:
        return False, "no such baseline line (already removed, or mistyped)"
    source = item["source"]
    if source.startswith("("):
        source = locate_source(item["function"])
        if not source:
            return False, f"no source spells {item['function']}; nothing left to verify"
    path = ROOT / item["baseline"]
    raw = path.read_bytes()
    eol = b"\r\n" if b"\r\n" in raw else b"\n"
    kept = [l for l in raw.split(eol) if l.decode("utf-8", "replace").strip() != line.strip()]
    path.write_bytes(eol.join(kept))
    cmd = build_cmd or [sys.executable, str(ROOT / "tools" / "build.py"), source]
    result = subprocess.run(cmd, cwd=ROOT)
    if result.returncode != 0:
        path.write_bytes(raw)
        return False, f"{item['check']} still fails for {item['function']} ({source}); line restored"
    return True, (f"PASS: {item['function']} passes {item['check']}; the line is deleted from "
                  f"{item['baseline']} -- commit it with the fix")


def _git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")


def removed_debt_sources():
    """{source: [baseline lines]} for gate-debt lines the index deletes against HEAD.
    A removal is credited as a repair, so each one is re-verified (rule 5)."""
    out = {}
    for path, kind in baseline_files():
        old, new = _git("show", f"HEAD:{path}"), _git("show", f":{path}")
        if old.returncode or old.stdout == new.stdout:
            continue
        gone = set(old.stdout.splitlines()) - set(new.stdout.splitlines())
        for item in repair_items_from(path, kind, old.stdout):
            if item["baseline_line"] in gone:
                source = item["source"]
                if source.startswith("("):
                    source = locate_source(item["function"])
                if source:                          # nothing spells it any more: nothing to verify
                    out.setdefault(source, []).append(item["baseline_line"])
    return out


def verify_removed(build_cmd=None):
    """Build each removed line's row source the commit does not already stage (the hook's
    delta verify builds staged ones). Returns the failures."""
    removed = removed_debt_sources()
    if not removed:
        return []
    staged = set(_git("diff", "--cached", "--name-only").stdout.split())
    failures = []
    for source, lines in sorted(removed.items()):
        if source in staged:
            continue
        cmd = (build_cmd or [sys.executable, str(ROOT / "tools" / "build.py")]) + [source]
        if subprocess.run(cmd, cwd=ROOT).returncode != 0:
            failures.append(f"{source}: removed {lines[0]!r} but the row still fails its check")
    return failures


def repair_items_from(path, kind, text):
    """repair_items() for one baseline text (HEAD's, when judging a removal)."""
    saved = _read
    try:
        others = {p for p, _ in baseline_files()} - {path}
        globals()["_read"] = lambda rel: text if rel == path else ("" if rel in others else saved(rel))
        return repair_items()
    finally:
        globals()["_read"] = saved


# ---------------------------------------------------------------- link tier

def link_items(path=None):
    """BFME2 link-cycle failures: rows not placed at retail RVA, or placed but not self-strict."""
    path = Path(path or LINK_STATUS)
    if BFME1 or not path.exists():
        return [], (f"no link-cycle status at {path}; run tools/link_cycle.py" if not BFME1
                    else "BFME1 has no link cycle yet")
    items = []
    with path.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row.get("kind") != "real" or (row["placed"] == "1" and row["self_strict"] == "1"):
                continue
            placed = row["placed"] == "1"
            reason = (row["failures"] or "not self-strict") if placed else (row["placement_reason"] or "not placed")
            items.append({
                "tier": "link", "target_rva": row["retail_rva"], "function": row["name"],
                "source": row["source"], "size": int(row["size"] or 0), "credit": int(row["size"] or 0),
                "placed": placed, "why": reason[:300],
                "pass_test": "python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1",
            })
    # placed-but-not-strict first: one relocation fix credits the whole row
    items.sort(key=lambda item: (not item["placed"], -item["size"]))
    mtime = path.stat().st_mtime
    return items, f"{len(items)} row(s) from {path} (written {__import__('time').ctime(mtime)})"


# ---------------------------------------------------------------- destination

@lru_cache(maxsize=1)
def file_evidence():
    out = {}
    for row in csv.DictReader(io.StringIO(_read(EVIDENCE))):
        if row.get("kind") == "file":
            out.setdefault(int(row["rva"], 16), []).append((row["route"], row["value"]))
    return out


def dest_tu(rva):
    """{"dest": path or None, "basis": why} for a new row at RVA."""
    for route, value in sorted(file_evidence().get(rva, ()),
                               key=lambda rv: FILE_ROUTES.index(rv[0]) if rv[0] in FILE_ROUTES else 99):
        path = SOURCE_PREFIX + value.lstrip("/")
        if (ROOT / path).exists():
            return {"dest": path, "basis": f"EA source-file evidence ({route})"}
    _, homes = ledger()
    starts = [h[0] for h in homes]
    i = bisect.bisect_left(starts, rva)
    prev = homes[i - 1] if i > 0 else None
    nxt = homes[i] if i < len(homes) and homes[i][0] != rva else (homes[i + 1] if i + 1 < len(homes) else None)
    if prev and nxt and prev[2] == nxt[2] and nxt[0] - (prev[0] + prev[1]) <= DEST_WINDOW:
        return {"dest": prev[2], "basis": f"between two rows of this unit (0x{prev[0]:08X}, 0x{nxt[0]:08X})"}
    near = []
    if prev and rva - (prev[0] + prev[1]) <= DEST_WINDOW:
        near.append((rva - (prev[0] + prev[1]), prev))
    if nxt and nxt[0] - rva <= DEST_WINDOW:
        near.append((nxt[0] - rva, nxt))
    if near:
        gap, home = min(near)
        return {"dest": home[2], "basis": f"nearest neighbour row 0x{home[0]:08X}, {gap} bytes away"}
    return {"dest": None, "basis": f"no neighbouring unit within 0x{DEST_WINDOW:X} bytes; put it in its "
                                   "class's file, never a new one-function file"}


REPAIR_EVERY = 3
ROTATION = "build/next_work_rotation.json"


def repair_turn(every=None, owner=None):
    """Is this default pick a repair turn? About 1 pick in EVERY (--repair-every, else
    BFME_REPAIR_EVERY, else 3; 1 = every pick, 0 = never first), rotated per agent
    (BFME_CLAIM_OWNER) by a counter in the untracked build/next_work_rotation.json and
    phase-shifted by the owner's name, so seats sharing a clock do not all repair at once."""
    import hashlib
    import json
    if every is None:
        env = os.environ.get("BFME_REPAIR_EVERY", "").strip()
        every = int(env) if env.isdigit() else REPAIR_EVERY
    if every <= 0:
        return False
    if every == 1:
        return True
    owner = owner or os.environ.get("BFME_CLAIM_OWNER") or "default"
    path = ROOT / ROTATION
    try:
        state = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        state = {}
    count = int(state.get(owner, 0))
    state[owner] = count + 1
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(state, sort_keys=True), encoding="utf-8")
    except OSError:
        pass
    phase = int(hashlib.sha256(owner.encode()).hexdigest(), 16) % every
    return (count + phase) % every == 0


def annotate_dest(candidates):
    """Add dest/dest_basis to queue candidates (new matches)."""
    for candidate in candidates:
        rva = candidate.get("target_rva") or candidate.get("candidate_rva")
        try:
            got = dest_tu(int(rva, 16))
        except (TypeError, ValueError):
            continue
        candidate["dest"], candidate["dest_basis"] = got["dest"], got["basis"]
    return candidates


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("repair", "link"):
        p = sub.add_parser(name)
        p.add_argument("--limit", type=int, default=20)
    sub.add_parser("dest").add_argument("rva")
    sub.add_parser("pass-test").add_argument("line")
    sub.add_parser("verify-removed", help="hook: re-verify rows whose debt lines the index deletes")
    args = ap.parse_args(argv)
    if args.cmd == "verify-removed":
        failures = verify_removed()
        for line in failures:
            print(f"repair_queue: {line}", file=sys.stderr)
        return 1 if failures else 0
    if args.cmd == "dest":
        got = dest_tu(int(args.rva, 16))
        print(f"{got['dest'] or '(no unit)'}  <- {got['basis']}")
        return 0
    if args.cmd == "pass-test":
        ok, message = pass_test(args.line)
        print(message)
        return 0 if ok else 1
    items, note = (all_repair_items(), f"{len(parse_debt())} baseline line(s), plus tier C / diffexec") if args.cmd == "repair" else link_items()
    print(note)
    for item in items[:args.limit]:
        print(f"  {item['size']:>6}B {item.get('check', '')} {item['target_rva']} {item['function'][:80]}")
        print(f"         {item['source']}: {item['why'][:160]}")
        print(f"         pass test: {item['pass_test']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
