"""targets/game/reverse/symbols.csv has to carry ONE line terminator, and who enforces it.

symbols.csv is `merge=union` and its rows are pins that several tools legitimately
re-emit. A line differing from its twin only by a `\\r` is a DISTINCT line to the
union driver, so the same pin lands twice and every later merge compounds it --
that is how 4,172 pins became 8,784. functions.csv survives the same mixing
because a duplicated row trips check_csv's duplicate-name rule; a duplicated pin
is legal, so nothing downstream catches it.

`gen_small.line_terminator` already refuses to append to a mixed file, which
stops every wave. That is the right refusal in the wrong place: it fires hours
later, in a session that did not cause it. The three tools that WRITE the file
are tested here instead -- check_csv rejects the commit that mixes it, dedup_csv
(the repair tool) normalizes rather than flipping CRLF to LF wholesale, and
locate.py --emit appends in the file's own terminator.
"""
import importlib.util
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,address,notes"
PIN_A = "?alpha@@YAXXZ,0x00401000,"
PIN_B = "?beta@@YAXXZ,0x00402000,"


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


check_csv = _load("check_csv")
dedup_csv = _load("dedup_csv")
ledger_io = _load("ledger_io")
add_match = _load("add_match")


def symbols(*lines, eol="\r\n"):
    return (eol.join([HEADER, *lines]) + eol).encode("utf-8")


# --------------------------------------------------------------------------
# check_csv: the commit that mixes the file is the one that fails
# --------------------------------------------------------------------------

@pytest.mark.parametrize("eol", ["\r\n", "\n"])
def test_a_uniform_symbols_file_is_fine_either_way(eol):
    """The file's terminator is not the point; carrying two of them is."""
    problems = []
    check_csv.check_symbols(symbols(PIN_A, PIN_B, eol=eol), problems)
    assert problems == []


def test_one_lf_pin_in_a_crlf_file_is_reported_with_its_line_number():
    """The live case: a hand-appended pin at the tail blocked every land."""
    raw = symbols(PIN_A) + (PIN_B + "\n").encode("utf-8")
    problems = []
    check_csv.check_symbols(raw, problems)
    assert len(problems) == 1, problems
    assert "line 3" in problems[0], problems[0]
    assert "union" in problems[0].lower(), "say why a stray \\r matters, not just that it is there"


def test_the_mixing_is_reported_whichever_terminator_is_the_odd_one():
    raw = symbols(PIN_A, eol="\n") + (PIN_B + "\r\n").encode("utf-8")
    problems = []
    check_csv.check_symbols(raw, problems)
    assert len(problems) == 1 and "line 3" in problems[0], problems


def test_the_terminator_check_does_not_mask_the_other_symbols_checks():
    raw = symbols("?alpha@@YAXXZ,0x00401000,") + b"?alpha@@YAXXZ,0x00401000,\n"
    problems = []
    check_csv.check_symbols(raw, problems)
    assert any("exact duplicate" in p for p in problems), problems


# --------------------------------------------------------------------------
# dedup_csv: the repair tool, which used to be a second way to break it
# --------------------------------------------------------------------------

def test_dedup_keeps_a_crlf_file_crlf(tmp_path):
    """It rewrote every line with LF, so one run flipped all 70,871 pins and the
    next merge saw a new line for each one."""
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_B, PIN_A))
    dedup_csv.dedup_symbols(path)
    assert set(t for _, t in ledger_io.split_records(path.read_bytes())) == {b"\r\n"}


def test_dedup_keeps_an_lf_file_lf(tmp_path):
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_B, PIN_A, eol="\n"))
    dedup_csv.dedup_symbols(path)
    assert set(t for _, t in ledger_io.split_records(path.read_bytes())) == {b"\n"}


def test_dedup_normalizes_a_mixed_file_to_its_majority(tmp_path, capsys):
    """This is the one tool that may change a terminator: it rewrites the whole
    file, so it is where a merged-in stray gets repaired -- out loud."""
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_A) + (PIN_B + "\n").encode("utf-8"))
    dedup_csv.dedup_symbols(path)
    assert set(t for _, t in ledger_io.split_records(path.read_bytes())) == {b"\r\n"}
    assert "terminator" in capsys.readouterr().out.lower(), "a silent rewrite is how it started"


def test_dedup_still_collapses_duplicate_pins(tmp_path):
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_A, PIN_A, PIN_B))
    before, after = dedup_csv.dedup_symbols(path)
    assert (before, after) == (3, 2)


# --------------------------------------------------------------------------
# dedup_csv over functions.csv: the same defect, at 60x the scale
# --------------------------------------------------------------------------

FN_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
SRC = "game/GameEngine/Source/Common/Thing.cpp"
ROW_A = f"?a@Thing@@QAEXXZ,,0x00401000,16,{SRC},matched,"
ROW_B = f"?b@Thing@@QAEXXZ,,0x00402000,16,{SRC},matched,"


