#!/usr/bin/env python3
"""Compose the complete retail image from compiled objects plus explicit,
sealed retail bridges: the fleet's integration measure.

Productizes the address-preserving reconstruction linker of the owner's
gpt-6.1-sol research (build/wt_codex_readonly_audit_20260929/build/
BFME_FRAMEWORK_BREAKTHROUGH.md, framework_layout/prototype/, accepted by two
adversarial reviews). Every byte of the file and of the loaded image has
exactly one OWNER, an address interval:

  compiled    a section slice of a compiled census object (an image_check
              item: its selected definition, at the one retail home its
              bytes prove), with EACH relocation field bound individually to
              the destination retail's field demands at that site. Two
              references through one undefined symbol may need different
              destinations; binding is per site, never per name. A
              reference to an absolute symbol (fs:[0]) is bound to its
              value, by name, from an explicit policy.
  bridge      a retail fragment nothing compiled owns yet, sealed with its
              hash; header, section content, raw alignment
  zero-fill   the loader's zero tail of a section (virtual beyond raw)

`seal` runs image_check on a census (its objects, /MAP selection and ledger),
selects compiled owners (authored, vendored, generated, library; never a
dump, whose bytes are retail re-encoded), reads the baseline ONCE to cut the
bridges, hard-links the selected objects into the bundle and writes a
manifest whose canonical hash is the contract. `compose` reads only the
bundle: a Python audit hook refuses the baseline and the census objects, and
the trusted contract hash must be given on the command line. It starts from
empty buffers, re-parses every selected COFF object, requires its relocation
set on each slice to equal the manifest's (fields straddling either end of a
slice are rejected), evaluates every field, requires every destination to be
owned, every file and image byte owned exactly once, each owner where the PE
section table puts it, the produced headers to equal the contract, a
loader-style mapping of the produced file to equal the address-owned image,
and the output's SHA-256 to equal the baseline's. There is no implicit
fallback: a byte nobody owns is a hole and fails the composition. Owner order
does not matter (the contract sorts owners; the output is identical).

Four figures, never merged (compose prints them; README/Discord unchanged):
  clean-source recovery    progress.py's authored + vendored bytes
  integrated               compiled bytes placed and verified in the
                           composed image, by lane and code/data
  source closure           image_check's closed-strict bytes
  retail dependencies      bridge bytes by kind and section

What this is not: a native link.exe link, a movable image or a boot. The
placement is retail's; bridges keep every unknown reference where it was.

  python3 tools/image_compose.py seal --census build/wt_link --tree build/wt_census_<commit> [--scalars CSV]
  python3 tools/image_compose.py compose --contract-sha256 <hash from seal>
  python3 tools/image_compose.py report
"""
import argparse
import bisect
import collections
import hashlib
import json
import os
import struct
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "build" / "image_compose"
LANES = ("authored", "vendored", "generated", "library")  # compiled owners, in selection priority
SUPPORTED = (0x0006, 0x0007, 0x0014)  # DIR32, DIR32NB, REL32
ABSOLUTE = {"__except_list": 0}  # the absolute symbols a field may name (fs:[0])


def sha(data):
    return hashlib.sha256(data).hexdigest()


def sha_file(path):
    digest = hashlib.sha256()
    with Path(path).open("rb") as handle:
        while True:
            block = handle.read(1 << 20)
            if not block:
                return digest.hexdigest()
            digest.update(block)


def canonical_hash(value):
    digest = hashlib.sha256()
    for piece in json.JSONEncoder(sort_keys=True, separators=(",", ":")).iterencode(value):
        digest.update(piece.encode("utf-8"))
    return digest.hexdigest()


def contract(manifest):
    """The contract a trusted hash pins: everything but owner order."""
    return {**{key: value for key, value in manifest.items() if key != "owners"},
            "owners": sorted(manifest["owners"], key=lambda owner: (owner["rva"], owner["id"]))}


# ------------------------------------------------------------------ COFF (compose side: stdlib only)


