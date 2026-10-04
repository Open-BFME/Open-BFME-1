"""Component linker arguments without requiring the compiler or Wine."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import component_link as component  # noqa: E402


@pytest.mark.parametrize("windows", [False, True])
def test_crt_paths_are_native_or_wine_mapped_without_losing_spaces(tmp_path, monkeypatch, windows):
    root = tmp_path / "repository"
    out = root / "build output"
    out.mkdir(parents=True)
    # Also cover a supported toolchain outside the checkout; rel(lib) cannot
    # express this case and an unconverted /tmp/... path is a linker option.
    vc = tmp_path / "toolchain with spaces"
    monkeypatch.setattr(component, "ROOT", root)
    monkeypatch.setattr(component.sys, "platform", "win32" if windows else "linux")
    env = {"fixture": "environment"}
    monkeypatch.setattr(component, "toolchain", lambda: (vc, env))
    mapped = []
    def wine_path(path):
        mapped.append(path)
        return "Z:" + str(path).replace("/", "\\")
    monkeypatch.setattr(component.build, "wine_path", wine_path)
    observed = []
    def run(command, **kwargs):
        observed.append((command, kwargs))
        return subprocess.CompletedProcess(command, 0, "fixture stdout", "fixture stderr")
    monkeypatch.setattr(component.subprocess, "run", run)
    driver, obj = out / "driver with spaces.obj", out / "object with spaces.obj"
    result = component.link([obj], driver, out)
    command, kwargs = observed[0]
    libs = [vc / "Vc7" / "lib" / name for name in ("msvcrt.lib", "kernel32.lib")]
    assert mapped == ([] if windows else libs)
    expected = [str(lib) if windows else "Z:" + str(lib).replace("/", "\\") for lib in libs]
    assert command[-2:] == expected
    assert command[:2] == ([str(vc / "Vc7" / "bin" / "link.exe"), "/NOLOGO"] if windows
                           else ["wine", str(vc / "Vc7" / "bin" / "link.exe")])
    assert command[-4:-2] == ["build output/driver with spaces.obj", "build output/object with spaces.obj"]
    assert not any(arg.upper().startswith(("/FORCE", "/ALTERNATENAME")) for arg in command)
    assert kwargs["cwd"] == root and kwargs["env"] is env
    assert result[:2] == (0, "fixture stdoutfixture stderr")
    assert (out / "link.log").read_text() == result[1]
