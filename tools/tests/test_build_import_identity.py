"""The build gate must not hide a wrong CRT import behind DIR32 rebasing.

``compile_function`` copies retail DIR32 operands so a linker address can be
reproduced.  For the audited CRT symbols that have known twins, the COFF symbol
and the retail PE import table must agree before that copy is accepted.
"""

import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


IMAGE_BASE = 0x00400000
IAT_RVA = 0x00001234
TARGET_RVA = 0x0046EE10
TARGET_SIZE = 8
DIR32 = 0x0006


def _row(symbol):
    return {
        "name": "?guardedImport@Test@@YAXXZ",
        "target_rva": f"0x{TARGET_RVA:08X}",
        "target_size": str(TARGET_SIZE),
        "source": "Code/GameEngine/Source/Common/BfmeSkipLevelPrefix.cpp",
        "status": "matched",
        "notes": f"object-symbol=body;test-coff={symbol}",
    }


def _compile(monkeypatch, symbol, actual_name, *, actual_dll="MSVCR71.dll",
             iat_rva=IAT_RVA, reloc_offset=2):
    # Keep a non-zero COFF addend so the guard proves it subtracts the value
    # held in the object rather than treating the retail operand as the slot.
    coff_addend = 4
    compiled = b"\xFF\x15" + struct.pack("<I", coff_addend) + b"\xC3\x90"
    target = b"\xFF\x15" + struct.pack(
        "<I", IMAGE_BASE + iat_rva + coff_addend
    ) + b"\xC3\x90"
    image = SimpleNamespace(
        image_base=IMAGE_BASE,
        imports={
            iat_rva: SimpleNamespace(
                dll=actual_dll, name=actual_name, ordinal=None, iat_rva=iat_rva
            )
        },
    )
    monkeypatch.setattr(build, "read_target_bytes",
                        lambda _rva, _size: target)
    monkeypatch.setattr(build, "read_object_symbol_bytes",
                        lambda *_args: (compiled, [(reloc_offset, DIR32, symbol)]))
    monkeypatch.setattr(build, "import_guard_image", lambda: image)
    return build.compile_function(_row(symbol), {}, Path("test.obj"))


def test_the_old_bfme_strnicmp_reference_is_rejected_as_strncmp(monkeypatch):
    with pytest.raises(SystemExit) as excinfo:
        _compile(monkeypatch, "__imp___strnicmp", "strncmp")

    message = str(excinfo.value)
    assert "__imp___strnicmp" in message
    assert "expected msvcr71.dll!_strnicmp" in message
    assert "MSVCR71.dll!strncmp" in message


def test_a_matching_strnicmp_reference_passes(monkeypatch):
    patch = _compile(monkeypatch, "__imp___strnicmp", "_strnicmp")

    assert patch["bytes"] == patch["target"]
    assert patch["unresolved"] == []


def test_the_corrected_bfme_strncmp_symbol_is_not_guarded(monkeypatch):
    patch = _compile(monkeypatch, "__imp__strncmp", "strncmp")

    assert patch["bytes"] == patch["target"]


def test_an_itoa_reference_is_rejected_when_the_slot_is_ultoa(monkeypatch):
    with pytest.raises(SystemExit) as excinfo:
        _compile(monkeypatch, "__imp__itoa", "_ultoa")

    message = str(excinfo.value)
    assert "__imp__itoa" in message
    assert "expected msvcr71.dll!_itoa" in message
    assert "MSVCR71.dll!_ultoa" in message


