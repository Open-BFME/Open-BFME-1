#!/usr/bin/env python3
"""Link the boot image, start it from a sandbox copy of the install, and classify how far start-up gets.

BFME1 port of Open-BFME-2's tools/boot_smoke.py (same outcomes, lies and guards).

  python3 tools/boot_smoke.py --game-dir SANDBOX [--retail | --unpacked] [--timeout 150]
                              [--base 0x10000000] [--overlay SET] [--guard DIR]...

SANDBOX is a copy of the install (never the install itself: this tool writes
lotrbfme.exe into it). An installed lotrbfme.exe is the game itself, not a
launcher: the workshop-vanilla-1.03 exe (inputs/baselines), i.e. withmorten's
SafeDisc unpack plus the workshop's patches so it runs without the launcher and
its CD check. The image under test is `tools/boot_image.py link` at --base, built
from the byte-matching baseline (retail-1.03-unpacked), which has those patches
reverted. --retail runs the installed exe (the control); --unpacked runs the
baseline itself at 0x400000 (a control for the launcher lie alone). It runs
under a minimal Win32 debugger and is killed at the timeout.

What the debugger changes, at the game's WOW64 loader breakpoint (the image is
relocated and bound, no game code has run):
  appdata lie      SHGetSpecialFolderPathA and ...W are pointed at stubs that
                   answer CSIDL_APPDATA and CSIDL_MYPICTURES with --appdata
                   (default GAME_DIR/../appdata, its profile seeded with a fixed
                   Options.ini); every other folder reaches the real call. Retail
                   calls them at 0x85D2F (A) and 0x85E02 (W) in
                   GlobalData::parseGameDataDefinition, and 0x83E27 (A, pictures).
                   No opt-out: if it cannot be installed the run is killed there
                   (`profile-redirect-failed`), and an --appdata inside the real
                   AppData is refused. The one other folder call, copyReplay's
                   CSIDL_DESKTOPDIRECTORY (0x4E11E5), needs a click in the replay
                   menu; nothing here clicks.
  launcher lie     the baseline manifest's `reverted_patches` (the workshop's
                   launcher and copy-protection patches, withmorten's exe-CRC
                   patches) are written back, at the image's own addresses, so
                   the rebuilt image starts like the installed exe. Bytes are
                   checked to be retail's first; an image that already carries
                   them (--retail) is left alone; anything else is
                   `launcher-lie-failed` and nothing runs.
  version lie      GetVersion/GetVersionExA report XP SP3 (the install runs
                   with the WINXPSP3 layer, keyed to D:'s path; a sandbox path
                   has none). --no-version-lie disables it.
  focus lie        BFME1 stops updating while its window lacks focus (WndProc's
                   WM_ACTIVATEAPP arm, retail 0x5CEFB: `test esi, esi` on wParam,
                   then isWinMainActive and TheGameEngine->setIsActive). One
                   breakpoint on that test, found by its bytes in the image under
                   test, makes a deactivation (esi 0) an activation.
                   --no-focus-lie disables it; --defocus N minimises the window.
  menu probe       a one-shot breakpoint on BfmeAptScreenMainMenu's constructor
                   (retail 0x51F3A0): the Apt main menu screen was built
                   (`menu_built`, seconds after launch).

Outcome (build/boot/smoke.json, or smoke_retail.json; also printed):
  link-error               the link failed or the image check found a difference
  crash-at-<row>           an unhandled (second-chance) exception, or a handled
                           access violation followed by a non-zero exit; mapped
                           back to retail's RVA and the ledger row holding it
  crash-dialog             the game's own Exception window is up
  exit-<code>              the process exited by itself before the timeout
  no-window / no-picture / blank-window   alive at the timeout without a window,
                           with one that renders nothing, or a flat one
  reached-menu             alive at the timeout, the main menu screen was built
                           and the window shows a picture
  loading-screen           alive with a picture but no main menu yet
  profile-redirect-failed  the appdata lie could not be installed (nothing ran)
  launcher-lie-failed      the launcher lie found other bytes (nothing ran)
  profile-changed          the owner's profile or the EA registry keys changed
  guard-violation          a --guard directory changed

Capture is the game window's own client area (PrintWindow), never the screen.
--guard DIR snapshots DIR's file names, sizes and mtimes before and after the
run. The image is scaffolding unless boot_image overlays authored code; no
outcome is progress by itself.

--overlay SET (as `boot_image.py link --overlay`) links authored units in; a crash
names the authored unit it is in. --probes puts a one-shot breakpoint on each
unit's first byte (`authored_executed`). --bisect: when the overlay breaks
start-up, halve it deterministically (with --probes only units that ran are
candidates; each half runs alone) down to the rows that fail by themselves, and
write them to build/boot/boot_queue.json (tools/repair_queue.py serves them as
`boot-crash`). Run every launch under _impl/scratch/game_lock.py or the
equivalent machine-wide lock.
"""
import argparse
import bisect
import collections
import csv
import ctypes
import ctypes.wintypes as wt
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402

OUT = ROOT / "build" / "boot"
GAME_EXE = "lotrbfme.exe"
INSTALLED_EXE = ROOT / "inputs" / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / GAME_EXE
MANIFEST = ROOT / "inputs" / "baselines" / "bfme1" / "retail-1.03-unpacked" / "manifest.json"
MENU_CTOR = 0x51F3A0        # ??0BfmeAptScreenMainMenu@@QAE@PAX@Z: the Apt main menu screen is built
DEBUG_PROCESS = 0x1
DBG_CONTINUE, DBG_NOT_HANDLED = 0x00010002, 0x80010001
EXCEPTION, CREATE_PROCESS, EXIT_PROCESS, LOAD_DLL = 1, 3, 5, 6
BREAKPOINTS = {0x80000003, 0x4000001F}          # int3, WOW64 int3
SINGLE_STEP = {0x80000004, 0x4000001E}          # single step, WOW64 single step
QUIET = {0x406D1388, 0xE06D7363, 0x40010006}    # thread naming, C++ throw, OutputDebugString


class STARTUPINFO(ctypes.Structure):
    _fields_ = [("cb", wt.DWORD), ("r", wt.LPWSTR), ("d", wt.LPWSTR), ("t", wt.LPWSTR)] + \
               [(n, wt.DWORD) for n in ("x", "y", "w", "h", "cx", "cy", "fill", "flags")] + \
               [("show", wt.WORD), ("cb2", wt.WORD), ("r2", ctypes.c_void_p),
                ("hin", wt.HANDLE), ("hout", wt.HANDLE), ("herr", wt.HANDLE)]


class PROCESS_INFORMATION(ctypes.Structure):
    _fields_ = [("hProcess", wt.HANDLE), ("hThread", wt.HANDLE), ("pid", wt.DWORD), ("tid", wt.DWORD)]


