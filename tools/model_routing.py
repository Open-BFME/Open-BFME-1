#!/usr/bin/env python3
"""Which models may take which task class, from measured outcomes.

Every attempt row in re_attempts.log carries the agent's `model=` and `t=`
fields. This turns them into a success rate per (task class, model) and routes
work with two rules from tools/model_routing.json:

  * a class lists the models allowed to take it at all ("*" = any model);
  * a model whose measured success rate in a class falls below that class's
    floor, over at least `min_attempts` decided attempts, stops being routed
    there. The rate used is the Wilson lower bound, so a lucky streak on few
    attempts never clears a floor and a short dry spell never trips one.

Task classes are retail size bands: the long tail (very large bodies, maths,
macro-heavy code) sits in the top band, which only the strongest models and
tools/variant_search.py are routed to. Judges are a separate, protected list:
judge_allowed() answers from tools/judges.json through tools/judges.py, the
repo's one judge runner (decision record, pillar 5); nothing here can add a
judge, and a missing or malformed list allows none.

`model=` in the log is self-declared by the agent. It is good enough to stop
routing work to a model that does not land it; it is never evidence for a
verdict. Runner-recorded models (variant_search.py) are written as `runner=`.

Usage:
  python3 tools/model_routing.py report [--json]
  python3 tools/model_routing.py route --size 420
  python3 tools/model_routing.py route --class large
"""
import argparse
import collections
import json
import math
import re
import statistics
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REVERSE = (ROOT / "targets" / "game" / "reverse"
           if (ROOT / "targets" / "game" / "reverse").is_dir() else ROOT / "reverse")
LOG = REVERSE / "re_attempts.log"
CONFIG = ROOT / "tools" / "model_routing.json"
JUDGES = ROOT / "tools" / "judges.json"
FIELD = re.compile(r"(?:^|\s)(model|runner|t)=(\S+)")


def load_config(path=CONFIG):
    return json.loads(Path(path).read_text(encoding="utf-8"))


def canonical(model, config):
    name = re.split(r"[;,]", model.strip())[0].rstrip(".:)").lower()
    return config.get("aliases", {}).get(name, name)


def task_class(size, config):
    for band in config["classes"]:
        if band.get("max_size") is None or size <= band["max_size"]:
            return band["name"]
    return config["classes"][-1]["name"]


def outcomes(log=LOG, config=None):
    """[(class, model, success: bool, t: float|None)] for decided attempts.

    Later rows win nothing here: every decided attempt is one trial, so a body
    blocked twice and landed on the third try counts 1 of 3 for those models."""
    config = config or load_config()
    success, failure = set(config["success"]), set(config["failure"])
    out = []
    path = Path(log)
    if not path.exists():
        return out
    with path.open(encoding="utf-8", errors="replace") as handle:
        for line in handle:
            fields = line.rstrip("\r\n").split("\t")
            if len(fields) < 5 or fields[3] not in success | failure:
                continue
            try:
                size = int(fields[2])
            except ValueError:
                continue
            found = dict(FIELD.findall(fields[4]))
            model = found.get("runner") or found.get("model")
            if not model:
                continue
            try:
                t = float(found["t"]) if "t" in found else None
            except ValueError:
                t = None
            out.append((task_class(size, config), canonical(model, config),
                        fields[3] in success, t))
    return out


def wilson_lower(wins, n, z=1.96):
    if n == 0:
        return 0.0
    p = wins / n
    centre = p + z * z / (2 * n)
    spread = z * math.sqrt(p * (1 - p) / n + z * z / (4 * n * n))
    return (centre - spread) / (1 + z * z / n)


def table(rows):
    """{(class, model): {"n", "wins", "rate", "lower", "median_t"}}."""
    grouped = collections.defaultdict(list)
    for cls, model, ok, t in rows:
        grouped[(cls, model)].append((ok, t))
    out = {}
    for key, items in grouped.items():
        n, wins = len(items), sum(ok for ok, _ in items)
        times = [t for ok, t in items if ok and t is not None]
        out[key] = {"n": n, "wins": wins, "rate": round(wins / n, 4),
                    "lower": round(wilson_lower(wins, n), 4),
                    "median_t": statistics.median(times) if times else None}
    return out


