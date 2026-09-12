#!/usr/bin/env python3
"""Extend the verified Astra executable with the continuous-ratio arm (050).

Like astra_unitinterp_patch.py: the Astra image is the input, a new appended
PE section carries the payload, and neither retail nor the Astra artifact is
overwritten.  One detour at GameEngine::_bfme_updateClientSubsystems entry.
"""
from __future__ import annotations

import argparse
import hashlib
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import modbuild  # noqa: E402
from cave import PE  # noqa: E402

IMAGE_BASE = 0x00400000
CLIENT_UPDATE_RVA = 0x0006B910
CLIENT_UPDATE_PREFIX = bytes.fromhex("6a ff 68 d8 2a ff 00")
ASTRA_SECTION = ".bfmemod"
SECTION = ".bfmerc"
CAVE_SIZE = 0x4000
SOURCE = ROOT / "mods/features/050-ratiocont/src/ratiocont.cpp"
ASTRA = Path(r"D:\BFME1\lotrbfme-astra.exe")
OUTPUT = Path(r"D:\BFME1\lotrbfme-interp3.exe")


def expect(pe: PE, rva: int, expected: bytes, label: str) -> None:
    actual = pe.read(rva, len(expected))
    if actual != expected:
        raise SystemExit(f"{label} at RVA 0x{rva:08X}: expected {expected.hex(' ')}, "
                         f"found {actual.hex(' ')}")


def patch(source: Path, output: Path, payload_source: Path,
          defines: tuple[str, ...] = ()) -> dict[str, object]:
    protected = {Path(r"D:\BFME1\lotrbfme.exe").resolve(),
                 Path(r"D:\BFME1\lotrbfme-astra.exe").resolve()}
    if output.resolve() in protected:
        raise SystemExit("refusing to overwrite retail or the verified Astra image")
    if not source.exists():
        raise SystemExit(f"missing Astra input: {source}")

    pe = PE(source)
    if pe.image_base != IMAGE_BASE:
        raise SystemExit(f"unexpected image base 0x{pe.image_base:08X}")
    if not any(s["name"] == ASTRA_SECTION for s in pe.sections()):
        raise SystemExit(f"input lacks the verified {ASTRA_SECTION} section")
    expect(pe, CLIENT_UPDATE_RVA, CLIENT_UPDATE_PREFIX, "client-subsystems entry")

    before_hash = hashlib.sha256(bytes(pe.data)).hexdigest()
    cave_rva = pe.add_cave(CAVE_SIZE, name=SECTION)

    with tempfile.TemporaryDirectory() as tmp:
        tmp_path = Path(tmp)
        obj = modbuild.compile_payload(payload_source, tmp_path / "ratiocont.obj",
                                       probe=False, defines=defines)
        image = modbuild.link_payload(obj, "ratiocont_client", tmp_path / "ratiocont.exe")
        blob, entries = modbuild.blob_at(image, pe.image_base + pe.next_rva())
    payload_rva = pe.alloc(blob)
    if payload_rva != cave_rva:
        raise SystemExit("payload allocation moved unexpectedly")

    hook_rva = pe.detour_call(CLIENT_UPDATE_RVA, entries["ratiocont_client"], args=("ecx",))
    pe.save(output)
    return {
        "before_hash": before_hash,
        "after_hash": hashlib.sha256(bytes(pe.data)).hexdigest(),
        "after_size": len(pe.data),
        "payload_rva": payload_rva,
        "payload_size": len(blob),
        "hook_rva": hook_rva,
        "client_update_detour": pe.read(CLIENT_UPDATE_RVA, 8).hex(" "),
        "output": str(output),
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--astra", type=Path, default=ASTRA)
    ap.add_argument("--output", type=Path, default=OUTPUT)
    ap.add_argument("--source", type=Path, default=SOURCE)
    ap.add_argument("--no-anim", action="store_true",
                    help="leave [0x012BB1CC] alone (isolates the ratio change)")
    args = ap.parse_args()
    info = patch(args.astra, args.output, args.source,
                 defines=("NO_ANIM_STEER",) if args.no_anim else ())
    for key, value in info.items():
        print(f"{key}={value}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
