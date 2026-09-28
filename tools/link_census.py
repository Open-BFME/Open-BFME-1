#!/usr/bin/env python3
"""Link every matched object into one image and count what stops it.

Every other gate verifies one function at a time. Nothing had ever linked the
tree, so nobody knew how far "the functions match" is from "the game builds".
This links the object of every matched ledger row (compiled TUs, MASM dumps,
generated C++, prebuilt-library members) with MSVC 7.1's own link.exe under
/FORCE, so it reports every problem instead of stopping at the first, and sorts
them into the classes the integration work has to clear:

  unresolved   a referenced name nothing defines
    data         a global the code reaches by a pinned address
                 (dir32_addresses.csv): needs a definition
    import       __imp__ DLL entry: needs the import libraries
    alias        a pinned call name whose address is matched under another
                 name: collapse onto the defining name
    dump         a pinned call name whose address is still a dump: the dump
                 defines ?d_XXXXXXXX, so it needs the real name
    unpinned     referenced but pinned nowhere (runtime, shims, typos)
    vtable/rtti  ??_7 / ??_R: a class's vftable or type info
  duplicate    a name defined by two objects (private class copies, shims,
               double conversions)

  python3 tools/link_census.py            # link, write build/link_census/census.json
  python3 tools/link_census.py --report   # summarise the last census

The census is diagnostic. The image it writes is not expected to run.
"""
import argparse
import collections
import csv
import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

OUT = ROOT / "build" / "link_census"
# The linker prints `"<demangled>" (<mangled>)` for a C++ name and the bare name for a C one.
UNRESOLVED = re.compile(r'error LNK20(?:01|19): unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))')
DUPLICATE = re.compile(r'^(\S+\.obj) : (?:error LNK2005|warning LNK4006): (?:"[^"]*" \((\S+)\)|(\S+)) '
                       r'already defined in (\S+\.obj)')
FATAL = re.compile(r"fatal error (LNK(?!1120)\d+).*")  # LNK1120 is only the unresolved count
REFERRER = re.compile(r"^(\S+\.obj) : error LNK20(?:01|19)")


def ledger():
    with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r.get("status") == "matched"
                and (r.get("target_rva") or "").startswith("0x")]


