"""link_cycle: the order/quarantine plan and the per-row measure's rules.

Each rule research 31 / the round-2 review found missing has a positive control
(the pilot's rule passes it, this one fails it) and a negative control."""
import collections
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_cycle as lc

B = lc.BASE


def test_order_name_drops_one_underscore():
    assert lc.order_name("_fill_00001000") == "fill_00001000"
    assert lc.order_name("__ehhandler$x") == "_ehhandler$x"
    assert lc.order_name("?f@@YAXXZ") == "?f@@YAXXZ"


def test_drift_names_the_unit_that_grew():
    items = [(0x1000, "_a", "unit"), (0x1010, "_fill_00001010", "fill"), (0x1020, "_b", "unit")]
    exact = {"_a": 0x1000, "_fill_00001010": 0x1010, "_b": 0x1020}
    assert lc.drift_culprits(items, exact) == ([], 0)
    grew = dict(exact, _fill_00001010=0x1014, _b=0x1024)          # _a linked 4 bytes longer
    assert lc.drift_culprits(items, grew)[0] == ["_a"]
    padded = dict(exact, _b=0x1030)                              # filler 'grew': _b's alignment padded it
    assert lc.drift_culprits(items, padded)[0] == ["_b"]


def test_fillers_cover_every_gap_split_at_cuts_and_groups():
    placed = [{"starts": [0x1010], "size": 0x10}]
    chunks = lc.filler_chunks(placed, [0x1008, 0x1030], 0x1000, 0x40)
    assert chunks == [(0x1000, 0x1008), (0x1008, 0x1010), (0x1020, 0x1030), (0x1030, 0x1040)]
    # BFME1 has one .text group (funclets beside their functions)
    assert lc.region(0x75B460) == ".text" and lc.group_of(".text$d0055e510") == ".text"
    assert lc.group_of(".text$x") == ".text$x"


def _unit(i, start, head="_f", cls=lc.EXTERNAL, secname=".text", flags=0x60100020, size=0x10):
    return {"id": i, "obj": f"o{i}.obj", "sec": 1, "secname": secname, "size": size, "comdat": True,
            "flags": flags, "rows": [{"size": size}], "starts": [start], "head": head, "head_cls": cls}


def test_plan_reasons():
    us = [_unit(0, 0x1000, "_a"), _unit(1, 0x1008, "_b"), _unit(2, 0x1020, "_c", cls=lc.STATIC),
          _unit(3, 0x1040, "_d", flags=0x60000020 | (5 << 20)),     # ALIGN_16 at 0x1040: fine
          _unit(4, 0x1058, "_e", flags=0x60000020 | (5 << 20)),     # ALIGN_16 at 0x1058: refused
          _unit(5, 0x75B460, "_x", secname=".text$x"), _unit(6, 0x1080, "_q")]
    placed, reasons, _ = lc.plan_order(us, {"_q"}, 0x1000, 0x7B8CE2)
    assert [u["head"] for u in placed] == ["_a", "_d"]
    assert us[1]["why"] == "overlaps previous unit"
    assert us[2]["why"] == "static COMDAT"
    assert us[4]["why"] == "retail start violates section alignment"
    assert us[5]["why"].startswith("section group mismatch")
    assert us[6]["why"].startswith("quarantined")


def test_closure_fillers_are_not_leaves():
    ok = {"a": True, "b": True, "c": True, "d": False}
    edges = {"a": {"b"}, "b": {("fill", 0x1000)}, "c": {"c"}, "e": {"d"}}
    # pilot rule (fillers are leaves): a and b close. Positive control: they no longer do.
    assert lc.greatest_closure(ok, edges, bad_targets=(), unknown_closes=True) == {"a", "b", "c"}
    assert lc.greatest_closure(ok, edges) == {"c"}                  # c: a self-cycle stays closed
    assert lc.greatest_closure({"x": True, "y": True}, {"x": {"y"}}) == {"x", "y"}   # negative control


def test_credit_counts_unique_bytes():
    assert lc.unique_bytes([(0, 10), (5, 15), (20, 30), (20, 30)]) == 25


def test_import_def_entries_follow_retail_names():
    retail = {"CreateFileA": {"kernel32.dll"}, "free": {"msvcr71.dll"}, "?x@@YAXXZ": {"msvcp71.dll"}}
    names = {"__imp__CreateFileA@28", "__imp__free", "__imp_?x@@YAXXZ", "__imp__NotRetail@4"}
    entries, missing = lc.import_def_entries(names, retail)
    assert entries == {"kernel32.dll": ["CreateFileA@28"], "msvcr71.dll": ["free"], "msvcp71.dll": ["?x@@YAXXZ"]}
    assert missing == ["__imp__NotRetail@4"]
    assert lc.import_name("GetUserNameA@8") == "GetUserNameA" and lc.import_name("free") == "free"


def test_coff_round_trip_with_absolute_symbol(tmp_path):
    p = lc.write_coff(tmp_path / "a.obj", [(".text$x", 0x60101020, b"\x90\xc3", 2)],
                      [("_f", 1, 0, lc.EXTERNAL), ("__except_list", -1, 0, lc.EXTERNAL)])
    secs, syms = lc.parse_coff(p.read_bytes())
    assert secs[0].name == ".text$x" and secs[0].size == 2 and secs[0].sel == 2
    by = {y.name: y for y in syms.values()}
    assert by["__except_list"].sec == -1 and by["_f"].sec == 1


def test_hardcoded_operand_needs_no_relocation():
    code = bytes.fromhex("8b0db0a3c200") + bytes.fromhex("c3")   # mov ecx,[0xc2a3b0]; ret
    assert lc.hardcoded_operands(code, B + 0x1000, set(), B + 0x1000, B + 0xADA000) == [2]
    assert lc.hardcoded_operands(code, B + 0x1000, {2, 3, 4, 5}, B + 0x1000, B + 0xADA000) == []
    # an opcode byte plus an immediate's low bytes (25 ff ff 00 = 0x00FFFF25) is not an operand
    masked = bytes.fromhex("25ffff00000d00000780c3")             # and eax,0xffff; or eax,0x80070000
    assert lc.hardcoded_operands(masked, B + 0x1000, set(), B + 0x1000, B + 0xADA000) == []
    tag = bytes.fromhex("68746e6900c3")                             # push 0x696E74 ("int")
    retail_data = (B + 0x7BA000, B + 0xADA000)
    assert lc.hardcoded_operands(tag, B + 0x1000, set(), *retail_data) == []
    assert lc.hardcoded_operands(tag, B + 0x1000, set(), *retail_data, starts={0x696E74}) == [1]
    small = bytes.fromhex("b810000000c3")                           # mov eax,0x10: not an address
    assert lc.hardcoded_operands(small, B + 0x1000, set(), B + 0x1000, B + 0xADA000) == []


