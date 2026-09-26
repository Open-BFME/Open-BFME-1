#!/usr/bin/env python3
"""Named __emit lifts: open work that no picker used to see.

WHY THIS EXISTS. progress.py scores a `__declspec(naked)`/`__emit` body inside
a .cpp as a dump -- it is retail's bytes re-encoded, not source -- but
eligibility.is_dump_row only knew gen-dump notes and .asm suffixes. So the
headline counted 592 lift bodies (496 KB, 5.1 pp, measured 2026-09-25) as
unconverted while open_dumps, and every picker built on it, never served one.
Most are the 2026-08-11 "Open-BFME5 ... via C++ thunk" lifts: NAMED functions
(ScriptActions::executeAction, GameEngine::init, GameLogic::startNewGame, ...),
315 of them with a same-name Zero Hour definition.

WHY A BOUNDARY CHECK. An __emit lift byte-matches whatever extent it claims, so
nothing ever tested those extents, and some are wrong: 0x004800FC starts in the
middle of `mov [0x012F1BC0], eax`, 0x00397540 stops before `pop ebx; add esp`,
and executeAction stops short of its own jump table (83 landed rows keep their
table inside the extent, 5 do not). Serving a wrong extent invites a "match"
against the wrong bytes. So a lift is open work only when its extent passes
the positive checks in `extent_problems`; the rest are listed by `--suspect`
for a boundary pass first.

  python3 tools/lift_lane.py                 # servable lifts, ZH twins first
  python3 tools/lift_lane.py --suspect       # lifts whose extent needs fixing
  python3 tools/lift_lane.py --summary       # counts and bytes only

Converting one (precedent 33110b4b40, AIPlayer::startTraining): write the real
body in the TU the lift's `// readable body of ...` comment names (or its ZH
home), repoint the row with `tools/add_match.py <name> <rva> <size> <source>
--replace-existing`, and delete the naked function -- the whole lift file when
nothing else lives in it. The conversion gate refuses a lift left behind.
"""
import argparse
import bisect
import re
import struct
import sys
from functools import lru_cache
from pathlib import Path

import capstone

import build

ROOT = Path(__file__).resolve().parents[1]
ZH_ROOT = ROOT / "inputs/reference" / "CnC_Generals_Zero_Hour"
READABLE_RE = re.compile(r"^//\s*readable (?:ZH )?body(?: of \S+)?:\s*(\S+)", re.M)

_LIFTS = None


def _image():
    data, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    base = struct.unpack_from("<I", data, pe + 24 + 28)[0]
    return data, text, base


@lru_cache(maxsize=1)
def image():
    return _image()


def read(rva, size):
    data, text, _ = image()
    lo = text["raw_pointer"] + rva - text["rva"]
    return data[lo:lo + size]


def lift_rows(rows=None):
    """{(name, target_rva): row} for matched rows whose body is a naked/__emit
    lift inside a C/C++ source (progress.py's definition, read from the working
    tree). Rows that already count as dumps (gen-dump note, .asm) are excluded:
    they need no second route into the queue."""
    import eligibility
    import progress

    rows = eligibility.load_rows() if rows is None else rows
    matched = {}
    by_key = {}
    for row in rows:
        if row.get("status") != "matched" or not (row.get("target_rva") or "").startswith("0x"):
            continue
        if Path(row.get("source", "")).suffix.lower() not in progress.CPP_SUFFIXES:
            continue
        if build.is_scaffold_row(row):
            continue
        key = (row["name"], row["target_rva"])
        try:
            matched[key] = (int(row["target_size"]), row["source"])
        except (TypeError, ValueError):
            continue
        by_key[key] = row
    naked = progress.naked_cpp_rows(matched, progress.naked_source_texts(matched, None))
    return {key: by_key[key] for key in naked}


class _Minus:
    """Membership in a Counter of edges with one occurrence taken away: the
    ledger's edges as seen by every row except the one being judged."""

    def __init__(self, counts, own):
        self.counts, self.own = counts, own

    def __contains__(self, value):
        return self.counts.get(value, 0) - (value == self.own) > 0


