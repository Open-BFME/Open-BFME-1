#!/usr/bin/env python3
"""Read reverse/re_attempts.log into a boundary-aware dead-end index.

Every work-selection tool must consult this, or it serves candidates the fleet
has already investigated. Two log shapes are in the file and both are load-bearing:

  symbol <TAB> no-match <TAB> evidence                      (3 fields, AGENTS.md)
  symbol <TAB> rva <TAB> size <TAB> status <TAB> evidence   (5 fields, in use since)

The previous reader only understood the first, because it tested field 1 for the
literal "no-match" — in a 5-field row field 1 is the RVA, so 441 rows were
invisible and list_naked_candidates.py consulted the log not at all.

Two rules keep this from over-suppressing, which would be worse than the leak:

* The log is append-only and chronological, so the LAST *verdict* for a boundary
  wins, and annotation rows are skipped rather than counted as verdicts.
  ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ ends in `converted` after
  earlier dead ends and must be released; ??0FastAllocatorGeneral@@QAE@XZ ends
  in `refuted` after three `solved` rows and must stay retired.
* A verdict describes the boundary its author examined. Where the row records an
  RVA the comparison is exact, so once an image-derived snap moves a candidate
  somewhere else the old verdict no longer covers it. Where the row records no
  RVA there is no boundary to have moved, and the verdict stands: the 3-field
  shape is a finding about the symbol.

A third rule keeps it from UNDER-correcting. Statuses are a closed vocabulary
and anything outside it is an annotation, so before `void` existed there was no
way to take back a row — an address typed rather than measured stayed live
forever, and the follow-up row could only ask a human to disregard it. `void`
is the one status that retracts rather than decides; see VOID_STATUS.
"""
import re
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RE_ATTEMPTS = ROOT / "reverse" / "re_attempts.log"

# Rows fall into three kinds and only two of them are verdicts. `note`,
# `evidence`, `lever`, `method`, `open`, `correction` and friends are
# annotations hung on an earlier finding — treating them as verdicts would let
# a follow-up note silently release a symbol the fleet had closed, which is how
# ?validateAudio@ThingTemplate@@IAEXXZ (no-match, then six annotations) came
# back ten times. Anything unrecognised is treated as an annotation, so a new
# status word leaks a candidate rather than burying one.
DEAD_END_STATUSES = frozenset({
    "no-match", "not-convertible", "refuted",
    "negative", "no-boundary", "mis-anchored?", "identity-suspect",
})
# A deferral is NOT a dead end, and conflating the two retired 535 symbols the
# project cannot finish without. Every retail byte needs a C++ equivalent, so
# "I could not match it" can only ever mean "not this session": the SEH-frame,
# register-allocation and inlining-depth walls these rows record are properties
# of the attempt, not proofs about the function. Worse, they were recorded by
# agents working a body SOLO, and AGENTS.md's measured land rate is 19.5% solo
# against 46.5% with ten or more siblings landed -- so a deferral is stale by
# construction the moment its file drains. These come back; DEAD_END_STATUSES
# stays for findings about the BOUNDARY (not a function, wrong anchor, refuted
# identity), which re-serving cannot fix.
# `partial` is a deferral that also hands the next agent what the attempt
# produced: the body is banked under reverse/attempts/<rva>.cpp and served
# beside the candidate. Same class because it is the same fact about the
# world -- an agent failed to match a real body -- and re-serving is correct.
DEFERRED_STATUSES = frozenset({
    "blocked", "attempted", "abandoned", "partial",
})
STASH_STATUS = "partial"          # the one status that may carry a banked body
RESOLVED_STATUSES = frozenset({
    "converted", "solved", "mapped", "landed",
})
VERDICT_STATUSES = DEAD_END_STATUSES | RESOLVED_STATUSES | DEFERRED_STATUSES

# `void` is not a verdict about the symbol — it is a retraction of the row it
# names, and the only way an append-only log can take back an address that was
# typed rather than measured. It deletes every EARLIER verdict at exactly its
# (symbol, rva); a verdict recorded at that boundary afterwards is new evidence
# and stands. Without it a mis-typed locator is permanent: _LoadInt was logged
# at 0x0099D2E0, which is 16 bytes inside _chunk's matched body and has nothing
# to do with _LoadInt, and the correction row appended next could only ask a
# human to read the earlier row as void — no tool could act on that sentence.
VOID_STATUS = "void"

