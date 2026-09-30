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

The LINKING WORKLIST ranks every bad node on a decompiled function's closure
by the authored files it alone would source-close (every counted function of
the file closed strict), groups them by family and by fix site, and serves one
at a time through tools/claims.py (single-fix model: see SINGLE_FIX). The
daily census (tools/fleet/daily_census.sh) regenerates the tracked
targets/game/reverse/linking_worklist.csv; `next` serves from it on any host
and first skips rows the tree has moved past since that census (Freshness).

  python3 tools/image_compose.py worklist --image-check <image_check out dir> --tree build/wt_census_<commit>
      [--status link_status.csv] [--publish targets/game/reverse/linking_worklist.csv]
  python3 tools/image_compose.py next [--family data] [--no-claim] [--worklist build/image_compose/worklist.csv]
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


# ------------------------------------------------------------------ worklist
#
# Source closure is per function; the Linking bar is per file. The worklist
# asks, of every bad node an image_check run leaves on a decompiled function's
# closure: which authored FILES would have every counted function closed
# strict if that node alone were fixed. It reads image_check's outputs
# (graph.pkl, items.csv, summary.json) and a checkout of their census commit;
# it never reruns image_check and changes no figure.

SINGLE_FIX = ("single-fix model: unlock_* counts what closes when THIS blocker (a group row: every blocker of "
              "the group) alone becomes retail-true and movable with the graph otherwise unchanged; a repair that "
              "changes a selected copy, its bytes or its references can add blockers (interactions ignored)")
FAMILIES = ("provider", "data", "import", "eh", "class-copy", "bridge", "body", "other")
EH_SECTIONS = (".xdata", ".text$x")
EH_NAMES = ("__ehhandler$", "__unwindfunclet$", "__catch$", "__ehfuncinfo$", "__tryblocktable$",
            "__unwindtable$", "__catchsym$")
CLASS_NAMES = ("??_7", "??_8", "??_R")
TYPED = "words need typed evidence"
PUBLISHED = ROOT / "targets" / "game" / "reverse" / "linking_worklist.csv"
# The one queue schema: `next` here and provider_repair.py data-next read these columns (tests pin both).
PUBLISHED_FIELDS = ["rank", "family", "rule", "verdict", "blocker", "claim_rva", "unlock_files",
                    "unlock_authored_bytes", "unlock_function_bytes", "files", "fix_site", "reason", "command",
                    "census"]


def exact_command(family, rule, verdict, blocker, claim, source, referrer):
    """The command that works on THIS blocker (never another picker, which
    would skip the claim `next` just took for this worker)."""
    name = f"'{blocker}'"
    if family == "provider" and rule not in ("alias", "pinned-elsewhere"):  # those two: rename at the referrer
        return f"python3 tools/provider_repair.py next --symbol {name}"
    if family == "data" and verdict == "unresolved":
        return f"python3 tools/provider_repair.py data-next --symbol {name}"
    if rule.startswith(TYPED):
        return f"python3 tools/reloc_ledger.py  # prove {claim}'s words scalar or pointer"
    from import_binding import editable  # the one generated-source rule: "" = the fix would edit one
    if family == "import" and referrer:
        return (f"python3 tools/import_binding.py apply '{referrer}'; python3 tools/import_binding.py check "
                f"'{referrer}'" if editable(referrer) else "")
    if family == "bridge" and claim:
        return f"python3 tools/brief.py --rvas {claim}"
    if family in ("body", "eh") and source:
        return f"./build.sh '{source}'" if editable(source) else ""
    target = referrer or source  # the fix edits it (a rename or a definition at the referrer)
    return f"python3 tools/link_check.py '{target}'" if editable(target) else ""
WORKLIST_FIELDS = ["rank", "blocker", "node", "family", "rule", "fix_site", "object", "source", "home", "claim_rva",
                   "verdict", "reason", "unlock_files", "unlock_authored_bytes", "unlock_vendored_bytes",
                   "unlock_census_linked_files", "unlock_functions", "unlock_function_bytes", "group_unlock_files",
                   "group_unlock_authored_bytes", "files", "example", "command", "census"]
GROUP_FIELDS = ["rank", "fix_site", "families", "blockers_listed", "unlock_files", "unlock_authored_bytes",
                "unlock_vendored_bytes", "unlock_census_linked_files", "unlock_functions", "unlock_function_bytes",
                "files"]


