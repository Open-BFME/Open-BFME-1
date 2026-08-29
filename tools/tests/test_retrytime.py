#!/usr/bin/env python3
"""Build the retransmit-timer arm and check it changed four bytes and no others.

This feature has no payload and no detour, so the usual cave assertions say
nothing about it. What can go wrong instead is arithmetic: the constant is an
imm32 three bytes into `mov dword ptr [edx+0x1C], 2000`, and an address off by
one writes a value that is still plausible into the middle of an instruction.
So the instruction around the poke is asserted, not just the poke, and the rest
of the retail image is asserted to be untouched -- a spike arm that quietly
moved something else would be credited or blamed for it.
"""
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
pytestmark = pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")

from cave import PE  # noqa: E402
from modbuild import RETRY_MS, RETRY_WAS, TARGET_RETRYTIME  # noqa: E402

FEATURE = "033-retrytime"
STORE = 0x006623DB                        # Connection::init's m_retryTime store
STORE_BYTES = bytes([0xC7, 0x42, 0x1C])   # mov dword ptr [edx+0x1C], imm32


@pytest.fixture(scope="module")
def built():
    out = Path(tempfile.mkdtemp()) / "retry.exe"
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", FEATURE, "-o", str(out)],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    return PE(out)


def test_the_poke_sits_inside_the_store_it_claims_to():
    """Asserted against retail, not against the build: if the opcode is not
    there, every other assertion here is about the wrong bytes."""
    pe = PE(EXE)
    assert pe.read(STORE, 3) == STORE_BYTES, f"0x{STORE:08X} is not the m_retryTime store"
    assert TARGET_RETRYTIME == STORE + 3, "the imm32 is three bytes into the store"
    assert struct.unpack("<I", pe.read(TARGET_RETRYTIME, 4))[0] == RETRY_WAS


def test_the_timer_is_the_new_value(built):
    assert struct.unpack("<I", built.read(TARGET_RETRYTIME, 4))[0] == RETRY_MS
    assert built.read(STORE, 3) == STORE_BYTES, "the poke overwrote the opcode"


def test_a_shorter_timer_is_the_point():
    """An arm that raised the timer would measure the opposite of what the
    feature claims, and the histogram it is judged on would still look moved."""
    assert 0 < RETRY_MS < RETRY_WAS


def test_nothing_else_in_the_retail_image_moved(built):
    retail = PE(EXE).data
    got = built.data[:len(retail)]
    differ = {i for i in range(len(retail)) if retail[i] != got[i]}
    site = set(range(built.rva_to_off(TARGET_RETRYTIME),
                     built.rva_to_off(TARGET_RETRYTIME) + 4))
    # Containment, not equality: 2000 and 400 share their two high bytes, so a
    # correct poke leaves two of its four bytes untouched. Requiring all four to
    # differ would fail on a working feature and pass only by coincidence of
    # which values were chosen.
    body = {i for i in differ if i >= 0x1000}
    assert body <= site, f"{len(body - site)} bytes outside the poke changed"
    assert body, "the build is byte-identical to retail: the poke never landed"


def test_it_is_promoted_and_dist_would_accept_it():
    """This test previously asserted the OPPOSITE, and the flip is the point.

    While the duplicate-delivery half was unmeasured, `--dist` refused this
    feature: at 40 ms round trip a 400 ms timer essentially never fires before
    the ack, so nothing exercised a command arriving twice, and a lockstep
    command executed twice is a desync rather than a bandwidth cost.

    That gate has been discharged by measurement -- duplicates counted directly
    at 150 ms and 300 ms round trip occur in every arm INCLUDING retail
    (0.45-2.20%) and are all absorbed, and the discard guard was measured at the
    decision site, where retail crosses it and a 400 ms timer never comes within
    five frames.

    Kept rather than deleted because a promoted feature silently un-asserts its
    own guard: without this, the suite would pass with the gate gone and nothing
    would record that it existed or why it was lifted.

    NOTE THIS DOES NOT SHELL OUT TO `--dist`. The refusal version could, safely,
    because it failed BEFORE writing anything. The accepting version writes
    `mods/dist` for real -- and with `--only` it writes a build carrying ONLY
    this feature, silently replacing the shipped artifact with one missing
    020-gameresult and 031-earlysend. That happened once. The registry check
    below tests the same property and cannot touch the tree.
    """
    import modbuild
    assert FEATURE in modbuild.FEATURES, (
        f"{FEATURE} is not in FEATURES, so --dist would still refuse it")
    assert FEATURE not in modbuild.UNSHIPPED, (
        f"{FEATURE} is still listed UNSHIPPED: {modbuild.UNSHIPPED.get(FEATURE)}")


def test_dist_still_refuses_an_unshipped_feature():
    """The gate itself must still work, or the check above is vacuous.

    034-framedrain is refuted and must never reach a --dist build. This is safe
    to run for the same reason the old version was: it fails before writing.
    """
    r = subprocess.run([sys.executable, str(ROOT / "tools/modbuild.py"),
                        "--only", "034-framedrain", "--dist"],
                       capture_output=True, text=True, cwd=ROOT)
    assert r.returncode != 0, "a --dist build accepted a refuted arm"
    assert "refusing --dist" in (r.stderr + r.stdout)
