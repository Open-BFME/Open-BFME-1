#!/usr/bin/env python3
"""The canonical-header lane: one header per class, adopted unit by unit.

WHY. Hundreds of units declare their own private copy of the same class
(Coord3D, AsciiString, Object). Each copy byte-matches its own unit and
blocks the link: inline members are COMDATs that differ between units, and
members one copy omits are unresolved. The fix is one evidenced header per
class and every unit including it. Research 11 measured that true layout
conflicts are rare (0-17%) and spelling divergence near 100%, so the lane is
mechanical: generate, swap, prove each unit with the byte gate, queue the rest.

PIPELINE (per class, in DEPENDENCY_ORDER):
  1. contract   tools/class_contract.py decides the ABI (rule order bytes ->
                retail access -> retail vtable -> ZH -> majority; ties queue).
  2. header     generated from the contract, or the class's registered header.
  3. tournament 2-4 header variants (data only, + user default ctor, + the
                views' non-special methods) are each gated against every unit;
                the variant with the most passes is frozen. Byte-equivalent is
                not retail-true: the contract, not the tournament, fixes layout.
  4. codemod    strip the unit's view (and its dependency views, e.g.
                StringBase with AsciiString), #include the header where the
                view stood, and rename the unit's ledger rows when its view
                spelled the other class-key (`U`/`V` mangling).
  5. gate       tools/build.py (BFME2) / build.sh (BFME1) on that one unit,
                in parallel. A batch gate stops at the first compile error.
  6. queue      every unit that does not pass gets an item with its first
                diagnostic and the acceptance command below.

ACCEPTANCE (the queue item's pass test, `accept`): the unit has no private
body for the class, includes the header, every ledger row in it still
byte-matches, and link_check does not lose the unit; a batch additionally
compares link_cycle's closed_strict rows before/after (`closure-diff`).

GATE COST. Changing a registered header re-verifies only its dependents
(tools/header_dependents.py, wired into pre-commit); `gate-cost` measures it.

    python3 tools/header_adopt_lane.py order
    python3 tools/header_adopt_lane.py run --class Coord3D --header PATH --generate --sample 60 --apply
    python3 tools/header_adopt_lane.py accept --class Coord3D FILE...
    python3 tools/header_adopt_lane.py gate-cost --header PATH
    python3 tools/header_adopt_lane.py closure-diff BEFORE.csv AFTER.csv
"""
import argparse
import collections
import concurrent.futures as cf
import csv
import json
import os
import random
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_contract  # noqa: E402
import class_layouts  # noqa: E402

BFME2 = (ROOT / "reverse" / "functions.csv").exists()
REVERSE = class_contract.REVERSE
LEDGER = class_contract.LEDGER
QUEUE = REVERSE / "header_queue.tsv"
REGISTRY = REVERSE / "canonical_classes.csv"
SCRATCH = ROOT / "build" / "header_lane"

# Adopt in this order: a header can only be adopted once the types it uses
# have one definition (research 11, section 5).
DEPENDENCY_ORDER = [
    ("typedefs", ["Bool", "Real", "Int", "UnsignedInt"]),
    ("value types", ["Coord2D", "Coord3D", "ICoord2D", "ICoord3D", "Region2D", "Region3D", "IRegion2D", "RGBColor"]),
    ("string base", ["StringBase"]),
    ("strings", ["AsciiString", "UnicodeString"]),
    ("snapshot", ["Snapshot"]),
    ("xfer", ["Xfer"]),
    ("thing", ["Thing"]),
    ("object", ["Object"]),
]
# Views of these are stripped together with the class (the header brings them in).
STRIP_WITH = {"AsciiString": ["StringBase"], "UnicodeString": ["StringBase"]}
NON_CODE = re.compile(r'//[^\n]*|/\*.*?(?:\*/|\Z)|"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?', re.S)


# ---------------------------------------------------------------- source surgery

def masked(text):
    return NON_CODE.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)


