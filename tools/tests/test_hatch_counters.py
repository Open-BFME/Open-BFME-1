"""hatch_counters.py: the escape-hatch register only shrinks by hand; growth needs a
tool allowance tied to the staged blob; a 2x jump in 24 h freezes allowances until a
Verifier-Change lift; the retail inventories are tool-owned."""
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import hatch_counters as hc  # noqa: E402

DAY = 24 * 3600
T0 = 1_900_000_000          # fixture clock: commits are dated relative to this

LAYOUTS = {
    "bfme2": {"src": "Code/GameEngine/a.cpp", "src2": "Code/GameEngine/b.cpp", "rev": "reverse",
              "base": "reverse/hatch_baseline.tsv"},
    "bfme1": {"src": "game/GameEngine/a.cpp", "src2": "game/GameEngine/b.cpp", "rev": "targets/game/reverse",
              "base": "targets/game/reverse/hatch_baseline.tsv"},
}

SOURCE = """\
#include "x.h"
#pragma optimize("", off)
//#pragma optimize("s", on)
#pragma comment(linker, "/alternatename:?f@@YAXXZ=?g@@YAXXZ")
// ?Foo::bar present-unmatched
// class-gate: allow AsciiString caller view
extern int g_Va00A1B2C3;
__declspec(selectany) int s_x = 1;
void f() { __asm { __emit 0x90 } g_Va00A1B2C3 = 1; }
"""

STUB_INVENTORY = '''
def verify_staged(paths):
    import subprocess
    errs = []
    for p in paths:
        got = subprocess.run(["git", "show", ":" + p], capture_output=True, text=True).stdout
        if got != "generated\\n":
            errs.append(p + " edited by hand")
    return errs
'''


class Repo:
    def __init__(self, root, layout):
        self.root, self.lay = root, LAYOUTS[layout]

    def git(self, *args, when=T0, check=True):
        env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
                   GIT_COMMITTER_EMAIL="", GIT_AUTHOR_DATE="@%d +0000" % when,
                   GIT_COMMITTER_DATE="@%d +0000" % when)
        got = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True, env=env)
        if check and got.returncode:
            raise AssertionError(got.stderr)
        return got.stdout

    def write(self, rel, text):
        p = self.root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text, newline="\n")

    def read(self, rel):
        return (self.root / rel).read_text()

    def tool(self, *args, now=T0 + 60):
        env = dict(os.environ, HATCH_NOW=str(now))
        env.pop("HATCH_ROOT", None)
        return subprocess.run([sys.executable, str(self.root / "tools/hatch_counters.py"), *args],
                              cwd=self.root, capture_output=True, text=True, env=env)

    def commit(self, msg="x", when=T0, paths=None):
        self.git("add", "--", *(paths or ["."]))
        self.git("commit", "-q", "--allow-empty", "-m", msg, when=when)


@pytest.fixture(params=sorted(LAYOUTS))
def repo(tmp_path, request):
    r = Repo(tmp_path, request.param)
    r.git("init", "-q")
    (tmp_path / "tools").mkdir()
    shutil.copy(TOOLS / "hatch_counters.py", tmp_path / "tools")
    (tmp_path / "tools" / "retail_inventory.py").write_text(STUB_INVENTORY)
    r.write(r.lay["src"], SOURCE)
    r.write(r.lay["rev"] + "/symbols.csv", "name,address,notes\n?a@@3HA,0x00001000,pin\n")
    r.write(r.lay["rev"] + "/functions.csv",
            "name,export_rva,target_rva,target_size,source,status,notes\n"
            "?f@@YAXXZ,,0x00002000,5,%s,matched,gen-alias;object-symbol=?f@@YAXXZ\n" % r.lay["src"])
    r.git("add", ".")
    assert r.tool("--write-baseline").returncode == 0
    r.commit("init", when=T0 - 2 * DAY)
    return r


def staged(repo, now=T0 + 60):
    return repo.tool("--staged", now=now)


def test_scan_counts_each_hatch_and_skips_commented_code():
    got = hc.scan("Code/a.cpp", SOURCE)
    assert {k[0] for k in got} == {"pragma_optimize", "alternatename", "present_unmatched", "class_gate_allow",
                                   "address_global", "selectany", "emit"}
    assert got[("address_global", "Code/a.cpp", "g_Va00A1B2C3")] == 2
    assert got[("pragma_optimize", "Code/a.cpp", '"",off')] == 1        # the //#pragma line is not counted
    assert hc.scan("Code/d.asm", "  db 55h, 8Bh, 0ECh ; c\n  db 'ab', 0\n") == {("asm_bytes", "Code/d.asm", "*"): 6}


