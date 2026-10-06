#!/usr/bin/env python3
"""Grade every matched ledger row into a verification tier. Deletes nothing.

  A  verified: the bytes match strictly AND every reference the body makes binds
     to an allowed symbol AND (when differential-execution results exist) no
     logic/binding divergence was recorded for it.
  B  the bytes match, the bindings are not proven (masked compare, unowned or
     unchecked callee, source changed since the binding scan, no binding data).
  C  contradicted: a keyed gate/identity/body baseline lists the row, its own
     name is contradicted by an oracle, a binding is wrong, or diffexec saw a
     logic/binding divergence. These rows feed the repair queue.
  G  not decompiled C++: generator-written source, a prebuilt .lib member, an
     asm dump, an __emit/naked lift, or a gen-alias row whose compare may run
     masked. G wins over C (the row earns no C++ credit either way); its C
     evidence is still listed in `reasons`.

The same file ships in Open-BFME-1 and Open-BFME-2; the repo is detected from
the ledger layout. Every input is a file the repo (or an explicitly named tree)
already has, so the CSV is deterministic for a given tree and is regenerated,
never hand-edited:

  BFME2  reverse/gate_baseline.txt                      -> C
         code identity register (tools/allowed_symbols.py classes, keyed
         source/row/symbol/target/class: reverse/code_identity_baseline.tsv
         or --bindings): wrong -> C; unowned/divergent -> B; rows absent from
         the scan's ledger, or whose source changed since --bindings-ref -> B
  BFME1  identity_baseline.txt `@` keys, body_guard_baseline.csv,
         full_gate_baseline.txt, ilt_contradicted_baseline.txt  -> C
         ILT oracle (tools/ilt_oracle.py, or --ilt-tools DIR) on the row's own
         name -> C when CONTRADICTED; retail call/jump/pointer targets decoded
         from the row's bytes must be owned by a ledger row whose names are not
         contradicted, else B; a pointer to a body_guard dir32 datum -> C
  both   diffexec JSON (--diffexec, default build/diffexec/results.json):
         logic/binding divergence -> C

  python3 tools/match_tiers.py                  write the CSV, print the summary
  python3 tools/match_tiers.py --check          exit 1 when the committed CSV is stale
  python3 tools/match_tiers.py --summary        summarize the committed CSV
  python3 tools/match_tiers.py --queue [-n N]   tier C rows, largest first (repair queue feed)
"""
import argparse
import bisect
import collections
import csv
import io
import json
import re
import subprocess
import sys
from pathlib import Path

sys.dont_write_bytecode = True  # importing --ilt-tools must not write into another tree

TOOLS = Path(__file__).resolve().parent
ROOT = TOOLS.parent
TIERS = ("A", "B", "C", "G")
HEADER = ["tier", "name", "target_rva", "target_size", "source", "lane", "reasons"]
IMAGE_BASE = 0x400000
# diffexec verdicts that mean "the rebuilt body does something else".
DIVERGENT = {"logic", "binding", "callee", "global", "data", "wrong-callee", "wrong-global"}
BRANCH = re.compile(r"^(call|jmp|j[a-z]{1,3}|loop[a-z]*)$")
ALSO = "also-unproven "
HEX = re.compile(r"0x([0-9a-f]{6,8})\b")


def tokens(notes):
    return {t.strip() for t in re.split(r"[;,]", notes or "") if t.strip()}


# ---------------------------------------------------------------- repo layout
def layout(root=ROOT):
    if (root / "targets/game/reverse/functions.csv").exists():
        rev = root / "targets/game/reverse"
        return {"game": "bfme1", "reverse": rev, "ledger": rev / "functions.csv", "out": rev / "match_tiers.csv"}
    rev = root / "reverse"
    return {"game": "bfme2", "reverse": rev, "ledger": rev / "functions.csv", "out": rev / "match_tiers.csv"}


def read_ledger(path):
    with open(path, encoding="utf-8", errors="replace", newline="") as f:
        return [r for r in csv.DictReader(f)
                if r["status"] == "matched" and (r["target_rva"] or "").startswith("0x")]


