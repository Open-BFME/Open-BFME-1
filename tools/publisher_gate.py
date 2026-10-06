#!/usr/bin/env python3
"""The publisher's gate command (config `gate`), run by a builder inside its
remote-less candidate worktree with the pinned checker overlaid: prepares
what the builder's scrubbed environment lacks, then runs the repository's own
.githooks/pre-push over LANDING_BASE..LANDING_TIP.

  --link PATH       a gitlink (BFME2: reference/open-bfme-1, the MSVC 7.1
                    toolchain) is served from DIR/<gitlink sha>, a clone the
                    publisher service provisions; linked (junction on Windows)
                    into the worktree. A unit whose gitlink sha is not
                    provisioned fails with PUBLISHER-BLAME on that path.
  --host-lock FILE  build.py's host-wide full-build lock is ~/.cache/
                    open-bfme-build.lock; the builder's HOME is its scratch
                    dir, so its ~/.cache lock is hard-linked to FILE (same
                    volume) and full builds serialize with every other clone
                    on the host instead of beside them.

  python3 tools/publisher_gate.py [--link PATH --toolchains DIR] [--host-lock FILE]
"""
import argparse
import os
import subprocess
import sys
from pathlib import Path


def git(*args):
    got = subprocess.run(["git", *args], capture_output=True, text=True)
    return got.stdout.strip() if got.returncode == 0 else None


def share_lock(host):
    host = Path(host)
    host.parent.mkdir(parents=True, exist_ok=True)
    host.open("a").close()
    mine = Path.home() / ".cache" / "open-bfme-build.lock"
    try:
        if mine.exists() and os.path.samefile(mine, host):
            return
        mine.parent.mkdir(parents=True, exist_ok=True)
        mine.unlink(missing_ok=True)
        os.link(host, mine)
    except OSError as error:
        print(f"publisher_gate: host build lock not shared ({error}); full builds here "
              "do not serialize with other clones", file=sys.stderr)


def remove_link(path):
    if path.is_dir() and not path.is_symlink():
        os.rmdir(path)              # a junction or an empty directory; never recursive
    else:
        path.unlink()


def link_gitlink(rel, store):
    entry = git("ls-tree", "HEAD", "--", rel)     # "160000 commit <sha>	<path>"
    if not entry or not entry.startswith("160000 "):
        return True
    sha = entry.split()[2]
    source = Path(store) / sha
    if not (source / ".git").exists():
        print(f"PUBLISHER-BLAME: {rel}\npublisher_gate: {rel} at {sha} is not provisioned in "
              f"{store} (the publisher service provisions the gitlink of every head and unit)")
        return False
    target = Path(rel)
    if target.exists() or target.is_symlink():
        try:
            if os.path.samefile(target, source):
                return True
        except OSError:
            pass
        try:
            remove_link(target)     # fails on a populated real directory, by design
        except OSError as error:
            print(f"publisher_gate: cannot replace {rel}: {error}")
            return False
    target.parent.mkdir(parents=True, exist_ok=True)
    if os.name == "nt":
        import _winapi
        _winapi.CreateJunction(str(source), str(target.resolve()))
    else:
        os.symlink(source, target, target_is_directory=True)
    return True


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--link", action="append", default=[])
    ap.add_argument("--toolchains")
    ap.add_argument("--host-lock")
    ap.add_argument("--hook", default=".githooks/pre-push")
    args = ap.parse_args(argv)
    base, tip = os.environ["LANDING_BASE"], os.environ["LANDING_TIP"]
    if args.host_lock:
        share_lock(args.host_lock)
    for rel in args.link:
        if not link_gitlink(rel, args.toolchains):
            return 1
    sys.stdout.flush()
    # "." as the remote: the builder has none, and the hook's remote probes
    # (publish window, destination fetch) must stay inside this clone.
    line = f"refs/heads/master {tip} refs/heads/master {base}\n"
    return subprocess.run(["bash", args.hook, ".", "."], input=line.encode()).returncode


if __name__ == "__main__":
    sys.exit(main())
