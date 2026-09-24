#!/usr/bin/env python3
"""Measure banked stashes with the compiler, so the finish lane ranks on fact.

pick_finish.py ordered its queue by the `score=0.xx` a worker typed into the
stash header. docs and brief.py both say that number is an author estimate;
the compiler's answer is authoritative. This module compiles a stash through
tools/probe.py (about 2 s, dependency-cached), reads the measured distance
from retail, and keeps it in build/finish_measured.json only while the stash,
target, probe logic, toolchain and verified compiler dependencies remain the
same. Failed probes receive a short retry window.

  python tools/finish_measure.py [--min-score 0.9] [--limit N]   # fill the cache
  python tools/finish_measure.py --report                          # author score vs measured
  python tools/finish_measure.py --one RVA STASH                   # resolve a manual probe

quality: 1.0 for EXACT, else 1 - (differing bytes + 2 x size error) / retail
size, floored at 0; 0 when the stash no longer compiles. `first` is the offset
of the first divergence: deep is nearly done, +0 is a different function.
This is diagnostic ranking, never byte-match acceptance.
"""
import hashlib
import importlib.metadata
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
import time
import uuid

from portable_lock import lock, unlock

ROOT = Path(__file__).resolve().parents[1]
CACHE = ROOT / "build" / "finish_measured.json"
SIZE = re.compile(r"^size\s+ours=(\d+) retail=(\d+)", re.M)
DIFFS = re.compile(r"^diffs\s+(\d+) non-reloc byte\(s\); first at \+(\d+)", re.M)
VERSION = 2
RETRY_SECONDS = 1800
_ROW_CACHE = None
_IMAGE_ID = None


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