def body_span(text, name):
    """(start, end, key) of the namespace-scope definition of `name`, with a
    `template <...>` line above it and the closing `;` and newline; None if absent."""
    code = masked(text)
    head = re.compile(r"^[ \t]*(template\s*<[^;{}]*>\s*)?(class|struct)[ \t]+(?:__declspec\([^)]*\)\s+)?"
                      + re.escape(name) + r"\b\s*(?::[^{;]*)?\{", re.M)
    for match in head.finditer(code):
        depth, index = 1, match.end()
        while depth and index < len(code):
            depth += (code[index] == "{") - (code[index] == "}")
            index += 1
        tail = re.match(r"[ \t]*;[ \t]*\r?\n?", code[index:])
        if depth or not tail:
            continue
        return match.start(), index + tail.end(), match.group(2)
    return None


def swap(text, names, include):
    """Text with every view of `names` removed and `include` where the first stood."""
    spans = []
    for name in names:
        span = body_span(text, name)
        while span:
            spans.append(span[:2])
            text = text[:span[0]] + "\0" * (span[1] - span[0]) + text[span[1]:]
            span = body_span(text, name)
    if not spans:
        return None
    first = min(s for s, _ in spans)
    out = text[:first] + f'#include "{include}"\n' + text[first:]
    return out.replace("\0", "")


def include_spelling(source, header):
    return os.path.relpath(ROOT / header, (ROOT / source).parent).replace("\\", "/")


# ---------------------------------------------------------------- header generation

def split_members(body):
    out, current, depth = [], "", 0
    index = 0
    while index < len(body):
        char = body[index]
        current += char
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                out.append(current.strip())
                current = ""
                while index + 1 < len(body) and body[index + 1] in " \t\r\n;":
                    index += 1
        elif char == ";" and depth == 0:
            out.append(current.strip())
            current = ""
        index += 1
    return [m for m in out + [current.strip()] if m]


def signature(member, name):
    head = member.split("{")[0]
    head = re.sub(r"\s+", " ", re.sub(r"^(public|private|protected)\s*:\s*", "", head)).strip(" ;")
    head = re.sub(r"\b(inline|__forceinline)\s+", "", head)
    head = re.sub(r"\s*([*&,()])\s*", r"\1", head)
    head = re.sub(r"(\w[*&]?)\s+\w+([,)=])", r"\1\2", head)
    return re.sub(r"\)\s*:.*$", ")", head)


# The ZH typedef layer, spelled out so the header does not depend on the
# unit's own typedefs (Bool is `int` in some units: C2371 otherwise).
TYPEDEFS = {"Real": "float", "Bool": "bool", "Int": "int", "UnsignedInt": "unsigned int",
            "Short": "short", "UnsignedShort": "unsigned short", "Byte": "char", "UnsignedByte": "unsigned char",
            "TRUE": "true", "FALSE": "false"}
PRIMITIVE_WORDS = set("void int float double char short long unsigned signed bool const return if else this "
                      "operator inline sqrtf sqrt fabs fabsf static_cast".split())


def view_methods(name, sources):
    """{signature: text} of the non-special inline methods the views declare.

    One method spelled several ways keeps its most common spelling; the
    tournament and the per-unit gate decide whether that spelling is
    byte-equivalent for each unit."""
    seen = collections.defaultdict(collections.Counter)
    special = re.compile(r"^\s*(?:(?:__forceinline|inline)\s+)?~?" + re.escape(name) + r"\s*\(")
    for source in sources:
        text = (ROOT / source).read_text(encoding="latin-1")
        span = body_span(text, name)
        if not span:
            continue
        code = re.sub(r"//[^\n]*|/\*.*?\*/", "", text[span[0]:span[1]], flags=re.S)
        inner = code[code.index("{") + 1:code.rindex("}")]
        for member in split_members(inner):
            member = re.sub(r"^(public|private|protected)\s*:\s*", "", member).strip()
            if "(" not in member or special.match(member) or re.match(r"(typedef|friend|enum)", member):
                continue
            for typedef, spelling in TYPEDEFS.items():
                member = re.sub(r"\b%s\b" % typedef, spelling, member)
            words = set(re.findall(r"[A-Za-z_]\w*", member)) - PRIMITIVE_WORDS - {name}
            if any(w[0].isupper() for w in words):
                continue                      # needs a type the header does not declare
            seen[signature(member, name)][member] += 1
    return {sig: spellings.most_common(1)[0][0] for sig, spellings in seen.items()}


