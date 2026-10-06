#!/usr/bin/env python3
"""The audit's queue: findings with a lifecycle, so nightly reviews do not grow a backlog.

Every finding carries
  identity     stable retail identity: repo, rva, size, ledger name, source
  kind         judge-defect | quality-regression | gate-escape | canary-drift
  evidence     what produced it (panel verdicts with answering models, component
               values, harness output) - references, not prose
  severity     high | medium | low
  root_cause   signature used to deduplicate: the same cause at the same identity
               is ONE item whose `seen` count grows
  affected     dependency set to re-certify (the unit, plus units including a
               touched header)
  acceptance   the command that must exit 0 for the item to close as fixed;
               it reruns the original reproducer
  lease        holder + expiry; an expired lease returns the item to `open`
  retries      remaining budget; a failed acceptance spends one, at zero the
               item is terminal `exhausted` and goes to a human
  disposition  open | leased | fixed | exhausted | false-positive | wont-fix |
               duplicate (terminal: all but open/leased)

Judge-only findings are advisory (they never block anything); `gate-escape`
items are reproduced by the deterministic harness before they are created.

  python3 tools/audit/findings.py list [--all] [--kind K]
  python3 tools/audit/findings.py lease --holder NAME [--kind K] [--hours 4]
  python3 tools/audit/findings.py release ID
  python3 tools/audit/findings.py complete ID         # runs the acceptance command
  python3 tools/audit/findings.py dispose ID --as false-positive|wont-fix|duplicate --reason TEXT
  python3 tools/audit/findings.py export               # TSV for next_work / repair_queue
"""
import argparse
import shlex
import subprocess
import sys
import time

import common

QUEUE = common.STATE / "queue.json"
OPEN = ("open", "leased")
TERMINAL = ("fixed", "exhausted", "false-positive", "wont-fix", "duplicate")
RETRIES = 3
SEVERITY = {"high": 0, "medium": 1, "low": 2}


def now():
    return int(time.time())


def load(path=None):
    return common.load_json(path or QUEUE, {"items": {}})


def save(queue, path=None):
    common.save_json(path or QUEUE, queue)


def expire(queue, t=None):
    t = t or now()
    for item in queue["items"].values():
        lease = item.get("lease")
        if item["disposition"] == "leased" and lease and lease["expires"] <= t:
            item["disposition"], item["lease"] = "open", None
            item["history"].append([t, "lease-expired", lease["holder"]])


def add(queue, *, kind, identity, evidence, severity, root_cause, acceptance, affected=(), t=None):
    """Insert or merge. Returns (item, created)."""
    t = t or now()
    key = common.digest(common.REPO, kind, identity.get("rva"), identity.get("source"), root_cause)
    item = queue["items"].get(key)
    if item:
        item["seen"] += 1
        item["evidence"] = (item["evidence"] + list(evidence))[-12:]
        if SEVERITY[severity] < SEVERITY[item["severity"]]:
            item["severity"] = severity
        if item["disposition"] in ("fixed",):  # it came back: a regression of a repair
            item["disposition"], item["retries"] = "open", RETRIES
            item["history"].append([t, "recurred", ""])
        item["updated"] = t
        return item, False
    item = {"id": key, "kind": kind, "identity": dict(identity), "evidence": list(evidence),
            "severity": severity, "root_cause": root_cause, "affected": sorted(set(affected)),
            "acceptance": acceptance, "lease": None, "retries": RETRIES, "disposition": "open",
            "seen": 1, "created": t, "updated": t, "history": [[t, "created", ""]]}
    queue["items"][key] = item
    return item, True


def lease(queue, holder, hours=4.0, kind=None, t=None):
    """Hand out the most severe, oldest open item."""
    t = t or now()
    expire(queue, t)
    ready = [i for i in queue["items"].values() if i["disposition"] == "open" and (not kind or i["kind"] == kind)]
    if not ready:
        return None
    item = min(ready, key=lambda i: (SEVERITY[i["severity"]], i["created"]))
    item["disposition"] = "leased"
    item["lease"] = {"holder": holder, "expires": t + int(hours * 3600)}
    item["history"].append([t, "leased", holder])
    return item


