import subprocess
import struct
import sys
import tempfile
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


def link(root, env, out, *inputs, extra=(), entry="start"):
    command = [str(root / "Vc7" / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", f"/ENTRY:{entry}",
               "/SUBSYSTEM:WINDOWS", "/INCREMENTAL:NO"]
    if sys.platform == "win32":
        command += [f"/OUT:{out.resolve()}", *(str(path.resolve()) for path in inputs), *extra]
    else:
        wine = ll.shutil.which("wine")
        assert wine is not None, "wine not found"
        command.insert(0, wine)
        command += [f"/OUT:{build.wine_path(out.resolve())}",
                    *(build.wine_path(path.resolve()) for path in inputs), *extra]
    out.unlink(missing_ok=True)
    with tempfile.TemporaryFile() as stdout, tempfile.TemporaryFile() as stderr:
        proc = subprocess.run(command, stdout=stdout, stderr=stderr, env=env, cwd=ll.ROOT)
        stdout.seek(0)
        stderr.seek(0)
        diagnostics = (stdout.read() + stderr.read()).decode("latin-1", errors="replace")
    assert proc.returncode == 0, diagnostics
    assert out.is_file() and out.read_bytes().startswith(b"MZ"), diagnostics
    return out


def test_name_types_reproduce_retail_import_names():
    assert ll.name_type("_AIL_startup@0", "_AIL_startup@0") == ll.IMPORT_NAME
    assert ll.name_type("_DirectInput8Create@20", "DirectInput8Create") == ll.IMPORT_UNDECORATE
    assert ll.name_type("_lineClose@4", "lineClose@4") == ll.IMPORT_NOPREFIX
    with pytest.raises(ValueError):
        ll.name_type("_a@4", "b")


def import_archive(symbol, dll):
    strings = symbol.encode('ascii') + b'\0' + dll.encode('ascii') + b'\0'
    body = struct.pack('<HHHHIIHH', 0, 0xFFFF, 0, 0x14C, 0, len(strings), 0, 0) + strings
    header = b'import.obj/     ' + b'0           ' + b'0     ' + b'0     ' + b'0       '
    header += str(len(body)).encode().ljust(10) + b'`\n'
    assert len(header) == 60
    return b'!<arch>\n' + header + body + (b'\n' if len(body) & 1 else b'')


@pytest.fixture
def fake_lib_tool(monkeypatch, tmp_path):
    root = tmp_path / 'Visual Studio with spaces'
    monkeypatch.setattr(build, 'vc71_root', lambda: root)
    monkeypatch.setattr(build, 'compiler_environment', lambda root, source: {'TEST': 'environment'})
    monkeypatch.setattr(ll.shutil, 'which', lambda name: '/usr/bin/wine')
    conversions = []
    def wine_path(path):
        conversions.append(path)
        return 'Z:' + str(path).replace('/', '\\')
    monkeypatch.setattr(build, 'wine_path', wine_path)
    return root, conversions


@pytest.mark.parametrize('platform', ['win32', 'linux'])
@pytest.mark.parametrize('name,hint,symbol,kind', [
    ('_AIL_startup@0', 212, '_AIL_startup@0', ll.IMPORT_NAME),
    ('DirectInput8Create', 17, '_DirectInput8Create@20', ll.IMPORT_UNDECORATE)])
def test_import_lib_portable_command_and_exact_patch(monkeypatch, tmp_path, fake_lib_tool,
                                                     platform, name, hint, symbol, kind):
    root, conversions = fake_lib_tool
    monkeypatch.setattr(ll.sys, 'platform', platform)
    out = tmp_path / 'output with spaces.lib'
    calls = []
    def run(command, **kwargs):
        calls.append((command, kwargs))
        assert kwargs['stdout'] != subprocess.PIPE and kwargs['stderr'] != subprocess.PIPE
        kwargs['stdout'].write(b'generated\n')
        out.write_bytes(import_archive(symbol, 'mss32.dll'))
        return subprocess.CompletedProcess(command, 0)
    monkeypatch.setattr(subprocess, 'run', run)
    assert ll.write_import_lib('mss32.dll', [name], [hint], out) == out
    command, kwargs = calls[0]
    paths = [out.with_suffix('.def').resolve(), out.resolve()]
    if platform == 'win32':
        assert command == [str(root / 'Vc7' / 'bin' / 'lib.exe'), '/NOLOGO', '/MACHINE:X86',
                           '/DEF:' + str(paths[0]), '/OUT:' + str(paths[1])]
        assert conversions == []
    else:
        assert command == ['/usr/bin/wine', str(root / 'Vc7' / 'bin' / 'lib.exe'), '/NOLOGO', '/MACHINE:X86',
                           '/DEF:Z:' + str(paths[0]).replace('/', '\\'),
                           '/OUT:Z:' + str(paths[1]).replace('/', '\\')]
        assert conversions == paths
    assert kwargs['cwd'] == ll.ROOT and kwargs['env'] == {'TEST': 'environment'}
    actual_hint, actual_kind = struct.unpack_from('<HH', out.read_bytes(), 8 + 60 + 16)
    assert actual_hint == hint and actual_kind == kind << ll.NAME_TYPE_SHIFT


@pytest.mark.parametrize('verdict', ['nonzero', 'missing', 'bad_archive', 'missing_import'])
def test_import_lib_refuses_failed_or_missing_output(monkeypatch, tmp_path, fake_lib_tool, verdict):
    monkeypatch.setattr(ll.sys, 'platform', 'linux')
    out = tmp_path / 'failed.lib'
    out.write_bytes(import_archive('_AIL_startup@0', 'mss32.dll'))  # A stale success must not pass.
    def run(command, **kwargs):
        assert not out.exists()
        kwargs['stderr'].write(b'actual lib failure')
        if verdict == 'nonzero':
            out.write_bytes(import_archive('_AIL_startup@0', 'mss32.dll'))
        elif verdict == 'bad_archive':
            out.write_bytes(b'not an archive')
        elif verdict == 'missing_import':
            out.write_bytes(b'!<arch>\n')
        return subprocess.CompletedProcess(command, 17 if verdict == 'nonzero' else 0)
    monkeypatch.setattr(subprocess, 'run', run)
    expected = {'nonzero': 'exit 17.*actual lib failure', 'missing': 'without producing',
                'bad_archive': 'not an archive', 'missing_import': 'no import object'}[verdict]
    with pytest.raises(SystemExit, match=expected):
        ll.write_import_lib('mss32.dll', ['_AIL_startup@0'], [212], out)


def test_import_lib_missing_wine_is_explicit(monkeypatch, tmp_path, fake_lib_tool):
    monkeypatch.setattr(ll.sys, 'platform', 'linux')
    monkeypatch.setattr(ll.shutil, 'which', lambda name: None)
    with pytest.raises(SystemExit, match='wine not found'):
        ll.write_import_lib('mss32.dll', ['_AIL_startup@0'], [212], tmp_path/'mss32.lib')


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
    def load_config(name, safeseh, extra=()):
        winmain_object(tmp_path / f"{name}.obj", safeseh)
        exe = link(root, env, tmp_path / f"{name}.exe", tmp_path / f"{name}.obj", *crt,
                   extra=extra, entry="WinMainCRTStartup")
        return ll.facts(ll.load(exe))["directories"]["load_config"]

    assert load_config("safe", True) == 72
    assert load_config("safe_no", True, ["/SAFESEH:NO"]) == 0
    assert load_config("unsafe", False) == 0
