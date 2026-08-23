#!/usr/bin/env python3
"""Build the real overlay and check the emitted code; needs MSVC 7.1 + capstone.

test_cave.py covers the cave mechanics with synthetic payloads. This covers the
feature itself, where the source reads correctly and only the emitted bytes give
it away. Every assertion below is a bug that actually shipped into a build:

  * the payload's exit fell straight into the helper functions emitted after it,
    because modbuild appends the relocated prologue after the WHOLE blob. The
    shim cave.py now generates cannot do that -- there is nothing after it but
    the prologue -- so what is asserted is the shape that makes it impossible;
  * fputs(str, FILE*) takes the string first, unlike fprintf(FILE*, fmt, ...).
    Copying fprintf's push order handed the FILE* over as the string and the
    game raised EXCEPTION_INVALID_HANDLE mid-match;
  * the leave payload's gate. The leave entry it hooks fires on a departure from
    a finished match as well as on a quit, so the gate has to be
    VictoryConditions' end frame. Anything that only says "a match was in
    progress" -- a started latch, or the network status, which is still 1 on the
    score screen -- reads correctly in the source and appends a spurious `leave`
    line to the file of every player who finishes a match;
  * `--probe` passed doing nothing after a rewrite dropped its guard. A flag
    with no assertion behind it looks like a working one.

Since the payloads became C++, two more things are worth holding: the record
formats, which downstream data is keyed on, and the absence of any runtime
library -- there is no CRT behind this code, so a compiler-emitted `_memset` or
`__chkstk` is an unresolvable symbol rather than a helper.
"""
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
SOURCE = ROOT / "overlay/features/020-gameresult/src/gameresult.cpp"
UPDATE = 0x0035F920      # VictoryConditions::update
SENDLEAVE = 0x00665C10   # ConnectionManager::sendPlayerLeaveCommands

# How many bytes of prologue each detour steals -- whole instructions covering a
# 5-byte jmp. A blob's end is findable from it: the relocated copy is followed
# by a jump back to exactly this address.
STOLEN = {UPDATE: 7, SENDLEAVE: 7}

VC71 = (ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
        / "Vc7/bin/cl.exe")

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present"),
    pytest.mark.skipif(shutil.which("wine") is None, reason="wine not installed"),
]
capstone = pytest.importorskip("capstone")

import modbuild  # noqa: E402
from cave import PE  # noqa: E402

IAT_FPUTS = 0x013593C8
VICTORY_CONDITIONS = 0x012F079C   # TheVictoryConditions
VC_LOCALSLOT = 0x94               # < 0 when this machine has no seat
VC_ENDFRAME = 0x98                # non-zero once the match resolved on this machine

# The shape every downstream reader of GameResult.jsonl is keyed on. These are
# not "the strings the source happens to hold" -- reverse/game_end/measured.jsonl
# was recorded through them, and test_game_records.py reads that file by these
# field names.
RECORD_FORMATS = [
    '{"ev":"start","t":%d,"slot":%d}\n',
    '{"ev":"leave","t":%d,"slot":%d,"frame":%d}\n',
    '{"ev":"end","t":%d,"slot":%d,"frame":%d,"result":"%s","observer":%d,'
    '"desync":%d,"slots":[',
    '{"leave":%d,"leaveFrame":%d,"defeatFrame":%d,"slotIndex":%d,"namePtr":%d,'
    '"name":"%s"}',
    '],"players":[',
    '{"player":%d,"defeated":%d,"teamWon":%d}',
    ']}\n',
    "victory",
    "defeat",
    "undecided",
    "BFME_RESULT_PATH",
    "APPDATA",
    "%s\\My Battle for Middle-earth Files\\GameResult.jsonl",
]


def _md():
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


def _build(*args):
    out = Path(tempfile.mkdtemp()) / "overlay.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"), "-o", str(out), *args],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    return PE(out)


