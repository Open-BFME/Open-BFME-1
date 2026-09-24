#!/usr/bin/env python3
"""Run one worker with an immutable brief, transcript and actual exit status.

The caller supplies a bounded command (seat.sh uses timeout). Runs share an
atomic RVA claim table across lanes. A claim is a LEASE: it carries the
worker's pid and an expiry (FLEET_LEASE_SECONDS, default the 150-minute
session cap plus 30 minutes). A lease is reclaimed only when it has expired
AND its pid is gone -- never out from under a live worker. An operator can
still release a named run with --release RUN --reason TEXT after establishing
the worker stopped. Existing legacy workers do not participate; deploy at a
fleet restart, not by overwriting a running script.
"""
import argparse
from contextlib import closing
import csv
import datetime
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import signal
import sqlite3
import subprocess
import sys
import threading
import time
import uuid

ROOT = Path(__file__).resolve().parents[1]
TARGET = re.compile(r"^- (0x[0-9a-fA-F]+) (\d+)B", re.M)
DIFF = re.compile(r"^(diff --git |index [0-9a-f]+\.\.|\+\+\+ |--- |@@ |[-+])")
# dis_retail.py prints +OFFSET HEX-BYTES MNEMONIC.  These are evidence, not
# added patch lines: dropping them made successful disassemblies look empty.
DISASSEMBLY = re.compile(r"^\+[0-9a-fA-F]{4,}\s+(?:[0-9a-fA-F]{2}\s+)+[a-zA-Z]")


def keep_transcript_line(line):
    return bool(DISASSEMBLY.match(line)) or not DIFF.match(line)


LEASE_SECONDS = int(os.environ.get("FLEET_LEASE_SECONDS", "0") or 0) or (9000 + 1800)


class ClaimConflict(RuntimeError):
    """An advisory selection lost ownership before any worker launched."""


class StaleBrief(RuntimeError):
    """A brief target is no longer an open body at the stated size."""


def connect(root):
    (root / "build").mkdir(exist_ok=True)
    db = sqlite3.connect(root / "build/fleet_runs.sqlite", timeout=60)
    db.execute("CREATE TABLE IF NOT EXISTS claims (rva TEXT PRIMARY KEY, run TEXT, started REAL)")
    db.execute("CREATE TABLE IF NOT EXISTS releases (run TEXT, at REAL, reason TEXT)")
    have = {row[1] for row in db.execute("PRAGMA table_info(claims)")}
    if "pid" not in have:
        db.execute("ALTER TABLE claims ADD COLUMN pid INTEGER")
    if "expires" not in have:
        db.execute("ALTER TABLE claims ADD COLUMN expires REAL")
    return db


def pid_alive(pid):
    """True while the process exists. Unknown pid (None) counts as alive: a
    lease we cannot check is not a lease we may take."""
    if not pid:
        return True
    if sys.platform.startswith("win"):
        import ctypes
        kernel32 = ctypes.windll.kernel32
        handle = kernel32.OpenProcess(0x1000, False, int(pid))  # PROCESS_QUERY_LIMITED_INFORMATION
        if not handle:
            # Access denied and other query errors do not prove the process is
            # gone. ERROR_INVALID_PARAMETER is the absent-PID result.
            return kernel32.GetLastError() != 87
        try:
            code = ctypes.c_ulong()
            if not kernel32.GetExitCodeProcess(handle, ctypes.byref(code)):
                return True
            return code.value == 259  # STILL_ACTIVE
        finally:
            kernel32.CloseHandle(handle)
    try:
        os.kill(int(pid), 0)
        return True
    except ProcessLookupError:
        return False
    except PermissionError:
        return True


def run_finished(root, run):
    """True when the immutable run record says the worker is no longer running.
    Legacy claims (no pid, no expiry) can only be judged this way."""
    record = root / "build" / "fleet_runs" / str(run) / "record.json"
    try:
        status = json.loads(record.read_text(encoding="utf-8")).get("status")
    except (OSError, ValueError):
        return False  # no trustworthy record: unknown liveness, keep the claim
    return status in ("finished", "failed", "aborted")


def lease_dead(expires, pid, now=None, root=None, run=None):
    now = time.time() if now is None else now
    if not expires:
        # An interrupted record may still have a live child. Even an ended
        # legacy record cannot override a PID that is still alive.
        return (root is not None and run_finished(root, run)
                and (not pid or not pid_alive(pid)))
    return now > expires and not pid_alive(pid)


