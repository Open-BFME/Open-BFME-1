#!/usr/bin/env python3
"""Per-row checks for what compile_function's masking cannot see.

compile_function copies every DIR32 operand from retail before comparing, and
compares only the ledger extent. So these byte-match while wrong:

  ltable  A jump-table entry, or `mov reg, offset $L`, that lands on the wrong
          case: the entry is a DIR32, so its value was copied from retail. Each
          same-section DIR32 must equal image base + row RVA + (label - function
          start) + addend. A same-section FUNCTION (a C file's static callback
          in a non-/Gy .text) is bound by name instead, like any callee.
  tail    Bytes the object places after the extent and before the next
          function: tail jump tables, a __except filter, a cut-short epilogue.
          They must equal retail (relocation sites masked; same-section DIR32s
          are checked exactly by ltable).
  static  A TU-local datum the body reads: a `$SG` string (compiled without
          /GF), a function-local static, a TU-local const table. The address
          is masked and nothing compared the bytes behind it. Initialised
          bytes must equal retail at the address retail uses (relocation slots
          masked; a `$SG` string is compared through its terminator).

Findings are keyed (check, target RVA, name). The ones already in the ledger
when this landed sit in targets/game/reverse/body_guard_baseline.csv, which
only ever shrinks: a fixed row's line must be removed in the same commit, and
a line may never be added by hand (`--assert-shrink-only REV`, run by the
commit hook whenever the file is staged).

Usage:
  python3 tools/body_guard.py --shadow OUT.csv     all matched rows, objects already built
  python3 tools/body_guard.py --assert-shrink-only HEAD
"""
import csv
import re
import struct
import sys
from bisect import bisect_right
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT
BASELINE = ROOT / "targets/game/reverse" / "body_guard_baseline.csv"
BASELINE_FIELDS = ["check", "target_rva", "name", "detail"]
IMAGE_BASE = 0x400000
DIR32 = 0x0006
SCN_CNT_CODE = 0x20
SCN_INITIALIZED = 0x40
SCN_UNINITIALIZED = 0x80
STORAGE_EXTERNAL = 2
STORAGE_STATIC = 3
FUNCTION_TYPE = 0x20


def _u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def _is_function(symbol):
    return symbol["type"] == FUNCTION_TYPE or symbol["storage"] == STORAGE_EXTERNAL


def _starts(symbols, section, *, functions_only):
    """Sorted start offsets of the named symbols in one section: functions only
    for a code extent, every named datum for a data extent. Section symbols
    carry an aux record; `$L` labels sit inside a function."""
    out = []
    for s in symbols:
        if (s["section"] != section or not s["name"] or s["aux"]
                or s["storage"] not in (STORAGE_EXTERNAL, STORAGE_STATIC)):
            continue
        if functions_only and (not _is_function(s) or s["name"].startswith("$")):
            continue
        out.append(s["value"])
    return sorted(set(out))


def _next_after(values, value, limit):
    i = bisect_right(values, value)
    return min(values[i], limit) if i < len(values) else limit


class Context:
    """Ledger-wide lookups, built once per run."""

    def __init__(self, symbol_map=None):
        self.symbol_map = build.load_symbol_map() if symbol_map is None else symbol_map
        exe = build.EXE.read_bytes()
        sections = build.pe_sections(exe)
        text = next(s for s in sections if s["name"] == ".text")
        low, high = text["rva"], text["rva"] + text["size"]
        self._follow = lambda rva: build.follow_thunk(exe, sections, rva, low, high) \
            if low <= rva < high - 5 else rva

    def same_function(self, address, name):
        candidates = self.symbol_map.get(name, ())
        if address in candidates:
            return True
        body = self._follow(address)
        return any(self._follow(c) == body for c in candidates)


def _retail(rva, size):
    try:
        return build.read_target_bytes(rva, size)
    except ValueError:
        return b""