def _shim(pe, md, target):
    """One detour's cave blob: (landing rva, instructions).

    Bounded by the jump back rather than by a fixed length, so a second blob
    laid down after the first is never read as part of it."""
    disp = struct.unpack_from("<i", pe.read(target + 1, 4))[0]
    start = target + 5 + disp
    out = []
    for ins in md.disasm(pe.read(start, 4096), pe.image_base + start):
        out.append(ins)
        if (ins.mnemonic == "jmp" and ins.op_str.startswith("0x")
                and int(ins.op_str, 16) - pe.image_base == target + STOLEN[target]):
            return start, out
    raise AssertionError(f"the detour at 0x{target:08X} never jumps back to its target")


def _body(pe, md, entry_va):
    """One compiled function, bounded by the first `ret` or tail `jmp` that
    nothing branches past -- which is what /O1 emits for a single-exit body."""
    out, furthest = [], 0
    for ins in md.disasm(pe.read(entry_va - pe.image_base, 4096), entry_va):
        out.append(ins)
        if ins.mnemonic in ("ret", "jmp") and ins.address >= furthest:
            break
        if ins.mnemonic.startswith("j") and ins.op_str.startswith("0x"):
            furthest = max(furthest, int(ins.op_str, 16))
    return out


def _reachable(pe, md, entry_va):
    """Every instruction a payload entered at `entry_va` can execute.

    A C++ payload is a call graph, not one straight run: the end record's two
    arrays and the file helpers are separate functions, and /O1 reaches some of
    them by tail jump. Assertions about what a payload does have to follow it."""
    cave = next(s for s in pe.sections() if s["name"] == ".bfmemod")
    inside = range(pe.image_base + cave["vaddr"], pe.image_base + cave["vaddr"] + cave["vsize"])
    todo, seen, out = [entry_va], set(), []
    while todo:
        va = todo.pop()
        if va in seen:
            continue
        seen.add(va)
        body = _body(pe, md, va)
        out += body
        for ins in body:
            if ins.mnemonic in ("call", "jmp") and ins.op_str.startswith("0x"):
                target = int(ins.op_str, 16)
                if target in inside:
                    todo.append(target)
    return out


@pytest.fixture(scope="module")
def built():
    pe, md = _build(), _md()
    return pe, {target: _shim(pe, md, target) for target in STOLEN}


@pytest.fixture(scope="module")
def payloads(built):
    """Each detour's reachable C++, found by following the shim's call."""
    pe, shims = built
    md = _md()
    out = {}
    for target, (_, ins) in shims.items():
        call = next(i for i in ins if i.mnemonic == "call")
        out[target] = _reachable(pe, md, int(call.op_str, 16))
    return out


@pytest.fixture(params=sorted(STOLEN), ids=lambda t: f"0x{t:08X}")
def detour(request, built):
    """Each detour in turn: (pe, target rva, landing rva, shim instructions)."""
    pe, shims = built
    start, ins = shims[request.param]
    return pe, request.param, start, ins


def test_the_shim_preserves_every_register_and_flag(detour):
    """The stolen prologue runs straight after the shim, so everything has to
    come back untouched -- the direction flag included, because a compiled
    struct copy is an inline `rep movsd` that reads it and never sets it."""
    _, _, _, ins = detour
    assert [i.mnemonic for i in ins[:4]] == ["pushal", "pushfd", "cld", "push"]
    assert ins[3].op_str == "ecx", "the payload's `this` is the ecx it was called with"
    call = next(n for n, i in enumerate(ins) if i.mnemonic == "call")
    assert [i.mnemonic for i in ins[call + 1:call + 4]] == ["add", "popfd", "popal"]
    assert ins[call + 1].op_str == "esp, 4", "cdecl: the shim pops the argument it pushed"


