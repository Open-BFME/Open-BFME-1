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
  python3 tools/link_census.py --build --history   # compile what changed first (all cores), then census
  python3 tools/link_census.py --report   # summarise the last census
  python3 tools/link_census.py --status   # redo link_status.csv + LINKED from the last log
  python3 tools/link_census.py --selected # which COMDAT copy the link selected (/MAP), vs retail truth

`--history` records the census in link_census_history.csv, with LINKED
(linked_bytes) measured on this tree, and writes
targets/game/reverse/link_status.csv: one row per C/C++
source, `linked=yes` when, in the plain link (no alias scaffold), its object
has no unresolved reference beyond imports and msvcrt.lib, no duplicate, and
no COMDAT copy that differs from retail's body (comdat_losers), no name it
defines or references resolves in the link to a kept definition proven not
retail's (wrong_selected; the /MAP of a second link says which it kept), and
the file holds no hard-coded image address. LINKED is progress.py's DECOMPILED restricted to
those sources; progress.py and the README print the last census's figure.

The census is diagnostic. The image it writes is not expected to run.
"""
import argparse
import collections
import csv
import json
import os
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
    """{name: address} from symbols.csv (first pin for diagnostic identity).
    The byte resolver checks additive candidates. `routes`, when given,
    collects {name: target} from `route=0x...` notes."""
    found = {}
    with (ROOT / "targets/game/reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.reader(handle):
            if len(row) >= 2 and row[1].startswith("0x"):
                found.setdefault(row[0], int(row[1], 16))
                route = re.search(r"route=(0x[0-9A-Fa-f]+)", ",".join(row[2:]))
                if routes is not None and route:
                    routes.setdefault(row[0], int(route.group(1), 16))
    return found


def validated_import_routes(routes=None, scanner=None):
    """Additional REL32 targets that are proven retail import thunks.

    A second symbols.csv pin is not identity evidence. Only an explicit
    `route=` claim re-derived by pin_consistency, at a matched FF 25 import
    thunk, may supplement the first pin when checking a call relocation.
    These addresses never become function-body homes or DIR32 targets.
    """
    import pin_consistency

    routes = pin_consistency.load_routes() if routes is None else routes
    if not routes:
        return {}
    scanner = pin_consistency.Scanner() if scanner is None else scanner
    approved = collections.defaultdict(set)
    for (name, address), claim in routes.items():
        if pin_consistency.route_verdict(scanner, name, address, claim) is not None:
            continue
        if build.read_target_bytes(address, 2) == b"\xff\x25":
            approved[_normal(name)].add(address)
    return dict(approved)


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


def stub_object(names, path):
    """Write a COFF object defining each name at offset 0 of one 16-byte
    section. It only lets link.exe finish: the census's ~95,000 unresolved
    names are fatal (LNK1120, even under /FORCE) and a failed link writes an
    empty /MAP; absolute symbols instead crash link.exe 7.1 (C0000005)."""
    import struct
    strings, symbols = bytearray(4), bytearray()
    for name in sorted(names):
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, bytes(1))
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + bytes(1))
        symbols += field + struct.pack("<IhHBB", 0, 1, 0, EXTERNAL, 0)
    strings[0:4] = struct.pack("<I", len(strings))
    body = bytes([0xCC]) * 16
    table = 20 + 40 + len(body)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, len(symbols) // 18, 0, 0)
    section = b".text".ljust(8, bytes(1)) + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x60500020)
    path.write_bytes(header + section + body + bytes(symbols) + bytes(strings))
    return path


def _arg(path):
    """A repo-relative, forward-slash path, as build.py passes cl.exe: under Wine
    an absolute POSIX path (/home/...) would read as a link.exe option."""
    return Path(path).resolve().relative_to(ROOT.resolve()).as_posix()


def link(objs, aliases=None, tag="census", extra=(), options=()):
    OUT.mkdir(parents=True, exist_ok=True)
    rsp = OUT / "objects.rsp"
    rsp.write_text("\n".join(f'"{_arg(o)}"' for o in objs) + "\n", encoding="utf-8")
    extra = [_arg(path) for path in extra] + list(options)
    if aliases:
        extra.append(_arg(alias_object(aliases, OUT / "aliases.obj")))
    root = build.vc71_root()
    linker = root / "Vc7" / "bin" / "link.exe"
    command = [str(linker), "/NOLOGO", "/FORCE", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
               "/SUBSYSTEM:WINDOWS", "/ENTRY:WinMainCRTStartup", f"/OUT:{_arg(OUT / (tag + '.exe'))}", f"@{_arg(rsp)}", *extra]
    if sys.platform != "win32":
        command.insert(0, "wine")
    started = time.time()
    # LNK1104 on the output (a scanner holding the new .exe) failed one run on
    # 2026-09-29 and linked on the next try: retry that one error, nothing else.
    for attempt in range(3):
        result = subprocess.run(command, capture_output=True, text=True, errors="replace",
                                env=build.compiler_environment(root), cwd=ROOT)
        if f"LNK1104: cannot open file '{_arg(OUT / (tag + '.exe'))}'" not in result.stdout + result.stderr:
            break
        if attempt < 2:
            time.sleep(10)
    (OUT / f"{tag}.log").write_text(result.stdout + result.stderr, encoding="utf-8")
    return result.stdout + result.stderr, time.time() - started, result.returncode


def fresh_outputs(*paths):
    """Delete a link's outputs before it runs, so any that exist afterwards
    were written by this invocation (a timestamp window cannot prove that)."""
    for path in paths:
        try:
            path.unlink()
        except FileNotFoundError:
            pass
        except OSError as exc:
            raise SystemExit(f"link_census: cannot remove the previous {path.name} ({exc}); a stale output "
                             "would read as this link's")


def unexplained_exit(code, log, output=None):
    """Refuse a link that did not complete: a termination by exception or
    signal (an NTSTATUS such as 0xC0000005, a negative code) whatever the log
    says before it; a failing exit the linker's own diagnostics do not
    explain (under /FORCE, the LNK errors and warnings the census counts);
    and, given `output` (removed by fresh_outputs before the link), no PE
    image written there by this run. Nothing is ever recorded as a census
    with nothing wrong."""
    if code < 0 or code > 0xFFFF:
        raise SystemExit(f"link_census: link.exe terminated abnormally (exit 0x{code & 0xFFFFFFFF:08X}); "
                         "no counts recorded")
    if code and not re.search(r"\b(?:error|warning) LNK\d+", log):
        raise SystemExit(f"link_census: link.exe exited {code} with no linker diagnostic; no counts recorded")
    if output is not None:
        try:
            head = output.read_bytes()[:2]
        except OSError:
            head = b""
        if head != b"MZ":
            raise SystemExit(f"link_census: link.exe exited {code} but wrote no image at {output.name}; "
                             "no counts recorded")


def classify(log, rows):
    pinned = pins()
    data = data_names()
    naked = naked_rows()
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
            if owners and any(not build_dump(r, naked) for r in owners):
                kind = "alias"
                entry["defined_as"] = sorted(r["name"] for r in owners if not build_dump(r, naked))[:3]
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
WEAK_EXTERNAL = 105  # IMAGE_SYM_CLASS_WEAK_EXTERNAL: a vftable slot's ??_E deleting destructor


def _coff_symbols(data):
    """[{index, name, section, storage, value}] for every symbol record, by raw
    index (aux records occupy indices too, which relocations count)."""
    import struct
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    out, index = [], 0
    while index < count:
        record = data[table + 18 * index:table + 18 * index + 18]
        if record[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", record, 4)[0]
            name = data[strings + offset:data.index(b"\0", strings + offset)]
        else:
            name = record[:8].rstrip(b"\0")
        value, section, _, storage, aux = struct.unpack_from("<IhHBB", record, 8)
        out.append({"index": index, "name": name.decode("latin-1"), "section": section, "storage": storage,
                    "value": value})
        index += 1 + aux
    return out


def _comdat_sections(data):
    """(symbol, body, relocs, digest, size) for each external COMDAT symbol
    in one COFF object. `body` is the section's raw bytes (None when
    uninitialized); `relocs` is [(offset, type, referent symbol)], a
    content-named referent (RetailTruth.CONSTANT) carrying its bytes.

    The digest covers the section's bytes AND its relocations (offset, type,
    target, weak externals included): two vftables with identical bytes whose
    slots point at different functions are different copies. A TU-local target
    (a string literal, a static) is named per TU, so it counts only as "local";
    an anonymous namespace's per-TU hash is normalised. An uninitialized section
    has no bytes to hash, only a size.
    """
    import hashlib
    import struct
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    symbols = _coff_symbols(data)
    by_index = {symbol["index"]: symbol for symbol in symbols}
    sections = []
    for index in range(count):
        offset = 20 + optional + index * 40
        size, pointer, relocs = struct.unpack_from("<III", data, offset + 16)
        nrelocs = struct.unpack_from("<H", data, offset + 32)[0]
        flags = struct.unpack_from("<I", data, offset + 36)[0]
        sections.append((size, pointer, relocs, nrelocs, flags))
    for symbol in symbols:
        section = symbol["section"]
        if symbol["storage"] != EXTERNAL or section <= 0 or section > count:
            continue
        size, pointer, relocs, nrelocs, flags = sections[section - 1]
        if not flags & COMDAT:
            continue
        body = data[pointer:pointer + size] if pointer else None
        digest = hashlib.sha1(body if body is not None else b"uninitialized %d" % size)
        found = []
        for at in range(relocs, relocs + 10 * nrelocs, 10):
            where, target, kind = struct.unpack_from("<IIH", data, at)
            referent = by_index.get(target, {"name": "?", "storage": 0, "section": 0, "value": 0})
            if referent["name"].startswith(RetailTruth.CONSTANT) and 0 < referent["section"] <= count:
                length, start = sections[referent["section"] - 1][:2]
                referent = {**referent, "content": data[start + referent["value"]:start + length] if start else None}
            label = (_normal(referent["name"]) if referent["storage"] in (EXTERNAL, WEAK_EXTERNAL) else "local")
            digest.update(b"%d:%d:" % (where, kind) + label.encode("latin-1") + b";")
            found.append((where, kind, referent))
        yield symbol, body, found, digest.hexdigest()[:12], size


def _normal(name):
    """A name with its anonymous namespace's per-TU hash normalised."""
    return re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", name)


