"""The add_match-only boundary guard catches byte-green C++ prefixes.

The ordinary build still compares a ledger row's requested bytes.  These tests
exercise the one extra fact requested by add_match: a newly claimed compiled
body may be rejected only when the boundary cuts a proven instruction or a
known in-body edge reaches an omitted executable epilogue.  Calls can be
noreturn, traps are valid bodies, and inline dispatch data is ambiguous.  The
compiler's COFF section may continue with padding or another function, so a raw
full-size equality rule would be wrong.
"""
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match
import build


TRACKER = bytes.fromhex(
    "8b01 85c0 742b 8b542404 56 eb03 8d4900 8b30 395608 740b "
    "8b4004 85c0 75f2 5e c20400 89442408 8d442408 50 "
    "e8 60 fa ff ff 5e c20400"
)
TRACKER_RELOC = [(44, build.REL32, "?erase@List@@QAEXPAVNode@@@Z")]
DISPLAY = bytes.fromhex(
    "56 8b31 57 8b7904 3bf7 7413 eb03 8d4900 8b0e "
    "e8 08 38 bb ff 83c604 3bf7 75f2 5f 5e c3"
)


def row(name="?candidate@Test@@QAEXXZ", source="Code/Test.cpp", notes=""):
    return {
        "name": name,
        "source": source,
        "target_rva": "0x00401000",
        "target_size": "0",
        "status": "matched",
        "notes": notes,
    }


def check(compiled, claimed_size, *, relocs=(), name="?candidate@Test@@QAEXXZ"):
    candidate = row(name=name)
    candidate["target_size"] = str(claimed_size)
    patch = {"compiled": compiled, "target": b"\0" * claimed_size,
             "relocs": relocs}
    build.verify_claimed_boundary(candidate, patch)


def rejected(compiled, claimed_size, *, relocs=(), name="?candidate@Test@@QAEXXZ"):
    with pytest.raises(SystemExit) as excinfo:
        check(compiled, claimed_size, relocs=relocs, name=name)
    message = str(excinfo.value)
    assert name in message
    assert str(claimed_size) in message
    return message


def test_tracker_prefix_is_rejected_before_ret4_after_pop_esi():
    message = rejected(TRACKER, 49, relocs=TRACKER_RELOC,
                       name="?bfmeDrop@BfmeTracker4310@@QAEXPAVBfmeObj4310@@@Z")

    assert "omitted executable epilogue" in message
    assert "ret 4" in message


def test_display_prefix_is_rejected_before_two_pops_and_ret():
    message = rejected(DISPLAY, 30,
                       name="?reset@Rva0048EE10Child@@QAEXXZ")

    assert "branches" in message
    assert "je" in message
    assert "pop edi, pop esi, ret" in message


@pytest.mark.parametrize("compiled, size, relocs", [
    (TRACKER, len(TRACKER), TRACKER_RELOC),
    (DISPLAY, len(DISPLAY), ()),
    (bytes.fromhex("558bec5dc3"), 5, ()),
    (bytes.fromhex("558bec5dc3cccc"), 7, ()),
])
def test_complete_return_bodies_and_trailing_padding_are_accepted(
        compiled, size, relocs):
    check(compiled, size, relocs=relocs)


def test_direct_relocated_tail_jump_is_accepted():
    # The zero pre-link displacement is not evidence of an internal jump; the
    # REL32 relocation identifies it as an ordinary external tail call.
    check(bytes.fromhex("e900000000"), 5,
          relocs=[(1, build.REL32, "?callee@Test@@YAXXZ")])


@pytest.mark.parametrize("callee", ["abort", "__CxxThrowException@8"])
def test_noreturn_call_followed_by_int3_is_not_called_incomplete(callee):
    # A call to abort/throw need not return.  The post-call INT3 is compiler
    # padding for the unreachable continuation, not an omitted return epilogue.
    check(bytes.fromhex("e800000000cc"), 5,
          relocs=[(1, build.REL32, callee)])


@pytest.mark.parametrize("compiled", [
    bytes.fromhex("0f0b"),
    bytes.fromhex("0f0bcccc"),
])
def test_ud2_trap_is_a_valid_complete_body(compiled):
    check(compiled, 2)


