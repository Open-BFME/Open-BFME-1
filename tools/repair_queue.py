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
          And boot-smoke crashes: rows `tools/boot_smoke.py --bisect` found break start-up
          when their authored code is overlaid (build/boot/boot_queue.json or REPAIR_BOOT;
          pass: `boot_smoke.py --overlay rva:RVA` reaches the menu).
  link    Local diagnostic cycle rows not placed at retail RVA or not self-strict,
          else the committed census's failing units, with the reason (build/link_cycle/
          link_status.csv, or REPAIR_LINK_STATUS). PASS TEST: the next cycle reports
          the row placed=1 self_strict=1 (`tools/link_cycle.py --measure-only`).
          --bundle DIR|current validates integrity, rules, freshness, clean-run
          evidence and local origin/master ancestry via cycle_artifacts. Only
          authoritative clean local runs may be routed.
          --closure ranks conditional single-root unique gains from the measured
          graph; joint-only bytes remain separate and scores must never be added.
          --route (also --router) exposes the failure router; --json includes the
          reason, route and cycle_artifacts.EXIT code. No automatic stale override.
  dest    for a NEW match: the translation unit the row belongs in. EA evidence of
          the source file first (BFME1 ea_evidence.csv `file` rows), then address
          contiguity: the unit both neighbouring rows come from, else the nearest
          neighbour's unit within DEST_WINDOW. Generated, dump and address-named
          one-function files are never offered; with no known neighbour the answer
          says so instead of inviting a fresh one-function file.

  python3 tools/repair_queue.py repair [--limit N]
  python3 tools/repair_queue.py link [--limit N] [--bundle DIR|current [--closure]] [--json] [--route]
  python3 tools/repair_queue.py dest 0xRVA
  python3 tools/repair_queue.py pass-test "<baseline line>"
  python3 tools/repair_queue.py verify-removed     # pre-commit, when a debt line is deleted:
                                                   # builds each such row's source not already staged
