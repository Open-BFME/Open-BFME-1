#!/usr/bin/env python3
"""The nightly audit (DECISION_RECORD pillar 5): sample, measure, judge, calibrate, red-team, queue.

Advisory only. Nothing here refuses a commit or changes a tracked file; it
writes <state>/runs/<stamp>/ (report.md, run.json, packets) and the queue
(<state>/queue.json, see findings.py). The exit code is 0 unless the audit
itself crashed.

Steps
  1. window   landed commits on AUDIT_REF (default origin/master) since the last
              run (or --last N / --since)
  2. quality  per-file components of every commit in the window; regressions on
              touched files -> quality-regression items (components.py)
  3. sample   stratified + uniform, blinded packets (sampler.py)
  4. canaries one per defect class + benign controls, shuffled into the stream
  5. judges   independent first verdicts from two allowlisted families,
              escalation on disagreement (panel.py); agreed/escalated defects on
              natural rows -> judge-defect items
  6. metrics  recall/precision per class and judge, benign false positives,
              drift alerts against <state>/canary_history.jsonl
  7. redteam  capped; deterministic harness; confirmed escapes -> fixtures +
              gate-escape items (redteam.py)

Run on the owner's PC, not in CI. Use a DEDICATED worktree of the repo that no
agent works in (the red team edits and restores files in it and runs the
gate there):

  git worktree add ..\\audit-bfme2 origin/master        (once)
  tools\\audit\\run_nightly.cmd C:\\path\\to\\audit-bfme2  (what the task runs)

Windows Task Scheduler (once, from an ordinary cmd prompt):

  schtasks /Create /TN "Open-BFME audit" /SC DAILY /ST 03:30 ^
    /TR "\\"C:\\path\\to\\audit-bfme2\\tools\\audit\\run_nightly.cmd\\" \\"C:\\path\\to\\audit-bfme2\\""

  The launcher fetches origin, checks the worktree out at origin/master
  (detached), runs this script with the defaults below and appends to
  build\\audit\\nightly.log. "Run whether user is logged on or not" needs the
  Codex/Claude CLIs logged in for that account.

  python3 tools/audit/nightly.py [--last N | --since 1.day] [--n 30]
      [--judges gpt-6.1-sol,claude-opus-5-5] [--escalate claude-fable-5-1]
      [--benign 3] [--redteam 2] [--redteam-model gpt-6.1-sol] [--no-judges]
"""
import argparse
import concurrent.futures
import datetime
import json
import random
import sys
import time
import traceback

import canaries
import common
import components
import findings
import panel
import redteam
import sampler

LAST_RUN = common.STATE / "last_run.json"
HISTORY = common.STATE / "canary_history.jsonl"
SEVERITY_OF = {"wrong_callee": "high", "wrong_data": "high", "truncated_string": "high",
               "switch_mapping": "high", "private_class_copy": "medium", "unsupported_name": "medium",
               "raw_offsets": "low", "prompt_injection": "medium", "other": "low"}


def judge_stream(items, first, escalate, workers, log):
    """Run the panel over [(packet, label)] in a small pool. Returns [(packet, label, panel)]."""
    def one(entry):
        packet, label = entry
        try:
            return packet, label, panel.panel(packet, first, escalate)
        except Exception as exc:  # one broken item never stops the night
            return packet, label, {"packet": packet["id"], "decision": "error", "error": repr(exc),
                                   "first": [], "escalated": None, "classes": []}
    out = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as pool:
        for i, res in enumerate(pool.map(one, items), 1):
            log(f"  judged {i}/{len(items)} {res[0]['id']} -> {res[2]['decision']} {res[2].get('classes')}")
            out.append(res)
    return out


def accuses(classes, label):
    """A semantic finding, or the very structural class a canary planted."""
    return bool(set(classes) & panel.SEMANTIC) or label in classes