# ---- a synthetic image for the measure ------------------------------------------------
def _sec(idx, name, size, relocs=(), ptr=0):
    s = lc.Sec()
    s.idx, s.name, s.size, s.ptr, s.flags, s.relocs, s.sel = idx, name, size, ptr, 0, list(relocs), 0
    return s


def _sym(i, name, sec, value=0, cls=lc.EXTERNAL):
    y = lc.Sym()
    y.i, y.name, y.value, y.sec, y.cls = i, name, value, sec, cls
    return y


class FakeObjs(lc.Objects):
    def __init__(self, table):
        super().__init__([])
        self.table = table

    def lookup(self, objbase, name):
        o = self.table.get(objbase)
        return (o, self.defined(o)[0][name]) if o and name in self.defined(o)[0] else None


def _measure(I, R, items, allsyms, objs=None, pins=None, ledger_starts=None, pub=None, pubobj=None):
    m = lc.Measure.__new__(lc.Measure)
    m.I, m.R, m.lbase, m.rbase = I, R, B, B
    m.isecs = {".text": (0x1000, 0x1000), ".data": (0x3000, 0x1000), ".stubd": (0x5000, 0x100)}
    m.ltext = m.isecs[".text"]
    m.items, m.istarts = sorted(items), [t[0] for t in sorted(items)]
    m.allsyms, m.avas = sorted(allsyms), [s[0] for s in sorted(allsyms)]
    m.pub, m.stat, m.pubobj = pub or {}, {}, pubobj or {}
    m.pins, m.objs, m.ledger_starts = pins or {}, objs or FakeObjs({}), ledger_starts or {}
    m.rimports, m.limports = {}, {}
    m._init_state()
    m.thunk_rows = set()
    return m


def _put(buf, at, raw):
    buf[at:at + len(raw)] = raw


