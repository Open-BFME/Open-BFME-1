#!/usr/bin/env python3
"""Derive anonymous function candidates from unclaimed retail ``.text``.

The matched ledger proves ranges, not the bytes between those ranges.  This
tool turns only positive boundary evidence into temporary anonymous rows:
direct REL32 call/jump targets prove starts, Ghidra entries are advisory starts
(never ends: its sizes stop short of the epilogue), and a decoded ``ret``/tail
``jmp`` followed by an MSVC ``int3`` run proves an end.  The output is deterministic and shrink-on-land: rows covered by the
current ledger are never emitted.

``python3 tools/carve_unclaimed.py --summary`` writes ``reverse/carved.csv``
and prints the candidate counts and bytes by size band.
"""
from __future__ import annotations

import argparse
import bisect
import collections
import csv
import sys
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
GHIDRA = ROOT / "reverse" / "ghidra_functions.csv"
OUTPUT = ROOT / "reverse" / "carved.csv"
TEXT_START = 0x1000
TEXT_SIZE = 0xC72000
MIN_PAD_RUN = 3

HEADER = ["rva", "size", "start_evidence", "callers", "end_evidence", "ghidra"]


def _rva(value: str) -> int | None:
    try:
        return int(value, 16) if value and value.lower().startswith("0x") else None
    except ValueError:
        return None


def load_ledger(path=FUNCTIONS):
    """Return valid ledger intervals, preserving the source of truth locally."""
    rows = []
    with Path(path).open(newline="", encoding="utf-8", errors="replace") as fh:
        for row in csv.DictReader(fh):
            start = _rva(row.get("target_rva", ""))
            try:
                size = int(row.get("target_size") or 0)
            except ValueError:
                continue
            if start is not None and size > 0:
                rows.append((start, start + size))
    return rows


def merge_ranges(intervals, lo=TEXT_START, hi=TEXT_START + TEXT_SIZE):
    """Merge ledger ranges and clip them to the retail text section."""
    ordered = sorted((max(lo, s), min(hi, e)) for s, e in intervals
                     if e > lo and s < hi)
    merged = []
    for start, end in ordered:
        if end <= start:
            continue
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], end))
        else:
            merged.append((start, end))
    return merged


def uncovered_ranges(merged, lo=TEXT_START, hi=TEXT_START + TEXT_SIZE):
    """Ranges not covered by any ledger interval."""
    out, cursor = [], lo
    for start, end in merged:
        if start > cursor:
            out.append((cursor, start))
        cursor = max(cursor, end)
    if cursor < hi:
        out.append((cursor, hi))
    return out


def _padding_runs(data, start, end):
    """Yield ``(run_start, run_end)`` for runs of three or more 0xCC bytes."""
    i = start
    while i < end:
        if data[i] != 0xCC:
            i += 1
            continue
        j = i + 1
        while j < end and data[j] == 0xCC:
            j += 1
        if j - i >= MIN_PAD_RUN:
            yield i, j
        i = j


def real_runs(data, start, end):
    """Split a gap at positive int3 padding runs, returning non-padding spans."""
    out, cursor = [], start
    for pad_start, pad_end in _padding_runs(data, start, end):
        if pad_start > cursor:
            out.append((cursor, pad_start))
        cursor = pad_end
    if cursor < end:
        out.append((cursor, end))
    return out


def _decode_map(data, file_lo, file_hi, address_lo=None):
    """Decode one linear text pass and index instructions by their RVA."""
    address_lo = file_lo if address_lo is None else address_lo
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return {ins.address: ins for ins in
            md.disasm(data[file_lo:file_hi], address_lo)}


def _direct_rel_targets(data, text_lo, text_hi, address_lo=None):
    """Map direct REL32 call/jump targets to their call-site RVAs.

    Capstone's sequential decode is deliberately used instead of matching raw
    E8/E9 bytes in data or immediates.  A target is still only advisory until
    the boundary validator accepts the resulting candidate.
    """
    calls = collections.defaultdict(list)
    for ins in _decode_map(data, text_lo, text_hi, address_lo).values():
        if ins.mnemonic not in ("call", "jmp") or not ins.operands:
            continue
        op = ins.operands[0]
        if op.type != capstone.x86.X86_OP_IMM:
            continue
        target = int(op.imm)
        if text_lo <= target < text_hi:
            calls[target].append(ins.address)
    return calls


def load_ghidra(path=GHIDRA):
    sizes, names = {}, {}
    path = Path(path)
    if not path.exists():
        return sizes, names
    with path.open(newline="", encoding="utf-8", errors="replace") as fh:
        for row in csv.DictReader(fh):
            start = _rva(row.get("rva", ""))
            try:
                size = int(row.get("size") or 0)
            except ValueError:
                continue
            if start is not None and size > 0:
                sizes[start] = size
                names[start] = row.get("name", "")
    return sizes, names


