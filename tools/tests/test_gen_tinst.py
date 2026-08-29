"""The two readings gen-tinst does before it ever compiles anything.

gen-tinst identifies a retail container body by its STLport-decorated NAME
rather than by its shape, which is the whole reason it can tell apart bodies a
masked comparison cannot: every four-byte trivially assignable element type
compiles `_M_fill_insert` to the same 282 bytes. That makes two readings
load-bearing, and both are pure functions of a string or of five bytes:

  * the element type has to come back out of the mangled name as the C++ that
    re-instantiates it -- and has to come back as None, not as a guess,
    whenever the parser does not fully understand the encoding. A guessed
    spelling would instantiate over the WRONG type and, for the size classes
    that compile identically, still land on a plausible body. Refusing is the
    only safe failure here, so it is asserted as hard as the successes;

  * the address has to be followed through the 5-byte incremental-link `jmp
    rel32` stub, because the name tables record the linker's ILT entry and not
    the function. Without it every lookup lands on five bytes.
"""
import importlib.util
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


gen_small = _load("gen_small")


@pytest.mark.parametrize("mangled, spelled", [
    # the primitives the ledger's landed vector bodies are instantiated over
    ("M", "float"),
    ("H", "int"),
    ("G", "unsigned short"),
    ("_N", "bool"),
    ("PAX", "void *"),
    # class / struct / enum, which differ only in their tag letter
    ("VProductionPrerequisite@@", "ProductionPrerequisite"),
    ("UCoord3D@@", "Coord3D"),
    ("W4ScienceType@@", "ScienceType"),
    # a nested name is encoded innermost-first and has to be read back outward
    ("UWeaponBarrelInfo@ModelConditionInfo@@", "ModelConditionInfo::WeaponBarrelInfo"),
    ("UUpgrades@OCLSpecialPowerModuleData@@", "OCLSpecialPowerModuleData::Upgrades"),
    # pointer-to-class, which is what the four-byte instantiations really carry
    ("PAVObject@@", "Object *"),
    # a template argument that is itself a template
    ("U?$pair@PAVSubsystemInterface@@PAX@_STL@@",
     "_STL::pair<SubsystemInterface *, void * >"),
    ("U?$pair@UICoord2D@@UCoord3D@@@_STL@@", "_STL::pair<ICoord2D, Coord3D >"),
])
def test_demangles_the_element_types_the_ledger_carries(mangled, spelled):
    assert gen_small.tinst_demangle(mangled) == spelled


@pytest.mark.parametrize("mangled", [
    "",                       # nothing at all
    "Q",                      # a tag letter this table does not define
    "V?$vector@H",            # a template that never closes
    "VUnterminated@",         # a class name missing its second @
    "U?$pair@@_STL@@",        # a template with an empty argument list
    "U?$hash_map@HPAX@_STL@@@_STL@@",   # trailing text after the close
])
def test_refuses_rather_than_guessing(mangled):
    """A wrong spelling would still compile and still land on a body that looks
    right, so anything not fully understood must come back as None."""
    assert gen_small.tinst_demangle(mangled) is None


@pytest.mark.parametrize("name, container, element", [
    ("?_M_insert_overflow@?$vector@VProductionPrerequisite@@V?$allocator@"
     "VProductionPrerequisite@@@_STL@@@_STL@@IAEXPAVProductionPrerequisite@@@Z",
     "vector", "VProductionPrerequisite@@"),
    ("?_M_reallocate_map@?$deque@PAXV?$allocator@PAX@_STL@@@_STL@@IAEXI_N@Z",
     "deque", "PAX"),
    ("?_M_insert_dispatch@?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@",
     "list", "VAsciiString@@"),
])
def test_reads_the_container_and_element_out_of_a_member_name(name, container, element):
    assert gen_small.tinst_element(name) == (container, element)


def test_a_name_that_is_not_a_sequence_container_is_not_a_candidate():
    """_Rb_tree and hashtable carry several type parameters and no single
    element, so the one-parameter reader must decline them outright."""
    tree = ("?insert_unique@?$_Rb_tree@VUnicodeString@@U?$pair@$$CBVUnicodeString@@"
            "_N@_STL@@@_STL@@")
    assert gen_small.tinst_element(tree) == (None, None)