"""
import argparse
import bisect
import calendar
import csv
import gzip
import io
import json
import os
import re
import subprocess
import sys
import time
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
LINK_STATUS_SET = os.environ.get("REPAIR_LINK_STATUS")
LINK_STATUS = LINK_STATUS_SET or str(ROOT / "build" / "link_cycle" / "link_status.csv")
CENSUS_STATUS = f"{REV}/link_status.csv"
CENSUS_HISTORY = f"{REV}/link_census_history.csv"
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


BOOT_QUEUE = os.environ.get("REPAIR_BOOT") or str(ROOT / "build" / "boot" / "boot_queue.json")


def boot_items(path=None):
    """Rows whose authored code breaks start-up when overlaid in the boot image:
    `tools/boot_smoke.py --bisect` halves a failing overlay down to them."""
    import json
    path = Path(path or BOOT_QUEUE)
    if not path.exists():
        return []
    items = []
    for r in json.loads(path.read_text(encoding="utf-8")).get("items", []):
        items.append({
            "tier": "repair", "check": "boot-crash", "target_rva": r["target_rva"], "function": r["name"],
            "source": r["source"], "size": int(r.get("size") or 0), "credit": int(r.get("size") or 0),
            "why": str(r.get("why", r.get("outcome", "")))[:300], "baseline": "", "baseline_line": "",
            "pass_test": f"python3 tools/boot_smoke.py --game-dir SANDBOX --overlay rva:{r['target_rva']} "
                         "--timeout 150  (exit 0: reached-menu with the row overlaid)",
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
    """Gate debt, then match_tiers tier C, diffexec divergences and boot-smoke
    crashes not already listed."""
    items = repair_items()
    seen = {(i["target_rva"].upper(), i["function"]) for i in items}
    extra = [i for i in diffexec_items() + boot_items() if (i["target_rva"].upper(), i["function"]) not in seen]
    seen |= {(i["target_rva"].upper(), i["function"]) for i in extra}
    extra += tier_c_items(seen)
    return items + sorted(extra, key=lambda i: -i["size"])


def shell_quote(text):
    return "'" + text.replace("'", "'\"'\"'") + "'"


def locate_source(name):
    owners = {row["source"] for row in csv.DictReader(io.StringIO(_read(f"{REV}/data_rows.csv")))
              if row.get("name") == name and row.get("status") == "matched" and row.get("source")}
    if not owners:
        # A DIR32 may name a function pointer (including an ILT target), not
        # just data. C++ need not spell its decorated COFF name literally.
        with (ROOT / LEDGER).open(newline="", encoding="utf-8") as handle:
            owners = {row["source"] for row in csv.DictReader(handle)
                      if row.get("name") == name and row.get("status") == "matched"
                      and row.get("source")}
    if owners:
        if len(owners) != 1:
            return None
        source = next(iter(owners))
        if (not source.startswith(SOURCE_PREFIX) or ".." in Path(source).parts
                or not (ROOT / source).is_file()):
            return None
        return source
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
    # Mixed CRLF/LF baselines must lose the selected exemption before the
    # checker runs. Preserve every remaining byte, including its terminator.
    kept = b"".join(l for l in raw.splitlines(keepends=True)
                    if l.decode("utf-8", "replace").strip() != line.strip())
    cmd = build_cmd or [sys.executable, str(ROOT / "tools" / "build.py"), source]
    verified = False
    try:
        path.write_bytes(kept)
        verified = subprocess.run(cmd, cwd=ROOT).returncode == 0
    finally:
        # A missing executable or an interrupted build has verified nothing.
        # Keep the deletion only after the checker completed successfully.
        if not verified:
            path.write_bytes(raw)
    if not verified:
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

def census_text(path):
    """Read one committed fallback input, never its mutable worktree copy."""
    got = subprocess.run(["git", "-C", str(ROOT), "rev-parse", "--show-toplevel"],
                         capture_output=True, text=True)
    if got.returncode or Path(got.stdout.strip()).resolve() != ROOT.resolve():
        return None
    got = subprocess.run(["git", "-C", str(ROOT), "show", "HEAD:" + str(path)],
                         capture_output=True, text=True)
    return got.stdout if got.returncode == 0 else None


def stored_census():
    """{"commit", "date", "when"} of the committed link census, or None when the repo has
    no reverse/link_status.csv or no history row saying what it measured."""
    if census_text(CENSUS_STATUS) is None:
        return None
    rows = list(csv.DictReader(io.StringIO(census_text(CENSUS_HISTORY) or "")))
    if not rows or not rows[-1].get("commit"):
        return None
    last = rows[-1]
    try:                                            # link_census.py writes the date in UTC
        when = calendar.timegm(time.strptime(last["date"], "%Y-%m-%d %H:%M"))
    except (TypeError, ValueError):
        when = 0
    return {"commit": last["commit"], "date": last.get("date", ""), "when": when}


def cycle_commit(path):
    """(commit, dirty) a link cycle's status describes, from the receipt.json beside it;
    (None, False) without one."""
    try:
        receipt = json.loads((Path(path).parent / "receipt.json").read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None, False
    return (receipt.get("commit") or None), receipt.get("dirty", False)


def link_source(path=None):
    """(kind, path, note) of the link status the link tier reads, or (None, None, why).

    A link cycle's per-row status (kind "cycle") is preferred: it says which ROW failed and
    why. It is used when named by hand (PATH, REPAIR_LINK_STATUS), or when it exists and is
    not older than the committed census: its receipt's commit descends from the census's
    commit, or, with no receipt or a commit this clone lacks, the file is newer than the
    census's date. Otherwise the committed census (kind "census")."""
    local = Path(path or LINK_STATUS)
    census = stored_census()
    skipped = ""
    if local.exists():
        commit, dirty = cycle_commit(local)
        newer, basis = True, "named by hand"
        if not (path or LINK_STATUS_SET) and census:
            got = subprocess.run(["git", "merge-base", "--is-ancestor", census["commit"], commit],
                                 cwd=ROOT, capture_output=True) if commit else None
            if got is not None and got.returncode in (0, 1):
                newer, basis = got.returncode == 0, "commit vs the census's %s" % census["commit"][:10]
            else:
                newer, basis = local.stat().st_mtime >= census["when"], "file time vs the census's date"
        when = time.ctime(local.stat().st_mtime)
        described = ("commit %s%s" % (commit[:10], " +uncommitted edits" if dirty else "") if commit
                     else "commit unknown (no receipt.json)")
        if newer:
            return "cycle", local, f"LOCAL DIAGNOSTIC (non-authoritative) link cycle {local} ({described}, written {when})"
        skipped = f"; local {local} ({described}) is not newer ({basis}), not used"
    if census:
        return "census", ROOT / CENSUS_STATUS, (f"committed link census {CENSUS_STATUS} (measured at commit "
                                                f"{census['commit']}, {census['date']} UTC){skipped}")
    return None, None, (f"no link status: no link-cycle status at {local} (run tools/link_cycle.py) and no "
                        f"committed census at {CENSUS_STATUS} with a {CENSUS_HISTORY} row")


