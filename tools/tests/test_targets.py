"""Target isolation and file-backed address checks using small independent PEs."""
from dataclasses import FrozenInstanceError
import hashlib
import json
from pathlib import Path
import struct
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from targets import TargetError, load_target


def image(body=b"\xC3", virtual_size=0x20, image_base=0x400000):
    data = bytearray(0x400)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", data, 0x84, 0x14C, 1, 0, 0, 0, 0xE0, 0x102)
    optional = 0x98
    struct.pack_into("<H", data, optional, 0x10B)
    struct.pack_into("<III", data, optional + 16, 0x1000, 0x1000, 0)
    struct.pack_into("<III", data, optional + 28, image_base, 0x1000, 0x200)
    struct.pack_into("<II", data, optional + 56, 0x2000, 0x200)
    struct.pack_into("<I", data, optional + 92, 16)
    struct.pack_into("<8sIIIIIIHHI", data, optional + 0xE0,
                     b".text\0\0\0", virtual_size, 0x1000, 0x200, 0x200,
                     0, 0, 0, 0, 0x60000020)
    data[0x200:0x200 + len(body)] = body
    return bytes(data)


def configure(root, target_id="worldbuilder", data=None):
    data = image() if data is None else data
    binary = root / "baselines" / (target_id + ".exe")
    binary.parent.mkdir(parents=True, exist_ok=True)
    binary.write_bytes(data)
    config = {
        "schema_version": 1,
        "target_id": target_id,
        "image": {"path": binary.relative_to(root).as_posix(),
                  "sha256": hashlib.sha256(data).hexdigest()},
        "ledger_root": "reverse/" + target_id,
        "build_root": "build/" + target_id,
        "profiles": {"size": {"flags": ["-O1"], "toolchain_includes": []}},
    }
    path = root / target_id / "target.json"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(config))
    return path, binary, config


def test_hash_bound_targets_keep_distinct_same_rva_images(tmp_path):
    configure(tmp_path, "first", image(b"\xC3"))
    configure(tmp_path, "second", image(b"\x90\xC3", image_base=0x500000))
    first = load_target("first", root=tmp_path)
    second = load_target("second", root=tmp_path)

    assert first.read_rva(0x1000, 1) == b"\xC3"
    assert second.read_rva(0x1000, 1) == b"\x90"
    assert first.read_rva(0x1000, 1) == b"\xC3"
    assert first.image_base == 0x400000
    assert second.image_base == 0x500000
    assert first.ledger_path == tmp_path / "reverse/first/functions.csv"
    assert first.build_root != second.build_root
    assert first.image_bytes == first.verify_hash()


@pytest.mark.parametrize("replacement", [image(b"\x90\xC3"), b"corrupt image"])
def test_wrong_binary_or_corruption_fails_before_pe_parsing(tmp_path, replacement):
    _, binary, _ = configure(tmp_path)
    binary.write_bytes(replacement)
    with pytest.raises(TargetError, match="SHA-256 mismatch"):
        load_target("worldbuilder", root=tmp_path)


def test_loaded_snapshot_cannot_silently_follow_disk_changes(tmp_path):
    _, binary, _ = configure(tmp_path)
    target = load_target("worldbuilder", root=tmp_path)
    binary.write_bytes(image(b"\x90\xC3"))
    assert target.read_rva(0x1000, 1) == b"\xC3"
    with pytest.raises(TargetError, match="SHA-256 mismatch"):
        target.verify_hash()


@pytest.mark.parametrize("rva,size", [(0x101F, 2), (0x1020, 1), (0xFFF, 2),
                                     (0x1000, 0), (0x1000, -1), (-1, 1)])
def test_read_rejects_padding_cross_section_and_invalid_extents(tmp_path, rva, size):
    configure(tmp_path)
    with pytest.raises(TargetError):
        load_target("worldbuilder", root=tmp_path).read_rva(rva, size)


def test_virtual_zero_fill_is_not_file_backed_code(tmp_path):
    configure(tmp_path, data=image(virtual_size=0x300))
    target = load_target("worldbuilder", root=tmp_path)
    assert target.section_for_rva(0x1200).name == ".text"
    with pytest.raises(TargetError, match="not fully backed"):
        target.read_rva(0x11FF, 2)