def per_judge_results(judged):
    """{judge or 'panel': [(label, classes, flagged)]} over labelled items."""
    out = {}
    for packet, label, result in judged:
        if label == "natural":
            continue
        for rec in result["first"] + ([result["escalated"]] if result.get("escalated") else []):
            if rec.get("counted"):
                got = panel.classes(rec)
                out.setdefault(rec["judge"], []).append((label, got, accuses(got, label)))
        flagged = result["decision"] in ("agreed-defect", "escalated-defect", "single-defect")
        got = set(result["classes"]) if flagged else set()
        out.setdefault("panel", []).append((label, got, accuses(got, label)))
    return out


def run(args, log):
    stamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    out_dir = common.STATE / "runs" / stamp
    out_dir.mkdir(parents=True, exist_ok=True)
    tip = common.git("rev-parse", common.REF).strip()
    last = common.load_json(LAST_RUN, {})
    if args.last or args.since:
        shas = sampler.window(args.last, args.since)
    elif last.get("tip"):
        shas = common.git("log", "--no-merges", "--format=%H", f"{last['tip']}..{tip}").split()
    else:
        shas = sampler.window(None, "1.day")
    seed = f"{common.REPO}:{tip}:{args.seed or stamp[:8]}"
    rng = random.Random(seed)
    report = {"repo": common.REPO, "tip": tip, "window": len(shas), "seed": seed, "stamp": stamp,
              "alerts": [], "created": {}, "judge_calls": 0}
    queue = findings.load()
    findings.expire(queue)
    log(f"{common.REPO}: window {len(shas)} commits, tip {tip[:10]}, seed {seed}")

    # 2. quality components on every commit in the window
    regress = 0
    for sha in shas[:args.quality_limit]:
        for path, key, before, after in components.commit_regressions(sha):
            limit = before if key != "one_row_file" else 0
            item, new = findings.add(
                queue, kind="quality-regression",
                identity={"repo": common.REPO, "source": path, "rva": "", "name": ""},
                evidence=[{"commit": sha, "component": key, "before": before, "after": after}],
                severity="low", root_cause=f"component:{key}",
                acceptance=f"python3 tools/audit/components.py check {path} --max {key}={limit}",
                affected=[path])
            regress += new
    report["created"]["quality-regression"] = regress
    log(f"  quality: {regress} new regression items over {min(len(shas), args.quality_limit)} commits")

    # 3. sample natural rows
    picked, eligible = sampler.sample(shas, args.n, seed)
    report["eligible"] = eligible
    stream, private = [], {}
    for unit, why, row in picked:
        packet, priv = sampler.build_packet(unit, row, seed)
        stream.append((packet, "natural"))
        private[packet["id"]] = {**priv, "why": why, "row": row}
    log(f"  sampled {len(picked)} of {eligible} eligible commits")

    # 4. canaries + benign controls from random carriers at the tip
    if args.canaries:
        ledger = common.ledger_at()
        names = sorted({common.leaf_name(r["name"]) for r in ledger if r.get("status") == "matched"
                        and len(common.leaf_name(r["name"])) > 4 and not common.ADDRESS_NAME.search(r["name"])})
        shared = canaries.shared_class_names(ledger)
        carry, vendored = canaries.carriers(ledger, rng, 60)
        head = {"sha": "HEAD", "strata": ["control"]}
        for kind in canaries.DEFECTS:
            for row in carry:
                packet, _ = sampler.build_packet(head, row, seed + kind)
                bad = canaries.mutate(packet, kind, rng, names, rng.choice(shared) if shared else None)
                if bad:
                    stream.append((bad, kind))
                    carry.remove(row)
                    break
        for row in vendored[:args.benign]:
            packet, _ = sampler.build_packet(head, row, seed + "benign")
            stream.append((canaries.benign(packet, rng), "benign"))
    rng.shuffle(stream)
    for packet, label in stream:
        common.save_json(out_dir / "packets" / f"{packet['id']}.json", packet)
    labels = {p["id"]: label for p, label in stream}
    common.save_json(out_dir / "labels.json", labels)  # held out: never part of a packet
    log(f"  stream: {len(stream)} items ({sum(l == 'natural' for l in labels.values())} natural)")

    # 5. judges
    judged = []
    if not args.no_judges:
        judged = judge_stream(stream, args.judges, args.escalate, args.workers, log)
        report["judge_calls"] = sum(len(r["first"]) + bool(r.get("escalated")) for _, _, r in judged)
        common.save_json(out_dir / "panel.json", [r for _, _, r in judged])
        new = 0
        for packet, label, result in judged:
            if label != "natural" or result["decision"] not in ("agreed-defect", "escalated-defect", "single-defect"):
                continue
            if not set(result["classes"]) & panel.SEMANTIC:
                continue  # structural only: components.py already measures and queues it
            row = private[packet["id"]]["row"]
            recs = result["first"] + ([result["escalated"]] if result.get("escalated") else [])
            severity = min((SEVERITY_OF.get(c, "low") for c in result["classes"]),
                           key=lambda s: findings.SEVERITY[s], default="low")
            _, created = findings.add(
                queue, kind="judge-defect",
                identity={"repo": common.REPO, "rva": row["target_rva"], "size": row["target_size"],
                          "name": row["name"], "source": row["source"]},
                evidence=[{"run": stamp, "packet": packet["id"], "decision": result["decision"],
                           "independence": result["independence"],
                           "verdicts": [{"judge": r["judge"], "model": r["answering_model"],
                                         "verdict": r["verdict"]} for r in recs if r.get("counted")]}],
                severity=severity, root_cause="judge:" + "+".join(result["classes"]),
                acceptance=f"python3 tools/build.py {row['source']}",
                affected=[row["source"]])
            new += created
        report["created"]["judge-defect"] = new

        # 6. calibration
        hist = common.read_jsonl(HISTORY)
        report["metrics"] = {}
        for who, results in per_judge_results(judged).items():
            m = canaries.metrics(results)
            report["metrics"][who] = m
            past = [h["metrics"][who] for h in hist if who in h.get("metrics", {})]
            report["alerts"] += [f"{who}: {a}" for a in canaries.drift(m, past)]
        common.append_jsonl(HISTORY, {"stamp": stamp, "repo": common.REPO, "metrics": report["metrics"]})
        for alert in report["alerts"]:
            findings.add(queue, kind="canary-drift", identity={"repo": common.REPO, "source": "", "rva": ""},
                         evidence=[{"run": stamp, "alert": alert}], severity="medium",
                         root_cause=f"drift:{alert.split(':')[0]}:{alert.split(':')[1].strip()}",
                         acceptance="python3 tools/audit/nightly.py --no-judges --n 0")

    # 7. red team
    report["redteam"] = []
    if args.redteam and not args.no_judges:
        report["redteam"] = red_team(picked, seed, args, queue, log)
        report["created"]["gate-escape"] = sum(1 for r in report["redteam"] if r.get("new_escape"))

    findings.save(queue)
    report["queue"] = findings.summary(queue)
    common.save_json(out_dir / "run.json", report)
    (out_dir / "report.md").write_text(render(report), encoding="utf-8")
    common.save_json(LAST_RUN, {"tip": tip, "stamp": stamp})
    log(f"  report: {out_dir / 'report.md'}")
    return report


