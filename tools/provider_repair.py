#!/usr/bin/env python3
"""Provider repair: make the link SELECT the proven retail body of one symbol.

A matched row proves one copy of a function. The link keeps whichever copy of
the name comes first, and a legacy ZH-layout body left in an old TU is often
that copy (census 22a5be53d9: 4,003 selected copies proven wrong). A pin does
not fix it; removing the competing definition does, if nothing verified moves.

  python3 tools/provider_repair.py next [--model M]   # serve + claim ONE conflict, write its brief
  python3 tools/provider_repair.py apply <symbol>      # snapshot the competitors, remove their definitions
  python3 tools/provider_repair.py check <symbol>      # verify; one PASS/FAIL and a JSON receipt
  python3 tools/provider_repair.py abandon <symbol> --model M   # restore, record blocked, release
  python3 tools/provider_repair.py status              # briefs and receipts in this checkout
  python3 tools/provider_repair.py data-next [--model M]  # data mode: serve ONE unresolved global with its
                               # one ZH definition; land it with tools/add_data_match.py
  python3 tools/provider_repair.py data-check <symbol>    # its data_rows.csv row verifies: PASS/FAIL + receipt

`next` reads the census index (build/link_census/link_index.pkl, as
link_check does; --index to point elsewhere) and serves a name only when
  * a ledger row names it and that row's object holds a copy judged retail
    (the owner is proven), and its source is real C++ (no __emit / naked lift);
  * every competing copy is judged wrong (disproved) and is a STRONG definition
    in a game/ C++ TU -- a definition in that file's text, which can be removed.
A competing copy that is an inline COMDAT comes from a header: that name is
reported "needs header window" and never served. inputs/reference/ competitors
are the reference-object lane, not this one.

`check` rebuilds every competitor and the owner with their objects deleted
first, runs the byte gate on them, diffs each competitor per function against
the snapshot `apply` took, and refuses when the symbol survives, when any
changed or removed function is a matched row of that file (the edit broke a
verified body, e.g. an inline COMDAT only the legacy code emitted), when the
edit removes the only census definition of a name another object references
(a vftable or destructor only the legacy constructor emitted), or when the
gate fails. A FAIL is closed with `abandon`, which restores the sources, records
a blocked verdict in re_attempts.log (so `next` never serves it again) and
releases the claim. Then the strict harness: the owner's body, sliced out of its fresh
object, links with no /FORCE at base 0x10000000 against labelled link-only
stubs and must equal retail outside relocation fields with every REL32 on its
named target (positive); the competitor's old body must NOT (negative); both
together must fail LNK2005. The selection is then re-derived: after the edit
every remaining definer of the name must be retail-true. --relink CENSUS_ROOT
also relinks that census's objects with the rebuilt ones and reads the /MAP
holder (minutes). Artifacts: build/provider_repair/<rva>/.
"""
import argparse
import csv
import hashlib
import json
import pickle
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census  # noqa: E402

OUT = ROOT / "build" / "provider_repair"
INDEX = link_census.OUT / "link_index.pkl"
LIFT = re.compile(r"__emit|__declspec\s*\(\s*naked\s*\)")
REL32, WEAK = 20, 105


# ---------------------------------------------------------------- ledger / index
def ledger():
    with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as fh:
        return [r for r in csv.DictReader(fh) if r["status"] == "matched"]


def object_symbol(row):
    for part in (row.get("notes") or "").split(";"):
        if part.startswith("object-symbol="):
            return part.split("=", 1)[1]
    return row["name"]


def load_index(path=None):
    path = Path(path or INDEX)
    if not path.exists():
        raise SystemExit(f"provider_repair: no census index at {path}; run "
                         "`python3 tools/link_census.py --build --history` or pass --index")
    with path.open("rb") as fh:
        return pickle.load(fh)


def census_references(index_path):
    """{name: [objects that reference it]} over the census's own objects
    (objects.rsp beside the index), cached next to the index."""
    index_path = Path(index_path or INDEX)
    census = index_path.parents[2]
    rsp = index_path.parent / "objects.rsp"
    OUT.mkdir(parents=True, exist_ok=True)
    cache = OUT / ("refs_" + hashlib.sha1(str(index_path.resolve()).encode()).hexdigest()[:12] + ".pkl")
    if cache.exists() and cache.stat().st_mtime >= rsp.stat().st_mtime:
        with cache.open("rb") as fh:
            return pickle.load(fh)
    refs = {}
    for line in rsp.read_text(encoding="utf-8").splitlines():
        rel = line.strip().strip('"')
        if not rel:
            continue
        try:
            data = (census / rel).read_bytes()
        except OSError:
            continue
        for sym in link_census._coff_symbols(data):
            if sym["storage"] == 2 and sym["section"] == 0 and sym["value"] == 0:
                refs.setdefault(sym["name"], []).append(Path(rel).name)
    with cache.open("wb") as fh:
        pickle.dump(refs, fh)
    return refs


