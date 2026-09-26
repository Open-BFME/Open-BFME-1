"""Check the one-time repository relocation against both Git snapshots."""

import argparse
import csv
import io
import itertools
import subprocess

from layout_history import canonical_source


MOVES = (
    ("Code/Tools/WorldBuilder/src/", "worldbuilder/src/"),
    ("Code/", "game/"),
    ("reverse/worldbuilder/", "targets/worldbuilder/reverse/"),
    ("reverse/", "targets/game/reverse/"),
    ("worldbuilder/dependencies/", "targets/worldbuilder/dependencies/"),
    ("worldbuilder/references.json", "targets/worldbuilder/references.json"),
    ("baselines/", "inputs/baselines/"),
    ("reference/", "inputs/reference/"),
    ("vendor/", "inputs/vendor/"),
    ("build/toolchains/", "inputs/toolchains/"),
    ("plans/", "docs/plans/"),
    ("ghdec", "docs/ghdec"),
)
REMOVED = {"worldbuilder/target.json"}
ADDED = {"tools/layout_history.py", "tools/layout_migration.py"}


def git(*args):
    return subprocess.check_output(("git", *args))


def paths(ref):
    if ref == ":":
        return set(git("ls-files", "-z").decode().split("\0")) - {""}
    return set(git("ls-tree", "-r", "--name-only", "-z", ref).decode().split("\0")) - {""}


def moved(path):
    for old, new in MOVES:
        if path == old or path.startswith(old):
            return new + path[len(old):]
    return path


def blob(ref, path):
    return git("show", f":{path}" if ref == ":" else f"{ref}:{path}")


def check_rows(old, new, old_path, new_path, *, game):
    before = csv.DictReader(io.StringIO(blob(old, old_path).decode("utf-8-sig")))
    after = csv.DictReader(io.StringIO(blob(new, new_path).decode("utf-8-sig")))
    if before.fieldnames != after.fieldnames:
        raise ValueError(f"{new_path}: ledger columns changed")
    count = 0
    for count, (left, right) in enumerate(itertools.zip_longest(before, after), 1):
        if left is None or right is None:
            raise ValueError(f"{new_path}: ledger row count changed at {count}")
        left["source"] = canonical_source(left["source"])
        if game:
            left.pop("notes")
            right.pop("notes")
        if left != right:
            raise ValueError(f"{new_path}: row {count} changed beyond source relocation")
    return count


def detect(old, new):
    before, after = paths(old), paths(new)
    return ("Code/GameEngine/Include/Common/INI/INI.h" in before
            and "game/GameEngine/Include/Common/INI/INI.h" in after
            and "Code/GameEngine/Include/Common/INI/INI.h" not in after
            and "reverse/functions.csv" in before
            and "targets/game/reverse/functions.csv" in after)


def check(old, new):
    before, after = paths(old), paths(new)
    if not detect(old, new):
        raise ValueError("not the Code/reverse to game/targets relocation")
    expected = {moved(path) for path in before - REMOVED} | ADDED
    if expected != after:
        missing, extra = sorted(expected - after), sorted(after - expected)
        raise ValueError(f"relocated path set differs: missing={missing[:8]}, extra={extra[:8]}")
    game_rows = check_rows(old, new, "reverse/functions.csv",
                           "targets/game/reverse/functions.csv", game=True)
    worldbuilder_rows = check_rows(old, new, "reverse/worldbuilder/functions.csv",
                                   "targets/worldbuilder/reverse/functions.csv", game=False)
    print(f"layout migration: {len(before)} paths, {game_rows} game rows, "
          f"{worldbuilder_rows} WorldBuilder rows preserved")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=("detect", "check"))
    parser.add_argument("old")
    parser.add_argument("new")
    args = parser.parse_args()
    try:
        if args.mode == "detect":
            if detect(args.old, args.new):
                print("layout-migration")
                return 0
            return 1
        check(args.old, args.new)
        return 0
    except (ValueError, subprocess.CalledProcessError) as error:
        print(f"layout migration: {error}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
