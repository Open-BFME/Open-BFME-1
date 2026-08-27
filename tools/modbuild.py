#!/usr/bin/env python3
"""Build the mods: stack every feature into one patched executable.

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
OUT = ROOT / "build/mods/lotrbfme.exe"
DIST = ROOT / "mods/dist"

TARGET_UPDATE = 0x0035F920    # VictoryConditions::update
# ConnectionManager::sendPlayerLeaveCommands -- the leave entry an in-game
# exit actually takes. Network::quitGame 0x006822E0 is the one the ledger
# points at and a four-client probe recorded it firing zero times.
TARGET_SENDLEAVE = 0x00665C10

# 030-netlatprobe. Every one of these is hooked at its ENTRY, which is what lets
# the shim lift the function's own first argument off the stack ("stack:0"): a
# thiscall's `this` arrives in ecx, but everything it was called WITH is on the
# stack, and for four of these five the argument IS the measurement.
TARGET_APPENDMESSAGE = 0x0008A4E0   # GameMessageList::appendMessage(msg)
TARGET_SENDLOCAL = 0x00664740       # ConnectionManager::sendLocalCommand(msg)
TARGET_RELAYCOMMAND = 0x00663100    # ConnectionManager::relayCommand(ref)
TARGET_FRAMERELAY = 0x00682A90      # Network::relayCommandsToCommandList(frame)
TARGET_SENDFRAMEINFO = 0x00665D10   # ConnectionManager::sendFrameInfo()
TARGET_ADVANCECOUNT = 0x00681F70   # BFMENativeNetwork::getFrameAdvanceCount()
# Connection::update, immediately before the engine decides whether to discard a
# just-resent command for good. eax = execution frame, esi = NetCommandRef,
# edi = Connection. Displaces `mov ecx,ds:0x12ED5C8` (6 bytes).
TARGET_DISCARD = 0x006620A4
TARGET_FRAMEDRIVER = 0x0006BAE0   # the per-iteration frame driver, vtable slot +0x7C
TARGET_LOOPBODY    = 0x0006BC2B   # GameEngine::execute's once-per-iteration call

# Connection::init's `mov dword ptr [edx+0x1C], 2000` -- m_retryTime, the wall
# time an unacked command waits before it is put in a packet again. The imm32
# starts three bytes into the instruction at RVA 0x006623DB.
TARGET_RETRYTIME = 0x006623DE
RETRY_WAS = 2000
# Pre-registered for the spike. Under 40 ms/1% loss the guest's stall histogram
# piles up at exactly 2.0 s -- this timer, once per lost packet -- and loses
# 10-17% of a match to it. 400 ms is ~2x a realistic ladder round trip, so an
# acked command still never resends; the 250 ms arm is this constant, changed,
# rebuilt to its own -o path.
RETRY_MS = 400

# 031-earlysend. The client half's tail, immediately before the engine's own
# liteupdate(FALSE) at 0x0006BA53 -- so a command queued by the payload is
# flushed to the wire by the next instruction of the retail path. The six bytes
# displaced are the `mov ecx,[TheNetwork]` that liteupdate is called through.
TARGET_CLIENTTAIL = 0x0006BA44

# 040-horplus. These are post-operation hook sites, so the retail W3DView
# methods run first and the payload only adjusts the resulting view plane.
# setHeight continues with ESI as the W3DView at 0x0073DC3E; setWidth leaves
# ESI as the W3DView at 0x0073DDF8; and BFME's camera-transform path reaches
# 0x00742609 with ESI as the W3DView after its final CameraClass transform.
TARGET_HORPLUS_HEIGHT_TAIL = 0x0073DC3E
TARGET_HORPLUS_WIDTH_TAIL = 0x0073DDF8
TARGET_HORPLUS_CAMERA_TAIL = 0x00742609
TARGET_HORPLUS_DIRECT_TRANSFORM_TAIL = 0x00931304

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
    "__ftol2": "float-to-integer conversion; keep payload conversions integer-only",
    "__fltused": "floating point marker; provide only a local CRT-free definition",
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
    defined = {s["name"] for s in symbols if s["section"] > 0 and s["name"]}
    unresolved = {s["name"] for s in symbols
                  if s["section"] == 0 and s["value"] == 0 and s["name"]}
    # MSVC emits a second undefined __fltused record when a /Zl translation
    # unit provides the conventional local _fltused marker. The linker resolves
    # that marker from this same object; do not turn this one compiler marker
    # into a general exemption for unresolved payload references.
    if "__fltused" in defined:
        unresolved.discard("__fltused")
    return sorted(unresolved)


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
    # directory is inside the blob. Left alone it makes mods/dist a different
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


def build_feature(pe, source, entry, hooks, probe=False):
    """Compile one feature's .cpp, lay it in the cave, and hook its entries.

    `hooks` is (target rva, exported name, shim arguments) per detour."""
    with tempfile.TemporaryDirectory() as tmp:
        stem = Path(source).stem
        obj = compile_payload(source, Path(tmp) / f"{stem}.obj", probe=probe)
        image = link_payload(obj, entry, Path(tmp) / f"{stem}.exe")
        # The cave address is only knowable once every earlier blob is down, and
        # the blob has to be relocated to it before it is written.
        at = pe.image_base + pe.next_rva()
        blob, entries = blob_at(image, at)

    rva = pe.alloc(blob)
    if pe.image_base + rva != at:
        raise SystemExit(f"the payload was relocated to 0x{at:08X} but placed at "
                         f"0x{pe.image_base + rva:08X}")

    detours = []
    for target, name, args in hooks:
        if name not in entries:
            raise SystemExit(f"{Path(source).name} exports {sorted(entries)}, not {name}")
        start = pe.detour_call(target, entries[name], args=args)
        detours.append(dict(target=target, entry=name, code_rva=start,
                            code_len=pe.cave_rva + pe.cave_used - start))
    return dict(code_rva=rva, code_len=len(blob), detours=detours)


def build_gameresult(pe, feature_dir, probe=False):
    return build_feature(pe, feature_dir / "src/gameresult.cpp", "gameresult_update", (
        (TARGET_UPDATE, "gameresult_update", ("ecx",)),
        (TARGET_SENDLEAVE, "gameresult_leave", ("ecx",)),
    ), probe=probe)


def build_netlatprobe(pe, feature_dir, probe=False):
    # netlat_admit is NOT in this list, and its absence is the point.
    #
    # It answered the admission question -- the guest polls the frame driver once
    # per logic frame, consumes permission in 0.2 ms, and its one-frame lag is
    # the protocol's correctness margin -- and that question is closed. What it
    # still does is write a flushed line per driver call, and a guest polls the
    # driver MORE when it is frozen. So its cost scales with how much an arm
    # freezes: the arm that freezes more pays more to be watched freezing. That
    # is a feedback loop, not an offset, and it silently flatters any fix that
    # reduces freezing.
    #
    # The entry point is kept in the payload. Re-add this line to ask an
    # admission question again, and do not have it installed while measuring
    # freezes.
    return build_feature(pe, feature_dir / "src/netlatprobe.cpp", "netlat_frame", (
        (TARGET_APPENDMESSAGE, "netlat_input", ("ecx", "stack:0")),
        (TARGET_SENDLOCAL, "netlat_send", ("ecx", "stack:0")),
        (TARGET_RELAYCOMMAND, "netlat_relay", ("ecx", "stack:0")),
        (TARGET_FRAMERELAY, "netlat_frame", ("ecx", "stack:0")),
        (TARGET_SENDFRAMEINFO, "netlat_ceiling", ("ecx",)),
        (TARGET_LOOPBODY, "netlat_loop", ("ecx",)),
        (TARGET_FRAMEDRIVER, "netlat_driver", ("ecx",)),
        (TARGET_DISCARD, "netlat_discard", ("eax", "esi", "edi")),
    ), probe=probe)


def build_framedrain(pe, feature_dir, probe=False):
    return build_feature(pe, feature_dir / "src/framedrain.cpp", "framedrain", (
        (TARGET_FRAMEDRIVER, "framedrain", ("ecx",)),
    ), probe=probe)


def build_retrytime(pe, feature_dir, probe=False):
    """No payload and no detour: one imm32, rewritten in place.

    A code cave would be the wrong shape here. The value is written once, by a
    constructor, into each Connection -- there is no behaviour to add, only a
    constant to change, and a detour would be five bytes of trampoline standing
    in for four bytes of data."""
    (feature_dir / "src").mkdir(parents=True, exist_ok=True)
    before = struct.unpack("<I", pe.read(TARGET_RETRYTIME, 4))[0]
    if before != RETRY_WAS:
        raise SystemExit(
            f"0x{TARGET_RETRYTIME:08X} holds {before}, not {RETRY_WAS}. This is not "
            f"the retail Connection::init, so the poke would land somewhere unknown.")
    pe.write(TARGET_RETRYTIME, struct.pack("<I", RETRY_MS))
    return dict(code_rva=0, code_len=0, detours=[],
                pokes=[dict(rva=TARGET_RETRYTIME, was=before, now=RETRY_MS)])


def build_earlysend(pe, feature_dir, probe=False):
    return build_feature(pe, feature_dir / "src/earlysend.cpp", "earlysend", (
        (TARGET_CLIENTTAIL, "earlysend", ("ecx",)),
    ), probe=probe)


def build_horplus(pe, feature_dir, probe=False):
    return build_feature(pe, feature_dir / "src/horplus.cpp", "horplus_set_width_tail", (
        (TARGET_HORPLUS_HEIGHT_TAIL, "horplus_set_height_tail", ("esi",)),
        (TARGET_HORPLUS_WIDTH_TAIL, "horplus_set_width_tail", ("esi",)),
        (TARGET_HORPLUS_CAMERA_TAIL, "horplus_set_camera_tail", ("esi",)),
        (TARGET_HORPLUS_DIRECT_TRANSFORM_TAIL, "horplus_set_direct_transform_tail", ("esi",)),
    ), probe=probe)


FEATURES = {"020-gameresult": build_gameresult,
            # Promoted once its spike came back green: twelve rig matches, no
            # retail match overlapping any fixed one, and the logic rate
            # unchanged at 5.000/s. docs/net-fixes.md has the numbers.
            "031-earlysend": build_earlysend,
            # Promoted 2026-08-29 on the condition its UNSHIPPED note set --
            # "green at 150ms+ round trip". Four stress matches at 300ms RTT,
            # both timer values, zero desync and no stuck seat on either seat;
            # duplicate delivery measured at 1.0-2.5% in EVERY arm including
            # retail, and provably absorbed (a tolerated duplicate would wedge a
            # seat forever, and no match wedged). At 150ms/3% it clears retail's
            # whole range: gap p99 420/419/420 vs 1740/1769/1800, worst stall
            # 805/806/800 vs 2031/3724/3719, game time lost ~0% vs 3-11%. On
            # real build orders, placement goes 0.7-2.6s unpredictable to
            # 0.43-0.65s. docs/net-fixes.md has the numbers.
            "033-retrytime": build_retrytime}
# Selected only by name, and refused by --dist. mods/dist is the artifact
# every ladder player runs: an instrument writes tens of lines a second, and a
# candidate has not earned a place in it until the spike measuring it is green.
# Promote one into FEATURES when it has.
UNSHIPPED = {
    "030-netlatprobe": (build_netlatprobe, "an instrument: it writes tens of lines a second"),
    "034-framedrain": (build_framedrain,
                       "REFUTED: it desyncs. the desync flag raised from logic frame 102 on "
                       "both seats, match dead at 127, against zero in every other arm. "
                       "See the header of its source before reviving it"),
    "040-horplus": (build_horplus, "a development camera modernization; build it to its own path"),
}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--baseline", default=BASELINE)
    ap.add_argument("-o", "--output", default=OUT)
    ap.add_argument("--cave-size", type=lambda v: int(v, 0), default=0x10000)
    ap.add_argument("--dist", action="store_true",
                    help="also write mods/dist/ (the tracked, shippable build)")
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
    if a.dist and a.only:
        # --only is for bisection, and its own help says never for shipping --
        # but nothing enforced that, so `--only X --dist` quietly rewrote the
        # shipped artifact with a build carrying ONLY X. It happened: dist went
        # to a one-feature build with gameresult and earlysend absent, and was
        # only caught because someone checked the hash. mods/dist is always the
        # whole of FEATURES or it is not mods/dist.
        raise SystemExit(
            "refusing --dist with --only: mods/dist is the artifact every ladder "
            "player runs and must carry all of FEATURES "
            f"({', '.join(sorted(FEATURES))}). --only builds a subset for "
            "bisection; give it its own path with -o.")
    if a.dist:
        for name in names:
            if name in UNSHIPPED:
                raise SystemExit(
                    f"refusing --dist with {name}: {UNSHIPPED[name][1]}. mods/dist "
                    f"is what every ladder player runs. Build it to its own path with "
                    f"-o instead, and promote it into FEATURES when it has earned it.")
    for name in names:
        fn = FEATURES.get(name) or (UNSHIPPED[name][0] if name in UNSHIPPED else None)
        if fn is None:
            raise SystemExit(f"unknown feature: {name}")
        info = fn(pe, ROOT / "mods/features" / name, probe=a.probe)
        if info["code_len"]:
            print(f"  {name}: {info['code_len']} B payload @ RVA 0x{info['code_rva']:08X}")
        for poke in info.get("pokes", ()):
            if poke["rva"] in claimed:
                raise SystemExit(f"address conflict: {name} and {claimed[poke['rva']]} "
                                 f"both claim 0x{poke['rva']:08X}")
            claimed[poke["rva"]] = name
            print(f"  {name}: poke 0x{poke['rva']:08X} {poke['was']} -> {poke['now']}")
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
            "id": "bfme1.mods",
            "name": "BFME1 mod build",
            "note": "Retail lotrbfme.exe with a .bfmemod code cave appended and "
                    "the mods detoured into it. Rebuild with "
                    "python3 tools/modbuild.py --dist",
            "baseline": {
                "path": str(Path(a.baseline).relative_to(ROOT)),
                "sha256": hashlib.sha256(base).hexdigest(),
                "size": len(base),
            },
            "output": {
                "path": "mods/dist/lotrbfme.exe",
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
