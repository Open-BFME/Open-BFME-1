"""dump_relocs: typing the references in a retail byte dump."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import dump_relocs as D  # noqa: E402

BASE = 0x400000
TEXT, RDATA, DATA, IDATA = 0x401000, 0x402000, 0x403000, 0x403800
BODY = 0x401100


def context(rows=(), dir32=None, iat=None, rdata=b"", data=b""):
    """A Context over a synthetic image; rows are (va, size, symbol)."""
    ctx = object.__new__(D.Context)
    image = bytearray(0x4000)                                           # mapped: offset = VA - BASE
    image[RDATA - BASE:RDATA - BASE + len(rdata)] = rdata
    image[DATA - BASE:DATA - BASE + len(data)] = data
    ctx.mapped = bytes(image)
    ctx.base, ctx.image_end = BASE, 0x404000
    ctx.sections = [(".text", TEXT, RDATA), (".rdata", RDATA, DATA), (".data", DATA, IDATA),
                    (".idata", IDATA, 0x404000)]
    ctx.row_starts = sorted(va for va, _, _ in rows)
    ctx.row_info = {va: (size, [symbol], [symbol]) for va, size, symbol in rows}
    ctx.multibody = set()
    ctx.dir32 = {va: set(names) for va, names in (dir32 or {}).items()}
    ctx.iat = dict(iat or {})
    ctx.ghidra, ctx.exports, ctx.vtables = set(), set(), set()
    ctx._ghidra_sorted = []
    return ctx


def poke(ctx, va, raw):
    ctx.mapped = ctx.mapped[:va - BASE] + bytes(raw) + ctx.mapped[va - BASE + len(raw):]


def call(at, to):
    return b"\xe8" + struct.pack("<i", to - (at + 5))


def run(code, ctx, va=BODY):
    return D.classify(bytes(code), va, ctx, "?body@@YAXXZ")


def test_rel32_leaving_the_body_is_exact_and_intra_body_branches_stay():
    callee = 0x401800
    code = b"\x85\xc0" + b"\x74\x05" + call(BODY + 4, callee) + b"\xc3"   # test; je +5; call; ret
    ctx = context(rows=[(callee, 0x20, "?callee@@YAXXZ"), (BODY, len(code), "?body@@YAXXZ")])
    c = run(code, ctx)
    assert [(r["site"], r["kind"], r["symbol"], r["addend"]) for r in c["relocs"]] == \
        [(5, D.REL32, "?callee@@YAXXZ", 0)]
    assert c["info"]["intra-branch"] == 1 and not c["failures"] and not c["ambiguous"]


def test_rel32_into_the_middle_of_a_row_keeps_an_addend():
    ctx = context(rows=[(0x401800, 0x40, "?big@@YAXXZ")])
    c = run(call(BODY, 0x401810) + b"\xc3", ctx)
    assert (c["relocs"][0]["symbol"], c["relocs"][0]["addend"], c["relocs"][0]["cls"]) == \
        ("?big@@YAXXZ", 0x10, "row-interior")


def test_rel8_leaving_the_body_is_a_failure():
    c = run(b"\x74\x10\xc3", context())
    assert [f[0] for f in c["failures"]] == ["rel8-leaves-body"]


def test_absolute_disp32_is_dir32_to_its_owner():
    code = (b"\xa1" + struct.pack("<I", DATA + 0x10)            # mov eax, [g]
            + b"\xff\x15" + struct.pack("<I", IDATA + 4)        # call [IAT]
            + b"\x8b\x04\x85" + struct.pack("<I", DATA + 0x40)  # mov eax, [eax*4 + table]
            + b"\xc3")
    ctx = context(dir32={IDATA + 4: {"__imp__Sleep@4", "__imp__Other@4"}}, iat={IDATA + 4: "KERNEL32.dll!Sleep"})
    got = [(r["site"], r["symbol"], r["cls"], r["rule"]) for r in run(code, ctx)["relocs"]]
    assert got == [(1, "g_00403010", "data-anon", "mem-abs"),
                   (7, "__imp__Sleep@4", "import", "mem-abs"),
                   (14, "g_00403040", "data-anon", "mem-sib")]


def test_disp32_outside_the_image_is_literal():
    c = run(b"\xa1\x00\x00\xfe\x7f\xc3", context())   # mov eax, [0x7ffe0000]
    assert not c["relocs"] and c["info"]["abs-outside-image"] == 1


def test_two_names_at_one_address_are_recorded_not_picked():
    ctx = context(dir32={DATA + 8: {"?a@@3HA", "?b@@3HA"}})
    r = run(b"\xa1" + struct.pack("<I", DATA + 8) + b"\xc3", ctx)["relocs"][0]
    assert r["symbol"] == "g_00403008" and r["cls"] == "data-multiname" and "names=2:" in r["evidence"]


def test_imm32_needs_a_witnessed_start_and_an_address_shaped_use():
    rdata = b"\0\0\0\0hello\0"
    code = (b"\x68" + struct.pack("<I", RDATA + 4)         # push "hello"       -> string
            + b"\x68" + struct.pack("<I", DATA + 0x20)     # push unwitnessed   -> ambiguous
            + b"\x25" + struct.pack("<I", TEXT)            # and eax, TEXT      -> arithmetic, ambiguous
            + b"\x68" + struct.pack("<I", 0x401800)        # push row start     -> start:row
            + b"\xc3")
    ctx = context(rows=[(0x401800, 0x10, "?fn@@YAXXZ")], rdata=rdata)
    c = run(code, ctx)
    assert [(r["site"], r["evidence"].split(";")[0]) for r in c["relocs"]] == [(1, "string"), (16, "start:row")]
    assert [(a[0], a[3]) for a in c["ambiguous"]] == [(6, "imm-no-witnessed-start"), (11, "imm-and")]


def test_imm32_used_as_this_pointer_is_an_address():
    code = b"\xb9" + struct.pack("<I", DATA + 0x30) + call(BODY + 5, 0x401800) + b"\xc3"  # mov ecx, g; call
    c = run(code, context(rows=[(0x401800, 0x10, "?m@C@@QAEXXZ")]))
    assert [(r["site"], r["evidence"].split(";")[0]) for r in c["relocs"] if r["kind"] == D.DIR32] == [(1, "this-call")]


def test_jump_table_inside_the_body_relocates_each_entry_to_the_body():
    # cmp eax,2; ja case0; jmp [eax*4+T]; case0: ret; case1: ret; case2: xor eax,eax; ret; filler; T: dd case0..2
    table = 0x14
    code = bytearray(b"\x83\xf8\x02" + b"\x77\x07" +b"\xff\x24\x85" + struct.pack("<I", BODY + table)
                     + b"\xc3" + b"\xc3" + b"\x33\xc0\xc3" + b"\x8d\x49\x00")
    assert len(code) == table
    for case in (0x0C, 0x0D, 0x0E):
        code += struct.pack("<I", BODY + case)
    c = run(code, context())
    tables = [(r["site"], r["symbol"], r["addend"]) for r in c["relocs"] if r["rule"] == "jumptable"]
    assert tables == [(0x14, "?body@@YAXXZ", 0x0C), (0x18, "?body@@YAXXZ", 0x0D), (0x1C, "?body@@YAXXZ", 0x0E)]
    self_disp = [r for r in c["relocs"] if r["rule"] == "mem-sib"]
    assert (self_disp[0]["symbol"], self_disp[0]["addend"]) == ("?body@@YAXXZ", table)
    assert not c["failures"] and not c["ambiguous"]      # the 8d 49 00 filler is padding, not unreached


def test_jump_table_after_the_body_is_emitted_as_its_own_labelled_table():
    code = (b"\x83\xf8\x01" + b"\x77\x08" + b"\xff\x24\x85" + struct.pack("<I", BODY + 0x20)
            + b"\xc3" + b"\x33\xc0\xc3")
    image_table = struct.pack("<II", BODY + 0x0C, BODY + 0x0D)
    ctx = context()
    poke(ctx, BODY + 0x20, image_table)
    c = run(code, ctx)
    assert [(t["label"], t["va"], len(t["relocs"])) for t in c["tables"]] == [("g_00401120", 0x401120, 2)]
    assert [(r["addend"]) for r in c["tables"][0]["relocs"]] == [0x0C, 0x0D]
    assert not c["failures"]


def test_unreached_bytes_are_reported_with_their_address_like_dwords():
    code = b"\xc3" + b"\x55" + struct.pack("<I", DATA)     # ret; then bytes nothing reaches
    c = run(code, context())
    assert [f[0] for f in c["failures"]] == ["unreached"]
    assert [(a[0], a[3]) for a in c["ambiguous"]] == [(2, "unreached-dword")]
    assert not c["relocs"]


def test_body_that_stops_mid_instruction_or_falls_through_fails():
    assert [f[0] for f in run(b"\x5e", context())["failures"]] == ["falls-off-end"]


def test_trailing_call_to_a_returning_function_is_a_boundary_defect():
    """Regression (review of cb480bffec): a truncated body ending in a call was `exact`."""
    code = b"\x6a\x00" + call(BODY + 2, 0x401800)
    ctx = context(rows=[(0x401800, 1, "?returning@@YAXXZ")])
    poke(ctx, 0x401800, b"\xc3")                                       # the callee is `ret`
    assert [f[0] for f in run(code, ctx)["failures"]] == ["falls-off-end-after-call"]


def test_trailing_call_to_a_noreturn_import_ends_the_body():
    slot = IDATA + 8
    thunk = 0x401800                                                    # jmp [slot]
    ilt = 0x401810                                                      # jmp thunk
    ctx = context(iat={slot: "MSVCR71.dll!_CxxThrowException"})
    poke(ctx, thunk, b"\xff\x25" + struct.pack("<I", slot))
    poke(ctx, ilt, b"\xe9" + struct.pack("<i", thunk - (ilt + 5)))
    for code in (b"\x6a\x00" + call(BODY + 2, ilt),                     # through ILT and import thunk
                 b"\x6a\x00\xff\x15" + struct.pack("<I", slot)):        # call [IAT] directly
        c = run(code, ctx)
        assert c["failures"] == [] and c["info"]["falls-off-end-after-noreturn"] == 1
    ctx.iat[slot] = "KERNEL32.dll!Sleep"
    assert [f[0] for f in run(b"\x6a\x00\xff\x15" + struct.pack("<I", slot), ctx)["failures"]] == \
        ["falls-off-end-after-call"]


def test_cmp_against_a_known_function_address_is_listed_not_relocated():
    """Regression (review of cb480bffec): `cmp [esp+24h], 0F00000h` was relocated to a function."""
    code = b"\x3d" + struct.pack("<I", 0x401800) + b"\xc3"             # cmp eax, <row start>
    c = run(code, context(rows=[(0x401800, 1, "?fn@@YAXXZ")]))
    assert c["relocs"] == []
    assert [(a[0], a[3], a[5]) for a in c["ambiguous"]] == [(1, "imm-cmp", "start:row")]


def test_mapped_image_reads_zero_past_a_sections_raw_data():
    """Regression (audit of cb480bffec): a raw read of .data's zero-filled tail found the
    next section's file bytes and witnessed a string ('tDevCaps') that is not in memory."""
    header = bytearray(0x400)
    header[0:2] = b"MZ"
    struct.pack_into("<I", header, 0x3C, 0x80)
    header[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HH", header, 0x84, 0x14C, 2)                      # machine, two sections
    struct.pack_into("<H", header, 0x94, 0xE0)                           # optional header size
    struct.pack_into("<I", header, 0x98 + 28, BASE)
    struct.pack_into("<I", header, 0x98 + 56, 0x3000)                    # SizeOfImage
    struct.pack_into("<I", header, 0x98 + 60, 0x400)                     # SizeOfHeaders
    table = 0x98 + 0xE0
    # .data: 0x1000 virtual over 0x200 raw at file 0x400; .next: raw right after it
    header[table:table + 8] = b".data\0\0\0"
    struct.pack_into("<IIII", header, table + 8, 0x1000, 0x1000, 0x200, 0x400)
    header[table + 40:table + 48] = b".next\0\0\0"
    struct.pack_into("<IIII", header, table + 48, 0x200, 0x2000, 0x200, 0x600)
    data = bytes(header) + b"\1" * 0x200 + b"\0tDevCaps\0".ljust(0x200, b"\0")
    base, end, sections, mapped = D.map_image(data)
    assert (base, end) == (BASE, BASE + 0x3000)
    assert sections == [(".data", BASE + 0x1000, BASE + 0x2000), (".next", BASE + 0x2000, BASE + 0x2200)]
    ctx = context()
    ctx.base, ctx.image_end, ctx.sections, ctx.mapped = base, end, sections, mapped
    assert ctx.read(BASE + 0x11FF, 2) == b"\1\0"                          # raw, then zero fill
    assert ctx.read(BASE + 0x1201, 8) == bytes(8)                          # the raw read gave tDevCaps
    assert ctx.read(BASE + 0x2001, 8) == b"tDevCaps"
    ctx.sections = [(".data", BASE + 0x1000, BASE + 0x2000), (".rdata", BASE + 0x2000, BASE + 0x2200)]
    assert ctx.start_evidence(BASE + 0x1201) is None
    assert ctx.start_evidence(BASE + 0x2001) == "string"


def test_pointer_embedded_in_the_body_is_listed_not_left_exact():
    """Regression (audit of cb480bffec): `mov eax, [BODY+6]; ret; dd callee` came out exact
    and the unaligned function pointer stayed at its retail address when moved."""
    code = b"\xa1" + struct.pack("<I", BODY + 6) + b"\xc3" + struct.pack("<I", 0x401800)
    c = run(code, context(rows=[(0x401800, 0x10, "?callee@@YAXXZ")]))
    assert [(r["site"], r["symbol"], r["addend"]) for r in c["relocs"]] == [(1, "?body@@YAXXZ", 6)]
    assert [(a[0], a[1], a[3]) for a in c["ambiguous"]] == [(6, 0x401800, "embedded-data-dword")]
    assert c["analysis"]["untyped"] == [(6, 10)]


def test_verifier_fails_an_unmoved_value_in_embedded_data(tmp_path, monkeypatch):
    code = b"\xa1" + struct.pack("<I", BODY + 6) + b"\xc3" + struct.pack("<I", 0x401800)
    analysis = {"insns": {0: D.decode(code, 0, BODY), 5: D.decode(code, 5, BODY)},
                "ambiguous_sites": set(), "untyped": [(6, 10)]}
    reloc = {"site": 1, "kind": D.DIR32, "symbol": "?body@@YAXXZ", "addend": 6, "target": BODY + 6}
    monkeypatch.setattr(D, "read_object", lambda path: (
        {".text$d": (code[:1] + struct.pack("<I", 6) + code[5:], [(1, D.DIR32, "?body@@YAXXZ")])},
        {"?body@@YAXXZ": (".text$d", 0)}))
    errors = D.verify_file(tmp_path / "x.obj", [("?body@@YAXXZ", BODY, code, [reloc], analysis)], {},
                           lambda v: BASE + 0x1000 <= v < 0x404000)["?body@@YAXXZ"]
    assert errors == ["+0x6 embedded value 0x401800 did not move"]
    analysis["ambiguous_sites"] = {6}
    assert D.verify_file(tmp_path / "x.obj", [("?body@@YAXXZ", BODY, code, [reloc], analysis)], {},
                         lambda v: BASE + 0x1000 <= v < 0x404000)["?body@@YAXXZ"] == []


def test_lea_of_an_instruction_address_does_not_make_code_into_data():
    """Regression (audit of cb480bffec): `lea eax, [0C8E8F9h]` at 0xC8E8F9 blocked the code
    after it as a table and failed with decode-runs-into-table."""
    code = b"\x90" + b"\x8d\x05" + struct.pack("<I", BODY + 1) + b"\x50" + b"\x58\xc3"  # nop; lea eax,[self]
    c = run(code, context())
    assert c["failures"] == [] and c["ambiguous"] == [] and c["analysis"]["tables"] == {}
    assert [(r["site"], r["symbol"], r["addend"], r["rule"]) for r in c["relocs"]] == \
        [(3, "?body@@YAXXZ", 1, "mem-abs")]


toolchain = pytest.mark.skipif(sys.platform != "win32" or not (build.DEFAULT_VC71_ROOT / "Vc7" / "bin" / "ml.exe").exists(),
                               reason="MSVC 7.1 ml.exe on Windows")


@toolchain
def test_emitted_object_resolves_to_the_original_bytes_at_both_placements(tmp_path, monkeypatch):
    monkeypatch.setattr(D, "OUT", tmp_path)
    (tmp_path / "asm").mkdir()
    (tmp_path / "obj").mkdir()
    long_name = "?" + "x" * 300 + "@@YAXXZ"
    code = (call(BODY, 0x401800) + b"\x0f\x85" + struct.pack("<i", 0x401900 - (BODY + 11))
            + b"\xa1" + struct.pack("<I", DATA + 4) + b"\xc3")
    ctx = context(rows=[(0x401800, 0x10, long_name), (0x401900, 0x10, "?g@@YAXXZ"), (BODY, len(code), "?body@@YAXXZ")])
    c = D.classify(code, BODY, ctx, "?body@@YAXXZ")
    c["analysis"]["ambiguous_sites"] = set()
    summary = {"_hard": [], "ambiguous": 0, "unreached": 0, "reasons": ""}
    D.finish_source("t/x.asm", [("?body@@YAXXZ", BODY, code, c["relocs"], c["analysis"], summary, False)], ctx)
    assert summary["status"] == "exact", summary
    sections, defined = D.read_object(tmp_path / "obj" / "t_x.obj")
    raw, relocs = sections[defined["?body@@YAXXZ"][0]]
    assert sorted((o, t, s) for o, t, s in relocs) == [(1, D.REL32, long_name), (7, D.REL32, "?g@@YAXXZ"),
                                                       (12, D.DIR32, "g_00403004")]


@pytest.mark.skipif(not build.EXE.exists(), reason="retail baseline not present")
def test_real_body_0x000E27A0():
    """A 702-byte dump: EH prologue, 29 calls, an IAT load, a vtable store, a dtor pointer."""
    ctx = D.load_context()
    va = ctx.base + 0x000E27A0
    body = build.read_target_bytes(0x000E27A0, 702)
    c = D.classify(body, va, ctx, "?d_000e27a0@@YAXXZ", [g - va for g in ctx.ghidra_in(va, 702)])
    assert not c["failures"] and not c["ambiguous"]
    rel32 = [r["site"] for r in c["relocs"] if r["kind"] == D.REL32]
    dir32 = [(r["site"], r["rule"]) for r in c["relocs"] if r["kind"] == D.DIR32]
    assert len(rel32) == 30
    assert dir32 == [(0x3, "imm"), (0x7C, "mem-abs"), (0x265, "imm"), (0x28E, "imm")]
    assert {r["target"] for r in c["relocs"] if r["site"] == 0x7C} == {0x01358E54}


def test_output_root_groups_preserve_independent_verdicts(tmp_path):
    sources = ("game/gen_asm/a.asm", "game/masm_dumps/b.asm", "game/gen_small/dumps_000.cpp")
    statuses = ("exact", "failed", "ambiguous")
    summaries = [dict(source=source, symbol=f"body{i}", rva=i, size=1, status=status,
                      rel32=0, dir32=0, ambiguous=0, unreached=0, tables=0,
                      reasons="fixture" if status == "failed" else "", detail="")
                 for i, (source, status) in enumerate(zip(sources, statuses))]
    summary = D.write_outputs([], [], summaries, [], tmp_path)
    assert summary["by_root"] == {"gen_asm": {"exact": 1}, "masm_dumps": {"failed": 1},
                                  "other .asm": {"ambiguous": 1}}
    assert summary["status"] == {"exact": 1, "failed": 1, "ambiguous": 1}
    assert [row["status"] for row in summaries] == list(statuses)


# ----------------------------------------------------------------- retail .reloc authority

def test_retail_reloc_promotes_a_listed_cmp_and_drops_an_unlisted_one():
    # cmp eax, imm32 is never relocated by the heuristics; retail's .reloc decides
    code = (b"\x3d" + struct.pack("<I", DATA + 0x10)            # cmp eax, g   (site listed)
            + b"\x3d" + struct.pack("<I", DATA + 0x20)          # cmp eax, n   (not listed)
            + b"\xc3")
    ctx = context()
    ctx.reloc_sites = [BODY + 1]
    c = run(code, ctx)
    assert [(r["site"], r["symbol"], r["rule"]) for r in c["relocs"]] == [(1, "g_00403010", "retail-reloc")]
    assert not c["ambiguous"] and not c["failures"] and c["literal"] == {6}


def test_retail_reloc_demotes_a_heuristic_imm_it_does_not_list():
    # push 1000000h equals a row start: the heuristics call it an address, retail does not
    row = 0x401800
    code = b"\x68" + struct.pack("<I", row) + b"\xc3"
    ctx = context(rows=[(row, 0x10, "?f@@YAXXZ")])
    assert [r["rule"] for r in run(code, ctx)["relocs"]] == ["imm"]           # negative control: no table
    ctx.reloc_sites = []
    c = run(code, ctx)
    assert not c["relocs"] and not c["failures"] and c["literal"] == {1}


def test_retail_reloc_site_no_dir32_covers_fails_the_body():
    # bytes rewritten after link (protection stub): retail lists a site mid-instruction
    code = b"\xa1" + struct.pack("<I", DATA + 0x10) + b"\xc3"
    ctx = context()
    ctx.reloc_sites = [BODY + 1]
    assert not run(code, ctx)["failures"]                                    # agreeing table passes
    ctx.reloc_sites = [BODY + 2]
    assert {f[0] for f in run(code, ctx)["failures"]} == {"retail-reloc-conflict"}


def test_retail_relocs_parses_highlow_blocks_and_stops_at_padding():
    import retail_relocs
    block = struct.pack("<II", 0x5000, 12) + struct.pack("<HH", 0x3000 | 0x10, 0)
    sites, padding, used = retail_relocs.parse_blocks(block + b"\0" * 16)
    assert (sites, padding, used) == ([0x5010], 1, 12)