def test_data_reference_checks_content_not_only_the_map():
    """Research 31: a datum that maps 1:1 but whose bytes differ from retail used to count."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, b"Default\0")
    _put(R, 0x3100, b"Default \0")                         # retail's literal is longer
    data_sec = _sec(2, ".rdata", 8)
    obj = ([_sec(1, ".text", 8), data_sec], {0: _sym(0, "_s", 2, 0, lc.STATIC)}, b"")
    m = _measure(I, R, [], [(0x3000, "_s", "a.obj")])
    fails, _, pinned = m.data_ref(0x3000, 0x3100, "_s", obj[1][0], obj, 0)
    assert fails == ["data-content:_s"] and not pinned
    _put(R, 0x3100, b"Default\0")                          # negative control
    m = _measure(I, R, [], [(0x3000, "_s", "a.obj")])
    assert m.data_ref(0x3000, 0x3100, "_s", obj[1][0], obj, 0)[0] == []


def test_data_reference_checks_the_pinned_address():
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, b"\1\2\3\4")
    _put(R, 0x3100, b"\1\2\3\4")
    obj = ([_sec(1, ".data", 4)], {0: _sym(0, "_g", 1)}, b"")
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": 0x3200})
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0)[0] == ["data-pin:_g"]
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": 0x3100})
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0) == ([], {("datum", (0x3000, 0x3100, 4))}, True)
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": B + 0x3100})   # pinned as a VA
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0)[0::2] == ([], True)


def test_repeated_section_names_are_all_kept():
    secs = lc.SectionList([(".data", 0x3000, 0x100), (".CRT", 0x4000, 0x10), (".data", 0x5000, 0x10)])
    assert secs[".data"] == (0x3000, 0x100)
    assert secs.name_at(0x3010) == ".data" and secs.name_at(0x5004) == ".data" and secs.name_at(0x6000) == "outside"


def test_communal_global_is_sized_by_its_reference():
    I, R = bytearray(0x6000), bytearray(0x6000)
    ref = ([_sec(1, ".text", 8)], {0: _sym(0, "?TheX@@3PAVX@@A", 0)}, b"")            # an extern
    definer = ([_sec(1, ".text", 8)], {0: _sym(0, "?TheX@@3PAVX@@A", 0, value=4)}, b"")  # COMMON, 4 bytes
    objs = FakeObjs({})
    objs.cache = {Path("d.obj"): definer}
    m = _measure(I, R, [], [(0x3000, "?TheX@@3PAVX@@A", "other.obj")], pub={"?TheX@@3PAVX@@A": 0x3000},
                 pubobj={"?TheX@@3PAVX@@A": "other.obj"}, objs=objs)
    assert m.data_ref(0x3000, 0x3100, "?TheX@@3PAVX@@A", ref[1][0], ref, 0)[0] == []
    _put(R, 0x3102, bytes.fromhex('01'))  # retail holds a non-zero byte there
    m = _measure(I, R, [], [(0x3000, "?TheX@@3PAVX@@A", "other.obj")], pub={"?TheX@@3PAVX@@A": 0x3000},
                 pubobj={"?TheX@@3PAVX@@A": "other.obj"}, objs=objs)
    assert m.data_ref(0x3000, 0x3100, "?TheX@@3PAVX@@A", ref[1][0], ref, 0)[0] == ["data-content:?TheX@@3PAVX@@A"]


def test_alternatename_alias_resolves_through_the_real_definition():
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, bytes.fromhex('07000000'))
    _put(R, 0x3100, bytes.fromhex('07000000'))
    definer = ([_sec(1, ".data", 4)], {0: _sym(0, "?Real@@3HA", 1)}, b"")
    ref = ([_sec(1, ".text", 8)], {0: _sym(0, "?Alias@@3HA", 0)}, b"")
    m = _measure(I, R, [], [(0x3000, "?Alias@@3HA", "d.obj"), (0x3000, "?Real@@3HA", "d.obj")],
                 objs=FakeObjs({"d.obj": definer}), pub={"?Alias@@3HA": 0x3000, "?Real@@3HA": 0x3000},
                 pubobj={"?Alias@@3HA": "d.obj", "?Real@@3HA": "d.obj"})
    assert m.data_ref(0x3000, 0x3100, "?Alias@@3HA", ref[1][0], ref, 0)[0] == []
    _put(R, 0x3100, bytes.fromhex('08'))  # the content check still applies
    m._init_state()
    assert m.data_ref(0x3000, 0x3100, "?Alias@@3HA", ref[1][0], ref, 0)[0] == ["data-content:?Alias@@3HA"]


def test_data_stub_and_vtable_code_pointer():
    I, R = bytearray(0x6000), bytearray(0x6000)
    m = _measure(I, R, [], [])
    assert m.data_ref(0x5004, 0x3100, "_x", None, None, 0)[0] == ["data-stub:_x"]
    # a vtable slot (DIR32) must translate through the unit/filler holding its target
    _put(I, 0x3000, struct.pack("<I", B + 0x1800))
    _put(R, 0x3100, struct.pack("<I", B + 0x1900))
    vt = ([_sec(1, ".rdata", 4, relocs=[(0, 0, lc.DIR32)])], {0: _sym(0, "??_7X@@6B@", 1)}, b"")
    items = [(0x1800, 0x1810, 0x1900, ("fill", 0x1900))]
    m = _measure(I, R, items, [(0x3000, "??_7X@@6B@", "a.obj")])
    fails, edges, _ = m.data_ref(0x3000, 0x3100, "??_7X@@6B@", vt[1][0], vt, 0)
    assert fails == [] and edges == {("datum", (0x3000, 0x3100, 4))}
    assert m.dnodes[(0x3000, 0x3100, 4)]["edges"] == {("fill", 0x1900)}   # a filler edge: not closed later
    m = _measure(I, R, [(0x1800, 0x1810, 0x1A00, ("unit", 1))], [(0x3000, "??_7X@@6B@", "a.obj")])
    assert m.data_ref(0x3000, 0x3100, "??_7X@@6B@", vt[1][0], vt, 0)[0] == ["data-codeptr:??_7X@@6B@"]


def _funcinfo(buf, at, unwind_to, base=B):
    _put(buf, at, struct.pack("<IiIIII", 0x19930520, len(unwind_to), base + at + 0x20, 0, 0, 0))
    for i, to in enumerate(unwind_to):
        _put(buf, at + 0x20 + 8 * i, struct.pack("<iI", to, 0))


def test_eh_thunk_counts_for_its_owner_only_when_funcinfo_matches():
    I, R = bytearray(0x6000), bytearray(0x6000)
    for buf, thunk, fi in ((I, 0x1C00, 0x3000), (R, 0x1D00, 0x3400)):
        _put(buf, thunk, b"\xb8" + struct.pack("<I", B + fi) + b"\xe9\0\0\0\0")
        _funcinfo(buf, fi, [-1, 0])
    m = _measure(I, R, [], [(0x1C00, "__ehhandler$?f@@YAXXZ", "a.obj")])
    assert m.code_ref(0x1C00, 0x1D00, "__ehhandler$?f@@YAXXZ", "?f@@YAXXZ") == (None, ("eh", 0x1C00))
    assert m.code_ref(0x1C00, 0x1D00, "x", "?g@@YAXXZ")[0].startswith("eh-foreign")   # not its owner
    _funcinfo(R, 0x3400, [-1, -1])                          # positive control: unwind map differs
    m = _measure(I, R, [], [(0x1C00, "__ehhandler$?f@@YAXXZ", "a.obj")])
    assert m.code_ref(0x1C00, 0x1D00, "x", "?f@@YAXXZ")[0] == "eh:unwind map differs"


def _twin_setup(callee_retail):
    """Linked other-name copy at 0x1C00 (call +0 -> 0x1800) vs retail row at 0x1D00."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    body = b"\xe8\0\0\0\0\xc3"
    _put(I, 0x1C00, b"\xe8" + struct.pack("<i", 0x1800 - 0x1C05) + b"\xc3")
    _put(R, 0x1D00, b"\xe8" + struct.pack("<i", callee_retail - 0x1D05) + b"\xc3")
    tw = ([_sec(1, ".text", 6, relocs=[(1, 0, lc.REL32)])], {0: _sym(0, "?copy@@YAXXZ", 1)}, body)
    items = [(0x1800, 0x1810, 0x1900, ("unit", 7))]
    m = _measure(I, R, items, [(0x1C00, "?copy@@YAXXZ", "b.obj")], objs=FakeObjs({"b.obj": tw}),
                 ledger_starts={0x1D00: 6})
    return m


def test_icf_twin_needs_resolved_relocations_not_masked_bytes():
    m = _twin_setup(0x1900)                                  # same bytes and same resolved callee
    assert m.code_ref(0x1C00, 0x1D00, "?copy@@YAXXZ", "?r@@YAXXZ") == (None, ("twin", 0x1C00, 0x1D00))
    m.judge_twins()
    assert m.twins[(0x1C00, 0x1D00)] == (True, "certified")
    assert m.twin_edges[(0x1C00, 0x1D00)] == {("unit", 7)}
    m = _twin_setup(0x1950)                                  # masked bytes equal, callee differs
    m.code_ref(0x1C00, 0x1D00, "?copy@@YAXXZ", "?r@@YAXXZ")
    m.judge_twins()
    assert m.twins[(0x1C00, 0x1D00)] == (False, "code-wrong")


def test_unmapped_call_without_ledger_target_fails():
    I, R = bytearray(0x6000), bytearray(0x6000)
    m = _measure(I, R, [], [(0x1C00, "?copy@@YAXXZ", "b.obj")])
    assert m.code_ref(0x1C00, 0x1D00, "?copy@@YAXXZ", "?r@@YAXXZ") == ("code-unmapped:?copy@@YAXXZ", None)


def test_relocs_records_every_failure_not_the_first():
    I, R = bytearray(0x6000), bytearray(0x6000)
    code = b"\xe8\0\0\0\0\xe8\0\0\0\0\x90"
    _put(I, 0x1000, b"\xe8" + struct.pack("<i", 0x1C00 - 0x1005) + b"\xe8" + struct.pack("<i", 0x1C00 - 0x100A) + b"\x90")
    _put(R, 0x1000, b"\xe8" + struct.pack("<i", 0x1D00 - 0x1005) + b"\xe8" + struct.pack("<i", 0x1D00 - 0x100A) + b"\x91")
    o = ([_sec(1, ".text", 11, relocs=[(1, 0, lc.REL32), (6, 1, lc.REL32)])],
         {0: _sym(0, "?a@@YAXXZ", 0), 1: _sym(1, "?b@@YAXXZ", 0)}, code)
    m = _measure(I, R, [], [])
    fails, _, masked, _, rels = m.relocs(0x1000, 0x1000, 11, o, 1, 0, "?f@@YAXXZ")
    assert fails == ["code-unmapped:?a@@YAXXZ", "code-unmapped:?b@@YAXXZ", "bytes:1"]
    assert masked == set(range(1, 5)) | set(range(6, 10))
    assert rels == [(1, lc.REL32, False), (6, lc.REL32, False)]


