#!/usr/bin/env python3
"""Build the frame probe and check the instrument, not the source.

036-fpsprobe is the gate the whole 60 FPS spike is decided on, and the failure
it exists to catch is a build that presents twice as often while showing the
same image twice. So the things asserted here are the ones that would let it
report smoothness that is not there:

  * the hook address. RVA 0x00909039 is exactly `mov eax,[TheD3DDevice]`, five
    bytes, one whole instruction. One byte out and the detour lands mid-
    instruction; a few bytes earlier and it fires on render-to-texture passes
    that never reach the screen, inflating the present rate with frames nobody
    saw;
  * that it sits after EndScene and before Present, which is what makes a
    backbuffer readback both legal and a picture of the frame about to be shown;
  * the D3D device global and the two vtable slots that identify it. A mistyped
    global would hash whatever else lives at that address and still produce
    plausible-looking numbers;
  * the reader's ability to tell a really-redrawn frame from a repeated one.
    That is the whole measurement, and it is asserted against synthetic captures
    with a known answer -- the offline half of the two calibration controls;
  * that a --dist build refuses to carry it. It reads the backbuffer back off
    the GPU; mods/dist is what every ladder player runs.
"""
import json
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
VC71 = (ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
        / "Vc7/bin/cl.exe")

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
]
capstone = pytest.importorskip("capstone")

from cave import PE  # noqa: E402

FEATURE = "036-fpsprobe"
HOOK = 0x00909039
DEVICE_GLOBAL = 0x01340534
PRESENT_SLOT = 0x44      # IDirect3DDevice9::Present
ENDSCENE_SLOT = 0xA8     # IDirect3DDevice9::EndScene
ENTRY = "fpsprobe_present"

needs_toolchain = pytest.mark.skipif(
    not VC71.exists() or shutil.which("wine") is None,
    reason="MSVC 7.1 toolchain or wine not present")


def disasm(pe, rva, n):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return list(md.disasm(pe.read(rva, n), pe.image_base + rva))


# ---- the anchor, in the retail baseline ----------------------------------
def test_hook_site_is_one_whole_five_byte_instruction():
    """A detour steals whole instructions. This one must steal exactly one."""
    pe = PE(EXE)
    ins = disasm(pe, HOOK, 16)[0]
    assert ins.mnemonic == "mov"
    assert ins.size == 5, f"the site is a {ins.size}-byte instruction, not 5"
    assert f"0x{DEVICE_GLOBAL:x}" in ins.op_str, ins.op_str
    assert ins.op_str.startswith("eax,"), ins.op_str


def test_hook_fires_only_on_frames_that_reach_the_screen():
    """The site sits on the taken side of End_Scene's `flip` test.

    Hooking before it would count render-to-texture passes as presented frames,
    which is a present rate that no player ever saw.
    """
    pe = PE(EXE)
    before = disasm(pe, HOOK - 6, 6)
    assert before[0].mnemonic == "je", before[0].mnemonic
    # the branch skips PAST the present, so its target is beyond the hook
    target = int(before[0].op_str, 16) - pe.image_base
    assert target > HOOK, f"the flip test jumps to 0x{target:08X}, not past the present"


def test_present_follows_the_hook():
    """Present is the next call, on the device the stolen instruction loads."""
    pe = PE(EXE)
    slots = [i for i in disasm(pe, HOOK, 24) if i.mnemonic == "call"]
    assert slots, "no call after the hook"
    assert f"+ 0x{PRESENT_SLOT:x}" in slots[0].op_str, slots[0].op_str


def test_endscene_precedes_the_hook_in_the_same_function():
    """The readback is legal only outside a scene, and shows the finished frame."""
    pe = PE(EXE)
    body = disasm(pe, 0x00908FE0, HOOK - 0x00908FE0)
    calls = [i.op_str for i in body if i.mnemonic == "call"]
    assert any(f"+ 0x{ENDSCENE_SLOT:x}" in c for c in calls), calls


