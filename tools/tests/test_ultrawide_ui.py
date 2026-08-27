"""Tests for the centered logical UI feature.

The first tests deliberately use the same integer policy as the naked payload,
so they run without Wine or the MSVC 7.1 toolchain.  The optional binary test
checks that the actual mod builder installs every declared detour into
.bfmemod.
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
SOURCE = ROOT / "mods/features/041-ultrawide-ui/src/ultrawide_ui.cpp"
VC71 = ROOT / "build/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/bin/cl.exe"
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
)


def ui_width(width, height):
    return min(width, height * 4 // 3)


@pytest.mark.parametrize("width,height,expected_width,expected_left", [
    (1024, 768, 1024, 0), (1280, 800, 1066, 107),
    (1920, 1080, 1440, 240), (2560, 1080, 1440, 560),
    (3440, 1440, 1920, 760), (3840, 1600, 2133, 853),
    (5120, 1440, 1920, 1600),
])
def test_ui_uses_a_centered_height_led_4_3_band(width, height, expected_width,
                                                expected_left):
    logical = ui_width(width, height)
    left = (width - logical) // 2
    assert logical == expected_width
    assert left == expected_left
    assert logical <= width
    assert left * 2 <= width - logical <= left * 2 + 1
    assert logical == width if width * 3 <= height * 4 else logical == height * 4 // 3


def test_reference_4_3_is_unchanged():
    assert ui_width(1024, 768) == 1024
    assert (1024 - ui_width(1024, 768)) // 2 == 0


def test_wider_displays_keep_the_same_logical_height_and_add_symmetric_margins():
    height = 1440
    reference = ui_width(1920, height)
    assert reference == 1920
    for width in (2560, 3440, 3840, 5120):
        logical = ui_width(width, height)
        assert logical == reference
        assert (width - logical) // 2 >= 0


def test_feature_is_integer_only_and_documents_the_parser_tail_order():
    text = SOURCE.read_text()
    assert "tan(" not in text
    assert "atan" not in text
    assert "TheDisplay" in text
    assert "after parseScreenRect has stored x/y" in text
    assert "CONTROLBAR_FOREGROUND_MARKER_X = 0x2D0" in text
    assert "CONTROLBAR_BACKGROUND_MARKER_X = 0x2D8" in text


@pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")
@pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present")
@pytest.mark.skipif(shutil.which("wine") is None, reason="wine not installed")
def test_binary_contains_all_ui_detours_and_a_code_cave():
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / "ultrawide-ui.exe"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools/modbuild.py"), "--only", "041-ultrawide-ui",
             "-o", str(out)], capture_output=True, text=True, cwd=ROOT)
        assert result.returncode == 0, result.stderr or result.stdout
        pe = PE(out)

    cave = next(section for section in pe.sections() if section["name"] == ".bfmemod")
    cave_start = pe.image_base + cave["vaddr"]
    cave_end = cave_start + cave["vsize"]
    baseline = PE(EXE)
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    for target in HOOKS:
        assert baseline.read(target, 1) != b"\xe9"
        _, stolen, _ = baseline._steal(target, 5)
        detour = pe.read(target, 5)
        assert detour[0] == 0xE9
        shim_rva = target + 5 + struct.unpack_from("<i", detour, 1)[0]
        shim = pe.image_base + shim_rva
        assert cave_start <= shim < cave_end
        jumps = [ins for ins in md.disasm(pe.read(shim_rva, 160), shim)
                 if ins.mnemonic == "jmp" and ins.op_str.startswith("0x")]
        assert jumps
        assert int(jumps[0].op_str, 16) == pe.image_base + target + stolen
    assert pe.data != baseline.data