def family_of(node, section):
    """(family, rule) of one bad graph node (image_check.compact tuple)."""
    if node[0] == "leaf":
        name, kind, reason = node[1], node[2], node[4]
        tag = reason[reason.find("(") + 1:reason.rfind(")")] if "(" in reason else ""
        if name.startswith(CLASS_NAMES):
            return "class-copy", "vftable/RTTI name nothing defines"
        if kind == "code-literal" or tag == "data":
            return "data", kind if kind == "code-literal" else "unresolved data name"
        if name.startswith("__imp_") or tag == "import":
            return "import", "unresolved import"
        if tag == "dump":
            return "bridge", "name pinned to a dump's address"
        if tag in ("alias", "pinned-elsewhere") or kind in ("selection-unknown", "discarded"):
            return "provider", tag or kind
        return "other", f"{kind}: {tag or reason}"
    label, reason, verdict, lane = node[1], node[4], node[5], node[7]
    if section.startswith(EH_SECTIONS) or label.startswith(EH_NAMES):
        return "eh", "EH table or funclet"
    if label.startswith(CLASS_NAMES):
        return "class-copy", "vftable/RTTI"
    if lane in ("dump", "generated"):
        return "bridge", f"{lane} body"
    if not section.startswith(".text"):
        if "unrelocated in-image dword" in reason:
            return "data", TYPED
        return "data", f"{section or '?'} item"
    if ("no retail address" in reason or "placements disagree" in reason or "several candidate" in reason
            or reason.startswith("shared address")):
        return "provider", "no single retail home"
    if " lands at " in reason:
        return "provider", "a relocation reaches a copy not at its retail address"
    if lane == "library":
        return "other", "library member"
    return "body", f"{verdict} body"


def class_of(name):
    """The class a vftable/RTTI name belongs to (the header that fixes it), else the name."""
    import re
    for pattern in (r"^\?\?_[78]([^@?][^?]*?)@@", r"^\?\?_R[234]([^@?][^?]*?)@@", r"\?A[VU]([^?]*?)@@",
                    r"([A-Za-z_]\w*)@@8$"):
        found = re.search(pattern, name)
        if found:
            return found.group(1)
    return name


def fix_site(node, family, source_of):
    if family == "class-copy":
        return f"class:{class_of(node[1])}"
    if node[0] == "leaf":
        return f"name:{node[1]}"
    source = source_of.get(node[2])
    return f"source:{source}" if source else f"object:{node[2]}"


def reach_keys(succ, comp, keys, cap):
    """Per node, the frozenset of keys of the bad nodes it reaches (itself
    included; keys[n] is None for a good node), None when more than `cap`.
    image_check._badsets with keys and a cap; `comp` from Image._scc."""
    members = collections.defaultdict(list)
    for node, c in enumerate(comp):
        members[c].append(node)
    empty, out = frozenset(), {}
    for c in sorted(members):  # successors first
        found, many = set(), False
        for node in members[c]:
            if keys[node] is not None:
                found.add(keys[node])
            for nxt in succ[node]:
                d = comp[nxt]
                if d != c:
                    if out[d] is None:
                        many = True
                        break
                    found |= out[d]
            if many or len(found) > cap:
                many = True
                break
        out[c] = None if many else frozenset(found) if found else empty
    return [out[comp[n]] for n in range(len(comp))]


def single_fix(functions, file_of, sets):
    """Under the single-fix model: ({key: files}, {key: functions}, closed
    files). A file unlocks for key k only when the union of its functions'
    reachable bad keys is exactly {k}; a file with a second key, or with more
    than the cap, unlocks for nobody."""
    per_file = {}
    for node in functions:
        current, found = per_file.get(file_of[node], frozenset()), sets[node]
        per_file[file_of[node]] = None if current is None or found is None else current | found
    files, fns = collections.defaultdict(list), collections.defaultdict(list)
    for node in functions:
        if sets[node] is not None and len(sets[node]) == 1:
            fns[next(iter(sets[node]))].append(node)
    closed = []
    for path, found in per_file.items():
        if found == frozenset():
            closed.append(path)
        elif found is not None and len(found) == 1:
            files[next(iter(found))].append(path)
    return files, fns, closed


def text_counter(text, start):
    """real(low, high): retail .text bytes in [low, high) that are not 0xCC."""
    def real(low, high):
        low, high = max(low, start), min(high, start + len(text))
        return 0 if low >= high else high - low - text[low - start:high - start].count(0xCC)
    return real


