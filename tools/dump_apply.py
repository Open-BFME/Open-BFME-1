#!/usr/bin/env python3
"""Write tools/dump_relocs.py's symbolic bodies back into the dump sources.

dump_relocs.py leaves every dump source alone and emits relocatable copies
under build/dump_relocs/. This tool takes the bodies it proved `exact` (every
reference typed, retail's own .reloc table agreeing, both placements verified)
and replaces their raw `db` lines in the tracked source, so the source itself
assembles with no raw retail address in those bodies:

  rel32 call/jmp/jcc  -> `call sym` / `jmp sym` / `jcc sym`
  absolute operands   -> `dd sym[+addend]`

Symbols are the ones dump_relocs resolved: the matched ledger row owning the
retail target (for code that is the ILT thunk row `?j_...` a retail call
encodes, never the body behind it), the import's `__imp_` name, a recorded
dir32_addresses.csv name, else the address-derived `g_<VA>`.

Each converted PROC moves into its own `_TEXT$d<va>` segment, so references
between two dumps of one file stay relocations. Bodies that are not exact,
own an external switch table (a new public label), call a name the gate's
resolver does not know (build.load_symbol_map: row names and pins, not
object-symbol= aliases) or need a name MASM cannot spell are left as they
were; so are PROCs no live row names.

Every rewritten source is then checked three ways, and restored if any fails:
  1. ml assembles it;
  2. dump_relocs.verify_file on the new object: relocations exactly the
     recovered ones, retail placement equals retail, every symbol moved
     (shifted placement) moves every field and leaves no in-image literal;
  3. (--gate) tools/build.py byte-verifies the source's rows with the gate's
     own resolver.

  python3 tools/dump_relocs.py --all                 # first: build/dump_relocs/
  python3 tools/dump_apply.py --all --gate           # rewrite + verify every eligible source
  python3 tools/dump_apply.py game/gen_asm/d_X.asm   # one source
  python3 tools/dump_apply.py --all --dry-run        # count only
"""
import argparse
import collections
import csv
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import dump_relocs as D  # noqa: E402

OUT = ROOT / "build" / "dump_relocs"
SEGMENT = re.compile(r"^(\S+)\s+SEGMENT\b")
ENDS = re.compile(r"^(\S+)\s+ENDS\b")
PUBLIC = re.compile(r"^public\s+(\S+)\s*$", re.I)
EXTERN = re.compile(r"^EXTERN\s+(\S+):(\w+)\s*$")
HEADER = "; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)"


def stem_of(source):
    return re.sub(r"[^A-Za-z0-9_]+", "_", Path(source).with_suffix("").as_posix())


def generated_blocks(text):
    """({symbol: [lines of its segment, SEGMENT..ENDS]}, {extern name: line})."""
    lines = text.split("\n")
    externs, blocks, i = {}, {}, 0
    while i < len(lines):
        m = EXTERN.match(lines[i])
        if m:
            externs[m.group(1)] = lines[i]
        m = SEGMENT.match(lines[i])
        if m:
            seg, j, symbol = m.group(1), i, None
            while not ENDS.match(lines[j]) or ENDS.match(lines[j]).group(1) != seg:
                p = PUBLIC.match(lines[j])
                if p and symbol is None:
                    symbol = p.group(1)
                j += 1
            blocks[symbol] = lines[i:j + 1]
            i = j
        i += 1
    return blocks, externs


def referenced(block):
    names = set()
    for line in block:
        m = re.match(r"^\s+(?:dd|call|jmp|j\w+)\s+(\S+)(?:\s*[+-]\s*0[0-9A-Fa-f]+h)?\s*$", line)
        if m:
            names.add(m.group(1))
    return names