def _reader(image):
    def read(rva, size):
        return image.get(rva, b"")[:size]
    return read


def test_follows_the_incremental_link_stub_to_the_body():
    """reloc_names.csv records the ILT entry, so 0x000264D1 is five bytes of
    `jmp rel32` and the 265-byte body is what a row has to claim."""
    # e9 <disp>: 0x000D32E0 - (0x000264D1 + 5) == 0x000ACE0A
    read = _reader({0x000264D1: bytes([0xE9]) + (0x000ACE0A).to_bytes(4, "little"),
                    0x000D32E0: bytes([0x83, 0xEC, 0x08])})
    assert gen_small.tinst_resolve(read, 0x000264D1) == 0x000D32E0


def test_an_address_that_is_already_a_body_is_returned_unchanged():
    read = _reader({0x000D32E0: bytes([0x83, 0xEC, 0x08, 0x53, 0x8B])})
    assert gen_small.tinst_resolve(read, 0x000D32E0) == 0x000D32E0


def test_a_stub_chain_terminates_instead_of_spinning():
    """A jmp to itself is a linker artifact, not a body; the walk is bounded so
    a malformed table cannot hang the sweep."""
    read = _reader({0x00001000: bytes([0xE9]) + (-5 & 0xFFFFFFFF).to_bytes(4, "little")})
    assert gen_small.tinst_resolve(read, 0x00001000) == 0x00001000


def test_a_truncated_read_is_not_mistaken_for_a_stub():
    """Past the end of .text the reader returns short, which must not decode as
    a jump into whatever the next bytes happen to be."""
    read = _reader({0x00FFFFFC: bytes([0xE9, 0x01])})
    assert gen_small.tinst_resolve(read, 0x00FFFFFC) == 0x00FFFFFC


def test_a_name_table_data_address_is_not_treated_as_code():
    def read(rva, _size):
        raise ValueError(f"RVA 0x{rva:08X} is outside all PE sections")

    assert gen_small.tinst_resolve(read, 0x0130BCA0) is None


# The call slots are the half a masked comparison cannot see, and they are where
# two instantiations that compile to identical code differ: deque<int>'s
# _M_push_back_aux_v is its neighbours' code reaching a different
# _M_reallocate_map. So the pin has to come out of the RETAIL bytes.

def test_a_rel32_callee_is_pinned_at_the_address_retail_reaches():
    # e8 90 06 9c ff at offset 35 of the body at 0x006472C0 reaches 0x00007978
    retail = bytes(35) + bytes([0xE8]) + (0x00007978 - (0x006472C0 + 35 + 5)
                                          & 0xFFFFFFFF).to_bytes(4, "little")
    pins = gen_small.tinst_callee_pins(
        0x006472C0, retail, [(36, 0x0014, "?_M_reallocate_map@@YAXXZ")], {})
    assert pins == {"?_M_reallocate_map@@YAXXZ,0x00007978"}


def test_a_name_that_already_answers_is_not_pinned_again():
    """symbols.csv is additive, so a second address under one name turns that
    name's slot into a wildcard for every other site that uses it."""
    retail = bytes(4) + bytes([0xE8, 0x00, 0x00, 0x00, 0x00])
    pinned = {"?_M_reallocate_map@@YAXXZ": {0x009EE360}}
    assert gen_small.tinst_callee_pins(
        0x006472C0, retail, [(5, 0x0014, "?_M_reallocate_map@@YAXXZ")], pinned) == set()


def test_only_rel32_slots_are_pinned():
    """A DIR32 slot holds an absolute address, not a displacement, so decoding
    it as one would pin a nonsense target."""
    retail = bytes([0x00] * 8)
    assert gen_small.tinst_callee_pins(
        0x006472C0, retail, [(0, 0x0006, "?some_data@@3HA")], {}) == set()


def test_a_slot_running_past_the_body_is_not_decoded():
    assert gen_small.tinst_callee_pins(
        0x006472C0, bytes([0xE8, 0x01]), [(1, 0x0014, "?f@@YAXXZ")], {}) == set()
