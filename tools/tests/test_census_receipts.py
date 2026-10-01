"""One successful compile can prove an uncacheable census TU, never cache it."""
import sys
import os
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import census_receipts as proofs


@pytest.mark.parametrize('exitcode', [0, 7])
def test_capture_finishes_on_direct_child_exit_with_inherited_handles(
        tmp_path, monkeypatch, exitcode):
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    ready = tmp_path / 'descendant.ready'
    release = tmp_path / 'descendant.release'
    done = tmp_path / 'descendant.done'
    child = tmp_path / 'compiler.py'
    child.write_text(
        'import os, pathlib, subprocess, sys, time\n'
        'descendant = subprocess.Popen([sys.executable, "-c", '
        '"import pathlib, sys, time; "\n'
        '"ready, release, done = map(pathlib.Path, sys.argv[1:]); ready.touch(); "\n'
        '"deadline = time.monotonic() + 30\\n"\n'
        '"while not release.exists() and time.monotonic() < deadline: time.sleep(0.01)\\n"\n'
        '"done.touch()", *sys.argv[1:4]])\n'
        'while not pathlib.Path(sys.argv[1]).exists(): time.sleep(0.01)\n'
        'os.write(1, bytes(range(256)) * 4096 + b"\\r\\n#line 9 \\\"unit.cpp\\\"\\n")\n'
        'os.write(2, bytes(reversed(range(256))) * 4096 + b"\\r\\ncompiler diagnostic\\n")\n'
        'sys.exit(int(sys.argv[4]))\n')
    pool = ThreadPoolExecutor(max_workers=1)
    future = pool.submit(proofs.capture_preprocessor,
                         [sys.executable, str(child), str(ready), str(release), str(done), str(exitcode)],
                         dict(os.environ))
    try:
        result = future.result(timeout=5)
        # The descendant still holds both output handles. Its lifetime must
        # neither delay the direct child's result nor change that exit code.
        assert ready.exists() and not release.exists() and not done.exists()
        assert result.returncode == exitcode
        assert result.stdout == bytes(range(256)) * 4096 + b'\r\n#line 9 "unit.cpp"\n'
        assert result.stderr == bytes(reversed(range(256))) * 4096 + b'\r\ncompiler diagnostic\n'
    finally:
        release.touch()
        pool.shutdown(wait=True)


def test_capture_turns_a_hung_preprocessor_into_a_failure(tmp_path, monkeypatch):
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    monkeypatch.setattr(proofs, 'PREPROCESS_TIMEOUT', 1)
    result = proofs.capture_preprocessor(
        [sys.executable, '-c', 'import time; time.sleep(30)'], dict(os.environ))
    assert result.returncode == 124
    assert b'timed out' in result.stderr


def test_real_capture_nonzero_exit_is_rejected_by_snapshot(tmp_path, monkeypatch):
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    source = tmp_path / 'unit.cpp'
    source.write_text('int f(){return 17;}\n')
    compiler = tmp_path / 'compiler.py'
    compiler.write_text(
        'import sys\n'
        'sys.stdout.buffer.write(b\'#line 1 "unit.cpp"\\nint f(){return 17;}\\n\')\n'
        'sys.stderr.buffer.write(b"compiler exit seven\\n")\n'
        'sys.exit(7)\n')
    with pytest.raises(ValueError, match='preprocessor failed: compiler exit seven'):
        proofs.snapshot(source, [sys.executable, str(compiler), '-c', str(source)], dict(os.environ))


