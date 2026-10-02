"""Parent-only mocked conversion; real commands, fingerprints and spawn checks."""
import concurrent.futures
import json
import multiprocessing
import os
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build

_INIT = build._stale_paths_init


def converted(path):
    return 'Z:\\' + str(path).lstrip('/').replace('/', '\\')


def forbidden_conversion(*args, **kwargs):
    raise AssertionError('worker attempted an external path conversion')


def configure(root):
    build.ROOT = Path(root)
    build.STLPORT_OVERLAY = build.ROOT / 'inputs/reference/shims/stlport_bfme'
    build._SWEEP_INCLUDE_DIRS = []
    build.shutil.which = lambda name: '/mock/' + name


def observed_init(paths):
    configure(os.environ['STALE_PATH_FIXTURE_ROOT'])
    build.subprocess.check_output = forbidden_conversion
    _INIT(paths)


def recipe(source, output):
    command, env = build.compiler_command(source, output)
    return command, {k: env.get(k) for k in ('INCLUDE', 'LIB', 'WINEPATH')}, build._cmd_fingerprint(command, env)


def observed_recipe(pair):
    assert multiprocessing.get_start_method() == 'spawn'
    return recipe(*pair)


@pytest.fixture
def fixture_tree(tmp_path, monkeypatch):
    if os.name == "nt":
        pytest.skip("Wine path-conversion fixture is POSIX-specific")
    monkeypatch.setattr(build, "ROOT", build.ROOT)
    monkeypatch.setattr(build, "STLPORT_OVERLAY", build.STLPORT_OVERLAY)
    monkeypatch.setattr(build, "_SWEEP_INCLUDE_DIRS", build._SWEEP_INCLUDE_DIRS)
    monkeypatch.setattr(build.shutil, "which", build.shutil.which)
    configure(tmp_path)
    monkeypatch.setenv('STALE_PATH_FIXTURE_ROOT', str(tmp_path))
    monkeypatch.setenv('VC71_ROOT', str(tmp_path / 'toolchain/install/vc71'))
    monkeypatch.setenv('WINEPREFIX', str(tmp_path / 'prefix'))
    for key in ('CL', '_CL_', 'STLPORT_ROOT'):
        monkeypatch.delenv(key, raising=False)
    toolchain = Path(os.environ['VC71_ROOT'])
    for part in ('Vc7/bin', 'Vc7/include', 'Vc7/lib', 'Common7/IDE'):
        (toolchain / part).mkdir(parents=True)
    (toolchain / 'Vc7/bin/cl.exe').touch()
    (toolchain / 'Vc7/bin/ml.exe').touch()
    (tmp_path / 'inputs/vendor/stlport/src').mkdir(parents=True)
    (tmp_path / 'inputs/vendor/stlport/list').touch()
    (tmp_path / 'inputs/vendor/nbench').mkdir(parents=True)
    (tmp_path / 'inputs/vendor/nbench/nbench1.c').touch()
    build.STLPORT_OVERLAY.mkdir(parents=True)
    drives = tmp_path / 'prefix/dosdevices'
    drives.mkdir(parents=True)
    (drives / 'z:').symlink_to('/')
    calls = []
    def conversion(args, **kwargs):
        assert os.getpid() == parent
        assert args[:2] == ['/mock/winepath', '-w']
        calls.append(args[2])
        return converted(args[2]) + '\n'
    parent = os.getpid()
    monkeypatch.setattr(build.subprocess, 'check_output', conversion)
    monkeypatch.setattr(build, '_WINE_PATH_CACHE', {})
    # configure() changes these globals explicitly in the spawned process too.
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    yield tmp_path, calls


def write_receipt(source, output):
    source.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(b'object fixture, never executed')
    command, env = build.compiler_command(source, output)
    roots = build.search_inventory(source, command, env)
    assert roots is not None
    build._deps_sidecar(output).write_text(json.dumps({
        'version': 2, 'deps': {}, 'source': build._hash_file(str(source)),
        'cmd': build._cmd_fingerprint(command, env), 'inventory': roots,
    }))


