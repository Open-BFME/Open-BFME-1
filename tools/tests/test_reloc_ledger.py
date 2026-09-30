import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_scaffold  # noqa: E402
import reloc_ledger  # noqa: E402

BASE = 0x400000


def make_pe(sections):
    """A minimal PE image: sections = [(name, rva, virtual size, raw bytes)]."""
    count = len(sections)
    pe = 0x40
    optional = 224
    headers = pe + 24 + optional + 40 * count
    raw_at = (headers + 0x1FF) & ~0x1FF
    table, body = bytearray(), bytearray()
    for name, rva, vsize, raw in sections:
        raw = bytes(raw)
        rsize = (len(raw) + 0x1FF) & ~0x1FF
        table += name.encode().ljust(8, b"\0") + struct.pack("<IIIIIIHHI", vsize, rva, rsize,
                                                              raw_at + len(body), 0, 0, 0, 0, 0x40000040)
        body += raw.ljust(rsize, b"\0")
    image_size = max(rva + vsize for _, rva, vsize, _ in sections)
    opt = bytearray(optional)
    struct.pack_into("<H", opt, 0, 0x10B)
    struct.pack_into("<I", opt, 28, BASE)
    struct.pack_into("<I", opt, 56, (image_size + 0xFFF) & ~0xFFF)
    struct.pack_into("<I", opt, 92, 16)
    head = bytearray(raw_at)
    struct.pack_into("<I", head, 0x3C, pe)
    head[pe:pe + 4] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", head, pe + 4, 0x14C, count, 0, 0, 0, optional, 0x102)
    head[pe + 24:pe + 24 + optional] = opt
    head[pe + 24 + optional:pe + 24 + optional + len(table)] = table
    return reloc_ledger.Image(bytes(head + body))


def image_with(rdata=b"", data=b"", data_vsize=None, text=b"\xc3" * 16):
    return make_pe([(".text", 0x1000, 0x1000, text), (".rdata", 0x2000, 0x1000, rdata),
                    (".data", 0x3000, data_vsize or 0x1000, data)])


def test_virtual_tail_reads_zero_and_sections_resolve():
    img = image_with(data=b"\x11\x22\x33\x44", data_vsize=0x2000)
    assert img.section(BASE + 0x3000) == ".data"
    assert img.read(BASE + 0x3000, 4) == b"\x11\x22\x33\x44"
    assert img.read(BASE + 0x3800, 4) == b"\0\0\0\0"
    assert img.is_data(BASE + 0x2004) and not img.is_data(BASE + 0x1004)


def coff_object(path, code, relocs, symbols, data_sections=()):
    """One .text section (code, relocs=[(offset, symbol index)]) plus data sections."""
    coff = data_scaffold.Coff()
    number = coff.add_section(".text", 0x60500020, code, len(code))
    coff.sections[number - 1]["relocs"] = list(relocs)
    for name, body in data_sections:
        coff.add_section(name, 0xC0300040, body, len(body))
    for name, value, section in symbols:
        coff.symbol(name, value, section, reloc_ledger.EXTERNAL if not name.startswith("$") else 3)
    coff.write(path)


def test_code_rows_read_targets_from_retail_and_refuse_literals(tmp_path, monkeypatch):
    # retail: mov eax,[0x402000]; mov eax,0 (our object relocates it); mov eax, fs:[__except_list]
    code_retail = b"\xa1" + struct.pack("<I", BASE + 0x2000) + b"\xb8" + b"\0\0\0\0" + b"\xa1\0\0\0\0\xc3"
    img = image_with(text=code_retail, rdata=b"DATA")
    monkeypatch.setattr(reloc_ledger, "_IMAGE", img)
    ours = b"\xa1\0\0\0\0\xb8\0\0\0\0\xa1\0\0\0\0\xc3"
    obj = tmp_path / "one.obj"
    coff_object(obj, ours, [(1, 1), (6, 2), (11, 3)],
                [("_f", 0, 1), ("_g_data", 0, 0), ("_g_other", 0, 0), ("__except_list", 0, 0)])
    out = reloc_ledger.scan_code((str(obj), [("_f", 0x1000, len(ours))]))
    assert out["rows_ok"] == 1
    assert [(r["site"], r["target"], r["symbol"]) for r in out["rows"]] == [(BASE + 0x1001, BASE + 0x2000, "_g_data")]
    assert ("_g_data", BASE + 0x2000, "_f+0x1") in out["names"]
    literal = {f["symbol"]: f["literal"] for f in out["literals"]}
    assert literal == {"_g_other": 0, "__except_list": 0}
    assert reloc_ledger.KNOWN_ABSOLUTE["__except_list"] == 0


