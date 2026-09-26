#!/usr/bin/env python3
"""Ask the compiler where every TU-local copy of a class puts its members.

`Object` has no header: about a thousand translation units declare their own
partial copy, padded out to the fields that one body touches. Each copy is a
byte-verified witness for the offsets it spells, and together they are the
evidence a canonical header has to agree with. Reading those offsets off the
text means evaluating `char pad[0x1c0 - 0x44]`, base classes, vtable pointers
and packing by hand, so this tool does not: it compiles each TU a second time
with a probe appended and lets MSVC 7.1 say the numbers.

VC7.1 has no `/d1reportSingleClassLayout`. The probe instantiates an undefined
template with the value, and the compiler's refusal names it (VC7.1 prints it as `with [ N=56 ]`):

    template <int N> struct LayoutCensusValue;
    LayoutCensusValue<(int)&((Object*)0)->m_position> layout_census_3;
    -> error C2079: 'layout_census_3' uses undefined struct 'LayoutCensusValue<N>' with [N=56]

One compile per TU reports every data member and `sizeof`. The probe file is
written under build/ and compiled with the original's flags and directory on
the include path, so the tracked source is never touched.

Usage:
  python3 tools/layout_census.py --class Object                  # all copies
  python3 tools/layout_census.py --class Object --limit 20       # a sample
  python3 tools/layout_census.py --class Object --report         # re-read results

Writes build/layout_census/<Class>.jsonl (one record per TU) and prints, per
offset, every name and type the copies give it and which copies disagree on
the member at a shared offset. Nothing here is a byte-match claim; it is the
evidence list a header is written from.
"""
import argparse
import collections
import json
import os
import re
import subprocess
import sys
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

OUT_DIR = ROOT / "build" / "layout_census"
PROBE_DIR = OUT_DIR / "probe"
# VC7.1 prints the argument out of line: "... 'LayoutCensusValue<N>' with [ N=56 ]".
VALUE = re.compile(r"'(layout_census_\d+)' uses undefined struct 'LayoutCensusValue<N>'\s*with\s*\[\s*N=(-?\d+)")
COMPILE_TIMEOUT = 240
SKIP_HEADS = ("virtual", "static", "typedef", "enum", "friend", "using", "template",
              "class", "struct", "union", "operator", "explicit", "inline")


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", " ", text)


def find_class(text, name):
    """Return (head, body) of the first top-level definition of `name`, or None.

    `head` is the text from `class` to the opening brace (it carries the base
    list); `body` is everything between the braces."""
    pattern = re.compile(rf"^(?:class|struct)\s+{re.escape(name)}\b[^;{{]*\{{", re.M)
    match = pattern.search(text)
    if match is None:
        return None
    depth, i = 1, match.end()
    while i < len(text) and depth:
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        i += 1
    return match.group(0)[:-1].strip(), text[match.end():i - 1]


def statements(body):
    """Split a class body into top-level member statements. An inline function
    body ends its statement at the closing brace; everything else at `;`."""
    out, cur, depth = [], [], 0
    for ch in body:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                cur.append(ch)
                out.append("".join(cur).strip())
                cur = []
                continue
        if ch == ";" and depth == 0:
            out.append("".join(cur).strip())
            cur = []
            continue
        cur.append(ch)
    return [re.sub(r"^(?:public|private|protected)\s*:\s*", "", s).strip() for s in out if s.strip()]


def parse_members(body):
    """Return (data, virtuals, methods) as text-derived lists.

    data     [(name, type_text)] in declaration order; offsets come from the compiler
    virtuals [signature] in declaration order (a base class's slots come first)
    methods  [signature] for non-virtual member functions, as spelled"""
    data, virtuals, methods = [], [], []
    for stmt in statements(body):
        while re.match(r"^(?:public|private|protected)\s*:", stmt):
            stmt = re.sub(r"^(?:public|private|protected)\s*:\s*", "", stmt)
        flat = " ".join(stmt.split())
        if not flat:
            continue
        head = flat.split()[0]
        if "(" in flat and not re.search(r"\(\s*\*\s*\w+\s*\)\s*\(", flat):
            sig = flat.split("{", 1)[0].strip()
            (virtuals if head == "virtual" else methods).append(sig)
            continue
        if head in SKIP_HEADS or "{" in flat:
            continue
        # Several declarators share one type: `Int m_a, m_b[4];`
        decl = re.sub(r"\s*=\s*[^,]+", "", flat)
        parts = [p.strip() for p in decl.split(",")]
        first = re.match(r"(.*?)([\w]+)\s*((?:\[[^\]]*\]\s*)*)(?::\s*\d+)?$", parts[0])
        if first is None:
            continue
        type_text = first.group(1).strip()
        if re.search(r":\s*\d+\s*$", parts[0]):  # bitfield: offsetof is ill-formed
            continue
        for index, part in enumerate(parts):
            m = re.match(r"(.*?)(\w+)\s*((?:\[[^\]]*\]\s*)*)$", part)
            if m is None or ":" in part:
                continue
            ptrs = m.group(1).strip() if index else ""
            full = (type_text if index == 0 else re.sub(r"[*&\s]+$", "", type_text) + " " + ptrs).strip()
            data.append((m.group(2), (full + " " + m.group(3).strip()).strip()))
    return data, virtuals, methods