def test_baseline_parse_takes_lowest_duplicate_and_round_trips():
    text = "emit\tCode/a.cpp\t*\t5\nemit\tCode/a.cpp\t*\t3\npin\tr/s.csv\tx@1\t1\tallow=abc\n"
    counts, allow = hc.parse(text)
    assert counts[("emit", "Code/a.cpp", "*")] == 3 and allow == {("pin", "r/s.csv", "x@1"): "abc"}
    assert hc.parse(hc.render(counts, allow)) == (counts, allow)


# ---- negative controls: correct work passes

def test_unrelated_and_shrinking_commits_pass(repo):
    repo.write(repo.lay["src2"], "int clean() { return 0; }\n")
    repo.git("add", ".")
    assert staged(repo).returncode == 0
    repo.write(repo.lay["src"], SOURCE.replace("__emit 0x90 ", ""))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "down to 0" in got.stderr          # slack is noted, not refused


def test_tightening_the_register_passes(repo):
    repo.write(repo.lay["src"], SOURCE.replace("__emit 0x90 ", ""))
    assert repo.tool("--update").returncode == 0
    assert "\temit\t" not in "\t" + repo.read(repo.lay["base"])
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_move_between_files_via_update_passes(repo):
    repo.git("mv", repo.lay["src"], repo.lay["src2"])
    assert staged(repo).returncode == 1                                   # moved without the register
    assert repo.tool("--update").returncode == 0                          # totals unchanged: a move
    repo.git("add", ".")
    assert staged(repo).returncode == 0


# ---- positive controls: each of these passed before this gate existed

@pytest.mark.parametrize("line", [
    "void h() { __asm { __emit 0x90 } }\n",
    '#pragma comment(linker, "/alternatename:?h@@YAXXZ=?g@@YAXXZ")\n',
    "#pragma optimize(\"gsy\", on)\n",
    "__declspec(selectany) int s_y = 2;\n",
    "int g_Rva00ABCDEFThing;\n",
    "// ?Baz::qux present-unmatched\n",
    "// class-gate: allow Thing because\n",
])
def test_new_occurrence_is_refused(repo, line):
    repo.write(repo.lay["src"], SOURCE + line)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "escape hatches grew" in got.stderr


def test_new_pin_and_alias_row_are_refused(repo):
    repo.write(repo.lay["rev"] + "/symbols.csv", repo.read(repo.lay["rev"] + "/symbols.csv") + "?b@@3HA,0x00001004,\n")
    repo.git("add", ".")
    assert "pin +1" in staged(repo).stderr
    repo.git("reset", "-q")
    repo.write(repo.lay["rev"] + "/functions.csv", repo.read(repo.lay["rev"] + "/functions.csv")
               + "?g@@YAXXZ,,0x00002000,5,x.cpp,matched,object-symbol=?f@@YAXXZ\n")
    repo.git("add", ".")
    assert "object_symbol +1" in staged(repo).stderr


def test_hand_raised_register_line_is_refused(repo):
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n")
    base = repo.read(repo.lay["base"]).replace("\t*\t1\n", "\t*\t2\n")
    repo.write(repo.lay["base"], base)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr


def test_lowered_line_is_reverified(repo):
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], "\n".join(l for l in base.splitlines() if not l.startswith("emit\t")) + "\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "emit +1" in got.stderr                # the occurrence is still there


def test_tool_allowance_admits_growth_bound_to_the_staged_blob(repo):
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n")
    assert repo.tool("--update").returncode != 0                          # growth needs --allow
    assert repo.tool("--allow", repo.lay["src"], "--reason", "x87 shape the compiler cannot emit").returncode == 0
    repo.git("add", ".")
    assert staged(repo).returncode == 0
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\nint more;\n")
    repo.git("add", repo.lay["src"])                                      # content changed after --allow
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr


def test_inventory_files_are_tool_owned(repo):
    inv = repo.lay["rev"] + "/retail_inventory/"
    repo.write(inv + "fold_list.csv", "generated\n")
    repo.git("add", ".")
    assert staged(repo).returncode == 0
    repo.write(inv + "fold_list.csv", "generated\nforged row\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "edited by hand" in got.stderr


# ---- anomaly freeze

def _allow_emits(repo, n, when, msg="allow", tool_now=None):
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + "void e%d() { __asm { %s } }\n"
               % (when, " ".join(["__emit 0x90"] * n)))
    got = repo.tool("--allow", repo.lay["src"], "--reason", "fixture growth step", now=tool_now or when + 1)
    if got.returncode == 0 and tool_now is None:
        repo.commit(msg, when=when)
    return got


def test_freeze_after_doubling_and_lift(repo):
    assert _allow_emits(repo, 9, T0 - 30 * 3600).returncode == 0       # emit total 10, 30 h ago
    assert _allow_emits(repo, 8, T0 - 3600).returncode == 0            # 18 <= 2 x 10: still fine
    got = _allow_emits(repo, 5, T0)                                     # 23 > 20: frozen
    assert got.returncode != 0 and "frozen" in got.stderr
    # an allowance written before the jump (no reference yet) is still refused by the gate now
    assert repo.tool("--allow", repo.lay["src"], "--reason", "fixture growth step", now=T0 - 60 * 3600).returncode == 0
    repo.git("add", ".")
    assert "FROZEN" in staged(repo, now=T0 + 60).stderr
    repo.git("reset", "-q", "--hard", "HEAD")
    repo.commit("Lift\n\nVerifier-Change: hatch-freeze-lift emit vetted the x87 batch", when=T0 + 10)
    assert _allow_emits(repo, 5, T0 + 20).returncode == 0              # reference is now the lift (18)
    assert _allow_emits(repo, 20, T0 + 30).returncode != 0             # 43 > 2 x 18: frozen again


def test_no_history_means_no_freeze(repo):
    assert hc.frozen("emit", 100, {}) is False
    assert hc.frozen("emit", 4, {"emit": 0}) is False                  # below FREEZE_MIN
    assert hc.frozen("emit", 21, {"emit": 10}) is True


def test_register_cannot_be_deleted_or_introduced_wrong(repo):
    repo.git("rm", "-q", "--cached", repo.lay["base"])
    got = staged(repo)
    assert got.returncode == 1 and "deleted" in got.stderr
    repo.git("reset", "-q", "--hard", "HEAD")
    first = Repo(repo.root / "intro", "bfme2")                         # a tree that introduces the register
    (repo.root / "intro").mkdir()
    first.git("init", "-q")
    (first.root / "tools").mkdir(parents=True)
    shutil.copy(TOOLS / "hatch_counters.py", first.root / "tools")
    first.write("Code/a.cpp", SOURCE)
    first.write("reverse/hatch_baseline.tsv", "emit\tCode/a.cpp\t*\t1\n")   # understates the tree
    first.git("add", ".")
    got = staged(first)
    assert got.returncode == 1 and "does not match the tree" in got.stderr
    assert first.tool("--write-baseline").returncode == 1                # refuses: a register exists
    (first.root / "reverse/hatch_baseline.tsv").unlink()
    assert first.tool("--write-baseline").returncode == 0
    first.git("add", ".")
    assert staged(first).returncode == 0


def _set_mode(repo, mode):
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: " + mode).replace(
        "# mode: shadow", "# mode: " + mode))


def test_shadow_mode_reports_growth_without_refusing(repo):
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: shadow"))
    repo.git("add", ".")
    assert "may not go back" in staged(repo).stderr                    # the fixture register says enforce
    repo.write(repo.lay["base"], base.replace("# mode: enforce\n", ""))
    repo.commit("legacy register", when=T0 - DAY)
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: shadow"))
    repo.commit("shadow", when=T0 - DAY + 1)
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "SHADOW (not enforced): emit +1" in got.stderr


def test_mode_may_go_shadow_to_enforce_but_not_back(repo):
    assert "# mode: enforce" in repo.read(repo.lay["base"])
    _set_mode(repo, "shadow")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "may not go back to shadow" in got.stderr
    repo.git("reset", "-q", "--hard", "HEAD")
    # a register without a mode line (written before modes existed) may be put in shadow once
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], base.replace("# mode: enforce\n", ""))
    repo.commit("legacy register", when=T0 - DAY)
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: shadow"))
    repo.commit("shadow", when=T0 - DAY + 1, paths=[repo.lay["base"]])
    _set_mode(repo, "enforce")
    repo.git("add", ".")
    assert staged(repo).returncode == 0