def test_real_commands_mixed_sources_and_spawn_currentness(fixture_tree, monkeypatch):
    root, calls = fixture_tree
    specs = [('game/plain.cpp', 'int x;\n'),
             ('game/stl.cpp', '// stlport\nint x;\n'),
             ('game/optout.cpp', '// stlport\n// stlport-range-errors: vendored\nint x;\n'),
             ('game/Libraries/Source/Benchmark/bench.cpp', 'int x;\n'),
             ('game/leaf.asm', 'end\n')]
    pairs = []
    for relative, text in specs:
        source = root / relative
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(text)
        output = source.with_suffix('.obj')
        write_receipt(source, output)
        pairs.append((source, output))
    # Directory inventories must be recorded after all fixture inputs exist.
    for pair in pairs:
        write_receipt(*pair)
    serial_recipes = [recipe(*pair) for pair in pairs]
    build._WINE_PATH_CACHE.clear()
    calls.clear()
    paths = build._warm_stale_paths(pairs)
    assert len(calls) == len(set(calls)) == len(paths)
    assert str(root) in paths
    assert str(build.STLPORT_OVERLAY) in paths
    assert str(root / 'inputs/vendor/nbench') in paths
    assert build._cmd_fingerprint(*build.compiler_command(*pairs[0])) == serial_recipes[0][2]
    with concurrent.futures.ProcessPoolExecutor(2, mp_context=multiprocessing.get_context('spawn'),
            initializer=observed_init, initargs=(paths,)) as pool:
        assert list(pool.map(observed_recipe, pairs)) == serial_recipes
        assert list(pool.map(build._stale_chunk, [[pair] for pair in pairs])) == [[], [], [], [], []]
    # Use the actual stale_sources dispatch (200-pair threshold) and initializer.
    monkeypatch.setattr(build, '_stale_paths_init', observed_init)
    repeated = pairs * 40
    outputs = dict(repeated)
    assert build.stale_sources([p[0] for p in repeated], outputs, workers=2) == []
    pairs[0][0].write_text('int changed;\n')
    serial = build._stale_chunk(pairs)
    assert serial == [pairs[0][0]]
    parallel = build.stale_sources([p[0] for p in repeated], outputs, workers=2)
    expected = [s for group in [repeated[::2], repeated[1::2]] for s, _ in group if s == pairs[0][0]]
    assert parallel == expected


@pytest.mark.parametrize('kind', ['missing_object', 'missing_sidecar', 'json', 'type', 'deps',
    'source', 'retry_type', 'retry_value', 'version', 'legacy_deps', 'legacy_asm_include', 'retry_changed'])
def test_preflight_false_never_discovers_tools(tmp_path, monkeypatch, kind):
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    monkeypatch.setattr(build, '_SWEEP_INCLUDE_DIRS', [])
    source = tmp_path / ('leaf.asm' if kind == 'legacy_asm_include' else 'leaf.cpp')
    source.write_text('include native.inc\n' if kind == 'legacy_asm_include' else 'int x;\n')
    output = source.with_suffix('.obj')
    if kind != 'missing_object': output.touch()
    meta = {'version': 2, 'source': 'hash', 'deps': {}}
    if kind == 'type': meta = []
    if kind == 'deps': meta['deps'] = {'bad\0path': 'hash'}
    if kind == 'source': meta['source'] = ''
    if kind == 'retry_type': meta['retry_dirs'] = 4
    if kind == 'retry_value': meta['retry_dirs'] = [4]
    if kind == 'version': meta['version'] = 3
    if kind == 'legacy_deps': meta = {'source': 'hash', 'deps': {'a.h': 'hash'}}
    if kind == 'legacy_asm_include': meta = {'source': 'hash', 'deps': {}}
    if kind == 'retry_changed': meta['retry_dirs'] = ['missing']
    if kind != 'missing_sidecar':
        build._deps_sidecar(output).write_text('{' if kind == 'json' else json.dumps(meta))
    monkeypatch.setattr(build, 'compiler_command', forbidden_conversion)
    monkeypatch.setattr(build, 'wine_path', forbidden_conversion)
    assert build._compile_receipt_preflight(source, output) is None
    assert not build.compile_is_current(source, output)
    build._warm_stale_paths([(source, output)])


