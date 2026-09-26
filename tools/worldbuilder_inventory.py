#!/usr/bin/env python3
"""Reproduce WorldBuilder identity evidence; inventories are never match claims."""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import pefile

from targets import Section, initial_ilt_map, load_target


SCHEMA = 1
DONOR = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/WorldBuilder"
DONOR_IMPORT = "4d091bbeec43fcdf420241849233bf444bbe355e"
# These are boundary and donor-association witnesses, not guessed names for bytes.
EDITOR_RECIPES = (
    ("CWorldBuilderView", "OnShowGrid", "WorldBuilderView", "IDM_ShowGrid", 0, 67),
    ("CWorldBuilderView", "OnUpdateShowGrid", "WorldBuilderView", "IDM_ShowGrid", -1, 51),
    ("CWorldBuilderView", "OnViewShowtexture", "WorldBuilderView", "ID_VIEW_SHOWTEXTURE", 0, 67),
    ("CWorldBuilderView", "OnUpdateViewShowtexture", "WorldBuilderView", "ID_VIEW_SHOWTEXTURE", -1, 28),
    ("CMainFrame", "OnViewBrushfeedback", "MainFrm", "ID_VIEW_BRUSHFEEDBACK", 0, 60),
    ("CMainFrame", "OnUpdateViewBrushfeedback", "MainFrm", "ID_VIEW_BRUSHFEEDBACK", -1, 24),
    ("CWorldBuilderDoc", "OnEditLinkCenters", "WorldBuilderDoc", "ID_EDIT_LINK_CENTERS", 0, 11),
    ("CWorldBuilderDoc", "OnUpdateEditLinkCenters", "WorldBuilderDoc", "ID_EDIT_LINK_CENTERS", -1, 25),
    ("CWB3dFrameWnd", "OnUpdateWindowPreview1024x768", "WBFrameWnd", "ID_WINDOW_PREVIEW1024X768", -1, 44),
    ("CWB3dFrameWnd", "OnUpdateWindowPreview640x480", "WBFrameWnd", "ID_WINDOW_PREVIEW640X480", -1, 44),
    ("WbView3d", "OnUpdateViewShowwireframe", "wbview3d", "ID_VIEW_SHOWWIREFRAME", -1, 28),
    ("WbView3d", "OnUpdateViewShowentire3dmap", "wbview3d", "ID_VIEW_SHOWENTIRE3DMAP", -1, 28),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def text_sha256(path):
    # Git's Windows checkout conversion must not invalidate source provenance.
    return sha256(path.read_bytes().replace(b"\r\n", b"\n"))


def require(condition, message):
    if not condition:
        raise ValueError(message)


class Image:
    def __init__(self, target):
        self.target = target
        self.pe = pefile.PE(data=target.image_bytes, fast_load=True)
        self.pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_RESOURCE"]])
        self.base = target.image_base
        self.text = target.text_section
        self.text_bytes = target.read_rva(self.text.rva, min(self.text.raw_size, self.text.virtual_size))
        self.highlow = {r.rva for r in target.relocations if r.type == 3}
        self.md = Cs(CS_ARCH_X86, CS_MODE_32)

    def read(self, rva, size):
        return self.target.read_rva(rva, size)

    def words(self, rva, count):
        return struct.unpack("<" + "I" * count, self.read(rva, count * 4))

    def executable(self, rva):
        return any(s.rva <= rva < s.rva + s.raw_size and s.characteristics & 0x20000000
                   for s in self.target.sections)

    def string(self, rva):
        section = self.target.section_for_rva(rva)
        require(section is not None, f"String RVA {rva:#x} has no section")
        raw = self.read(rva, min(2048, section.rva + section.raw_size - rva))
        require(b"\0" in raw, f"Unterminated string at RVA {rva:#x}")
        return raw.split(b"\0", 1)[0].decode("ascii")

    def route(self, rva):
        return self.target.follow_ilt(rva), [rva] if rva in self.target.ilt_thunks else []

    def constant_getter(self, rva):
        body, _ = self.route(rva)
        raw = self.read(body, 6)
        if raw[0] == 0xB8 and raw[5] == 0xC3:
            return body, struct.unpack_from("<I", raw, 1)[0] - self.base
        return None


def offsets(raw, needle):
    start = 0
    while (start := raw.find(needle, start)) >= 0:
        yield start
        start += 1


def runtime_classes(image):
    records = []
    for section in image.target.sections:
        if section.name != ".rdata":
            continue
        raw = image.read(section.rva, min(section.raw_size, section.virtual_size))
        for pos in offsets(raw, b"\xff\xff\x00\x00"):
            off = pos - 8
            if off < 0 or off + 28 > len(raw) or off % 4:
                continue
            rva = section.rva + off
            name, size, schema, create, base, next_class, init = struct.unpack_from("<7I", raw, off)
            if rva not in image.highlow or not 0 < size < 0x1000000:
                continue
            if not image.executable(base - image.base) or (create and not image.executable(create - image.base)):
                continue
            try:
                label = image.string(name - image.base)
            except (ValueError, UnicodeDecodeError):
                continue
            if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_:]{0,127}", label):
                continue
            records.append(dict(name=label, record_rva=rva, object_size=size, schema=schema,
                                name_rva=name - image.base,
                                create_entry_rva=create - image.base if create else None,
                                base_getter_entry_rva=base - image.base))
    return sorted(records, key=lambda r: r["record_rva"])