_BY_BOUNDARY = None   # {symbol: {rva|None: latest status}}
_LATEST = None        # {symbol: latest status seen at any boundary}
_ATTEMPTS = None      # {symbol: how many deferral rows it carries}


def _reset():
    """Drop the parsed index. Tests repoint RE_ATTEMPTS at a tmpdir, and
    monkeypatch restores the attribute but not the cache built from it -- so
    this belongs both before the repoint and in the test's finally."""
    global _BY_BOUNDARY, _LATEST, _ATTEMPTS
    _BY_BOUNDARY = _LATEST = _ATTEMPTS = None


def _parse(fields):
    """Return (symbol, status, rva) for one log row, or None if it carries neither."""
    if len(fields) >= 5:
        symbol, rva_text, status = fields[0], fields[1], fields[3]
        try:
            rva = int(rva_text, 16) if rva_text else None
        except ValueError:
            rva = None
        return symbol, status, rva
    if len(fields) >= 3:
        return fields[0], fields[1], None
    return None


def _load():
    global _BY_BOUNDARY, _LATEST, _ATTEMPTS
    if _BY_BOUNDARY is not None:
        return
    _BY_BOUNDARY, _LATEST, _ATTEMPTS = {}, {}, {}
    if not RE_ATTEMPTS.exists():
        return
    rows = []
    with RE_ATTEMPTS.open(encoding="utf-8", errors="replace") as handle:
        for line in handle:
            parsed = _parse(line.rstrip("\r\n").split("\t"))
            if parsed is None:
                continue
            symbol, status, rva = parsed
            if not symbol or not status:
                continue
            if status == VOID_STATUS:
                rows.append((symbol, status, rva))
                continue
            if status not in VERDICT_STATUSES:
                continue          # an annotation never overrides a standing verdict
            rows.append((symbol, status, rva))

    # A void retracts only the rows ABOVE it at its own (symbol, rva), so the
    # log stays chronological and re-recording the same boundary later works.
    live = [True] * len(rows)
    for index, (symbol, status, rva) in enumerate(rows):
        if status != VOID_STATUS:
            continue
        live[index] = False
        for earlier in range(index):
            if rows[earlier][0] == symbol and rows[earlier][2] == rva:
                live[earlier] = False

    for keep, (symbol, status, rva) in zip(live, rows):
        if not keep:
            continue
        _BY_BOUNDARY.setdefault(symbol, {})[rva] = status
        _LATEST[symbol] = status
        if status in DEFERRED_STATUSES:
            _ATTEMPTS[symbol] = _ATTEMPTS.get(symbol, 0) + 1


def is_dead_end(symbol, rva=None, *, boundary_moved=False):
    """True when the standing verdict is a finding about the BOUNDARY.

    Only these retire a candidate: re-serving cannot turn "this RVA is not a
    function" into a match. An agent's failure to match a real body is
    is_deferred, not this. See standing_status for the boundary rules.
    """
    return standing_status(symbol, rva,
                           boundary_moved=boundary_moved) in DEAD_END_STATUSES


def is_deferred(symbol, rva=None, *, boundary_moved=False):
    """True when the standing verdict is an agent's deferral, not a boundary finding.

    Serving this again is correct -- see DEFERRED_STATUSES -- but it goes behind
    every never-attempted candidate, so a body nobody has tried always outranks
    one that already cost somebody an attempt.
    """
    return standing_status(symbol, rva,
                           boundary_moved=boundary_moved) in DEFERRED_STATUSES


def attempts(symbol):
    """How many deferral rows `symbol` carries, for ordering and for reporting."""
    _load()
    return _ATTEMPTS.get(symbol, 0)


def standing_status(symbol, rva=None, *, boundary_moved=False):
    """The verdict that currently stands for `symbol` at `rva`, or None.

    The boundary rules live here alone so every caller reads the log the same
    way. `boundary_moved` is the caller's evidence that this candidate's address
    was re-derived since the log was written (a drift snap): a verdict recorded
    against a *different* boundary does not govern it. A verdict recorded
    against no boundary at all still does, because it is a finding about the
    symbol rather than about an address -- reading it the other way leaked 377
    already-investigated candidates back into the queue, every drift candidate
    being snap-corrected by construction.
    """
    _load()
    verdicts = _BY_BOUNDARY.get(symbol)
    if not verdicts:
        return None
    if rva is not None and rva in verdicts:
        return verdicts[rva]
    if boundary_moved and None not in verdicts:
        return None
    return _LATEST.get(symbol)