def functions(*rows_with_terms):
    out = FN_HEADER.encode() + b"\r\n"
    for row, term in rows_with_terms:
        out += row.encode() + term
    return out


def test_dedup_functions_keeps_every_row_terminator_it_found(tmp_path):
    """functions.csv legitimately carries \\r\\r\\n, \\r\\n and \\n. csv.DictWriter
    rewrote all three as \\r\\n -- on the live ledger that is 95,184 lines the
    union driver has never seen, for rows that already exist on every branch,
    while collapsing nothing (157,958 -> 157,958)."""
    path = tmp_path / "functions.csv"
    path.write_bytes(functions((ROW_A, b"\r\r\n"), (ROW_B, b"\n")))
    before = path.read_bytes()
    assert dedup_csv.dedup_functions(path) == (2, 2)
    assert path.read_bytes() == before, "nothing to collapse must mean nothing to write"


def test_dedup_functions_still_collapses_and_keeps_the_survivor_verbatim(tmp_path):
    path = tmp_path / "functions.csv"
    path.write_bytes(functions((ROW_B, b"\r\r\n"), (ROW_A, b"\n"), (ROW_A, b"\r\n")))
    assert dedup_csv.dedup_functions(path) == (3, 2)
    kept = ledger_io.split_records(path.read_bytes())[1:]
    assert [payload.decode() for payload, _ in kept] == [ROW_A, ROW_B]
    assert {term for _, term in kept} == {b"\n", b"\r\r\n"}, (
        "each survivor keeps the terminator it arrived with")


def test_dedup_functions_still_refuses_a_two_source_tie(tmp_path):
    path = tmp_path / "functions.csv"
    other = ROW_A.replace(SRC, "game/GameEngine/Source/Common/Other.cpp")
    path.write_bytes(functions((ROW_A, b"\r\n"), (other, b"\r\n")))
    before = path.read_bytes()
    with pytest.raises(SystemExit) as exc:
        dedup_csv.dedup_functions(path)
    assert exc.value.code == 1
    assert path.read_bytes() == before


def test_add_match_rewrite_key_accepts_lowercase_csv_hex():
    """CSV hex spelling must not make --replace-existing leave its row behind."""
    fields = ["?assign@Thing@@QAEAAV1@ABV1@@Z", "", "0x005d5ae0", "60",
              SRC, "matched", ""]
    assert add_match.ledger_key(fields) == (fields[0], 0x005D5AE0)


# --------------------------------------------------------------------------
# ledger_io: one implementation of "which terminator", two policies over it
# --------------------------------------------------------------------------

def test_uniform_terminator_names_the_file_and_the_repair():
    with pytest.raises(SystemExit) as exc:
        ledger_io.uniform_terminator(symbols(PIN_A) + b"x,0x1,\n", "symbols.csv")
    assert "symbols.csv" in str(exc.value) and "dedup_csv" in str(exc.value)


def test_uniform_terminator_returns_the_one_the_file_uses():
    assert ledger_io.uniform_terminator(symbols(PIN_A), "symbols.csv") == b"\r\n"
    assert ledger_io.uniform_terminator(symbols(PIN_A, eol="\n"), "symbols.csv") == b"\n"


# Anything that opens symbols.csv for writing, however it spells it. locate
# --emit wrote "\n" per pin and the retired gen_uw generator passed b"" as the
# terminator its own rejoin appends -- both put LF pins into the CRLF file, in bulk.
WRITE = ("SYMBOLS.open(\"a", "rewrite_lines(SYMBOLS", "symbols.csv\").write",
         "dedup_symbols")


def symbols_writers():
    return sorted(path.name for path in TOOLS.glob("*.py")
                  if any(mark in path.read_text(encoding="utf-8") for mark in WRITE))


def test_the_set_of_symbols_writers_is_the_one_this_file_reasons_about():
    """A new writer must not appear without deciding this question.

    Four of the six this file used to name -- gen_small, gen_uw, land_wave and
    zh_sweep's per-site pin append -- went with the generator retirement. Two
    are left, and both answer the question through ledger_io.uniform_terminator.
    """
    assert symbols_writers() == ["dedup_csv.py", "locate.py"], symbols_writers()


@pytest.mark.parametrize("tool", ["dedup_csv.py", "locate.py"])
def test_a_symbols_writer_takes_the_terminator_from_the_file(tool):
    text = (TOOLS / tool).read_text(encoding="utf-8")
    assert "uniform_terminator" in text or "line_terminator" in text or \
        "terminator_census" in text, (
            f"{tool}: the symbols.csv write must ask the file for its terminator, "
            "not spell one out -- every tool that spelled one out spelled LF")
