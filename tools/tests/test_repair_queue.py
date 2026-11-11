"""repair_queue: gate-debt and link-cycle repairs carry their check and a machine pass
test; new matches are told which unit they belong in (never a fresh one-function file)."""
import importlib
import os
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def load(tmp_path, layout, ledger, files=()):
    rev = tmp_path / ("targets/game/reverse" if layout == "bfme1" else "reverse")
    rev.mkdir(parents=True)
    src = "game" if layout == "bfme1" else "Code"
    (rev / "functions.csv").write_text(HEADER + "".join(
        f"{n},,0x{r:08X},{s},{src}/{f},matched,\n" for n, r, s, f in ledger), newline="\n")
    for rel, text in files:
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, newline="\n")
    os.environ["REPAIR_ROOT"] = str(tmp_path)
    try:
        import repair_queue
        return importlib.reload(repair_queue), rev, src
    finally:
        del os.environ["REPAIR_ROOT"]


LEDGER = [("?a@Loco@@QAEXXZ", 0x1000, 0x40, "GameEngine/Loco.cpp"),
          ("?b@Loco@@QAEXXZ", 0x1080, 0x40, "GameEngine/Loco.cpp"),
          ("?c@Body@@QAEXXZ", 0x2000, 0x20, "GameEngine/Body.cpp"),
          ("?d_00003000@@YAXXZ", 0x3000, 0x8, "GameEngine/Rva00003000Noop.cpp"),
          ("?g@@YAXXZ", 0x3100, 0x8, "gen_small/uw.cpp")]


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
def test_dest_prefers_the_unit_around_the_address(tmp_path, layout):
    rq, _, src = load(tmp_path, layout, LEDGER)
    assert rq.dest_tu(0x1040)["dest"] == f"{src}/GameEngine/Loco.cpp"            # between two Loco rows
    assert "between two rows" in rq.dest_tu(0x1040)["basis"]
    assert rq.dest_tu(0x1F00)["dest"] == f"{src}/GameEngine/Body.cpp"            # nearest, 0x100 away
    got = rq.dest_tu(0x3010)                                                     # only an address-named file
    assert got["dest"] == f"{src}/GameEngine/Body.cpp"                           # and a generated one nearby
    got = rq.dest_tu(0x40000)
    assert got["dest"] is None and "never a new one-function file" in got["basis"]


def test_dest_takes_ea_file_evidence_first(tmp_path):
    rq, rev, src = load(tmp_path, "bfme1", LEDGER, [
        ("game/GameEngine/Source/Snapshot.cpp", "//\n"),
        ("targets/game/reverse/ea_evidence.csv",
         "rva,kind,value,route,basis\n0x00001040,file,GameEngine/Source/Snapshot.cpp,zh,\n")])
    got = rq.dest_tu(0x1040)
    assert got == {"dest": "game/GameEngine/Source/Snapshot.cpp", "basis": "EA source-file evidence (zh)"}


def test_bfme2_gate_debt_items_and_pass_test(tmp_path):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "# header\ntail 0x00001000 ?a@Loco@@QAEXXZ\nstrnul 0x00002000 ?c@Body@@QAEXXZ\n")])
    items = rq.repair_items()
    assert [(i["check"], i["source"], i["size"]) for i in items] == [
        ("tail", "Code/GameEngine/Loco.cpp", 0x40), ("strnul", "Code/GameEngine/Body.cpp", 0x20)]
    assert "pass-test 'tail 0x00001000 ?a@Loco@@QAEXXZ'" in items[0]["pass_test"]
    ok, _ = rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ", build_cmd=[sys.executable, "-c", "raise SystemExit(1)"])
    assert not ok and "tail 0x00001000" in (rev / "gate_baseline.txt").read_text()     # restored
    ok, message = rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ", build_cmd=[sys.executable, "-c", "pass"])
    assert ok and "tail 0x00001000" not in (rev / "gate_baseline.txt").read_text()
    assert "strnul 0x00002000" in (rev / "gate_baseline.txt").read_text()
    assert rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ")[0] is False                  # already gone


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
@pytest.mark.parametrize("error", [FileNotFoundError, PermissionError, KeyboardInterrupt])
def test_interrupted_pass_test_restores_baseline_bytes(tmp_path, monkeypatch, layout, error):
    rq, rev, _ = load(tmp_path, layout, LEDGER)
    if layout == "bfme1":
        path = rev / "body_guard_baseline.csv"
        line = "tail,0x00001000,?a@Loco@@QAEXXZ,tail mismatch"
        raw = ("check,target_rva,name,detail\r\n" + line + "\r\n"
               "strnul,0x00002000,?c@Body@@QAEXXZ,literal mismatch\n").encode()
    else:
        path = rev / "gate_baseline.txt"
        line = "tail 0x00001000 ?a@Loco@@QAEXXZ"
        raw = ("# gate debt\r\n" + line + "\r\n"
               "strnul 0x00002000 ?c@Body@@QAEXXZ\n").encode()
    path.write_bytes(raw)

    def interrupted_build(*args, **kwargs):
        # The checker must see the debt removed, but that removal is provisional.
        assert line.encode() not in path.read_bytes()
        raise error("build did not complete")

    monkeypatch.setattr(rq.subprocess, "run", interrupted_build)
    with pytest.raises(error, match="build did not complete"):
        rq.pass_test(line)
    assert path.read_bytes() == raw