def comdat_bodies(obj):
    """[(name, digest, size)] for each external COMDAT symbol an object defines
    (see _comdat_sections for what the digest covers)."""
    try:
        data = obj.read_bytes()
    except OSError:
        return []
    return [(symbol["name"], digest, size) for symbol, _, _, digest, size in _comdat_sections(data)]


class RetailTruth:
    """Is a COMDAT copy the body retail shipped?

    A COMDAT symbol whose ledger row (functions.csv, else a symbols.csv pin)
    gives a retail address is judged against retail itself: its bytes must
    equal retail's at that address outside the relocation fields, and every
    relocation must land where retail's instruction lands. A relocation's
    target NAME is resolved the way an identity is, not the way the byte gate
    resolves a call: a ledger row first (never an icf-owner= over-claim:
    __purecall's row sits on one of many `xor eax,eax; ret` bodies), and a
    symbols.csv pin only for a name with no row (plus its numeric route=), because
    symbols.csv is an ADDITIVE candidate list and a pin on the wrong body
    still byte-matches. That is exactly how
    ??1AsciiString@@QAE@XZ's owner copy passed the gate: retail 0x5EE90 is
    `jmp 0x887940` (releaseBuffer), the owner's copy jumps to
    ??1?$StringBase@D@@AAE@XZ, whose row is 0x5E490, and a pin of that name to
    0x887940 hid the difference. Data names resolve through
    dir32_addresses.csv, __imp_ names to retail's import slot, and a label in
    the copy's own section to the same offset in retail. An incremental-link
    stub (a `jmp` packed between other `jmp`s) stands for its target on either
    side; a padded 5-byte `jmp` is a function that tail-jumps (0x5E490 is
    ~StringBase's own body, not a stub) and is never followed. symbols.csv
    holds VAs and RVAs alike, so a pin at or above the image base is read both
    ways. A TU-local referent (a static, `_$E2`, `$S1`) is named per TU, so it
    has no address to check; a string literal or float constant (`??_C@`,
    `__real@`) is named by its content and retail holds several copies of
    some ("" at least twice), so it is checked by content: retail's bytes at
    the target must be the constant's own. Additional FF 25 import routes
    independently verified by pin_consistency may match REL32 calls, but
    never supply body homes or data-pointer targets.

    An address several ledger names claim (0x5E6F0 for ??8 of eight
    VectorClass instances) proves nothing when it disagrees: retail had no
    ICF, so most of those claims are wrong, and the mismatch is the ledger's.

    verdict() returns "retail" (every byte and relocation proven), "wrong"
    (a byte or a resolvable relocation differs from a single-claim address),
    "unknown" (nothing disproves it, but a relocation names something with no
    known address, or only a shared claim disagrees) or None (the symbol
    itself has no retail address: retail truth cannot judge it).
    """

    DIR32, DIR32NB, REL32 = 0x0006, 0x0007, 0x0014
    ABSOLUTE = {"__except_list": 0}  # msvcrt.lib's absolute symbols (fs:[0])
    CONSTANT = ("??_C@", "__real@")  # content-named: retail may hold several copies

    @staticmethod
    def _rvas(address):
        """symbols.csv mixes RVAs and VAs: 0x0044A061 is VA 0x0044A061 of
        RVA 0x4A061. Both readings are candidates; a pin is only a candidate."""
        return {address, address - BASE} if address >= BASE else {address}

    def __init__(self, rows):
        routes = {}
        pinned = pins(routes)
        self.ledger = collections.defaultdict(set)
        names_at = collections.defaultdict(set)
        for row in rows:
            notes = row.get("notes") or ""
            if "icf-owner=" in notes:
                continue  # a second name on an address: an over-claim to retire, not an identity
            address = int(row["target_rva"], 16)
            names = {row["name"]} if "gen-alias" in notes else {row["name"], build.ledger_object_symbol(row)}
            for name in names:  # a gen-alias twin's object symbol names its original, not the twin
                self.ledger[_normal(name)].add(address)
            names_at[address].add(row["name"])
        # An address several names claim is an unresolved over-claim (retail
        # had no ICF, so at most one of them is right): a mismatch against it
        # proves nothing about the copy, only about the ledger.
        self.shared = {address for address, names in names_at.items() if len(names) > 1}
        self.pinned = collections.defaultdict(set)
        for name, address in pinned.items():
            self.pinned[_normal(name)] |= self._rvas(address)
        for name, address in routes.items():  # where calls ENCODE the name: an ILT or import stub
            key = _normal(name)
            (self.ledger[key] if key in self.ledger else self.pinned[key]).update(self._rvas(address))
        self.import_routes = validated_import_routes()
        with (ROOT / "targets/game/reverse/dir32_addresses.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):  # a data name: pin or dir32 entry, either may be right
                self.pinned[_normal(row["name"])].add(int(row["va"], 16) - BASE)
        self.slots = collections.defaultdict(set)
        for name, address in retail_import_slots():
            self.slots[name].add(address)
        self.image, self.sections = build.exe_image()
        self._cache = {}

    def addresses(self, name, kind=None):
        """Retail relocation targets, with proven import routes for REL32 only."""
        key = _normal(name)
        if key in self.ledger:
            return self.ledger[key]
        if kind == self.REL32 and key in self.import_routes:
            return set(self.pinned.get(key, ())) | self.import_routes[key]
        if key in self.pinned:
            return self.pinned[key]
        if name.startswith("__imp_"):
            bare = name[len("__imp_"):]
            found = self.slots.get(bare) or self.slots.get(_undecorate(bare))
            return found or None
        return None

    def _read(self, rva, size):
        try:
            offset = build.rva_to_file_offset(self.sections, rva)
        except ValueError:  # outside every section: nothing there to compare
            return None
        chunk = self.image[offset:offset + size]
        return chunk if len(chunk) == size else None

    def _stub(self, address):
        """Where an incremental-link stub at `address` jumps, else None. A stub
        sits in a packed .text table: another `jmp` right before or after it.
        The same byte pattern in data is not executable and proves no route."""
        import struct
        text = next((section for section in self.sections if section["name"] == ".text"), None)
        if text is None or not text["rva"] <= address < text["rva"] + text["size"]:
            return None
        around = self._read(address - 5, 15)
        if around is None or around[5] != 0xE9 or (around[0] != 0xE9 and around[10] != 0xE9):
            return None
        target = address + 5 + struct.unpack_from("<i", around, 6)[0]
        return target if text["rva"] <= target < text["rva"] + text["size"] else None

    def _lands(self, target, expected):
        if target in expected or self._stub(target) in expected:
            return True
        return any(self._stub(address) == target for address in expected)

    @staticmethod
    def _verdict_fingerprint(symbol, relocs):
        """Parts of one copy that can change relocation judgment.

        The COMDAT digest deliberately normalises a TU-local referent to
        ``local`` so equivalent private labels do not manufacture conflicts.
        That digest is therefore too coarse for the verdict cache: a label in
        the COMDAT's own section is checked at its section-relative value, and
        two copies can have the same digest while those values differ.  Keep
        section numbering out of this key (it is TU-dependent); only whether
        the referent is in the symbol's own section affects _judge.
        """
        found = []
        for where, kind, referent in relocs:
            external = referent["storage"] in (EXTERNAL, WEAK_EXTERNAL)
            same_section = referent["section"] == symbol["section"]
            content = referent.get("content")
            # Mirror _judge's branch order exactly.  In particular, absolute
            # symbols are recognized by name regardless of storage class, and
            # a same-section weak external takes the section-relative branch.
            identity = (("absolute", referent["name"]) if
                        kind == RetailTruth.DIR32 and referent["name"] in RetailTruth.ABSOLUTE else
                        ("content", content) if content is not None else
                        ("self", referent["value"]) if same_section and referent["storage"] != EXTERNAL else
                        ("external", _normal(referent["name"])) if external else
                        ("local",))
            found.append((where, kind, identity))
        return symbol["value"], tuple(found)

    def verdict(self, symbol, body, relocs, digest, size):
        home = self.ledger.get(_normal(symbol["name"])) or self.pinned.get(_normal(symbol["name"]))
        if not home:
            return None
        home = set(home) | {self._stub(address) for address in home} - {None}  # a row on an ILT stub
        key = (symbol["name"], digest, self._verdict_fingerprint(symbol, relocs))
        if key not in self._cache:
            results = [self._judge(address - symbol["value"], symbol, body, relocs, size) for address in sorted(home)]
            if all(address in self.shared for address in home):
                results = ["unknown" if result == "wrong" else result for result in results]
            self._cache[key] = ("retail" if "retail" in results else "unknown" if "unknown" in results else "wrong")
        return self._cache[key]

    def _judge(self, start, symbol, body, relocs, size):
        import struct
        if body is None:
            return "unknown"
        retail = self._read(start, size)
        if retail is None:
            return "wrong"
        mask = bytearray(body)
        fields = []
        for where, kind, referent in relocs:
            width = 2 if kind == 0x000A else 4  # IMAGE_REL_I386_SECTION is 16-bit
            if where + width > size:
                return "wrong"
            mask[where:where + width] = retail[where:where + width]
            fields.append((where, kind, referent))
        if bytes(mask) != retail:
            return "wrong"
        result = "retail"
        for where, kind, referent in fields:
            addend = struct.unpack_from("<i", body, where)[0] if kind != 0x000A else 0
            value = struct.unpack_from("<i", retail, where)[0] if kind != 0x000A else 0
            if kind == self.DIR32 and referent["name"] in self.ABSOLUTE:
                if (value - addend) & 0xFFFFFFFF != self.ABSOLUTE[referent["name"]]:
                    return "wrong"
                continue
            if kind == self.DIR32:
                target = (value - addend - BASE) & 0xFFFFFFFF
            elif kind == self.DIR32NB:
                target = (value - addend) & 0xFFFFFFFF
            elif kind == self.REL32:
                target = start + where + 4 + value - addend
            else:
                result = "unknown"
                continue
            if referent.get("content") is not None:
                if self._read(target, len(referent["content"])) != referent["content"]:
                    return "wrong"
                continue
            if referent["section"] == symbol["section"] and referent["storage"] != EXTERNAL:
                expected = {start + referent["value"]}  # a label in this very section
            elif referent["storage"] in (EXTERNAL, WEAK_EXTERNAL):
                expected = self.addresses(referent["name"], kind)
            else:  # a static's name is per TU (_$E2, $SG1234): no address to check
                expected = None
            if not expected:
                result = "unknown"
            elif not self._lands(target, expected):
                if not all(address in self.shared for address in expected):
                    return "wrong"
                result = "unknown"
        return result


_TRUTH = None


def _truth_init(rows):
    global _TRUTH
    _TRUTH = RetailTruth(rows)


def comdat_conflicts(objs):
    """{name: [(sha, size, obj), ...]} for COMDAT symbols whose copies differ.

    The linker never reports these: inline functions, template instances and
    vftables are COMDATs, and link.exe keeps one copy and discards the rest
    without a word. When two TUs compiled different private copies of a class,
    that silent pick is a one-definition-rule violation, the failure the
    unresolved/duplicate counts cannot show.
    """
    copies = collections.defaultdict(dict)
    for obj in objs:
        for name, digest, size in comdat_bodies(obj):
            copies[name].setdefault(digest, (size, obj.name))
    return {name: [(sha, size, obj) for sha, (size, obj) in found.items()]
            for name, found in copies.items() if len(found) > 1}


def keep_rule(copies):
    """({object: loses?}, rule) for one COMDAT symbol's copies [(object, digest,
    verdict)] in link order.

    `retail` when retail truth can judge the symbol (it has a retail address):
    a copy proven wrong loses; a proven copy never does; a copy whose bytes
    match but whose relocations cannot all be resolved loses only when it
    differs from the kept copy (the first proven one, else the first
    unresolved one), since nothing shows it is right. `first` when it cannot:
    link.exe keeps the first copy in link order, so a copy that differs from
    that one loses. Majority is never used: it would let the most-copied
    private class decide what retail shipped.
    """
    verdicts = [verdict for _, _, verdict in copies]
    if all(verdict is None for verdict in verdicts):
        kept = copies[0][1]
        return {obj: digest != kept for obj, digest, _ in copies}, "first"
    proven = [digest for _, digest, verdict in copies if verdict == "retail"]
    unknown = [digest for _, digest, verdict in copies if verdict == "unknown"]
    kept = proven[0] if proven else unknown[0] if unknown else None
    loses = {}
    for obj, digest, verdict in copies:
        loses[obj] = verdict == "wrong" or (verdict == "unknown" and digest != kept and digest not in proven)
    return loses, "retail"


def _comdat_selections(data):
    """{section number: COMDAT selection} from each section definition's aux
    record (IMAGE_COMDAT_SELECT_NODUPLICATES = 1, _ANY = 2, ...)."""
    import struct
    table, count = struct.unpack_from("<II", data, 8)
    found, index = {}, 0
    while index < count:
        record = table + 18 * index
        value, section, _, storage, aux = struct.unpack_from("<IhHBB", data, record + 8)
        if storage == 3 and aux and value == 0 and section > 0:  # IMAGE_SYM_CLASS_STATIC section symbol
            found.setdefault(section, data[record + 18 + 14])
        index += 1 + aux
    return found


class MissingObject(RuntimeError):
    """An object a check needs cannot be read. Never an empty object: an
    object with no facts has no blockers and would read as linking."""


def object_facts(obj, truth=None):
    """(COMDAT copies [(name, digest, size, verdict)], exclusive definitions,
    undefined externals, weak externals [(name, default)]) of one object:
    what a link needs to know about it. An unreadable object raises
    MissingObject.
    A definition is exclusive when link.exe refuses a second one (LNK2005):
    in an ordinary section, or in a COMDAT whose selection is NODUPLICATES,
    which /Gy gives every non-inline function."""
    truth = truth or _TRUTH
    try:
        data = obj.read_bytes()
    except OSError as exc:
        raise MissingObject(f"{obj}: cannot read the object ({exc})") from exc
    import struct
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    comdat = {index + 1 for index in range(count)
              if struct.unpack_from("<I", data, 20 + optional + index * 40 + 36)[0] & COMDAT}
    selections = _comdat_selections(data)
    strong, undefined = [], []
    for symbol in _coff_symbols(data):
        if symbol["storage"] != EXTERNAL:
            continue
        if symbol["section"] == 0:
            if symbol["value"] == 0:  # a nonzero value is a common symbol: a definition that merges
                undefined.append(symbol["name"])
        elif symbol["section"] not in comdat or selections.get(symbol["section"]) == 1:
            strong.append(symbol["name"])
    copies = [(symbol["name"], digest, size, truth.verdict(symbol, body, relocs, digest, size))
              for symbol, body, relocs, digest, size in _comdat_sections(data)]
    return copies, strong, undefined, _weak_externals(data)


def _weak_externals(data):
    """[(name, default)] for each weak external: the name resolves to
    `default` when no object defines it (IMAGE_WEAK_EXTERN aux TagIndex)."""
    import struct
    names = {symbol["index"]: symbol["name"] for symbol in _coff_symbols(data)}
    table, count = struct.unpack_from("<II", data, 8)
    found, index = [], 0
    while index < count:
        storage, aux = data[table + 18 * index + 16], data[table + 18 * index + 17]
        if storage == WEAK_EXTERNAL and aux:
            tag = struct.unpack_from("<I", data, table + 18 * (index + 1))[0]
            found.append((names.get(index, "?"), names.get(tag, "?")))
        index += 1 + aux
    return found


def read_facts(objs, rows):
    """object_facts for every object, in parallel (BUILD_POOL processes)."""
    workers = build._pool_size()
    if workers > 1:
        import concurrent.futures
        with concurrent.futures.ProcessPoolExecutor(workers, initializer=_truth_init, initargs=(rows,)) as pool:
            return list(pool.map(object_facts, objs, chunksize=64))
    truth = RetailTruth(rows)
    return [object_facts(obj, truth) for obj in objs]


def comdat_losers(objs, rows=None, stats=None, facts=None):
    """{object name: {symbol}} for COMDAT copies that are not retail's body.

    keep_rule() decides each symbol: by retail truth where the ledger gives it
    a retail address, else by link order (link.exe keeps the first copy, so an
    object whose copy differs from that one runs someone else's code). Before
    2026-09-29 every symbol used link order, so an arbitrary first object
    decided who lost: for ??1AsciiString@@QAE@XZ the first object held a
    minority variant, and the retail-true copies were the ones charged.
    `stats`, when given, collects how many symbols and losing copies each
    rule decided. `facts` is read_facts(objs), read here when not given."""
    rows = ledger() if rows is None else rows
    facts = read_facts(objs, rows) if facts is None else facts
    copies = collections.defaultdict(list)
    for obj, (found, _, _, _) in zip(objs, facts):
        for name, digest, _, verdict in found:
            copies[name].append((obj.name, digest, verdict))
    losers = collections.defaultdict(set)
    stats = stats if stats is not None else {}
    for name, found in copies.items():
        loses, rule = keep_rule(found)
        stats[f"symbols_{rule}"] = stats.get(f"symbols_{rule}", 0) + 1
        for obj, lost in loses.items():
            if lost:
                losers[obj].add(name)
                stats[f"losers_{rule}"] = stats.get(f"losers_{rule}", 0) + 1
    return losers


def ledger_owners(rows):
    """{name: {object}}: the object of each ledger row naming it (its object
    symbol too), never an icf-owner over-claim or a scaffold row. For a name
    several objects define, the owner's is retail's definition."""
    owners = collections.defaultdict(set)
    for row in rows:
        if "icf-owner=" not in (row.get("notes") or "") and not build.is_scaffold_row(row):
            for name in {row["name"], build.ledger_object_symbol(row)}:
                owners[name].add(build.row_object(row).name)
    return owners


def judge_selected(holder, copies, definers, exclusive, owners):
    """Is the definition the link kept for one name retail's?

    `holder` is the object whose definition the link kept (None when the map
    does not say); `copies` {object: (digest, verdict)} the name's COMDAT
    copies with their retail-truth verdicts; `definers` every object defining
    it; `exclusive` those whose definition is exclusive (an ordinary section or
    a NODUPLICATES COMDAT); `owners` the ledger owner objects.

    "wrong" when the kept copy is proven not retail's body, or when two or
    more objects define the name, one exclusively, and the kept definition is
    not a ledger owner's (operator new/delete kept from GameMemory.obj while
    the retail body is mem_ops.obj's). Proven bytes decide before ownership.
    "ok" when it is proven (its bytes, or the owner's matched row); "unknown"
    when the choice matters (copies differ, or a duplicate) and nothing proves
    it either way; None when there is nothing to choose between."""
    if holder is None or holder not in definers:
        return "unknown" if len(definers) > 1 else None
    _, verdict = copies.get(holder, (None, None))
    if verdict == "wrong":
        return "wrong"
    if verdict == "retail":
        return "ok"
    if len(definers) > 1 and exclusive:
        mine = owners & definers
        if mine:
            return "ok" if holder in mine else "wrong"
        return "unknown"
    if len({digest for digest, _ in copies.values()}) > 1:
        return "unknown"
    return None


def touched_names(fact):
    """Every name one object's facts define or reference (weak externals and
    their defaults included)."""
    copies, strong, undefined, weaks = fact
    names = {name for name, _, _, _ in copies} | set(strong) | set(undefined)
    for name, default in weaks:
        names.update((name, default))
    return names


def selection_verdicts(present, facts, owners, kept):
    """({name: result}, {name: holder index or None}) for every name the census
    objects define, judged on the definition the link kept (`kept`, from the
    /MAP: selected_definitions). The second map lists only the names whose
    kept definition is NOT the first definer in link order (link.exe keeps the
    first for all but a handful), so link_check can predict the holder the way
    the census saw it."""
    position = {obj.name: index for index, obj in enumerate(present)}
    copies = collections.defaultdict(dict)
    definers = collections.defaultdict(set)
    exclusive = collections.defaultdict(set)
    for obj, (found, strong, _, _) in zip(present, facts):
        for name, digest, _, verdict in found:
            copies[name].setdefault(obj.name, (digest, verdict))
            definers[name].add(obj.name)
        for name in strong:
            definers[name].add(obj.name)
            exclusive[name].add(obj.name)
    results, exceptions = {}, {}
    for name, objs in definers.items():
        holder = kept.get(name)
        holder = holder if holder in objs else None
        first = min(objs, key=position.__getitem__)
        if holder != first:
            exceptions[name] = position[holder] if holder is not None else None
        result = judge_selected(holder, copies[name], objs, exclusive[name], owners.get(name, set()))
        if result is not None:
            results[name] = result
    return results, exceptions


MAP_PUBLIC = re.compile(r"^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+[0-9A-Fa-f]{8}\s+(?:f\s+)?(?:i\s+)?(.+?)\s*$")


def selected_definitions(map_text):
    """{symbol: object} for the definition link.exe put in the image, from
    the /MAP file's "Publics by Value" (its Lib:Object column)."""
    found = {}
    for line in map_text.splitlines():
        if line.lstrip().startswith("Static symbols"):
            break
        match = MAP_PUBLIC.match(line)
        if match:
            found.setdefault(match.group(1), match.group(2).split(":")[-1])
    return found


SELECTED = OUT / "selected.csv"
DUPLICATES = OUT / "duplicates_selected.csv"
ALIASED = OUT / "aliased.csv"
SELECTION = OUT / "selection.json"


def selection_report(present, facts, rows, clean_objects, map_text, log):
    """What the link actually put in the image, against retail truth.

    The per-file rule asks whether a file's OWN copy is retail's body. The
    image holds one copy per COMDAT symbol, the one link.exe selected, so a
    clean file can still run a wrong copy another object supplied. From the
    /MAP, for every COMDAT symbol whose copies differ: which object's copy was
    selected, its verdict, and whether it was the first in link order.
    `clean_objects` are the objects of files counted as linked; one depends on
    a symbol when it holds a copy of it or references it. Also every name
    that only resolves to a DIFFERENT name: a weak external falling back to
    its default, or an unresolved name the alias scaffold (a pin's address)
    would point at another definition. And every name with more than one
    definition at least one of which is exclusive (an ordinary section or a
    NODUPLICATES COMDAT: LNK2005, a warning LNK4006 under /FORCE): which
    object's definition the link kept, and whether that object is the ledger
    row's own (operator new/delete: mem_ops.cpp holds the retail body,
    GameMemory.cpp another, and link order keeps GameMemory.cpp's). Writes
    selected.csv, duplicates_selected.csv, aliased.csv and selection.json
    under build/link_census/; measures, changes no rule."""
    kept = selected_definitions(map_text)
    position = {obj.name: index for index, obj in enumerate(present)}
    copies = collections.defaultdict(list)
    users = collections.defaultdict(set)
    defined = set()
    weak = collections.defaultdict(set)
    definers, exclusive = collections.defaultdict(set), collections.defaultdict(set)
    for obj, (found, strong, undefined, weaks) in zip(present, facts):
        for name, digest, _, verdict in found:
            copies[name].append((obj.name, digest, verdict))
            users[name].add(obj.name)
            defined.add(name)
            definers[name].add(obj.name)
        defined.update(strong)
        for name in strong:
            definers[name].add(obj.name)
            exclusive[name].add(obj.name)
            users[name].add(obj.name)
        for name in undefined:
            users[name].add(obj.name)
        for name, default in weaks:
            weak[(name, default)].add(obj.name)
    table, counts = [], collections.Counter()
    bad = collections.defaultdict(set)  # clean object -> (symbol, verdict of the selected copy)
    for name, found in copies.items():
        if len({digest for _, digest, _ in found}) < 2:
            continue
        holder = kept.get(name, "")
        verdicts = {obj: verdict for obj, _, verdict in found}
        verdict = verdicts[holder] if holder in verdicts else "not-in-map"
        verdict = verdict or "no-address"
        first = min(found, key=lambda copy: position[copy[0]])[0]
        table.append({"symbol": name, "copies": len(found), "digests": len({d for _, d, _ in found}),
                      "selected_object": holder, "selected_verdict": verdict,
                      "selected_is_first": "yes" if holder == first else "no",
                      "retail_true_copies": sum(1 for _, _, v in found if v == "retail")})
        counts[f"selected_{verdict}"] += 1
        counts["selected_first" if holder == first else "selected_not_first"] += 1
        if verdict != "retail":
            for obj in users[name] & clean_objects:
                bad[obj].add((name, verdict))
    with SELECTED.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["symbol", "copies", "digests", "selected_object", "selected_verdict",
                                         "selected_is_first", "retail_true_copies"], lineterminator="\n")
        writer.writeheader()
        writer.writerows(sorted(table, key=lambda row: row["symbol"]))
    owners = ledger_owners(rows)
    duplicates, owner_misses = [], collections.defaultdict(set)
    for name, objs in exclusive.items():
        if len(definers[name]) < 2:
            continue
        holder = kept.get(name, "")
        first = min(definers[name], key=lambda obj: position[obj])
        mine = owners.get(name, set()) & definers[name]
        state = "no-owner" if not mine else "owner" if holder in mine else "not-owner"
        duplicates.append({"symbol": name, "definers": len(definers[name]), "exclusive": len(objs),
                           "selected_object": holder, "selected_is_first": "yes" if holder == first else "no",
                           "owner_objects": " ".join(sorted(mine)), "selected": state})
        counts[f"duplicate_{state}"] += 1
        if state == "not-owner":
            for obj in users[name] & clean_objects:
                owner_misses[obj].add(name)
    with DUPLICATES.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["symbol", "definers", "exclusive", "selected_object", "selected_is_first",
                                         "owner_objects", "selected"], lineterminator="\n")
        writer.writeheader()
        writer.writerows(sorted(duplicates, key=lambda row: row["symbol"]))
    aliased = []
    for (name, default), objs in sorted(weak.items()):
        if name not in defined and default != name:
            # ??_E (vector deleting dtor) falling back to ??_G (scalar) is how
            # MSVC emits a class nobody deletes as an array: standard, listed.
            aliased.append({"name": name, "via": "weak-external", "resolves_to": default, "excused": "no",
                            "objects": len(objs), "linked_objects": len(objs & clean_objects)})
    _, detail, _, _ = classify(log, rows)
    wanted = [name for name, entry in detail.items() if entry["kind"] in ("alias", "dump", "pinned-elsewhere")]
    referrers = collections.defaultdict(set)
    for line in log.splitlines():
        found, referrer = UNRESOLVED.search(line), REFERRER.match(line)
        if found and referrer:
            referrers[found.group(1) or found.group(2)].add(Path(referrer.group(1)).name)
    crt = build.vc71_root() / "Vc7" / "lib" / "msvcrt.lib"
    runtime, stubs, imported = library_symbols(crt), import_stubs(), retail_imports()
    for name, target in sorted(alias_scaffold(rows, wanted).items()):
        excuse = excused(name, runtime, imported, stubs)  # the real link finds it in an import library
        aliased.append({"name": name, "via": f"pin ({detail[name]['kind']})", "resolves_to": target,
                        "excused": "yes" if excuse else "no", "objects": len(referrers[name]),
                        "linked_objects": len(referrers[name] & clean_objects)})
    with ALIASED.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["name", "via", "resolves_to", "excused", "objects", "linked_objects"],
                                lineterminator="\n")
        writer.writeheader()
        writer.writerows(aliased)
    wrong = {obj for obj, found in bad.items() if any(v == "wrong" for _, v in found)}
    weak_rows = [row for row in aliased if row["via"] == "weak-external"]
    summary = {"conflicted_symbols": len(table), **dict(counts), "linked_files": len(clean_objects),
               "linked_files_on_wrong_selected_copy": len(wrong),
               "linked_files_on_unproven_selected_copy": len(bad),
               "duplicated_symbols": len(duplicates),
               "linked_files_on_non_owner_duplicate": len(owner_misses),
               "top_non_owner_duplicates": collections.Counter(
                   name for found in owner_misses.values() for name in found).most_common(10),
               "weak_fallbacks": len(weak_rows),
               "weak_fallbacks_not_deleting_dtor": sum(1 for row in weak_rows if not (
                   row["name"].startswith("??_E") and row["resolves_to"].startswith("??_G"))),
               "weak_fallbacks_in_linked_files": sum(1 for row in weak_rows if row["linked_objects"]),
               "pin_aliases": len(aliased) - len(weak_rows),
               "pin_aliases_in_linked_files": sum(1 for row in aliased if row["via"] != "weak-external"
                                                  and row["excused"] == "no" and row["linked_objects"]),
               "top_wrong_selected": collections.Counter(
                   name for found in bad.values() for name, v in found if v == "wrong").most_common(10)}
    return summary, bad, owner_misses


