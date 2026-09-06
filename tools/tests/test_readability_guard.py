"""--staged refuses an axis gain that comes from a rename and nothing else.

Two of the seven axes can be moved by an edit a reader cannot tell from the
original, and neither can be defended by a better pattern:

  * 13,329 ledger rows in the measured areas are named `d_`/`dup_`/`sub_`/`uw_`/
    `j_` plus an address. They are ICF aliases, ILT thunks and unwind funclets --
    `?dup_XXXXXXXX@@YAXXZ` is a real body PARKED under its address precisely
    because its identity is not known (docs/lessons.md, "Two placeholder
    conventions"). Spelling them all as words is Ident 20.72 -> 29.21 (+8.49 pp)
    and not one function becomes easier to read.
  * 10,522 pad members answer to `char m_pad[8]`. Renamed to `char m_slack[8]`
    they leave the pad vocabulary, and Types goes to 100.0 (+18.72 pp) with the
    same eight bytes still unaccounted for. No pattern can read that declaration
    and know whether the name was earned: `char m_name[8]` is the same shape.

What separates the sweep from the work is in the DIFF, not in either tree: a swap
keeps the thing being named. A real identity recovery moves the row to the source
that now holds the body -- over the last 600 commits touching the ledger, 622 rows
left an alias name and EVERY one of them also moved source, because that is the
gen_asm dump -> real C++ lane -- and a real Types gain changes the declaration's
type or its extent. So the refusal is for renames that keep the source, or keep
the base type and the extent, and only past a budget: exactly one commit in those
600 renamed a row in place (553094eb6, ?dup_00217620 -> ??1CollideModule@@UAE@XZ),
and exactly one in the last 800 commits touching Code/ renamed a pad member into a
same-type same-extent field.

Every test below stages the gaming edit and asserts it is caught, or stages the
legitimate edit it most resembles and asserts it is not.
"""
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_readability_metric import (  # noqa: E402
    AREA, ALPHA_CPP, GAMMA_CPP, LEDGER_PATH, cli, commit, metric, stage)

# Six alias rows, one per family plus enough dup_ to clear the budget of four.
ALIASES = ("?d_00401000@@YAXXZ", "?dup_00401020@@YAXXZ", "?dup_00401040@@YAXXZ",
           "?dup_00401060@@YAXXZ", "?j_00401080@@YAXXZ", "?uw_004010a0@@YAXXZ")
NAMES = ("?init@Alpha@@QAEXXZ", "?reset@Alpha@@QAEXXZ", "?step@Alpha@@QAEXXZ",
         "?stop@Alpha@@QAEXXZ", "?draw@Alpha@@QAEXXZ", "?tick@Alpha@@QAEXXZ")

# Six pad members of two shapes, so a swap can be counted per (type, extent).
PADS_H = "struct Wide {\n" + "".join(
    "\tunsigned char m_pad%02d[ 0x%02x ];\n" % (n, 8 + 8 * (n % 2)) for n in range(6)
) + "\tint m_known;\n};\n"


def rows(names, source=f"{AREA}/alpha.cpp"):
    header = b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
    return header + b"".join(
        ("%s,,0x004010%02x,16,%s,matched,\r\r\n" % (name, 0x20 * n, source)).encode()
        for n, name in enumerate(names))


def world(tmp_path, header=PADS_H, names=ALIASES):
    """A committed fixture tree whose ledger is all alias rows."""
    root = (tmp_path / "repo").resolve()
    (root / AREA).mkdir(parents=True)
    (root / "reverse").mkdir()
    (root / AREA / "alpha.h").write_text(header)
    (root / AREA / "alpha.cpp").write_text(ALPHA_CPP)
    (root / AREA / "gamma.cpp").write_text(GAMMA_CPP)
    (root / LEDGER_PATH).write_bytes(rows(names))
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    stage(root, "Code", "reverse")
    commit(root)
    return root


def restage(root, path, content):
    (root / path).write_bytes(content) if isinstance(content, bytes) \
        else (root / path).write_text(content)
    stage(root, path)


def staged(root, *args):
    return cli(root, "--staged", *args)


def test_renaming_alias_rows_in_place_is_refused(tmp_path):
    root = world(tmp_path)
    restage(root, LEDGER_PATH, rows(NAMES))

    done = staged(root)
    assert done.returncode == 2, done.stdout + done.stderr
    assert "REFUSED" in done.stderr
    assert "6 ledger rows" in done.stderr
    assert "0x00401000 ?d_00401000@@YAXXZ -> ?init@Alpha@@QAEXXZ" in done.stderr
    # The trailer is the evidence for the refusal, so it still goes to stdout --
    # and it shows the gain the sweep was reaching for.
    assert done.stdout.startswith("readability: Ident 0.0 -> 100.0 (+100.00 pp)")


