import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import target_verify as verify


@pytest.fixture
def target(tmp_path):
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    image = bytearray(b"\xcc" * 512)
    image[:6] = b"\xb8\x01\0\0\0\xc3"
    path = tmp_path / "retail.exe"
    path.write_bytes(image)
    source = tmp_path / "Code/example.cpp"
    source.parent.mkdir()
    source.write_text("int Example() { return 1; }\n")
    result = SimpleNamespace(
        target_id="worldbuilder", root=tmp_path, image_path=path,
        image_bytes=bytes(image), image_base=0x400000,
        expected_sha256=hashlib.sha256(image).hexdigest(),
        ledger_path=tmp_path / "reverse/worldbuilder/functions.csv",
        build_root=tmp_path / "build/worldbuilder",
        profiles={"size": SimpleNamespace(flags=("-O1", "-Gy"), toolchain_includes=())},
        exports=(SimpleNamespace(name="_Example", rva=0x1000, forwarder=None),),
        imports=(), relocations=(),
        sections=(SimpleNamespace(rva=0x1000, raw_size=512, virtual_size=512,
                                  raw_offset=0, characteristics=0x60000020),),
    )
    def read(rva, size):
        if not 0x1000 <= rva < rva + size <= 0x1200:
            raise verify.TargetVerificationError("outside test image")
        return result.image_bytes[rva - 0x1000:rva - 0x1000 + size]
    def check():
        actual = path.read_bytes()
        verify._require(hashlib.sha256(actual).hexdigest() == result.expected_sha256,
                        "target SHA-256 mismatch")
        return actual
    result.read_rva = read
    result.verify_hash = check
    result.follow_ilt = lambda rva: rva
    return result


def row(**changes):
    return {"name": "_Example", "target_rva": "0x1000", "target_size": "6",
            "status": "matched", "source": "Code/example.cpp", "profile": "size",
            "evidence": "export", "model": "test", **changes}


def put(target, offset, data):
    image = bytearray(target.image_bytes)
    image[offset:offset + len(data)] = data
    target.image_bytes = bytes(image)
    target.image_path.write_bytes(image)
    target.expected_sha256 = hashlib.sha256(image).hexdigest()


def test_wrong_binary_refused_before_reading_ledger(target):
    target.image_path.write_bytes(b"wrong target")
    with pytest.raises(verify.TargetVerificationError, match="SHA-256"):
        verify.read_rows(target)


def test_read_rows_requires_exact_schema_and_lf(target):
    target.ledger_path.parent.mkdir(parents=True)
    target.ledger_path.write_bytes((",".join(verify.LEDGER_FIELDS) + "\r\n").encode())
    with pytest.raises(verify.TargetVerificationError, match="LF"):
        verify.read_rows(target)
    target.ledger_path.write_text("name,target_rva\n")
    with pytest.raises(verify.TargetVerificationError, match="expected header"):
        verify.read_rows(target)


def test_cross_target_export_identity_refused(target):
    target.exports = (SimpleNamespace(name="_Example", rva=0x1010, forwarder=None),)
    with pytest.raises(verify.TargetVerificationError, match="export route"):
        verify.validate_rows(target, [row()])


def test_overlap_is_not_an_alias(target):
    with pytest.raises(verify.TargetVerificationError, match="overlapping"):
        verify.validate_rows(target, [row(), row(name="_Other", target_rva="0x1001")])


def test_naked_source_rejected(target):
    (target.root / "Code/example.cpp").write_text("__declspec(naked) void f() {}")
    with pytest.raises(verify.TargetVerificationError, match="naked"):
        verify.validate_rows(target, [row()])


def test_source_cannot_escape_target_roots(target):
    with pytest.raises(verify.TargetVerificationError, match="repository-relative"):
        verify.validate_rows(target, [row(source="../other.cpp")])


@pytest.mark.parametrize("suffix", [".cpp", ".cc", ".c", ".cxx", ".asm", ".s"])
def test_unclaimed_worldbuilder_source_refused(target, suffix):
    unclaimed = target.root / ("Code/Tools/WorldBuilder/forgotten" + suffix)
    unclaimed.parent.mkdir(parents=True)
    unclaimed.write_text("int forgot() { return 2; }")
    subprocess.run(["git", "add", str(unclaimed)], cwd=target.root, check=True)
    with pytest.raises(verify.TargetVerificationError, match="unclaimed target sources"):
        verify.validate_rows(target, [row()])


def test_non_ilt_e9_wrapper_is_not_followed(target):
    put(target, 0, b"\xe9\xfb\xff\xff\xff")
    assert verify._route(target, 0x1000) == 0x1000