def test_absolute_except_list_compares_raw_value():
    I, R = bytearray(0x6000), bytearray(0x6000)
    code = b"\x64\xa1\0\0\0\0"
    _put(I, 0x1000, code)
    _put(R, 0x1000, code)
    o = ([_sec(1, ".text", 6, relocs=[(2, 0, lc.DIR32)])], {0: _sym(0, "__except_list", 0)}, code)
    m = _measure(I, R, [], [])
    assert m.relocs(0x1000, 0x1000, 6, o, 1, 0, "?f@@YAXXZ")[0] == []
    _put(I, 0x1002, struct.pack("<I", B + 0x5000))           # positive control: a stub, not absolute 0
    assert m.relocs(0x1000, 0x1000, 6, o, 1, 0, "?f@@YAXXZ")[0] == ["abs:__except_list"]


# ---- link-cycle-2: closure through data, shifted base, imports, selected copies, receipts ----
def _ptr_setup(target_linked, target_retail_bytes=b"BBBB", pins=None):
    """Linked datum A at 0x3000 holds a pointer (DIR32) to target_linked (_b at 0x3010
    or _c at 0x3020); retail's A at 0x3100 points at retail's B, 0x3110."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, struct.pack("<I", B + target_linked))
    _put(R, 0x3100, struct.pack("<I", B + 0x3110))
    _put(I, 0x3010, b"BBBB")
    _put(I, 0x3020, b"CCCC")
    _put(R, 0x3110, target_retail_bytes)
    syms = {0: _sym(0, "_a", 1), 1: _sym(1, "_b", 1, value=0x10), 2: _sym(2, "_c", 1, value=0x20)}
    target = 1 if target_linked == 0x3010 else 2
    o = ([_sec(1, ".data", 0x30, relocs=[(0, target, lc.DIR32)], ptr=0)], syms, bytes(0x30))
    objs = FakeObjs({"a.obj": o})
    objs.cache = {Path("a.obj"): o}
    m = _measure(I, R, [], [(0x3000, "_a", "a.obj"), (0x3010, "_b", "a.obj"), (0x3020, "_c", "a.obj")],
                 objs=objs, pins=pins, pub={"_a": 0x3000, "_b": 0x3010, "_c": 0x3020},
                 pubobj={"_a": "a.obj", "_b": "a.obj", "_c": "a.obj"})
    return m, o


def test_pointer_inside_data_must_reach_retails_datum():
    """link-cycle-1 masked data pointers inside data: a wrong pointer kept full credit."""
    m, o = _ptr_setup(0x3010)                                  # negative control: points at B, B equal
    fails, edges, _ = m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)
    assert fails == [] and edges == {("datum", (0x3000, 0x3100, 0x10))}
    a = m.dnodes[(0x3000, 0x3100, 0x10)]
    assert a["fails"] == [] and a["edges"] == {("datum", (0x3010, 0x3110, 0x10))}
    assert m.dnodes[(0x3010, 0x3110, 0x10)]["fails"] == []
    m, o = _ptr_setup(0x3020)                                  # positive control: points at C ("CCCC")
    m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)
    assert m.dnodes[(0x3020, 0x3110, 0x10)]["fails"] == ["data-content:_c"]
    ok = {("datum", k): not n["fails"] for k, n in m.dnodes.items()}
    edges = {("datum", k): n["edges"] for k, n in m.dnodes.items()}
    assert ("datum", (0x3000, 0x3100, 0x10)) not in lc.greatest_closure(ok, edges)   # A no longer closes


def test_pointer_inside_data_checks_pin_and_one_to_one():
    m, o = _ptr_setup(0x3010, pins={"_b": 0x3200})             # B pinned elsewhere
    assert m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)[0] == ["data-ptr-pin:_b"]
    m, o = _ptr_setup(0x3010)
    m.discover([(0x3010, 0x3120, "_b", o[1][1], o, 0, "addr")])   # code elsewhere maps B to another retail datum
    assert "data-ptr-fwd:_b" in m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)[0]


# ---- signed DIR32 addends (port of Open-BFME-2 0113e6e7a4, GPT-6.1-Sol rounds 1-4 there)
def _disp_setup(local, a_tail=b"GOOD", b_head=b"GOOD", L=0x3000):
    """_a, _b, _c (0x10 each) linked at L and at retail L + 0x100; a reference
    naming one of them from its own object (local) or from another one through
    the map. Linked, _a ends with `a_tail` and _b starts with `b_head`; retail
    has GOOD at both."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, L + 0xC, a_tail + b_head)
    _put(R, L + 0x10C, b"GOODGOOD")
    syms = {0: _sym(0, "_a", 1), 1: _sym(1, "_b", 1, value=0x10), 2: _sym(2, "_c", 1, value=0x20)}
    o = ([_sec(1, ".data", 0x30)], syms, bytes(0x30))
    allsyms = [(L, "_a", "a.obj"), (L + 0x10, "_b", "a.obj"), (L + 0x20, "_c", "a.obj")]
    if local:
        return _measure(I, R, [], allsyms), o, syms
    pub = {"_a": L, "_b": L + 0x10, "_c": L + 0x20}
    objs = FakeObjs({"a.obj": o})
    objs.cache = {Path("a.obj"): o}
    ref = ([_sec(1, ".text", 8)], {0: _sym(0, "_a", 0), 1: _sym(1, "_b", 0)}, b"")
    return _measure(I, R, [], allsyms, objs=objs, pub=pub, pubobj={k: "a.obj" for k in pub}), ref, ref[1]