def rkey(row):
    return int(row["target_rva"], 16), row["name"]


# ---------------------------------------------------------------- G: provenance
def lanes(rows, progress=None):
    """{row key: (lane, why)} using the repo's own progress.source_lane and naked scan."""
    if progress is None:
        try:
            sys.path.insert(0, str(TOOLS))
            import progress  # noqa: F811
        except Exception:  # pragma: no cover - a tree without progress.py
            progress = None
    matched = {(r["name"], r["target_rva"]): (int(r["target_size"] or 0), r["source"]) for r in rows}
    naked = set()
    if progress is not None:
        try:
            naked = progress.naked_cpp_rows_at(matched, "HEAD")
        except (SystemExit, Exception) as exc:
            print(f"match_tiers: naked scan unavailable ({exc}); __emit lifts not separated", file=sys.stderr)
    out = {}
    for r in rows:
        is_naked = (r["name"], r["target_rva"]) in naked
        suffix = Path(r["source"]).suffix.lower()
        if progress is not None:
            lane = progress.source_lane(r["source"], r.get("notes", ""), is_naked)
        else:
            lane = ("library" if suffix == ".lib" else "dump" if suffix in (".asm", ".s")
                    else "generated" if "/gen_" in r["source"] or any(t.startswith("gen-") for t in tokens(r.get("notes"))) else "authored")
        why = None
        if lane == "library":
            why = "lib-member"
        elif lane == "dump":
            why = "emit-lift" if is_naked and suffix not in (".asm", ".s") else "asm-dump"
        elif "gen-alias" in tokens(r.get("notes")):
            why = "gen-alias-masked"
        elif lane == "generated":
            why = "generated"
        out[rkey(r)] = (lane, why)
    return out


# ---------------------------------------------------------------- evidence
class Evidence:
    def __init__(self):
        self.c = collections.defaultdict(list)      # row key -> contradiction reasons
        self.b = collections.defaultdict(list)      # row key -> unproven reasons
        self.proven = None                           # set of row keys with proven bindings, or None
        self.used = []                               # provenance lines for the summary

    def has(self, label, count):
        self.used.append(f"{label}: {count:,}")


def _lines(path):
    return [ln.rstrip("\n") for ln in open(path, encoding="utf-8", errors="replace")
            if ln.strip() and not ln.startswith("#")]


def gate_baseline(ev, path):
    """BFME2 `<check> 0xRVA name` lines."""
    n = 0
    for ln in _lines(path):
        parts = ln.split(None, 2)
        if len(parts) == 3 and parts[1].startswith("0x"):
            ev.c[(int(parts[1], 16), parts[2].strip())].append(f"gate:{parts[0]}")
            n += 1
    ev.has(f"gate baseline {path.name}", n)


def identity_baseline(ev, path):
    """BFME1 identity_guard keys `@ label 0xADDR name`."""
    n = 0
    for ln in _lines(path):
        parts = ln.split(None, 3)
        if len(parts) == 4 and parts[0] == "@" and parts[2].startswith("0x"):
            ev.c[(int(parts[2], 16), parts[3].strip())].append(f"identity:{parts[1]}")
            n += 1
    ev.has(f"identity baseline {path.name}", n)


def body_baseline(ev, path):
    """BFME1 body_guard keys. A dir32 key names a datum's VA and the unrecorded name a
    source spells for it, not the row: {datum rva: [(name, "C" | "B")]}. "nothing owns"
    is unproven (B); a second name for a recorded datum, a name encoding another
    address, or a function name are contradictions (C)."""
    data, n = collections.defaultdict(list), 0
    with open(path, encoding="utf-8", errors="replace", newline="") as f:
        for r in csv.DictReader(f):
            if r["check"] == "dir32":             # keyed by the datum's VA (build.py)
                kind = "B" if r["detail"].startswith("nothing in the ledger owns") else "C"
                data[int(r["target_rva"], 16) - IMAGE_BASE].append((r["name"], kind))
            else:
                ev.c[(int(r["target_rva"], 16), r["name"])].append(f"body:{r['check']}")
                n += 1
    ev.has(f"body baseline {path.name} (rows / dir32 data)", n)
    ev.used[-1] += f" / {len(data):,}"
    return data


