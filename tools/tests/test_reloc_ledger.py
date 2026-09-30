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


def test_crt_initializer_tables_are_linker_built(tmp_path):
    tables = tmp_path / "retail_tables.json"
    tables.write_text('{"XC": {"begin": "0x00403000", "end": "0x00403010"}, "XI": {"begin": null}}')
    ranges = reloc_ledger.linker_ranges(image_with(), tables)
    assert (BASE + 0x3000, BASE + 0x3014, "crt-table-XC") in ranges and len(ranges) == 1


def decoded(code, va=BASE + 0x1000):
    return next(reloc_ledger._md().disasm(code, va))


def test_scalar_access_needs_a_byte_word_or_float_element():
    addr = struct.pack("<I", BASE + 0x2000)
    site = BASE + 0x1003
    assert reloc_ledger.element_access(decoded(b"\x0f\xb6\x05" + addr), site)[0]          # movzx eax, byte
    assert reloc_ledger.element_access(decoded(b"\x66\x8b\x0d" + addr), site)[0]          # mov cx, word
    assert reloc_ledger.element_access(decoded(b"\xd9\x05" + addr), BASE + 0x1002)[0]     # fld dword
    assert not reloc_ledger.element_access(decoded(b"\xa1" + addr), BASE + 0x1001)[0]     # mov eax, dword
    assert not reloc_ledger.element_access(decoded(b"\x68" + addr), BASE + 0x1001)[0]     # push address
    assert not reloc_ledger.element_access(None, site)[0]


def test_an_object_is_vendored_when_its_rows_name_one_upstream_library(monkeypatch):
    monkeypatch.setattr(reloc_ledger.build, "row_object", lambda row: row["obj"])
    rows = [{"obj": "a.obj", "notes": "vendored=zlib-1.1.4"}, {"obj": "a.obj", "notes": "vendored=zlib-1.1.4;x"},
            {"obj": "b.obj", "notes": "vendored=lua-4.0.1"}, {"obj": "b.obj", "notes": ""},
            {"obj": "c.obj", "notes": "vendored=lua-4.0.1"}, {"obj": "c.obj", "notes": "vendored=zlib-1.1.4"},
            {"obj": "d.obj", "notes": "authored"}]
    assert reloc_ledger.vendored_objects(rows) == {"a.obj": "zlib-1.1.4", "b.obj": "lua-4.0.1"}


def scalar_fixture():
    # a section of two words at 0x402000: code reads ONE byte of the first word
    addr = BASE + 0x2000
    code = b"\x0f\xb6\x05" + struct.pack("<I", addr) + b"\xc3"
    img = image_with(text=code, rdata=struct.pack("<2I", BASE + 0x2010, BASE + 0x1000))
    key = ("fixture.obj", 1)
    comp = {"unrelocated": [(key, addr, 8, addr, BASE + 0x2010, ("_first", 0)),
                            (key, addr, 8, addr + 4, BASE + 0x1000, ("_second", 4))],
            "verdicts": {key: (addr, "verified")}}
    ledger = reloc_ledger.Ledger(img)
    ledger.add(BASE + 0x1003, reloc_ledger.DIR32, addr, "compiler", "code-dir32", "exact")
    return img, comp, ledger, {BASE + 0x1000: len(code)}


def test_one_byte_access_proves_neither_word():
    img, comp, ledger, bodies = scalar_fixture()
    counts, _ = reloc_ledger.prove_scalars(img, comp, ledger, [], bodies)
    assert counts == {"unproven": 2}
    assert BASE + 0x2004 not in ledger.rows


def test_every_byte_of_a_word_read_proves_that_word_only():
    img, comp, ledger, bodies = scalar_fixture()
    code = b"".join(b"\x0f\xb6\x05" + struct.pack("<I", BASE + 0x2000 + k) for k in range(4)) + b"\xc3"
    img = image_with(text=code, rdata=struct.pack("<2I", BASE + 0x2010, BASE + 0x1000))
    ledger = reloc_ledger.Ledger(img)
    for k in range(4):
        ledger.add(BASE + 0x1003 + 7 * k, reloc_ledger.DIR32, BASE + 0x2000 + k, "compiler", "code-dir32", "exact")
    counts, _ = reloc_ledger.prove_scalars(img, comp, ledger, [], {BASE + 0x1000: len(code)})
    assert counts == {"element-access": 1, "unproven": 1}
    assert ledger.rows[BASE + 0x2000]["provenance"] == "proven-scalar"


