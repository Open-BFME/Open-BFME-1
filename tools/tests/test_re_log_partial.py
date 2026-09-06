#!/usr/bin/env python3
"""The `partial` verdict: a near miss keeps its candidate servable and banks its body.

Every test repoints re_log.RE_ATTEMPTS at a tmpdir and resets the parsed index
both before and in a finally -- monkeypatch restores the attribute but not the
cache built from it, so a leaked index would decide later tests in this process.
"""
import sys
import hashlib
import json
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


def test_partial_without_a_body_is_refused(log):
    """The body IS the verdict. Measured over the first 95 partial rows, a
    bodyless `partial` landed 5.1% against 7.5% for an outright dead end -- it
    performed worse than saying nothing -- and it was two thirds of all usage
    because it was the cheaper thing to type. So it is refused, with the
    honest alternative named in the message."""
    refusal = record(SYM, "0x00401000", "16", "partial",
                     "callee at 0x401200 confirmed; body shape still wrong")
    assert refusal is not None, "a partial with no banked body was accepted"
    assert "requires --stash" in refusal and "blocked" in refusal, refusal
    re_log._reset()
    assert re_log.stash_for(RVA) is None


def test_lower_scored_attempt_keeps_best_and_archives_both(log, tmp_path):
    body = tmp_path / "attempt.cpp"
    for value, score in [(1, "0.99"), (2, "0.80")]:
        body.write_text(f"int f() {{ return {value}; }}\n")
        assert record(SYM, hex(RVA), "16", "partial", "trial",
                      "--stash", str(body), "--score", score) is None
    path, score = re_log.stash_for(RVA)
    assert score == .99 and "return 1" in path.read_text()
    variants = list((log.parent / "attempt_history" / f"0x{RVA:08x}").glob("*.json"))
    assert len(variants) == 2
    assert {json.loads(p.read_text())["score"] for p in variants} == {.99, .8}
    last = log.read_text().splitlines()[-1]
    assert "score=0.99 stash=" in last and "submitted=0.8" in last


def test_higher_score_replaces_pointer_but_keeps_original(log, tmp_path):
    body = tmp_path / "attempt.cpp"
    body.write_text("int f() { return 1; }")
    re_log._bank(SYM, hex(RVA), str(body), ".8")
    body.write_text("int f() { return 2; }")
    re_log._bank(SYM, hex(RVA), str(body), ".99")
    path, score = re_log.stash_for(RVA)
    assert score == .99 and "return 2" in path.read_text()
    assert len(list((log.parent / "attempt_history").rglob("*.json"))) == 2


def test_rebank_stash_does_not_nest_headers(log, tmp_path):
    body = tmp_path / "attempt.cpp"
    body.write_text("int f() { return 1; }")
    re_log._bank(SYM, hex(RVA), str(body), ".8")
    path, _ = re_log.stash_for(RVA)
    re_log._bank(SYM, hex(RVA), str(path), ".9")
    assert path.read_text().count("// partial score=") == 1


def test_bom_source_is_normalized_before_metadata(log, tmp_path):
    """A BOM at the source start must not become a compiler identifier."""
    body = tmp_path / "bom-source.cpp"
    body.write_bytes(re_log.UTF8_BOM + b"// near miss\nvoid Sym() {}\n")

    assert record(SYM, hex(RVA), "16", "partial", "bom source",
                  "--stash", str(body), "--score", "0.8") is None

    path, score = re_log.stash_for(RVA)
    raw = path.read_bytes()
    assert score == 0.8
    assert raw.startswith(f"// {SYM}\n// partial score=0.8 date=".encode())
    assert re_log.UTF8_BOM not in raw
    assert raw.endswith(b"// near miss\nvoid Sym() {}\n")


def test_resumed_bom_bank_repairs_preferred_body_and_archives_original(log,
                                                                        tmp_path):
    """A same-score resume repairs line-three BOM without replacing the best body."""
    target = re_log._stash_path(RVA)
    target.parent.mkdir(parents=True, exist_ok=True)
    old = (f"// {SYM}\n// partial score=0.80 date=2026-09-05\n".encode()
           + re_log.UTF8_BOM + b"int f() { return 1; }\n")
    target.write_bytes(old)
    incoming = tmp_path / "resumed-bom.cpp"
    incoming.write_bytes(re_log.UTF8_BOM + b"int f() { return 2; }\n")

    result = re_log._bank(SYM, hex(RVA), str(incoming), "0.80")

    repaired = target.read_bytes()
    assert result.startswith("score=0.8 ")
    assert repaired == (f"// {SYM}\n// partial score=0.80 date=2026-09-05\n".encode()
                       + b"int f() { return 1; }\n")
    assert re_log.UTF8_BOM not in repaired
    assert re_log.stash_for(RVA)[1] == 0.8

    history = log.parent / "attempt_history" / f"0x{RVA:08x}"
    archived = [json.loads(path.read_text(encoding="utf-8"))
                for path in history.glob("*.json")]
    assert any(entry["sha256"] == hashlib.sha256(old).hexdigest()
               and entry["source"] == old.decode("utf-8")
               for entry in archived), "the malformed preferred bytes must remain archived"