def fixture(tmp_path, monkeypatch):
    source = tmp_path / 'game/unit.cpp'
    source.parent.mkdir()
    header = tmp_path / 'build/generated.h'
    header.parent.mkdir()
    header.write_text('#define VALUE 17\n')
    source.write_text('#include "../build/generated.h"\nint f(){return VALUE;}\n')
    output = tmp_path / 'unit.obj'
    output.write_bytes(b'previous object')
    command = ['cl', '-c', '-Fo' + str(output), str(source)]
    env = {'INCLUDE': ''}
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    monkeypatch.setattr(build, 'compiler_command', lambda *a: (command, env))
    monkeypatch.setattr(build, '_cmd_fingerprint', lambda *a: 'flags')
    monkeypatch.setattr(build, 'search_inventory', lambda *a, **k: {})
    monkeypatch.setattr(build, '_write_deps_sidecar', lambda *a: None)
    def run(cmd, **kwargs):
        if '-E' in cmd:
            pp = (f'#line 1 "{source}"\n#line 1 "{header}"\n'.encode()
                  + header.read_bytes() + source.read_bytes())
            return SimpleNamespace(returncode=0, stdout=pp,
                                   stderr=('Note: including file: ' + str(header)).encode())
        output.write_bytes(b'compiled object')
        return SimpleNamespace(returncode=0, stdout='Note: including file: ' + str(header))
    monkeypatch.setattr(build.subprocess, 'run', run)
    # Input-proof unit tests replace the compiler with the same byte transcript
    # as before. Real regular-file capture is exercised separately below.
    monkeypatch.setattr(proofs, 'capture_preprocessor', lambda cmd, env:
                        build.subprocess.run(cmd, cwd=build.ROOT, env=env,
                                             stdout=build.subprocess.PIPE,
                                             stderr=build.subprocess.PIPE))
    return source, header, output, command, env, run


def test_actual_compile_receipt_does_not_enable_reusable_cache(tmp_path, monkeypatch):
    source, header, obj, command, env, _ = fixture(tmp_path, monkeypatch)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    assert build.try_compile_source(source, obj, input_proof=receipt)[0]
    assert receipt.current(source, obj)
    assert not build.compile_is_current(source, obj)
    receipt.save()
    restored = proofs.Receipts.load(receipt.path, receipt.run)
    assert restored.current(source, obj)
    assert proofs.Receipts.load(receipt.path, 'different census') is None
    obj.write_bytes(b'last week object')
    assert not restored.current(source, obj)


