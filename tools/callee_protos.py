#!/usr/bin/env python3
"""Inferred calling contract of every unsigned callee that open work calls.

WHY THIS EXISTS. Callee ABI is the blocker named most often in anonymous-lane
partials: a body calls `?d_XXXXXXXX`, a gen_asm dump, a scaffold or a lift, and
that name carries a dummy `void()` signature, so the seat has to guess how many
arguments to push, whether `this` travels in ecx and whether the result in eax
is used. A wrong guess moves every byte after the call, and the seat reads the
mismatch as its own body's fault. `callees.py` already warns that a ledger name
is not ABI proof; this says what the retail bytes do instead.

Evidence per callee, each column independent so a seat can weigh it:
  ret_bytes  every `ret N` in the body (N > 0: the callee cleans N bytes, so it
             is __stdcall or __thiscall with N/4 stack slots)
  ecx        first touch of ecx in the body: read (uses `this`), write, none,
             or call (forwarded before any explicit touch -- undecided)
  cleanup    caller-side `add esp, N` / `pop ecx` straight after each call
             site, as N:count (a __cdecl callee; the MINIMUM is the arity,
             larger values are deferred cleanup of earlier calls merged in)
  eax_used   call sites that read eax before writing it, of sites decoded
  ghidra     the decompiler's signature line (needs the GhidraSQL server)
and a one-line `contract` combining them. All of it is inference, never a
pin: prove a contract against a caller before relying on it for a landing.

  python3 tools/callee_protos.py                 # rewrite the tracked CSV
  python3 tools/callee_protos.py --no-ghidra     # bytes only (no server)
  python3 tools/callee_protos.py --calibrate 400 # score against landed names

callees.py and the brief's context pack print the contract under each callee.
"""
import argparse
import collections
import csv
import json
import re
import struct
import sys
import urllib.request
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

OUT = ROOT / "targets/game/reverse/inferred_protos.csv"
FIELDS = ["target_rva", "size", "ret_bytes", "ecx", "sites", "cleanup", "ecx_set", "eax_used",
          "ghidra", "contract"]
IMAGE_BASE = 0x400000
PLACEHOLDER = re.compile(r"^\?(d|dup|b|j)_[0-9a-fA-F]{8}@@")


# ----------------------------------------------------------------- the image

