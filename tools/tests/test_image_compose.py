"""image_compose: a complete retail image from compiled owners plus sealed bridges, and its controls."""
import copy
import json
import random
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import image_compose as C  # noqa: E402
import test_image_check as T  # noqa: E402

I = T.I
TEXT_RAW, DATA_RAW = 0x1000, 0x800  # .data: raw 0x800 of virtual 0x1000, a zero-fill tail


def pe_file(flat):
    """A PE32 file whose loader mapping is `flat` (0x1000 .text, .data with a zero tail)."""
    header = bytearray(0x400)
    header[0:2] = b"MZ"
    struct.pack_into("<I", header, 0x3C, 0x40)
    header[0x40:0x44] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", header, 0x44, 0x14C, 2, 0, 0, 0, 224, 0x102)
    opt = 0x58
    struct.pack_into("<H", header, opt, 0x10B)
    struct.pack_into("<I", header, opt + 16, 0x1000)  # entry
    struct.pack_into("<I", header, opt + 28, I.BASE)
    struct.pack_into("<II", header, opt + 32, 0x1000, 0x200)
    struct.pack_into("<II", header, opt + 56, 0x3000, 0x400)
    struct.pack_into("<I", header, opt + 92, 16)
    table = opt + 224
    for index, (name, rva, vsize, raw, pointer, flags) in enumerate(
            [(b".text", 0x1000, 0x1000, TEXT_RAW, 0x400, 0x60000020),
             (b".data", 0x2000, 0x1000, DATA_RAW, 0x1400, 0xC0000040)]):
        at = table + 40 * index
        header[at:at + 8] = name.ljust(8, b"\0")
        struct.pack_into("<IIII", header, at + 8, vsize, rva, raw, pointer)
        struct.pack_into("<I", header, at + 36, flags)
    assert not any(flat[0x2000 + DATA_RAW:0x3000]), "the zero-fill tail must be zero"
    return bytes(header) + bytes(flat[0x1000:0x1000 + TEXT_RAW]) + bytes(flat[0x2000:0x2000 + DATA_RAW])


def sealed(tmp_path, objects, kept, retail, ledger, **kw):
    """(bundle, baseline, contract hash, manifest) for an image_check run of synthetic objects."""
    image = T.build(objects, kept, retail, ledger, **kw)
    image.image_size = 0x3000
    paths = {}
    for name, data in objects:
        path = tmp_path / "objects" / name
        path.parent.mkdir(exist_ok=True)
        path.write_bytes(data)
        paths[name] = path
    baseline = tmp_path / "retail.exe"
    baseline.write_bytes(pe_file(retail))
    figures = {"clean_source_recovery": {"total": 0}, "source_closure": {"closed_strict_bytes": 0}}
    manifest, digest = C.seal(image, baseline, tmp_path / "bundle", figures, paths)
    return tmp_path / "bundle", baseline, digest, manifest


def retrust(bundle, manifest):
    """A new trusted contract for a deliberately changed manifest: the deeper checks must still fail."""
    (bundle / "manifest.json").write_text(json.dumps(manifest), encoding="utf-8")
    return C.canonical_hash(C.contract(manifest))


def chain(tmp_path, holder="C2.obj"):
    return sealed(tmp_path, T.CHAIN, {"_a": "A.obj", "_b": "B.obj", "_c": holder}, T.RETAIL, T.LEDGER)


def test_the_composed_image_is_retail_without_reading_it(tmp_path):
    bundle, baseline, digest, manifest = chain(tmp_path)
    refused = C.deny_reads([baseline])
    receipt = C.compose(bundle, digest, tmp_path / "out.exe")
    assert refused == [str(baseline.resolve()).casefold()]  # the probe, and nothing after it
    assert (tmp_path / "out.exe").read_bytes() == pe_file(T.RETAIL)
    compiled = {owner["name"]: owner for owner in manifest["owners"] if owner["kind"] == "compiled"}
    assert set(compiled) == {"_a", "_b", "_c"} and receipt["integrated_bytes"] == {"authored/code": 18}
    assert receipt["compiler_fields_evaluated"] == 2
    assert receipt["integrated_total"] + receipt["retail_dependency_total"] == 0x3000 + 0  # image bytes
    assert receipt["retail_dependency_bytes"]["zero-fill"] == 0x800
    assert receipt["retail_dependency_bytes"]["image-gap"] == 0xC00  # between the headers and .text


def test_a_wrong_selected_copy_stays_a_retail_bridge(tmp_path):
    _, _, _, manifest = chain(tmp_path, holder="C1.obj")
    names = {owner.get("name") for owner in manifest["owners"] if owner["kind"] == "compiled"}
    assert names == {"_a", "_b"} and manifest["rejected_candidates"] == {"bytes differ from retail": 1}


def test_two_calls_through_one_symbol_bind_per_site(tmp_path):
    # retail calls 0x1010 and 0x1020 through what the source spells as one name: a name-level
    # linker must pick one; per-site binding keeps both calls, each to the destination retail demands
    retail = bytearray(T.RETAIL)
    retail[0x1040:0x104B] = T.call(0x1040, 0x1010) + T.call(0x1045, 0x1020) + b"\xc3"
    f = T.function("_f", b"\xe8\0\0\0\0\xe8\0\0\0\0\xc3", [(1, "_x", I.REL32), (6, "_x", I.REL32)])
    bundle, baseline, digest, manifest = sealed(tmp_path, T.CHAIN[:1] + T.CHAIN[1:2] + [T.CHAIN[3], ("F.obj", f)],
                                                {"_a": "A.obj", "_b": "B.obj", "_c": "C2.obj", "_f": "F.obj"},
                                                retail, {**T.LEDGER, "_f": {0x1040}})
    owner = next(owner for owner in manifest["owners"] if owner.get("name") == "_f")
    assert [edge[4] for edge in owner["edges"]] == [0x1010, 0x1020] and owner["edges"][0][3] == owner["edges"][1][3]
    C.compose(bundle, digest, tmp_path / "out.exe")
    assert (tmp_path / "out.exe").read_bytes() == pe_file(retail)


