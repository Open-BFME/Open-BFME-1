"""Strict, isolated byte verification for explicitly selected reconstruction targets."""

import csv
import hashlib
import io
import json
import re
import struct
import subprocess
import tempfile
from pathlib import Path

import capstone

import build
from conversion_gate import is_lift_line


class TargetVerificationError(ValueError):
    pass


LEDGER_FIELDS = ("name", "target_rva", "target_size", "status", "source",
                 "profile", "evidence", "model")


def read_rows(target):
    target.verify_hash()
    raw = target.ledger_path.read_bytes()
    _require(b"\r" not in raw and raw.endswith(b"\n"),
             f"{target.ledger_path}: target ledger must use LF and end with newline")
    reader = csv.DictReader(io.StringIO(raw.decode("utf-8")))
    _require(reader.fieldnames == list(LEDGER_FIELDS),
             f"{target.ledger_path}: expected header {','.join(LEDGER_FIELDS)}")
    rows = list(reader)
    _require(all(set(row) == set(LEDGER_FIELDS) for row in rows),
             f"{target.ledger_path}: malformed ledger row")
    return rows


def _exclusive_roots(target):
    return (target.root / "Code/Tools/WorldBuilder",
            target.root / "targets" / target.target_id / "Code")


def validate_rows(target, rows):
    """Validate ledger ownership, ranges, profiles and independently witnessed identities."""
    target.verify_hash()
    validated = _validate_rows(target, list(rows))
    for _, _, row, _ in validated:
        _identity(target, row)
    claimed = {source for _, _, _, source in validated}
    roots = [path.relative_to(target.root).as_posix() for path in _exclusive_roots(target)]
    tracked = subprocess.run(["git", "ls-files", "-z", "--", *roots], cwd=target.root,
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    _require(tracked.returncode == 0, f"cannot enumerate tracked target sources: {tracked.stderr.decode()}")
    unclaimed = [target.root / name.decode() for name in tracked.stdout.split(b"\0") if name
                 and Path(name.decode()).suffix.lower() in {".c", ".cc", ".cpp", ".cxx", ".asm", ".s"}
                 and (target.root / name.decode()).resolve() not in claimed]
    _require(not unclaimed, f"unclaimed target sources: {', '.join(map(str, unclaimed))}")


def _require(condition, message):
    if not condition:
        raise TargetVerificationError(message)


def _number(value):
    return int(value, 0) if isinstance(value, str) else int(value)


def _sha(data):
    return hashlib.sha256(data).hexdigest()


def _route(target, rva):
    return target.follow_ilt(rva)


def _executable(target, rva, size=1):
    return any(section.characteristics & 0x20000000 and section.rva <= rva
               and rva + size <= section.rva + min(section.virtual_size, section.raw_size)
               for section in target.sections)


def _exports(target):
    return {entry.name: entry.rva for entry in target.exports
            if entry.name is not None and entry.forwarder is None}


def _identity(target, row):
    rva = _number(row["target_rva"])
    evidence = row["evidence"]
    if evidence == "export":
        exports = _exports(target)
        _require(row["name"] in exports,
                 f"{row['name']}: no same-name export in {target.target_id}")
        entry = exports[row["name"]]
        _require(_route(target, entry) == rva,
                 f"{row['name']}: export route does not identify RVA {rva:#x}")
        return {"kind": "export", "entry_rva": entry, "body_rva": rva}
    if evidence.startswith("mfc:"):
        from worldbuilder_inventory import validate_mfc_identity
        return validate_mfc_identity(target, row, evidence[4:])
    raise TargetVerificationError(
        f"{row['name']}: unsupported identity evidence {evidence!r}; "
        "use a target export or a verified MFC candidate")


def _source(target, value, *, scratch=False):
    _require(not Path(value).is_absolute() and ".." not in Path(value).parts
             and "\\" not in value and ":" not in value,
             f"source {value!r} must be repository-relative without '..'")
    path = (target.root / value).resolve()
    roots = [target.root / "Code", target.root / "targets" / target.target_id / "Code"]
    if scratch:
        roots.append(target.build_root)
    _require(any(path.is_relative_to(root.resolve()) for root in roots),
             f"source {value!r} must belong to Code/ or targets/{target.target_id}/Code/")
    _require(path.suffix.lower() == ".cpp" and path.is_file(),
             f"source {value!r} must be an existing C++ translation unit")
    text = path.read_text(encoding="utf-8-sig", errors="replace")
    _require(not any(is_lift_line(line) for line in text.splitlines()),
             f"source {value!r} contains a naked or emitted-byte body")
    return path


def _validate_rows(target, rows, *, scratch=False):
    validated = []
    names = set()
    for row in rows:
        required = {"name", "target_rva", "target_size", "status", "source",
                    "profile", "evidence", "model"}
        _require(required <= row.keys() and all(row[key] for key in required),
                 f"target ledger row needs nonempty {', '.join(sorted(required))}")
        _require(row["status"] == "matched", f"{row['name']}: unsupported status {row['status']!r}")
        _require(row["name"] not in names, f"duplicate target symbol {row['name']}")
        names.add(row["name"])
        rva, size = _number(row["target_rva"]), _number(row["target_size"])
        _require(size > 0, f"{row['name']}: target size must be positive")
        _require(_executable(target, rva, size),
                 f"{row['name']}: target extent must lie within executable file-backed code")
        _require(row["profile"] in target.profiles,
                 f"{row['name']}: unknown compiler profile {row['profile']!r}")
        target.read_rva(rva, size)
        validated.append((rva, rva + size, row, _source(target, row["source"], scratch=scratch)))
    validated.sort(key=lambda item: item[0])
    for before, after in zip(validated, validated[1:]):
        _require(before[1] <= after[0],
                 f"overlapping target ranges: {before[2]['name']} and {after[2]['name']}")
    return validated


def _compile(target, source, profile_name, output):
    target.verify_hash()
    profile = target.profiles[profile_name]
    extras = build.source_extra_flags(source)
    _require(all(flag.startswith("-I") for flag in extras),
             f"{source}: target profiles own compiler settings; move non-include // cl flags into a profile")
    command, env = build.compiler_command(source, output)
    prefix = command[:command.index("-c") + 1] + list(profile.flags) + extras
    listing = output.with_suffix(".asm")
    command = prefix + ["-FAs", "-Fa" + listing.relative_to(target.root).as_posix(),
        "-Fo" + output.relative_to(target.root).as_posix(),
        source.relative_to(target.root).as_posix(),
    ]
    includes = [build.wine_path(build.vc71_root() / path)
                for path in profile.toolchain_includes]
    if includes:
        env["INCLUDE"] = ";".join(includes + [env["INCLUDE"]])
    source_hash = _sha(source.read_bytes())
    preprocess_command = prefix + ["-EP", source.relative_to(target.root).as_posix()]
    preprocessed = subprocess.run(preprocess_command, cwd=target.root, env=env, text=True,
                                  stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    expanded = output.with_suffix(".preprocessed.cpp")
    expanded.write_text(preprocessed.stdout)
    _require(preprocessed.returncode == 0, f"{source}: preprocessing failed; see {expanded}")
    _require(not any(is_lift_line(line) for line in preprocessed.stdout.splitlines()),
             f"{source}: preprocessed translation unit contains a naked or emitted-byte body; see {expanded}")
    target.verify_hash()
    result = subprocess.run(command, cwd=target.root, env=env, text=True,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    log = output.with_suffix(".compile.log")
    log.write_text(json.dumps({"command": command, "INCLUDE": env["INCLUDE"],
                               "profile": profile_name}) + "\n" + result.stdout)
    _require(result.returncode == 0,
             f"{source.name}: compiler exited {result.returncode}; see {log}")
    _require(_sha(source.read_bytes()) == source_hash,
             f"{source}: source changed during compilation; rerun verification")
    return {"command": command, "preprocess_command": preprocess_command,
            "profile": profile_name, "compile_log": str(log), "listing_path": str(listing),
            "source_sha256": source_hash,
            "compiler_sha256": _sha((build.vc71_root() / "Vc7/bin/cl.exe").read_bytes())}


def _object_body(obj, symbol):
    code, relocs = build.read_object_symbol_bytes(obj, symbol)
    data, sections, symbols = build._object_layout(str(obj), obj.stat().st_mtime_ns, obj.stat().st_size)
    defined = [entry for entry in symbols if entry["name"] == symbol and entry["section"] > 0]
    _require(len(defined) == 1, f"{symbol}: expected one defined object symbol")
    entry = defined[0]
    following = [other["value"] for other in symbols
                 if other["section"] == entry["section"] and other["storage"] == 2
                 and other["value"] > entry["value"]]
    if following:
        code = code[:min(following) - entry["value"]]
    code = code.rstrip(b"\xcc")
    return code, [reloc for reloc in relocs if reloc[0] < len(code)]


def _check_definitions(target, source, obj, claimed):
    if not any(source.is_relative_to(root.resolve()) for root in _exclusive_roots(target)):
        return
    listing = obj.with_suffix(".asm").read_text()
    toolchain = build.wine_path(build.vc71_root()).replace("/", "\\").casefold().rstrip("\\") + "\\"
    origin = None
    definitions = {}
    for line in listing.splitlines():
        if line.startswith("; File "):
            origin = line[len("; File "):].replace("/", "\\").casefold()
        match = re.match(r"^(\S+)\s+PROC\b", line)
        if match:
            _require(origin is not None, f"{source}: compiler listing omits origin of {match[1]}")
            definitions[match[1]] = origin
    authored = {name for name, path in definitions.items() if not path.startswith(toolchain)}
    _require(authored <= claimed,
             f"{source}: unclaimed target definitions: {', '.join(sorted(authored - claimed))}")
    _require(claimed <= authored, f"{source}: claimed definitions lack authored-source provenance: "
             f"{', '.join(sorted(claimed - authored))}")


def _import_name(symbol):
    if symbol.startswith("__imp_"):
        symbol = symbol[6:]
    if symbol.startswith("_"):
        symbol = re.sub(r"@\d+$", "", symbol[1:])
    return symbol


def _import_identity(target, entry, symbol, *, call=False):
    _require(entry is not None, f"{symbol}: target address is not an IAT entry")
    receipt = {"dll": entry.dll, "ordinal": entry.ordinal, "iat_rva": entry.iat_rva}
    name = entry.name
    if name is None:
        import worldbuilder_mfc
        manifest = json.loads(worldbuilder_mfc.MANIFEST.read_text())
        _require(manifest["target"]["sha256"] == target.expected_sha256,
                 f"{symbol}: ordinal mapping belongs to another target binary")
        name = worldbuilder_mfc.resolve_ordinal(entry.dll, entry.ordinal)
        mapping = worldbuilder_mfc.load_mapping()[entry.ordinal]
        _require(not call or mapping["kind"] == "code",
                 f"{symbol}: imported ordinal denotes data, not callable code")
        receipt["mapping_sha256"] = manifest["mapping_sha256"]
    _require(name == _import_name(symbol),
             f"{symbol}: target import names {name!r}, not the requested symbol")
    receipt["name"] = name
    return receipt


def _relocate(target, row, obj, code, relocs, known):
    rva = _number(row["target_rva"])
    retail = target.read_rva(rva, len(code))
    linked = bytearray(code)
    highlow = {entry.rva for entry in target.relocations if entry.type == 3}
    imports = {entry.iat_rva: entry for entry in target.imports}
    exports = _exports(target)
    checks = []
    occupied = set()
    for offset, kind, symbol in relocs:
        _require(offset >= 0 and offset + 4 <= len(code), f"{symbol}: relocation exceeds body extent")
        sites = set(range(offset, offset + 4))
        _require(not occupied & sites, f"{symbol}: overlapping relocations")
        occupied |= sites
        addend = struct.unpack_from("<I", code, offset)[0]
        _require(addend == 0, f"{symbol}: nonzero relocation addend needs explicit target evidence")
        actual = struct.unpack_from("<I", retail, offset)[0]
        check = {"offset": offset, "kind": kind, "symbol": symbol}
        if kind == 20:
            destination = (rva + offset + 4 + actual) & 0xffffffff
            _require(_executable(target, destination),
                     f"{symbol}: call destination RVA {destination:#x} is not executable")
            if symbol in known:
                _require(_route(target, destination) == _route(target, known[symbol]),
                         f"{symbol}: call target RVA {destination:#x} contradicts target identity")
            else:
                stub = target.read_rva(destination, 6)
                _require(stub[:2] == b"\xff\x25",
                         f"{symbol}: unresolved target callee at RVA {destination:#x}; add independently verified identity")
                iat = struct.unpack_from("<I", stub, 2)[0] - target.image_base
                entry = imports.get(iat)
                check["import"] = _import_identity(target, entry, symbol, call=True)
            value = (destination - (rva + offset + 4)) & 0xffffffff
            check["target_rva"] = destination
        elif kind == 6:
            destination = actual - target.image_base
            _require(rva + offset in highlow,
                     f"{symbol}: absolute operand is absent from target HIGHLOW relocations")
            if symbol.startswith("??_C@"):
                literal, literal_relocs = build.read_object_symbol_bytes(obj, symbol)
                _require(not literal_relocs and literal.endswith(b"\0"),
                         f"{symbol}: expected relocation-free terminated string object")
                _require(target.read_rva(destination, len(literal)) == literal,
                         f"{symbol}: target string does not match object literal")
                check["literal_hex"] = literal.hex()
            elif symbol.startswith("__imp_"):
                entry = imports.get(destination)
                check["import"] = _import_identity(target, entry, symbol)
            else:
                _require(symbol in exports and exports[symbol] == destination,
                         f"{symbol}: absolute data/code identity has no matching target export")
            value = actual
            check["target_rva"] = destination
        else:
            raise TargetVerificationError(f"{symbol}: unsupported COFF relocation type {kind}; explicit support required")
        struct.pack_into("<I", linked, offset, value)
        checks.append(check)
    _require(linked == retail,
             f"{row['name']}: relocated bytes differ at offsets "
             f"{[i for i, (left, right) in enumerate(zip(linked, retail)) if left != right][:16]}")
    return bytes(linked), checks


def _extent(target, rva, code, relocations=()):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, rva))
    _require(instructions and sum(ins.size for ins in instructions) == len(code),
             f"RVA {rva:#x}: body contains undecoded bytes")
    _require(instructions[-1].mnemonic in {"ret", "jmp"},
             f"RVA {rva:#x}: supported complete extent must end in ret or tail jmp")
    starts = {instruction.address for instruction in instructions}
    relative_operands = {check["offset"] for check in relocations if check["kind"] == 20}
    for instruction in instructions:
        if instruction.group(capstone.CS_GRP_JUMP) and instruction.operands[0].type == capstone.x86.X86_OP_IMM:
            destination = instruction.operands[0].imm & 0xffffffff
            _require(destination in starts or instruction.address - rva + instruction.imm_offset in relative_operands,
                     f"RVA {rva:#x}: branch targets an unproved boundary at {destination:#x}")
    _require(target.read_rva(rva + len(code), 1) == b"\xcc",
             f"RVA {rva:#x}: extent lacks following INT3 boundary evidence; investigate extent explicitly")


def _verify(target, rows, selectors, *, probing=False):
    original = target.verify_hash()
    rows = list(rows)
    if not probing:
        validate_rows(target, rows)
    validated = _validate_rows(target, rows, scratch=probing)
    identities = {row["name"]: _identity(target, row) for _, _, row, _ in validated}
    known = _exports(target)
    known.update({row["name"]: _number(row["target_rva"]) for _, _, row, _ in validated})
    selected = validated
    if selectors:
        missing = [selector for selector in selectors if not any(
            selector in {entry[2]["name"], entry[2]["source"]} for entry in validated)]
        _require(not missing, f"unknown target selectors: {', '.join(missing)}")
        selected = [entry for entry in validated if any(
            selector in {entry[2]["name"], entry[2]["source"]} for selector in selectors)]
    _require(bool(selected) or (not validated and not selectors), "no target ledger rows selected")
    target.build_root.mkdir(parents=True, exist_ok=True)
    run = Path(tempfile.mkdtemp(prefix="verify-", dir=target.build_root))
    objects = {}
    receipts = []
    patched = bytearray(original)
    for start, end, row, source in selected:
        key = (source, row["profile"])
        if key not in objects:
            obj = run / (_sha(str(key).encode())[:16] + ".obj")
            objects[key] = obj, _compile(target, source, row["profile"], obj)
            claimed = {other["name"] for _, _, other, path in validated
                       if path == source and other["profile"] == row["profile"]}
            if not probing:
                _check_definitions(target, source, obj, claimed)
        obj, compilation = objects[key]
        code, relocations = _object_body(obj, row["name"])
        _require(len(code) == end - start,
                 f"{row['name']}: object extent {len(code)} differs from target extent {end-start}")
        linked, checks = _relocate(target, row, obj, code, relocations, known)
        _extent(target, start, linked, checks)
        section = next(section for section in target.sections
                       if section.rva <= start and end <= section.rva + section.raw_size)
        offset = section.raw_offset + start - section.rva
        patched[offset:offset + len(linked)] = linked
        receipts.append({**row, "object_path": str(obj), "compilation": compilation,
                         "identity": identities[row["name"]], "relocations": checks,
                         "body_sha256": _sha(linked), "verified_bytes": len(linked)})
    target.verify_hash()
    _require(bytes(patched) == original, "verified no-op image differs from target baseline")
    noop = run / (target.target_id + ".noop.exe")
    noop.write_bytes(patched)
    receipt = {"target": target.target_id, "binary_sha256": _sha(original),
               "mode": "probe" if probing else "verify",
               "run_dir": str(run), "rows": receipts, "noop_path": str(noop),
               "receipt_path": str(run / "receipt.json")}
    (run / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    return receipt


def verify(target, rows, selectors=None):
    """Verify selected full-ledger rows and write an identical no-op image plus receipts."""
    return _verify(target, rows, selectors)


def probe(target, source, symbol, rva, size, profile, evidence="export"):
    """Verify a candidate without requiring its scratch TU to be fully claimed."""
    return _verify(target, [{"name": symbol, "target_rva": rva, "target_size": size,
                            "source": str(source), "profile": profile, "evidence": evidence,
                            "status": "matched", "model": "probe"}], None, probing=True)
