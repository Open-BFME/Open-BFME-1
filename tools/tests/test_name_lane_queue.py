"""Queue metadata must select exactly the same work without exposing proposal text."""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane


def queue_fixture(monkeypatch):
    files = ['game/a.cpp', 'game/b.cpp', 'game/c.cpp', 'game/gen_asm/d.cpp']
    monkeypatch.setattr(name_lane, 'ledger_rows', lambda: dict.fromkeys(files, []))
    monkeypatch.setattr(name_lane, 'type_counts', lambda: {})
    monkeypatch.setattr(name_lane, 'ea_labelled', lambda: {})
    monkeypatch.setattr(name_lane, 'agreed_state', lambda: {})
    monkeypatch.setattr(name_lane, 'servable', lambda *args: True)
    monkeypatch.setattr(name_lane, 'read', lambda path: 'int a1;')
    monkeypatch.setattr(name_lane, 'owned', lambda *args: [('local', 'f', 'a1'), ('local', 'f', 'a2'), ('member', '', 'm_04')])
    monkeypatch.setattr(name_lane.random, 'shuffle', lambda files: None)
    monkeypatch.setattr(name_lane, 'table', lambda path: [
        {'key': 'game/a.cpp|local|f|a1', 'model': 'gpt-6-sol', 'hash': 'private'},
        {'key': 'game/c.cpp|local|f|a1', 'model': 'grok', 'hash': 'private'},
    ])


def test_metadata_uses_same_selection_and_priority(monkeypatch, capsys):
    queue_fixture(monkeypatch)
    served = []
    monkeypatch.setattr(name_lane, 'brief', lambda rel, *args: served.append(rel))
    args = argparse.Namespace(model='gpt-6-sol', file=None, count=2, list_only=False)
    name_lane.cmd_next(args)
    assert served == ['game/c.cpp', 'game/b.cpp']
    args.list_only = True
    name_lane.cmd_next(args)
    result = json.loads(capsys.readouterr().out)
    assert [r['file'] for r in result] == served
    assert served == ['game/c.cpp', 'game/b.cpp']
    assert all(set(r) == {'file', 'chars', 'kinds'} for r in result)
    assert result[0]['kinds'] == {'local': 2, 'member': 1}


def test_metadata_file_filter_and_empty_json(monkeypatch, capsys):
    queue_fixture(monkeypatch)
    monkeypatch.setattr(name_lane, 'brief', lambda *args: (_ for _ in ()).throw(AssertionError('must not create a session')))
    args = argparse.Namespace(model='gpt-6-sol', file='game/b.cpp', count=1, list_only=True)
    name_lane.cmd_next(args)
    assert [r['file'] for r in json.loads(capsys.readouterr().out)] == ['game/b.cpp']
    args.file = 'game/a.cpp'
    name_lane.cmd_next(args)
    assert json.loads(capsys.readouterr().out) == []
