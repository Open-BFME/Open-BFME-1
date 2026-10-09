"""tools/dir32_record.py retire and the commit-msg Dir32-Retire check, on a throwaway repo."""
import importlib
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import dir32_record_guard as guard  # noqa: E402

OLD, NEW, VA = "?g_wrong@@3HA", "?TheRight@@3HA", 0x012ED5D4
KEEP = "?TheKept@@3HA"


def git(repo, *args):
    subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True)


def make_repo(tmp_path, *, owned=True, mention_old=False):
    repo = tmp_path / "repo"
    rev = repo / "targets/game/reverse"
    rev.mkdir(parents=True)
    (rev / "dir32_addresses.csv").write_text(f"name,va\n{OLD},0x{VA:08X}\n{KEEP},0x01300000\n")
    data = "name,address,address_kind,size,section,source,status,evidence,model\n"
    if owned:
        data += f"{NEW},0x{VA:08X},va,4,.data,game/a.cpp,matched,x,m\n"
    (rev / "data_rows.csv").write_text(data)
    (rev / "functions.csv").write_text("name,export_rva,target_rva,target_size,source,status,notes\n")
    (repo / "game").mkdir()
    (repo / "game/a.cpp").write_text("int TheRight;\n" + ("extern int g_wrong;\n" if mention_old else ""))
    git(repo, "init", "-q")
    git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "base", "--no-gpg-sign")
    return repo


def tool(monkeypatch, repo):
    monkeypatch.chdir(repo)
    import dir32_record
    return importlib.reload(dir32_record)


def stage_record(repo):
    git(repo, "add", "targets/game/reverse/dir32_addresses.csv")


def test_retire_ok_and_trailer_passes_commit_msg(tmp_path, monkeypatch, capsys):
    repo = make_repo(tmp_path)
    msg = tmp_path / "msg"
    msg.write_text("Retire a wrong name\n")
    assert tool(monkeypatch, repo).main(["retire", OLD, "--for", NEW, "--msg", str(msg)]) == 0
    line = guard.trailer(OLD, VA, NEW)
    assert line in capsys.readouterr().out
    assert line in msg.read_text().splitlines()
    record = (repo / guard.REL).read_text()
    assert OLD not in record and KEEP in record
    stage_record(repo)
    assert guard.check_commit_msg(str(msg)) == 0


def test_retire_refuses_new_not_owned(tmp_path, monkeypatch, capsys):
    repo = make_repo(tmp_path, owned=False)
    assert tool(monkeypatch, repo).main(["retire", OLD, "--for", NEW]) == 1
    assert "not ledger-owned" in capsys.readouterr().err
    assert OLD in (repo / guard.REL).read_text()


def test_retire_refuses_old_still_under_game(tmp_path, monkeypatch, capsys):
    repo = make_repo(tmp_path, mention_old=True)
    assert tool(monkeypatch, repo).main(["retire", OLD, "--for", NEW]) == 1
    assert "still appears in game/a.cpp" in capsys.readouterr().err
    assert OLD in (repo / guard.REL).read_text()


