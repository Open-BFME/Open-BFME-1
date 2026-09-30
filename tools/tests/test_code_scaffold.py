import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import code_scaffold  # noqa: E402
import data_scaffold  # noqa: E402
import reloc_ledger  # noqa: E402
from test_reloc_ledger import BASE, image_with  # noqa: E402

FUNCLET = b"\x8d\x4d\xf0\xe9\0\0\0\0"          # lea ecx,[ebp-0x10]; jmp <dtor>
RETAIL = b"\x8d\x4d\xf0\xe9\x10\x00\x00\x00"


def funclet_object(path, labels=("$L100", "$L101"), second=FUNCLET):
    coff = data_scaffold.Coff()
    n = coff.add_section(".text", 0x60501020, FUNCLET + second, 16)
    coff.symbol("??1Dtor@@QAE@XZ")
    coff.sections[n - 1]["relocs"] = [(4, 0), (12, 0)]
    coff.symbol("?parent@@YAXXZ", 0, n)
    for k, label in enumerate(labels):
        coff.symbol(label, 8 * k, n, code_scaffold.STATIC)
    coff.write(path)
    return reloc_ledger.parse_coff(path.read_bytes())


def row(pin, parent="?parent@@YAXXZ"):
    return {"name": "uw_x", "target_rva": "0x00001000", "target_size": "8",
            "notes": f"gen-funclet;object-symbol={pin};parent={parent}"}


def test_appended_symbol_keeps_every_existing_index(tmp_path):
    path = tmp_path / "f.obj"
    sections, before = funclet_object(path)
    patched = code_scaffold.append_symbols(path.read_bytes(), [("g_00401000", 8, 1)])
    after_sections, after = reloc_ledger.parse_coff(patched)
    assert [after[i]["name"] for i in before] == [before[i]["name"] for i in before]
    added = after[max(after)]
    assert (added["name"], added["value"], added["section"], added["storage"]) == ("g_00401000", 8, 1, 2)
    assert after_sections[0]["body"] == sections[0]["body"] and after_sections[0]["relocs"] == sections[0]["relocs"]


def test_funclet_found_by_pin_or_by_the_parent_group(tmp_path):
    sections, symbols = funclet_object(tmp_path / "f.obj", second=b"\x90" * 8)
    sym, how = code_scaffold.find_funclet(sections, symbols, row("$L100"), RETAIL)
    assert (sym["name"], how) == ("$L100", "pin")
    # the pin renumbered onto a body that is not the funclet: the parent's group names it
    sym, how = code_scaffold.find_funclet(sections, symbols, row("$L101"), RETAIL)
    assert (sym["name"], how) == ("$L100", "parent-group")
    sym, how = code_scaffold.find_funclet(sections, symbols, row("$L101", parent="?other@@YAXXZ"), RETAIL)
    assert sym is None and how == "parent-group-0-hits"


def test_two_equal_labels_in_one_group_name_neither(tmp_path):
    sections, symbols = funclet_object(tmp_path / "f.obj")
    sym, how = code_scaffold.find_funclet(sections, symbols, row("$L999"), RETAIL)
    assert sym is None and how == "parent-group-2-hits"


def test_code_aliases_follow_ilt_stubs_and_need_an_exported_definer(tmp_path, monkeypatch):
    obj = tmp_path / "body.obj"
    coff = data_scaffold.Coff()
    n = coff.add_section(".text", 0x60500020, b"\xc3", 1)
    coff.symbol("?real@@YAXXZ", 0, n)
    coff.write(obj)
    rows = [{"name": "?real@@YAXXZ", "target_rva": "0x00001000", "target_size": "1", "notes": "",
             "source": "game/a.cpp"},
            {"name": "?j_00002000@@YAXXZ", "target_rva": "0x00002000", "target_size": "5",
             "notes": "target=0x00001000", "source": "game/b.cpp"}]
    monkeypatch.setattr(code_scaffold.build, "row_object", lambda r: obj)
    monkeypatch.setattr(code_scaffold.link_census, "pins",
                        lambda routes=None: {"?called@@YAXXZ": 0x2000, "?direct@@YAXXZ": 0x1000,
                                             "?nowhere@@YAXXZ": 0x3000})
    img = image_with(text=b"\xc3" * 0x1000)
    undefined = {"?called@@YAXXZ", "?direct@@YAXXZ", "?nowhere@@YAXXZ", "g_00401000"}
    table, why = code_scaffold.code_aliases(img, rows, undefined, {"?real@@YAXXZ"}, {}, dir32={}, calls={})
    assert table == {"?called@@YAXXZ": "?real@@YAXXZ", "?direct@@YAXXZ": "?real@@YAXXZ",
                     "g_00401000": "?real@@YAXXZ"}
    assert why["pinned:via-ilt"] == 1 and why["pinned:no-owner"] == 1
    assert BASE == 0x400000


def test_a_pin_is_read_as_rva_or_va_only_where_a_row_lives():
    owned = {0x1010}.__contains__
    assert code_scaffold.resolve_pin("?f@@YAXXZ", 0x00401010, owned) == (0x1010, "va")
    both = {0x1010, 0x401010}.__contains__
    assert code_scaffold.resolve_pin("?f@@YAXXZ", 0x00401010, both) == (None, "ambiguous-va-rva")
    assert code_scaffold.resolve_pin("?f@@YAXXZ", 0x00401010, both, {"?f@@YAXXZ": 0x00401010}) == (0x1010, "dir32")
    assert code_scaffold.resolve_pin("?f@@YAXXZ", 0x2000, both) == (None, "no-owner")


def test_where_verified_calls_land_decides_an_ambiguous_pin():
    both = {0x1010, 0x401010}.__contains__
    calls = {"?f@@YAXXZ": {0x1010}}
    assert code_scaffold.resolve_pin("?f@@YAXXZ", 0x00401010, both, {}, calls) == (0x1010, "call-target")


def test_contrary_call_evidence_fails_closed_instead_of_picking_an_exported_decoy(tmp_path, monkeypatch):
    obj = tmp_path / "decoy.obj"
    coff = data_scaffold.Coff()
    n = coff.add_section(".text", 0x60500020, b"\xc3", 1)
    coff.symbol("?decoy@@YAXXZ", 0, n)
    coff.write(obj)
    rows = [{"name": "?actual@@YAXXZ", "target_rva": "0x00401010", "target_size": "1", "notes": "",
             "source": "game/actual.cpp"},
            {"name": "?decoy@@YAXXZ", "target_rva": "0x00001010", "target_size": "1", "notes": "",
             "source": "game/decoy.cpp"}]
    monkeypatch.setattr(code_scaffold.link_census, "pins", lambda routes=None: {"?f@@YAXXZ": 0x401010})
    monkeypatch.setattr(code_scaffold.build, "row_object",
                        lambda row: obj if row["name"] == "?decoy@@YAXXZ" else tmp_path / "absent.obj")
    img = image_with(text=b"\xc3" * 0x1000)
    table, why = code_scaffold.code_aliases(img, rows, {"?f@@YAXXZ"}, {"?decoy@@YAXXZ"}, {}, dir32={},
                                            calls={"?f@@YAXXZ": {0x401010}})
    assert table == {} and why == {"pinned:no-exported-definer": 1}
    # evidence pointing at neither owned reading is a contradiction, reported
    assert code_scaffold.resolve_pin("?f@@YAXXZ", 0x401010, lambda r: True, {}, {"?f@@YAXXZ": {0x5000}}) \
        == (None, "evidence-contradicts-pin")