def test_bfme1_body_guard_items(tmp_path):
    rq, rev, _ = load(tmp_path, "bfme1", LEDGER, [
        ("targets/game/reverse/body_guard_baseline.csv",
         "check,target_rva,name,detail\nltable,0x00001080,?b@Loco@@QAEXXZ,+12 $L9 wants 0x1 retail 0x2\n"
         "dir32,0x00401942,?g_00401942@@YAXXZ,\"nothing owns 0x00401942, give it a data row\"\n"),
        ("targets/game/reverse/full_gate_baseline.txt", "# full-gate red rows\n")])
    items = rq.repair_items()
    assert items[0]["check"] == "ltable" and items[0]["source"] == "game/GameEngine/Loco.cpp"
    assert items[0]["why"].startswith("+12 $L9")
    assert items[1]["check"] == "dir32" and items[1]["source"].startswith("(git grep")


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
@pytest.mark.parametrize("returncode", [0, 1])
def test_data_owner_pass_test_runs_the_normal_gate(tmp_path, monkeypatch, layout, returncode):
    rq, rev, src = load(tmp_path, layout, LEDGER, [
        (("game" if layout == "bfme1" else "Code") + "/Data.cpp",
         'namespace Keys { extern const char key[] = "Shader3"; }\n')])
    symbol = "?key@Keys@@3QBDB"
    source = f"{src}/Data.cpp"
    (rev / "data_rows.csv").write_text(
        f"name,source,status\n{symbol},{source},matched\n", newline="\n")
    if layout == "bfme1":
        path = rev / "body_guard_baseline.csv"
        line = f"dir32,0x00401942,{symbol},unowned datum"
        raw = f"check,target_rva,name,detail\n{line}\n".encode()
    else:
        path = rev / "gate_baseline.txt"
        line = f"dir32 0x00401942 {symbol}"
        raw = f"{line}\n".encode()
    path.write_bytes(raw)
    calls = []

    def run_gate(command, **kwargs):
        assert command == [sys.executable, str(tmp_path / "tools/build.py"), source]
        assert line.encode() not in path.read_bytes()
        calls.append(command)
        return rq.subprocess.CompletedProcess(command, returncode)

    monkeypatch.setattr(rq.subprocess, "run", run_gate)
    ok, message = rq.pass_test(line)
    assert ok == (returncode == 0)
    assert len(calls) == 1
    if returncode:
        assert path.read_bytes() == raw
        assert "line restored" in message
    else:
        assert line.encode() not in path.read_bytes()


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
@pytest.mark.parametrize("sources", [
    ("Missing.cpp",), ("../outside.cpp",), ("Other/Data.cpp",), ("Data.cpp", "Other.cpp")])
def test_invalid_or_ambiguous_data_owner_does_not_fall_back_to_grep(
        tmp_path, monkeypatch, layout, sources):
    rq, rev, src = load(tmp_path, layout, LEDGER)
    symbol = "?key@Keys@@3QBDB"
    rows = []
    for relative in sources:
        source = relative if relative.startswith("Other/") else f"{src}/{relative}"
        if relative != "Missing.cpp":
            path = tmp_path / source
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('extern const char key[] = "Shader3";\n')
        rows.append(f"{symbol},{source},matched\n")
    (rev / "data_rows.csv").write_text("name,source,status\n" + "".join(rows), newline="\n")

    def unexpected_grep(*args, **kwargs):
        pytest.fail("an invalid recorded data owner must not select another source")

    monkeypatch.setattr(rq.subprocess, "run", unexpected_grep)
    assert rq.locate_source(symbol) is None


