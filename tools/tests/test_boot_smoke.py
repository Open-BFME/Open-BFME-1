"""boot_smoke: the lies it tells the game, the owner's-profile protection, and the outcome rules.

Nothing here starts the game. The redirect and the launcher lie are checked as
code (stub bytes, installation against a fake process), every refusal is checked
to happen before a process could exist, and the bisection runs over a fake smoke.
"""
import ctypes
import json
import os
import struct
import sys
import time
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
bs = pytest.importorskip("boot_smoke", exc_type=(ImportError, OSError, ValueError))  # Win32 only

BASELINE = bs.boot_image.build.EXE
REAL = r"C:\Users\Someone\AppData\Roaming"
needs_exes = pytest.mark.skipif(not (BASELINE.exists() and bs.INSTALLED_EXE.exists()), reason="no baseline exes")


# ---------------------------------------------------------------- sandbox appdata
@pytest.mark.parametrize("bad", [REAL, REAL + "\\", REAL.upper(), REAL + r"\sandbox",
                                 REAL + r"\My Battle for Middle-earth Files"])
def test_real_appdata_and_anything_inside_it_are_refused(bad):
    with pytest.raises(bs.RedirectError):
        bs.check_sandbox_appdata(bad, real=REAL)


@pytest.mark.parametrize("ok", [REAL + "2", r"C:\Users\Someone\AppData\Roaming-sandbox", r"D:\scratch\appdata"])
def test_a_sibling_with_a_common_prefix_is_allowed(ok):       # negative control
    assert bs.check_sandbox_appdata(ok, real=REAL) == Path(ok)


def test_the_default_real_appdata_is_refused():
    with pytest.raises(bs.RedirectError):
        bs.check_sandbox_appdata(bs.real_appdata())


def test_profile_is_seeded_once_and_never_overwritten(tmp_path):
    prof = bs.prepare_sandbox_profile(tmp_path, real=r"C:\nowhere")
    assert prof == tmp_path / "My Battle for Middle-earth Files"
    assert (prof / "Options.ini").read_text() == bs.SANDBOX_OPTIONS
    (prof / "Options.ini").write_text("StaticGameLOD = High\n")
    bs.prepare_sandbox_profile(tmp_path, real=r"C:\nowhere")
    assert (prof / "Options.ini").read_text() == "StaticGameLOD = High\n"


def test_seeded_options_skip_the_first_start_benchmark():
    keys = dict(line.split(" = ") for line in bs.SANDBOX_OPTIONS.splitlines())
    assert keys["IdealStaticGameLOD"] == "Low" and keys["HasSeenLogoMovies"] == "yes"


def test_preparing_inside_real_appdata_refuses_before_writing(tmp_path):
    with pytest.raises(bs.RedirectError):
        bs.prepare_sandbox_profile(tmp_path / "x", real=tmp_path)
    assert os.listdir(tmp_path) == []


# ---------------------------------------------------------------- the stubs
MEM, ORIG = 0x01230000, 0x76543210


def disasm(path=r"C:\sandbox\appdata", wide=True):
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    blob = bs.appdata_stub(MEM, ORIG, path, wide)
    code = blob[:blob.index(b"\xC2\x10\x00") + 3]
    return blob, [f"{i.mnemonic} {i.op_str}" for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, MEM)]


@pytest.mark.parametrize("wide", [True, False])
def test_appdata_and_pictures_redirect_everything_else_reaches_the_real_call(wide):
    blob, text = disasm(wide=wide)
    path = "C:\\sandbox\\appdata\0".encode("utf-16-le" if wide else "ascii")
    assert struct.unpack_from("<I", blob, 0x80)[0] == ORIG and blob[0x100:] == path
    redirect = f"je {MEM + 0x19:#x}"
    assert text[:7] == ["mov eax, dword ptr [esp + 0xc]", "and eax, 0xff", "cmp eax, 0x1a", redirect,
                        "cmp eax, 0x27", redirect, f"jmp dword ptr [{MEM + 0x80:#x}]"]
    assert text[7:] == ["push esi", "push edi", "mov edi, dword ptr [esp + 0x10]", f"mov esi, {MEM + 0x100:#x}",
                        f"mov ecx, {len(path):#x}", "rep movsb byte ptr es:[edi], byte ptr [esi]", "pop edi",
                        "pop esi", "mov eax, 1", "ret 0x10"]


