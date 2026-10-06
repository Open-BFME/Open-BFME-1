#!/usr/bin/env python3
"""Parallel, model-proposed variant search for one near-miss function.

Blind source permutation (tools/permute.py) closes register and stack details,
but spent on a body whose control flow or types are still wrong it loops for
hours ("doom loops and token burn" in other AI decomp projects). This puts a
strong model in the loop instead: each round it sees the best source so far and
an instruction-level diff against retail, and proposes N (8-16) targeted
rewrites. All N compile in parallel, each is scored with the gate's own path
(build.compile_function: relocations resolved against the ledger's symbol map,
byte equality = exact), the best is kept, and rounds are capped. Only when the
remaining diff is register allocation alone -- same instructions, operands
equal once registers are masked -- does a blind permutation phase run, under
its own trial cap.

The model is called by this runner, never by the agent, and the result records
which model answered (`runner=<model>` in the attempt note), so routing and
audits can trust it. The call goes through tools/judge_call.py when the
publisher's judge layer is installed, else through a command template from
tools/model_routing.json (`commands`), with the prompt on stdin.

Nothing here lands a row. A win is written to build/variant_search/<rva>/win.cpp
for tools/add_match.py and the normal gates.

Usage:
  python3 tools/variant_search.py SOURCE SYMBOL RVA SIZE [--n 12] [--rounds 4]
      [--model M] [--command "codex exec --model {model} -"] [--jobs 12]
      [--permute-trials 300]
"""
import argparse
import concurrent.futures
import difflib
import hashlib
import json
import random
import re
import shlex
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
OUT = ROOT / "build" / "variant_search"
FORBIDDEN = re.compile(r"\b(?:__asm|_asm|__emit|_emit|naked)\b|#\s*pragma\s+optimize"
                       r"|/alternatename")
FENCE = re.compile(r"```(?:cpp|c\+\+|c)?[ \t]*\n(.*?)```", re.S)
REGISTER = re.compile(r"\b(?:e?[abcd]x|[abcd][lh]|e?[sd]i|e?bp)\b")
_DISASM = None


# ----------------------------------------------------------------- diff

def instructions(blob):
    global _DISASM
    if _DISASM is None:
        import capstone
        _DISASM = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return [(m, o) for _, _, m, o in _DISASM.disasm_lite(bytes(blob), 0)]


def fitness(compiled, target):
    """0..1 closeness: mnemonic alignment, then full instructions, then bytes
    (the same weighting as tools/permute.py, so scores are comparable)."""
    ratio = lambda a, b: difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()
    ours, theirs = instructions(compiled), instructions(target)
    if not ours or not theirs:
        return ratio(compiled, target)
    return (0.5 * ratio([m for m, _ in ours], [m for m, _ in theirs])
            + 0.3 * ratio(ours, theirs) + 0.2 * ratio(compiled, target))


def classify(compiled, target):
    """'exact', 'regalloc' (only register choice differs), or 'structural'."""
    if compiled == target:
        return "exact"
    ours, theirs = instructions(compiled), instructions(target)
    if len(ours) != len(theirs) or not ours:
        return "structural"
    mask = lambda op: REGISTER.sub("R", op)
    for (m1, o1), (m2, o2) in zip(ours, theirs):
        if m1 != m2 or mask(o1) != mask(o2):
            return "structural"
    return "regalloc"