class WOW64_CONTEXT(ctypes.Structure):
    _fields_ = [("flags", wt.DWORD), ("dr", wt.DWORD * 6), ("fpu", ctypes.c_byte * 112), ("seg", wt.DWORD * 4),
                ("edi", wt.DWORD), ("esi", wt.DWORD), ("ebx", wt.DWORD), ("edx", wt.DWORD), ("ecx", wt.DWORD),
                ("eax", wt.DWORD), ("ebp", wt.DWORD), ("eip", wt.DWORD), ("cs", wt.DWORD), ("eflags", wt.DWORD),
                ("esp", wt.DWORD), ("ss", wt.DWORD), ("ext", ctypes.c_byte * 512)]


def k32():
    k = ctypes.WinDLL("kernel32", use_last_error=True)
    k.WaitForDebugEvent.argtypes = [ctypes.c_void_p, wt.DWORD]
    k.ContinueDebugEvent.argtypes = [wt.DWORD, wt.DWORD, wt.DWORD]
    k.CloseHandle.argtypes = [wt.HANDLE]
    k.TerminateProcess.argtypes = [wt.HANDLE, wt.UINT]
    k.CreateProcessW.argtypes = [wt.LPCWSTR, wt.LPWSTR, ctypes.c_void_p, ctypes.c_void_p, wt.BOOL, wt.DWORD,
                                 ctypes.c_void_p, wt.LPCWSTR, ctypes.c_void_p, ctypes.c_void_p]
    k.VirtualAllocEx.restype = ctypes.c_void_p
    k.VirtualAllocEx.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD, wt.DWORD]
    k.OpenThread.restype = wt.HANDLE
    return k


def read_mem(k, hproc, va, n):
    buf, got = ctypes.create_string_buffer(n), ctypes.c_size_t()
    ok = k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(va), buf, n, ctypes.byref(got))
    return buf.raw[:got.value] if ok else b""


def write_code(k, hproc, addr, data):
    old = wt.DWORD()
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(addr), len(data), 0x40, ctypes.byref(old))
    ok = k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(addr), data, len(data), None)
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(addr), len(data), old.value, ctypes.byref(old))
    k.FlushInstructionCache(wt.HANDLE(hproc), ctypes.c_void_p(addr), len(data))
    return ok


def windows_of(pid):
    """[(title, (l, t, r, b), hwnd)] of the visible top-level windows of pid."""
    u = ctypes.WinDLL("user32")
    found = []

    @ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
    def cb(h, _):
        p = wt.DWORD()
        u.GetWindowThreadProcessId(h, ctypes.byref(p))
        if p.value == pid and u.IsWindowVisible(h):
            rc = wt.RECT()
            u.GetWindowRect(h, ctypes.byref(rc))
            buf = ctypes.create_unicode_buffer(256)
            u.GetWindowTextW(h, buf, 256)
            found.append((buf.value, (rc.left, rc.top, rc.right, rc.bottom), h))
        return True
    u.EnumWindows(cb, 0)
    return found


def main_window(pid):
    wins = [w for w in windows_of(pid) if w[1][2] - w[1][0] > 100 and w[1][3] - w[1][1] > 100]
    return max(wins, key=lambda w: (w[1][2] - w[1][0]) * (w[1][3] - w[1][1]))[2] if wins else None


def snapshot(d):
    out = {}
    for root, _, files in os.walk(d):
        for f in files:
            p = os.path.join(root, f)
            try:
                st = os.stat(p)
            except OSError:
                continue
            out[p] = (st.st_size, st.st_mtime_ns)
    return out


def game_running():
    """PIDs of running lotrbfme.exe processes (the owner's game or another run)."""
    got = subprocess.run(["tasklist", "/FO", "CSV", "/NH", "/FI", f"IMAGENAME eq {GAME_EXE}"],
                         capture_output=True, text=True)
    return [int(r[1]) for r in csv.reader(got.stdout.splitlines()) if len(r) > 1 and r[0].lower() == GAME_EXE]


def xp_version_lie(k, hproc, base, exe):
    """Point the image's GetVersion / GetVersionExA IAT slots at stubs reporting
    Windows XP SP3 (5.1.2600, the version part of the WINXPSP3 layer the install
    runs with). Returns the slots changed."""
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    pe.parse_data_directories([1])
    slots = {}
    for d in pe.DIRECTORY_ENTRY_IMPORT:
        for imp in d.imports:
            if d.dll.lower() == b"kernel32.dll" and imp.name in (b"GetVersion", b"GetVersionExA"):
                slots[imp.name] = imp.address - pe.OPTIONAL_HEADER.ImageBase + base
    pe.close()
    mem = k.VirtualAllocEx(hproc, None, 0x1000, 0x3000, 0x40)
    info = struct.pack("<IIIII", 156, 5, 1, 2600, 2) + b"Service Pack 3".ljust(128, bytes(1)) \
        + struct.pack("<HHHBB", 3, 0, 0x100, 1, 0)
    get_version = bytes.fromhex("B8 05 01 28 0A C3")                      # mov eax, 0x0A280105; ret
    get_version_ex = (bytes.fromhex("56 57 8B7C240C 8B0F 81F99C000000 7605 B99C000000 83E904 83C704 BE")
                      + struct.pack("<I", mem + 0x104)                     # esi = template + 4
                      + bytes.fromhex("F3A4 5F 5E B801000000 C20400"))     # rep movsb; return TRUE
    blob = get_version.ljust(0x40, b"\xCC") + get_version_ex.ljust(0xC0, b"\xCC") + info
    k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(mem), blob, len(blob), None)
    for name, va in slots.items():
        old = wt.DWORD()
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(va), 4, 0x04, ctypes.byref(old))
        ptr = struct.pack("<I", mem if name == b"GetVersion" else mem + 0x40)
        k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(va), ptr, 4, None)
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(va), 4, old.value, ctypes.byref(old))
    return sorted(n.decode() for n in slots)


# --------------------------------------------------------------------------- the owner's profile
# GlobalData::parseGameDataDefinition builds the profile from SHGetSpecialFolderPathA
# and ...W (CSIDL_APPDATA) + UserDataLeafName (HKLM ...\The Battle for Middle-earth,
# "My Battle for Middle-earth Files"); screenshots go to CSIDL_MYPICTURES.
PROFILE_LEAF = "My Battle for Middle-earth Files"
CSIDL_APPDATA, CSIDL_MYPICTURES = 0x1A, 0x27
FOLDER_IMPORTS = (b"SHGetSpecialFolderPathA", b"SHGetSpecialFolderPathW")
# Fixed low-cost options: an Options.ini without IdealStaticGameLOD makes the
# first start benchmark the machine (BFME2 faults there under the debugger).
SANDBOX_OPTIONS = """AudioLOD = Low
FixedStaticGameLOD = Low
FlashTutorial = 0
HasGotOnline = yes
HasSeenLogoMovies = yes
IdealStaticGameLOD = Low
IsThreadedLoad = yes
Resolution = 1280 720
StaticGameLOD = Low
TimesInGame = 1
"""
# read-only snapshots around every run: HKCU's EA keys, their UAC VirtualStore copy
# (an unelevated 32-bit write to HKLM lands there) and HKLM's own
REGISTRY = (("HKEY_CURRENT_USER", r"Software\Electronic Arts"),
            ("HKEY_CURRENT_USER", r"Software\Classes\VirtualStore\MACHINE\SOFTWARE\WOW6432Node\Electronic Arts"),
            ("HKEY_LOCAL_MACHINE", r"SOFTWARE\WOW6432Node\Electronic Arts\EA Games\The Battle for Middle-earth"))


