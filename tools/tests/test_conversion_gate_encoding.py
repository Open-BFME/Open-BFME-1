"""UTF-8 or legacy comments must not crash the conversion-direction gate."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import conversion_gate


@pytest.mark.parametrize("comment", ["// Unicode quote: \u201d\n".encode("utf-8"), b"// Legacy comment: \xe9\n"])
@pytest.mark.parametrize("lift", [False, True])
def test_staged_direction_scan_handles_comment_encoding(tmp_path, monkeypatch, comment, lift):
    def git(*args):
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("-c", "user.name=Gate fixture", "-c", "user.email=fixture@example.invalid",
        "commit", "--allow-empty", "-qm", "Fixture baseline")
    source = tmp_path / "Code/GameEngine/Encoding.cpp"
    source.parent.mkdir(parents=True)
    body = b"__declspec(naked) void f() { __asm { __emit 0xC3 } }\n" if lift else b"int f() { return 1; }\n"
    source.write_bytes(comment + body)
    git("add", "Code/GameEngine/Encoding.cpp")
    monkeypatch.chdir(tmp_path)

    failures = conversion_gate.added_lift_lines("HEAD", ":")
    if lift:
        assert len(failures) == 1
        assert failures[0][0] == "Code/GameEngine/Encoding.cpp"
        assert "__emit" in failures[0][1]
    else:
        assert failures == []
