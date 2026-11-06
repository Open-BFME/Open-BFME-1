"""tools/dir32_record.py retire and the commit-msg Dir32-Retire check, on a throwaway repo."""
import importlib

import pytest
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
    assert guard.bare_identifier("??_7Foo@@6B@") == "Foo"
    assert guard.bare_identifier("??_7?$T@H@@6B@") is None
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


# --- code owners: a matched function row, or a vtable its deleting destructor proves ---

FN_OLD, FN_VA = "?d_00001500@@YAXXZ", 0x00401500
VT_OLD, VT_VA = "??_7Rva00001100Foo@@6B@", 0x00402000
FN_NEW, VT_NEW = "_Rva00001500", "??_7Foo@@6B@"
HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def make_pe():
    """A two-section image: .text (code) at RVA 0x1000, .rdata at 0x2000. The table
    at VA 0x402000 holds an ILT slot (0x401010: jmp 0x401100) and a direct slot
    0x401300, then a zero."""
    image = bytearray(0x3000)
    image[0:2] = b"MZ"
    image[0x3C:0x40] = (0x80).to_bytes(4, "little")
    image[0x80:0x84] = b"PE\0\0"
    image[0x86:0x88] = (2).to_bytes(2, "little")
    image[0x94:0x96] = (0xE0).to_bytes(2, "little")
    table = 0x80 + 24 + 0xE0
    for i, (name, rva, flags) in enumerate(((b".text", 0x1000, 0x60000020), (b".rdata", 0x2000, 0x40000040))):
        at = table + 40 * i
        image[at:at + 8] = name.ljust(8, b"\0")
        for k, value in enumerate((0x1000, rva, 0x1000, rva)):
            image[at + 8 + 4 * k:at + 12 + 4 * k] = value.to_bytes(4, "little")
        image[at + 36:at + 40] = flags.to_bytes(4, "little")
    image[0x1010] = 0xE9
    image[0x1011:0x1015] = (0x1100 - 0x1015).to_bytes(4, "little", signed=True)
    image[0x1600:0x1606] = bytes([0xC7, 0x00]) + (0x402000).to_bytes(4, "little")  # ctor: mov [eax], table
    image[0x2000:0x2004] = (0x401010).to_bytes(4, "little")
    image[0x2004:0x2008] = (0x401300).to_bytes(4, "little")
    return bytes(image)


def make_code_repo(tmp_path, rows, files=None):
    repo = tmp_path / "code"
    rev = repo / "targets/game/reverse"
    rev.mkdir(parents=True)
    (rev / "dir32_addresses.csv").write_text(f"name,va\n{FN_OLD},0x{FN_VA:08X}\n{VT_OLD},0x{VT_VA:08X}\n")
    (rev / "data_rows.csv").write_text("name,address,address_kind,size,section,source,status,evidence,model\n")
    (rev / "functions.csv").write_text(HEADER + "".join(r + "\n" for r in rows))
    exe = repo / guard.EXE
    exe.parent.mkdir(parents=True)
    exe.write_bytes(make_pe())
    (repo / "game").mkdir()
    for path, text in (files or {"game/b.cpp": "int x;\n"}).items():
        (repo / path).parent.mkdir(parents=True, exist_ok=True)
        (repo / path).write_text(text)
    git(repo, "init", "-q")
    git(repo, "add", "-A")
    git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "base", "--no-gpg-sign")
    guard._IMAGE.clear()
    return repo


FN_ROW = f"{FN_NEW},,0x00001500,64,game/b.cpp,matched,x"
DTOR_ROW = "??_GFoo@@UAEPAXI@Z,,0x00001100,30,game/b.cpp,matched,x"


def retire(monkeypatch, repo, old, new):
    return tool(monkeypatch, repo).main(["retire", old, "--for", new])


def test_retire_owned_by_matched_function_row(tmp_path, monkeypatch):
    repo = make_code_repo(tmp_path, [FN_ROW])
    msg = tmp_path / "msg"
    msg.write_text("x\n")
    assert tool(monkeypatch, repo).main(["retire", FN_OLD, "--for", FN_NEW, "--msg", str(msg)]) == 0
    stage_record(repo)
    assert guard.check_commit_msg(str(msg)) == 0