@pytest.mark.parametrize("local", [True, False])
@pytest.mark.parametrize("before, addend", [(4, 0xFFFFFFFC), (2, 0xFFFFFFFE)])
@pytest.mark.parametrize("a_tail, b_head", [(b"GOOD", b"GOOD"), (b"BAD!", b"GOOD"), (b"GOOD", b"BAD!")])
def test_displacement_before_its_symbol_is_unresolved(local, before, addend, a_tail, b_head):
    """MSVC folds table[i - 1] into [reg*4 + table-4]: a DIR32 addend of -4. Read
    unsigned (0xFFFFFFFC), a symbol its own object defines reached the section's
    last datum at a negative retail start (data-extent). Signed, `_b-4` is an
    indexed read of _b, a direct read of _a's last bytes or (`_b-2`) both:
    judging _b alone credits a bad _a, judging _a alone a bad _b. Until both are
    judged it stays unresolved, whatever the bytes, on both paths."""
    m, o, syms = _disp_setup(local, a_tail, b_head)
    lt = 0x3010 - before
    fails, edges, _ = m.data_ref(lt, lt + 0x100, "_b", syms[1], o, addend)
    assert "data-unmapped:_b" in fails and edges == set()
    assert not [f for f in fails if f.startswith("data-extent")]


@pytest.mark.parametrize("local", [True, False])
def test_displacement_before_its_section_is_unresolved(local):
    m, o, syms = _disp_setup(local, L=0x3040)                         # _a-4: another section's bytes
    fails, edges, _ = m.data_ref(0x303C, 0x313C, "_a", syms[0], o, 0xFFFFFFFC)
    assert "data-unmapped:_a" in fails and edges == set()


@pytest.mark.parametrize("local", [True, False])
def test_displacement_inside_its_symbol_is_judged_by_it(local):
    m, o, syms = _disp_setup(local)                                   # control: _b+4
    assert m.data_ref(0x3014, 0x3114, "_b", syms[1], o, 4)[:2] == ([], {("datum", (0x3010, 0x3110, 0x10))})
    m, o, syms = _disp_setup(local, b_head=b"BAD!")
    assert m.data_ref(0x3014, 0x3114, "_b", syms[1], o, 4)[0] == ["data-content:_b"]


def _strictly_closed(m, recs):
    """Unit 0 in the strict closure of the rows and datums, the measure only:
    as measure() builds it, a unit is ok when every row is and holds the union
    of their edges (shift checks, twins, EH and dump edges are not modelled; the
    fixtures here have none)."""
    ok, edges = {}, {}
    for rec in recs:
        n = ("unit", rec["unit"]["id"])
        ok[n] = ok.get(n, True) and rec["measured"] and not rec["fails"]
        edges.setdefault(n, set()).update(rec["edges"])
    for key, node in m.dnodes.items():
        ok[("datum", key)], edges[("datum", key)] = not node["fails"], set(node["edges"])
    return ("unit", 0) in lc.greatest_closure(ok, edges)


def _indexed_row(addend, a_tail=b"GOOD", b_head=b"GOOD"):
    """A row `mov eax,[eax*4 + _b+addend]; ret` (DIR32 at +3 against _b, defined in
    d.obj's .data with _a and _c) measured end to end by Measure.run()."""
    disp = addend if addend >= 0 else addend + (1 << 32)
    code = b"\x8b\x04\x85" + struct.pack("<I", disp) + b"\xc3"
    a = Path("x/a.obj")
    row = ([_sec(1, ".text", 8, relocs=[(3, 1, lc.DIR32)], ptr=4)],
           {0: _sym(0, "?f@@YAXXZ", 1), 1: _sym(1, "_b", 0)}, b"\0" * 4 + code)
    data = ([_sec(1, ".data", 0x30)], {0: _sym(0, "_a", 1), 1: _sym(1, "_b", 1, value=0x10),
                                       2: _sym(2, "_c", 1, value=0x20)}, bytes(0x30))
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x1000, code[:3] + struct.pack("<I", B + 0x3010 + addend) + b"\xc3")
    _put(R, 0x1000, code[:3] + struct.pack("<I", B + 0x3110 + addend) + b"\xc3")
    _put(I, 0x300C, a_tail + b_head)
    _put(R, 0x310C, b"GOODGOOD")
    objs = FakeObjs({"d.obj": data})
    objs.cache[a] = row
    u = {"id": 0, "obj": str(a), "sec": 1, "secname": ".text", "size": 8, "head": "?f@@YAXXZ",
         "head_cls": lc.EXTERNAL, "starts": [0x1000],
         "rows": [{"name": "?f@@YAXXZ", "rva": 0x1000, "size": 8, "off": 0, "sym": "?f@@YAXXZ"}]}
    pub = {"?f@@YAXXZ": 0x1000, "_a": 0x3000, "_b": 0x3010, "_c": 0x3020}
    mapped = (pub, {}, sorted([(0x1000, "?f@@YAXXZ", "a.obj"), (0x3000, "_a", "d.obj"), (0x3010, "_b", "d.obj"),
                               (0x3020, "_c", "d.obj")]), {"?f@@YAXXZ": "a.obj", "_a": "d.obj", "_b": "d.obj", "_c": "d.obj"})
    m = lc.Measure([u], [], mapped, I, R, {".text": (0x1000, 0x1000), ".data": (0x3000, 0x1000)}, {}, {}, {}, objs,
                   {0x1000: 8})
    return m, m.run()


@pytest.mark.parametrize("a_tail, b_head", [(b"GOOD", b"GOOD"), (b"BAD!", b"GOOD"), (b"GOOD", b"BAD!")])
def test_indexed_read_before_its_symbol_never_credits_the_row(a_tail, b_head):
    """`[eax*4 + _b-4]` with eax = 1 reads _b; the row must not close whichever
    datum is wrong (Open-BFME-2's review round 2 reproduction, through run())."""
    m, recs = _indexed_row(-4, a_tail, b_head)
    rec = recs[0]
    assert rec["measured"] and "data-unmapped:_b" in rec["fails"] and not rec["edges"] & {
        ("datum", (0x3000, 0x3100, 0x10)), ("datum", (0x3010, 0x3110, 0x10))}
    assert not _strictly_closed(m, recs)
    m, recs = _indexed_row(4, a_tail, b_head)                         # control: inside _b
    assert recs[0]["fails"] == ([] if b_head == b"GOOD" else ["data-content:_b"])
    assert ("datum", (0x3010, 0x3110, 0x10)) in recs[0]["edges"]
    assert _strictly_closed(m, recs) == (b_head == b"GOOD")


