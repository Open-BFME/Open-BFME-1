#!/usr/bin/env python3
"""Verify explicit targets against the snapshot a hook will publish."""
import argparse
import ast
import csv
import io
import json
from pathlib import Path, PurePosixPath
import subprocess
import sys


ROOT = Path(__file__).resolve().parents[1]
CONFIG = "inputs/baselines/bfme1/workshop-vanilla-1.03/manifest.json"
LEDGER = "targets/worldbuilder/reverse/functions.csv"
OWNED = ("worldbuilder/", "targets/worldbuilder/")
CHECKERS = frozenset("tools/" + name + ".py" for name in (
    "target_hooks", "target_guard", "targets", "target_verify", "worldbuilder", "worldbuilder_inventory",
    "build", "coffar", "gen_case_shims", "portable_lock"))
REQUIRED = {"name", "target_rva", "target_size", "status", "source", "profile", "evidence", "model"}
HEADERS = {".h", ".hpp", ".hh", ".hxx", ".inl", ".inc"}
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".asm", ".s"}
SOURCE_ROOTS = ("worldbuilder/",)
DONOR_ROOT = "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/WorldBuilder/"


class HookError(ValueError):
    pass


def _git(root, *args):
    return subprocess.run(["git", *args], cwd=root, check=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE).stdout


def _paths(root, snapshot):
    args = ("ls-files", "-z") if snapshot == ":" else (
        "ls-tree", "-r", "--name-only", "-z", snapshot)
    return set(_git(root, *args).decode("utf-8").rstrip("\0").split("\0")) - {""}


def _blob(root, snapshot, path):
    return _git(root, "show", f"{snapshot}:{path}" if snapshot != ":" else ":" + path)


def _sources(root, snapshot, paths):
    if LEDGER not in paths:
        return set()
    reader = csv.DictReader(io.StringIO(_blob(root, snapshot, LEDGER).decode("utf-8-sig")))
    if not reader.fieldnames or not REQUIRED <= set(reader.fieldnames) or len(set(reader.fieldnames)) != len(reader.fieldnames):
        raise HookError(f"{LEDGER}: invalid target ledger schema")
    result = set()
    for line, row in enumerate(reader, 2):
        if None in row or not all(row.get(key) for key in REQUIRED) or row["status"] != "matched":
            raise HookError(f"{LEDGER}:{line}: malformed matched row")
        source = row["source"]
        path = PurePosixPath(source)
        if ("\\" in source or ":" in source or ".." in path.parts or path.is_absolute()
                or not source.startswith(("game/", "worldbuilder/"))
                or path.suffix != ".cpp"):
            raise HookError(f"{LEDGER}:{line}: invalid source path {source!r}")
        if source not in paths:
            raise HookError(f"{LEDGER}:{line}: source is absent from snapshot: {source}")
        result.add(source)
    return result


def _game_sources(root, snapshot, candidates):
    if not candidates:
        return set()
    rows = csv.DictReader(io.StringIO(_blob(root, snapshot, "targets/game/reverse/functions.csv").decode("utf-8-sig")))
    if not rows.fieldnames or not {"source", "status"} <= set(rows.fieldnames):
        raise HookError("targets/game/reverse/functions.csv: invalid source membership schema")
    return {row["source"] for row in rows
            if row.get("status") == "matched" and row.get("source") in candidates}


def _checker_paths(root, snapshot, paths):
    pending = list(CHECKERS & paths)
    found = set()
    while pending:
        path = pending.pop()
        if path in found:
            continue
        found.add(path)
        tree = ast.parse(_blob(root, snapshot, path), filename=path)
        for node in ast.walk(tree):
            modules = ([alias.name for alias in node.names] if isinstance(node, ast.Import)
                       else [node.module] if isinstance(node, ast.ImportFrom) and node.module else [])
            pending.extend("tools/" + module + ".py" for module in modules
                           if "tools/" + module + ".py" in paths)
    return found


def _donor_paths(root, snapshot, paths):
    result = set()
    for name in ("candidates.json", "provenance.json"):
        path = "targets/worldbuilder/reverse/" + name
        if path not in paths:
            continue
        data = json.loads(_blob(root, snapshot, path))
        donors = list(data.get("donor", {}).get("files", []))
        for candidate in data.get("candidates", []):
            donors.extend(candidate.get("donor_files", []))
        for donor in donors:
            source = donor["path"]
            if (not isinstance(source, str) or "\\" in source or ":" in source
                    or ".." in PurePosixPath(source).parts
                    or not source.startswith(("inputs/reference/", "game/")) or source not in paths):
                raise HookError(f"{path}: donor is absent from snapshot or invalid: {source!r}")
            result.add(source)
    return result


def _exclusive_source(path):
    return path.startswith(SOURCE_ROOTS) and PurePosixPath(path).suffix.lower() in SOURCE_SUFFIXES


def _compiler_input(path, checkers=CHECKERS):
    return (path in checkers or path.startswith(("inputs/reference/shims/", "inputs/toolchains/", DONOR_ROOT))
            or (PurePosixPath(path).suffix.lower() in HEADERS
                and path.startswith(("game/", "inputs/reference/"))))


