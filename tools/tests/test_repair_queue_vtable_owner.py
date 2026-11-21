"""A compiler-created name needs one current real owner, not a source comment.

These tests use actual COFF bytes, a private Git census boundary and normal
build dependency receipts. Only pure toolchain command discovery is fixed for
the portable fixture; no compiler runs and no cache verdict is mocked true.
The separate pass-test child is an orchestration fixture, not a C++ verifier.
"""
import hashlib
import json
import pickle
import struct
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build as B
import link_check as C
import link_census as L
from test_repair_queue import load

VTABLE = "??_7FixtureOwner@@6B@"


def data_coff(name=VTABLE, *, storage=2, section=1, duplicate=False, function=False):
    """A complete one-section i386 object; undefined/weak controls are real COFF."""
    strings = bytearray(b"\0" * 4)

    def symbol(spelling, cls, sec, typ=0, aux=0):
        encoded = spelling.encode()
        if len(encoded) > 8:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(encoded + b"\0")
        else:
            field = encoded.ljust(8, b"\0")
        return field + struct.pack("<IhHBB", 0, sec, typ, cls, aux)

    records = [symbol(name, storage, section, 0x20 if function else 0,
                      1 if storage == 105 else 0)]
    if storage == 105:
        records += [struct.pack("<II", 2, 2) + b"\0" * 10,
                    symbol("fallback", 2, 0, 0x20)]
    if duplicate:
        records.append(symbol(name, storage, section))
    strings[:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, 64, len(records), 0, 0)
    sec = b".rdata\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 4, 60, 0, 0, 0, 0, 0x40000040)
    return header + sec + b"\0" * 4 + b"".join(records) + strings


def git(root, *args):
    return subprocess.check_output(["git", "-C", str(root), *args], text=True).strip()


@pytest.fixture
def owner(tmp_path, monkeypatch):
    monkeypatch.syspath_prepend(str(Path(__file__).resolve().parents[1]))
    root = tmp_path / "repo"
    root.mkdir()
    rel = "game/GameEngine/Owner.cpp"
    rq, rev, _ = load(root, "bfme1", [("?ctor@FixtureOwner@@QAEXXZ", 0x1000, 16,
                                      "GameEngine/Owner.cpp")], [
        (rel, '#include "Owner.h"\nclass FixtureOwner { public: virtual ~FixtureOwner(); };\n'),
        ("game/GameEngine/Owner.h", "#define OWNER_VERSION 1\n"),
        (".gitignore", "build/\n"),
        ("tools/build.py", 'import json,os,sys\nfrom pathlib import Path\n'
         'root=Path.cwd()\np=root/"targets/game/reverse/body_guard_baseline.csv"\n'
         'raw=p.read_bytes()\nassert b"??_7FixtureOwner@@6B@" not in raw\n'
         '(root/"build/gate.json").write_text(json.dumps({"args":sys.argv[1:],"baseline":raw.hex()}))\n'
         'raise SystemExit(int(os.environ.get("TEST_REPAIR_GATE_EXIT","0")))\n')])
    source = root / rel
    header = source.with_suffix(".h")
    for module in (B, C, L):
        monkeypatch.setattr(module, "ROOT", root)
    monkeypatch.setattr(B, "BUILD_DIR", root / "build/match")
    monkeypatch.setattr(C, "INDEX", root / "build/link_census/link_index.pkl")
    monkeypatch.setattr(C, "_TRACKED", None)
    obj = B.obj_path(source)
    obj.parent.mkdir(parents=True)
    obj.write_bytes(data_coff())
    # Actual fingerprint, source/header hashing, COFF validation and directory
    # inventory remain native; this is only deterministic command discovery.
    command = ["cl", "-I" + str(source.parent), "-Fo" + str(obj), str(source)]
    env = {}
    monkeypatch.setattr(B, "compiler_command", lambda *_: (command, env))
    inventory = B.search_inventory(source, command, env)
    B._write_deps_sidecar(source, obj, B._cmd_fingerprint(command, env),
                          "Note: including file: " + str(header), True,
                          command, env, inventory, [])
    assert B.compile_is_current(source, obj)
    git(root, "init", "-q")
    git(root, "add", ".")
    git(root, "-c", "user.name=fixture", "-c", "user.email=fixture@example.invalid",
        "commit", "-qm", "fixture census inputs")
    index = {"meta": {"commit": git(root, "rev-parse", "HEAD"), "date": "fixture"},
             "objects": [obj.name], "strong": {VTABLE: [0]}, "comdat": {}, "common": {},
             "selection": {}, "blockers": {rel: {"object": obj.name}},
             "weak_root": str(root.resolve()),
             "weak_inventory": {obj.name: (str(obj), hashlib.sha256(obj.read_bytes()).hexdigest())}}

    def save():
        C.INDEX.parent.mkdir(parents=True, exist_ok=True)
        C.INDEX.write_bytes(pickle.dumps(index))

    save()
    return SimpleNamespace(root=root, rev=rev, rq=rq, rel=rel, source=source, header=header,
                           obj=obj, index=index, save=save, command=command)


def test_compiler_name_locates_real_current_owner_without_source_literal(owner):
    assert VTABLE not in owner.source.read_text()
    assert owner.rq.locate_source(VTABLE) == owner.rel


def test_compiler_name_comdat_and_strong_inventory_same_definer_is_one_owner(owner):
    owner.index["comdat"][VTABLE] = [(0, "same-object", None)]
    owner.save()
    assert owner.rq.locate_source(VTABLE) == owner.rel


