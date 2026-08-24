#!/usr/bin/env python3
"""Choose one naked asm function to decompile to clean C++.

The default picks uniformly at random from the whole candidate queue. Use
``--ranked`` to inspect the full ranking.
"""
import argparse
from collections import defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import secrets
import struct
import sys

import build
import re_log
import yield_model

_spec = importlib.util.spec_from_file_location(
    "audit_ret_arity", str(Path(__file__).resolve().parent / "audit_ret_arity.py"))
audit_ret_arity = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(audit_ret_arity)


NAKED_RE = re.compile(r"__declspec\s*\(\s*naked\s*\)")
EMIT_RE = re.compile(r"__emit\s+0x([0-9a-fA-F]{1,2})")
RE_ATTEMPTS = build.ROOT / "reverse" / "re_attempts.log"


def logged_no_match(paths):
    """Return decorated names retired by the shared or worker-local logs."""
    symbols = set()
    for path in paths:
        if not path.exists():
            continue
        with path.open(encoding="utf-8", errors="replace") as stream:
            for line in stream:
                fields = line.rstrip("\r\n").split("\t")
                if len(fields) >= 2 and fields[1] == "no-match":
                    symbols.add(fields[0])
    return symbols


def actual_ret(data):
    """Bytes the transcribed body pops, or None for a tail call / no return."""
    if data and data[-1] == 0xC3:
        return 0
    if len(data) >= 3 and data[-3] == 0xC2:
        return struct.unpack_from("<H", data, len(data) - 3 + 1)[0]
    return None


def arity_contradicts(symbol, data):
    """True when the decorated name cannot possibly produce this body.

    A name says how many bytes a callee-cleaned function must pop and the
    transcribed bytes say how many it does pop. When they disagree the row's
    name is on the wrong body, so no amount of writing the C++ correctly will
    ever make it compile to these bytes -- offering it as a conversion
    candidate only burns an afternoon. audit_ret_arity.py already reports these
    repo-wide; this keeps them out of the queue that hands out work.
    """
    if not symbol:
        return False
    # A name that stops at the class terminator carries no signature at all --
    # ?beginBlock@XferSave@@ is a row title, not something the compiler can emit.
    # There is nothing to write C++ against, so it is unconvertible for the same
    # practical reason as an arity clash even though the arity check has no
    # opinion on it.
    if symbol.startswith("?") and symbol.endswith("@@"):
        return True
    want, _convention = audit_ret_arity.expected_ret(symbol)
    if want is None:                      # varargs, drifted parse: no opinion
        return False
    got = actual_ret(data)
    if got is None:                       # tail call: nothing to compare
        return False
    return got != want


def collect_rows():
    rows = {}
    by_name = {}
    for row in build.load_all_function_rows():
        rows.setdefault(row["source"], []).append(row)
        by_name.setdefault(row["name"], []).append(row)
    return rows, by_name


def matched_body_index(rows_by_source, max_bytes):
    """Exact binary bytes of every matched row -> row. A naked body that
    byte-verifies is a literal copy of the binary, so an already-matched
    function is recognizable by its bytes even when the symbol comment is
    missing or the source mangles the name differently than the ledger."""
    exe = build.EXE.read_bytes()
    sections = build.pe_sections(exe)
    index = {}
    for rows in rows_by_source.values():
        for row in rows:
            if row["status"] != "matched":
                continue
            size = int(row["target_size"])
            if not 0 < size <= max_bytes:
                continue
            offset = build.rva_to_file_offset(sections, int(row["target_rva"], 16))
            index.setdefault(exe[offset : offset + size], row)
    return index


def symbol_comment(lines, index):
    for cursor in range(index - 1, max(-1, index - 5), -1):
        text = lines[cursor].strip()
        if not text:
            continue
        if text.startswith("// "):
            return text[3:].strip()
        break
    return None


def signature(lines, index):
    parts = []
    for cursor in range(index, max(-1, index - 4), -1):
        text = lines[cursor].strip()
        if text:
            parts.insert(0, text)
        if ")" in text and ("(" in text or parts):
            break
    sig = " ".join(parts)
    return " ".join(sig.split())