def strip_timeout(command):
    """Return (command, cap_seconds, kill_after). The seat scripts say
    `timeout -k N SECS prog ...`; fleet_run enforces that cap itself, because
    on Windows a bare `timeout` is TIMEOUT.EXE (a console pause) and Git's
    Cygwin coreutils copy rejects the brief argument ("Too many levels of
    nesting for @"). Both pilot seats died on it in under a second."""
    if not command or command[0] != "timeout":
        return command, None, None
    i, kill_after = 1, None
    if i < len(command) and command[i] == "-k":
        kill_after = parse_duration(command[i + 1]); i += 2
    cap = parse_duration(command[i]); i += 1
    return command[i:], cap, kill_after


def parse_duration(text):
    units = {"s": 1, "m": 60, "h": 3600, "d": 86400}
    text = str(text).strip()
    if text and text[-1] in units:
        return float(text[:-1]) * units[text[-1]]
    return float(text)


def kill_tree(child):
    """Kill the worker and everything it spawned (codex forks tool shells)."""
    if sys.platform.startswith("win"):
        try:
            subprocess.Popen(["taskkill", "/T", "/F", "/PID", str(child.pid)],
                             stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).wait(30)
        except OSError:
            pass
    else:
        try:
            os.killpg(child.pid, signal.SIGKILL)
        except OSError:
            pass
    try:
        child.kill()
    except (ProcessLookupError, OSError):
        pass


def surviving_group(child):
    """A direct child may exit while a tool process in its session still runs."""
    if sys.platform.startswith("win"):
        return False  # native Windows has no POSIX process-group query
    try:
        os.killpg(child.pid, 0)
        return True
    except ProcessLookupError:
        return False
    except OSError:
        return True


def claim(root, run, targets, pid=None, lease=None):
    lease = LEASE_SECONDS if lease is None else lease
    now = time.time()
    with closing(connect(root)) as db, db:
        db.execute("BEGIN IMMEDIATE")
        for rva, _ in targets:
            owner = db.execute("SELECT run, pid, expires FROM claims WHERE rva=?", (rva,)).fetchone()
            if owner:
                if not lease_dead(owner[2], owner[1], now, root, owner[0]):
                    raise ClaimConflict(f"{rva} is already owned by run {owner[0]}")
                db.execute("DELETE FROM claims WHERE rva=?", (rva,))
                db.execute("INSERT INTO releases VALUES (?,?,?)",
                           (owner[0], now, f"lease expired and pid {owner[1]} is gone; {rva} taken by {run}"))
            db.execute("INSERT INTO claims (rva, run, started, pid, expires) VALUES (?,?,?,?,?)",
                       (rva, run, now, pid, now + lease))


def set_pid(root, run, pid, expected=None):
    with closing(connect(root)) as db, db:
        db.execute("BEGIN IMMEDIATE")
        count = db.execute("SELECT count(*) FROM claims WHERE run=?", (run,)).fetchone()[0]
        if not count or (expected is not None and count != expected):
            raise ClaimConflict(f"run {run} lost its claim before PID recording")
        db.execute("UPDATE claims SET pid=? WHERE run=?", (pid, run))


def validate_targets(root, targets):
    """Use eligibility's one open-body rule just before spawning a worker."""
    import eligibility
    rows = eligibility.load_rows(root / "reverse/functions.csv")
    latest = eligibility.latest_verdicts(root / "reverse/re_attempts.log")
    live = {row["target_rva"].lower(): int(row.get("target_size") or 0)
            for row in eligibility.open_dumps(
                rows, latest, include_carved=True,
                carved_path=root / "reverse/carved.csv")}
    for rva, size in targets:
        if live.get(rva) != size:
            raise StaleBrief(f"{rva}/{size}B is no longer an open body at that size")


def active_rvas(root):
    """Leases that are live: unexpired, or expired with the worker still running."""
    now = time.time()
    with closing(connect(root)) as db, db:
        rows = db.execute("SELECT rva, run, pid, expires FROM claims").fetchall()
    return {rva for rva, run, pid, expires in rows if not lease_dead(expires, pid, now, root, run)}


def run_tag(text):
    """Attach provenance without letting an environment value corrupt a ledger."""
    run = os.environ.get("BFME_RUN_ID", "")
    if run and re.fullmatch(r"[A-Za-z0-9_-]{1,80}", run):
        text = re.sub(r"(?:^|\s)run=\S+", "", text).strip()
        return (text + " run=" + run).strip()
    return text


ABORT_SECONDS = int(os.environ.get("FLEET_ABORT_SECONDS", "300"))