def test_long_or_non_ascii_paths_are_refused():
    with pytest.raises(bs.RedirectError):
        bs.appdata_stub(MEM, ORIG, "C:\\" + "x" * 300)
    with pytest.raises(bs.RedirectError):
        bs.appdata_stub(MEM, ORIG, "C:\\sandb\u00f6x", wide=False)
    bs.appdata_stub(MEM, ORIG, "C:\\sandb\u00f6x", wide=True)          # the W call takes it


class FakeProcess:
    """kernel32 stand-in over a dict of bytes: enough for the installers."""

    def __init__(self, mem=None, alloc=0x02000000, drop_writes=False):
        self.mem, self.next, self.drop = dict(mem or {}), alloc, drop_writes

    def VirtualAllocEx(self, *a):
        got = self.next
        self.next += 0x1000 if got else 0
        return got

    def VirtualFreeEx(self, *a):
        return 1

    def VirtualProtectEx(self, *a):
        return 1

    def FlushInstructionCache(self, *a):
        return 1

    def ReadProcessMemory(self, h, va, buf, n, got):
        ctypes.memmove(buf, bytes(self.mem.get(va.value + i, 0) for i in range(n)), n)
        got._obj.value = n
        return 1

    def WriteProcessMemory(self, h, va, data, n, _):
        if not self.drop:
            for i, b in enumerate(bytes(data)[:n]):
                self.mem[va.value + i] = b
        return 1

    def u32(self, va):
        return struct.unpack("<I", bytes(self.mem.get(va + i, 0) for i in range(4)))[0]

    def load(self, va, data):
        self.mem.update({va + i: b for i, b in enumerate(data)})


@needs_exes
def test_both_folder_slots_point_at_stubs_and_keep_the_real_functions(tmp_path):
    slots = bs.folder_slots(BASELINE, 0x400000)
    k = FakeProcess()
    k.load(slots[b"SHGetSpecialFolderPathA"][0], struct.pack("<I", 0x77001111))
    k.load(slots[b"SHGetSpecialFolderPathW"][0], struct.pack("<I", 0x77002222))
    info = bs.install_appdata_lie(k, 1, 0x400000, BASELINE, tmp_path)
    for name, real in ((b"SHGetSpecialFolderPathA", 0x77001111), (b"SHGetSpecialFolderPathW", 0x77002222)):
        stub = k.u32(slots[name][0])
        assert info[name.decode()] == hex(slots[name][0]) and stub >= 0x02000000
        assert k.u32(stub + 0x80) == real
    assert k.mem[k.u32(slots[b"SHGetSpecialFolderPathA"][0]) + 0x101] == ord(":")       # narrow path
    assert k.mem[k.u32(slots[b"SHGetSpecialFolderPathW"][0]) + 0x102] == ord(":")       # wide path


@needs_exes
def test_a_write_that_does_not_stick_refuses(tmp_path):        # positive control
    with pytest.raises(bs.RedirectError):
        bs.install_appdata_lie(FakeProcess(drop_writes=True), 1, 0x400000, BASELINE, tmp_path)


@needs_exes
def test_no_stub_memory_refuses(tmp_path):
    with pytest.raises(bs.RedirectError):
        bs.install_appdata_lie(FakeProcess(alloc=0), 1, 0x400000, BASELINE, tmp_path)