def block_bytes(lines, start):
    depth = 0
    seen_open = False
    data = []
    end = start
    for index in range(start, len(lines)):
        line = lines[index]
        if "{" in line:
            depth += line.count("{")
            seen_open = True
        if "__emit" in line:
            for match in EMIT_RE.finditer(line):
                data.append(int(match.group(1), 16))
        if "}" in line:
            depth -= line.count("}")
            if seen_open and depth <= 0:
                end = index
                break
    return bytes(data), end


DB_RE = re.compile(r"^\s*db\s+(.*)$")
PROC_RE = re.compile(r"^(\S+)\s+PROC\b")


def asm_proc_blocks(lines):
    """(symbol, body bytes, start index, end index) per PROC in a MASM dump.

    Code/gen_asm/ holds the scaled dump pass: 4.5 MB of machine bodies in `db`
    rows, which no __declspec(naked) scan can see. Without this reader the
    convert lane goes empty the moment dumping replaces the .cpp wave form.
    """
    blocks = []
    start, symbol, data = None, None, []
    for index, line in enumerate(lines):
        match = PROC_RE.match(line)
        if match:
            start, symbol, data = index, match.group(1), []
            continue
        if start is None:
            continue
        if line.startswith(symbol) and " ENDP" in line:
            blocks.append((symbol, bytes(data), start, index))
            start = None
            continue
        db = DB_RE.match(line)
        if db:
            data.extend(int(token.strip().rstrip("hH"), 16)
                        for token in db.group(1).split(","))
    return blocks


def _has_x87(data):
    """True only if an x87 escape opcode starts an instruction.

    Testing whether any byte is in D8..DF finds the opcode wherever it lands --
    inside a call displacement, an immediate, a ModRM byte. Across the naked
    thunks that test flags 753 functions where only 150 contain x87, so six out
    of seven of its hits are wrong, and every one of them was being pushed down
    the ranking by the penalty below. Decode instead; fall back to the loose
    test only if capstone is unavailable, and say so by returning None.
    """
    try:
        import capstone
    except ImportError:
        return None
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return any(0xD8 <= ins.bytes[0] <= 0xDF for ins in md.disasm(data, 0))


def score_candidate(data, sig):
    score = 100
    reasons = []
    size = len(data)

    score -= size
    if size <= 16:
        reasons.append("tiny")
    elif size <= 64:
        reasons.append("small")

    calls = data.count(0xE8)
    if calls:
        score -= calls * 12
        reasons.append(f"{calls} call(s)")
    else:
        score += 12
        reasons.append("leaf")

    jumps = sum(data.count(op) for op in (0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x7C, 0x7D, 0x7E, 0x7F, 0xE9, 0xEB))
    if jumps:
        score -= jumps * 6
        reasons.append(f"{jumps} branch(es)")

    x87 = _has_x87(data)
    if x87 is None:
        if any(0xD8 <= b <= 0xDF for b in data):
            score -= 18
            reasons.append("x87? (no decoder)")
    elif x87:
        score -= 18
        reasons.append("x87")

    if b"\xff\x52" in data or b"\xff\x50" in data:
        score += 10
        reasons.append("virtual-call pattern")

    if data in (bytes.fromhex("8b c1 c3"), bytes.fromhex("c3")):
        score += 30
        reasons.append("trivial return")

    if "operator<<" in sig and "Debug" in sig:
        score += 20
        reasons.append("Debug stream")

    if "operator=" in sig:
        score += 10
        reasons.append("assignment")

    return score, reasons


def rank_candidates(candidates):
    candidates.sort(key=lambda item: (-item["score"], item["size"],
                                      item["path"], item["line"]))
    return candidates


def drop_logged(candidates):
    """Remove candidates whose BOUNDARY the fleet has already refuted.

    This tool had no such filter, which is why one dump could be drawn and
    re-analysed by independent agents over and over — ??0FastAllocatorGeneral
    was logged fourteen times and suppressed none of them.

    An agent's deferral is not a refutation: the dump still has to become C++,
    so those are kept and tagged `deferred_attempts` for select_candidate to
    order behind untried work. See tools/re_log.py."""
    kept, dropped = [], 0
    for item in candidates:
        rva = item.get("rva")
        try:
            rva = int(rva, 16) if rva else None
        except ValueError:
            rva = None
        if item["symbol"] and re_log.is_dead_end(item["symbol"], rva):
            dropped += 1
            continue
        if item["symbol"] and re_log.is_deferred(item["symbol"], rva):
            item["deferred_attempts"] = re_log.attempts(item["symbol"])
        kept.append(item)
    return kept, dropped