def mark_touched(rva):
    """probe, re_log and add_match call this: the run really worked on `rva`.
    Only touched targets cool down afterwards (eligibility.recent_run_rvas);
    the rest of the brief returns to the queue. Never raises: bookkeeping
    must not break the tool a worker is running."""
    directory = os.environ.get("BFME_RUN_DIR", "")   # set by execute() for its worker
    if not directory:
        return
    try:
        number = rva if isinstance(rva, int) else int(str(rva), 16)
        directory = Path(directory)
        if directory.is_dir() and (directory / "record.json").exists():
            with (directory / "touched.txt").open("a", encoding="ascii") as handle:
                handle.write(f"0x{number:08x}\n")
    except (OSError, ValueError):
        pass


def touched_rvas(directory):
    try:
        return sorted(set((Path(directory) / "touched.txt").read_text(encoding="ascii").split()))
    except OSError:
        return []


def aborted(record):
    """A run that died at once and worked on nothing (quota, network, a bad
    command line). 2,680 of these on 2026-09-18 cooled 1,796 bodies for 48 h."""
    return (record.get("status") == "aborted"
            or (record.get("exit_code") not in (0, None)
                and (record.get("seconds") or ABORT_SECONDS) < ABORT_SECONDS
                and not record.get("touched")))


def stash_fingerprint(rva):
    import re_log
    stash = re_log.stash_for(rva)
    if not stash:
        return "none"
    # A higher self-reported score or a new date is not a new source hypothesis.
    body = b"\n".join(stash[0].read_bytes().splitlines()[2:])
    return hashlib.sha256(body).hexdigest()


def retry_allowed(root, rva, before):
    import re_log
    current = stash_fingerprint(rva)
    record = re_log.latest_records(root / "reverse/re_attempts.log").get(rva)
    stash = re_log.stash_for(rva)
    if current in ("none", before) or not record or record[3] != "partial" or stash[1] < .5:
        return False
    with (root / "reverse/functions.csv").open(newline="", encoding="utf-8") as ledger:
        return any(int(row["target_rva"], 16) == rva and row["source"].endswith(".asm")
                   for row in csv.DictReader(ledger) if row.get("target_rva"))


def release(root, run, reason):
    with closing(connect(root)) as db, db:
        db.execute("DELETE FROM claims WHERE run=?", (run,))
        db.execute("INSERT INTO releases VALUES (?,?,?)", (run, time.time(), reason))


def save(path, data):
    tmp = path.with_suffix(".tmp")
    tmp.write_text(json.dumps(data, indent=2), encoding="utf-8")
    os.replace(tmp, path)


