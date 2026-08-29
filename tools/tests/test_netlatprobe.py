#!/usr/bin/env python3
"""Build the latency probe and check what it actually emitted.

The probe is an instrument: everything the network-delay spike concludes is
computed from the file it writes, so a fault here is not a broken feature but a
measurement that looks fine and says the wrong thing. What is asserted is what
disassembly, not the source, can settle:

  * four of the five hooks need the hooked function's OWN first argument -- the
    message being appended, sent or relayed. A thiscall's `this` arrives in ecx
    and its arguments do not, so the shim lifts one off the target's frame; the
    displacement that does it is arithmetic against an esp three things have
    moved, and if it is wrong the payload logs a plausible number read from the
    wrong dword;
  * the addresses the payload reads the engine through. A mistyped global is
    invisible in the source and produces a file full of -1s at best;
  * the record schema, which tools/netlat.py parses by name;
  * that a --dist build refuses to carry it. mods/dist is what every ladder
    player runs, and this writes tens of lines a second.
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

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
VC71 = (ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
        / "Vc7/bin/cl.exe")

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present"),
    pytest.mark.skipif(shutil.which("wine") is None, reason="wine not installed"),
]
capstone = pytest.importorskip("capstone")

from cave import PE  # noqa: E402

FEATURE = "030-netlatprobe"

# Hook -> (exported entry, whether the shim must lift the target's argument).
# Every one is hooked at the function's ENTRY, which is the only place
# "stack:0" means anything: the body has not pushed yet, so argument 0 is still
# one dword above the return address.
HOOKS = {
    0x0008A4E0: ("netlat_input", True),     # GameMessageList::appendMessage(msg)
    0x00664740: ("netlat_send", True),      # ConnectionManager::sendLocalCommand(msg)
    0x00663100: ("netlat_relay", True),     # ConnectionManager::relayCommand(ref)
    0x00682A90: ("netlat_frame", True),     # Network::relayCommandsToCommandList(frame)
    0x00665D10: ("netlat_ceiling", False),  # ConnectionManager::sendFrameInfo()
    0x0006BC2B: ("netlat_loop", False),     # GameEngine::execute loop body
    0x0006BAE0: ("netlat_driver", False),   # the frame driver entry
}

# The engine functions this payload CALLS. A mistyped one does not read a wrong
# number, it transfers control into the middle of an unrelated body -- and it is
# invisible in the source, because each is a cast integer literal.
CALLS = {
    0x00A633E0: "ConnectionManager::areFrameCommandsComplete",
    0x00A70780: "FrameDataManager::getFrameCommandCount",
    0x00A70720: "FrameDataManager::getCommandCount",
}

# The engine this payload reads, by absolute address. These are the values a
# typo destroys silently.
GLOBALS = {
    0x012F7714: "TheNetwork",
    0x012F0898: "TheGameLogic",
    0x01358EB4: "QueryPerformanceCounter's IAT slot",
    0x01358EB8: "QueryPerformanceFrequency's IAT slot",
}

# tools/netlat.py parses by these names; measured files are keyed on them.
SCHEMA = [
    '{"ev":"%s","qlo":%u,"qhi":%u,"f":%d,"c":%d,"slot":%d,"router":%d',
    ',"type":%u,"msg":%u,"list":%u,"owner":%u',
    ',"type":%u,"cmd":%u,"player":%u,"exec":%d',
    ',"type":%u,"cmd":%u,"player":%u,"exec":%d,"mask":%u',
    ',"exec":%d,"desync":%u,"stalls":%u,"loops":%u,"drivers":%u',
    '{"ev":"open","qfreqlo":%u,"qfreqhi":%u}\n',
    "BFME_LAT_PATH",
    "%s\\My Battle for Middle-earth Files\\NetLat.jsonl",
]


def _md():
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


@pytest.fixture(scope="module")
def built():
    out = Path(tempfile.mkdtemp()) / "netlat.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "-o", str(out)],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    return PE(out)


@pytest.fixture(scope="module")
def cave_bytes(built):
    s = next(x for x in built.sections() if x["name"] == ".bfmemod")
    return bytes(built.data[s["raddr"]:s["raddr"] + s["rsize"]])


def _shim(pe, target):
    """The detour's cave blob, bounded by its jump back to the target."""
    assert pe.read(target, 1)[0] == 0xE9, f"no detour installed at 0x{target:08X}"
    start = target + 5 + struct.unpack_from("<i", pe.read(target + 1, 4))[0]
    out = []
    for ins in _md().disasm(pe.read(start, 512), pe.image_base + start):
        out.append(ins)
        if ins.mnemonic == "jmp" and ins.op_str.startswith("0x"):
            return start, out, int(ins.op_str, 16) - pe.image_base
    raise AssertionError(f"the detour at 0x{target:08X} never jumps back")


