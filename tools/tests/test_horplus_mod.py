#!/usr/bin/env python3
"""Check that the Hor+ feature is emitted through the normal cave machinery."""
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
VC71 = ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/bin/cl.exe"
capstone = pytest.importorskip("capstone")

import modbuild  # noqa: E402
from cave import PE  # noqa: E402

TARGETS = {
    0x0073DC3E: 0x0073DC44,
    0x0073DDF8: 0x0073DDFD,
    0x00742609: 0x0074260E,
    0x00931304: 0x00931309,
}

pytestmark = [
    pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present"),
    pytest.mark.skipif(shutil.which("wine") is None, reason="wine not installed"),
]


def _md():
    return capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


@pytest.fixture(scope="module")
def built():
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / "horplus.exe"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools/modbuild.py"), "--only", "040-horplus",
             "-o", str(out)],
            capture_output=True, text=True, cwd=ROOT)
        assert result.returncode == 0, result.stderr or result.stdout
        yield PE(out)


def test_horplus_is_registered_as_an_unshipped_feature():
    assert "040-horplus" not in modbuild.FEATURES
    assert "040-horplus" in modbuild.UNSHIPPED


def test_horplus_payload_has_no_unresolved_runtime_symbols():
    with tempfile.TemporaryDirectory() as tmp:
        obj = modbuild.compile_payload(
            ROOT / "mods/features/040-horplus/src/horplus.cpp",
            Path(tmp) / "horplus.obj")
        assert modbuild.undefined_externals(obj) == []


def test_horplus_patches_post_operation_sites_and_reaches_the_cave(built):
    pe = built
    cave = next(section for section in pe.sections() if section["name"] == ".bfmemod")
    cave_start = pe.image_base + cave["vaddr"]
    cave_end = cave_start + cave["vsize"]
    cave_bytes = pe.read(cave["vaddr"], cave["vsize"])
    # Calls inside a payload use fixed retail VAs; 0x00931780 is the RVA in
    # reverse/functions.csv, while the executable's image base is 0x00400000.
    assert b"\xB8\x80\x17\xD3\x00" in cave_bytes  # mov eax, 0x00D31780
    md = _md()
    shim_targets = []

    for target, resume in TARGETS.items():
        detour = pe.read(target, 5)
        assert detour[0] == 0xE9, f"0x{target:08X} was not replaced by a rel32 detour"
        shim = target + 5 + struct.unpack("<i", detour[1:])[0]
        instructions = list(md.disasm(pe.read(shim, 96), pe.image_base + shim))
        assert [ins.mnemonic for ins in instructions[:3]] == ["pushal", "pushfd", "cld"]
        call = next(ins for ins in instructions if ins.mnemonic == "call")
        assert cave_start <= int(call.op_str, 16) < cave_end
        shim_targets.append(shim)

        # The generated shim must return to the first instruction after the
        # exact five-byte stolen tail, preserving the retail epilogue path.
        back = next(ins for ins in instructions if ins.mnemonic == "jmp"
                    and ins.address > call.address)
        assert int(back.op_str, 16) - pe.image_base == resume

    assert len(set(shim_targets)) == len(TARGETS)
    assert pe.data != bytearray(EXE.read_bytes())


def test_horplus_sites_follow_retail_projection_writes():
    pe = PE(EXE)
    # setHeight: direct Set_Aspect_Ratio call at 0x0073DC39, then the hook
    # receives ESI as the view before retail updates the viewport.
    assert pe.read(0x0073DC39, 5)[0] == 0xE8
    assert pe.read(0x0073DC3E, 6) == b"\x8b\x86\x04\x01\x00\x00"

    # setWidth: direct Set_View_Plane call ends at the hooked epilogue.
    assert pe.read(0x0073DDF3, 5)[0] == 0xE8
    assert pe.read(0x0073DDF8, 5) == b"\x5f\x5e\x83\xc4\x18"

    # BFME camera-transform path: Set_View_Plane, then vtable +0x54
    # (CameraClass::Set_Transform), then the proposed final hook.
    assert pe.read(0x00742551, 5)[0] == 0xE8
    assert pe.read(0x00742605, 4) == b"\x52\xff\x50\x54"
    assert pe.read(0x00742609, 5) == b"\xa1\xe0\x7f\x2f\x01"

    # The direct locked/scripted-camera transform path is the only global
    # CameraClass hook retained; its payload filters against TheTacticalView.
    assert pe.read(0x00931304, 5) == b"\x5e\xc2\x04\x00\xcc"