def full_gate_baseline(ev, path, rows):
    by_name_src = collections.defaultdict(list)
    for r in rows:
        by_name_src[(r["name"], r["source"])].append(rkey(r))
    n = 0
    for ln in _lines(path):
        m = re.match(r"^(\S+) \((.+)\)$", ln.strip())
        for k in by_name_src.get(m.groups() if m else (), ()):
            ev.c[k].append("full-gate")
            n += 1
    ev.has(f"full-gate baseline {path.name}", n)


def ilt_baseline(ev, path):
    n = 0
    for ln in _lines(path):
        parts = ln.split("\t")
        if len(parts) == 3 and parts[0] == "functions":
            ev.c[(int(parts[1], 16), parts[2])].append("ilt:contradicted")
            n += 1
    ev.has(f"ILT baseline {path.name}", n)


def code_identity(ev, path, rows, ref=None, root=ROOT):
    """allowed_symbols classes from the keyed register; proof only for rows the scan saw."""
    text = Path(path).read_text(encoding="utf-8", errors="replace")
    mode = re.search(r"^# mode: (\w+)", text, re.M)
    by_src_name = collections.defaultdict(list)
    for r in rows:
        by_src_name[(r["source"], r["name"])].append(rkey(r))
    listed, counts = set(), collections.Counter()
    for ln in text.splitlines():
        parts = ln.split("\t")
        if ln.startswith("#") or len(parts) != 5:
            continue
        src, name, sym, target, cls = parts
        counts[cls] += 1
        for k in by_src_name.get((src, name), ()):
            listed.add(k)
            reason = f"code:{cls} {sym}@{target}"
            (ev.c if cls == "wrong" else ev.b)[k].append(reason)
    ev.has(f"code identity register {Path(path).name} ({dict(sorted(counts.items()))})", sum(counts.values()))
    if ref is None and mode and mode.group(1) == "enforce":
        ev.proven = {rkey(r) for r in rows} - listed
        return
    if ref is None:
        ref = _git(root, "log", "-1", "--format=%H", "--", str(Path(path).resolve().relative_to(root)))
    scanned = _ledger_at(root, ref)
    changed = set(_git(root, "diff", "--name-only", ref, "HEAD").splitlines())
    proven = set()
    for r in rows:
        k = rkey(r)
        if (r["name"], r["target_rva"], r["target_size"], r["source"]) not in scanned:
            ev.b[k].append("bindings:not-in-scan")
        elif r["source"] in changed:
            ev.b[k].append("bindings:source-changed-since-scan")
        elif k not in listed:
            proven.add(k)
    ev.proven = proven
    ev.used.append(f"binding scan ref: {ref[:10]} ({len(proven):,} rows proven)")


def _git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True).stdout.strip()


def _ledger_at(root, ref):
    rel = "reverse/functions.csv"
    text = _git(root, "show", f"{ref}:{rel}")
    return {(r["name"], r["target_rva"], r["target_size"], r["source"])
            for r in csv.DictReader(io.StringIO(text))}


def diffexec(ev, path):
    """Accept a list, {"rows": [...]} or {"results": [...]} of {name?, rva|target_rva, verdict|class}."""
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    items = data if isinstance(data, list) else data.get("rows") or data.get("results") or []
    n = 0
    for it in items:
        rva = it.get("target_rva", it.get("rva"))
        verdict = str(it.get("verdict", it.get("class", it.get("divergence", "")))).lower()
        if rva is None:
            continue
        rva = int(rva, 16) if isinstance(rva, str) else int(rva)
        if verdict in DIVERGENT:
            ev.c[("diffexec", rva, it.get("name"))].append(f"diffexec:{verdict}")
            n += 1
    ev.has(f"diffexec {Path(path).name} divergences", n)


