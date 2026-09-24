#!/usr/bin/env python3
"""051-meleeac borrows the predicate's own skip bit, and does not ship."""
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

# call site -> first instruction after the five stolen bytes.
# The call's resume is the disarm hook. The disarm hook's resume is the je.
HOOK_RESUMES = {
    modbuild.MELEEAC_ONENTER_CALL: modbuild.MELEEAC_ONENTER_RESTORE,
    modbuild.MELEEAC_ONENTER_RESTORE: modbuild.MELEEAC_ONENTER_RESTORE + 5,
    modbuild.MELEEAC_UPDATE_CALL: modbuild.MELEEAC_UPDATE_RESTORE,
    modbuild.MELEEAC_UPDATE_RESTORE: modbuild.MELEEAC_UPDATE_RESTORE + 5,
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
        out = Path(tmp) / "meleeac.exe"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools/modbuild.py"), "--only", "051-meleeac",
             "-o", str(out)],
            capture_output=True, text=True, cwd=ROOT)
        assert result.returncode == 0, result.stderr or result.stdout
        yield PE(out)


def test_meleeac_is_a_shipped_feature():
    assert "051-meleeac" in modbuild.FEATURES
    assert "051-meleeac" not in modbuild.UNSHIPPED


def test_meleeac_payload_has_no_unresolved_runtime_symbols():
    with tempfile.TemporaryDirectory() as tmp:
        obj = modbuild.compile_payload(
            ROOT / "mods/features/051-meleeac/src/meleeac.cpp",
            Path(tmp) / "meleeac.obj")
        assert modbuild.undefined_externals(obj) == []


def test_retail_hook_sites_preserve_predicate_test_and_branch():
    pe = PE(EXE)
    for call, restore in (
            (modbuild.MELEEAC_ONENTER_CALL, modbuild.MELEEAC_ONENTER_RESTORE),
            (modbuild.MELEEAC_UPDATE_CALL, modbuild.MELEEAC_UPDATE_RESTORE)):
        assert pe.read(call, 1) == b"\xE8"
        assert pe.read(restore, 5) == modbuild.MELEEAC_AFTER_CALL
        # The short je stays outside the stolen bytes, so the disarm hook can
        # return to it.
        assert pe.read(restore + 5, 1) == b"\x74"


def test_meleeac_detours_both_calls_and_returns_to_the_je(built):
    pe = built
    cave = next(section for section in pe.sections() if section["name"] == ".bfmemod")
    cave_start = pe.image_base + cave["vaddr"]
    cave_end = cave_start + cave["vsize"]
    md = _md()
    shim_targets = []

    for target, resume in HOOK_RESUMES.items():
        detour = pe.read(target, 5)
        assert detour[0] == 0xE9, f"0x{target:08X} was not replaced by a rel32 detour"
        shim = target + 5 + struct.unpack("<i", detour[1:])[0]
        instructions = list(md.disasm(pe.read(shim, 96), pe.image_base + shim))
        assert [ins.mnemonic for ins in instructions[:3]] == ["pushal", "pushfd", "cld"]
        call = next(ins for ins in instructions if ins.mnemonic == "call")
        assert cave_start <= int(call.op_str, 16) < cave_end
        shim_targets.append(shim)

        back = next(ins for ins in instructions if ins.mnemonic == "jmp"
                    and ins.address > call.address)
        assert int(back.op_str, 16) - pe.image_base == resume

    assert len(set(shim_targets)) == len(HOOK_RESUMES)
    assert pe.data != bytearray(EXE.read_bytes())