def orphans(removed, competitor_obj, index, refs, keep=()):
    """Names this edit removed whose only census definition was the competitor
    and that some OTHER census object references: the edit would leave them
    unresolved."""
    objs = index["objects"]
    try:
        me = objs.index(competitor_obj)
    except ValueError:
        return []
    out = []
    for name in removed:
        if name in keep:
            continue
        definers = set(index["strong"].get(name, [])) | {i for i, _, _ in index["comdat"].get(name, [])}
        users = [o for o in refs.get(name, []) if o != competitor_obj]
        if definers <= {me} and users:
            out.append({"name": name, "referenced_by": users[:5]})
    return out


def is_lift(source):
    try:
        return bool(LIFT.search((ROOT / source).read_text(encoding="latin-1")))
    except OSError:
        return True


def classify(name, index, obj_source, owners):
    """(verdict, facts) for one name. verdict: serve | needs-header-window |
    owner-unproven | owner-lift | reference-object | no-conflict | no-owner."""
    objs = index["objects"]
    strong = {objs[i] for i in index["strong"].get(name, [])}
    copies = [(objs[i], verdict) for i, _, verdict in index["comdat"].get(name, [])]
    definers = strong | {o for o, _ in copies}
    own = [r for r in owners.get(name, []) if build.row_object(r).name in definers]
    if not own:
        return "no-owner", {}
    owner_obj = build.row_object(own[0]).name
    facts = {"symbol": name, "rva": own[0]["target_rva"], "size": int(own[0]["target_size"]),
             "owner": {"source": own[0]["source"], "object": owner_obj},
             "competitors": [], "other_copies": []}
    verdicts = dict(copies)
    if verdicts.get(owner_obj) != "retail":
        return "owner-unproven", facts
    if is_lift(own[0]["source"]):
        return "owner-lift", facts
    competitors = []
    for obj in sorted(definers - {owner_obj}):
        entry = {"object": obj, "source": obj_source.get(obj), "strong": obj in strong,
                 "verdict": verdicts.get(obj)}
        if entry["verdict"] == "retail":
            facts["other_copies"].append(entry)
            continue
        competitors.append(entry)
    if not competitors:
        return "no-conflict", facts
    facts["competitors"] = competitors
    if any(c["verdict"] != "wrong" for c in competitors):
        return "competitor-undecided", facts  # a copy nothing proves or disproves: evidence first
    if any((c["source"] or "").startswith("inputs/reference/") or c["object"].startswith("inputs_reference")
           for c in competitors):
        return "reference-object", facts
    if any(not c["strong"] for c in competitors):
        return "needs-header-window", facts
    if any(not c["source"] or not c["source"].startswith("game/") or is_lift(c["source"]) for c in competitors):
        return "competitor-not-removable", facts
    return "serve", facts


def candidates(index):
    rows = ledger()
    owners, obj_source = {}, {}
    for r in rows:
        owners.setdefault(r["name"], []).append(r)
        if r["source"].lower().endswith((".cpp", ".c")):
            obj_source.setdefault(build.row_object(r).name, r["source"])
    names = {n for n, v in index["strong"].items() if len(v) > 1} | \
            {n for n, v in index["comdat"].items() if len(v) > 1}
    for name in sorted(names):
        if name not in owners:
            continue
        verdict, facts = classify(name, index, obj_source, owners)
        if facts:
            yield verdict, facts


# ---------------------------------------------------------------- source surgery
def method_of(symbol):
    """'Class::method' for a plain member, ctor or dtor; None for operators and free functions."""
    m = re.match(r"\?\?([01])([A-Za-z_]\w*)@", symbol)
    if m:
        return f"{m.group(2)}::{'~' if m.group(1) == '1' else ''}{m.group(2)}"
    m = re.match(r"\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@", symbol)
    return f"{m.group(2)}::{m.group(1)}" if m else None


def find_definitions(text, qual):
    """[(first_line, last_line)] of top-level definitions of Class::method in `text`
    (line lists, 0-based, inclusive), including the contiguous comment block above."""
    cls, meth = qual.split("::")
    head = re.compile(r"^(?:__declspec\(\w+\)\s*)?(?:[\w\*&<>,:]+[\s\*&]+)*" + re.escape(cls) + r"::"
                      + re.escape(meth) + r"\s*\(")
    lines = text.split("\n")
    found, i, depth = [], 0, 0
    while i < len(lines):
        line = lines[i]
        if depth == 0 and head.match(line) and not line.rstrip().endswith(";"):
            j, d, started = i, 0, False
            while j < len(lines):
                code = re.sub(r"//.*", "", lines[j])
                for ch in code:
                    if ch == "{":
                        d += 1; started = True
                    elif ch == "}":
                        d -= 1
                if started and d == 0:
                    break
                if not started and code.rstrip().endswith(";"):
                    break                                    # a declaration after all
                j += 1
            if started:
                k = comment_start(lines, i)
                found.append((k, j))
                i = j + 1
                continue
        for ch in re.sub(r"//.*", "", line):
            depth += ch == "{"
            depth -= ch == "}"
        i += 1
    return found


def comment_start(lines, i):
    """First line of the comment block directly above line i: // lines and whole
    /* ... */ blocks, never half of one."""
    k = i
    while k > 0:
        s = lines[k - 1].strip()
        if s.startswith("//"):
            k -= 1
        elif s.endswith("*/"):
            j = k - 1
            while j >= 0 and "/*" not in lines[j]:
                j -= 1
            if j < 0 or lines[j].strip().find("/*") != 0:
                break                       # the block opens mid-line: leave it alone
            k = j
        else:
            break
    return k