def test_retire_owned_by_ilt_row(tmp_path, monkeypatch):
    repo = make_repo(tmp_path, owned=False)
    thunk = "?j_00EED5D4@@YAXXZ"
    (repo / "targets/game/reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"{thunk},,0x{VA - 0x400000:08X},5,game/a.cpp,matched,x\n")
    git(repo, "add", "-A")
    assert tool(monkeypatch, repo).main(["retire", OLD, "--for", thunk]) == 0


def test_deletion_without_trailer_refused(tmp_path, monkeypatch, capsys):
    repo = make_repo(tmp_path)
    monkeypatch.chdir(repo)
    (repo / guard.REL).write_text(f"name,va\n{KEEP},0x01300000\n")
    stage_record(repo)
    msg = tmp_path / "msg"
    msg.write_text("Drop a line by hand\n")
    assert guard.check_commit_msg(str(msg)) == 1
    err = capsys.readouterr().err
    assert "without a Dir32-Retire trailer" in err and "tools/dir32_record.py" in err


def test_trailer_not_matching_diff_refused(tmp_path, monkeypatch, capsys):
    repo = make_repo(tmp_path)
    monkeypatch.chdir(repo)
    msg = tmp_path / "msg"
    # a trailer with no deletion
    msg.write_text("x\n\n" + guard.trailer(OLD, VA, NEW) + "\n")
    assert guard.check_commit_msg(str(msg)) == 1
    assert "does not delete its line" in capsys.readouterr().err
    # a deletion whose trailer names the wrong address
    (repo / guard.REL).write_text(f"name,va\n{KEEP},0x01300000\n")
    stage_record(repo)
    msg.write_text("x\n\n" + guard.trailer(OLD, VA + 4, NEW) + "\n")
    assert guard.check_commit_msg(str(msg)) == 1
    assert "the deleted line recorded" in capsys.readouterr().err


def test_hand_deletion_with_trailer_but_unowned_new_refused(tmp_path, monkeypatch, capsys):
    repo = make_repo(tmp_path, owned=False)
    monkeypatch.chdir(repo)
    (repo / guard.REL).write_text(f"name,va\n{KEEP},0x01300000\n")
    stage_record(repo)
    msg = tmp_path / "msg"
    msg.write_text("x\n\n" + guard.trailer(OLD, VA, NEW) + "\n")
    assert guard.check_commit_msg(str(msg)) == 1
    assert "not ledger-owned" in capsys.readouterr().err


def test_commit_msg_quiet_without_deletion(tmp_path, monkeypatch):
    repo = make_repo(tmp_path)
    monkeypatch.chdir(repo)
    msg = tmp_path / "msg"
    msg.write_text("Unrelated\n")
    assert guard.check_commit_msg(str(msg)) == 0


def test_bare_identifier():
    assert guard.bare_identifier("?Foo@Bar@@3HA") == "Foo"
    assert guard.bare_identifier("_g_x") == "g_x"
    assert guard.bare_identifier("?$S1@?1??f@@YAXXZ@4IA") is None


def test_append_trailer_joins_existing_trailer_block(tmp_path):
    import dir32_record
    msg = tmp_path / "m.txt"
    msg.write_text("Subject\n\nBody text.\n\nClaim-Lease: abc\nCo-Authored-By: X <x@y>\n")
    dir32_record.append_trailer(str(msg), "Dir32-Retire: A 0x1 for B")
    dir32_record.append_trailer(str(msg), "Dir32-Retire: C 0x2 for D")
    paras = msg.read_text().rstrip("\n").split("\n\n")
    assert paras[-1].splitlines() == ["Claim-Lease: abc", "Co-Authored-By: X <x@y>",
                                      "Dir32-Retire: A 0x1 for B", "Dir32-Retire: C 0x2 for D"]
    out = subprocess.run(["git", "interpret-trailers", "--parse", str(msg)],
                         capture_output=True, text=True, check=True).stdout
    assert "Dir32-Retire: A 0x1 for B" in out and "Claim-Lease: abc" in out


def test_append_trailer_new_block_after_prose(tmp_path):
    import dir32_record
    msg = tmp_path / "m.txt"
    msg.write_text("Subject: not a trailer\n\nProse: this line\nis not all trailers.\n")
    dir32_record.append_trailer(str(msg), "Dir32-Retire: A 0x1 for B")
    assert msg.read_text().endswith("is not all trailers.\n\nDir32-Retire: A 0x1 for B\n")
    one = tmp_path / "s.txt"
    one.write_text("Subject: x\n")
    dir32_record.append_trailer(str(one), "Dir32-Retire: A 0x1 for B")
    assert one.read_text() == "Subject: x\n\nDir32-Retire: A 0x1 for B\n"
