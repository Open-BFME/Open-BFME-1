"""A relocated data table must never prove an executable function claim."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def write_object(path, section_name, characteristics, body, sites=()):
    symbols = [struct.pack("<8sIhHBB", b"_lookup", 0, 1, 0, 3, 0)]
    relocs = []
    for index, site in enumerate(sites, 1):
        symbols.append(struct.pack("<8sIhHBB", f"_p{index}".encode(),
                                   0, 0, 0, 2, 0))
        relocs.append(struct.pack("<IIH", site, index, 6))
    raw_at = 60
    reloc_at = raw_at + len(body)
    symbol_at = reloc_at + 10 * len(relocs)
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, symbol_at, len(symbols), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", section_name.encode(), 0, 0,
                          len(body), raw_at, reloc_at, 0, len(relocs), 0,
                          characteristics)
    path.write_bytes(header + section + body + b"".join(relocs)
                     + b"".join(symbols) + struct.pack("<I", 4))
    return path


def row(size):
    return {"name": "?allegedFunction@@YAXXZ", "target_rva": "0x0013D150",
            "target_size": str(size), "source": "game/Test.cpp",
            "status": "matched", "notes": "object-symbol=_lookup"}


@pytest.mark.parametrize("section_name", [".data", ".rdata", ".text"])
def test_pointer_table_cannot_match_code_by_masking_every_byte(
        tmp_path, monkeypatch, section_name):
    # The real WeaponSet::Lookup false claim: five pointers mask two accessors
    # and thirteen alignment bytes. A misleading section name is no exemption.
    retail = bytes.fromhex("8b01c3" + "cc" * 13 + "8b4104c3")
    obj = write_object(tmp_path / "table.obj", section_name, 0xC0301040,
                       bytes(20), range(0, 20, 4))
    monkeypatch.setattr(build, "read_target_bytes", lambda *_: retail)
    with pytest.raises(ValueError, match="non-code COFF section"):
        build.compile_function(row(20), {}, obj)

    # The shared extractor must still support legitimate data/string checks.
    raw, relocs = build.read_object_symbol_bytes(obj, "_lookup", 20)
    assert raw == bytes(20)
    assert [offset for offset, kind, name in relocs] == list(range(0, 20, 4))


def test_code_section_with_comdat_suffix_remains_eligible(tmp_path, monkeypatch):
    body = bytes.fromhex("8b01c3")
    obj = write_object(tmp_path / "code.obj", ".text$mn", 0x60301020, body)
    monkeypatch.setattr(build, "read_target_bytes", lambda *_: body)
    patch = build.compile_function(row(len(body)), {}, obj)
    assert build.verified_patch_eligible(patch, body)


def test_target_function_extraction_rejects_noncode_sections(tmp_path):
    import target_verify
    body = bytes.fromhex("8b01c3")
    obj = write_object(tmp_path / "data_body.obj", ".data", 0xC0300040, body)
    with pytest.raises(ValueError, match="non-code COFF section"):
        target_verify._object_body(obj, "_lookup")
    obj = write_object(tmp_path / "code_body.obj", ".text$mn", 0x60301020, body)
    assert target_verify._object_body(obj, "_lookup") == (body, [])