SPELL = {"uint": "unsigned int", "ushort": "unsigned short", "uchar": "unsigned char", "ulong": "unsigned long",
         "int64": "__int64", "uint64": "unsigned __int64", "wchar": "wchar_t", "int8": "signed char",
         "uint8": "unsigned char"}


def spelled(type_name, field):
    stem = type_name.rstrip("*")
    stars = type_name[len(stem):]
    array = re.match(r"(.+)\[(\d+)\]$", stem)
    if array:
        return f"{SPELL.get(array.group(1), array.group(1))} {field}[{array.group(2)}]"
    return f"{SPELL.get(stem, stem)} {stars}{field}"


def generate(contract, variant, methods):
    name, key = contract["class"], contract["key"]
    guard = re.sub(r"\W", "_", f"CANONICAL_{name}_H").upper()
    lines = [f"// {name}: canonical layout, generated by tools/header_adopt_lane.py from",
             f"// {(REVERSE / 'class_contracts' / (name + '.json')).relative_to(ROOT).as_posix()}"
             f" (variant {variant}). Edit the contract, not this file.",
             f"// sizeof {contract['size']} ({contract['size_by']}); class-key {key} ({contract['key_by']}).",
             f"#ifndef {guard}", f"#define {guard}", ""]
    bases = ", ".join(f"public {b}" for b in contract["bases"])
    lines.append(f"{key} {name}" + (f" : {bases}" if bases else "") + " {")
    if key == "class":
        lines.append("public:")
    for field in contract["fields"]:
        if field["kind"] == "VPTR":
            continue
        lines.append(f"    {spelled(field['type'], field['name'])};")
    if "ctor" in variant:
        lines.append(f"    {name}() {{}}")
    if "methods" in variant:
        for member in methods.values():
            lines.append("    " + member.replace("\n", "\n    "))
    lines += ["};", "", f"#endif // {guard}", ""]
    return "\n".join(lines)


# ---------------------------------------------------------------- the gate

def gate_one(source):
    """None when every row of `source` byte-matches, else the first diagnostic."""
    if BFME2:
        command = [sys.executable, "tools/build.py", source]
        env = dict(os.environ, MSYS_NO_PATHCONV="1")
    else:
        # through bash, as adopt_header.py does; build.sh needs MSYS path conversion
        import bash_path
        command = [bash_path.bash(), str(ROOT / "build.sh"), source]
        env = {k: v for k, v in bash_path.env().items() if k != "MSYS_NO_PATHCONV"}
    done = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, errors="replace", env=env)
    out = done.stdout + done.stderr
    if done.returncode == 0 and "Functions: OK" in out:
        return None
    return next((line.strip()[:200] for line in out.splitlines()
                 if re.search(r"error C\d+|Functions: FAIL|compile failed|MISMATCH|FAIL", line)),
                f"gate exited {done.returncode}")


def ledger_renames(source, name, want_key):
    """[(old, new)] for the unit's row names that mangle the other class-key."""
    have, other = ("U", "V") if want_key == "struct" else ("V", "U")
    pattern = re.compile(other + re.escape(name) + r"@@")
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        return [(r["name"], pattern.sub(have + name + "@@", r["name"])) for r in csv.DictReader(handle)
                if r["source"] == source and pattern.search(r["name"])]


def rewrite_ledger(renames):
    if not renames:
        return
    table = dict(renames)
    text = LEDGER.read_text(encoding="utf-8")
    lines = text.splitlines(keepends=True)
    for i, line in enumerate(lines):
        first = line.split(",", 1)[0]
        if first in table:
            lines[i] = table[first] + line[len(first):]
    LEDGER.write_text("".join(lines), encoding="utf-8", newline="")


def try_unit(source, strip, header, key):
    """(source, None | why, new text, renames). Restores the unit before returning."""
    path = ROOT / source
    original = path.read_bytes()
    text = original.decode("latin-1")
    span = body_span(text, strip[0])
    view_key = span[2] if span else key
    swapped = swap(text, strip, include_spelling(source, header))
    if swapped is None:
        return source, "no private view found", None, []
    renames = ledger_renames(source, strip[0], key) if view_key != key else []
    if renames:
        return source, f"class-key {view_key}: {len(renames)} ledger rename(s) needed", swapped, renames
    try:
        path.write_bytes(swapped.encode("latin-1"))
        why = gate_one(source)
    finally:
        path.write_bytes(original)
    return source, why, swapped, renames