def test_the_device_global_is_the_one_present_is_called_on():
    """Both slots the retail code calls through it are IDirect3DDevice9's.

    Present at +0x44 and EndScene at +0xA8 agree with that interface and with
    no other one this image uses, which is what pins the global.
    """
    pe = PE(EXE)
    loads = [i for i in disasm(pe, 0x00908FE0, 0x80)
             if i.mnemonic == "mov" and f"0x{DEVICE_GLOBAL:x}" in i.op_str]
    assert loads, "End_Scene never loads the device global this probe reads"


def test_the_client_frame_getter_is_the_slot_the_engine_uses():
    """GameEngine::execute reads the render clock through vtable slot 26 to
    decide whether to run the frame limiter. The probe calls the same slot
    rather than reading a field that merely looks like a frame counter."""
    pe = PE(EXE)
    body = disasm(pe, 0x0006BE8E, 0x10)
    load = body[0]
    assert load.mnemonic == "mov" and "0x12f1464" in load.op_str, load.op_str
    call = [i for i in body if i.mnemonic == "call"][0]
    assert "+ 0x68" in call.op_str, call.op_str


# ---- what the build produced ---------------------------------------------
@pytest.fixture(scope="module")
def built(tmp_path_factory):
    out = tmp_path_factory.mktemp("fpsprobe") / "fpsprobe.exe"
    subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                    "--only", FEATURE, "-o", str(out)],
                   cwd=ROOT, check=True, capture_output=True, text=True)
    return PE(out)


@needs_toolchain
def test_detour_replaces_exactly_the_stolen_instruction(built):
    ins = disasm(built, HOOK, 16)
    assert ins[0].mnemonic == "jmp" and ins[0].size == 5
    # No nop padding: a 5-byte steal for a 5-byte trampoline is exact.
    assert ins[1].address - built.image_base == HOOK + 5


@needs_toolchain
def test_the_cave_puts_the_stolen_instruction_back(built):
    """The payload runs, every register is restored, and the original `mov`
    executes before control returns to the instruction after the hook."""
    cave = int(disasm(built, HOOK, 8)[0].op_str, 16) - built.image_base
    body = disasm(built, cave, 0x30)
    text = [(i.mnemonic, i.op_str) for i in body]
    assert text[0][0] == "pushal"
    assert text[1][0] == "pushfd"
    assert text[2][0] == "cld"
    assert text[3][0] == "call"
    assert [m for m, _ in text[4:7]] == ["add", "popfd", "popal"], text[4:7]
    stolen = text[7]
    assert stolen[0] == "mov" and f"0x{DEVICE_GLOBAL:x}" in stolen[1], stolen
    back = [i for i in body if i.mnemonic == "jmp"][-1]
    assert int(back.op_str, 16) - built.image_base == HOOK + 5


@needs_toolchain
def test_dist_refuses_to_ship_the_instrument():
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "--dist"],
                       cwd=ROOT, capture_output=True, text=True)
    assert r.returncode != 0
    assert "refusing --dist" in r.stdout + r.stderr


# ---- the reader: the offline half of the calibration controls ------------
sys.path.insert(0, str(ROOT / "tools"))
import fpsmeter  # noqa: E402

TILES = 192


def capture(path, kind, bursts=6, live_tiles=(100, 101), period_ms=16.7):
    """A synthetic capture with a known answer.

    "moving"   every present redraws: the live tiles differ every frame, which
               is what a build that really interpolates produces.
    "stepped"  every second present is a pixel-identical repeat: the loop ran
               at the higher rate and the screen did not. This is the exact
               failure the original spike gate would have passed.
    """
    freq = 10_000_000
    lines = [json.dumps(dict(ev="open", qfreqlo=freq & 0xFFFFFFFF, qfreqhi=freq >> 32,
                             w=800, h=600, fmt=22, bpp=4, cols=16, rows=12,
                             cellw=50, cellh=50, burst=8, periodms=2000))]
    seq = present = 0
    t = 0.0
    for b in range(bursts):
        for i in range(8):
            tiles = [1000 + n for n in range(TILES)]
            for n in live_tiles:
                step = seq if kind == "moving" else seq // 2
                tiles[n] = 5000 + step
            q = int(t * freq / 1000.0)
            lines.append(json.dumps(dict(ev="frame", qlo=q & 0xFFFFFFFF, qhi=q >> 32,
                                         ms=int(t), seq=seq, present=present,
                                         f=b, cf=seq, live=1, tiles=tiles)))
            seq += 1
            present += 1
            t += period_ms
        t += 2000.0
        present += 3          # presents the burst did not sample
    Path(path).write_text("\n".join(lines) + "\n")
    return path


