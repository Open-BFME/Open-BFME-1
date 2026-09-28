#!/usr/bin/env python3
"""Sweep the scratch-register rotation lever over one allocation-only near miss.

MSVC 7.1 hands out EAX/ECX/EDX to short-lived values round-robin, in program
order across the whole function (targets/game/reverse/analysis/allocation_residue.md, measured
2026-09-26). A body whose scratch registers are all shifted one step from
retail's is one rotation step away, and the step comes from spelling, not from
the value: `f(m_x)` and `T v = m_x; f(v)` compile to the same bytes except
that the copied form advances the rotation. Toggling the nearest pushed memory
load ABOVE the first mismatch landed 4 of the first 5 bodies tried.

This generates every such toggle mechanically and measures each one:
  copy     wrap a call argument, member-call receiver or memory-reading local
           initialiser in an identity inline (`rotation_sweep_copy_(x)`), the
           compiler's view of a local copy or a Zero Hour accessor
  inline   substitute a single-use local back into its one use (the reverse)

  python3 tools/rotation_sweep.py SOURCE.cpp "MANGLED" 0xRVA [--size N] [--jobs 4]

Run `tools/alloc_residue.py` first: the lever reaches the scratch class only
(EAX/ECX/EDX), not callee-saved swaps, stack slots or SIB order. A winning
variant is a HYPOTHESIS: respell it naturally (a local copy, or ZH's accessor
such as `getObject()`), re-probe that spelling, and land only the natural one;
the identity inline never goes into game/. Each variant is a temporary copy
beside SOURCE so relative includes resolve; the copies are always removed.
"""
import argparse
import re
import sys
import uuid
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import build
import probe

COPY = "rotation_sweep_copy_"
PRELUDE = f"template<class T> inline T {COPY}(T v) {{ return v; }}\n"
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", COPY}
LITERAL = re.compile(r"-?[\d.]+f?|0x[0-9a-fA-F]+|true|false|this|NULL")


def locate(text, symbol):
    """(line start of the definition, index of its `{`, index of its `}`)."""
    m = re.match(r"\?(\w+)@(\w+)@", symbol)          # method@Class@ (nested scopes follow)
    if symbol.startswith("??") or not re.match(r"\?\w+@", symbol):
        raise SystemExit("rotation_sweep: special members and templates are not supported")
    head = f"{m.group(2)}::{m.group(1)}(" if m and not symbol.startswith(f"?{m.group(1)}@@")         else re.match(r"\?(\w+)@@", symbol).group(1) + "("
    for hit in re.finditer(re.escape(head), text):
        line0 = text.rfind("\n", 0, hit.start()) + 1
        if text[line0:hit.start()].strip().startswith("//"):
            continue
        brace = text.find("{", hit.end())
        if brace == -1 or text.find(";", hit.end(), brace) != -1:
            continue                                      # a declaration, not the definition
        depth = 0
        for i in range(brace, len(text)):
            depth += {"{": 1, "}": -1}.get(text[i], 0)
            if depth == 0:
                return line0, brace, i
    raise SystemExit(f"rotation_sweep: no definition of {head} in the source")


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        depth += {"(": 1, "[": 1, ")": -1, "]": -1}.get(ch, 0)
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    out.append(cur)
    return out


def variants(text, symbol):
    """{name: (description, new full text)} for every copy/inline toggle."""
    line0, brace, end = locate(text, symbol)
    body = text[brace:end + 1]
    out = {}

    def add(kind, what, new_body):
        if new_body != body:
            name = f"v{len(out) + 1}_{kind}"
            out[name] = (f"{kind}: {what}", text[:line0] + PRELUDE + text[line0:brace] + new_body + text[end + 1:])

    for call in re.finditer(r"(\w+)\s*\(", body):
        if call.group(1) in KEYWORDS:
            continue
        depth, k = 1, call.end()
        while k < len(body) and depth:
            depth += {"(": 1, ")": -1}.get(body[k], 0)
            k += 1
        text_of_call = body[call.start():k]
        for arg in split_args(body[call.end():k - 1]):
            expr = arg.strip()
            if not expr or LITERAL.fullmatch(expr) or expr.startswith(("&", '"', "'")):
                continue
            new_call = text_of_call.replace(arg, arg.replace(expr, f"{COPY}({expr})", 1), 1)
            add("copy", f"argument `{expr}` of {call.group(1)}(...)",
                body[:call.start()] + new_call + body[k:])
    for recv in re.finditer(r"([\w\]\[]+(?:->\w+)+)->(\w+)\s*\(", body):
        add("copy", f"receiver `{recv.group(1)}` of ->{recv.group(2)}(...)",
            body[:recv.start()] + f"{COPY}({recv.group(1)})->{recv.group(2)}(" + body[recv.end():])
    decl = re.compile(r"\n(\s*)((?:const\s+)?[\w:]+(?:\s*\*+\s*|\s+))(\w+)\s*=\s*([^;]+);")
    for local in decl.finditer(body):
        init = local.group(4).strip()
        if re.search(r"->|\.|\bm_\w+|\[", init) and not init.startswith(COPY):
            stmt = local.group(0)
            add("copy", f"initialiser of local `{local.group(3)}`",
                body[:local.start()] + stmt.replace(init + ";", f"{COPY}({init});", 1) + body[local.end():])
    for local in decl.finditer(body):
        name, init = local.group(3), local.group(4)
        rest = body[local.end():]
        uses = re.findall(rf"\b{re.escape(name)}\b", rest)
        if len(uses) == 1 and "(" not in init:
            add("inline", f"single-use local `{name}` substituted into its use",
                body[:local.start()] + re.sub(rf"\b{re.escape(name)}\b", f"({init})", rest, count=1))
    return out