def test_vendored_tag_without_a_declaration_proves_nothing(monkeypatch, tmp_path):
    img, comp, ledger, _ = scalar_fixture()
    monkeypatch.setattr(reloc_ledger.build, "row_object", lambda row: Path("fixture.obj"))
    rows = [{"source": "nonexistent_upstream.c", "notes": "vendored=zlib-1.1.4"}]
    counts, _ = reloc_ledger.prove_scalars(img, comp, reloc_ledger.Ledger(img), rows, {})
    assert counts == {"unproven": 2}


def preprocessed(tmp_path, text, headers=""):
    """What cl -E would give for a fixture unit: headers, then the source."""
    return "#pragma pack(from-flags 8)\n" + headers + "\n" + text


def test_upstream_declaration_lays_out_the_element_type(tmp_path):
    headers = "typedef unsigned char uch;\ntypedef unsigned short ush;\ntypedef int (*compress_func)(int);\n"
    text = ("local const uch tab[4] = {1,2,3,4};\nconst char *names[] = {\"a\"};\n"
            "typedef struct config_s { ush good; ush lazy; compress_func func; } config;\n"
            "local const config configuration_table[2] = {{1,2,0},{3,4,0}};\n"
            "/* uch fake[1] = {0}; */\n")
    types = reloc_ledger.CTypes(tmp_path / "t.c", preprocessed=preprocessed(tmp_path, text, headers))
    tab = types.declaration("tab")
    assert tab == ("local const uch", (1, 1, [(0, 1, "scalar")]))
    assert reloc_ledger.scalar_bytes(tab[1], 0)
    assert not reloc_ledger.scalar_bytes(types.declaration("names")[1], 0)
    config = types.declaration("configuration_table")[1]
    assert config[0] == 8 and reloc_ledger.scalar_bytes(config, 0) and not reloc_ledger.scalar_bytes(config, 4)
    assert types.declaration("fake") is None
    assert reloc_ledger.c_name("?primeTable@@3PAGA") == "primeTable" and reloc_ledger.c_name("?a@B@@2HA") is None


def test_pack_pragmas_move_the_pointer_and_an_unknown_pack_proves_no_struct(tmp_path):
    text = ("#pragma pack(push,1)\ntypedef struct { char tag; double number; int *p; } Packed;\n"
            "const Packed tbl[1] = {{0,0,(int *)0x00401000}};\n#pragma pack(pop)\n"
            "typedef struct { char c; int *q; } Loose;\nconst Loose after[1] = {{0,0}};\n")
    types = reloc_ledger.CTypes(tmp_path / "packed.c", preprocessed=preprocessed(tmp_path, text))
    packed = types.declaration("tbl")[1]
    assert packed[0] == 13 and not reloc_ledger.scalar_bytes(packed, 9) and reloc_ledger.scalar_bytes(packed, 1)
    loose = types.declaration("after")[1]
    assert loose == (8, 4, [(0, 1, "scalar"), (4, 4, "pointer")])  # pack(pop) restored /Zp8
    unknown = reloc_ledger.CTypes(tmp_path / "raw.c", preprocessed=preprocessed(
        tmp_path, "#pragma pack(pop)\ntypedef struct { char c; } S;\nconst S s[1] = {{0}};\n"))
    assert unknown.declaration("s") is None  # popping an empty stack: pack state unknown
    src = tmp_path / "notpre.c"
    src.write_text(text)
    assert reloc_ledger.upstream_declaration(src, "tbl") is None  # no preprocessed unit, no struct layout


