"""Focused PE and pin-shape tests for :mod:`tools.import_pin_guard`.

The fixture is a tiny PE32 image with a real import directory and IAT.  That
keeps the tests about the guard's evidence path: pins are checked against the
fixture's parsed import slots, while the wrong-import case uses the same
``FF25`` body as a good pin and differs only in the IAT entry it names.
"""

import importlib.util
import json
import struct
import sys
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools"
sys.path.insert(0, str(TOOLS))


def _load_guard():
    spec = importlib.util.spec_from_file_location(
        "import_pin_guard_test_module", TOOLS / "import_pin_guard.py"
    )
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def _load_pin_consistency():
    spec = importlib.util.spec_from_file_location(
        "pin_consistency_import_guard_test_module", TOOLS / "pin_consistency.py"
    )
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


guard = _load_guard()

IMAGE_BASE = 0x00400000
TEXT_RVA = 0x1000
IMPORT_RVA = 0x3000
IAT_RVA = 0x3060


def _write_ff25(data, rva, iat_rva):
    offset = 0x200 + (rva - TEXT_RVA)
    struct.pack_into("<2sI", data, offset, b"\xFF\x25",
                     IMAGE_BASE + iat_rva)


def _fixture_pe():
    """Return a PE32 fixture with five imports and good/bad thunk bodies."""
    data = bytearray(0x800)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x80)
    data[0x80:0x84] = b"PE\0\0"

    coff = 0x84
    struct.pack_into("<HHIIIHH", data, coff, 0x014C, 2, 0, 0, 0, 0xE0, 0x010F)
    optional = coff + 20
    struct.pack_into("<H", data, optional, 0x010B)
    struct.pack_into("<I", data, optional + 28, IMAGE_BASE)
    struct.pack_into("<I", data, optional + 92, 16)
    struct.pack_into("<II", data, optional + 96 + 8, IMPORT_RVA, 0x80)

    section_table = optional + 0xE0
    struct.pack_into(
        "<8sIIIIIIHHI", data, section_table,
        b".text\0\0\0", 0x200, TEXT_RVA, 0x200, 0x200,
        0, 0, 0, 0, 0x60000020,
    )
    struct.pack_into(
        "<8sIIIIIIHHI", data, section_table + 40,
        b".idata\0", 0x200, IMPORT_RVA, 0x200, 0x400,
        0, 0, 0, 0, 0xC0000040,
    )

    idata = 0x400
    struct.pack_into("<IIIII", data, idata, 0x3040, 0, 0, 0x3080, IAT_RVA)

    names = ["_CIacos", "_CIasin", "_CIfmod", "_CIpow", "_CxxThrowException"]
    name_rvas = [0x30A0, 0x30B0, 0x30C0, 0x30D0, 0x30F0]
    for index, (name, name_rva) in enumerate(zip(names, name_rvas)):
        struct.pack_into("<I", data, 0x440 + index * 4, name_rva)
        struct.pack_into("<I", data, 0x460 + index * 4, name_rva)
        name_offset = 0x400 + (name_rva - IMPORT_RVA)
        encoded = name.encode("ascii") + b"\0"
        struct.pack_into("<H", data, name_offset, 0)
        data[name_offset + 2:name_offset + 2 + len(encoded)] = encoded
    # The zero ILT/IAT entries terminate both arrays.
    struct.pack_into("<II", data, 0x454, 0, 0)
    struct.pack_into("<II", data, 0x474, 0, 0)
    data[0x480:0x480 + len(b"MSVCR71.dll\0")] = b"MSVCR71.dll\0"

    # Five correct terminal import jumps, plus one import mismatch and one
    # ordinary function body that must be rejected as a CRT thunk.
    good_rvas = [0x1010, 0x1020, 0x1030, 0x1040, 0x1050]
    for index, rva in enumerate(good_rvas):
        _write_ff25(data, rva, IAT_RVA + index * 4)
    _write_ff25(data, 0x1060, IAT_RVA + 3 * 4)  # _CIpow, not _CIfmod
    data[0x200 + (0x1070 - TEXT_RVA):0x200 + (0x1070 - TEXT_RVA) + 4] = \
        b"\x55\x8B\xEC\xC3"
    jump_offset = 0x200 + (0x1080 - TEXT_RVA)
    struct.pack_into("<Bi", data, jump_offset, 0xE9, 0x1010 - (0x1080 + 5))
    return bytes(data)


def _cross_section_thunk(opcode):
    """Put a thunk's trailing bytes in a contiguous neighbouring section."""
    data = bytearray(_fixture_pe())
    coff = 0x84
    struct.pack_into("<H", data, coff + 2, 3)
    optional = coff + 20
    section_table = optional + 0xE0
    struct.pack_into(
        "<8sIIIIIIHHI", data, section_table + 80,
        b".tail\0\0\0", 0x200, TEXT_RVA + 0x200, 0x200, 0x600,
        0, 0, 0, 0, 0x60000020,
    )

    current = TEXT_RVA + 0x1FD
    if opcode == b"\xE9":
        instruction = b"\xE9\0\0\0\0"
    else:
        instruction = b"\xFF\x25" + struct.pack("<I", IMAGE_BASE + IAT_RVA)
    text_count = (TEXT_RVA + 0x200) - current
    text_offset = 0x200 + (current - TEXT_RVA)
    data[text_offset:text_offset + text_count] = instruction[:text_count]
    data[0x600:0x600 + len(instruction) - text_count] = instruction[text_count:]
    return guard.PEImage.from_bytes(data), current


@pytest.fixture
def image():
    return guard.PEImage.from_bytes(_fixture_pe())