def test_converting_alias_rows_onto_a_new_source_is_the_work_not_a_swap(tmp_path):
    """The default lane: a gen_asm dump becomes real C++, the row gets both a name
    and the source that now holds the body. 622 of 622 historical alias renames
    look like this, so the guard must never see them."""
    root = world(tmp_path)
    restage(root, LEDGER_PATH, rows(NAMES, source=f"{AREA}/gamma.cpp"))

    done = staged(root)
    assert done.returncode == 0, done.stderr
    assert "REFUSED" not in done.stderr


def test_upgrading_a_few_parked_rows_stays_inside_the_budget(tmp_path):
    """`?dup_` rows do get upgraded in place when evidence turns up, one at a time
    -- so the guard is a budget, not a ban, and it is set where history put it."""
    root = world(tmp_path)
    restage(root, LEDGER_PATH, rows(NAMES[:metric.TOKEN_SWAP_BUDGET]
                                    + ALIASES[metric.TOKEN_SWAP_BUDGET:]))

    done = staged(root)
    assert done.returncode == 0, done.stderr
    assert "Ident" in done.stdout


def test_renaming_pad_members_out_of_the_vocabulary_is_refused(tmp_path):
    root = world(tmp_path)
    restage(root, f"{AREA}/alpha.h", PADS_H.replace("m_pad", "m_slack"))

    done = staged(root)
    assert done.returncode == 2, done.stdout + done.stderr
    assert "6 pad members are renamed" in done.stderr
    assert f"{AREA}/alpha.h unsigned char[0x08]" in done.stderr
    # 7 pads (6 here, 1 in alpha.cpp) against 2 named fields, then 1 against 8.
    assert done.stdout == "readability: Types 22.2 -> 88.9 (+66.67 pp), files +0\n"


def test_a_pad_rename_that_leaves_the_ratio_entirely_is_still_a_swap(tmp_path):
    """`char pad[8]` -> `char slack[8]` has no `m_`, so the new declaration is not
    a named member at all -- it drops out of the Types denominator instead of
    crossing it, and Types rises anyway. Reading NAMED_MEMBER on the arriving side
    caught 6,603 of this tree's 10,519 pad members and let the other 3,916
    through; any array member of the same type and extent catches 9,835."""
    root = world(tmp_path, header=PADS_H.replace("m_pad", "pad"))
    restage(root, f"{AREA}/alpha.h",
            PADS_H.replace("m_pad", "pad").replace("pad", "slack"))

    done = staged(root)
    assert done.returncode == 2, done.stdout + done.stderr
    assert "6 pad members are renamed" in done.stderr


def test_naming_the_bytes_a_pad_was_hiding_is_not_a_swap(tmp_path):
    """The real Types work: the eight bytes turn out to be two ints, so neither the
    type nor the extent survives. Six of them at once, well past the budget."""
    root = world(tmp_path)
    named = "struct Wide {\n" + "".join(
        "\tint m_left%02d;\n\tint m_right%02d;\n" % (n, n) for n in range(6)
    ) + "\tint m_known;\n};\n"
    restage(root, f"{AREA}/alpha.h", named)

    done = staged(root)
    assert done.returncode == 0, done.stderr
    assert "REFUSED" not in done.stderr
    assert "Types" in done.stdout


def test_a_swap_hidden_behind_a_partial_commit_is_still_caught(tmp_path):
    """--only scopes the trailer to what a partial commit carries; the guard reads
    the same scope, or a sweep would hide behind a second staged path."""
    root = world(tmp_path)
    restage(root, LEDGER_PATH, rows(NAMES))
    restage(root, f"{AREA}/gamma.cpp", GAMMA_CPP + "\nvoid unrelated(void)\n{\n}\n")

    scoped = staged(root, "--only", LEDGER_PATH)
    assert scoped.returncode == 2, scoped.stdout + scoped.stderr
    assert "6 ledger rows" in scoped.stderr

    held = staged(root, "--only", f"{AREA}/gamma.cpp")
    assert held.returncode == 0, held.stderr


def test_an_untouched_ledger_costs_the_guard_nothing(tmp_path):
    """The common commit changes no ledger row and no member declaration; the
    guard reads the staged diff only, so it has nothing to walk."""
    root = world(tmp_path)
    restage(root, f"{AREA}/gamma.cpp", GAMMA_CPP + "\nvoid extra(void)\n{\n}\n")

    done = staged(root)
    assert done.returncode == 0, done.stderr
    assert metric.staged_swaps(metric.staged_diff(root, [])) == ([], [])
