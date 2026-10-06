"""match_tiers: every ledger row lands in exactly one of A/B/C/G, deterministically.

The positive controls are rows today's byte gate accepts although they are wrong
(a wrong callee binding, a contradicted name, a baselined gate failure, a
diffexec logic divergence): each must grade C, never A. The negative controls are
correct rows, which must stay A.
"""
import importlib.util
import json
import struct
import subprocess
import sys
import types
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("match_tiers", TOOLS / "match_tiers.py")
mt = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mt)

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def row(name, rva, size, source="Code/A.cpp", notes=""):
    return {"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}", "target_size": str(size),
            "source": source, "status": "matched", "notes": notes}


def ledger_text(rows):
    return HEADER + "".join(f"{r['name']},,{r['target_rva']},{r['target_size']},{r['source']},matched,{r['notes']}\n"
                            for r in rows)


STUB_PROGRESS = types.SimpleNamespace(
    naked_cpp_rows_at=lambda matched, ref: {k for k, (_, src) in matched.items() if "Lift" in src},
    source_lane=lambda source, notes, naked: (
        "library" if source.endswith(".lib") else "dump" if naked or source.endswith(".asm")
        else "generated" if "/gen_small/" in source or "gen-" in notes else "authored"))


def tiers(graded):
    return {g["name"]: g["tier"] for g in graded}


def git(root, *args):
    subprocess.run(["git", *args], cwd=root, check=True, capture_output=True)


@pytest.fixture
def bfme2(tmp_path):
    """A two-commit BFME2-shaped repo: the register scanned commit 1."""
    rows = [row("good", 0x1000, 16), row("wrongcallee", 0x1010, 16), row("unowned", 0x1020, 16),
            row("gated", 0x1030, 16), row("edited", 0x1040, 16, "Code/B.cpp"),
            row("gen", 0x1050, 8, "Code/gen_small/G.cpp", "gen-funclet"),
            row("alias", 0x1058, 8, notes="gen-alias"), row("lib", 0x1060, 32, "vendor/x.lib"),
            row("lifted", 0x1080, 16, "Code/Lift.cpp")]
    (tmp_path / "reverse").mkdir()
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/B.cpp").write_text("int b;\n")
    (tmp_path / "reverse/functions.csv").write_text(ledger_text(rows[:-1]))
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "scan")
    (tmp_path / "Code/B.cpp").write_text("int b = 1;\n")
    (tmp_path / "reverse/functions.csv").write_text(ledger_text(rows))
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "later")
    (tmp_path / "register.tsv").write_text(
        "# mode: shadow\n"
        "Code/A.cpp\twrongcallee\t?other@@YAXXZ\t0x00002000\twrong\n"
        "Code/A.cpp\tunowned\t?nobody@@YAXXZ\t0x00003000\tunowned\n"
        "Code/A.cpp\talias\t?x@@YAXXZ\t0x00004000\twrong\n")
    (tmp_path / "reverse/gate_baseline.txt").write_text("# debt\ntail 0x00001030 gated\n")
    return tmp_path, rows


def grade_bfme2(root, rows, ref="HEAD~1", diffexec=None):
    ev = mt.Evidence()
    mt.gate_baseline(ev, root / "reverse/gate_baseline.txt")
    mt.code_identity(ev, root / "register.tsv", rows, ref, root)
    if diffexec:
        mt.diffexec(ev, diffexec)
    return mt.grade(rows, mt.lanes(rows, STUB_PROGRESS), ev)


def test_bfme2_positive_and_negative_controls(bfme2):
    root, rows = bfme2
    graded = grade_bfme2(root, rows)
    t = tiers(graded)
    assert t["good"] == "A"                          # negative control: proven bindings stay A
    assert t["wrongcallee"] == "C"                   # positive: byte-matching wrong callee
    assert t["gated"] == "C"                         # positive: excused by the gate baseline
    assert t["unowned"] == "B"
    assert t["edited"] == "B"                        # source changed after the scan
    assert {t["gen"], t["alias"], t["lib"], t["lifted"]} == {"G"}
    alias = next(g for g in graded if g["name"] == "alias")
    assert alias["reasons"].startswith("gen-alias-masked") and "C-evidence code:wrong" in alias["reasons"]


def test_naked_lift_is_g_and_lanes_are_kept(bfme2):
    root, rows = bfme2
    graded = {g["name"]: g for g in grade_bfme2(root, rows, ref="HEAD")}
    assert graded["lifted"]["tier"] == "G" and graded["lifted"]["reasons"] == "emit-lift"
    assert graded["lib"]["reasons"] == "lib-member" and graded["lib"]["lane"] == "library"


def test_enforce_mode_register_needs_no_ref(bfme2):
    root, rows = bfme2
    reg = root / "register.tsv"
    reg.write_text(reg.read_text().replace("shadow", "enforce"))
    ev = mt.Evidence()
    mt.code_identity(ev, reg, rows, None, root)
    t = tiers(mt.grade(rows, mt.lanes(rows, STUB_PROGRESS), ev))
    assert t["edited"] == "A" and t["wrongcallee"] == "C"


def test_no_binding_data_caps_at_b(bfme2):
    _, rows = bfme2
    t = tiers(mt.grade(rows, mt.lanes(rows, STUB_PROGRESS), mt.Evidence()))
    assert t["good"] == "B"


def test_diffexec_logic_divergence_is_c_env_is_not(bfme2, tmp_path):
    root, rows = bfme2
    dx = tmp_path / "dx.json"
    dx.write_text(json.dumps({"rows": [{"target_rva": "0x00001000", "name": "good", "verdict": "env"},
                                       {"target_rva": 0x1000, "verdict": "regalloc"}]}))
    assert tiers(grade_bfme2(root, rows, diffexec=dx))["good"] == "A"
    dx.write_text(json.dumps([{"rva": "0x00001000", "class": "logic"}]))
    assert tiers(grade_bfme2(root, rows, diffexec=dx))["good"] == "C"