@lru_cache(maxsize=1)
def image():
    import build
    data = open(build.EXE, "rb").read()
    sections = build.pe_sections(data)
    text = sections[0]
    raw = data[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    return raw, text["rva"]


def read(rva, size):
    raw, lo = image()
    if not lo <= rva < lo + len(raw):
        return b""
    return raw[rva - lo:rva - lo + size]


def thunk_target(rva):
    """Body a 5-byte `jmp rel32` incremental-link thunk lands on, else rva."""
    head = read(rva, 5)
    if len(head) == 5 and head[0] == 0xE9:
        return rva + 5 + struct.unpack_from("<i", head, 1)[0]
    return rva


@lru_cache(maxsize=1)
def call_sites():
    """{resolved body rva: [call-site rvas]}, callers through ILT thunks folded in."""
    sys.path.insert(0, str(ROOT / "tools/fleet"))
    import context_pack
    raw, lo = image()
    calls = context_pack.call_index(raw, lo, ROOT / "build/call_index.json")
    folded = collections.defaultdict(list)
    for target, sites in calls.items():
        folded[thunk_target(target)].extend(sites)
    return folded


def _md():
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


def _ecx_regs():
    import capstone
    x = capstone.x86
    return {x.X86_REG_ECX, x.X86_REG_CX, x.X86_REG_CL, x.X86_REG_CH}


def _eax_regs():
    import capstone
    x = capstone.x86
    return {x.X86_REG_EAX, x.X86_REG_AX, x.X86_REG_AL, x.X86_REG_AH}


# ------------------------------------------------------------- body evidence

def body_evidence(rva, size):
    """(sorted distinct `ret N` values, first ecx touch) from the body bytes."""
    import capstone
    import lift_lane

    body = read(rva, size)
    if not body:
        return [], "none"
    code = lift_lane._code_end(body, rva, IMAGE_BASE)
    ecx, rets = None, set()
    for ins in _md().disasm(body[:code], rva):
        if ins.mnemonic == "ret":
            rets.add(int(ins.op_str, 16) if ins.op_str else 0)
        # `push ecx` is MSVC's one-byte `sub esp, 4` for a local slot, not a use of `this`.
        if ecx is None and not (ins.mnemonic == "push" and ins.op_str == "ecx"):
            try:
                regs_read, regs_written = ins.regs_access()
            except capstone.CsError:
                ecx = "none"
                continue
            if _ecx_regs() & set(regs_read):
                ecx = "read"
            elif _ecx_regs() & set(regs_written):
                ecx = "write"
            elif ins.mnemonic == "call":
                ecx = "call"
            elif ins.mnemonic in ("ret", "jmp"):
                ecx = "none"
    return sorted(rets), ecx or "none"


@lru_cache(maxsize=1)
def _spans():
    """Sorted (start, size) of every matched ledger body, to find a call site's owner."""
    import eligibility
    spans = set()
    for r in eligibility.load_rows():
        if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x"):
            spans.add((int(r["target_rva"], 16), int(r["target_size"] or 0)))
    return sorted(spans)


@lru_cache(maxsize=4096)
def _decoded(start, size):
    return list(_md().disasm(read(start, size), start))


def caller_sets_ecx(site):
    """True when the caller loads ecx for this call (it passes `this`), False
    when the value in ecx is garbage or an argument, None when undecided.

    Walking back from the call: a write to ecx passes `this`, unless the value
    was consumed by `push ecx` in between (an argument load: `mov ecx, [x];
    push ecx; call f` is the commonest cdecl shape). Other reads (`mov esi,
    ecx`, `test ecx, ecx`) leave ecx intact and are walked past. A call before
    any write clobbered ecx. An unconditional ret/jmp means the site is a
    branch target whose ecx comes from elsewhere, and function entry means
    `this` passes straight through; both are undecided."""
    import bisect
    import capstone

    spans = _spans()
    i = bisect.bisect_right(spans, (site, 1 << 32)) - 1
    if i < 0 or not spans[i][0] <= site < spans[i][0] + spans[i][1]:
        return None
    body = _decoded(*spans[i])
    at = next((k for k, ins in enumerate(body) if ins.address == site), None)
    if at is None:
        return None
    pushed = False
    for ins in reversed(body[max(0, at - 16):at]):
        if ins.mnemonic == "call":
            return False
        if ins.mnemonic in ("ret", "jmp"):
            return None
        try:
            regs_read, regs_written = ins.regs_access()
        except capstone.CsError:
            return None
        if ins.mnemonic == "push" and ins.op_str == "ecx":
            pushed = True
            continue
        if _ecx_regs() & set(regs_written) and not (ins.mnemonic == "pop" and ins.op_str == "ecx"):
            return not pushed
    return None


def site_evidence(site):
    """(bytes the caller pops right after the call or None, eax read after it)."""
    import capstone

    cleanup, popped, eax = None, 0, None
    for ins in _md().disasm(read(site, 40), site):
        if ins.address == site:
            continue                                  # the call itself
        if eax is None and cleanup is None and ins.mnemonic == "add" and ins.op_str.startswith("esp, "):
            cleanup = int(ins.op_str.split(", ")[1], 0)
            continue
        if eax is None and cleanup is None and ins.mnemonic == "pop" and ins.op_str == "ecx":
            popped += 4
            continue
        try:
            regs_read, regs_written = ins.regs_access()
        except capstone.CsError:
            break
        ops = [o.strip() for o in ins.op_str.split(",")]
        if ins.mnemonic in ("xor", "sub") and len(ops) == 2 and ops[0] == ops[1]:
            regs_read = ()                            # `xor eax, eax` only writes
        if ins.mnemonic in ("call", "ret", "jmp") and not (_eax_regs() & set(regs_read)):
            eax = eax if eax is not None else False
            break
        if _eax_regs() & set(regs_read):
            eax = True
            break
        if _eax_regs() & set(regs_written):
            eax = False
            break
        if ins.mnemonic.startswith("j"):
            break                                     # a branch: stop judging
    if cleanup is None and popped:
        cleanup = popped
    return cleanup, eax


def _ghidra_slots(ghidra):
    if not ghidra:
        return None
    import lift_arity
    return lift_arity.inferred_slots(ghidra)


def contract(rets, ecx, cleanups, eax_used, eax_decoded, ghidra, ecx_set=0, ecx_decided=0, sites=0):
    """One line a seat can read; every clause names its own evidence."""
    callee_clean = [r for r in rets if r]
    unsure = False
    if ecx_decided:
        # callers loading ecx right before the call outrank the callee side:
        # a __thiscall that never uses `this` still receives it
        this = 2 * ecx_set > ecx_decided
    else:
        this = ecx == "read" or bool(ghidra and "__thiscall" in ghidra and ecx != "write")
        # no caller to ask (a virtual, or only reached by jmp) and the body
        # never reads ecx: a __thiscall that ignores `this` looks identical
        unsure = not this
    if len(set(rets)) > 1:
        conv, slots = "?", f"ret values disagree {rets}"
    elif callee_clean:
        conv = "__thiscall" if this else "__stdcall"
        slots = f"{callee_clean[0] // 4} stack slot(s)"
    elif rets and this and ecx_decided:
        # callers load ecx and the callee pops nothing: any `add esp` after
        # the call is deferred cleanup of an earlier __cdecl call
        conv, slots = "__thiscall", "0 stack slots"
    elif cleanups and 2 * len(cleanups) < sites:
        # __ftol2: `add esp` after 4% of 1,273 sites, all of it an earlier
        # call's cleanup deferred past this one
        conv = "__cdecl"
        slots = (f"stack slots unknown (cleanup after only {len(cleanups)}/{sites} sites: "
                 f"0 and deferred, or deferred elsewhere)")
    elif cleanups:
        conv = "__cdecl"
        low = min(cleanups)
        spread = " (variadic?)" if len(set(cleanups)) > 2 else ""
        slots = f"{low // 4} stack slot(s){spread}"
    elif rets and this:
        conv, slots = "__thiscall", "0 stack slots"
    elif rets:
        conv = "__cdecl"
        slots = (f"stack slots unknown (no caller cleanup after {sites} site(s): 0, or deferred)"
                 if sites else "stack slots unknown (no direct call site)")
        inferred = _ghidra_slots(ghidra)
        if inferred is not None:
            slots += f"; ghidra reads {inferred}"
    else:
        conv, slots = "?", "no ret decoded (tail call or wrong extent)"
    if unsure and conv in ("__cdecl", "__stdcall"):
        conv += " (or a __thiscall that never reads `this`)"
    if eax_decoded:
        result = ("returns a value" if eax_used else "result unused at every site (void?)")
        result += f" [eax read at {eax_used}/{eax_decoded} sites]"
    else:
        result = "no call site decoded"
    return f"{conv}, {slots}, {result}"


# ------------------------------------------------------------------ ghidra

def ghidra_signature(url, rva):
    req = urllib.request.Request(url, data=(
        f"SELECT text FROM pseudocode WHERE func_addr = {rva + IMAGE_BASE} "
        "AND completed = 1 AND is_fallback = 0;").encode("utf-8"), method="POST")
    with urllib.request.urlopen(req, timeout=600) as resp:
        res = json.loads(resp.read().decode("utf-8"))["results"][-1]
    if not res.get("success") or not res["rows"]:
        return ""
    for line in res["rows"][0][0].splitlines():
        line = line.strip()
        if line and not line.startswith("/*"):
            return line
    return ""


def ghidra_size(url, rva):
    req = urllib.request.Request(url, data=(
        f"SELECT size FROM funcs WHERE addr = {rva + IMAGE_BASE};").encode("utf-8"), method="POST")
    with urllib.request.urlopen(req, timeout=60) as resp:
        res = json.loads(resp.read().decode("utf-8"))["results"][-1]
    return int(res["rows"][0][0]) if res.get("success") and res["rows"] else 0


# ----------------------------------------------------------------- targets

def unreliable_rows(rows):
    """{rva: size} of bodies whose every ledger identity carries no real signature."""
    import build
    import eligibility

    by_rva = collections.defaultdict(list)
    for r in rows:
        if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x"):
            by_rva[int(r["target_rva"], 16)].append(r)

    def reliable(r):
        return not (PLACEHOLDER.match(r["name"]) or r["source"].startswith("game/gen_")
                    or r["source"].endswith((".asm", ".s")) or build.is_scaffold_row(r)
                    or eligibility.is_lift_row(r))
    return by_rva, {rva: int(rs[0]["target_size"] or 0) for rva, rs in by_rva.items()
                    if not any(reliable(r) for r in rs)}


def open_callers(rows):
    """(rva, size) of every body a seat may be writing: open dumps, lifts, stashes."""
    import eligibility
    import lift_lane

    latest = eligibility.latest_verdicts()
    out = {(eligibility.rva_of(r), int(r["target_size"])) for r in eligibility.open_dumps(rows, latest)}
    sized = {int(r["target_rva"], 16): int(r["target_size"] or 0) for r in rows
             if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")}
    for name, rva_text in lift_lane.lift_rows(rows):
        rva = int(rva_text, 16)
        out.add((rva, sized.get(rva, 0)))
    for path in (ROOT / "targets/game/reverse/attempts").glob("0x*.cpp"):
        rva = int(path.stem, 16)
        if sized.get(rva):
            out.add((rva, sized[rva]))
    return sorted(x for x in out if x[1])


def targets(rows):
    """{callee rva: ledger size or 0} for unsigned callees of open work."""
    import callees

    by_rva, unsigned = unreliable_rows(rows)
    found = {}
    for rva, size in open_callers(rows):
        try:
            called = callees.call_targets(rva, size)
        except Exception:                             # noqa: BLE001 -- a bad extent
            continue
        for target in called:
            body = thunk_target(target)
            if body in unsigned or body not in by_rva:
                found[body] = unsigned.get(body, 0)
    return found


def judge(rva, size, url=None, ghidra=""):
    if url and not ghidra:
        try:
            ghidra = ghidra_signature(url, rva)
            size = size or ghidra_size(url, rva)
        except OSError:
            pass
    rets, ecx = body_evidence(rva, size) if size else ([], "none")
    sites = call_sites().get(rva, [])
    cleanups, eax_used, eax_decoded, ecx_set, ecx_decided = [], 0, 0, 0, 0
    for site in sites:
        sets = caller_sets_ecx(site)
        if sets is not None:
            ecx_decided += 1
            ecx_set += sets
        popped, eax = site_evidence(site)
        if popped:
            cleanups.append(popped)
        if eax is not None:
            eax_decoded += 1
            eax_used += bool(eax)
    counted = collections.Counter(cleanups)
    return {"target_rva": f"0x{rva:08X}", "size": size or "",
            "ret_bytes": " ".join(str(r) for r in rets), "ecx": ecx, "sites": len(sites),
            "cleanup": " ".join(f"{n}:{c}" for n, c in sorted(counted.items())),
            "ecx_set": f"{ecx_set}/{ecx_decided}", "eax_used": f"{eax_used}/{eax_decoded}",
            "ghidra": ghidra,
            "contract": contract(rets, ecx, cleanups, eax_used, eax_decoded, ghidra, ecx_set, ecx_decided,
                                 len(sites))}


# -------------------------------------------------------------- readers

@lru_cache(maxsize=1)
def load(path=None):
    """{rva: row} from the tracked CSV; {} when it has not been generated."""
    path = Path(path or OUT)
    if not path.exists():
        return {}
    with path.open(newline="", encoding="utf-8") as handle:
        return {int(r["target_rva"], 16): r for r in csv.DictReader(handle)}


def describe(rva):
    """Short contract line for a callee, or None when nothing was inferred."""
    row = load().get(rva)
    if not row:
        return None
    ghidra = row["ghidra"] if len(row["ghidra"]) <= 110 else row["ghidra"][:107] + "..."
    return f"inferred ABI: {row['contract']}" + (f" | ghidra: {ghidra}" if ghidra else "")


# ------------------------------------------------------------- calibration

def declared(name):
    """(convention, stack slots, returns value) from a decorated name, or None."""
    import audit_ret_arity as A
    import lift_arity

    slots = lift_arity.declared_slots(name)
    if slots is None:
        return None
    _, convention = A.expected_ret(name)
    if convention is None:
        return None
    m = re.search(r"@@([A-Z])", name)
    lead = m.group(1)
    pos = m.end() if (lead == "Y" or lead in A.STATIC_MEMBER) else m.end() + 1
    if re.match(r"\?\?[01]", name):
        return None                                    # ctor/dtor: no return type
    returns = name[pos + 1:pos + 2] != "X"
    return convention, slots, returns


def calibrate(rows, count):
    import random
    import eligibility

    landed = [r for r in rows if r.get("status") == "matched"
              and (r.get("target_rva") or "").startswith("0x")
              and r.get("source", "").endswith(".cpp") and not r["source"].startswith("game/gen_")
              and not eligibility.is_dump_row(r) and declared(r["name"]) is not None]
    random.seed(11)
    sample = random.sample(landed, min(count, len(landed)))
    tally = collections.Counter()
    misses, result_misses, slot_misses = [], [], []
    for r in sample:
        want = declared(r["name"])
        got = judge(int(r["target_rva"], 16), int(r["target_size"] or 0))["contract"]
        conv, slots, returns = want
        slot_m = re.search(r"(\d+) stack slot", got)
        tally["judged"] += 1
        if got.startswith(conv + ","):
            tally["convention"] += 1
        elif "(or a __thiscall" in got:
            tally["ambiguous"] += 1
        elif got.startswith(("__thiscall", "__stdcall", "__cdecl")):
            misses.append((r["name"], r["target_rva"], got))
        if slot_m and int(slot_m.group(1)) != slots:
            slot_misses.append((r["name"], r["target_rva"], got))
        if "returns a value" in got and not returns:
            result_misses.append((r["name"], r["target_rva"], got))
        if slot_m and int(slot_m.group(1)) == slots:
            tally["slots"] += 1
        if slot_m:
            tally["slots_decided"] += 1
        if "returns a value" in got or "result unused" in got:
            tally["result_decided"] += 1
            tally["result"] += ("returns a value" in got) == returns
    n = tally["judged"]
    print(f"calibration on {n} landed rows: convention {tally['convention']}/{n} right, "
          f"{tally['ambiguous']} honestly ambiguous, {len(misses)} wrong; "
          f"slots {tally['slots']}/{tally['slots_decided']} decided, "
          f"result {tally['result']}/{tally['result_decided']} decided")
    for name, rva, got in misses[:12]:
        print(f"  convention miss {rva} {name[:60]}: {got}")
    for name, rva, got in slot_misses[:8]:
        print(f"  slot miss {rva} {name[:60]}: {got}")
    for name, rva, got in result_misses[:6]:
        print(f"  declared void, eax read {rva} {name[:60]}: {got}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--url", default="http://127.0.0.1:8081/query")
    ap.add_argument("--no-ghidra", action="store_true")
    ap.add_argument("--calibrate", type=int, default=0)
    ap.add_argument("--rva", nargs="*", help="judge these callees and print, write nothing")
    args = ap.parse_args(argv)

    import eligibility

    url = None if args.no_ghidra else args.url
    if url:
        try:
            urllib.request.urlopen(urllib.request.Request(url, data=b"SELECT 1;", method="POST"), timeout=10)
        except OSError as error:
            raise SystemExit(f"callee_protos: no GhidraSQL server at {url} ({error}); "
                             "start tools/ghidrasql_serve.cmd or pass --no-ghidra")
    rows = eligibility.load_rows()
    if args.rva:
        by_rva, _ = unreliable_rows(rows)
        for text in args.rva:
            rva = thunk_target(int(text, 16))
            size = int(by_rva[rva][0]["target_size"] or 0) if rva in by_rva else 0
            row = judge(rva, size, url)
            print(f"0x{rva:08X}: {row['contract']}\n  ret={row['ret_bytes'] or '-'} ecx={row['ecx']} "
                  f"sites={row['sites']} cleanup={row['cleanup'] or '-'} ecx_set={row['ecx_set']} eax={row['eax_used']}\n"
                  f"  ghidra: {row['ghidra'] or '-'}")
        return 0
    if args.calibrate:
        calibrate(rows, args.calibrate)
        return 0
    found = targets(rows)
    prior = load()                                   # decompiling is the slow part: reuse it
    out = []
    for n, (rva, size) in enumerate(sorted(found.items())):
        known = prior.get(rva, {})
        out.append(judge(rva, size or int(known.get("size") or 0), url, known.get("ghidra", "")))
        if n % 200 == 0:
            print(f"  {n}/{len(found)}", file=sys.stderr, flush=True)
    with OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(out)
    print(f"callee_protos: {len(out)} unsigned callees of open work -> "
          f"{OUT.relative_to(ROOT).as_posix()}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
