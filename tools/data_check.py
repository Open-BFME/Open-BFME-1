#!/usr/bin/env python3
"""Prove one source file's initialized data against the retail executable.

The function byte gate masks relocation fields and does not validate global
initializers.  This checker uses the same current object and retail placement
machinery as component_link, but is deliberately strict: an unplaced section
or an unresolved relocation is UNVERIFIED, never a match.

  py -3 tools/data_check.py game/path/to/source.cpp

Exit 0 means every initialized non-code section in the object was placed and
matched, including its relocation targets.  Exit 1 means retail contradicts
the object.  Exit 2 means the available anchors were insufficient to prove it.
"""
import argparse
import csv
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import component_link  # noqa: E402

CODE = 0x00000020
SUPPORTED = (component_link.DIR32, component_link.DIR32NB, component_link.REL32)


def _target_candidates(placement, obj, target):
    """Return (known RVAs, reason).  An empty set is explicitly unproved."""
    if target["section"] > 0:
        key = (obj, target["section"])
        base = placement.base.get(key)
        return ({base + target["value"]} if base is not None else set(), "local section is unplaced")
    if target["section"] == -1:  # COFF absolute symbol
        # The COFF value is an absolute VA.  Internally candidates are RVAs;
        # _encoded adds ImageBase only for DIR32, exactly as link.exe does.
        return {(target["value"] - component_link.BASE) & 0xFFFFFFFF}, ""
    if target["storage"] == component_link.EXTERNAL and target["name"] in placement.defined:
        owner, section, value = placement.defined[target["name"]]
        base = placement.base.get((owner, section))
        return ({base + value} if base is not None else set(), "defining section is unplaced")
    if target["name"].startswith("__imp_"):
        bare = target["name"][len("__imp_"):]
        slots = placement.slots.get(component_link.link_census._undecorate(bare)) \
            or placement.slots.get(bare) or set()
        return set(slots), "retail import slot is unknown"
    candidates = set(placement.anchors.get(target["name"], set()))
    for row in getattr(placement, "ledger_rows", {}).get(target["name"], []):
        value = row.get("target_rva") or ""
        if value.startswith("0x"):
            candidates.add(int(value, 16))
    return candidates, "target has no retail anchor"


def _encoded(kind, target_rva, addend, source_rva, where):
    if kind == component_link.DIR32:
        return (component_link.BASE + target_rva + addend) & 0xFFFFFFFF
    if kind == component_link.DIR32NB:
        return (target_rva + addend) & 0xFFFFFFFF
    return (target_rva + addend - (source_rva + where + 4)) & 0xFFFFFFFF


def _actual_target(kind, value, addend, source_rva, where):
    if kind == component_link.DIR32:
        return (value - addend - component_link.BASE) & 0xFFFFFFFF
    if kind == component_link.DIR32NB:
        return (value - addend) & 0xFFFFFFFF
    return (source_rva + where + 4 + value - addend) & 0xFFFFFFFF


def _packed_stub(placement, rva):
    """Follow only an E9 in retail's packed incremental-link table."""
    def in_text(address):
        return any(section["name"] == ".text"
                   and section["rva"] <= address < section["rva"] + section["size"]
                   for section in getattr(placement, "pe", []))

    if not in_text(rva):
        return None
    around = placement.read(rva - 5, 15)
    if around is None or around[5] != 0xE9 or (around[0] != 0xE9 and around[10] != 0xE9):
        return None
    destination = (rva + 5 + struct.unpack_from("<i", around, 6)[0]) & 0xFFFFFFFF
    return destination if in_text(destination) else None