def _static_content(info, symbol, base_va, addend):
    """(verdict, detail) for one TU-local datum against retail at base_va."""
    data, sections, symbols = info["data"], info["sections"], info["symbols"]
    sec = sections[symbol["section"] - 1]
    if (sec["characteristics"] & (SCN_CNT_CODE | SCN_UNINITIALIZED)
            or not sec["characteristics"] & SCN_INITIALIZED or not sec["raw_pointer"]):
        return "skip", ""
    end = _next_after(_starts(symbols, symbol["section"], functions_only=False),
                      symbol["value"], sec["raw_size"])
    start = sec["raw_pointer"] + symbol["value"]
    blob = data[start: sec["raw_pointer"] + end]
    mask = bytearray(len(blob))
    for r in range(sec["reloc_count"]):
        ro = sec["reloc_pointer"] + r * 10
        at = _u32(data, ro) - symbol["value"]
        if 0 <= at < len(blob):
            width = build.RELOC_WIDTH.get(struct.unpack_from("<H", data, ro + 8)[0], 4)
            mask[at: at + width] = b"\1" * width
    if symbol["name"].startswith("$SG"):
        # The string the body reads starts at the addend and ends at its NUL;
        # what follows is alignment padding retail need not share.
        lo = addend if 0 <= addend < len(blob) else 0
        nul = blob.find(b"\0", lo)
        lo, hi = lo, (nul + 1 if nul >= 0 else len(blob))
    else:
        lo, hi = 0, len(blob)
        # Trailing zero bytes up to the next 4-byte boundary can be the
        # compiler's alignment pad rather than part of the datum.
        while hi > 0 and hi % 4 and blob[hi - 1] == 0:
            hi -= 1
    retail = _retail(base_va - IMAGE_BASE + lo, hi - lo)
    if len(retail) != hi - lo:
        return "mismatch", f"{symbol['name'][:40]} outside the retail image"
    diff = [i for i in range(lo, hi) if not mask[i] and blob[i] != retail[i - lo]]
    if diff:
        return "mismatch", (f"{symbol['name'][:40]}@0x{base_va:08X}: {len(diff)} byte(s) "
                            f"differ, first +{diff[0]}: source {blob[lo:hi][:24].hex()} "
                            f"retail {retail[:24].hex()}")
    return "ok", ""


def row_findings(row, ctx, stats=None):
    """[(check, detail)] for one matched row whose object is built."""
    stats = {} if stats is None else stats
    obj = build.row_object(row)
    rva, size = int(row["target_rva"], 16), int(row["target_size"])
    symbol = build.ledger_object_symbol(row)
    if build.is_funclet_row(row, symbol) or (ROOT / row["source"]).suffix.lower() == build.LIB_SUFFIX:
        return []  # funclet bodies are re-read by label; lib members are pre-link
    try:
        body, relocs, info = build.read_object_symbol_bytes(obj, symbol, size, detail=True)
    except (ValueError, OSError):
        return []  # verify_functions already reports an unreadable row
    secno, start = info["section"], info["value"]
    sec = info["sections"][secno - 1]
    func_end = _next_after(_starts(info["symbols"], secno, functions_only=True), start,
                           sec["raw_size"])
    func = body[: func_end - start].rstrip(b"\xcc")
    retail = _retail(rva, max(len(func), size))
    findings = []

    covered = bytearray(len(func))
    for (off, rtype, name), target in zip(relocs, info["reloc_symbols"]):
        width = build.RELOC_WIDTH.get(rtype, 4)
        covered[off: off + width] = b"\1" * len(covered[off: off + width])
        if rtype != DIR32 or off + 4 > len(func) or off + 4 > len(retail):
            continue
        addend = _u32(body, off)
        final = _u32(retail, off)
        if target["section"] == secno and target["section"] > 0:
            if _is_function(target) and not target["name"].startswith("$"):
                stats["ltable_function"] = stats.get("ltable_function", 0) + 1
                got = (final - addend - IMAGE_BASE) & 0xFFFFFFFF
                if not ctx.same_function(got, name):
                    findings.append(("ltable", f"+{off} {name[:60]} -> 0x{got:08X}"))
                continue
            want = (IMAGE_BASE + rva + target["value"] - start + addend) & 0xFFFFFFFF
            stats["ltable_entries"] = stats.get("ltable_entries", 0) + 1
            if want != final:
                findings.append(("ltable", f"+{off} {name} wants 0x{want:08X} retail 0x{final:08X}"))
            continue
        if off + 4 > size or target["section"] <= 0:
            continue
        # $T<n> is the function's own FuncInfo (exception state table): the
        # exception verifier owns it, and object-symbol= rows alias one anchor
        # TU's table onto thousands of retail copies by design.
        local = (target["storage"] == STORAGE_STATIC and not target["aux"]
                 and not name.startswith("$T"))
        if not (local or name.startswith("$SG")):
            if target["aux"] and target["storage"] == STORAGE_STATIC:
                stats["static_section_symbol"] = stats.get("static_section_symbol", 0) + 1
            continue
        tsec = info["sections"][target["section"] - 1]
        if tsec["characteristics"] & SCN_CNT_CODE:
            continue
        verdict, detail = _static_content(info, target, (final - addend) & 0xFFFFFFFF, addend)
        stats["static_" + verdict] = stats.get("static_" + verdict, 0) + 1
        if verdict == "mismatch":
            findings.append(("static", f"+{off} {detail}"))

    if len(func) > size:
        tail = len(func) - size
        stats["tail_rows"] = stats.get("tail_rows", 0) + 1
        if len(retail) < len(func):
            findings.append(("tail", f"compiled={len(func)} ledger={size}: tail past the image"))
        else:
            diff = [k for k in range(size, len(func)) if not covered[k] and func[k] != retail[k]]
            if diff:
                findings.append(("tail", f"compiled={len(func)} ledger={size} tail={tail}: "
                                 f"{len(diff)} byte(s) differ from retail, first +{diff[0]}"))
    return findings


