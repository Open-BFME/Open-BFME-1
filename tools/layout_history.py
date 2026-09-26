"""Resolve ledgers across the repository's source and evidence relocation."""

import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OLD_LEDGER = "reverse/functions.csv"
NEW_LEDGER = "targets/game/reverse/functions.csv"
OLD_PINS = "reverse/symbols.csv"
NEW_PINS = "targets/game/reverse/symbols.csv"


def canonical_source(path):
    for old, new in (
        ("Code/Tools/WorldBuilder/src/", "worldbuilder/src/"),
        ("Code/", "game/"),
        ("reference/", "inputs/reference/"),
        ("vendor/", "inputs/vendor/"),
        ("build/toolchains/", "inputs/toolchains/"),
    ):
        if path.startswith(old):
            return new + path[len(old):]
    return path


def path_at(ref, current_path, old_path, *, allow_missing=False, root=ROOT):
    """Return the sole path present in a Git snapshot, rejecting ambiguity."""
    command = (["git", "-C", str(root), "ls-files", "-z", "--"]
               if ref == "" else
               ["git", "-C", str(root), "ls-tree", "-r", "--name-only", "-z", ref, "--"])
    found = subprocess.check_output(command + [current_path, old_path])
    present = [path for path in found.decode().split("\0") if path]
    if not present and allow_missing:
        return None
    if len(present) != 1:
        raise ValueError(f"{ref or 'index'}: expected one ledger path, found {present}")
    return present[0]


def read_at(ref, current_path, old_path, *, root=ROOT):
    path = path_at(ref, current_path, old_path, root=root)
    object_name = f":{path}" if ref == "" else f"{ref}:{path}"
    return subprocess.check_output(["git", "-C", str(root), "show", object_name])
