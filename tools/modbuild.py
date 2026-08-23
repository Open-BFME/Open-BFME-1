#!/usr/bin/env python3
"""Build the overlay: stack every feature into one patched executable.

Features always stack — there is no mix-and-match — so this produces exactly
one artifact. Two features claiming the same address is a hard error, never a
last-writer-wins merge.

A feature is one .cpp file. It is compiled and linked with the game's own
toolchain (MSVC 7.1, through tools/build.py's wine machinery), laid into the
cave, and reached through the register-preserving shim tools/cave.py generates.
There is no loader and no CRT behind it, so the link is deliberately naked:
/NODEFAULTLIB, an explicit entry point, and a build that fails on any unresolved
external rather than pulling one in.
"""
import argparse
import hashlib
import json
import os
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as toolchain  # noqa: E402  — vc71_root/wine_path/compiler_environment
from cave import PE  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
OUT = ROOT / "build/overlay/lotrbfme.exe"
DIST = ROOT / "overlay/dist"

TARGET_UPDATE = 0x0035F920    # VictoryConditions::update
# ConnectionManager::sendPlayerLeaveCommands -- the leave entry an in-game
# exit actually takes. Network::quitGame 0x006822E0 is the one the ledger
# points at and a four-client probe recorded it firing zero times.
TARGET_SENDLEAVE = 0x00665C10

# No CRT startup, no exceptions, no RTTI, no runtime library at all. /GS is off
# by default in 7.1 and it rejects /GS-, so there is nothing to turn off there.
# Warnings are errors: this build discards compiler output on success, so a
# warning nobody is shown is a warning nobody acts on.
CL_FLAGS = ["-nologo", "-c", "-O1", "-GR-", "-EHs-c-", "-Zl", "-W4", "-WX"]
# link.exe refuses a /BASE that is not 64K-aligned and the cave never lands on
# one, so the blob is linked here and moved with its own base relocations. This
# address never reaches the game.
LINK_BASE = 0x10000000
LINK_FLAGS = [
    "/NOLOGO", "/NODEFAULTLIB", "/FIXED:NO", "/ALIGN:16", f"/BASE:0x{LINK_BASE:X}",
    "/SUBSYSTEM:CONSOLE",
    # 4108: /ALIGN without /DRIVER, "image may not run" -- this image never
    # runs, it is copied into a section of another one. 4216: the entry point
    # is also exported, which is exactly what lets both payloads be found.
    "/IGNORE:4108,4216",
]

# Helpers the compiler can emit a call to without the source ever naming one.
# Each is a real behaviour of C++ that has no runtime here to land on.
CRT_HELPERS = {
    "__chkstk": "a stack frame over a page; keep locals small or make them static",
    "_memset": "zero-initialising an aggregate; assign the fields instead",
    "_memcpy": "copying a struct or an array; copy the fields instead",
    "__allmul": "64-bit multiplication; the payload has no 64-bit arithmetic",
    "__alldiv": "64-bit division; the payload has no 64-bit arithmetic",
    "__allrem": "64-bit remainder; the payload has no 64-bit arithmetic",
    "__aullshr": "64-bit shift; the payload has no 64-bit arithmetic",
    "__ftol2": "float-to-integer conversion; the payload has no floating point",
    "__fltused": "floating point anywhere in the TU; the payload has none",
}


def _msvc(name):
    """The command prefix that runs one MSVC 7.1 binary on this host."""
    command = [str(toolchain.vc71_root() / "Vc7" / "bin" / name)]
    if os.name != "nt":
        wine = shutil.which("wine")
        if wine is None:
            raise SystemExit("wine not found. Install Wine to run MSVC 7.1 on this host.")
        command.insert(0, wine)
    return command


def _run(command, what):
    env = toolchain.compiler_environment(toolchain.vc71_root())
    result = subprocess.run(command, cwd=ROOT, env=env, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)
    if result.returncode != 0:
        raise SystemExit(f"{what} failed:\n{result.stdout}")


def undefined_externals(obj):
    """Every external symbol the object leaves for someone else to provide.

    With no CRT and no import library there IS no someone else, so this must be
    empty. The link fails on one anyway, but only as `LNK2001 __chkstk`, which
    says nothing about which line of C++ asked for it."""
    symbols = toolchain.read_object_symbols(Path(obj).read_bytes())
    return sorted({s["name"] for s in symbols
                   if s["section"] == 0 and s["value"] == 0 and s["name"]})


def compile_payload(source, obj, probe=False):
    command = _msvc("cl.exe") + CL_FLAGS
    if probe:
        command.append("-DPROBE")
    command += [f"-Fo{toolchain.wine_path(obj)}", toolchain.wine_path(source)]
    _run(command, f"compiling {Path(source).name}")

    missing = undefined_externals(obj)
    if missing:
        detail = "".join(f"\n  {name}: {CRT_HELPERS.get(name, 'not provided by anything here')}"
                         for name in missing)
        raise SystemExit(
            f"{Path(source).name} needs {len(missing)} symbol(s) nothing can resolve — "
            f"there is no CRT and no loader behind this code:{detail}")
    return obj


def link_payload(obj, entry, image):
    _run(_msvc("link.exe") + LINK_FLAGS + [
        f"/ENTRY:{entry}",
        f"/IMPLIB:{toolchain.wine_path(Path(image).with_suffix('.lib'))}",
        f"/OUT:{toolchain.wine_path(image)}",
        toolchain.wine_path(obj),
    ], f"linking {Path(obj).name}")
    return image


