"""The funclet templates gen_uw emits, pinned to the bytes a probe compile made.

Every fixture below is a body MSVC 7.1 actually produced for the C++ the
emitters write -- captured from a probe TU compiled with the same
`/DNDEBUG /MD /EHsc` the generated files carry -- with the relocation slots
zeroed. Two claims are under test and they have to hold together:

  * the retail-side reader decodes each template's displacement, callee and
    member offset out of those bytes, in BOTH the int8 and int32 encodings of
    the frame reference (the disp32 twin is the same C++ at a bigger frame);
  * the emitted-side reader turns the same bytes back into the same key, so a
    row anchored to a $L label reproduces the funclet the key came from.

A shape that only round-trips through the reader proves nothing about codegen,
so the layout arithmetic the emitters do -- member offsets, the EBP-0x10 pad
ladder, and the 4-byte slot the frame already has -- is asserted separately
against the emitted source text.
"""
import importlib.util
import re
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


gen_uw = _load("gen_uw")

RVA = 0x00BF0000
DTOR = "??1Gen_uw_0000d828@@QAE@XZ"
MEMBER_DTOR = "??1Gen_uwm_0000d828@@QAE@XZ"
TARGET = 0x0000D828
# One of the 19 addresses retail pushes as a placement tag: .data, well past the
# last raw byte of that section, at the 104-byte stride of the table it sits in.
TAG = 0x0130B260


def body(hexed, call_at):
    """A probe body with its REL32 slot aimed at TARGET from RVA."""
    raw = bytearray(bytes.fromhex(hexed))
    struct.pack_into("<i", raw, call_at, TARGET - (RVA + call_at + 4))
    return bytes(raw)


# hex, REL32 offset, expected (kind, disp, member offset)
TEMPLATES = [
    ("8d 4d f0 e9 00000000", 4, ("A", -0x10, 0)),
    ("8d 8d f0 fd ff ff e9 00000000", 7, ("A", -0x210, 0)),
    ("8d 4d 04 e9 00000000", 4, ("B", 4, 0)),
    ("8b 45 f0 50 e8 00000000 59 c3", 5, ("C", -0x10, 0)),
    ("8b 85 f0 fd ff ff 50 e8 00000000 59 c3", 8, ("C", -0x210, 0)),
    ("8b 4d f0 e9 00000000", 4, ("M", -0x10, 0)),
    ("8b 8d f0 fd ff ff e9 00000000", 7, ("M", -0x210, 0)),
    ("8b 4d f0 83 c1 04 e9 00000000", 7, ("M", -0x10, 4)),
    ("8b 4d f0 81 c1 98 00 00 00 e9 00000000", 10, ("M", -0x10, 0x98)),
    ("8b 8d f0 fd ff ff 83 c1 04 e9 00000000", 10, ("M", -0x210, 4)),
    ("8b 8d f0 fd ff ff 81 c1 08 06 00 00 e9 00000000", 13, ("M", -0x210, 0x608)),
    ("6a 24 8b 45 f0 50 e8 00000000 83 c4 08 c3", 7, ("S", -0x10, 36)),
    ("68 2c 01 00 00 8b 45 f0 50 e8 00000000 83 c4 08 c3", 10, ("S", -0x10, 300)),
    ("6a 10 8b 85 f0 fe ff ff 50 e8 00000000 83 c4 08 c3", 10, ("S", -0x110, 16)),
    ("68 2c 01 00 00 8b 85 f0 fe ff ff 50 e8 00000000 83 c4 08 c3", 13,
     ("S", -0x110, 300)),
    ("8b 45 04 50 8b 4d f0 51 e8 00000000 83 c4 08 c3", 9, ("P", -0x10, 4)),
    ("8b 45 0c 50 8b 4d b0 51 e8 00000000 83 c4 08 c3", 9, ("P", -0x50, 12)),
    # Byte for byte an S, decided a K because 0x0130B260 is an address in this
    # image and no class is 19,968,608 bytes.
    ("68 60 b2 30 01 8b 45 f0 50 e8 00000000 83 c4 08 c3", 10, ("K", -0x10, TAG)),
    ("68 60 b2 30 01 8b 85 f0 fe ff ff 50 e8 00000000 83 c4 08 c3", 13,
     ("K", -0x110, TAG)),
]
SIZED_DELETE = {36: "??3Gen_uws36_0000d828@@SAXPAXI@Z",
                300: "??3Gen_uws300_0000d828@@SAXPAXI@Z",
                16: "??3Gen_uws16_0000d828@@SAXPAXI@Z"}