def test_inline_switch_table_data_is_left_ambiguous():
    # `jmp [eax*4]` is an indirect dispatch; the following dwords are an
    # inline table, not a linear instruction stream that must end in `ret`.
    # The boundary guard has no proof that this data is an omitted epilogue.
    compiled = bytes.fromhex("ff2485 10203040 50607080 90a0b0c0")
    check(compiled, len(compiled))


def test_internal_forward_jump_to_omitted_epilogue_is_rejected():
    # jmp +0 lands on the ret immediately after the claim.  It is a local
    # branch, not a tail call, so stopping at the jmp hides the epilogue.
    message = rejected(bytes.fromhex("eb00c3"), 2)

    assert "jmp" in message
    assert "omitted executable epilogue" in message


def test_conditional_false_edge_falls_through_to_omitted_epilogue():
    message = rejected(bytes.fromhex("90 75fd 5f 5e c3"), 3)

    assert "falls through" in message
    assert "pop edi, pop esi, ret" in message


def test_claim_cutting_a_multibyte_instruction_is_rejected():
    message = rejected(bytes.fromhex("b801000000c3"), 3)

    assert "cuts instruction" in message
    assert "mov eax, 1" in message


def test_object_symbol_alias_checks_the_body_selected_by_the_row(monkeypatch):
    body = bytes.fromhex("558bec5dc3")
    alias = row(name="?alias@Test@@QAEXXZ", notes="object-symbol=_actual")
    alias["target_size"] = str(len(body))
    monkeypatch.setattr(build, "read_target_bytes", lambda _rva, _size: body)

    def read_selected(_path, symbol, _expected_size=None):
        assert symbol == "_actual"
        return body, []

    monkeypatch.setattr(build, "read_object_symbol_bytes", read_selected)
    patch = build.compile_function(
        alias, {}, Path("test.obj"), retain_compiled=True)

    # The boundary check consumes the raw bytes returned for object-symbol,
    # independently of the ledger-facing alias name.
    assert patch["compiled"] == body
    build.verify_claimed_boundary(alias, patch)


def test_add_match_passes_only_the_new_cpp_row_to_the_build_child(
        monkeypatch, tmp_path):
    root = tmp_path
    (root / "reverse").mkdir()
    source = root / "Code" / "Candidate.cpp"
    source.parent.mkdir()
    source.write_text("void candidate() {}\n", encoding="utf-8")
    (root / "reverse" / "functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\r\n",
        encoding="utf-8")
    build_sh = root / "build.sh"
    build_sh.write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    build_sh.chmod(0o755)
    calls = []

    def fake_build(command, *, cwd, env):
        calls.append((command, cwd, env))
        return SimpleNamespace(returncode=0)

    monkeypatch.setattr(add_match.subprocess, "run", fake_build)
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", "?candidate@Test@@QAEXXZ", "0x00401000", "5",
        "Code/Candidate.cpp", "--root", str(root),
    ])

    add_match.main()

    assert len(calls) == 1
    environment = calls[0][2]
    assert environment[add_match.BOUNDARY_ENV["name"]] == "?candidate@Test@@QAEXXZ"
    assert environment[add_match.BOUNDARY_ENV["rva"]] == "0x00401000"
    assert environment[add_match.BOUNDARY_ENV["source"]] == "Code/Candidate.cpp"


@pytest.mark.parametrize("suffix, expected", [
    (".cpp", True),
    (".c", True),
    (".asm", False),
    (".s", False),
    (".lib", False),
])
def test_add_match_requests_the_guard_only_for_compiled_sources(
        suffix, expected):
    source = Path("candidate" + suffix)
    environment = add_match.verification_environment(
        source, "Code/candidate" + suffix, "?f@Test@@YAXXZ", 0x401000)

    has_request = all(variable in environment for variable in add_match.BOUNDARY_ENV.values())
    assert has_request is expected
    if not expected:
        assert not any(variable in environment for variable in add_match.BOUNDARY_ENV.values())


def test_no_boundary_request_keeps_normal_builds_unmodified(monkeypatch):
    for variable in add_match.BOUNDARY_ENV.values():
        monkeypatch.delenv(variable, raising=False)
    assert build._boundary_request() is None


def test_bytes_after_backward_unconditional_jump_are_not_linear_code():
    # The unconditional back edge has no fallthrough. Following section bytes
    # cannot establish a split executable instruction in the claimed body.
    check(bytes.fromhex("ebfe b801"), 4)