def test_unmatched_data_owner_retains_literal_source_search(tmp_path, monkeypatch):
    rq, rev, src = load(tmp_path, "bfme1", LEDGER)
    symbol = "?key@Keys@@3QBDB"
    (rev / "data_rows.csv").write_text(
        f"name,source,status\n{symbol},{src}/Data.cpp,unmatched\n", newline="\n")

    def grep_source(command, **kwargs):
        assert command == ["git", "grep", "-l", "-F", "--", symbol, f"{src}/"]
        return rq.subprocess.CompletedProcess(command, 0, stdout=f"{src}/Legacy.cpp\n")

    monkeypatch.setattr(rq.subprocess, "run", grep_source)
    assert rq.locate_source(symbol) == f"{src}/Legacy.cpp"


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
def test_function_pointer_debt_finds_exact_ledger_owner(tmp_path, monkeypatch, layout):
    src = "game" if layout == "bfme1" else "Code"
    rq, _, _ = load(tmp_path, layout, LEDGER, [
        (f"{src}/GameEngine/Loco.cpp", "void Loco::a() {}\n")])

    def unexpected_grep(*args, **kwargs):
        pytest.fail("a matched function owner does not need a literal mangled name")

    monkeypatch.setattr(rq.subprocess, "run", unexpected_grep)
    assert rq.locate_source("?a@Loco@@QAEXXZ") == f"{src}/GameEngine/Loco.cpp"


@pytest.mark.parametrize("sources", [
    ("Missing.cpp",), ("../outside.cpp",), ("Other/Data.cpp",), ("Data.cpp", "Other.cpp")])
def test_invalid_or_ambiguous_function_owner_does_not_fall_back_to_grep(
        tmp_path, monkeypatch, sources):
    symbol = "?callback@@YAXXZ"
    rq, rev, _ = load(tmp_path, "bfme1", [
        (symbol, 0x1000 + i * 16, 8, path) for i, path in enumerate(sources)])
    ledger = rev / "functions.csv"
    ledger.write_text(ledger.read_text().replace("game/Other/", "Other/"))
    for relative in sources:
        if relative != "Missing.cpp":
            path = tmp_path / "game" / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("void callback() {}\n")

    def unexpected_grep(*args, **kwargs):
        pytest.fail("an invalid recorded function owner must not select another source")

    monkeypatch.setattr(rq.subprocess, "run", unexpected_grep)
    assert rq.locate_source(symbol) is None


def test_link_items_serve_placed_unwired_rows_first(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    status = tmp_path / "link_status.csv"
    status.write_text(
        "name,kind,source,retail_rva,size,linked_rva,placed,placement_reason,self_strict,closed_strict,"
        "closed_strict_pilot_rule,pinned_strict,byte_equal,hardcoded,failure_count,failures\n"
        "?ok@@YAXXZ,real,Code/a.cpp,0x00001000,64,0x00001000,1,,1,1,1,1,1,0,0,\n"
        "?far@@YAXXZ,real,Code/a.cpp,0x00002000,500,0x007BBD80,0,retail start violates section alignment,1,1,1,1,0,0,0,\n"
        "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n"
        "?gen@@YAXXZ,gen-funclet,Code/gen_small/u.cpp,0x00004000,9,,0,not COMDAT,0,0,0,0,0,0,0,\n", newline="\n")
    items, note = rq.link_items(status)
    assert [(i["function"], i["why"]) for i in items] == [
        ("?wire@@YAXXZ", "data-back:g_x"), ("?far@@YAXXZ", "retail start violates section alignment")]
    assert "2 row(s)" in note


def test_next_work_serves_repairs_before_new_matches():
    import next_work
    repair = [{"function": "r", "target_rva": "0x1", "size": 4}]
    named = [{"function": "n", "target_rva": "0x2", "size": 4}]
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair)[0] == "gate-debt repair"
    assert next_work.selected_queue(None, [], [], [], [], named, repair=[])[1] == named
    assert next_work.selected_queue("named", [], [], [], [], named, repair=repair)[1] == named
    assert next_work.selected_queue("repair", [], [], [], [], named, repair=repair)[1] == repair


