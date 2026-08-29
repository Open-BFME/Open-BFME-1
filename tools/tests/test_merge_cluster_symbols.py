"""--symbols drains a donor one row at a time.

A donor whose rows are not all ready was previously unmergeable: INI_stl.cpp has
eleven rows that verify byte-exact and cannot be taken, because repointing the
donor's markered rows wholesale drags in twenty-one that fail. The same gap let
an apply move a second row nobody had screened, which then failed the build.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import merge_cluster  # noqa: E402
from test_merge_cluster import DEST, MERGED, repo, run, sibling, sources_of  # noqa: E402

A = "?alpha@X@@QAEXXZ"
B = "?beta@X@@QAEXXZ"


def _two_row_donor(tmp_path):
    """One donor carrying two rows, both markered for DEST."""
    donor = "Code/Donor.cpp"
    text = (f"// readable body of {A}: {DEST}\n"
            f"// readable body of {B}: {DEST}\n"
            "void alpha() {}\nvoid beta() {}\n")
    return donor, repo(tmp_path, {donor: text, MERGED: "// merged\n"},
                       [(A, donor, b"\r\n"), (B, donor, b"\r\n")])


def _where(ledger):
    """{symbol: source} -- sources_of returns them in ledger row order."""
    return dict(zip((A, B), sources_of(ledger)))


def test_symbols_moves_one_row_and_keeps_the_donor(tmp_path):
    donor, ledger = _two_row_donor(tmp_path)
    assert run("--apply", DEST, "--into", MERGED, "--only", donor,
               "--symbols", A, "--root", str(tmp_path)) == 0
    src = _where(ledger)
    assert src[A] == MERGED, "the selected row moved"
    assert src[B] == donor, "the unselected row stayed with its donor"
    assert (tmp_path / donor).exists(), "a donor still owning a row must survive"


def test_the_deferred_row_keeps_its_marker(tmp_path):
    """Cluster membership is defined by the marker; strip it and the row is lost."""
    donor, _ = _two_row_donor(tmp_path)
    run("--apply", DEST, "--into", MERGED, "--only", donor,
        "--symbols", A, "--root", str(tmp_path))
    left = (tmp_path / donor).read_text()
    assert B in left, "the deferred row's marker must survive for the next apply"
    assert A not in left, "the moved row's marker must go"


def test_the_deferred_row_can_be_taken_afterwards(tmp_path):
    donor, ledger = _two_row_donor(tmp_path)
    run("--apply", DEST, "--into", MERGED, "--only", donor,
        "--symbols", A, "--root", str(tmp_path))
    assert run("--apply", DEST, "--into", MERGED, "--only", donor,
               "--symbols", B, "--root", str(tmp_path)) == 0
    assert _where(ledger)[B] == MERGED
    assert not (tmp_path / donor).exists(), "drained donor is deleted on the last row"


def test_without_symbols_the_whole_donor_still_drains(tmp_path):
    """The default path must be untouched."""
    donor, ledger = _two_row_donor(tmp_path)
    assert run("--apply", DEST, "--into", MERGED, "--only", donor,
               "--root", str(tmp_path)) == 0
    src = _where(ledger)
    assert src[A] == MERGED and src[B] == MERGED
    assert not (tmp_path / donor).exists()


def test_a_typo_in_symbols_fails_instead_of_moving_nothing(tmp_path):
    donor, ledger = _two_row_donor(tmp_path)
    with pytest.raises(SystemExit):
        run("--apply", DEST, "--into", MERGED, "--only", donor,
            "--symbols", "?nosuch@X@@QAEXXZ", "--root", str(tmp_path))
    assert _where(ledger)[A] == donor, "a failed apply moves nothing"


def test_a_truncated_marker_symbol_selects_the_full_row(tmp_path):
    donor, ledger = _two_row_donor(tmp_path)
    assert run("--apply", DEST, "--into", MERGED, "--only", donor,
               "--symbols", "?alpha@X@@", "--root", str(tmp_path)) == 0
    assert _where(ledger)[A] == MERGED


def test_symbols_is_rejected_by_list_and_plan(tmp_path):
    _two_row_donor(tmp_path)
    for mode in (["--list"], ["--plan", DEST]):
        with pytest.raises(SystemExit):
            run(*mode, "--symbols", A, "--root", str(tmp_path))