def print_selection(summary):
    print(f"  selected COMDAT copies (the /MAP), {summary['conflicted_symbols']:,} symbols whose copies differ:")
    for key in ("retail", "unknown", "wrong", "no-address", "not-in-map", "first", "not_first"):
        print(f"    {key:18} {summary.get('selected_' + key, 0):8,}")
    print(f"  files counted as linked: {summary['linked_files']:,}; "
          f"{summary['linked_files_on_wrong_selected_copy']:,} use a symbol whose selected copy is proven wrong, "
          f"{summary['linked_files_on_unproven_selected_copy']:,} one whose selected copy is not proven retail")
    print(f"  ... those files' LINKED bytes: {summary.get('linked_bytes_on_wrong_selected_copy', 0):,} "
          f"(wrong), {summary.get('linked_bytes_on_unproven_selected_copy', 0):,} (not proven)")
    print(f"  names defined more than once with an exclusive definition: {summary.get('duplicated_symbols', 0):,}; "
          f"the kept definition is the ledger owner's for {summary.get('duplicate_owner', 0):,}, another object's "
          f"for {summary.get('duplicate_not-owner', 0):,}, no owner {summary.get('duplicate_no-owner', 0):,}")
    print(f"  files counted as linked that use a symbol whose kept definition is not its owner's: "
          f"{summary.get('linked_files_on_non_owner_duplicate', 0):,} "
          f"({summary.get('linked_bytes_on_non_owner_duplicate', 0):,} LINKED bytes)")
    print(f"  names resolved only through another name: {summary['weak_fallbacks']:,} weak-external fallbacks "
          f"({summary['weak_fallbacks_not_deleting_dtor']:,} other than ??_E -> ??_G; "
          f"{summary['weak_fallbacks_in_linked_files']:,} used by linked files), {summary['pin_aliases']:,} "
          f"unresolved names a pin would alias ({summary['pin_aliases_in_linked_files']:,} not excused in "
          "linked files)")