def test_output_is_deterministic_and_summary_counts_overlap_once(bfme2):
    root, rows = bfme2
    a = mt.render(grade_bfme2(root, rows))
    b = mt.render(grade_bfme2(root, list(reversed(rows))))
    assert a == b
    graded = [{"tier": "A", "target_rva": "0x00001000", "target_size": "16", "reasons": ""},
              {"tier": "G", "target_rva": "0x00001008", "target_size": "16", "reasons": "generated"}]
    lines = {ln.split()[0]: ln.split()[1:] for ln in mt.summary(graded).splitlines()[1:]}
    assert lines["A"] == ["1", "16", "16"]
    assert lines["G"] == ["1", "16", "8"]           # the overlap counts once, under A


# ---------------------------------------------------------------- BFME1
class FakeOracle:
    """Two ILT slots at first_thunk: slot 0 -> 0x2000, slot 1 -> 0x3000."""
    first_thunk = mt.IMAGE_BASE + 0x1005
    target = [0x2000, 0x3000]

    def check(self, name, rva):
        return ("CONTRADICTED" if name.startswith("?bad") else "CONFIRMED"), 1e-4, ""


FAKE_MOD = types.SimpleNamespace(tier=lambda n: "placeholder" if "Rva" in n else "real",
                                 CONTRADICTED="CONTRADICTED")


def call(at, target):
    return b"\xe8" + struct.pack("<i", target - (at + 5)) + b"\xc3"


def test_bfme1_bindings_from_retail(tmp_path):
    pytest.importorskip("capstone")
    rows = [row("?caller_ok@@YAXXZ", 0x5000, 6), row("?caller_thunk_bad@@YAXXZ", 0x5010, 6),
            row("?caller_unowned@@YAXXZ", 0x5020, 6), row("?caller_dir32@@YAXXZ", 0x5030, 6),
            row("?good@@YAXXZ", 0x2000, 1), row("?bad@@YAXXZ", 0x3000, 1),
            row("?Rva00005040@@YAXXZ", 0x5040, 6), row("?reads_real@@YAXXZ", 0x5050, 6, "Code/Clean.cpp"),
            row("?reads_new@@YAXXZ", 0x5060, 6)]
    image = {0x5000: call(0x5000, 0x2000), 0x5010: call(0x5010, 0x1005 + 5),   # via ILT slot 1 -> 0x3000
             0x5020: call(0x5020, 0x4444), 0x5030: b"\xa1" + struct.pack("<I", mt.IMAGE_BASE + 0x9000) + b"\xc3",
             0x2000: b"\xc3", 0x3000: b"\xc3", 0x5040: call(0x5040, 0x5000),
             0x5050: b"\xa1" + struct.pack("<I", mt.IMAGE_BASE + 0x9000) + b"\xc3",
             0x5060: b"\xa1" + struct.pack("<I", mt.IMAGE_BASE + 0xA000) + b"\xc3"}
    ev = mt.Evidence()
    base = tmp_path / "identity_baseline.txt"
    base.write_text("one_identity.surplus = 1\n@ one_identity.surplus 0x00005040 ?Rva00005040@@YAXXZ\n")
    mt.identity_baseline(ev, base)
    ilt = (FakeOracle(), FAKE_MOD)
    mt.own_name_ilt(ev, rows, ilt)
    body = tmp_path / "body_guard_baseline.csv"
    body.write_text("check,target_rva,name,detail\n"
                    "dir32,0x00409000,?g_dup@@3HA,retail 0x00409000 is already recorded as ?g_real@@3HA\n"
                    "dir32,0x0040A000,?g_new@@3HA,nothing in the ledger owns 0x0040A000. Give ...\n")
    data_bad = mt.body_baseline(ev, body)
    sources = {"Code/A.cpp": "extern int g_dup; extern int g_new;", "Code/Clean.cpp": "extern int g_real;"}
    mt.bfme1_bindings(ev, rows, set(), data_bad, lambda rva, size: image[rva][:size],
                      0x1000, 0x8000, ilt, pins=[("?pin@@YAXXZ", 0x7000)], read_source=sources.get)
    t = tiers(mt.grade(rows, mt.lanes(rows, STUB_PROGRESS), ev))
    assert t["?caller_ok@@YAXXZ"] == "A"             # negative control
    assert t["?good@@YAXXZ"] == "A"
    assert t["?bad@@YAXXZ"] == "C"                   # positive: own name contradicted by the oracle
    assert t["?caller_thunk_bad@@YAXXZ"] == "B"      # callee through the ILT carries a contradicted name
    assert t["?caller_unowned@@YAXXZ"] == "B"
    assert t["?caller_dir32@@YAXXZ"] == "C"          # spells a second name for a recorded datum
    assert t["?reads_real@@YAXXZ"] == "A"            # same datum, recorded name: not implicated
    assert t["?reads_new@@YAXXZ"] == "B"             # a datum nothing owns: unproven, not wrong
    assert t["?Rva00005040@@YAXXZ"] == "C"           # keyed identity debt


def test_layout_detects_both_repos(tmp_path):
    (tmp_path / "targets/game/reverse").mkdir(parents=True)
    (tmp_path / "targets/game/reverse/functions.csv").write_text(HEADER)
    assert mt.layout(tmp_path)["game"] == "bfme1"
    assert mt.layout(tmp_path / "nowhere")["game"] == "bfme2"
