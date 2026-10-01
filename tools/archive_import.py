"""Verify a generated FF25 dispatch route against an already vendored archive.

This is a provider repair, not general permission to replace gen-import rows.
The native public thunk, table field, and independently matched initializer
must reproduce the existing retail route before add_match writes anything.
"""
import hashlib
import re
import struct
from pathlib import Path

import build
import coffar
import reloc_ledger


def note_value(notes, key):
    values = [part[len(key) + 1:] for part in notes.split(";")
              if part.startswith(key + "=")]
    return values[0] if len(values) == 1 else None


def is_archive_import_row(row):
    return (row["status"] == "matched" and row["size"] == 6
            and re.fullmatch(r"game/gen_small/imports_\d+\.cpp", row["source"]) is not None
            and row["notes"].split(";", 1)[0] == "gen-import"
            and row["name"].lower() == f"?ji_{row['rva']:08x}@@yaxxz")


def _provider(root, name, source, notes, rows, rva, size):
    """Raise ValueError on a missing physical/ownership witness; never writes."""
    def require(condition, message):
        if not condition:
            raise ValueError(message)

    root = Path(root).resolve()
    require(size == 6, "archive dispatch extent must remain exactly six bytes")
    require(not any(part.startswith("object-symbol=") for part in notes.split(";")),
            "replacement must name the actual archive symbol without object-symbol indirection")
    path = root / source
    require(Path(source).suffix.lower() == ".lib" and path.is_file()
            and path.resolve().is_relative_to(root / "inputs/vendor"),
            "replacement must be an existing archive under inputs/vendor")
    member, vendor = note_value(notes, "member"), note_value(notes, "vendored")
    require(member and vendor, "replacement needs one member= and vendored= token")
    native_rows = [r for r in rows if r["status"] == "matched" and r["source"] == source
                   and note_value(r["notes"], "member") == member
                   and note_value(r["notes"], "vendored") == vendor]
    require(native_rows, "archive release and member have no independently matched ledger owner")
    archive_bytes = path.read_bytes()
    archive_members = coffar.read_archive_bytes(archive_bytes, str(path))
    members = [data for label, data in archive_members if label == member]
    require(len(members) == 1, "archive member is absent or ambiguous")
    try:
        sections, symbols = reloc_ledger.parse_coff(members[0])
    except (ValueError, IndexError, struct.error) as error:
        raise ValueError(f"archive member is not valid ordinary COFF: {error}") from error
    public = [s for s in symbols.values() if s["name"] == name and s["storage"] == 2
              and s["section"] > 0 and s["type"] & 0x20]
    require(len(public) == 1, "replacement is not one external archive function")
    public = public[0]
    sec = sections[public["section"] - 1]
    require(public["value"] == 0 and sec["size"] == 6 and sec["body"] is not None
            and sec["body"][:2] == b"\xff\x25" and len(sec["relocs"]) == 1,
            "archive public body is not exactly one six-byte FF25 thunk")
    offset, index, kind = sec["relocs"][0]
    require(offset == 2 and kind == reloc_ledger.DIR32,
            "archive thunk does not have one DIR32 operand at +2")
    table = symbols.get(index)
    require(table and table["storage"] == 2 and table["section"] > 0,
            "archive thunk does not reference its own external table definition")
    data_sec = sections[table["section"] - 1]
    require(reloc_ledger.is_data_section(data_sec) and data_sec["body"] is not None,
            "archive dispatch table is not initialized native data")
    addend = struct.unpack_from("<i", sec["body"], 2)[0]
    field = table["value"] + addend
    require(0 <= field <= data_sec["size"] - 4, "dispatch field is outside the native table")
    baseline = root / build.EXE.relative_to(build.ROOT)
    image = reloc_ledger.Image(baseline.read_bytes())
    retail = image.read(image.base + rva, 6)
    require(retail is not None and retail[:2] == b"\xff\x25",
            "retail old extent is not a six-byte FF25 thunk")
    cell = struct.unpack_from("<I", retail, 2)[0]
    homes = build.read_dir32_addresses(root / build.DIR32_ADDRESSES.relative_to(build.ROOT))
    require(table["name"] in homes and homes[table["name"]] + addend == cell,
            "native table home plus field offset misses the actual retail cell")
    initializer_relocs = []
    for where, index, kind in data_sec["relocs"]:
        width = coffar.RELOC_WIDTH.get(kind)
        require(width is not None, "native table has an unsupported relocation width")
        if where < field + 4 and where + width > field:
            initializer_relocs.append((where, index, kind))
    require(len(initializer_relocs) == 1
            and initializer_relocs[0][0] == field
            and initializer_relocs[0][2] == reloc_ledger.DIR32,
            "native dispatch field has no sole nonoverlapping DIR32 initializer")
    initializer = symbols.get(initializer_relocs[0][1])
    require(initializer and initializer["name"] != name and initializer["storage"] == 2 and initializer["section"] > 0
            and initializer["type"] & 0x20,
            "native dispatch initializer is not an external archive function")
    owned = [r for r in native_rows if r["name"] == initializer["name"]]
    require(len(owned) == 1, "native initializer has no unique independently matched archive row")
    initial_addend = struct.unpack_from("<i", data_sec["body"], field)[0]
    require(initial_addend == 0 and image.u32(cell) == image.base + owned[0]["rva"],
            "native initializer does not reproduce the retail cell's initial target")
    init_sec = sections[initializer["section"] - 1]
    lo, size = initializer["value"], owned[0]["size"]
    require(init_sec["body"] is not None and lo + size <= init_sec["size"],
            "native initializer extent is absent from the member")
    native_body = init_sec["body"][lo:lo + size]
    original = image.read(image.base + owned[0]["rva"], size)
    covered = set()
    for where, _, kind in init_sec["relocs"]:
        width = 2 if kind == 0x000A else 4
        covered.update(range(max(0, where - lo), min(size, where - lo + width)))
    require(size - len(covered) >= build.MIN_LIB_CONCRETE,
            "native initializer has too few independently compared bytes")
    require(original is not None and reloc_ledger.masked_equal(
        native_body, original, init_sec["relocs"], lo),
        "native initializer bytes disagree with its independently matched retail extent")

    # A masked initializer alone cannot distinguish equal opcode shapes using
    # different private table fields. Bind every operand independently, and fail
    # closed for unsupported relocations or unresolved/ambiguous destinations.
    for where, index, kind in init_sec["relocs"]:
        if not lo <= where < lo + size:
            continue
        require(where + 4 <= lo + size, "initializer relocation crosses its extent")
        target = symbols.get(index)
        require(target and target["storage"] == 2,
                "initializer relocation has no external native identity")
        operand_addend = struct.unpack_from("<i", init_sec["body"], where)[0]
        if kind == reloc_ledger.DIR32:
            require(target["name"] in homes,
                    "initializer DIR32 has no independently recorded native home")
            expected = homes[target["name"]] + operand_addend
            actual = struct.unpack_from("<I", original, where - lo)[0]
        elif kind == reloc_ledger.REL32:
            destinations = [r for r in rows if r["status"] == "matched"
                            and r["source"] == source and r["name"] == target["name"]
                            and note_value(r["notes"], "vendored") == vendor]
            require(len(destinations) == 1,
                    "initializer REL32 has no unique independently owned archive destination")
            destination = destinations[0]
            destination_member = note_value(destination["notes"], "member")
            definitions = []
            for label, data in archive_members:
                _, native_symbols = reloc_ledger.parse_coff(data)
                definitions.extend((label, v) for v in native_symbols.values()
                                   if v["name"] == target["name"] and v["storage"] == 2
                                   and v["section"] > 0 and v["type"] & 0x20)
            require(len(definitions) == 1 and definitions[0][0] == destination_member,
                    "initializer REL32 destination lacks its actual archive definition")
            expected = image.base + destination["rva"] + operand_addend
            site = image.base + owned[0]["rva"] + where - lo
            actual = site + 4 + struct.unpack_from("<i", original, where - lo)[0]
        else:
            raise ValueError("initializer relocation kind cannot be independently bound")
        require(actual == expected,
                "native initializer relocation operand disagrees with its owned retail route")

    # Reconstruct the operand from owned native data, never by copying target bytes.
    return {"raw": sec["body"],
            "bytes": sec["body"][:2] + struct.pack("<I", homes[table["name"]] + addend),
            "relocs": [(2, reloc_ledger.DIR32, table["name"])],
            "archive_sha256": hashlib.sha256(archive_bytes).hexdigest(),
            "member_sha256": hashlib.sha256(members[0]).hexdigest()}