def test_call_target_verified_instead_of_masked(target):
    code = b"\xe8\0\0\0\0\xc3"
    put(target, 0, b"\xe8" + struct.pack("<i", 0x1040 - 0x1005) + b"\xc3")
    put(target, 0x40, b"\xc3")
    linked, checks = verify._relocate(target, row(), None, code,
                                      [(1, 20, "_Callee")], {"_Callee": 0x1040})
    assert linked == target.read_rva(0x1000, 6)
    assert checks[0]["target_rva"] == 0x1040
    with pytest.raises(verify.TargetVerificationError, match="contradicts"):
        verify._relocate(target, row(), None, code, [(1, 20, "_Callee")], {"_Callee": 0x1050})


def test_literal_requires_matching_bytes_and_pe_fixup(target, monkeypatch):
    code = b"\x68\0\0\0\0\xc3"
    put(target, 0, b"\x68" + struct.pack("<I", 0x401080) + b"\xc3")
    put(target, 0x80, b"yes\0")
    monkeypatch.setattr(verify.build, "read_object_symbol_bytes", lambda *args: (b"yes\0", []))
    relocs = [(1, 6, "??_C@test")]
    with pytest.raises(verify.TargetVerificationError, match="HIGHLOW"):
        verify._relocate(target, row(), None, code, relocs, {})
    target.relocations = (SimpleNamespace(rva=0x1001, type=3),)
    assert verify._relocate(target, row(), None, code, relocs, {})[0] == target.read_rva(0x1000, 6)
    put(target, 0x80, b"bad\0")
    with pytest.raises(verify.TargetVerificationError, match="string does not match"):
        verify._relocate(target, row(), None, code, relocs, {})


def test_guessed_global_not_accepted_as_relocation(target):
    put(target, 0, b"\x68" + struct.pack("<I", 0x401080) + b"\xc3")
    target.relocations = (SimpleNamespace(rva=0x1001, type=3),)
    with pytest.raises(verify.TargetVerificationError, match="no matching target export"):
        verify._relocate(target, row(), None, b"\x68\0\0\0\0\xc3", [(1, 6, "_Guess")], {})


def test_unknown_relocations_and_addends_refused(target):
    with pytest.raises(verify.TargetVerificationError, match="unsupported COFF"):
        verify._relocate(target, row(), None, b"\x68\0\0\0\0\xc3", [(1, 7, "_Data")], {})
    with pytest.raises(verify.TargetVerificationError, match="nonzero"):
        verify._relocate(target, row(), None, b"\x68\x01\0\0\0\xc3", [(1, 6, "_Data")], {})


def test_named_import_requires_exact_api_identity(target):
    entry = SimpleNamespace(dll="USER32.dll", name="InvalidateRect", ordinal=None, iat_rva=0x1100)
    proof = verify._import_identity(target, entry, "__imp__InvalidateRect@12")
    assert proof["name"] == "InvalidateRect"
    with pytest.raises(verify.TargetVerificationError, match="target import names"):
        verify._import_identity(target, entry, "__imp__ValidateRect@12")


def test_ordinal_map_from_other_binary_refused(target, monkeypatch, tmp_path):
    manifest = tmp_path / "dependency.json"
    manifest.write_text(json.dumps({"target": {"sha256": "0" * 64}}))
    monkeypatch.setitem(sys.modules, "worldbuilder_mfc", SimpleNamespace(MANIFEST=manifest))
    entry = SimpleNamespace(dll="MFC71.DLL", name=None, ordinal=1084, iat_rva=0x1100)
    with pytest.raises(verify.TargetVerificationError, match="another target binary"):
        verify._import_identity(target, entry, "?AfxGetModuleState@@YGPAVAFX_MODULE_STATE@@XZ")


def test_ordinal_mapping_validates_name_and_code_kind(target, monkeypatch, tmp_path):
    manifest = tmp_path / "dependency.json"
    manifest.write_text(json.dumps({"target": {"sha256": target.expected_sha256}, "mapping_sha256": "proof"}))
    monkeypatch.setitem(sys.modules, "worldbuilder_mfc", SimpleNamespace(
        MANIFEST=manifest, resolve_ordinal=lambda dll, ordinal: "?Imported@@YAXXZ",
        load_mapping=lambda: {1084: {"kind": "code"}}))
    entry = SimpleNamespace(dll="MFC71.DLL", name=None, ordinal=1084, iat_rva=0x1100)
    assert verify._import_identity(target, entry, "?Imported@@YAXXZ", call=True)["ordinal"] == 1084
    with pytest.raises(verify.TargetVerificationError, match="target import names"):
        verify._import_identity(target, entry, "?Guessed@@YAXXZ", call=True)


def test_empty_target_is_explicit_zero_success(target):
    result = verify.verify(target, [])
    assert result["rows"] == []
    assert Path(result["noop_path"]).read_bytes() == target.image_path.read_bytes()


def test_unknown_selector_not_hidden_by_another_valid_selector(target):
    with pytest.raises(verify.TargetVerificationError, match="unknown target selectors"):
        verify.verify(target, [row()], selectors=["_Example", "_Typo"])


