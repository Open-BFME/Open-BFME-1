#!/usr/bin/env python3
"""Build the learned-horde-AI proof of concept as a standalone BFME executable."""

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))

import modbuild  # noqa: E402


FEATURE = ROOT / "mods/features/057-learned-horde-ai"
SOURCE = FEATURE / "src/learned_horde_ai.cpp"
TARGET_HORDE_UPDATE = 0x002C4790
# HordeAIUpdate::update begins:
#   push ecx; push ebx; push esi; mov ebx,ecx
# All five bytes are whole position-independent instructions.
EXPECTED_HEAD = bytes.fromhex("5153568bd9")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--baseline", default=modbuild.BASELINE)
    ap.add_argument("-o", "--output", default=ROOT / "build/learned-horde-ai.exe")
    args = ap.parse_args()

    pe = modbuild.PE(args.baseline)
    pe.add_cave(0x10000)
    modbuild.reserve_mod_bus(pe)

    if pe.read(TARGET_HORDE_UPDATE, len(EXPECTED_HEAD)) != EXPECTED_HEAD:
        raise SystemExit(
            f"0x{TARGET_HORDE_UPDATE:08X} is not the expected retail "
            "HordeAIUpdate::update entry"
        )

    info = modbuild.build_feature(
        pe,
        SOURCE,
        "learned_horde_ai_tick",
        ((TARGET_HORDE_UPDATE, "learned_horde_ai_tick", ("ecx",)),),
        probe=False,
    )

    out = Path(args.output)
    out.parent.mkdir(parents=True, exist_ok=True)
    pe.save(out)

    detour = info["detours"][0]
    print(
        f"learned-horde-ai: {info['code_len']} B payload @ "
        f"RVA 0x{info['code_rva']:08X}"
    )
    print(
        f"detour 0x{detour['target']:08X} -> "
        f"{detour['entry']} (shim RVA 0x{detour['code_rva']:08X})"
    )
    print(f"wrote {out}")


if __name__ == "__main__":
    main()
