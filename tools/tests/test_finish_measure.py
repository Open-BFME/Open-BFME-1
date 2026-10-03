"""The finish lane ranks on the compiler's measurement, not the author's score."""
from pathlib import Path
import shlex
import subprocess
import sys
import time
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import finish_measure  # noqa: E402
import experiment_store  # noqa: E402
import eligibility  # noqa: E402


@pytest.fixture
def proof(monkeypatch):
    # These ranking tests isolate ordering from retail-image and compiler I/O.
    # Input/receipt invalidation is exercised separately with real fixtures.
    monkeypatch.setattr(finish_measure, "hypothesis",
                        lambda rva, path: finish_measure.body_hash(path))
    monkeypatch.setattr(experiment_store, "validated_object_receipt", lambda path: "object")
    def entry(path, **fields):
        return dict(fields, version=finish_measure.VERSION,
                    fingerprint=finish_measure.body_hash(path), receipt="object",
                    path=str(path), at=time.time())
    return entry

NEAR = """compile  reused verified dependency cache
symbol   ?f@@YAXXZ
size     ours=143 retail=143  relocs=4
diffs    1 non-reloc byte(s); first at +130
candidate instruction-change  (confidence pattern only)
"""
EXACT = "symbol   ?f@@YAXXZ\nsize     ours=90 retail=90  relocs=1\nresult   EXACT (modulo relocation slots)\n"
WRONG_SIZE = "size     ours=1305 retail=1137  relocs=9\ndiffs    760 non-reloc byte(s); first at +12\n"
BROKEN = "compile failed: targets/game/reverse/attempts/0x00879f60.cpp\nfatal error C1083: Cannot open include file\n"


def test_probe_output_becomes_a_measurement():
    near = finish_measure.parse(NEAR)
    assert (near["diffs"], near["first"], near["compiles"]) == (1, 130, True)
    assert 0.99 < near["quality"] < 1.0
    assert finish_measure.parse(EXACT)["quality"] == 1.0
    assert finish_measure.parse(WRONG_SIZE)["quality"] < 0.05      # 760 diffs + 2 x 168 size error of 1137
    assert finish_measure.parse(BROKEN) == dict(compiles=False, quality=0.0)


@pytest.mark.parametrize("diagnostic", [
    "attempt.cpp(1) : error C2065: 'missing' : undeclared identifier",
    "attempt.cpp(33) : error C2908: explicit specialization; 'StringBase<unsigned short>::str' has already been instantiated",
    "attempt.cpp(1) : fatal error C1083: Cannot open include file: 'missing.h': No such file or directory",
])
def test_confirmed_source_error_measures_zero(tmp_path, monkeypatch, diagnostic):
    path = stash(tmp_path, "source_error.cpp", "int f;")
    monkeypatch.setattr(finish_measure.subprocess, "run", lambda *a, **kw: SimpleNamespace(
        returncode=1, stdout=diagnostic, stderr=f"compile failed: {path}"))
    result = finish_measure.measure(0x10, path)
    assert result["compiles"] is False and result["quality"] == 0.0
    assert not result.get("unavailable")


@pytest.mark.parametrize("stdout,stderr,code", [
    ("", "wineserver: bind: Operation not permitted\nTraceback (most recent call last):\nwinepath failed", 1),
    ("fatal error C1083: Cannot open compiler intermediate file: 'temp': Permission denied", "compile failed: attempt.cpp", 1),
    ("fatal error C1083: Cannot open include file: 'header.h': Permission denied", "compile failed: attempt.cpp", 1),
    ("fatal error C1033: cannot open program database", "compile failed: attempt.cpp", 1),
    ("fatal error C1060: compiler is out of memory", "compile failed: attempt.cpp", 1),
    ("error C1999: unrecognized diagnostic", "compile failed: attempt.cpp", 1),
    ("error C2065: 'missing': undeclared identifier\nRuntime Error!\nMicrosoft Visual C++ Runtime Library\nruntime error R6002", "compile failed: attempt.cpp", 1),
    ("error C2065: 'missing': undeclared identifier", "compile failed: attempt.cpp\nwineserver: bind: Operation not permitted", 1),
    ("error C2908: explicit specialization; 'StringBase<unsigned short>::str' has already been instantiated", "compile failed: attempt.cpp\nwineserver: bind: Operation not permitted", 1),
    (EXACT, "ModuleNotFoundError: No module named capstone", 1),
    ("result   NOT IN OBJECT\nwineserver: bind: Operation not permitted", "", 2),
    ("", "", 1),
    ("", "", 0),
])
def test_tool_or_unknown_failure_has_no_measured_quality(tmp_path, monkeypatch, stdout, stderr, code):
    path = stash(tmp_path, "unavailable.cpp", "int f;")
    monkeypatch.setattr(finish_measure.subprocess, "run", lambda *a, **kw: SimpleNamespace(
        returncode=code, stdout=stdout, stderr=stderr))
    result = finish_measure.measure(0x10, path)
    assert result["compiles"] is False and result["unavailable"] is True
    assert "quality" not in result