def test_code_row_that_differs_from_retail_contributes_nothing(tmp_path, monkeypatch):
    img = image_with(text=b"\x90\xc3")
    monkeypatch.setattr(reloc_ledger, "_IMAGE", img)
    obj = tmp_path / "two.obj"
    coff_object(obj, b"\xcc\xc3", [], [("_f", 0, 1)])
    out = reloc_ledger.scan_code((str(obj), [("_f", 0x1000, 2)]))
    assert out["mismatch"] == 1 and out["rows"] == []


def test_placed_data_section_is_verified_or_contradicted(tmp_path, monkeypatch):
    rdata = struct.pack("<I", BASE + 0x2010) + b"XY"
    img = image_with(rdata=rdata)
    monkeypatch.setattr(reloc_ledger, "_IMAGE", img)
    obj = tmp_path / "three.obj"
    coff = data_scaffold.Coff()
    coff.add_section(".rdata", 0x40300040, b"\x10\0\0\0XY", 6)
    coff.sections[0]["relocs"] = [(0, 1)]
    coff.symbol("_table", 0, 1)
    coff.symbol("_target", 0, 0)
    coff.write(obj)
    good = reloc_ledger.scan_data((str(obj), {1: BASE + 0x2000}))
    assert good["verdicts"] == [(1, BASE + 0x2000, "verified")]
    # retail target 0x402010, our addend 0x10 -> _target lives at 0x402000
    assert good["rows"][0]["target"] == BASE + 0x2010 and good["rows"][0]["sym_va"] == BASE + 0x2000
    bad = reloc_ledger.scan_data((str(obj), {1: BASE + 0x2002}))
    assert bad["verdicts"][0][2] == "contradicted" and bad["rows"] == []


def funcinfo_image(action=BASE + 0x1000, magic=reloc_ledger.EH_MAGIC):
    funcinfo = struct.pack("<7I", magic, 2, BASE + 0x2020, 0, 0, 0, 0)
    unwind = struct.pack("<iIiI", -1, action, 0, 0)
    return image_with(rdata=funcinfo.ljust(0x20, b"\0") + unwind)


def test_funcinfo_walk_emits_every_pointer_field():
    s = reloc_ledger.Structures(funcinfo_image())
    assert s.funcinfo(BASE + 0x2000)
    assert sorted(s.rows) == [(BASE + 0x2008, BASE + 0x2020, "eh-funcinfo"),
                              (BASE + 0x2024, BASE + 0x1000, "eh-unwind-action")]
    assert s.items[BASE + 0x2000] == (28, "eh-funcinfo")
    assert s.items[BASE + 0x2020] == (16, "eh-unwindmap")


def test_funcinfo_walk_refuses_a_bad_field():
    assert not reloc_ledger.Structures(funcinfo_image(magic=0x19930521)).funcinfo(BASE + 0x2000)
    s = reloc_ledger.Structures(funcinfo_image(action=BASE + 0x2000))  # action must be code
    assert not s.funcinfo(BASE + 0x2000) and s.rows == []


def test_fieldparse_table_needs_strings_code_and_a_terminator():
    strings = b"Alpha\0\0\0Beta\0\0\0\0"
    table = struct.pack("<4I", BASE + 0x2000, BASE + 0x1000, 0, 4) + struct.pack("<4I", BASE + 0x2008,
                                                                                 BASE + 0x1004, BASE + 0x2000, 8)
    img = image_with(rdata=strings.ljust(0x20, b"\0") + table + b"\0" * 16)
    s = reloc_ledger.Structures(img)
    assert s.fieldparse(BASE + 0x2020, lambda v: v in (BASE + 0x1000, BASE + 0x1004))
    assert len(s.rows) == 5 and s.items[BASE + 0x2020] == (48, "ini-fieldparse")
    unterminated = image_with(rdata=strings.ljust(0x20, b"\0") + table + b"\x01" * 16)
    assert not reloc_ledger.Structures(unterminated).fieldparse(BASE + 0x2020, lambda v: True)


def test_mangled_data_types():
    assert reloc_ledger.mangled_scalar_size("?g_count@@3HA") == 4
    assert reloc_ledger.mangled_scalar_size("?s_scale@Foo@@2NA") == 8
    assert reloc_ledger.mangled_scalar_size("?TheNames@@3PAPBDA") is None  # pointer or array
    assert reloc_ledger.mangled_scalar_size("?TheData@@3UData@@A") is None
    assert reloc_ledger.mangled_scalar_size("_c_name") is None
    assert reloc_ledger.mangled_identity("?x@A@@2HA") == ("?x@A@@", "2HA")


def test_looks_string_ascii_and_wide():
    img = image_with(rdata=b"abc\0" + "wide".encode("utf-16-le") + b"\0\0" + b"\x01\x02\0")
    assert reloc_ledger.looks_string(img, BASE + 0x2000) == 4
    assert reloc_ledger.looks_string(img, BASE + 0x2004) == 10
    assert reloc_ledger.looks_string(img, BASE + 0x200E) == 0
