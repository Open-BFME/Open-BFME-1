#!/usr/bin/env python3
"""Seat side of the publisher rollout: the pre-push step that turns a push to
master into a publisher unit (tools/publisher.py), gated by a mode file.

MODE. `reverse/publisher_mode` (Open-BFME-1: `targets/game/reverse/publisher_mode`)
holds `off`, `shadow` or `enforce`. It is read from the REMOTE tip being
pushed onto, never from the outgoing commits, so a push cannot switch its own
mode; the mode changes when a commit changing the file lands.

  off      nothing happens.
  shadow   the push goes ahead untouched. A detached background process waits
           until the push has landed (the remote-tracking ref contains the
           pushed tip), then submits the same range to
           refs/submit/<operator>/<unit> on the same remote. Nothing here can
           fail or slow the push: the hook returns after spawning it (tens of
           ms) and the background process only logs, to
           <git dir>/publisher-hook.log.
  enforce  the range is submitted synchronously, then the push is refused
           (exit 3; the pre-push line turns that into a refusal). The
           publisher host fast-forwards master once the unit's gate is green.

OPERATOR. v1 is UNAUTHENTICATED: the operator is the git author name,
normalized, and the envelope is signed with a key anyone can derive from that
name (`unauth_key`), marked auth=none-v1. The publisher service registers such
operators on first sight; an operator an admin has issued a real key to
(`publisher.py operator`) cannot be impersonated this way, because the derived
key no longer verifies for that name.

  python3 tools/publisher_hook.py pre-push REMOTE < pre-push stdin
  python3 tools/publisher_hook.py status UNIT [--remote origin]
  python3 tools/publisher_hook.py operator
"""
import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile
import time
from pathlib import Path

ZERO = "0" * 40
BRANCH = "refs/heads/master"
MODE_FILES = ("reverse/publisher_mode", "targets/game/reverse/publisher_mode")
MODES = ("off", "shadow", "enforce")
REFUSE = 3                      # exit code the pre-push line turns into a refusal
AUTH = "none-v1"
RESULTS_REF = "refs/publisher/results"


def git(*args, check=True, timeout=60):
    got = subprocess.run(["git", *args], capture_output=True, timeout=timeout)
    if check and got.returncode:
        raise RuntimeError(f"git {' '.join(args)}: {got.stderr.decode(errors='replace').strip()}")
    return got.stdout.decode(errors="replace").strip()


def normalize(name):
    name = re.sub(r"[^a-z0-9]+", "-", (name or "").lower()).strip("-")[:40].strip("-")
    return name or "unknown"


def operator_id():
    ident = git("var", "GIT_AUTHOR_IDENT", check=False)
    return normalize(ident.split(" <")[0] if ident else "")


def unauth_key(operator):
    """The v1 key for `operator`: public by construction (see module doc)."""
    return hashlib.sha256(b"open-bfme-publisher/unauthenticated-v1/" + operator.encode()).hexdigest()


def read_mode(remote_sha):
    """Mode as of the remote tip; `off` when no mode file is there."""
    if not remote_sha or remote_sha == ZERO:
        return "off"
    for path in MODE_FILES:
        got = subprocess.run(["git", "show", f"{remote_sha}:{path}"], capture_output=True)
        if got.returncode == 0:
            text = got.stdout.decode(errors="replace").strip()
            return text if text in MODES else "off"
    return "off"


def submit(remote, operator, base, tip, after=()):
    """Push the range as a unit; returns its id (publisher.submit does the work).
    Its scope is exactly the paths the range touches (--scope-from-diff)."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import publisher
    with tempfile.NamedTemporaryFile("w", suffix=".key", delete=False) as handle:
        handle.write(unauth_key(operator) + "\n")
    try:
        return publisher.submit(Path.cwd(), operator, handle.name, f"{base}..{tip}", remote=remote,
                                after=after, scope="diff", extra=dict(auth=AUTH, base=base, tip=tip))
    finally:
        os.unlink(handle.name)


def patch_ids(base, tip):
    """[(commit, stable patch-id)] of base..tip, oldest first."""
    text = subprocess.run(["git", "log", "--reverse", "--no-merges", "-p", "--format=commit %H",
                           f"{base}..{tip}"], capture_output=True).stdout
    got = subprocess.run(["git", "patch-id", "--stable"], input=text, capture_output=True)
    ids = {c: p for p, c in (l.split() for l in got.stdout.decode().splitlines() if l.strip())}
    return [(c, ids.get(c)) for c in git("rev-list", "--reverse", f"{base}..{tip}").split()]


def submitted_path():
    return Path(git("rev-parse", "--absolute-git-dir")) / "publisher-submitted.jsonl"


def results(remote):
    """{unit: record} from the publisher's results ref; {} when unreachable."""
    got = subprocess.run(["git", "fetch", "-q", "--no-tags", remote,
                          f"+{RESULTS_REF}:refs/publisher-results"], capture_output=True, timeout=30)
    if got.returncode:
        return {}
    text = git("show", "refs/publisher-results:results.jsonl", check=False)
    return {r["unit"]: r for r in map(json.loads, text.splitlines()) if r.get("unit")}