def test_function_owner_wrong_address_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [f"{FN_NEW},,0x00001504,64,game/b.cpp,matched,x"])
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "no matched functions.csv row" in capsys.readouterr().err


def test_function_owner_generated_row_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [f"{FN_NEW},,0x00001500,64,game/gen_asm/d.asm,matched,x"])
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "generated row" in capsys.readouterr().err


def test_function_owner_unmatched_row_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [f"{FN_NEW},,0x00001500,64,game/b.cpp,partial,x"])
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "no matched functions.csv row" in capsys.readouterr().err


def test_function_owner_second_identity_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [FN_ROW, "?other@@YAXXZ,,0x00001500,64,game/c.cpp,matched,x"])
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "one identity per body" in capsys.readouterr().err


def test_function_owner_other_object_symbol_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [f"{FN_NEW},,0x00001500,64,game/b.cpp,matched,object-symbol=_Rva1;x"])
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "links as object-symbol" in capsys.readouterr().err


def test_function_owner_old_name_still_in_game_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [FN_ROW], {"game/b.cpp": "void d_00001500();\n"})
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "still appears in game/b.cpp" in capsys.readouterr().err


def test_old_name_only_in_unbuilt_gen_dump_allowed(tmp_path, monkeypatch):
    repo = make_code_repo(tmp_path, [FN_ROW], {"game/b.cpp": "int x;\n",
                                               "game/gen_asm/d.asm": f"public {FN_OLD}\n"})
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 0


def test_old_name_in_built_gen_dump_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [FN_ROW, "?d_1@@YAXXZ,,0x00001600,8,game/gen_asm/d.asm,matched,x"],
                          {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": f"extrn {FN_OLD}:near\n"})
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert "still appears in game/gen_asm/d.asm" in capsys.readouterr().err


def test_retire_vtable_proven_by_deleting_destructor(tmp_path, monkeypatch):
    repo = make_code_repo(tmp_path, [DTOR_ROW])
    msg = tmp_path / "msg"
    msg.write_text("x\n")
    assert tool(monkeypatch, repo).main(["retire", VT_OLD, "--for", VT_NEW, "--msg", str(msg)]) == 0
    stage_record(repo)
    assert guard.check_commit_msg(str(msg)) == 0


def test_vtable_direct_slot_dtor_proves(tmp_path, monkeypatch):
    repo = make_code_repo(tmp_path, ["??_EFoo@@UAEPAXI@Z,,0x00001300,30,game/b.cpp,matched,x"])
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 0


def test_vtable_other_class_dtor_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW, "??_GBar@@UAEPAXI@Z,,0x00001400,30,game/b.cpp,matched,x"])
    assert retire(monkeypatch, repo, VT_OLD, "??_7Bar@@6B@") == 1
    assert "does not reach a matched deleting destructor of Bar" in capsys.readouterr().err


def test_vtable_ctor_alone_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, ["??0Foo@@QAE@XZ,,0x00001100,30,game/b.cpp,matched,x"])
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "no matched, non-generated ??_G/??_E" in capsys.readouterr().err


def test_vtable_generated_or_unmatched_dtor_refused(tmp_path, monkeypatch):
    for i, row in enumerate(("??_GFoo@@UAEPAXI@Z,,0x00001100,30,game/gen_small/g.cpp,matched,x",
                             "??_GFoo@@UAEPAXI@Z,,0x00001100,30,game/b.cpp,partial,x")):
        repo = make_code_repo(tmp_path / str(i), [row])
        assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_vtable_name_at_wrong_address_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW])
    # the function line's VA is code, not Foo's table
    assert retire(monkeypatch, repo, FN_OLD, VT_NEW) == 1
    assert "not a vtable start" in capsys.readouterr().err


def test_vtable_new_recorded_elsewhere_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW])
    rec = repo / guard.REL
    rec.write_text(rec.read_text() + f"{VT_NEW},0x00402100\n")
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "is recorded at 0x00402100" in capsys.readouterr().err


def test_vtable_walk_stops_at_next_recorded_table(tmp_path, monkeypatch, capsys):
    bar = "??_GBar@@UAEPAXI@Z,,0x00001300,30,game/b.cpp,matched,x"
    repo = make_code_repo(tmp_path / "open", [bar])
    assert retire(monkeypatch, repo, VT_OLD, "??_7Bar@@6B@") == 0
    repo = make_code_repo(tmp_path / "next", [bar])
    rec = repo / guard.REL
    rec.write_text(rec.read_text() + "??_7Next@@6B@,0x00402004\n")
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, VT_OLD, "??_7Bar@@6B@") == 1
    assert "does not reach" in capsys.readouterr().err