class Ledger:
    """Every matched extent, indexed once: edges for the boundary checks and
    an overlap test that ignores the row being corrected."""

    def __init__(self, rows):
        from collections import Counter

        spans = []
        for row in rows:
            if row.get("status") != "matched" or not (row.get("target_rva") or "").startswith("0x"):
                continue
            try:
                start, size = int(row["target_rva"], 16), int(row["target_size"])
            except (TypeError, ValueError):
                continue
            if size > 0:
                spans.append((start, start + size))
        spans.sort()
        self.spans = spans
        self.span_starts = [s for s, _ in spans]
        self.longest = max((e - s for s, e in spans), default=0)
        self.starts = Counter(s for s, _ in spans)
        self.ends = Counter(e for _, e in spans)

    def edges(self, own=None):
        """(starts, ends) containers; `own=(rva, size)` hides that row's edges."""
        rva, size = own or (None, 0)
        return (_Minus(self.starts, rva), _Minus(self.ends, None if rva is None else rva + size))

    def claimed(self, lo, hi, own=None):
        """True when a matched row other than `own=(rva, size)` overlaps [lo, hi)."""
        own_span = None if own is None else (own[0], own[0] + own[1])
        skipped = False
        j = bisect.bisect_left(self.span_starts, hi) - 1
        while j >= 0 and self.span_starts[j] > lo - self.longest:
            start, end = self.spans[j]
            if (start, end) == own_span and not skipped:
                skipped = True
            elif start < hi and lo < end:
                return True
            j -= 1
        return False


def ledger_edges(rows):
    """(starts, ends) membership containers over every matched row."""
    return Ledger(rows).edges()


def _code_end(body, rva, base):
    """Offset where executable code stops: the lowest in-body table an indexed
    memory operand names (a switch's `jmp [reg*4 + T]` dword table, or the
    `movzx reg, byte ptr [reg + T]` index table of a sparse switch), else the
    whole body. MSVC places both after the function's code, inside its extent.
    Decoding stops at the first table so its data is never read as code."""
    end = len(body)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    for ins in md.disasm(body, rva):
        if ins.address - rva >= end:
            break
        for op in ins.operands:
            if op.type != capstone.x86.X86_OP_MEM or op.mem.index == 0:
                continue
            table = (op.mem.disp & 0xFFFFFFFF) - base
            if rva < table < rva + end:
                end = table - rva
    return end


def _filler(ins):
    """nop / int3 / `mov r, r` / `lea r, [r]`: alignment padding, not code."""
    if ins.mnemonic in ("nop", "int3"):
        return True
    ops = [o.strip() for o in ins.op_str.split(",")]
    return (len(ops) == 2 and (ins.mnemonic == "mov" and ops[0] == ops[1]
                               or ins.mnemonic == "lea" and ops[1] in (f"[{ops[0]}]", f"[{ops[0]} + 0]")))


def extent_problems(name, rva, size, starts, ends, reader=read, base=None):
    """Reasons [rva, rva+size) is not a proven function extent; [] when clean.

    Every accept is positive evidence: int3 padding or a neighbouring ledger
    body on both sides, a linear decode that lands exactly on the end (or on an
    in-body jump table), a terminal last instruction, no int3 run with code
    after it inside, no jump table pointing back into the body right after the
    end, and a stack cleanup the decorated name agrees with."""
    import audit_ret_arity

    if base is None:
        base = image()[2]
    end = rva + size
    body = reader(rva, size)
    problems = []
    if reader(rva - 1, 1) != b"\xcc" and rva not in ends:
        problems.append("start: neither int3 nor a ledger body ends before it")
    after = reader(end, 4)
    if after[:1] != b"\xcc" and end not in starts:
        problems.append("end: neither int3 nor a ledger body starts after it")
    if len(after) == 4 and rva <= struct.unpack("<I", after)[0] - base < end:
        problems.append("end: a jump table into the body follows the extent")
    code = _code_end(body, rva, base)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    last, reached, run, pad_inside = None, 0, 0, None
    for ins in md.disasm(body[:code], rva):
        reached = ins.address + ins.size - rva
        # MSVC aligns an in-body jump table with filler after the final ret.
        if last is None or not _filler(ins):
            last = ins
        # Padding between two functions decodes as int3 instructions; a 0xCC
        # byte inside an immediate or displacement does not.
        if ins.mnemonic == "int3":
            run += 1
        else:
            if run >= 3 and pad_inside is None:
                pad_inside = ins.address - rva - run
            run = 0
    first = next(md.disasm(body[:16], rva), None)
    if first is None or first.mnemonic in JUNK_FIRST:
        problems.append(f"start: first instruction is {first.mnemonic if first else 'undecodable'}")
    if reached != code:
        problems.append(f"decode: stops at +0x{reached:X}, code runs to +0x{code:X}")
    elif last is None or last.mnemonic not in ("ret", "retf", "jmp", "int3"):
        # A body may end in a call that never returns (a throw helper), but
        # only int3 padding right after it says so.
        if not (last is not None and last.mnemonic == "call" and after[:1] == b"\xcc"):
            problems.append(f"end: last instruction is {last.mnemonic if last else 'nothing'}, not a ret/jmp")
    if pad_inside is not None:
        problems.append(f"interior: int3 run at +0x{pad_inside:X} with code after it")
    want, convention = audit_ret_arity.expected_ret(name)
    got = audit_ret_arity.actual_ret(body[:code])
    if convention != "__cdecl" and want is not None and got is not None and got != want:
        problems.append(f"arity: {convention} name pops {want}B, body pops {got}B")
    return problems