def release(queue, key, t=None):
    item = queue["items"][key]
    if item["disposition"] == "leased":
        item["disposition"], item["lease"] = "open", None
        item["history"].append([t or now(), "released", ""])
    return item


def argv_of(cmd):
    """Acceptance commands are written `python3 tools/...`; run them with this interpreter."""
    argv = shlex.split(cmd)
    if argv and argv[0] in ("python3", "python", "py"):
        argv[0] = sys.executable
    return argv


def complete(queue, key, run=None, t=None):
    """Run the acceptance command: exit 0 -> fixed; else spend one retry."""
    t = t or now()
    item = queue["items"][key]
    if item["disposition"] in TERMINAL:
        return item
    run = run or (lambda cmd: subprocess.run(argv_of(cmd), cwd=common.ROOT).returncode)
    code = run(item["acceptance"])
    if code == 0:
        item["disposition"] = "fixed"
        item["history"].append([t, "fixed", item["acceptance"]])
    else:
        item["retries"] -= 1
        item["disposition"] = "exhausted" if item["retries"] <= 0 else "open"
        item["history"].append([t, f"acceptance-failed exit {code}", ""])
    item["lease"] = None
    item["updated"] = t
    return item


def dispose(queue, key, disposition, reason, t=None):
    if disposition not in TERMINAL or disposition == "fixed":
        raise ValueError(f"{disposition}: not a manual terminal disposition")
    item = queue["items"][key]
    item["disposition"], item["lease"] = disposition, None
    item["history"].append([t or now(), disposition, reason])
    return item


def summary(queue):
    out = {}
    for item in queue["items"].values():
        out.setdefault(item["kind"], {}).setdefault(item["disposition"], 0)
        out[item["kind"]][item["disposition"]] += 1
    return out


def export_lines(queue):
    """One TSV line per open item, the shape tools/repair_queue.py tiers use: kind, source, rva, test."""
    lines = []
    for item in sorted(queue["items"].values(), key=lambda i: (SEVERITY[i["severity"]], i["created"])):
        if item["disposition"] == "open":
            ident = item["identity"]
            lines.append("\t".join([f"audit-{item['kind']}", ident.get("source", ""), ident.get("rva", ""),
                                    item["severity"], item["id"], item["acceptance"]]))
    return lines


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    ls = sub.add_parser("list")
    ls.add_argument("--all", action="store_true")
    ls.add_argument("--kind")
    le = sub.add_parser("lease")
    le.add_argument("--holder", required=True)
    le.add_argument("--kind")
    le.add_argument("--hours", type=float, default=4.0)
    sub.add_parser("release").add_argument("id")
    sub.add_parser("complete").add_argument("id")
    dp = sub.add_parser("dispose")
    dp.add_argument("id")
    dp.add_argument("--as", dest="disposition", required=True)
    dp.add_argument("--reason", required=True)
    sub.add_parser("export")
    args = ap.parse_args(argv)
    queue = load()
    expire(queue)
    if args.cmd == "list":
        for item in queue["items"].values():
            if (args.all or item["disposition"] in OPEN) and (not args.kind or item["kind"] == args.kind):
                ident = item["identity"]
                print(f"{item['id']} {item['disposition']:9} {item['severity']:6} {item['kind']:18} "
                      f"{ident.get('rva', ''):10} {ident.get('source', '')} :: {item['root_cause']}")
        print(summary(queue))
    elif args.cmd == "lease":
        item = lease(queue, args.holder, args.hours, args.kind)
        print("nothing open" if item is None else
              f"{item['id']} {item['identity']}\n  acceptance: {item['acceptance']}")
    elif args.cmd == "release":
        release(queue, args.id)
    elif args.cmd == "complete":
        item = complete(queue, args.id)
        print(f"{item['id']}: {item['disposition']} (retries left {item['retries']})")
    elif args.cmd == "dispose":
        dispose(queue, args.id, args.disposition, args.reason)
    else:
        lines = export_lines(queue)
        path = common.STATE / "repair_items.tsv"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("".join(line + "\n" for line in lines), encoding="utf-8")
        print(f"{len(lines)} open items -> {path}")
    save(queue)
    return 0


if __name__ == "__main__":
    sys.exit(main())