def red_team(picked, seed, args, queue, log):
    allow = panel.judges_by_id()
    proposer = allow[args.redteam_model]
    builds, out = 0, []
    rows = [(u, r) for u, why, r in picked if int(r.get("target_size") or 0) >= 16][:args.redteam]
    for unit, row in rows:
        packet, _ = sampler.build_packet({"sha": "HEAD", "strata": []}, row, seed + "rt")
        text = redteam.PROMPT.format(n=redteam.MAX_VARIANTS, retail=packet["retail"],
                                     source=packet["source_excerpt"], fence=sampler.nonce())
        got = panel.invoke(proposer, text)
        variants = redteam.parse_variants(got["reply"])
        log(f"  redteam {row['target_rva']} {row['source']}: {len(variants)} variants from "
            f"{got['answering_model']}")
        for variant in variants:
            if builds + 3 > redteam.MAX_BUILDS:
                break
            res = redteam.trial(row["source"], variant["edits"], symbol=row["name"], rva=row["target_rva"])
            builds += 3 if res["status"] not in ("invalid", "skipped") else (1 if res["status"] == "skipped" else 0)
            entry = {"rva": row["target_rva"], "source": row["source"], "class": variant["defect_class"],
                     "status": res["status"], "diff": res.get("diff"), "proposer": got["answering_model"]}
            if res["status"] == "escape":
                path, new = redteam.record_escape(row, variant, res, "HEAD")
                entry.update(fixture=str(path), new_escape=new)
                findings.add(queue, kind="gate-escape",
                             identity={"repo": common.REPO, "rva": row["target_rva"], "name": row["name"],
                                       "size": row["target_size"], "source": row["source"]},
                             evidence=[{"fixture": path.name, "diff": res["diff"], "diffexec": res.get("diffexec")}],
                             severity="high", root_cause=redteam.signature(variant["defect_class"], res["diff"]),
                             acceptance=f"python3 tools/audit/redteam.py replay {path.as_posix()}",
                             affected=[row["source"]])
            log(f"    {variant['defect_class']}: {res['status']} {res.get('diff') or res.get('why') or ''}")
            out.append(entry)
    return out