def remove_definition(path, span, note):
    """Replace lines span[0]..span[1] of `path` by one comment line; keep line endings."""
    raw = path.read_bytes()
    lines = raw.split(b"\n")
    cr = b"\r" if lines[span[0]].endswith(b"\r") else b""
    lines[span[0]:span[1] + 1] = [b"// " + note.encode("latin-1") + cr]
    path.write_bytes(b"\n".join(lines))


# ---------------------------------------------------------------- objects
def compile_fresh(source, dest=None):
    src = ROOT / source
    obj = build.obj_path(src)
    for stale in (obj, obj.with_suffix(".deps.json")):
        stale.unlink(missing_ok=True)
    ok, text, _ = build.try_compile_source(src, obj)
    if not ok:
        raise RuntimeError(f"compile failed: {source}\n{text}")
    if dest:
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(obj, dest)
    return obj


def section_table(path):
    """{external COMDAT name: digest} of one object."""
    out = {}
    for sym, _, _, digest, _ in link_census._comdat_sections(Path(path).read_bytes()):
        out.setdefault(sym["name"], digest)
    return out


def objdiff(before, after):
    a, b = section_table(before), section_table(after)
    return {"removed": sorted(set(a) - set(b)), "added": sorted(set(b) - set(a)),
            "changed": sorted(n for n in set(a) & set(b) if a[n] != b[n]),
            "unchanged": len(set(a) & set(b)) - sum(1 for n in set(a) & set(b) if a[n] != b[n])}