def naked_rows():
    """{(name, target_rva)} of the C/C++ rows whose body is naked or __emit
    assembly, by progress.py's scan of the source itself (the rows it counts
    as dumps)."""
    import progress
    return set(progress.naked_cpp_rows_at(progress.matched_at(None), None))


def build_dump(row, naked=frozenset()):
    """Not a C++ definition: a gen-dump row (349 live in gen_small C++), MASM,
    or a naked/__emit body (`naked`, from naked_rows()). Decided from the
    source, never from the note: "exact C++ __emit thunk converted from MASM
    dump" is the note of real C++ (STLRbGlobalBoolIncrementThunk.cpp)."""
    return (build.is_scaffold_row(row) or row["source"].endswith(".asm")
            or (row["name"], row["target_rva"]) in naked)


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
                    help="append this census to targets/game/reverse/link_census_history.csv (the daily trend)")
    ap.add_argument("--scaffold-limit", type=int, default=0,
                    help="use only the first N aliases (bisecting a linker failure)")
    ap.add_argument("--build", action="store_true",
                    help="first compile every matched source whose object is not current (build.compile_rows, "
                         "BUILD_POOL defaults to all cores but two); no byte verification")
    ap.add_argument("--selected", action="store_true",
                    help="relink the last census's objects with /MAP and report which COMDAT copy link.exe selected "
                         "(selected.csv, aliased.csv); on the census's own commit, records nothing")
    ap.add_argument("--status", action="store_true",
                    help="redo link_status.csv and the last history row's LINKED from the last link log, on the census's own commit")
    args = ap.parse_args(argv)
    path = OUT / "census.json"
    if args.report:
        report(json.loads(path.read_text(encoding="utf-8")))
        if SELECTION.exists():
            print_selection(json.loads(SELECTION.read_text(encoding="utf-8")))
        return 0
    if args.selected:
        return selected_main()
    if args.status:
        record(json.loads(path.read_text(encoding="utf-8")), ledger(), rerun=True)
        return 0
    rows = ledger()
    if args.build:
        os.environ.setdefault("BUILD_POOL", str(max(1, (os.cpu_count() or 2) - 2)))
        # BUILD_RECOMPILE_ONLY trusts every object it is not told to rebuild;
        # record(fresh=True) below relies on the full currency check instead.
        os.environ.pop("BUILD_RECOMPILE_ONLY", None)
        started = time.time()
        build.ensure_case_shims()
        build.compile_rows(rows, list(dict.fromkeys(ROOT / row["source"] for row in rows)))
        print(f"link_census: compile {time.time() - started:.0f}s", flush=True)
    present, missing = objects(rows)
    if missing:
        print(f"link_census: {len(missing):,} objects missing (run the full ./build.sh first); "
              f"linking the {len(present):,} present", file=sys.stderr)
    fresh_outputs(OUT / "census.exe")
    log, seconds, code = link(present)
    unexplained_exit(code, log, OUT / "census.exe")
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
        fresh_outputs(OUT / "scaffold.exe")
        log, seconds, code = link(present, table, tag="scaffold")
        unexplained_exit(code, log, OUT / "scaffold.exe")
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
        # --build just proved every object current (compile_is_current, the
        # full gate's own test), so record() need not hash them again.
        record(census, rows, fresh=args.build)
    return 0