def _gap_for(rva, gaps, gap_starts=None):
    gap_starts = gap_starts if gap_starts is not None else [s for s, _ in gaps]
    i = bisect.bisect_right(gap_starts, rva) - 1
    if i >= 0 and rva < gaps[i][1]:
        return gaps[i]
    return None


def _terminal_end(data, rva, limit, instructions=None):
    """Return ``(end, evidence)`` for a positive decoded function tail."""
    if limit <= rva:
        return None
    if instructions is not None and rva in instructions:
        decoded = []
        ins = instructions[rva]
        while ins.address < limit:
            decoded.append(ins)
            nxt = ins.address + ins.size
            if nxt >= limit:
                break
            ins = instructions.get(nxt)
            if ins is None:
                break
    else:
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
        body = data[rva:limit]
        decoded = list(md.disasm(body, rva))
    if not decoded:
        return None
    # Only a terminal instruction immediately before padding/end is evidence.
    for ins in reversed(decoded):
        if ins.mnemonic not in ("ret", "retf", "jmp"):
            continue
        end = ins.address + ins.size
        if end > limit:
            continue
        if end == limit:
            return end, f"{ins.mnemonic}-tail"
        # The caller passes a real run ending at the next int3 run.  The
        # instruction is therefore a terminal immediately before padding.
        if all(b == 0xCC for b in data[end:min(limit, end + MIN_PAD_RUN)]):
            return end, f"{ins.mnemonic}+int3"
    return None


def _end_for(data, start, gap_end, next_start, ghidra_size, instructions=None):
    """Find a candidate end without crossing another positive start."""
    hard_end = min(gap_end, next_start or gap_end)
    # The first positive pad run is itself an end fence.  Decode only the
    # non-padding portion before it; the terminal instruction must be positive.
    pad = next(iter(_padding_runs(data, start, hard_end)), None)
    decode_end = pad[0] if pad else hard_end
    result = _terminal_end(data, start, decode_end, instructions)
    if result and pad and result[0] == pad[0] and result[1].endswith("-tail"):
        return result[0], result[1].replace("-tail", "+int3")
    # Ghidra's size is advisory for ENDS as much as for starts: the first eight
    # served ghidra-size candidates all ended 3-13 bytes before the real ret
    # (refuted as no-boundary on 2026-09-16, 0x003A2700 .. 0x0068C400). A
    # candidate without a decoded terminal has no positive end and is not served.
    del ghidra_size
    return result


def _conditional_escapes(data, start, end):
    """Reject a tail fence if an earlier conditional enters the next range.

    An EH cleanup funclet can already be claimed in the ledger even though a
    branch in its parent reaches the epilogue after it.  The parent's last
    instruction before that claim may be a backward ``jmp``; treating it as a
    complete jmp-tail body would serve a truncated candidate.  A conditional
    target outside the proposed body proves that it is not self-contained.
    """
    # A whole-image linear pass can decode the bytes before a function start
    # under another alignment.  Decode from this candidate's proven start.
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    for ins in md.disasm(data[start:end], start):
        if ins.mnemonic == "jmp" or not ins.group(capstone.CS_GRP_JUMP):
            continue
        if ins.operands and ins.operands[0].type == capstone.x86.X86_OP_IMM:
            target = int(ins.operands[0].imm)
            if not start <= target < end:
                return True
    return False