def test_the_shim_returns_into_the_relocated_prologue(detour):
    """There is nothing between the shim's exit and the replayed prologue. That
    is the point: the hand-written payloads it replaced emitted their helper
    functions there and had to jump over them, and one of them did not."""
    pe, target, _, ins = detour
    k = next(n for n, i in enumerate(ins) if i.mnemonic == "popal")
    assert ins[k - 1].mnemonic == "popfd"
    prologue = ins[k + 1]
    assert prologue.address - pe.image_base == ins[-1].address - pe.image_base - STOLEN[target], \
        "the instruction after the shim should be the replayed original prologue"
    assert ins[-1].mnemonic == "jmp", \
        "and the replayed prologue should end in the jump back"


def test_the_stolen_prologue_is_replayed_byte_for_byte(detour):
    """Neither prologue holds a relative operand, so relocation is the identity.
    Asserting that pins _relocate against the retail bytes rather than against
    its own output: a mangled displacement would land the game mid-instruction."""
    pe, target, _, ins = detour
    landing = ins[-1].address - pe.image_base - STOLEN[target]
    assert pe.read(landing, STOLEN[target]) == PE(EXE).read(target, STOLEN[target]), \
        f"the prologue replayed for 0x{target:08X} is not the retail one"


def test_each_shim_holds_exactly_one_entry_sequence(built):
    """The two shims sit in one cave, so a reader that does not stop at the jump
    back runs straight out of the first and into the second -- and then every
    assertion below is really about whichever one reached the check first."""
    pe, shims = built
    spans = []
    for target, (start, ins) in sorted(shims.items()):
        entries = [i.address - pe.image_base for i in ins if i.mnemonic == "pushal"]
        assert entries == [start], (
            f"the shim for 0x{target:08X} holds {len(entries)} entries, "
            f"not just its own at 0x{start:08X}")
        spans.append((start, ins[-1].address - pe.image_base + ins[-1].size))
    spans.sort()
    for (_, end), (nxt, _) in zip(spans, spans[1:]):
        assert end <= nxt, f"a shim ending at 0x{end:08X} runs into one at 0x{nxt:08X}"


def test_the_leave_payload_gates_on_the_end_frame(payloads):
    """The leave entry fires on a departure from a FINISHED match too -- it was
    measured firing on all three survivors of a 2v2, twenty-six frames after
    they wrote their end record. So the gate has to be VictoryConditions' own
    end frame, which is non-zero exactly when this machine has already seen the
    match resolve. Nothing may be written before it is read."""
    ins = payloads[SENDLEAVE]
    read = next((n for n, i in enumerate(ins)
                 if i.mnemonic == "mov" and hex(VICTORY_CONDITIONS) in i.op_str), None)
    assert read is not None, "the leave payload never reads TheVictoryConditions"
    gate = next((n for n, i in enumerate(ins[read:], start=read)
                 if i.mnemonic == "cmp" and i.op_str.endswith(f"+ 0x{VC_ENDFRAME:x}], 0")), None)
    assert gate is not None, (
        "the leave payload never compares VictoryConditions+0x98 against 0: it is "
        "gated on something that does not distinguish a quit from leaving a score "
        "screen")
    calls = [n for n, i in enumerate(ins) if i.mnemonic == "call"]
    assert calls and gate < calls[0], \
        "the payload calls out before it has decided the match is still running"


def test_fputs_receives_the_string_first(payloads):
    """fputs(str, FILE*): the stream is arg2, so it is pushed FIRST. Reusing
    fprintf's order passes the FILE* as the string -- an invalid handle."""
    for ins in payloads.values():
        for n, i in enumerate(ins):
            if i.mnemonic != "call" or hex(IAT_FPUTS) not in i.op_str:
                continue
            first, second = ins[n - 2], ins[n - 1]
            assert first.mnemonic == "push" and second.mnemonic == "push"
            # pushed last == arg1 == the string, an immediate cave address
            assert second.op_str.startswith("0x"), \
                f"fputs at 0x{i.address:X}: arg1 should be the string constant"
            # pushed first == arg2 == the FILE*, which is never a constant
            assert not first.op_str.startswith("0x"), \
                f"fputs at 0x{i.address:X}: arg2 should be the FILE* variable"


