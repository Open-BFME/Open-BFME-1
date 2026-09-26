#!/usr/bin/env python3
"""Build the early-send fix and check it changed only what it claims to.

The constraint on this feature is not "does it work" -- the spike measures that
-- it is that it must not alter the pace of the game. The engine welds those
together: game time per logic frame is a compiled-in constant, so touching the
5 Hz quantum multiplies the speed of the game, and that is the failure this
project has been burned by before. So the assertions here are mechanical rather
than behavioural:

  * the quantum, the frame-ceiling writers and GameLogic's own cadence are
    byte-identical to retail in the built image;
  * outside the appended cave, the ONLY bytes that differ from retail are the
    detour sites the build printed. A fix that is surgical in the source and
    broad in the image is broad;
  * the payload tail-calls the retail pump with the engine's own three guards,
    so it can only make an existing mechanism run more often.
"""
import struct
import subprocess
import sys
import shutil
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "inputs/baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
VC71 = (ROOT / "inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
        / "Vc7/bin/cl.exe")

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present"),
    pytest.mark.skipif(shutil.which("wine") is None, reason="wine not installed"),
]
capstone = pytest.importorskip("capstone")

from cave import PE  # noqa: E402

FEATURE = "031-earlysend"
TARGET = 0x0006BA44           # the client half's tail, before liteupdate(FALSE)
PUMP = 0x00A828D0             # Network::getCommandsFromCommandList, as a VA

# What the fix must leave exactly as retail left it. Each is a place where a
# change would alter the speed of the game rather than the latency of a command.
PACING = {
    0x00682074: "the 5 Hz quantum (push 5) -- game time per logic frame is "
                "compiled in, so raising this multiplies the speed of the game",
    0x00665E45: "sendFrameInfo's write of the frame ceiling",
    0x0066A4BE: "the client-side ceiling max()",
    0x0038DA10: "GameLogic::update's entry",
    0x00681F70: "getFrameAdvanceCount's entry",
}


@pytest.fixture(scope="module")
def built():
    out = Path(tempfile.mkdtemp()) / "fix.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "-o", str(out)],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    return PE(out), r.stdout


def test_the_hook_is_installed_and_replays_what_it_stole(built):
    pe, _ = built
    assert pe.read(TARGET, 1)[0] == 0xE9, "the client-half tail was not hooked"
    start = TARGET + 5 + struct.unpack_from("<i", pe.read(TARGET + 1, 4))[0]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    ins = []
    for i in md.disasm(pe.read(start, 128), pe.image_base + start):
        ins.append(i)
        if i.mnemonic == "jmp" and i.op_str.startswith("0x"):
            break
    back = int(ins[-1].op_str, 16) - pe.image_base
    stolen = back - TARGET
    assert stolen == 6, "the displaced run is the six-byte mov ecx,[TheNetwork]"
    assert pe.read(TARGET + 5, 1) == b"\x90", "the sixth byte must be a NOP"
    popal = next(n for n, i in enumerate(ins) if i.mnemonic == "popal")
    replayed = b"".join(bytes(i.bytes) for i in ins[popal + 1:-1])
    assert replayed == PE(EXE).read(TARGET, stolen)


def test_the_payload_calls_the_retail_pump_behind_the_engine_s_own_guards(built):
    """It adds no mechanism: it makes the engine's own drain run on every engine
    tick instead of only on a 5 Hz logic tick, under the same three conditions
    the retail call site is guarded by."""
    pe, _ = built
    cave = next(s for s in pe.sections() if s["name"] == ".bfmemod")
    blob = bytes(pe.data[cave["raddr"]:cave["raddr"] + cave["rsize"]])
    assert struct.pack("<I", PUMP) in blob, "the payload never reaches the pump"
    assert struct.pack("<I", 0x012F7714) in blob, "the payload never reads TheNetwork"
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    text = " ".join(f"{i.mnemonic} {i.op_str}"
                    for i in md.disasm(blob, pe.image_base + cave["vaddr"]))
    assert "cmp dword ptr [ecx + 0xc], 1" in text, "the in-match gate is missing"
    assert "cmp dword ptr [ecx + 8], 0" in text, "the ConnectionManager gate is missing"


@pytest.mark.parametrize("rva", sorted(PACING))
def test_the_pacing_machinery_is_untouched(built, rva):
    """The pace of the game is not this feature's to change."""
    pe, _ = built
    assert pe.read(rva, 16) == PE(EXE).read(rva, 16), PACING[rva]


def test_nothing_outside_the_detour_site_is_modified(built):
    """Surgical in the source is not surgical in the image unless it is checked.
    Everything the build did is one trampoline plus an appended section."""
    pe, stdout = built
    retail = PE(EXE).data
    changed = [i for i in range(len(retail)) if pe.data[i] != retail[i]]
    header_end = pe.sect_table + pe.n_sections * 40
    trampoline = range(pe.rva_to_off(TARGET), pe.rva_to_off(TARGET) + 6)
    stray = [i for i in changed if i not in trampoline and i >= header_end]
    assert not stray, (f"{len(stray)} bytes changed outside the detour and the PE "
                       f"header, first at file offset 0x{stray[0]:X}")
    assert f"0x{TARGET:08X}" in stdout


def test_the_shipped_build_carries_it():
    """Every mod in the repo stacks into the one artifact players run. This one
    was held out only until its spike was green; the measurement instrument is
    the sole thing still excluded, because it writes tens of lines a second."""
    import modbuild  # noqa: E402  -- imported here so the module path is set up
    assert FEATURE in modbuild.FEATURES, "the fix is no longer in the shipped build"
    assert "030-netlatprobe" in modbuild.UNSHIPPED, "the instrument must stay out"