def test_an_image_without_the_imports_refuses(tmp_path):
    with pytest.raises(bs.RedirectError, match="want exactly one each"):
        bs.install_appdata_lie(FakeProcess(), 1, 0x400000, sys.executable, tmp_path)


@needs_exes
def test_real_appdata_refuses_before_touching_the_process():
    k = FakeProcess()
    with pytest.raises(bs.RedirectError):
        bs.install_appdata_lie(k, 1, 0x400000, BASELINE, bs.real_appdata())
    assert k.mem == {}


# ---------------------------------------------------------------- the launcher lie
@needs_exes
def test_launcher_patches_turn_the_baseline_into_the_installed_exe():
    """Writing the runs over the baseline gives the installed exe's bytes (the PE
    checksum, at 0x188, is the only other difference)."""
    base, INST = bytearray(BASELINE.read_bytes()), bs.INSTALLED_EXE.read_bytes()
    patches = bs.launcher_patches()
    for rva, old, new in patches:                 # the .text file offset equals its RVA here
        assert old is None or base[rva:rva + len(old)] == old
        base[rva:rva + len(new)] = new
    diff = [i for i in range(len(base)) if base[i] != INST[i]]
    assert diff and all(0x188 <= i < 0x18C for i in diff)
    unchecked = [rva for rva, old, _ in patches if old is None]
    assert unchecked == [0x853F9, 0x853FF]        # GlobalData's dead code over two relocated fields


@needs_exes
def test_launcher_lie_writes_checks_and_knows_the_installed_exe():
    patches = bs.launcher_patches()
    k = FakeProcess()
    data = BASELINE.read_bytes()
    for rva, _, new in patches:
        k.load(0x10000000 + rva, data[rva:rva + len(new)])
    assert bs.install_launcher_lie(k, 1, 0x10000000, patches)["state"] == "written"
    assert all(bytes(k.mem[0x10000000 + rva + i] for i in range(len(new))) == new for rva, _, new in patches)
    assert bs.install_launcher_lie(k, 1, 0x10000000, patches)["state"] == "already"   # the installed exe


@needs_exes
def test_launcher_lie_refuses_other_bytes_before_writing():  # positive control
    patches = bs.launcher_patches()
    k = FakeProcess()
    data = bytearray(BASELINE.read_bytes())
    data[0x7A4E7] = 0x90                          # GameEngine::init's je is something else
    for rva, _, new in patches:
        k.load(rva, data[rva:rva + len(new)])
    before = dict(k.mem)
    with pytest.raises(bs.LauncherLieError):
        bs.install_launcher_lie(k, 1, 0, patches)
    assert k.mem == before


def test_to_image_follows_the_piece_map():
    pm = [[".text", 0x1000, 0x1000, 0x100], [".rdata", 0x5000, 0x7000, 0x100]]
    assert bs.to_image(0x1010, pm) == 0x1010 and bs.to_image(0x5010, pm) == 0x7010
    assert bs.to_image(0x9000, pm) is None and bs.to_image(0x9000, None) == 0x9000


# ---------------------------------------------------------------- focus lie, menu, outcomes
@needs_exes
def test_focus_arm_found_in_both_exes_and_not_in_a_copy_without_it(tmp_path):
    assert bs.focus_arm_rva(BASELINE) == 0x5CF00 == bs.focus_arm_rva(bs.INSTALLED_EXE)
    data = bytearray(BASELINE.read_bytes())
    at = data.index(bytes.fromhex("85F60F95C23AD074"))
    data[at + 1] = 0xFF                           # test esi, edi: no longer the arm
    (tmp_path / "g.exe").write_bytes(bytes(data))
    assert bs.focus_arm_rva(tmp_path / "g.exe") is None


def test_menu_probe_is_the_main_menu_constructor():
    assert bs.ledger_row(bs.MENU_CTOR)[:2] == ("??0BfmeAptScreenMainMenu@@QAE@PAX@Z", hex(bs.MENU_CTOR))


