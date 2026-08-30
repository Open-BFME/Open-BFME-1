"""--only scopes the trailer to a PARTIAL commit.

--staged compares the whole index against HEAD. On `git commit <paths>` while
other work sits staged, that attributes the held work to the commit being made --
which misreported a trailer once. --only takes the index blob for the committed
paths and HEAD's for everything else.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_readability_metric import (  # noqa: E402
    AREA, ALPHA_CPP, cli, commit, stage, world)


def _two_staged_edits(tmp_path):
    """A committed tree, then TWO staged edits that move DIFFERENT axes.

    alpha.cpp names a padding array (Types); gamma.cpp buries its body in asm
    (Body). Different axes, so a correctly scoped trailer names one and not the
    other -- which is the whole property under test.
    """
    root = world(tmp_path)
    commit(root)
    (root / AREA / "alpha.cpp").write_text(
        ALPHA_CPP.replace("char pad[8];", "int m_namedField;"))
    (root / AREA / "gamma.cpp").write_text(
        (root / AREA / "gamma.cpp").read_text().replace(
            "m_flag = 0;", "__asm { nop }\n\t__emit 0x90"))
    stage(root, "Code")
    return root


def test_only_without_staged_is_refused(tmp_path):
    out = cli(world(tmp_path), "--only", "Code")
    assert out.returncode != 0
    assert "--only belongs to --staged" in out.stderr + out.stdout


def test_only_selecting_nothing_staged_fails_loudly(tmp_path):
    """A silent 'no measurable change' here would be the bug, not the answer."""
    root = world(tmp_path)
    commit(root)
    out = cli(root, "--staged", "--only", "reverse")
    assert out.returncode != 0
    assert "selects nothing staged" in out.stderr + out.stdout


def test_only_attributes_just_the_named_path(tmp_path):
    """The held file's axis must not appear in the scoped trailer."""
    root = _two_staged_edits(tmp_path)
    whole = cli(root, "--staged").stdout.strip()
    scoped = cli(root, "--staged", "--only", f"{AREA}/alpha.cpp").stdout.strip()
    assert whole != scoped, f"scoping changed nothing: {whole!r}"
    assert "Types" in whole and "Body" in whole, whole
    assert "Types" in scoped, scoped
    assert "Body" not in scoped, f"held work leaked into the scoped trailer: {scoped!r}"


def test_only_matches_a_directory_prefix_not_a_substring(tmp_path):
    root = _two_staged_edits(tmp_path)
    out = cli(root, "--staged", "--only", AREA)
    assert out.returncode == 0, out.stderr