# ---------------------------------------------------------------- BFME1 bindings from retail
def load_ilt(ilt_tools=None):
    """(Oracle, windows path, contradicted-baseline path) or (None, None, None)."""
    tools = Path(ilt_tools) if ilt_tools else TOOLS
    if not (tools / "ilt_oracle.py").exists():
        return None, None, None
    if str(tools) not in sys.path:
        sys.path.append(str(tools))   # after this tree's tools: never shadow build/progress
    import ilt_oracle
    rev = tools.parent / "targets/game/reverse"
    windows = rev / "ilt_windows.tsv"
    base = rev / "ilt_contradicted_baseline.txt"
    return ilt_oracle, windows, (base if base.exists() else None)


def identifier(name):
    """The C++ spelling a source uses for a decorated name (?g_x@@3HA -> g_x, _g_x -> g_x)."""
    m = re.match(r"^\?{1,2}([A-Za-z_$][\w$]*)@", name)
    return m.group(1) if m else name[1:] if name.startswith("_") else name


def source_reader(root=ROOT):
    cache = {}

    def read(source):
        if source not in cache:
            try:
                cache[source] = (root / source).read_text(encoding="utf-8", errors="replace")
            except OSError:
                cache[source] = None
        return cache[source]
    return read


def bfme1_bindings(ev, rows, g_keys, data_bad, read_bytes, text_lo, text_hi, ilt=None, pins=(),
                   read_source=None):
    """Decode each non-G row's retail bytes; every call/jump/pointer leaving the body must
    land on an address a matched row (or pin) owns, with no contradicted name there.
    Without ILT data, a contradicted callee can only come from the keyed baselines."""
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    owners = collections.defaultdict(set)
    for r in rows:
        owners[int(r["target_rva"], 16)].add(r["name"])
    for name, rva in pins:
        owners[rva].add(name)
    bad_names = {k for k, v in ev.c.items() if any(x.startswith(("ilt:", "identity:")) for x in v)}
    oracle, mod = ilt if ilt else (None, None)
    first = (oracle.first_thunk - IMAGE_BASE) if oracle else None
    verdict_cache = {}

    def contradicted(name, rva):
        if (rva, name) in bad_names:
            return True
        if oracle is None or mod.tier(name) != "real":
            return False
        if (name, rva) not in verdict_cache:
            verdict_cache[(name, rva)] = oracle.check(name, rva)[0] == mod.CONTRADICTED
        return verdict_cache[(name, rva)]

    def resolve(rva):
        if first is not None:
            k, rem = divmod(rva - first, 5)
            if rem == 0 and 0 <= k < len(oracle.target):
                return oracle.target[k]
        return rva

    proven = set()
    for r in rows:
        k = rkey(r)
        if k in g_keys:
            continue
        start, size = k[0], int(r["target_size"] or 0)
        problems = []
        for addr, _sz, mnem, ops in md.disasm_lite(read_bytes(start, size), IMAGE_BASE + start):
            for h in HEX.findall(ops):
                target = int(h, 16) - IMAGE_BASE
                for dname, kind in data_bad.get(target, ()):
                    text = read_source(r["source"]) if read_source else None
                    if text is not None and identifier(dname) not in text:
                        continue                  # this row reads the datum under another name
                    if kind == "C":
                        ev.c[k].append(f"body:dir32-misnamed 0x{target + IMAGE_BASE:08X} {dname}")
                    else:
                        problems.append(f"bindings:dir32-unowned 0x{target + IMAGE_BASE:08X}")
                if not (text_lo <= target < text_hi) or start <= target < start + size:
                    continue
                if not BRANCH.match(mnem) and "offset" not in ops and "[" in ops:
                    continue  # a memory operand inside .text is data in code, not a binding
                body = resolve(target)
                names = owners.get(body)
                if not names:
                    problems.append(f"bindings:unowned 0x{body:08X}")
                elif any(contradicted(n, body) for n in names):
                    problems.append(f"bindings:callee-contradicted 0x{body:08X}")
        if problems:
            ev.b[k].extend(sorted(set(problems))[:3] + ([f"+{len(set(problems)) - 3} more"] if len(set(problems)) > 3 else []))
        else:
            proven.add(k)
    ev.proven = proven
    ev.used.append(f"retail call/pointer decode: {len(proven):,} non-G rows with every target owned"
                   + (" and ILT-uncontradicted" if oracle else ""))