class RedirectError(RuntimeError):
    """The appdata lie could not be put in place: the run must not go on."""


class LauncherLieError(RuntimeError):
    """The image does not hold the bytes the launcher lie expects: nothing may run."""


def real_appdata():
    """The owner's roaming AppData (where the game would put its profile)."""
    return Path(os.environ.get("APPDATA") or Path.home() / "AppData" / "Roaming")


def real_profile():
    return real_appdata() / PROFILE_LEAF


def _norm(p):
    return os.path.normcase(os.path.abspath(str(p))).rstrip("\\/")


def check_sandbox_appdata(appdata, real=None):
    """Refuse a sandbox root that is the real AppData or lies inside it."""
    a, r = _norm(appdata), _norm(real if real is not None else real_appdata())
    if a == r or a.startswith(r + os.sep):
        raise RedirectError(f"sandbox appdata {appdata} is (inside) the real AppData {r}")
    return Path(appdata)


def prepare_sandbox_profile(appdata, real=None):
    """Check the sandbox root, create its profile and seed Options.ini (only if
    missing). Returns the sandbox profile directory."""
    prof = check_sandbox_appdata(appdata, real) / PROFILE_LEAF
    prof.mkdir(parents=True, exist_ok=True)
    if not (prof / "Options.ini").exists():
        (prof / "Options.ini").write_text(SANDBOX_OPTIONS)
    return prof


def appdata_stub(mem, orig, appdata, wide=True):
    """The SHGetSpecialFolderPath{W,A} replacement written at `mem`: CSIDL_APPDATA
    and CSIDL_MYPICTURES (low byte, so the CREATE flag is ignored) copy `appdata`
    into pszPath and return TRUE; every other folder jumps to the real function
    (`orig`, kept at mem+0x80)."""
    text = str(appdata).rstrip("\\") + "\0"
    try:
        path = text.encode("utf-16-le") if wide else text.encode("ascii")
    except UnicodeEncodeError:
        raise RedirectError(f"sandbox appdata path is not ASCII (the A call cannot take it): {appdata}")
    if len(text) > 260:
        raise RedirectError(f"sandbox appdata path longer than MAX_PATH: {appdata}")
    code = (bytes.fromhex("8B44240C 25FF000000")                       # mov eax, [esp+0Ch] (csidl); and eax, 0FFh
            + b"\x83\xF8" + bytes([CSIDL_APPDATA]) + b"\x74\x0B"        # cmp eax, 1Ah; je redirect
            + b"\x83\xF8" + bytes([CSIDL_MYPICTURES]) + b"\x74\x06"     # cmp eax, 27h; je redirect
            + b"\xFF\x25" + struct.pack("<I", mem + 0x80)               # jmp [orig]
            + bytes.fromhex("56 57 8B7C2410 BE") + struct.pack("<I", mem + 0x100)   # edi = pszPath; esi = path
            + b"\xB9" + struct.pack("<I", len(path))                    # ecx = bytes
            + bytes.fromhex("F3A4 5F 5E B801000000 C21000"))            # rep movsb; return TRUE (stdcall, 16)
    return code.ljust(0x80, b"\xCC") + struct.pack("<I", orig).ljust(0x80, b"\0") + path


def folder_slots(exe, base):
    """{import name: IAT slot VA} of SHGetSpecialFolderPathA/W in `exe` loaded at base."""
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    pe.parse_data_directories([1])
    found = collections.defaultdict(list)
    for d in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for imp in d.imports:
            if d.dll.lower() == b"shell32.dll" and imp.name in FOLDER_IMPORTS:
                found[imp.name].append(imp.address - pe.OPTIONAL_HEADER.ImageBase + base)
    pe.close()
    return found


def install_appdata_lie(k, hproc, base, exe, appdata):
    """At the game's loader breakpoint: point both SHGetSpecialFolderPath slots at
    appdata_stub, read everything back, and raise RedirectError on any failure."""
    appdata = check_sandbox_appdata(Path(appdata).resolve())
    found = folder_slots(exe, base)
    bad = [f"{n.decode()} x{len(found.get(n, []))}" for n in FOLDER_IMPORTS if len(found.get(n, [])) != 1]
    if bad:
        raise RedirectError(f"import slots in {exe}: {', '.join(bad)} (want exactly one each)")
    out = {"appdata": str(appdata)}
    for name in FOLDER_IMPORTS:
        slot = found[name][0]
        orig = read_mem(k, hproc, slot, 4)
        mem = k.VirtualAllocEx(hproc, None, 0x1000, 0x3000, 0x40)
        if len(orig) != 4 or not mem:
            raise RedirectError(f"cannot read the import slot {slot:#x} or allocate the stub")
        blob = appdata_stub(mem, struct.unpack("<I", orig)[0], appdata, wide=name.endswith(b"W"))
        old = wt.DWORD()
        k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(mem), blob, len(blob), None)
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(slot), 4, 0x04, ctypes.byref(old))
        k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(slot), struct.pack("<I", mem), 4, None)
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(slot), 4, old.value, ctypes.byref(old))
        if read_mem(k, hproc, mem, len(blob)) != blob or read_mem(k, hproc, slot, 4) != struct.pack("<I", mem):
            raise RedirectError(f"the redirect did not stick ({name.decode()} slot {slot:#x})")
        out[name.decode()] = hex(slot)
    return out


def profile_snapshot(d):
    """{relative path: (size, mtime_ns)} plus the SHA-256 of Options.ini."""
    import hashlib
    d = Path(d)
    files = {os.path.relpath(p, d): v for p, v in snapshot(d).items()} if d.exists() else {}
    opt = d / "Options.ini"
    sha = hashlib.sha256(opt.read_bytes()).hexdigest() if opt.exists() else None
    return {"files": files, "options_sha256": sha}


def profile_diff(before, after):
    """Changed, added or removed files (and an Options.ini content change)."""
    a, b = before["files"], after["files"]
    changed = sorted(set(a) ^ set(b) | {p for p in a if p in b and a[p] != b[p]})
    if before["options_sha256"] != after["options_sha256"]:
        changed.append("Options.ini (content)")
    return changed


def registry_snapshot(keys=REGISTRY):
    """{hive\\key\\value: repr(data)} of everything under each (hive, key), read only."""
    import winreg
    out = {}

    def walk(hive, sub):
        try:
            key = winreg.OpenKey(getattr(winreg, hive), sub, 0, winreg.KEY_READ)
        except OSError:
            return
        with key:
            i = 0
            while True:
                try:
                    n, v, _ = winreg.EnumValue(key, i)
                except OSError:
                    break
                out[f"{hive}\\{sub}\\{n}"] = repr(v)
                i += 1
            i = 0
            while True:
                try:
                    s = winreg.EnumKey(key, i)
                except OSError:
                    break
                walk(hive, f"{sub}\\{s}")
                i += 1
    for hive, sub in keys:
        walk(hive, sub)
    return out