_ROW_SIZE = {}


def _row_sizes():
    if not _ROW_SIZE:
        for row in build.load_all_function_rows():
            _ROW_SIZE.setdefault(int(row["target_rva"], 16), int(row["target_size"]))
    return _ROW_SIZE


_TEXT = []


def _text_follow(rva):
    if not _TEXT:
        exe = build.EXE.read_bytes()
        sections = build.pe_sections(exe)
        text = next(s for s in sections if s["name"] == ".text")
        _TEXT.extend([exe, sections, text["rva"], text["rva"] + text["size"]])
    exe, sections, low, high = _TEXT
    for _ in range(4):
        if not low <= rva < high - 5:
            return rva
        nxt = build.follow_thunk(exe, sections, rva, low, high)
        if nxt == rva:
            return rva
        rva = nxt
    return rva


def _shape(start, size):
    """Retail body with relocations resolved the way a link resolves them:
    raw bytes, except a relative branch, which is its target -- an offset
    when it stays inside the body, else the thunk-followed callee."""
    from capstone import CS_ARCH_X86, CS_GRP_CALL, CS_GRP_JUMP, CS_MODE_32, CS_OP_IMM, Cs
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.detail = True
    code = _retail(start, size)
    if len(code) != size:
        return None
    out, end = [], 0
    for ins in md.disasm(code, start):
        end = ins.address + ins.size - start
        if ((ins.group(CS_GRP_JUMP) or ins.group(CS_GRP_CALL)) and len(ins.operands) == 1
                and ins.operands[0].type == CS_OP_IMM):
            dest = ins.operands[0].imm
            out.append((ins.mnemonic, "in", dest - start) if start <= dest < start + size
                       else (ins.mnemonic, "out", _text_follow(dest)))
        else:
            out.append(bytes(ins.bytes))
    return out if end == size else None


def callee_twin(dest, candidates):
    """True when the retail call target `dest` is the named callee: the same
    body through another thunk, or a body whose bytes AND resolved call targets
    equal the callee's (an identical second copy). A masked gen-alias call is
    admitted only on this proof."""
    body = _text_follow(dest)
    named = {_text_follow(c) for c in candidates}
    if body in named:
        return True
    sizes = _row_sizes()
    for callee in named:
        size = sizes.get(callee)
        if not size or sizes.get(body, size) != size:
            continue
        mine = _shape(callee, size)
        if mine is not None and mine == _shape(body, size):
            return True
    return False


def read_baseline(path=BASELINE):
    if not Path(path).exists():
        return set()
    with Path(path).open(encoding="utf-8", newline="") as handle:
        return {(r["check"], "0x%08X" % int(r["target_rva"], 16), r["name"])
                for r in csv.DictReader(handle)}


def _key(check, row):
    return (check, "0x%08X" % int(row["target_rva"], 16), row["name"])