def test_truncated_raw_section_is_rejected(tmp_path):
    configure(tmp_path, data=image()[:-1])
    with pytest.raises(TargetError, match="raw extent exceeds image size"):
        load_target("worldbuilder", root=tmp_path)


def test_missing_target_does_not_use_another_config(tmp_path):
    configure(tmp_path)
    with pytest.raises(TargetError, match="cannot load target absent"):
        load_target("absent", root=tmp_path)


@pytest.mark.parametrize("changed", [{"target_id": "other"}, {"schema_version": 2}, {"schema_version": True},
                                     {"ledger_root": "reverse"}, {"build_root": "build/match"}])
def test_invalid_identity_or_shared_state_namespace_is_rejected(tmp_path, changed):
    path, _, config = configure(tmp_path)
    config.update(changed)
    path.write_text(json.dumps(config))
    with pytest.raises(TargetError):
        load_target("worldbuilder", root=tmp_path)


def test_image_path_cannot_escape_root(tmp_path):
    path, _, config = configure(tmp_path)
    config["image"]["path"] = "../worldbuilder.exe"
    path.write_text(json.dumps(config))
    with pytest.raises(TargetError, match="relative path"):
        load_target("worldbuilder", root=tmp_path)


def test_target_state_cannot_redirect_to_game_ledgers(tmp_path):
    configure(tmp_path)
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    try:
        (reverse / "worldbuilder").symlink_to(reverse, target_is_directory=True)
    except OSError:
        pytest.skip("symlink creation unavailable on this host")
    with pytest.raises(TargetError, match="must not redirect through a symlink"):
        load_target("worldbuilder", root=tmp_path)


def test_selected_target_and_profile_are_immutable(tmp_path):
    configure(tmp_path)
    target = load_target("worldbuilder", root=tmp_path)
    with pytest.raises(FrozenInstanceError):
        target.target_id = "other"
    with pytest.raises(TypeError):
        target.profiles["size"] = None
    with pytest.raises(FrozenInstanceError):
        target.profiles["size"].flags = ("-O2",)


def ilt_image():
    body = bytearray(b"\xCC" * 0x100)
    for offset, destination in ((5, 0x1040), (10, 0x1050), (0x40, 0x1060)):
        struct.pack_into("<Bi", body, offset, 0xE9, destination - (0x1000 + offset + 5))
    body[0x50] = body[0x60] = 0xC3
    return image(bytes(body), virtual_size=0x100)


def test_ilt_routing_preserves_real_tailcall_wrapper(tmp_path):
    configure(tmp_path, data=ilt_image())
    target = load_target("worldbuilder", root=tmp_path)
    assert dict(target.ilt_thunks) == {0x1005: 0x1040, 0x100A: 0x1050}
    assert target.follow_ilt(0x1005) == 0x1040
    assert target.follow_ilt(0x1040) == 0x1040
    assert target.ilt_provenance == {
        "start_rva": 0x1005, "end_rva": 0x100F, "entry_count": 2,
        "sha256": hashlib.sha256(target.read_rva(0x1005, 10)).hexdigest()}


@pytest.mark.parametrize("mutation", ["padding", "outside", "recursive"])
def test_malformed_initial_table_is_rejected(tmp_path, mutation):
    data = bytearray(ilt_image())
    if mutation == "padding":
        data[0x210] = 0xC3
    else:
        destination = 0x5000 if mutation == "outside" else 0x100A
        struct.pack_into("<i", data, 0x206, destination - 0x100A)
    configure(tmp_path, data=bytes(data))
    with pytest.raises(TargetError, match="initial ILT"):
        load_target("worldbuilder", root=tmp_path)


def test_plain_e9_function_without_table_witness_is_not_routed(tmp_path):
    configure(tmp_path, data=image(b"\xE9\x05\0\0\0\xCC\xCC\xCC"))
    target = load_target("worldbuilder", root=tmp_path)
    assert target.follow_ilt(0x1000) == 0x1000
    assert target.ilt_provenance is None
