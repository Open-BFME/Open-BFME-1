"""Correctness boundaries for the scoped publication evidence cache."""
import hashlib
import json
import subprocess
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
import sys
sys.path.insert(0, str(ROOT / "tools"))
import verification_cache as cache  # noqa: E402


def git(repo, *args):
    return subprocess.check_output(["git", "-C", str(repo), *args], text=True).strip()


def test_exact_worktree_rejects_dirty_and_untracked_inputs(tmp_path, monkeypatch):
    repo = tmp_path / "repo"
    repo.mkdir()
    (repo / "game").mkdir()
    (repo / "tools").mkdir()
    (repo / "game" / "a.cpp").write_text("int a;\n")
    (repo / "tools" / "rule.py").write_text("RULE=1\n")
    git(repo, "init", "-q")
    git(repo, "config", "user.name", "cache-test")
    git(repo, "config", "user.email", "cache-test@example.invalid")
    git(repo, "add", ".")
    subprocess.check_call(["git", "-C", str(repo), "commit", "-qm", "base"])
    commit = git(repo, "rev-parse", "HEAD")
    monkeypatch.setattr(cache, "ROOT", repo)
    monkeypatch.setattr(cache, "TREE_PATHS", ("game", "tools"))
    cache.exact_worktree(commit)

    (repo / "game" / "a.cpp").write_text("int changed;\n")
    with pytest.raises(RuntimeError, match="differs from pushed commit"):
        cache.exact_worktree(commit)
    (repo / "game" / "a.cpp").write_text("int a;\n")
    (repo / "game" / "new.h").write_text("// untracked input\n")
    with pytest.raises(RuntimeError, match="untracked verification input"):
        cache.exact_worktree(commit)


def test_payload_changes_only_for_relevant_inputs(tmp_path, monkeypatch):
    source = tmp_path / "a.cpp"
    header = tmp_path / "a.h"
    obj = tmp_path / "a.obj"
    sidecar = tmp_path / "a.deps.json"
    rules = tmp_path / "rule.py"
    source.write_text("int a;\n")
    header.write_text("#define A 1\n")
    obj.write_bytes(b"object")
    rules.write_text("RULE=1\n")
    sidecar.write_text(json.dumps({"version": 2, "deps": {str(header): "header"}}))
    row = {"name": "?a@@YAXXZ", "target_rva": "0x1000", "target_size": "4",
           "source": "a.cpp", "status": "matched", "notes": ""}
    target = b"ABCD"
    symbol_map = {"callee": [0x2000], "unrelated": [0x3000]}

    monkeypatch.setattr(cache, "ROOT", tmp_path)
    monkeypatch.setattr(cache.B, "ROOT", tmp_path)
    monkeypatch.setattr(cache.B, "row_object", lambda _row: obj)
    monkeypatch.setattr(cache.B, "_deps_sidecar", lambda _obj: sidecar)
    monkeypatch.setattr(cache.B, "read_target_bytes", lambda _rva, _size: target)
    monkeypatch.setattr(cache.B, "ledger_object_symbol", lambda _row: "f")
    monkeypatch.setattr(cache.B, "is_funclet_row", lambda *_args: False)
    monkeypatch.setattr(cache.B, "read_object_symbol_bytes",
                        lambda *_args: (b"body", [(0, cache.B.REL32, "callee")]))
    monkeypatch.setattr(cache.B, "compiler_command", lambda *_args: (["compiler.exe"], {}))
    monkeypatch.setattr(cache.B, "_cmd_fingerprint", lambda *_args: "command")
    monkeypatch.setattr(cache.B, "compile_is_current", lambda *_args, **_kw: True)
    monkeypatch.setattr(cache.B, "compile_function",
                        lambda *_args: {"bytes": target, "masked": False, "concrete": 4})
    monkeypatch.setattr(cache, "_tool_receipt", lambda _command: [["compiler.exe", "tool"]])
    monkeypatch.setattr(cache, "_rules_receipt", lambda: [["rule.py", cache._sha256(rules)]])
    monkeypatch.setattr(cache, "_live_build_marker", lambda: None)

    payload = cache._payload(row, symbol_map, {})
    original = cache._key(payload)
    assert original

    source.write_text("int changed;\n")
    assert cache._key(cache._payload(row, symbol_map, {})) != original
    source.write_text("int a;\n")
    header.write_text("#define A 2\n")
    assert cache._key(cache._payload(row, symbol_map, {})) != original
    header.write_text("#define A 1\n")

    # An unrelated ledger candidate is not part of this row's resolution.
    unrelated = dict(symbol_map)
    unrelated["unrelated"] = [0x4000]
    assert cache._key(cache._payload(row, unrelated, {})) == original
    relevant = dict(symbol_map)
    relevant["callee"] = [0x5000]
    assert cache._key(cache._payload(row, relevant, {})) != original

    monkeypatch.setattr(cache.B, "read_target_bytes", lambda _rva, _size: b"WXYZ")
    monkeypatch.setattr(cache.B, "compile_function",
                        lambda *_args: {"bytes": b"WXYZ", "masked": False, "concrete": 4})
    assert cache._key(cache._payload(row, symbol_map, {})) != original

    rules.write_text("RULE=2\n")
    assert cache._key(cache._payload(row, symbol_map, {})) != original


def test_corrupt_or_incompatible_entries_are_misses(tmp_path, monkeypatch):
    monkeypatch.setattr(cache, "CACHE", tmp_path)
    key = "a" * 64
    path = cache._entry_path(key)
    path.write_text("{")
    assert cache._load_entry(key) is None
    path.write_text(json.dumps({"version": cache.VERSION - 1, "key": key, "payload": {}}))
    assert cache._load_entry(key) is None


def test_concurrent_writers_leave_one_complete_entry(tmp_path, monkeypatch):
    from concurrent.futures import ThreadPoolExecutor

    monkeypatch.setattr(cache, "CACHE", tmp_path)
    key = "b" * 64
    payload = {"version": cache.VERSION, "resolved": hashlib.sha256(b"ok").hexdigest()}

    def write():
        cache._write_entry(key, payload)

    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(lambda _index: write(), range(12)))
    loaded = json.loads(cache._entry_path(key).read_text())
    assert loaded["key"] == key
    assert loaded["payload"] == payload