def coff_sections(data):
    """[(size, body or None, [(offset, symbol index, type)] sorted)] of a COFF object."""
    machine, count, _, table, nsyms, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C:
        raise ValueError("not an i386 COFF object")
    sections = []
    for index in range(count):
        at = 20 + optional + 40 * index
        size, pointer, relocs, _, nrelocs, _, flags = struct.unpack_from("<IIIIHHI", data, at + 16)
        if flags & 0x01000000:
            raise ValueError("COFF relocation overflow is not supported")
        body = None if flags & 0x80 or not pointer else data[pointer:pointer + size]
        if body is not None and len(body) != size:
            raise ValueError("truncated COFF section")
        fixups = sorted(struct.iter_unpack("<IIH", data[relocs:relocs + 10 * nrelocs])) if nrelocs else []
        sections.append((size, body, fixups))
    return sections


def section_slice(sections, number, start, size):
    """(bytes, {(offset, type, addend, symbol index)}) of [start, start+size)
    of section `number`: every compiler field inside, a field straddling
    either end rejected."""
    if not 0 < number <= len(sections):
        raise ValueError(f"no section {number}")
    total, body, fixups = sections[number - 1]
    if start < 0 or start + size > total:
        raise ValueError("slice outside its COFF section")
    data = body[start:start + size] if body is not None else bytes(size)
    fields = set()
    offsets = [fixup[0] for fixup in fixups]
    for where, index, kind in fixups[bisect.bisect_left(offsets, start - 3):bisect.bisect_left(offsets, start + size)]:
        width = 2 if kind == 0x000A else 4
        if where < start:
            if where + width > start:
                raise ValueError("a compiler relocation straddles the slice's start")
            continue
        if where + width > start + size:
            raise ValueError("a compiler relocation straddles the slice's end")
        if kind not in SUPPORTED:
            raise ValueError(f"unsupported relocation type 0x{kind:X}")
        fields.add((where - start, kind, struct.unpack_from("<i", data, where - start)[0], index))
    return data, fields


# ------------------------------------------------------------------ seal


def pe_layout(data):
    """Header facts and sections of the baseline PE (seal side)."""
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count, optional = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    opt = pe + 24
    entry, base = struct.unpack_from("<I", data, opt + 16)[0], struct.unpack_from("<I", data, opt + 28)[0]
    image_size, header_size = struct.unpack_from("<II", data, opt + 56)
    directories = struct.unpack_from("<I", data, opt + 92)[0]
    sections = []
    for index in range(count):
        at = opt + optional + 40 * index
        name = data[at:at + 8].rstrip(b"\0").decode("latin-1")
        vsize, rva, raw, pointer = struct.unpack_from("<IIII", data, at + 8)
        sections.append({"name": name, "rva": rva, "virtual_size": vsize, "raw_size": raw, "file_offset": pointer,
                         "characteristics": struct.unpack_from("<I", data, at + 36)[0]})
    return {"file_size": len(data), "image_base": base, "entry_rva": entry, "image_size": image_size,
            "header_size": header_size, "sections": sections,
            "directories": [list(struct.unpack_from("<II", data, opt + 96 + 8 * i)) for i in range(directories)]}


def candidates(image):
    """Compiled owner candidates from an image_check run, in selection order,
    and the rejected ones counted by reason."""
    import image_check as I
    rejected = collections.Counter()
    found = []
    for item in image.items:
        if not item.bound or item.home is None or item.constant or item.size <= 0:
            continue
        if item.lane not in LANES:
            rejected[f"lane {item.lane or 'unknown'}"] += 1
            continue
        if len(item.homes or {item.home}) > 1 and not item.derived:
            rejected["several homes"] += 1
            continue
        if image.bytes_at(item, item.home) is not None:
            rejected["bytes differ from retail"] += 1
            continue
        found.append(item)
    order = {lane: i for i, lane in enumerate(LANES)}
    found.sort(key=lambda item: (order[item.lane], not item.code, item.home, item.obj.name))
    return found, rejected, I


