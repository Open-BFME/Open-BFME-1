import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import data_scaffold  # noqa: E402
import loader_lanes as ll  # noqa: E402


def toolchain():
    try:
        root = build.vc71_root()
    except SystemExit:
        pytest.skip("VC 7.1 toolchain not present")
    return root, build.compiler_environment(root, None)


def entry_object(path, imports=(), safeseh=False):
    """`_start: ret`, plus one DIR32 per __imp_ symbol so the linker imports it.
    `safeseh` adds the absolute @feat.00 = 1 cl writes into every object it
    compiles (the object registers no handlers, so it is SafeSEH-compatible)."""
    coff = data_scaffold.Coff()
    if safeseh:
        coff.symbol("@feat.00", 1, -1, 3)
    text = coff.add_section(".text", 0x60500020, b"\xC3" * 16, 16)
    coff.symbol("_start", 0, text)
    if imports:
        data = coff.add_section(".data", 0xC0300040, bytes(4 * len(imports)), 4 * len(imports))
        coff.sections[data - 1]["relocs"] = [(4 * i, coff.symbol(f"__imp_{s}")) for i, s in enumerate(imports)]
    coff.write(path)


def link(root, env, out, *inputs, extra=()):
    proc = subprocess.run([str(root / "Vc7" / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/ENTRY:start",
                           "/SUBSYSTEM:WINDOWS", "/INCREMENTAL:NO", f"/OUT:{out}", *map(str, inputs), *extra],
                          capture_output=True, text=True, env=env)
    assert proc.returncode == 0, proc.stdout + proc.stderr
    return out


def test_name_types_reproduce_retail_import_names():
    assert ll.name_type("_AIL_startup@0", "_AIL_startup@0") == ll.IMPORT_NAME
    assert ll.name_type("_DirectInput8Create@20", "DirectInput8Create") == ll.IMPORT_UNDECORATE
    assert ll.name_type("_lineClose@4", "lineClose@4") == ll.IMPORT_NOPREFIX
    with pytest.raises(ValueError):
        ll.name_type("_a@4", "b")


def test_lanes_without_a_linked_image_are_unknown():
    lanes = ll.compare({}, None)
    assert {v["status"] for v in lanes.values()} == {"unknown"}


def test_absent_directories_must_stay_absent():
    base = {"headers": {}, "imports": [], "exports": {"module": None, "symbols": [], "ordinal_slots": 0},
            "resources": [], "stlport": None, "debug": [], "directories": {k: 0 for k in ll.ABSENT_DIRS}}
    linked = {**base, "directories": {**base["directories"], "load_config": 0x48}}
    lanes = ll.compare(base, linked)
    assert lanes["load_config"]["status"] == "mismatched" and lanes["tls"]["status"] == "matched"


def test_generated_import_library_imports_retail_names_and_hints(tmp_path):
    root, env = toolchain()
    names, hints = ["_AIL_startup@0", "_AIL_set_digital_master_volume@8"], [212, 187]
    lib = ll.write_import_lib("mss32.dll", names, hints, tmp_path / "mss32.lib")
    dlib = ll.write_import_lib("DINPUT8.dll", ["DirectInput8Create"], [0], tmp_path / "dinput8.lib")
    entry_object(tmp_path / "e.obj", ["_AIL_startup@0", "_AIL_set_digital_master_volume@8",
                                      "_DirectInput8Create@20"])
    exe = link(root, env, tmp_path / "t.exe", tmp_path / "e.obj", lib, dlib)
    got = {i["dll"].lower(): i for i in ll.facts(ll.load(exe))["imports"]}
    assert sorted(zip(got["mss32.dll"]["names"], got["mss32.dll"]["hints"])) == sorted(zip(names, hints))
    assert got["dinput8.dll"]["names"] == ["DirectInput8Create"]


def test_retail_res_links_to_retail_resources(tmp_path):
    if not build.EXE.exists():
        pytest.skip("retail image not present")
    root, env = toolchain()
    retail = ll.load(build.EXE)
    res = tmp_path / "retail.res"
    res.write_bytes(ll.res_bytes(ll.resource_leaves(retail)))
    entry_object(tmp_path / "e.obj")
    exe = link(root, env, tmp_path / "r.exe", tmp_path / "e.obj", res)
    assert ll.facts(ll.load(exe))["resources"] == ll.facts(retail)["resources"]


def winmain_object(path, safeseh):
    """`_WinMain@16: xor eax, eax / ret 16` for msvcrt.lib's crtexew.obj to call."""
    coff = data_scaffold.Coff()
    if safeseh:
        coff.symbol("@feat.00", 1, -1, 3)
    text = coff.add_section(".text", 0x60500020, bytes([0x33, 0xC0, 0xC2, 0x10, 0x00]) + bytes([0xCC]) * 11, 16)
    coff.symbol("_WinMain@16", 0, text)
    coff.write(path)


def test_load_config_appears_only_for_an_all_safeseh_crt_link(tmp_path):
    """Measured on link.exe 7.1 with msvcrt.lib's WinMainCRTStartup: when every
    input is SafeSEH-compatible (@feat.00) the default link adds msvcrt's
    loadcfg.obj (a 72-byte load-config directory); /SAFESEH:NO, or any input
    without @feat.00, leaves none -- retail's shape."""
    root, env = toolchain()
    lib = root / "Vc7" / "lib"
    crt = [lib / "msvcrt.lib", lib / "kernel32.lib"]
    flags = ["/ENTRY:WinMainCRTStartup"]

    def load_config(name, safeseh, extra=()):
        winmain_object(tmp_path / f"{name}.obj", safeseh)
        proc = subprocess.run([str(root / "Vc7" / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB",
                               "/SUBSYSTEM:WINDOWS", "/INCREMENTAL:NO", *flags, *extra,
                               f"/OUT:{tmp_path / name}.exe", str(tmp_path / f"{name}.obj"), *map(str, crt)],
                              capture_output=True, text=True, env=env)
        assert proc.returncode == 0, proc.stdout + proc.stderr
        return ll.facts(ll.load(tmp_path / f"{name}.exe"))["directories"]["load_config"]

    assert load_config("safe", True) == 72
    assert load_config("safe_no", True, ["/SAFESEH:NO"]) == 0
    assert load_config("unsafe", False) == 0