def test_a_guarded_reference_to_a_non_import_body_is_rejected(monkeypatch):
    # No entry at the linked operand's IAT RVA models a DIR32 that points at
    # an ordinary body or other image address instead of an import slot.
    coff_addend = 4
    compiled = b"\xFF\x15" + struct.pack("<I", coff_addend) + b"\xC3\x90"
    target = b"\xFF\x15" + struct.pack(
        "<I", IMAGE_BASE + 0x00005678 + coff_addend
    ) + b"\xC3\x90"
    image = SimpleNamespace(image_base=IMAGE_BASE, imports={})
    monkeypatch.setattr(build, "read_target_bytes",
                        lambda _rva, _size: target)
    monkeypatch.setattr(build, "read_object_symbol_bytes",
                        lambda *_args: (compiled, [(2, DIR32, "__imp__itoa")]))
    monkeypatch.setattr(build, "import_guard_image", lambda: image)

    with pytest.raises(SystemExit, match="not an import-table slot"):
        build.compile_function(_row("__imp__itoa"), {}, Path("test.obj"))


def test_a_guarded_relocation_after_this_comdat_body_is_ignored(monkeypatch):
    # A COFF section may contain a following function.  Its relocation is
    # outside this row and compile_function's resolver deliberately skips it.
    body = b"\x90" * TARGET_SIZE
    monkeypatch.setattr(build, "read_target_bytes",
                        lambda _rva, _size: body)
    monkeypatch.setattr(build, "read_object_symbol_bytes",
                        lambda *_args: (body, [(TARGET_SIZE, DIR32, "__imp__itoa")]))
    monkeypatch.setattr(
        build, "import_guard_image",
        lambda: pytest.fail("a later-function relocation must not parse imports"),
    )

    patch = build.compile_function(_row("__imp__itoa"), {}, Path("test.obj"))

    assert patch["bytes"] == body


def test_a_guarded_dir32_that_straddles_this_body_is_rejected(monkeypatch):
    with pytest.raises(SystemExit, match="does not fit"):
        _compile(
            monkeypatch, "__imp__itoa", "_itoa",
            reloc_offset=TARGET_SIZE - 2,
        )


def test_the_retail_import_parser_is_cached_for_one_baseline_identity(
        monkeypatch, tmp_path):
    exe = tmp_path / "fixture.exe"
    exe.write_bytes(b"fixture")
    image = object()
    calls = []

    import import_pin_guard

    monkeypatch.setattr(
        import_pin_guard.PEImage,
        "from_path",
        lambda path: calls.append(Path(path)) or image,
    )
    monkeypatch.setattr(build, "EXE", exe)
    build._cached_import_guard_image.cache_clear()
    try:
        assert build.import_guard_image() is image
        assert build.import_guard_image() is image
    finally:
        build._cached_import_guard_image.cache_clear()

    assert calls == [exe]


@pytest.mark.parametrize("symbol, actual, expected", [
    ("__imp__ceil", "floor", "ceil"),
    ("__imp__floor", "ceil", "floor"),
    ("__imp__memmove", "_memicmp", "memmove"),
    ("__imp___memicmp", "memmove", "_memicmp"),
    ("__imp__strstr", "strtok", "strstr"),
    ("__imp__strtok", "strstr", "strtok"),
    ("__imp__fopen", "_wfopen", "fopen"),
    ("__imp___wfopen", "fopen", "_wfopen"),
])
def test_audited_same_shape_import_twins_are_rejected(monkeypatch, symbol, actual, expected):
    with pytest.raises(SystemExit, match="expected msvcr71.dll!" + expected):
        _compile(monkeypatch, symbol, actual)


@pytest.mark.parametrize("symbol, actual", [
    ("__imp__ceil", "ceil"),
    ("__imp__floor", "floor"),
    ("__imp__memmove", "memmove"),
    ("__imp___memicmp", "_memicmp"),
    ("__imp__strstr", "strstr"),
    ("__imp__strtok", "strtok"),
    ("__imp__fopen", "fopen"),
    ("__imp___wfopen", "_wfopen"),
])
def test_audited_correct_imports_keep_matching(monkeypatch, symbol, actual):
    patch = _compile(monkeypatch, symbol, actual)
    assert patch["bytes"] == patch["target"]
    assert patch["unresolved"] == []
