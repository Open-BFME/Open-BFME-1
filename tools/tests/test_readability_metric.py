"""The six readability axes, the per-blob cache, and the --staged commit trailer.

The tree here is small enough to count by hand, and every expected number below
is written as the arithmetic that produced it rather than as a magic constant, so
a changed axis definition fails with a readable diff instead of an opaque one.

Two properties get their own tests because nothing else would catch them:

  * the cache is keyed by git blob hash and an entry found under any other hash
    is recomputed, never served -- a metric that silently reports last week's
    counters for an edited file is worse than no metric;
  * --staged measures the INDEX against HEAD, not the worktree. It is the number
    that goes into a commit message, so a worktree edit the commit does not carry
    must not move it;
  * --staged names only the axes whose delta survives the rounding it prints at.
    Dropping one file shifts every denominator, and axes rendered "-0.00 pp"
    make a commit that moved one axis read as one that moved four.

The fixture ledger deliberately mixes \\r\\r\\n, \\r\\n and bare \\n terminators.
functions.csv does the same (tools/ledger_io.py:1-14) and every naive split has
silently dropped or invented rows there; here a naive split would move Ident and
Local off their hand-computed values.
"""
import builtins
import importlib.util
import json
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


metric = _load("readability_metric")

AREA = "Code/GameEngine/Source/Common"

# 7 lines. One pad member, one named member, two virtual slots of which v12 is
# anonymous, and one class body that does NOT count against SSoT: it is in a
# header, which is where a shared type belongs.
ALPHA_H = """class Alpha {
        virtual void Draw();
        virtual void v12();

        char pad[8];
        int m_count;
};
"""

# The same 7 lines with the 8-byte pad split into two named 4-byte fields. Line
# count is deliberately unchanged -- the blank line the pad was separated by is
# what the second field takes -- so this edit moves Types and nothing else.
SPLIT_H = """class Alpha {
        virtual void Draw();
        virtual void v12();
        int m_left;
        int m_right;
        int m_count;
};
"""

# 12 lines, two of them raw assembly, one pad member, one named member, and one
# class body opened inside a TU -- the shim shape the SSoT axis counts.
ALPHA_CPP = """#include "alpha.h"

struct LocalPatch {
        char pad[8];
        int m_flag;
};

void Alpha::Draw()
{
        __asm { nop }
        __emit 0x90
}
"""

# 6 lines and nothing any axis counts except its line total and its .cpp-ness.
GAMMA_CPP = """#include "alpha.h"

void Alpha::Reset()
{
        m_flag = 0;
}
"""

# 5 lines that no axis counts but every denominator does -- padding for the one
# test that needs a tree big enough for a dropped file to shift the denominators
# by less than the trailer's printed precision.
FILLER = """#include "alpha.h"

void filler{n}(void)
{{
}}
"""

LEDGER_PATH = "reverse/functions.csv"


def ledger(reset_lives_in=f"{AREA}/gamma.cpp"):
    """The fixture ledger, with Reset's owning file as the one knob. Repointing
    it at alpha.cpp is a merge: gamma.cpp stops being a one-function file."""
    return b"".join(payload + terminator for payload, terminator in (
        (b"name,export_rva,target_rva,target_size,source,status,notes", b"\r\n"),
        (f"?d_00401000@@YAXXZ,,0x00401000,16,{AREA}/alpha.cpp,matched,".encode(), b"\r\r\n"),
        (f"?Draw@Alpha@@UAEXXZ,,0x00401020,16,{AREA}/alpha.cpp,matched,".encode(), b"\n"),
        (f"?Init@Alpha@@QAEXXZ,,0x00401040,16,{AREA}/alpha.cpp,matched,".encode(), b"\r\n"),
        (f"?Reset@Alpha@@QAEXXZ,,0x00401060,16,{reset_lives_in},matched,".encode(), b"\r\r\n"),
    ))


LEDGER = ledger()

# Hand-computed over the three sources above. `lines` counts split("\n") pieces,
# so a file of N newline-terminated lines contributes N + 1: 8 + 13 + 7 = 28.
BODY = 100.0 * (1 - 2 / 28)     # 2 __asm/__emit lines out of 28
IDENT = 100.0 * (1 - 1 / 4)     # 1 of 4 ledger names is address-derived
TYPES = 100.0 * (1 - 2 / 4)     # 2 char pad[N] against 2 m_ fields
IFACE = 100.0 * (1 - 1 / 2)     # v12 of {Draw, v12} is an anonymous slot
LOCAL = 100.0 * (1 - 1 / 2)     # gamma.cpp holds 1 of the 2 files' only function
SSOT = 100.0 * (1 - 1 / 3)      # 1 TU-local class body against 2 .cpp files
EXPECTED = (BODY, IDENT, TYPES, IFACE, LOCAL, SSOT)