def _export_dir(image):
    rva = struct.unpack_from("<I", image.data, image.opt + 96)[0]
    if not rva:
        raise SystemExit("the linked payload exports nothing, so no hook can reach it")
    return image.rva_to_off(rva)


def _exports(image):
    """Exported name -> RVA. This is how both entry points are found: /ENTRY
    names only one, and a payload is a set of hooks, not a program."""
    table = _export_dir(image)
    count, functions, names, ordinals = struct.unpack_from("<IIII", image.data, table + 24)
    out = {}
    for i in range(count):
        name_rva = struct.unpack_from("<I", image.data, image.rva_to_off(names) + 4 * i)[0]
        start = image.rva_to_off(name_rva)
        name = image.data[start:image.data.index(b"\0", start)].decode("ascii")
        index = struct.unpack_from("<H", image.data, image.rva_to_off(ordinals) + 2 * i)[0]
        out[name] = struct.unpack_from("<I", image.data,
                                       image.rva_to_off(functions) + 4 * index)[0]
    return out


def blob_at(image_path, va):
    """The linked image's sections as one flat blob to place at `va`, plus the
    VA every export ends up at.

    The linker will only base an image at a 64K boundary and the cave is
    nowhere near one, so the blob is moved here instead — by applying the base
    relocations the image carries, exactly as a loader would. Absolute game
    addresses in the payload are immediates, not relocation sites, so they are
    untouched."""
    image = PE(image_path)
    # link.exe stamps the export directory with the current time, and that
    # directory is inside the blob. Left alone it makes overlay/dist a different
    # file on every rebuild, so its recorded sha256 would say the payload
    # changed when nothing did.
    struct.pack_into("<I", image.data, _export_dir(image) + 4, 0)
    kept = [s for s in image.sections() if s["name"] != ".reloc"]
    first = min(s["vaddr"] for s in kept)
    base = va - first
    _rebase(image, base - image.image_base)

    blob = bytearray(max(s["vaddr"] + s["vsize"] for s in kept) - first)
    for s in kept:
        n = min(s["rsize"], s["vsize"])   # .bss has no raw bytes; padding has no virtual ones
        blob[s["vaddr"] - first:s["vaddr"] - first + n] = image.data[s["raddr"]:s["raddr"] + n]
    return bytes(blob), {name: base + rva for name, rva in _exports(image).items()}


def _rebase(image, delta):
    rva, size = struct.unpack_from("<II", image.data, image.opt + 96 + 8 * 5)
    if not rva:
        raise SystemExit("the linked payload carries no base relocations; link with /FIXED:NO")
    table, done = image.rva_to_off(rva), 0
    while done < size:
        page, block = struct.unpack_from("<II", image.data, table + done)
        for entry in range(8, block, 2):
            fixup = struct.unpack_from("<H", image.data, table + done + entry)[0]
            kind, offset = fixup >> 12, fixup & 0xFFF
            if kind == 0:                      # IMAGE_REL_BASED_ABSOLUTE: padding
                continue
            if kind != 3:                      # HIGHLOW is all a 32-bit image emits
                raise SystemExit(f"unhandled base relocation type {kind} at 0x{page + offset:X}")
            site = image.rva_to_off(page + offset)
            value = struct.unpack_from("<I", image.data, site)[0]
            struct.pack_into("<I", image.data, site, (value + delta) & 0xFFFFFFFF)
        done += block


def build_gameresult(pe, feature_dir, probe=False):
    """Compile the feature, lay it in the cave, and hook both of its entries."""
    with tempfile.TemporaryDirectory() as tmp:
        obj = compile_payload(feature_dir / "src/gameresult.cpp", Path(tmp) / "gameresult.obj",
                              probe=probe)
        image = link_payload(obj, "gameresult_update", Path(tmp) / "gameresult.exe")
        # The cave address is only knowable once every earlier blob is down, and
        # the blob has to be relocated to it before it is written.
        at = pe.image_base + pe.next_rva()
        blob, entries = blob_at(image, at)

    rva = pe.alloc(blob)
    if pe.image_base + rva != at:
        raise SystemExit(f"the payload was relocated to 0x{at:08X} but placed at "
                         f"0x{pe.image_base + rva:08X}")

    detours = []
    for target, entry in ((TARGET_UPDATE, "gameresult_update"),
                          (TARGET_SENDLEAVE, "gameresult_leave")):
        if entry not in entries:
            raise SystemExit(f"gameresult.cpp exports {sorted(entries)}, not {entry}")
        start = pe.detour_call(target, entries[entry])
        detours.append(dict(target=target, entry=entry, code_rva=start,
                            code_len=pe.cave_rva + pe.cave_used - start))
    return dict(code_rva=rva, code_len=len(blob), detours=detours)


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
        print(f"  {name}: {info['code_len']} B payload @ RVA 0x{info['code_rva']:08X}")
        for d in info["detours"]:
            t = d["target"]
            if t in claimed:
                raise SystemExit(
                    f"address conflict: {name} and {claimed[t]} both claim 0x{t:08X}")
            claimed[t] = name
            print(f"  {name}: detour 0x{t:08X} -> shim 0x{d['code_rva']:08X} "
                  f"({d['code_len']} B) -> {d['entry']}")

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