def try_renamed(items, jobs):
    """Units whose view spelled the other class-key: rename their ledger rows and gate,
    serially in one ledger state (the ledger is shared by all of them)."""
    results = {}
    if not items:
        return results
    backup = LEDGER.read_bytes()
    try:
        rewrite_ledger([r for _, _, _, renames in items for r in renames])
        originals = {s: (ROOT / s).read_bytes() for s, _, _, _ in items}
        for source, _, text, _ in items:
            (ROOT / source).write_bytes(text.encode("latin-1"))
        with cf.ThreadPoolExecutor(jobs) as pool:
            for source, why in zip([i[0] for i in items], pool.map(gate_one, [i[0] for i in items])):
                results[source] = why
    finally:
        for source, data in originals.items():
            (ROOT / source).write_bytes(data)
        LEDGER.write_bytes(backup)
    return results


def tournament(name, contract, sources, header, variants, jobs, fixed_header=False):
    strip = [name] + STRIP_WITH.get(name, [])
    methods = view_methods(name, sources) if not fixed_header else {}
    results = {}
    keep = (ROOT / header).read_bytes() if (ROOT / header).exists() else None
    for variant in variants:
        if not fixed_header:
            (ROOT / header).parent.mkdir(parents=True, exist_ok=True)
            (ROOT / header).write_text(generate(contract, variant, methods), encoding="utf-8", newline="\n")
        started = time.time()
        with cf.ThreadPoolExecutor(jobs) as pool:
            got = list(pool.map(lambda s: try_unit(s, strip, header, contract["key"]), sources))
        renamed = [g for g in got if g[3]]
        fixed = try_renamed(renamed, jobs)
        verdicts = {s: (fixed[s] if s in fixed else why) for s, why, _, _ in got}
        results[variant] = {"verdicts": verdicts, "texts": {s: t for s, _, t, _ in got},
                            "renames": {s: r for s, _, _, r in got if r}, "seconds": time.time() - started,
                            "header": (ROOT / header).read_text(encoding="utf-8") if (ROOT / header).exists() else ""}
        passes = sum(v is None for v in verdicts.values())
        print(f"  variant {variant:<14} {passes}/{len(sources)} pass  ({results[variant]['seconds']:.0f}s)", flush=True)
    if not fixed_header:
        if keep is None:
            (ROOT / header).unlink(missing_ok=True)
        else:
            (ROOT / header).write_bytes(keep)
    return results


# ---------------------------------------------------------------- queue + acceptance

def failure_class(why):
    """Research 11's taxonomy, by first diagnostic."""
    code = re.search(r"error (C\d+)", why)
    if code:
        return code.group(1) + (" missing member" if code.group(1) in ("C2039", "C2661", "C2660") else "")
    if why.startswith("class-key"):
        return "class-key rename"
    if "FAIL" in why:
        return "bytes/callee identity"
    return why.split(":")[0][:40]


def acceptance_command(name, source):
    return f"python3 tools/header_adopt_lane.py accept --class {name} {source}"


def write_queue(name, header, failures):
    rows = []
    if QUEUE.exists():
        with QUEUE.open(newline="", encoding="utf-8") as handle:
            rows = [r for r in csv.DictReader(handle, delimiter="\t") if r["class"] != name]
    rvas = collections.defaultdict(list)
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        for r in csv.DictReader(handle):
            rvas[r["source"]].append(r["target_rva"])
    for source, why in sorted(failures.items()):
        rows.append({"class": name, "source": source, "retail_rvas": " ".join(sorted(rvas[source])[:4]),
                     "header": header, "failure": re.sub(r"\s+", " ", why)[:160], "retry_budget": "3",
                     "acceptance": acceptance_command(name, source)})
    cols = ["class", "source", "retail_rvas", "header", "failure", "retry_budget", "acceptance"]
    with QUEUE.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, cols, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(sorted(rows, key=lambda r: (r["class"], r["source"])))