def test_a_removed_debt_line_is_reverified(tmp_path):
    import subprocess
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\nstrnul 0x00002000 ?c@Body@@QAEXXZ\n"),
        ("Code/GameEngine/Loco.cpp", "//\n"), ("Code/GameEngine/Body.cpp", "//\n")])

    def git(*args):
        return subprocess.run(["git", "-C", str(tmp_path), *args], capture_output=True, text=True, check=True)
    git("init", "-q")
    git("add", ".")
    git("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    fail, ok = [sys.executable, "-c", "raise SystemExit(1)"], [sys.executable, "-c", "pass"]
    assert rq.verify_removed(fail) == []                                   # nothing removed
    (rev / "gate_baseline.txt").write_text("strnul 0x00002000 ?c@Body@@QAEXXZ\n", newline="\n")
    git("add", "reverse/gate_baseline.txt")
    got = rq.verify_removed(fail)                                          # credited without a fix
    assert len(got) == 1 and "Code/GameEngine/Loco.cpp" in got[0]
    assert rq.verify_removed(ok) == []                                     # the row really passes
    (tmp_path / "Code/GameEngine/Loco.cpp").write_text("// fixed\n")
    git("add", "Code/GameEngine/Loco.cpp")
    assert rq.verify_removed(fail) == []                                   # staged: the hook builds it


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
def test_stdin_hook_rechecks_removed_debt_in_checkout(tmp_path, layout):
    import subprocess
    source = "game/GameEngine/Loco.cpp" if layout == "bfme1" else "Code/GameEngine/Loco.cpp"
    baseline = ("targets/game/reverse/body_guard_baseline.csv" if layout == "bfme1"
                else "reverse/gate_baseline.txt")
    raw = ("check,target_rva,name,detail\ntail,0x00001000,?a@Loco@@QAEXXZ,mismatch\n"
           if layout == "bfme1" else "tail 0x00001000 ?a@Loco@@QAEXXZ\n")
    load(tmp_path, layout, LEDGER, [
        (source, "// body\n"), (baseline, raw),
        ("tools/build.py", "raise SystemExit(1)\n")])

    def git(*args):
        return subprocess.run(["git", "-C", str(tmp_path), *args], capture_output=True, text=True, check=True)

    git("init", "-q")
    git("add", ".")
    git("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    (tmp_path / baseline).write_text("")
    git("add", baseline)
    env = os.environ.copy()
    env.pop("REPAIR_ROOT", None)
    # Match pre-commit's `git show HEAD:... | python3 - verify-removed`.
    result = subprocess.run([sys.executable, "-", "verify-removed"], cwd=tmp_path,
                            input=(TOOLS / "repair_queue.py").read_text(),
                            capture_output=True, text=True, env=env)
    assert result.returncode == 1
    assert source in result.stderr and "row still fails" in result.stderr


def test_repairs_are_capped_to_one_pick_in_n(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    monkeypatch.delenv("BFME_REPAIR_EVERY", raising=False)
    turns = [rq.repair_turn(owner="seat-a") for _ in range(9)]
    assert sum(turns) == 3 and turns[:3].count(True) == 1                 # default: 1 in 3, rotated
    assert sum(rq.repair_turn(4, owner="seat-b") for _ in range(8)) == 2
    assert all(rq.repair_turn(1, owner="x") for _ in range(3))
    assert not any(rq.repair_turn(0, owner="x") for _ in range(3))
    monkeypatch.setenv("BFME_REPAIR_EVERY", "1")
    assert rq.repair_turn(owner="seat-c")


def test_off_turn_picks_skip_repairs_unless_nothing_else():
    import next_work
    repair = [{"function": "r", "target_rva": "0x1", "size": 4}]
    named = [{"function": "n", "target_rva": "0x2", "size": 4}]
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair, repair_turn=False)[1] == named
    assert next_work.selected_queue(None, [], [], [], [], [], repair=repair, repair_turn=False)[1] == repair
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair, repair_turn=True)[1] == repair


def test_tier_c_and_diffexec_findings_feed_the_repair_queue(tmp_path):
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n"),
        ("reverse/match_tiers.csv", "target_rva,target_size,name,source,tier,reasons\n"
         "0x00001000,64,?a@Loco@@QAEXXZ,Code/GameEngine/Loco.cpp,C,gate:tail\n"
         "0x00002000,32,?c@Body@@QAEXXZ,Code/GameEngine/Body.cpp,C,identity:wrong\n"
         "0x00001080,64,?b@Loco@@QAEXXZ,Code/GameEngine/Loco.cpp,A,\n")])
    dx = tmp_path / "results.jsonl"
    dx.write_text('{"name":"?d@@YAXXZ","rva":"0x00004000","size":9,"source":"Code/d.cpp","verdict":"binding",'
                  '"reason":"objects: call #0: retail rva:0x1 rebuilt rva:0x2"}\n'
                  '{"name":"?e@@YAXXZ","rva":"0x00005000","size":9,"source":"Code/e.cpp","verdict":"binding",'
                  '"reason":"objects: call #0 (twin bodies)"}\n'
                  '{"name":"?f@@YAXXZ","rva":"0x00006000","size":9,"source":"Code/f.cpp","verdict":"none"}\n')
    rq.DIFFEXEC = str(dx)
    items = rq.all_repair_items()
    assert [(i["check"], i["target_rva"]) for i in items] == [
        ("tail", "0x00001000"), ("tier-C", "0x00002000"), ("diffexec-binding", "0x00004000")]
    assert "diffexec.py --row 0x00004000" in items[2]["pass_test"]