class ProfileGuard:
    """Snapshot the owner's profile and the EA registry keys before a run;
    `check()` afterwards returns the report and whether anything changed."""

    def __init__(self, profile=None, keys=REGISTRY):
        self.profile, self.keys = Path(profile) if profile is not None else real_profile(), keys
        self.before, self.reg = profile_snapshot(self.profile), registry_snapshot(keys)

    def check(self):
        changed = profile_diff(self.before, profile_snapshot(self.profile))
        reg, old = registry_snapshot(self.keys), self.reg
        reg_changed = sorted(set(reg) ^ set(old) | {x for x in reg if x in old and reg[x] != old[x]})
        report = {"dir": str(self.profile), "files": len(self.before["files"]),
                  "options_sha256": self.before["options_sha256"], "changed": changed[:20],
                  "registry_values": len(old), "registry_changed": reg_changed[:20]}
        return report, bool(changed or reg_changed)


# --------------------------------------------------------------------------- the launcher lie
def launcher_patches(r=None, manifest=MANIFEST):
    """[(retail rva, retail bytes or None, workshop bytes)] from the baseline
    manifest's reverted_patches: one entry per run of differing bytes. A run
    inside a relocated field has no fixed retail bytes (the loader moved them),
    so it is written unchecked; every such run is dead code after the patch."""
    r = r or boot_image.Retail()
    fields = set()
    for s in boot_image.table_sites(r):
        fields.update(range(s, s + 4))
    out = []
    for p in json.loads(Path(manifest).read_text(encoding="utf-8"))["reverted_patches"]:
        rva, old, new = int(p["rva"], 16), bytes.fromhex(p["original"]), bytes.fromhex(p["cracked"])
        if len(old) != len(new) or bytes(r.secs[".text"][2][rva - r.secs[".text"][0]:][:len(old)]) != old:
            raise LauncherLieError(f"manifest patch {p['rva']} does not match the baseline's bytes")
        i = 0
        while i < len(old):
            if old[i] == new[i]:
                i += 1
                continue
            j, in_field = i, rva + i in fields
            while j < len(old) and old[j] != new[j] and (rva + j in fields) == in_field:
                j += 1
            out.append((rva + i, None if in_field else old[i:j], new[i:j]))
            i = j
    return out


def install_launcher_lie(k, hproc, base, patches):
    """Write `patches` [(image rva, expected bytes or None, new bytes)]. All new
    already: 'already' (the installed exe). Every checked run retail's: written
    and read back. Anything else raises LauncherLieError before a write."""
    now = [read_mem(k, hproc, base + rva, len(new)) for rva, _, new in patches]
    if all(n == new for n, (_, _, new) in zip(now, patches)):
        return {"runs": len(patches), "state": "already"}
    for n, (rva, old, new) in zip(now, patches):
        if len(n) != len(new) or (old is not None and n != old):
            raise LauncherLieError(f"image rva {rva:#x} holds {n.hex()}, not retail's {old.hex() if old else '?'}")
    for rva, _, new in patches:
        if not write_code(k, hproc, base + rva, new) or read_mem(k, hproc, base + rva, len(new)) != new:
            raise LauncherLieError(f"the write at image rva {rva:#x} did not stick")
    return {"runs": len(patches), "bytes": sum(len(n) for _, _, n in patches), "state": "written"}


def to_image(rva, pieces_map):
    """The image's RVA for retail RVA `rva` (identity without a piece map)."""
    if not pieces_map:
        return rva
    for _, rstart, nstart, size in pieces_map:
        if rstart <= rva < rstart + size:
            return nstart + rva - rstart
    return None


def to_retail(addr, base, pieces_map):
    """Retail RVA of a run-time address in the boot image (None outside its pieces)."""
    rva = addr - base
    for name, rstart, nstart, size in pieces_map:
        if nstart <= rva < nstart + size:
            return rstart + rva - nstart, name
    return None, None


# --------------------------------------------------------------------------- breakpoints
def set_probes(k, hproc, base, rvas):
    """One-shot int3 at each RVA: {address: original byte}."""
    out = {}
    for rva in sorted(rvas):
        a = base + rva
        b = read_mem(k, hproc, a, 1)
        if len(b) == 1 and write_code(k, hproc, a, b"\xCC"):
            out[a] = b
    return out


def clear_probe(k, hproc, tid, addr, byte):
    """Put the original byte back and re-run the instruction the probe replaced."""
    write_code(k, hproc, addr, byte)
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10001                       # WOW64_CONTEXT_CONTROL
    if h and k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        ctx.eip = addr
        k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
    if h:
        k.CloseHandle(h)


# WndProc's WM_ACTIVATEAPP arm (retail 0x5CEFB, reached through the message jump
# table): `mov al, [isWinMainActive]; test esi, esi; setne dl; cmp dl, al; je`.
# wParam lives in esi. The breakpoint sits on `test esi, esi`; the global's operand
# is relocated, so it is a wildcard.
FOCUS_ARM = re.compile(rb"\xA0....(\x85\xF6)\x0F\x95\xC2\x3A\xD0\x74", re.DOTALL)


def focus_arm_rva(exe):
    """RVA of the WM_ACTIVATEAPP arm's wParam test in `exe` (found by its bytes),
    or None unless exactly one place matches."""
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    hits = []
    for sec in pe.sections:
        if sec.Characteristics & 0x20000000:          # executable
            hits += [sec.VirtualAddress + m.start(1) for m in FOCUS_ARM.finditer(sec.get_data())]
    pe.close()
    return hits[0] if len(hits) == 1 else None


def focus_lie(k, hproc, tid, addr, byte):
    """At the WM_ACTIVATEAPP arm a deactivation (esi 0) becomes an activation. The
    original instruction then runs under the trap flag; the breakpoint goes back on
    the single step. True if rewritten."""
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10003                       # WOW64_CONTEXT_CONTROL | INTEGER
    rewritten = False
    if h and k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        if ctx.esi == 0:
            ctx.esi, rewritten = 1, True
        write_code(k, hproc, addr, byte)
        ctx.eip, ctx.eflags = addr, ctx.eflags | 0x100
        k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
    if h:
        k.CloseHandle(h)
    return rewritten


