"""The finish lane ranks on the compiler's measurement, not the author's score."""
from pathlib import Path
import shlex
import sys
import time

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import finish_measure  # noqa: E402
import experiment_store  # noqa: E402


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
BROKEN = "compile failed: reverse/attempts/0x00879f60.cpp\nfatal error C1083: Cannot open include file\n"


def test_probe_output_becomes_a_measurement():
    near = finish_measure.parse(NEAR)
    assert (near["diffs"], near["first"], near["compiles"]) == (1, 130, True)
    assert 0.99 < near["quality"] < 1.0
    assert finish_measure.parse(EXACT)["quality"] == 1.0
    assert finish_measure.parse(WRONG_SIZE)["quality"] < 0.05      # 760 diffs + 2 x 168 size error of 1137
    assert finish_measure.parse(BROKEN) == dict(compiles=False, quality=0.0)


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
    assert shlex.split(command) == [Path(sys.executable).as_posix(), "tools/probe.py", str(path), actual, "0x00000010"]


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
                        lambda rva, source: dict(compiles=False, quality=0.0, note="compiler unavailable"))
    assert finish_measure.main(["--one", "0x10", str(path)]) == 1
    output = capsys.readouterr()
    assert "compiler unavailable" in output.err
    assert "probe:" not in output.out