def test_probe_timeout_has_no_measured_quality(tmp_path, monkeypatch):
    path = stash(tmp_path, "timeout.cpp", "int f;")
    def timeout(*args, **kwargs):
        raise subprocess.TimeoutExpired(args[0], kwargs["timeout"])
    monkeypatch.setattr(finish_measure.subprocess, "run", timeout)
    result = finish_measure.measure(0x10, path)
    assert result == dict(compiles=False, unavailable=True, note="probe timed out")


def test_completed_missing_symbol_probe_measures_zero(tmp_path, monkeypatch):
    path = stash(tmp_path, "missing_symbol.cpp", "int f;")
    monkeypatch.setattr(finish_measure.subprocess, "run", lambda *a, **kw: SimpleNamespace(
        returncode=2, stdout=NOT_IN_OBJECT, stderr=""))
    monkeypatch.setattr(finish_measure, "object_symbols", lambda *a: [])
    monkeypatch.setattr(finish_measure, "fallback_symbols", lambda *a: [])
    monkeypatch.setattr(finish_measure, "ledger_size", lambda *a: 10)
    result = finish_measure.measure(0x10, path)
    assert result["compiles"] is False and result["quality"] == 0.0
    assert not result.get("unavailable")


def test_failure_during_symbol_probe_is_unavailable(tmp_path, monkeypatch):
    path = stash(tmp_path, "fallback.cpp", "int f;")
    replies = iter([
        SimpleNamespace(returncode=2, stdout=NOT_IN_OBJECT, stderr=""),
        SimpleNamespace(returncode=1, stdout="", stderr="wineserver: bind: Operation not permitted"),
    ])
    monkeypatch.setattr(finish_measure.subprocess, "run", lambda *a, **kw: next(replies))
    monkeypatch.setattr(finish_measure, "object_symbols", lambda *a: ["?actual@@YAXXZ"])
    monkeypatch.setattr(finish_measure, "ledger_size", lambda *a: 10)
    result = finish_measure.measure(0x10, path)
    assert result["unavailable"] is True and "quality" not in result


def test_unavailable_probe_is_not_cached(tmp_path, monkeypatch, proof):
    path = stash(tmp_path, "unavailable.cpp", "int f;")
    monkeypatch.setattr(finish_measure, "CACHE", tmp_path / "cache.json")
    monkeypatch.setattr(finish_measure, "measure", lambda *a: dict(
        compiles=False, unavailable=True, note="probe timed out"))
    assert finish_measure.ensure([(0x10, path)], budget=1) == {}
    assert not finish_measure.CACHE.exists()


def stash(tmp_path, name, body):
    path = tmp_path / name
    path.write_text(f"// ?f@@YAXXZ\n// partial score=0.99 date=2026-09-01\n{body}\n", encoding="utf-8")
    return path


def test_measured_quality_outranks_an_optimistic_author_score(tmp_path, proof):
    honest, boastful, unmeasured = (stash(tmp_path, n, n) for n in ("a.cpp", "b.cpp", "c.cpp"))
    cache = {
        "0x00000010": proof(honest, **finish_measure.parse(NEAR)),
        "0x00000020": proof(boastful, **finish_measure.parse(BROKEN)),
    }
    bodies = [(0x20, boastful, 0.999, 700), (0x30, unmeasured, 0.95, 300), (0x10, honest, 0.90, 143)]
    bodies.sort(key=lambda b: finish_measure.rank_key(cache, *b))
    assert [b[0] for b in bodies] == [0x10, 0x30, 0x20]      # a failed probe cannot outrank fresh work