# --------------------------------------------------------------------------- the run
def run(exe, game_dir, args, timeout, *, appdata, patches=(), version_lie=True, probes=(), focus_rva=None,
        menu_rva=None, defocus_at=None):
    """Start `exe` (the sandbox's lotrbfme.exe, the game itself) under a debugger
    that follows children; the process whose image is `exe` is classified. At its
    loader breakpoint, before any game code: the appdata lie (required: on
    failure every process is killed, `profile-redirect-failed`), the launcher
    lie (`patches`, image RVAs; on failure `launcher-lie-failed`), the version
    lie, the focus breakpoint (`focus_rva`), the menu probe (`menu_rva`) and
    one-shot `probes` (RVAs; the ones reached go to res["probes_hit"]).
    `defocus_at` (s): minimise the window then, show it unactivated 15 s before
    the end."""
    check_sandbox_appdata(appdata)
    k = k32()
    k.QueryFullProcessImageNameW.argtypes = [wt.HANDLE, wt.DWORD, wt.LPWSTR, ctypes.POINTER(wt.DWORD)]
    si, pi = STARTUPINFO(), PROCESS_INFORMATION()
    si.cb = ctypes.sizeof(si)
    cmd = ctypes.create_unicode_buffer(f'"{exe}" {args}')
    if not k.CreateProcessW(None, cmd, None, None, False, DEBUG_PROCESS, None, str(game_dir),
                            ctypes.byref(si), ctypes.byref(pi)):
        raise SystemExit(f"boot_smoke: CreateProcess failed ({ctypes.get_last_error()})")
    ev = ctypes.create_string_buffer(256)
    procs = {}                                        # pid -> [hProcess, image path, base, ready]
    res = {"first_chance": [], "first_chance_count": 0, "processes": [], "probes_hit": []}
    armed, focus, menu, stepping = {}, {}, {}, {}
    if focus_rva is not None:
        res["focus_lie"] = {"rva": hex(focus_rva), "hits": 0, "rewritten": 0}
    u = ctypes.WinDLL("user32")
    u.ShowWindowAsync.argtypes = [wt.HWND, ctypes.c_int]   # never wait on a thread stopped at a breakpoint
    t0 = time.time()

    def stop(outcome, **why):
        res.update(outcome=outcome, **why)
        for hp, *_ in procs.values():             # killed before the stopped thread is let go
            k.TerminateProcess(hp, 1)
    try:
        while True:
            left = timeout - (time.time() - t0)
            if left <= 0:
                res["outcome"] = "timeout" if "pid" in res else "no-game-process"
                break
            if defocus_at is not None and "pid" in res:
                d = res.setdefault("defocus", {})
                if "minimised" not in d and time.time() - t0 >= defocus_at:
                    d["hwnd"] = main_window(res["pid"])
                    if d["hwnd"]:
                        u.ShowWindowAsync(d["hwnd"], 6)     # SW_MINIMIZE: another window is activated
                        d["minimised"] = round(time.time() - t0, 1)
                if d.get("hwnd") and "shown" not in d and left <= 15:
                    u.ShowWindowAsync(d["hwnd"], 4)         # SW_SHOWNOACTIVATE: back for the capture, unfocused
                    d["shown"] = round(time.time() - t0, 1)
            if not k.WaitForDebugEvent(ev, int(min(left, 1.0) * 1000)):
                continue
            code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
            status = DBG_CONTINUE
            game = pid == res.get("pid")
            if code == CREATE_PROCESS:
                k.CloseHandle(int.from_bytes(ev.raw[16:24], "little"))
                h = int.from_bytes(ev.raw[24:32], "little")
                buf, n = ctypes.create_unicode_buffer(1024), wt.DWORD(1024)
                k.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(n))
                procs[pid] = [h, buf.value, int.from_bytes(ev.raw[40:48], "little"), False]
                res["processes"].append(Path(buf.value).name)
                if _norm(buf.value) == _norm(exe) and "pid" not in res:
                    res.update(pid=pid, image_base=procs[pid][2], started=round(time.time() - t0, 1),
                               main_thread=int.from_bytes(ev.raw[32:40], "little"))
            elif code == LOAD_DLL:
                h = int.from_bytes(ev.raw[16:24], "little")
                if h:
                    k.CloseHandle(h)
            elif code == EXIT_PROCESS and game:
                res.update(outcome="exit", exit_code=int.from_bytes(ev.raw[16:20], "little"),
                           seconds=round(time.time() - t0, 1))
                k.ContinueDebugEvent(pid, tid, DBG_CONTINUE)
                break
            elif code == EXCEPTION:
                exc = int.from_bytes(ev.raw[16:20], "little")
                addr = int.from_bytes(ev.raw[32:40], "little")
                first = int.from_bytes(ev.raw[168:172], "little")
                nparam = int.from_bytes(ev.raw[40:44], "little")
                info = [int.from_bytes(ev.raw[48 + 8 * i:56 + 8 * i], "little") for i in range(min(nparam, 2))]
                bp = exc in BREAKPOINTS and game

                def at(table):
                    return next((a for a in (addr, addr - 1) if a in table), None) if bp else None
                at_focus, at_menu, hit = at(focus), at(menu), at(armed)
                handled = at_focus is not None or (exc in SINGLE_STEP and game and tid in stepping)
                if at_focus is not None:
                    res["focus_lie"]["hits"] += 1
                    res["focus_lie"]["rewritten"] += focus_lie(k, procs[pid][0], tid, at_focus, focus[at_focus])
                    stepping[tid] = at_focus
                elif handled:
                    write_code(k, procs[pid][0], stepping.pop(tid), b"\xCC")
                elif at_menu is not None:
                    clear_probe(k, procs[pid][0], tid, at_menu, menu.pop(at_menu))
                    if menu_rva in probes:                  # an authored unit starts there too
                        res["probes_hit"].append(menu_rva)
                    res["menu_built"] = round(time.time() - t0, 1)
                elif hit is not None:
                    clear_probe(k, procs[pid][0], tid, hit, armed.pop(hit))
                    res["probes_hit"].append(hit - procs[pid][2])
                elif exc == 0x4000001F and pid in procs and not procs[pid][3]:
                    h, path, base, _ = procs[pid]
                    procs[pid][3] = True
                    if game:                                # first, so a failure leaves nothing running
                        try:
                            res["appdata_lie"] = install_appdata_lie(k, h, base, path, appdata)
                        except (RedirectError, OSError, ImportError) as e:
                            stop("profile-redirect-failed", redirect_error=str(e))
                            k.ContinueDebugEvent(pid, tid, DBG_CONTINUE)
                            break
                        try:
                            res["launcher_lie"] = install_launcher_lie(k, h, base, patches)
                        except LauncherLieError as e:
                            stop("launcher-lie-failed", launcher_error=str(e))
                            k.ContinueDebugEvent(pid, tid, DBG_CONTINUE)
                            break
                    res.setdefault("version_lie", {})[Path(path).name] = \
                        xp_version_lie(k, h, base, path) if version_lie else []
                    if game and probes:
                        armed.update(set_probes(k, h, base, set(probes) - {menu_rva}))
                        res["probes_armed"] = len(armed)
                    if game and focus_rva is not None:
                        focus.update(set_probes(k, h, base, [focus_rva]))
                        res["focus_lie"]["armed"] = bool(focus)
                    if game and menu_rva is not None:
                        menu.update(set_probes(k, h, base, [menu_rva]))
                        res["menu_probe"] = {"rva": hex(menu_rva), "armed": bool(menu)}
                if exc not in BREAKPOINTS and not handled:
                    status = DBG_NOT_HANDLED
                    if first and game:
                        res["first_chance_count"] += 1
                        if exc not in QUIET and len(res["first_chance"]) < 10:
                            res["first_chance"].append([hex(exc), addr, info])
                            if exc == 0xC0000005 and "stack" not in res:   # the fault itself, not a rethrow
                                res["stack"] = stack_words(k, procs[pid][0], tid)
                                res["fault"] = addr
                    elif not first and game:
                        res.update(outcome="crash", code=hex(exc), address=res.get("fault", addr), info=info,
                                   seconds=round(time.time() - t0, 1))
                        res.setdefault("stack", stack_words(k, procs[pid][0], tid))
                        break
            k.ContinueDebugEvent(pid, tid, status)
        if res["outcome"] == "timeout":
            res["main_eips"] = sample_eips(k, res["main_thread"])
            res["windows"] = [(t, r) for t, r, _ in windows_of(res["pid"])]
            res["screenshot"] = screenshot(res["pid"])
    finally:
        for h, *_ in procs.values():
            k.TerminateProcess(h, 1)
        for h, *_ in procs.values():                # gone before lotrbfme.exe is written again
            k.WaitForSingleObject(wt.HANDLE(h), 30000)
        k.CloseHandle(pi.hThread)
        k.CloseHandle(pi.hProcess)
    return res


