#!/usr/bin/env python3
"""`mods/dist` is the artifact every ladder player would run. Verify it.

Nothing checked this. `--dist` guarded only against UNSHIPPED feature names, so
`--only X --dist` quietly rewrote the shipped executable with a build carrying
ONLY X -- and it happened: dist went to a one-feature build with 020-gameresult
and 031-earlysend absent, from a test that had merely been flipped to expect
success. It was caught by hashing the file by hand afterwards, which is not a
control.

These tests make that failure loud and instant. They read the tree only; none of
them builds anything, because a test that rebuilds `mods/dist` to check
`mods/dist` is the bug it is meant to catch.
"""
import hashlib
import json
import struct
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

DIST = ROOT / "mods/dist/lotrbfme.exe"
MANIFEST = ROOT / "mods/dist/manifest.json"

pytestmark = pytest.mark.skipif(not DIST.exists(), reason="no dist build present")

JMP_REL32 = 0xE9


@pytest.fixture(scope="module")
def manifest():
    return json.loads(MANIFEST.read_text(encoding="utf-8"))


@pytest.fixture(scope="module")
def image():
    return DIST.read_bytes()


def test_dist_matches_its_own_manifest(image, manifest):
    """The single check that catches every accidental rewrite.

    A partial build, a stale artifact, a hand-edited byte and a half-finished
    `modbuild` run all fail here, because none of them reproduces the recorded
    digest.
    """
    assert len(image) == manifest["output"]["size"], (
        f"dist is {len(image)} bytes, manifest says {manifest['output']['size']}")
    got = hashlib.sha256(image).hexdigest()
    assert got == manifest["output"]["sha256"], (
        f"mods/dist/lotrbfme.exe does not match its manifest.\n"
        f"  on disk   {got}\n"
        f"  manifest  {manifest['output']['sha256']}\n"
        f"Rebuild with `python3 tools/modbuild.py --dist` (never with --only), "
        f"or restore with `git checkout -- mods/dist/`.")


def test_dist_was_built_from_the_recorded_baseline(manifest):
    """A correct-looking dist built from the wrong retail image is still wrong.

    Every absolute address the cave payloads use is pinned to this exact
    executable, so a different baseline silently relocates all of them.
    """
    base = ROOT / manifest["baseline"]["path"]
    if not base.exists():
        pytest.skip("retail baseline not present")
    assert base.stat().st_size == manifest["baseline"]["size"]
    assert hashlib.sha256(base.read_bytes()).hexdigest() == manifest["baseline"]["sha256"], (
        "the retail baseline on disk is not the one dist was built from")


def test_dist_carries_every_shipped_feature(manifest):
    """The manifest must name all of FEATURES, not a subset.

    This is the check that a one-feature build fails even if someone also
    regenerated the manifest, which the digest test alone would then accept.
    """
    import modbuild
    named = {f["name"] for f in manifest["features"]}
    missing = set(modbuild.FEATURES) - named
    assert not missing, (
        f"dist manifest is missing {sorted(missing)}: mods/dist must carry all "
        f"of FEATURES ({', '.join(sorted(modbuild.FEATURES))}), never a subset")
    unshipped = named & set(modbuild.UNSHIPPED)
    assert not unshipped, f"dist carries UNSHIPPED features: {sorted(unshipped)}"


def test_every_claimed_target_actually_changed(image, manifest):
    """The bytes must agree with the manifest, not just the digest.

    A digest proves the file is the one that was built; this proves the build
    did what it claimed. They fail independently: a manifest regenerated over a
    bad build passes the first and fails this.

    Asserted as "differs from retail" rather than "is a jmp", because the
    manifest does not record which kind of change a feature makes and the two
    are not interchangeable: 031/020 install `jmp rel32` detours, while
    033-retrytime rewrites one imm32 three bytes inside a `mov`, leaving 0x90 at
    its recorded target. Difference-from-baseline is the invariant both satisfy,
    and it needs no format change to stay true for whatever lands next.
    """
    base_path = ROOT / manifest["baseline"]["path"]
    if not base_path.exists():
        pytest.skip("retail baseline not present")
    retail = base_path.read_bytes()
    for feature in manifest["features"]:
        rva = int(feature["target_rva"], 16)
        window = slice(rva, rva + 5)
        assert image[window] != retail[window], (
            f"{feature['name']} claims {feature['target_rva']} but dist is "
            f"byte-identical to retail there -- the feature is not installed")


def test_the_detour_features_install_a_jmp(image, manifest):
    """The two cave features specifically, since 'differs from retail' would
    also accept a wrong or half-written patch at their targets."""
    import modbuild
    detours = {"031-earlysend", "020-gameresult"}
    for feature in manifest["features"]:
        if feature["name"] not in detours:
            continue
        rva = int(feature["target_rva"], 16)
        assert image[rva] == JMP_REL32, (
            f"{feature['name']} claims a detour at {feature['target_rva']} but "
            f"the byte there is 0x{image[rva]:02X}, not a jmp rel32")


def test_the_retransmit_timer_is_actually_poked(image):
    """033-retrytime has no detour -- it is one imm32 -- so the loop above
    cannot see it, and a dist that silently lost it would look healthy.

    Asserted on the instruction as well as the value: an address off by one
    writes a plausible number into the middle of `mov dword ptr [edx+0x1C]`.
    """
    import modbuild
    if "033-retrytime" not in modbuild.FEATURES:
        pytest.skip("033-retrytime is not a shipped feature")
    store = modbuild.TARGET_RETRYTIME - 3
    assert image[store:store + 3] == bytes([0xC7, 0x42, 0x1C]), (
        "the retry-timer store is not where the poke expects it")
    got = struct.unpack_from("<I", image, modbuild.TARGET_RETRYTIME)[0]
    assert got == modbuild.RETRY_MS, (
        f"dist retry timer is {got} ms, expected {modbuild.RETRY_MS}")


def test_dist_is_not_a_probe_build(image, manifest):
    """A diagnostic build must never be shipped.

    030-netlatprobe writes tens of JSONL lines a second to disk during play. It
    is invaluable on the rig and would be a performance bug in a player's hands,
    and the two builds differ only by a section that is present in both.
    """
    import modbuild
    assert image[modbuild.TARGET_DISCARD] != JMP_REL32, (
        "mods/dist carries the netlatprobe discard hook -- this is a --probe "
        "build and must not ship")
    assert "030-netlatprobe" not in {f["name"] for f in manifest["features"]}