def merged(intervals):
    out = []
    for low, high in sorted(intervals):
        if low >= high:
            continue
        if out and low <= out[-1][1]:
            out[-1][1] = max(out[-1][1], high)
        else:
            out.append([low, high])
    return [tuple(span) for span in out]


def overlap(spans, low, high):
    """[(a, b)] of the merged `spans` inside [low, high)."""
    at = max(bisect.bisect_right(spans, (low, float("inf"))) - 1, 0)
    out = []
    while at < len(spans) and spans[at][0] < high:
        a, b = max(spans[at][0], low), min(spans[at][1], high)
        if a < b:
            out.append((a, b))
        at += 1
    return out


def census_status(tree, census):
    """{source: link_status row} the census of `census` wrote: the
    link_status.csv of the origin/master commit that recorded its history row."""
    import csv
    import subprocess
    found = subprocess.run(["git", "log", "origin/master", "--format=%H", "-S", f"{census['date']},{census['commit']}",
                            "--", "targets/game/reverse/link_census_history.csv"], cwd=tree, capture_output=True,
                           text=True, check=True).stdout.split()
    if not found:
        raise SystemExit(f"image_compose: no origin/master commit records census {census['commit']}; pass --status")
    text = subprocess.run(["git", "show", f"{found[-1]}:targets/game/reverse/link_status.csv"], cwd=tree,
                          capture_output=True, text=True, check=True).stdout
    return {row["source"]: row for row in csv.DictReader(text.splitlines())}, found[-1]


def reconcile(progress, real, counted, status, closed, census):
    """Byte-exact decomposition of source closure (closed strict, authored +
    vendored, per function, transitive) against the census's linked_authored
    (authored rows of files that link on their own terms, per file, one hop).
    `counted` [(node, home, end, lane, file, verdict, retail_verdict)]."""
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    naked = set(progress.naked_cpp_rows_at(matched, None))
    linked = {source for source, row in status.items() if row["linked"] == "yes"}
    census_spans = merged((int(key[1], 16), int(key[1], 16) + size) for key, (size, source) in matched.items()
                          if source in linked and progress.source_lane(source, notes[key], key in naked) == "authored")
    total = lambda spans: sum(real(a, b) for a, b in spans)  # noqa: E731
    census_bytes = total(census_spans)
    if census_bytes != census["linked_authored"]:
        raise SystemExit(f"image_compose: census rows give {census_bytes:,} authored bytes, the census recorded "
                         f"{census['linked_authored']:,}: not this census's link_status")
    strict_a = merged((home, end) for node, home, end, lane, *_ in counted if node in closed and lane == "authored")
    strict_all = merged((home, end) for node, home, end, *_ in counted if node in closed)
    pieces, last = [], None  # the counted functions as a partition: the first at an address owns it
    for entry in sorted(counted, key=lambda e: (e[1], e[0])):
        low = entry[1] if last is None else max(entry[1], last)
        if low < entry[2]:
            pieces.append((low, entry[2], entry))
            last = entry[2]
    closed_only, census_only, both = collections.Counter(), collections.Counter(), 0
    for low, high, (node, _, _, lane, path, verdict, retail_verdict) in pieces:
        for a, b in overlap(strict_a, low, high):
            inside = sum(real(x, y) for x, y in overlap(census_spans, a, b))
            both += inside
            if real(a, b) - inside:
                row = status.get(path)
                why = ("file has no link_status row" if row is None else
                       "file linked, bytes in no authored census row" if row["linked"] == "yes" else
                       "file not linked: " + "+".join(k for k in ("unresolved", "duplicates", "comdat_losers",
                                                                   "addresses", "wrong_selected") if row[k] != "0"))
                closed_only[why] += real(a, b) - inside
        for a, b in overlap(census_spans, low, high):
            rest = real(a, b) - sum(real(x, y) for x, y in overlap(strict_a, a, b))
            if rest:
                why = ("counted in the vendored lane" if lane != "authored" else
                       f"function not retail-true at retail's placement ({retail_verdict})"
                       if retail_verdict != "retail" else f"function retail-true, not movable ({verdict})"
                       if verdict != "retail" else "function good, its closure reaches a bad node")
                census_only[why] += rest
    counted_spans = merged((home, end) for _, home, end, *_ in counted)
    census_only["no counted function at the address"] += census_bytes - both - sum(census_only.values())
    strict_total = total(strict_all)
    return {"source_closure_bytes": strict_total, "census_linked_authored": census_bytes,
            "closed_strict_vendored_only": strict_total - total(strict_a), "closed_strict_authored": total(strict_a),
            "both": both, "closed_strict_authored_not_census": dict(closed_only.most_common()),
            "census_not_closed_strict": dict(census_only.most_common()),
            "counted_function_bytes": total(counted_spans)}


