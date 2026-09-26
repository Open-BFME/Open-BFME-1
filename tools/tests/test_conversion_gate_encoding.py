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
    source = tmp_path / "game/GameEngine/Encoding.cpp"
    source.parent.mkdir(parents=True)
    body = b"__declspec(naked) void f() { __asm { __emit 0xC3 } }\n" if lift else b"int f() { return 1; }\n"
    source.write_bytes(comment + body)
    git("add", "game/GameEngine/Encoding.cpp")
    monkeypatch.chdir(tmp_path)

    failures = conversion_gate.added_lift_lines("HEAD", ":")
    if lift:
        assert len(failures) == 1
        assert failures[0][0] == "game/GameEngine/Encoding.cpp"
        assert "__emit" in failures[0][1]
    else:
        assert failures == []


def test_a_comment_mentioning_emit_is_not_a_lift():
    """Rule A scans added lines for __emit. It fired on a merge whose only
    __emit was in a line explaining why a dump was being LEFT ALONE -- which
    reads as "you added a naked body" and sends the author hunting one that is
    not there. Prose is not code."""
    gate = _gate()
    assert not _flags(gate, "// leaving tryToIgnite's __emit dump alone")
    assert not _flags(gate, "\tstartBurning();  // not the __emit body")
    assert not _flags(gate, "/* __declspec(naked) */ int x;")


def test_a_real_lift_is_still_caught_beside_a_comment():
    gate = _gate()
    assert _flags(gate, "\t__emit 0x90;")
    assert _flags(gate, "\t__emit 0x90;  // one byte")
    assert _flags(gate, "__declspec(naked) void f(void)")


def test_an_unterminated_block_comment_still_scans():
    """Only whole // tails and complete /* */ pairs are stripped, so the scan
    cannot be talked out of a real lift by an unclosed comment."""
    gate = _gate()
    assert _flags(gate, "/* opening a block and then __emit 0x90")


def _gate():
    import importlib.util
    from pathlib import Path
    path = Path(__file__).resolve().parents[1] / "conversion_gate.py"
    spec = importlib.util.spec_from_file_location("conversion_gate_under_test", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _flags(gate, line):
    return gate.is_lift_line(line)


def test_the_scanner_goes_through_is_lift_line():
    """Testing is_lift_line proves nothing unless added_lift_lines calls it --
    an earlier version of this test passed with the fix reverted, because the
    scanner still matched the raw line while the helper sat unused."""
    import inspect
    gate = _gate()
    assert "is_lift_line" in inspect.getsource(gate.added_lift_lines)
