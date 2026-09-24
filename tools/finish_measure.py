#!/usr/bin/env python3
"""Measure banked stashes with the compiler, so the finish lane ranks on fact.

pick_finish.py ordered its queue by the `score=0.xx` a worker typed into the
stash header. docs and brief.py both say that number is an author estimate;
the compiler's answer is authoritative. This module compiles a stash through
tools/probe.py (about 2 s, dependency-cached), reads the measured distance
from retail, and keeps it in build/finish_measured.json keyed by the stash
body hash, so an unchanged stash is never measured twice.

  python tools/finish_measure.py [--min-score 0.9] [--limit N]   # fill the cache
  python tools/finish_measure.py --report                          # author score vs measured

quality: 1.0 for EXACT, else 1 - (differing bytes + 2 x size error) / retail
size, floored at 0; 0 when the stash no longer compiles. `first` is the offset
of the first divergence: deep is nearly done, +0 is a different function.
"""
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
CACHE = ROOT / "build" / "finish_measured.json"
SIZE = re.compile(r"^size\s+ours=(\d+) retail=(\d+)", re.M)
DIFFS = re.compile(r"^diffs\s+(\d+) non-reloc byte\(s\); first at \+(\d+)", re.M)


def body_hash(path):
    # Line 1 selects the symbol probe.py measures. Only line 2's author score
    # and date are metadata; changing the symbol is a new hypothesis.
    lines = Path(path).read_bytes().splitlines()
    return hashlib.sha256(b"\n".join(lines[:1] + lines[2:])).hexdigest()


def symbol_of(path):
    first = Path(path).read_text(encoding="utf-8", errors="replace").splitlines()[:1]
    return first[0][2:].strip() if first and first[0].startswith("//") else ""


def parse(text):
    """Probe output -> measurement dict. Pure, so it can be tested without a compiler."""
    size = SIZE.search(text)
    if not size:
        return dict(compiles=False, quality=0.0)
    ours, retail = int(size.group(1)), int(size.group(2))
    if "result   EXACT" in text:
        return dict(compiles=True, ours=ours, retail=retail, diffs=0, first=retail, quality=1.0)
    diffs = DIFFS.search(text)
    count, first = (int(diffs.group(1)), int(diffs.group(2))) if diffs else (retail, 0)
    distance = count + 2 * abs(ours - retail)
    return dict(compiles=True, ours=ours, retail=retail, diffs=count, first=first,
                quality=round(max(0.0, 1.0 - distance / max(retail, 1)), 4))


NEAREST = re.compile(r"^\s{6,}(\S+)\s*$", re.M)


def fallback_symbols(text, rva, limit=16):
    """A stash header usually names the LEDGER symbol (`?d_00689170@@YAXXZ`), while
    the C++ in it defines the real one. probe.py then says NOT IN OBJECT and lists
    what the object does define. Measuring that as "does not compile" ranked 150
    good stashes last. Candidates: the address-tagged symbol first, then the rest;
    never an EH handler or a compiler-generated helper."""
    if "NOT IN OBJECT" not in text:
        return []
    block = text.split("nearest", 1)[-1].split("hint", 1)[0]
    names = [n for n in NEAREST.findall(block) if not n.startswith(("__", "$", "??_"))]
    tag = f"{rva:08x}"
    # a reconstruction with helper templates defines many address-tagged symbols
    # (0x003E8E10 had eleven); plain members and functions before templates
    names.sort(key=lambda n: (tag not in n.lower(), n.startswith("??$"), n.startswith(("??0", "??1"))))
    return names[:limit]


def ledger_size(rva):
    sys.path.insert(0, str(ROOT / "tools"))
    import probe
    try:
        return probe.ledger_size(rva) or 0
    except Exception:  # noqa: BLE001
        return 0


def object_symbols(path, retail_size, limit=3):
    """probe.py lists only the few names nearest the one asked for; a body with
    helper templates (0x003E8E10 defines eleven tagged symbols) hides the real
    one. Read the cached object instead: the function symbols whose code size
    is closest to retail's."""
    try:
        sys.path.insert(0, str(ROOT / "tools"))
        import build
        from experiment_store import compile_cached
        obj, _ = compile_cached(Path(path).resolve())
        sized = []
        for symbol in build.read_object_symbols(Path(obj).read_bytes()):
            name = symbol["name"]
            if symbol["section"] <= 0 or not name.startswith("?") or name.startswith(("??_", "?$S")):
                continue
            try:
                sized.append((abs(len(build.read_object_symbol_bytes(obj, name)[0]) - retail_size), name))
            except Exception:  # noqa: BLE001  (data symbols, labels)
                continue
        return [name for _, name in sorted(sized)[:limit]]
    except Exception:  # noqa: BLE001  (no compiler on this host: fall back to probe's list)
        return []


