"""Real bounded dispatch through the build and census process pools."""
import hashlib
import concurrent.futures.process
import json
import multiprocessing
import os
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import link_census as census
from test_weak_fallback_truth import coff, provider_coff

_STALE_CHUNK = build._stale_chunk
_OBJECT_FACTS = census.object_facts


def fixture_compiler_command(source, output):
    return ["fixture-compiler", "-I" + str(source.parent / "include")], {}


def observed_stale_chunk(pairs):
    assert multiprocessing.get_start_method() == "spawn"
    assert os.getpid() != int(pairs[0][0].parent.name)
    # Keep external tool discovery/path conversion out of this pure fixture;
    # the receipt hashes and include inventory checks remain the real code.
    build.compiler_command = fixture_compiler_command
    build.wine_path = str
    return _STALE_CHUNK(pairs)


def observed_object_facts(obj):
    assert multiprocessing.get_start_method() == "spawn"
    assert os.getpid() != int(obj.parent.name)
    assert isinstance(census._TRUTH, census.RetailTruth)
    assert census._TRUTH._weak_rows_current is True
    assert census._TRUTH.ledger["pool_fixture"] == {0x1000}
    return _OBJECT_FACTS(obj)


def test_stale_sources_spawn_dispatch_agrees_with_serial(tmp_path, monkeypatch):
    default = multiprocessing.get_start_method()
    root = tmp_path / str(os.getpid())
    root.mkdir()
    sources = [root / f"source{i}.cpp" for i in range(200)]
    outputs = {source: source.with_suffix(".obj") for source in sources}
    include = root / "include"
    include.mkdir()
    for source in sources[:5]:
        source.write_text(f'#include "{source.stem}.h"\n')
        (include / (source.stem + ".h")).write_text("#define VALUE 1\n")
        outputs[source].write_bytes(b"pure fixture object")
        build._deps_sidecar(outputs[source]).write_text("{}")
    monkeypatch.setattr(build, "compiler_command", fixture_compiler_command)
    monkeypatch.setattr(build, "wine_path", str)
    for source in sources[:4]:
        header = include / (source.stem + ".h")
        command, env = fixture_compiler_command(source, outputs[source])
        build._deps_sidecar(outputs[source]).write_text(json.dumps({
            "version": 2, "source": build._hash_file(str(source)),
            "deps": {str(header): build._hash_file(str(header))},
            "cmd": build._cmd_fingerprint(command, env),
            "inventory": build.search_inventory(source, command, env),
        }))
    sources[1].write_text(sources[1].read_text() + "// changed source\n")
    (include / (sources[2].stem + ".h")).write_text("#define VALUE 2\n")
    sidecar = build._deps_sidecar(outputs[sources[3]])
    meta = json.loads(sidecar.read_text())
    meta["cmd"] = "different compiler recipe"
    sidecar.write_text(json.dumps(meta))
    assert build.compile_is_current(sources[0], outputs[sources[0]])
    serial = build.stale_sources(sources, outputs, workers=1)
    assert serial == sources[1:]
    monkeypatch.setattr(build, "_stale_chunk", observed_stale_chunk)
    parallel = build.stale_sources(sources, outputs, workers=2)
    assert parallel == [source for source in sources[::2] + sources[1::2] if source != sources[0]]
    assert set(parallel) == set(serial) and len(parallel) == len(serial)
    assert multiprocessing.get_start_method() == default


def test_census_spawn_dispatch_preserves_initializer_and_facts(tmp_path, monkeypatch):
    default = multiprocessing.get_start_method()
    root = tmp_path / str(os.getpid())
    root.mkdir()
    objs = [root / "provider.obj", root / "table.obj"]
    objs[0].write_bytes(provider_coff())
    objs[1].write_bytes(coff())
    rows = census.LedgerRows([{"name": "pool_fixture", "source": "game/PoolFixture.cpp",
                              "target_rva": "0x00001000", "notes": ""}])
    digest = hashlib.sha256()
    with build.FUNCTIONS.open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    rows.digest = digest.hexdigest()
    monkeypatch.setattr(build, "_pool_size", lambda: 1)
    serial = census.read_facts(objs, rows)
    monkeypatch.setattr(build, "_pool_size", lambda: 2)
    monkeypatch.setattr(census, "object_facts", observed_object_facts)
    parallel = census.read_facts(objs, rows)
    assert parallel == serial
    for obj, actual, expected in zip(objs, parallel, serial):
        assert isinstance(actual, census.ObjectFacts)
        assert actual.__dict__ == expected.__dict__
        assert actual.data == obj.read_bytes()
        assert actual.truth and actual.policy
    census.validate_fact_snapshots(objs, parallel)
    with pytest.raises(census.MissingObject, match="cannot read the object"):
        census.read_facts([root / "missing.obj"], rows)
    assert multiprocessing.get_start_method() == default


def test_census_spawn_refuses_invalid_ledger_in_initializer(tmp_path, monkeypatch):
    obj = tmp_path / "provider.obj"
    obj.write_bytes(provider_coff())
    rows = census.LedgerRows()
    rows.digest = "not the current ledger digest"
    monkeypatch.setattr(build, "_pool_size", lambda: 1)
    with pytest.raises(census.MissingObject, match="function ledger changed"):
        census.read_facts([obj], rows)
    monkeypatch.setattr(build, "_pool_size", lambda: 2)
    with pytest.raises(concurrent.futures.process.BrokenProcessPool):
        census.read_facts([obj], rows)
