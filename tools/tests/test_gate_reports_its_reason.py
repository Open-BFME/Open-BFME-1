"""The gate must print a failing check's own explanation, not swallow it.

`run(label, check)` catches SystemExit so every check reports before the gate
exits once. It used to discard `exc.code` -- so a check raising
SystemExit("<explanation>") had its explanation thrown away, and the summary
line read like a crash. Three full-gate runs and two wrong diagnoses were spent
before someone called the check directly to recover the text.

Source-level, deliberately: `run` is a closure inside main() and reproducing its
semantics in a test would only test the reproduction.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

SRC = (Path(__file__).resolve().parents[1] / "build.py").read_text()
HANDLER = re.search(r"except SystemExit as exc:.*?return None\n", SRC, re.S).group(0)


def test_the_handler_prints_exc_code():
    assert "exc.code" in HANDLER
    assert "print(" in HANDLER, HANDLER


def test_a_bare_int_exit_status_is_not_printed_as_a_message():
    """An int carries no diagnosis; printing it would be noise, not evidence."""
    assert "isinstance(exc.code, int)" in HANDLER, HANDLER


def test_a_clean_exit_still_propagates():
    """`if not exc.code: raise` must survive -- a zero exit is not a failure."""
    assert "if not exc.code:" in HANDLER and "raise" in HANDLER


def test_the_failure_is_still_recorded_so_the_gate_exits_once():
    assert "failed.append(label)" in HANDLER
