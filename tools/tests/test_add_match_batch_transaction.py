"""Batch scaffold takeovers keep functions, tombstones, and sources atomic."""
import csv
import io
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match_batch


HEADER = "name,export_rva,target_rva,target_size,source,status,notes"


def dump(name, rva, size, source, kind="gen-dump"):
    return f"{name},,{rva},{size},{source},matched,{kind};origin=test"


def arrange(tmp_path, monkeypatch, dumps, claims, outcomes=(0,)):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    functions = reverse / "functions.csv"
    functions.write_bytes(
        (HEADER + "\r\n" + "".join(row + "\r\n" for row in dumps)).encode("utf-8"))
    deleted = reverse / "deleted_rows.csv"
    deleted.write_bytes(b"name,target_rva,reason\n")
    sources = []
    for claim in claims:
        source = tmp_path / claim[3]
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_bytes(
            f"// {claim[0]} present-unmatched\r\nvoid body() {{}}\r\n".encode("utf-8"))
        sources.append(source)
    manifest_text = io.StringIO()
    csv.writer(manifest_text, lineterminator="\n").writerows(claims)
    manifest = tmp_path / "rows.csv"
    manifest.write_text(manifest_text.getvalue(), encoding="utf-8")
    monkeypatch.setattr(sys, "argv", [
        "add_match_batch.py", str(manifest), "--root", str(tmp_path),
    ])
    if outcomes is not None:
        verdicts = iter(outcomes)
        monkeypatch.setattr(
            add_match_batch.subprocess, "run",
            lambda command, *, cwd: SimpleNamespace(returncode=next(verdicts)))
    return functions, deleted, sources


@pytest.mark.parametrize("kind", ["gen-dump", "gen-thunk"])
def test_batch_takeover_tombstones_each_scaffold(tmp_path, monkeypatch, kind):
    old = "?d_00abcd00@@YAXXZ" if kind == "gen-dump" else "?j_00abcd00@@YAXXZ"
    source = "Code/gen_asm/d_00abcd00.asm" if kind == "gen-dump" else "Code/gen_small/t.cpp"
    real = "?realBody@Thing@@QAEXXZ"
    functions, deleted, _sources = arrange(
        tmp_path, monkeypatch,
        [dump(old, "0x00ABCD00", 32, source, kind)],
        [(real, "0x00ABCD00", "32", "Code/Thing.cpp", "", "0x00ABCD00")])

    add_match_batch.main()

    assert old not in functions.read_text(encoding="utf-8")
    assert real in functions.read_text(encoding="utf-8")
    tombstone = list(csv.reader(io.StringIO(
        deleted.read_text(encoding="utf-8"))))[-1]
    assert tombstone[:2] == [old, "0x00ABCD00"]
    assert real in tombstone[2]


def test_later_red_gate_restores_every_file_byte_for_byte(tmp_path, monkeypatch):
    dumps = [
        dump("?d_00abcd00@@YAXXZ", "0x00ABCD00", 32, "Code/gen_asm/a.asm"),
        dump("?d_00abce00@@YAXXZ", "0x00ABCE00", 48, "Code/gen_asm/b.asm"),
    ]
    claims = [
        ("?a@Thing@@QAEXXZ", "0x00ABCD00", "32", "Code/A.cpp", "", "0x00ABCD00"),
        ("?b@Thing@@QAEXXZ", "0x00ABCE00", "48", "Code/B.cpp", "", "0x00ABCE00"),
    ]
    functions, deleted, sources = arrange(
        tmp_path, monkeypatch, dumps, claims, outcomes=(0, 1))
    before = (functions.read_bytes(), deleted.read_bytes(),
              *(source.read_bytes() for source in sources))

    with pytest.raises(SystemExit):
        add_match_batch.main()

    assert (functions.read_bytes(), deleted.read_bytes(),
            *(source.read_bytes() for source in sources)) == before


def test_interruption_restores_every_file_byte_for_byte(tmp_path, monkeypatch):
    functions, deleted, sources = arrange(
        tmp_path, monkeypatch,
        [dump("?d_00abcd00@@YAXXZ", "0x00ABCD00", 32, "Code/gen_asm/a.asm")],
        [("?a@Thing@@QAEXXZ", "0x00ABCD00", "32", "Code/A.cpp", "", "0x00ABCD00")])
    before = (functions.read_bytes(), deleted.read_bytes(), sources[0].read_bytes())
    monkeypatch.setattr(
        add_match_batch.subprocess, "run",
        lambda command, *, cwd: (_ for _ in ()).throw(KeyboardInterrupt()))

    with pytest.raises(KeyboardInterrupt):
        add_match_batch.main()

    assert (functions.read_bytes(), deleted.read_bytes(), sources[0].read_bytes()) == before


def test_dry_run_is_mutation_free(tmp_path, monkeypatch):
    functions, deleted, sources = arrange(
        tmp_path, monkeypatch,
        [dump("?d_00abcd00@@YAXXZ", "0x00ABCD00", 32, "Code/gen_asm/a.asm")],
        [("?a@Thing@@QAEXXZ", "0x00ABCD00", "32", "Code/A.cpp", "", "0x00ABCD00")])
    before = (functions.read_bytes(), deleted.read_bytes(), sources[0].read_bytes())
    sys.argv.insert(1, "--dry-run")

    add_match_batch.main()

    assert (functions.read_bytes(), deleted.read_bytes(), sources[0].read_bytes()) == before


def test_batch_rejects_a_different_scaffold_extent_without_changes(tmp_path, monkeypatch):
    functions, deleted, sources = arrange(
        tmp_path, monkeypatch,
        [dump("?d_00abcd00@@YAXXZ", "0x00ABCD00", 32, "Code/gen_asm/a.asm")],
        [("?a@Thing@@QAEXXZ", "0x00ABCD00", "47", "Code/A.cpp", "", "0x00ABCD00")])
    before = (functions.read_bytes(), deleted.read_bytes(), sources[0].read_bytes())

    with pytest.raises(SystemExit):
        add_match_batch.main()

    assert (functions.read_bytes(), deleted.read_bytes(), sources[0].read_bytes()) == before


def test_ordinary_batch_append_does_not_touch_deletion_ledger(tmp_path, monkeypatch):
    functions, deleted, _sources = arrange(
        tmp_path, monkeypatch, [],
        [("?a@Thing@@QAEXXZ", "0x00ABCD00", "32", "Code/A.cpp", "", "")])
    deleted_before = deleted.read_bytes()

    add_match_batch.main()

    assert "?a@Thing@@QAEXXZ" in functions.read_text(encoding="utf-8")
    assert deleted.read_bytes() == deleted_before