def bind_fields(image, item, I):
    """[offset, type, addend, symbol index, destination RVA, absolute name]
    for every relocation field of `item` at its home: the destination is the
    one retail's field demands there (per site). None with a reason when a
    field cannot be bound."""
    retail = image.read(item.home, item.size) if item.sec.body is not None else bytes(item.size)
    body = item.body()
    edges = []
    for where, index, kind in sorted(item.relocs):
        at = where - item.start
        if kind not in SUPPORTED:
            return None, f"relocation type 0x{kind:X}"
        symbol = item.obj.symbols.get(index)
        addend = struct.unpack_from("<i", body, at)[0]
        value = struct.unpack_from("<i", retail, at)[0]
        if symbol is not None and symbol[0] in ABSOLUTE and kind == 0x0006:
            if (value - addend) & 0xFFFFFFFF != ABSOLUTE[symbol[0]]:
                return None, f"absolute {symbol[0]} differs"
            edges.append([at, kind, addend, index, None, symbol[0]])
            continue
        if kind == 0x0006:
            target = (value - I.BASE) & 0xFFFFFFFF
        elif kind == 0x0007:
            target = value & 0xFFFFFFFF
        else:
            target = (item.home + at + 4 + value) & 0xFFFFFFFF
        if not 0 <= target < image.image_size:
            return None, "a field's destination is outside the image"
        edges.append([at, kind, addend, index, target, None])
    return edges, None


def seal(image, baseline, bundle, figures, paths=None):
    """Select compiled owners, cut the sealed bridges and write the bundle.
    Returns (manifest, contract hash)."""
    data = Path(baseline).read_bytes()
    layout = pe_layout(data)
    bundle = Path(bundle)
    (bundle / "objects").mkdir(parents=True, exist_ok=True)
    found, rejected, I = candidates(image)
    paths = paths or image.paths
    occupied = []  # sorted (start, end)
    sections = layout["sections"]

    def section_of(rva, size):
        for sec in sections:
            end = sec["rva"] + max(sec["raw_size"], sec["virtual_size"])
            if sec["rva"] <= rva and rva + size <= end:
                return sec
        return None

    owners, objects, digests = [], {}, {}
    for item in found:
        home, size = item.home, item.size
        sec = section_of(home, size)
        if sec is None or home < layout["header_size"]:
            rejected["outside one section"] += 1
            continue
        raw_end = sec["rva"] + sec["raw_size"]
        if home < raw_end < home + size:
            rejected["straddles the raw/zero-fill boundary"] += 1
            continue
        in_tail = home >= raw_end
        body = item.body()
        if in_tail and (item.relocs or (body is not None and any(body))):
            rejected["initialized bytes in the zero-fill tail"] += 1
            continue
        if item.code and sec["name"] != ".text":
            rejected["code outside .text"] += 1
            continue
        at = bisect.bisect_right(occupied, (home, float("inf")))
        if (at and occupied[at - 1][1] > home) or (at < len(occupied) and occupied[at][0] < home + size):
            rejected["overlaps a selected owner"] += 1
            continue
        edges, why = bind_fields(image, item, I)
        if edges is None:
            rejected[why] += 1
            continue
        path = paths[item.obj.name]
        if path not in digests:
            digests[path] = sha_file(path)
        digest = digests[path]
        key = digest[:24]
        if key not in objects:
            blob = bundle / "objects" / f"{key}.obj"
            if not blob.exists():
                try:
                    os.link(path, blob)
                except OSError:
                    blob.write_bytes(Path(path).read_bytes())
            if sha_file(blob) != digest:
                raise SystemExit(f"image_compose: {path} changed while it was sealed")
            objects[key] = {"blob": f"objects/{key}.obj", "sha256": digest, "origin": item.obj.name}
        coff = bytes(size) if body is None else body
        owners.append({"id": f"c{home:08X}", "kind": "compiled", "rva": home, "size": size,
                       "file_offset": None if in_tail else sec["file_offset"] + home - sec["rva"],
                       "section": sec["name"], "object": key, "coff_section": item.sec.number,
                       "coff_offset": item.start, "coff_sha256": sha(coff), "lane": item.lane,
                       "code": item.code, "name": item.label(), "edges": edges})
        bisect.insort(occupied, (home, home + size))
    rejected = dict(rejected)
    pack = bytearray()

    def bridge(kind, rva, size, file_offset, section):
        chunk = data[file_offset:file_offset + size]
        owners.append({"id": f"b{rva:08X}", "kind": kind, "rva": rva, "size": size, "file_offset": file_offset,
                       "section": section, "pack": [len(pack), size], "sha256": sha(chunk), "edges": []})
        pack.extend(chunk)

    bridge("header", 0, layout["header_size"], 0, "headers")
    cursor = layout["header_size"]
    spans = sorted(occupied)
    for sec in sections:
        start, raw_end = sec["rva"], sec["rva"] + sec["raw_size"]
        end = sec["rva"] + max(sec["raw_size"], sec["virtual_size"])
        content_end = min(raw_end, sec["rva"] + sec["virtual_size"]) if sec["virtual_size"] else raw_end
        if cursor < start:
            owners.append({"id": f"g{cursor:08X}", "kind": "image-gap", "rva": cursor, "size": start - cursor,
                           "file_offset": None, "section": "", "edges": []})
        cursor = start
        inside = [span for span in spans if start <= span[0] < end] + [(end, end)]
        for low, high in inside:
            for piece_start, piece_end, kind in ((cursor, min(low, content_end), "bridge"),
                                                 (max(cursor, content_end), min(low, raw_end), "alignment"),
                                                 (max(cursor, raw_end), low, "zero-fill")):
                if piece_start < piece_end:
                    if kind == "zero-fill":
                        owners.append({"id": f"z{piece_start:08X}", "kind": kind, "rva": piece_start,
                                       "size": piece_end - piece_start, "file_offset": None,
                                       "section": sec["name"], "edges": []})
                    else:
                        bridge(kind, piece_start, piece_end - piece_start,
                               sec["file_offset"] + piece_start - sec["rva"], sec["name"])
            cursor = max(cursor, high)
        cursor = end
    if cursor < layout["image_size"]:
        owners.append({"id": f"g{cursor:08X}", "kind": "image-gap", "rva": cursor,
                       "size": layout["image_size"] - cursor, "file_offset": None, "section": "", "edges": []})
    (bundle / "bridges.bin").write_bytes(bytes(pack))
    manifest = {"schema": 1, "mode": "fixed-retail-layout", **layout, "baseline_sha256": sha(data),
                "bridges": {"blob": "bridges.bin", "sha256": sha(bytes(pack))}, "objects": objects,
                "absolute": ABSOLUTE, "figures": figures, "rejected_candidates": rejected, "owners": owners}
    with (bundle / "manifest.json").open("w", encoding="utf-8") as handle:
        for piece in json.JSONEncoder(separators=(",", ":")).iterencode(manifest):
            handle.write(piece)
    digest = canonical_hash(contract(manifest))
    (bundle / "contract.sha256").write_text(digest + "\n", encoding="utf-8")
    return manifest, digest