def message_maps(image, classes):
    jumps = {}
    for entry, dest in image.target.ilt_thunks.items():
        jumps.setdefault(dest, []).append(entry)
    maps = []
    for record in classes:
        needle = b"\xb8" + struct.pack("<I", record["record_rva"] + image.base) + b"\xc3"
        for off in offsets(image.text_bytes, needle):
            body = image.text.rva + off
            for getter in [body] + jumps.get(body, []):
                for section in image.target.sections:
                    if section.name != ".rdata":
                        continue
                    raw = image.read(section.rva, min(section.raw_size, section.virtual_size))
                    for ptr in offsets(raw, struct.pack("<I", getter + image.base)):
                        vtable = section.rva + ptr
                        if vtable not in image.highlow or ptr + 0x34 > len(raw):
                            continue
                        entry = image.words(vtable + 0x30, 1)[0] - image.base
                        if not image.executable(entry):
                            continue
                        decoded = image.constant_getter(entry)
                        if decoded is None:
                            continue
                        map_body, map_rva = decoded
                        if not section.rva <= map_rva < section.rva + section.raw_size - 8:
                            continue
                        base_getter, entries = image.words(map_rva, 2)
                        entries -= image.base
                        if not image.executable(base_getter - image.base) or not section.rva <= entries < section.rva + section.raw_size:
                            continue
                        rows = []
                        for index in range(1024):
                            at = entries + index * 24
                            words = image.words(at, 6)
                            if not any(words):
                                break
                            msg, code, ident, last, signature, handler = words
                            require(at + 20 in image.highlow and image.executable(handler - image.base),
                                    f"Invalid MFC handler pointer at RVA {at:#x}")
                            target, route = image.route(handler - image.base)
                            rows.append(dict(entry_rva=at, message=msg, code=code, resource_id=ident,
                                             last_resource_id=last, signature=signature,
                                             handler_entry_rva=handler - image.base,
                                             handler_rva=target, ilt_route_rvas=route))
                        else:
                            raise ValueError(f"Unterminated message map at {map_rva:#x}")
                        maps.append(dict(class_name=record["name"], runtime_class_rva=record["record_rva"],
                                         vtable_rva=vtable, runtime_getter_entry_rva=getter,
                                         runtime_getter_rva=body, message_getter_entry_rva=entry,
                                         message_getter_rva=map_body, message_map_rva=map_rva,
                                         base_map_getter_entry_rva=base_getter - image.base, entries=rows))
    return sorted(maps, key=lambda m: (m["runtime_class_rva"], m["vtable_rva"]))