def test_a_changed_stash_body_is_measured_again_but_a_new_score_is_not(tmp_path, proof):
    path = stash(tmp_path, "a.cpp", "int x;")
    cache = {"0x00000010": proof(path, compiles=True, quality=0.5)}
    assert finish_measure.current(cache, 0x10, path)
    path.write_text("// ?f@@YAXXZ\n// partial score=0.999 date=2026-09-21\nint x;\n", encoding="utf-8")
    assert finish_measure.current(cache, 0x10, path)          # same hypothesis, louder claim
    path.write_text("// ?f@@YAXXZ\n// partial score=0.999 date=2026-09-21\nint y;\n", encoding="utf-8")
    assert finish_measure.current(cache, 0x10, path) is None


def test_ensure_respects_its_budget(tmp_path, monkeypatch):
    monkeypatch.setattr(finish_measure, "hypothesis",
                        lambda rva, path: finish_measure.body_hash(path))
    monkeypatch.setattr(experiment_store, "validated_object_receipt", lambda path: "object")
    monkeypatch.setattr(finish_measure, "CACHE", tmp_path / "cache.json")
    monkeypatch.setattr(finish_measure, "measure", lambda rva, path: finish_measure.parse(EXACT))
    bodies = [(0x10 * i, stash(tmp_path, f"{i}.cpp", str(i))) for i in range(1, 6)]
    cache = finish_measure.ensure(bodies, budget=2)
    assert len(cache) == 2
    assert len(finish_measure.ensure(bodies, budget=10)) == 5
    assert finish_measure.load().keys() == cache.keys() | finish_measure.load().keys()


NOT_IN_OBJECT = """compile  reused verified dependency cache
symbol   ?d_00689170@@YAXXZ
result   NOT IN OBJECT -- the TU compiled, but defines no symbol by that name.
nearest  defined symbols in this object (copy the exact one):
         ??1AsciiString@@QAE@XZ
         ?_bfme_onSerializedGameInfo_00689170@LANAPI@@UAE_NPAUTransportAddress@@HPADI@Z
         ??0AsciiString@@QAE@PBD@Z
         ?_bfme_handleHasMap_0068ACF0@LANAPI@@IAEXPAULANMessage@@PBUTransportAddress@@@Z
         __ehhandler$?_bfme_onSerializedGameInfo_00689170@LANAPI@@UAE_NPAUTransportAddress@@HPADI@Z
hint     the class/namespace/const-ness/calling convention in the mangled name must match the C++ you wrote;
"""


def test_a_ledger_name_in_the_header_is_not_a_compile_failure():
    names = finish_measure.fallback_symbols(NOT_IN_OBJECT, 0x00689170)
    assert names[0].startswith("?_bfme_onSerializedGameInfo_00689170@")     # the address-tagged one first
    assert not any(n.startswith("__ehhandler") for n in names)
    assert names[-1].startswith("??")                                        # constructors and destructors last
    assert finish_measure.fallback_symbols(NEAR, 0x10) == []


def test_one_prints_the_measured_symbol_not_the_stale_stash_header(tmp_path, monkeypatch, capsys):
    path = stash(tmp_path, "bank.cpp", "int x;")
    actual = "?real@Class@@QAEXXZ"
    monkeypatch.setattr(finish_measure, "hypothesis", lambda rva, source: finish_measure.body_hash(source))
    monkeypatch.setattr(finish_measure, "measure",
                        lambda rva, source: dict(finish_measure.parse(NEAR), symbol=actual))
    monkeypatch.setattr(experiment_store, "validated_object_receipt", lambda source: "current")
    assert finish_measure.main(["--one", "0x10", str(path)]) == 0
    output = capsys.readouterr().out
    assert f"candidate object symbol  {actual}" in output
    assert "Diagnostic only" in output
    command = next(line.removeprefix("probe: ") for line in output.splitlines()
                   if line.startswith("probe: "))
    arguments = shlex.split(command)
    assert arguments[:2] == [Path(sys.executable).as_posix(), "tools/probe.py"]
    assert (finish_measure.ROOT / arguments[2]).resolve() == path.resolve()
    assert arguments[3:] == [actual, "0x00000010"]


def test_one_rejects_a_stash_changed_during_measurement(tmp_path, monkeypatch, capsys):
    path = stash(tmp_path, "bank.cpp", "int x;")
    monkeypatch.setattr(finish_measure, "hypothesis", lambda rva, source: finish_measure.body_hash(source))
    def change_source(rva, source):
        source.write_text(source.read_text() + "int y;\n", encoding="utf-8")
        return dict(finish_measure.parse(NEAR), symbol="?real@Class@@QAEXXZ")
    monkeypatch.setattr(finish_measure, "measure", change_source)
    assert finish_measure.main(["--one", "0x10", str(path)]) == 1
    output = capsys.readouterr()
    assert "inputs changed" in output.err
    assert "probe:" not in output.out


