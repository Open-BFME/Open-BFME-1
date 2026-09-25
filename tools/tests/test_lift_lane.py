"""Extent checks that decide whether a named __emit lift is servable work.

An __emit lift byte-matches whatever extent it claims, so these checks are the
only thing that stands between a picker and a body with the wrong bounds. Each
case is a shape found in the real ledger on 2026-09-25.
"""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

pytest.importorskip("capstone")
import lift_lane  # noqa: E402

BASE = 0x00400000
ORIGIN = 0x1000


def image(*chunks):
    """A reader over consecutive byte chunks laid out from ORIGIN."""
    data = b"".join(chunks)

    def read(rva, size):
        lo = rva - ORIGIN
        return data[max(lo, 0):max(lo + size, 0)]
    return read


PAD = b"\xcc" * 16
# push ebp; mov ebp, esp; pop ebp; ret  -- padded to 16 with int3
LEAF = b"\x55\x8b\xec\x5d\xc3" + b"\xcc" * 11
LEAF_AT = ORIGIN + 16


def problems(name, rva, size, read, starts=(), ends=()):
    return lift_lane.extent_problems(name, rva, size, set(starts), set(ends), read, BASE)


def test_a_padded_leaf_is_clean():
    read = image(PAD, LEAF, PAD)
    assert problems("?f@@YAXXZ", LEAF_AT, 5, read) == []


def test_a_truncated_end_is_refused():
    # Ghidra-sized lifts stop a few bytes before the real ret.
    read = image(PAD, LEAF, PAD)
    found = problems("?f@@YAXXZ", LEAF_AT, 4, read)
    assert any(p.startswith("end: neither int3") for p in found)
    assert any(p.startswith("end: last instruction is pop") for p in found)


def test_a_start_inside_an_instruction_is_refused():
    # 0x004800FC: the claim began on the last byte of `mov [imm32], eax`.
    body = b"\x55\xa3\xc0\x1b\x2f\x01\x5d\xc3"
    read = image(PAD, body, PAD)
    found = problems("?f@@YAXXZ", LEAF_AT + 5, 3, read)
    assert any(p.startswith("start: neither int3") for p in found)


def test_a_jump_table_after_the_extent_is_refused():
    # executeAction stopped at its ret, leaving its own table outside the claim.
    code = b"\x55\x5d\xc3"
    table = (BASE + LEAF_AT).to_bytes(4, "little")
    read = image(PAD, code, table, PAD)
    found = problems("?f@@YAXXZ", LEAF_AT, len(code), read)
    assert "end: a jump table into the body follows the extent" in found


def test_an_in_body_switch_table_is_not_decoded_as_code():
    # jmp dword ptr [eax*4 + T] with T inside the body, then the table itself.
    table_at = LEAF_AT + 12
    code = b"\xff\x24\x85" + (BASE + table_at).to_bytes(4, "little") + b"\xc3" + b"\x90" * 4
    table = (BASE + LEAF_AT).to_bytes(4, "little") * 2
    read = image(PAD, code, table, PAD)
    assert problems("?f@@YAXXZ", LEAF_AT, len(code) + len(table), read) == []


def test_a_noreturn_call_before_padding_is_an_end():
    code = b"\x6a\x00\xe8\x00\x00\x00\x00"   # push 0; call rel32
    read = image(PAD, code, PAD)
    assert problems("?f@@YAXXZ", LEAF_AT, len(code), read) == []


def test_stack_cleanup_must_agree_with_the_name():
    code = b"\x55\x5d\xc2\x04\x00"           # ret 4 on a no-argument thiscall
    read = image(PAD, code, PAD)
    found = problems("?m@C@@QAEXXZ", LEAF_AT, len(code), read)
    assert any(p.startswith("arity:") for p in found)


def test_a_start_that_decodes_to_hlt_is_refused():
    read = image(PAD, b"\xf4\x55\x5d\xc3", PAD)
    found = problems("?f@@YAXXZ", LEAF_AT, 4, read)
    assert "start: first instruction is hlt" in found


def _ledger(*spans):
    rows = [{"status": "matched", "target_rva": f"0x{s:08X}", "target_size": str(n)}
            for s, n in spans]
    return lift_lane.Ledger(rows)


def test_proposed_extent_grows_a_short_end_to_the_padding():
    read = image(PAD, LEAF, PAD)
    row = {"name": "?f@@YAXXZ", "target_rva": f"0x{LEAF_AT:08X}", "target_size": "4"}
    found = problems("?f@@YAXXZ", LEAF_AT, 4, read)
    start, size, evidence = lift_lane.proposed_extent(row, found, _ledger((LEAF_AT, 4)), read)
    assert (start, size) == (LEAF_AT, 5)
    assert "int3" in evidence


def test_proposed_extent_never_crosses_another_claim():
    read = image(PAD, LEAF, PAD)
    row = {"name": "?f@@YAXXZ", "target_rva": f"0x{LEAF_AT:08X}", "target_size": "4"}
    found = problems("?f@@YAXXZ", LEAF_AT, 4, read)
    # Someone else already claims the byte the correction would need.
    ledger = _ledger((LEAF_AT, 4), (LEAF_AT + 4, 1))
    assert lift_lane.proposed_extent(row, found, ledger, read) is None


def test_arity_refusals_are_not_boundary_corrections():
    read = image(PAD, LEAF, PAD)
    row = {"name": "?m@C@@QAEXXZ", "target_rva": f"0x{LEAF_AT:08X}", "target_size": "5"}
    assert lift_lane.proposed_extent(row, ["arity: x"], _ledger((LEAF_AT, 5)), read) is None


def test_ledger_edges_hide_only_the_row_being_judged():
    ledger = _ledger((0x1000, 0x10), (0x1010, 0x10))
    starts, ends = ledger.edges((0x1010, 0x10))
    assert 0x1000 in starts and 0x1010 not in starts
    assert 0x1010 in ends and 0x1020 not in ends
    assert ledger.claimed(0x1008, 0x1012, (0x1010, 0x10))
    assert not ledger.claimed(0x1010, 0x1020, (0x1010, 0x10))
