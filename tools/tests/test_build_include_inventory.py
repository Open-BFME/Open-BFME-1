"""A new earlier include must invalidate an object with unchanged old dependencies."""
import json
import os
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def _fixture(tmp_path, monkeypatch):
    root = tmp_path / "project"
    code = root / "game"
    early = root / "inputs" / "reference" / "shims" / "sweep"
    late = root / "inputs" / "reference" / "original"
    (early / "Common").mkdir(parents=True)
    (late / "Common").mkdir(parents=True)
    code.mkdir()
    source = code / "NetPacket.cpp"
    source.write_text('#include "Common/MessageStream.h"\n')
    original = late / "Common" / "MessageStream.h"
    original.write_text("#define PACKET_RANGE 6\n")
    output = root / "NetPacket.obj"
    output.write_bytes(b"old object")
    command = ["cl", "-I" + str(early), "-I" + str(late)]
    env = {}
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    inventory = build.search_inventory(source, command, env)
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, inventory, [])
    return source, output, early, original, command, env


def test_new_higher_priority_header_invalidates_old_object(tmp_path, monkeypatch):
    source, output, early, original, _, _ = _fixture(tmp_path, monkeypatch)
    assert build.compile_is_current(source, output)
    shadow = early / "Common" / "MessageStream.h"
    shadow.write_text("#define PACKET_RANGE 7\n")
    # Make the directory timestamp change explicit on coarse filesystems.
    previous = (early / "Common").stat().st_mtime_ns
    os.utime(early / "Common", ns=(previous + 1_000_000_000, previous + 1_000_000_000))
    assert original.read_text() == "#define PACKET_RANGE 6\n"
    assert not build.compile_is_current(source, output)


def test_split_include_flags_are_in_the_same_search_inventory(tmp_path, monkeypatch):
    source, _, early, original, command, env = _fixture(tmp_path, monkeypatch)
    late = original.parents[1]
    split = ["cl", "-I", str(early), "/I", str(late)]
    assert build.search_inventory(source, split, env) == build.search_inventory(source, command, env)


def test_source_adjacent_header_invalidates_old_object(tmp_path, monkeypatch):
    source, output, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    assert build.compile_is_current(source, output)
    (source.parent / "Common").mkdir()
    (source.parent / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    assert not build.compile_is_current(source, output)


def test_new_sibling_cpp_does_not_invalidate_header_free_namespace(tmp_path, monkeypatch):
    source, output, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    assert build.compile_is_current(source, output)
    (source.parent / "AnotherBody.cpp").write_text("int other() { return 1; }\n")
    assert build.compile_is_current(source, output)


def test_legacy_cpp_receipt_cannot_prove_search_precedence(tmp_path, monkeypatch):
    source, output, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    sidecar = build._deps_sidecar(output)
    metadata = json.loads(sidecar.read_text())
    metadata.pop("version")
    metadata.pop("inventory")
    sidecar.write_text(json.dumps(metadata))
    assert not build.compile_is_current(source, output)


def test_legacy_header_free_receipt_remains_reusable(tmp_path, monkeypatch):
    source = tmp_path / "bare.cpp"
    source.write_text("int f() { return 1; }\n")
    output = tmp_path / "bare.obj"
    output.write_bytes(b"old object")
    command, env = ["cl"], {}
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": "command", "source": build._hash_file(str(source)), "deps": {},
    }))
    assert build.compile_is_current(source, output)
    command.append("-FIhidden.h")
    assert not build.compile_is_current(source, output)


def test_legacy_empty_deps_with_include_directive_misses(tmp_path, monkeypatch):
    source = tmp_path / "broken.cpp"
    source.write_text('#inc\\\nlude "Later.h"\n')
    output = tmp_path / "broken.obj"
    output.write_bytes(b"old object")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (["cl"], {}))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": "command", "source": build._hash_file(str(source)), "deps": {},
    }))
    assert not build.compile_is_current(source, output)


def test_spliced_or_comment_prefixed_parent_include_refuses_cache(tmp_path, monkeypatch, capsys):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    for directive in ('#inc\\\nlude "../outside/Header.h"\n',
                      '/*why*/ #include "../outside/Header.h"\n'):
        source.write_text('const char *a = "/*"; const char *b = "*/";\n' + directive)
        inventory = build.search_inventory(source, command, env)
        build._write_deps_sidecar(source, output, "command",
                                  "Note: including file: " + str(original), True,
                                  command, env, inventory, [])
        assert not build._deps_sidecar(output).exists()
        assert "unknown search roots" in capsys.readouterr().err


def test_stlport_native_macro_accepts_one_parent_only(tmp_path, monkeypatch):
    vendor = tmp_path / "inputs" / "vendor" / "stlport"
    vendor.mkdir(parents=True)
    header = vendor / "math.h"
    monkeypatch.setattr(build, "ROOT", tmp_path)
    header.write_text("#include _STLP_NATIVE_C_HEADER(math.h)\n")
    assert not build._include_escapes_search_roots(header, True)
    header.write_text("#include _STLP_NATIVE_C_HEADER(../../../outside.h)\n")
    assert build._include_escapes_search_roots(header, True)
    header.write_text("#include _STLP_NATIVE_C_HEADER(body.cpp)\n")
    assert build._include_escapes_search_roots(header, True)


def test_batch_inventory_detects_edit_after_memoized_check(tmp_path, monkeypatch):
    source, _, early, _, command, env = _fixture(tmp_path, monkeypatch)
    cache = {}
    assert build.search_inventory(source, command, env, inventory_cache=cache)
    assert build._inventory_cache_still_current(cache)
    (early / "Common" / "New.h").write_text("#define NEW 1\n")
    assert not build._inventory_cache_still_current(cache)


def test_search_change_during_compile_refuses_sidecar(tmp_path, monkeypatch, capsys):
    source, output, early, original, command, env = _fixture(tmp_path, monkeypatch)
    inventory = build.search_inventory(source, command, env)
    (early / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    previous = (early / "Common").stat().st_mtime_ns
    os.utime(early / "Common", ns=(previous + 1_000_000_000, previous + 1_000_000_000))
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, inventory, [])
    assert not build._deps_sidecar(output).exists()
    assert "deps-cache: not caching" in capsys.readouterr().err


def test_unknown_or_parent_traversing_include_refuses_sidecar(tmp_path, monkeypatch, capsys):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    for directive in ("#include HEADER_NAME\n", '#include"../Common/MessageStream.h"\n',
                      '#include "AnotherBody.cpp"\n'):
        source.write_text(directive)
        inventory = build.search_inventory(source, command, env)
        build._write_deps_sidecar(source, output, "command",
                                  "Note: including file: " + str(original), True,
                                  command, env, inventory, [])
        assert not build._deps_sidecar(output).exists()
        assert "unknown search roots" in capsys.readouterr().err


def test_legacy_asm_without_include_can_still_reuse(tmp_path, monkeypatch):
    source = tmp_path / "body.asm"
    source.write_text("body PROC\nret\nbody ENDP\n")
    output = tmp_path / "body.obj"
    output.write_bytes(b"old object")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (["ml"], {}))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": "command", "source": build._hash_file(str(source)), "deps": {},
    }))
    assert build.compile_is_current(source, output)
