#!/usr/bin/env python3
"""Extend the verified Astra executable with the unit interpolation arm.

The existing Astra image is intentionally the input and a new appended PE
section is used for this experiment.  No retail executable or existing Astra
artifact is overwritten.
"""
from __future__ import annotations

import argparse
import hashlib
import struct
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import modbuild  # noqa: E402
from cave import PE  # noqa: E402


IMAGE_BASE = 0x00400000
DRAW_VIEWS_RVA = 0x0040DA30
DRAW_VIEWS_PREFIX = bytes.fromhex("56 8b 71 18 85 f6")
ASTRA_SECTION = ".bfmemod"
INTERP_SECTION = ".bfmeip"
INTERP_CAVE_SIZE = 0x1A0000  # 8192-record pool x2 matrices history + index
SOURCE = ROOT / "mods/features/049-unitinterp/src/unitinterp.cpp"
ASTRA = Path(r"D:\BFME1\lotrbfme-astra.exe")
OUTPUT = Path(r"D:\BFME1\lotrbfme-interp.exe")


def expect(pe: PE, rva: int, expected: bytes, label: str) -> None:
    actual = pe.read(rva, len(expected))
    if actual != expected:
        raise SystemExit(
            f"{label} at RVA 0x{rva:08X}: expected {expected.hex(' ')}, "
            f"found {actual.hex(' ')}")


def link_payload_blob(pe: PE, source: Path) -> tuple[bytes, dict[str, int]]:
    with tempfile.TemporaryDirectory() as tmp:
        tmp_path = Path(tmp)
        obj = modbuild.compile_payload(
            source, tmp_path / "unitinterp.obj", probe=False)
        image = modbuild.link_payload(
            obj, "unitinterp_begin", tmp_path / "unitinterp.exe")
        at = pe.image_base + pe.next_rva()
        return modbuild.blob_at(image, at)


def p32(value: int) -> bytes:
    return struct.pack("<I", value & 0xFFFFFFFF)


def patch(source: Path, output: Path, payload_source: Path) -> dict[str, object]:
    if source.resolve() in (Path(r"D:\BFME1\lotrbfme.exe").resolve(),
                            output.resolve()):
        raise SystemExit("refusing an original retail path as interpolation input")
    if output.resolve() in (Path(r"D:\BFME1\lotrbfme.exe").resolve(),
                            Path(r"D:\BFME1\lotrbfme-astra.exe").resolve()):
        raise SystemExit("refusing to overwrite retail or the verified Astra image")
    if not source.exists():
        raise SystemExit(f"missing Astra input: {source}")
    if not payload_source.exists():
        raise SystemExit(f"missing payload source: {payload_source}")

    pe = PE(source)
    if pe.image_base != IMAGE_BASE:
        raise SystemExit(f"unexpected image base 0x{pe.image_base:08X}")
    if not any(s["name"] == ASTRA_SECTION for s in pe.sections()):
        raise SystemExit(f"input lacks the verified {ASTRA_SECTION} section")
    expect(pe, DRAW_VIEWS_RVA, DRAW_VIEWS_PREFIX, "Display::drawViews entry")

    before_hash = hashlib.sha256(bytes(pe.data)).hexdigest()
    before_size = len(pe.data)
    old_sections = len(pe.sections())
    cave_rva = pe.add_cave(INTERP_CAVE_SIZE, name=INTERP_SECTION)

    blob, entries = link_payload_blob(pe, payload_source)
    payload_rva = pe.alloc(blob)
    if pe.image_base + payload_rva != pe.image_base + cave_rva:
        raise SystemExit("payload allocation moved unexpectedly")

    # The main detour enters Display::drawViews, applies transforms, pushes a
    # synthetic return address, and then runs the original entire function.
    # drawViews' own ret consumes the synthetic address, leaving the caller's
    # original return address for this restore stub's ret.
    restore_start = pe.next_rva()
    restore_stub = pe.shim(
        entries["unitinterp_restore"], pe.image_base + restore_start,
        args=()) + b"\xC3"
    restore_rva = pe.alloc(restore_stub)

    main_start = pe.next_rva()
    apply_shim = pe.shim(
        entries["unitinterp_begin"], pe.image_base + main_start,
        args=("ecx",))
    main_payload = apply_shim + b"\x68" + p32(pe.image_base + restore_rva)
    main_rva = pe.detour(DRAW_VIEWS_RVA, payload=main_payload)

    if main_rva != main_start:
        raise SystemExit("drawViews wrapper allocation moved unexpectedly")
    pe.save(output)
    return {
        "before_hash": before_hash,
        "after_hash": hashlib.sha256(bytes(pe.data)).hexdigest(),
        "before_size": before_size,
        "after_size": len(pe.data),
        "old_sections": old_sections,
        "new_sections": len(pe.sections()),
        "interp_section_rva": cave_rva,
        "interp_section_size": pe.cave_size,
        "payload_rva": payload_rva,
        "payload_size": len(blob),
        "restore_rva": restore_rva,
        "restore_size": len(restore_stub),
        "draw_wrapper_rva": main_rva,
        "draw_wrapper_size": len(main_payload),
        "draw_views_detour": pe.read(DRAW_VIEWS_RVA, 6).hex(" "),
        "output": str(output),
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--astra", type=Path, default=ASTRA)
    ap.add_argument("--output", type=Path, default=OUTPUT)
    ap.add_argument("--source", type=Path, default=SOURCE)
    args = ap.parse_args()
    info = patch(args.astra, args.output, args.source)
    for key, value in info.items():
        print(f"{key}={value}")
    print(f"wrote {info['output']} ({info['after_size']:,} bytes)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
