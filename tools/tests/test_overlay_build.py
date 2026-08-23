#!/usr/bin/env python3
"""Assemble the real overlay and check the emitted code; needs yasm + capstone.

test_cave.py covers the cave mechanics with synthetic payloads. This covers the
bugs that lived in the feature's own assembly, where the source read correctly
and only the emitted bytes gave them away:

  * the payload's `.done` did popfd/popad and then fell straight into the helper
    functions emitted after it, because modbuild appends the relocated prologue
    after the WHOLE blob -- so the exit has to jump past the helpers, not run
    off the end of its own code;
  * fputs(str, FILE*) takes the string first, unlike fprintf(FILE*, fmt, ...).
    Copying fprintf's push order handed the FILE* over as the string and the
    game raised EXCEPTION_INVALID_HANDLE mid-match;
  * the leave payload's gate. The leave entry it hooks fires on a departure
    from a finished match as well as on a quit, so the gate has to be
    VictoryConditions' end frame. Anything that only says "a match was in
    progress" -- a d_started latch, or the network status, which is still 1 on
    the score screen -- reads correctly in the source and appends a spurious
    `leave` line to the file of every player who finishes a match.

None of these is visible without disassembling what was actually built.
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
UPDATE = 0x0035F920      # VictoryConditions::update
SENDLEAVE = 0x00665C10   # ConnectionManager::sendPlayerLeaveCommands

# How many bytes of prologue each detour steals -- whole instructions covering a
# 5-byte jmp. A blob's end is findable from it: the relocated copy is followed
# by a jump back to exactly this address.
STOLEN = {UPDATE: 7, SENDLEAVE: 7}

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(shutil.which("yasm") is None, reason="yasm not installed"),
]
capstone = pytest.importorskip("capstone")

from cave import PE  # noqa: E402

IAT_FPUTS = 0x013593C8
IAT_FPRINTF = 0x013593C0
VICTORY_CONDITIONS = 0x012F079C   # TheVictoryConditions
VC_ENDFRAME = 0x98                # non-zero once the match resolved on this machine


def _blob(pe, md, target):
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


@pytest.fixture(scope="module")
def built():
    out = Path(tempfile.mkdtemp()) / "overlay.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"), "-o", str(out)],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    pe = PE(out)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return pe, {target: _blob(pe, md, target) for target in STOLEN}


@pytest.fixture(params=sorted(STOLEN), ids=lambda t: f"0x{t:08X}")
def detour(request, built):
    """Each detour in turn: (pe, target rva, landing rva, instructions)."""
    pe, blobs = built
    start, ins = blobs[request.param]
    return pe, request.param, start, ins


def test_entry_preserves_everything(detour):
    """The stolen prologue runs straight after the payload, so every register
    and flag has to come back untouched."""
    _, _, _, ins = detour
    assert [i.mnemonic for i in ins[:2]] == ["pushal", "pushfd"]


def test_exit_jumps_past_the_helpers_to_the_relocated_prologue(detour):
    """popfd/popad must be followed by a jump, not by falling into whatever the
    assembler emitted next -- which is the helper functions."""
    pe, target, _, ins = detour
    k = next(n for n, i in enumerate(ins) if i.mnemonic == "popal")
    assert ins[k - 1].mnemonic == "popfd"
    exit_jmp = ins[k + 1]
    assert exit_jmp.mnemonic == "jmp", \
        "the payload exit falls through instead of jumping past its helpers"

    landing = int(exit_jmp.op_str, 16) - pe.image_base
    assert landing == ins[-1].address - pe.image_base - STOLEN[target], \
        "the exit should land on the replayed original prologue"
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


def test_each_blob_holds_exactly_one_payload(built):
    """The two blobs sit back to back in one cave, so a reader that does not
    stop at the jump back runs straight out of the first payload and into the
    second -- and then every assertion below is really about whichever payload
    happened to reach the check first. Exactly one entry sequence per span is
    what says the two were actually separated.

    (They cannot overlap: the cave is bump-allocated and detour() takes its
    landing address from the same cursor it then allocates at. What can go wrong
    is a payload assembled against an org it is not placed at, and modbuild
    makes that a build error rather than a test.)"""
    pe, blobs = built
    spans = []
    for target, (start, ins) in sorted(blobs.items()):
        entries = [i.address - pe.image_base for i in ins if i.mnemonic == "pushal"]
        assert entries == [start], (
            f"the blob for 0x{target:08X} holds {len(entries)} payload entries, "
            f"not just its own at 0x{start:08X}")
        spans.append((start, ins[-1].address - pe.image_base + ins[-1].size))
    spans.sort()
    for (_, end), (nxt, _) in zip(spans, spans[1:]):
        assert end <= nxt, f"a blob ending at 0x{end:08X} runs into one at 0x{nxt:08X}"


def test_the_leave_payload_gates_on_the_end_frame(built):
    """The leave entry fires on a departure from a FINISHED match too -- it was
    measured firing on all three survivors of a 2v2, twenty-six frames after
    they wrote their end record. So the gate has to be VictoryConditions' own
    end frame, which is non-zero exactly when this machine has already seen the
    match resolve. Nothing may be written before it is read."""
    pe, blobs = built
    _, ins = blobs[SENDLEAVE]
    read = next((n for n, i in enumerate(ins)
                 if i.mnemonic == "mov" and hex(VICTORY_CONDITIONS) in i.op_str), None)
    assert read is not None, \
        "the leave payload never reads TheVictoryConditions"
    gate = next((n for n, i in enumerate(ins[read:], start=read)
                 if i.mnemonic == "cmp" and i.op_str.endswith(f"+ 0x{VC_ENDFRAME:x}], 0")), None)
    assert gate is not None, (
        "the leave payload never compares VictoryConditions+0x98 against 0: it is "
        "gated on something that does not distinguish a quit from leaving a score "
        "screen")
    calls = [n for n, i in enumerate(ins) if i.mnemonic == "call"]
    assert calls and gate < calls[0], \
        "the payload calls out before it has decided the match is still running"


def test_fputs_receives_the_string_first(detour):
    """fputs(str, FILE*): the stream is arg2, so it is pushed FIRST. Reusing
    fprintf's order passes the FILE* as the string -- an invalid handle."""
    _, _, _, ins = detour
    calls = [n for n, i in enumerate(ins)
             if i.mnemonic == "call" and hex(IAT_FPUTS) in i.op_str]
    for n in calls:
        first, second = ins[n - 2], ins[n - 1]
        assert first.mnemonic == "push" and second.mnemonic == "push"
        # pushed first  == arg2 == the FILE*, read from the data area
        assert first.op_str.startswith("dword ptr ["), \
            f"fputs at 0x{ins[n].address:X}: arg2 should be the FILE* variable"
        # pushed second == arg1 == the string, an immediate cave address
        assert second.op_str.startswith("0x"), \
            f"fputs at 0x{ins[n].address:X}: arg1 should be the string constant"