def rewrite(source_text, convert, blocks, externs):
    """New source text with each symbol in `convert` replaced by its generated segment."""
    lines = source_text.split("\n")
    defined = {m.group(1) for m in (D.PROC.match(x.strip()) for x in lines) if m}
    out, segment, i, done = [], None, 0, set()
    while i < len(lines):
        line = lines[i]
        m = SEGMENT.match(line.strip())
        if m:
            segment = (m.group(1), line)
        elif ENDS.match(line.strip()):
            segment = None
        p = PUBLIC.match(line.strip())
        if p and p.group(1) in convert:
            symbol = p.group(1)
            j = i
            while not (D.ENDP.match(lines[j].strip()) and D.ENDP.match(lines[j].strip()).group(1) == symbol):
                j += 1
            if segment is None:
                raise ValueError(f"{symbol}: PROC outside a segment")
            out.append(f"{segment[0]} ENDS")
            out.extend(blocks[symbol])
            out.append(segment[1])
            done.add(symbol)
            i = j + 1
            continue
        out.append(line)
        i += 1
    if done != set(convert):
        raise ValueError(f"PROCs not found: {sorted(set(convert) - done)[:3]}")
    names = set()
    for symbol in convert:
        names |= referenced(blocks[symbol])
    wanted = sorted(n for n in names - defined if n in externs)
    missing = sorted(n for n in names - defined if n not in externs)
    if missing:
        raise ValueError(f"no EXTERN for {missing[:3]}")
    at = next(k for k, x in enumerate(out) if x.strip().lower().startswith(".model")) + 1
    out[at:at] = [HEADER] + [externs[n] for n in wanted]
    return "\n".join(out)


def plan(sources=None):
    """{source: [symbols to convert]} and per-source skip counts."""
    bodies = list(csv.DictReader((OUT / "bodies.csv").open(newline="", encoding="utf-8")))
    by_source = collections.defaultdict(list)
    for b in bodies:
        if sources is None or b["source"] in sources:
            by_source[b["source"]].append(b)
    # the gate resolves a rel32 only through load_symbol_map (ledger row names and
    # symbols.csv pins); an object-symbol= alias dump_relocs binds to is not there
    gate_names = build.load_symbol_map()
    rel32 = collections.defaultdict(set)
    with (OUT / "relocs.csv").open(newline="", encoding="utf-8") as handle:
        for r in csv.DictReader(handle):
            if r["kind"] == "REL32":
                rel32[r["body"]].add(r["symbol"])
    result, skipped = {}, collections.Counter()
    for source, rows in sorted(by_source.items()):
        asm = OUT / "asm" / f"{stem_of(source)}.asm"
        if not asm.exists():
            skipped["no-generated-asm"] += len(rows)
            continue
        blocks, _ = generated_blocks(asm.read_text(encoding="utf-8"))
        text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
        if HEADER in text:
            skipped["already-applied"] += len(rows)
            continue
        convert = []
        for b in rows:
            block = blocks.get(b["symbol"])
            if b["status"] != "exact":
                skipped["status-" + b["status"]] += 1
            elif int(b["tables"]):
                skipped["external-table"] += 1
            elif block is None or any("lnm_" in x for x in block):
                skipped["unsafe-name"] += 1
            elif rel32[b["symbol"]] - set(gate_names) - {b["symbol"]}:
                skipped["rel32-name-not-in-gate-map"] += 1
            elif not int(b["rel32"]) and not int(b["dir32"]):
                skipped["no-references"] += 1
            else:
                convert.append(b)
        if convert:
            result[source] = convert
    return result, skipped


def assemble(text, obj):
    root = build.vc71_root()
    env = build.compiler_environment(root, None)
    asm = obj.with_suffix(".asm")
    asm.write_text(text, encoding="utf-8", newline="\n")
    proc = subprocess.run([str(root / "Vc7" / "bin" / "ml.exe"), "-nologo", "-c", "-Cp", f"-Fo{obj}", str(asm)],
                          capture_output=True, text=True, env=env, cwd=str(asm.parent))
    if proc.returncode:
        raise RuntimeError((proc.stdout + proc.stderr).strip()[-600:])