def test_a_really_redrawn_frame_reads_as_live(tmp_path):
    cap = fpsmeter.load(capture(tmp_path / "moving.jsonl", "moving"))
    fpsmeter.clock(cap)
    rates, npairs = fpsmeter.tiles(cap)
    assert npairs == 6 * 7, npairs        # 7 consecutive pairs per 8-frame burst
    assert rates[100] == 0.0 and rates[101] == 0.0
    live = fpsmeter.classify(rates)[1]
    assert set(live) == {100, 101}


def test_a_repeated_frame_reads_as_stepped(tmp_path):
    """The positive control: the loop is at 60 Hz and the screen is at 30."""
    cap = fpsmeter.load(capture(tmp_path / "stepped.jsonl", "stepped"))
    fpsmeter.clock(cap)
    rates, _ = fpsmeter.tiles(cap)
    assert 0.4 <= rates[100] <= 0.6, rates[100]
    static, live, stepped = fpsmeter.classify(rates)
    assert set(stepped) == {100, 101}, "a repeated frame must not read as live"
    assert 100 not in live and 100 not in static


def test_pairs_never_span_a_burst_gap(tmp_path):
    """Two seconds of real motion between two samples is not a duplicate.

    Without the present-counter test the last frame of one burst and the first
    of the next would be compared, which manufactures whichever answer the
    scene happened to give.
    """
    cap = fpsmeter.load(capture(tmp_path / "moving.jsonl", "moving"))
    fpsmeter.clock(cap)
    for a, b, dt in fpsmeter.pairs(cap):
        assert b["present"] == a["present"] + 1
        assert dt < fpsmeter.BURST_GAP_MS


def test_preflight_refuses_a_stopped_capture(tmp_path, capsys):
    p = capture(tmp_path / "stopped.jsonl", "moving")
    with open(p, "a") as f:
        f.write(json.dumps(dict(ev="stop", why="backbuffer is multisampled",
                                hr=0)) + "\n")
    assert fpsmeter.preflight([fpsmeter.load(p)]) == 1
    out = capsys.readouterr().out
    assert "REFUSED" in out and "multisampled" in out


def test_preflight_accepts_a_good_capture(tmp_path, capsys):
    p = capture(tmp_path / "ok.jsonl", "moving")
    assert fpsmeter.preflight([fpsmeter.load(p)]) == 0
    assert "ok " in capsys.readouterr().out


def test_present_cadence_is_read_from_the_clock(tmp_path):
    cap = fpsmeter.load(capture(tmp_path / "fast.jsonl", "moving", period_ms=16.7))
    fpsmeter.clock(cap)
    dts = [dt for _, _, dt in fpsmeter.pairs(cap)]
    assert abs(fpsmeter.pct(dts, 50) - 16.7) < 0.1


def test_a_tile_count_change_is_refused(tmp_path):
    """A capture whose samples disagree on the grid is not silently truncated."""
    p = tmp_path / "ragged.jsonl"
    capture(p, "moving")
    lines = p.read_text().splitlines()
    e = json.loads(lines[3])
    e["tiles"] = e["tiles"][:10]
    lines[3] = json.dumps(e)
    p.write_text("\n".join(lines) + "\n")
    cap = fpsmeter.load(p)
    fpsmeter.clock(cap)
    with pytest.raises(SystemExit, match="tiles"):
        fpsmeter.tiles(cap)