def census_items(path, *, committed=False):
    """Units the stored census says do not link: fewest blockers first.

    Size is the unit's matched extent sum, not a proven unique-byte gain.
    """
    from link_census import STATUS_FIELDS
    if committed:
        functions = csv.DictReader(io.StringIO(census_text(LEDGER) or ""))
        by_rva = {}
        for row in functions:
            if row.get("status") == "matched":
                by_rva.setdefault(int(row["target_rva"], 16), []).append(row)
    else:
        by_rva, _ = ledger()
    rows_of = {}
    for rva, rows in by_rva.items():
        for row in rows:
            rows_of.setdefault(row["source"], []).append((rva, row))
    data_path = "targets/game/reverse/data_rows.csv"
    data_text = census_text(data_path) if committed else _read(data_path)
    for row in csv.DictReader(io.StringIO(data_text or "")):
        if row.get("status") != "matched":
            continue
        address = int(row["address"], 16)
        if row["address_kind"] == "va":
            address -= 0x400000
        elif row["address_kind"] != "rva":
            raise ValueError("unknown data address_kind")
        rows_of.setdefault(row["source"], []).append((address, dict(row, target_size=0, data=True)))
    items = []
    text = census_text(CENSUS_STATUS) if committed else Path(path).read_text(encoding="utf-8")
    with io.StringIO(text or "") as handle:
        for row in csv.DictReader(handle):
            if row.get("linked") == "yes" or row["source"] not in rows_of:
                continue
            owned = sorted(rows_of[row["source"]], key=lambda r: r[0])
            blockers = {k: int(row.get(k) or 0) for k in
                        STATUS_FIELDS[2:]}
            size = sum(int(r["target_size"] or 0) for _, r in owned)
            items.append({
                "tier": "link", "target_rva": "0x%08X" % owned[0][0], "function": owned[0][1]["name"],
                "source": row["source"], "size": size, "credit": 0, "placed": False,
                "address_kind": "rva", "provider_kind": "data" if all(r.get("data") for _, r in owned) else "code",
                "blockers": sum(blockers.values()),
                "why": ("unit does not link (%d matched row(s)): " % len(owned)
                        + (", ".join("%s %d" % kv for kv in blockers.items() if kv[1]) or "linked=no")),
                "pass_test": f"python3 tools/link_check.py {row['source']}: LINKS (the next census: linked=yes)",
            })
    items.sort(key=lambda item: (item["blockers"], -item["size"]))
    return items


def link_items(path=None):
    """BFME1 link repairs, with a note naming the source read and the commit it describes:
    a link cycle's rows not placed at retail RVA or placed but not self-strict, else the
    committed census's units that do not link (link_source)."""
    kind, path, note = link_source(path)
    if kind is None:
        return [], note
    if kind == "census":
        items = census_items(path, committed=True)
        return eligible_link_items(items), f"{len(items)} unit(s) that do not link, from the {note}"
    items = cycle_items(path)
    return eligible_link_items(items), f"{len(items)} row(s) from the {note}"