SPLIT_TYPES = 100.0 * (1 - 1 / 5)   # 1 char pad[N] against 4 m_ fields
TRAILER = "readability: Types 50.0 -> 80.0 (+30.00 pp), files +0\n"


def world(tmp_path, header=ALPHA_H, fillers=0):
    """A tracked fixture tree. git ls-files/hash-object drive the tool, so the
    sources have to be in an index, not merely on disk."""
    root = (tmp_path / "repo").resolve()
    (root / AREA).mkdir(parents=True)
    (root / "reverse").mkdir()
    (root / AREA / "alpha.h").write_text(header)
    (root / AREA / "alpha.cpp").write_text(ALPHA_CPP)
    (root / AREA / "gamma.cpp").write_text(GAMMA_CPP)
    for n in range(fillers):
        (root / AREA / f"filler{n}.cpp").write_text(FILLER.format(n=n))
    (root / LEDGER_PATH).write_bytes(LEDGER)
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    stage(root, "Code", "reverse")
    return root


def stage(root, *paths):
    subprocess.run(["git", "-C", str(root), "add", "--", *paths], check=True)


def commit(root):
    subprocess.run(["git", "-C", str(root), "-c", "user.email=fixture@example.com",
                    "-c", "user.name=Fixture", "commit", "-q", "-m", "fixture"],
                   check=True)


def blob_of(root, path):
    return subprocess.run(["git", "-C", str(root), "hash-object", "--", path],
                          capture_output=True, text=True, check=True).stdout.strip()


def measure(root):
    """The six whole-tree axes, leaving the cache on disk as a real run would."""
    cache = metric.Cache(root)
    areas, _tracked = metric.measure_worktree(root, cache)
    cache.save()
    return metric.axes(metric.totals(areas))


def cli(root, *args):
    return subprocess.run([sys.executable, str(TOOLS / "readability_metric.py"),
                           "--root", str(root), *args], capture_output=True, text=True)


def test_six_axes_over_a_hand_computed_tree(tmp_path):
    assert measure(world(tmp_path)) == pytest.approx(EXPECTED)


def test_a_cache_entry_under_another_hash_is_recomputed_never_served(tmp_path):
    root = world(tmp_path)
    assert measure(root) == pytest.approx(EXPECTED)

    counts = root / "build" / "readability" / "counts.json"
    header_blob = blob_of(root, f"{AREA}/alpha.h")
    stored = json.loads(counts.read_text())
    assert header_blob in stored["files"]
    # Re-file the header's counters under a hash that is not the header's, and
    # make them absurd: a lookup that ignores the hash would report them.
    stored["files"].pop(header_blob)
    stored["files"]["0" * 40] = dict.fromkeys(metric.scan(ALPHA_H), 999)
    counts.write_text(json.dumps(stored))
    assert measure(root) == pytest.approx(EXPECTED)

    # Same rule the other way round: the entry for the pre-edit content survives
    # in the cache and must not be served for the edited file.
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    assert measure(root)[2] == pytest.approx(SPLIT_TYPES)
    assert header_blob in json.loads(counts.read_text())["files"]


@pytest.mark.skipif(os.geteuid() == 0, reason="root reads through chmod 000")
def test_an_unreadable_source_aborts_instead_of_totalling_the_rest(tmp_path):
    root = world(tmp_path)
    blocked = root / AREA / "alpha.cpp"
    blocked.chmod(0o000)
    done = cli(root)
    assert done.returncode != 0
    assert str(blocked) in done.stderr
    assert "ALL Code/" not in done.stdout


def test_a_warm_run_opens_no_file_it_already_has_counters_for(tmp_path, capsys,
                                                              monkeypatch):
    root = world(tmp_path)
    metric.main(["--root", str(root)])
    first = capsys.readouterr().out

    real_open = builtins.open

    def guarded(file, *args, **kwargs):
        target = Path(file).resolve()
        if target.is_relative_to(root) and not target.is_relative_to(root / "build"):
            raise AssertionError(f"warm run opened {target}")
        return real_open(file, *args, **kwargs)

    monkeypatch.setattr(builtins, "open", guarded)
    metric.main(["--root", str(root)])
    assert capsys.readouterr().out == first