PLACEMENT_DELETE = "??3@YAXPAXPAUGen_uwt_0000d828@@@Z"


@pytest.mark.parametrize("hexed,call_at,expected", TEMPLATES)
def test_retail_bytes_decode_to_the_template_that_made_them(hexed, call_at, expected):
    kind, disp, target, offset = gen_uw.classify(RVA, body(hexed.replace(" ", ""), call_at))

    assert (kind, disp, offset) == expected
    assert target == TARGET, "the destructor address comes out of the displacement"


@pytest.mark.parametrize("hexed,call_at,expected", TEMPLATES)
def test_emitted_bytes_decode_back_to_the_key_the_row_is_anchored_to(
        hexed, call_at, expected):
    kind, disp, offset = expected
    raw = bytes.fromhex(hexed.replace(" ", ""))
    callee = {"C": gen_uw.DELETE_NAME, "M": MEMBER_DTOR, "P": PLACEMENT_DELETE,
              "K": PLACEMENT_DELETE, "S": SIZED_DELETE.get(offset)}.get(kind, DTOR)

    key = gen_uw.emitted_key(raw, {call_at: callee})

    funclet = gen_uw.Funclet(kind, RVA, len(raw), disp, TARGET, offset)
    assert key == gen_uw.key_of(funclet)


def test_a_label_running_past_its_funclet_still_decodes():
    """read_object_symbol_bytes hands back everything to the end of the section,
    so the emitted side is recognised by opcode and never by length."""
    raw = bytes.fromhex("8b4df083c104e900000000") + b"\xcc" * 40

    assert gen_uw.emitted_key(raw, {7: MEMBER_DTOR}) == ("M", -0x10, TARGET, 4)


def test_gen_uw_new_is_not_mistaken_for_an_address_bearing_name():
    """Gen_uw_new shares the Gen_uw_ prefix and carries no address; taking eight
    characters on faith turns it into a ValueError inside the label walk."""
    assert gen_uw.emitted_target("??1Gen_uw_new@@QAE@XZ", "??1Gen_uw_") is None
    assert gen_uw.emitted_target(DTOR, "??1Gen_uw_") == TARGET


def struct_offsets(text, name):
    """Byte offset of each Gen_uwm_ member in an emitted host struct."""
    fields = re.search(r"struct %s \{(.*?)\};" % name, text, re.S).group(1)
    offsets, position = [], 0
    for filler, member in re.findall(r"char q\d+\[(\d+)\];|(Gen_uwm_\w+ a\d+;)", fields):
        if filler:
            position += int(filler)
        else:
            offsets.append(position)
            position += 4
    return offsets


def test_the_member_host_puts_every_member_where_retail_says_it_is():
    wanted = (0, 4, 0x98, 0x9C, 0x2A9BC4)

    text = gen_uw.emit_member(TARGET, 0, wanted)

    assert struct_offsets(text, "Gen_uwh0_0000d828") == list(wanted)
    assert text.count("Gen_uwm_0000d828 a") == len(wanted), (
        "one member per offset")
    assert "Gen_uwm_0000d828 z;" in text, (
        "a member is only unwound because a LATER member's constructor threw past "
        "it, so without the trailing member the last offset emits no funclet")


def test_the_host_constructor_is_marked_absent_from_retail():
    """It is the only definition this generator writes that no row claims, and the
    commit hook refuses a Class::Method definition the ledger does not declare.
    Retail has no such constructor -- only the funclets it makes MSVC emit."""
    text = gen_uw.emit_member(TARGET, 0, (4,))

    assert "// ??0Gen_uwh0_0000d828@@QAE@XZ absent-from-retail" in text
    assert text.index("absent-from-retail") < text.index(
        "Gen_uwh0_0000d828::Gen_uwh0_0000d828"), "the marker precedes its definition"