def open_status(path):
    """A link_status.csv, plain or gzip (by its magic bytes), as text."""
    path = Path(path)
    with path.open("rb") as handle:
        gz = handle.read(2) == b"\x1f\x8b"
    if gz:
        return io.TextIOWrapper(gzip.open(path), encoding="utf-8", newline="")
    return path.open(encoding="utf-8", newline="")


def cycle_items(path):
    """A link cycle's real rows not placed at their retail RVA, or placed but not
    self-strict: placed ones first, then by size."""
    items = []
    with open_status(path) as handle:
        for row in csv.DictReader(handle):
            if row.get("kind") != "real" or (row["placed"] == "1" and row["self_strict"] == "1"
                                               and not int(row.get("hardcoded") or 0)
                                               and not int(row.get("failure_count") or 0)):
                continue
            placed = row["placed"] == "1"
            reason = (row["failures"] or "not self-strict") if placed else (row["placement_reason"] or "not placed")
            items.append({
                "tier": "link", "target_rva": row["retail_rva"], "function": row["name"],
                "source": row["source"], "size": int(row["size"] or 0), "credit": 0,
                "placed": placed, "why": reason[:300],
                "pass_test": "python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1",
            })
    # Placed-but-not-strict first; ordinary row extents make no closure gain claim.
    items.sort(key=lambda item: (not item["placed"], -item["size"]))
    return items


def eligible_link_items(items):
    """Use BFME1's shared predicate, including live claims; selection creates no lease.

    A worker must still claim the served address with tools/claims.py before work.
    The BFME2-layout compatibility tests do not use BFME1 eligibility rules.
    """
    if not BFME1 or not items:
        return items
    # Also works when the committed hook runs this file through stdin.
    tools = str(ROOT / "tools")
    if tools not in sys.path:
        sys.path.insert(0, tools)
    import eligibility
    ok = eligibility.servable(root=ROOT)
    return [dict(item, claim_required=True,
                 claim_command=f"python3 tools/claims.py claim {item['target_rva']}")
            for item in items if ok(int(item["target_rva"], 16))]


def cycle_artifacts():
    """Lazy import: the debt hook can execute this module through stdin."""
    tools = str(Path(__file__).resolve().parent if "__file__" in globals() else ROOT / "tools")
    if tools not in sys.path:
        sys.path.insert(0, tools)
    import cycle_artifacts as ca
    return ca


FAILURE_ROUTES = {
    "corrupt": "tooling seat",
    "unavailable": "use another work lane",
    "empty": "use another work lane",
    "stale": "use another work lane",
    "incompatible-rules": "tooling seat / human review",
    "not-authoritative": "refuse",
    "no-closure-report": "ordinary link queue, no closure ranking",
}


def failure_route(reason):
    """Pure routing decision for other selectors; never retries or relaxes validation."""
    return {"reason": reason, "route": FAILURE_ROUTES[reason],
            "exit_code": cycle_artifacts().EXIT[reason]}


def bundle_path(bundle):
    return cycle_artifacts().DEFAULT_STORE if str(bundle) == "current" else bundle


def bundle_note(b, fr, what, allow_stale=False):
    trust = "authoritative clean local run" if fr["authoritative"] else "non-authoritative diagnostic"
    return (f"{what} from link-cycle bundle {b.tag} ({b.dir}; commit {b.commit[:12]}, measured "
            f"{fr['measured_end_utc']} UTC, {fr['age_hours']:.2f} h ago; {trust}; "
            f"allow_stale={allow_stale}; {fr['ancestry']})")