def _voidable(symbol, rva_text):
    """True when some row in the log already records `symbol` at `rva_text`.

    Read straight off the file rather than through the index: the index has
    already applied voids, so asking it would refuse a second void of a row
    that a first one retracted — and would also hide a malformed row that only
    a human can see. This is the check that keeps a void honest about having
    something to retract.
    """
    if not RE_ATTEMPTS.exists():
        return False
    try:
        rva = int(rva_text, 16)
    except ValueError:
        return False
    with RE_ATTEMPTS.open(encoding="utf-8", errors="replace") as handle:
        for line in handle:
            fields = line.rstrip("\r\n").split("\t")
            if len(fields) < 5 or fields[0] != symbol:
                continue
            try:
                if int(fields[1], 16) == rva and fields[3] != VOID_STATUS:
                    return True
            except ValueError:
                continue
    return False


STASH_LIMIT = 64 * 1024
# The range lives in the pattern so a hand-edited 5.0 is caught on read, not
# quietly ranked above every honest stash.
_STASH_SCORE = re.compile(r"^// partial score=(0(?:\.\d+)?|1(?:\.0+)?) date=\d{4}-\d{2}-\d{2}$")


def _stash_path(rva):
    """Beside the log, so repointing RE_ATTEMPTS in a test moves the stash too."""
    return RE_ATTEMPTS.parent / "attempts" / f"0x{rva:08x}.cpp"


def stash_for(rva):
    """Return (path, score) for the attempt body banked at `rva`, else None.

    The only reader of the header: serving ranks on the score and hygiene
    validates the same two lines, and a second parser would let them disagree
    about what a stash is. A file that exists but does not parse raises -- a
    banked body whose score had to be guessed would be ranked on a lie.
    """
    path = _stash_path(rva)
    if not path.exists():
        return None
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    score = _STASH_SCORE.match(lines[1]) if len(lines) > 1 else None
    if not score:
        raise ValueError(
            f"{path}: line 2 must read '// partial score=<0..1> date=<iso>', "
            f"got {lines[1:2]}. Rewrite it or delete the stash.")
    return path, float(score.group(1))


def stats():
    """Return (symbols carrying a live dead-end verdict, total symbols logged)."""
    _load()
    dead = sum(1 for status in _LATEST.values() if status in DEAD_END_STATUSES)
    return dead, len(_LATEST)


def _take(argv, flag):
    """Pull a trailing `--flag value` pair out of argv; returns (argv, value)."""
    if flag not in argv:
        return argv, None
    at = argv.index(flag)
    if at + 1 >= len(argv):
        raise SystemExit(f"{flag} needs a value after it.")
    return argv[:at] + argv[at + 2:], argv[at + 1]


def _bank(symbol, rva_text, source_text, score_text):
    """Copy an attempt body under reverse/attempts/ and return its evidence tokens.

    Runs before the log row is appended: an orphan stash is visible to hygiene
    and deletable, whereas a row pointing at a file that was never written sends
    the next agent looking for evidence that does not exist.
    """
    if not 0.0 <= float(score_text) <= 1.0:
        raise SystemExit(
            f"--score {score_text} is outside 0..1. It is the fraction of the "
            f"body believed right, and serving ranks the frontier on it.")
    source = Path(source_text)
    if not source.is_file():
        raise SystemExit(f"--stash {source_text}: no such file to bank.")
    size = source.stat().st_size
    if not 0 < size <= STASH_LIMIT:
        raise SystemExit(
            f"--stash {source_text}: {size} bytes, outside 1..{STASH_LIMIT}. "
            f"An empty body banks nothing; a huge one is not one function.")
    score = float(score_text)
    target = _stash_path(int(rva_text, 16))
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(
        f"// {symbol}\n// partial score={score} date={date.today().isoformat()}\n"
        .encode("utf-8") + source.read_bytes())
    return f"score={score} stash={target.relative_to(RE_ATTEMPTS.parent.parent).as_posix()}"