def registered():
    if not REGISTRY.exists():
        return {}
    with REGISTRY.open(newline="", encoding="utf-8") as handle:
        return {r["class"]: r["header"] for r in csv.DictReader(handle) if r.get("class")}


def register(name, header, note):
    if name in registered():
        return
    exists = REGISTRY.exists()
    with REGISTRY.open("a", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, lineterminator="\n")
        if not exists:
            writer.writerow(["class", "header", "notes"])
        writer.writerow([name, header, note])


def link_ok(sources):
    """{source: True/False/None} from tools/link_check.py (None: no verdict)."""
    if not (ROOT / "tools" / "link_check.py").exists():
        return {s: None for s in sources}
    done = subprocess.run([sys.executable, "tools/link_check.py", *sources], cwd=ROOT, capture_output=True,
                          text=True, errors="replace", env=dict(os.environ, MSYS_NO_PATHCONV="1"))
    out = done.stdout + done.stderr
    return {s: (None if s not in out else not re.search(re.escape(s) + r".*(unresolved|duplicate|FAIL|not link)", out))
            for s in sources}


def accept(name, sources, header=None):
    header = header or registered().get(name)
    bad = 0
    for source in sources:
        text = (ROOT / source).read_text(encoding="latin-1")
        problems = []
        if name in class_layouts.class_bodies(text):
            problems.append("still declares a private body")
        if not header or Path(header).name not in text:
            problems.append(f"does not include {header}")
        why = gate_one(source)
        if why:
            problems.append(why)
        print(f"  {'PASS' if not problems else 'FAIL'} {source}" + ("" if not problems else ": " + "; ".join(problems)))
        bad |= bool(problems)
    return bad


def closure_diff(before, after):
    def closed(path):
        with open(path, newline="", encoding="utf-8") as handle:
            return {(r["name"], r["retail_rva"]): r["closed_strict"] == "1" for r in csv.DictReader(handle)}
    old, new = closed(before), closed(after)
    lost = sorted(k for k, v in old.items() if v and not new.get(k))
    gained = sorted(k for k, v in new.items() if v and not old.get(k))
    print(f"closed_strict: {sum(old.values())} -> {sum(new.values())}; lost {len(lost)}, gained {len(gained)}")
    for name, rva in lost[:50]:
        print(f"  LOST {rva} {name}")
    return 1 if lost else 0


def gate_cost(header, jobs):
    """Dependents of `header` and the wall time to re-verify them in parallel."""
    sys.path.insert(0, str(ROOT / "tools"))
    import header_dependents as H
    edges, macro = H.scan(None)
    rows = H.ledger_sources(None)
    reached = H.dependents([header], H.graph(edges), macro)
    sources = sorted(p for p in reached if p in rows)
    started = time.time()
    with cf.ThreadPoolExecutor(jobs) as pool:
        verdicts = list(pool.map(gate_one, sources))
    seconds = time.time() - started
    red = [s for s, v in zip(sources, verdicts) if v]
    print(f"{header}: {len(sources)} dependent ledger sources; re-verified in {seconds:.0f}s with {jobs} jobs; "
          f"{len(red)} red")
    for source in red[:20]:
        print(f"  red {source}")
    return {"header": header, "dependents": len(sources), "seconds": round(seconds, 1), "jobs": jobs, "red": red}


# ---------------------------------------------------------------- driver