def test_input_changed_inside_actual_compile_refuses_receipt(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    def changed(cmd, **kwargs):
        result = run(cmd, **kwargs)
        if '-E' not in cmd:
            header.write_text('#define VALUE 18\n')
        return result
    monkeypatch.setattr(build.subprocess, 'run', changed)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    with pytest.raises(SystemExit, match='inputs changed during compile'):
        build.try_compile_source(source, obj, input_proof=receipt)
    assert not receipt.entries


def test_cacheable_sidecar_cannot_skip_observed_input_change(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    def changed(cmd, **kwargs):
        result = run(cmd, **kwargs)
        if '-E' not in cmd:
            header.write_text('#define VALUE 18\n')
        return result
    monkeypatch.setattr(build.subprocess, 'run', changed)
    def sidecar(*args):
        build._deps_sidecar(obj).write_text('a reusable receipt appeared')
    monkeypatch.setattr(build, '_write_deps_sidecar', sidecar)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    with pytest.raises(SystemExit, match='inputs changed during compile'):
        build.try_compile_source(source, obj, input_proof=receipt)
    assert not receipt.entries
    assert not build._deps_sidecar(obj).exists()


def test_change_and_restore_during_compile_is_still_refused(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    def restored(cmd, **kwargs):
        result = run(cmd, **kwargs)
        if '-E' not in cmd:
            original = header.read_bytes()
            header.write_text('#define VALUE 18\n')
            header.write_bytes(original)
        return result
    monkeypatch.setattr(build.subprocess, 'run', restored)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    with pytest.raises(SystemExit, match='inputs changed during compile'):
        build.try_compile_source(source, obj, input_proof=receipt)
    assert not receipt.entries


def test_new_shadow_and_raw_newline_change_refuse_old_input(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    assert build.try_compile_source(source, obj, input_proof=receipt)[0]
    header.write_bytes(header.read_bytes().replace(b'\n', b'\r\n'))
    assert not receipt.current(source, obj)
    header.write_text('#define VALUE 17\n')
    shadow = tmp_path / 'shadow.h'
    shadow.write_text('#define VALUE 17\n')
    def shadowed(cmd, **kwargs):
        result = run(cmd, **kwargs)
        if '-E' in cmd:
            result.stdout = result.stdout.replace(str(header).encode(), str(shadow).encode())
        return result
    monkeypatch.setattr(build.subprocess, 'run', shadowed)
    assert not receipt.current(source, obj)


def test_failed_actual_compile_cannot_bless_existing_object(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    def failed(cmd, **kwargs):
        return run(cmd, **kwargs) if '-E' in cmd else SimpleNamespace(returncode=1, stdout='error C1000')
    monkeypatch.setattr(build.subprocess, 'run', failed)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    assert not build.try_compile_source(source, obj, input_proof=receipt)[0]
    assert obj.read_bytes() == b'previous object'
    assert not receipt.current(source, obj)


def test_preprocessor_nonzero_exit_refuses_complete_looking_output(tmp_path, monkeypatch):
    source, header, obj, command, env, _ = fixture(tmp_path, monkeypatch)
    original = proofs.capture_preprocessor
    def failed(cmd, flags):
        result = original(cmd, flags)
        result.returncode = 7
        result.stderr += b'\ncompiler failed\n'
        return result
    monkeypatch.setattr(proofs, 'capture_preprocessor', failed)
    with pytest.raises(ValueError, match='preprocessor failed:'):
        proofs.snapshot(source, command, env)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    assert not receipt.current(source, obj)


@pytest.mark.parametrize('macro', ['__TIME__', '__DATE__', '__TIMESTAMP__'])
def test_volatile_macro_never_proves_actual_compile(tmp_path, monkeypatch, macro):
    source, header, obj, command, env, _ = fixture(tmp_path, monkeypatch)
    header.write_text('const char *value=' + macro + ';\n')
    with pytest.raises(ValueError, match='volatile predefined macro'):
        proofs.snapshot(source, command, env)


def test_masm_partial_preprocessor_output_is_not_proof(tmp_path):
    with pytest.raises(ValueError, match='MASM preprocessing'):
        proofs.snapshot(tmp_path / 'unit.asm', ['ml', '-c'], {})


def test_token_pasted_clock_expansion_is_refused(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    source.write_text('#define CAT(a,b) a##b\nconst char *clock=CAT(__TI,ME__);\n')
    def expanded(cmd, **kwargs):
        result = run(cmd, **kwargs)
        result.stdout += b'const char *clock="17:17:59";\n'
        return result
    monkeypatch.setattr(build.subprocess, 'run', expanded)
    with pytest.raises(ValueError, match='date/time output'):
        proofs.snapshot(source, command, env)


def test_virtual_historical_line_filename_is_preserved_not_opened(tmp_path, monkeypatch):
    source, header, obj, command, env, _ = fixture(tmp_path, monkeypatch)
    source.write_text('#include "../build/generated.h"\n#line 74 "F:\\\\bfme\\\\historical.cpp"\nint f(){return VALUE;}\n')
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    assert build.try_compile_source(source, obj, input_proof=receipt)[0]
    assert receipt.current(source, obj)
    entry = receipt.entries[str(obj.resolve())]
    assert set(entry['input']['files']) == {str(source), str(header)}
    source.write_text(source.read_text().replace('historical.cpp', 'different.cpp'))
    assert not receipt.current(source, obj)


def test_successful_sweep_retry_gets_its_actual_command_receipt(tmp_path, monkeypatch):
    source, header, obj, command, env, run = fixture(tmp_path, monkeypatch)
    sweep = tmp_path / 'sweep'
    sweep.mkdir()
    monkeypatch.setattr(build, '_SWEEP_INCLUDE_DIRS', [sweep])
    monkeypatch.setattr(build, 'wine_path', lambda p: str(p))
    def needs_sweep(cmd, **kwargs):
        if '-I' + str(sweep) in cmd:
            return run(cmd, **kwargs)
        error = "fatal error C1083: Cannot open include file: 'windows.h'"
        if '-E' in cmd:
            return SimpleNamespace(returncode=2, stdout=b'', stderr=error.encode())
        return SimpleNamespace(returncode=2, stdout=error)
    monkeypatch.setattr(build.subprocess, 'run', needs_sweep)
    receipt = proofs.Receipts(tmp_path / 'inputs.json')
    assert build.try_compile_source(source, obj, input_proof=receipt)[0]
    assert receipt.entries[str(obj.resolve())]['command'] == command + ['-I' + str(sweep)]
    assert receipt.current(source, obj)