def _clean(root, snapshot, paths):
    args = ("diff", "--name-only", "-z") if snapshot == ":" else (
        "diff", "--name-only", "-z", snapshot)
    dirty = set(_git(root, *args).decode("utf-8").rstrip("\0").split("\0")) & paths
    if dirty:
        raise HookError("WorldBuilder verification inputs differ from "
                        + ("the staged index" if snapshot == ":" else snapshot)
                        + ": " + ", ".join(sorted(dirty))
                        + "; stage/commit or revert those edits before verification")


def validated_worldbuilder_sources(root=ROOT):
    """Game source scans may exclude only claims accepted by the target validator."""
    root = Path(root)
    config, ledger = root / CONFIG, root / LEDGER
    if not config.exists() and not ledger.exists():
        return set()
    from targets import load_target
    from target_verify import read_rows, validate_rows
    target = load_target("worldbuilder", root=root)
    rows = read_rows(target)
    validate_rows(target, rows)
    return {row["source"] for row in rows}


def run(root, snapshot, base=None, exclusive_output=None):
    root = Path(root)
    paths = _paths(root, snapshot)
    old_paths = _paths(root, base) if base else set()
    if CONFIG not in paths and LEDGER not in paths:
        if any(path.startswith(OWNED) for path in paths | old_paths):
            raise HookError("WorldBuilder files require a target configuration and ledger")
        if exclusive_output:
            Path(exclusive_output).write_text("")
        return False
    if CONFIG not in paths or LEDGER not in paths:
        raise HookError("WorldBuilder requires both its target configuration and ledger")
    sources = _sources(root, snapshot, paths)
    old_sources = _sources(root, base, old_paths) if base else set()
    if snapshot == ":":
        changed = set(_git(root, "diff", "--cached", "--name-only", "-z").decode("utf-8").rstrip("\0").split("\0"))
    elif base:
        changed = set(_git(root, "diff", "--name-only", "-z", base, snapshot).decode("utf-8").rstrip("\0").split("\0"))
    else:
        changed = paths
    checkers = _checker_paths(root, snapshot, paths)
    donors = _donor_paths(root, snapshot, paths)
    old_donors = _donor_paths(root, base, old_paths) if base else set()
    if base:
        checkers |= _checker_paths(root, base, old_paths)
    affected = any(path.startswith(OWNED) or path in sources | old_sources | donors | old_donors
                   or _compiler_input(path, checkers) for path in changed)
    if affected:
        if snapshot != ":" and _git(root, "rev-parse", snapshot).strip() != _git(root, "rev-parse", "HEAD").strip():
            raise HookError("WorldBuilder outgoing revision must be checked out at HEAD before verification")
        config = json.loads(_blob(root, snapshot, CONFIG))
        image = next((entry["path"] for entry in config["files"]
                      if entry.get("path") == "files/worldbuilder.exe"), None)
        if image is None:
            raise HookError("baseline manifest lacks files/worldbuilder.exe")
        dependencies = {path for path in paths if path.startswith(OWNED) or _compiler_input(path, checkers)}
        dependencies |= sources | donors | {CONFIG, LEDGER, "inputs/baselines/bfme1/workshop-vanilla-1.03/" + image}
        unclaimed = {path for path in paths if _exclusive_source(path)} - sources
        if unclaimed:
            raise HookError("Unclaimed WorldBuilder sources in snapshot: " + ", ".join(sorted(unclaimed)))
        missing = CHECKERS - paths
        if missing:
            raise HookError("WorldBuilder verification tools absent from snapshot: " + ", ".join(sorted(missing)))
        _clean(root, snapshot, dependencies)
        untracked = set(_git(root, "ls-files", "--others", "--exclude-standard", "-z").decode("utf-8").rstrip("\0").split("\0"))
        untracked_inputs = {path for path in untracked if _compiler_input(path, checkers)
                            or (path.startswith(OWNED) and not _exclusive_source(path))}
        if untracked_inputs:
            raise HookError("Untracked WorldBuilder verification inputs: " + ", ".join(sorted(untracked_inputs)))
        for command in ("check", "verify"):
            subprocess.run([sys.executable, "tools/worldbuilder.py", command], cwd=root, check=True)
    if exclusive_output:
        exclusive = sources - _game_sources(root, snapshot, sources)
        Path(exclusive_output).write_text("".join(path + "\n" for path in sorted(exclusive)))
    return affected


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("BASE", "REV"))
    mode.add_argument("--ref")
    parser.add_argument("--exclusive-output")
    args = parser.parse_args()
    snapshot, base = (":", "HEAD") if args.staged else ((args.range[1], args.range[0]) if args.range else (args.ref, None))
    try:
        run(ROOT, snapshot, base, args.exclusive_output)
    except (HookError, ValueError, KeyError, OSError, SyntaxError, subprocess.CalledProcessError) as error:
        print(f"TARGET GATE FAILED: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