def test_the_update_payload_is_the_one_that_calls_fputs(built):
    """Which is what makes the assertion above a check rather than a no-op: the
    end record is built out of fputs, the leave record is a single fprintf."""
    _, blobs = built
    calls = {target: sum(1 for i in ins if i.mnemonic == "call" and hex(IAT_FPUTS) in i.op_str)
             for target, (_, ins) in blobs.items()}
    assert calls[UPDATE] > 0 and calls[SENDLEAVE] == 0, calls


def test_every_cdecl_call_cleans_up_after_itself(detour):
    """Every CRT call is cdecl: the caller pops. A forgotten `add esp, N` leaves
    the varargs on the stack, and the stolen prologue then runs on a frame that
    has silently drifted.

    Counting the matching pushes is deliberately NOT attempted -- helper calls
    sit between pushes (`push slot / call now / push eax / ...`), so any linear
    backward scan miscounts. What is checkable without dataflow is that the
    cleanup exists and is a sane multiple of four."""
    _, _, _, ins = detour
    calls = [(n, i) for n, i in enumerate(ins)
             if i.mnemonic == "call" and "dword ptr [0x135" in i.op_str]
    assert calls, "the payload should call into the IAT"
    for n, i in calls:
        nxt = ins[n + 1]
        assert nxt.mnemonic == "add" and nxt.op_str.startswith("esp,"), (
            f"cdecl call at 0x{i.address:X} is not followed by a stack cleanup")
        popped = int(nxt.op_str.split(",")[1].strip(), 0)
        assert popped % 4 == 0 and 0 < popped <= 64, (
            f"call at 0x{i.address:X} pops an implausible {popped} bytes")


def test_cave_section_present_and_baseline_untouched(built):
    pe, _ = built
    cave = [s for s in pe.sections() if s["name"] == ".bfmemod"]
    assert len(cave) == 1 and cave[0]["chars"] & 0x20000000
    assert PE(EXE).data == bytearray(EXE.read_bytes()), \
        "building the overlay must never write to the byte-exact baseline"