def test_secondary_vtable_old_name_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW])
    rec = repo / guard.REL
    rec.write_text(rec.read_text().replace(VT_OLD, "??_7Foo@@6BBase@@@"))
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, "??_7Foo@@6BBase@@@", VT_NEW) == 1
    assert "secondary" in capsys.readouterr().err


def test_vtable_old_class_still_spelled_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW], {"game/b.cpp": "class Rva00001100Foo;\n"})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "still appears in game/b.cpp" in capsys.readouterr().err


def test_vtable_walk_reaching_two_classes_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW, "??_GBar@@UAEPAXI@Z,,0x00001300,30,game/b.cpp,matched,x"])
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "another class's deleting destructor" in capsys.readouterr().err


def test_function_owner_at_jump_thunk_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, ["?body@@YAXXZ,,0x00001010,5,game/b.cpp,matched,x"])
    rec = repo / guard.REL
    rec.write_text(rec.read_text() + "?old@@YAXXZ,0x00401010\n")
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, "?old@@YAXXZ", "?body@@YAXXZ") == 1
    assert "jmp thunk" in capsys.readouterr().err


def test_is_dtor_of_exact_class():
    assert guard.is_dtor_of("??_GFoo@@UAEPAXI@Z", "Foo")
    assert guard.is_dtor_of("??_G?$V@PAX@@@UAEPAXI@Z", "?$V@PAX@")
    assert not guard.is_dtor_of("??_G?$V@PAX@@@UAEPAXI@Z", "?$V@PAX")
    assert not guard.is_dtor_of("??_GFooBar@@UAEPAXI@Z", "Foo")


# --- round-1 review counterexamples ---

def test_walk_stops_at_code_referenced_slot(tmp_path, monkeypatch, capsys):
    bar = "??_GBar@@UAEPAXI@Z,,0x00001300,30,game/b.cpp,matched,x"
    repo = make_code_repo(tmp_path, [bar])
    exe = repo / guard.EXE
    image = bytearray(exe.read_bytes())
    image[0x1500:0x1506] = bytes([0xC7, 0x00]) + (0x402004).to_bytes(4, "little")  # mov [eax], 0x402004
    exe.write_bytes(bytes(image))
    git(repo, "add", "-A")
    guard._IMAGE.clear()
    assert retire(monkeypatch, repo, VT_OLD, "??_7Bar@@6B@") == 1
    assert "does not reach" in capsys.readouterr().err


def test_adjustor_thunk_dtor_proves_nothing(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, ["??_EFoo@@WBA@AEPAXI@Z,,0x00001100,30,game/b.cpp,matched,x"])
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "no matched, non-generated ??_G/??_E" in capsys.readouterr().err
    assert not guard.is_dtor_of("??_ETexProjectClass@@WMM@AEPAXI@Z", "TexProjectClass")


def test_old_name_in_vendored_library_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW], {"game/b.cpp": "int x;\n",
                                                 "inputs/vendor/lib/x.lib": f"\0\0{VT_OLD}\0"})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "inputs/vendor/lib/x.lib" in capsys.readouterr().err


def test_placeholder_may_not_replace_descriptive(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, ["??_GRva00001100X@@UAEPAXI@Z,,0x00001100,30,game/b.cpp,matched,x"])
    rec = repo / guard.REL
    rec.write_text(rec.read_text().replace(VT_OLD, "??_7Desc@@6B@"))
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, "??_7Desc@@6B@", "??_7Rva00001100X@@6B@") == 1
    assert "placeholder" in capsys.readouterr().err


def test_retire_address_body_alias_for_matched_bfme_callback(tmp_path, monkeypatch):
    old = "?b_00001500@@YAXXZ"
    callback = "?bfmeEnumThreadWndProc@@YGHPAXJ@Z"
    repo = make_code_repo(tmp_path, [FN_ROW.replace(FN_NEW, callback)])
    record = repo / guard.REL
    record.write_text(record.read_text().replace(FN_OLD, old))
    git(repo, "add", "-A")

    assert retire(monkeypatch, repo, old, callback) == 0
    assert old not in record.read_text()


