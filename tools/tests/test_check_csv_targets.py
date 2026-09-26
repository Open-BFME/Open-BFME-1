"""Game orphan accounting recognizes independently validated target ownership."""
import csv
import io
from pathlib import Path
import struct
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_csv
from target_verify import LEDGER_FIELDS
from test_targets import configure, image


SOURCES = ["worldbuilder/src/First.cpp", "worldbuilder/src/Second.cpp"]
LEDGER = "targets/worldbuilder/reverse/functions.csv"


def exported_image():
    data = bytearray(image(b"\xc3\xc3", virtual_size=0x200))
    struct.pack_into("<II", data, 0x98 + 96, 0x1100, 0x80)
    struct.pack_into("<IIHHIIIIIII", data, 0x300,
                     0, 0, 0, 0, 0x1144, 1, 2, 2, 0x1130, 0x1138, 0x1140)
    struct.pack_into("<IIIIHH", data, 0x330, 0x1000, 0x1001, 0x1150, 0x1160, 0, 1)
    for offset, value in ((0x344, b"fixture\0"), (0x350, b"_First\0"), (0x360, b"_Second\0")):
        data[offset:offset + len(value)] = value
    return bytes(data)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    def git(*args):
        return subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.name", "Target test")
    git("config", "user.email", "target@example.invalid")
    git("config", "core.autocrlf", "false")
    config, binary, _ = configure(tmp_path, data=exported_image())
    for source in SOURCES:
        path = tmp_path / source
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("void body() {}\n")
    target_ledger = tmp_path / LEDGER
    target_ledger.parent.mkdir(parents=True)
    out = io.StringIO()
    writer = csv.DictWriter(out, fieldnames=LEDGER_FIELDS, lineterminator="\n")
    writer.writeheader()
    for n, source in enumerate(SOURCES):
        writer.writerow(dict(name=("_First", "_Second")[n], target_rva=hex(0x1000 + n),
                             target_size="1", status="matched", source=source, profile="editor-size",
                             evidence="export", model="fixture"))
    target_ledger.write_text(out.getvalue())
    game_files = {"FUNCTIONS": ("functions.csv", check_csv.FUNCTIONS_HEADER),
                  "SYMBOLS": ("symbols.csv", check_csv.SYMBOLS_HEADER),
                  "DELETED": ("deleted_rows.csv", "name,target_rva,reason")}
    monkeypatch.setattr(check_csv, "ROOT", tmp_path)
    (tmp_path / "targets/game/reverse").mkdir(parents=True)
    for key, (name, header) in game_files.items():
        path = tmp_path / "targets/game/reverse" / name
        path.write_bytes((header + "\r\n").encode())
        monkeypatch.setattr(check_csv, key, path)
    git("add", "--", *SOURCES, "targets", str(config), str(binary))
    git("commit", "-qm", "target ownership fixture")
    return tmp_path, git


@pytest.mark.parametrize("args", [[], ["--staged"], ["--ref", "HEAD"]])
def test_two_editor_sources_pass_actual_ledger_check(repo, monkeypatch, capsys, args):
    monkeypatch.setattr(sys, "argv", ["check_csv.py", *args])
    check_csv.main()
    assert "check_csv: OK" in capsys.readouterr().out


def test_unclaimed_editor_source_is_not_hidden_by_orphan_allowance(repo):
    root, git = repo
    path = root / "worldbuilder/src/Unclaimed.cpp"
    path.write_text("void unclaimed() {}\n")
    git("add", "--", str(path))
    problems = []
    check_csv.check_orphans(None, problems)
    assert any("unclaimed target sources" in problem for problem in problems)


@pytest.mark.parametrize("damage", ["missing", "bad-schema", "wrong-identity"])
def test_invalid_target_ledger_cannot_exempt_sources(repo, damage):
    root, git = repo
    ledger = root / LEDGER
    if damage == "missing":
        ledger.unlink()
    elif damage == "bad-schema":
        ledger.write_text("source,status\n")
    else:
        ledger.write_text(ledger.read_text().replace("_First", "_Invented"))
    git("add", "--", LEDGER)
    problems = []
    assert check_csv.check_orphans(None, problems) == 0
    assert any("WorldBuilder source ownership is invalid" in problem for problem in problems)


@pytest.mark.parametrize("spec", ["", "HEAD"])
def test_snapshot_cannot_borrow_different_working_tree_claims(repo, spec):
    root, _ = repo
    ledger = root / LEDGER
    ledger.write_text(ledger.read_text().replace("_First", "_Invented"))
    problems = []
    assert check_csv.check_orphans(spec, problems) == 0
    assert any("verification inputs differ" in problem for problem in problems)


def test_genuine_game_orphans_remain_failures(repo):
    root, git = repo
    for n in range(2):
        path = root / f"game/GameOrphan{n}.cpp"
        path.parent.mkdir(exist_ok=True)
        path.write_text("void unclaimed() {}\n")
        git("add", "--", str(path))
    problems = []
    assert check_csv.check_orphans(None, problems) == 2
    assert len(problems) == 1
    assert "game/GameOrphan0.cpp" in problems[0]
    assert all(source not in problems[0] for source in SOURCES)
