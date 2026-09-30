import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import data_scaffold  # noqa: E402
import reloc_ledger  # noqa: E402
from test_reloc_ledger import BASE, image_with  # noqa: E402


def test_reloc_overflow_round_trips(tmp_path):
    coff = data_scaffold.Coff()
    n = coff.add_section(".data$S", 0xC0300040, bytes(4 * 70000), 4 * 70000)
    target = coff.symbol("_t")
    coff.sections[n - 1]["relocs"] = [(4 * k, target) for k in range(70000)]
    coff.write(tmp_path / "big.obj")
    sections, symbols = reloc_ledger.parse_coff((tmp_path / "big.obj").read_bytes())
    relocs = sections[0]["relocs"]
    assert len(relocs) == 70000 and relocs[0] == (0, 0, 6) and relocs[-1][0] == 4 * 69999
    assert symbols[0]["name"] == "_t"


def test_alignment_follows_the_retail_address():
    assert data_scaffold.align_flags(0x1000) == 5 << 20
    assert data_scaffold.align_flags(0x1004) == 3 << 20
    assert data_scaffold.align_flags(0x1001) == 1 << 20


def item(start, end, label, proof="inferred", section=".rdata"):
    return {"start": start, "end": end, "label": label, "proof": proof, "section": section, "kind": "data"}


def test_blocks_merge_contiguous_items_and_split_gaps_and_bss():
    blocks = data_scaffold.blocks_of([item(0, 4, "a"), item(4, 8, "b"), item(12, 16, "c"),
                                      item(16, 20, "d", proof="uninitialised")])
    assert [(b["start"], b["end"], b["bss"]) for b in blocks] == [(0, 8, False), (12, 16, False), (16, 20, True)]


def row(site, target, symbol, addend=0):
    return {"site_va": f"0x{site:08X}", "target_va": f"0x{target:08X}", "link_symbol": symbol,
            "link_addend": f"{addend:#x}", "link_class": "scaffold", "provenance": "vtable"}


def scaffold_fixture(tmp_path, scan_listed=True):
    # item A (0x402000): pointer to item B + 4, pointer to code, one unexplained in-image dword
    # item B (0x402010): 8 bytes of data
    rdata = struct.pack("<4I", BASE + 0x2014, BASE + 0x1000, BASE + 0x1234, 0) + b"ABCDEFGH"
    img = image_with(rdata=rdata)
    items = [item(BASE + 0x2000, BASE + 0x2010, "g_00402000"), item(BASE + 0x2010, BASE + 0x2018, "_named")]
    relocs = {BASE + 0x2000: row(BASE + 0x2000, BASE + 0x2014, "_named", 4),
              BASE + 0x2004: row(BASE + 0x2004, BASE + 0x1000, "?f@@YAXXZ")}
    names = [{"va": f"0x{BASE + 0x2010:08X}", "name": "_named", "sources": "dir32", "role": "scaffold",
              "alias_of": ""},
             {"va": f"0x{BASE + 0x2010:08X}", "name": "?named@@3HA", "sources": "compiler", "role": "alias",
              "alias_of": "_named"}]
    objects, labels, aliases, problems, unlinkable = data_scaffold.emit(img, items, relocs, names, tmp_path)
    scan = {BASE + 0x2008} if scan_listed else set()
    return img, objects, labels, aliases, relocs, scan, unlinkable


def test_emitted_scaffold_reproduces_retail_and_moves_every_field(tmp_path):
    img, objects, labels, aliases, relocs, scan, unlinkable = scaffold_fixture(tmp_path)
    assert aliases == {"?named@@3HA": "_named"}
    checks, failures = data_scaffold.verify(img, objects, relocs, scan, labels, unlinkable)
    assert failures == []
    assert checks["relocations"] == 2 and checks["listed_literals"] == 1
    assert not checks.get("retail_differs") and not checks.get("unlisted_literals")
    sections, symbols = reloc_ledger.parse_coff(objects[0].read_bytes())
    assert sections[0]["name"] == ".rdata$S" and len(sections[0]["relocs"]) == 2
    # the in-place addend is the offset into the target item, not retail's address
    assert struct.unpack_from("<I", sections[0]["body"], 0)[0] == 4
    assert (tmp_path / "obj" / "aliases.obj").exists()


def test_an_unlisted_in_image_literal_fails_verification(tmp_path):
    img, objects, labels, aliases, relocs, scan, unlinkable = scaffold_fixture(tmp_path, scan_listed=False)
    checks, failures = data_scaffold.verify(img, objects, relocs, scan, labels, unlinkable)
    assert checks["unlisted_literals"] == 1 and "0x00401234" in failures[0]


def test_unpinned_residue_groups_by_cause_most_referenced_first():
    out = data_scaffold.residue(["_memcpy", "??0Foo@@QAE@XZ", "?x@BfmeThing@@QAEXXZ", "??4Foo@@QAEAAV0@ABV0@@Z",
                                 "??1Foo@@QAE@XZ", "?f@A@@QAEXXZ"], {"??1Foo@@QAE@XZ": 5, "??0Foo@@QAE@XZ": 2})
    ctor = out["ctor/dtor (private class copies)"]
    assert ctor["names"] == 2 and ctor["references"] == 7 and ctor["top"][0] == ["??1Foo@@QAE@XZ", 5]
    assert set(out) == {"crt", "ctor/dtor (private class copies)", "invented Bfme*/Rva*/Gen* name", "operator",
                        "other method or function"}


def test_queue_suggests_an_owner_by_address_or_by_qualified_name(tmp_path):
    img = image_with()
    log = "\n".join([
        'a.obj : error LNK2001: unresolved external symbol "public: __thiscall Foo::Foo(int)" (??0Foo@@QAE@H@Z)',
        'b.obj : error LNK2001: unresolved external symbol "public: __thiscall Foo::Foo(int)" (??0Foo@@QAE@H@Z)',
        "c.obj : error LNK2001: unresolved external symbol g_00401010"])
    detail = {"??0Foo@@QAE@H@Z": {"kind": "unpinned"}, "g_00401010": {"kind": "g_text:dump-reference"}}
    rows = [{"name": "??0Foo@@QAE@XZ", "target_rva": "0x00001200", "source": "game/Foo.cpp"},
            {"name": "?body@@YAXXZ", "target_rva": "0x00001010", "source": "game/Body.cpp"}]
    data_scaffold.write_queue(tmp_path / "queue.csv", log, detail, rows, img)
    out = list(reloc_ledger.read_csv_rows(tmp_path / "queue.csv"))
    assert [r["name"] for r in out] == ["??0Foo@@QAE@H@Z", "g_00401010"]
    assert out[0]["referring_objects"] == "2" and out[0]["cause"] == "ctor/dtor (private class copies)"
    assert out[0]["suggested_owner_row"] == "??0Foo@@QAE@XZ" and "same-qualified-name" in out[0]["evidence"]
    assert out[1]["suggested_owner_row"] == "?body@@YAXXZ" and "address-derived" in out[1]["evidence"]