def closure_queue(b):
    """Read a receipt-bound report and reproduce its ranking from the measured graph.

    Hashes alone do not prove the report's claimed gains. Compare its whole score
    table (ignoring only the optional forced-closure annotation) with analyze().
    Never add root scores, joint-only candidates, or overlapping own/beneficiary
    sizes. A root names a failed node address, which can also be a datum.
    """
    ca = cycle_artifacts()
    import closure_report as cr
    try:
        doc = cr.load_roots(b.closure_roots)
        graph = cr.load_graph(b.closure_graph, b.receipt["closure_graph_sha256"])
        expected, _ = cr.analyze(*graph)
        strip_verified = lambda roots: [dict(e, verified=None) for e in roots]
        ca.same("closure root gains reproduced from graph", strip_verified(doc["roots"]), expected["roots"])
        ca.same("closure summary reproduced from graph", doc["summary"], expected["summary"])
    except cr.ReportError as e:
        raise ca.BundleError(f"closure ranking: {e}") from None
    except (OSError, ValueError, TypeError, KeyError, IndexError) as e:
        raise ca.BundleError(f"malformed closure ranking: {e}") from None
    # A passing row must never be served as a repair. The failed datum or other
    # non-unit root can be served by its own node identity, not a passing caller.
    with open_status(b.link_status) as handle:
        passing = {(int(r["retail_rva"], 16), r["name"], r["source"]) for r in csv.DictReader(handle)
                   if r["placed"] == "1" and r["self_strict"] == "1" and r["closed_strict"] == "1"}
    items, unaddressed = [], []
    for e in doc["roots"]:
        if not re.fullmatch(r"0x[0-9A-Fa-f]+", e["root"]):
            unaddressed.append(e["root"])
            continue
        name, source = cr.root_line(e)
        if (int(e["root"], 16), name, source) in passing:
            continue
        gain = e["conditional_gain_bytes"]
        items.append({
            "tier": "closure", "check": "closure", "target_rva": e["root"],
            "function": name, "source": source or "(no unit)", "size": gain, "credit": gain,
            "conditional_gain_bytes": gain, "non_additive": True,
            "why": (f"conditional single-root unique gain {gain} B; beneficiaries {e['beneficiary_rows']} row(s) "
                    f"/ {e['beneficiary_bytes']} B; own failing rows {e['direct_rows']} / {e['direct_bytes']} B; "
                    + "; ".join(e["failures"])),
            "pass_test": (f"a later validated bundle no longer lists root {e['root']} and its rows are "
                          "closed_strict=1; claim the root before working on it"),
        })
    # analyze() is ranked, but make the ordering contract explicit to consumers.
    items.sort(key=lambda item: (-item["conditional_gain_bytes"], item["target_rva"]))
    joint = dict(doc["summary"]["joint_only"])
    notes = [f"graph: {doc['graph']['label']}",
             "CONDITIONAL single-root unique bytes on the frozen measured graph; root scores may overlap: "
             "do not add them; not a repair proof.",
             f"JOINT-ONLY candidate unique bytes: {joint['candidate_unique_bytes']} B (separate, non-additive; "
             "never included in any single-root score).",
             "limits: " + "; ".join(doc["limits"])]
    if unaddressed:
        notes.append(f"{len(unaddressed)} report root(s) have no retail address for eligibility/claims; "
                     "not served: " + ", ".join(unaddressed))
    return items, notes, joint


def candidate_scope(item, graph=None):
    """Sources and addresses whose measured state supports this candidate."""
    sources = set(item.get("sources") or [item.get("source", "")]) - {"", "(no unit)"}
    address = item.get("target_rva") or item.get("rva")
    addresses = {int(address, 16)} if address else set()
    if graph is None:
        return sources, addresses
    ok, edges, rows, describe = graph
    nodes = {n for n in ok if describe(n).get("source") in sources
             or (describe(n).get("retail_rva") and int(describe(n)["retail_rva"], 16) in addresses)}
    nodes.update(r["node"] for r in rows if r["source"] in sources or r["rva"] in addresses)
    pending = list(nodes)
    while pending:
        for target in edges.get(pending.pop(), ()):
            if target not in nodes:
                nodes.add(target)
                pending.append(target)
    for node in nodes:
        desc = describe(node)
        if desc.get("source"):
            sources.add(desc["source"])
        sources.update(desc.get("sources", []))
        if desc.get("retail_rva"):
            addresses.add(int(desc["retail_rva"], 16))
    for row in rows:
        if row["node"] in nodes:
            sources.add(row["source"])
            addresses.add(row["rva"])
    return sources, addresses