def selected_main():
    """--selected: the selection report for the last recorded census, on its
    own tree, from a fresh /MAP link of the same objects."""
    history = read_history()
    changed = subprocess.run(["git", "diff", "--quiet", history[-1]["commit"] if history else "HEAD", "--", "game",
                              "targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv"],
                             cwd=ROOT).returncode if history else 1
    if changed:
        raise SystemExit("link_census: --selected needs the last census's sources and ledger "
                         f"({history[-1]['commit'] if history else 'no census'}); this tree differs")
    rows = ledger()
    present, missing = objects(rows)
    if missing:
        raise SystemExit(f"link_census: {len(missing):,} objects missing")
    sources = _object_sources(rows)
    stale = [obj for obj in present if obj in sources and not object_current(sources[obj], obj)]
    if stale:
        raise SystemExit(f"link_census: {len(stale):,} objects are not current for their source, "
                         f"e.g. {stale[0].name}")
    log = final_log(None)  # the census's own link says which names nothing defines
    map_text = selection_link(present, log)
    with STATUS.open(newline="", encoding="utf-8") as handle:
        clean = {row["source"] for row in csv.DictReader(handle) if row["linked"] == "yes"}
    clean_objects = {build.row_object(row).name for row in rows if row["source"] in clean}
    summary, bad, owner_misses = selection_report(present, read_facts(present, rows), rows, clean_objects,
                                    map_text, log)
    import link_check
    sizes = link_check.source_bytes(clean)
    by_object = {build.row_object(row).name: row["source"] for row in rows if row["source"] in clean}
    wrong = {obj for obj, found in bad.items() if any(verdict == "wrong" for _, verdict in found)}
    summary["linked_bytes_on_wrong_selected_copy"] = sum(sizes.get(by_object.get(obj), 0) for obj in wrong)
    summary["linked_bytes_on_unproven_selected_copy"] = sum(sizes.get(by_object.get(obj), 0) for obj in bad)
    summary["linked_bytes_on_non_owner_duplicate"] = sum(sizes.get(by_object.get(obj), 0) for obj in owner_misses)
    summary["linked_bytes"] = sum(sizes.values())
    SELECTION.write_text(json.dumps(summary, indent=1), encoding="utf-8")
    print_selection(summary)
    return 0