def parse_menu(raw):
    version, offset = struct.unpack_from("<HH", raw)
    require(version == 0, f"Unsupported menu resource version: {version}")
    pos = 4 + offset

    def items():
        nonlocal pos
        result = []
        while pos < len(raw):
            flags = struct.unpack_from("<H", raw, pos)[0]
            pos += 2
            ident = None
            if not flags & 0x10:
                ident = struct.unpack_from("<H", raw, pos)[0]
                pos += 2
            start = pos
            while struct.unpack_from("<H", raw, pos)[0]:
                pos += 2
            text = raw[start:pos].decode("utf-16le")
            pos += 2
            row = dict(flags=flags, resource_id=ident, text=text)
            if flags & 0x10:
                row["children"] = items()
            result.append(row)
            if flags & 0x80:
                return result
        raise ValueError("Menu resource lacks an end marker")

    return items()


def resources(image):
    rows = []
    for kind in image.pe.DIRECTORY_ENTRY_RESOURCE.entries:
        for ident in kind.directory.entries:
            for lang in ident.directory.entries:
                value = lang.data.struct
                raw = image.read(value.OffsetToData, value.Size)
                row = dict(type_id=kind.id, resource_id=ident.id, language_id=lang.id,
                           rva=value.OffsetToData, size=value.Size, sha256=sha256(raw))
                if kind.id == 4:
                    row["menu"] = parse_menu(raw)
                rows.append(row)
    return rows


def donor_association(root, class_name, method, filename, resource_name, code):
    source = f"{DONOR}/src/{filename}.cpp"
    header = f"{DONOR}/include/{filename}.h"
    resource = f"{DONOR}/res/resource.h"
    contents = {p: (root / p).read_text(encoding="utf-8") for p in (source, header, resource)}
    macro = "ON_COMMAND" if code == 0 else "ON_UPDATE_COMMAND_UI"
    association = rf"{macro}\(\s*{resource_name}\s*,\s*{method}\s*\)"
    require(re.search(association, contents[source]) is not None, f"Missing donor association {class_name}::{method}")
    require(f"BEGIN_MESSAGE_MAP({class_name}," in contents[source], f"Wrong donor class {class_name}")
    match = re.search(rf"^#define\s+{resource_name}\s+(\d+)\s*$", contents[resource], re.M)
    require(match is not None, f"Missing donor resource ID {resource_name}")
    declaration = rf"afx_msg\s+void\s+{method}\s*\(([^)]*)\)\s*;"
    declared = re.search(declaration, contents[header])
    require(declared is not None, f"Missing donor method declaration {method}")
    access = re.findall(r"\b(public|protected|private)\s*:", contents[header][:declared.start()])
    require(access and access[-1] == "protected", f"Unproven protected method ABI for {method}")
    argument = "XZ" if code == 0 else "PAVCCmdUI@@@Z"
    require((not declared[1].strip()) if code == 0 else bool(re.fullmatch(r"CCmdUI\s*\*\s*\w+", declared[1].strip())),
            f"Unexpected donor method signature for {method}")
    return dict(name=f"?{method}@{class_name}@@IAEX{argument}", resource_id=int(match[1]),
                donor_files=[dict(path=p, sha256=text_sha256(root / p), normalization="CRLF-to-LF") for p in contents],
                donor_source=source, donor_line=contents[source][:re.search(association, contents[source]).start()].count("\n") + 1)