@pytest.mark.parametrize("res, outcome", [
    ({"screenshot": {"path": "x", "stddev": 40}, "menu_built": 30.2}, "reached-menu"),
    ({"screenshot": {"path": "x", "stddev": 40}}, "loading-screen"),         # a picture is not the menu
    ({"screenshot": {"path": "x", "stddev": 3}, "menu_built": 30.2}, "blank-window"),
    ({"screenshot": {"capture": "none"}, "menu_built": 30.2}, "no-picture"),
    ({"screenshot": None}, "no-window"),
    ({"screenshot": {"path": "x", "stddev": 40}, "windows": [("Exception", (0, 0, 1, 1))]}, "crash-dialog"),
])
def test_alive_outcomes(res, outcome):
    assert bs.classify_alive(res) == outcome


# ---------------------------------------------------------------- the owner's profile guard
def test_rewritten_options_is_caught_even_with_same_size_and_mtime(tmp_path):
    opt = tmp_path / "Options.ini"
    opt.write_text("Resolution = 800 600\n")
    st = opt.stat()
    before = bs.profile_snapshot(tmp_path)
    opt.write_text("Resolution = 640 480\n")
    os.utime(opt, ns=(st.st_atime_ns, st.st_mtime_ns))
    assert bs.profile_diff(before, bs.profile_snapshot(tmp_path)) == ["Options.ini (content)"]


def test_new_replay_and_touched_file_are_caught(tmp_path):
    f = tmp_path / "Skirmish.ini"
    f.write_text("a")
    before = bs.profile_snapshot(tmp_path)
    later = time.time_ns() + 5_000_000_000
    os.utime(f, ns=(later, later))
    (tmp_path / "Replays").mkdir()
    (tmp_path / "Replays" / "x.BfMEReplay").write_bytes(b"x")
    assert bs.profile_diff(before, bs.profile_snapshot(tmp_path)) == [str(Path("Replays/x.BfMEReplay")),
                                                                      "Skirmish.ini"]


def test_guard_object_reports_a_touched_profile(tmp_path):
    (tmp_path / "Options.ini").write_text("a = 1\n")
    g = bs.ProfileGuard(tmp_path, keys=())
    assert g.check() == ({"dir": str(tmp_path), "files": 1, "options_sha256": g.before["options_sha256"],
                          "changed": [], "registry_values": 0, "registry_changed": []}, False)
    (tmp_path / "Options.ini").write_text("a = 2\n")
    report, touched = g.check()
    assert touched and "Options.ini (content)" in report["changed"]


def test_registry_snapshot_reads_hklm_install_key():
    snap = bs.registry_snapshot(bs.REGISTRY[2:])
    if not snap:
        pytest.skip("BFME1 is not installed here")
    assert any(k.endswith("\\UserDataLeafName") for k in snap)


# ---------------------------------------------------------------- refusals before a launch
def test_run_requires_a_sandbox_appdata():
    with pytest.raises(TypeError):
        bs.run(Path("Z:/nope/lotrbfme.exe"), Path("Z:/nope"), "-win", 1)
    with pytest.raises(bs.RedirectError):
        bs.run(Path("Z:/nope/lotrbfme.exe"), Path("Z:/nope"), "-win", 1, appdata=bs.real_appdata())


def test_cli_refuses_real_appdata():
    with pytest.raises(SystemExit, match="real AppData"):
        bs.main(["--game-dir", "Z:/nope", "--retail", "--appdata", str(bs.real_appdata())])


