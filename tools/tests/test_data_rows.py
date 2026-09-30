import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import data_rows  # noqa: E402
import data_scaffold  # noqa: E402
from test_reloc_ledger import BASE, image_with  # noqa: E402

SECTIONS = [(".text", BASE + 0x1000, BASE + 0x2000), (".rdata", BASE + 0x2000, BASE + 0x3000),
            (".data", BASE + 0x3000, BASE + 0x5000)]


def ledger(*rows):
    lines = [data_rows.HEADER] + [",".join(r) for r in rows]
    return ("\n".join(lines) + "\n").encode()


def row(name="?g@@3HA", address="0x00403000", kind="va", size="4", section=".data",
        source="game/G.cpp", status="matched", evidence="ZH defines it", model="m"):
    return [name, address, kind, size, section, source, status, evidence, model]


def problems_of(raw, sources_ok=None):
    problems = []
    data_rows.check(raw, problems, sources_ok, SECTIONS)
    return problems


def test_a_clean_ledger_passes_and_rva_and_va_mean_the_same_place():
    assert problems_of(ledger(row(), row("?h@@3HA", "0x00003004", "rva"))) == []
    assert data_rows.va_of(dict(zip(data_rows.FIELDS, row(address="0x00003004", kind="rva")))) == BASE + 0x3004


def test_integrity_refusals():
    assert "address_kind" in problems_of(ledger(row(kind="")))[0]
    assert "overlaps" in problems_of(ledger(row(size="8"), row("?h@@3HA", "0x00403004")))[0]
    assert "one owner per address" in problems_of(ledger(row(), row("?h@@3HA")))[0]
    assert "one row per name" in problems_of(ledger(row(), row(address="0x00403008")))[0]
    assert "is in .data" in problems_of(ledger(row(section=".rdata")))[0]
    assert "no single retail section" in problems_of(ledger(row(address="0x00402FFE")))[0]
    assert "not tracked" in problems_of(ledger(row()), sources_ok=set())[0]
    assert "empty model" in problems_of(ledger(row(model="")))[0]
    assert "bad header" in problems_of(b"name,address\n")[0]


def compiled(tmp_path, monkeypatch, sections, symbols):
    """A fake object for game/G.cpp: sections [(name, flags, body, size, relocs)]."""
    coff = data_scaffold.Coff()
    for name, flags, body, size, relocs in sections:
        n = coff.add_section(name, flags, body, size)
        coff.sections[n - 1]["relocs"] = relocs
    for name, value, section in symbols:
        coff.symbol(name, value, section, 3 if name.startswith("$") else 2)
    obj = tmp_path / "G.obj"
    coff.write(obj)
    (tmp_path / "game").mkdir(exist_ok=True)
    (tmp_path / "game/G.cpp").write_text("// fixture\n")
    monkeypatch.setattr(data_rows, "ROOT", tmp_path)
    monkeypatch.setattr(data_rows._tools()[0], "obj_path", lambda source: obj)


def verify(img, entry, homes):
    return data_rows.verify_row(dict(zip(data_rows.FIELDS, entry)), img, lambda name: homes.get(name, set()),
                                compile=False)


def test_initialised_symbol_needs_retail_bytes_and_retail_pointers(tmp_path, monkeypatch):
    # retail .data at 0x403000: {0x00402010 (pointer to _target), 7}
    img = image_with(data=struct.pack("<2I", BASE + 0x2010, 7))
    body = struct.pack("<2I", 0, 7)
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, body, 8, [(0, 1)])], [("?t@@3PAUX@@A", 0, 1),
                                                                                  ("_target", 0, 0)])
    entry = row("?t@@3PAUX@@A", size="8")
    assert verify(img, entry, {"_target": {BASE + 0x2010}})[0]
    ok, message = verify(img, entry, {"_target": {BASE + 0x2020}})
    assert not ok and "retail points at 0x00402010" in message
    assert "no retail address" in verify(img, entry, {})[1]
    assert "size 4 unproven" in verify(img, row("?t@@3PAUX@@A", size="4"), {"_target": {BASE + 0x2010}})[1]


def test_initializer_bytes_must_equal_retail(tmp_path, monkeypatch):
    img = image_with(data=struct.pack("<I", 5))
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, struct.pack("<I", 6), 4, [])], [("?g@@3HA", 0, 1)])
    assert "differs" in verify(img, row(), {})[1]


def test_zero_filled_symbols_are_checked_alone_at_their_own_address(tmp_path, monkeypatch):
    # .bss holds ?b (8 bytes) then ?a (4): MSVC's by-name order is not retail's;
    # each symbol only needs retail zeros over its own extent at its own address
    img = image_with(data=bytes(4) + b"\x01" + bytes(11))
    compiled(tmp_path, monkeypatch, [(".bss", 0xC0300080, None, 12, [])], [("?b@@3NA", 0, 1), ("?a@@3HA", 8, 1)])
    assert verify(img, row("?a@@3HA", "0x00403000"), {})[0]            # retail order: a first
    assert verify(img, row("?b@@3NA", "0x00403008", size="8"), {})[0]
    ok, message = verify(img, row("?b@@3NA", "0x00403004", size="8"), {})
    assert not ok and "non-zero" in message


def test_a_relocation_to_a_tu_local_cannot_be_placed(tmp_path, monkeypatch):
    img = image_with(data=struct.pack("<I", BASE + 0x2000))
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(4), 4, [(0, 1)])],
             [("?p@@3PBDB", 0, 1), ("$SG1", 0, 2)])
    ok, message = verify(img, row("?p@@3PBDB"), {})
    assert not ok and "TU-local" in message


def test_provider_repair_data_mode_names_globals_and_ranks_the_queue(tmp_path):
    import provider_repair
    assert provider_repair.data_identifier("?OurLanguage@@3W4LanguageID@@A") == ("OurLanguage", "OurLanguage")
    assert provider_repair.data_identifier("?s_x@Foo@@2HA") == ("Foo::s_x", "s_x")
    assert provider_repair.data_identifier("??_7Foo@@6B@") is None
    queue = tmp_path / "queue.csv"
    queue.write_text("name,class,cause,referring_objects,referrers_first5,suggested_owner_row,evidence\n"
                     "?a@@3HA,data:unplaced,data:unplaced,1,,,\n"
                     "?b@@3HA,unpinned,static/global data,5,,,\n"
                     "?f@@YAXXZ,unpinned,other method or function,9,,,\n")
    assert [r["name"] for r in provider_repair.data_candidates(queue)] == ["?b@@3HA", "?a@@3HA"]
