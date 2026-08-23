#!/usr/bin/env python3
"""Assemble the real overlay and check the emitted code; needs yasm + capstone.

test_cave.py covers the cave mechanics with synthetic payloads. This covers the
two bugs that lived in the feature's own assembly, where the source read
correctly and only the emitted bytes gave them away:

  * the payload's `.done` did popfd/popad and then fell straight into the helper
    functions emitted after it, because modbuild appends the relocated prologue
    after the WHOLE blob -- so the exit has to jump past the helpers, not run
    off the end of its own code;
  * fputs(str, FILE*) takes the string first, unlike fprintf(FILE*, fmt, ...).
    Copying fprintf's push order handed the FILE* over as the string and the
    game raised EXCEPTION_INVALID_HANDLE mid-match.

Neither is visible without disassembling what was actually built.
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
UPDATE = 0x0035F920

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(shutil.which("yasm") is None, reason="yasm not installed"),
]
capstone = pytest.importorskip("capstone")

from cave import PE  # noqa: E402

IAT_FPUTS = 0x013593C8
IAT_FPRINTF = 0x013593C0


@pytest.fixture(scope="module")
def built():
    out = Path(tempfile.mkdtemp()) / "overlay.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"), "-o", str(out)],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    pe = PE(out)
    disp = struct.unpack_from("<i", pe.read(UPDATE + 1, 4))[0]
    start = UPDATE + 5 + disp
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ins = list(md.disasm(pe.read(start, 4096), pe.image_base + start))
    return pe, start, ins


def test_entry_preserves_everything(built):
    """The stolen prologue runs straight after the payload, so every register
    and flag has to come back untouched."""
    _, _, ins = built
    assert [i.mnemonic for i in ins[:2]] == ["pushal", "pushfd"]


def test_exit_jumps_past_the_helpers_to_the_relocated_prologue(built):
    """popfd/popad must be followed by a jump, not by falling into whatever the
    assembler emitted next -- which is the helper functions."""
    pe, start, ins = built
    k = next(n for n, i in enumerate(ins) if i.mnemonic == "popal")
    assert ins[k - 1].mnemonic == "popfd"
    exit_jmp = ins[k + 1]
    assert exit_jmp.mnemonic == "jmp", \
        "the payload exit falls through instead of jumping past its helpers"

    landing = int(exit_jmp.op_str, 16) - pe.image_base
    tail = [i for i in ins if i.address - pe.image_base >= landing][:3]
    assert [t.mnemonic for t in tail[:2]] == ["push", "push"], \
        "the exit should land on the replayed original prologue"
    assert tail[2].mnemonic == "jmp"
    assert int(tail[2].op_str, 16) - pe.image_base == UPDATE + 7, \
        "and then return just past the bytes the trampoline overwrote"


def test_fputs_receives_the_string_first(built):
    """fputs(str, FILE*): the stream is arg2, so it is pushed FIRST. Reusing
    fprintf's order passes the FILE* as the string -- an invalid handle."""
    pe, _, ins = built
    calls = [n for n, i in enumerate(ins)
             if i.mnemonic == "call" and hex(IAT_FPUTS) in i.op_str]
    assert calls, "the payload should call fputs"
    for n in calls:
        first, second = ins[n - 2], ins[n - 1]
        assert first.mnemonic == "push" and second.mnemonic == "push"
        # pushed first  == arg2 == the FILE*, read from the data area
        assert first.op_str.startswith("dword ptr ["), \
            f"fputs at 0x{ins[n].address:X}: arg2 should be the FILE* variable"
        # pushed second == arg1 == the string, an immediate cave address
        assert second.op_str.startswith("0x"), \
            f"fputs at 0x{ins[n].address:X}: arg1 should be the string constant"


def test_every_cdecl_call_cleans_up_after_itself(built):
    """Every CRT call is cdecl: the caller pops. A forgotten `add esp, N` leaves
    the varargs on the stack, and the stolen prologue then runs on a frame that
    has silently drifted.

    Counting the matching pushes is deliberately NOT attempted -- helper calls
    sit between pushes (`push slot / call now / push eax / ...`), so any linear
    backward scan miscounts. What is checkable without dataflow is that the
    cleanup exists and is a sane multiple of four."""
    _, _, ins = built
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
    pe, _, _ = built
    cave = [s for s in pe.sections() if s["name"] == ".bfmemod"]
    assert len(cave) == 1 and cave[0]["chars"] & 0x20000000
    assert PE(EXE).data == bytearray(EXE.read_bytes()), \
        "building the overlay must never write to the byte-exact baseline"
