"""image_check: selection, retail truth and dependency closure on synthetic COFF objects."""
import collections
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import image_check as I  # noqa: E402
import link_census as L  # noqa: E402

TEXT, DATA, END = 0x1000, 0x2000, 0x3000
CODE_FLAGS, DATA_FLAGS, RDATA_FLAGS = 0x60000020, 0xC0000040, 0x40000040


def coff(sections, symbols):
    """COFF bytes. sections: [(name, flags, body, relocs [(offset, symbol name, type)], comdat selection or
    None)]; symbols: [(name, section number or 0, value, storage, type, weak default name or None)]. Every
    section gets its section symbol (with the COMDAT aux record) first."""
    table = []
    for number, (name, flags, body, _, selection) in enumerate(sections, 1):
        aux = struct.pack("<IHHIHB3x", len(body), 0, 0, 0, 0, selection or 0)
        table.append((name, 0, number, 0, I.STATIC, [aux]))
    index_of = {}
    for name, section, value, storage, kind, default in symbols:
        table.append((name, value, section, kind, storage, [default] if default else []))
    strings = bytearray(4)
    raw, position = [], 0
    for name, value, section, kind, storage, aux in table:
        index_of.setdefault(name, position)
        position += 1 + len(aux)
    for name, value, section, kind, storage, aux in table:
        encoded = name.encode("latin-1")
        if len(encoded) <= 8:
            field = encoded.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings += encoded + b"\0"
        records = []
        for extra in aux:
            if isinstance(extra, bytes):
                records.append(extra)
            else:  # weak external: TagIndex, SEARCH_ALIAS
                records.append(struct.pack("<II10x", index_of[extra], 3))
        raw.append(field + struct.pack("<IhHBB", value, section, kind, storage, len(records)) + b"".join(records))
    header_size = 20 + 40 * len(sections)
    blobs, headers, at = [], [], header_size
    for name, flags, body, relocs, selection in sections:
        data = b"" if flags & I.UNINITIALIZED else body
        fixups = b"".join(struct.pack("<IIH", off, index_of[sym], kind) for off, sym, kind in relocs)
        pointer = at if data else 0
        at += len(data)
        reloc_at = at if fixups else 0
        at += len(fixups)
        size = len(body)
        flags |= I.COMDAT if selection else 0
        headers.append(name.encode().ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, size, pointer, reloc_at, 0,
                                                                   len(relocs), 0, flags))
        blobs.append(data + fixups)
    symtab = at
    count = sum(len(r) // 18 for r in raw)
    struct.pack_into("<I", strings, 0, len(strings))
    return (struct.pack("<HHIIIHH", 0x14C, len(sections), 0, symtab, count, 0, 0) + b"".join(headers)
            + b"".join(blobs) + b"".join(raw) + bytes(strings))


def function(name, body, relocs=(), selection=2):
    """An object holding one COMDAT function."""
    return coff([(".text", CODE_FLAGS, body, list(relocs), selection)],
                [(name, 1, 0, I.EXTERNAL, 0x20, None)] + [(sym, 0, 0, I.EXTERNAL, 0x20, None)
                                                          for sym in sorted({s for _, s, _ in relocs} - {name})])


def truth(image, ledger=None, pinned=None, shared=()):
    """A RetailTruth over the synthetic image (flat: rva == offset)."""
    t = object.__new__(L.RetailTruth)
    t.image = bytes(image)
    t.sections = [{"name": ".text", "rva": TEXT, "size": DATA - TEXT, "raw_pointer": TEXT},
                  {"name": ".data", "rva": DATA, "size": END - DATA, "raw_pointer": DATA}]
    t.ledger = collections.defaultdict(set, {k: set(v) for k, v in (ledger or {}).items()})
    t.pinned = collections.defaultdict(set, {k: set(v) for k, v in (pinned or {}).items()})
    t.import_routes, t.slots, t.shared, t._cache = {}, collections.defaultdict(set), set(shared), {}
    return t


def build(objects, kept, retail, ledger, excused=None, statics=None, pinned=None):
    objs = [I.parse_object(name, data, i) for i, (name, data) in enumerate(objects)]
    image = bytes(retail)

    def read(rva, size):
        return image[rva:rva + size] if 0 <= rva and rva + size <= len(image) else None
    lanes = {name: {None: "authored"} for name, _ in objects}
    return I.Image(objs, kept, truth(image, ledger, pinned), statics or {}, read, excused or (lambda n: None),
                   lanes, (TEXT, DATA)).run()


def call(at, to):
    return b"\xe8" + struct.pack("<i", to - (at + 5))


def item(image, name):
    return next(i for i in image.items if any(n == name for n, _, _ in i.names) and i.bound)


# retail: a at 0x1000 calls b at 0x1010, which calls c at 0x1020 (mov eax,1; ret)
RETAIL = bytearray(END)
RETAIL[0x1000:0x1006] = call(0x1000, 0x1010) + b"\xc3"
RETAIL[0x1010:0x1016] = call(0x1010, 0x1020) + b"\xc3"
RETAIL[0x1020:0x1026] = b"\xb8\x01\0\0\0\xc3"
LEDGER = {"_a": {0x1000}, "_b": {0x1010}, "_c": {0x1020}}
CHAIN = [("A.obj", function("_a", b"\xe8\0\0\0\0\xc3", [(1, "_b", I.REL32)])),
         ("B.obj", function("_b", b"\xe8\0\0\0\0\xc3", [(1, "_c", I.REL32)])),
         ("C1.obj", function("_c", b"\xb8\x02\0\0\0\xc3")),   # a private copy that is not retail's
         ("C2.obj", function("_c", b"\xb8\x01\0\0\0\xc3"))]


def test_wrong_selected_copy_two_hops_away_breaks_closure():
    image = build(CHAIN, {"_a": "A.obj", "_b": "B.obj", "_c": "C1.obj"}, RETAIL, LEDGER)
    a, b, c = item(image, "_a"), item(image, "_b"), item(image, "_c")
    assert (a.verdict, b.verdict, c.verdict) == ("retail", "retail", "wrong")
    assert c.obj.name == "C1.obj" and "bytes differ" in c.reason
    assert image.badset[a.id] == frozenset({c.id})
    assert [image.nodes[n].label() for n in image.path(a.id)] == ["_a", "_b", "_c"]
    summary, queue, paths, _ = I.results(image)
    assert summary["retail_true_bytes"] == 12 and summary["closed_bytes"] == 0
    assert queue[0]["name"] == "_c" and queue[0]["object"] == "C1.obj"
    assert queue[0]["unlock_bytes"] == 18 and queue[0]["unlock_functions"] == 3  # a, b and c itself
    assert any(row["path"] == "_a -> _b -> _c" for row in paths)
    # the other copy selected: everything closes
    image = build(CHAIN, {"_a": "A.obj", "_b": "B.obj", "_c": "C2.obj"}, RETAIL, LEDGER)
    assert all(image.badset[item(image, n).id] == frozenset() for n in ("_a", "_b", "_c"))
    assert I.results(image)[0]["closed_bytes"] == 18


def test_selected_copy_decides_not_the_first_in_link_order():
    # C1 comes first in link order, but the map says C2's copy was kept
    image = build(CHAIN, {"_a": "A.obj", "_b": "B.obj", "_c": "C2.obj"}, RETAIL, LEDGER)
    shadow = [i for i in image.items if i.obj.name == "C1.obj"]
    assert not shadow  # a COMDAT the link discarded is not in the image at all
    assert item(image, "_c").obj.name == "C2.obj"


def test_unknown_stays_unknown_not_wrong():
    retail = bytearray(RETAIL)
    retail[0x1030:0x1036] = call(0x1030, 0x1080) + b"\xc3"
    objects = [("F.obj", function("_f", b"\xe8\0\0\0\0\xc3", [(1, "_crtfn", I.REL32)]))]
    image = build(objects, {"_f": "F.obj"}, retail, {"_f": {0x1030}},
                  excused=lambda name: "crt" if name == "_crtfn" else None)
    f = item(image, "_f")
    assert f.verdict == "unknown" and "no retail address" in f.reason
    assert image.badset[f.id] == frozenset({f.id})
    summary, queue, _, _ = I.results(image)
    assert summary["function_verdicts"] == {"unknown": 1} and queue[0]["verdict"] == "unknown"
    # with the CRT name pinned where retail calls it, the excused leaf closes
    image = build(objects, {"_f": "F.obj"}, retail, {"_f": {0x1030}}, pinned={"_crtfn": {0x1080}},
                  excused=lambda name: "crt" if name == "_crtfn" else None)
    assert item(image, "_f").verdict == "retail" and image.badset[item(image, "_f").id] == frozenset()


def static_data_object(value):
    """f and g each load a TU-local int `$d` (no ledger row: placed by propagation)."""
    text = b"\xa1\0\0\0\0\xc3" + b"\xcc" * 10 + b"\xa1\0\0\0\0\xc3"
    return coff([(".text", CODE_FLAGS, text, [(1, "$d", I.DIR32), (17, "$d", I.DIR32)], None),
                 (".data", DATA_FLAGS, struct.pack("<I", value), [], None)],
                [("_f", 1, 0, I.EXTERNAL, 0x20, None), ("_g", 1, 16, I.EXTERNAL, 0x20, None),
                 ("$d", 2, 0, I.STATIC, 0, None)])


def test_propagated_static_is_verified_and_disagreement_is_unknown():
    retail = bytearray(RETAIL)
    retail[0x1040:0x1050] = b"\xa1" + struct.pack("<I", I.BASE + 0x2000) + b"\xc3" + b"\xcc" * 10
    retail[0x1050:0x1056] = b"\xa1" + struct.pack("<I", I.BASE + 0x2000) + b"\xc3"
    retail[0x2000:0x2004] = struct.pack("<I", 7)
    ledger = {"_f": {0x1040}, "_g": {0x1050}}
    image = build([("S.obj", static_data_object(7))], {"_f": "S.obj", "_g": "S.obj"}, retail, ledger)
    d = item(image, "$d")
    assert d.derived and d.home == 0x2000 and d.verdict == "retail"
    assert image.badset[item(image, "_f").id] == frozenset()
    # the static holds another value: it is wrong where retail's code reads it
    image = build([("S.obj", static_data_object(8))], {"_f": "S.obj", "_g": "S.obj"}, retail, ledger)
    assert item(image, "$d").verdict == "wrong" and "placed by" in item(image, "$d").reason
    # f and g read two different addresses: nothing says which is the static
    retail[0x1050:0x1056] = b"\xa1" + struct.pack("<I", I.BASE + 0x2010) + b"\xc3"
    retail[0x2010:0x2014] = struct.pack("<I", 7)
    image = build([("S.obj", static_data_object(7))], {"_f": "S.obj", "_g": "S.obj"}, retail, ledger)
    assert item(image, "$d").verdict == "unknown" and "disagree" in item(image, "$d").reason
    assert item(image, "_f").verdict == "unknown" and item(image, "_g").verdict == "unknown"


VTABLE, DELETING, VECTOR = "??_7X@@6B@", "??_GX@@UAEPAXI@Z", "??_EX@@UAEPAXI@Z"


def vtable_objects():
    vtable = coff([(".rdata", RDATA_FLAGS, bytes(4), [(0, VECTOR, I.DIR32)], 2)],
                  [(VTABLE, 1, 0, I.EXTERNAL, 0, None), (DELETING, 0, 0, I.EXTERNAL, 0x20, None),
                   (VECTOR, 0, 0, I.WEAK_EXTERNAL, 0x20, DELETING)])
    return [("V.obj", vtable), ("G.obj", function(DELETING, b"\xc3"))]


def test_weak_fallback_is_flagged_and_judged_on_what_the_link_binds():
    retail = bytearray(RETAIL)
    retail[0x1060] = 0xC3
    retail[0x2020:0x2024] = struct.pack("<I", I.BASE + 0x1060)
    kept = {VTABLE: "V.obj", DELETING: "G.obj"}
    ledger = {VTABLE: {0x2020}, DELETING: {0x1060}}
    image = build(vtable_objects(), kept, retail, ledger)
    vtable = item(image, VTABLE)
    assert [(name, default) for _, _, name, default in image.weak_fallbacks] == [(VECTOR, DELETING)]
    (_, _, target, _, flag), = vtable.edges
    assert target is item(image, DELETING) and flag == f"weak-fallback:{DELETING}"
    assert vtable.verdict == "retail"
    # retail's slot holds the vector deleting destructor at 0x1070: the fallback is not retail's
    retail[0x1070] = 0xC3
    retail[0x2020:0x2024] = struct.pack("<I", I.BASE + 0x1070)
    image = build(vtable_objects(), kept, retail, {**ledger, VECTOR: {0x1070}})
    assert item(image, VTABLE).verdict == "wrong"


def test_strong_duplicate_not_selected_is_shadowed():
    objects = [("M.obj", function("_new", b"\xb8\x01\0\0\0\xc3", selection=None)),
               ("N.obj", function("_new", b"\xb8\x02\0\0\0\xc3", selection=None))]
    retail = bytearray(RETAIL)
    retail[0x1090:0x1096] = b"\xb8\x01\0\0\0\xc3"
    image = build(objects, {"_new": "N.obj"}, retail, {"_new": {0x1090}})
    by_obj = {i.obj.name: i for i in image.items}
    assert by_obj["M.obj"].verdict == "shadowed" and by_obj["N.obj"].verdict == "wrong"


def test_unresolved_name_is_a_bad_leaf():
    objects = [("H.obj", function("_h", b"\xe8\0\0\0\0\xc3", [(1, "_missing", I.REL32)]))]
    retail = bytearray(RETAIL)
    retail[0x10A0:0x10A6] = call(0x10A0, 0x1000) + b"\xc3"
    image = build(objects, {"_h": "H.obj"}, retail, {"_h": {0x10A0}, "_missing": {0x1000}})
    h = item(image, "_h")
    leaf = image.leaves[("unresolved", "_missing")]
    assert h.verdict == "retail" and image.badset[h.id] == frozenset({leaf.id})


def test_relocation_whose_retail_field_is_no_address_is_wrong():
    # retail holds the constant 10 where our object relocates to the static
    retail = bytearray(RETAIL)
    retail[0x1040:0x1050] = b"\xa1" + struct.pack("<I", 10) + b"\xc3" + b"\xcc" * 10
    retail[0x1050:0x1056] = b"\xa1" + struct.pack("<I", I.BASE + 0x2000) + b"\xc3"
    retail[0x2000:0x2004] = struct.pack("<I", 7)
    image = build([("S.obj", static_data_object(7))], {"_f": "S.obj", "_g": "S.obj"}, retail,
                  {"_f": {0x1040}, "_g": {0x1050}})
    assert item(image, "_f").verdict == "wrong" and "outside" in item(image, "_f").reason
    assert item(image, "$d").home == 0x2000 and item(image, "$d").verdict == "retail"


def test_row_on_an_ilt_stub_is_judged_at_the_body():
    retail = bytearray(RETAIL)
    retail[0x1100:0x1105] = b"\xe9" + struct.pack("<i", 0x1020 - 0x1105)  # packed ILT: stub for c
    retail[0x1105:0x110A] = b"\xe9" + struct.pack("<i", 0x1000 - 0x110A)
    image = build(CHAIN, {"_a": "A.obj", "_b": "B.obj", "_c": "C2.obj"}, retail, {**LEDGER, "_c": {0x1100}})
    assert item(image, "_c").home == 0x1020 and item(image, "_c").verdict == "retail"
    # a ?j_ thunk row sits on the stub itself: its body IS the jmp
    thunk = ("J.obj", function("?j_00001100@@YAXXZ", b"\xe9\0\0\0\0", [(1, "_c", I.REL32)]))
    image = build(CHAIN + [thunk], {"_a": "A.obj", "_b": "B.obj", "_c": "C2.obj", "?j_00001100@@YAXXZ": "J.obj"},
                  retail, {**LEDGER, "?j_00001100@@YAXXZ": {0x1100}})
    j = item(image, "?j_00001100@@YAXXZ")
    assert j.home == 0x1100 and j.verdict == "retail" and image.badset[j.id] == frozenset()
