"""link_census: which COMDAT copies lose, judged by retail truth."""
import collections
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as L  # noqa: E402

TEXT = 0x1000


def truth(image, ledger=None, pinned=None, shared=()):
    """A RetailTruth over a synthetic .text at TEXT, without reading the repo."""
    t = object.__new__(L.RetailTruth)
    t.image = bytes(image)
    t.sections = [{"name": ".text", "rva": TEXT, "size": len(image), "raw_pointer": 0}]
    t.ledger = collections.defaultdict(set, {k: set(v) for k, v in (ledger or {}).items()})
    t.pinned = collections.defaultdict(set, {k: set(v) for k, v in (pinned or {}).items()})
    t.slots = collections.defaultdict(set)
    t.shared = set(shared)
    t._cache = {}
    return t


def jmp(at, to):
    return b"\xe9" + struct.pack("<i", to - (at + 5))


def symbol(name, section=1, value=0):
    return {"name": name, "section": section, "storage": L.EXTERNAL, "value": value}


def referent(name):
    return {"name": name, "section": 0, "storage": L.EXTERNAL, "value": 0}


# retail: 0x1000 `jmp 0x1020` (~AsciiString), 0x1010 `jmp 0x1020` (~StringBase), 0x1020 releaseBuffer
IMAGE = bytearray(0x40)
IMAGE[0x00:0x05] = jmp(0x1000, 0x1020)
IMAGE[0x10:0x15] = jmp(0x1010, 0x1020)
IMAGE[0x20] = 0xC3
LEDGER = {"dtor": {0x1000}, "base_dtor": {0x1010}, "release": {0x1020}}


def test_copy_jumping_to_retail_target_is_retail():
    t = truth(IMAGE, LEDGER)
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("release"))], "a", 5) == "retail"


def test_pin_does_not_hide_a_wrong_target():
    # the byte gate accepts base_dtor -> 0x1020 through a pin; retail truth
    # resolves base_dtor to its own row 0x1010, which is not where retail jumps
    t = truth(IMAGE, LEDGER, pinned={"base_dtor": {0x1020}})
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("base_dtor"))], "b", 5) == "wrong"


def test_ilt_stub_is_followed_but_a_padded_jmp_is_not():
    image = bytearray(IMAGE) + bytearray(0x20)
    image[0x40:0x45] = jmp(0x1040, 0x1020)  # a packed ILT table: stub for releaseBuffer
    image[0x45:0x4A] = jmp(0x1045, 0x1000)
    image[0x08:0x0D] = b"\xe8" + struct.pack("<i", 0x1040 - 0x100D)  # call through the stub
    ledger = {**LEDGER, "caller": {0x1008}}
    body = b"\xe8\0\0\0\0"
    assert truth(image, ledger).verdict(symbol("caller"), body, [(1, L.RetailTruth.REL32, referent("release"))],
                                        "c", 5) == "retail"
    image[0x08:0x0D] = b"\xe8" + struct.pack("<i", 0x1010 - 0x100D)  # call ~StringBase: padded, a function
    assert truth(image, ledger).verdict(symbol("caller"), body, [(1, L.RetailTruth.REL32, referent("release"))],
                                        "d", 5) == "wrong"


def test_static_referent_is_unknown_and_absolute_symbol_is_checked():
    image = bytearray(IMAGE)
    image[0x28:0x2E] = b"\x64\xa1\0\0\0\0"  # mov eax, fs:[__except_list]
    t = truth(image, {**LEDGER, "seh": {0x1028}})
    body = b"\x64\xa1\0\0\0\0"
    local = {"name": "_$E2", "section": 3, "storage": 3, "value": 0}
    assert t.verdict(symbol("seh"), body, [(2, L.RetailTruth.DIR32, referent("__except_list"))], "h", 6) == "retail"
    assert t.verdict(symbol("seh"), body, [(2, L.RetailTruth.DIR32, local)], "i", 6) == "unknown"


def test_pin_is_read_as_va_and_rva():
    assert L.RetailTruth._rvas(0x0044A061) == {0x0044A061, 0x0004A061}
    assert L.RetailTruth._rvas(0x0003A061) == {0x0003A061}


def test_string_literal_is_checked_by_content():
    image = bytearray(IMAGE)
    image[0x30:0x32] = b"A\0"
    image[0x38:0x3D] = b"h" + struct.pack("<I", L.BASE + 0x1030)  # push offset "A"
    t = truth(image, {**LEDGER, "pusher": {0x1038}})
    body = b"\x68\0\0\0\0"
    literal = {"name": "??_C@_01A@A?$AA@", "section": 2, "storage": L.EXTERNAL, "value": 0, "content": b"A\0"}
    assert t.verdict(symbol("pusher"), body, [(1, L.RetailTruth.DIR32, literal)], "j", 5) == "retail"
    other = {**literal, "content": b"B\0"}
    assert t.verdict(symbol("pusher"), body, [(1, L.RetailTruth.DIR32, other)], "k", 5) == "wrong"


def test_bytes_differ_is_wrong_and_unknown_name_is_unknown():
    t = truth(IMAGE, LEDGER)
    assert t.verdict(symbol("release"), b"\xc2\x04\x00", [], "e", 3) == "wrong"
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("nowhere"))], "f", 5) == "unknown"


def test_no_retail_address_is_none():
    t = truth(IMAGE, LEDGER)
    assert t.verdict(symbol("inline_only"), b"\xc3", [], "g", 1) is None


def test_keep_rule_retail_truth_ignores_link_order():
    copies = [("a.obj", "owner", "wrong"), ("b.obj", "right", "retail"), ("c.obj", "owner", "wrong")]
    loses, rule = L.keep_rule(copies)
    assert rule == "retail"
    assert loses == {"a.obj": True, "b.obj": False, "c.obj": True}


def test_keep_rule_unknown_copies_follow_the_proven_one():
    copies = [("a.obj", "x", "unknown"), ("b.obj", "y", "retail"), ("c.obj", "y", "retail")]
    assert L.keep_rule(copies)[0] == {"a.obj": True, "b.obj": False, "c.obj": False}
    copies = [("a.obj", "x", "unknown"), ("b.obj", "x", "unknown"), ("c.obj", "z", "unknown")]
    assert L.keep_rule(copies)[0] == {"a.obj": False, "b.obj": False, "c.obj": True}


def test_keep_rule_without_retail_address_keeps_first_in_link_order():
    copies = [("a.obj", "x", None), ("b.obj", "y", None), ("c.obj", "y", None)]
    loses, rule = L.keep_rule(copies)
    assert rule == "first"
    assert loses == {"a.obj": False, "b.obj": True, "c.obj": True}


def test_shared_claim_mismatch_is_unknown_not_wrong():
    # base_dtor's only address is claimed by several names: disagreeing with it
    # says the ledger is wrong, not the copy
    t = truth(IMAGE, LEDGER, shared={0x1010})
    body = b"\xe9\0\0\0\0"
    assert t.verdict(symbol("dtor"), body, [(1, L.RetailTruth.REL32, referent("base_dtor"))], "l", 5) == "unknown"
