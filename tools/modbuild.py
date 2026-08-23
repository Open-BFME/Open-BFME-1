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

TARGET_UPDATE = 0x0035F920    # VictoryConditions::update
# ConnectionManager::sendPlayerLeaveCommands -- the leave entry an in-game
# exit actually takes. Network::quitGame 0x006822E0 is the one the ledger
# points at and a four-client probe recorded it firing zero times.
TARGET_SENDLEAVE = 0x00665C10


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


def payload(pe, src, defines, target):
    """Assemble one payload against the address it will really be placed at,
    then detour `target` through it.

    detour() allocates payload, relocated prologue and jump-back together, so
    that address is only knowable once every earlier blob is down. Getting it
    wrong is silent while every org is 16-aligned and every jump inside the
    payload is relative, and catastrophic the moment either stops holding --
    yasm's bin output pads a blob whose org is unaligned, which shifts the entry
    point away from the address the trampoline jumps to. So it is checked."""
    defines["CODE_VA"] = hex(pe.image_base + pe.next_rva())
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as t:
        code = yasm(src, defines, t.name)
    at = pe.detour(target, payload=code)
    if pe.image_base + at != int(defines["CODE_VA"], 16):
        raise SystemExit(
            f"{src.name} was assembled at org {defines['CODE_VA']} but placed at "
            f"0x{pe.image_base + at:08X}")
    return dict(target=target, code_rva=at, code_len=len(code))


def build_gameresult(pe, feature_dir, probe=False):
    """Lay out the feature's data, assemble both its payloads against that
    layout, then detour VictoryConditions::update and the leave entry."""
    strings = [
        ("FMT_START",  '{"ev":"start","t":%d,"slot":%d}\n'),
        ("FMT_LEAVE",  '{"ev":"leave","t":%d,"slot":%d,"frame":%d}\n'),
        ("FMT_END",    '{"ev":"end","t":%d,"slot":%d,"frame":%d,"result":"%s",'
                       '"observer":%d,"desync":%d,"slots":['),
        ("FMT_SLOT",   '{"leave":%d,"leaveFrame":%d,"defeatFrame":%d,'
                       '"slotIndex":%d,"namePtr":%d,"name":"%s"}'),
        ("COMMA",      ','),
        ("MID",        '],"players":['),
        ("TAIL",       ']}\n'),
        ("FMT_PLAYER", '{"player":%d,"defeated":%d,"teamWon":%d}'),
        ("ENVNAME",    'BFME_RESULT_PATH'),
        ("APPDATA",    'APPDATA'),
        ("FMT_PATH",   '%s\\My Battle for Middle-earth Files\\GameResult.jsonl'),
        ("MODE",       'a'),
        ("VICTORY",    'victory'),
        ("DEFEAT",     'defeat'),
        ("UNDECIDED",  'undecided'),
        ("EMPTY",      ''),
    ]
    # Both payloads share one scratch block, so its offsets are emitted as
    # defines rather than spelled in each .asm: a number written twice drifts.
    scratch = [("STARTED", 4), ("ENDED", 4), ("RESULT", 4), ("FILE", 4),
               ("NAMEPTR", 4), ("LEFT", 4), ("PATHBUF", 512)]
    offsets, scratch_len = {}, 0
    for name, size in scratch:
        offsets["OFF_D_" + name] = scratch_len
        scratch_len += size
    offsets["OFF_STRINGS"] = scratch_len

    pool = bytearray()
    for name, text in strings:
        offsets["OFF_" + name] = len(pool)
        pool += text.encode() + b"\0"

    data_rva = pe.alloc(bytes(bytearray(scratch_len) + pool))
    defines = {"DATA_VA": hex(pe.image_base + data_rva), **offsets}
    if probe:
        defines["PROBE"] = 1

    src = feature_dir / "src"
    return dict(data_rva=data_rva, data_len=scratch_len + len(pool), detours=[
        payload(pe, src / "payload.asm", defines, TARGET_UPDATE),
        payload(pe, src / "leave.asm", defines, TARGET_SENDLEAVE),
    ])


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
        for d in info["detours"]:
            t = d["target"]
            if t in claimed:
                raise SystemExit(
                    f"address conflict: {name} and {claimed[t]} both claim 0x{t:08X}")
            claimed[t] = name
            print(f"  {name}: detour 0x{t:08X} -> cave 0x{d['code_rva']:08X} "
                  f"({d['code_len']} B code)")
        print(f"  {name}: {info['data_len']} B data @ RVA 0x{info['data_rva']:08X}")

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