def probe_one(source, cls):
    text = source.read_text(encoding="utf-8-sig", errors="replace")
    found = find_class(strip_comments(text), cls)
    if found is None:
        return {"source": str(source.relative_to(ROOT)), "error": "no top-level definition"}
    head, body = found
    data, virtuals, methods = parse_members(body)
    probes = ["template <int N> struct LayoutCensusValue;",
              f"LayoutCensusValue<(int)sizeof({cls})> layout_census_0;"]
    # Offsets are probes 1..n, member sizes n+1..2n: an extent is what shows
    # two copies overlapping each other's fields.
    for i, (name, _type) in enumerate(data, 1):
        probes.append(f"LayoutCensusValue<(int)&(((({cls}*)0)->{name}))> layout_census_{i};")
    for i, (name, _type) in enumerate(data, 1):
        probes.append(f"LayoutCensusValue<(int)sizeof((({cls}*)0)->{name})> layout_census_{len(data) + i};")
    rel = source.relative_to(ROOT)
    probe = PROBE_DIR / rel.parent / (rel.stem + ".census.cpp")
    probe.parent.mkdir(parents=True, exist_ok=True)
    probe.write_text(text + "\n\n" + "\n".join(probes) + "\n", encoding="utf-8")
    obj = probe.with_suffix(".obj")
    command, env = build.compiler_command(probe, obj)
    # The probe starts with the TU's own text, so its `// cl:` flags already
    # apply; quoted includes still have to resolve from the original directory.
    command[-2:-2] = [f"-I{build.wine_path(source.parent) if os.name != 'nt' else source.parent}"]
    try:
        proc = subprocess.run(command, env=env, cwd=ROOT, capture_output=True, text=True,
                              errors="replace", timeout=COMPILE_TIMEOUT)
    except subprocess.TimeoutExpired:
        # A wedged cl.exe under Wine must not stall the whole census.
        return {"source": str(rel), "error": f"compile timed out after {COMPILE_TIMEOUT}s"}
    values = {m.group(1): int(m.group(2)) for m in VALUE.finditer(proc.stdout + proc.stderr)}
    record = {
        "source": str(rel), "head": " ".join(head.split()),
        "size": values.get("layout_census_0"),
        "members": [
            {"name": name, "type": type_text, "offset": values.get(f"layout_census_{i}"),
             "size": values.get(f"layout_census_{len(data) + i}")}
            for i, (name, type_text) in enumerate(data, 1)
        ],
        "virtuals": virtuals, "methods": methods,
    }
    if record["size"] is None:
        other = [l for l in (proc.stdout + proc.stderr).splitlines()
                 if " error " in l and "layout_census_" not in l]
        record["error"] = (other[0] if other else "no probe value reported")[:300]
    return record


def sources_defining(cls):
    proc = subprocess.run(
        ["git", "grep", "-lE", rf"^(class|struct) {cls}( *[:{{]|$)", "--", "game/*.cpp"],
        cwd=ROOT, capture_output=True, text=True)
    return [ROOT / line for line in proc.stdout.splitlines() if line]


PAD_TYPE = re.compile(r"^(?:unsigned\s+)?(?:char|Byte|UnsignedByte|BYTE|uint8_t)\s*\[")
INT32 = {"ObjectID", "UnsignedInt", "Int", "int", "unsigned", "unsigned int", "DWORD", "UINT",
         "unsigned long", "long", "Int32", "UnsignedInt32", "uint32_t", "int32_t", "Color"}


def kind(type_text, size):
    """Coarse type class, so `ObjectID m_id` and `unsigned m_id` count as one vote."""
    t = re.sub(r"\b(?:const|volatile|mutable)\b", "", type_text).strip()
    if t.endswith("*"):
        return "ptr"
    if t in INT32:
        return "int32"
    if t in ("float", "Real", "double"):
        return t.replace("Real", "float")
    return t or f"?{size}"


def named(record):
    """The members of one copy that claim a field, not an opaque pad."""
    return [m for m in record["members"]
            if m["offset"] is not None and m.get("size") and not PAD_TYPE.match(m["type"])]