def test_vendored_declaration_proves_only_arithmetic_words(tmp_path, monkeypatch):
    src = tmp_path / "up.c"
    src.write_text("typedef struct { unsigned short a; unsigned short b; int *p; } pair;\n"
                   "const pair tbl[1] = {{1, 2, 0}};\n")
    addr = BASE + 0x2000
    img = image_with(rdata=struct.pack("<2I", BASE + 0x1000, BASE + 0x1000))
    key = ("up.obj", 1)
    comp = {"unrelocated": [(key, addr, 8, addr, BASE + 0x1000, ("_tbl", 0)),
                            (key, addr, 8, addr + 4, BASE + 0x1000, ("_tbl", 0))],
            "verdicts": {key: (addr, "verified")}}
    monkeypatch.setattr(reloc_ledger.build, "row_object", lambda row: Path("up.obj"))
    monkeypatch.setattr(reloc_ledger, "ROOT", tmp_path)
    monkeypatch.setattr(reloc_ledger, "preprocess", lambda source: preprocessed(tmp_path, source.read_text()))
    ledger = reloc_ledger.Ledger(img)
    counts, _ = reloc_ledger.prove_scalars(img, comp, ledger, [{"source": "up.c", "notes": "vendored=x-1"}], {})
    assert counts == {"vendored-declaration": 1, "unproven": 1}
    assert "sha256" in ledger.rows[addr]["origin"] and addr + 4 not in ledger.rows


def test_call_evidence_records_the_symbol_not_the_addend_shifted_destination(tmp_path, monkeypatch):
    import data_scaffold
    obj = tmp_path / "addend.obj"
    coff = data_scaffold.Coff()
    section = coff.add_section(".text", 0x60500020, b"\xe8" + struct.pack("<I", 4) + b"\xc3", 6)
    coff.symbol("_caller", 0, section)
    callee = coff.symbol("_callee")
    coff.sections[section - 1]["relocs"] = [(1, callee)]
    coff.write(obj)
    data = bytearray(obj.read_bytes())
    reloc_at = struct.unpack_from("<I", data, 20 + 24)[0]
    struct.pack_into("<H", data, reloc_at + 8, reloc_ledger.REL32)  # the writer emits DIR32
    obj.write_bytes(data)
    # retail: call 0x00401014 = _callee (0x00401010) + 4
    monkeypatch.setattr(reloc_ledger, "_IMAGE", image_with(text=b"\xe8" + struct.pack("<i", 0x1014 - 0x1005) + b"\xc3"))
    result = reloc_ledger.scan_code((str(obj), [("_caller", 0x1000, 6)]))
    assert result["calls"] == [("_callee", BASE + 0x1010, BASE + 0x1014)]


def test_scope_needs_the_full_qualified_name_and_live_branches():
    text = "namespace Other {\nint OurLanguage = 0;\n}\nint Other::x = 1;\n"
    assert reloc_ledger.file_scope_definitions(text, "OurLanguage") == []
    assert reloc_ledger.file_scope_definitions(text, "Other::OurLanguage") == [(2, "int OurLanguage = 0;")]
    assert reloc_ledger.file_scope_definitions("int Other::y = 0;\n", "Other::y") == [(1, "int Other::y = 0;")]
    chain = "#if 0\nint g = 1;\n#elif 0\nint g = 2;\n#else\nint g = 3;\n#endif\n"
    assert reloc_ledger.file_scope_definitions(chain, "g") == [(6, "int g = 3;")]
    assert reloc_ledger.file_scope_definitions("#ifdef X\nint g = 1;\n#endif\n", "g") is None  # unknown branch
    assert reloc_ledger.file_scope_definitions("namespace {\nint g = 1;\n}\n", "g") == []  # anonymous
    unit = '#line 1 "hdr.h"\nint g = 1;\n#line 1 "game/src.c"\nint h = 2;\n'
    assert reloc_ledger.file_scope_definitions(unit, "g", origin="game/src.c") == []
    assert reloc_ledger.file_scope_definitions(unit, "h", origin="game/src.c") == [(1, "int h = 2;")]


def test_a_c_unit_with_two_typedefs_of_one_name_lays_out_nothing(tmp_path):
    text = ("#pragma pack(from-flags 8)\ntypedef char Element;\ntypedef long Element;\n"
            "Element values[2] = {0,0};\n")
    assert reloc_ledger.CTypes(tmp_path / "t.c", preprocessed=text).declaration("values") is None
    cpp = ("#pragma pack(from-flags 8)\nnamespace A { typedef char Element; }\n"
           "namespace B { typedef long Element; }\nusing namespace B;\nElement values[2] = {0,0};\n")
    assert reloc_ledger.CTypes(tmp_path / "t.cpp", preprocessed=cpp).declaration("values") is None
