#!/usr/bin/env python3
"""A cooperative publish window on master: one ref, held by one publisher.

WHY. A header-wide change runs a ~17 minute push gate; master takes a push
every ~79 s (median, 2026-09-29), and a 17-minute gap with no push happened
1.8% of the time, so such a change never lands by racing. The landing
service (tools/landing_service.py) opens a window, lands the change while
master is quiet, and closes it.

HOW. The window is the ref `refs/landing/window` on origin, pointing at a
parentless commit whose message is JSON {owner, host, purpose, opened,
expires}. Opening creates it with an expected-absent lease (or takes over an
EXPIRED one by compare-and-swap), so two publishers cannot both hold it.
Every pre-push hook asks `check` before pushing to refs/heads/master, at the
start and again after its gates: a live window held by someone else refuses
the push. The holder's own pushes carry BFME_WINDOW_TOKEN=<window sha>.

COOPERATIVE. Only hooks that contain the check respect it: a checkout older
than this file, a --no-verify push, or a push through the GitHub API ignores
the window. The check fails OPEN when origin cannot be asked (the push itself
needs origin anyway). An abandoned window blocks master until it expires
(default 90 minutes); `close --force` ends one.

  python3 tools/publish_window.py status
  python3 tools/publish_window.py open [--minutes 90] [--purpose TEXT]   # prints the token
  python3 tools/publish_window.py close TOKEN | --force
  python3 tools/publish_window.py check        # exit 1 while someone else holds it
"""
import argparse
import json
import os
import socket
import subprocess
import sys
import time
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = "refs/landing/window"
SEEN = "refs/landing-seen/window"
TOKEN_ENV = "BFME_WINDOW_TOKEN"


class WindowHeld(RuntimeError):
    """Someone else holds a live window."""


def _git(*args, root=None, input_text=None, timeout=60):
    cwd = Path(root or ROOT)
    env = dict(os.environ, GIT_CEILING_DIRECTORIES=str(cwd.resolve().parent))
    try:
        return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True,
                              input=input_text, timeout=timeout, env=env)
    except subprocess.TimeoutExpired as error:
        return subprocess.CompletedProcess(error.cmd, 124, "", f"timed out after {timeout}s")


def read(remote="origin", root=None):
    """(token, info) of the window on `remote`, (None, None) when there is
    none. Raises RuntimeError when the remote cannot be asked."""
    listed = _git("ls-remote", remote, REF, root=root, timeout=60)
    if listed.returncode:
        raise RuntimeError(f"publish_window: cannot ask {remote}: {listed.stderr.strip()}")
    line = listed.stdout.strip()
    if not line:
        return None, None
    token = line.split()[0]
    if _git("cat-file", "-e", f"{token}^{{commit}}", root=root).returncode:
        got = _git("fetch", "-q", "--no-tags", remote, f"+{REF}:{SEEN}", root=root, timeout=60)
        if got.returncode:
            raise RuntimeError(f"publish_window: cannot fetch {REF}: {got.stderr.strip()}")
    body = _git("log", "-1", "--format=%B", token, root=root).stdout
    try:
        return token, json.loads(body)
    except ValueError:
        return token, {"owner": "?", "expires": 0}


def live(info, now=None):
    return bool(info) and info.get("expires", 0) > (now or time.time())


def open_window(minutes=90, purpose="", owner=None, remote="origin", root=None):
    """Hold the window; returns its token. Raises WindowHeld."""
    token, info = read(remote, root)
    if token and live(info):
        raise WindowHeld(f"publish window held by {info.get('owner')} "
                         f"({info.get('purpose', '')}) for {(info['expires'] - time.time()) / 60:.0f} more min")
    now = time.time()
    body = json.dumps({"owner": owner or f"{os.environ.get('USERNAME') or os.environ.get('USER') or '?'}"
                                        f"@{socket.gethostname()}",
                       "host": socket.gethostname(), "purpose": purpose, "nonce": uuid.uuid4().hex,
                       "opened": int(now), "expires": int(now + minutes * 60)}, sort_keys=True)
    tree = _git("mktree", input_text="", root=root).stdout.strip()
    made = _git("-c", "user.name=window", "-c", "user.email=window@localhost",
                "commit-tree", tree, "-m", body, root=root)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    new = made.stdout.strip()
    lease = f"--force-with-lease={REF}:{token or ''}"
    # the push hook skips refs/landing/* (a lock marker, like refs/claims/*)
    pushed = _git("push", "-q", lease, remote, f"+{new}:{REF}", root=root, timeout=120)
    if pushed.returncode:
        token, info = read(remote, root)
        raise WindowHeld(f"publish window taken by {info and info.get('owner')} first")
    return new


def close_window(token=None, force=False, remote="origin", root=None):
    """Release the window we hold (or any, with force). Returns True if closed."""
    current, _ = read(remote, root)
    if not current or (token and current != token and not force):
        return False
    pushed = _git("push", "-q", f"--force-with-lease={REF}:{current}", remote,
                  f":{REF}", root=root, timeout=120)
    return pushed.returncode == 0


def check(remote="origin", root=None):
    """(allowed, message) for a push to master right now."""
    try:
        token, info = read(remote, root)
    except RuntimeError as error:
        return True, f"{error}; not checking the publish window"
    if not token or not live(info):
        return True, ""
    if os.environ.get(TOKEN_ENV) == token:
        return True, "this push holds the publish window"
    left = (info.get("expires", 0) - time.time()) / 60
    return False, (f"master is in a publish window held by {info.get('owner')} "
                   f"({info.get('purpose', '')}), {left:.0f} min left; retry after it closes")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["status", "open", "close", "check"])
    ap.add_argument("token", nargs="?")
    ap.add_argument("--minutes", type=float, default=90)
    ap.add_argument("--purpose", default="")
    ap.add_argument("--remote", default="origin")
    ap.add_argument("--force", action="store_true")
    args = ap.parse_args(argv)
    if args.action == "check":
        allowed, message = check(args.remote)
        if message:
            print(f"publish_window: {message}", file=sys.stderr)
        return 0 if allowed else 1
    if args.action == "status":
        token, info = read(args.remote)
        print("no window" if not token else
              f"{token[:10]} {'LIVE' if live(info) else 'expired'} {json.dumps(info, sort_keys=True)}")
        return 0
    if args.action == "open":
        try:
            print(open_window(args.minutes, args.purpose, remote=args.remote))
        except WindowHeld as error:
            print(f"publish_window: {error}", file=sys.stderr)
            return 1
        return 0
    return 0 if close_window(args.token, args.force, args.remote) else 1


if __name__ == "__main__":
    sys.exit(main())