def _common_pointer_row(addend):
    """A row `mov eax,[_D]; ret` whose datum _D (d.obj .data) holds a DIR32 pointer
    to COMMON _x + addend; _x is 4 bytes at linked 0x3040, retail 0x3140."""
    a = Path("x/a.obj")
    row = ([_sec(1, ".text", 6, relocs=[(1, 1, lc.DIR32)], ptr=4)],
           {0: _sym(0, "?f@@YAXXZ", 1), 1: _sym(1, "_D", 0)}, b"\0" * 4 + b"\xa1\0\0\0\0\xc3")
    disp = addend if addend >= 0 else addend + (1 << 32)
    data = ([_sec(1, ".data", 4, relocs=[(0, 1, lc.DIR32)], ptr=4)],
            {0: _sym(0, "_D", 1), 1: _sym(1, "_x", 0)}, b"\0" * 4 + struct.pack("<I", disp))
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x1000, b"\xa1" + struct.pack("<I", B + 0x3000) + b"\xc3")
    _put(R, 0x1000, b"\xa1" + struct.pack("<I", B + 0x3100) + b"\xc3")
    _put(I, 0x3000, struct.pack("<I", B + 0x3040 + addend))
    _put(R, 0x3100, struct.pack("<I", B + 0x3140 + addend))
    objs = FakeObjs({"d.obj": data})
    objs.cache[a] = row
    objs.cache[Path("c.obj")] = ([_sec(1, ".text", 4)], {0: _sym(0, "_x", 0, value=4)}, b"")  # COMMON, 4 bytes
    u = {"id": 0, "obj": str(a), "sec": 1, "secname": ".text", "size": 6, "head": "?f@@YAXXZ",
         "head_cls": lc.EXTERNAL, "starts": [0x1000],
         "rows": [{"name": "?f@@YAXXZ", "rva": 0x1000, "size": 6, "off": 0, "sym": "?f@@YAXXZ"}]}
    pub = {"?f@@YAXXZ": 0x1000, "_D": 0x3000, "_x": 0x3040}
    mapped = (pub, {}, [(0x1000, "?f@@YAXXZ", "a.obj"), (0x3000, "_D", "d.obj"), (0x3040, "_x", "other.obj")],
              {"?f@@YAXXZ": "a.obj", "_D": "d.obj", "_x": "other.obj"})
    m = lc.Measure([u], [], mapped, I, R, {".text": (0x1000, 0x1000), ".data": (0x3000, 0x1000)}, {}, {}, {}, objs,
                   {0x1000: 6})
    return m, m.run()


def test_pointer_before_a_common_global_fails_what_reaches_it():
    """Transitive: a datum holding `&_x - 4` (COMMON _x) is not resolved, so the
    datum fails and the row reading it does not close; `&_x` closes."""
    m, recs = _common_pointer_row(-4)
    assert any(f.endswith("unmapped:_x") for f in m.dnodes[(0x3000, 0x3100, 4)]["fails"])
    assert not _strictly_closed(m, recs)
    recs[0]["fails"] = []                                             # the edge alone keeps it out
    assert ("datum", (0x3000, 0x3100, 4)) in recs[0]["edges"] and not _strictly_closed(m, recs)
    m, recs = _common_pointer_row(0)                                  # control
    assert m.dnodes[(0x3000, 0x3100, 4)]["fails"] == [] and recs[0]["fails"] == []
    assert _strictly_closed(m, recs)


def test_displacement_before_a_common_global_is_unresolved():
    I, R = bytearray(0x6000), bytearray(0x6000)
    name = "?TheX@@3PAVX@@A"
    ref = ([_sec(1, ".text", 8)], {0: _sym(0, name, 0)}, b"")
    objs = FakeObjs({})
    objs.cache = {Path("d.obj"): ([_sec(1, ".text", 8)], {0: _sym(0, name, 0, value=4)}, b"")}  # COMMON, 4 bytes
    m = _measure(I, R, [], [(0x3040, name, "other.obj")], pub={name: 0x3040}, pubobj={name: "other.obj"}, objs=objs)
    assert m.data_ref(0x3040, 0x3140, name, ref[1][0], ref, 0)[0] == []                # control
    fails, edges, _ = m.data_ref(0x303C, 0x313C, name, ref[1][0], ref, 0xFFFFFFFC)
    assert f"data-unmapped:{name}" in fails and edges == set()


def _shifted(I, S):
    sh = lc.Shifted.__new__(lc.Shifted)
    sh.I, sh.S, sh.delta, sh.base_s, sh.why, sh.failed = I, S, lc.SHIFT_BASE - B, lc.SHIFT_BASE, None, collections.Counter()
    sh.lo, sh.hi, sh.starts = B + 0x1F00, B + 0x2000, set()
    return sh


def test_shifted_link_checks_every_relocation_moves():
    I, S = bytearray(0x2000), bytearray(0x2000)
    _put(I, 0x1000, b"\xa1" + struct.pack("<I", B + 0x1800) + b"\xc3")             # mov eax,[0x401800]; ret
    _put(S, 0x1000, b"\xa1" + struct.pack("<I", lc.SHIFT_BASE + 0x1800) + b"\xc3")
    sh = _shifted(I, S)
    rels, masked = [(1, lc.DIR32, False)], {1, 2, 3, 4}
    assert sh.code(0x1000, 6, masked, rels) is None                   # negative control
    _put(S, 0x1001, struct.pack("<I", B + 0x1800))                    # the word did not move
    assert sh.code(0x1000, 6, masked, rels) == "relocation not adjusted"
    raw = b"\xa1" + struct.pack("<I", B + 0x1F10) + b"\xc3"          # raw address: no relocation at all
    _put(I, 0x1100, raw)
    _put(S, 0x1100, raw)
    assert sh.code(0x1100, 6, set(), []) == "hardcoded address"
    sh.S, sh.why = None, "no shifted link"                            # nothing verified, nothing credited
    assert sh.code(0x1000, 6, masked, rels) == "no shifted link"


def test_shift_failure_invalidates_the_dependent_closure():
    """link-cycle-1 only flagged the row; its callers kept closed credit."""
    ok = {("unit", 1): True, ("unit", 2): True, ("unit", 3): True, ("datum", 9): False}
    edges = {("unit", 1): {("unit", 2)}, ("unit", 2): {("datum", 9)}, ("unit", 3): set()}
    assert lc.greatest_closure(ok, edges) == {("unit", 3)}            # the datum's pointer did not move
    ok[("datum", 9)] = True
    assert lc.greatest_closure(ok, edges) == {("unit", 1), ("unit", 2), ("unit", 3), ("datum", 9)}
    del ok[("datum", 9)]                                                # an edge the graph does not hold
    assert lc.greatest_closure(ok, edges) == {("unit", 3)}


