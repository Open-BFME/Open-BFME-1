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


def compiled(tmp_path, monkeypatch, sections, symbols, source_text="// fixture\n"):
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
    (tmp_path / "game/G.cpp").write_text(source_text)
    monkeypatch.setattr(data_rows, "ROOT", tmp_path)
    monkeypatch.setattr(data_rows._tools()[0], "obj_path", lambda source: obj)


# what the compiler's sizeof probe answers for the fixture objects' symbols
SIZES = {"?t@@3PAUX@@A": 8, "?g@@3HA": 4, "?a@@3HA": 4, "?b@@3NA": 8, "?p@@3PBDB": 4}


def fixture_sizer(source, symbol):
    return (SIZES[symbol], "fixture sizeof") if symbol in SIZES else (None, "the sizeof probe does not compile")


def verify(img, entry, homes):
    return data_rows.verify_row(dict(zip(data_rows.FIELDS, entry)), img, lambda name: homes.get(name, set()),
                                compile=False, sizer=fixture_sizer)


def test_initialised_symbol_needs_retail_bytes_and_retail_pointers(tmp_path, monkeypatch):
    # retail .data at 0x403000: {0x00402010 (pointer to _target), 7}
    img = image_with(data=struct.pack("<2I", BASE + 0x2010, 7))
    body = struct.pack("<2I", 0, 7)
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, body, 8, [(0, 1)])],
             [("?t@@3PAUX@@A", 0, 1), ("_target", 0, 0)], "X *t[2] = { &target, (X *)7 };\n")
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
             [("?p@@3PBDB", 0, 1), ("$SG1", 0, 2)], 'const char *p = "x";\n')
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


def test_allocation_padding_is_not_a_size(tmp_path, monkeypatch):
    # a 4-byte int alone in an 8-byte allocation (4 bytes of alignment padding)
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(8), 8, [])], [("?g@@3HA", 0, 1)])
    img = image_with(data=bytes(8))
    ok, message = verify(img, row(size="8"), {})
    assert not ok and "size 8 unproven" in message
    assert verify(img, row(size="4"), {})[0]


def test_no_compiler_sizeof_no_size(tmp_path, monkeypatch):
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(8), 8, [])], [("?s@@3US@@A", 0, 1)])
    ok, message = verify(image_with(data=bytes(8)), row("?s@@3US@@A", size="8"), {})
    assert not ok and "unproven" in message and "does not compile" in message


def test_data_check_fails_closed_when_verification_exits_or_says_nothing(tmp_path, monkeypatch):
    from types import SimpleNamespace
    import provider_repair
    ledger = tmp_path / "data_rows.csv"
    ledger.write_bytes(ledger_bytes := data_rows.HEADER.encode() + b"\n"
                       + ",".join(row("?OurLanguage@@3W4LanguageID@@A")).encode() + b"\n")
    monkeypatch.setattr(data_rows, "DATA_ROWS", ledger)
    monkeypatch.setattr(data_rows, "check", lambda raw, problems, *a, **k: 1)
    monkeypatch.setattr(provider_repair, "OUT", tmp_path / "receipts")
    assert ledger_bytes

    def compiler_missing(**kwargs):
        raise SystemExit("VC71_ROOT does not exist")
    monkeypatch.setattr(data_rows, "verify", compiler_missing)
    assert provider_repair.cmd_data_check(SimpleNamespace(symbol="?OurLanguage@@3W4LanguageID@@A")) == 1
    monkeypatch.setattr(data_rows, "verify", lambda **kwargs: 0)  # returns, logs nothing
    assert provider_repair.cmd_data_check(SimpleNamespace(symbol="?OurLanguage@@3W4LanguageID@@A")) == 1
    monkeypatch.setattr(data_rows, "verify", lambda **kwargs: kwargs["log"]("Data rows: OK (1 row(s))"))
    assert provider_repair.cmd_data_check(SimpleNamespace(symbol="?OurLanguage@@3W4LanguageID@@A")) == 0


def test_reference_definitions_count_only_file_scope(monkeypatch):
    _toolchain()
    import provider_repair
    ref = data_rows.ROOT / "build" / "data_rows" / "test_provider" / "Code"
    ref.mkdir(parents=True, exist_ok=True)
    (ref / "Local.cpp").write_text("void f() {\nint OurLanguage = 0;\n}\nstruct S { int OurLanguage; };\n")
    (ref / "Global.cpp").write_text("namespace N {\n}\n#if 0\nint OurLanguage = 2;\n#endif\n"
                                    "LanguageID OurLanguage = LANGUAGE_ID_US;\n")
    (ref / "Two.cpp").write_text("namespace Other {\nint OurLanguage;\n}\n")
    monkeypatch.setattr(provider_repair, "REFERENCE_ROOTS", (ref,))
    found, why = provider_repair.reference_definitions("OurLanguage")
    assert why is None and [(Path(f).name, n, t) for f, n, t in found] == [
        ("Global.cpp", 6, "LanguageID OurLanguage = LANGUAGE_ID_US;")]
    (ref / "Three.cpp").write_text("int OurLanguage;\n")
    found, _ = provider_repair.reference_definitions("OurLanguage")
    assert len(found) == 2  # two definitions: not served
    (ref / "Three.cpp").unlink()