def verify_object(obj, rows, ctx):
    """dump_relocs.verify_file over the converted bodies: {symbol: [errors]}."""
    items, symbol_va = [], {}
    for b in rows:
        rva, size = int(b["rva"], 16), int(b["size"])
        va = ctx.base + rva
        retail = build.read_target_bytes(rva, size)
        c = D.classify(retail, va, ctx, b["symbol"], [g - va for g in ctx.ghidra_in(va, size)])
        c["analysis"]["ambiguous_sites"] = {a[0] for a in c["ambiguous"]} | c["literal"]
        if c["ambiguous"] or c["failures"]:
            return {b["symbol"]: ["reclassification is no longer exact"]}
        for r in c["relocs"]:
            symbol_va.setdefault(r["symbol"], r["target"] - r["addend"])
        items.append((b["symbol"], va, retail, c["relocs"], c["analysis"]))
    return D.verify_file(obj, items, symbol_va, lambda v: ctx.in_image(v) and v >= ctx.base + 0x1000)


def gate(sources):
    """tools/build.py on the sources: (ok, tail of its output)."""
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "build.py"), *sources], cwd=str(ROOT),
                          capture_output=True, text=True)
    return proc.returncode == 0, (proc.stdout + proc.stderr)[-3000:]


def gate_bisect(sources):
    """[(source, gate output)] for the sources tools/build.py fails, found by halving."""
    ok, tail = gate(sources)
    if ok:
        return []
    if len(sources) == 1:
        return [(sources[0], tail)]
    half = len(sources) // 2
    return gate_bisect(sources[:half]) + gate_bisect(sources[half:])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("sources", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--gate", action="store_true", help="also run tools/build.py on each rewritten source")
    ap.add_argument("--limit", type=int, default=0, help="at most N sources (batching)")
    ap.add_argument("--report", type=Path, default=OUT / "apply.json")
    args = ap.parse_args(argv)
    if not args.all and not args.sources:
        ap.error("name sources or --all")
    todo, skipped = plan(None if args.all else set(args.sources))
    if args.limit:
        todo = dict(list(todo.items())[:args.limit])
    report = {"skipped_bodies": dict(skipped), "sources": {}, "applied_bodies": 0, "applied_bytes": 0,
              "restored_sources": 0}
    if args.dry_run:
        report["applied_bodies"] = sum(len(v) for v in todo.values())
        report["applied_bytes"] = sum(int(b["size"]) for v in todo.values() for b in v)
        print(json.dumps(report | {"sources": len(todo)}, indent=1))
        return 0
    ctx = D.load_context()
    originals = {}
    with tempfile.TemporaryDirectory() as tmp:
        for source, rows in todo.items():
            path = ROOT / source
            original = path.read_bytes()
            blocks, externs = generated_blocks((OUT / "asm" / f"{stem_of(source)}.asm").read_text(encoding="utf-8"))
            entry = {"bodies": len(rows), "bytes": sum(int(b["size"]) for b in rows), "status": "applied"}
            try:
                text = rewrite(original.decode("utf-8", "replace").replace("\r\n", "\n"),
                               [b["symbol"] for b in rows], blocks, externs)
                obj = Path(tmp) / f"{stem_of(source)}.obj"
                assemble(text, obj)
                errors = {k: v for k, v in verify_object(obj, rows, ctx).items() if v}
                if errors:
                    raise RuntimeError(f"verify: {next(iter(errors.items()))}")
            except (ValueError, RuntimeError, StopIteration) as exc:
                entry.update(status="refused", detail=str(exc)[-400:])
                report["sources"][source] = entry
                print(f"refused {source}: {str(exc)[-200:]}", file=sys.stderr)
                continue
            crlf = b"\r\n" in original
            path.write_bytes((text.replace("\n", "\r\n") if crlf else text).encode("utf-8"))
            originals[source] = original
            report["sources"][source] = entry
            print(f"rewrote {source}: {entry['bodies']} bodies, {entry['bytes']} B", file=sys.stderr)
    if args.gate and originals:
        for source, tail in gate_bisect(sorted(originals)):
            (ROOT / source).write_bytes(originals.pop(source))
            report["sources"][source].update(status="restored", detail=tail[-600:])
            report["restored_sources"] += 1
            print(f"gate failed, restored {source}", file=sys.stderr)
    for source in originals:
        report["applied_bodies"] += report["sources"][source]["bodies"]
        report["applied_bytes"] += report["sources"][source]["bytes"]
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=1), encoding="utf-8")
    print(json.dumps({k: v for k, v in report.items() if k != "sources"}, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