def callee_contract(image, instructions):
    imports = {item.iat_rva: item for item in image.target.imports}
    result = []
    for ins in instructions:
        if ins.mnemonic != "call":
            continue
        row = dict(instruction_rva=ins.address, operands=ins.op_str)
        iat = None
        if ins.bytes[0] == 0xE8:
            entry = ins.address + 5 + struct.unpack("<i", ins.bytes[1:])[0]
            body, route = image.route(entry)
            row.update(entry_rva=entry, target_rva=body, ilt_route_rvas=route)
            if image.read(body, 2) == b"\xff\x25":
                iat = image.words(body + 2, 1)[0] - image.base
        elif ins.bytes[:2] == b"\xff\x15":
            iat = struct.unpack("<I", ins.bytes[2:])[0] - image.base
        if iat is not None:
            require(iat in imports, f"Call through unknown import at RVA {iat:#x}")
            item = imports[iat]
            row["import"] = dict(iat_rva=iat, dll=item.dll, name=item.name, ordinal=item.ordinal)
        result.append(row)
    return result


def editor_candidates(image, maps):
    candidates = []
    for cls, method, filename, resource_name, code, size in EDITOR_RECIPES:
        donor = donor_association(image.target.root, cls, method, filename, resource_name, code)
        owners = [m for m in maps if m["class_name"] == cls]
        require(len(owners) == 1, f"Ambiguous/missing MFC class map for {cls}")
        owner = owners[0]
        entries = [e for e in owner["entries"] if e["message"] == 0x111 and e["code"] == code & 0xFFFFFFFF
                   and e["resource_id"] == donor["resource_id"] and e["last_resource_id"] == donor["resource_id"]]
        require(len(entries) == 1, f"Ambiguous/missing MFC handler for {cls}::{method}")
        entry = entries[0]
        require(entry["signature"] == (0x35 if code == 0 else 0x3D), f"Unexpected MFC signature for {method}")
        rva = entry["handler_rva"]
        raw = image.read(rva, size)
        instructions = list(image.md.disasm(raw, rva))
        require(sum(i.size for i in instructions) == size and instructions[-1].mnemonic == "ret",
                f"Unproven end boundary for {cls}::{method}")
        require(image.read(rva + size, 1) == b"\xcc", f"Missing boundary padding for {method}")
        for ins in instructions:
            if ins.mnemonic.startswith("j"):
                require(rva <= int(ins.op_str, 16) < rva + size, f"Branch leaves selected extent for {method}")
        strings = []
        for ins in instructions:
            if ins.bytes[0] == 0x68 and ins.address + 1 in image.highlow:
                address = struct.unpack("<I", ins.bytes[1:])[0] - image.base
                strings.append(dict(operand_rva=ins.address + 1, string_rva=address, value=image.string(address)))
        ident = f"{cls}::{method}"
        candidates.append(dict(id=ident, evidence=f"mfc:{ident}", readable_name=ident, **donor,
                               source=f"Code/Tools/WorldBuilder/src/{filename}.cpp", profile="editor-size",
                               target_rva=rva, target_size=size, bytes_sha256=sha256(raw),
                               boundary="message-map entry, complete instructions, contained branches, RET then INT3",
                               chain={k: v for k, v in owner.items() if k != "entries"}, message_entry=entry,
                               highlow_operand_rvas=sorted(x for x in image.highlow if rva <= x < rva + size),
                               string_witnesses=strings, callee_contract=callee_contract(image, instructions)))
        candidates[-1]["packet_sha256"] = sha256(json.dumps(candidates[-1], sort_keys=True, separators=(",", ":")).encode())
    return candidates


def extract_editor_candidates(target):
    image = Image(target)
    return editor_candidates(image, message_maps(image, runtime_classes(image)))


