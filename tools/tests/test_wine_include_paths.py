"""Wine drive mappings must preserve dependency-cache invalidation."""
import os
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import experiment_store

pytestmark = pytest.mark.skipif(os.name == "nt", reason="Wine drive mappings are POSIX paths")


@pytest.fixture
def mapped_tree(tmp_path, monkeypatch):
    root = tmp_path / "Projects" / "Game"
    code = root / "game"
    code.mkdir(parents=True)
    prefix = tmp_path / "prefix"
    devices = prefix / "dosdevices"
    devices.mkdir(parents=True)
    (devices / "x:").symlink_to(tmp_path, target_is_directory=True)
    (devices / "z:").symlink_to("/", target_is_directory=True)
    monkeypatch.setenv("WINEPREFIX", str(prefix))
    monkeypatch.setattr(build, "ROOT", root)
    source = code / "Test.cpp"
    header = code / "Thing.h"
    source.write_text('#include "Thing.h"\nint f() { return VALUE; }\n')
    header.write_text("#define VALUE 1\n")
    return root, source, header, devices


def test_configured_drive_and_case_insensitive_include(mapped_tree):
    root, _, header, _ = mapped_tree
    reported = build._host_path(r"  x:\projects\game\game\thing.h")
    assert build._case_resolve(reported) == str(header)
    assert build._host_path("Z:" + str(header)) == str(header)
    assert build._host_path("game/Thing.h") == str(root / "game/Thing.h")


def test_mapping_is_read_again_after_drive_changes(mapped_tree, tmp_path):
    _, _, _, devices = mapped_tree
    previous = build._host_path(r"X:\Projects\Game\game\Thing.h")
    other = tmp_path / "other"
    other.mkdir()
    (devices / "x:").unlink()
    (devices / "x:").symlink_to(other, target_is_directory=True)
    assert build._host_path(r"X:\Projects\Game\game\Thing.h") != previous
    assert build._host_path(r"X:\Projects\Game\game\Thing.h") == str(other / "Projects/Game/game/Thing.h")


def test_mapped_header_change_invalidates_a_cached_object(mapped_tree, monkeypatch):
    _, source, header, _ = mapped_tree
    output = source.with_suffix(".obj")
    output.write_bytes(b"compiled object")
    monkeypatch.setattr(build, "compiler_command", lambda *_: (["cl"], {}))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._write_deps_sidecar(source, output, "command",
                             r"Note: including file: X:\Projects\Game\game\Thing.h", True)
    assert build.compile_is_current(source, output)
    header.write_text("#define VALUE 222\n")
    assert not build.compile_is_current(source, output)


def test_drive_remapping_invalidates_existing_header_evidence(mapped_tree, tmp_path, monkeypatch):
    _, source, _, devices = mapped_tree
    output = source.with_suffix(".obj")
    output.write_bytes(b"compiled object")
    command, env = ["cl", "-IX:/Projects/Game/game"], {}
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_portable", lambda value: value)
    build._write_deps_sidecar(source, output, build._cmd_fingerprint(command, env),
                             r"Note: including file: X:\Projects\Game\game\Thing.h", True)
    assert build.compile_is_current(source, output)
    other = tmp_path / "other"
    other.mkdir()
    (devices / "x:").unlink()
    (devices / "x:").symlink_to(other, target_is_directory=True)
    assert not build.compile_is_current(source, output)


def test_probe_search_inventory_uses_the_same_drive_mapping(mapped_tree):
    root, source, _, _ = mapped_tree
    expected = experiment_store.search_inventory(source, ["cl"], {"INCLUDE": str(root / "game")})
    actual = experiment_store.search_inventory(source, ["cl", r"-Ix:\projects\game\game"],
                                                {"INCLUDE": r"X:\Projects\Game\game"})
    assert actual is not None and actual == expected
    assert experiment_store.search_inventory(source, ["cl", r"-IY:\missing"], {}) is None


@pytest.mark.parametrize("reported", [r"Y:\missing.h", r"X:relative.h", r"X:"])
def test_unknown_or_drive_relative_paths_refuse_cache(mapped_tree, reported, capsys):
    _, source, _, _ = mapped_tree
    output = source.with_suffix(".obj")
    output.write_bytes(b"compiled object")
    build._deps_sidecar(output).write_text('{"old": "metadata"}')
    build._write_deps_sidecar(source, output, "command", "Note: including file: " + reported, True)
    assert not build._deps_sidecar(output).exists()
    assert "deps-cache: not caching" in capsys.readouterr().err