def test_the_update_payload_is_the_one_that_calls_fputs(payloads):
    """Which is what makes the assertion above a check rather than a no-op: the
    end record is built out of fputs, the leave record is a single fprintf."""
    calls = {target: sum(1 for i in ins
                         if i.mnemonic == "call" and hex(IAT_FPUTS) in i.op_str)
             for target, ins in payloads.items()}
    assert calls[UPDATE] > 0 and calls[SENDLEAVE] == 0, calls


def test_the_record_formats_are_the_measured_ones(built):
    """reverse/game_end/measured.jsonl was recorded through these exact strings
    and test_game_records.py reads it by these field names. A rewrite that
    renames a field or drops a `\\n` produces a file no reader can join."""
    pe, _ = built
    cave = next(s for s in pe.sections() if s["name"] == ".bfmemod")
    blob = pe.read(cave["vaddr"], cave["vsize"])
    for text in RECORD_FORMATS:
        assert blob.count(text.encode() + b"\0") == 1, \
            f"the cave does not hold exactly one {text!r}"


def test_probe_builds_take_the_end_path_as_soon_as_a_slot_exists():
    """--probe exists so struct layouts can be read off a live game without
    playing a match to its finish, and a flag with no assertion behind it looks
    like a working one: this one once passed doing nothing at all. A probe build
    must gate on the local slot where a shipping build gates on the end frame."""
    md = _md()
    gates = {}
    for label, args in (("ship", ()), ("probe", ("--probe",))):
        pe = _build(*args)
        _, ins = _shim(pe, md, UPDATE)
        call = next(i for i in ins if i.mnemonic == "call")
        entry = _body(pe, md, int(call.op_str, 16))
        gates[label] = {offset for offset in (VC_LOCALSLOT, VC_ENDFRAME)
                        for i in entry[:6] if f"+ 0x{offset:x}]" in i.op_str}
    assert gates["ship"] == {VC_ENDFRAME}, \
        f"a shipping build must reach the end path only on the end frame: {gates}"
    assert gates["probe"] == {VC_LOCALSLOT}, \
        f"--probe built the shipping payload, so the flag does nothing: {gates}"


def test_two_builds_of_one_source_are_the_same_bytes():
    """overlay/dist/lotrbfme.exe is committed and its sha256 is recorded beside
    it, so a rebuild that moves a byte for no reason says the payload changed
    when nothing did. link.exe stamps the export directory with the current
    time, which is exactly that."""
    first, second = _build(), _build()
    assert first.data == second.data, \
        "the overlay build is not reproducible: something in it carries a clock"


def test_the_payload_needs_no_runtime_library():
    """There is no CRT and no loader behind this code, so a compiler-emitted
    helper -- _memset for an aggregate, __chkstk for a big frame, __alldiv for
    64-bit arithmetic -- is a symbol nothing can ever resolve."""
    with tempfile.TemporaryDirectory() as tmp:
        obj = modbuild.compile_payload(SOURCE, Path(tmp) / "gameresult.obj")
        assert modbuild.undefined_externals(obj) == []


def test_a_compiler_emitted_crt_helper_fails_the_build():
    """And that check is a check: the same compile of a payload that does need
    one has to stop the build, naming the symbol and what asks for it."""
    with tempfile.TemporaryDirectory() as tmp:
        source = Path(tmp) / "greedy.cpp"
        source.write_text('extern "C" __declspec(dllexport) void __cdecl f(char **out)\n'
                          "{ char frame[9000]; frame[0] = 1; *out = frame; }\n")
        with pytest.raises(SystemExit, match=r"__chkstk"):
            modbuild.compile_payload(source, Path(tmp) / "greedy.obj")


def test_cave_section_present_and_baseline_untouched(built):
    pe, _ = built
    cave = [s for s in pe.sections() if s["name"] == ".bfmemod"]
    assert len(cave) == 1 and cave[0]["chars"] & 0x20000000
    assert PE(EXE).data == bytearray(EXE.read_bytes()), \
        "building the overlay must never write to the byte-exact baseline"