def assertion_candidate(image):
    name = "?Negate@Coord2D@@QAEAAV1@XZ"
    exported = next(e for e in image.target.exports if e.name == name)
    rva, route = image.route(exported.rva)
    size = 116
    raw = image.read(rva, size)
    instructions = list(image.md.disasm(raw, rva))
    require(sum(i.size for i in instructions) == size and instructions[-1].mnemonic == "ret"
            and image.read(rva + size, 1) == b"\xcc", "Coord2D::Negate boundary changed")
    require(all(rva <= int(i.op_str, 16) < rva + size for i in instructions if i.mnemonic.startswith("j")),
            "Coord2D::Negate branch leaves proven extent")
    candidate = dict(id="Coord2D::Negate", name=name, readable_name="Coord2D::Negate", evidence="export",
                     target_rva=rva, target_size=size, export_rva=exported.rva, ilt_route_rvas=route,
                     source="targets/worldbuilder/Code/Libraries/Source/Math/MathCoord2D.cpp",
                     profile="engine-size", bytes_sha256=sha256(raw), donor_files=[],
                     boundary="named export, complete instructions, contained branches, RET then INT3",
                     callee_contract=callee_contract(image, instructions),
                     known_blockers=["Normal verifier needs independently witnessed identities for function RVA 0x12e0e0 and data RVA 0x1046508; calibration is not a landing."])
    candidate["packet_sha256"] = sha256(json.dumps(candidate, sort_keys=True, separators=(",", ":")).encode())
    return candidate


def validate_mfc_identity(target, row, candidate_id):
    require(target.target_id == "worldbuilder", "MFC evidence requires the WorldBuilder target")
    matches = [c for c in extract_editor_candidates(target) if c["id"] == candidate_id]
    require(len(matches) == 1, f"Unknown MFC candidate identity: {candidate_id}")
    candidate = matches[0]
    for field in ("name", "target_rva", "target_size"):
        actual = row[field]
        if field != "name":
            actual = int(actual, 0) if isinstance(actual, str) else actual
        require(actual == candidate[field], f"MFC identity {candidate_id}: {field} disagrees with binary/donor evidence")
    return dict(kind="mfc", candidate_id=candidate_id, image_sha256=target.expected_sha256,
                target_rva=candidate["target_rva"], target_size=candidate["target_size"],
                chain=candidate["chain"], message_entry=candidate["message_entry"],
                donor_files=candidate["donor_files"])


def source_strings(image):
    rows = []
    expression = rb"[A-Za-z]:\\[^\x00\r\n]{1,512}\.(?:cpp|cxx|cc|c|hpp|h)(?=\x00)"
    for section in image.target.sections:
        if not section.raw_size:
            continue
        raw = image.read(section.rva, min(section.raw_size, section.virtual_size))
        for match in re.finditer(expression, raw, re.I):
            value = match[0].decode("ascii", errors="strict")
            rows.append(dict(rva=section.rva + match.start(), value=value))
    return rows


def game_reference(root):
    manifest_path = root / "baselines/bfme1/workshop-vanilla-1.03/manifest.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    row = next(x for x in manifest["files"] if x["path"] == "files/lotrbfme.exe")
    raw = (manifest_path.parent / row["path"]).read_bytes()
    require(sha256(raw) == row["sha256"], "Game reference SHA-256 disagrees with baseline manifest")
    pe = pefile.PE(data=raw, fast_load=True)
    pe.parse_data_directories(directories=[0])
    section = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".text")
    text = Section(".text", section.VirtualAddress, section.Misc_VirtualSize, section.SizeOfRawData,
                   section.PointerToRawData, section.Characteristics)
    ilt = initial_ilt_map(raw, text)
    result = {}
    for exported in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        if exported.name is None:
            continue
        item = dict(export_rva=exported.address, ordinal=exported.ordinal,
                    identity_evidence="identical PE export name; source and ABI compatibility unverified")
        section = pe.get_section_by_rva(exported.address)
        if section is not None and section.Characteristics & 0x20000000 and exported.forwarder is None:
            rva = ilt.get(exported.address, exported.address)
            route = [exported.address] if exported.address in ilt else []
            item.update(target_rva=rva, ilt_route_rvas=route)
        result[exported.name.decode("ascii")] = item
    return row["sha256"], result