def verify(root, old, name, source, notes, rows):
    """Validate the original generated identity and the independently owned route."""
    if not is_archive_import_row(old) or name == old["name"]:
        raise ValueError("old row is not an exact address-owned six-byte gen-import")
    result = _provider(root, name, source, notes, rows, old["rva"], old["size"])
    slot = note_value(old["notes"], "slot")
    if not slot or int(slot, 16) != struct.unpack_from("<I", result["bytes"], 2)[0]:
        raise ValueError("old slot note disagrees with the actual retail operand")
    return result


def verify_row(root, row):
    """Fresh build verification; the metadata token alone never grants a pass."""
    import csv
    evidence = note_value(row.get("notes", ""), "archive-import-evidence")
    path = Path(evidence) if evidence else None
    if (path is None or path.is_absolute() or ".." in path.parts
            or path.parts[:4] != ("targets", "game", "reverse", "identity_evidence")
            or path.suffix != ".md" or not (Path(root) / path).is_file()
            or not (Path(root) / path).read_text(encoding="utf-8").strip()):
        raise ValueError("archive dispatch row needs a nonempty identity evidence file")
    rows = []
    with (Path(root) / "targets/game/reverse/functions.csv").open(newline="") as handle:
        for candidate in csv.DictReader(handle):
            if candidate["source"] == row["source"] and candidate["status"] == "matched":
                rows.append({"name": candidate["name"], "rva": int(candidate["target_rva"], 16),
                             "size": int(candidate["target_size"]), "source": candidate["source"],
                             "status": candidate["status"], "notes": candidate["notes"]})
    result = _provider(root, row["name"], row["source"], row.get("notes", ""), rows,
                       int(row["target_rva"], 16), int(row["target_size"]))
    for key in ("archive_sha256", "member_sha256"):
        token = {"archive_sha256": "archive-import-sha256",
                 "member_sha256": "archive-import-member-sha256"}[key]
        if note_value(row.get("notes", ""), token) != result[key]:
            raise ValueError(f"archive dispatch {key} changed since its verified replacement")
    return result