def audit(placement):
    """Return (verified, contradictions, unknowns) for Placement's data."""
    verified, contradictions, unknowns = [], [], []
    for obj, (sections, symbols) in placement.objs.items():
        for section in sections:
            if section["size"] == 0 or section["flags"] & component_link.SKIP_FLAGS \
                    or section["flags"] & CODE or section["name"].startswith(".text"):
                continue
            label = component_link.section_label(sections, symbols, section["number"])
            subject = f"{obj}:{label} {section['name']} ({section['size']} bytes)"
            key = (obj, section["number"])
            source_rva = placement.base.get(key)
            if section["body"] is None:
                unknowns.append(f"{subject}: uninitialized/BSS has no object bytes to compare")
                continue
            if source_rva is None:
                unknowns.append(f"{subject}: section is unplaced")
                continue
            retail = placement.read(source_rva, section["size"])
            if retail is None:
                contradictions.append(f"{subject}: retail has no raw bytes at RVA 0x{source_rva:08X}")
                continue
            malformed = [(where, kind) for where, _, kind in section["relocs"]
                         if where < 0 or where + (2 if kind == 0x000A else 4) > section["size"]]
            if malformed:
                where, kind = malformed[0]
                contradictions.append(
                    f"{subject}: malformed relocation type 0x{kind:04X} at +0x{where:X}")
                continue
            diff = placement.masked_diff(section, retail)
            if diff:
                contradictions.append(f"{subject}: initializer differs in {len(diff)} byte(s), first +0x{diff[0]:X}")
                continue

            fixup_unknown = False
            fixup_bad = False
            for where, index, kind in section["relocs"]:
                target = symbols.get(index)
                target_name = target["name"] if target else f"symbol-index-{index}"
                site = f"{subject}+0x{where:X} -> {target_name}"
                if target is None or kind not in SUPPORTED or where + 4 > section["size"]:
                    unknowns.append(f"{site}: unsupported or malformed relocation type 0x{kind:04X}")
                    fixup_unknown = True
                    continue
                candidates, reason = _target_candidates(placement, obj, target)
                if not candidates:
                    unknowns.append(f"{site}: {reason}")
                    fixup_unknown = True
                    continue
                addend = struct.unpack_from("<i", section["body"], where)[0]
                actual = struct.unpack_from("<I", retail, where)[0]
                expected = {_encoded(kind, rva, addend, source_rva, where) for rva in candidates}
                actual_target = _actual_target(kind, actual, addend, source_rva, where)
                if actual not in expected and _packed_stub(placement, actual_target) not in candidates:
                    contradictions.append(
                        f"{site}: retail 0x{actual:08X}, expected one of "
                        + ", ".join(f"0x{x:08X}" for x in sorted(expected)))
                    fixup_bad = True
            if not fixup_bad and not fixup_unknown:
                verified.append(f"{subject}: RVA 0x{source_rva:08X} matches")
    contradictions.extend(f"placement conflict: {line}" for line in placement.conflicts)
    return verified, contradictions, unknowns


def rows_for_source(source):
    rows = []
    with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row.get("status") == "matched" and row.get("source") == source \
                    and (row.get("target_rva") or "").startswith("0x"):
                rows.append(row)
    return rows


def add_relocation_rows(placement):
    """Load ledger routes only for external names used by this object's data."""
    wanted = set()
    for sections, symbols in placement.objs.values():
        for section in sections:
            if section["flags"] & CODE or section["name"].startswith(".text"):
                continue
            for _, index, _ in section["relocs"]:
                symbol = symbols.get(index)
                if symbol and symbol["storage"] == component_link.EXTERNAL:
                    wanted.add(symbol["name"])
    if not wanted:
        return
    with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row.get("name") in wanted and (row.get("target_rva") or "").startswith("0x"):
                placement.ledger_rows[row["name"]].append(row)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("source", help="repository-relative C/C++ source path")
    args = parser.parse_args(argv)
    try:
        source = (ROOT / args.source).resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        parser.error("source must be inside the repository")
    rows = rows_for_source(source)
    if not rows:
        print(f"UNVERIFIED {source}: no matched ledger rows anchor this source")
        return 2
    objects, stale = component_link.ensure_objects(rows)
    if stale:
        for name in stale:
            print(f"FAIL {name}: object remained stale after compilation")
        return 1
    placement = component_link.Placement(objects, rows)
    add_relocation_rows(placement)
    placement.run()
    verified, contradictions, unknowns = audit(placement)
    for line in verified:
        print("PASS", line)
    for line in contradictions:
        print("FAIL", line)
    for line in unknowns:
        print("UNVERIFIED", line)
    print(f"data check: {len(verified)} verified, {len(contradictions)} contradicted, {len(unknowns)} unverified")
    return 1 if contradictions else 2 if unknowns else 0


if __name__ == "__main__":
    raise SystemExit(main())
