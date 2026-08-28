"""Tests for the renderer-level ultrawide UI feature.

The arithmetic tests run everywhere.  The optional binary test uses the same
MSVC 7.1/Wine path as test_mods_build.py and proves that each renderer path is
actually detoured into .bfmemod.
"""
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[2]
EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
SOURCE = ROOT / "mods/features/042-ultrawide-render/src/ultrawide_render.cpp"
VC71 = (ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
        / "Vc7/bin/cl.exe")
sys.path.insert(0, str(ROOT / "tools"))

import modbuild  # noqa: E402
from cave import PE  # noqa: E402

HOOKS = (
    modbuild.TARGET_UI_PARSE_ENTRY,
    modbuild.TARGET_UI_PARSE_TAIL,
    modbuild.TARGET_UI_SCHEME_BY_NAME_ENTRY,
    modbuild.TARGET_UI_SCHEME_BY_NAME_TAIL,
    modbuild.TARGET_UI_SCHEME_BY_TEMPLATE_ENTRY,
    modbuild.TARGET_UI_SCHEME_BY_TEMPLATE_TAIL,
    modbuild.TARGET_UI_SCHEME_BY_PLAYER_ENTRY,
    modbuild.TARGET_UI_SCHEME_BY_PLAYER_TAIL,
    modbuild.TARGET_UI_CONTROLBAR_INIT_TAIL,
    modbuild.TARGET_UI_COORDINATE_RANGE,
    modbuild.TARGET_UI_SENTENCE_VIEWPORT,
    modbuild.TARGET_UI_RENDER_VIEWPORT,
)


def ui_band(width, height):
    """Return (centred left, logical width) using the naked payload policy."""
    band = min(width, height * 4 // 3)
    return (width - band) // 2, band


def ui_coordinate_range(width, height):
    """Return the physical inclusive/exclusive Render2D coordinate interval."""
    left, band = ui_band(width, height)
    return left, left + band


@pytest.mark.parametrize("width,height,expected_left,expected_band", [
    (1024, 768, 0, 1024),
    (1280, 800, 107, 1066),
    (1920, 1080, 240, 1440),
    (2560, 1080, 560, 1440),
    (3440, 1440, 760, 1920),
    (3840, 1600, 853, 2133),
    (5120, 1440, 1600, 1920),
])
def test_reference_band(width, height, expected_left, expected_band):
    left, band = ui_band(width, height)
    assert (left, band) == (expected_left, expected_band)
    assert left * 2 <= width - band <= left * 2 + 1
    assert band <= width


def test_vertical_framing_is_constant_and_horizontal_extent_grows():
    reference_left, reference_band = ui_band(1024, 768)
    assert reference_left == 0
    assert reference_band == 1024

    # At a fixed height, the 4:3 band stays fixed while the unused horizontal
    # space grows symmetrically.  The viewport is full-height in every case.
    height = 1440
    expected_band = 1920
    for width in (1920, 2560, 3440, 3840, 5120):
        left, band = ui_band(width, height)
        assert band == expected_band
        assert left == (width - expected_band) // 2
        assert (left + band) <= width


def test_reference_compatibility():
    left, band = ui_band(1024, 768)
    assert left == 0
    assert band == 1024
    assert band / 768 == pytest.approx(4.0 / 3.0)


def test_renderer_range_matches_already_centered_window_coordinates():
    assert ui_coordinate_range(1920, 1080) == (240, 1680)
    assert ui_coordinate_range(3440, 1440) == (760, 2680)
    assert ui_coordinate_range(5120, 1440) == (1600, 3520)


def test_extreme_diagnostic_is_unmistakable():
    width, height = 3440, 1440
    left, band = width // 4, width // 2
    assert (left, band) == (860, 1720)
    assert band / height < 1.3


def test_payload_avoids_trigonometry_and_documents_renderer_order():
    text = SOURCE.read_text()
    assert "tan(" not in text
    assert "atan" not in text
    assert "Set_Coordinate_Range" in text
    assert "ui_parse_begin" in text
    assert "ui_scheme_begin" in text
    assert "physical centred interval" in text
    assert "range->left" in text
    assert "00933FD0" in text
    assert "00934AD5" in text
    assert "copySurfaceRects006e" in text
    assert "_fltused" in text


def _shim_target(pe, md, target):
    detour = pe.read(target, 5)
    assert detour[0] == 0xE9
    shim_rva = target + 5 + struct.unpack_from("<i", detour, 1)[0]
    cave = next(s for s in pe.sections() if s["name"] == ".bfmemod")
    assert cave["vaddr"] <= shim_rva < cave["vaddr"] + cave["vsize"]
    _, stolen, _ = PE(EXE)._steal(target, 5)
    expected_resume = pe.image_base + target + stolen
    instructions = list(md.disasm(pe.read(shim_rva, 256), pe.image_base + shim_rva))
    jumps = [i for i in instructions
             if i.mnemonic == "jmp" and i.op_str.startswith("0x")]
    assert any(int(i.op_str, 16) == expected_resume for i in jumps)
    return shim_rva, instructions


@pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")
@pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present")
@pytest.mark.skipif(shutil.which("wine") is None, reason="wine not installed")
def test_binary_contains_renderer_detours_and_retail_viewport_call():
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / "ultrawide-render.exe"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools/modbuild.py"),
             "--only", "042-ultrawide-render", "-o", str(out)],
            capture_output=True, text=True, cwd=ROOT)
        assert result.returncode == 0, result.stderr or result.stdout
        pe = PE(out)

    baseline = PE(EXE)
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    for target in HOOKS:
        assert baseline.read(target, 1) != b"\xe9"
        _, instructions = _shim_target(pe, md, target)
        assert [i.mnemonic for i in instructions[:3]] == ["pushal", "pushfd", "cld"]

    cave = next(s for s in pe.sections() if s["name"] == ".bfmemod")
    cave_start = pe.image_base + cave["vaddr"]
    instructions = list(md.disasm(pe.read(cave["vaddr"], cave["vsize"]), cave_start))
    assert any(i.mnemonic == "mov" and i.op_str == "eax, 0xd043b0"
               and any(j.mnemonic == "call" and j.op_str == "eax"
                       for j in instructions[n + 1:n + 6])
               for n, i in enumerate(instructions))
    assert pe.data != baseline.data
