"""WorldBuilder identity must survive neither row edits nor broken binary chains."""
from dataclasses import replace
from pathlib import Path
import struct
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worldbuilder_inventory as inventory
from targets import load_target


@pytest.fixture(scope="module")
def target():
    return load_target("worldbuilder")


@pytest.fixture(scope="module")
def candidates(target):
    return inventory.extract_editor_candidates(target)


def test_real_binary_connects_class_and_menu_handler(candidates):
    rows = {row["id"]: row for row in candidates}
    update = rows["CWorldBuilderView::OnUpdateShowGrid"]
    assert update["name"] == "?OnUpdateShowGrid@CWorldBuilderView@@IAEXPAVCCmdUI@@@Z"
    assert (update["target_rva"], update["target_size"]) == (0x104431, 51)
    assert update["chain"]["runtime_class_rva"] == 0xCFBD18
    assert update["chain"]["vtable_rva"] == 0xCFBDC8
    assert update["message_entry"]["resource_id"] == 32772
    assert update["message_entry"]["ilt_route_rvas"] == [0x64D8]
    toggle = rows["CWorldBuilderView::OnShowGrid"]
    assert [item["value"] for item in toggle["string_witnesses"]] == ["ShowGrid", "MainFrame"]
    assert [(c["import"]["dll"], c["import"]["ordinal"], c["import"]["name"])
            for c in toggle["callee_contract"]] == [
        ("MFC71.DLL", 1084, None), ("MFC71.DLL", 6305, None), ("USER32.dll", None, "InvalidateRect")]


@pytest.mark.parametrize("field,value", [
    ("name", "?OnUpdateViewShowtexture@CWorldBuilderView@@IAEXPAVCCmdUI@@@Z"),
    ("target_rva", "0x1044c3"),
    ("target_size", "50"),
])
def test_validator_rejects_wrong_name_address_or_extent(target, candidates, field, value):
    row = dict(candidates[1])
    row[field] = value
    with pytest.raises(ValueError, match=f"{field} disagrees"):
        inventory.validate_mfc_identity(target, row, row["id"])


def test_validator_rederives_evidence_instead_of_using_packet(target, candidates):
    row = dict(candidates[1], chain={"runtime_class_rva": 0}, donor_files=[])
    receipt = inventory.validate_mfc_identity(target, row, row["id"])
    assert receipt["chain"]["runtime_class_rva"] == 0xCFBD18
    assert len(receipt["donor_files"]) == 3


def test_broken_vtable_getter_breaks_class_ownership(target):
    raw = bytearray(target.image_bytes)
    rva = 0xCFBDF8
    section = target.section_for_rva(rva)
    offset = section.raw_offset + rva - section.rva
    struct.pack_into("<I", raw, offset, 0x4095C0)
    with pytest.raises(ValueError, match="missing MFC class map for CWorldBuilderView"):
        inventory.extract_editor_candidates(replace(target, image_bytes=bytes(raw)))


def test_removed_donor_association_is_not_a_silent_name_guess(target, tmp_path):
    cls, method, filename, resource_name, code, _ = inventory.EDITOR_RECIPES[0]
    for relative in (f"src/{filename}.cpp", f"include/{filename}.h", "res/resource.h"):
        path = Path(inventory.DONOR) / relative
        destination = tmp_path / path
        destination.parent.mkdir(parents=True, exist_ok=True)
        text = (target.root / path).read_text()
        destination.write_text(text.replace("ON_COMMAND(IDM_ShowGrid, OnShowGrid)", ""))
    with pytest.raises(ValueError, match="Missing donor association"):
        inventory.donor_association(tmp_path, cls, method, filename, resource_name, code)


def test_menu_ids_come_from_binary_not_donor_constants():
    text = "Show Grid".encode("utf-16le") + b"\0\0"
    raw = struct.pack("<4H", 0, 0, 0x80, 32772) + text
    assert inventory.parse_menu(raw) == [{"flags": 0x80, "resource_id": 32772, "text": "Show Grid"}]
    with pytest.raises(ValueError, match="Unsupported menu"):
        inventory.parse_menu(struct.pack("<2H", 1, 0))
    with pytest.raises(ValueError, match="end marker"):
        inventory.parse_menu(struct.pack("<4H", 0, 0, 0, 32772) + text)


def test_provenance_survives_windows_checkout_but_not_source_edits(tmp_path):
    source = tmp_path / "donor.cpp"
    source.write_bytes(b"void function();\n")
    original = inventory.text_sha256(source)
    source.write_bytes(b"void function();\r\n")
    assert inventory.text_sha256(source) == original
    source.write_bytes(b"void renamed();\r\n")
    assert inventory.text_sha256(source) != original


def test_exported_tail_jump_remains_its_own_function(target):
    image = inventory.Image(target)
    wrapper = next(e for e in target.exports if image.executable(e.rva)
                   and e.rva not in target.ilt_thunks and target.read_rva(e.rva, 1) == b"\xe9")
    assert image.route(wrapper.rva) == (wrapper.rva, [])