def worklist(ic_dir, tree, status_path=None, out=OUT, publish=None):
    """Rank every blocker by the authored files it alone would close; write
    worklist.csv, worklist_groups.csv and worklist_summary.json to `out`."""
    import csv
    import pickle
    import subprocess
    import image_check as I
    summary = json.loads((ic_dir / "summary.json").read_text(encoding="utf-8"))
    census = summary["census_linked"]
    if subprocess.run(["git", "diff", "--quiet", census["commit"], "--", "game", "targets/game/reverse/functions.csv",
                       "targets/game/reverse/symbols.csv", "targets/game/reverse/dir32_addresses.csv"],
                      cwd=tree).returncode:
        raise SystemExit(f"image_compose: {tree} differs from the census commit {census['commit']}")
    build, link_census, progress = I.load_tree(tree)
    with (ic_dir / "graph.pkl").open("rb") as handle:
        graph = pickle.load(handle)
    nodes = graph["nodes"]
    sections, sizes = {}, {}
    with (ic_dir / "items.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            node = int(row["id"])
            sections[node], sizes[node] = row["section"], int(row["size"])
            if row["closed"] == "":  # unbound
                sizes[node] = None
    rows = link_census.ledger()
    homes = {int(row["target_rva"], 16) for row in rows}
    source_of = {}
    for row in rows:
        source_of.setdefault(build.row_object(row).name, row["source"])
    start, size = progress.retail_text()
    real = text_counter(build.read_target_bytes(start, size), start)
    counted = []  # image_check.results' `counted`: bound code at a matched .text home, authored or vendored
    for node, entry in enumerate(nodes):
        if entry[0] != "item" or sizes.get(node) is None or not sections[node].startswith(".text"):
            continue
        home, lane = entry[6], entry[7]
        if home is None or not start <= home < start + size or lane not in I.DECOMPILED or home not in homes:
            continue
        counted.append((node, home, home + sizes[node], lane, source_of.get(entry[2], entry[2]), entry[5], entry[9]))
    closed = {e[0] for e in counted if graph["badset"][e[0]] == frozenset()}
    strict = sum(real(a, b) for a, b in merged((e[1], e[2]) for e in counted if e[0] in closed))
    if (len(counted), len(closed), strict) != (summary["decompiled_functions"], summary["closed_strict_functions"],
                                                summary["closed_strict_bytes"]):
        raise SystemExit(f"image_compose: rebuilt {len(counted):,} counted / {len(closed):,} closed strict functions, "
                         f"{strict:,} bytes; image_check says {summary['decompiled_functions']:,} / "
                         f"{summary['closed_strict_functions']:,}, {summary['closed_strict_bytes']:,}")
    succ = [()] * len(nodes)
    for node, edges in graph["edges"].items():
        succ[node] = tuple({target for _, target, _ in edges if target != node})
    comp = I.Image._scc(succ)
    good = [entry[3] for entry in nodes]
    node_sets = reach_keys(succ, comp, [None if ok else n for n, ok in enumerate(good)], 2)
    if node_sets != graph["badset"]:
        raise SystemExit("image_compose: recomputed bad sets differ from image_check's")
    family, site = {}, {}
    for node, entry in enumerate(nodes):
        if not good[node]:
            family[node] = family_of(entry, sections.get(node, ""))
            site[node] = fix_site(entry, family[node][0], source_of)
    group_sets = reach_keys(succ, comp, [site.get(n) for n in range(len(nodes))], 2)
    family_sets = reach_keys(succ, comp, [family[n][0] if n in family else None for n in range(len(nodes))],
                             len(FAMILIES))
    functions = [e[0] for e in counted]
    file_of = {e[0]: e[4] for e in counted}
    fn_bytes = {e[0]: real(e[1], e[2]) for e in counted}
    lane_spans = collections.defaultdict(list)
    for node, home, end, lane, path, *_ in counted:
        lane_spans[(path, lane)].append((home, end))
    file_bytes = collections.defaultdict(lambda: [0, 0])
    for (path, lane), spans in lane_spans.items():
        file_bytes[path][lane != "authored"] += sum(real(a, b) for a, b in merged(spans))

    def union(files, lane):  # one address in several files counts once
        return sum(real(a, b) for a, b in merged(span for p in files for span in lane_spans.get((p, lane), ())))
    status, recorded = ((census_status(tree, census)) if status_path is None else
                        ({r["source"]: r for r in csv.DictReader(status_path.open(newline="", encoding="utf-8"))},
                         str(status_path)))
    linked = {path for path, row in status.items() if row["linked"] == "yes"}

    def unlock(files, fns):
        files = sorted(files, key=lambda p: (-file_bytes[p][0], -file_bytes[p][1], p))
        return {"_files": files, "unlock_files": len(files), "unlock_authored_bytes": union(files, "authored"),
                "unlock_vendored_bytes": union(files, "vendored"),
                "unlock_census_linked_files": sum(1 for p in files if p in linked),
                "unlock_functions": len(fns), "unlock_function_bytes": sum(fn_bytes[n] for n in fns),
                "files": "; ".join(f"{p} ({file_bytes[p][0]:,})" for p in files[:5])
                         + (f"; +{len(files) - 5} more" if len(files) > 5 else "")}

    def rank_key(row):
        return (-row["unlock_authored_bytes"], -row["unlock_vendored_bytes"], -row["unlock_function_bytes"],
                row.get("blocker") or row["fix_site"], row.get("node", 0))

    by_node_files, by_node_fns, closed_files = single_fix(functions, file_of, node_sets)
    by_group_files, by_group_fns, _ = single_fix(functions, file_of, group_sets)
    by_family_files, by_family_fns, _ = single_fix(functions, file_of, family_sets)
    groups = {}
    for key in set(by_group_files) | set(by_group_fns):
        groups[key] = {"fix_site": key, **unlock(by_group_files.get(key, ()), by_group_fns.get(key, ()))}
    work, truth = [], None
    for node in set(by_node_files) | set(by_node_fns):
        entry = nodes[node]
        is_item = entry[0] == "item"
        home = entry[6] if is_item else None
        claim = home
        if claim is None and not is_item:
            truth = truth or link_census.RetailTruth(rows)
            addresses = sorted(truth.addresses(entry[1]) or ())
            claim = addresses[0] if addresses else None
        example = max(by_node_fns.get(node, ()), key=lambda n: (fn_bytes[n], -n), default=None)
        chain = []
        while example is not None:
            chain.append(example)
            if example == node or len(chain) > 64:
                break
            example = graph["hop"][example]
        referrer = source_of.get(nodes[chain[-2]][2], "") if len(chain) > 1 and chain[-1] == node else ""
        source = source_of.get(entry[2], "") if is_item else ""
        group = groups.get(site[node], {})
        work.append({"blocker": entry[1], "node": node, "family": family[node][0], "rule": family[node][1],
                     "fix_site": site[node], "object": entry[2] if is_item else "",
                     "source": source, "home": f"0x{home:08X}" if home is not None else "",
                     "claim_rva": f"0x{claim:08X}" if claim is not None else "",
                     "verdict": entry[5] if is_item else entry[2], "reason": entry[4],
                     **unlock(by_node_files.get(node, ()), by_node_fns.get(node, ())),
                     "group_unlock_files": group.get("unlock_files", 0),
                     "group_unlock_authored_bytes": group.get("unlock_authored_bytes", 0),
                     "example": " -> ".join(nodes[n][1] for n in chain), "census": census["commit"],
                     "command": exact_command(family[node][0], family[node][1], entry[5] if is_item else entry[2],
                                              entry[1], f"0x{claim:08X}" if claim is not None else "", source,
                                              referrer)})
    work.sort(key=rank_key)
    for rank, row in enumerate(work, 1):
        row["rank"] = rank
    listed = collections.Counter(row["fix_site"] for row in work)
    fams = collections.defaultdict(set)
    for node, key in site.items():
        if key in groups:
            fams[key].add(family[node][0])
    group_rows = sorted(groups.values(), key=rank_key)
    for rank, row in enumerate(group_rows, 1):
        row.update(rank=rank, families="+".join(sorted(fams[row["fix_site"]])), blockers_listed=listed[row["fix_site"]])
    blocked = collections.Counter()  # files each family blocks at all (exact: the cap is every family)
    per_file = collections.defaultdict(set)
    for node in functions:
        per_file[file_of[node]] |= family_sets[node]
    for found in per_file.values():
        blocked.update(found)
    totals = {}
    for name in FAMILIES:
        mine = [row for row in work if row["family"] == name]
        whole = unlock(by_family_files.get(name, ()), by_family_fns.get(name, ()))
        totals[name] = {"blockers": len(mine), "files_blocked": blocked[name],
                        "single_fix_authored_bytes": union([p for r in mine for p in r["_files"]], "authored"),
                        "single_fix_files": sum(r["unlock_files"] for r in mine),
                        "single_fix_function_bytes": sum(r["unlock_function_bytes"] for r in mine),
                        "whole_family_files": whole["unlock_files"],
                        "whole_family_authored_bytes": whole["unlock_authored_bytes"],
                        "whole_family_function_bytes": whole["unlock_function_bytes"]}
    authored_files = [p for p in file_bytes if file_bytes[p][0]]
    result = {"model": SINGLE_FIX, "image_check": str(ic_dir), "census": census, "link_status": recorded,
              "files": len(file_bytes), "authored_files": len(authored_files),
              "files_closed": len(closed_files),
              "files_closed_authored_bytes": union(closed_files, "authored"),
              "files_closed_vendored_bytes": union(closed_files, "vendored"),
              "counted_authored_bytes": union(list(file_bytes), "authored"),
              "blockers": len(work), "groups": len(group_rows), "families": totals,
              "reconciliation": reconcile(progress, real, counted, status, closed, census)}
    out.mkdir(parents=True, exist_ok=True)
    for name, fields, data in (("worklist.csv", WORKLIST_FIELDS, work), ("worklist_groups.csv", GROUP_FIELDS,
                                                                          group_rows)):
        with (out / name).open("w", newline="", encoding="utf-8") as handle:
            handle.write(f"# {SINGLE_FIX}\n")
            writer = csv.DictWriter(handle, fields, lineterminator="\n", extrasaction="ignore")
            writer.writeheader()
            writer.writerows(data)
    (out / "worklist_summary.json").write_text(json.dumps(result, indent=1), encoding="utf-8")
    if publish is not None:
        write_published(publish, work, census, summary.get("proven_scalar_data_dwords", 0))
    return result, work, group_rows


def write_published(path, work, census, scalars):
    """The tracked worklist every host serves from: the rows whose fix alone
    closes at least one authored file, in rank order, minimal columns."""
    import csv
    closing = [row for row in work if row["unlock_authored_bytes"] > 0]
    rows = [row for row in closing if row["command"]]  # "": its fix would edit a generated source
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        handle.write(f"# linking worklist, census {census['commit']} ({census['date']}), image_check with {scalars:,} "
                     "proven-scalar data words; rows: blockers whose fix alone closes >= 1 authored file (the full "
                     f"list: build/image_compose/worklist.csv), less {len(closing) - len(rows)} whose fix would edit "
                     "game/gen_asm or game/gen_small. Serve: python3 tools/image_compose.py next\n")
        handle.write(f"# {SINGLE_FIX}\n")
        writer = csv.DictWriter(handle, PUBLISHED_FIELDS, lineterminator="\n", extrasaction="ignore")
        writer.writeheader()
        for rank, row in enumerate(rows, 1):
            more = len(row["_files"]) - 1
            writer.writerow({**row, "rank": rank, "reason": row["reason"][:60],
                             "files": row["_files"][0] + (f"; +{more} more" if more > 0 else "")})
    return len(rows)


def read_worklist(path):
    import csv
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(line for line in handle if not line.startswith("#")))