def test_parent_conversion_failure_is_not_hidden(fixture_tree, monkeypatch):
    root, _ = fixture_tree
    source = root / 'leaf.cpp'; source.write_text('int x;\n')
    output = source.with_suffix('.obj'); output.touch()
    build._deps_sidecar(output).write_text(json.dumps({'version': 2, 'source': 'hash', 'deps': {}}))
    monkeypatch.setattr(build.subprocess, 'check_output', lambda *a, **k: (_ for _ in ()).throw(subprocess.CalledProcessError(1, a[0])))
    with pytest.raises(subprocess.CalledProcessError): build._warm_stale_paths([(source, output)])


@pytest.mark.parametrize('paths', [None, [], {'host': ''}, {'host': 'unix'}, {1: 'Z:\\a'}])
def test_initializer_rejects_invalid_snapshot(paths):
    with pytest.raises(SystemExit, match='invalid parent'): build._stale_paths_init(paths)


def test_unknown_path_uses_ordinary_conversion_failure(fixture_tree, monkeypatch):
    root, _ = fixture_tree
    build._stale_paths_init({'relative/host': 'Z:\\existing'})
    monkeypatch.setattr(build.subprocess, 'check_output', forbidden_conversion)
    assert build.wine_path('relative/host') == 'Z:\\existing'
    with pytest.raises(AssertionError, match='external'): build.wine_path(root / 'new')


def test_all_cold_receipts_spawn_without_tool_requirement(fixture_tree, monkeypatch):
    root, _ = fixture_tree
    pairs = [(root / f'cold{i}.cpp', root / f'cold{i}.obj') for i in range(200)]
    # No object exists, and no compiler/tool discovery is permitted in parent.
    monkeypatch.setattr(build, 'compiler_command', forbidden_conversion)
    monkeypatch.setattr(build, 'wine_path', forbidden_conversion)
    monkeypatch.setattr(build, '_stale_paths_init', observed_init)
    assert build.stale_sources([s for s, _ in pairs], dict(pairs), workers=2) == [
        s for group in [pairs[::2], pairs[1::2]] for s, _ in group]


@pytest.mark.parametrize('change', ['flags', 'header', 'inventory', 'drive', 'receipt'])
def test_warming_does_not_replace_live_guard_checks(fixture_tree, change):
    root, _ = fixture_tree
    source = root / 'game/live.cpp'; source.parent.mkdir(); source.write_text('#include "native.h"\nint x;\n')
    header = source.parent / 'native.h'; header.write_text('#define X 1\n')
    output = root / 'build/live.obj'; output.parent.mkdir(); write_receipt(source, output)
    sidecar = build._deps_sidecar(output)
    meta = json.loads(sidecar.read_text()); meta['deps'] = {str(header): build._hash_file(str(header))}
    sidecar.write_text(json.dumps(meta))
    assert build.compile_is_current(source, output)
    paths = build._warm_stale_paths([(source, output)])
    build._WINE_PATH_CACHE.clear(); build._stale_paths_init(paths)
    if change == 'flags': source.write_text('// cl: /Od\n' + source.read_text())
    if change == 'header': header.write_text('#define X 2\n')
    if change == 'inventory': (source.parent / 'extra.h').write_text('#define EXTRA 1\n')
    if change == 'drive':
        drive = root / 'prefix/dosdevices/z:'; drive.unlink(); drive.symlink_to('/tmp')
    if change == 'receipt': sidecar.write_text('{')
    assert not build.compile_is_current(source, output)
    with concurrent.futures.ProcessPoolExecutor(1, mp_context=multiprocessing.get_context("spawn"),
            initializer=observed_init, initargs=(paths,)) as pool:
        assert list(pool.map(build._stale_chunk, [[(source, output)]])) == [[source]]