def _currency_row_relevant(row, path, sources, addresses):
    raw = row.get("target_rva") or row.get("address")
    candidates = set()
    if raw:
        value = int(raw, 16)
        candidates.add(value)
        if row.get("address_kind") == "va" or path.endswith("symbols.csv"):
            candidates.add(value - 0x400000)
    return bool(candidates & addresses or row.get("source") in sources)


def _currency_rows(stream, path, sources, addresses):
    return {tuple(sorted(row.items())) for row in csv.DictReader(stream)
            if _currency_row_relevant(row, path, sources, addresses)}


def _currency_ledger(root, commit, path, sources, addresses):
    """Stream a revision's ledger, retaining only candidate/dependency rows."""
    # Distinguish a genuinely absent ledger from an unreadable Git object.
    listing = subprocess.run(["git", "-C", str(root), "ls-tree", "--name-only", commit, "--", path],
                             check=True, capture_output=True, text=True)
    if not listing.stdout.strip():
        return set()
    command = ["git", "-C", str(root), "show", f"{commit}:{path}"]
    found = set()
    with subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL,
                          text=True, encoding="utf-8") as proc:
        found = _currency_rows(proc.stdout, path, sources, addresses)
        if proc.wait():
            raise subprocess.CalledProcessError(proc.returncode, command)
    return found


def candidate_include_changes(sources, changed, graph, root):
    """Use witnessed deps/search roots, not a guessed header suffix list."""
    import hashlib
    proofs = {}
    if graph is not None:
        for node in graph[0]:
            proofs.update(graph[3](node).get("include_proofs", {}))
    moved = set()
    for source in sources:
        proof = proofs.get(source)
        if proof is None:
            # Legacy graphs have no include witness. BFME1 build's directory
            # inventory watches all non-.cpp files, including untracked ones.
            # Bound uncertainty to the candidate's source-adjacent search tree.
            parent = Path(source).parent
            moved.update(p for p in changed if Path(p).is_relative_to(parent)
                         and not p.lower().endswith(".cpp"))
            continue
        for path, digest in proof.get("deps", {}).items():
            try:
                current = hashlib.sha256((Path(root) / path).read_bytes()).hexdigest()
            except OSError:
                current = None
            if current != digest:
                moved.add(path)
        # BFME1 build.search_inventory treats a new earlier include as a
        # compile input change, regardless of suffix or Git tracking status.
        import build
        previous_root = build.ROOT
        try:
            build.ROOT = Path(root).resolve()
            if build._recorded_inventory(proof) != proof.get("inventory") or proof.get("inventory") is None:
                moved.add(source + " (include search changed)")
        finally:
            build.ROOT = previous_root
    return moved


def current_bundle_items(items, commit, *, root=None, graph=None):
    """Never serve work whose measured sources/dependencies/ledger rows moved.

    An ancestor bundle's age/authority says nothing about a later repair. Diff
    paths first, then compare only relevant rows in changed ledgers; unrelated
    ledger additions do not stale every root. Git uncertainty fails closed.
    """
    if not items:
        return [], []
    root = ROOT if root is None else root
    scopes = [candidate_scope(item, graph) for item in items]
    try:
        changed = set(subprocess.run(
            ["git", "-C", str(root), "diff", "--no-renames", "--name-only", "-z", f"{commit}..HEAD"],
            check=True, capture_output=True, text=True).stdout.split("\0")) - {""}
        # Local source/header edits must not revive stale measurements either.
        local_changed = set(subprocess.run(
            ["git", "-C", str(root), "diff", "--no-renames", "--name-only", "-z", "HEAD"],
            check=True, capture_output=True, text=True).stdout.split("\0")) - {""}
        changed.update(local_changed)
        changed.update(set(subprocess.run(
            ["git", "-C", str(root), "ls-files", "--others", "--exclude-standard", "-z"],
            check=True, capture_output=True, text=True).stdout.split("\0")) - {""})
        ledgers = {f"targets/game/reverse/{name}.csv" for name in ("functions", "symbols", "data_rows")} & changed
        sources = set().union(*(s for s, _ in scopes))
        addresses = set().union(*(a for _, a in scopes))
        deltas = {}
        for path in ledgers:
            before = _currency_ledger(root, commit, path, sources, addresses)
            after = _currency_ledger(root, "HEAD", path, sources, addresses)
            deltas[path] = before ^ after
            if path in local_changed:
                try:
                    with (Path(root) / path).open(newline="", encoding="utf-8") as stream:
                        local = _currency_rows(stream, path, sources, addresses)
                except FileNotFoundError:
                    local = set()
                deltas[path].update(after ^ local)
    except (OSError, ValueError, subprocess.SubprocessError):
        return [], [dict(item, reason="stale", stale_reason="cannot compare measured commit with HEAD") for item in items]
    kept, skipped = [], []
    for item, (sources, addresses) in zip(items, scopes):
        moved = sorted((sources & changed) | candidate_include_changes(sources, changed, graph, root))
        for path, rows in deltas.items():
            # Reuse the same address/source filter on the narrow row delta.
            for values in rows:
                if _currency_row_relevant(dict(values), path, sources, addresses):
                    moved.append(path)
                    break
        if moved:
            skipped.append(dict(item, reason="stale", stale_reason="changed since measurement: " + ", ".join(sorted(set(moved)))))
        else:
            kept.append(item)
    return kept, skipped