def test_one_rejects_stale_compiler_dependencies_and_failed_probes(tmp_path, monkeypatch, capsys):
    path = stash(tmp_path, "bank.cpp", "int x;")
    monkeypatch.setattr(finish_measure, "hypothesis", lambda rva, source: finish_measure.body_hash(source))
    monkeypatch.setattr(finish_measure, "measure",
                        lambda rva, source: dict(finish_measure.parse(NEAR), symbol="?real@Class@@QAEXXZ"))
    monkeypatch.setattr(experiment_store, "validated_object_receipt", lambda source: None)
    assert finish_measure.main(["--one", "0x10", str(path)]) == 1
    output = capsys.readouterr()
    assert "no longer current" in output.err
    assert "probe:" not in output.out
    monkeypatch.setattr(finish_measure, "measure",
                        lambda rva, source: dict(compiles=False, unavailable=True, note="compiler unavailable"))
    assert finish_measure.main(["--one", "0x10", str(path)]) == 1
    output = capsys.readouterr()
    assert "compiler unavailable" in output.err
    assert "probe:" not in output.out


# --------------------------------------------------------------------------
# Argument parsing: nothing reaches a compiler before the mode is decided.
# --help and every rejected argument used to fall through to the bulk pass,
# which spends one probe per unmeasured body.
# --------------------------------------------------------------------------

@pytest.fixture
def no_measurement(monkeypatch):
    """Make every entry point that can spend a compiler run loud about it."""
    def forbidden(*args, **kwargs):
        print("MEASUREMENT_REACHED", file=sys.stderr)
        raise AssertionError("argument parsing must decide before any measurement")
    for name in ("ensure", "measure", "measure_one", "save"):
        monkeypatch.setattr(finish_measure, name, forbidden)
    monkeypatch.setattr(eligibility, "finish_bodies", forbidden)
    return forbidden


@pytest.mark.parametrize("flag", ["--help", "-h"])
def test_help_prints_usage_and_never_measures(flag, no_measurement, capsys):
    assert finish_measure.main([flag]) == 0
    output = capsys.readouterr()
    assert "usage: finish_measure.py" in output.out
    assert "--one RVA STASH" in output.out and "--report" in output.out
    assert output.err == ""


@pytest.mark.parametrize("argv,offending", [
    (["--hepl"], "--hepl"),                       # a typo, not a flag
    (["-x"], "-x"),
    (["0x00000010"], "0x00000010"),               # a stray positional used to measure all 350
    (["--min_score", "0.9"], "--min_score"),      # underscore spelling
    (["--report-all"], "--report-all"),
    (["--min-score"], "--min-score"),             # value missing: was an IndexError traceback
    (["--limit"], "--limit"),
    (["--min-score", "high"], "high"),
    (["--limit", "many"], "many"),
    (["--report", "--limit", "3"], "--limit"),
    (["--one"], "--one"),
    (["--one", "0x10"], "RVA and STASH"),
    (["--one", "notanrva", "stash.cpp"], "notanrva"),
    (["--one", "0x10", "stash.cpp", "--min-score", "0.5"], "--min-score"),
    (["--report", "--one", "0x10", "stash.cpp"], "RVA and STASH"),
])
def test_unsupported_argument_is_refused_without_measuring(argv, offending, no_measurement, capsys):
    assert finish_measure.main(argv) == 2
    output = capsys.readouterr()
    assert offending in output.err
    assert "usage: finish_measure.py" in output.err
    assert output.out == ""


def test_parse_args_keeps_the_documented_bulk_and_report_arguments():
    assert finish_measure.parse_args([]) == (("bulk", {"floor": 0.9, "limit": 10 ** 6}), "")
    assert finish_measure.parse_args(["--min-score", "0.95", "--limit", "3"]) == (
        ("bulk", {"floor": 0.95, "limit": 3}), "")
    assert finish_measure.parse_args(["--limit=3"]) == (("bulk", {"floor": 0.9, "limit": 3}), "")
    assert finish_measure.parse_args(["--report"]) == (("report", {"floor": 0.9}), "")
    assert finish_measure.parse_args(["--report", "--min-score=0.5"]) == (("report", {"floor": 0.5}), "")
    assert finish_measure.parse_args(["--one", "0x10", "banked.cpp"]) == (
        ("one", {"rva": 16, "stash": "banked.cpp"}), "")


