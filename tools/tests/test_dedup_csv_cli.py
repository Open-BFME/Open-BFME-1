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
    def normalize(path):
        calls.append(path.name)
        return 2, 1
    monkeypatch.setattr(dedup_csv, 'dedup_functions', normalize)
    monkeypatch.setattr(dedup_csv, 'dedup_symbols', normalize)
    dedup_csv.main([])
    assert calls == ['functions.csv', 'symbols.csv']