def plan(remote, base, tip):
    """(base, after units, refusal) for an enforce-mode submission. A seat keeps
    working on top of commits it already queued, so its next push repeats
    them: the leading commits whose patch-ids were queued in the last day and
    not rejected are left out, and the new unit is ordered after their units."""
    try:
        lines = submitted_path().read_text(encoding="utf-8").splitlines()
    except FileNotFoundError:
        lines = []
    queued = {}
    for record in map(json.loads, lines):
        if time.time() - record.get("t", 0) < 86400:
            for pid in record.get("patch_ids") or ():
                queued[pid] = record["unit"]
    commits = patch_ids(base, tip)
    if not any(pid in queued for _, pid in commits):
        return base, (), None
    outcome = results(remote)
    for pid, unit in list(queued.items()):
        state = (outcome.get(unit) or {}).get("outcome")
        if state == "rejected":
            del queued[pid]                 # resubmitting a rejected unit is allowed
        elif state == "landed" and any(p == pid for _, p in commits):
            return None, (), f"unit {unit} already landed; `git pull --rebase` and push again"
    after, start, at = [], base, 0
    for commit, pid in commits:
        if pid not in queued:
            break
        if queued[pid] not in after:
            after.append(queued[pid])
        start, at = commit, at + 1
    if any(pid in queued for _, pid in commits[at:]):
        return None, (), ("these commits interleave with ones already queued; wait for them to "
                          "land, `git pull --rebase`, push again")
    if start == tip:
        return None, (), f"everything in this push is already queued ({', '.join(after)})"
    return start, after, None


def remember(unit, base, tip):
    record = dict(unit=unit, base=base, tip=tip, t=time.time(),
                  patch_ids=[p for _, p in patch_ids(base, tip) if p])
    with submitted_path().open("a", encoding="utf-8") as handle:
        handle.write(json.dumps(record) + "\n")


def log_path():
    return Path(git("rev-parse", "--absolute-git-dir")) / "publisher-hook.log"


def log(message):
    try:
        with log_path().open("a", encoding="utf-8") as handle:
            handle.write(f"{time.strftime('%Y-%m-%dT%H:%M:%S')} {message}\n")
    except OSError:
        pass


def landed(remote, tip, timeout=180.0):
    """True once the push of `tip` is visible on the remote. The remote-tracking
    ref is updated by git right after a successful push; a remote without one
    is asked directly."""
    tracking = f"refs/remotes/{remote}/master"
    has_tracking = bool(git("config", "--get-all", f"remote.{remote}.fetch", check=False))
    deadline = time.time() + timeout
    while time.time() < deadline:
        if has_tracking:
            at = git("rev-parse", "-q", "--verify", tracking, check=False)
            if at and subprocess.run(["git", "merge-base", "--is-ancestor", tip, at],
                                     capture_output=True).returncode == 0:
                return True
            time.sleep(0.5)
        else:
            time.sleep(5)
            listed = git("ls-remote", remote, BRANCH, check=False).split()
            if listed and listed[0] == tip:
                return True
    return False


def shadow_worker(remote, operator, base, tip):
    """Background half of shadow mode. Never raises."""
    try:
        if not landed(remote, tip):
            log(f"shadow: {base[:12]}..{tip[:12]} did not land on {remote}; not submitted")
            return 0
        started = time.time()
        unit = submit(remote, operator, base, tip)
        log(f"shadow: submitted {unit} operator={operator} {base[:12]}..{tip[:12]} "
            f"({time.time() - started:.1f}s)")
    except Exception as error:  # noqa: BLE001 -- shadow mode only logs
        log(f"shadow: submission of {base[:12]}..{tip[:12]} failed: {error}")
    return 0