def test_the_default_bulk_pass_still_measures_every_unmeasured_body(monkeypatch, capsys):
    calls = {}
    def finish_bodies(floor):
        calls["floor"] = floor
        return []
    def ensure(bodies, budget):
        calls["budget"] = budget
        return {}
    monkeypatch.setattr(eligibility, "finish_bodies", finish_bodies)
    monkeypatch.setattr(finish_measure, "ensure", ensure)
    assert finish_measure.main([]) == 0
    assert calls == {"floor": 0.9, "budget": 10 ** 6}
    assert "0 of 0 measured" in capsys.readouterr().out
    assert finish_measure.main(["--min-score", "0.95", "--limit", "3"]) == 0
    assert calls == {"floor": 0.95, "budget": 3}


def test_report_still_reads_the_cache_and_measures_nothing(monkeypatch, capsys, tmp_path):
    monkeypatch.setattr(finish_measure, "CACHE", tmp_path / "cache.json")
    monkeypatch.setattr(eligibility, "finish_bodies", lambda floor: [])
    monkeypatch.setattr(finish_measure, "ensure", lambda *a, **kw: pytest.fail("--report must not measure"))
    assert finish_measure.main(["--report"]) == 0
    assert "0 of 0 finish stashes measured" in capsys.readouterr().out
    assert not finish_measure.CACHE.exists()


CLI_DRIVER = """\
import sys
from pathlib import Path
sys.path.insert(0, {tools!r})
import eligibility
import finish_measure as f

def forbidden(*args, **kwargs):
    print("MEASUREMENT_REACHED", file=sys.stderr)
    raise SystemExit(9)

eligibility.finish_bodies = lambda floor: []      # a ledger walk, not a compile
f.ensure = f.measure = f.measure_one = f.save = forbidden
f.CACHE = Path({cache!r})
raise SystemExit(f.main())
"""


def run_cli(tmp_path, *argv):
    """The real command line in a subprocess: real sys.argv, real exit code.

    Every side effect is replaced by a loud stub, so a parser that regressed
    into the bulk pass fails the test instead of spending 350 compiler runs.
    """
    cache = tmp_path / "finish_measured.json"
    driver = tmp_path / "cli.py"
    driver.write_text(CLI_DRIVER.format(
        tools=str(Path(finish_measure.__file__).parent), cache=str(cache)))
    result = subprocess.run([sys.executable, str(driver), *argv],
                            capture_output=True, text=True, timeout=60)
    return result, cache


@pytest.mark.parametrize("argv,code,needle", [
    (("--help",), 0, "usage: finish_measure.py"),
    (("-h",), 0, "usage: finish_measure.py"),
    (("--report",), 0, "0 of 0 finish stashes measured"),
    (("--hepl",), 2, "--hepl"),
    (("--min_score", "0.9"), 2, "--min_score"),
    (("0x00000010",), 2, "0x00000010"),
    (("--min-score",), 2, "needs a value"),
    (("--limit",), 2, "needs a value"),
    (("--min-score", "high"), 2, "high"),
    (("--limit", "many"), 2, "many"),
    (("--report", "--limit", "3"), 2, "--limit"),
    (("--one",), 2, "RVA and STASH"),
    (("--one", "0x10"), 2, "RVA and STASH"),
    (("--one", "notanrva", "banked.cpp"), 2, "notanrva"),
    (("--one", "0x10", "banked.cpp", "--min-score", "0.5"), 2, "--min-score"),
])
def test_the_command_line_never_falls_through_to_the_measurement_pass(tmp_path, argv, code, needle):
    result, cache = run_cli(tmp_path, *argv)
    assert result.returncode == code, result.stderr
    assert needle in result.stdout + result.stderr
    assert "MEASUREMENT_REACHED" not in result.stderr, result.stderr
    assert not cache.exists()


@pytest.mark.parametrize("argv", [
    (),                                              # no argument: the documented bulk pass
    ("--min-score", "0.5", "--limit", "1"),          # bounded bulk pass
    ("--one", "0x10", "banked.cpp"),                 # one manual probe
])
def test_the_documented_arguments_still_reach_their_pass(tmp_path, argv):
    result, cache = run_cli(tmp_path, *argv)
    assert result.returncode == 9, result.stderr      # the stub's own exit code
    assert "MEASUREMENT_REACHED" in result.stderr
    assert not cache.exists()