def save(updates):
    """Merge only newly measured entries under a dedicated short cache lock."""
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    with CACHE.with_suffix(".lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        try:
            latest = load()
            for key, entry in updates.items():
                path = Path(entry["path"])
                rva = int(key, 16)
                if current({key: entry}, rva, path) is not None:
                    prior = latest.get(key)
                    if (not entry.get("compiles") and prior and prior.get("compiles")
                            and current({key: prior}, rva, Path(prior.get("path", ""))) is not None):
                        continue  # concurrent transient failure cannot erase verified quality
                    latest[key] = entry
            tmp = CACHE.with_name(CACHE.name + "." + uuid.uuid4().hex + ".tmp")
            try:
                tmp.write_text(json.dumps(latest, indent=1, sort_keys=True), encoding="utf-8")
                os.replace(tmp, CACHE)
            finally:
                tmp.unlink(missing_ok=True)
            return latest
        finally:
            unlock(handle)


def _row_identity(rva):
    """Read one row from a ledger snapshot, refreshing after any file change."""
    global _ROW_CACHE
    import eligibility
    path = ROOT / "reverse/functions.csv"
    stat = path.stat()
    token = (str(path), stat.st_ino, stat.st_size, stat.st_mtime_ns)
    if _ROW_CACHE is None or _ROW_CACHE[0] != token:
        rows = {}
        for row in eligibility.load_rows(path):
            found = eligibility.rva_of(row)
            if found is not None:
                rows.setdefault(found, []).append(row)
        _ROW_CACHE = (token, rows)
    matches = _ROW_CACHE[1].get(rva, [])
    if len(matches) != 1:
        raise ValueError(f"0x{rva:08x} has {len(matches)} ledger rows; no unambiguous measurement")
    row = matches[0]
    return [row.get(field, "") for field in ("name", "target_rva", "target_size", "source", "status")]


def hypothesis(rva, path):
    """Fingerprint the measured question, excluding only author score/date."""
    global _IMAGE_ID
    import build
    image = build.EXE.stat()
    token = (str(build.EXE), image.st_ino, image.st_size, image.st_mtime_ns)
    if _IMAGE_ID != token:
        build.exe_image.cache_clear()
        _IMAGE_ID = token
    row = _row_identity(rva)
    size = int(row[2])
    # Read the extent from disk, not only exe_image's process-wide byte cache:
    # an image replaced during a long picker process must change this key.
    _, sections = build.exe_image()
    with build.EXE.open("rb") as image_file:
        image_file.seek(build.rva_to_file_offset(sections, rva))
        target = image_file.read(size)
    if len(target) != size:
        raise ValueError(f"short retail target for 0x{rva:08x}/{size}B")
    logic = []
    for name in ("finish_measure.py", "probe.py", "build.py", "experiment_store.py"):
        logic.append(hashlib.sha256((ROOT / "tools" / name).read_bytes()).hexdigest())
    try:
        capstone = importlib.metadata.version("capstone")
    except importlib.metadata.PackageNotFoundError:
        capstone = "missing"
    data = [str(Path(path).resolve()), body_hash(path), rva, row,
            hashlib.sha256(target).hexdigest(), logic,
            [sys.executable, sys.version, capstone,
             {key: os.environ.get(key, "") for key in ("PYTHONPATH", "PYTHONHOME",
                                                      "PYTHONNOUSERSITE", "WINEPREFIX")}]]
    return hashlib.sha256(json.dumps(data, sort_keys=True).encode()).hexdigest()


def measure(rva, path, timeout=180):
    symbol = symbol_of(path)
    if not symbol:
        return dict(compiles=False, quality=0.0, note="stash line 1 names no symbol")
    env = {k: v for k, v in os.environ.items() if k not in ("BFME_RUN_DIR", "BFME_RUN_ID")}  # measuring is not working on it
    def probe(name):
        return subprocess.run([sys.executable, str(ROOT / "tools/probe.py"), str(path), name, f"0x{rva:08X}"],
                              cwd=ROOT, capture_output=True, text=True, errors="replace", timeout=timeout, env=env)
    try:
        result = probe(symbol)
        text = result.stdout
        best = parse(text)
        # the object is cached after the first compile, so each retry is cheap
        for name in (object_symbols(path, best.get("retail") or ledger_size(rva)) or fallback_symbols(text, rva))                 if "NOT IN OBJECT" in text else []:
            other_result = probe(name)
            other = dict(parse(other_result.stdout), symbol=name)
            if other_result.returncode:
                other["compiles"] = False
            # the body is the symbol closest to retail's size, then the best quality
            if other["compiles"] and (not best["compiles"] or
                                      (abs(other["ours"] - other["retail"]), -other["quality"]) <
                                      (abs(best["ours"] - best["retail"]), -best["quality"])):
                best = other
        if not best["compiles"] and "NOT IN OBJECT" in text:
            best = dict(best, note="compiles, but no defined symbol measures against this body")
        elif result.returncode and best.get("symbol") is None:
            best = dict(compiles=False, quality=0.0,
                        note=(result.stderr or result.stdout or f"probe exit {result.returncode}")[-300:])
        elif not best["compiles"]:
            best = dict(best, note=(result.stderr or result.stdout or "probe produced no size")[-300:])
    except subprocess.TimeoutExpired:
        return dict(compiles=False, quality=0.0, note="probe timed out")
    return best


def current(cache, rva, path):
    """A qualified measurement of this exact current question, else None."""
    entry = cache.get(f"0x{rva:08x}")
    if not entry or entry.get("version") != VERSION:
        return None
    if entry.get("path") != str(Path(path).resolve()):
        return None
    if entry.get("fingerprint") != hypothesis(rva, path):
        return None
    if not entry.get("compiles"):
        return entry if time.time() - entry.get("at", 0) < RETRY_SECONDS else None
    if not entry.get("receipt"):
        return None
    import experiment_store
    return entry if entry.get("receipt") == experiment_store.validated_object_receipt(path) else None


def ensure(bodies, budget=8, cache=None):
    """bodies: [(rva:int, stash_path)]. Measure up to `budget` unmeasured ones
    (first come first served: pass them best author score first) and retry a
    bounded number of expired transient failures. A picker uses a small budget;
    the cache fills across picks, and this file can run the bulk pass."""
    cache = load() if cache is None else cache
    fresh, retry = [], []
    for rva, path in bodies:
        if current(cache, rva, path) is None:
            entry = cache.get(f"0x{rva:08x}", {})
            (retry if entry.get("version") == VERSION and entry.get("compiles") is False
             and entry.get("fingerprint") == hypothesis(rva, path) else fresh).append((rva, path))
    if fresh and retry and budget > 1:
        selected = fresh[:budget - 1] + retry[:1]
        selected += fresh[budget - 1:budget - len(selected)]
        selected += retry[1:1 + budget - len(selected)]
    else:
        selected = (fresh or retry)[:budget]
    updates = {}
    import experiment_store
    for rva, path in selected:
        before = hypothesis(rva, path)
        result = measure(rva, path)
        if hypothesis(rva, path) != before:
            continue  # changed while probing: never publish the old answer
        receipt = experiment_store.validated_object_receipt(path) if result.get("compiles") else None
        if result.get("compiles") and receipt is None:
            continue  # a successful probe without a reusable object is not cache proof
        key = f"0x{rva:08x}"
        updates[key] = dict(result, version=VERSION, fingerprint=before,
                            hash=body_hash(path), receipt=receipt,
                            path=str(Path(path).resolve()), at=time.time())
        cache[key] = updates[key]
    if updates:
        cache.update(save(updates))
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


def measure_one(rva, path):
    """Print a current diagnostic probe command for one banked body.

    A compiled candidate symbol is not proof of identity or byte acceptance.
    Do not print a command if the source, target, tool logic, or compiler object
    changed while measuring.
    """
    import experiment_store
    path = Path(path).resolve()
    try:
        before = hypothesis(rva, path)
        result = measure(rva, path)
        after = hypothesis(rva, path)
    except (OSError, ValueError) as error:
        print(f"finish_measure: {error}", file=sys.stderr)
        return 1
    if before != after:
        print("finish_measure: inputs changed during measurement; run again", file=sys.stderr)
        return 1
    if not result.get("compiles"):
        print(f"finish_measure: probe failed: {result.get('note', 'no measurable body')}", file=sys.stderr)
        return 1
    if experiment_store.validated_object_receipt(path) is None:
        print("finish_measure: compiled object or dependencies are no longer current; run again",
              file=sys.stderr)
        return 1
    symbol = result.get("symbol") or symbol_of(path)
    display_path = path.relative_to(ROOT).as_posix() if path.is_relative_to(ROOT) else str(path)
    command = " ".join(shlex.quote(part) for part in (
        Path(sys.executable).as_posix(), "tools/probe.py", display_path, symbol, f"0x{rva:08X}"))
    print(f"candidate object symbol  {symbol}")
    print(f"size ours={result['ours']} retail={result['retail']} "
          f"diffs={result['diffs']} first=+{result['first']} quality={result['quality']:.4f}")
    print(f"probe: {command}")
    print("Diagnostic only: prove identity and pass the strict byte-match gate before landing.")
    return 0


def main(argv=None):
    sys.path.insert(0, str(ROOT / "tools"))
    import eligibility
    args = list(sys.argv[1:] if argv is None else argv)
    if "--one" in args:
        if len(args) != 3 or args[0] != "--one":
            print("usage: finish_measure.py --one RVA STASH", file=sys.stderr)
            return 2
        try:
            rva = int(args[1], 0)
        except ValueError:
            print(f"finish_measure: invalid RVA {args[1]!r}", file=sys.stderr)
            return 2
        return measure_one(rva, args[2])
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
    raise SystemExit(main())