def test_hooks_keep_a_data_only_source_under_verification(tmp_path):
    root = Path(__file__).resolve().parents[2]
    text = (root / ".githooks/pre-commit").read_text()
    start = text.index("import csv, os, sys\nclaimed =")
    hook_python = text[start:text.index("\nPY\n", start)]
    ledger = tmp_path / "targets/game/reverse"
    ledger.mkdir(parents=True)
    (ledger / "functions.csv").write_text("name,target_rva,target_size,status,source,notes\n")
    (ledger / "data_rows.csv").write_text(data_rows.HEADER + "\n" + ",".join(row(source="game/G.cpp")) + "\n")
    selectors = tmp_path / "selectors"
    selectors.write_bytes(b"game/G.cpp\0game/Other.cpp\0")
    import subprocess
    result = subprocess.run([sys.executable, "-", str(selectors)], input=hook_python, cwd=tmp_path,
                            capture_output=True, text=True, check=True)
    assert result.stdout == "game/Other.cpp\0"  # only the unowned source is dropped


def test_delta_sources_reports_changed_data_rows(monkeypatch):
    import delta_sources
    old = data_rows.HEADER + "\n" + ",".join(row()) + "\n"
    new = old + ",".join(row("?h@@3HA", "0x00403004", source="game/H.cpp")) + "\n"
    texts = {"A:" + delta_sources.DATA_ROWS: old, "B:" + delta_sources.DATA_ROWS: new}
    monkeypatch.setattr(delta_sources, "text_at", lambda spec: texts.get(spec, ""))
    assert delta_sources.data_delta_sources("A", "B") == ["game/H.cpp"]
    changed = new.replace("ZH defines it", "ZH defines it at line 3")
    texts["B:" + delta_sources.DATA_ROWS] = changed
    assert delta_sources.data_delta_sources("A", "B") == ["game/G.cpp", "game/H.cpp"]


def test_cpp_names_reach_namespaced_and_member_data_only():
    assert data_rows.cpp_name("?OurLanguage@@3W4LanguageID@@A") == "::OurLanguage"
    assert data_rows.cpp_name("?x@B@A@@2HA") == "::A::B::x"
    assert data_rows.cpp_name("_c_global") == "c_global"
    assert data_rows.cpp_name("?$S1@?1??f@@YAXXZ@4IA") is None


def test_the_compiler_sizes_what_a_textual_lookup_gets_wrong():
    """The review's real-MSVC case: A::Element is char, B::Element is long, and
    `using namespace B` makes `Element values[2]` 8 bytes. A textual parser
    picked A's typedef (2 bytes); the sizeof probe asks the compiler."""
    import pytest
    build = data_rows._tools()[0]
    if not (build.vc71_root() / "Vc7" / "bin" / "cl.exe").exists():
        pytest.skip("MSVC 7.1 toolchain not present")
    work = data_rows.ROOT / "build" / "data_rows" / "test_type_scope"
    work.mkdir(parents=True, exist_ok=True)
    source = work / "type_scope.cpp"
    source.write_text("namespace A { typedef char Element; }\nnamespace B { typedef long Element; }\n"
                      "using namespace B;\nElement values[2] = {0,0};\n")
    size, how = data_rows.compiled_size(source, "?values@@3PAJA")
    assert size == 8, how


def _toolchain():
    import pytest
    build = data_rows._tools()[0]
    if not (build.vc71_root() / "Vc7" / "bin" / "cl.exe").exists():
        pytest.skip("MSVC 7.1 toolchain not present")


def test_reference_lookup_refuses_a_file_it_cannot_preprocess_no_raw_fallback():
    _toolchain()
    import reloc_ledger
    work = data_rows.ROOT / "build" / "data_rows" / "test_reference"
    (work / "good").mkdir(parents=True, exist_ok=True)
    (work / "bad").mkdir(parents=True, exist_ok=True)
    (work / "good" / "g.cpp").write_text("unsigned short refTable[3] = { 67, 61, 59 };\n")
    (work / "bad" / "b.cpp").write_text('#include "missing_header.h"\nunsigned short refTable[3] = { 1, 2, 3 };\n')
    found, why = reloc_ledger.reference_definitions("refTable", roots=(work / "good",))
    assert why is None and [(line, text) for _, line, text in found] == [(1, "unsigned short refTable[3] = { 67, 61, 59 };")]
    found, why = reloc_ledger.reference_definitions("refTable", roots=(work / "good", work / "bad"))
    assert found is None and why.startswith("reference-not-preprocessable")