def stack_words(k, hproc, tid, n=2048):
    """(esp, [dwords from esp]) of the faulting WOW64 thread: return-address candidates."""
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10003                       # WOW64_CONTEXT_CONTROL | INTEGER
    if not h or not k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        return None
    k.CloseHandle(h)
    buf, got = ctypes.create_string_buffer(n * 4), ctypes.c_size_t()
    k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(ctx.esp), buf, n * 4, ctypes.byref(got))
    return {"esp": ctx.esp, "ebp": ctx.ebp, "regs": {r: hex(getattr(ctx, r)) for r in
                                                      ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "eip")},
            "words": [int.from_bytes(buf.raw[i:i + 4], "little") for i in range(0, got.value, 4)]}


def sample_eips(k, hthread, n=8):
    """EIPs of the game's main thread sampled 250 ms apart (where a hang spins)."""
    out = []
    for _ in range(n):
        ctx = WOW64_CONTEXT()
        ctx.flags = 0x10001
        k.Wow64SuspendThread(wt.HANDLE(hthread))
        if k.Wow64GetThreadContext(wt.HANDLE(hthread), ctypes.byref(ctx)):
            out.append(ctx.eip)
        k.ResumeThread(wt.HANDLE(hthread))
        time.sleep(0.25)
    return out


def screenshot(pid, name=None):
    """The game window's own picture, never the screen: a screen grab shows whatever
    lies on top of the window, which may be anything on the owner's desktop."""
    from PIL import ImageStat
    h = main_window(pid)
    if not h:
        return None
    u = ctypes.WinDLL("user32")
    rc = wt.RECT()
    u.GetClientRect(h, ctypes.byref(rc))
    img = window_image(h, rc.right, rc.bottom)
    if img is None:                           # nothing rendered (all black) or the capture failed
        return {"capture": "none"}
    path = OUT / (name or f"smoke_{pid}.png")
    img.save(path)
    stat = ImageStat.Stat(img.convert("L"))
    out = {"path": str(path), "size": list(img.size), "mean": round(stat.mean[0], 1),
           "stddev": round(stat.stddev[0], 1), "capture": "PrintWindow"}
    try:
        shot = json.loads((OUT / "smoke_retail.json").read_text())["run"]["screenshot"]["path"]
        out["differs_from_retail"] = image_distance(img, shot)
    except (OSError, KeyError, TypeError, ValueError):
        pass
    return out


def window_image(h, w, ht):
    """The window's own client-area pixels (PrintWindow, PW_CLIENTONLY |
    PW_RENDERFULLCONTENT); None when the capture fails or comes back black."""
    from PIL import Image
    if w <= 0 or ht <= 0:
        return None
    u, g = ctypes.WinDLL("user32"), ctypes.WinDLL("gdi32")
    u.GetDC.restype = g.CreateCompatibleDC.restype = g.CreateCompatibleBitmap.restype = wt.HANDLE
    g.SelectObject.argtypes = [wt.HANDLE, wt.HANDLE]
    g.CreateCompatibleDC.argtypes = [wt.HANDLE]
    g.CreateCompatibleBitmap.argtypes = [wt.HANDLE, ctypes.c_int, ctypes.c_int]
    g.DeleteObject.argtypes = g.DeleteDC.argtypes = [wt.HANDLE]
    u.ReleaseDC.argtypes = [wt.HWND, wt.HANDLE]
    u.PrintWindow.argtypes = [wt.HWND, wt.HANDLE, wt.UINT]
    g.GetDIBits.argtypes = [wt.HANDLE, wt.HANDLE, wt.UINT, wt.UINT, ctypes.c_void_p, ctypes.c_void_p, wt.UINT]
    sdc = u.GetDC(None)
    mdc = g.CreateCompatibleDC(sdc)
    bmp = g.CreateCompatibleBitmap(sdc, w, ht)
    g.SelectObject(mdc, bmp)
    ok = u.PrintWindow(h, mdc, 3)
    info = struct.pack("<IiiHHIIiiII", 40, w, -ht, 1, 32, 0, 0, 0, 0, 0, 0)
    buf = ctypes.create_string_buffer(w * ht * 4)
    got = g.GetDIBits(mdc, bmp, 0, ht, buf, ctypes.create_string_buffer(info, 44), 0)
    g.DeleteObject(bmp)
    g.DeleteDC(mdc)
    u.ReleaseDC(None, sdc)
    if not ok or got != ht:
        return None
    img = Image.frombuffer("RGBX", (w, ht), buf.raw, "raw", "BGRX", 0, 1).convert("RGB")
    return img if img.getextrema() != ((0, 0), (0, 0), (0, 0)) else None


def image_distance(img, other_path):
    """Mean absolute grey difference (0..255) of 64x36 thumbnails of two screens:
    a coarse 'same screen as the retail control' measure."""
    from PIL import Image, ImageChops, ImageStat

    def thumb(i):
        g = i.convert("L")
        return g.crop(g.point(lambda v: 255 if v > 8 else 0).getbbox() or (0, 0) + g.size).resize((64, 36))
    a, b = thumb(img), thumb(Image.open(other_path))
    return round(ImageStat.Stat(ImageChops.difference(a, b)).mean[0], 1)


def classify_alive(res):
    """The outcome of a run still alive at the timeout."""
    shot = res.get("screenshot")
    if "Exception" in [t for t, _ in res.get("windows", [])]:    # the game's own crash dialog
        return "crash-dialog"
    if not shot:
        return "no-window"
    if "path" not in shot:
        return "no-picture"
    if shot["stddev"] <= 8:
        return "blank-window"
    return "reached-menu" if res.get("menu_built") is not None else "loading-screen"


