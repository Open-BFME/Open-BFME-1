"""Execute native CRT startup with its verified default providers, never game code."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import coffar
import link_cycle as lc
from test_link_cycle_identity import TEXT, emit

ROOT = build.ROOT
D, R = lc.DIR32, lc.REL32
SOURCE = "game/Libraries/Source/CRT/StartupDefaults.c"
MESSAGES = {"_initmsg": b"initializer\n", "_mainmsg": b"WinMain\n", "_exitmsg": b"atexit\n"}


def sequence(*parts):
    body, relocs = b"", []
    for code, refs in parts:
        relocs.extend((len(body) + off, name, kind) for off, name, kind in refs)
        body += code
    return body, relocs


def store_stage(stage):
    return b"\xc7\x05" + bytes(4) + struct.pack("<I", stage), [(2, "_stage", D)]


def write_phase(name):
    code = b"\x6a" + bytes([len(MESSAGES[name])]) + b"\x68" + bytes(4)
    return code + b"\x6a\x01\xe8" + bytes(4) + b"\x83\xc4\x0c", [(3, name, D), (10, "__write", R)]


def register_callback(name):
    return b"\x68" + bytes(4) + b"\xe8" + bytes(4) + b"\x59", [(1, name, D), (6, "_atexit", R)]


def exit_failure(code):
    return b"\x6a" + bytes([code]) + b"\xe8" + bytes(4) + b"\xcc", [(3, "__exit", R)]


def require_value(symbol, expected, error):
    failure = exit_failure(error)
    compare = b"\x83\x3d" + bytes(4) + bytes([expected]) + b"\x74" + bytes([len(failure[0])])
    return sequence((compare, [(2, symbol, D)]), failure)


def driver(path, variant):
    ret = (b"\xc3", [])
    init = sequence(store_stage(1), write_phase("_initmsg"), register_callback("_validate"),
                    register_callback("_cleanup") if variant != "missing-callback" else (b"", []), ret)
    math_check = sequence((b"\x6a\x00\xe8" + bytes(4) + b"\x59\x85\xc0\x74\x08", [(3, "__matherr", R)]), exit_failure(45))
    fdiv_check = sequence((b"\xa1" + bytes(4) + b"\x8b\x0d" + bytes(4) + b"\x3b\x01\x74\x08",
                           [(1, "__adjust_fdiv", D), (7, "__imp___adjust_fdiv", D)]), exit_failure(46))
    main = sequence(require_value("_stage", 1, 31), require_value("__commode", 0, 41),
                    require_value("__newmode", 0, 42), require_value("__dowildcard", 0, 43),
                    require_value("___defaultmatherr", 1, 44), math_check, fdiv_check,
                    store_stage(2), write_phase("_mainmsg"), (b"\x33\xc0\xc2\x10\x00", []))
    cleanup = sequence(require_value("_stage", 2, 32), store_stage(3), write_phase("_exitmsg"), ret)
    validate = sequence(require_value("_stage", 3, 33), ret)
    sections, symbols = [], []
    for name, (code, relocs) in {"_initialize": init, "_WinMain@16": main, "_cleanup": cleanup, "_validate": validate}.items():
        symbols.append({"name": name, "sec": len(sections)})
        sections.append({"name": ".text", "flags": TEXT, "body": code, "relocs": relocs})
    symbols.append({"name": "_stage", "sec": len(sections)})
    sections.append({"name": ".data", "flags": 0xC0300040, "body": bytes(4)})
    data = b""
    for name, message in MESSAGES.items():
        symbols.append({"name": name, "sec": len(sections), "value": len(data)})
        data += message
    sections.append({"name": ".rdata", "flags": 0x40300040, "body": data})
    if variant != "missing-initializer":
        sections.append({"name": ".CRT$XCU", "flags": 0xC0300040, "body": bytes(4), "relocs": [(0, "_initialize", D)]})
    symbols += [{"name": name} for name in ("__write", "_atexit", "__exit", "__matherr", "__commode",
                                            "__newmode", "__dowildcard", "___defaultmatherr", "__adjust_fdiv",
                                            "__imp___adjust_fdiv")]
    path.write_bytes(emit(sections, symbols))
    return path


def test_native_crt_startup_defaults_initializers_and_termination(tmp_path):
    if sys.platform != "win32" and not shutil.which("wine"):
        pytest.skip("requires the committed MSVC/Wine toolchain")
    import pefile
    env = build.compiler_environment(build.vc71_root())
    env.pop("DISPLAY", None)
    env.pop("WAYLAND_DISPLAY", None)
    gate = subprocess.run([sys.executable, str(ROOT / "tools/build.py"), SOURCE, "_WinMainCRTStartup"],
                          cwd=ROOT, env=env, capture_output=True, text=True, timeout=120)
    (tmp_path / "provider-gate.log").write_text(gate.stdout + gate.stderr)
    assert gate.returncode == 0, gate.stdout + gate.stderr
    provider = build.obj_path(ROOT / SOURCE)
    archives = lc.runtime_libraries() + [build.vc71_root() / "Vc7/lib/RunTmChk.lib"]
    archive_hashes = {str(p): lc.sha256(p) for p in archives}
    libraries = lc.make_import_libs({"kernel32.dll": ["GetModuleHandleA@4", "GetStartupInfoA@4"]}, tmp_path) + archives
    native = dict(coffar.read_archive(archives[0]))
    duplicate = tmp_path / "original-merr.obj"
    duplicate.write_bytes(native[r"build\intel\dll_obj\merr.obj"])
    common = tmp_path / "original-adjustfd.obj"
    common.write_bytes(native[r"build\intel\dll_obj\adjustfd.obj"])
    retail_imports = {(dll.lower(), name) for dll, name, _ in lc.census._retail_import_entries()}
    manifest = {"head": lc.git("rev-parse", "HEAD"), "test_sha256": lc.sha256(Path(__file__)),
                "source_sha256": lc.sha256(ROOT / SOURCE), "provider_sha256": lc.sha256(provider),
                "archives": archive_hashes, "entry_member_sha256": hashlib.sha256(native[r"build\intel\dll_obj\crtexew.obj"]).hexdigest(),
                "cases": []}

    def link(obj, label, base, extras):
        target = tmp_path / (label + ".exe")
        command = [str(build.vc71_root() / "Vc7/bin/link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/SUBSYSTEM:CONSOLE",
                   "/MACHINE:X86", "/ENTRY:WinMainCRTStartup", "/INCREMENTAL:NO", "/OPT:NOICF", "/OPT:NOREF",
                   "/FIXED:NO", "/BASE:" + hex(base), "/OUT:" + target.name, "/MAP:" + label + ".map", obj.name]
        command += [os.path.relpath(p, tmp_path) for p in [provider, *extras, *libraries]]
        if sys.platform != "win32":
            command.insert(0, "wine")
        assert not any(arg.upper().startswith(("/FORCE", "/ALTERNATENAME")) for arg in command)
        result = subprocess.run(command, cwd=tmp_path, env=env, capture_output=True, text=True, timeout=30)
        (tmp_path / (label + ".link.log")).write_text(result.stdout + result.stderr)
        return result, target, command

    for variant in ("complete", "missing-initializer", "missing-callback", "extra-common"):
        obj = driver(tmp_path / (variant + ".obj"), variant)
        for base in (lc.BASE, lc.SHIFT_BASE):
            label = variant + "-" + hex(base)[2:]
            result, target, command = link(obj, label, base, [common] if variant == "extra-common" else [])
            assert result.returncode == 0, result.stdout + result.stderr
            assert "LNK4006" not in result.stdout and "LNK2005" not in result.stdout and "LNK4078" not in result.stdout
            image = pefile.PE(str(target))
            assert image.OPTIONAL_HEADER.ImageBase == base
            actual_imports = {(d.dll.decode("latin-1").lower(), i.name.decode("latin-1"))
                              for d in image.DIRECTORY_ENTRY_IMPORT for i in d.imports}
            assert actual_imports <= retail_imports
            map_text = (tmp_path / (label + ".map")).read_text()
            publics, _, _, owners = lc.read_map(map_text, base)
            for name in ("__matherr", "__setargv", "___defaultmatherr", "__commode", "__newmode", "__dowildcard"):
                assert owners[name] == provider.name.lower(), (name, owners[name])
            assert owners["_WinMainCRTStartup"] == "crtexew.obj"
            assert any("_WinMainCRTStartup" in line and line.rstrip().endswith("msvcrt:crtexew.obj")
                       for line in map_text.splitlines())
            assert "__adjust_fdiv" in publics
            assert publics["__matherr"] != publics["__setargv"]
            launch = [str(target)] if sys.platform == "win32" else ["wine", str(target)]
            run = subprocess.run(launch, cwd=tmp_path, env=env, capture_output=True, text=True, timeout=30)
            (tmp_path / (label + ".run.log")).write_text(run.stdout + run.stderr)
            expected = {"complete": (0, "initializer\nWinMain\natexit\n"),
                        "extra-common": (0, "initializer\nWinMain\natexit\n"),
                        "missing-initializer": (31, ""), "missing-callback": (33, "initializer\nWinMain\n")}[variant]
            assert (run.returncode, run.stdout) == expected, (variant, run.returncode, run.stdout, run.stderr)
            manifest["cases"].append({"variant": variant, "base": hex(base), "object_sha256": lc.sha256(obj),
                                      "exe_sha256": lc.sha256(target), "link_command": command,
                                      "exit": run.returncode, "stdout": run.stdout})
    result, _, _ = link(driver(tmp_path / "duplicate.obj", "complete"), "duplicate-merr", lc.BASE, [duplicate])
    assert result.returncode != 0 and "LNK2005" in result.stdout
    assert archive_hashes == {str(p): lc.sha256(p) for p in archives}
    (tmp_path / "manifest.json").write_text(json.dumps(manifest, indent=2))