def candidate_weights(candidates):
    """Selection weight per candidate: see tools/yield_model.weight.

    Deliberately NOT weighted by this tool's own `score`. That score is an
    unvalidated convertibility heuristic, and the one feature of its kind that
    has been measured — drift `aligned_pct` — turned out not to predict landing
    at all. Weighting on an unmeasured feature concentrates the queue without
    buying anything. `score` still orders the ranked view for humans."""
    return [yield_model.weight(item["size"]) for item in candidates]


PACKET_DIR = build.ROOT / "reverse" / "zh_sweep" / "packets"


def packet_rvas():
    """Retail addresses tools/zh_sweep.py wrote a work packet for.

    A packet is Zero Hour's own source for that body, named and 85%+ aligned
    with the retail bytes. Converting from one is a different job from reading
    a nameless dump out of a disassembly, so the queue spends them first."""
    if not PACKET_DIR.is_dir():
        return {}
    out = {}
    for path in PACKET_DIR.glob("*.md"):
        try:
            out[int(path.stem, 16)] = path
        except ValueError:
            continue
    return out


def candidate_packet(item, packets):
    try:
        return packets.get(int(item["rva"], 16)) if item.get("rva") else None
    except ValueError:
        return None


def select_candidate(candidates):
    """Draw one candidate weighted by expected yield. Still random, so
    concurrent contributors rarely collide; no longer worth the pool average."""
    rank_candidates(candidates)
    if not candidates:
        return None, {"pool": 0}
    untried = [item for item in candidates if not item.get("deferred_attempts")]
    if untried:
        candidates = untried
    packets = packet_rvas()
    led = [item for item in candidates if candidate_packet(item, packets)]
    if led:
        candidates = led
    weights = candidate_weights(candidates)
    cutoff = secrets.randbelow(sum(weights))
    for item, weight in zip(candidates, weights):
        cutoff -= weight
        if cutoff < 0:
            return item, {"pool": len(candidates),
                          "packet": candidate_packet(item, packets)}
    raise AssertionError("select_candidate fell through its cumulative walk")


def parse_shard(value):
    try:
        index_text, count_text = value.split("/", 1)
        index, count = int(index_text), int(count_text)
    except (AttributeError, TypeError, ValueError):
        raise argparse.ArgumentTypeError("shard must be INDEX/COUNT, for example 0/6")
    if count <= 0 or index < 0 or index >= count:
        raise argparse.ArgumentTypeError(
            "shard requires COUNT > 0 and 0 <= INDEX < COUNT")
    return index, count


def apply_shard(candidates, shard):
    """Give concurrent workers stable, disjoint candidate pools."""
    if shard is None:
        return candidates
    index, count = shard
    kept = []
    for candidate in candidates:
        identity = candidate["symbol"] or (
            f"{candidate['path']}:{candidate['line']}:{candidate['signature']}")
        digest = hashlib.sha256(identity.encode("utf-8")).digest()
        if int.from_bytes(digest[:8], "big") % count == index:
            kept.append(candidate)
    return kept