def test_escaping_conditional_branch_is_not_a_complete_extent(target):
    put(target, 0, bytes.fromhex("7505c3cc"))
    with pytest.raises(verify.TargetVerificationError, match="unproved boundary"):
        verify._extent(target, 0x1000, bytes.fromhex("7505c3"))


def test_branch_into_an_instruction_operand_is_rejected(target):
    put(target, 0, bytes.fromhex("7501b800000000c3cc"))
    with pytest.raises(verify.TargetVerificationError, match="unproved boundary"):
        verify._extent(target, 0x1000, bytes.fromhex("7501b800000000c3"))


def test_exclusive_translation_unit_cannot_hide_unclaimed_functions(target, monkeypatch):
    source = target.root / "Code/Tools/WorldBuilder/editor.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("int claimed(); int unclaimed();")
    obj = target.root / "editor.obj"
    obj.write_bytes(b"object")
    obj.with_suffix(".asm").write_text(f"; File {source}\n_Claimed PROC NEAR\n_Hidden PROC NEAR\n")
    monkeypatch.setattr(verify.build, "vc71_root", lambda: target.root / "sdk")
    monkeypatch.setattr(verify.build, "wine_path", str)
    with pytest.raises(verify.TargetVerificationError, match="unclaimed target definitions: _Hidden"):
        verify._check_definitions(target, source, obj, {"_Claimed"})


def test_header_helpers_do_not_claim_authored_functions(target, monkeypatch):
    source = target.root / "Code/Tools/WorldBuilder/editor.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("void Claimed() {}")
    obj = target.root / "editor.obj"
    obj.with_suffix(".asm").write_text(
        f"; File {target.root}/sdk/atlmfc/include/header.h\n_HeaderHelper PROC NEAR\n"
        f"; File {source}\n_Claimed PROC NEAR\n")
    monkeypatch.setattr(verify.build, "vc71_root", lambda: target.root / "sdk")
    monkeypatch.setattr(verify.build, "wine_path", str)
    verify._check_definitions(target, source, obj, {"_Claimed"})


def test_untracked_other_worker_source_does_not_block_validation(target):
    pending = target.root / "Code/Tools/WorldBuilder/other_worker.cpp"
    pending.parent.mkdir(parents=True)
    pending.write_text("int Pending() { return 1; }")
    verify.validate_rows(target, [row()])


def test_macro_or_included_lift_rejected_after_preprocessing(target, monkeypatch):
    source = target.root / "Code/example.cpp"
    source.write_text('#include "lift.h"\n')
    output = target.build_root / "attempt.obj"
    output.parent.mkdir(parents=True)
    monkeypatch.setattr(verify.build, "source_extra_flags", lambda source: [])
    monkeypatch.setattr(verify.build, "compiler_command", lambda *args: (["cl", "-c", "-O2"], {"INCLUDE": "sdk"}))
    calls = []
    def run(command, **kwargs):
        calls.append(command)
        return SimpleNamespace(returncode=0, stdout="__declspec(naked) void Example() {}")
    monkeypatch.setattr(verify.subprocess, "run", run)
    with pytest.raises(verify.TargetVerificationError, match="preprocessed translation unit"):
        verify._compile(target, source, "size", output)
    assert len(calls) == 1 and "-EP" in calls[0]


def test_probe_accepts_scratch_without_claiming_other_worldbuilder_files(target, monkeypatch):
    source = target.build_root / "attempt.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("int Example() { return 1; }")
    other = target.root / "Code/Tools/WorldBuilder/new.cpp"
    other.parent.mkdir(parents=True)
    other.write_text("int unrelated() { return 2; }")
    monkeypatch.setattr(verify, "_compile", lambda *args: {})
    monkeypatch.setattr(verify, "_object_body", lambda *args: (b"\xb8\x01\0\0\0\xc3", []))
    result = verify.probe(target, "build/worldbuilder/attempt.cpp", "_Example", 0x1000, 6, "size")
    assert result["mode"] == "probe"


def test_normal_verification_produces_identical_image_and_receipt(target, monkeypatch):
    def compile_fixture(target, source, profile, output):
        output.write_bytes(b"fixture")
        return {"profile": profile}
    monkeypatch.setattr(verify, "_compile", compile_fixture)
    monkeypatch.setattr(verify, "_object_body", lambda *args: (b"\xb8\x01\0\0\0\xc3", []))
    result = verify.verify(target, [row()])
    assert Path(result["noop_path"]).read_bytes() == target.image_path.read_bytes()
    assert json.loads(Path(result["receipt_path"]).read_text())["rows"][0]["verified_bytes"] == 6


def test_mismatch_cannot_produce_a_receipt(target, monkeypatch):
    monkeypatch.setattr(verify, "_compile", lambda *args: {})
    monkeypatch.setattr(verify, "_object_body", lambda *args: (b"\xb8\x02\0\0\0\xc3", []))
    with pytest.raises(verify.TargetVerificationError, match="relocated bytes differ"):
        verify.verify(target, [row()])
    assert not list(target.build_root.rglob("receipt.json"))