_ECX = {capstone.x86.X86_REG_ECX, capstone.x86.X86_REG_CX,
        capstone.x86.X86_REG_CL, capstone.x86.X86_REG_CH}


def identity_warnings(name, rva, size, reader=read):
    """Hints that the lift's NAME is wrong; a warning, never a refusal.

    The first lift finishers (2026-09-25) found 3 of 4 names wrong even though
    stack cleanup agreed with them: an INI parser under a WeaponStore method,
    a MeshClass virtual under W3DAssetManager, a six-argument cdecl under a
    no-argument thiscall. A thiscall body whose first touch of ecx is a write
    (or that never touches it before returning) is not using `this`. Among
    thiscall bodies >= 60 B that is 2.3% of landed C++ against 6.8% of lifts,
    so it is a lead worth checking first, not a verdict."""
    import audit_ret_arity

    if audit_ret_arity.expected_ret(name)[1] != "__thiscall" or size < 60:
        return []
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    for ins in md.disasm(reader(rva, size), rva):
        try:
            regs_read, regs_written = ins.regs_access()
        except capstone.CsError:
            return []
        if ins.mnemonic == "call" or _ECX & set(regs_read):
            return []
        if _ECX & set(regs_written) or ins.mnemonic in ("ret", "jmp"):
            break
    return ["thiscall name, but the body overwrites or ignores ecx before using it: "
            "`this` looks unused, so prove the class and convention (callers' pushes, "
            "vtable slot) before porting"]


_SPECIAL_RE = re.compile(r"^\?\?(?:_[0-9A-Z]|[0-9A-Z])([A-Za-z_]\w*)@")   # ??0 ctor, ??1 dtor, ??_G ...
_MEMBER_RE = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@")


def class_of(name):
    """Owning class of a decorated member name, else None (free functions)."""
    m = _SPECIAL_RE.match(name or "")
    if m:
        return m.group(1)
    m = _MEMBER_RE.match(name or "")
    return m.group(2) if m else None


@lru_cache(maxsize=1)
def _class_index():
    """{class: Counter(source)} over landed real C++ (no lifts, dumps or gen)."""
    from collections import Counter, defaultdict
    import eligibility

    index = defaultdict(Counter)
    rows = eligibility.load_rows()
    lifts = set(lift_rows(rows))
    for row in rows:
        source = row.get("source", "")
        if (row.get("status") != "matched" or not source.endswith((".cpp", ".c"))
                or source.startswith("game/gen_") or (row["name"], row["target_rva"]) in lifts
                or build.is_scaffold_row(row)):
            continue
        cls = class_of(row["name"])
        if cls:
            index[cls][source] += 1
    return index


def class_homes(name, limit=3):
    """[(source, landed rows)] where this class's landed methods already live."""
    cls = class_of(name)
    return _class_index().get(cls, {}).most_common(limit) if cls else []


SCAN_LIMIT = 0x10000
# 61,015 of 61,018 landed C++ bodies that follow int3 padding start on a
# 16-byte boundary (measured 2026-09-25), so a padding run is only a function
# fence when the code after it is 16-aligned. That keeps a 0xCC byte inside a
# jump table or an immediate from being read as the end of a body.
ALIGN = 16
# Privileged or I/O instructions never open a function in this game: a start
# that decodes to one is data or a misaligned decode (0x001C8E60 opens with hlt).
JUNK_FIRST = {"hlt", "in", "out", "insb", "insd", "outsb", "outsd", "int1", "cli", "sti",
              "iretd", "lds", "les", "arpl", "into", "bound", "retf", "sldt", "lock"}