def diff_text(compiled, target, limit=60):
    """A compact side-by-side of the differing instruction runs, for the prompt."""
    ours = [f"{m} {o}".strip() for m, o in instructions(compiled)]
    theirs = [f"{m} {o}".strip() for m, o in instructions(target)]
    lines = []
    matcher = difflib.SequenceMatcher(None, ours, theirs, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal":
            continue
        lines.append(f"@ ours[{i1}:{i2}] retail[{j1}:{j2}] {tag}")
        lines += [f"-  {x}" for x in ours[i1:i2]] + [f"+  {x}" for x in theirs[j1:j2]]
        if len(lines) >= limit:
            lines.append("... (truncated)")
            break
    return "\n".join(lines) or "(no instruction differences; bytes differ in operands)"


# ----------------------------------------------------------------- scoring

class Scorer:
    """Compile one candidate in a private directory and score it the gate's way."""

    def __init__(self, symbol, rva, size, workdir, symbol_map=None):
        import build
        self.build = build
        self.symbol, self.rva, self.size = symbol, rva, size
        self.dir = Path(workdir)
        self.dir.mkdir(parents=True, exist_ok=True)
        self.symbol_map = symbol_map if symbol_map is not None else build.load_symbol_map()
        self.n = 0

    def __call__(self, text):
        """{"fitness", "exact", "class", "compiled", "target"}; fitness -1 if it fails."""
        self.n += 1
        source = self.dir / f"c{self.n}.cpp"
        output = source.with_suffix(".obj")
        source.write_text(text, encoding="latin-1", errors="replace")
        try:
            ok = self.build.try_compile_source(source, output)[0]
            if not ok:
                return {"fitness": -1.0, "exact": False, "class": "compile-error"}
            row = {"name": self.symbol, "target_rva": f"0x{self.rva:08X}",
                   "target_size": str(self.size),
                   "source": source.relative_to(ROOT).as_posix(), "notes": ""}
            got = self.build.compile_function(row, self.symbol_map, output)
        except (SystemExit, Exception) as error:
            return {"fitness": -1.0, "exact": False, "class": f"error: {str(error)[:120]}"}
        compiled, target = got["bytes"], got["target"]
        exact = compiled == target and not got["unresolved"]
        return {"fitness": 1.0 if exact else round(fitness(compiled, target), 5),
                "exact": exact, "class": "exact" if exact else classify(compiled, target),
                "compiled": compiled, "target": target}


def score_all(texts, make_scorer, jobs):
    """Score candidates in parallel, one scorer (and directory) per worker slot."""
    scorers = [make_scorer(i) for i in range(max(1, min(jobs, len(texts))))]
    results = [None] * len(texts)
    with concurrent.futures.ThreadPoolExecutor(max_workers=len(scorers)) as pool:
        futures = {}
        for i, text in enumerate(texts):
            futures[pool.submit(scorers[i % len(scorers)], text)] = i
        for future in concurrent.futures.as_completed(futures):
            results[futures[future]] = future.result()
    return results


# ----------------------------------------------------------------- model

def model_command(model, template=None):
    if template is None:
        import model_routing
        config = model_routing.load_config()
        template = config.get("commands", {}).get(model) or config["commands"]["default"]
    return [part.replace("{model}", model) for part in shlex.split(template)]


def call_model(model, prompt, template=None, timeout=900):
    """The model's raw answer. judge_call, when installed, owns provenance."""
    try:
        import judge_call  # noqa: F401  (publisher judge layer, when present)
        return judge_call.call(model, prompt)
    except ImportError:
        pass
    proc = subprocess.run(model_command(model, template), input=prompt, capture_output=True,
                          text=True, encoding="utf-8", errors="replace", timeout=timeout)
    if proc.returncode != 0:
        raise RuntimeError(f"model command failed ({proc.returncode}): {proc.stderr[-400:]}")
    return proc.stdout


def prompt_for(symbol, size, best_text, best, n, history):
    tried = "\n".join(f"- round {r}: best fitness {f:.4f} ({c})" for r, f, c in history) or "- none"
    return f"""You are matching one MSVC 7.1 (VS2003, /O2) function byte for byte.
Function: {symbol}  ({size} bytes of retail code)
Current best fitness {best['fitness']:.4f}, diff class: {best['class']}.

Current best translation unit:
```cpp
{best_text}
```

Instruction diff, ours (-) against retail (+):
```
{diff_text(best['compiled'], best['target']) if best.get('compiled') is not None else '(does not compile)'}
```

Previous rounds:
{tried}

Write {n} DIFFERENT complete versions of this translation unit, each a targeted
hypothesis about what the original source looked like (statement order, types,
temporaries, loop shape, inlined helpers, const/ref, signedness, struct layout).
Keep the function's name and signature. No inline assembly, __emit, naked,
#pragma optimize or /alternatename. Reply with exactly {n} ```cpp fenced blocks
and nothing else."""


def parse_variants(answer, limit):
    out, seen = [], set()
    for block in FENCE.findall(answer or ""):
        text = block.strip() + "\n"
        key = hashlib.sha1(text.encode("utf-8", "replace")).hexdigest()
        if key in seen or FORBIDDEN.search(text):
            continue
        seen.add(key)
        out.append(text)
        if len(out) >= limit:
            break
    return out


# ----------------------------------------------------------------- blind phase

STATEMENT = re.compile(r"^\s+[^#/{}\s][^{}]*;\s*$")
COMMUTE = re.compile(r"(\b[A-Za-z_][\w.\->\[\]]*)\s*([+*&|^])\s*([A-Za-z_][\w.\->\[\]]*\b)(?!\s*[(\[])")


def blind_mutate(text, rng):
    """One register-pressure mutation: swap two adjacent simple statements or
    commute one operator. tools/permute.py's richer set is used when present."""
    try:
        import permute
        return permute.mutate(text, rng)[0]
    except (ImportError, AttributeError, Exception):
        pass
    lines = text.split("\n")
    swappable = [i for i in range(len(lines) - 1)
                 if STATEMENT.match(lines[i]) and STATEMENT.match(lines[i + 1])
                 and "return" not in lines[i] + lines[i + 1]]
    if swappable and rng.random() < 0.6:
        i = rng.choice(swappable)
        lines[i], lines[i + 1] = lines[i + 1], lines[i]
        return "\n".join(lines)
    sites = [(i, m) for i, line in enumerate(lines) for m in COMMUTE.finditer(line)]
    if not sites:
        return text
    i, m = rng.choice(sites)
    lines[i] = lines[i][:m.start()] + f"{m[3]} {m[2]} {m[1]}" + lines[i][m.end():]
    return "\n".join(lines)


def blind_phase(best_text, best, make_scorer, trials, jobs, seed):
    """Permute a regalloc-only near miss; stop at exact, the trial cap, or a diff
    that is no longer register-only (the model's job again)."""
    rng = random.Random(seed)
    spent = 0
    while spent < trials and not best["exact"]:
        batch = []
        for _ in range(min(jobs, trials - spent)):
            text = best_text
            for _ in range(rng.choice((1, 1, 2))):
                text = blind_mutate(text, rng)
            batch.append(text)
        spent += len(batch)
        for text, result in zip(batch, score_all(batch, make_scorer, jobs)):
            if result["fitness"] > best["fitness"]:
                best_text, best = text, result
    return best_text, best, spent


# ----------------------------------------------------------------- search

def search(source, symbol, rva, size, *, model, n=12, rounds=4, jobs=12, template=None,
           permute_trials=300, propose=None, make_scorer=None, out=None, seed=0):
    """Run the loop; returns the result dict (also written to <out>/result.json)."""
    if not 8 <= n <= 16:
        raise ValueError("--n must be 8..16 (the amendment's band)")
    out = Path(out or OUT / f"0x{rva:08x}")
    out.mkdir(parents=True, exist_ok=True)
    propose = propose or (lambda prompt: call_model(model, prompt, template))
    if make_scorer is None:
        import build
        symbol_map = build.load_symbol_map()
        make_scorer = lambda i: Scorer(symbol, rva, size, out / f"w{i}", symbol_map)  # noqa: E731
    best_text = Path(source).read_text(encoding="latin-1", errors="replace")
    best = score_all([best_text], make_scorer, 1)[0]
    result = {"symbol": symbol, "rva": f"0x{rva:08X}", "size": size, "runner_model": model,
              "start": best["fitness"], "rounds": [], "blind_trials": 0}
    history = []
    started = time.monotonic()
    stop = "round cap"
    for number in range(1, rounds + 1):
        if best["exact"]:
            stop = "exact"
            break
        if best["class"] == "regalloc":
            break
        answer = propose(prompt_for(symbol, size, best_text, best, n, history))
        variants = parse_variants(answer, n)
        if not variants:
            history.append((number, best["fitness"], "model returned no usable variant"))
            result["rounds"].append({"round": number, "variants": 0})
            continue
        scored = score_all(variants, make_scorer, jobs)
        for i, (text, res) in enumerate(zip(variants, scored)):
            (out / f"r{number}-v{i:02d}.cpp").write_text(text, encoding="latin-1", errors="replace")
        top = max(range(len(scored)), key=lambda i: scored[i]["fitness"])
        improved = scored[top]["fitness"] > best["fitness"]
        if improved:
            best_text, best = variants[top], scored[top]
        history.append((number, best["fitness"], best["class"]))
        result["rounds"].append({
            "round": number, "variants": len(variants),
            "compiled": sum(r["fitness"] >= 0 for r in scored),
            "scores": [r["fitness"] for r in scored], "best": best["fitness"],
            "improved": improved})
    if best["exact"]:
        stop = "exact"
    elif best["class"] == "regalloc" and permute_trials > 0:
        best_text, best, spent = blind_phase(best_text, best, make_scorer, permute_trials, jobs, seed)
        result["blind_trials"] = spent
        stop = "exact (blind phase)" if best["exact"] else "regalloc: blind trial cap"
    result.update(best=best["fitness"], exact=best["exact"], diff_class=best["class"], stop=stop,
                  seconds=round(time.monotonic() - started, 1))
    (out / "best.cpp").write_text(best_text, encoding="latin-1", errors="replace")
    if best["exact"]:
        (out / "win.cpp").write_text(best_text, encoding="latin-1", errors="replace")
    (out / "result.json").write_text(json.dumps(result, indent=2), encoding="utf-8")
    return result


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source", type=Path)
    ap.add_argument("symbol")
    ap.add_argument("rva", type=lambda s: int(s, 16))
    ap.add_argument("size", type=int)
    ap.add_argument("--n", type=int, default=12)
    ap.add_argument("--rounds", type=int, default=4)
    ap.add_argument("--jobs", type=int, default=12)
    ap.add_argument("--model", help="default: model_routing.json variant_model, if routable")
    ap.add_argument("--command", help="model command template; {model} is substituted")
    ap.add_argument("--permute-trials", type=int, default=300)
    args = ap.parse_args(argv)
    model = args.model
    if not model:
        import model_routing
        config = model_routing.load_config()
        stats = model_routing.table(model_routing.outcomes(config=config))
        routed, _, _ = model_routing.route(model_routing.task_class(args.size, config), stats, config)
        model = config.get("variant_model") if config.get("variant_model") in routed else routed[0]
    result = search(args.source, args.symbol, args.rva, args.size, model=model, n=args.n,
                    rounds=args.rounds, jobs=args.jobs, template=args.command,
                    permute_trials=args.permute_trials)
    print(json.dumps({k: v for k, v in result.items() if k != "rounds"}, indent=2))
    print(f"evidence: {OUT / f'0x{args.rva:08x}' / 'result.json'}")
    print(f"attempt note: runner={model} t={len(result['rounds'])} "
          f"score={result['best']:.4f} variant-search {result['stop']}")
    return 0 if result["exact"] else 1


if __name__ == "__main__":
    sys.exit(main())