def print_worklist(result, work, groups, limit):
    print(f"image_compose worklist ({result['census']['commit']}): {result['blockers']:,} blockers close a file or a "
          f"function alone, {result['groups']:,} fix sites; {result['files_closed']:,} of {result['files']:,} files "
          f"already closed ({result['files_closed_authored_bytes']:,} authored bytes)")
    print(f"  {SINGLE_FIX}")
    print(f"  {'rank':>4} {'files':>5} {'authored':>9} {'fn bytes':>9}  {'family':<10} blocker")
    for row in work[:limit]:
        print(f"  {row['rank']:>4} {row['unlock_files']:>5} {row['unlock_authored_bytes']:>9,} "
              f"{row['unlock_function_bytes']:>9,}  {row['family']:<10} {row['blocker'][:90]}")
    print(f"  {'family':<10} {'blocks':>6} {'blockers':>8} {'single-fix files/bytes':>24} "
          f"{'whole-family files/bytes':>26}")
    for name, total in result["families"].items():
        print(f"  {name:<10} {total['files_blocked']:>6,} {total['blockers']:>8,} {total['single_fix_files']:>9,} / "
              f"{total['single_fix_authored_bytes']:>12,} {total['whole_family_files']:>11,} / "
              f"{total['whole_family_authored_bytes']:>12,}")
    print("  top fix sites (every blocker of the site fixed):")
    for row in groups[:min(limit, 10)]:
        print(f"    {row['unlock_files']:>4} files {row['unlock_authored_bytes']:>9,} B  {row['families']:<12} "
              f"{row['fix_site'][:100]}")
    recon = result["reconciliation"]
    print(f"  source closure {recon['source_closure_bytes']:,} = authored {recon['closed_strict_authored']:,} + "
          f"vendored-only {recon['closed_strict_vendored_only']:,}; census linked_authored "
          f"{recon['census_linked_authored']:,}; both {recon['both']:,}")
    for label, key in (("closed strict, not census", "closed_strict_authored_not_census"),
                       ("census, not closed strict", "census_not_closed_strict")):
        parts = list(recon[key].items())
        print(f"    {label} {sum(recon[key].values()):,}: " + "; ".join(f"{why} {count:,}" for why, count in parts[:4])
              + (f"; {len(parts) - 4} more in worklist_summary.json" if len(parts) > 4 else ""))