def test_a_member_host_walks_this_down_with_the_same_pad_the_locals_use():
    assert "char pad[2120]; gen_uw_sink(pad);" in gen_uw.emit_member(TARGET, 2120, (4,))
    assert "char pad" not in gen_uw.emit_member(TARGET, 0, (4,))


def test_a_four_byte_pad_cannot_move_a_local_so_the_ladder_does():
    """`char pad[4]` lands in the spare slot the frame already has. It is the one
    displacement the pad rule does not reach, and the only reason two ladder
    locals survive in the emitter at all."""
    assert "char pad[4]" not in gen_uw.emit_local(TARGET, 4)
    assert gen_uw.emit_local(TARGET, 4).count("Gen_uw_0000d828 v") == 2
    assert "char pad[8]; gen_uw_sink(pad);" in gen_uw.emit_local(TARGET, 8)


@pytest.mark.parametrize("unit,funclets", [
    (gen_uw.Unit("local", TARGET, 1, (2120,)), [("A", -0x858, 0)]),
    (gen_uw.Unit("param", TARGET, 2, (2,)), [("B", 4, 0), ("B", 8, 0)]),
    (gen_uw.Unit("new", None, 1, (8,)), [("C", -0x18, 0)]),
    (gen_uw.Unit("member", TARGET, 2, (12, (0, 0x98))), [("M", -0x1C, 0), ("M", -0x1C, 0x98)]),
    (gen_uw.Unit("sized", TARGET, 1, (8, 36)), [("S", -0x18, 36)]),
    (gen_uw.Unit("place", TARGET, 1, (64, 8)), [("P", -0x50, 8)]),
])
def test_a_unit_claims_exactly_the_keys_its_funclets_ask_for(unit, funclets):
    """`missing` stops the run on a key claimed here that the compiler did not
    produce, so this mapping is the whole reason no row can be anchored to a
    label that reproduces something else."""
    expected = [gen_uw.key_of(gen_uw.Funclet(kind, RVA, 8, disp, TARGET, offset))
                for kind, disp, offset in funclets]

    assert sorted(gen_uw.unit_keys(unit)) == sorted(expected)


@pytest.mark.parametrize("kind,disp,offset,why", [
    ("M", -0x10 + 2, 0, "a slot 2 bytes below EBP-0x10 is not on the 4-byte ladder"),
    ("M", -0x0C, 0, "above EBP-0x10 there is no pad that reaches it"),
    ("M", -0x10, 6, "a 6-byte member offset is not a field a struct layout produces"),
    ("M", -0x10, -4, "a negative member offset is not a field at all"),
    ("P", -0x10, -32, "a placement argument in a local slot is not a parameter"),
    ("P", -0x14, 4, "EBP-0x14 is the spare slot no pad moves the block into"),
    ("S", -0x14, 36, "same spare slot, and a sized delete has no second-new escape"),
    ("S", -0x10, 0, "a zero-byte class is not a size retail can have pushed"),
])
def test_an_unplaceable_slot_is_declined_with_the_reason_recorded(
        kind, disp, offset, why):
    funclet = gen_uw.Funclet(kind, RVA, 11, disp, TARGET, offset)

    assert not gen_uw.on_the_ladder(funclet), why
    assert gen_uw.unreachable(funclet), "the reason becomes a tombstone's reason column"


def test_the_sized_delete_class_is_declared_once_per_target_and_size():
    """The same (target, size) reaches several frame slots; a struct definition
    per slot is a redefinition the compiler refuses, and it did."""
    units = [gen_uw.Unit("sized", TARGET, 1, (pad, 16)) for pad in (0, 8, 16)]

    text = gen_uw.emit_source(units)

    assert text.count("struct Gen_uws16_0000d828 {") == 1
    assert text.count("*gen_uw_s") == 3
    assert "char q[16];" in text, "sizeof is what retail's pushed immediate is"


