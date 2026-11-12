"""Link-only controls for the original ATL cookie source and its CRT consumer."""
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import link_cycle

SOURCE = build.ROOT / "game/Libraries/Source/CRT/VS2003/security_cookie_init.cpp"
DEFAULT_COOKIE = bytes.fromhex("4ee640bb")


@pytest.fixture
def cookie_objects(tmp_path):
    if sys.platform != "win32" and not shutil.which("wine"):
        pytest.skip("requires committed MSVC/Wine toolchain")
    root = build.vc71_root()
    env = build.compiler_environment(root)

    def compile_source(source, obj):
        command, compiler_env = build.compiler_command(source, obj)
        obj.with_suffix(".compile-command.json").write_text(json.dumps(command, indent=2) + "\n")
        result = subprocess.run(command, env=compiler_env, capture_output=True, text=True,
                                errors="replace", timeout=30)
        obj.with_suffix(".compile.log").write_text(result.stdout + result.stderr)
        assert result.returncode == 0, result.stdout + result.stderr
        return obj

    provider = compile_source(SOURCE, tmp_path / "provider.obj")
    driver_source = tmp_path / "driver.cpp"
    driver_source.write_text(
        '// cl: /DNDEBUG /MD\n'
        'extern "C" unsigned long __security_cookie;\n'
        'extern "C" void __cdecl __security_init_cookie();\n'
        'extern "C" void __fastcall __security_check_cookie(unsigned long);\n'
        'extern "C" __declspec(dllexport) unsigned long *cookie_address() {\n'
        ' return &__security_cookie; }\n'
        'extern "C" __declspec(dllexport) void cookie_initialize() {\n'
        ' __security_init_cookie(); }\n'
        'extern "C" __declspec(dllexport) void cookie_check(unsigned long value) {\n'
        ' __security_check_cookie(value); }\n')
    driver = compile_source(driver_source, tmp_path / "driver.obj")
    duplicate_source = tmp_path / "duplicate.cpp"
    duplicate_source.write_text(
        '// cl: /DNDEBUG /MD\n'
        'extern "C" { unsigned long __security_cookie = 0xBB40E64E; }\n')
    duplicate = compile_source(duplicate_source, tmp_path / "duplicate.obj")
    libraries = link_cycle.runtime_libraries() + [root / "Vc7/PlatformSDK/Lib/Kernel32.Lib"]
    original = {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in libraries}

    def link(label, objects, base=0x400000, runtime=True):
        output = tmp_path / (label + ".dll")
        command = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/DLL", "/NOENTRY",
                   "/NODEFAULTLIB", "/MACHINE:X86", "/OPT:NOREF", "/OPT:NOICF",
                   f"/BASE:{base}", "/OUT:" + build.wine_path(output),
                   "/MAP:" + build.wine_path(output.with_suffix(".map"))]
        command += [build.wine_path(p) for p in objects]
        command += [build.wine_path(p) for p in libraries] if runtime else []
        if sys.platform != "win32":
            command.insert(0, "wine")
        output.with_suffix(".link-command.json").write_text(json.dumps(command, indent=2) + "\n")
        result = subprocess.run(command, env=env, capture_output=True, text=True,
                                errors="replace", timeout=30)
        output.with_suffix(".link.log").write_text(result.stdout + result.stderr)
        assert not any(arg.upper().startswith(("/FORCE", "/ALTERNATENAME")) for arg in command)
        return result, output

    yield provider, driver, duplicate, link
    assert original == {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in libraries}


@pytest.mark.parametrize("base", [0x400000, 0x10000000])
def test_security_cookie_source_owns_data_and_native_crt_consumer(cookie_objects, base):
    import pefile
    provider, driver, _, link = cookie_objects
    result, output = link(f"positive-{base:x}", [provider, driver], base)
    assert result.returncode == 0, result.stdout + result.stderr
    mapped = output.with_suffix(".map").read_text(errors="replace")
    cookie = next(line for line in mapped.splitlines() if re.search(r"\s___security_cookie\s", line))
    initializer = next(line for line in mapped.splitlines() if re.search(r"\s___security_init_cookie\s", line))
    check = next(line for line in mapped.splitlines() if "@__security_check_cookie@4" in line)
    assert "provider.obj" in cookie and "provider.obj" in initializer
    assert "secchk.obj" in check
    address = int(cookie.split()[2], 16)
    pe = pefile.PE(str(output))
    assert pe.get_data(address - base, 4) == DEFAULT_COOKIE
    assert pe.OPTIONAL_HEADER.ImageBase == base
    assert pe.OPTIONAL_HEADER.AddressOfEntryPoint == 0


def test_security_cookie_requires_an_explicit_provider(cookie_objects):
    _, driver, _, link = cookie_objects
    result, _ = link("missing", [driver], runtime=False)
    assert result.returncode != 0
    assert "__security_cookie" in result.stdout + result.stderr
    assert "__security_init_cookie" in result.stdout + result.stderr


def test_published_native_crt_already_provides_the_symbols(cookie_objects):
    _, driver, _, link = cookie_objects
    result, output = link("archive-control", [driver])
    assert result.returncode == 0, result.stdout + result.stderr
    mapped = output.with_suffix(".map").read_text(errors="replace")
    cookie = next(line for line in mapped.splitlines() if re.search(r"\s___security_cookie\s", line))
    initializer = next(line for line in mapped.splitlines() if re.search(r"\s___security_init_cookie\s", line))
    assert "seccook.obj" in cookie and "seccinit.obj" in initializer
    assert "provider.obj" not in cookie + initializer


def test_security_cookie_duplicate_strong_owner_is_rejected(cookie_objects):
    provider, driver, duplicate, link = cookie_objects
    result, _ = link("duplicate", [provider, driver, duplicate])
    assert result.returncode != 0
    assert "LNK2005" in result.stdout + result.stderr
    assert "__security_cookie" in result.stdout + result.stderr