def selection_link(present, log):
    """The /MAP text of a relink of `present` in which every name the plain
    link (`log`) left unresolved is defined in one stub section, so the link
    finishes and the map says which definition it kept for every name.
    /OPT:NOREF keeps every selected COMDAT in the map."""
    missing_names = {found.group(1) or found.group(2) for found in map(UNRESOLVED.search, log.splitlines()) if found}
    stubs = stub_object(missing_names, OUT / "selected_stubs.obj")
    link_map = OUT / "selected.map"
    fresh_outputs(link_map, OUT / "selected.exe")  # a failed link leaves an empty map, never last run's
    relink, _, code = link(present, tag="selected", extra=[stubs],
                           options=["/OPT:NOREF", f"/MAP:{_arg(link_map)}"])
    unexplained_exit(code, relink, OUT / "selected.exe")  # a crash can leave a partial map
    if FATAL.search(relink) or not link_map.exists() or not link_map.stat().st_size:
        raise SystemExit(f"link_census: the /MAP link failed; see {_arg(OUT / 'selected.log')}")
    return link_map.read_text(encoding="latin-1")


def _object_sources(rows):
    """{object: source} for every compiled (C/C++/MASM) row."""
    return {build.row_object(row): ROOT / row["source"] for row in rows
            if Path(row["source"]).suffix.lower() in (".c", ".cpp", ".asm")}


STATUS = ROOT / "targets/game/reverse/link_status.csv"
STATUS_FIELDS = ["source", "linked", "unresolved", "duplicates", "comdat_losers", "addresses", "wrong_selected"]


def final_log(census):
    """The plain link's log. The alias scaffold's link resolves a call through
    a generated weak alias when the called name and the defining name differ;
    that is a naming defect to fix, not a name that resolves."""
    return (OUT / "census.log").read_text(encoding="utf-8", errors="replace")


def library_symbols(path):
    """Public names a COFF archive defines, from its first linker member."""
    import struct
    data = path.read_bytes()
    size = int(data[56:66].decode("ascii").strip())
    body = data[68:68 + size]
    count = struct.unpack(">I", body[:4])[0]
    return {name.decode("latin-1") for name in body[4 + 4 * count:].split(b"\0")[:count]}


