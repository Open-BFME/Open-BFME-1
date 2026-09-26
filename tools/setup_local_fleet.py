#!/usr/bin/env python3
"""Create isolated local Open-BFME writer clones."""
import argparse
import json
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_FLEET = Path.home() / "Projects" / "open-bfme-local-fleet"
DEFAULT_ORIGIN = "https://github.com/Open-BFME/Open-BFME-1.git"
GH_EXE = Path("/mnt/c/Program Files/GitHub CLI/gh.exe")
GENERATED_INPUTS = (
    "targets/game/reverse/exports.csv",
    "targets/game/reverse/ghidra_functions.csv",
    "targets/game/reverse/string_xrefs.tsv",
)


def git(repo, *args, capture=False):
    proc = subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True, text=True, capture_output=capture,
    )
    return proc.stdout.strip() if capture else ""


def git_dir(repo):
    return Path(git(repo, "rev-parse", "--path-format=absolute", "--git-dir",
                    capture=True))


def configure_repo(repo, origin):
    git(repo, "remote", "set-url", "origin", origin)
    git(repo, "config", "--local", "pull.rebase", "true")
    git(repo, "config", "--local", "rebase.autoStash", "true")
    git(repo, "config", "--local", "core.hooksPath", ".githooks")
    git(repo, "config", "--local",
        f"lfs.{origin}/info/lfs.locksverify", "false")
    if GH_EXE.exists():
        git(repo, "config", "--local", "credential.helper",
            f'!"{GH_EXE}" auth git-credential')
    # Older setup versions installed deterministic queue sharding here. Remove
    # stale private configuration so every clone uses the randomized queue.
    (git_dir(repo) / "openbfme-worker.json").unlink(missing_ok=True)


def copy_generated_inputs(source, target):
    copied = []
    for rel in GENERATED_INPUTS:
        src, dst = source / rel, target / rel
        if src.exists() and not dst.exists():
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
            copied.append(rel)
    return copied


def ensure_clone(source, target, branch):
    if target.exists():
        git(target, "rev-parse", "--is-inside-work-tree", capture=True)
        return False
    target.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([
        "git", "clone", "--shared", "--single-branch", "--branch", branch,
        str(source), str(target),
    ], check=True)
    return True


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=ROOT)
    parser.add_argument("--root", type=Path, default=DEFAULT_FLEET)
    parser.add_argument("--workers", type=int, default=2,
                        help="additional writer clones (default 2; primary makes 3)")
    parser.add_argument("--origin", default=DEFAULT_ORIGIN)
    parser.add_argument("--branch")
    args = parser.parse_args()

    source = args.source.resolve()
    fleet_root = args.root.resolve()
    if args.workers < 0:
        parser.error("--workers must be non-negative")
    branch = args.branch or git(source, "branch", "--show-current", capture=True)
    if not branch:
        parser.error("source is detached; pass --branch")

    entries = [{"role": "primary", "path": str(source)}]
    configure_repo(source, args.origin)

    for index in range(args.workers):
        number = index + 2
        target = fleet_root / f"writer-{number}"
        created = ensure_clone(source, target, branch)
        copied = copy_generated_inputs(source, target)
        configure_repo(target, args.origin)
        entries.append({
            "role": "writer",
            "path": str(target), "created": created, "copied": copied,
        })

    fleet_root.mkdir(parents=True, exist_ok=True)
    manifest = fleet_root / "fleet.json"
    manifest.write_text(json.dumps({
        "branch": branch,
        "origin": args.origin,
        "source": str(source),
        "workers": entries,
    }, indent=2) + "\n", encoding="utf-8")

    print(f"fleet: {manifest}")
    for entry in entries:
        print(f"  {entry['role']}: {entry['path']}")
    print("full build gate: run in one writer at a time")


if __name__ == "__main__":
    main()