def ledger_row(rva):
    """(name, start, status) of the functions.csv row holding retail RVA `rva`, else the
    Ghidra function, else None."""
    with open(boot_image.REVERSE / "functions.csv", newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            if not row.get("target_rva"):
                continue
            s = int(row["target_rva"], 16)
            if s <= rva < s + int(row["target_size"] or 0):
                return row["name"], hex(s), row["status"]
    starts = []
    with open(boot_image.REVERSE / "ghidra_functions.csv", newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            starts.append((int(row["rva"], 16), int(row["size"] or 0), row["name"]))
    starts.sort()
    i = bisect.bisect_right(starts, (rva, 1 << 62)) - 1
    if i >= 0 and starts[i][0] <= rva < starts[i][0] + max(starts[i][1], 1):
        return starts[i][2], hex(starts[i][0]), "ghidra-only"
    return None


def smoke(a, rows=None, tag=None):
    """Build (unless --retail / --unpacked / --no-build), run once, classify: the
    outcome dict. `rows` (ledger rows) replaces the --overlay specs (bisection)."""
    tag = tag or a.tag
    out = {"image": "retail" if a.retail else "unpacked" if a.unpacked else "boot", "base": hex(a.base),
           "args": a.args, "overlay": a.overlay if rows is None else f"{len(rows)} row(s)"}
    authored, pieces_map = [], None
    if a.retail:
        exe, base = INSTALLED_EXE, boot_image.RETAIL_BASE
    elif a.unpacked:
        exe, base = boot_image.build.EXE, boot_image.RETAIL_BASE
    else:
        if a.no_build and rows is None:
            rep = json.loads((OUT / f"{tag}.json").read_text())
        else:
            rep = boot_image.build_image(a.base, OUT, tag, a.overlay, a.status, rows)
        out["link"] = {k: rep.get(k) for k in ("link_exit", "link_seconds", "imports_used")} | \
            {"check": rep.get("check", {})}
        if rep.get("overlay"):
            out["link"]["overlay"] = {k: v for k, v in rep["overlay"].items() if k != "rows_csv"}
        if not boot_image.image_ok(rep):
            out["outcome"] = "link-error"
            return out
        exe, pieces_map, base = OUT / f"{tag}.exe", rep["pieces_map"], a.base
        authored = rep.get("authored", [])
    out["sha256"] = __import__("hashlib").sha256(Path(exe).read_bytes()).hexdigest()
    patches = []
    for rva, old, new in launcher_patches():
        at = to_image(rva, pieces_map)
        if at is None or to_image(rva + len(new) - 1, pieces_map) != at + len(new) - 1:
            out["outcome"] = "launcher-lie-failed"
            out["launcher_error"] = f"retail {rva:#x} is not in one piece of the image"
            return out
        patches.append((at, old, new))
    prepare_sandbox_profile(a.appdata)
    target = a.game_dir / GAME_EXE
    shutil.copyfile(exe, target)
    before = {str(g): snapshot(g) for g in a.guard}
    profile_guard = ProfileGuard()
    if a.compat:
        os.environ["__COMPAT_LAYER"] = a.compat
    out["compat"] = a.compat
    moved = {}
    if pieces_map:
        start_of = {rs: ns for _, rs, ns, _ in pieces_map}
        moved = {start_of[rva]: (rva, size, name) for rva, size, name in authored}
    focus_rva = None if a.no_focus_lie else focus_arm_rva(exe)
    if not a.no_focus_lie and focus_rva is None:
        out["focus_lie"] = "WM_ACTIVATEAPP arm not found (no lie)"
    res = run(target, a.game_dir.resolve(), a.args, a.timeout, appdata=a.appdata, patches=patches,
              version_lie=not a.no_version_lie, probes=sorted(moved) if a.probes else (), focus_rva=focus_rva,
              menu_rva=to_image(MENU_CTOR, pieces_map), defocus_at=a.defocus)
    out["run"] = {k: v for k, v in res.items() if k not in ("first_chance", "stack", "probes_hit")}
    out["run"]["first_chance"] = [[c, hex(x), [hex(i) for i in info]] for c, x, info in res["first_chance"]]
    if authored:
        hit = [moved[x] for x in res["probes_hit"] if x in moved]
        out["authored_executed"] = {"units": len(hit), "of_units": len(authored),
                                    "bytes": sum(z for _, z, _ in hit), "of_bytes": sum(z for _, z, _ in authored),
                                    "probed": a.probes,
                                    "rows": [[hex(rva), name] for rva, _, name in sorted(hit)]}
    loaded = res.get("image_base", base)
    authored_at = sorted((rva, rva + size, name) for rva, size, name in authored)

    def blame(rva):
        """The authored unit holding retail RVA `rva`, if any."""
        i = bisect.bisect_right(authored_at, (rva, 1 << 62, "")) - 1
        return authored_at[i][2] if i >= 0 and authored_at[i][0] <= rva < authored_at[i][1] else None

    def retail_of(addr):
        return to_retail(addr, loaded, pieces_map) if pieces_map else (addr - loaded, "retail")
    if res["outcome"] == "crash" or (res["outcome"] == "exit" and res.get("fault") is not None
                                     and res["exit_code"]):
        fault = res["address"] if res["outcome"] == "crash" else res["fault"]
        rva, piece = retail_of(fault)
        row = ledger_row(rva) if rva is not None else None
        frames = []
        size = boot_image.Retail().size_of_image if pieces_map is None else max(n + z for _, _, n, z in pieces_map)
        for w in (res.get("stack") or {}).get("words", []):
            if loaded <= w < loaded + size and len(frames) < 12:
                fr = retail_of(w)
                if fr[0] is not None and fr[1].startswith((".text", "retail")):
                    frames.append([hex(w), hex(fr[0]), ledger_row(fr[0]), blame(fr[0])])
        st = res.get("stack") or {}
        out["run"].update(esp=hex(st.get("esp", 0)), regs=st.get("regs"),
                          stack_top=[hex(w) for w in st.get("words", [])[:8]])
        if row is None and frames:                   # faulted outside the image: blame the first game frame
            row = frames[0][2]
        out["crash"] = {"address": hex(fault), "retail_rva": hex(rva) if rva is not None else None, "piece": piece,
                        "row": row, "stack_frames": frames, "authored": blame(rva) if rva is not None else None}
        if res["outcome"] == "exit":
            out["crash"]["handled_then_exit"] = res["exit_code"]
        out["outcome"] = f"crash-at-{row[0] if row else (hex(rva) if rva is not None else 'outside-image')}"
    elif res["outcome"] == "exit":
        out["outcome"] = f"exit-{res['exit_code']:#x}"
    elif res["outcome"] == "timeout":
        out["main_thread_samples"] = []
        for e in res.get("main_eips", []):
            rva, _ = retail_of(e)
            out["main_thread_samples"].append([hex(e), hex(rva) if rva is not None else None,
                                               ledger_row(rva) if rva is not None else None])
        out["outcome"] = classify_alive(res)
    else:
        out["outcome"] = res["outcome"]             # no-game-process, profile-redirect-failed, launcher-lie-failed
    for g, snap in before.items():
        after = snapshot(Path(g))
        changed = sorted(set(after) ^ set(snap) | {p for p in snap if p in after and after[p] != snap[p]})
        out.setdefault("guard", {})[g] = changed[:20]
        if changed:
            out["outcome"] = "guard-violation"
    out["profile_guard"], touched = profile_guard.check()
    if touched:
        out["outcome"] = "profile-changed"
    return out


def broke(outcome):
    """A start-up the overlay broke: a crash, an exit, no or a blank window (not a slow
    load, not a link, lie or guard failure)."""
    return outcome.startswith(("crash", "exit-")) or outcome in ("no-window", "blank-window", "no-picture")


def bisect_rows(a, rows, executed=None):
    """Deterministic halving of a failing overlay to the rows that fail on their own.
    With a probed failing run, only units it executed are candidates. Each step runs
    one half alone; when neither half fails by itself the remaining set is reported
    together (an interaction). Returns (guilty rows, steps)."""
    by_rva = collections.defaultdict(list)
    for r in rows:
        by_rva[int(r["target_rva"], 16)].append(r)
    cand = sorted(by_rva if executed is None else set(by_rva) & set(executed))
    steps = []
    while len(cand) > 1:
        nxt = None
        for h in (cand[:len(cand) // 2], cand[len(cand) // 2:]):
            res = smoke(a, [r for x in h for r in by_rva[x]], tag="bisect")
            steps.append({"units": len(h), "first": hex(h[0]), "last": hex(h[-1]), "outcome": res["outcome"]})
            print(f"boot_smoke: bisect {len(h)} unit(s) {h[0]:#x}..{h[-1]:#x}: {res['outcome']}", flush=True)
            if broke(res["outcome"]):
                nxt = h
                break
        if nxt is None:
            break
        cand = nxt
    return [r for x in cand for r in by_rva[x]], steps


def write_queue(guilty, outcome, path=None):
    """build/boot/boot_queue.json: the rows repair_queue.py serves as `boot-crash` repairs."""
    path = Path(path or OUT / "boot_queue.json")
    alone = len({r["target_rva"] for r in guilty}) == 1
    items = [{"target_rva": r["target_rva"], "name": r["name"], "source": r["source"],
              "size": int(r["target_size"] or 0), "outcome": outcome,
              "why": (f"boot smoke {outcome} with this row's authored code overlaid alone" if alone else
                      f"boot smoke {outcome}: {len(guilty)} rows fail together, no half alone")} for r in guilty]
    path.write_text(json.dumps({"tool": "boot_smoke", "items": items}, indent=1), encoding="utf-8")
    return path


def install_path():
    """The install's registry InstallPath (None if unset)."""
    import winreg
    try:
        with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE,
                            r"SOFTWARE\WOW6432Node\Electronic Arts\EA Games\The Battle for Middle-earth") as key:
            return Path(winreg.QueryValueEx(key, "InstallPath")[0])
    except OSError:
        return None


def check_game_dir(game_dir, guards, installed=None):
    """Refuse a sandbox that is (inside) the registered install or a guarded directory."""
    d = Path(game_dir).resolve()
    for g in [x for x in [installed] if x] + list(guards):
        g = Path(g).resolve()
        if d == g or g in d.parents:
            raise SystemExit(f"boot_smoke: --game-dir {game_dir} is (inside) {g}: never run in an install")
    if not (d / GAME_EXE).exists() or not (d / "ini.big").exists():
        raise SystemExit(f"boot_smoke: {game_dir} is not a copy of the install (no {GAME_EXE} / ini.big)")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--game-dir", type=Path, required=True, help="a sandbox copy of the install")
    image = ap.add_mutually_exclusive_group()
    image.add_argument("--retail", action="store_true", help="control: the installed (workshop) lotrbfme.exe")
    image.add_argument("--unpacked", action="store_true",
                       help="control: the byte-matching baseline at 0x400000, with the launcher lie")
    ap.add_argument("--base", type=lambda v: int(v, 0), default=0x10000000)
    ap.add_argument("--tag", default="boot", help="build/boot/TAG.exe (boot_image.py link --tag)")
    ap.add_argument("--timeout", type=float, default=150)
    ap.add_argument("--args", default="-win -xres 1280 -yres 720")
    ap.add_argument("--guard", type=Path, action="append", default=[])
    ap.add_argument("--appdata", type=Path,
                    help="sandbox AppData root the game gets instead of the owner's (default GAME_DIR/../appdata)")
    ap.add_argument("--compat", default="", help="__COMPAT_LAYER for the child (WinXPSP3 needs elevation here)")
    ap.add_argument("--no-version-lie", action="store_true")
    ap.add_argument("--no-build", action="store_true", help="reuse build/boot/TAG.exe and TAG.json")
    ap.add_argument("--overlay", action="append", default=[], metavar="SET",
                    help="authored units in the image (as boot_image.py link --overlay)")
    ap.add_argument("--status", type=Path, default=boot_image.LINK_STATUS)
    ap.add_argument("--no-focus-lie", action="store_true",
                    help="let WM_ACTIVATEAPP(FALSE) through (the engine stops while the window lacks focus)")
    ap.add_argument("--defocus", type=float, metavar="SECONDS",
                    help="minimise the game window SECONDS after launch, show it unfocused 15 s before the end")
    ap.add_argument("--probes", action="store_true",
                    help="one-shot breakpoints at authored unit starts: which authored code ran")
    ap.add_argument("--bisect", action="store_true",
                    help="when the overlay fails, halve it to the guilty rows (build/boot/boot_queue.json)")
    a = ap.parse_args(argv)
    a.appdata = (a.appdata or a.game_dir.resolve().parent / "appdata").resolve()
    try:
        check_sandbox_appdata(a.appdata)
    except RedirectError as e:
        raise SystemExit(f"boot_smoke: {e}")
    check_game_dir(a.game_dir, a.guard, install_path())
    if game_running():
        raise SystemExit(f"boot_smoke: {GAME_EXE} is already running (the owner's game or another run)")
    ctypes.WinDLL("user32").SetProcessDPIAware()      # window and screen coordinates in physical pixels
    OUT.mkdir(parents=True, exist_ok=True)
    name = "smoke_retail.json" if a.retail else "smoke_unpacked.json" if a.unpacked else f"smoke_{a.tag}.json"
    out = smoke(a)
    (OUT / name).write_text(json.dumps(out, indent=1))
    if a.bisect and a.overlay and broke(out["outcome"]):
        with open(OUT / f"{a.tag}.overlay.csv", newline="", encoding="utf-8") as f:
            kept = {(int(x["retail_rva"], 16), x["name"]) for x in csv.DictReader(f) if x["overlay"] == "overlaid"}
        rows = [r for r in boot_image.overlay_rows(a.overlay, a.status)
                if (int(r["target_rva"], 16), r["name"]) in kept]
        ex = out.get("authored_executed", {})
        executed = {int(x[0], 16) for x in ex.get("rows", [])} if ex.get("probed") else None
        guilty, steps = bisect_rows(a, rows, executed)
        out["bisect"] = {"steps": steps, "guilty": [[r["target_rva"], r["name"], r["source"]] for r in guilty],
                         "queue": str(write_queue(guilty, out["outcome"]))}
        (OUT / name).write_text(json.dumps(out, indent=1))
    shown = dict(out)
    if "authored_executed" in out:
        shown["authored_executed"] = {k: v for k, v in out["authored_executed"].items() if k != "rows"}
    print(json.dumps(shown, indent=1))
    return 0 if out["outcome"] == "reached-menu" else 1


if __name__ == "__main__":
    sys.exit(main())