def _retail_import_entries():
    """[(dll, name, slot rva)] from retail's import table (every entry is
    imported by name)."""
    import pefile
    pe = pefile.PE(data=build.EXE.read_bytes(), fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    return [(dll.dll.decode("latin-1"), entry.name.decode("latin-1"), entry.address - pe.OPTIONAL_HEADER.ImageBase)
            for dll in pe.DIRECTORY_ENTRY_IMPORT for entry in dll.imports if entry.name]


def retail_imports():
    """{name: {dll, lower case}} for every function retail's import table
    lists (every entry is imported by name)."""
    found = collections.defaultdict(set)
    for dll, name, _ in _retail_import_entries():
        found[name].add(dll.lower())
    return dict(found)


def retail_import_slots():
    """[(name, IAT slot rva)]: where retail's `call [__imp_name]` reads."""
    return [(name, slot) for _, name, slot in _retail_import_entries()]


def _undecorate(name):
    """`_socket@12` -> `socket`: one decoration underscore and a stdcall @N off."""
    return re.sub(r"@\d+$", "", name[1:] if name.startswith("_") else name)


def library_import_thunks(path):
    """{call stub: {(dll, imported name)}} for the short import objects of CODE
    type an import library holds: `_strcpy` in msvcrt.lib forwards to
    MSVCR71's strcpy, `_socket@12` in WSock32.Lib to WSOCK32's socket. Such a
    name resolves in the real link only if the image imports that function.
    The imported name follows the object's name type (IMPORT_OBJECT_NAME,
    _NO_PREFIX, _UNDECORATE); an import by ordinal names its function by the
    undecorated stub name."""
    import struct
    data, at, thunks = path.read_bytes(), 8, collections.defaultdict(set)
    while at + 60 <= len(data):
        try:
            size = int(data[at + 48:at + 58].decode("ascii").strip())
        except ValueError:
            break
        body = data[at + 60:at + 60 + size]
        if body[:4] == b"\0\0\xff\xff" and len(body) > 20:
            kind = struct.unpack_from("<H", body, 18)[0]
            if kind & 3 == 0:  # IMPORT_OBJECT_CODE
                end = body.index(b"\0", 20)
                symbol = body[20:end].decode("latin-1")
                dll = body[end + 1:body.index(b"\0", end + 1)].decode("latin-1").lower()
                name_type = (kind >> 2) & 7
                if name_type == 1:
                    name = symbol
                elif name_type == 2:
                    name = symbol[1:] if symbol[:1] in "?@_" else symbol
                else:
                    name = _undecorate(symbol).split("@")[0] if name_type == 3 else _undecorate(symbol)
                thunks[symbol].add((dll, name))
        at += 60 + size + (size & 1)
    return thunks


def import_stubs():
    """Every call stub the committed toolchain's import libraries define:
    Vc7/lib (msvcrt.lib, kernel32.lib) and Vc7/PlatformSDK/Lib (WSock32.Lib,
    WS2_32.Lib, User32.Lib, ...). Static libraries in those directories hold
    no short import objects and add nothing."""
    root = build.vc71_root() / "Vc7"
    stubs = collections.defaultdict(set)
    for directory in (root / "lib", root / "PlatformSDK" / "Lib"):
        for path in sorted(directory.glob("*")):
            if path.suffix.lower() == ".lib" and path.read_bytes()[:8] == b"!<arch>\n":
                for symbol, targets in library_import_thunks(path).items():
                    stubs[symbol] |= targets
    return dict(stubs)


def excused(symbol, runtime, imported, thunks=None):
    """True for a name the real link resolves without this tree defining it.

    An __imp_ name only when retail imports that function: strip the prefix,
    one decoration underscore and a stdcall @N (__imp__GetModuleFileNameA@12,
    __imp___iob); MSVCR71 exports a few C++ names mangled, so a ?name must
    match as is (??1exception@@UAE@XZ). An address-named slot or a name
    retail does not import is a declaration defect. A call stub an import
    library in the toolchain defines (`_strcpy` in msvcrt.lib, `_socket@12` in
    WSock32.Lib, import_stubs()) counts only when retail imports that function
    from that DLL: `_htons@4` is a WSock32.Lib stub, but retail imports only
    htonl and ntohs, so a direct htons call stays a defect. Any other name
    only when msvcrt.lib (MSVCR71's import library and CRT statics:
    __except_list, __fltused) defines it. `imported` is retail_imports().
    """
    if thunks and symbol in thunks:  # a call stub: only as good as the import behind it
        return any(dll in imported.get(name, ()) for dll, name in thunks[symbol])
    if symbol.startswith("__imp_"):
        name = symbol[len("__imp_"):]
        if name in imported or name.startswith("?"):
            return name in imported  # Miles exports decorated: _AIL_startup@0
        return re.sub(r"@\d+$", "", name[1:] if name.startswith("_") else name) in imported
    return symbol in runtime


def write_status(log, rows, present, meta, kept):
    """One row per C/C++ source: does its object link cleanly on its own terms?

    Per file, not per program: a clean file may still call into one that is
    not. Read from the full plain-link log, not census.json, which keeps five
    referrers per name. The census links /NODEFAULTLIB, so two kinds of
    unresolved name are not held against a file: __imp_ entries and call stubs
    (`_socket@12`) retail imports, which want the import libraries, and names msvcrt.lib defines (retail imports
    MSVCR71.dll, and the ledger's CRT rows are msvcrt.lib members), which the
    real link searches by default -- __except_list alone is referenced by 3,088
    objects. See excused() for exactly which names. A duplicate counts against both definers, since the log cannot say
    which copy is wrong. A COMDAT copy that is not retail's body counts against
    its object (comdat_losers: retail truth where the symbol has a retail
    address, else the copy link.exe keeps, the first in link order). Any hard-coded image address counts too
    (link_debt.addresses): it links, but only while nothing moves.

    And since 2026-09-29 (wrong_selected), a file is not linked when any name
    it defines or references resolves, in the actual link, to a definition
    proven not retail's: the COMDAT copy link.exe kept is proven wrong, or the
    kept one of several definitions is not the ledger owner's
    (judge_selected). `kept` is the /MAP's {name: object}
    (selected_definitions of selection_link). A name with no retail address or
    owner is not held against anyone; the files that depend on such a choice
    are counted (`unknown_only`).

    Returns (clean, files, blocking names, clean under the rule before
    wrong_selected, stats). It also writes build/link_census/link_index.pkl, which tools/link_check.py
    reads to check one file in seconds (`meta` names the census).
    """
    import link_debt
    crt = build.vc71_root() / "Vc7" / "lib" / "msvcrt.lib"
    runtime, thunks = library_symbols(crt), import_stubs()
    imported = retail_imports()
    if present is None:
        present, _ = objects(rows)
    stats = {}
    facts = read_facts(present, rows)
    losers = comdat_losers(present, rows, stats, facts)
    owners = ledger_owners(rows)
    results, exceptions = selection_verdicts(present, facts, owners, kept)
    wrong_selected, unknown_selected = {}, {}
    for obj, fact in zip(present, facts):
        touched = touched_names(fact)
        wrong_selected[obj.name] = sorted(name for name in touched if results.get(name) == "wrong")
        unknown_selected[obj.name] = sum(1 for name in touched if results.get(name) == "unknown")
    print(f"link_census: selected definitions: {sum(1 for r in results.values() if r == 'wrong'):,} names proven "
          f"wrong, {sum(1 for r in results.values() if r == 'unknown'):,} unproven, "
          f"{sum(1 for r in results.values() if r == 'ok'):,} proven; {len(exceptions):,} not the first in link order")
    print(f"link_census: COMDAT keeper: {stats.get('symbols_retail', 0):,} symbols judged by retail truth "
          f"({stats.get('losers_retail', 0):,} losing copies), {stats.get('symbols_first', 0):,} with no retail "
          f"address by link order ({stats.get('losers_first', 0):,} losing copies)")
    unresolved = collections.defaultdict(set)
    duplicates = collections.defaultdict(set)
    for line in log.splitlines():
        found = UNRESOLVED.search(line)
        if found:
            symbol = found.group(1) or found.group(2)
            referrer = REFERRER.match(line)
            if referrer and not excused(symbol, runtime, imported, thunks):
                unresolved[Path(referrer.group(1)).name].add(symbol)
            continue
        found = DUPLICATE.match(line)
        if found:
            symbol = found.group(2) or found.group(3)
            duplicates[Path(found.group(1)).name].add(symbol)
            duplicates[Path(found.group(4)).name].add(symbol)
    out, blockers, clean_prev, unknown_only = {}, {}, set(), set()
    for row in rows:
        source = row["source"]
        if source in out or Path(source).suffix.lower() not in (".c", ".cpp"):
            continue
        obj = build.row_object(row).name
        try:
            text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        counts = (len(unresolved.get(obj, ())), len(duplicates.get(obj, ())), len(losers.get(obj, ())),
                  len(link_debt.addresses(text)), len(wrong_selected.get(obj, ())))
        out[source] = {"source": source, "linked": "no" if any(counts) else "yes",
                       **dict(zip(STATUS_FIELDS[2:], counts))}
        if not any(counts[:4]):
            clean_prev.add(source)
        if not any(counts) and unknown_selected.get(obj):
            unknown_only.add(source)
        blockers[source] = {"object": obj, "linked": not any(counts), "unresolved": sorted(unresolved.get(obj, ())),
                            "duplicates": sorted(duplicates.get(obj, ())), "losers": sorted(losers.get(obj, ())),
                            "addresses": counts[3], "wrong_selected": wrong_selected.get(obj, [])}
    with STATUS.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, STATUS_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(out[s] for s in sorted(out))
    clean = {source for source, r in out.items() if r["linked"] == "yes"}
    import link_check
    link_check.write_index(present, facts, blockers, {"runtime": runtime, "imported": imported, "stubs": thunks},
                           meta or {}, {"exceptions": exceptions, "owners": dict(owners)})
    print(f"link_census: wrote {STATUS.relative_to(ROOT).as_posix()} ({len(clean):,} of {len(out):,} sources link cleanly; "
          f"{len(clean_prev):,} before wrong_selected; {len(unknown_only):,} of the clean ones use a selected "
          "definition nothing proves or disproves)")
    blocking = set().union(*unresolved.values()) if unresolved else set()
    return clean, len(out), len(blocking), clean_prev, {"unknown_only": unknown_only}


def linked_split(clean):
    """progress.py's lane split restricted to sources that link cleanly,
    measured on this tree: the one the census just linked."""
    import progress
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    return progress.real_split(matched, notes, start, size, naked, keep=lambda key, source: source in clean)


def linked_figures(clean):
    """The stored LINKED figures: linked_bytes (authored + vendored, over all
    code: the chart's LINKED) and linked_authored over game_code (the game's
    own code on this tree: all code minus vendored source and prebuilt
    libraries), the README card's and daily post's Linking bar. Storing the
    denominator keeps Linking one snapshot."""
    import progress
    split = linked_split(clean)
    start, size = progress.retail_text()
    _, total = progress.real_code_denominator(start, size)
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    full = progress.real_split(matched, notes, start, size, progress.naked_cpp_rows_at(matched, None))
    return {"linked_bytes": progress.decompiled(split), "linked_authored": split["authored"],
            "game_code": progress.game_code(full, total)}


def head():
    return subprocess.run(["git", "rev-parse", "--short=10", "HEAD"], cwd=ROOT,
                          capture_output=True, text=True, check=True).stdout.strip()


def object_current(source, obj):
    """The object is what this source, its recorded headers and this compile
    command produce. This is build.compile_is_current without the include-
    directory inventory: that fingerprint moves with unrelated files (a scratch
    file in the repo root, another checkout's build/include) and flipped 18
    provably identical objects to "stale" and back on 2026-09-28, which would
    make the census refuse at random. An object with no dependency record must
    at least be newer than its source."""
    sidecar = build._deps_sidecar(obj)
    if not sidecar.exists():
        return obj.stat().st_mtime >= source.stat().st_mtime
    meta = json.loads(sidecar.read_text())
    if meta.get("source") != build._hash_file(str(source)):
        return False
    for dep, digest in (meta.get("deps") or {}).items():
        if build._hash_file(dep if os.path.isabs(dep) else str(ROOT / dep)) != digest:
            return False
    command, env = build.compiler_command(source, obj)
    return meta.get("cmd") == build._cmd_fingerprint(command, env)


def record(census, rows, rerun=False, fresh=False):
    """Write link_status.csv and the census's history row, LINKED included.

    LINKED is stored, not recomputed later: measured on the tree that was
    linked, it stays fixed until the next census instead of decaying with
    every edit made since. Nothing is recorded when an object is missing (a
    file the link never saw would read as clean) or older than its source (a
    failed compile leaves last week's object), or when game sources or the
    ledger have uncommitted edits. --status (rerun)
    only runs on the census's own commit, so a log is never paired with
    another tree's ledger or sources.
    """
    if census["missing"]:
        raise SystemExit(f"link_census: {census['missing']:,} objects were missing from the link; "
                         "nothing recorded (build everything and rerun)")
    dirty = subprocess.run(["git", "status", "--porcelain", "-uno", "--", "game", "targets/game/reverse/functions.csv",
                            "targets/game/reverse/symbols.csv"], cwd=ROOT, capture_output=True, text=True).stdout
    if dirty.strip():
        raise SystemExit(f"link_census: uncommitted source or ledger edits; the census would not match its commit:\n{dirty}")
    # cl.exe leaves the previous .obj in place when a compile fails, and the
    # full build stops at the first failure: an object that is not current for
    # its source, recorded headers and compile command is last week's code
    # under this week's ledger.
    present, missing = objects(rows)
    if missing:  # census.json's count is the census's; an object gone since then would read as clean
        raise SystemExit(f"link_census: {len(missing):,} objects are missing now, e.g. {missing[0].name}; "
                         "nothing recorded")
    by_object = _object_sources(rows)
    stale = [] if fresh else [obj for obj in present if obj in by_object and not object_current(by_object[obj], obj)]
    if stale:
        raise SystemExit(f"link_census: {len(stale):,} objects are not current for their source (a failed compile?), "
                         f"e.g. {stale[0].name}; nothing recorded")
    history = read_history()
    commit = head()
    log = final_log(census)
    if rerun:
        if not history or history[-1]["commit"] != commit or history[-1]["date"] != census["when"]:
            raise SystemExit(f"link_census: --status must run on the census's own tree (HEAD {commit}; last census "
                             f"{history[-1]['commit'] + ' ' + history[-1]['date'] if history else 'none'}; "
                             f"census.json {census['when']})")
        # A later link that crashed rewrites census.log without touching
        # census.json: the log must still reproduce the census's own totals
        # (totals, since how a name is classified changes between versions).
        classes, _, dup_kinds, _ = classify(log, rows)
        if (sum(classes.values()) != sum(census["unresolved_classes"].values())
                or sum(dup_kinds.values()) != sum(census["duplicate_classes"].values())):
            raise SystemExit("link_census: census.log no longer reproduces census.json's counts; rerun the census")
    import link_debt
    kept = selected_definitions(selection_link(present, log))
    clean, files, blocking, clean_prev, _ = write_status(log, rows, present, {"date": census["when"], "commit": commit},
                                                         kept)
    before = linked_figures(clean_prev)
    figure = {"files": files, "files_linked": len(clean), "blocking_names": blocking,
              "addresses": sum(count for count, _ in link_debt.per_file(link_debt.addresses)),
              **linked_figures(clean), "files_linked_prev_rule": len(clean_prev),
              "linked_bytes_prev_rule": before["linked_bytes"], "linked_authored_prev_rule": before["linked_authored"]}
    if rerun:
        history[-1].update(figure)
    else:
        history.append({**history_row(census, commit), **figure})
    write_history(history)
    print(f"link_census: LINKED {figure['linked_bytes']:,} bytes ({figure['linked_bytes_prev_rule']:,} before "
          f"wrong_selected), authored {figure['linked_authored']:,} ({figure['linked_authored_prev_rule']:,}); "
          f"{'updated' if rerun else 'appended'} {HISTORY.relative_to(ROOT).as_posix()}")


HISTORY = ROOT / "targets/game/reverse/link_census_history.csv"
HISTORY_FIELDS = ["date", "commit", "objects", "unresolved", "alias", "pinned_elsewhere", "dump", "data",
                  "import", "unpinned", "duplicates", "comdat_conflicts", "comdat_vtables",
                  "scaffold_aliases", "scaffold_unresolved", "scaffold_crashed",
                  "files", "files_linked", "blocking_names", "addresses", "linked_bytes",
                  "linked_authored", "game_code", "files_linked_prev_rule", "linked_bytes_prev_rule",
                  "linked_authored_prev_rule"]


def read_history():
    if not HISTORY.exists():
        return []
    with HISTORY.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def write_history(rows):
    with HISTORY.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, HISTORY_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def history_row(census, commit):
    """One row per census: the trend of what stands between the tree and a link."""
    unresolved = census["unresolved_classes"]
    conflicts = census.get("comdat_conflicts", {})
    scaffold = census.get("scaffold") or {}
    return {"date": census["when"], "commit": commit, "objects": census["objects"],
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


if __name__ == "__main__":
    sys.exit(main())