def generate(target):
    image = Image(target)
    classes = runtime_classes(image)
    maps = message_maps(image, classes)
    editor = editor_candidates(image, maps)
    game_hash, game_exports = game_reference(target.root)
    exports, code_candidates = [], []
    for exported in target.exports:
        row = dict(name=exported.name, ordinal=exported.ordinal, export_rva=exported.rva,
                   forwarder=exported.forwarder, executable=image.executable(exported.rva))
        if row["executable"] and exported.forwarder is None:
            body, route = image.route(exported.rva)
            row.update(target_rva=body, ilt_route_rvas=route)
            relation = game_exports.get(exported.name)
            candidate = dict(id=f"export:{exported.ordinal}", evidence="export", **row)
            if relation is not None:
                candidate["game_counterpart"] = relation
            code_candidates.append(candidate)
        exports.append(row)
    binding = dict(schema_version=SCHEMA, target_id=target.target_id, binary_sha256=target.expected_sha256,
                   image_base=target.image_base, address_convention="All address fields are RVAs; decoded immediate operands are VAs")
    relocation_bytes = b"".join(struct.pack("<IH", r.rva, r.type) for r in target.relocations)
    inventory = dict(**binding, exports=exports, runtime_classes=classes, message_maps=maps,
                     resources=resources(image), source_strings=source_strings(image),
                     base_relocations=dict(count=len(target.relocations),
                                           counts_by_type=dict(sorted(Counter(str(r.type) for r in target.relocations).items())),
                                           rva_type_sha256=sha256(relocation_bytes),
                                           encoding="sha256 of ordered little-endian uint32 RVA + uint16 type; raw entries available through targets.load_target"),
                     coverage=dict(runtime_classes="schema 0xffff CRuntimeClass records with relocated names and executable create/base getters",
                                   message_maps="class-named vtable runtime getter plus slot +0x30 constant message-map getter",
                                   function_boundaries="Only selected editor candidates have proven extents; exports are entry identities"))
    files = {f["path"]: f["sha256"] for c in editor for f in c["donor_files"]}
    provenance = dict(**binding, generator="tools/worldbuilder_inventory.py", generator_sha256=text_sha256(Path(__file__)),
                      text_hash_normalization="CRLF-to-LF; binary fingerprints remain byte-exact",
                      ilt=target.ilt_provenance,
                      donor=dict(path="reference/CnC_Generals_Zero_Hour", import_commit=DONOR_IMPORT,
                                 upstream_revision=None, upstream_revision_status="not recorded by the vendoring commit or bundled README",
                                 files=[dict(path=p, sha256=h) for p, h in sorted(files.items())]),
                      mfc_schema=dict(version="MFC 7.1 x86 _AFXDLL", runtime_class_bytes=28,
                                      message_map_bytes=8, message_entry_bytes=24, get_message_map_vtable_offset=48),
                      game_reference=dict(target="bfme1-game", binary_sha256=game_hash))
    return {"inventory.json": inventory, "candidates.json": dict(**binding, candidates=editor + [assertion_candidate(image)], exports=code_candidates),
            "provenance.json": provenance}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="Fail if tracked inventory is stale; do not rewrite it")
    args = parser.parse_args(argv)
    target = load_target("worldbuilder")
    outputs = generate(target)
    for name, value in outputs.items():
        path = target.ledger_root / name
        text = json.dumps(value, indent=2, ensure_ascii=False) + "\n"
        if args.check:
            require(path.is_file() and path.read_text(encoding="utf-8") == text, f"Stale WorldBuilder inventory: {path}")
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8", newline="\n")
    print(f"WorldBuilder: {len(outputs['candidates.json']['exports'])} code exports, "
          f"{len(outputs['inventory.json']['message_maps'])} class maps, "
          f"{len(outputs['candidates.json']['candidates'])} bounded candidates")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