def execute(root, brief, legacy_log, engine, seat, command):
    body = Path(brief).read_bytes()
    # briefs quote retail sources; a cp1252 byte must not kill the seat
    targets = [(r.lower(), int(n)) for r, n in TARGET.findall(body.decode("utf-8-sig", errors="replace"))]
    if not targets or len({r for r, _ in targets}) != len(targets):
        raise ValueError("brief must contain unique live TARGETS lines")
    run = datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%dT%H%M%SZ-") + uuid.uuid4().hex[:12]
    directory = root / "build/fleet_runs" / run
    directory.mkdir(parents=True)
    (directory / "brief.txt").write_bytes(body)
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=root, capture_output=True, text=True)
    record = dict(id=run, engine=engine, seat=seat, source_head=head.stdout.strip(),
                  brief_sha256=hashlib.sha256(body).hexdigest(), targets=targets,
                  start=time.time(), status="starting", legacy_log=str(legacy_log),
                  usage=None, usage_note="No token or cost attribution from plain-text output")
    save(directory / "record.json", record)
    claimed = False
    child = None
    try:
        claim(root, run, targets)
        claimed = True
        validate_targets(root, targets)
        record["status"] = "running"
        save(directory / "record.json", record)
        # The compatibility path becomes a pointer; preserve any old transcript.
        pointer = Path(legacy_log)
        pointer.parent.mkdir(parents=True, exist_ok=True)
        if pointer.exists():
            pointer.rename(pointer.with_name(pointer.name + ".before-" + run))
        pointer.write_text(f"run={run}\n{directory / 'output.log'}\n", encoding="utf-8")
        print(f"fleet run {run}: {directory}", flush=True)
        with (directory / "output.log").open("w", encoding="utf-8") as log:
            command, cap, kill_after = strip_timeout(command)
            # Popen without a shell does not consult PATHEXT: on Windows the
            # npm `codex` shim is codex.cmd, and a bare `codex` is WinError 2.
            command = [shutil.which(command[0]) or command[0]] + list(command[1:])
            # seat.sh passes the whole brief as one argument; on Windows the
            # npm codex shim goes through cmd.exe, whose line limit is ~8 KB
            # ("The command line is too long"). Hand the brief over stdin
            # instead: `codex exec -` reads the prompt from stdin everywhere.
            def norm(value):
                # ASCII only: argv arrives through the ANSI code page, so a
                # cp1252 byte in the brief never compares equal otherwise
                value = value.replace("\r\n", "\n").strip()
                return "".join(ch for ch in value if ch < "\x80")
            text = norm(body.decode("utf-8-sig", errors="ignore"))
            feed = None
            if any(norm(arg) == text for arg in command[1:]):
                command = ["-" if norm(arg) == text else arg for arg in command]
                feed = body.decode("utf-8-sig", errors="replace").encode("utf-8")  # codex refuses invalid UTF-8
            elif "-" in command[1:]:
                # seat.sh now passes `-` itself; the brief still goes over stdin
                feed = body.decode("utf-8-sig", errors="replace").encode("utf-8")
            child = subprocess.Popen(command, cwd=root, env=dict(os.environ, BFME_RUN_ID=run, BFME_RUN_DIR=str(directory)),
                                     stdin=subprocess.PIPE if feed else subprocess.DEVNULL,
                                     stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                     start_new_session=not sys.platform.startswith("win"))
            record["pid"] = child.pid
            record["cap_seconds"] = cap
            save(directory / "record.json", record)
            try:
                set_pid(root, run, child.pid, expected=len(targets))
            except ClaimConflict:
                kill_tree(child)
                child.wait(timeout=30)
                raise
            if feed:
                try:
                    child.stdin.write(feed)
                finally:
                    child.stdin.close()
            timer = None
            if cap:
                def expire():
                    record["timed_out"] = True
                    kill_tree(child)
                timer = threading.Timer(cap, expire)
                timer.daemon = True
                timer.start()
            # Bound memory even if a tool emits a multi-megabyte single line.
            with child.stdout:
                while chunk := child.stdout.readline(65536):
                    line = chunk.decode("utf-8", errors="replace")
                    if keep_transcript_line(line):
                        log.write(line.rstrip("\r\n")[:400] + "\n")
                        log.flush()
            code = child.wait()
            if timer:
                timer.cancel()
                timer.join()
        record.update(status="finished", exit_code=code)
        return code
    except BaseException as error:
        record.update(status="interrupted" if child and child.poll() is None else "failed",
                      error=str(error))
        raise
    finally:
        record.update(end=time.time())
        record["seconds"] = record["end"] - record["start"]
        record["touched"] = touched_rvas(directory)
        if claimed and child is not None and child.poll() is not None and surviving_group(child):
            # The direct CLI exited but a subprocess remains. Its PID is not
            # the stored PID, so retain ownership as unknown until an operator
            # verifies the whole group is gone and releases the named run.
            record["surviving_group"] = True
            try:
                set_pid(root, run, None, expected=len(targets))
            except ClaimConflict:
                record["claim_lost_with_surviving_group"] = True
        if record.get("status") == "finished" and aborted(record):
            record["status"] = "aborted"
        save(directory / "record.json", record)
        # A detached surviving child still owns its bodies. Do not time it out
        # of the registry and hand them to another worker.
        if claimed and not record.get("surviving_group") and (child is None or child.poll() is not None):
            release(root, run, "worker exited" if child is not None else "launch failed")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--brief", type=Path)
    ap.add_argument("--log", type=Path)
    ap.add_argument("--engine", default="manual")
    ap.add_argument("--seat", default="manual")
    ap.add_argument("--release")
    ap.add_argument("--reason")
    ap.add_argument("--fingerprint", type=lambda s: int(s, 16))
    ap.add_argument("--can-retry", type=lambda s: int(s, 16))
    ap.add_argument("--before")
    ap.add_argument("command", nargs=argparse.REMAINDER)
    a = ap.parse_args()
    if a.fingerprint is not None:
        print(stash_fingerprint(a.fingerprint))
        return
    if a.can_retry is not None:
        if not a.before:
            ap.error("--can-retry requires --before fingerprint")
        sys.exit(0 if retry_allowed(ROOT, a.can_retry, a.before) else 1)
    if a.release:
        if not a.reason:
            ap.error("--release requires --reason after verifying the worker has stopped")
        release(ROOT, a.release, a.reason)
        return
    command = a.command[1:] if a.command[:1] == ["--"] else a.command
    if not a.brief or not a.log or not command:
        ap.error("--brief, --log and a bounded command after -- are required")
    try:
        sys.exit(execute(ROOT, a.brief, a.log, a.engine, a.seat, command))
    except (ClaimConflict, StaleBrief) as error:
        print(f"fleet run: {error}; repick", file=sys.stderr)
        sys.exit(75)


if __name__ == "__main__":
    main()