def _bundle_queue(bundle, *, closure=False, now=None, allow_stale=False):
    ca = cycle_artifacts()
    b, fr, lines = ca.serve(bundle_path(bundle), root=ROOT, now=now, allow_stale=allow_stale,
                            need_closure=closure)
    if closure:
        items, notes, joint = closure_queue(b)
    else:
        items, notes, joint = cycle_items(b.link_status), [], None
    import closure_report as cr
    graph = cr.load_graph(b.closure_graph, b.receipt["closure_graph_sha256"])
    items, skipped = current_bundle_items(items, b.commit, root=ROOT, graph=graph)
    notes.extend(f"stale candidate {i['target_rva']}: {i['stale_reason']}" for i in skipped)
    items = eligible_link_items(items)
    authoritative = fr["authoritative"]
    for item in items:
        item.update(authoritative=authoritative, diagnostic=not authoritative)
    notes.insert(0, bundle_note(b, fr, f"{len(items)} {'closure root' if closure else 'row'}(s)", allow_stale))
    warnings = [line for line in lines if line.startswith(("STALE", "NOT AUTHORITATIVE", "NOT THE NEWEST", "WARNING"))]
    return {"items": items, "notes": notes, "warnings": warnings, "joint_only": joint, "skipped_candidates": skipped,
            "authoritative": authoritative, "diagnostic": not authoritative, "freshness": fr,
            "source_kind": "bundle", "bundle": str(b.dir), "tag": b.tag, "commit": b.commit}


def bundle_link_items(bundle, now=None, allow_stale=False):
    """BFME2-compatible diagnostic API; validation failures never use local files."""
    result = _bundle_queue(bundle, now=now, allow_stale=allow_stale)
    return result["items"], "\n".join(result["notes"]), result["warnings"]


def closure_items(bundle, now=None, allow_stale=False):
    """Conditional roots only; joint-only gains are separate notes, never scores."""
    result = _bundle_queue(bundle, closure=True, now=now, allow_stale=allow_stale)
    return result["items"], result["notes"], result["warnings"]