def split_candidates(data, gaps, ghidra_sizes=None, ghidra_names=None,
                     calls=None, validator=None, instructions=None):
    """Split uncovered gaps into validated candidate dictionaries.

    The function is intentionally independent of the retail image loader so
    tests can provide a small synthetic byte image and a small validator.
    ``data`` is indexed by RVA (callers may pad a synthetic image accordingly).
    """
    ghidra_sizes = ghidra_sizes or {}
    ghidra_names = ghidra_names or {}
    calls = calls or {}
    if validator is None:
        from boundary_validator import BoundaryValidator
        validator = BoundaryValidator(lambda r, n: data[r:r + n], ghidra_sizes)
    gap_starts = [s for s, _ in gaps]
    starts = {}
    for target, sites in calls.items():
        gap = _gap_for(target, gaps, gap_starts)
        if gap and data[target] != 0xCC:
            starts.setdefault(target, {"callers": list(sites), "call": True})
    for target, size in ghidra_sizes.items():
        gap = _gap_for(target, gaps, gap_starts)
        if gap and data[target] != 0xCC:
            entry = starts.setdefault(target, {"callers": [], "call": False})
            entry["ghidra"] = size
    ordered = sorted(starts)
    out = []
    occupied = []
    for index, start in enumerate(ordered):
        gap = _gap_for(start, gaps, gap_starts)
        if gap is None:
            continue
        next_start = ordered[index + 1] if index + 1 < len(ordered) else None
        if next_start is not None and next_start >= gap[1]:
            next_start = None
        start_ok, _ = validator.check_start(start)
        if start_ok is False:
            continue
        end_info = _end_for(data, start, gap[1], next_start,
                     starts[start].get("ghidra"), instructions)
        if not end_info:
            continue
        end, end_evidence = end_info
        size = end - start
        if size <= 0 or end > gap[1]:
            continue
        if _conditional_escapes(data, start, end):
            continue
        if validator.check_end(start, size) is not None:
            continue
        # Explicit overlap rejection keeps a candidate from consuming the next
        # positive start even when the injected validator has no inventory for it.
        if any(start < old_end and old_start < end for old_start, old_end in occupied):
            continue
        occupied.append((start, end))
        evidence = []
        if starts[start].get("call"):
            evidence.append("rel32-call/jmp")
        if start in ghidra_sizes:
            evidence.append("ghidra-start")
        out.append({
            "name": f"?d_{start:08x}@@YAXXZ",
            "target_rva": f"0x{start:08X}",
            "target_size": str(size),
            "start_evidence": ";".join(evidence),
            "callers": str(len(starts[start].get("callers", []))),
            "end_evidence": end_evidence,
            "ghidra": ghidra_names.get(start, ""),
        })
    return sorted(out, key=lambda row: int(row["target_rva"], 16))


def carve(image=None, ledger=FUNCTIONS, ghidra=GHIDRA):
    """Return carved rows and a summary dictionary from the current checkout."""
    if image is None:
        import build
        image = build.EXE.read_bytes()
    import build
    sections = build.pe_sections(image)
    text = next(section for section in sections if section["name"] == ".text")
    text_lo, text_hi = text["rva"], text["rva"] + text["size"]
    merged = merge_ranges(load_ledger(ledger), text_lo, text_hi)
    gaps = uncovered_ranges(merged, text_lo, text_hi)
    sizes, names = load_ghidra(ghidra)
    file_lo = text["raw_pointer"]
    file_hi = file_lo + text["size"]
    calls = _direct_rel_targets(image, file_lo, file_hi, text["rva"])
    instructions = _decode_map(image, file_lo, file_hi, text["rva"])
    from boundary_validator import BoundaryValidator
    read = lambda r, n: image[build.rva_to_file_offset(sections, r):
                               build.rva_to_file_offset(sections, r) + n]
    validator = BoundaryValidator(read, sizes)
    # split_candidates expects RVA-indexable bytes; normalize the PE image into
    # a bytearray indexed by RVA for the bounded .text slice.
    rva_data = bytearray(text_hi)
    rva_data[text_lo:text_hi] = image[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    rows = split_candidates(rva_data, gaps, sizes, names, calls, validator,
                            instructions)
    bands = collections.OrderedDict((label, [0, 0]) for label in
                                     ("32-299", "300-999", "1000-2499", "2500+"))
    for row in rows:
        size = int(row["target_size"])
        label = "32-299" if size < 300 else "300-999" if size < 1000 else "1000-2499" if size < 2500 else "2500+"
        bands[label][0] += 1
        bands[label][1] += size
    return rows, bands, {"gaps": gaps, "merged": merged, "calls": calls}


def write_rows(rows, path=OUTPUT):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as fh:
        writer = csv.DictWriter(fh, fieldnames=HEADER, lineterminator="\n")
        writer.writeheader()
        for row in rows:
            writer.writerow({
                "rva": row["target_rva"],
                "size": row["target_size"],
                "start_evidence": row["start_evidence"],
                "callers": row["callers"],
                "end_evidence": row["end_evidence"],
                "ghidra": row["ghidra"],
            })


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--summary", action="store_true", help="print counts and bytes by size band")
    ap.add_argument("--output", type=Path, default=OUTPUT)
    args = ap.parse_args(argv)
    rows, bands, meta = carve()
    write_rows(rows, args.output)
    print(f"carved: {len(rows):,} candidates, {sum(int(r['target_size']) for r in rows):,} bytes")
    print(f"uncovered gaps: {len(meta['gaps']):,}")
    print("band          candidates       bytes")
    for label, (count, total) in bands.items():
        print(f"{label:>10} {count:>12,} {total:>12,}")
    if not args.summary:
        output_path = args.output.resolve()
        try:
            display_path = output_path.relative_to(ROOT)
        except ValueError:
            display_path = output_path
        print(f"wrote {display_path.as_posix()}")


if __name__ == "__main__":
    main()