def test_game_dir_inside_an_install_or_guard_is_refused(tmp_path):
    inst = tmp_path / "BFME1"
    (inst / "sub").mkdir(parents=True)
    for d, guards, installed in ((inst, [], inst), (inst / "sub", [], inst), (inst, [inst], None)):
        with pytest.raises(SystemExit, match="never run in an install"):
            bs.check_game_dir(d, guards, installed)
    with pytest.raises(SystemExit, match="not a copy of the install"):
        bs.check_game_dir(tmp_path / "BFME1-copy", [inst], inst)
    copy = tmp_path / "copy"
    copy.mkdir()
    (copy / "lotrbfme.exe").write_bytes(b"MZ")
    (copy / "ini.big").write_bytes(b"BIGF")
    bs.check_game_dir(copy, [inst], inst)         # negative control


# ---------------------------------------------------------------- bisection and queue
ROWS = [{"target_rva": f"0x{0x1000 + 0x10 * k:08X}", "name": f"f{k}", "source": "game/x.cpp",
         "target_size": "16"} for k in range(37)]


def run_bisect(monkeypatch, bad, executed=None):
    runs = []

    def smoke(a, rows=None, tag=None):
        got = {r["name"] for r in rows}
        runs.append(len(got))
        return {"outcome": "crash-at-x" if bad(got) else "reached-menu"}
    monkeypatch.setattr(bs, "smoke", smoke)
    guilty, steps = bs.bisect_rows(None, ROWS, executed)
    return [r["name"] for r in guilty], steps, runs


def test_one_guilty_row_is_found(monkeypatch):
    guilty, steps, _ = run_bisect(monkeypatch, lambda names: "f23" in names)
    assert guilty == ["f23"] and len(steps) <= 2 * 6


def test_only_executed_units_are_candidates(monkeypatch):
    guilty, _, runs = run_bisect(monkeypatch, lambda names: "f5" in names, executed={0x1050, 0x1060})
    assert guilty == ["f5"] and runs[0] == 1


def test_an_interaction_is_reported_together(monkeypatch):
    guilty, _, _ = run_bisect(monkeypatch, lambda names: {"f2", "f30"} <= names)
    assert len(guilty) == 37


def test_queue_items_carry_the_rows(tmp_path):
    items = json.loads(bs.write_queue(ROWS[3:4], "crash-at-x", tmp_path / "q.json").read_text())["items"]
    assert (items[0]["target_rva"], items[0]["name"], items[0]["size"]) == ("0x00001030", "f3", 16)


def test_slow_loads_and_refusals_are_not_breakage():
    assert bs.broke("crash-at-x") and bs.broke("exit-0x1") and bs.broke("blank-window")
    for ok in ("reached-menu", "loading-screen", "link-error", "guard-violation", "profile-changed",
               "launcher-lie-failed", "profile-redirect-failed"):
        assert not bs.broke(ok)


class Alloc32Kernel:
    """VirtualAllocEx that answers anywhere=`anywhere` and honours an asked address."""

    def __init__(self, anywhere):
        self.anywhere, self.freed = anywhere, []

        def alloc(h, at, size, kind, prot):
            return self.anywhere if at is None else at
        self.VirtualAllocEx = alloc
        self.VirtualFreeEx = lambda h, at, size, kind: self.freed.append(at) or 1


def test_alloc32_keeps_a_low_address():
    k = Alloc32Kernel(0x02000000)
    assert bs.alloc32(k, 1, 0x1000) == 0x02000000 and k.freed == []


def test_alloc32_frees_a_high_address_and_asks_low():    # Wine's WoW64 can answer above 4 GiB
    k = Alloc32Kernel(0x1_0000_0000)
    mem = bs.alloc32(k, 1, 0x1000)
    assert k.freed == [0x1_0000_0000] and mem + 0x1000 < 1 << 31


def test_alloc32_without_memory_is_none():
    k = Alloc32Kernel(0)
    k.VirtualAllocEx = lambda *a: 0
    assert bs.alloc32(k, 1, 0x1000) is None


def test_windows_waits_for_the_wow64_loader_int3():
    if sys.platform == "win32" and bs.under_wine():
        pytest.skip("running under Wine")
    assert bs.LOADER_BREAKPOINTS == {0x4000001F}
