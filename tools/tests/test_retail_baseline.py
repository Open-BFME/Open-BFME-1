"""The game baseline is the workshop image with its crack patches reverted, and its manifest says which bytes."""
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import eligibility

WORKSHOP = build.ROOT / "inputs/baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"


def test_reverted_patches_are_the_only_difference_from_the_workshop_image():
    clean, image = build.EXE.read_bytes(), bytearray(WORKSHOP.read_bytes())
    for patch in json.loads(build.MANIFEST.read_text(encoding="utf-8"))["reverted_patches"]:
        rva, size = int(patch["rva"], 16), patch["size"]
        assert image[rva:rva + size].hex() == patch["cracked"], patch["function"]
        image[rva:rva + size] = bytes.fromhex(patch["original"])
    checksum = int.from_bytes(clean[0x3C:0x40], "little") + 0x58
    assert image[:checksum] + image[checksum + 4:] == clean[:checksum] + clean[checksum + 4:]


def test_safedisc_bodies_are_retired_and_real_code_is_not():
    stripped, rebuilt, notify_launcher = 0x0006CDF0, 0x0006EF90 + 0x40, 0x001020D0
    assert eligibility.retired(stripped, {}) and eligibility.retired(rebuilt, {})
    assert not eligibility.retired(notify_launcher, {})
