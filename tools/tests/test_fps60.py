#!/usr/bin/env python3
"""Check the 60 Hz arm changes what it claims to change, and nothing else.

037-fps60 is two byte pokes and one detour, and each of the three is a place
where being one byte out produces a build that runs and measures something
else:

  * the two immediates are the length of GameEngine::update's sub-step cycle.
    They are single bytes inside `cmp eax,6` and `cmp ecx,6`, and the bytes
    either side of them are opcodes. A poke landing on a neighbouring
    comparison would change an unrelated branch and still boot;
  * the detour sits on GameEngine::update's entry, whose first five bytes must
    be whole instructions with no relative operand, or the relocated prologue
    jumps somewhere arbitrary;
  * the payload writes the render rate to the engine, and the offset it writes
    to is the one the frame limiter reads.

And the arms are diffed against each other, because "the two builds differ only
where I meant them to" is the property the whole comparison rests on and is not
implied by any of the above.
"""
import shutil
import struct
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
VC71 = (ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
        / "Vc7/bin/cl.exe")

pytestmark = [pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")]
capstone = pytest.importorskip("capstone")

from cave import PE  # noqa: E402
import modbuild  # noqa: E402

NETWORK_GLOBAL = 0x012F7714     # TheNetwork; NULL outside a match
ANIM_FIELD = 0x012BB1CC         # ms of animation per simulation sub-step

needs_toolchain = pytest.mark.skipif(
    not VC71.exists() or shutil.which("wine") is None,
    reason="MSVC 7.1 toolchain or wine not present")


def disasm(pe, rva, n):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return list(md.disasm(pe.read(rva, n), pe.image_base + rva))


def test_the_immediates_are_the_substep_cycle():
    """Each poke site is the imm8 of a `cmp <reg>, 6` in GameEngine::update."""
    pe = PE(EXE)
    for rva in modbuild.SUBSTEP_IMMEDIATES:
        ins = disasm(pe, rva - 2, 8)[0]
        assert ins.mnemonic == "cmp", f"0x{rva:08X} is not the imm8 of a cmp"
        assert ins.size == 3 and ins.op_str.endswith(", 6"), ins.op_str
        assert pe.read(rva, 1)[0] == modbuild.SUBSTEPS_WERE


def test_the_two_comparisons_bracket_the_cycle():
    """One decides the counter has come round, the other that this iteration is
    the network-gated phase. Both are inside GameEngine::update's body."""
    lo, hi = min(modbuild.SUBSTEP_IMMEDIATES), max(modbuild.SUBSTEP_IMMEDIATES)
    assert modbuild.TARGET_ENGINE_UPDATE < lo < hi
    assert hi - modbuild.TARGET_ENGINE_UPDATE < 392   # the function's own size


def test_the_detour_site_is_whole_instructions_with_no_branch():
    pe = PE(EXE)
    taken, insns = 0, []
    for ins in disasm(pe, modbuild.TARGET_ENGINE_UPDATE, 32):
        insns.append(ins)
        taken += ins.size
        if taken >= 5:
            break
    assert taken == 5, f"the first whole instructions cover {taken} bytes, not 5"
    for ins in insns:
        assert ins.mnemonic in ("push", "mov"), (ins.mnemonic, ins.op_str)
        assert "0x" not in ins.op_str or ins.mnemonic == "mov", ins.op_str


def test_the_render_rate_and_the_substeps_keep_their_ratio():
    """76/12 is 38/6. The loop keeps the same number of spare iterations per
    network frame to spend re-attempting the gated phase, so the change is the
    rate of both halves and not the balance between them."""
    assert (modbuild.FPS_LIMIT / modbuild.SUBSTEPS
            == pytest.approx(modbuild.FPS_LIMIT_WAS / modbuild.SUBSTEPS_WERE))


def test_the_limit_field_is_the_one_the_limiter_reads():
    """GameEngine::execute's frame budget is 1000 / (this+8 * timescale)."""
    pe = PE(EXE)
    body = disasm(pe, 0x0006BEF2, 0x24)
    fild = [i for i in body if i.mnemonic == "fild"]
    assert fild, "no integer load in the limiter"
    assert "+ 8]" in fild[0].op_str, fild[0].op_str


def test_the_shipped_limit_is_not_the_compiled_one():
    """The value the game runs on comes from _patch222.big.

    Quoting the disassembly here would put 30 in a document about a build that
    measures 38, which is the trap docs/lessons.md records twice already."""
    out = subprocess.run([sys.executable, str(ROOT / "tools/ini_value.py"),
                          "FramesPerSecondLimit"],
                         capture_output=True, text=True, cwd=ROOT)
    if "not set" in out.stdout or out.returncode != 0:
        pytest.skip("no game install to read the archives from")
    assert str(modbuild.FPS_LIMIT_WAS) in out.stdout, out.stdout


# ---- the built arms -------------------------------------------------------
@pytest.fixture(scope="module")
def arms(tmp_path_factory):
    d = tmp_path_factory.mktemp("fps60")
    retail, fixed = d / "retail.exe", d / "fixed.exe"
    base = [sys.executable, str(ROOT / "tools/modbuild.py"), "--only", "036-fpsprobe"]
    subprocess.run(base + ["-o", str(retail)], cwd=ROOT, check=True, capture_output=True)
    subprocess.run(base + ["--only", "037-fps60", "-o", str(fixed)],
                   cwd=ROOT, check=True, capture_output=True)
    return PE(retail), PE(fixed)


@needs_toolchain
def test_the_poke_lands(arms):
    _, fixed = arms
    for rva in modbuild.SUBSTEP_IMMEDIATES:
        assert fixed.read(rva, 1)[0] == modbuild.SUBSTEPS


@needs_toolchain
def test_the_payload_writes_the_limit_to_the_engine(arms):
    """The store, found in the cave: `mov dword ptr [eax+8], 76`."""
    _, fixed = arms
    jmp = disasm(fixed, modbuild.TARGET_ENGINE_UPDATE, 8)[0]
    shim = int(jmp.op_str, 16) - fixed.image_base
    # The shim saves state and calls the payload; the store is in the payload.
    call = [i for i in disasm(fixed, shim, 0x20) if i.mnemonic == "call"][0]
    entry = int(call.op_str, 16) - fixed.image_base
    body = disasm(fixed, entry, 0x40)
    stores = [i for i in body
              if i.mnemonic == "mov" and "+ 8]" in i.op_str
              and i.op_str.endswith(f"{modbuild.FPS_LIMIT:#x}")]
    assert stores, [(i.mnemonic, i.op_str) for i in body]


@needs_toolchain
def test_the_arms_differ_only_where_intended(arms):
    """Everything outside the cave must be the three sites and nothing else."""
    retail, fixed = arms
    a, b = bytes(retail.data), bytes(fixed.data)
    assert len(a) == len(b)
    # Both arms carry the probe, so the cave differs only by 037's own payload;
    # what must be identical is the retail image the cave was appended to.
    original = min(s["raddr"] for s in fixed.sections() if s["name"] == ".bfmemod")
    runs = []
    for i in (i for i in range(original) if a[i] != b[i]):
        if runs and i == runs[-1][1] + 1:
            runs[-1][1] = i
        else:
            runs.append([i, i])
    runs = [tuple(r) for r in runs]
    assert runs == [
        (modbuild.TARGET_ENGINE_UPDATE, modbuild.TARGET_ENGINE_UPDATE + 4),
        (modbuild.SUBSTEP_IMMEDIATES[0], modbuild.SUBSTEP_IMMEDIATES[0]),
        (modbuild.SUBSTEP_IMMEDIATES[1], modbuild.SUBSTEP_IMMEDIATES[1]),
    ], runs


@needs_toolchain
def test_dist_refuses_the_unmeasured_arm():
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", "037-fps60", "--dist"],
                       cwd=ROOT, capture_output=True, text=True)
    assert r.returncode != 0
    assert "refusing --dist" in r.stdout + r.stderr


