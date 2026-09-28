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
    monkeypatch.setattr(cache, "_tool_receipt", lambda _command, *_args: [["compiler.exe", "tool"]])
    monkeypatch.setattr(cache, "_rules_receipt", lambda *_args: [["rule.py", cache._sha256(rules)]])
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
    header.unlink()
    assert cache._key(cache._payload(row, symbol_map, {})) is None
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


def test_one_shot_boundary_requests_disable_reuse(monkeypatch):
    assert not cache._boundary_request_active()
    monkeypatch.setenv("ADDMATCH_BOUNDARY_RVA", "0x1000")
    assert cache._boundary_request_active()


def test_record_skips_rows_whose_evidence_cannot_be_keyed(tmp_path, monkeypatch):
    # The build gate has already verified the row; evidence that cannot be keyed
    # (uncacheable dependencies) must be a later miss, not a failed push.
    manifest = tmp_path / "manifest.json"
    row = {"name": "?a@@YAXXZ", "target_rva": "0x1000", "target_size": "4",
           "source": "a.cpp", "status": "matched", "notes": ""}
    manifest.write_text(json.dumps({"version": cache.VERSION, "commit": "c",
                                    "rows": [row], "hits": [], "selectors": []}))
    written = []
    monkeypatch.setattr(cache, "exact_worktree", lambda _commit: None)
    monkeypatch.setattr(cache, "_live_build_marker", lambda: None)
    monkeypatch.setattr(cache.B, "load_symbol_map", lambda: {})
    monkeypatch.setattr(cache, "_payload", lambda *_args, **_kwargs: None)
    for check in ('verify_baseline', 'verify_string_refs', 'verify_constant_refs',
                  'verify_dir32_addresses', 'verify_dir32_consistency'):
        monkeypatch.setattr(cache.B, check, lambda *a, **kw: None)
    monkeypatch.setattr(cache.B, 'row_object', lambda _: tmp_path / 'obj')
    monkeypatch.setattr(cache.B, 'read_target_bytes', lambda *a: b'ABCD')
    monkeypatch.setattr(cache.B, 'compile_function', lambda *a: {'bytes': b'ABCD', 'masked': False, 'concrete': 4})
    monkeypatch.setattr(cache, "_write_entry", lambda *args: written.append(args))
    assert cache.main(["record", "--manifest", str(manifest)]) == 0
    assert written == []


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


@pytest.mark.parametrize('payload', [None, [], 1, 'bad', {'version': 1}, {}])
def test_malformed_nested_receipt_is_a_miss(tmp_path, monkeypatch, payload):
    monkeypatch.setattr(cache, 'CACHE', tmp_path)
    key = 'c' * 64
    cache._entry_path(key).write_text(json.dumps({'version': cache.VERSION, 'key': key, 'payload': payload}))
    assert cache._load_entry(key) is None


def test_hits_keep_all_rows_in_gate(tmp_path, monkeypatch, capsys):
    row = {'name': '?f', 'target_rva': '0x10', 'target_size': '1', 'source': 'game/a.cpp'}
    monkeypatch.setattr(cache, 'exact_worktree', lambda _: None)
    monkeypatch.setattr(cache, '_live_build_marker', lambda: None)
    monkeypatch.setattr(cache, '_rows', lambda: [row])
    monkeypatch.setattr(cache, '_rules_receipt', lambda *a: [])
    monkeypatch.setattr(cache.B, 'load_symbol_map', lambda: {})
    monkeypatch.setattr(cache, '_payload', lambda *a, **kw: {'version': cache.VERSION, 'rules': [], 'resolved': 'x'})
    monkeypatch.setattr(cache, '_load_entry', lambda _: {'payload': {'version': cache.VERSION, 'rules': [], 'resolved': 'x'}})
    manifest = tmp_path / 'manifest'
    cache.prepare('sha', ['game/a.cpp'], manifest)
    assert cache._row_selector(row) in capsys.readouterr().out
    assert json.loads(manifest.read_text())['rows'] == [row]


@pytest.fixture
def record_fixture(tmp_path, monkeypatch):
    rows = [{'name': name, 'target_rva': hex(rva), 'target_size': '4', 'source': 'game/a.cpp'}
            for name, rva in [('one', 16), ('two', 32)]]
    path = tmp_path / 'manifest'
    path.write_text(json.dumps({'version': cache.VERSION, 'commit': 'sha', 'rows': rows, 'hits': ['one', 'two']}))
    monkeypatch.setattr(cache, 'exact_worktree', lambda _: None)
    monkeypatch.setattr(cache, '_live_build_marker', lambda: None)
    monkeypatch.setattr(cache.B, 'load_symbol_map', lambda: {})
    monkeypatch.setattr(cache.B, 'row_object', lambda _: tmp_path / 'obj')
    monkeypatch.setattr(cache.B, 'read_target_bytes', lambda *a: b'ABCD')
    monkeypatch.setattr(cache.B, 'compile_function', lambda *a: {'bytes': b'ABCD', 'masked': False, 'concrete': 4})
    monkeypatch.setattr(cache, '_payload', lambda *a, **kw: None)
    for name in ('verify_baseline', 'verify_string_refs', 'verify_constant_refs', 'verify_dir32_addresses', 'verify_dir32_consistency'):
        monkeypatch.setattr(cache.B, name, lambda *a, **kw: None)
    return path, rows


