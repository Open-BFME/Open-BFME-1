"""Callee contracts inferred from retail bytes (tools/callee_protos.py).

Every case is a shape met while calibrating on landed rows (2026-09-26).
"""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

pytest.importorskip("capstone")
import callee_protos as P  # noqa: E402

ORIGIN = 0x1000


def image(monkeypatch, code):
    def read(rva, size):
        lo = rva - ORIGIN
        return code[max(lo, 0):max(lo + size, 0)]
    monkeypatch.setattr(P, "read", read)


def test_callee_cleanup_with_this_is_thiscall():
    line = P.contract([8], "read", [], 0, 0, "", sites=0)
    assert line.startswith("__thiscall, 2 stack slot(s)")


def test_callee_cleanup_without_this_is_stdcall_but_says_so():
    line = P.contract([4], "write", [], 0, 0, "", sites=0)
    assert line.startswith("__stdcall (or a __thiscall that never reads `this`), 1 stack slot(s)")


def test_callers_loading_ecx_outrank_a_body_that_ignores_it():
    line = P.contract([4], "none", [], 0, 0, "", ecx_set=3, ecx_decided=3, sites=3)
    assert line.startswith("__thiscall, 1 stack slot(s)")


def test_cleanup_after_a_thiscall_is_deferred_not_arity():
    # doEnableInput: callers load ecx, the body pops nothing, and the `add esp`
    # after the call belongs to an earlier __cdecl call.
    line = P.contract([0], "read", [112], 0, 1, "", ecx_set=1, ecx_decided=1, sites=1)
    assert line.startswith("__thiscall, 0 stack slots")


def test_cdecl_arity_is_the_smallest_cleanup():
    line = P.contract([0], "none", [8, 16, 8], 2, 3, "", ecx_set=0, ecx_decided=3, sites=3)
    assert line.startswith("__cdecl, 2 stack slot(s)")
    assert "returns a value [eax read at 2/3 sites]" in line


def test_cdecl_with_no_visible_cleanup_does_not_claim_zero():
    line = P.contract([0], "none", [], 0, 0, "void f(int param_1)", sites=0)
    assert "stack slots unknown (no direct call site)" in line
    assert "ghidra reads 1" in line


def test_push_ecx_is_a_local_slot_not_this(monkeypatch):
    # push ecx; mov eax, [esp+8]; pop ecx; ret
    image(monkeypatch, b"\x51\x8b\x44\x24\x08\x59\xc3")
    assert P.body_evidence(ORIGIN, 7) == ([0], "write")


def test_ret_n_is_read_from_every_return(monkeypatch):
    # mov eax, [ecx]; ret 8
    image(monkeypatch, b"\x8b\x01\xc2\x08\x00")
    assert P.body_evidence(ORIGIN, 5) == ([8], "read")


def _caller(monkeypatch, code):
    image(monkeypatch, code)
    monkeypatch.setattr(P, "_spans", lambda: [(ORIGIN, len(code))])
    P._decoded.cache_clear()
    return ORIGIN + code.index(b"\xe8")


def test_an_argument_load_is_not_this(monkeypatch):
    # mov ecx, [esp+4]; push ecx; call f
    site = _caller(monkeypatch, b"\x8b\x4c\x24\x04\x51\xe8\x00\x00\x00\x00\xc3")
    assert P.caller_sets_ecx(site) is False


def test_a_this_load_walks_past_reads(monkeypatch):
    # mov ecx, esi; mov edi, ecx; push 0; call f
    site = _caller(monkeypatch, b"\x8b\xce\x8b\xf9\x6a\x00\xe8\x00\x00\x00\x00\xc3")
    assert P.caller_sets_ecx(site) is True


def test_a_call_in_between_clobbers_ecx(monkeypatch):
    # mov ecx, esi; call g; push eax; call f
    site_code = b"\x8b\xce\xe8\x00\x00\x00\x00\x50\xe8\x00\x00\x00\x00\xc3"
    image(monkeypatch, site_code)
    monkeypatch.setattr(P, "_spans", lambda: [(ORIGIN, len(site_code))])
    P._decoded.cache_clear()
    assert P.caller_sets_ecx(ORIGIN + 8) is False


def test_cleanup_and_eax_after_a_call(monkeypatch):
    # call f; add esp, 8; test eax, eax; ret
    image(monkeypatch, b"\xe8\x00\x00\x00\x00\x83\xc4\x08\x85\xc0\xc3")
    assert P.site_evidence(ORIGIN) == (8, True)


def test_xor_eax_eax_after_a_call_is_not_a_result_read(monkeypatch):
    # call f; pop ecx; xor eax, eax; ret
    image(monkeypatch, b"\xe8\x00\x00\x00\x00\x59\x33\xc0\xc3")
    assert P.site_evidence(ORIGIN) == (4, False)


def test_rare_cleanup_is_deferred_not_arity():
    # __ftol2: `add esp` after 4 of 1,284 sites, every one an earlier call's
    line = P.contract([0], "write", [4, 4, 4, 16], 1242, 1273, "", ecx_decided=994, sites=1284)
    assert "stack slots unknown (cleanup after only 4/1284 sites" in line