def own_name_ilt(ev, rows, ilt):
    oracle, mod = ilt
    n = 0
    for r in rows:
        k = rkey(r)
        if mod.tier(r["name"]) != "real" or any(x == "ilt:contradicted" for x in ev.c.get(k, ())):
            continue
        verdict, p = oracle.check(r["name"], k[0])[:2]
        if verdict == mod.CONTRADICTED:
            ev.c[k].append(f"ilt:contradicted(p={p:.1e})")
            n += 1
    ev.has("ILT oracle, own name contradicted (beyond baseline)", n)


# ---------------------------------------------------------------- grading
def grade(rows, lane_map, ev, diffexec_present=False):
    diff_c = {(k[1], k[2]): v for k, v in ev.c.items() if k and k[0] == "diffexec"}
    out = []
    for r in rows:
        k = rkey(r)
        lane, gwhy = lane_map[k]
        c = list(ev.c.get(k, ()))
        c += diff_c.get((k[0], r["name"]), []) + diff_c.get((k[0], None), [])
        b = list(ev.b.get(k, ()))
        if "masked-REL32 family" in tokens(r.get("notes")):
            b.append("masked-REL32 compare")
        if gwhy:
            tier, reasons = "G", [gwhy] + [f"C-evidence {x}" for x in c]
        elif c:
            tier, reasons = "C", c + [f"{ALSO}{x}" for x in b]
        elif b or ev.proven is None or k not in ev.proven:
            tier, reasons = "B", b or ["bindings:no-binding-data"]
        else:
            tier, reasons = "A", []
        out.append({"tier": tier, "name": r["name"], "target_rva": r["target_rva"],
                    "target_size": r["target_size"], "source": r["source"], "lane": lane,
                    "reasons": "; ".join(dict.fromkeys(reasons))})
    out.sort(key=lambda o: (int(o["target_rva"], 16), o["name"], o["source"]))
    return out


def render(graded):
    buf = io.StringIO()
    w = csv.DictWriter(buf, fieldnames=HEADER, lineterminator="\n")
    w.writeheader()
    w.writerows(graded)
    return buf.getvalue()


def summary(graded, used=()):
    rows, sizes = collections.Counter(), collections.Counter()
    intervals = {t: [] for t in TIERS}
    for g in graded:
        size = int(g["target_size"] or 0)
        rows[g["tier"]] += 1
        sizes[g["tier"]] += size
        start = int(g["target_rva"], 16)
        intervals[g["tier"]].append((start, start + size))
    unique, claimed = {}, []
    for t in TIERS:                      # an address claimed twice counts once, under the best tier
        before = _union(claimed)
        claimed += intervals[t]
        unique[t] = _union(claimed) - before
    lines = ["tier  rows      row-bytes    unique-bytes"]
    for t in TIERS:
        lines.append(f"{t:<5} {rows[t]:>8,}  {sizes[t]:>11,}  {unique[t]:>13,}")
    lines.append(f"all   {sum(rows.values()):>8,}  {sum(sizes.values()):>11,}  {sum(unique.values()):>13,}")
    top = collections.Counter()
    for g in graded:
        if g["tier"] == "C":
            top.update({x.split(" ")[0].split("(")[0] for x in g["reasons"].split("; ")
                        if not x.startswith(ALSO)})
    if top:
        lines.append("top C reasons (rows): " + ", ".join(f"{k} {v:,}" for k, v in top.most_common(8)))
    lines += [f"  evidence: {u}" for u in used]
    return "\n".join(lines)


def _union(intervals):
    total, end = 0, None
    for s, e in sorted(intervals):
        if end is None or s > end:
            total += e - s
            end = e
        elif e > end:
            total += e - end
            end = e
    return total


