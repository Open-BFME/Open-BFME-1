#!/usr/bin/env python3
"""The `partial` verdict: a near miss keeps its candidate servable and banks its body.

Every test repoints re_log.RE_ATTEMPTS at a tmpdir and resets the parsed index
both before and in a finally -- monkeypatch restores the attribute but not the
cache built from it, so a leaked index would decide later tests in this process.
"""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import re_log  # noqa: E402  (path insert must precede the import)


@pytest.fixture
def log(tmp_path, monkeypatch):
    """An empty log in a tmpdir, with the index reset around the test.

    Laid out as <root>/reverse/re_attempts.log rather than bare in tmp_path:
    the stash token is written relative to the log's grandparent, so only this
    shape exercises the `reverse/attempts/...` path the ledger actually carries.
    """
    path = tmp_path / "reverse" / "re_attempts.log"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("", encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", path)
    re_log._reset()
    try:
        yield path
    finally:
        re_log._reset()


def record(*args):
    """Drive _record in-process, which is the only way the monkeypatched
    RE_ATTEMPTS applies -- a subprocess would append to the real shared ledger.
    Returns the refusal message, or None when the row was accepted."""
    try:
        re_log._record(list(args))
    except SystemExit as refusal:
        return str(refusal)
    return None


def write_rows(path, *rows):
    path.write_bytes("".join(rows).encode("utf-8"))


SYM = "?Sym@@QAEXXZ"
RVA = 0x00401000


def test_partial_after_dead_end_releases_the_candidate(log):
    """The whole point: a near miss recorded after a dead end un-retires it."""
    write_rows(log,
               f"{SYM}\t0x00401000\t16\tno-match\twrong shape\r\n",
               f"{SYM}\t0x00401000\t16\tpartial\t92%, arm order\r\n")
    re_log._reset()
    assert not re_log.is_dead_end(SYM, RVA)


def test_dead_end_after_partial_still_retires(log):
    """Latest verdict wins in BOTH directions, or `partial` would be a one-way
    escape hatch that no later refutation could close."""
    write_rows(log,
               f"{SYM}\t0x00401000\t16\tpartial\t92%, arm order\r\n",
               f"{SYM}\t0x00401000\t16\tno-match\tre-measured, boundary is wrong\r\n")
    re_log._reset()
    assert re_log.is_dead_end(SYM, RVA)


def test_unknown_status_after_dead_end_leaves_it_dead(log):
    """The fail-open rule, and the stale-clone property it buys: a checkout that
    predates `partial` reads it as an annotation and keeps the candidate
    retired, rather than releasing something it cannot serve."""
    write_rows(log,
               f"{SYM}\t0x00401000\t16\tno-match\twrong shape\r\n",
               f"{SYM}\t0x00401000\t16\tpartialish\tnot a real status\r\n")
    re_log._reset()
    assert re_log.is_dead_end(SYM, RVA)


def test_stash_round_trips_through_its_header(log, tmp_path):
    """record --stash banks the body; stash_for is the only reader of it."""
    body = tmp_path / "attempt.cpp"
    body.write_text("void Sym() { return; }\n", encoding="utf-8")
    assert record(SYM, "0x00401000", "16", "partial", "92%, arm order",
                  "--stash", str(body), "--score", "0.92") is None

    found = re_log.stash_for(RVA)
    assert found is not None, "banked body is not readable back"
    path, score = found
    assert score == 0.92
    text = path.read_text(encoding="utf-8")
    assert text.startswith(f"// {SYM}\n// partial score=0.92 date=")
    assert "void Sym() { return; }" in text, "the body itself must survive"

    row = log.read_text(encoding="utf-8")
    assert "score=0.92" in row and "stash=reverse/attempts/0x00401000.cpp" in row


def test_stash_absent_reads_as_none(log):
    assert re_log.stash_for(RVA) is None


def test_unparsable_header_raises_rather_than_guessing(log):
    """A stash whose score cannot be read must not be served at a made-up rank."""
    target = re_log._stash_path(RVA)
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text("// ?Sym@@QAEXXZ\n// no score here\nvoid Sym() {}\n",
                      encoding="utf-8")
    with pytest.raises(ValueError, match="line 2 must read"):
        re_log.stash_for(RVA)


@pytest.mark.parametrize("args, expect", [
    (("--score", "1.5"), "outside 0..1"),
    (("--score", "-0.1"), "outside 0..1"),
    (("--stash", "/nonexistent/body.cpp", "--score", "0.5"), "no such file"),
])
def test_refusals_are_loud(log, tmp_path, args, expect):
    """Every refusal exits non-zero and names its reason -- no silent fallback."""
    body = tmp_path / "attempt.cpp"
    body.write_text("void Sym() {}\n", encoding="utf-8")
    full = args if "--stash" in args else ("--stash", str(body)) + args
    refusal = record(SYM, "0x00401000", "16", "partial", "evidence", *full)
    assert refusal is not None, f"accepted {full}"
    assert expect in refusal, refusal


def test_empty_body_is_refused(log, tmp_path):
    """An empty stash banks nothing while looking like evidence."""
    body = tmp_path / "empty.cpp"
    body.write_text("", encoding="utf-8")
    refusal = record(SYM, "0x00401000", "16", "partial", "evidence",
                     "--stash", str(body), "--score", "0.5")
    assert refusal is not None and "outside 1.." in refusal, refusal


def test_flags_come_as_a_pair(log, tmp_path):
    body = tmp_path / "attempt.cpp"
    body.write_text("void Sym() {}\n", encoding="utf-8")
    for partial_args in (("--stash", str(body)), ("--score", "0.5")):
        refusal = record(SYM, "0x00401000", "16", "partial", "evidence",
                         *partial_args)
        assert refusal is not None, f"accepted half a pair: {partial_args}"
        assert "one pair" in refusal, refusal


def test_stash_refused_on_any_other_status(log, tmp_path):
    """A dead end has nothing to hand on; a landed body belongs in Code/."""
    body = tmp_path / "attempt.cpp"
    body.write_text("void Sym() {}\n", encoding="utf-8")
    refusal = record(SYM, "0x00401000", "16", "no-match", "evidence",
                     "--stash", str(body), "--score", "0.5")
    assert refusal is not None and "belong to" in refusal, refusal


def test_partial_without_flags_is_a_legal_facts_only_row(log):
    """Facts outlive bodies -- a partial that banks only evidence is valid."""
    assert record(SYM, "0x00401000", "16", "partial",
                  "callee at 0x401200 confirmed; body shape still wrong") is None
    re_log._reset()
    assert not re_log.is_dead_end(SYM, RVA)
    assert re_log.stash_for(RVA) is None