NOT_RECHECKED = ("not re-checked (needs a relink and image_check): whether the fix made the blocker retail-true "
                 "and movable, blockers a fix adds, and callers, selection or files changed elsewhere since the census")


class Freshness:
    """Is a worklist row still open on this tree? A cheap, honest subset:
    the row is skipped when, since its census commit, its fix site's source
    changed, a functions.csv / symbols.csv / data_rows.csv line naming its
    address or its name was added or removed, or this checkout holds a PASS
    provider_repair receipt whose inputs match this tree. NOT_RECHECKED says
    the rest."""
    LEDGERS = ("targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv",
               "targets/game/reverse/data_rows.csv")

    def __init__(self, census, root=ROOT):
        import subprocess

        def git(*args):
            done = subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, encoding="utf-8",
                                  errors="replace")
            if done.returncode:
                raise SystemExit(f"image_compose: git {' '.join(args[:2])} failed; is census {census} fetched? "
                                 f"(git fetch origin) {done.stderr.strip()}")
            return done.stdout
        git("cat-file", "-e", f"{census}^{{commit}}")
        self.root = root
        self.changed = set(git("diff", "--name-only", census, "--", "game", "inputs/reference").splitlines())
        self.lines = [line[1:] for line in git("diff", "--no-color", "-U0", census, "--", *self.LEDGERS).splitlines()
                      if line[:1] in "+-" and not line.startswith(("+++", "---"))]

    def stale(self, row):
        site = row.get("fix_site", "")
        if site.startswith("source:") and site[len("source:"):] in self.changed:
            return "its source changed since the census"
        rva = row.get("claim_rva", "")
        if rva and any(rva.casefold() in line.casefold() for line in self.lines):
            return "a ledger line at its address changed since the census"
        name = row.get("blocker", "")
        if name and any(line.startswith((name + ",", f'"{name}"')) for line in self.lines):
            return "a row, pin or data row naming it changed since the census"
        import provider_repair
        receipt = self.root / "build" / "provider_repair" / f"0x{int(rva, 16):08X}" / "receipt.json" if rva else None
        if receipt is not None and provider_repair.receipt_valid(receipt, self.root):
            return "a PASS provider_repair receipt matches this tree"
        return None


