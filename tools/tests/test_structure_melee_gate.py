#!/usr/bin/env python3
"""Structural checks for the attempted structure melee gate; no gameplay claim."""
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
# Each predicate call resumes at the restore hook, which resumes at the je.
HOOK_RESUMES = {
    modbuild.STRUCTURE_MELEE_ONENTER_CALL: modbuild.STRUCTURE_MELEE_ONENTER_RESTORE,
    modbuild.STRUCTURE_MELEE_ONENTER_RESTORE: modbuild.STRUCTURE_MELEE_ONENTER_RESTORE + 5,
    modbuild.STRUCTURE_MELEE_UPDATE_CALL: modbuild.STRUCTURE_MELEE_UPDATE_RESTORE,
    modbuild.STRUCTURE_MELEE_UPDATE_RESTORE: modbuild.STRUCTURE_MELEE_UPDATE_RESTORE + 5,
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
        out = Path(tmp) / "structure-melee-gate.exe"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools/modbuild.py"), "--only", "051-structure-melee-gate",
             "-o", str(out)],
            capture_output=True, text=True, cwd=ROOT)
        assert result.returncode == 0, result.stderr or result.stdout
        yield PE(out)


def test_structure_melee_gate_is_registered_in_the_shipped_feature_set():
    assert "051-structure-melee-gate" in modbuild.FEATURES
    assert "051-structure-melee-gate" not in modbuild.UNSHIPPED


def test_structure_melee_gate_payload_has_no_unresolved_runtime_symbols():
    with tempfile.TemporaryDirectory() as tmp:
        obj = modbuild.compile_payload(
            ROOT / "mods/features/051-structure-melee-gate/src/structure_melee_gate.cpp",
            Path(tmp) / "structure_melee_gate.obj")
        assert modbuild.undefined_externals(obj) == []


def test_retail_call_sites_resolve_through_ilt_to_the_melee_horde_predicate():
    pe = PE(EXE)
    predicate_ilt_rva = 0x0002056D
    for call in (modbuild.STRUCTURE_MELEE_ONENTER_CALL, modbuild.STRUCTURE_MELEE_UPDATE_CALL):
        call_bytes = pe.read(call, 5)
        assert call_bytes[0] == 0xE8
        displacement = struct.unpack("<i", call_bytes[1:])[0]
        assert call + 5 + displacement == predicate_ilt_rva
        thunk = next(_md().disasm(pe.read(predicate_ilt_rva, 5),
                                  pe.image_base + predicate_ilt_rva))
        assert thunk.mnemonic == "jmp"
        assert int(thunk.op_str, 16) == pe.image_base + 0x00175820


def test_retail_restore_sites_preserve_predicate_test_and_branch():
    pe = PE(EXE)
    for restore in (modbuild.STRUCTURE_MELEE_ONENTER_RESTORE, modbuild.STRUCTURE_MELEE_UPDATE_RESTORE):
        assert pe.read(restore, 5) == modbuild.STRUCTURE_MELEE_AFTER_CALL
        assert pe.read(restore + 5, 1) == b"\x74"


def test_hook_detours_land_in_payload_and_resume_at_expected_addresses(built):
    pe = built
    cave = next(section for section in pe.sections() if section["name"] == ".bfmemod")
    cave_start = pe.image_base + cave["vaddr"]
    cave_end = cave_start + cave["vsize"]
    md = _md()
    shim_targets = []

    for hook_rva, resume in HOOK_RESUMES.items():
        detour = pe.read(hook_rva, 5)
        assert detour[0] == 0xE9, f"0x{hook_rva:08X} was not replaced by a rel32 detour"
        shim = hook_rva + 5 + struct.unpack("<i", detour[1:])[0]
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