def print_candidate(item):
    location = f"{item['path']}:{item['line']}"
    reasons = ", ".join(item["reasons"])
    print(f"  {item['score']:4d}  {item['size']:4d} bytes  {location}  {item['status']}")
    print(f"        {item['signature']}")
    if item["symbol"]:
        print(f"        symbol: {item['symbol']}")
    if item["tracked"]:
        print(f"        verify: ./build.sh '{item['symbol']}'")
    print(f"        {reasons}; file has {item['unmatched_count']} unmatched csv row(s)")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("paths", nargs="*", default=["Code"],
                        help="source files or directories to scan (default: Code)")
    parser.add_argument("--all", action="store_true", help="include untracked naked functions")
    parser.add_argument("--ranked", action="store_true",
                        help="show the complete ranking for humans/debugging")
    parser.add_argument("--groups", action="store_true",
                        help="with --ranked, group repeated naked byte patterns")
    parser.add_argument("--limit", type=int, default=30,
                        help="max items/groups with --ranked (default 30)")
    parser.add_argument("--max-bytes", type=int, default=512,
                        help="serve naked bodies up to this size (measured land "
                             "rates peak at 128-255B and gen_dump waves run to "
                             "511B; the old 160 default hid most of the fuel)")
    parser.add_argument("--shard", type=parse_shard, metavar="INDEX/COUNT",
                        help="stable zero-based partition for concurrent workers")
    parser.add_argument("--exclude-file", action="append", type=Path, default=[],
                        help="additional TSV no-match log (repeatable)")
    parser.add_argument("--include-logged", action="store_true",
                        help="include candidates retired by no-match evidence")
    parser.add_argument("--json", action="store_true",
                        help="emit the filtered candidate queue as machine-readable JSON")
    args = parser.parse_args()
    if args.groups and not args.ranked:
        parser.error("--groups requires --ranked")

    row_by_source, rows_by_name = collect_rows()
    body_index = matched_body_index(row_by_source, args.max_bytes)
    files = []
    for raw in args.paths:
        path = build.ROOT / raw
        if path.is_dir():
            files.extend(sorted(path.rglob("*.cpp")))
            files.extend(sorted((path / "gen_asm").rglob("*.asm"))
                         if (path / "gen_asm").is_dir()
                         else (sorted(path.rglob("*.asm"))
                               if path.name == "gen_asm" else []))
        elif path.exists():
            files.append(path)

    candidates = []
    already_matched = 0
    arity_conflicts = 0
    for path in files:
        rel = path.relative_to(build.ROOT).as_posix()
        text = path.read_text(encoding="utf-8", errors="replace")
        if path.suffix.lower() == ".asm":
            lines = text.splitlines()
            source_rows = row_by_source.get(rel, [])
            unmatched = sum(1 for row in source_rows if row["status"] != "matched")
            for symbol, data, start, end in asm_proc_blocks(lines):
                if not data or len(data) > args.max_bytes:
                    continue
                own = [row for row in rows_by_name.get(symbol, [])
                       if row["source"] == rel]
                if not own and not args.all:
                    continue
                score, reasons = score_candidate(data, "")
                candidates.append({
                    "score": score, "path": rel, "line": start + 1,
                    "end": end + 1, "size": len(data),
                    "rva": own[0]["target_rva"] if own else None,
                    "bytes": data, "symbol": symbol, "tracked": bool(own),
                    "status": own[0]["status"] if own else "untracked",
                    "signature": "", "reasons": reasons,
                    "unmatched_count": unmatched,
                })
            continue
        if "__declspec(naked)" not in text:
            continue
        lines = text.splitlines()
        source_rows = row_by_source.get(rel, [])
        unmatched_count = sum(1 for row in source_rows if row["status"] != "matched")
        for index, line in enumerate(lines):
            if not NAKED_RE.search(line):
                continue
            data, end = block_bytes(lines, index)
            if not data or len(data) > args.max_bytes:
                continue
            sig = signature(lines, index)
            symbol = symbol_comment(lines, index)
            symbol_rows = rows_by_name.get(symbol, []) if symbol else []
            own = [row for row in symbol_rows if row["source"] == rel]
            row = own[0] if own else None
            if row is None:
                # not this file's ledger row, but the function may already be
                # matched — by name under another source, or (when the symbol
                # comment is missing) by its exact bytes; listing it as
                # "untracked" lures agents into redoing done work
                if any(r["status"] == "matched" for r in symbol_rows) or data in body_index:
                    already_matched += 1
                    continue
            if not row and not args.all:
                continue
            if arity_contradicts(symbol, data):
                arity_conflicts += 1
                continue
            score, reasons = score_candidate(data, sig)
            candidates.append(
                {
                    "score": score,
                    "path": rel,
                    "line": index + 1,
                    "end": end + 1,
                    "size": len(data),
                    "rva": row["target_rva"] if row else None,
                    "bytes": data,
                    "symbol": symbol,
                    "tracked": row is not None,
                    "status": row["status"] if row else "untracked",
                    "signature": sig,
                    "reasons": reasons,
                    "unmatched_count": unmatched_count,
                }
            )

    retired = (set() if args.include_logged else
               logged_no_match([RE_ATTEMPTS, *args.exclude_file]))
    retired_count = sum(candidate["symbol"] in retired for candidate in candidates)
    candidates = [candidate for candidate in candidates
                  if candidate["symbol"] not in retired]
    candidates = apply_shard(candidates, args.shard)
    rank_candidates(candidates)
    # Layer the boundary/status-aware index on top of the 3-field retirement
    # above: logged_no_match reads only the AGENTS.md log shape, so 5-field
    # verdicts (441 rows) pass through it. drop_logged (tools/re_log.py) is
    # what actually retires them.
    suppressed = 0
    if not args.include_logged:
        candidates, suppressed = drop_logged(candidates)
        retired_count += suppressed
    if args.json:
        serializable = []
        for candidate in candidates:
            item = {key: value for key, value in candidate.items() if key != "bytes"}
            item["bytes_hex"] = candidate["bytes"].hex()
            serializable.append(item)
        print(json.dumps({"candidates": serializable,
                          "excluded_matched": already_matched,
                          "excluded_arity": arity_conflicts,
                          "excluded_logged": retired_count}, indent=2))
        return
    if not args.ranked:
        selected, meta = select_candidate(candidates)
        if selected is None:
            print("No validated naked-asm candidates remain in the requested paths.")
            return
        print(f"== selected naked-asm conversion (drawn from {meta['pool']}) ==")
        print(f"  {selected['symbol'] or selected['signature'] or '(unnamed)'}")
        print(f"  {selected['size']} bytes  {selected['path']}:{selected['line']}")
        if meta.get("packet"):
            print(f"  START HERE: {meta['packet'].relative_to(build.ROOT)} — Zero Hour's "
                  "own source for this body, named and nearly aligned. Port it, then "
                  "close the gap against the disassembly the packet quotes.")
        if selected["tracked"]:
            print(f"  verify: ./build.sh '{selected['symbol']}'")
        # The queue now serves gen_dump waves, whose bodies byte-verify by
        # construction. Without this, a green build.sh reads as a landed
        # conversion: 56 __emit lifts were reverted across 10 commits, and one
        # A/B session reported five conversions having converted nothing.
        print("  NOTE: a passing byte check proves nothing here — the naked body IS the "
              "retail bytes; it converts only once that __emit body is gone.")
        return

    if already_matched:
        print(f"{already_matched} excluded as already matched in reverse/functions.csv")
    if retired_count:
        print(f"{retired_count} excluded as already no-match in the investigation log")
    if arity_conflicts:
        print(f"{arity_conflicts} excluded because the decorated name cannot produce the "
              "body: either its stack cleanup contradicts the bytes, so the name is on the "
              "wrong function (tools/audit_ret_arity.py lists those), or the name carries no "
              "signature at all")
    if args.groups:
        groups = defaultdict(list)
        for item in candidates:
            groups[item["bytes"]].append(item)
        grouped = sorted(groups.items(), key=lambda entry: (-len(entry[1]), -entry[1][0]["score"], len(entry[0])))
        for data, items in grouped[: args.limit]:
            tracked = sum(1 for item in items if item["tracked"])
            sample = items[0]
            reasons = ", ".join(sample["reasons"])
            print(f"{len(items):4d} function(s), {tracked:4d} tracked, {len(data):4d} bytes, score {sample['score']:4d}")
            print(f"      bytes: {' '.join(f'{byte:02x}' for byte in data)}")
            print(f"      {reasons}")
            for item in items[:5]:
                location = f"{item['path']}:{item['line']}"
                print(f"      {location}  {item['status']}  {item['signature']}")
                if item["tracked"]:
                    print(f"        ./build.sh '{item['symbol']}'")
            if len(items) > 5:
                print(f"      ... {len(items) - 5} more")
        return

    for item in candidates[: args.limit]:
        print_candidate(item)


if __name__ == "__main__":
    main()