@pytest.fixture(params=sorted(HOOKS), ids=lambda t: f"0x{t:08X}")
def detour(request, built):
    start, ins, back = _shim(built, request.param)
    return built, request.param, ins, back


def test_every_hook_is_detoured(built):
    for target in HOOKS:
        assert built.read(target, 1)[0] == 0xE9, f"0x{target:08X} was not hooked"


def test_the_detour_replays_the_prologue_it_stole(detour):
    """The target keeps running: the stolen bytes are re-emitted in the cave and
    control returns to the first instruction after them. A jump back anywhere
    else lands mid-instruction."""
    pe, target, ins, back = detour
    stolen = back - target
    assert stolen >= 5, "a jmp rel32 needs five bytes"
    # The padding after the trampoline must be NOPs, or the tail of a
    # half-overwritten instruction executes as garbage.
    assert pe.read(target + 5, stolen - 5) == b"\x90" * (stolen - 5)
    # Everything between the shim putting the machine back and the jump home is
    # the stolen run, re-emitted. None of these five prologues contains a
    # relative branch (cave.py refuses one it cannot rewrite), so the replay is
    # byte-for-byte what the target had.
    popal = next(n for n, i in enumerate(ins) if i.mnemonic == "popal")
    replayed = b"".join(bytes(i.bytes) for i in ins[popal + 1:-1])
    assert replayed == PE(EXE).read(target, stolen), \
        f"0x{target:08X}: the replayed prologue is not what was stolen"


def test_the_shim_hands_over_the_target_s_own_argument(detour):
    """`this` is in ecx, but the message being appended/sent/relayed is on the
    target's stack. At the hook nothing has been pushed yet, so argument 0 sits
    at entry_esp+4 -- and the shim reaches it across pushad (32) plus pushfd (4)
    plus whatever it has pushed itself."""
    pe, target, ins, _ = detour
    _, wants_arg = HOOKS[target]
    assert [i.mnemonic for i in ins[:3]] == ["pushal", "pushfd", "cld"]
    pushes = [i for i in ins[3:] if i.mnemonic == "push"]
    stack = [i for i in pushes if i.op_str.startswith("dword ptr [esp")]
    if not wants_arg:
        assert not stack, "this hook takes no argument of its own"
        return
    assert len(stack) == 1, "exactly one of the target's arguments is lifted"
    moved = -36 - 4 * pushes.index(stack[0])
    disp = int(stack[0].op_str.split("+")[1].strip(" ]"), 16)
    assert moved + disp == 4, \
        f"0x{target:08X}: the lifted dword is at entry_esp+{moved + disp}, not the argument"


def test_the_shim_puts_the_machine_back(detour):
    """The stolen prologue runs straight after, so every register and the flags
    have to return untouched -- the direction flag included."""
    _, target, ins, _ = detour
    call = next(n for n, i in enumerate(ins) if i.mnemonic == "call")
    nargs = 2 if HOOKS[target][1] else 1
    assert ins[call + 1].mnemonic == "add"
    assert int(ins[call + 1].op_str.split(",")[1], 0) == 4 * nargs, "cdecl: the shim pops"
    assert [i.mnemonic for i in ins[call + 2:call + 4]] == ["popfd", "popal"]


def test_the_payload_reads_the_engine_it_claims_to(cave_bytes):
    """A mistyped global compiles, links, runs, and logs the wrong dword."""
    for address, what in GLOBALS.items():
        assert struct.pack("<I", address) in cave_bytes, f"the payload never reads {what}"


def test_the_payload_calls_the_engine_bodies_not_their_thunks(cave_bytes):
    """Each is a cast literal, so a wrong digit compiles and links and then
    jumps into the middle of some other function at match time."""
    for address, what in CALLS.items():
        assert struct.pack("<I", address) in cave_bytes, f"the payload never calls {what}"


def test_the_record_schema_is_what_the_analysis_parses(cave_bytes):
    for fmt in SCHEMA:
        assert fmt.encode() in cave_bytes, f"missing from the payload: {fmt!r}"


def test_the_pump_s_own_filter_bounds_what_is_logged(cave_bytes):
    """Outside [0x3E9, 0x7CE] a GameMessage is mouse movement and camera noise:
    the same bound the pump itself applies, or the file it shares is buried."""
    assert struct.pack("<I", 0x3E9) in cave_bytes or b"\xe9\x03\x00\x00" in cave_bytes
    assert b"\xce\x07\x00\x00" in cave_bytes or b"\xcf\x07\x00\x00" in cave_bytes


def test_a_dist_build_refuses_to_carry_the_instrument():
    """mods/dist is what every ladder player runs."""
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "--dist"],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode != 0, "a --dist build accepted an instrument"
    assert "refusing --dist" in (r.stderr + r.stdout)