@pytest.mark.parametrize("damage", [
    "missing-index", "broken-index", "foreign-root", "missing-inventory", "digest",
    "missing-object", "missing-receipt", "source-receipt", "dependency-receipt", "command",
    "inventory", "source-change", "dependency-change", "new-source", "unknown-commit",
])
def test_compiler_owner_refuses_missing_stale_or_different_evidence(owner, damage):
    if damage == "missing-index":
        C.INDEX.unlink()
    elif damage == "broken-index":
        C.INDEX.write_bytes(b"not a census")
    elif damage == "foreign-root":
        owner.index["weak_root"] = str(owner.root.parent)
        owner.save()
    elif damage == "missing-inventory":
        owner.index["weak_inventory"] = {}
        owner.save()
    elif damage == "digest":
        owner.obj.write_bytes(owner.obj.read_bytes() + b"different object")
    elif damage == "missing-object":
        owner.obj.unlink()
    elif damage == "missing-receipt":
        B._deps_sidecar(owner.obj).unlink()
    elif damage in ("source-receipt", "dependency-receipt", "inventory"):
        sidecar = B._deps_sidecar(owner.obj)
        receipt = json.loads(sidecar.read_text())
        if damage == "source-receipt":
            receipt["source"] = "0" * 64
        elif damage == "dependency-receipt":
            receipt["deps"] = {key: "0" * 64 for key in receipt["deps"]}
        else:
            receipt["inventory"] = "not the current include directories"
        sidecar.write_text(json.dumps(receipt))
    elif damage == "command":
        owner.command.append("-DOTHER_PROFILE")
    elif damage == "source-change":
        owner.source.write_text(owner.source.read_text() + "// changed\n")
    elif damage == "dependency-change":
        owner.header.write_text("#define OWNER_VERSION 2\n")
    elif damage == "new-source":
        (owner.source.parent / "AnotherEmitter.cpp").write_text("// unknown new definer\n")
    elif damage == "unknown-commit":
        owner.index["meta"]["commit"] = "not-a-commit"
        owner.save()
    assert owner.rq.locate_source(VTABLE) is None


@pytest.mark.parametrize("kwargs", [
    {"section": 0}, {"storage": 105, "section": 0}, {"name": "??_7Different@@6B@"},
    {"duplicate": True}, {"function": True},
])
def test_index_name_without_exact_external_data_definition_is_not_an_owner(owner, kwargs):
    owner.obj.write_bytes(data_coff(**kwargs))
    owner.index["weak_inventory"][owner.obj.name] = (
        str(owner.obj), hashlib.sha256(owner.obj.read_bytes()).hexdigest())
    owner.save()
    assert B.compile_is_current(owner.source, owner.obj)  # native inputs still match
    assert owner.rq.locate_source(VTABLE) is None


@pytest.mark.parametrize("other", ["second-source", "second-object"])
def test_multiple_compiler_owners_are_refused_even_if_one_is_first(owner, other):
    owner.index["blockers"]["game/GameEngine/Other.cpp"] = {"object": owner.obj.name}
    if other == "second-object":
        owner.index["objects"].append("other.obj")
        owner.index["weak_inventory"]["other.obj"] = (str(owner.obj), "unknown")
        owner.index["strong"][VTABLE].append(1)
    owner.save()
    assert owner.rq.locate_source(VTABLE) is None


@pytest.mark.parametrize("source", [
    "game/Missing.cpp", "game/../outside.cpp", "Other/Owner.cpp", "game/Owner.asm",
    "game\\GameEngine\\Owner.cpp", "game/Untracked.cpp",
])
def test_compiler_owner_source_paths_must_be_safe_existing_tracked_c_cpp(owner, source):
    entry = owner.index["blockers"].pop(owner.rel)
    owner.index["blockers"][source] = entry
    owner.save()
    assert owner.rq.locate_source(VTABLE) is None


def test_compiler_owner_does_not_reuse_a_different_object_for_a_source(owner):
    other = owner.obj.with_name("other.obj")
    other.write_bytes(owner.obj.read_bytes())
    owner.index["objects"] = [other.name]
    owner.index["blockers"][owner.rel]["object"] = other.name
    owner.index["weak_inventory"] = {other.name: (str(other), hashlib.sha256(other.read_bytes()).hexdigest())}
    owner.save()
    assert owner.rq.locate_source(VTABLE) is None


@pytest.mark.parametrize("exitcode", [0, 7])
def test_compiler_owner_pass_test_calls_original_gate_and_restores_all_bytes(owner, monkeypatch, exitcode):
    path = owner.rev / "body_guard_baseline.csv"
    line = f"dir32,0x00402000,{VTABLE},unowned datum"
    untouched = b"tail,0x00003000,other,last row without newline"
    header = b"check,target_rva,name,detail\r\n"
    raw = header + line.encode() + b"\r\n" + untouched
    path.write_bytes(raw)
    monkeypatch.setenv("TEST_REPAIR_GATE_EXIT", str(exitcode))
    ok, _ = owner.rq.pass_test(line)
    assert ok == (exitcode == 0)
    gate = json.loads((owner.root / "build/gate.json").read_text())
    assert gate == {"args": [owner.rel], "baseline": (header + untouched).hex()}
    assert path.read_bytes() == (header + untouched if ok else raw)


def test_compiler_branch_never_uses_grep_after_census_refusal(owner, monkeypatch):
    C.INDEX.unlink()
    native_run = owner.rq.subprocess.run

    def run(command, **kwargs):
        assert command[:2] != ["git", "grep"]
        return native_run(command, **kwargs)

    monkeypatch.setattr(owner.rq.subprocess, "run", run)
    assert owner.rq.locate_source(VTABLE) is None