def route(cls, stats, config):
    """(routed models best first, under-sampled trial models, {model: why cut}).

    Routed: measured on >= min_attempts decided attempts in this class and above
    its floor, or listed in `cost` (known models) and not yet cut. Trial: seen,
    allowed, but too few attempts to judge -- give them work sparingly until
    they are measured. Cut: measured and below the floor."""
    band = next(b for b in config["classes"] if b["name"] == cls)
    allowed = band.get("models", ["*"])
    floor, minimum = band.get("floor", config["floor"]), config["min_attempts"]
    seen = sorted({m for (c, m) in stats if c == cls})
    pool = seen if "*" in allowed else [canonical(m, config) for m in allowed]
    known = set(config.get("cost", {}))
    if "*" in allowed:
        pool = sorted(set(pool) | known)
    keep, trial, cut = [], [], {}
    for model in pool:
        s = stats.get((cls, model))
        if s and s["n"] >= minimum and s["lower"] < floor:
            cut[model] = (f"{s['wins']}/{s['n']} landed (lower bound {s['lower']:.3f} "
                          f"< floor {floor})")
        elif (s and s["n"] >= minimum) or model in known or "*" not in allowed:
            keep.append(model)
        else:
            trial.append(model)
    cost = config.get("cost", {})
    if band.get("prefer") == "cheap":
        keep.sort(key=lambda m: (cost.get(m, 1), -(stats.get((cls, m)) or {}).get("lower", 0), m))
    else:
        keep.sort(key=lambda m: (-(stats.get((cls, m)) or {}).get("lower", 0), m))
    return keep, trial, cut


def judge_allowed(model, path=JUDGES):
    """True only for models on the protected judge list (tools/judges.py decides)."""
    sys.path.insert(0, str(ROOT / "tools"))
    import judges
    return judges.allowed(model, path)


def report(stats, config, min_n=1):
    lines = []
    for band in config["classes"]:
        cls = band["name"]
        keep, trial, cut = route(cls, stats, config)
        lines.append(f"== {cls} (size <= {band.get('max_size') or 'any'}; floor "
                     f"{band.get('floor', config['floor'])}; prefer {band.get('prefer', 'strong')})")
        rows = sorted(((m, s) for (c, m), s in stats.items() if c == cls and s["n"] >= min_n),
                      key=lambda ms: (-ms[1]["n"], ms[0]))
        for model, s in rows:
            mark = ("CUT" if model in cut else "ok" if model in keep
                    else "trial" if model in trial else "not allowed")
            t = "" if s["median_t"] is None else f"  median t={s['median_t']:g}"
            lines.append(f"  {model:<28} {s['wins']:>6}/{s['n']:<6} {100 * s['rate']:5.1f}%  "
                         f"lower {100 * s['lower']:5.1f}%  {mark}{t}")
        lines.append(f"  route: {', '.join(keep) or '(none)'}; {len(trial)} under-sampled "
                     f"model(s) on trial; {len(cut)} cut")
    return "\n".join(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=("report", "route", "judge"))
    ap.add_argument("--log", default=str(LOG))
    ap.add_argument("--config", default=str(CONFIG))
    ap.add_argument("--size", type=int)
    ap.add_argument("--class", dest="cls")
    ap.add_argument("--model")
    ap.add_argument("--min-n", type=int, default=20, help="report rows with at least this many")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args(argv)
    config = load_config(args.config)
    if args.cmd == "judge":
        ok = judge_allowed(args.model or "")
        print("allowed" if ok else "not a judge")
        return 0 if ok else 1
    stats = table(outcomes(args.log, config))
    if args.cmd == "report":
        if args.json:
            print(json.dumps({f"{c}\t{m}": s for (c, m), s in sorted(stats.items())}, indent=2))
        else:
            print(report(stats, config, args.min_n))
        return 0
    cls = args.cls or (task_class(args.size, config) if args.size is not None else None)
    if cls is None:
        ap.error("route needs --size or --class")
    keep, trial, cut = route(cls, stats, config)
    print(json.dumps({"class": cls, "models": keep, "trial": trial, "cut": cut}, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