# ------------------------------------------------------------------ compose


def deny_reads(paths):
    """Refuse, for the rest of this process, every open of `paths` (files, or
    everything under a directory). Probes the first to prove the refusal
    works; returns the list of refused opens."""
    forbidden = [str(Path(path).resolve()).casefold() for path in paths]
    refused = []

    def audit(event, args):
        if event == "open" and args and isinstance(args[0], (str, bytes, os.PathLike)):
            try:
                target = str(Path(os.fsdecode(args[0])).resolve()).casefold()
            except (ValueError, TypeError, OSError):
                return
            if any(target == path or target.startswith(path.rstrip("\\/") + os.sep) for path in forbidden):
                refused.append(target)
                raise PermissionError(f"image_compose: {target} is not a composition input")
    probe = next((Path(path) for path in paths if Path(path).is_file()), None)
    sys.addaudithook(audit)
    if probe is not None:
        try:
            probe.read_bytes()
        except PermissionError:
            pass
        else:
            raise SystemExit("image_compose: the read denial did not operate")
    return refused


def mark(mask, start, size, ident):
    if start < 0 or size < 1 or start + size > len(mask):
        raise ValueError(f"{ident}: range outside the file/image")
    if any(mask[start:start + size]):
        raise ValueError(f"{ident}: ownership overlap")
    mask[start:start + size] = b"\1" * size