def test_old_without_plain_identifier_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [FN_ROW])
    rec = repo / guard.REL
    rec.write_text(rec.read_text().replace(FN_OLD, "??0Foo@@QAE@XZ"))
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, "??0Foo@@QAE@XZ", FN_NEW) == 1
    assert "no plain identifier" in capsys.readouterr().err


def test_placeholder_names():
    for name in ("?d_00819920@@YAXXZ", "_Rva00819920", "??_7Rva00A3AA39SizeOptDeleting@@6B@",
                 "??_7T1A2_0110F9CC@@6B@", "?g_bfme937Obj@@3PADA", "??_7Gen_0014B790@@6B@"):
        assert guard.is_placeholder(name), name
    for name in ("??_7CCodecDXT@D3DXTex@@6B@", "??_7AttackHordeStateMachine@@6B@",
                 "?TheIMEManager@@3PAVIMEManager@@A", "??0Vector3i16@@QAE@XZ"):
        assert not guard.is_placeholder(name), name
    assert guard.bare_identifier("_Rva009F8AA0@0") == "Rva009F8AA0"
    assert guard.bare_identifier("__real@41200000") is None


REAL = Path(__file__).resolve().parents[2]


@pytest.mark.skipif(not (REAL / guard.EXE).exists(), reason="retail image not present")
@pytest.mark.parametrize("old,new,why", [
    ("??_7?$DynamicVectorClass@VVector2@@@@6B@", "??_7?$DynamicVectorClass@VStringClass@@@@6B@",
     "no plain identifier"),
    ("??0Vector3i16@@QAE@XZ", "?value@Rva00923A10@@QAEPAU1@XZ", "no plain identifier"),
    ("??_7CCodecDXT@D3DXTex@@6B@", "??_7Rva00A3AA39SizeOptDeleting@@6B@", "placeholder"),
    ("??_7T1A2_0110F9CC@@6B@", "??_7EmissionVelocityInfo@FXParticleSystem@@6B@", "does not reach"),
])
def test_reviewer_counterexamples_on_real_ledger(monkeypatch, old, new, why):
    monkeypatch.chdir(REAL)
    guard._IMAGE.clear()
    recorded = guard.read_at(f":{guard.REL}")
    if old not in recorded:
        pytest.skip(f"{old} no longer recorded")
    after = {k: v for k, v in recorded.items() if k != old}
    problem = guard.retire_problem(old, recorded[old], new, recorded, after)
    guard._IMAGE.clear()
    assert problem and why in problem


# --- round-2 review ---

def test_mid_table_va_is_not_a_vtable_start(tmp_path, monkeypatch, capsys):
    # Foo's dtor sits in slot 1 (0x401300); OLD recorded at table+4, which no code stores.
    repo = make_code_repo(tmp_path, ["??_GFoo@@UAEPAXI@Z,,0x00001300,30,game/b.cpp,matched,x"])
    rec = repo / guard.REL
    rec.write_text(rec.read_text() + "?g_Va00402004@@3PAXA,0x00402004\n")
    git(repo, "add", "-A")
    assert retire(monkeypatch, repo, "?g_Va00402004@@3PAXA", VT_NEW) == 1
    assert "not a vtable start" in capsys.readouterr().err


def test_import_and_constant_names_have_no_identifier():
    for name in ("__imp__strcmpi", "__imp_?f@@YAXXZ", "__real@41200000"):
        assert guard.bare_identifier(name) is None, name
    assert guard.bare_identifier("__bfmeDynBufXZ") == "_bfmeDynBufXZ"


def test_old_name_in_other_built_source_refused(tmp_path, monkeypatch, capsys):
    lib = "inputs/toolchains/vc/lib/libc.lib"
    repo = make_code_repo(tmp_path, [FN_ROW, f"_crt,,0x00001700,8,{lib},matched,x"],
                          {"game/b.cpp": "int x;\n", lib: f"\0{FN_OLD}\0"})
    assert retire(monkeypatch, repo, FN_OLD, FN_NEW) == 1
    assert lib in capsys.readouterr().err


# --- OLD spelled only inside a gen_asm PROC no row builds (approved by the project lead 2026-10-16) ---

