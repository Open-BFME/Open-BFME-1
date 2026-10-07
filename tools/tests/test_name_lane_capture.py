"""Naming commands must not wait for Wine services that inherited their output."""
import json
import os
from pathlib import Path
import signal
import subprocess
import sys

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import name_lane


def test_command_exits_while_descendant_keeps_output_descriptors(tmp_path):
    pidfile = tmp_path / 'descendant.pid'
    program = tmp_path / 'command.py'
    program.write_text(
        'import subprocess, sys\n'
        'from pathlib import Path\n'
        'child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(60)"])\n'
        f'Path({str(pidfile)!r}).write_text(str(child.pid))\n'
        'print("stdout evidence", flush=True)\n'
        'print("stderr evidence", file=sys.stderr, flush=True)\n'
        'sys.exit(23)\n'
    )
    caller = tmp_path / 'caller.py'
    caller.write_text(
        'import json, sys\n'
        f'sys.path.insert(0, {str(TOOLS)!r})\n'
        'import name_lane\n'
        f'done = name_lane.captured([sys.executable, {str(program)!r}])\n'
        'print(json.dumps([done.returncode, done.stdout, done.stderr]))\n'
    )
    try:
        done = subprocess.run([sys.executable, str(caller)], capture_output=True, text=True, timeout=5, check=True)
        assert json.loads(done.stdout) == [23, 'stdout evidence\n', 'stderr evidence\n']
        os.kill(int(pidfile.read_text()), 0)
    finally:
        if pidfile.exists():
            try:
                os.kill(int(pidfile.read_text()), signal.SIGTERM)
            except ProcessLookupError:
                pass


@pytest.mark.parametrize('exit_code,output,expected', [
    (0, 'Functions: OK 2/2', None),
    (0, 'Functions: OK 1/2', 'build.sh exited 0'),
    (1, 'Functions: OK 2/2', 'build.sh exited 1'),
    (1, 'MISMATCH fixture', 'MISMATCH fixture'),
])
def test_capture_change_preserves_gate_verdicts(monkeypatch, exit_code, output, expected):
    monkeypatch.setattr(name_lane, 'captured', lambda command: subprocess.CompletedProcess(command, exit_code, output, ''))
    assert name_lane.gate('game/fixture.cpp') == expected
