#!/usr/bin/env python3
"""Build the overlay: stack every feature into one patched executable.

Features always stack — there is no mix-and-match — so this produces exactly
one artifact. Two features claiming the same address is a hard error, never a
last-writer-wins merge.
"""
import argparse
import hashlib
import json
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from cave import PE, CaveError  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
OUT = ROOT / "build/overlay/lotrbfme.exe"
DIST = ROOT / "overlay/dist"

TARGET_UPDATE = 0x0035F920  # VictoryConditions::update


def yasm(src, defines, out):
    cmd = ["yasm", "-f", "bin", "-o", str(out)]
    for k, v in defines.items():
        cmd += ["-D", f"{k}={v}"]
    cmd.append(str(src))
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        raise SystemExit(f"yasm failed:\n{r.stderr}")
    return Path(out).read_bytes()


def cstr(s):
    return s.encode() + b"\0"


def build_gameresult(pe, feature_dir, probe=False):
    """Lay out the feature's data, assemble its code against that layout,
    then detour VictoryConditions::update through it."""
    strings = [
        ("FMT_START",  '{"ev":"start","t":%d,"slot":%d}\n'),
        ("FMT_END",    '{"ev":"end","t":%d,"slot":%d,"frame":%d,"result":"%s",'
                       '"observer":%d,"desync":%d,"slots":['),
        ("FMT_SLOT",   '{"leave":%d,"leaveFrame":%d,"defeatFrame":%d,"victoryFrame":%d,'
                       '"slotIndex":%d,"namePtr":%d,"name":"%s"}'),
        ("COMMA",      ','),
        ("MID",        '],"players":['),
        ("TAIL",       ']}\n'),
        ("FMT_PLAYER", '{"player":%d,"defeated":%d,"teamWon":%d}'),
        ("ENVNAME",    'BFME_RESULT_PATH'),
        ("DEFPATH",    'GameResult.jsonl'),
        ("MODE",       'a'),
        ("VICTORY",    'victory'),
        ("DEFEAT",     'defeat'),
        ("UNDECIDED",  'undecided'),
        ("EMPTY",      ''),
    ]
    SCRATCH = 20                      # started, ended, result, file, nameptr
    pool, offsets = bytearray(), {}
    for name, text in strings:
        offsets["OFF_" + name] = len(pool)
        pool += text.encode() + b"\0"

    data_rva = pe.alloc(bytes(bytearray(SCRATCH) + pool))
    defines = {
        "DATA_VA": hex(pe.image_base + data_rva),
        "CODE_VA": hex(pe.image_base + pe.next_rva()),
        **offsets,
    }
    if probe:
        defines["PROBE"] = 1
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as t:
        code = yasm(feature_dir / "src/payload.asm", defines, t.name)

    cave_at = pe.detour(TARGET_UPDATE, payload=code)
    return dict(data_rva=data_rva, code_rva=cave_at, code_len=len(code),
                data_len=SCRATCH + len(pool), target=TARGET_UPDATE)


FEATURES = {"020-gameresult": build_gameresult}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--baseline", default=BASELINE)
    ap.add_argument("-o", "--output", default=OUT)
    ap.add_argument("--cave-size", type=lambda v: int(v, 0), default=0x10000)
    ap.add_argument("--dist", action="store_true",
                    help="also write overlay/dist/ (the tracked, shippable build)")
    ap.add_argument("--probe", action="store_true",
                    help="drop end-of-game gates; diagnostic builds only")
    ap.add_argument("--only", action="append", default=[],
                    help="build a subset — for bisection only, never for shipping")
    a = ap.parse_args()

    pe = PE(a.baseline)
    pe.add_cave(a.cave_size)
    print(f"cave .bfmemod @ RVA 0x{pe.cave_rva:08X} size 0x{pe.cave_size:X}")

    claimed = {}
    names = a.only or list(FEATURES)
    for name in names:
        fn = FEATURES.get(name)
        if fn is None:
            raise SystemExit(f"unknown feature: {name}")
        info = fn(pe, ROOT / "overlay/features" / name, probe=a.probe)
        t = info["target"]
        if t in claimed:
            raise SystemExit(
                f"address conflict: {name} and {claimed[t]} both claim 0x{t:08X}")
        claimed[t] = name
        print(f"  {name}: detour 0x{t:08X} -> cave 0x{info['code_rva']:08X} "
              f"({info['code_len']} B code, {info['data_len']} B data)")

    out = Path(a.output)
    out.parent.mkdir(parents=True, exist_ok=True)
    pe.save(out)
    print(f"wrote {out} ({len(pe.data):,} bytes, cave used {pe.cave_used}/{pe.cave_size})")

    if a.dist:
        DIST.mkdir(parents=True, exist_ok=True)
        exe = DIST / "lotrbfme.exe"
        exe.write_bytes(out.read_bytes())
        base = Path(a.baseline).read_bytes()
        manifest = {
            "schema_version": 1,
            "id": "bfme1.overlay",
            "name": "BFME1 overlay build",
            "note": "Retail lotrbfme.exe with a .bfmemod code cave appended and "
                    "the overlay features detoured into it. Rebuild with "
                    "python3 tools/modbuild.py --dist",
            "baseline": {
                "path": str(Path(a.baseline).relative_to(ROOT)),
                "sha256": hashlib.sha256(base).hexdigest(),
                "size": len(base),
            },
            "output": {
                "path": "overlay/dist/lotrbfme.exe",
                "sha256": hashlib.sha256(exe.read_bytes()).hexdigest(),
                "size": exe.stat().st_size,
            },
            "cave": {
                "section": ".bfmemod",
                "rva": f"0x{pe.cave_rva:08X}",
                "size": f"0x{pe.cave_size:X}",
                "used": pe.cave_used,
            },
            "features": [
                {"name": n, "target_rva": f"0x{t:08X}"} for t, n in sorted(claimed.items())
            ],
        }
        (DIST / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
        print(f"dist: {exe} + manifest.json")


if __name__ == "__main__":
    sys.exit(main())