def cmd_next(args):
    """Serve and claim the best unclaimed blocker that is still open, with its evidence."""
    import claims
    import eligibility
    rows = read_worklist(args.worklist)
    census = {row["census"] for row in rows}
    if len(census) != 1:
        raise SystemExit(f"image_compose: {args.worklist} names {len(census)} census commits; regenerate it")
    census = census.pop()
    fresh = Freshness(census)
    history = (ROOT / "targets/game/reverse/link_census_history.csv").read_text(encoding="utf-8").splitlines()
    last = history[-1].split(",")[1] if len(history) > 1 else census
    if last != census:
        print(f"image_compose next: the worklist is from census {census}; the last census is {last} "
              "(the daily census no longer regenerates it: `link_check.py next` serves the linking queue; "
              "run the worklist command for a fresh local list)", file=sys.stderr)
    busy = set() if args.no_claim else {int(t, 16) for t in eligibility.busy_rvas() if t.startswith("0x")}
    latest = eligibility.latest_verdicts()
    skipped = collections.Counter()
    for row in rows:
        if args.family and row["family"] != args.family:
            continue
        if not int(row["unlock_authored_bytes"]) and not int(row["unlock_function_bytes"]):
            continue
        if not row["command"]:
            skipped["its fix would edit a generated source"] += 1
            continue
        if not row["claim_rva"]:
            skipped["no address to claim"] += 1
            continue
        rva = int(row["claim_rva"], 16)
        if rva in busy:
            skipped["claimed"] += 1
            continue
        if eligibility.retired(rva, latest):
            skipped["dead-end verdict"] += 1
            continue
        why = fresh.stale(row)
        if why:
            skipped[why] += 1
            continue
        if not args.no_claim:
            try:
                got = claims.claim([rva], note=f"image_compose worklist {row['family']}")
            except claims.ClaimsUnavailable as exc:
                print(f"image_compose: {exc}", file=sys.stderr)
                return 2
            if not got.claimed:
                skipped["claim refused"] += 1
                continue
        print(f"image_compose next: rank {row['rank']} {row['family']} "
              f"{'claimed' if not args.no_claim else 'NOT claimed (--no-claim)'} {row['claim_rva']} "
              f"(census {census})")
        for key in ("blocker", "rule", "object", "source", "home", "verdict", "reason", "fix_site"):
            if row.get(key):
                print(f"  {key:<9} {row[key]}")
        print(f"  unlocks   {row['unlock_files']} files, {int(row['unlock_authored_bytes']):,} authored bytes; "
              f"{int(row['unlock_function_bytes']):,} bytes of functions closed")
        print(f"  files     {row['files']}")
        if row.get("example"):
            print(f"  path      {row['example']}")
        print(f"  command   {row['command']}")
        print(f"  model     {SINGLE_FIX}")
        print(f"  open      {NOT_RECHECKED}")
        if skipped:
            print("  skipped   " + ", ".join(f"{w} {n}" for w, n in sorted(skipped.items())))
        return 0
    print("image_compose next: nothing to serve" + (": " if skipped else "") +
          ", ".join(f"{why} {count}" for why, count in sorted(skipped.items())))
    return 1


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
    w = sub.add_parser("worklist", help="rank blockers by the authored files each alone would source-close")
    w.add_argument("--image-check", type=Path, default=ROOT / "build" / "image_check",
                   help="an image_check output directory (graph.pkl, items.csv, summary.json)")
    w.add_argument("--tree", type=Path, required=True, help="checkout of that run's census commit")
    w.add_argument("--status", type=Path, help="that census's link_status.csv (default: from origin/master)")
    w.add_argument("--out", type=Path, default=OUT)
    w.add_argument("--limit", type=int, default=15)
    w.add_argument("--publish", type=Path, help="also write the tracked worklist (targets/game/reverse/"
                                                "linking_worklist.csv)")
    n = sub.add_parser("next", help="claim the best unclaimed worklist blocker and print its evidence")
    n.add_argument("--worklist", type=Path, default=PUBLISHED,
                   help="default: the tracked targets/game/reverse/linking_worklist.csv; "
                        "build/image_compose/worklist.csv for the full local list")
    n.add_argument("--family", choices=FAMILIES)
    n.add_argument("--no-claim", action="store_true", help="show it without claiming (and without skipping claims)")
    args = ap.parse_args(argv)
    if args.command == "worklist":
        result, work, groups = worklist(args.image_check.resolve(), args.tree.resolve(), args.status, args.out,
                                        args.publish)
        print_worklist(result, work, groups, args.limit)
        return 0
    if args.command == "next":
        return cmd_next(args)
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