def verify(rows, symbol_map=None, *, full=False):
    """Fail on a finding the baseline does not hold, or a baseline line a
    checked row no longer earns (lower the baseline in the same commit)."""
    ctx = Context(symbol_map)
    baseline = read_baseline()
    stats, new, earned, checked = {}, [], set(), set()
    for row in rows:
        for check in ("ltable", "tail", "static"):
            checked.add(_key(check, row))
        for check, detail in row_findings(row, ctx, stats):
            key = _key(check, row)
            if key in baseline:
                earned.add(key)
            else:
                new.append((key, row["source"], detail))
    stale = sorted((baseline & checked) - earned)
    if new or stale:
        print(f"Body guard: FAIL {len(new)} new finding(s), {len(stale)} baseline line(s) "
              "no longer earned")
        for (check, rva, name), source, detail in new[:20]:
            print(f"    {check} {rva} {name} ({source}): {detail}")
        if new:
            print("    The byte check copies DIR32 operands from retail and stops at the "
                  "extent, so it cannot see these. ltable: a case label or table entry "
                  "is wrong. tail: the object continues past the row and differs from "
                  "retail; extend the extent or fix the body. static: a TU-local string "
                  "or table differs from the one retail reads.")
        for check, rva, name in stale[:20]:
            print(f"    fixed: remove `{check},{rva},{name}` from "
                  f"{BASELINE.relative_to(ROOT)}")
        raise SystemExit(1)
    print(f"Body guard: OK ({len(rows)} row(s); {len(earned)} baselined finding(s); {stats})")


def shadow(out_path):
    """Every finding over every matched row whose object exists (no compile)."""
    import time
    t0 = time.perf_counter()
    ctx = Context()
    stats, n, flagged = {}, 0, []
    for row in build.load_function_rows():
        if not build.row_object(row).exists():
            stats["no_object"] = stats.get("no_object", 0) + 1
            continue
        n += 1
        for check, detail in row_findings(row, ctx, stats):
            flagged.append({"check": check, "target_rva": "0x%08X" % int(row["target_rva"], 16),
                            "name": row["name"], "detail": detail, "source": row["source"],
                            "target_size": row["target_size"]})
    with open(out_path, "w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=BASELINE_FIELDS + ["source", "target_size"],
                                lineterminator="\n")
        writer.writeheader()
        writer.writerows(flagged)
    rows_by_check = {}
    for f in flagged:
        rows_by_check.setdefault(f["check"], set()).add((f["target_rva"], f["name"]))
    print(f"shadow: {n} rows read in {time.perf_counter() - t0:.0f}s; "
          + ", ".join(f"{c}={len(v)} row(s)" for c, v in sorted(rows_by_check.items())))
    print(f"stats: {stats}")


def assert_shrink_only(rev):
    import subprocess
    rel = BASELINE.relative_to(ROOT).as_posix()
    shown = subprocess.run(["git", "show", f"{rev}:{rel}"], cwd=ROOT, capture_output=True)
    if shown.returncode != 0:
        old = set()
    else:
        old = {(r["check"], "0x%08X" % int(r["target_rva"], 16), r["name"])
               for r in csv.DictReader(shown.stdout.decode("utf-8").splitlines())}
    staged = subprocess.run(["git", "show", f":{rel}"], cwd=ROOT, capture_output=True)
    text = staged.stdout.decode("utf-8") if staged.returncode == 0 else ""
    now = {(r["check"], "0x%08X" % int(r["target_rva"], 16), r["name"])
           for r in csv.DictReader(text.splitlines())}
    added = sorted(now - old)
    if added and old:
        print(f"body_guard: {rel} grew by {len(added)} line(s); it may only shrink:")
        for key in added[:12]:
            print("    " + ",".join(key))
        raise SystemExit(1)
    print(f"body_guard: baseline shrink-only OK ({len(old)} -> {len(now)})")


if __name__ == "__main__":
    if len(sys.argv) == 3 and sys.argv[1] == "--shadow":
        shadow(sys.argv[2])
    elif len(sys.argv) == 3 and sys.argv[1] == "--assert-shrink-only":
        assert_shrink_only(sys.argv[2])
    else:
        sys.exit(__doc__)