def witness(cls):
    try:
        rows = json.loads((ROOT / "targets/game/reverse" / "bfme_layouts.json").read_text(encoding="utf-8"))
    except OSError:
        return {}
    out = collections.defaultdict(list)
    for row in rows:
        if row.get("owner") == cls and isinstance(row.get("bfme"), int):
            out[row["bfme"]].append((row["member"], row.get("confidence")))
    return out


def report(records, cls):
    ok = [r for r in records if r.get("size") is not None]
    print(f"{cls}: {len(records)} copies, {len(ok)} probed, {len(records) - len(ok)} failed")
    for r in records:
        if r.get("size") is None:
            print(f"  FAILED {r['source']}: {r.get('error', '')[:160]}")
    sizes = collections.Counter(r["size"] for r in ok)
    print("  sizeof:", ", ".join(f"0x{s:x}x{n}" for s, n in sizes.most_common(10)))
    at = collections.defaultdict(list)          # offset -> [(member, source)]
    for r in ok:
        for m in named(r):
            at[m["offset"]].append((m, r["source"]))
    wit = witness(cls)
    print(f"  offsets with a named field: {len(at)}   (witness rows in bfme_layouts.json: {len(wit)})")
    for offset in sorted(set(at) | set(wit)):
        claims = at.get(offset, [])
        names = collections.Counter(m["name"] for m, _ in claims)
        kinds = collections.Counter((kind(m["type"], m["size"]), m["size"]) for m, _ in claims)
        w = ", ".join(f"{n}@{c}" for n, c in wit.get(offset, []))
        flag = []
        if len(names) > 1:
            flag.append("names differ")
        if len({s for (_k, s) in kinds}) > 1:
            flag.append("sizes differ")
        if wit.get(offset) and names and not ({n for n, _ in wit[offset]} & set(names)):
            flag.append("witness names another")
        print(f"  +0x{offset:03x} {len(claims):4}  " + "  ".join(f"{n}x{c}" for n, c in names.most_common(5))
              + (f"   [{'; '.join(flag)}]" if flag else "") + (f"   witness: {w}" if w else ""))
        if len(kinds) > 1 or (claims and len(names) > 1):
            print("         kinds: " + "  ".join(f"{k}/{s}x{c}" for (k, s), c in kinds.most_common(6)))
    # Two byte-verified copies cannot both be right when a field of one
    # straddles a DIFFERENT field start of the other.
    spans = sorted({(m["offset"], m["size"], m["name"]) for r in ok for m in named(r)})
    starts = collections.defaultdict(set)
    for off, _size, name in spans:
        starts[off].add(name)
    conflicts = []
    for off, size, name in spans:
        for inner in range(off + 1, off + size):
            if inner in starts:
                conflicts.append((off, size, name, inner, sorted(starts[inner])))
    print(f"  overlapping claims: {len(conflicts)}")
    for off, size, name, inner, others in conflicts[:60]:
        who = [s for r in ok for m in named(r) if (m["offset"], m["size"], m["name"]) == (off, size, name)
               for s in [r["source"]]]
        print(f"    +0x{off:03x}..+0x{off + size:03x} {name} (x{len(who)}) covers +0x{inner:03x} {', '.join(others)}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--class", dest="cls", required=True)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=int(os.environ.get("BUILD_POOL", "4")))
    ap.add_argument("--report", action="store_true", help="only re-read the last results")
    ap.add_argument("--fresh", action="store_true", help="discard earlier results")
    ap.add_argument("--source", action="append", default=[], help="probe these sources only")
    args = ap.parse_args()
    out = OUT_DIR / f"{args.cls}.jsonl"
    if not args.report:
        sources = [ROOT / s for s in args.source] or sources_defining(args.cls)
        if args.limit:
            sources = sources[:args.limit]
        OUT_DIR.mkdir(parents=True, exist_ok=True)
        # Resumable: a record is appended the moment its compile ends, and a
        # rerun skips every source already answered unless --fresh.
        done = set()
        if out.exists() and not args.fresh and not args.source:
            done = {json.loads(line)["source"] for line in out.open(encoding="utf-8")}
        elif args.fresh or args.source:
            out.write_text("", encoding="utf-8")
        todo = [s for s in sources if str(s.relative_to(ROOT)) not in done]
        print(f"probing {len(todo)} source(s), {len(done)} already recorded", file=sys.stderr)
        lock = threading.Lock()

        def run(source):
            record = probe_one(source, args.cls)
            with lock, out.open("a", encoding="utf-8") as fh:
                fh.write(json.dumps(record) + "\n")

        with ThreadPoolExecutor(args.jobs) as pool:
            list(pool.map(run, todo))
    records = [json.loads(line) for line in out.open(encoding="utf-8")]
    report(records, args.cls)


if __name__ == "__main__":
    main()