def pairs(text, symbol, first):
    """Second-order toggles: the rotation has three registers, so a body two
    steps off needs two copies (or a copy and an inline). {name: (what, text)}."""
    out, seen = {}, {t for _, t in first.values()}
    for name, (what, text1) in first.items():
        base = text1.replace(PRELUDE, "", 1)
        for what2, text2 in variants(base, symbol).values():
            if text2 in seen or what2 == what or COPY + "(" in what2:
                continue
            seen.add(text2)
            out[f"{name}+{len(out) + 1}"] = (f"{what} AND {what2}", text2)
    return out


def measure(source, text, symbol, retail):
    scratch = source.with_name(f"_rotsweep_{uuid.uuid4().hex[:10]}{source.suffix}")
    obj = build.ROOT / "build" / "rotation_sweep" / (scratch.stem + ".obj")
    obj.parent.mkdir(parents=True, exist_ok=True)
    try:
        scratch.write_bytes(text.encode("utf-8"))
        ok, _, _ = build.try_compile_source(scratch, obj)
        if not ok:
            return {"error": "compile failed"}
        compiled, relocs = build.read_object_symbol_bytes(obj, symbol)
        compiled = bytes(compiled)
        ours, theirs = probe.masked(compiled, relocs), probe.masked(retail, relocs)
        diffs = sum(1 for a, b in zip(ours, theirs) if a != b) + abs(len(compiled) - len(retail))
        return {"size": len(compiled), "diffs": diffs,
                "exact": diffs == 0 and len(compiled) == len(retail)}
    except (Exception, SystemExit) as error:
        return {"error": str(error)[:80]}
    finally:
        scratch.unlink(missing_ok=True)
        obj.unlink(missing_ok=True)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("source")
    ap.add_argument("symbol")
    ap.add_argument("rva")
    ap.add_argument("--size", type=int)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--top", type=int, default=10)
    ap.add_argument("--pairs", action="store_true",
                    help="also try every pair of toggles (two rotation steps; slower)")
    args = ap.parse_args(argv)

    source = Path(args.source)
    source = (source if source.is_absolute() else build.ROOT / source).resolve()
    rva = int(args.rva, 16)
    size = args.size or probe.ledger_size(rva)
    if not size:
        raise SystemExit("rotation_sweep: no ledger size for this RVA; pass --size")
    retail = build.read_target_bytes(rva, size)
    text = source.read_text(encoding="utf-8-sig", errors="replace")
    found = variants(text, args.symbol)
    if args.pairs:
        found.update(pairs(text, args.symbol, found))
    jobs = {"base": ("unchanged source", text), **found}
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        results = dict(zip(jobs, pool.map(lambda item: measure(source, item[1], args.symbol, retail),
                                          jobs.values())))
    base = results["base"]
    if "error" in base:
        raise SystemExit(f"rotation_sweep: the unchanged source does not build ({base['error']})")
    good = sorted((r["diffs"], name) for name, r in results.items() if "error" not in r and name != "base")
    print(f"rotation_sweep: {len(found)} toggles; base {base['diffs']} differing byte(s) at size {base['size']}/{size}")
    for diffs, name in good[:args.top]:
        mark = "EXACT" if results[name]["exact"] else f"{diffs:4} diff"
        delta = diffs - base["diffs"]
        print(f"  {mark:9} ({delta:+d})  {name:12} {jobs[name][0]}")
    failed = sum("error" in r for r in results.values())
    if failed:
        print(f"  ({failed} variant(s) did not compile)")
    exact = [name for _, name in good if results[name]["exact"]]
    if exact:
        print(f"HYPOTHESIS CONFIRMED by {exact[0]}: respell that toggle naturally (a local copy passed on, or Zero "
              f"Hour's accessor), probe the natural spelling, and land only that; {COPY} never goes into game/.")
    return 0 if exact else 1


if __name__ == "__main__":
    sys.exit(main())
