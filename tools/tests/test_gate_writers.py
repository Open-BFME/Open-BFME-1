"""tools/gate_writers.py: a gate-read ledger fact passes when its one writer stamped
it in this worktree's git dir, and a hand edit is refused."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import gate_writers as gw  # noqa: E402

DATA = "targets/game/reverse/data_rows.csv"
DATA_HEAD = "name,address,address_kind,size,section,source,status,evidence,model\n"
ROW_A = "?g_a@@3HA,0x01000000,va,4,.data,game/a.cpp,matched,old evidence,m\n"
ROW_B = "?g_b@@3HA,0x01000004,va,4,.data,game/a.cpp,matched,e,m\n"
SYMS = "targets/game/reverse/symbols.csv"
SYMS_HEAD = "name,address,notes\n__imp__GetClientRect@8,0x0135901C,iat\n?f@@YAXXZ,0x00001000,pin\n"
FUNCS = "targets/game/reverse/functions.csv"
FUNCS_HEAD = ("name,export_rva,target_rva,target_size,source,status,notes\r\n"
              "?f@@YAXXZ,,0x00100000,40,game/a.cpp,matched,\r\n"
              "?d_1@@YAXXZ,,0x00100100,12,game/a.cpp,matched,parent=?f@@YAXXZ;object-symbol=$L100\r\n")
EXTRA = {SYMS: SYMS_HEAD, FUNCS: FUNCS_HEAD}


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="t@t",
               GIT_COMMITTER_EMAIL="t@t")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


@pytest.fixture
def repo(tmp_path, monkeypatch):
    files = {DATA: DATA_HEAD + ROW_A}
    files.update(EXTRA)
    for rel, text in files.items():
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text(text, newline="\n")
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", ".")
    git(tmp_path, "commit", "-qm", "init")
    monkeypatch.chdir(tmp_path)
    return tmp_path


def write(root, rel, text, tool_kind=None):
    before = (root / rel).read_bytes()
    (root / rel).write_text(text, newline="\n")
    if tool_kind:
        gw.stamp(tool_kind, before, (root / rel).read_bytes())
    git(root, "add", rel)


def test_a_tool_added_data_row_passes(repo):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B, tool_kind="data_row")
    assert gw.staged_problems() == {}
    assert gw.main(["x", "--staged"]) == 0


def test_a_hand_added_or_moved_data_row_is_refused(repo, capsys):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B)
    assert list(gw.staged_problems()) == ["data_row"]
    assert gw.main(["x", "--staged"]) == 1
    assert "tools/add_data_match.py" in capsys.readouterr().err
    write(repo, DATA, DATA_HEAD + ROW_A.replace("game/a.cpp", "game/b.cpp"))
    assert gw.staged_problems()["data_row"][0].endswith("game/b.cpp|matched")


def test_deleting_a_row_or_editing_its_evidence_is_not_refused(repo):
    write(repo, DATA, DATA_HEAD + ROW_A.replace("old evidence", "new evidence"))
    assert gw.staged_problems() == {}
    write(repo, DATA, DATA_HEAD)
    assert gw.staged_problems() == {}


def test_a_stamp_from_another_write_does_not_cover_this_one(repo):
    gw.stamp("data_row", DATA_HEAD, DATA_HEAD + ROW_B)
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B.replace("0x01000004", "0x01000008"))
    assert "data_row" in gw.staged_problems()


def test_merges_are_skipped(repo):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B)
    head = git(repo, "rev-parse", "HEAD").strip()
    (repo / ".git" / "MERGE_HEAD").write_text(head + "\n")
    assert gw.main(["x", "--staged"]) == 0


def test_add_data_match_stamps_its_write():
    text = (Path(__file__).resolve().parents[1] / "add_data_match.py").read_text()
    assert 'gate_writers.stamp("data_row", existing, candidate)' in text


def test_a_hand_edited_imp_pin_is_refused_with_the_import_binding_command(repo, capsys):
    write(repo, SYMS, SYMS_HEAD.replace("0x0135901C", "0x01359020"))
    assert gw.staged_problems()["imp_pin"] == ["+__imp__GetClientRect@8,0x01359020",
                                               "-__imp__GetClientRect@8,0x0135901C"]
    assert gw.main(["x", "--staged"]) == 1
    assert "tools/import_binding.py pin NAME ADDR" in capsys.readouterr().err
    write(repo, SYMS, SYMS_HEAD + "__imp__Sleep@4,0x01359000,new\n")
    assert "imp_pin" in gw.staged_problems()


def test_other_symbols_csv_writers_still_pass(repo):
    # an ordinary pin added (pin tools, add_match), an __imp_ note reworded, and a
    # dedup/line-ending rewrite (dedup_csv.py) change no __imp_ (name, address)
    write(repo, SYMS, SYMS_HEAD.replace("iat", "iat slot").replace("\n", "\r\n")
          + "?g@@YAXXZ,0x00002000,pin\r\n")
    assert gw.staged_problems() == {}


# ---------------------------------------------------------------- import_binding pin / retire-pin
SLOT = 0x00F5901C                       # RVA of the retail IAT slot __imp__GetClientRect@8 binds


def _imports():
    import types
    key = ("user32.dll", "GetClientRect")
    return types.SimpleNamespace(slots={SLOT: key, SLOT + 4: ("user32.dll", "GetDC")},
                                 imp={"__imp__GetClientRect@8": key}, by_import={key: SLOT})


def _binding(repo, monkeypatch):
    import argparse
    import import_binding as ib
    monkeypatch.setattr(ib, "ROOT", repo)
    monkeypatch.setattr(ib, "SYMBOLS", repo / SYMS)
    return ib, argparse.Namespace


def _obj_referencing(path, name):
    """A minimal i386 COFF object with one undefined external NAME."""
    import struct
    raw = name.encode() + b"\0"
    head = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, 1, 0, 0)
    sym = struct.pack("<II", 0, 4) + struct.pack("<IhHBB", 0, 0, 0, 2, 0)
    path.write_bytes(head + sym + struct.pack("<I", 4 + len(raw)) + raw)


def test_retire_pin_of_an_unused_pin_passes_and_stamps(repo, monkeypatch, tmp_path):
    ib, ns = _binding(repo, monkeypatch)
    obj = tmp_path / "a.obj"
    _obj_referencing(obj, "__imp__Sleep@4")
    assert ib.cmd_retire_pin(ns(name="__imp__GetClientRect@8"), objects={obj: "game/a.cpp"}) == 0
    assert "__imp__GetClientRect" not in (repo / SYMS).read_text()
    git(repo, "add", SYMS)
    assert gw.staged_problems() == {}


def test_retire_pin_of_a_still_bound_pin_is_refused(repo, monkeypatch, tmp_path):
    ib, ns = _binding(repo, monkeypatch)
    obj = tmp_path / "a.obj"
    _obj_referencing(obj, "__imp__GetClientRect@8")
    with pytest.raises(ib.Refused, match="game/a.cpp"):
        ib.cmd_retire_pin(ns(name="__imp__GetClientRect@8"), objects={obj: "game/a.cpp"})
    with pytest.raises(ib.Refused, match="build.sh game/b.cpp"):
        ib.cmd_retire_pin(ns(name="__imp__GetClientRect@8"), objects={tmp_path / "none.obj": "game/b.cpp"})
    assert (repo / SYMS).read_text() == SYMS_HEAD


def test_pin_at_retail_slot_passes_and_a_wrong_slot_is_refused(repo, monkeypatch):
    ib, ns = _binding(repo, monkeypatch)
    with pytest.raises(ib.Refused, match="not 0x01359020"):
        ib.cmd_pin(ns(name="__imp__GetClientRect@8", address="0x01359020", note=None), imports=_imports())
    with pytest.raises(ib.Refused, match="no import library"):
        ib.cmd_pin(ns(name="__imp__Nope@4", address="0x0135901C", note=None), imports=_imports())
    assert (repo / SYMS).read_text() == SYMS_HEAD
    write(repo, SYMS, SYMS_HEAD.replace("0x0135901C", "0x01359020"))       # hand move
    assert ib.cmd_pin(ns(name="__imp__GetClientRect@8", address="0x0135901C", note=None),
                      imports=_imports()) == 0                            # tool moves it back
    git(repo, "add", SYMS)
    assert gw.staged_problems() == {}


def test_consume_drops_the_stamps_a_commit_used(repo):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B, tool_kind="data_row")
    git(repo, "commit", "-qm", "tool row")
    gw.consume()
    assert gw.stamped() == set()
    write(repo, DATA, DATA_HEAD + ROW_A)
    git(repo, "commit", "-qm", "drop")
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B)         # the old stamp no longer covers a hand re-add
    assert "data_row" in gw.staged_problems()


# ---------------------------------------------------------------- eh_label (shadow)
def test_a_stamped_relabel_is_quiet(repo, capsys):
    write(repo, FUNCS, FUNCS_HEAD.replace("$L100", "$L104"), tool_kind="eh_label")
    assert gw.main(["x", "--staged"]) == 0
    assert "shadow" not in capsys.readouterr().err


def test_a_hand_relabel_notes_and_never_refuses(repo, capsys):
    write(repo, FUNCS, FUNCS_HEAD.replace("$L100", "$L104"))
    assert gw.main(["x", "--staged"]) == 0
    err = capsys.readouterr().err
    assert "gate_writers: shadow: eh_label 0x00100100 $L100 -> $L104" in err
    assert "would be refused" in err and "eh_state_pins.py" in err


def test_a_new_label_row_produces_no_note(repo, capsys):
    write(repo, FUNCS, FUNCS_HEAD + "?d_2@@YAXXZ,,0x00100200,12,game/a.cpp,matched,object-symbol=$L7\r\n")
    assert gw.main(["x", "--staged"]) == 0
    assert capsys.readouterr().err == ""


def test_label_writers_stamp():
    tools = Path(__file__).resolve().parents[1]
    assert 'gate_writers.stamp("eh_label", raw, functions_csv.read_bytes())' in (tools / "add_match.py").read_text()
    assert 'gate_writers.stamp("eh_label", raw, functions.read_bytes())' in (tools / "eh_state_pins.py").read_text()