def proposed_extent(row, problems, ledger, reader=read):
    """(start, size, evidence) for a lift whose recorded extent failed, or None.

    Grows the extent only across bytes no other row claims: back to the
    16-aligned address after the previous int3 run or ledger body, forward to
    the next int3 run that ends on a 16-aligned address or the next ledger
    body. The result must pass every `extent_problems` check itself. Arity is
    a claim about the NAME, not the extent, so an arity refusal is never
    corrected here."""
    if any(p.startswith("arity") for p in problems):
        return None
    rva, size = int(row["target_rva"], 16), int(row["target_size"])
    own = (rva, size)
    starts, ends = ledger.edges(own)
    start, end = rva, rva + size
    evidence = []
    if any(p.startswith("start") for p in problems):
        # Only padding moves a start. A neighbouring ledger body's end is not
        # enough: of the first 13 moved starts, the three that stopped there
        # landed mid-function or merged CRT import stubs.
        p = rva
        while p > rva - SCAN_LIMIT and not (reader(p - 1, 1) == b"\xcc" and p % ALIGN == 0):
            p -= 1
        if p <= rva - SCAN_LIMIT or ledger.claimed(p, rva, own):
            return None
        start = p
        evidence.append(f"start 0x{start:08X} is 16-aligned after int3")
    if any(p.startswith(("end", "decode", "interior")) for p in problems):
        q = end
        while q < end + SCAN_LIMIT and q not in starts:
            if reader(q, 1) == b"\xcc":
                r = q
                while reader(r, 1) == b"\xcc":
                    r += 1
                if r % ALIGN == 0:
                    break
                q = r
            else:
                q += 1
        if q >= end + SCAN_LIMIT or ledger.claimed(end, q, own):
            return None
        evidence.append(f"end 0x{q:08X} " + ("meets a ledger body" if q in starts
                                             else "meets int3 padding before a 16-aligned start"))
        end = q
    if (start, end) == (rva, rva + size):
        return None
    if extent_problems(row["name"], start, end - start, starts, ends, reader):
        return None
    return start, end - start, "; ".join(evidence)


EXTENTS = ROOT / "targets/game/reverse" / "lift_extents.csv"
EXTENT_FIELDS = ["name", "ledger_rva", "ledger_size", "start", "size", "evidence"]


def load_extents(path=None):
    """{(name, ledger_rva): {start, size, evidence}} from targets/game/reverse/lift_extents.csv."""
    import csv

    path = Path(path or EXTENTS)
    if not path.exists():
        return {}
    with path.open(newline="", encoding="utf-8") as fh:
        return {(r["name"], r["ledger_rva"]): r for r in csv.DictReader(fh)}


def lift_verdicts(rows=None, extents=None):
    """[(row, problems, correction)] for every lift row, one per address.

    `problems` judges the recorded extent. `correction` is the entry for this
    lift in targets/game/reverse/lift_extents.csv, re-verified against the image now, or
    None; a correction that no longer passes is dropped rather than trusted."""
    import eligibility

    rows = eligibility.load_rows() if rows is None else rows
    extents = load_extents() if extents is None else extents
    ledger = Ledger(rows)
    starts, ends = ledger.edges()
    out, seen = [], set()
    for (name, rva_text), row in sorted(lift_rows(rows).items(), key=lambda kv: kv[0][1]):
        rva = int(rva_text, 16)
        if rva in seen:
            continue
        seen.add(rva)
        problems = extent_problems(name, rva, int(row["target_size"]), starts, ends)
        correction = None
        entry = extents.get((name, rva_text))
        if problems and entry and entry.get("ledger_size") == row["target_size"]:
            own = (rva, int(row["target_size"]))
            start, size = int(entry["start"], 16), int(entry["size"])
            if not ledger.claimed(start, start + size, own) and \
                    not extent_problems(name, start, size, *ledger.edges(own)):
                correction = entry
        out.append((row, problems, correction))
    return out


def servable_lift_keys(rows=None):
    """{(name, target_rva)} of lifts whose recorded extent is clean or has a
    verified correction: what eligibility.is_dump_row admits. Cached per
    process; `reset()` after changing the tree."""
    return {key for key, (problems, correction) in _verdict_map(rows).items()
            if not problems or correction}


def correction_for(row):
    """The verified targets/game/reverse/lift_extents.csv entry for a servable lift, else None."""
    found = _verdict_map().get((row["name"], row["target_rva"]))
    return found[1] if found else None


def _verdict_map(rows=None):
    global _LIFTS
    if _LIFTS is None:
        _LIFTS = {(row["name"], row["target_rva"]): (problems, correction)
                  for row, problems, correction in lift_verdicts(rows)}
    return _LIFTS


def reset():
    global _LIFTS
    _LIFTS = None