def pins(routes=None):
    """{name: address} from symbols.csv (first pin wins, as the resolver does).
    `routes`, when given, collects {name: target} from `route=0x...` notes."""
    found = {}
    with (ROOT / "targets/game/reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.reader(handle):
            if len(row) >= 2 and row[1].startswith("0x"):
                found.setdefault(row[0], int(row[1], 16))
                route = re.search(r"route=(0x[0-9A-Fa-f]+)", ",".join(row[2:]))
                if routes is not None and route:
                    routes.setdefault(row[0], int(route.group(1), 16))
    return found


BASE = 0x400000


def _thunk_target(notes):
    """RVA an ILT jump-stub row forwards to (`target=0x...` RVA or `target=FUN_<va>`)."""
    found = re.search(r"target=(?:0x([0-9A-Fa-f]+)|FUN_([0-9A-Fa-f]+))", notes or "")
    if not found:
        return None
    return int(found.group(1), 16) if found.group(1) else int(found.group(2), 16) - BASE


def alias_scaffold(rows, wanted):
    """{called name: defining name} for names the census found unresolved.

    Every byte-matched call already lands on retail's address, so pointing the
    name it spells at the symbol DEFINED at that address reproduces what the
    retail image does. This is a link scaffold, like a dump: the source still
    calls the alias, and each one a header lane fixes leaves this table. An
    address is followed through its ILT jump stub (route= pin note, or the stub
    row's target=). One definition per address is chosen deterministically:
    authored game/ C++ first, then by name. Addresses with no defining row are
    left unresolved (the census still reports them).
    """
    routes = {}
    pinned = pins(routes)
    by_address = collections.defaultdict(list)
    stubs = {}
    for row in rows:
        address = int(row["target_rva"], 16)
        if row["name"].startswith("?j_"):
            target = _thunk_target(row.get("notes"))
            if target is not None:
                stubs.setdefault(address, target)
        else:
            by_address[address].append(row)

    defined = {}

    def object_name(row):
        """The symbol the row's object really defines for it: the notes'
        object-symbol= alias, else the ledger name, else the one defined
        symbol equal to it up to the per-machine anonymous-namespace hash."""
        obj = build.row_object(row)
        if obj not in defined:
            try:
                defined[obj] = {s["name"] for s in build.read_object_symbols(obj.read_bytes()) if s["section"] > 0}
            except OSError:
                defined[obj] = set()
        wanted_name = build.ledger_object_symbol(row)
        if wanted_name in defined[obj]:
            return wanted_name
        normal = re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", wanted_name)
        found = [n for n in defined[obj] if re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", n) == normal]
        return found[0] if len(found) == 1 else None

    def defining(address, depth=0):
        owners = by_address.get(address)
        if owners:
            ranked = sorted(owners, key=lambda r: (not (r["source"].startswith("game/") and not r["source"].startswith(
                ("game/gen_small/", "game/gen_asm/"))), r["name"]))
            for row in ranked:
                name = object_name(row)
                if name:
                    return name
            return None
        if depth < 2 and address in stubs:
            return defining(stubs[address], depth + 1)
        return None

    table = {}
    for name in wanted:
        address = routes.get(name, pinned.get(name))
        if address is None:
            continue
        target = defining(address)
        if target and target != name:
            table[name] = target
    # A defining name can itself be unresolved and aliased (2 such chains on
    # 2026-09-28): point every alias straight at the end of its chain.
    for name in list(table):
        seen, target = {name}, table[name]
        while target in table and target not in seen:
            seen.add(target)
            target = table[target]
        table[name] = target
    return {name: target for name, target in table.items() if name != target}


def data_names():
    with (ROOT / "targets/game/reverse/dir32_addresses.csv").open(newline="", encoding="utf-8") as handle:
        return {row["name"] for row in csv.DictReader(handle)}


def objects(rows):
    """Unique object per matched row; (present, missing)."""
    build.extract_lib_members([r for r in rows if r["source"].lower().endswith(build.LIB_SUFFIX)])
    seen, present, missing = set(), [], []
    for row in rows:
        obj = build.row_object(row)
        if obj in seen:
            continue
        seen.add(obj)
        (present if obj.exists() else missing).append(obj)
    return present, missing


def alias_object(table, path):
    """Write a COFF object holding one weak external per alias.

    /ALTERNATENAME for all 71,090 aliases crashed link.exe 7.1 (LNK1000) while
    20,000 linked; a weak external with IMAGE_WEAK_EXTERN_SEARCH_ALIAS, the
    record MASM's ALIAS directive emits, is the ordinary object-file way to say
    "if nothing defines this name, use that one".
    """
    import struct
    targets = sorted(set(table.values()))
    strings = bytearray(b"\0\0\0\0")

    def name_field(text):
        raw = text.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, offset)

    symbols = bytearray()
    index = {}
    for target in targets:
        index[target] = len(symbols) // 18
        symbols += name_field(target) + struct.pack("<IhHBB", 0, 0, 0x20, 2, 0)  # UNDEF external
    for alias, target in sorted(table.items()):
        symbols += name_field(alias) + struct.pack("<IhHBB", 0, 0, 0, 105, 1)  # WEAK_EXTERNAL
        symbols += struct.pack("<II", index[target], 3) + b"\0" * 10          # SEARCH_ALIAS
    count = len(symbols) // 18
    strings[0:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, count, 0, 0)
    path.write_bytes(header + bytes(symbols) + bytes(strings))
    return path


def _arg(path):
    """A repo-relative, forward-slash path, as build.py passes cl.exe: under Wine
    an absolute POSIX path (/home/...) would read as a link.exe option."""
    return Path(path).resolve().relative_to(ROOT.resolve()).as_posix()


def link(objs, aliases=None, tag="census"):
    OUT.mkdir(parents=True, exist_ok=True)
    rsp = OUT / "objects.rsp"
    rsp.write_text("\n".join(f'"{_arg(o)}"' for o in objs) + "\n", encoding="utf-8")
    extra = []
    if aliases:
        extra.append(_arg(alias_object(aliases, OUT / "aliases.obj")))
    root = build.vc71_root()
    linker = root / "Vc7" / "bin" / "link.exe"
    command = [str(linker), "/NOLOGO", "/FORCE", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
               "/SUBSYSTEM:WINDOWS", "/ENTRY:WinMainCRTStartup", f"/OUT:{_arg(OUT / (tag + '.exe'))}", f"@{_arg(rsp)}", *extra]
    if sys.platform != "win32":
        command.insert(0, "wine")
    started = time.time()
    result = subprocess.run(command, capture_output=True, text=True, errors="replace",
                            env=build.compiler_environment(root), cwd=ROOT)
    (OUT / f"{tag}.log").write_text(result.stdout + result.stderr, encoding="utf-8")
    return result.stdout + result.stderr, time.time() - started, result.returncode


def classify(log, rows):
    pinned = pins()
    data = data_names()
    by_address = collections.defaultdict(list)
    for row in rows:
        by_address[int(row["target_rva"], 16)].append(row)
    unresolved = {}
    duplicates = collections.defaultdict(set)
    for line in log.splitlines():
        found = UNRESOLVED.search(line)
        if found:
            symbol = found.group(1) or found.group(2)
            referrer = REFERRER.match(line)
            entry = unresolved.setdefault(symbol, {"refs": set()})
            if referrer:
                entry["refs"].add(Path(referrer.group(1)).name)
            continue
        found = DUPLICATE.match(line)
        if found:
            duplicates[found.group(2) or found.group(3)].update({Path(found.group(1)).name, Path(found.group(4)).name})
    classes = collections.Counter()
    detail = {}
    for symbol, entry in unresolved.items():
        address = pinned.get(symbol)
        if symbol.startswith("__imp_"):
            kind = "import"
        elif symbol.startswith(("??_7", "??_R")):
            kind = "vtable/rtti"
        elif symbol in data:
            kind = "data"
        elif address is not None:
            owners = [r for r in by_address.get(address, []) if not r["name"].startswith("?j_")]
            if owners and any(not build_dump(r) for r in owners):
                kind = "alias"
                entry["defined_as"] = sorted(r["name"] for r in owners if not build_dump(r))[:3]
            elif owners:
                kind = "dump"
            else:
                kind = "pinned-elsewhere"
            entry["address"] = f"0x{address:08X}"
        else:
            kind = "unpinned"
        classes[kind] += 1
        entry["kind"] = kind
        entry["refs"] = sorted(entry["refs"])[:5]
        detail[symbol] = entry
    dup_kinds = collections.Counter()
    for symbol in duplicates:
        dup_kinds["vtable/rtti" if symbol.startswith(("??_7", "??_R")) else
                  "data" if symbol in data else "function/other"] += 1
    return classes, detail, dup_kinds, {s: sorted(o)[:6] for s, o in duplicates.items()}


COMDAT = 0x1000  # IMAGE_SCN_LNK_COMDAT
EXTERNAL = 2      # IMAGE_SYM_CLASS_EXTERNAL


def comdat_conflicts(objs):
    """{name: [(sha, size, obj), ...]} for COMDAT symbols whose copies differ.

    The linker never reports these: inline functions, template instances and
    vftables are COMDATs, and link.exe keeps one copy and discards the rest
    without a word. When two TUs compiled different private copies of a class,
    that silent pick is a one-definition-rule violation, the failure the
    unresolved/duplicate counts cannot show.
    """
    import hashlib
    import struct
    copies = collections.defaultdict(dict)
    for obj in objs:
        try:
            data = obj.read_bytes()
        except OSError:
            continue
        count = struct.unpack_from("<H", data, 2)[0]
        flags, spans = [], []
        for index in range(count):
            offset = 20 + index * 40
            size, pointer = struct.unpack_from("<II", data, offset + 16)
            flags.append(struct.unpack_from("<I", data, offset + 36)[0])
            spans.append((pointer, size))
        for symbol in build.read_object_symbols(data):
            section = symbol["section"]
            if (symbol["storage"] != EXTERNAL or section <= 0 or section > count
                    or not flags[section - 1] & COMDAT):
                continue
            pointer, size = spans[section - 1]
            body = data[pointer:pointer + size]
            digest = hashlib.sha1(body).hexdigest()[:12]
            copies[symbol["name"]].setdefault(digest, (size, obj.name))
    return {name: [(sha, size, obj) for sha, (size, obj) in found.items()]
            for name, found in copies.items() if len(found) > 1}


def build_dump(row):
    """Not a C++ definition: a gen-dump row (349 live in gen_small C++), MASM, or an __emit lift."""
    return build.is_scaffold_row(row) or row["source"].endswith(".asm") or "__emit" in row.get("notes", "")


def report(census):
    print(f"link census {census['when']}: {census['objects']:,} objects linked, "
          f"{census['missing']:,} missing, link {census['seconds']:.0f}s")
    print(f"  unresolved names: {sum(census['unresolved_classes'].values()):,}")
    for kind, count in sorted(census["unresolved_classes"].items(), key=lambda kv: -kv[1]):
        print(f"    {kind:18} {count:8,}")
    print(f"  duplicate definitions: {sum(census['duplicate_classes'].values()):,}")
    for kind, count in sorted(census["duplicate_classes"].items(), key=lambda kv: -kv[1]):
        print(f"    {kind:18} {count:8,}")
    conflicts = census.get("comdat_conflicts", {})
    vtables = sum(1 for name in conflicts if name.startswith(("??_7", "??_R")))
    print(f"  COMDAT copies that differ (linker keeps one silently): {len(conflicts):,} "
          f"({vtables:,} vftable/RTTI)")
    scaffold = census.get("scaffold")
    if scaffold and scaffold.get("crashed"):
        print(f"  with the alias scaffold ({scaffold['aliases']:,} entries): LINK DIED -- {scaffold['crashed']}; "
              "no counts")
    elif scaffold:
        print(f"  with the alias scaffold ({scaffold['aliases']:,} weak-external aliases): "
              f"{sum(scaffold['unresolved_classes'].values()):,} unresolved, "
              f"{sum(scaffold['duplicate_classes'].values()):,} duplicates")
        for kind, count in sorted(scaffold["unresolved_classes"].items(), key=lambda kv: -kv[1]):
            print(f"    {kind:18} {count:8,}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--report", action="store_true", help="summarise build/link_census/census.json")
    ap.add_argument("--scaffold", action="store_true",
                    help="relink with the alias scaffold (a weak external from each called name to the symbol "
                         "defined at its pinned address) and report what remains")
    ap.add_argument("--history", action="store_true",
                    help="append this census to targets/game/reverse/link_census_history.csv (the weekly trend)")
    ap.add_argument("--scaffold-limit", type=int, default=0,
                    help="use only the first N aliases (bisecting a linker failure)")
    args = ap.parse_args(argv)
    path = OUT / "census.json"
    if args.report:
        report(json.loads(path.read_text(encoding="utf-8")))
        return 0
    rows = ledger()
    present, missing = objects(rows)
    if missing:
        print(f"link_census: {len(missing):,} objects missing (run the full ./build.sh first); "
              f"linking the {len(present):,} present", file=sys.stderr)
    log, seconds, _ = link(present)
    crashed = FATAL.search(log)
    if crashed:
        # A linker that dies prints no per-symbol errors, which would read as
        # "0 unresolved": never report counts from a crashed link.
        raise SystemExit(f"link_census: the link died ({crashed.group(0).strip()}); no counts recorded")
    classes, detail, dup_kinds, dups = classify(log, rows)
    census = {"when": time.strftime("%Y-%m-%d %H:%M"), "objects": len(present), "missing": len(missing),
              "seconds": seconds, "unresolved_classes": dict(classes), "duplicate_classes": dict(dup_kinds),
              "unresolved": detail, "duplicates": dups, "comdat_conflicts": comdat_conflicts(present),
              "missing_objects": [str(p.relative_to(ROOT)) for p in missing[:200]]}
    if args.scaffold:
        wanted = [name for name, entry in detail.items() if entry["kind"] in ("alias", "dump", "pinned-elsewhere")]
        table = alias_scaffold(rows, wanted)
        if args.scaffold_limit:
            table = dict(sorted(table.items())[:args.scaffold_limit])
        log, seconds, _ = link(present, table, tag="scaffold")
        crashed = FATAL.search(log)
        after, after_detail, after_dup_kinds, _ = classify(log, rows)
        census["scaffold"] = {"aliases": len(table), "seconds": seconds,
                              "crashed": crashed.group(0).strip() if crashed else None,
                              "unresolved_classes": dict(after), "duplicate_classes": dict(after_dup_kinds),
                              "unresolved": {n: e for n, e in after_detail.items()
                                             if e["kind"] in ("alias", "dump", "pinned-elsewhere")}}
    OUT.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(census, indent=1), encoding="utf-8")
    report(census)
    if args.history:
        append_history(census)
    return 0