def test_eh_tables_must_move_with_the_base():
    I, S = bytearray(0x6000), bytearray(0x6000)
    for buf, base in ((I, B), (S, lc.SHIFT_BASE)):
        _put(buf, 0x1C00, b"\xb8" + struct.pack("<I", base + 0x3000) + b"\xe9\0\0\0\0")
        _funcinfo(buf, 0x3000, [-1, 0], base=base)
    sh = _shifted(I, S)
    assert sh.eh(0x1C00) is None
    _put(S, 0x3008, struct.pack("<I", B + 0x3020))                     # unwind map pointer left at the old base
    assert sh.eh(0x1C00) in ("FuncInfo not adjusted", "FuncInfo unparsable")


def _import_measure(limports, rimports):
    I, R = bytearray(0x8000), bytearray(0x8000)
    m = _measure(I, R, [], [])
    m.isecs = lc.SectionList([(".text", 0x1000, 0x1000), (".rdata", 0x6000, 0x1000), (".data", 0x3000, 0x1000)])
    m.limports, m.rimports = limports, rimports
    return m


def test_import_identity_is_dll_and_name():
    k32, usr = lc.import_key("KERNEL32.dll", b"Foo"), lc.import_key("USER32.dll", b"Foo")
    m = _import_measure({0x6000: k32}, {0x6100: usr})
    assert m.data_ref(0x6000, 0x6100, "__imp__Foo@4", None, None, 0)[0] == ["import-mismatch:__imp__Foo@4"]
    m = _import_measure({0x6000: k32}, {0x6100: lc.import_key("kernel32.dll", "Foo")})
    assert m.data_ref(0x6000, 0x6100, "__imp__Foo@4", None, None, 0)[0] == []
    assert lc.import_key("ws2_32.dll", None, 23) == ("ws2_32.dll", "#23")
    assert lc.import_key("x.dll", "Bar@8") == ("x.dll", "Bar")


def test_duplicate_retail_iat_slots_are_one_import_only_when_read_through():
    """Retail has two IAT slots for msvcr71 strncpy; the link has one. A call through
    either reads the same function: equivalent. Taking a slot's address is not."""
    imp = lc.import_key("msvcr71.dll", "strncpy")
    m = _import_measure({0x6000: imp}, {0x6100: imp, 0x6104: imp})
    refs = [(0x6000, 0x6100, "__imp__strncpy", None, None, 0, "read"),
            (0x6000, 0x6104, "__imp__strncpy", None, None, 0, "read")]
    m.discover(refs)
    assert [m.ref_check(r)[0] for r in refs] == [[], []] and m.import_equiv == 2
    observe = (0x6000, 0x6104, "__imp__strncpy", None, None, 0, "addr")
    m.discover([observe])
    assert m.ref_check(observe)[0] == ["data-fwd:__imp__strncpy"]
    other = lc.import_key("msvcr71.dll", "toupper")                   # wrong import, read through: still fails
    m = _import_measure({0x6000: imp}, {0x6100: imp, 0x6104: other})
    bad = (0x6000, 0x6104, "__imp__strncpy", None, None, 0, "read")
    m.discover([bad, refs[0]])
    assert m.ref_check(bad)[0] == ["import-mismatch:__imp__strncpy", "data-fwd:__imp__strncpy"]


def test_read_through_operand_forms():
    assert lc.read_through(b"\xff\x15\0\0\0\0", 2)             # call [m32]
    assert lc.read_through(b"\xff\x25\0\0\0\0", 2)             # jmp [m32]
    assert lc.read_through(b"\x8b\x3d\0\0\0\0", 2)             # mov edi,[m32]
    assert lc.read_through(b"\xa1\0\0\0\0", 1)                 # mov eax,[m32]
    assert not lc.read_through(b"\x68\0\0\0\0", 1)             # push offset slot: address taken
    assert not lc.read_through(b"\xc7\x05\0\0\0\0", 2)         # mov [slot], imm: a store
    assert not lc.read_through(b"\x8d\x05\0\0\0\0", 2)         # lea eax,[slot]


