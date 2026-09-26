#!/usr/bin/env python3
"""Reproduce the WorldBuilder MFC71 ordinal map from pinned external evidence."""
import argparse
import bisect
import csv
import hashlib
import io
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
import urllib.request
import xml.etree.ElementTree as ET

import pefile

ROOT = Path(__file__).resolve().parents[1]
DEPENDENCIES = ROOT / "worldbuilder/dependencies"
MANIFEST = DEPENDENCIES / "mfc71.json"
MAPPING = DEPENDENCIES / "mfc71.csv"
CACHE = ROOT / "build/worldbuilder/dependencies/mfc71"
FIELDS = ("ordinal", "name", "rva", "kind", "pdb_rva_candidates")


def digest(data):
    return hashlib.sha256(data).hexdigest()


def checked_file(path, expected):
    data = path.read_bytes()
    if digest(data) != expected:
        raise ValueError(f"SHA-256 mismatch: {path}")
    return data


def load_mapping():
    manifest = json.loads(MANIFEST.read_text())
    data = checked_file(MAPPING, manifest["mapping_sha256"])
    rows = list(csv.DictReader(io.StringIO(data.decode())))
    mapped = {int(row["ordinal"]): row for row in rows}
    if len(mapped) != len(rows) or len(rows) != manifest["verified_imports"]:
        raise ValueError("MFC71 mapping has duplicate ordinals or unexpected row count")
    return mapped


def resolve_ordinal(dll, ordinal):
    """Resolve only independently proved imports of the pinned WorldBuilder target."""
    if dll.lower() != "mfc71.dll":
        raise ValueError(f"No verified ordinal mapping for {dll}")
    row = load_mapping().get(ordinal)
    if row is None:
        raise ValueError(f"MFC71 ordinal {ordinal} is unverified; run tools/worldbuilder_mfc.py verify for evidence")
    return row["name"]


def fetch_inputs(manifest):
    CACHE.mkdir(parents=True, exist_ok=True)
    for name, artifact in manifest["inputs"].items():
        path = CACHE / name
        if not path.exists():
            with urllib.request.urlopen(artifact["url"], timeout=45) as response:
                data = response.read()
            if digest(data) != artifact["sha256"]:
                raise ValueError(f"Downloaded SHA-256 mismatch: {artifact['url']}")
            path.write_bytes(data)
        checked_file(path, artifact["sha256"])


def pdb_streams(data):
    # Only MSF 7 is needed; accepting older formats would conceal a wrong dependency.
    if data[:32] != b"Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0":
        raise ValueError("Expected an MSF 7 PDB")
    block_size, _, count, directory_size, _, block_map = struct.unpack_from("<6I", data, 32)
    if count * block_size != len(data):
        raise ValueError("PDB block count does not match its size")

    def read_blocks(blocks, size):
        if any(block >= count for block in blocks):
            raise ValueError("PDB stream block outside file")
        return b"".join(data[block * block_size:(block + 1) * block_size] for block in blocks)[:size]

    directory_blocks = (directory_size + block_size - 1) // block_size
    indices = struct.unpack_from(f"<{directory_blocks}I", data, block_map * block_size)
    directory = read_blocks(indices, directory_size)
    stream_count = struct.unpack_from("<I", directory)[0]
    sizes = struct.unpack_from(f"<{stream_count}I", directory, 4)
    offset = 4 + stream_count * 4
    streams = []
    for size in sizes:
        if size == 0xffffffff:
            streams.append(None)
            continue
        blocks = (size + block_size - 1) // block_size
        indices = struct.unpack_from(f"<{blocks}I", directory, offset)
        offset += blocks * 4
        streams.append(read_blocks(indices, size))
    return streams


def pdb_publics(streams, dll):
    info = streams[1]
    identity = info[12:28] + info[8:12]
    codeviews = [dll.get_data(d.struct.AddressOfRawData, d.struct.SizeOfData)
                 for d in dll.DIRECTORY_ENTRY_DEBUG if d.struct.Type == 2]
    if len(codeviews) != 1 or codeviews[0][:4] != b"RSDS" or codeviews[0][4:24] != identity:
        raise ValueError("PDB GUID/age does not match MFC71 DLL")
    dbi = streams[3]
    debug_offset = 64 + sum(struct.unpack_from("<5I", dbi, 24)) + struct.unpack_from("<I", dbi, 52)[0]
    debug = struct.unpack_from("<11H", dbi, debug_offset)
    # This DLL was reordered by BBT; public addresses are in the pre-BBT image.
    omap = list(struct.iter_unpack("<II", streams[debug[4]]))
    keys = [entry[0] for entry in omap]
    sections = streams[debug[10]]
    bases = [struct.unpack_from("<I", sections, offset + 12)[0] for offset in range(0, len(sections), 40)]
    records = streams[struct.unpack_from("<H", dbi, 20)[0]]
    result = {}
    offset = 0
    while offset < len(records):
        size, kind = struct.unpack_from("<HH", records, offset)
        end = offset + size + 2
        if size < 2 or end > len(records):
            raise ValueError("Malformed PDB symbol record")
        if kind == 0x110e:  # S_PUB32, defined by Microsoft's cvinfo.h.
            flags, address, section = struct.unpack_from("<IIH", records, offset + 4)
            name = records[offset + 14:end].split(b"\0", 1)[0].decode("ascii")
            if 1 <= section <= len(bases):
                before = bases[section - 1] + address
                index = bisect.bisect_right(keys, before) - 1
                if index >= 0 and omap[index][1]:
                    after = omap[index][1] + before - omap[index][0]
                    result.setdefault(after, {})[name] = flags
        offset = end
    return result