def test_the_placement_tag_type_is_what_separates_one_target_from_another():
    """The two-argument operator delete is a free function, so its mangled name
    carries only the tag type -- that is the whole identity of the callee."""
    text = gen_uw.emit_source([gen_uw.Unit("place", TARGET, 1, (0, 8))])

    assert "void operator delete(void *, Gen_uwt_0000d828 *);" in text
    assert "gen_uw_d0_8_0000d828(Gen_uwt_0000d828 *a0, Gen_uwt_0000d828 *a1)" in text
    assert "new (a1) Gen_uwp_0000d828(0)" in text, "the LAST parameter is the tag"


def test_a_pushed_address_is_a_placement_tag_and_never_a_class_size():
    """The one thing separating the S and K templates is the immediate.

    Nineteen retail funclets push a constant in the 0x0130Bxxx table and were
    read as sizes, which put nineteen class-scoped sized deletes of 19,968,608
    bytes and up in reverse/symbols.csv -- all nineteen pinned onto 0x0002AAA9,
    an address whose body is a lone `ret` and which 253 placement-delete rows
    already name as a free two-argument delete. One function cannot be the
    class-scoped delete of nineteen classes; the immediate is an address.
    """
    assert gen_uw.delete_kind(TAG) == "K"
    base, end = gen_uw.image_span()
    assert base <= TAG < end, "the evidence is the image's own address range"
    for size in (4, 16, 36, 300, 960, base - 1):
        assert gen_uw.delete_kind(size) == "S", (
            "%d is not an address in this image, so it is a class size" % size)


def test_the_tag_and_the_slot_placement_share_one_pin():
    """The constant-tag site and the parameter-slot site call the SAME free
    two-argument delete, so one tag type and one pin answer for both. Modelling
    the constant as a size gave every site a class of its own instead."""
    text = gen_uw.emit_source([gen_uw.Unit("place", TARGET, 1, (0, 4)),
                               gen_uw.Unit("tag", TARGET, 1, (0, TAG))])

    assert text.count("void operator delete(void *, Gen_uwt_0000d828 *);") == 1
    assert text.count("struct Gen_uwp_0000d828 {") == 1
    assert "new ((Gen_uwt_0000d828 *)0x0130B260) Gen_uwp_0000d828(0)" in text
    assert "Gen_uws" not in text, "a pushed address must not mint a sized-delete class"


def test_two_operator_delete_pins_at_one_address_stop_the_run(tmp_path, monkeypatch):
    """The guard that makes the mis-read immediate unrepeatable.

    Reading a pushed address as a class size gave every one of 19 sites its own
    Gen_uws<size> class and pinned all 19 class-scoped deletes onto the single
    free placement delete they call. A destructor and its member twin may share
    an address -- they are two invented types with one retail destructor -- but
    an operator delete is a function, so two delete pins at one address are a
    contradiction the run must not write.
    """
    sized = [gen_uw.Funclet("S", RVA + 8 * i, 15, -0x10, TARGET, 100 + i)
             for i in range(2)]
    monkeypatch.setattr(gen_uw, "compiled_slots",
                        lambda source: {gen_uw.key_of(f): "$L%d" % (700 + i)
                                        for i, f in enumerate(sized)})
    monkeypatch.setattr(gen_uw, "SOURCE_DIR", tmp_path)
    monkeypatch.setattr(gen_uw, "source_name", lambda index: "uw_gen_%03d.cpp" % index)
    monkeypatch.setattr(gen_uw, "ROOT", tmp_path)

    class Nothing:
        tombstoned, owned, pinned, declined = {}, {}, set(), {}

        def resolves(self, name, address):
            return False

    class Staging:
        def stage(self, paths):
            pass

    with pytest.raises(SystemExit) as raised:
        gen_uw.emit_and_write(Nothing(), sized, Staging())

    assert "two different operator deletes" in str(raised.value)
    assert "0x%08X" % TARGET in str(raised.value)