def compose(bundle, trusted, output):
    """Compose the image from the bundle alone; the receipt, or ValueError."""
    bundle = Path(bundle)
    manifest = json.loads((bundle / "manifest.json").read_text(encoding="utf-8"))
    if not trusted:
        raise ValueError("a trusted contract SHA-256 is required")
    if canonical_hash(contract(manifest)) != trusted:
        raise ValueError("the manifest's ownership/binding/input contract differs from the trusted hash")
    if manifest.get("schema") != 1 or manifest.get("mode") != "fixed-retail-layout":
        raise ValueError("unsupported manifest")
    owners = manifest["owners"]
    by_id = {owner["id"]: owner for owner in owners}
    if len(by_id) != len(owners):
        raise ValueError("duplicate owner identity")
    ordered = sorted(owners, key=lambda owner: owner["rva"])
    starts = [owner["rva"] for owner in ordered]
    pack = (bundle / manifest["bridges"]["blob"]).read_bytes()
    if sha(pack) != manifest["bridges"]["sha256"]:
        raise ValueError("sealed bridge pack hash differs")
    file_bytes, memory = bytearray(manifest["file_size"]), bytearray(manifest["image_size"])
    file_mask, image_mask = bytearray(manifest["file_size"]), bytearray(manifest["image_size"])
    sections = {sec["name"]: sec for sec in manifest["sections"]}
    cache = collections.OrderedDict()
    integrated, bridges = collections.Counter(), collections.Counter()
    fields_evaluated = 0
    base = manifest["image_base"]
    for owner in owners:
        ident, rva, size, kind = owner["id"], owner["rva"], owner["size"], owner["kind"]
        if kind == "header":
            if owner["file_offset"] != 0 or rva != 0 or size != manifest["header_size"]:
                raise ValueError(f"{ident}: header placement differs")
        elif kind == "image-gap":
            if owner["file_offset"] is not None:
                raise ValueError(f"{ident}: an image gap has no file bytes")
        else:
            sec = sections.get(owner["section"])
            if sec is None:
                raise ValueError(f"{ident}: section {owner['section']!r} absent")
            if owner["file_offset"] is None:
                if rva < sec["rva"] + sec["raw_size"] or rva + size > sec["rva"] + sec["virtual_size"]:
                    raise ValueError(f"{ident}: zero-fill owner outside its section's virtual tail")
            elif (owner["file_offset"] != sec["file_offset"] + rva - sec["rva"] or rva < sec["rva"]
                  or rva + size > sec["rva"] + sec["raw_size"]):
                raise ValueError(f"{ident}: file/RVA placement disagrees with the section table")
        if kind == "compiled":
            record = manifest["objects"][owner["object"]]
            if owner["object"] not in cache:
                data = (bundle / record["blob"]).read_bytes()
                if sha(data) != record["sha256"]:
                    raise ValueError(f"{ident}: sealed object hash differs")
                cache[owner["object"]] = coff_sections(data)
                while len(cache) > 16:
                    cache.popitem(last=False)
            else:
                cache.move_to_end(owner["object"])
            body, fields = section_slice(cache[owner["object"]], owner["coff_section"], owner["coff_offset"], size)
            if sha(body) != owner["coff_sha256"]:
                raise ValueError(f"{ident}: compiled bytes differ")
            if fields != {tuple(edge[:4]) for edge in owner["edges"]}:
                raise ValueError(f"{ident}: compiler relocation set differs")
            if owner["file_offset"] is None and (any(body) or owner["edges"]):
                raise ValueError(f"{ident}: initialized compiled bytes in a zero-fill tail")
            linked = bytearray(body)
            covered = set()
            for at, typ, addend, _, target, absolute in owner["edges"]:
                if covered.intersection(range(at, at + 4)):
                    raise ValueError(f"{ident}: overlapping relocation fields")
                covered.update(range(at, at + 4))
                if absolute is not None:
                    if absolute not in manifest["absolute"] or typ != 0x0006:
                        raise ValueError(f"{ident}: absolute {absolute} is not an allowed binding")
                    value = manifest["absolute"][absolute] + addend
                else:
                    index = bisect.bisect_right(starts, target) - 1
                    holder = ordered[index] if index >= 0 else None
                    if holder is None or not holder["rva"] <= target < holder["rva"] + holder["size"]:
                        raise ValueError(f"{ident}+0x{at:X}: destination 0x{target:08X} has no owner")
                    value = base + target if typ == 0x0006 else target if typ == 0x0007 else target - (rva + at + 4)
                    if typ == 0x0014 and not -(1 << 31) <= value < (1 << 31):
                        raise ValueError(f"{ident}+0x{at:X}: REL32 overflow")
                struct.pack_into("<I", linked, at, value & 0xFFFFFFFF)
                fields_evaluated += 1
            integrated[f"{owner['lane']}/{'code' if owner['code'] else 'data'}"] += size
        elif kind in ("zero-fill", "image-gap"):
            if owner["edges"]:
                raise ValueError(f"{ident}: a zero owner has no fields")
            linked = bytes(size)
            bridges[kind] += size
        else:
            offset, length = owner["pack"]
            linked = pack[offset:offset + length]
            if length != size or sha(linked) != owner["sha256"]:
                raise ValueError(f"{ident}: sealed bridge fragment differs")
            bridges[f"{kind}:{owner['section'].strip() or '(unnamed)'}" if kind == "bridge" else kind] += size
        mark(image_mask, rva, size, ident)
        memory[rva:rva + size] = linked
        if owner["file_offset"] is not None:
            mark(file_mask, owner["file_offset"], size, ident)
            file_bytes[owner["file_offset"]:owner["file_offset"] + size] = linked
    if not all(file_mask):
        raise ValueError(f"file ownership hole at 0x{file_mask.index(0):X}")
    if not all(image_mask):
        raise ValueError(f"image ownership hole at RVA 0x{image_mask.index(0):X}")
    produced = pe_layout(bytes(file_bytes))
    for key in ("image_base", "entry_rva", "image_size", "header_size", "sections", "directories"):
        if produced[key] != manifest[key]:
            raise ValueError(f"produced PE header differs from the contract: {key}")
    loader = bytearray(manifest["image_size"])
    loader[:manifest["header_size"]] = file_bytes[:manifest["header_size"]]
    for sec in manifest["sections"]:
        loader[sec["rva"]:sec["rva"] + sec["raw_size"]] = \
            file_bytes[sec["file_offset"]:sec["file_offset"] + sec["raw_size"]]
    if loader != memory:
        raise ValueError("a loader-style mapping of the produced file differs from the address-owned image")
    result = sha(bytes(file_bytes))
    if result != manifest["baseline_sha256"]:
        raise ValueError(f"the composed image's SHA-256 {result} differs from the baseline's")
    output = Path(output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(bytes(file_bytes))
    receipt = {"output_sha256": result, "trusted_contract_sha256": trusted, "owners": len(owners),
               "compiled_owners": sum(1 for owner in owners if owner["kind"] == "compiled"),
               "compiler_fields_evaluated": fields_evaluated, "file_bytes": len(file_mask),
               "image_bytes": len(image_mask), "address_owned_memory_sha256": sha(bytes(memory)),
               "loader_mapping_equal": True, "integrated_bytes": dict(sorted(integrated.items())),
               "integrated_total": sum(integrated.values()), "retail_dependency_bytes": dict(sorted(bridges.items())),
               "retail_dependency_total": sum(bridges.values()), "figures": manifest["figures"],
               "rejected_candidates": manifest["rejected_candidates"],
               "not_claimed": ["native link.exe link", "movable image", "source-closed program", "boot"]}
    output.with_suffix(".receipt.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    return receipt


# ------------------------------------------------------------------ CLI


def figures_from(image, linked):
    """The seal-time figures: clean-source recovery (progress.py on the
    census tree) and source closure (image_check)."""
    import image_check
    progress = sys.modules["progress"]
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    start, size = progress.retail_text()
    split = progress.real_split(matched, notes, start, size, progress.naked_cpp_rows_at(matched, None))
    summary = image_check.results(image, linked)[0]
    return {"census": linked, "clean_source_recovery": {"authored": split["authored"], "vendored": split["vendored"],
                                                        "total": progress.decompiled(split)},
            "source_closure": {"closed_strict_bytes": summary["closed_strict_bytes"],
                               "closed_strict_functions": summary["closed_strict_functions"],
                               "closed_bytes": summary["closed_bytes"],
                               "retail_true_bytes": summary["retail_true_bytes"]}}


def print_figures(receipt):
    figures = receipt["figures"]
    clean, closure = figures["clean_source_recovery"], figures["source_closure"]
    print(f"image_compose: composed {receipt['file_bytes']:,} file bytes, SHA-256 {receipt['output_sha256']} "
          f"(= baseline), {receipt['owners']:,} owners, {receipt['compiler_fields_evaluated']:,} compiler fields")
    print(f"  1. clean-source recovery (authored + vendored): {clean['total']:,}")
    print(f"  2. integrated (compiled, placed and verified):  {receipt['integrated_total']:,}")
    for key, value in receipt["integrated_bytes"].items():
        print(f"       {key:22} {value:>12,}")
    print(f"  3. source closure (closed strict):              {closure['closed_strict_bytes']:,}")
    print(f"  4. retail dependencies (bridges):               {receipt['retail_dependency_total']:,}")
    for key, value in receipt["retail_dependency_bytes"].items():
        print(f"       {key:22} {value:>12,}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="command", required=True)
    s = sub.add_parser("seal", help="run image_check on a census and seal a composition bundle")
    s.add_argument("--census", type=Path, required=True)
    s.add_argument("--tree", type=Path, required=True)
    s.add_argument("--scalars", type=Path)
    s.add_argument("--bundle", type=Path, default=OUT / "bundle")
    c = sub.add_parser("compose", help="compose from the bundle alone")
    c.add_argument("--bundle", type=Path, default=OUT / "bundle")
    c.add_argument("--contract-sha256", required=True)
    c.add_argument("--output", type=Path, default=OUT / "composed.exe")
    c.add_argument("--forbid-read", type=Path, action="append", default=[],
                   help="a file or directory the composer may not open (default: the census tree's baseline "
                        "and objects, as recorded at seal)")
    r = sub.add_parser("report", help="print the four figures of the last composition")
    r.add_argument("--output", type=Path, default=OUT / "composed.exe")
    args = ap.parse_args(argv)
    if args.command == "report":
        print_figures(json.loads(args.output.with_suffix(".receipt.json").read_text(encoding="utf-8")))
        return 0
    if args.command == "compose":
        forbid = list(args.forbid_read)
        if not forbid:
            recorded = json.loads((args.bundle / "sources.json").read_text(encoding="utf-8"))
            forbid = [Path(path) for path in recorded["forbid"]]
        refused = deny_reads(forbid)
        started = time.time()
        try:
            receipt = compose(args.bundle, args.contract_sha256, args.output)
        except ValueError as exc:
            print(f"image_compose: FAIL: {exc}", file=sys.stderr)
            return 2
        receipt["read_denial"] = {"forbidden": [str(path) for path in forbid], "probe_refused": bool(refused),
                                  "refused_after_probe": max(0, len(refused) - 1)}
        receipt["seconds"] = round(time.time() - started)
        args.output.with_suffix(".receipt.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
        if receipt["read_denial"]["refused_after_probe"]:
            print("image_compose: FAIL: the composer tried to read a forbidden input", file=sys.stderr)
            return 2
        print_figures(receipt)
        return 0
    import image_check
    census_tree, tree = args.census.resolve(), args.tree.resolve()
    lock = image_check.census_lock(census_tree)
    if lock is None:
        raise SystemExit(f"image_compose: {census_tree}.census-lock is held (a census is running); try later")
    try:
        image, linked = image_check.load(tree, census_tree, args.scalars)
        image.run()
        figures = figures_from(image, linked)
        if args.bundle.exists():
            import shutil
            shutil.rmtree(args.bundle)
        manifest, digest = seal(image, image.baseline, args.bundle, figures)
    finally:
        lock.rmdir()
    objects_dir = next(iter(image.paths.values())).parent
    (args.bundle / "sources.json").write_text(json.dumps({"forbid": [str(image.baseline), str(objects_dir)]}),
                                              encoding="utf-8")
    compiled = [owner for owner in manifest["owners"] if owner["kind"] == "compiled"]
    print(f"image_compose: sealed {len(manifest['owners']):,} owners ({len(compiled):,} compiled, "
          f"{sum(owner['size'] for owner in compiled):,} bytes) in {args.bundle}; "
          f"rejected {manifest['rejected_candidates']}")
    print(f"image_compose: contract SHA-256 {digest}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