def slice_object(data, names):
    """COFF with only `names`' sections, the local sections their relocations reach
    and associative children; everything else they reference stays external."""
    count, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
    table, symbol_count = struct.unpack_from("<II", data, 8)
    strings = data[table + 18 * symbol_count:]
    symbols = link_census._coff_symbols(data)
    by_idx = {s["index"]: s for s in symbols}
    sections = {}
    for i in range(1, count + 1):
        p = 20 + optional + 40 * (i - 1)
        header = bytearray(data[p:p + 40])
        size, raw, rel = struct.unpack_from("<III", header, 16)
        nrel = struct.unpack_from("<H", header, 32)[0]
        sections[i] = (header, data[raw:raw + size] if raw else b"\0" * size,
                       [struct.unpack_from("<IIH", data, rel + n * 10) for n in range(nrel)])
    live = {s["section"] for s in symbols if s["name"] in names and s["section"] > 0}
    changed = True
    while changed:
        old = set(live)
        for i in list(live):
            for _, idx, _ in sections[i][2]:
                target = by_idx[idx]
                if target["section"] > 0 and target["storage"] != 2:
                    live.add(target["section"])
        for s in symbols:
            p = table + 18 * s["index"]
            if s["storage"] == 3 and s["section"] > 0 and data[p + 17] == 1:
                aux = data[p + 18:p + 36]
                if aux[14] == 5 and struct.unpack_from("<H", aux, 12)[0] in live:
                    live.add(s["section"])
        changed = old != live
    secmap = {old: new for new, old in enumerate(sorted(live), 1)}
    refs = {idx for i in live for _, idx, _ in sections[i][2]}
    keep = {s["index"] for s in symbols if (s["section"] in live and (s["storage"] != 2 or s["name"] in names))
            or s["index"] in refs}
    for s in symbols:
        if s["index"] in keep and s["storage"] == WEAK:
            keep.add(struct.unpack_from("<I", data, table + 18 * s["index"] + 18)[0])
    kept = [s for s in symbols if s["index"] in keep]
    idxmap, blob = {}, bytearray()
    for s in kept:
        p = table + 18 * s["index"]
        aux = data[p + 17]
        idxmap[s["index"]] = len(blob) // 18
        record = bytearray(data[p:p + 18 * (1 + aux)])
        external = s["storage"] == 2 and s["section"] > 0 and s["name"] not in names
        if external:                                       # defined here, but not ours to keep
            record = record[:18]
            struct.pack_into("<Ih", record, 8, 0, 0)
            record[17] = 0
        elif s["section"] > 0:
            struct.pack_into("<h", record, 12, secmap[s["section"]])
            if s["storage"] == 3 and aux == 1 and record[32] == 5:
                struct.pack_into("<H", record, 30, secmap[struct.unpack_from("<H", record, 30)[0]])
        elif s["section"] < 0 or (aux and s["storage"] not in (WEAK,)):
            record = record[:18]
            record[17] = 0
        blob.extend(record)
    for s in kept:
        if s["storage"] == WEAK:
            at = idxmap[s["index"]] * 18 + 18
            struct.pack_into("<I", blob, at, idxmap[struct.unpack_from("<I", blob, at)[0]])
    headers, payload = bytearray(), bytearray()
    start = 20 + 40 * len(live)
    for old in sorted(live):
        header, raw, relocs = sections[old]
        header = bytearray(header)
        uninit = struct.unpack_from("<I", header, 36)[0] & 0x80
        struct.pack_into("<III", header, 20, 0 if uninit else start + len(payload),
                         (start + len(payload) + (0 if uninit else len(raw))) if relocs else 0, 0)
        struct.pack_into("<H", header, 34, 0)
        struct.pack_into("<I", header, 36, struct.unpack_from("<I", header, 36)[0] & ~0x01000000)
        if not uninit:
            payload.extend(raw)
        for offset, idx, kind in relocs:
            payload.extend(struct.pack("<IIH", offset, idxmap[idx], kind))
        headers.extend(header)
    header = bytearray(data[:20])
    struct.pack_into("<H", header, 2, len(live))
    struct.pack_into("<H", header, 16, 0)
    struct.pack_into("<II", header, 8, start + len(payload), len(blob) // 18)
    return bytes(header + headers + payload + blob + strings)


def _link(args):
    root = build.vc71_root()
    command = [str(root / "Vc7" / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO",
               "/MACHINE:X86", "/SUBSYSTEM:CONSOLE", *map(str, args)]
    if sys.platform != "win32":
        command.insert(0, "wine")
    return subprocess.run(command, capture_output=True, text=True, errors="replace",
                          env=build.compiler_environment(root), cwd=ROOT)


MAP_LINE = re.compile(r"\s*[0-9a-fA-F]{4}:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8})\s")


def strict_body(obj_data, name, work, label):
    """Link `name` alone (strict, base 0x10000000) and return (linked body with
    relocation fields restored from the object, [(offset, size)] relocation
    fields, error). Every REL32 must land on the map address of its referent."""
    work.mkdir(parents=True, exist_ok=True)
    sl = slice_object(obj_data, {name})
    obj = work / f"{label}.obj"
    obj.write_bytes(sl)
    undefined = {s["name"] for s in link_census._coff_symbols(sl) if s["storage"] == 2 and s["section"] == 0}
    stubs = link_census.stub_object(undefined, work / f"{label}_stubs.obj")
    exe, mapf = work / f"{label}.exe", work / f"{label}.map"
    r = _link([f"/ENTRY:{name}", "/BASE:0x10000000", "/FIXED:NO", f"/OUT:{exe}", f"/MAP:{mapf}", obj, stubs])
    if r.returncode:
        return None, None, f"strict link failed ({r.returncode}): " + " | ".join(
            l for l in r.stdout.splitlines() if "error" in l)[:400]
    addrs = {m[1]: int(m[2], 16) for m in map(MAP_LINE.match, mapf.read_text(encoding="latin-1").splitlines()) if m}
    image = exe.read_bytes()
    import pefile
    base = pefile.PE(data=image, fast_load=True).OPTIONAL_HEADER.ImageBase
    body = relocs = size = None
    for sym, raw, rel, _, n in link_census._comdat_sections(sl):
        if sym["name"] == name:
            body, relocs, size = raw, rel, n
    got = bytearray(image[build.rva_to_file_offset(build.pe_sections(image), addrs[name] - base):][:size])
    fields = []
    for offset, kind, ref in relocs:
        if kind == REL32 and ref["name"] in addrs:
            target = addrs[name] + offset + 4 + struct.unpack_from("<i", got, offset)[0]
            if target != addrs[ref["name"]]:
                return None, None, f"REL32 at +0x{offset:X} misses {ref['name']}"
        fields.append((offset, 4))
    return bytes(got), fields, None


def compare(body, fields, expected):
    if body is None:
        return None
    got, want = bytearray(body), bytearray(expected[:len(body)])
    if len(want) != len(got):
        return f"size {len(got)} vs expected {len(want)}"
    for offset, width in fields:
        got[offset:offset + width] = want[offset:offset + width]
    diff = [i for i in range(len(got)) if got[i] != want[i]]
    return "equal" if not diff else f"differs at +0x{diff[0]:X} ({len(diff)} bytes)"


def harness(name, owner_data, legacy_data, expected, work):
    """Positive, negative and duplicate controls for one name."""
    body, fields, err = strict_body(owner_data, name, work, "owner")
    positive = err or compare(body, fields, expected)
    body, fields, err = strict_body(legacy_data, name, work, "legacy")
    negative = err or compare(body, fields, expected)
    both = _link([f"/ENTRY:{name}", f"/OUT:{work / 'both.exe'}", work / "owner.obj", work / "legacy.obj",
                  work / "owner_stubs.obj"])
    duplicate = "LNK2005" in both.stdout
    ok = positive == "equal" and negative != "equal" and negative is not None and duplicate
    return {"positive": positive, "negative": negative, "duplicate_LNK2005": duplicate, "pass": ok}


def retail_bytes(rva, size):
    image = build.EXE.read_bytes()
    return image[build.rva_to_file_offset(build.pe_sections(image), int(rva, 16)):][:size]


# ---------------------------------------------------------------- commands
def work_dir(rva):
    return OUT / f"0x{int(rva, 16):08X}"


def brief_of(symbol):
    for path in OUT.glob("0x*/brief.json"):
        data = json.loads(path.read_text())
        if data["symbol"] == symbol:
            return data
    raise SystemExit(f"provider_repair: no brief for {symbol}; `next` writes one")


def write_brief(facts):
    rows = ledger()
    for comp in facts["competitors"]:
        comp["matched_rows_in_source"] = sum(1 for r in rows if r["source"] == comp["source"])
        qual = method_of(facts["symbol"])
        text = (ROOT / comp["source"]).read_text(encoding="latin-1") if comp["source"] else ""
        comp["definition_lines"] = [a + 1 for a, _ in find_definitions(text, qual)] if qual else []
    facts["retail_bytes"] = retail_bytes(facts["rva"], facts["size"]).hex()
    callers = subprocess.run([sys.executable, str(ROOT / "tools/callers_of.py"), facts["rva"]],
                             capture_output=True, text=True, cwd=ROOT).stdout
    facts["retail_callers"] = [l.strip()[3:] for l in callers.splitlines() if l.strip().startswith("<-")]
    d = work_dir(facts["rva"])
    d.mkdir(parents=True, exist_ok=True)
    (d / "brief.json").write_text(json.dumps(facts, indent=1))
    return d / "brief.json"


def print_brief(facts, path):
    print(f"provider conflict: {facts['symbol']}")
    print(f"  retail      {facts['rva']} ({facts['size']} B) {facts['retail_bytes'][:64]}...")
    print(f"  owner       {facts['owner']['source']} (retail-true copy)")
    for c in facts["competitors"]:
        print(f"  competitor  {c['source']} lines {c['definition_lines']} ({c['verdict']}, "
              f"{'strong' if c['strong'] else 'inline'}; {c['matched_rows_in_source']} matched rows in that file)")
    for c in facts["other_copies"]:
        print(f"  also emits  {c['source'] or c['object']} (retail-true {'strong' if c['strong'] else 'inline'} copy)")
    print(f"  callers     {len(facts['retail_callers'])} retail: " + ", ".join(facts["retail_callers"][:4]))
    print(f"  brief       {path.relative_to(ROOT).as_posix()}")
    print(f"next: python3 tools/provider_repair.py apply '{facts['symbol']}' && "
          f"python3 tools/provider_repair.py check '{facts['symbol']}'")


def cmd_next(args):
    index = load_index(args.index)
    import claims
    import eligibility
    busy = set()
    for token in (eligibility.busy_rvas() if not args.no_claim else ()):
        try:
            busy.add(int(str(token), 16))
        except ValueError:
            pass
    done = {p.parent.name.lower() for p in OUT.glob("0x*/receipt.json")}
    tally = {}
    for verdict, facts in candidates(index):
        tally[verdict] = tally.get(verdict, 0) + 1
        if verdict != "serve" or int(facts["rva"], 16) in busy or f"0x{int(facts['rva'], 16):08x}" in done                 or recorded(facts["rva"]):
            continue
        qual = method_of(facts["symbol"])
        if not qual:
            tally["operator-or-free"] = tally.get("operator-or-free", 0) + 1
            continue
        if not all(find_definitions((ROOT / c["source"]).read_text(encoding="latin-1"), qual)
                   for c in facts["competitors"]):
            tally["gone-since-census"] = tally.get("gone-since-census", 0) + 1   # the index is older than the tree
            continue
        if not args.no_claim:
            got = claims.claim([facts["rva"]], note="provider_repair")
            if not got.claimed:
                continue
        facts["index"] = str(Path(args.index or INDEX).resolve())
        path = write_brief(facts)
        print_brief(facts, path)
        return 0
    print("provider_repair: nothing to serve; " + ", ".join(f"{k} {v}" for k, v in sorted(tally.items())))
    return 1


def cmd_apply(args):
    facts = brief_of(args.symbol)
    d = work_dir(facts["rva"])
    qual = method_of(facts["symbol"])
    for comp in facts["competitors"]:
        before = d / "before" / comp["object"]
        compile_fresh(comp["source"], before)
        path = ROOT / comp["source"]
        spans = find_definitions(path.read_text(encoding="latin-1"), qual)
        if not spans:
            raise SystemExit(f"provider_repair: no definition of {qual} in {comp['source']}")
        original = path.read_bytes()
        note = f"Retail {qual} ({facts['rva']}) is implemented in {Path(facts['owner']['source']).name}."
        # Overloads: remove the one whose removal takes this symbol out of the object.
        for span in sorted(spans, reverse=True):
            path.write_bytes(original)
            remove_definition(path, span, note)
            obj = compile_fresh(comp["source"])
            if not defines(obj, facts["symbol"]):
                print(f"removed {qual} at {comp['source']}:{span[0] + 1}")
                break
        else:
            path.write_bytes(original)
            raise SystemExit(f"provider_repair: no single definition in {comp['source']} emits {facts['symbol']}")
    return 0


def defines(obj, name):
    """True when the object defines `name` (any section, COMDAT or not)."""
    return any(s["name"] == name and s["storage"] == 2 and s["section"] > 0
               for s in link_census._coff_symbols(Path(obj).read_bytes()))


def cmd_check(args):
    facts = brief_of(args.symbol)
    d = work_dir(facts["rva"])
    rows = ledger()
    receipt = {"symbol": facts["symbol"], "rva": facts["rva"], "size": facts["size"], "steps": {}}
    fail = []
    sources = [c["source"] for c in facts["competitors"]] + [facts["owner"]["source"]]
    for source in sources:
        compile_fresh(source)
    gate = subprocess.run([sys.executable, str(ROOT / "tools/build.py"), *sorted(set(sources))],
                          capture_output=True, text=True, errors="replace", cwd=ROOT)
    line = next((l for l in gate.stdout.splitlines() if l.startswith("Functions:")), "Functions: ?")
    receipt["steps"]["gate"] = {"exit": gate.returncode, "result": line}
    if gate.returncode:
        fail.append(f"byte gate: {line}")
    owner_data = build.obj_path(ROOT / facts["owner"]["source"]).read_bytes()
    for comp in facts["competitors"]:
        before = d / "before" / comp["object"]
        if not before.exists():
            raise SystemExit("provider_repair: no snapshot; run `apply` first")
        after = build.obj_path(ROOT / comp["source"])
        diff = objdiff(before, after)
        verified = {object_symbol(r) for r in rows if r["source"] == comp["source"]}
        broken = sorted(verified & (set(diff["removed"]) | set(diff["changed"])) - {facts["symbol"]})
        still = defines(after, facts["symbol"])
        receipt["steps"].setdefault("objdiff", {})[comp["source"]] = {
            "removed": diff["removed"], "changed": diff["changed"], "unchanged": diff["unchanged"],
            "matched_rows_touched": broken, "symbol_still_defined": still}
        if still:
            fail.append(f"{comp['source']} still defines the symbol")
        if facts.get("index"):
            index = load_index(facts["index"])
            lost = orphans(diff["removed"], comp["object"], index, census_references(facts["index"]),
                           keep={facts["symbol"]})
            receipt["steps"]["objdiff"][comp["source"]]["orphaned_references"] = lost
            if lost:
                fail.append(f"{comp['source']}: the edit removes the only definition of "
                            f"{[o['name'] for o in lost]}, still referenced elsewhere")
        if broken:
            fail.append(f"{comp['source']}: the edit changes matched rows {broken}")
        h = harness(facts["symbol"], owner_data, before.read_bytes(), retail_bytes(facts["rva"], facts["size"]),
                    d / "harness" / comp["object"].replace(".obj", ""))
        receipt["steps"].setdefault("harness", {})[comp["source"]] = h
        if not h["pass"]:
            fail.append(f"harness vs {comp['source']}: {h}")
    remaining = [c for c in facts["other_copies"]] + [{"source": facts["owner"]["source"], "verdict": "retail"}]
    receipt["steps"]["selection_after"] = {"definers": [c.get("source") for c in remaining],
                                           "all_retail": all(c["verdict"] == "retail" for c in remaining)}
    if args.relink:
        receipt["steps"]["relink"] = relink_holder(facts, Path(args.relink), d)
        if receipt["steps"]["relink"].get("holder") not in (
                [facts["owner"]["object"]] + [c["object"] for c in facts["other_copies"]]):
            fail.append(f"relink holder is {receipt['steps']['relink'].get('holder')}")
    receipt["inputs"] = {s: hashlib.sha256((ROOT / s).read_bytes()).hexdigest() for s in sorted(set(sources))}
    receipt["objects"] = {s: hashlib.sha256(build.obj_path(ROOT / s).read_bytes()).hexdigest()
                          for s in sorted(set(sources))}
    receipt["head"] = subprocess.run(["git", "rev-parse", "HEAD"], capture_output=True, text=True,
                                     cwd=ROOT).stdout.strip()
    receipt["pass"] = not fail
    receipt["failures"] = fail
    (d / "receipt.json").write_text(json.dumps(receipt, indent=1))
    for source, h in receipt["steps"].get("harness", {}).items():
        print(f"  harness {source}: owner {h['positive']}; legacy {h['negative']}; "
              f"both {'LNK2005' if h['duplicate_LNK2005'] else 'linked'}")
    for source, o in receipt["steps"].get("objdiff", {}).items():
        print(f"  objdiff {source}: removed {len(o['removed'])}, changed {len(o['changed'])} "
              f"(matched rows touched {len(o['matched_rows_touched'])}), unchanged {o['unchanged']}")
    print(f"  gate: {receipt['steps']['gate']['result']}")
    print(("PASS" if not fail else "FAIL: " + "; ".join(fail)) + f"  receipt {(d / 'receipt.json').relative_to(ROOT).as_posix()}")
    return 0 if not fail else 1


def relink_holder(facts, census, d):
    """Relink `census`'s objects.rsp with this checkout's rebuilt objects, labelled
    stubs for its unresolved names, /MAP: which object holds the symbol."""
    subs = {build.obj_path(ROOT / s).name: build.obj_path(ROOT / s)
            for s in [c["source"] for c in facts["competitors"]] + [facts["owner"]["source"]]}
    objs = []
    for line in (census / "build/link_census/objects.rsp").read_text(encoding="utf-8").splitlines():
        p = line.strip().strip('"')
        if p:
            objs.append(subs.pop(Path(p).name, census / p))
    objs += list(subs.values())
    rsp = d / "relink.rsp"
    rsp.write_text("\n".join(f'"{o}"' for o in objs) + "\n", encoding="utf-8")
    base = ["/FORCE", "/ENTRY:WinMainCRTStartup", "/OPT:NOREF", f"/OUT:{d / 'relink.exe'}"]
    first = _link(base + [f"@{rsp}"])
    names = {m.group(1) or m.group(2) for m in map(link_census.UNRESOLVED.search, first.stdout.splitlines()) if m}
    stubs = link_census.stub_object(names, d / "relink_stubs.obj")
    mapf = d / "relink.map"
    _link(base + [f"/MAP:{mapf}", f"@{rsp}", stubs])
    holder = link_census.selected_definitions(mapf.read_text(encoding="latin-1")).get(facts["symbol"])
    return {"objects": len(objs), "holder": holder}


def cmd_abandon(args):
    """Restore the competitor sources, record the verdict, release the claim."""
    facts = brief_of(args.symbol)
    d = work_dir(facts["rva"])
    receipt = json.loads((d / "receipt.json").read_text()) if (d / "receipt.json").exists() else {}
    for comp in facts["competitors"]:
        subprocess.run(["git", "checkout", "--", comp["source"]], cwd=ROOT, check=True)
    why = "; ".join(receipt.get("failures", [])) or args.reason or "abandoned before check"
    evidence = (f"provider_repair (link selection, not a byte attempt): owner {facts['owner']['source']}; "
                f"competitor {', '.join(c['source'] for c in facts['competitors'])}; {why}; "
                f"t={args.minutes}min model={args.model} blocker={args.blocker}")
    subprocess.run([sys.executable, str(ROOT / "tools/re_log.py"), "record", facts["symbol"], facts["rva"],
                    str(facts["size"]), "blocked", evidence.replace(",", ";")], cwd=ROOT, check=True)
    subprocess.run([sys.executable, str(ROOT / "tools/claims.py"), "release", facts["rva"]], cwd=ROOT)
    (d / "abandoned").write_text(evidence)
    print(f"abandoned {facts['symbol']}: sources restored, verdict recorded, claim released")
    return 0


def recorded(rva):
    """True when re_attempts.log already has a provider_repair verdict for this address."""
    log = ROOT / "targets/game/reverse/re_attempts.log"
    token = f"0x{int(rva, 16):08X}".lower()
    try:
        return any("provider_repair" in line and token in line.lower()
                   for line in log.read_text(encoding="utf-8", errors="replace").splitlines())
    except OSError:
        return False


def cmd_status(_args):
    for d in sorted(OUT.glob("0x*")):
        brief = d / "brief.json"
        receipt = d / "receipt.json"
        name = json.loads(brief.read_text())["symbol"] if brief.exists() else "?"
        state = "no receipt"
        if receipt.exists():
            r = json.loads(receipt.read_text())
            state = "PASS" if r["pass"] else "FAIL " + "; ".join(r["failures"])[:120]
        print(f"{d.name}  {state:10}  {name}")
    return 0


# ---------------------------------------------------------------- data mode
# A global the link cannot find (the trial link's queue, class data:* or the
# unpinned static/global data group) whose Zero Hour definition is one line in
# one reference .cpp: serve it so a seat writes that definition in its honest
# owner and lands it with tools/add_data_match.py (data_rows.csv).
REFERENCE = ROOT / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
DATA_QUEUE = ROOT / "build" / "data_scaffold" / "queue.csv"


def data_identifier(symbol):
    """(qualified C++ name, bare identifier) a mangled global or static data member
    spells, or None: `?x@@3HA` -> ("x", "x"), `?x@C@@2HA` -> ("C::x", "x")."""
    m = re.match(r"^\?(\w+)@(?:(\w+)@)?@[23]", symbol)
    if not m:
        return None
    return (f"{m.group(2)}::{m.group(1)}" if m.group(2) else m.group(1)), m.group(1)


def reference_definitions(qualified):
    """[(file, line, text)] of file-scope definitions of `qualified` in the ZH tree."""
    pattern = (r"^[A-Za-z_][\w:<>,\s\*&]*[\s\*&]" + re.escape(qualified)
               + r"\s*(\[[^\]]*\]\s*)*(=[^;]*)?;?\s*(//.*)?$")
    proc = subprocess.run(["rg", "-n", "--no-heading", "-g", "*.cpp", "-e", pattern,
                           REFERENCE.relative_to(ROOT).as_posix()],
                          capture_output=True, text=True, errors="replace", cwd=str(ROOT))
    out = []
    for line in proc.stdout.splitlines():
        path, number, text = line.split(":", 2)
        if text.lstrip().startswith(("extern", "return", "//", "typedef")) or "(" in text.split("=")[0]:
            continue
        out.append((path.replace("\\", "/"), int(number), text.strip()))
    return out


def data_candidates(queue):
    """Queue rows naming a data global, most-referenced first."""
    with Path(queue).open(newline="", encoding="utf-8") as fh:
        rows = [r for r in csv.DictReader(fh)
                if r["class"].startswith("data:") or r["cause"] == "static/global data"]
    rows.sort(key=lambda r: (-int(r["referring_objects"] or 0), r["name"]))
    return rows


def cmd_data_next(args):
    import claims
    import data_rows
    import eligibility
    import reloc_ledger
    dir32 = {r["name"]: int(r["va"], 16) for r in reloc_ledger.read_csv_rows(build.DIR32_ADDRESSES)}
    owned = {r["name"] for r in data_rows.load()}
    busy = set()
    for token in (eligibility.busy_rvas() if not args.no_claim else ()):
        try:
            busy.add(int(str(token), 16))
        except ValueError:
            pass
    img = reloc_ledger.Image()
    tally = {}
    for row in data_candidates(args.queue):
        name = row["name"]
        ident = data_identifier(name)
        va = dir32.get(name)
        verdict = ("owned" if name in owned else "no-dir32-address" if va is None
                   else "not-a-simple-global" if ident is None
                   else "busy" if (va - 0x400000) in busy or recorded(hex(va - 0x400000)) else None)
        if verdict is None:
            found = reference_definitions(ident[0])
            files = {f for f, _, _ in found}
            # a ZH `static` is TU-local: the external name our code spells cannot be
            # landed from that definition without changing its linkage -- not served
            verdict = ("no-reference-definition" if not found else "several-reference-definitions"
                       if len(files) != 1 else "reference-definition-is-static"
                       if found[0][2].startswith("static") else None)
        if verdict:
            tally[verdict] = tally.get(verdict, 0) + 1
            continue
        rva = f"0x{va - 0x400000:08X}"
        if not args.no_claim:
            got = claims.claim([rva], note="provider_repair data")
            if not got.claimed:
                tally["claimed-elsewhere"] = tally.get("claimed-elsewhere", 0) + 1
                continue
        ref_file, ref_line, ref_text = found[0]
        game_path = "game/" + ref_file.split("/Code/", 1)[1]
        facts = {"mode": "data", "symbol": name, "rva": rva, "va": f"0x{va:08X}", "section": img.section(va),
                 "retail_bytes": (img.read(va, 16) or b"").hex(), "referring_objects": row["referring_objects"],
                 "reference": {"file": ref_file, "line": ref_line, "definition": ref_text},
                 "owner": game_path, "owner_exists": (ROOT / game_path).exists(),
                 "steps": [f"write the definition in {game_path} (ZH's own file; copy its `// cl:` line "
                           "from a sibling that compiles)",
                           f"python3 tools/add_data_match.py '{name}' 0x{va:08X} --va {game_path} "
                           "--model <you> --evidence '<ZH file:line and why this address>'",
                           f"python3 tools/provider_repair.py data-check '{name}'"]}
        d = OUT / f"data_{rva.lower()}"
        d.mkdir(parents=True, exist_ok=True)
        (d / "brief.json").write_text(json.dumps(facts, indent=1), encoding="utf-8")
        print(json.dumps(facts, indent=1))
        return 0
    print("provider_repair data: nothing to serve; " + ", ".join(f"{k} {v}" for k, v in sorted(tally.items())))
    return 1


def cmd_data_check(args):
    """PASS when the symbol's data row verifies and the data ledger is clean."""
    import data_rows
    rows = [r for r in data_rows.load() if r["name"] == args.symbol]
    failures = []
    problems = []
    data_rows.check(data_rows.DATA_ROWS.read_bytes(), problems)
    failures += problems
    if len(rows) != 1:
        failures.append(f"{args.symbol} has {len(rows)} data_rows.csv row(s), expected one")
    else:
        try:
            data_rows.verify(rows=rows, log=lambda text: failures.append(text.strip())
                             if "FAIL" in text or text.startswith("    ") else None)
        except SystemExit:
            pass
    rva = f"0x{data_rows.va_of(rows[0]) - 0x400000:08X}" if len(rows) == 1 else "unknown"
    receipt = {"mode": "data", "symbol": args.symbol, "rva": rva, "pass": not failures, "failures": failures}
    d = OUT / f"data_{rva.lower()}"
    d.mkdir(parents=True, exist_ok=True)
    (d / "receipt.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    print(("PASS " if not failures else "FAIL ") + args.symbol + ("" if not failures else ": " + "; ".join(failures)))
    return 0 if not failures else 1


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    n = sub.add_parser("next")
    n.add_argument("--index")
    n.add_argument("--model", default="")
    n.add_argument("--no-claim", action="store_true", help="list without claiming (dry run)")
    a = sub.add_parser("apply")
    a.add_argument("symbol")
    c = sub.add_parser("check")
    c.add_argument("symbol")
    c.add_argument("--relink", metavar="CENSUS_ROOT", help="also relink that census's objects and read the /MAP")
    b = sub.add_parser("abandon", help="restore the competitor sources, record a blocked verdict, release the claim")
    b.add_argument("symbol")
    b.add_argument("--model", required=True)
    b.add_argument("--minutes", type=int, default=0)
    b.add_argument("--blocker", default="inline")
    b.add_argument("--reason", default="")
    sub.add_parser("status")
    dn = sub.add_parser("data-next", help="serve + claim ONE global the link cannot find, with its ZH definition")
    dn.add_argument("--queue", default=str(DATA_QUEUE), help="tools/data_scaffold.py --trial-link's queue.csv")
    dn.add_argument("--model", default="")
    dn.add_argument("--no-claim", action="store_true", help="list without claiming (dry run)")
    dc = sub.add_parser("data-check", help="verify the symbol's data_rows.csv row; one PASS/FAIL and a receipt")
    dc.add_argument("symbol")
    args = ap.parse_args(argv)
    return {"next": cmd_next, "apply": cmd_apply, "check": cmd_check, "abandon": cmd_abandon,
            "status": cmd_status, "data-next": cmd_data_next, "data-check": cmd_data_check}[args.cmd](args)


if __name__ == "__main__":
    sys.exit(main())