def test_twin_is_judged_on_the_selected_copy_inside_its_section():
    """A section holding two functions: link-cycle-1 rejected the second on
    'extent' (offset != 0); the /MAP's copy at its own offset is judged now."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    body = b"\x90" * 0x10 + b"\xe8\0\0\0\0\xc3" + b"\xcc" * 10
    _put(I, 0x1C00, b"\x90" * 0x10 + b"\xe8" + struct.pack("<i", 0x1800 - 0x1C15) + b"\xc3")
    _put(R, 0x1D00, b"\xe8" + struct.pack("<i", 0x1900 - 0x1D05) + b"\xc3")
    tw = ([_sec(1, ".text", 0x20, relocs=[(0x11, 0, lc.REL32)], ptr=4)],      # raw data at file offset 4
          {0: _sym(0, "?f@@YAXXZ", 1), 1: _sym(1, "?g@@YAXXZ", 1, value=0x10)}, b"\0" * 4 + body)
    m = _measure(I, R, [(0x1800, 0x1810, 0x1900, ("unit", 7))],
                 [(0x1C00, "?f@@YAXXZ", "b.obj"), (0x1C10, "?g@@YAXXZ", "b.obj")],
                 objs=FakeObjs({"b.obj": tw}), ledger_starts={0x1D00: 6})
    assert m.code_ref(0x1C10, 0x1D00, "?g@@YAXXZ", "?r@@YAXXZ") == (None, ("twin", 0x1C10, 0x1D00))
    m.judge_twins()
    assert m.twins[(0x1C10, 0x1D00)] == (True, "certified")
    m = _measure(I, R, [], [(0x1C10, "?g@@YAXXZ", "b.obj")], objs=FakeObjs({"b.obj": tw}),
                 ledger_starts={0x1D00: 0x12})                          # retail's row is longer: not this copy
    m.code_ref(0x1C10, 0x1D00, "?g@@YAXXZ", "?r@@YAXXZ")
    m.judge_twins()
    assert m.twins[(0x1C10, 0x1D00)] == (False, "extent differs")


def test_unit_whose_copy_the_link_did_not_select_is_not_measured():
    u = {"id": 0, "obj": "x/a.obj", "sec": 1, "secname": ".text", "size": 4, "head": "?f@@YAXXZ",
         "head_cls": lc.EXTERNAL, "starts": [0x1000],
         "rows": [{"name": "?f@@YAXXZ", "rva": 0x1000, "size": 4, "off": 0, "sym": "?f@@YAXXZ"}]}
    mapped = ({"?f@@YAXXZ": 0x1000}, {}, [(0x1000, "?f@@YAXXZ", "b.obj")], {"?f@@YAXXZ": "b.obj"})
    m = lc.Measure([u], [], mapped, bytearray(0x2000), bytearray(0x2000), {".text": (0x1000, 0x1000)},
                   {}, {}, {}, FakeObjs({}), {})
    assert u["linked"] is None and u["not_selected"] == "b.obj"
    rec = m.run()[0]
    assert rec["fails"] == ["not-selected:b.obj"] and not rec["measured"]
    mapped[3]["?f@@YAXXZ"] = "a.obj"                                   # negative control: its own copy
    lc.Measure([u], [], mapped, bytearray(0x2000), bytearray(0x2000), {".text": (0x1000, 0x1000)},
               {}, {}, {}, FakeObjs({}), {})
    assert u["linked"] == 0x1000 and "not_selected" not in u


def test_object_identity_ignores_time_stamp_and_debug_records(tmp_path):
    def ident(raw):
        return lc.object_identity(lc.parse_coff(bytes(raw)) + (bytes(raw),))
    a = lc.write_coff(tmp_path / "a.obj", [(".text", 0x60500020, b"\x90\xc3", 0), (".debug$S", 0x42100040, b"C:/x", 0)],
                      [("_f", 1, 0, lc.EXTERNAL)]).read_bytes()
    b = bytearray(lc.write_coff(tmp_path / "b.obj", [(".text", 0x60500020, b"\x90\xc3", 0),
                                                     (".debug$S", 0x42100040, b"D:/yyy", 0)],
                                [("_f", 1, 0, lc.EXTERNAL)]).read_bytes())
    b[4:8] = b"\x01\x02\x03\x04"                                       # a compile time stamp
    assert ident(b) == ident(a)
    b[b.index(b"\x90\xc3")] = 0xCC                                     # positive control: a code byte
    assert ident(b) != ident(a)


def test_warm_start_caches_are_bound_to_their_objects(tmp_path):
    q = tmp_path / "quarantine.json"
    lc.save_cache(q, "digest-A", ["?x@@YAXXZ"])
    assert lc.cache_file(q, "digest-A", False) == (["?x@@YAXXZ"], False)
    assert lc.cache_file(q, "digest-B", False) == (None, False)        # stale: a cold start
    assert lc.cache_file(q, "digest-B", True) == (["?x@@YAXXZ"], True)   # allowed, but marked
    q.write_text('["?x@@YAXXZ"]')                                       # an unstamped (link-cycle-1) cache
    assert lc.cache_file(q, "digest-A", False) == (None, False)


def test_receipt_core_leaves_out_times_and_history():
    r = {"rules": "link-cycle-2", "commit": "c", "series": {"credit_unique_bytes": 5}, "objects_digest": "o",
         "date_utc": "now", "seconds": {"total": 1}, "links": [{"secs": 3}], "warm_start": {"stubs": True}}
    cold = dict(r, date_utc="then", seconds={"total": 99}, links=[{"secs": 1}, {"secs": 2}], warm_start={})
    assert lc.digest_of(lc.receipt_core(r)) == lc.digest_of(lc.receipt_core(cold))
    assert lc.digest_of(lc.receipt_core(r)) != lc.digest_of(lc.receipt_core(dict(r, series={"credit_unique_bytes": 4})))


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))


# ----------------------------------------------------------------- BFME1 binding rules

def test_call_bound_at_the_ilt_thunk_counts_when_the_thunk_reaches_the_body():
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(R, 0x1100, b"\xe9" + struct.pack("<i", 0x1900 - 0x1105))            # retail ILT: jmp body
    _put(R, 0x1200, b"\xe9" + struct.pack("<i", 0x1A00 - 0x1205))            # a thunk to another body
    items = [(0x1800, 0x1810, 0x1900, ("unit", 1))]                          # linked body = retail 0x1900
    m = _measure(I, R, items, [])
    assert m.code_ref(0x1800, 0x1100, "?f@@YAXXZ", "?r@@YAXXZ") == (None, ("unit", 1))
    assert m.ilt_routes["call"] == 1
    # positive control: a thunk to a different body is a wrong target
    assert m.code_ref(0x1800, 0x1200, "?f@@YAXXZ", "?r@@YAXXZ") == ("code-wrong:?f@@YAXXZ", None)
    assert m.ilt_body(0x1100) == 0x1900 and m.ilt_body(0x1900) == 0x1900


def test_vtable_slot_through_the_ilt():
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, struct.pack("<I", B + 0x1800))
    _put(R, 0x3100, struct.pack("<I", B + 0x1100))                           # retail slot -> ILT thunk
    _put(R, 0x1100, b"\xe9" + struct.pack("<i", 0x1900 - 0x1105))
    vt = ([_sec(1, ".rdata", 4, relocs=[(0, 0, lc.DIR32)])], {0: _sym(0, "??_7X@@6B@", 1)}, b"")
    m = _measure(I, R, [(0x1800, 0x1810, 0x1900, ("unit", 1))], [(0x3000, "??_7X@@6B@", "a.obj")])
    fails, edges, _ = m.data_ref(0x3000, 0x3100, "??_7X@@6B@", vt[1][0], vt, 0)
    assert fails == [] and edges == {("datum", (0x3000, 0x3100, 4))} and m.ilt_routes["pointer"] == 1
    assert m.dnodes[(0x3000, 0x3100, 4)]["edges"] == {("unit", 1)}


def test_row_kinds_keep_dumps_out_of_credit():
    assert lc.row_kind({"source": "game/gen_asm/d_1.asm", "notes": "gen-dump"}) == "generated"
    assert lc.row_kind({"source": "game/masm_dumps/X.asm", "notes": ""}) == "asm"
    assert lc.row_kind({"source": "game/GameEngine/a.cpp", "notes": ""}) == "real"
    # a dump edge closes nothing in the source closure (positive control: as a unit it would)
    ok = {"a": True, ("unit", 2): True}
    assert lc.greatest_closure(ok, {"a": {("unit", 2)}}) == {"a", ("unit", 2)}
    assert lc.greatest_closure(ok, {"a": {("dump", 2)}}, bad_targets=("fill", "stub", "dump")) == {("unit", 2)}