def link_queue(bundle=None, *, closure=False, now=None, allow_stale=False, router=False):
    """Machine result for diagnostics or routing, with cycle_artifacts reason/exit codes.

    The caller must explicitly request allow_stale; it is passed once, recorded,
    and never retried. Explicit bundles have no local/census fallback. The router
    cannot return diagnostic items, including an explicit stale override.
    no-closure-report returns the ordinary-queue route, not a different source.
    """
    ca = cycle_artifacts()
    result = {"items": [], "notes": [], "warnings": [], "joint_only": None,
              "authoritative": False, "diagnostic": True, "router": router,
              "allow_stale": allow_stale, "sub_reason": None,
              "closure_requested": closure, "closure_ranking": False,
              "requested_bundle": str(bundle) if bundle is not None else None,
              "reason": None, "exit_code": 0, "route": None}
    try:
        if bundle is not None:
            result.update(_bundle_queue(bundle, closure=closure, now=now, allow_stale=allow_stale))
            if router and not result["authoritative"]:
                raise ca.Refused("bundle diagnostics are never routed", "not-authoritative",
                                 result["freshness"]["sub_reason"])
            result["closure_ranking"] = closure
        else:
            if closure or allow_stale:
                raise ca.Unavailable("--closure and --allow-stale require --bundle DIR|current")
            kind, path, note = link_source()
            if kind is None:
                raise ca.Unavailable(note)
            if router and kind == "cycle":
                raise ca.Refused("local cycle files are non-authoritative diagnostics; never routed",
                                 "not-authoritative", "diagnostic")
            items = census_items(path, committed=True) if kind == "census" else cycle_items(path)
            result.update(items=eligible_link_items(items), notes=[note], source_kind=kind)
        if not result["items"]:
            raise ca.Empty("no eligible unclaimed repairs in this source (passing rows are excluded)")
        result["status"] = "ok"
        if router:
            result["route"] = "closure link queue" if closure else "ordinary link queue"
    except ca.Problem as e:
        result.update(failure_route(e.reason), status="refused", message=str(e), items=[],
                      authoritative=False, diagnostic=True, sub_reason=getattr(e, "sub_reason", None),
                      closure_ranking=False,
                      joint_only=result["joint_only"] if e.reason == "empty" else None)
    except (OSError, ValueError, TypeError, KeyError, AttributeError, EOFError, csv.Error) as e:
        result.update(failure_route("corrupt"), status="refused", message=str(e), items=[],
                      authoritative=False, diagnostic=True,
                      closure_ranking=False, joint_only=None)
    return result


def route_link_queue(bundle=None, **kwargs):
    """Router entry point: uses link_queue's checks, never routes diagnostic bundles."""
    return link_queue(bundle, router=True, **kwargs)


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
        if name == "link":
            p.add_argument("--bundle", metavar="DIR|current", help="validated cycle bundle/store; never local fallback")
            p.add_argument("--closure", action="store_true", help="rank conditional single-root gains in --bundle")
            p.add_argument("--allow-stale", action="store_true", help="explicit human freshness override, recorded in output")
            p.add_argument("--route", "--router", dest="router", action="store_true", help="router mode: refuse diagnostic bundles")
            p.add_argument("--json", action="store_true", help="machine result with reason, route and cycle_artifacts exit code")
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
    if args.cmd == "link":
        result = link_queue(args.bundle, closure=args.closure, allow_stale=args.allow_stale,
                            router=args.router)
        if args.json:
            print(json.dumps(dict(result, items=result["items"][:max(0, args.limit)]), sort_keys=True))
        else:
            for line in result["notes"]:
                print(line)
            for line in result["warnings"]:
                print(f"repair_queue: {line}", file=sys.stderr)
            if result["reason"]:
                print(f"repair_queue: [reason={result['reason']}, sub_reason={result['sub_reason']}] {result['message']}; "
                      f"route: {result['route']}; allow_stale={result['allow_stale']}", file=sys.stderr)
            else:
                if result["route"]:
                    print(f"route: {result['route']}")
                for item in result["items"][:max(0, args.limit)]:
                    print(f"  {item['size']:>6}B {item.get('check', '')} {item['target_rva']} {item['function'][:80]}")
                    print(f"         {item['source']}: {item['why'][:400]}")
                    print(f"         pass test: {item['pass_test']}")
                    if item.get("claim_required"):
                        print(f"         claim first: {item['claim_command']}")
        return result["exit_code"]
    items, note = all_repair_items(), f"{len(parse_debt())} baseline line(s), plus tier C / diffexec"
    print(note)
    for item in items[:args.limit]:
        print(f"  {item['size']:>6}B {item.get('check', '')} {item['target_rva']} {item['function'][:80]}")
        print(f"         {item['source']}: {item['why'][:160]}")
        print(f"         pass test: {item['pass_test']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
