"""Source-declared compiler flags use the checkout's toolchain paths."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def test_short_vs2003_include_roots_resolve_to_installed_toolchain(tmp_path, monkeypatch):
    toolchain = tmp_path / "toolchain"
    vc7 = toolchain / "Vc7"
    atlmfc = vc7 / "atlmfc" / "include"
    platformsdk = vc7 / "PlatformSDK" / "Include"
    atlmfc.mkdir(parents=True)
    platformsdk.mkdir(parents=True)

    source = tmp_path / "Test.cpp"
    source.write_text(
        "// cl: /DNDEBUG /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/"
        "Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/"
        "MICR~2RR.NET/Vc7/PLAT~MIB/Include\n"
    )
    monkeypatch.setattr(build, "vc71_root", lambda: toolchain)

    assert build.source_extra_flags(source) == [
        "-DNDEBUG",
        "-I" + str(atlmfc),
        "-I" + str(platformsdk),
    ]


def test_stlport_marker_after_long_compiler_flags(tmp_path):
    source = tmp_path / "LongFlags.cpp"
    source.write_text("// cl: " + "-Iinputs/reference/very/long/path " * 70 + "\n// stlport\n")
    assert build.source_needs_stlport(source)