LIVE = "?d_00001500@@YAXXZ,,0x00001500,8,game/gen_asm/d.asm,matched,gen-dump"
# the hand-written row that replaced the dead proc's body at 0x1600
REPLACED = "?real@@YAXXZ,,0x00001600,8,game/b.cpp,matched,x"


def dump(dead_body=f"    dd {VT_OLD}\n", live_body="    db 0C3h\n", extern=True, outside=""):
    return ((f"EXTERN {VT_OLD}:BYTE\n" if extern else "") + "_TEXT SEGMENT\n" + outside
            + "?d_00001500@@YAXXZ PROC\n" + live_body + "?d_00001500@@YAXXZ ENDP\n"
            + "?d_00001600@@YAXXZ PROC\n" + dead_body + "?d_00001600@@YAXXZ ENDP\n_TEXT ENDS\nEND\n")


def test_old_only_in_an_unbuilt_proc_of_a_built_dump_allowed(tmp_path, monkeypatch):
    # the TBuff case: the dump is still built for another proc, the vtable's
    # only use is the replaced proc's body plus its EXTERN
    repo = make_code_repo(tmp_path, [DTOR_ROW, LIVE, REPLACED],
                          {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": dump()})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 0


def test_old_in_a_proc_still_built_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW, LIVE],
                          {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": dump(live_body=f"    dd {VT_OLD}\n")})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "still appears in game/gen_asm/d.asm" in capsys.readouterr().err


def test_old_outside_any_proc_refused(tmp_path, monkeypatch, capsys):
    repo = make_code_repo(tmp_path, [DTOR_ROW, LIVE],
                          {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": dump(outside=f"    dd {VT_OLD}\n")})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "still appears in game/gen_asm/d.asm" in capsys.readouterr().err


def test_old_in_a_proc_another_row_builds_refused(tmp_path, monkeypatch, capsys):
    # the dead-looking proc is built under another name through object-symbol=
    alias = "_Rva00001600,,0x00001600,8,game/gen_asm/d.asm,matched,object-symbol=?d_00001600@@YAXXZ"
    repo = make_code_repo(tmp_path, [DTOR_ROW, LIVE, alias],
                          {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": dump()})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "still appears in game/gen_asm/d.asm" in capsys.readouterr().err


def test_old_in_an_unmatched_row_proc_refused(tmp_path, monkeypatch, capsys):
    # any row (not only a matched one) that builds the proc keeps it live
    row = "?d_00001600@@YAXXZ,,0x00001600,8,game/gen_asm/d.asm,partial,x"
    repo = make_code_repo(tmp_path, [DTOR_ROW, LIVE, row],
                          {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": dump()})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_bare_word_outside_procs_refused(tmp_path, monkeypatch, capsys):
    # a bare spelling in a comment between procs is not inside a dead body
    repo = make_code_repo(tmp_path, [DTOR_ROW, LIVE],
                          {"game/b.cpp": "int x;\n",
                           "game/gen_asm/d.asm": dump(outside="; Rva00001100Foo table\n")})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_gen_small_cpp_dump_still_built_refused(tmp_path, monkeypatch, capsys):
    row = "?g@@YAXXZ,,0x00001600,8,game/gen_small/s.cpp,matched,x"
    repo = make_code_repo(tmp_path, [DTOR_ROW, row],
                          {"game/b.cpp": "int x;\n", "game/gen_small/s.cpp": f"// {VT_OLD}\nvoid g() {{}}\n"})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    assert "still appears in game/gen_small/s.cpp" in capsys.readouterr().err


def test_asm_procs_bounds():
    text = "x\nA PROC\n db 0\nA ENDP\nB PROC NEAR\nB ENDP\n"
    assert guard.asm_procs(text) == [(2, 4, "A"), (5, 6, "B")]
    # bounds unknown: unclosed, or a PROC opening inside another
    assert guard.asm_procs(text + "C PROC\n") is None
    assert guard.asm_procs("A PROC\nB PROC\nB ENDP\nA ENDP\n") is None


# --- round 1 review (build/review_deadproc_r1): each hole now refuses ---

DEAD_ROW = "?d_00001600@@YAXXZ,,0x00001600,8,game/gen_asm/d.asm,matched,gen-dump"


def dead_repo(tmp_path, text, rows=(DTOR_ROW, LIVE, REPLACED), extra=None):
    files = {"game/b.cpp": "int x;\n", "game/gen_asm/d.asm": text}
    files.update(extra or {})
    return make_code_repo(tmp_path, list(rows), files)


def test_A_dead_proc_called_from_a_built_proc_refused(tmp_path, monkeypatch):
    repo = dead_repo(tmp_path, dump(live_body="    call ?d_00001600@@YAXXZ\n"))
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_A_dead_proc_called_from_another_dump_refused(tmp_path, monkeypatch):
    repo = dead_repo(tmp_path, dump(), extra={"game/gen_asm/e.asm": "EXTERN ?d_00001600@@YAXXZ:NEAR\n"})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_B_row_deleted_without_a_replacement_refused(tmp_path, monkeypatch):
    # the seat drops ?d_00001600's row and lands nothing at 0x1600
    repo = dead_repo(tmp_path, dump(), rows=(DTOR_ROW, LIVE))
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1
    # a generated replacement covers nothing either
    gen = "?g@@YAXXZ,,0x00001600,8,game/gen_small/g.cpp,matched,gen-x"
    repo = dead_repo(tmp_path / "g", dump(), rows=(DTOR_ROW, LIVE, gen),
                     extra={"game/gen_small/g.cpp": "void g() {}\n"})
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_B_proc_without_an_address_name_refused(tmp_path, monkeypatch):
    text = dump().replace("?d_00001600@@YAXXZ", "?helper@@YAXXZ")
    repo = dead_repo(tmp_path, text)
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


@pytest.mark.parametrize("dead_body,live_body", [
    (f"lbl EQU {VT_OLD}\n", "    dd lbl\n"),               # an EQU a built proc uses
    (f"lbl2:\n    dd {VT_OLD}\n", "    jmp lbl2\n"),        # a label a built proc jumps to
    (f"lbl3 LABEL BYTE\n    dd {VT_OLD}\n", "    dd lbl3\n"),  # a LABEL a built proc reads
])
def test_C_G_label_defined_in_the_dead_body_used_elsewhere_refused(tmp_path, monkeypatch, dead_body, live_body):
    repo = dead_repo(tmp_path, dump(dead_body=dead_body, live_body=live_body))
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_D_nested_procs_refused(tmp_path, monkeypatch):
    text = (f"EXTERN {VT_OLD}:BYTE\n_TEXT SEGMENT\n?d_00001600@@YAXXZ PROC\n?d_00001500@@YAXXZ PROC\n"
            f"    dd {VT_OLD}\n?d_00001500@@YAXXZ ENDP\n?d_00001600@@YAXXZ ENDP\n_TEXT ENDS\nEND\n")
    repo = dead_repo(tmp_path, text)
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_E_proc_word_in_a_comment_is_failsafe(tmp_path, monkeypatch):
    repo = dead_repo(tmp_path, dump(outside="; PROC\n"))
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 1


def test_F_crlf_and_lowercase_directives_read_as_masm_does(tmp_path, monkeypatch):
    # MASM directives are case-insensitive, so `proc`/`endp` bound a proc too
    repo = dead_repo(tmp_path, dump().replace("\n", "\r\n"))
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 0
    repo = dead_repo(tmp_path / "l", dump().replace(" PROC", " proc").replace(" ENDP", " endp"))
    assert retire(monkeypatch, repo, VT_OLD, VT_NEW) == 0


# --- round 2 review (build/review_deadproc_r2/src/tools/tests/test_r2_probes.py): refusals ---

HDR = f"EXTERN {VT_OLD}:BYTE\n_TEXT SEGMENT\n"
END = "_TEXT ENDS\nEND\n"
DEAD = "?d_00001600@@YAXXZ"
LIVEP = "?d_00001500@@YAXXZ"


def proc(sym, body):
    return f"public {sym}\n{sym} PROC\n{body}{sym} ENDP\n"


def r2(tmp_path, monkeypatch, text, rows=(DTOR_ROW, LIVE, REPLACED), extra=None):
    return retire(monkeypatch, dead_repo(tmp_path, text, rows=rows, extra=extra), VT_OLD, VT_NEW)


def test_r2_case_variant_of_old_in_built_proc_refused(tmp_path, monkeypatch):
    assert r2(tmp_path, monkeypatch, dump(live_body=f"    dd {VT_OLD.lower()}\n")) == 1


def test_r2_case_variant_call_of_dead_proc_refused(tmp_path, monkeypatch):
    assert r2(tmp_path, monkeypatch, dump(live_body=f"    call {DEAD.upper()}\n")) == 1


def test_r2_global_label_in_dead_body_refused(tmp_path, monkeypatch):
    assert r2(tmp_path, monkeypatch, dump(dead_body=f"lbl2::\n    dd {VT_OLD}\n", live_body="    jmp LBL2\n")) == 1


def test_r2_data_label_without_colon_refused(tmp_path, monkeypatch):
    assert r2(tmp_path, monkeypatch, dump(dead_body=f"tbl dd {VT_OLD}\n", live_body="    dd tbl\n")) == 1


def test_r2_macro_in_dead_body_refused(tmp_path, monkeypatch):
    text = HDR + proc(DEAD, f"mymac MACRO\n    dd {VT_OLD}\nENDM\n    db 0C3h\n") + proc(LIVEP, "    mymac\n") + END
    assert r2(tmp_path, monkeypatch, text) == 1


def test_r2_textequ_in_dead_body_refused(tmp_path, monkeypatch):
    text = HDR + proc(DEAD, f"tq TEXTEQU <{VT_OLD}>\n    db 0C3h\n") + proc(LIVEP, "    dd tq\n") + END
    assert r2(tmp_path, monkeypatch, text) == 1


def test_r2_coverage_must_start_at_the_proc(tmp_path, monkeypatch):
    other = "?other@@YAXXZ,,0x000015F0,32,game/b.cpp,matched,x"
    assert r2(tmp_path, monkeypatch, dump(), rows=(DTOR_ROW, LIVE, other)) == 1


def test_r2_reference_from_a_built_non_game_source_refused(tmp_path, monkeypatch):
    ref = "inputs/reference/x/r.asm"
    row = f"?r@@YAXXZ,,0x00001700,8,{ref},matched,x"
    assert r2(tmp_path, monkeypatch, dump(), rows=(DTOR_ROW, LIVE, REPLACED, row),
              extra={ref: f"EXTERN {DEAD}:NEAR\n"}) == 1


def test_r2_undecorated_cpp_declaration_refused(tmp_path, monkeypatch):
    cpp = "void d_00001600(void);\nvoid j_00001700(void) { d_00001600(); }\n"
    row = "?j_00001700@@YAXXZ,,0x00001700,5,game/c.cpp,matched,carved"
    assert r2(tmp_path, monkeypatch, dump(), rows=(DTOR_ROW, LIVE, REPLACED, row),
              extra={"game/c.cpp": cpp}) == 1


def test_r2_formfeed_forged_bounds_refused(tmp_path, monkeypatch):
    text = (HDR + f"public {LIVEP}\n{LIVEP} PROC\n"
            f"    db 90h ; \x0c{LIVEP} ENDP\x0c{DEAD} PROC\n"
            f"    dd {VT_OLD}\n"
            f"    db 0C3h ; \x0c{DEAD} ENDP\x0c{LIVEP} PROC\n"
            f"{LIVEP} ENDP\n" + END)
    assert r2(tmp_path, monkeypatch, text) == 1


@pytest.mark.parametrize("block", ["IF 0", "COMMENT ~"])
def test_r2_conditional_or_comment_block_refused(tmp_path, monkeypatch, block):
    close = "ENDIF" if block == "IF 0" else "~"
    text = (HDR + f"public {LIVEP}\n{LIVEP} PROC\n    db 90h\n{block}\n{LIVEP} ENDP\n{DEAD} PROC\n{close}\n"
            f"    dd {VT_OLD}\n{block}\n{DEAD} ENDP\n{LIVEP} PROC\n{close}\n{LIVEP} ENDP\n" + END)
    assert r2(tmp_path, monkeypatch, text) == 1


def test_r2_dump_lines_rejects_control_characters_and_directives():
    assert guard.dump_lines("a\x0cb\n") is None
    assert guard.dump_lines("x\nIF 0\nENDIF\n") is None
    assert guard.dump_lines("x\r\ny\n") == ["x", "y", ""]