def test_splitting_a_pad_moves_types_and_leaves_the_other_five(tmp_path):
    root = world(tmp_path)
    before = measure(root)
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    after = measure(root)
    assert after[2] == pytest.approx(SPLIT_TYPES)
    assert before[2] == pytest.approx(TYPES)
    assert after[:2] + after[3:] == pytest.approx(before[:2] + before[3:])


def test_staged_trailer_names_only_the_axis_that_moved(tmp_path):
    root = world(tmp_path)
    commit(root)
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    stage(root, f"{AREA}/alpha.h")
    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stdout == TRAILER


def test_staged_measures_the_index_not_the_worktree(tmp_path):
    root = world(tmp_path)
    commit(root)
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    stage(root, f"{AREA}/alpha.h")
    (root / AREA / "alpha.h").write_text(
        SPLIT_H.replace("        int m_count;\n",
                        "        int m_count;\n        int m_extra;\n"))

    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stdout == TRAILER
    # ...and the edit really would have moved the number, had the tool read it.
    assert measure(root)[2] == pytest.approx(100.0 * (1 - 1 / 6))


# SSoT is the tightest of the six against a dropped .cpp: its shift is
# 100 / ((F + 2)(F + 3)) points, so F = 200 puts it at 0.0024 -- real, and half
# an order of magnitude under the 0.005 the trailer's 2 decimals can show.
FILLERS = 200


def merged(tmp_path):
    """A merge commit in miniature, staged: Reset's ledger row repointed onto
    alpha.cpp so gamma.cpp stops being a one-function file, and a donor dropped.
    Local moves by 50 points; every other denominator only wobbles."""
    root = world(tmp_path, fillers=FILLERS)
    commit(root)
    (root / LEDGER_PATH).write_bytes(ledger(f"{AREA}/alpha.cpp"))
    subprocess.run(["git", "-C", str(root), "rm", "-q", "--", f"{AREA}/filler0.cpp"],
                   check=True)
    stage(root, LEDGER_PATH)
    return root


def staged_sides(root):
    """The two axis tuples --staged compares: HEAD, then the staged index."""
    cache = metric.Cache(root)
    return (metric.axes(metric.totals(metric.measure_blobs(root, "HEAD", cache))),
            metric.axes(metric.totals(metric.measure_blobs(root, None, cache))))


def test_a_denominator_shift_below_the_printed_precision_is_not_named(tmp_path):
    root = merged(tmp_path)
    head, index = staged_sides(root)
    for axis in (0, 5):   # Body and SSoT really moved -- just below 0.005 points
        assert 0 < abs(index[axis] - head[axis]) < 0.005
    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stdout == "readability: Local 50.0 -> 100.0 (+50.00 pp), files -1\n"


def test_a_commit_that_only_drops_files_still_reports_them(tmp_path):
    root = world(tmp_path, fillers=FILLERS)
    commit(root)
    subprocess.run(["git", "-C", str(root), "rm", "-q", "--", f"{AREA}/filler0.cpp"],
                   check=True)
    assert cli(root, "--staged").stdout == "readability: files -1\n"


def test_a_commit_that_moves_nothing_says_so(tmp_path):
    root = world(tmp_path)
    commit(root)
    assert cli(root, "--staged").stdout == "readability: no measurable change\n"


def test_a_cold_scan_says_so_on_stderr_and_a_warm_one_is_silent(tmp_path):
    """A cold cache scans every source, which is minutes of no output and reads
    as a hang -- a fresh worktree's first run was mistaken for a blocked build
    lock. It gets one stderr line, and only stderr: stdout carries the trailer
    into commit messages and is asserted on elsewhere, so it must not move."""
    root = world(tmp_path, fillers=metric.SCAN_NOTICE_MIN + 5)

    cold = cli(root)
    assert cold.returncode == 0, cold.stderr
    assert "cold cache" in cold.stderr
    assert cold.stderr.count("\n") == 1, f"expected one line, got {cold.stderr!r}"

    warm = cli(root)
    assert warm.returncode == 0, warm.stderr
    assert warm.stderr == ""
    assert warm.stdout == cold.stdout


def test_a_handful_of_changed_files_scans_quietly(tmp_path):
    """The per-commit case must stay silent, or the notice becomes noise on every
    commit and stops meaning anything."""
    root = world(tmp_path, fillers=metric.SCAN_NOTICE_MIN + 5)
    commit(root)
    cli(root)                                   # warm the cache
    (root / AREA / "filler0.cpp").write_text(FILLER.format(n=0) + "\nvoid extra(void)\n{\n}\n")
    stage(root, f"{AREA}/filler0.cpp")

    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stderr == ""