def test_owner_order_does_not_matter(tmp_path):
    bundle, _, digest, manifest = chain(tmp_path)
    first = C.compose(bundle, digest, tmp_path / "a.exe")
    shuffled = copy.deepcopy(manifest)
    random.Random(314159).shuffle(shuffled["owners"])
    assert retrust(bundle, shuffled) == digest  # the contract sorts owners
    second = C.compose(bundle, digest, tmp_path / "b.exe")
    assert (tmp_path / "a.exe").read_bytes() == (tmp_path / "b.exe").read_bytes()
    assert first["address_owned_memory_sha256"] == second["address_owned_memory_sha256"]


def owner_named(manifest, name):
    return next(owner for owner in manifest["owners"] if owner.get("name") == name)


def control(tmp_path, change, message):
    bundle, _, digest, manifest = chain(tmp_path)
    changed = copy.deepcopy(manifest)
    change(changed, bundle)
    trusted = retrust(bundle, changed)
    with pytest.raises(ValueError, match=message):
        C.compose(bundle, trusted, tmp_path / "out.exe")
    assert not (tmp_path / "out.exe").exists()


def test_a_forged_manifest_needs_new_trust(tmp_path):
    bundle, _, digest, manifest = chain(tmp_path)
    changed = copy.deepcopy(manifest)
    owner_named(changed, "_a")["rva"] += 4
    (bundle / "manifest.json").write_text(json.dumps(changed), encoding="utf-8")
    with pytest.raises(ValueError, match="differs from the trusted hash"):
        C.compose(bundle, digest, tmp_path / "out.exe")


@pytest.mark.parametrize("name,change,message", [
    ("missing dependency", lambda m, b: m["owners"].remove(owner_named(m, "_b")), "has no owner"),
    ("hole", lambda m, b: m["owners"].remove(next(o for o in m["owners"] if o["kind"] == "header")),
     "file ownership hole"),
    ("no zero-fill", lambda m, b: m["owners"].remove(next(o for o in m["owners"] if o["kind"] == "zero-fill")),
     "image ownership hole"),
    ("overlap", lambda m, b: m["owners"].append({**owner_named(m, "_a"), "id": "overlap"}), "ownership overlap"),
    ("deleted field", lambda m, b: owner_named(m, "_a").update(edges=[]), "relocation set differs"),
    ("unowned destination", lambda m, b: owner_named(m, "_a")["edges"][0].__setitem__(4, 0x5000), "has no owner"),
    ("same-bytes other instance", lambda m, b: owner_named(m, "_a")["edges"][0].__setitem__(4, 0x1100),
     "differs from the baseline"),
    ("file/RVA", lambda m, b: owner_named(m, "_a").update(file_offset=owner_named(m, "_a")["file_offset"] + 1),
     "placement disagrees"),
    ("bad absolute", lambda m, b: owner_named(m, "_a")["edges"][0].__setitem__(5, "_evil"), "not an allowed"),
])
def test_tamper_controls_fail_under_new_trust(tmp_path, name, change, message):
    control(tmp_path, change, message)


def test_a_changed_compiler_byte_changes_the_image(tmp_path):
    bundle, _, digest, manifest = chain(tmp_path)
    owner = owner_named(manifest, "_b")
    record = manifest["objects"][owner["object"]]
    blob = bundle / record["blob"]
    data = bytearray(blob.read_bytes())
    blob.unlink()  # a hard link: never write through to the census object
    body_at = struct.unpack_from("<I", data, 20 + 40 * (owner["coff_section"] - 1) + 20)[0]
    data[body_at + owner["coff_offset"] + 5] ^= 0xFF  # the ret after the call
    blob.write_bytes(bytes(data))
    changed = copy.deepcopy(manifest)
    changed["objects"][owner["object"]]["sha256"] = C.sha(bytes(data))
    owner_named(changed, "_b")["coff_sha256"] = C.sha(bytes(data[body_at:body_at + 6]))
    trusted = retrust(bundle, changed)
    with pytest.raises(ValueError, match="differs from the baseline"):
        C.compose(bundle, trusted, tmp_path / "out.exe")


def test_a_changed_bridge_fragment_is_refused(tmp_path):
    bundle, _, digest, manifest = chain(tmp_path)
    pack = bytearray((bundle / "bridges.bin").read_bytes())
    pack[-1] ^= 1
    (bundle / "bridges.bin").write_bytes(bytes(pack))
    with pytest.raises(ValueError, match="bridge pack hash differs"):
        C.compose(bundle, digest, tmp_path / "out.exe")


def test_a_field_straddling_a_slice_edge_is_refused():
    sections = [(8, bytes(8), [(3, 0, 0x0006)])]
    with pytest.raises(ValueError, match="straddles the slice's start"):
        C.section_slice(sections, 1, 4, 4)
    with pytest.raises(ValueError, match="straddles the slice's end"):
        C.section_slice(sections, 1, 0, 5)
    assert C.section_slice(sections, 1, 0, 8)[1] == {(3, 0x0006, 0, 0)}


def test_a_dump_is_never_a_compiled_owner(tmp_path):
    image = T.build(T.CHAIN, {"_a": "A.obj", "_b": "B.obj", "_c": "C2.obj"}, T.RETAIL, T.LEDGER)
    for item in image.items:
        item.lane = "dump"
    found, rejected, _ = C.candidates(image)
    assert not found and rejected == {"lane dump": 3}
