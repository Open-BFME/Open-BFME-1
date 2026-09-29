"""zlib links from the census's own objects without /FORCE and runs its API tests."""
import os
import shutil
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import component_link  # noqa: E402

VC71 = Path(os.environ.get("VC71_ROOT", build.DEFAULT_VC71_ROOT)) / "Vc7" / "bin" / "link.exe"

pytestmark = [
    pytest.mark.skipif(not build.EXE.exists(), reason="retail baseline not present"),
    pytest.mark.skipif(not VC71.exists(), reason="MSVC 7.1 toolchain not present"),
    pytest.mark.skipif(sys.platform != "win32" and shutil.which("wine") is None, reason="wine not installed"),
]


def test_zlib_links_runs_and_matches_retail(capsys):
    assert component_link.main(["zlib"]) == 0
    out = capsys.readouterr().out
    assert "COMDATs with differing copies across the linked objects: 0" in out
    assert "imports read through retail's own IAT slot: 2 of 2 references" in out
    assert "component zlib: PASS" in out


def test_lzhl_takes_retails_operator_new_not_the_crts(capsys):
    assert component_link.main(["lzhl"]) == 0
    out = capsys.readouterr().out
    assert "TEST DOUBLE in driver" in out
    assert "component lzhl: PASS" in out