def render(r):
    lines = [f"# Nightly audit {r['repo']} {r['stamp']}", "",
             f"Tip `{r['tip'][:10]}`, window {r['window']} commits ({r.get('eligible', 0)} with matched rows), "
             f"seed `{r['seed']}`, {r['judge_calls']} judge calls.", "",
             "Advisory only: nothing here blocks a commit.", "", "## New queue items", ""]
    lines += [f"- {k}: {v}" for k, v in r["created"].items()] or ["- none"]
    lines += ["", "## Queue", "", "```", json.dumps(r.get("queue", {}), indent=1), "```"]
    if r.get("metrics"):
        lines += ["", "## Calibration (canaries and benign controls)", "",
                  "| judge | class | n | recall | recall(any) | precision |", "|---|---|---|---|---|---|"]
        for who, m in r["metrics"].items():
            for c in canaries.DEFECTS:
                if m[c]["n"] or m[c]["precision"] is not None:
                    lines.append(f"| {who} | {c} | {m[c]['n']} | {m[c]['recall']} | {m[c]['recall_any']} | "
                                 f"{m[c]['precision']} |")
            lines.append(f"| {who} | benign | {m['benign']['n']} | | fp {m['benign']['fp_rate']} | |")
    lines += ["", "## Alerts", ""] + ([f"- {a}" for a in r["alerts"]] or ["- none"])
    if r.get("redteam"):
        lines += ["", "## Red team", ""]
        lines += [f"- {e['rva']} {e['source']} {e['class']}: {e['status']} {e.get('diff') or ''}"
                  for e in r["redteam"]]
    return "\n".join(lines) + "\n"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--last", type=int)
    ap.add_argument("--since")
    ap.add_argument("--n", type=int, default=30)
    ap.add_argument("--seed")
    ap.add_argument("--judges", type=lambda s: s.split(","))
    ap.add_argument("--escalate", type=lambda s: s.split(","))
    ap.add_argument("--workers", type=int, default=3)
    ap.add_argument("--no-canaries", dest="canaries", action="store_false")
    ap.add_argument("--benign", type=int, default=3)
    ap.add_argument("--redteam", type=int, default=redteam.MAX_ROWS)
    ap.add_argument("--redteam-model", default="gpt-6.1-sol")
    ap.add_argument("--quality-limit", type=int, default=5000)
    ap.add_argument("--no-judges", action="store_true")
    args = ap.parse_args(argv)
    args.redteam = min(args.redteam, redteam.MAX_ROWS)
    log_path = common.STATE / "nightly.log"
    log_path.parent.mkdir(parents=True, exist_ok=True)

    def log(msg):
        line = f"{time.strftime('%H:%M:%S')} {msg}"
        print(line, flush=True)
        with log_path.open("a", encoding="utf-8") as fh:
            fh.write(line + "\n")
    try:
        run(args, log)
    except Exception:
        log(traceback.format_exc())
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