def test_a_direct_ff25_pin_resolves_the_expected_import(image):
    result = guard.inspect_pin(image, "__CIacos", 0x1010)

    assert result.status == "ok"
    assert result.iat_rva == IAT_RVA
    assert result.actual_dll == "MSVCR71.dll"
    assert result.actual_name == "_CIacos"
    assert result.chain == (0x1010,)


def test_a_bounded_e9_chain_reaches_the_expected_import(image):
    result = guard.inspect_pin(image, "__CIacos", 0x1080)

    assert result.status == "ok"
    assert result.chain == (0x1080, 0x1010)


def test_the_same_thunk_shape_can_still_name_the_wrong_import(image):
    result = guard.inspect_pin(image, "__CIfmod", 0x1060)

    assert result.status == "wrong-import"
    assert result.actual_name == "_CIpow"
    assert "expected msvcr71.dll!_CIfmod" in result.detail


def test_an_ordinary_function_body_is_not_accepted_as_a_crt_thunk(image):
    result = guard.inspect_pin(image, "__CxxThrowException@8", 0x1070)

    assert result.status == "wrong-body"
    assert result.actual_name is None


def test_additive_pins_report_good_and_bad_candidates_together(image):
    pins = {name: [rva] for name, rva in zip(
        guard.EXPECTED_IMPORTS,
        [0x1010, 0x1020, 0x1030, 0x1040, 0x1050],
    )}
    pins["__CIfmod"].append(0x1060)

    results = guard.check_pins(image, pins)
    fmod = [result for result in results if result.symbol == "__CIfmod"]
    assert [result.status for result in fmod] == ["ok", "wrong-import"]


def test_pe32_plus_is_rejected_instead_of_parsed_as_x86(image):
    data = bytearray(_fixture_pe())
    struct.pack_into("<H", data, 0x98, 0x020B)

    with pytest.raises(guard.PEFormatError, match="requires x86 PE32"):
        guard.PEImage.from_bytes(data)


def test_non_x86_machine_is_rejected(image):
    data = bytearray(_fixture_pe())
    struct.pack_into("<H", data, 0x84, 0x8664)

    with pytest.raises(guard.PEFormatError, match="requires x86 PE32"):
        guard.PEImage.from_bytes(data)


def test_a_rva_read_must_fit_inside_section_raw_bytes(image):
    with pytest.raises(guard.PEFormatError, match="section raw data"):
        image.read_rva(TEXT_RVA + 0x1FF, 2)


@pytest.mark.parametrize("opcode", [b"\xE9", b"\xFF\x25"])
def test_a_complete_thunk_instruction_cannot_cross_into_a_neighbouring_section(opcode):
    image, current = _cross_section_thunk(opcode)

    result = guard.inspect_pin(image, "__CIacos", current)

    assert result.status == "bad-thunk"
    assert "section raw data" in result.detail or "leaves .text" in result.detail


def test_json_mode_leaves_stdout_parseable(tmp_path, capsys):
    exe = tmp_path / "fixture.exe"
    symbols = tmp_path / "symbols.csv"
    exe.write_bytes(_fixture_pe())
    rows = [
        ("__CIacos", 0x1010),
        ("__CIasin", 0x1020),
        ("__CIfmod", 0x1030),
        ("__CIpow", 0x1040),
        ("__CxxThrowException@8", 0x1050),
    ]
    symbols.write_text(
        "name,address,notes\n"
        + "".join(f"{name},0x{rva:08X},\n" for name, rva in rows),
        encoding="utf-8",
    )

    assert guard.main([
        "--exe", str(exe), "--symbols", str(symbols), "--json",
    ]) == 0
    captured = capsys.readouterr()
    parsed = json.loads(captured.out)
    assert len(parsed) == 5
    assert "import_pin_guard: PASS 5/5 guarded pins" in captured.err


def test_pin_consistency_check_rejects_an_additive_wrong_cifmod_pin(
        tmp_path, monkeypatch, capsys):
    """The existing ``--check`` path must run the import guard too."""
    pin_consistency = _load_pin_consistency()
    exe = tmp_path / "fixture.exe"
    symbols = tmp_path / "symbols.csv"
    baseline = tmp_path / "pin_consistency_baseline.csv"
    exe.write_bytes(_fixture_pe())
    rows = [
        ("__CIacos", 0x1010),
        ("__CIasin", 0x1020),
        ("__CIfmod", 0x1030),
        ("__CIpow", 0x1040),
        ("__CxxThrowException@8", 0x1050),
        ("__CIfmod", 0x1060),  # additive candidate reaches _CIpow
    ]
    symbols.write_text(
        "name,address,notes\n"
        + "".join(f"{name},0x{rva:08X},\n" for name, rva in rows),
        encoding="utf-8",
    )
    baseline.write_text("symbol,bodies,kind,evidence\n", encoding="utf-8")

    class CleanScanner:
        def scan(self):
            return [], {"multi_pinned": 0, "names": 0}

    monkeypatch.setattr(pin_consistency, "Scanner", CleanScanner)
    monkeypatch.setattr(pin_consistency.build, "EXE", exe)
    monkeypatch.setattr(pin_consistency.build, "SYMBOLS", symbols)
    original_verify = pin_consistency.verify
    monkeypatch.setattr(
        pin_consistency, "verify", lambda: original_verify(path=baseline)
    )

    with pytest.raises(SystemExit) as excinfo:
        pin_consistency.main(["--check"])

    assert excinfo.value.code == 1
    output = capsys.readouterr().out
    assert "CRT import pins: FAIL 1 of 6 guarded pins" in output
    assert "__CIfmod" in output
    assert "wrong-import" in output