@pytest.mark.parametrize('check', ['verify_baseline', 'verify_string_refs', 'verify_constant_refs', 'verify_dir32_addresses', 'verify_dir32_consistency'])
def test_receipt_hits_cannot_skip_ancillary_failure(record_fixture, monkeypatch, check):
    path, rows = record_fixture
    def fail(*args, **kwargs):
        if args:
            assert args[0] == rows
        raise SystemExit('fixture ancillary failure')
    monkeypatch.setattr(cache.B, check, fail)
    with pytest.raises(SystemExit, match='ancillary failure'):
        cache.record(path)


def test_unrecordable_evidence_cannot_hide_byte_failure(record_fixture, monkeypatch):
    path, _ = record_fixture
    monkeypatch.setattr(cache.B, 'compile_function', lambda *a: {'bytes': b'BAD!', 'masked': False, 'concrete': 4})
    with pytest.raises(RuntimeError, match='evidence failed'):
        cache.record(path)


def test_combined_rows_detect_new_dir32_conflict(record_fixture, tmp_path, monkeypatch):
    path, rows = record_fixture
    # Exercise the real consistency implementation: each row alone agrees;
    # combined receipts must not hide the disagreement on an unrecorded global.
    import importlib.util
    spec = importlib.util.spec_from_file_location('audit_build', ROOT / 'tools/build.py')
    real = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(real)
    whitelist = tmp_path / 'whitelist'
    whitelist.write_text('')
    monkeypatch.setattr(real, 'ROOT', tmp_path)
    monkeypatch.setattr(real, 'DIR32_WHITELIST', whitelist)
    monkeypatch.setattr(real, 'read_dir32_addresses', lambda: {})
    monkeypatch.setattr(real, 'read_dir32_whitelist', lambda: set())
    monkeypatch.setattr(real, 'propose_dir32_addresses', lambda *a, **kw: None)
    monkeypatch.setattr(real, 'dir32_references', lambda selected: [(r, 0, 'global', int(r['target_rva'], 16)) for r in selected])
    for row in rows:
        real.verify_dir32_consistency([row])
    monkeypatch.setattr(cache.B, 'verify_dir32_consistency', real.verify_dir32_consistency)
    with pytest.raises(SystemExit):
        cache.record(path)


@pytest.mark.parametrize('meta', [None, [], 3, {'deps': None}, {'version': 2, 'deps': []}, {'version': 2, 'deps': {'a': []}}, {'version': 2, 'deps': {}, 'search_roots': [None]}])
def test_malformed_object_sidecars_are_misses(tmp_path, monkeypatch, meta):
    source, obj = tmp_path / 'a.cpp', tmp_path / 'a.obj'
    source.write_text('int a;')
    obj.write_bytes(b'obj')
    sidecar = tmp_path / 'deps'
    sidecar.write_text(json.dumps(meta))
    monkeypatch.setattr(cache.B, '_deps_sidecar', lambda _: sidecar)
    assert cache.B.compile_is_current(source, obj, check_command=False) is False


def test_concurrent_object_edit_discards_evidence(record_fixture, tmp_path, monkeypatch):
    path, rows = record_fixture
    obj = tmp_path / 'obj'
    obj.write_bytes(b'before')
    monkeypatch.setattr(cache.B, 'verify_constant_refs', lambda _: obj.write_bytes(b'after'))
    with pytest.raises(RuntimeError, match='inputs changed'):
        cache.record(path)


def test_fingerprints_share_hashes_only_within_invocation(tmp_path, monkeypatch):
    source = tmp_path / 'source'
    source.write_bytes(b'initial')
    calls = []
    original = cache._sha256
    def digest(path):
        calls.append(path)
        return original(path)
    monkeypatch.setattr(cache, '_sha256', digest)
    context = cache.Fingerprints()
    assert context.file(source) == context.file(source)
    assert len(calls) == 1
    context.validate()
    assert len(calls) == 2  # independent final content check
    cache.Fingerprints().file(source)
    assert len(calls) == 3  # no reuse across invocations
    source.write_bytes(b'changed')
    with pytest.raises(RuntimeError, match='input changed'):
        context.validate()


def test_rule_and_tool_fingerprints_are_shared_per_configuration(monkeypatch):
    calls = []
    monkeypatch.setattr(cache, '_rules_receipt', lambda *a: calls.append('rules') or [])
    monkeypatch.setattr(cache, '_tool_receipt', lambda cmd, *a: calls.append(tuple(cmd)) or [])
    context = cache.Fingerprints()
    for _ in range(4):
        context.rules()
        context.toolchain(['compiler', 'config-a'])
    context.toolchain(['compiler', 'config-b'])
    assert calls == ['rules', ('compiler', 'config-a'), ('compiler', 'config-b')]


def test_scoped_consistency_does_not_publish_partial_address_proposal(record_fixture, monkeypatch):
    path, rows = record_fixture
    calls = []
    def consistency(selected, *, propose):
        assert selected == rows
        calls.append(propose)
    monkeypatch.setattr(cache.B, 'verify_dir32_consistency', consistency)
    cache.record(path)
    assert calls == [False]


def test_nul_dependency_path_is_a_cache_miss(tmp_path, monkeypatch):
    source, obj = tmp_path / 'body.asm', tmp_path / 'body.obj'
    source.write_text('ret\n')
    obj.write_bytes(b'object')
    sidecar = cache.B._deps_sidecar(obj)
    sidecar.write_text(json.dumps({'version': 2, 'source': cache.B._hash_file(str(source)),
                                  'deps': {'invalid\0path': 'digest'}}))
    assert cache.B.compile_is_current(source, obj, check_command=False) is False
    assert cache._read_meta(obj) is None