def test_overlay_optout_changed_after_warming_is_stale(fixture_tree):
    root, _ = fixture_tree
    source = root / 'game/overlay.cpp'; source.parent.mkdir(); source.write_text('// stlport\nint x;\n')
    output = root / 'build/overlay.obj'; output.parent.mkdir(); write_receipt(source, output)
    assert build.compile_is_current(source, output)
    before = recipe(source, output)
    build._warm_stale_paths([(source, output)])
    source.write_text('// stlport\n// stlport-range-errors: vendored\nint x;\n')
    assert recipe(source, output)[1]['INCLUDE'] != before[1]['INCLUDE']
    assert not build.compile_is_current(source, output)


@pytest.mark.parametrize('hidden', ['// cl: /FIhidden.h\n', '#include "hidden.h"\n'])
def test_legacy_headerfree_actual_command_still_rejects_hidden_include(fixture_tree, hidden):
    root, _ = fixture_tree
    source = root / 'game/legacy.cpp'; source.parent.mkdir(); source.write_text('int x;\n')
    output = source.with_suffix('.obj'); output.touch()
    command, env = build.compiler_command(source, output)
    sidecar = build._deps_sidecar(output)
    sidecar.write_text(json.dumps({'deps': {}, 'source': build._hash_file(str(source)),
        'cmd': build._cmd_fingerprint(command, env)}))
    assert build.compile_is_current(source, output)
    build._warm_stale_paths([(source, output)])
    source.write_text(hidden + 'int x;\n')
    # Update identity fields to isolate the unchanged forced-include guard.
    command, env = build.compiler_command(source, output)
    sidecar.write_text(json.dumps({'deps': {}, 'source': build._hash_file(str(source)),
        'cmd': build._cmd_fingerprint(command, env)}))
    assert not build.compile_is_current(source, output)


def test_retry_directory_change_after_warming_is_stale(fixture_tree):
    root, _ = fixture_tree
    source = root / 'game/retry.cpp'; source.parent.mkdir(); source.write_text('int x;\n')
    output = root / 'build/retry.obj'; output.parent.mkdir(); write_receipt(source, output)
    sweep = root / 'sweep'; sweep.mkdir(); build._SWEEP_INCLUDE_DIRS = [sweep]
    command, env = build.compiler_command(source, output)
    sidecar = build._deps_sidecar(output); meta = json.loads(sidecar.read_text())
    meta['retry_dirs'] = ['sweep']
    meta['inventory'] = build.search_inventory(source, command + ['-I' + str(sweep)], env)
    sidecar.write_text(json.dumps(meta))
    assert build.compile_is_current(source, output)
    build._warm_stale_paths([(source, output)])
    sweep.rmdir()
    assert not build.compile_is_current(source, output)


def test_native_windows_path_branch_has_no_conversion(monkeypatch):
    from types import SimpleNamespace
    monkeypatch.setattr(build, 'os', SimpleNamespace(name='nt'))
    monkeypatch.setattr(build.subprocess, 'check_output', forbidden_conversion)
    assert build.wine_path('C:\\native\\include') == 'C:\\native\\include'


def test_new_path_after_warming_propagates_spawn_conversion_failure(fixture_tree):
    root, _ = fixture_tree
    source = root / 'game/plain.cpp'; source.parent.mkdir(); source.write_text('int x;\n')
    output = root / 'build/plain.obj'; output.parent.mkdir(); write_receipt(source, output)
    paths = build._warm_stale_paths([(source, output)])
    assert str(root / 'inputs/vendor/nbench') not in paths
    new_source = root / 'game/Libraries/Source/Benchmark/new.cpp'
    new_source.parent.mkdir(parents=True); new_source.write_text(source.read_text())
    new_output = root / 'build/new.obj'; new_output.write_bytes(output.read_bytes())
    build._deps_sidecar(new_output).write_text(build._deps_sidecar(output).read_text())
    with concurrent.futures.ProcessPoolExecutor(1, mp_context=multiprocessing.get_context('spawn'),
            initializer=observed_init, initargs=(paths,)) as pool:
        with pytest.raises(AssertionError, match='external path conversion'):
            list(pool.map(build._stale_chunk, [[(new_source, new_output)]]))