def derive_mapping(manifest):
    dll = pefile.PE(data=checked_file(CACHE / "mfc71.dll", manifest["inputs"]["mfc71.dll"]["sha256"]))
    pdb = checked_file(CACHE / "mfc71.pdb", manifest["inputs"]["mfc71.pdb"]["sha256"])
    publics = pdb_publics(pdb_streams(pdb), dll)
    table = ET.fromstring(checked_file(CACHE / "mfc71.exports", manifest["inputs"]["mfc71.exports"]["sha256"]))
    names = {int(entry.attrib["ORDINAL"]): entry.attrib["NAME"] for entry in table}
    target = manifest["target"]
    wb = pefile.PE(data=checked_file(ROOT / target["binary"], target["sha256"]))
    imports = {i.ordinal for d in wb.DIRECTORY_ENTRY_IMPORT if d.dll.lower() == b"mfc71.dll" for i in d.imports}
    exports = {e.ordinal: e.address for e in dll.DIRECTORY_ENTRY_EXPORT.symbols}
    rows, unresolved = [], []
    for ordinal in sorted(imports):
        address, name = exports[ordinal], names[ordinal]
        candidates = publics.get(address, {})
        if name not in candidates:
            unresolved.append(ordinal)
            continue
        executable = bool(dll.get_section_by_rva(address).Characteristics & 0x20000000)
        if executable != bool(candidates[name] & 2):
            raise ValueError(f"MFC71 ordinal {ordinal}: PDB function flag disagrees with DLL section")
        rows.append(dict(zip(FIELDS, [ordinal, name, f"0x{address:08x}", "code" if executable else "data", len(candidates)])))
    if unresolved != manifest["unresolved_ordinals"]:
        raise ValueError(f"Unexpected unresolved MFC71 imports: {unresolved}")
    output = io.StringIO(newline="")
    writer = csv.DictWriter(output, FIELDS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(rows)
    return output.getvalue().encode()


def build_import_library():
    import build
    rows = load_mapping().values()
    definition = "LIBRARY MFC71.dll\nEXPORTS\n" + "".join(
        f"{row['name']} @{row['ordinal']} NONAME" + (" DATA" if row["kind"] == "data" else "") + "\n"
        for row in rows)
    path = CACHE / "mfc71.def"
    path.write_text(definition)
    root = build.vc71_root()
    env = build.compiler_environment(root)
    env["WINEDEBUG"] = "-all"
    command = ([] if os.name == "nt" else ["wine"]) + [str(root / "Vc7/bin/lib.exe"), "/nologo", "/machine:x86",
        "/def:" + build.wine_path(path), "/out:" + build.wine_path(CACHE / "mfc71.lib")]
    subprocess.run(command, cwd=ROOT, env=env, check=True)
    verify_import_library(CACHE / "mfc71.lib")
    print(f"Built {CACHE / 'mfc71.lib'} (531 verified WorldBuilder imports; ordinal 5230 intentionally excluded)")


def verify_import_library(path):
    from coffar import read_archive
    expected = load_mapping()
    found = set()
    for _, data in read_archive(path):
        if data[:4] != b"\0\0\xff\xff":
            continue
        _, _, _, machine, _, size, ordinal, flags = struct.unpack_from("<HHHHIIHH", data)
        name, dll, _ = data[20:20 + size].split(b"\0")
        row = expected.get(ordinal)
        if row is None or ordinal in found or machine != 0x14c or dll != b"MFC71.dll":
            raise ValueError(f"Unexpected import-library member for ordinal {ordinal}")
        if name.decode() != row["name"] or flags != (1 if row["kind"] == "data" else 0):
            raise ValueError(f"Import-library symbol/type mismatch at ordinal {ordinal}")
        found.add(ordinal)
    if found != set(expected):
        raise ValueError("Import library does not contain all verified MFC71 ordinals")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("fetch", "verify", "prepare"))
    args = parser.parse_args()
    manifest = json.loads(MANIFEST.read_text())
    if args.action in ("fetch", "prepare"):
        fetch_inputs(manifest)
    actual = derive_mapping(manifest)
    expected = checked_file(MAPPING, manifest["mapping_sha256"])
    if actual != expected:
        raise ValueError("Reproduced MFC71 mapping differs from tracked mapping")
    print(f"Verified {len(load_mapping())}/532 MFC71 imports against matching DLL, PDB and pinned ordinal table; unresolved: 5230")
    if args.action == "prepare":
        build_import_library()


if __name__ == "__main__":
    try:
        main()
    except (ValueError, OSError, KeyError, struct.error) as error:
        sys.exit(f"worldbuilder_mfc: {error}")