def spawn_shadow(remote, operator, base, tip):
    argv = [sys.executable, str(Path(__file__).resolve()), "_shadow", remote, operator, base, tip]
    kw = dict(stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
              close_fds=True)
    if os.name == "nt":
        kw["creationflags"] = subprocess.CREATE_NO_WINDOW | subprocess.CREATE_NEW_PROCESS_GROUP
    else:
        kw["start_new_session"] = True
    subprocess.Popen(argv, **kw)


def pre_push(remote, lines):
    if os.environ.get("CHECKER_DIGEST") or os.environ.get("LANDING_TIP"):
        return 0                # inside a publisher builder: this IS the gate
    status = 0
    for line in lines:
        parts = line.split()
        if len(parts) != 4 or parts[2] != BRANCH or parts[1] == ZERO:
            continue
        _, tip, _, base = parts
        try:
            mode = read_mode(base)
        except Exception as error:  # noqa: BLE001
            log(f"mode unreadable ({error}); treated as off")
            continue
        if mode == "off":
            continue
        operator = operator_id()
        known = base != ZERO and subprocess.run(
            ["git", "cat-file", "-e", f"{base}^{{commit}}"], capture_output=True).returncode == 0
        if mode == "shadow":
            if not known:
                log(f"shadow: remote master tip {base[:12]} not local; {tip[:12]} not submitted")
                continue
            try:
                spawn_shadow(remote, operator, base, tip)
            except Exception as error:  # noqa: BLE001 -- never fail the push in shadow
                log(f"shadow: could not start the submitter: {error}")
            continue
        # enforce
        status = REFUSE
        if not known:
            print("pre-push: master is publisher-only and the remote master tip is not local; "
                  "fetch and rebase, then push again", file=sys.stderr)
            continue
        try:
            start, after, refusal = plan(remote, base, tip)
            if refusal:
                print(f"pre-push: master is publisher-only; {refusal}", file=sys.stderr)
                continue
            unit = submit(remote, operator, start, tip, after)
            remember(unit, start, tip)
        except Exception as error:  # noqa: BLE001
            print(f"pre-push: master is publisher-only; submitting {base[:12]}..{tip[:12]} "
                  f"FAILED ({error}). Nothing was queued; push again to retry.", file=sys.stderr)
            continue
        log(f"enforce: submitted {unit} operator={operator} {start[:12]}..{tip[:12]} after={after}")
        print(f"PUBLISHER-QUEUED {unit} {start}..{tip} operator={operator}"
              + (f" after={','.join(after)}" if after else ""), file=sys.stderr)
        print("pre-push: master is publisher-only. Your commits were QUEUED, not pushed; the "
              "publisher lands them after its gate.\n"
              f"  check: python3 tools/publisher_hook.py status {unit}\n"
              "  landed = `git pull --rebase` shows them on master. Do not push the same "
              "commits again.", file=sys.stderr)
    return status


def unit_status(unit, remote):
    """queued (still on refs/submit), landed/rejected (publisher results), or pending."""
    if git("ls-remote", remote, f"refs/submit/*/{unit}", check=False):
        return dict(unit=unit, state="queued",
                    note="not yet ingested: the publisher host is offline or behind")
    record = results(remote).get(unit)
    if record:
        return dict(record, state=record.get("outcome"))
    return dict(unit=unit, state="pending", note="ingested; not finished yet")


def main(argv):
    if len(argv) >= 2 and argv[0] == "pre-push":
        try:
            return pre_push(argv[1], sys.stdin.read().splitlines())
        except Exception as error:  # noqa: BLE001 -- shadow must never fail a push
            log(f"pre-push step crashed: {error}")
            return 0            # fail open: in enforce the server ruleset still refuses
    if len(argv) == 5 and argv[0] == "_shadow":
        return shadow_worker(*argv[1:])
    if argv and argv[0] == "status" and len(argv) >= 2:
        remote = argv[argv.index("--remote") + 1] if "--remote" in argv else "origin"
        print(json.dumps(unit_status(argv[1], remote), indent=1))
        return 0
    if argv == ["operator"]:
        print(operator_id())
        return 0
    print(__doc__, file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