def test_boot_smoke_crashes_feed_the_repair_queue(tmp_path):
    rq, rev, src = load(tmp_path, "bfme1", LEDGER, [])
    q = tmp_path / "boot_queue.json"
    q.write_text('{"tool": "boot_smoke", "items": [{"target_rva": "0x00003000", "name": "?g@@YAXXZ", '
                 '"source": "game/g.cpp", "size": 12, "outcome": "crash-at-?g@@YAXXZ", '
                 '"why": "boot smoke crash with this row overlaid alone"}]}')
    rq.BOOT_QUEUE = str(q)
    rq.DIFFEXEC = str(tmp_path / "none.json")
    items = [i for i in rq.all_repair_items() if i["check"] == "boot-crash"]
    assert [(i["target_rva"], i["function"], i["credit"]) for i in items] == [("0x00003000", "?g@@YAXXZ", 12)]
    assert "boot_smoke.py --game-dir SANDBOX --overlay rva:0x00003000" in items[0]["pass_test"]
    rq.BOOT_QUEUE = str(tmp_path / "missing.json")
    assert rq.boot_items() == []


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
@pytest.mark.parametrize("target_eol", [b"\n", b"\r\n"])
@pytest.mark.parametrize("last_eol", [b"\n", b"\r\n", b""])
@pytest.mark.parametrize("returncode", [0, 1])
def test_pass_test_removes_only_target_with_mixed_line_endings(
        tmp_path, monkeypatch, layout, target_eol, last_eol, returncode):
    rq, rev, src = load(tmp_path, layout, LEDGER)
    if layout == "bfme1":
        path = rev / "body_guard_baseline.csv"
        header = b"check,target_rva,name,detail\r\n"
        line = "tail,0x00001000,?a@Loco@@QAEXXZ,tail mismatch"
        other = b"strnul,0x00002000,?c@Body@@QAEXXZ,literal mismatch"
    else:
        path = rev / "gate_baseline.txt"
        header = b"# gate debt\r\n"
        line = "tail 0x00001000 ?a@Loco@@QAEXXZ"
        other = b"strnul 0x00002000 ?c@Body@@QAEXXZ"
    raw = header + line.encode() + target_eol + other + last_eol
    expected = header + other + last_eol
    path.write_bytes(raw)
    calls = []

    def run_gate(command, **kwargs):
        # The normal checker must see the exemption removed, while all other
        # bytes (including a missing final newline) retain their original form.
        assert command == [sys.executable, str(tmp_path / "tools/build.py"),
                           f"{src}/GameEngine/Loco.cpp"]
        assert path.read_bytes() == expected
        calls.append(command)
        return rq.subprocess.CompletedProcess(command, returncode)

    monkeypatch.setattr(rq.subprocess, "run", run_gate)
    ok, _ = rq.pass_test(line)
    assert len(calls) == 1
    assert ok == (returncode == 0)
    assert path.read_bytes() == (expected if ok else raw)