def _record(argv):
    """Append one verdict row with correct framing; the safe path for agents.

    Hand-appending has produced three shapes of damage this index has to
    tolerate: LF/CRLF mixes (editor tools normalise the whole file on touch),
    missing columns, and status words nothing recognises. This writes exactly
    one 5-field CRLF row and refuses statuses outside the vocabulary, loudly.

    Usage:
      python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence...>
                                     [--stash <file> --score <0..1>]

    `<status> = partial` is a near miss: the candidate stays servable and the
    two flags bank the body you are about to revert as reverse/attempts/<rva>.cpp
    for whoever draws it next. They are REQUIRED for `partial` and legal on no
    other status -- a partial without a body measured worse than silence.

    `<status> = void` retracts an earlier row instead of adding a verdict: pass
    the SAME symbol and rva as the row being taken back, and say in the evidence
    which row and why. It is refused unless such a row exists.

    Put attempt duration and model in the evidence free-text (e.g. "t=25min
    model=haiku ...") — that is what lets the selection weights in
    tools/yield_model.py be refit from outcomes instead of guessed.
    """
    argv, stash_text = _take(argv, "--stash")
    argv, score_text = _take(argv, "--score")
    if len(argv) < 5:
        raise SystemExit(_record.__doc__)
    symbol, rva_text, size_text, status = argv[0], argv[1], argv[2], argv[3]
    evidence = " ".join(argv[4:])
    if status not in VERDICT_STATUSES and status != VOID_STATUS:
        raise SystemExit(
            f"unknown status {status!r}. Dead ends: {sorted(DEAD_END_STATUSES)}; "
            f"resolutions: {sorted(RESOLVED_STATUSES)}; frontier: "
            f"deferrals: {sorted(DEFERRED_STATUSES)}; retraction: "
            f"{VOID_STATUS!r}. An unrecognised status "
            f"would be ignored by every queue, so it is refused here.")
    if status == VOID_STATUS and not _voidable(symbol, rva_text):
        raise SystemExit(
            f"nothing to void: no earlier verdict for {symbol!r} at {rva_text}. "
            f"A void that matches no row is a typo about a typo, and would sit "
            f"in the log forever looking like it had retracted something.")
    int(rva_text, 16), int(size_text)          # fail loudly on malformed fields
    if (stash_text is None) != (score_text is None):
        raise SystemExit(
            "--stash and --score are one pair: a banked body nothing can rank "
            "never gets served, and a score pointing at no body ranks nothing.")
    # Measured over the first 95 partial rows: banking a body lands 25.0% of the
    # time, while a bodyless `partial` lands 5.1% -- BELOW the 7.5% of an
    # outright dead end. Two thirds of usage was the bodyless form, because it
    # was the cheaper thing to type. So the body is the verdict: without one,
    # say `blocked` and let the queue re-serve it on its own terms.
    if status == STASH_STATUS and stash_text is None:
        raise SystemExit(
            f"{STASH_STATUS!r} requires --stash <file> --score <0..1>. A row "
            f"that only describes the near miss measured WORSE than recording "
            f"nothing (5.1% vs 7.5% landing). Bank the body you are about to "
            f"revert, or record `blocked` with your evidence instead.")
    if stash_text is not None:
        if status != STASH_STATUS:
            raise SystemExit(
                f"--stash/--score belong to {STASH_STATUS!r}, not "
                f"{status!r}: a dead end has nothing worth handing on, and a "
                f"landed body belongs in Code/.")
        evidence = f"{evidence} {_bank(symbol, rva_text, stash_text, score_text)}"
    row = f"{symbol}\t{rva_text}\t{size_text}\t{status}\t{evidence}\r\n"
    with RE_ATTEMPTS.open("ab") as handle:
        handle.write(row.encode("utf-8"))
    print(f"recorded: {symbol} @ {rva_text} -> {status}")


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1 and sys.argv[1] == "record":
        _record(sys.argv[2:])
    else:
        dead, total = stats()
        print(f"{dead} standing dead ends of {total} symbols with verdicts; "
              f"append with: re_log.py record <symbol> <rva> <size> <status> <evidence>")