def test_a_wrong_baseline_is_refused(tmp_path):
    """The poke checks what it is overwriting. A baseline whose byte is not 6
    is not retail's GameEngine::update, and the poke would land on an unknown
    comparison rather than on the sub-step cycle."""
    victim = tmp_path / "notretail.exe"
    data = bytearray(EXE.read_bytes())
    pe = PE(EXE)
    data[pe.rva_to_off(modbuild.SUBSTEP_IMMEDIATES[0])] = 9
    victim.write_bytes(bytes(data))
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", "037-fps60", "--baseline", str(victim),
                        "-o", str(tmp_path / "out.exe")],
                       cwd=ROOT, capture_output=True, text=True)
    assert r.returncode != 0
    assert "holds 9, not 6" in r.stdout + r.stderr


@needs_toolchain
def test_dist_refuses_the_arm():
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", "037-fps60", "--dist"],
                       cwd=ROOT, capture_output=True, text=True)
    assert r.returncode != 0
    assert "refusing --dist" in r.stdout + r.stderr


@needs_toolchain
def test_the_animation_clock_is_compensated(arms):
    """Doubling the sub-steps doubles animation speed unless the ms-per-step
    constant halves with them. 33/2 is not an integer, so the payload writes
    16 and 17 alternately and averages 16.5 -- both must be in the body."""
    _, fixed = arms
    jmp = disasm(fixed, modbuild.TARGET_ENGINE_UPDATE, 8)[0]
    shim = int(jmp.op_str, 16) - fixed.image_base
    call = [i for i in disasm(fixed, shim, 0x20) if i.mnemonic == "call"][0]
    body = disasm(fixed, int(call.op_str, 16) - fixed.image_base, 0x60)
    text = " | ".join(f"{i.mnemonic} {i.op_str}" for i in body)
    # The compiler renders the alternation branchlessly: it emits the HIGH
    # constant as an immediate and reaches the LOW one by subtracting one via
    # sbb, so the low value never appears as a literal. What is assertable is
    # the field, the high constant, and that the store is conditional at all --
    # an unconditional store would be the bug this exists to prevent.
    assert f"{ANIM_FIELD:#x}" in text, text
    assert f"{modbuild.ANIM_MS_HIGH:#x}" in text, text
    assert "sbb" in text and "sete" in text, text


def test_the_compensation_averages_the_retail_constant():
    """16 and 17 straddle 16.5, and 16.5 x 12 is 33 x 6 -- the same animation
    milliseconds per cycle retail has."""
    avg = (modbuild.ANIM_MS_LOW + modbuild.ANIM_MS_HIGH) / 2.0
    assert avg * modbuild.SUBSTEPS == modbuild.ANIM_MS_WAS * modbuild.SUBSTEPS_WERE