def load():
    try:
        return json.loads(CACHE.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return {}


def save(cache):
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    tmp = CACHE.with_suffix(".tmp%d" % os.getpid())
    tmp.write_text(json.dumps(cache, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, CACHE)


def measure(rva, path, timeout=180):
    symbol = symbol_of(path)
    if not symbol:
        return dict(compiles=False, quality=0.0, note="stash line 1 names no symbol")
    env = {k: v for k, v in os.environ.items() if k not in ("BFME_RUN_DIR", "BFME_RUN_ID")}  # measuring is not working on it
    def probe(name):
        return subprocess.run([sys.executable, str(ROOT / "tools/probe.py"), str(path), name, f"0x{rva:08X}"],
                              cwd=ROOT, capture_output=True, text=True, errors="replace", timeout=timeout, env=env).stdout
    try:
        text = probe(symbol)
        best = parse(text)
        # the object is cached after the first compile, so each retry is cheap
        for name in (object_symbols(path, best.get("retail") or ledger_size(rva)) or fallback_symbols(text, rva))                 if "NOT IN OBJECT" in text else []:
            other = dict(parse(probe(name)), symbol=name)
            # the body is the symbol closest to retail's size, then the best quality
            if other["compiles"] and (not best["compiles"] or
                                      (abs(other["ours"] - other["retail"]), -other["quality"]) <
                                      (abs(best["ours"] - best["retail"]), -best["quality"])):
                best = other
        if not best["compiles"] and "NOT IN OBJECT" in text:
            best = dict(best, note="compiles, but no defined symbol measures against this body")
    except subprocess.TimeoutExpired:
        return dict(compiles=False, quality=0.0, note="probe timed out")
    return best


def current(cache, rva, path):
    """The cached measurement of this exact stash body, else None."""
    entry = cache.get(f"0x{rva:08x}")
    try:
        return entry if entry and entry.get("hash") == body_hash(path) else None
    except OSError:
        return None


def ensure(bodies, budget=8, cache=None):
    """bodies: [(rva:int, stash_path)]. Measure up to `budget` unmeasured ones
    (first come first served: pass them best author score first) and return
    the cache. A picker calls this with a small budget, so the cache fills over
    a few picks; run this file for the bulk pass."""
    cache = load() if cache is None else cache
    changed = 0
    for rva, path in bodies:
        if changed >= budget:
            break
        if current(cache, rva, path) is None:
            cache[f"0x{rva:08x}"] = dict(measure(rva, path), hash=body_hash(path), at=time.time())
            changed += 1
    if changed:
        save(cache)
    return cache


def rank_key(cache, rva, path, score, size):
    """Sort key: positive measured, unmeasured, valid zero, failed probe.

    A measurement's mere existence cannot make a broken or unrelated body
    outrank a viable, unmeasured hypothesis.
    """
    entry = current(cache, rva, path)
    if entry is None:
        return (1, -score, -size)
    quality = entry.get("quality", 0.0)
    if entry.get("compiles") and quality > 0:
        return (0, -quality, -entry.get("first", 0) / max(entry.get("retail", 1), 1), -size)
    if entry.get("compiles"):
        return (2, -score, -size)
    return (3, -score, -size)


def select(candidates, cache, count):
    """Choose ranked (author score, size, RVA text, stash) tuples.

    A four-target finish brief reserves one place for a previously unmeasured
    candidate when measured positives would otherwise fill every place.
    """
    ordered = sorted(candidates, key=lambda c: rank_key(
        cache, int(c[2], 16), c[3], c[0], c[1]))
    chosen = ordered[:count]
    if count >= 4 and chosen and all(current(cache, int(c[2], 16), c[3]) is not None
                                     for c in chosen):
        fresh = next((c for c in ordered[count:]
                      if current(cache, int(c[2], 16), c[3]) is None), None)
        if fresh is not None:
            chosen[-1] = fresh
    return chosen


def main():
    sys.path.insert(0, str(ROOT / "tools"))
    import eligibility
    args = sys.argv[1:]
    floor = float(args[args.index("--min-score") + 1]) if "--min-score" in args else 0.9
    limit = int(args[args.index("--limit") + 1]) if "--limit" in args else 10 ** 6
    bodies = [(eligibility.rva_of(row), path, score) for row, path, score in eligibility.finish_bodies(floor)]
    if "--report" in args:
        cache = load()
        rows = [(score, current(cache, rva, path), rva) for rva, path, score in bodies]
        measured = [(s, e, r) for s, e, r in rows if e]
        print(f"{len(measured)} of {len(rows)} finish stashes measured")
        broken = sum(1 for _, e, _ in measured if not e["compiles"])
        exact = sum(1 for _, e, _ in measured if e["quality"] == 1.0)
        over = sum(1 for s, e, _ in measured if s - e["quality"] > 0.2)
        print(f"  no longer compile: {broken}   EXACT already: {exact}   author score > measured by 0.2+: {over}")
        for s, e, r in sorted(measured, key=lambda t: t[0] - t[1]["quality"], reverse=True)[:15]:
            print(f"  0x{r:08X} author {s:.3f} measured {e['quality']:.3f} diffs={e.get('diffs', '-')} first=+{e.get('first', '-')}")
        return
    cache = ensure([(rva, path) for rva, path, _ in bodies], budget=limit)
    print(f"finish_measure: {sum(1 for rva, path, _ in bodies if current(cache, rva, path))} of {len(bodies)} measured")


if __name__ == "__main__":
    main()