# ---------------------------------------------------------------- driver
def build_tiers(args, root=ROOT):
    lay = layout(root)
    rows = read_ledger(lay["ledger"])
    lane_map = lanes(rows)
    g_keys = {k for k, (_, why) in lane_map.items() if why}
    ev = Evidence()
    rev = lay["reverse"]
    if lay["game"] == "bfme2":
        if (rev / "gate_baseline.txt").exists():
            gate_baseline(ev, rev / "gate_baseline.txt")
        register = Path(args.bindings) if args.bindings else rev / "code_identity_baseline.tsv"
        if register.exists():
            code_identity(ev, register, rows, args.bindings_ref, root)
        else:
            ev.used.append("code identity register: absent -> no row can reach A")
    else:
        data_bad = {}
        if (rev / "identity_baseline.txt").exists():
            identity_baseline(ev, rev / "identity_baseline.txt")
        if (rev / "body_guard_baseline.csv").exists():
            data_bad = body_baseline(ev, rev / "body_guard_baseline.csv")
        if (rev / "full_gate_baseline.txt").exists():
            full_gate_baseline(ev, rev / "full_gate_baseline.txt", rows)
        mod, windows, ilt_base = load_ilt(args.ilt_tools)
        ilt = None
        if mod is not None:
            ilt = (mod.Oracle(windows), mod)
            if ilt_base:
                ilt_baseline(ev, ilt_base)
            own_name_ilt(ev, rows, ilt)
        else:
            ev.used.append("ILT oracle: absent (callee names checked against keyed baselines only)")
        sys.path.insert(0, str(TOOLS))
        import build
        _, sections = build.exe_image()
        text = next(s for s in sections if s["name"] == ".text")
        pins = []
        if (rev / "symbols.csv").exists():
            with open(rev / "symbols.csv", encoding="utf-8", errors="replace", newline="") as f:
                for p in csv.DictReader(f):
                    if (p.get("address") or "").startswith("0x"):
                        pins.append((p["name"], int(p["address"], 16)))
        bfme1_bindings(ev, rows, g_keys, data_bad, build.read_target_bytes,
                       text["rva"], text["rva"] + text["size"], ilt, pins, source_reader(root))
    dx = Path(args.diffexec) if args.diffexec else root / "build/diffexec/results.json"
    if dx.exists():
        diffexec(ev, dx)
    else:
        ev.used.append("diffexec: no results file (A does not yet require execution evidence)")
    return lay, grade(rows, lane_map, ev), ev.used


def read_csv(path):
    with open(path, encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true", help="exit 1 when the committed CSV differs from a fresh grade")
    ap.add_argument("--summary", action="store_true", help="summarize the committed CSV")
    ap.add_argument("--queue", action="store_true", help="print tier C rows, largest first")
    ap.add_argument("-n", type=int, default=0, help="limit for --queue")
    ap.add_argument("--bindings", help="BFME2: code identity register (allowed_symbols classes)")
    ap.add_argument("--bindings-ref", help="BFME2: commit whose tree the register scanned")
    ap.add_argument("--ilt-tools", help="BFME1: tools/ dir holding ilt_oracle.py when this tree lacks it")
    ap.add_argument("--diffexec", help="diffexec results JSON")
    ap.add_argument("--out", help="write the CSV here instead of the ledger's match_tiers.csv")
    args = ap.parse_args(argv)
    lay = layout()
    out = Path(args.out) if args.out else lay["out"]
    if args.summary or args.queue:
        graded = read_csv(out)
        if args.queue:
            c = sorted((g for g in graded if g["tier"] == "C"), key=lambda g: (-int(g["target_size"]), g["target_rva"]))
            print("target_rva\tsize\tname\tsource\treasons")
            for g in c[:args.n or None]:
                print(f"{g['target_rva']}\t{g['target_size']}\t{g['name']}\t{g['source']}\t{g['reasons']}")
        else:
            print(summary(graded))
        return 0
    _, graded, used = build_tiers(args)
    text = render(graded)
    if args.check:
        current = out.read_text(encoding="utf-8") if out.exists() else ""
        if current != text:
            print(f"match_tiers: {out.name} is stale; run python3 tools/match_tiers.py", file=sys.stderr)
            return 1
        return 0
    out.write_text(text, encoding="utf-8", newline="\n")
    print(summary(graded, used))
    return 0


if __name__ == "__main__":
    sys.exit(main())