def run(args):
    name = args.name
    header = args.header or registered().get(name)
    if not header:
        raise SystemExit(f"{name}: no header given or registered")
    fixed = not args.generate
    sources = class_contract.census(name)
    if args.sample and len(sources) > args.sample:
        sources = sorted(random.Random(args.seed).sample(sources, args.sample))
    print(f"{name}: {len(sources)} units, header {header} ({'registered' if fixed else 'generated'})", flush=True)
    contract_path = REVERSE / "class_contracts" / f"{name}.json"
    if contract_path.exists():
        contract = json.loads(contract_path.read_text(encoding="utf-8"))
    else:
        contract = class_contract.decide(name, sources=sources, jobs=args.jobs)
        contract_path.parent.mkdir(parents=True, exist_ok=True)
        contract_path.write_text(json.dumps({k: v for k, v in contract.items() if k != "sources"}, indent=1,
                                            sort_keys=True) + "\n", encoding="utf-8")
    if contract["queue"] and not fixed:
        print(f"  contract has {len(contract['queue'])} undecided attribute(s); refusing to generate: "
              f"{[q['attribute'] for q in contract['queue']]}")
        return 2
    variants = args.variants.split(",") if not fixed else ["registered"]
    results = tournament(name, contract, sources, header, variants, args.jobs, fixed_header=fixed)
    winner = max(variants, key=lambda v: (sum(x is None for x in results[v]["verdicts"].values()), -variants.index(v)))
    best = results[winner]
    passed = sorted(s for s, v in best["verdicts"].items() if v is None)
    failed = {s: v for s, v in best["verdicts"].items() if v is not None}
    print(f"{name}: winner {winner}: {len(passed)}/{len(sources)} pass "
          f"({100 * len(passed) / max(1, len(sources)):.0f}%), {len(failed)} queued")
    reasons = collections.Counter(failure_class(v) for v in failed.values())
    print("  failures:", dict(reasons.most_common(8)))
    summary = {"class": name, "header": header, "units": len(sources), "winner": winner,
               "variants": {v: sum(x is None for x in r["verdicts"].values()) for v, r in results.items()},
               "seconds": {v: round(r["seconds"], 1) for v, r in results.items()}, "passed": passed,
               "failed": failed, "reasons": dict(reasons)}
    SCRATCH.mkdir(parents=True, exist_ok=True)
    (SCRATCH / f"{name}.json").write_text(json.dumps(summary, indent=1), encoding="utf-8")
    if args.apply:
        if not fixed:
            (ROOT / header).parent.mkdir(parents=True, exist_ok=True)
            (ROOT / header).write_text(best["header"], encoding="utf-8", newline="\n")
            register(name, header, f"generated by header_adopt_lane from class_contracts/{name}.json; "
                     f"variant {winner}; {len(passed)}/{len(sources)} sampled units adopt")
        else:
            register(name, header, f"existing header; contract class_contracts/{name}.json; "
                     f"{len(passed)}/{len(sources)} sampled units adopt")
        for source in passed:
            (ROOT / source).write_bytes(best["texts"][source].encode("latin-1"))
        rewrite_ledger([r for s in passed for r in best["renames"].get(s, [])])
        write_queue(name, header, failed)
        print(f"  applied: {len(passed)} units rewritten, {len(failed)} queued in {QUEUE.relative_to(ROOT).as_posix()}")
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="cmd", required=True)
    sub.add_parser("order")
    p = sub.add_parser("run")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--header")
    p.add_argument("--generate", action="store_true", help="generate the header from the contract (tournament)")
    p.add_argument("--variants", default="data,data+ctor,data+methods")
    p.add_argument("--sample", type=int)
    p.add_argument("--seed", type=int, default=20261006)
    p.add_argument("--jobs", type=int, default=max(2, (os.cpu_count() or 4) // 2))
    p.add_argument("--apply", action="store_true")
    p = sub.add_parser("accept")
    p.add_argument("--class", dest="name", required=True)
    p.add_argument("--header")
    p.add_argument("files", nargs="+")
    p = sub.add_parser("gate-cost")
    p.add_argument("--header", required=True)
    p.add_argument("--jobs", type=int, default=max(2, (os.cpu_count() or 4) // 2))
    p = sub.add_parser("closure-diff")
    p.add_argument("before")
    p.add_argument("after")
    args = parser.parse_args(argv)
    if args.cmd == "order":
        canon = registered()
        for stage, names in DEPENDENCY_ORDER:
            print(f"{stage}:")
            for name in names:
                print(f"  {name:<14} {len(class_contract.census(name)):5} private views  {canon.get(name, '-')}")
        return 0
    if args.cmd == "run":
        return run(args)
    if args.cmd == "accept":
        return accept(args.name, args.files, args.header)
    if args.cmd == "gate-cost":
        gate_cost(args.header, args.jobs)
        return 0
    return closure_diff(args.before, args.after)


if __name__ == "__main__":
    sys.exit(main())