def test_prime_table_words_are_upstream_declared_unsigned_shorts():
    """The worklist's #1 data blocker: mpmath.cpp's primeTable holds 16-bit primes
    (0x0043003D = 67, 61) that read as in-image dwords. Our definition is the
    Zero Hour reference's own text and the compiler sizes it 3511 x 2."""
    _toolchain()
    import reloc_ledger
    source = data_rows.ROOT / "game/Libraries/Source/WWVegas/WWLib/mpmath.cpp"
    match = reloc_ledger._reference_match(source, "?primeTable@@3PAGA")
    assert match is not None and match[0] == 7022 and match[1] == "unsigned short primeTable[3511]"
    evidence = reloc_ledger.reference_evidence(source, ("?primeTable@@3PAGA", 0), 0x012DA1F0, 0x012DA212, {})
    assert evidence[0] == "reference-declaration"
    assert reloc_ledger.reference_evidence(source, ("?primeTable@@3PAGA", 0), 0x012DA1F0, 0x012DA1F0 + 7020, {}) is None


def test_data_next_reads_the_worklist_and_names_c_globals(tmp_path):
    import provider_repair
    assert provider_repair.data_identifier("___gameMemFreePtr") == ("__gameMemFreePtr", "__gameMemFreePtr")
    worklist = tmp_path / "worklist.csv"
    worklist.write_text("# model note\n"
                        "rank,blocker,family,verdict,unlock_files\n"
                        "1,?primeTable@@3PAGA,data,unknown,2\n"
                        "4,___gameMemFreePtr,data,unresolved,29\n"
                        "2,?compare@AsciiString@@QBEHABV1@@Z,provider,wrong,11\n"
                        "10,?g_bfmeDefaultBU@@3MA,data,code-literal,16\n"
                        "12,?TheWritableGlobalData@@3PAVGlobalData@@A,data,unresolved,14\n")
    tally = {}
    rows = provider_repair.data_candidates(worklist, tally)
    assert [r["name"] for r in rows] == ["___gameMemFreePtr", "?TheWritableGlobalData@@3PAVGlobalData@@A"]
    assert tally == {"typed-evidence-lane": 1, "code-literal-lane": 1}


def test_the_sizeof_probe_refuses_a_macro_named_like_the_symbol():
    _toolchain()
    work = data_rows.ROOT / "build" / "data_rows" / "test_macro"
    work.mkdir(parents=True, exist_ok=True)
    source = work / "macro.cpp"
    source.write_text("int values[2] = {0, 0};\nshort tiny;\n#define values tiny\n")
    size, how = data_rows.compiled_size(source, "?values@@3PAHA")
    assert size is None and "does not compile" in how
    source.write_text("int values[2] = {0, 0};\n")
    assert data_rows.compiled_size(source, "?values@@3PAHA")[0] == 8


def test_data_next_refuses_a_zh_line_that_defines_another_type():
    import provider_repair
    assert not provider_repair.type_agrees("?TheVictoryConditions@@3PAVVictoryConditions@@A",
                                           "VictoryConditionsInterface *TheVictoryConditions = 0;")
    assert provider_repair.type_agrees("?TheWritableGlobalData@@3PAVGlobalData@@A",
                                       "GlobalData* TheWritableGlobalData = 0;")
    assert provider_repair.type_agrees("?OurLanguage@@3W4LanguageID@@A", "LanguageID OurLanguage = LANGUAGE_ID_US;")
    assert not provider_repair.type_agrees("?OurLanguage@@3W4Other@@A", "LanguageID OurLanguage = LANGUAGE_ID_US;")


def test_only_a_compiler_proven_arithmetic_type_is_a_number():
    """review_20260930_1105: a pointer with the same reference declaration was a
    'proven scalar'. The compiler's own overload resolution decides now."""
    _toolchain()
    work = data_rows.ROOT / "build" / "data_rows" / "test_arith"
    work.mkdir(parents=True, exist_ok=True)
    source = work / "kinds.cpp"
    source.write_text("int *pointer = (int *)0x00401000;\n"
                      "unsigned short table[3] = { 67, 61, 59 };\n"
                      "double ratio = 1.5;\n"
                      "enum Kind { KA, KB };\nKind kind = KB;\n"
                      "struct Pair { float a, b; };\nPair pair = { 1.0f, 2.0f };\n"
                      "int **handle = 0;\n"
                      "short grid[2][2] = { {1, 2}, {3, 4} };\n")
    expect = {"?pointer@@3PAHA": False, "?table@@3PAGA": True, "?ratio@@3NA": True, "?kind@@3W4Kind@@A": False,
              "?pair@@3UPair@@A": False, "?handle@@3PAPAHA": False, "?grid@@3PAY01FA": False}
    for symbol, want in expect.items():
        assert data_rows.compiled_arithmetic(source, symbol)[0] is want, symbol


def test_data_next_uses_the_input_it_is_given(tmp_path, monkeypatch):
    import provider_repair
    seen = []
    monkeypatch.setattr(provider_repair, "data_candidates", lambda path, tally=None: seen.append(str(path)) or [])
    provider_repair.main(["data-next", "--no-claim", "--queue", str(tmp_path / "q.csv")])
    provider_repair.main(["data-next", "--no-claim", "--worklist", str(tmp_path / "w.csv")])
    provider_repair.main(["data-next", "--no-claim"])
    assert seen == [str(tmp_path / "q.csv"), str(tmp_path / "w.csv"), str(provider_repair.WORKLIST)]