HISTORY = ROOT / "targets/game/reverse/link_census_history.csv"
HISTORY_FIELDS = ["date", "commit", "objects", "unresolved", "alias", "pinned_elsewhere", "dump", "data",
                  "import", "unpinned", "duplicates", "comdat_conflicts", "comdat_vtables",
                  "scaffold_aliases", "scaffold_unresolved", "scaffold_crashed"]


def append_history(census):
    """One row per census: the trend of what stands between the tree and a link."""
    unresolved = census["unresolved_classes"]
    conflicts = census.get("comdat_conflicts", {})
    scaffold = census.get("scaffold") or {}
    commit = subprocess.run(["git", "rev-parse", "--short=10", "HEAD"], cwd=ROOT,
                            capture_output=True, text=True).stdout.strip()
    row = {"date": census["when"], "commit": commit, "objects": census["objects"],
           "unresolved": sum(unresolved.values()), "alias": unresolved.get("alias", 0),
           "pinned_elsewhere": unresolved.get("pinned-elsewhere", 0), "dump": unresolved.get("dump", 0),
           "data": unresolved.get("data", 0), "import": unresolved.get("import", 0),
           "unpinned": unresolved.get("unpinned", 0), "duplicates": sum(census["duplicate_classes"].values()),
           "comdat_conflicts": len(conflicts),
           "comdat_vtables": sum(1 for n in conflicts if n.startswith(("??_7", "??_R"))),
           "scaffold_aliases": scaffold.get("aliases", ""),
           "scaffold_unresolved": "" if not scaffold or scaffold.get("crashed")
           else sum(scaffold["unresolved_classes"].values()),
           "scaffold_crashed": (scaffold.get("crashed") or "")[:60]}
    new = not HISTORY.exists()
    with HISTORY.open("a", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, HISTORY_FIELDS, lineterminator="\n")
        if new:
            writer.writeheader()
        writer.writerow(row)
    print(f"link_census: appended {HISTORY.relative_to(ROOT).as_posix()}")


if __name__ == "__main__":
    sys.exit(main())
