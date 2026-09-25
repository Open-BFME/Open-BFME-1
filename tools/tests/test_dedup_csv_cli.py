"""Help and invalid arguments must never normalize the live ledgers."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import dedup_csv


@pytest.mark.parametrize('args,code', [(['--help'], 0), (['-h'], 0),
                                      (['--not-an-option'], 2), (['extra'], 2)])
def test_non_mutating_argument_paths(monkeypatch, args, code):
    def forbidden(*_):
        pytest.fail('argument handling reached a ledger mutation')
    monkeypatch.setattr(dedup_csv, 'dedup_functions', forbidden)
    monkeypatch.setattr(dedup_csv, 'dedup_symbols', forbidden)
    with pytest.raises(SystemExit) as result:
        dedup_csv.main(args)
    assert result.value.code == code


def test_no_arguments_preserves_explicit_normalization(monkeypatch):
    calls = []
    def normalize(path, *_):
        calls.append(path.name)
        return 2, 1
    monkeypatch.setattr(dedup_csv, 'dedup_functions', normalize)
    monkeypatch.setattr(dedup_csv, 'dedup_symbols', normalize)
    dedup_csv.main([])
    assert calls == ['functions.csv', 'symbols.csv']


HEADER = "name,export_rva,target_rva,target_size,source,status,notes\r\n"
KEEP = "?keep@@YAXXZ,,0x00401000,16,Code/A.cpp,matched,\r\n"
DEAD = "?dead@@YAXXZ,,0x00402000,16,Code/B.cpp,matched,\r\n"


def test_drop_tombstoned_removes_a_resurrected_row(tmp_path, capsys):
    # A rebase or cherry-pick skips pre-commit, so a union merge can bring a
    # deliberately deleted row back unseen until pre-push.
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes((HEADER + KEEP + DEAD).encode())
    before, after = dedup_csv.dedup_functions(ledger, frozenset({("?dead@@YAXXZ", 0x00402000)}))
    assert (before, after) == (2, 1)
    assert ledger.read_bytes() == (HEADER + KEEP).encode()
    assert "dropped tombstoned ?dead@@YAXXZ @ 0x00402000" in capsys.readouterr().out


def test_without_the_flag_nothing_tombstoned_is_dropped(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes((HEADER + DEAD).encode())
    assert dedup_csv.dedup_functions(ledger) == (1, 1)
    assert ledger.read_bytes() == (HEADER + DEAD).encode()
