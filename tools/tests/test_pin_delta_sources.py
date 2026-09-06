#!/usr/bin/env python3
"""The gate hole d27ae4b7b went through, and the mode that closes it.

That commit deleted 1,599 reverse/symbols.csv pins and byte-verified two files.
Both hooks size their build from tools/delta_sources.py, which reads
functions.csv and nothing else, so the deletion was invisible to them: 612 rows
went red. GameLogic.cpp is 17/70 red on master today and 70/70 with those pins
put back, which is what makes it a fair anchor -- its redness is caused by the
deletion, not merely correlated with it.

The CONTRAST between the two modes over that one range is the regression test.
A pin mode that quietly returned the same two files would pass a weaker test;
so would one that gave up and returned the whole tree, which is the other way
to make this hook useless. Both are asserted against here.
"""
import importlib.util
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"

OLD, NEW = "d27ae4b7b~1", "d27ae4b7b"
CONVERTED = ["Code/Libraries/Source/WWVegas/WW3D2/BoxDynamicVBAccess_AllocateDX8.cpp",
             "Code/Libraries/Source/WWVegas/WW3D2/BoxDynamicVBAccess_AllocateSorting.cpp"]
REDDENED = "Code/GameEngine/Source/GameLogic/System/GameLogic.cpp"

pytestmark = pytest.mark.skipif(
    not EXE.exists() or subprocess.run(["git", "-C", str(ROOT), "cat-file", "-e", NEW],
                                       capture_output=True).returncode != 0,
    reason="retail baseline or the d27ae4b7b history is not present")


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
delta_sources = _load("delta_sources")


def run(*args):
    out = subprocess.run([sys.executable, str(TOOLS / "delta_sources.py"), "--range", OLD, NEW]
                         + list(args), capture_output=True, text=True, cwd=str(ROOT))
    assert out.returncode == 0, out.stderr
    return out.stdout.split()


@pytest.fixture(scope="module")
def pin_sources():
    return run("--pins")


def test_plain_delta_sees_only_the_two_converted_files():
    """The whole byte-verify set the hooks had for a 1,599-pin deletion."""
    assert run() == CONVERTED


def test_pin_mode_sees_a_source_the_deletion_reddened(pin_sources):
    assert REDDENED in pin_sources
    print(f"PASS {REDDENED} is in the {len(pin_sources)}-source pin-deletion set")


def test_pin_mode_stays_scoped(pin_sources):
    """Not a disguised full gate: the failure mode on the other side is a mode
    that answers "rebuild everything" and therefore never runs."""
    everything = {row["source"] for row in delta_sources.dict_rows_at(f"{NEW}:{delta_sources.LEDGER}")
                  if row["status"] == "matched"}
    assert REDDENED in everything
    assert len(pin_sources) < len(everything) / 2, (len(pin_sources), len(everything))


def test_a_pin_the_ledger_still_supplies_is_not_a_lost_resolution():
    """Why a routine pin edit costs nothing. symbols.csv pins CALL TARGETS, and
    the same address usually also arrives from the row that matched the body, so
    deleting the pin removes no candidate and scopes to no source at all."""
    body, thunks = next(iter(_thunked().items()))
    rows = [{"name": "?f@@YAXXZ", "target_rva": f"0x{body:08X}"}]
    assert delta_sources.lost_candidates({("?f@@YAXXZ", body)}, set(), rows,
                                         {body: thunks}) == {}


def test_a_deleted_pin_takes_its_incremental_link_thunks_with_it():
    """Most call sites in the image encode the ILT thunk, not the body, so a
    deletion that only invalidated the body address would miss its own callers."""
    body, thunks = next(iter(_thunked().items()))
    lost = delta_sources.lost_candidates({("?f@@YAXXZ", body)}, set(), [], {body: thunks})
    assert set(lost) == {body, *thunks}
    assert all(names == {"?f@@YAXXZ"} for names in lost.values())


def test_call_sites_are_read_out_of_retail_not_out_of_our_objects():
    """A site is only at risk if RETAIL encodes the lost address there. Reading
    that from the image is what lets the mode bound the blast radius on a clone
    with no build/match objects at all."""
    body, thunks = next(iter(_thunked().items()))
    sites = delta_sources.call_sites({thunks[0]: {"?f@@YAXXZ"}})
    assert sites, thunks
    assert all(callee == thunks[0] for _site, callee in sites)


def _thunked():
    """{body: [thunk rvas]} for one thunked function in the retail image."""
    body, thunks = next(iter(delta_sources.build.build_call_thunks().items()))
    return {body: thunks}