def write_extents(rows=None, path=None):
    """Recompute targets/game/reverse/lift_extents.csv from the image: one row per suspect
    lift whose extent `proposed_extent` can prove. Returns the rows written."""
    import csv
    import eligibility

    rows = eligibility.load_rows() if rows is None else rows
    out = []
    ledger = Ledger(rows)
    for row, problems, _ in lift_verdicts(rows, extents={}):
        if not problems:
            continue
        found = proposed_extent(row, problems, ledger)
        if found:
            start, size, evidence = found
            out.append({"name": row["name"], "ledger_rva": row["target_rva"],
                        "ledger_size": row["target_size"], "start": f"0x{start:08X}",
                        "size": str(size), "evidence": evidence})
    path = Path(path or EXTENTS)
    with path.open("w", newline="", encoding="utf-8") as fh:
        writer = csv.DictWriter(fh, fieldnames=EXTENT_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(out)
    reset()
    return out


@lru_cache(maxsize=1)
def zh_definitions():
    """({(Class, method)}, {free function}) defined in the ZH reference .cpp files."""
    methods, free = set(), set()
    for path in ZH_ROOT.rglob("*.cpp"):
        text = path.read_text(encoding="utf-8", errors="replace")
        methods.update(re.findall(r"^[^\n;/]*?\b(\w+)::(~?\w+)\s*\(", text, re.M))
        free.update(re.findall(
            r"^(?:static\s+)?[A-Za-z_][\w\*&]*(?:\s+[\w\*&]+)*\s+\**(\w+)\s*\([^;{]*\)?\s*$",
            text, re.M))
    return methods, free


def zh_twin(name):
    """True when the decorated name's Class::method (or free function) is defined in ZH."""
    methods, free = zh_definitions()
    m = re.match(r"\?(\?[0-9A-Z])?(\w+)@(\w+)@@", name)
    if m and m.group(1) == "?0":
        return (m.group(3), m.group(3)) in methods
    if m and m.group(1) == "?1":
        return (m.group(3), "~" + m.group(3)) in methods
    if m and not m.group(1):
        return (m.group(3), m.group(2)) in methods
    m = re.match(r"\?(\w+)@@", name) or re.match(r"_(\w+?)(?:@\d+)?$", name)
    return bool(m) and m.group(1) in free


def readable_home(source):
    """The TU a lift file's header names as the readable body's home, if any."""
    try:
        text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
    except OSError:
        return ""
    m = READABLE_RE.search(text[:2000])
    return m.group(1) if m else ""


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--suspect", action="store_true",
                    help="list lifts whose extent fails and has no proven correction")
    ap.add_argument("--summary", action="store_true", help="counts and bytes only")
    ap.add_argument("--write-extents", action="store_true",
                    help="recompute targets/game/reverse/lift_extents.csv (proven extent corrections)")
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--min-size", type=int, default=0)
    args = ap.parse_args(argv)

    import eligibility

    rows = eligibility.load_rows()
    if args.write_extents:
        written = write_extents(rows)
        print(f"lift_extents.csv: {len(written)} proven extent correction(s)")
    latest = eligibility.latest_verdicts()
    counts = eligibility.attempt_counts()
    verdicts = lift_verdicts(rows)
    live = [v for v in verdicts if not eligibility.retired(eligibility.rva_of(v[0]), latest)]
    clean = [v for v in live if not v[1]]
    corrected = [v for v in live if v[1] and v[2]]
    suspect = [v for v in live if v[1] and not v[2]]
    retired = [v for v in verdicts if v not in live]

    def total(items):
        return sum(int(v[0]["target_size"]) for v in items)

    print(f"lifts: {len(verdicts)} bodies, {total(verdicts):,} B; servable {len(clean) + len(corrected)} "
          f"({total(clean) + total(corrected):,} B, {len(corrected)} of them with a proven extent "
          f"correction), suspect extent {len(suspect)} ({total(suspect):,} B), retired by a "
          f"dead-end verdict {len(retired)} ({total(retired):,} B)")
    if args.summary:
        return 0
    items = suspect if args.suspect else clean + corrected
    items = [v for v in items if int(v[0]["target_size"]) >= args.min_size]
    twins = {id(v[0]): zh_twin(v[0]["name"]) for v in items}
    items.sort(key=lambda v: (not twins[id(v[0])], -int(v[0]["target_size"])))
    for row, problems, correction in items[:args.limit]:
        rva = eligibility.rva_of(row)
        home = readable_home(row["source"])
        print(f"{int(row['target_size']):6}B {row['target_rva']} {'ZH ' if twins[id(row)] else '   '}"
              f"verdicts={counts.get(rva, 0)} {row['name']}")
        print(f"         lift: {row['source']}" + (f"  readable: {home}" if home else ""))
        for warning in identity_warnings(row["name"], rva, int(row["target_size"])):
            print(f"         ? {warning}")
        if correction:
            print(f"         extent: {correction['start']} {correction['size']}B, not the ledger's "
                  f"{row['target_size']}B ({correction['evidence']})")
        elif problems:
            for problem in problems:
                print(f"         ! {problem}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
