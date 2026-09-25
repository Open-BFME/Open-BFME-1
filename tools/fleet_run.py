#!/usr/bin/env python3
"""Run one worker with an immutable brief, transcript and actual exit status.

The caller supplies a bounded command (seat.sh uses timeout). Runs share an
atomic RVA claim table across lanes. A claim carries its worker PID, expiry,
and delegated Linux cgroup-v2 path. Reclaim requires an expired lease and a
verified ``populated=0`` event; a dead PID or terminal record alone is not
enough. Hosts without delegated cgroup-v2 support fail before launch. An
operator can release a named cgroup-less legacy claim after establishing the
worker stopped. Deploy at a controlled fleet restart, not over running workers.
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
import sqlite3
import subprocess
import sys
import threading
import time
import uuid

import fleet_cgroup

from portable_lock import lock

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


class CoordinationUnavailable(RuntimeError):
    """Prior fleet state cannot be proved intact; refuse a new owner."""


def coordination_marker(root):
    return Path(root) / "build/fleet_coordination.json"


def _database(root):
    return Path(root) / "build/fleet_runs.sqlite"


def _open_existing(path, *, readonly=False):
    mode = "ro" if readonly else "rw"
    return sqlite3.connect(path.resolve().as_uri() + f"?mode={mode}",
                           uri=True, timeout=60)


def _schema(db):
    db.execute("CREATE TABLE IF NOT EXISTS claims (rva TEXT PRIMARY KEY, run TEXT, started REAL)")
    db.execute("CREATE TABLE IF NOT EXISTS releases (run TEXT, at REAL, reason TEXT)")
    db.execute("CREATE TABLE IF NOT EXISTS fleet_coordination (id TEXT PRIMARY KEY)")
    have = {row[1] for row in db.execute("PRAGMA table_info(claims)")}
    if "pid" not in have:
        db.execute("ALTER TABLE claims ADD COLUMN pid INTEGER")
    if "expires" not in have:
        db.execute("ALTER TABLE claims ADD COLUMN expires REAL")
    if "cgroup_path" not in have:
        db.execute("ALTER TABLE claims ADD COLUMN cgroup_path TEXT")


def _require_schema(db, *, initialized, require_cgroup=True):
    """An initialized database must not repair a missing claims schema on read."""
    required = {
        "claims": ({"rva", "run", "started", "pid", "expires"}
                   | ({"cgroup_path"} if require_cgroup else set())) if initialized
                  else {"rva", "run", "started"},
        "releases": {"run", "at", "reason"},
    }
    if initialized:
        required["fleet_coordination"] = {"id"}
    for table, columns in required.items():
        actual = {row[1] for row in db.execute(f"PRAGMA table_info({table})")}
        if not columns <= actual:
            if table == "claims" and require_cgroup and "cgroup_path" not in actual:
                raise CoordinationUnavailable(
                    "claims database needs the guarded cgroup schema migration; "
                    "stop the fleet, review --coordination-status, then run --init-coordination")
            raise CoordinationUnavailable(f"claims database schema lacks {table} columns")


def _database_id(db):
    try:
        values = [row[0] for row in db.execute("SELECT id FROM fleet_coordination")]
    except sqlite3.Error as error:
        raise CoordinationUnavailable(f"claims database lacks coordination identity: {error}") from error
    if len(values) > 1:
        raise CoordinationUnavailable("claims database has multiple coordination identities")
    if not values:
        return None
    try:
        if str(uuid.UUID(values[0])) != values[0]:
            raise ValueError("noncanonical UUID")
    except (ValueError, TypeError, AttributeError) as error:
        raise CoordinationUnavailable(f"invalid claims database identity: {error}") from error
    return values[0]


def _marker_id(path):
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
        value = data["id"]
        if data.get("version") != 1 or str(uuid.UUID(value)) != value:
            raise ValueError("invalid marker version or UUID")
        return value
    except (OSError, ValueError, KeyError, TypeError, AttributeError) as error:
        raise CoordinationUnavailable(f"invalid fleet coordination marker {path}: {error}") from error


def _write_marker(path, identity):
    temporary = path.with_name(path.name + "." + uuid.uuid4().hex + ".tmp")
    try:
        with temporary.open("w", encoding="utf-8") as handle:
            json.dump({"version": 1, "id": identity}, handle, sort_keys=True)
            handle.write("\n")
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(temporary, path)
    finally:
        temporary.unlink(missing_ok=True)


def _history(root):
    runs = Path(root) / "build/fleet_runs"
    log = Path(root) / "build/fleet_logs/seats.log"
    if runs.exists() and any(runs.iterdir()):
        return True
    if not log.exists():
        return False
    # New picker diagnostics never reserve anything. A picker may write one
    # before the first runner initializes SQLite; only old/unknown log events
    # require a stopped-fleet review at that point.
    for line in log.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.strip() and not re.fullmatch(
                r"\S+ seat pick selected(?: \S+)+", line):
            return True
    return False


def _run_history(root):
    runs = Path(root) / "build/fleet_runs"
    return runs.exists() and any(runs.iterdir())


def _ready_connection(path, marker):
    identity = _marker_id(marker)
    if not path.exists():
        raise CoordinationUnavailable(f"claims database missing after initialization: {path}")
    try:
        db = _open_existing(path)
        _require_schema(db, initialized=True)
        if _database_id(db) != identity:
            raise CoordinationUnavailable("claims database identity differs from coordination marker")
        return db
    except BaseException:
        if "db" in locals():
            db.close()
        raise


def connect(root):
    """Open one intact local claims database, creating only a fresh one.

    A missing/replaced database after any run was recorded is not an empty
    queue. The marker's UUID binds the file to this checkout's prior claims.
    """
    root = Path(root)
    build = root / "build"
    build.mkdir(exist_ok=True)
    path, marker = _database(root), coordination_marker(root)
    if marker.exists():
        return _ready_connection(path, marker)
    with (build / ".fleet_coordination.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        if marker.exists():
            return _ready_connection(path, marker)
        if _history(root):
            raise CoordinationUnavailable(
                "historical fleet records exist without a coordination marker; "
                "stop the fleet and run --coordination-status, then guarded --init-coordination")
        if path.exists():
            try:
                db = _open_existing(path)
                _require_schema(db, initialized=False)
                db.execute("BEGIN IMMEDIATE")
                if (db.execute("SELECT count(*) FROM claims").fetchone()[0]
                        or db.execute("SELECT count(*) FROM releases").fetchone()[0]):
                    raise CoordinationUnavailable(
                        "unmarked claims database contains claim or release history")
                _schema(db)
            except BaseException:
                if "db" in locals():
                    db.close()
                raise
        else:
            db = sqlite3.connect(path, timeout=60)
            _schema(db)
        try:
            identity = _database_id(db)
            if identity is None:
                identity = str(uuid.uuid4())
                db.execute("INSERT INTO fleet_coordination (id) VALUES (?)", (identity,))
            db.commit()
            _write_marker(marker, identity)
            return db
        except BaseException:
            db.close()
            raise


def _coordination_digest(root):
    """Bind a dry-run cutover approval to the local records it inspected."""
    root = Path(root)
    build = root / "build"
    paths = [_database(root), Path(str(_database(root)) + "-wal"),
             Path(str(_database(root)) + "-shm"), coordination_marker(root),
             Path(str(_database(root)) + "-journal"),
             build / "fleet_logs/seats.log"]
    runs = build / "fleet_runs"
    if runs.exists():
        for directory in sorted(runs.iterdir()):
            paths.extend((directory / "record.json", directory / "touched.txt"))
    digest = hashlib.sha256()
    for path in paths:
        digest.update(str(path.relative_to(root)).encode("utf-8", errors="replace") + b"\0")
        try:
            with path.open("rb") as handle:
                while chunk := handle.read(1024 * 1024):
                    digest.update(chunk)
        except FileNotFoundError:
            digest.update(b"<missing>")
        digest.update(b"\0")
    return digest.hexdigest()


def cgroup_state(path, run=None):
    """Return the verified cgroup state; absent, malformed or unreadable is unknown."""
    if not path:
        return None
    try:
        unit = fleet_cgroup.CgroupV2Unit.from_path(path)
        if run is not None and unit.path.name != f"bfme-fleet-{run}":
            return None
        return unit.populated()
    except (fleet_cgroup.CgroupStateUnavailable,
            fleet_cgroup.ContainmentUnavailable, OSError, TypeError, ValueError):
        return None


def _cgroup_summary(states):
    counts = {"empty": 0, "populated": 0, "unknown": 0}
    for state in states:
        counts["empty" if state is False else "populated" if state is True else "unknown"] += 1
    return counts


def coordination_status(root):
    """Read-only report for a controlled fleet coordination cutover."""
    root = Path(root)
    path, marker = _database(root), coordination_marker(root)
    records = sorted((root / "build/fleet_runs").glob("*/record.json"))
    report = dict(state="fresh", claim_count=None, release_count=None,
                  record_count=len(records))
    unit_states = []
    for record_path in records:
        try:
            data = json.loads(record_path.read_text(encoding="utf-8"))
            path_value = data.get("cgroup_path") if isinstance(data, dict) else None
            if path_value:
                state = cgroup_state(path_value, data.get("id") or record_path.parent.name)
                if state is None and data.get("cgroup_empty_verified") is True:
                    state = False
                unit_states.append(state)
        except (OSError, ValueError):
            unit_states.append(None)

    def finished():
        # SQLite's first read of a WAL database may create a shared-memory
        # sidecar. Snapshot after the read so the dry run does not stale itself.
        report.setdefault("cgroup_units", _cgroup_summary(unit_states))
        report["snapshot_sha256"] = _coordination_digest(root)
        return report

    identity = None
    if marker.exists():
        try:
            identity = _marker_id(marker)
        except CoordinationUnavailable as error:
            report.update(state="inconsistent", problem=str(error))
            return finished()
    if not path.exists():
        report["state"] = "missing" if marker.exists() else (
            "missing" if _run_history(root) else
            "requires_review" if _history(root) else "fresh")
        return finished()
    try:
        with closing(_open_existing(path, readonly=True)) as db:
            _require_schema(db, initialized=identity is not None, require_cgroup=False)
            report["claim_count"] = db.execute("SELECT count(*) FROM claims").fetchone()[0]
            report["release_count"] = db.execute("SELECT count(*) FROM releases").fetchone()[0]
            columns = {row[1] for row in db.execute("PRAGMA table_info(claims)")}
            report["cgroup_schema"] = "present" if "cgroup_path" in columns else "missing"
            if "cgroup_path" in columns:
                for run, path_value in db.execute(
                        "SELECT DISTINCT run, cgroup_path FROM claims WHERE cgroup_path IS NOT NULL"):
                    unit_states.append(cgroup_state(path_value, run))
            report["cgroup_units"] = _cgroup_summary(unit_states)
            if identity is not None and _database_id(db) != identity:
                report.update(state="inconsistent", problem="database UUID differs from marker")
            else:
                if identity is None:
                    report["state"] = "requires_review"
                else:
                    report["state"] = ("ready" if "cgroup_path" in columns
                                        else "requires_cgroup_migration")
    except (sqlite3.Error, CoordinationUnavailable) as error:
        report.update(state="inconsistent", problem=str(error))
    return finished()


def _recorded_live_pids(root):
    for directory in (Path(root) / "build/fleet_runs").glob("*"):
        path = directory / "record.json"
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, ValueError) as error:
            raise CoordinationUnavailable(f"cannot establish run-record liveness at {path}: {error}") from error
        if not isinstance(data, dict):
            raise CoordinationUnavailable(f"cannot establish run-record liveness at {path}: not an object")
        pid = data.get("pid")
        if pid is not None and (not isinstance(pid, int) or isinstance(pid, bool) or pid <= 0):
            raise CoordinationUnavailable(f"cannot establish run-record liveness at {path}: invalid PID")
        if pid is None and data.get("status") not in ("finished", "failed", "aborted"):
            raise CoordinationUnavailable(f"cannot establish run-record liveness at {path}: nonterminal run has no PID")
        if pid and pid_alive(pid):
            yield pid
        cgroup_path = data.get("cgroup_path")
        if cgroup_path:
            state = cgroup_state(cgroup_path, data.get("id") or directory.name)
            if state is True or (state is None and data.get("cgroup_empty_verified") is not True):
                raise CoordinationUnavailable(
                    f"cannot establish empty cgroup for run {directory.name}: {state or 'unknown'}")


def initialize_coordination(root, *, stopped_fleet=False, expected_sha=None):
    """Guarded migration; never clears a claim or changes a run record."""
    if not stopped_fleet or not expected_sha:
        raise ValueError("initialization requires --stopped-fleet and --state-sha from a dry run")
    root = Path(root)
    build = root / "build"
    build.mkdir(exist_ok=True)
    with (build / ".fleet_coordination.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        report = coordination_status(root)
        if report["snapshot_sha256"] != expected_sha:
            raise ValueError("fleet coordination state changed since dry run; inspect and retry")
        if report["state"] in ("missing", "inconsistent"):
            raise CoordinationUnavailable(
                "prior claims database is missing or inconsistent; restore it before migration")
        if report["state"] == "ready":
            return report
        marked_cgroup_migration = report["state"] == "requires_cgroup_migration"
        live = list(_recorded_live_pids(root))
        if live:
            raise CoordinationUnavailable(f"recorded worker PID(s) still alive: {live}")
        path = _database(root)
        if path.exists():
            db = _open_existing(path)
            try:
                db.execute("BEGIN IMMEDIATE")
                if marked_cgroup_migration:
                    # A marked database may add only the reviewed nullable
                    # cgroup column. Never repair another lost required field.
                    _require_schema(db, initialized=True, require_cgroup=False)
                else:
                    _require_schema(db, initialized=False)
                columns = {row[1] for row in db.execute("PRAGMA table_info(claims)")}
                if "pid" in columns:
                    live = [pid for (pid,) in db.execute("SELECT pid FROM claims")
                            if pid and pid_alive(pid)]
                    if live:
                        raise CoordinationUnavailable(f"claimed worker PID(s) still alive: {live}")
                if "cgroup_path" in columns:
                    for owner, cgroup_path in db.execute(
                            "SELECT DISTINCT run, cgroup_path FROM claims WHERE cgroup_path IS NOT NULL"):
                        if cgroup_state(cgroup_path, owner) is not False:
                            raise CoordinationUnavailable(
                                f"cannot establish empty cgroup for claimed run {owner}")
                _schema(db)
            except BaseException:
                db.close()
                raise
        else:
            db = sqlite3.connect(path, timeout=60)
            _schema(db)
        try:
            identity = _database_id(db)
            if identity is None:
                identity = str(uuid.uuid4())
                db.execute("INSERT INTO fleet_coordination (id) VALUES (?)", (identity,))
            db.commit()
            _write_marker(coordination_marker(root), identity)
        finally:
            db.close()
        return coordination_status(root)


def pid_alive(pid):
    """True while the process exists. Unknown pid (None) counts as alive: a
    lease we cannot check is not a lease we may take."""
    # A negative POSIX PID addresses a process group; zero addresses our own
    # group. Neither is an unambiguous worker PID, so never use kill(0) on it.
    if not isinstance(pid, int) or isinstance(pid, bool) or pid <= 0:
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


def lease_dead(expires, pid, now=None, root=None, run=None, cgroup_path=None):
    now = time.time() if now is None else now
    # A dead direct PID or terminal legacy record cannot prove detached
    # descendants stopped. Only a contained run with an expired lease and a
    # positively empty cgroup can be reclaimed automatically.
    if not expires or now <= expires or not cgroup_path:
        return False
    # Empty containment excludes descendants; the separately recorded direct
    # PID must also be absent so an escaped/migrated worker cannot be replaced.
    if cgroup_state(cgroup_path, run) is not False:
        return False
    pids = []
    if pid is not None:
        pids.append(pid)
    record_has_pid = False
    preexec_no_pid = False
    if root is not None and run is not None:
        record_path = Path(root) / "build/fleet_runs" / str(run) / "record.json"
        try:
            record = json.loads(record_path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            return False
        if not isinstance(record, dict):
            return False
        if (record.get("id") != str(run)
                or record.get("cgroup_path") != str(cgroup_path)):
            return False
        record_has_pid = "pid" in record
        if record_has_pid:
            pids.append(record["pid"])
        preexec_no_pid = (
            not record_has_pid
            and record.get("touch_tracking") is True
            and record.get("launch_phase") in ("starting", "preexec")
            and record.get("status") in ("starting", "running"))
    elif pid is None:
        return False
    if any(pid_alive(value) for value in pids):
        return False
    # With no direct PID yet, only the durable prelaunch record state is
    # eligible: the gated bootstrap cannot exec before attach and PID commit.
    return bool(pids) or preexec_no_pid


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


def claim(root, run, targets, pid=None, lease=None, cgroup_path=None, expires_at=None):
    lease = LEASE_SECONDS if lease is None else lease
    now = time.time()
    expires = now + lease if expires_at is None else expires_at
    with closing(connect(root)) as db, db:
        db.execute("BEGIN IMMEDIATE")
        for rva, _ in targets:
            owner = db.execute(
                "SELECT run, pid, expires, cgroup_path FROM claims WHERE rva=?", (rva,)).fetchone()
            if owner:
                if not lease_dead(owner[2], owner[1], now, root, owner[0], owner[3]):
                    raise ClaimConflict(f"{rva} is already owned by run {owner[0]}")
                db.execute("DELETE FROM claims WHERE rva=?", (rva,))
                db.execute("INSERT INTO releases VALUES (?,?,?)",
                           (owner[0], now,
                            f"lease expired and run cgroup was verified empty; "
                            f"{rva} taken by {run}"))
            db.execute(
                "INSERT INTO claims (rva, run, started, pid, expires, cgroup_path) "
                "VALUES (?,?,?,?,?,?)",
                (rva, run, now, pid, expires, cgroup_path))


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
    """Leases that are live or whose worker termination is not yet proven."""
    now = time.time()
    with closing(connect(root)) as db, db:
        rows = db.execute("SELECT rva, run, pid, expires, cgroup_path FROM claims").fetchall()
    return {rva for rva, run, pid, expires, cgroup_path in rows
            if not lease_dead(expires, pid, now, root, run, cgroup_path)}


MODEL_TOKEN = re.compile(r"[A-Za-z0-9._/-]{1,60}")


def launched_model(command):
    """The model a worker command runs (`-m X`, `--model X`, `--model=X`), so
    re_log and add_match can attribute its verdicts and landings without
    trusting the session to type it: on 2026-09-25 about 80% of landings and
    3,000 verdict rows carried no usable model, so no lane's yield could be
    measured."""
    for i, arg in enumerate(command):
        value = None
        if arg in ("-m", "--model") and i + 1 < len(command):
            value = command[i + 1]
        elif arg.startswith("--model="):
            value = arg.split("=", 1)[1]
        if value and MODEL_TOKEN.fullmatch(value):
            return value
    return ""


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
    return ((record.get("status") == "aborted" and not record.get("touched"))
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


def release(root, run, reason, *, stopped_fleet=False, expected_state_sha=None):
    with closing(connect(root)) as db, db:
        db.execute("BEGIN IMMEDIATE")
        rows = db.execute(
            "SELECT DISTINCT run, pid, cgroup_path FROM claims WHERE run=?", (run,)).fetchall()
        record_path = Path(root) / "build/fleet_runs" / str(run) / "record.json"
        try:
            data = json.loads(record_path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            data = {}
        if not isinstance(data, dict):
            data = {}
        record_cgroup = data.get("cgroup_path")
        record_pid = data.get("pid")
        if record_pid is not None and pid_alive(record_pid):
            raise ClaimConflict(f"cannot release run {run}: recorded worker PID is alive or unknown")
        if record_cgroup and cgroup_state(record_cgroup, run) is not False:
            raise ClaimConflict(f"cannot release run {run}: its recorded cgroup is populated or unknown")
        legacy_claim = False
        for owner, pid, path in rows:
            if path != record_cgroup:
                raise ClaimConflict(
                    f"cannot release run {run}: claim and record cgroup paths differ")
            if pid is not None and pid_alive(pid):
                raise ClaimConflict(f"cannot release run {run}: claimed worker PID is alive or unknown")
            if path:
                if data.get("id") != str(run):
                    raise ClaimConflict(f"cannot release run {run}: its recorded cgroup owner ID differs")
                if cgroup_state(path, owner) is not False:
                    raise ClaimConflict(f"cannot release run {run}: its cgroup is populated or unknown")
            else:
                legacy_claim = True
        if legacy_claim:
            if not stopped_fleet or not expected_state_sha:
                raise ClaimConflict(
                    f"cgroup-less run {run} requires --stopped-fleet and a fresh --state-sha "
                    "from --coordination-status before named release")
            report = coordination_status(root)
            if report["snapshot_sha256"] != expected_state_sha:
                raise ClaimConflict("fleet state changed since coordination status; inspect and retry")
            units = report.get("cgroup_units", {})
            if units.get("populated", 0) or units.get("unknown", 0):
                raise ClaimConflict("cannot release cgroup-less ownership while any cgroup is active or unknown")
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
    # First use must establish durable coordination before writing a starting
    # run record. Otherwise our own preclaim record would look like a prior
    # fleet run when the database does not yet exist.
    with closing(connect(root)):
        pass
    run = datetime.datetime.now(datetime.timezone.utc).strftime("%Y%m%dT%H%M%SZ-") + uuid.uuid4().hex[:12]
    # Fail before recording or claiming work unless a delegated cgroup-v2
    # unit can be created. There is no process-group fallback.
    unit = fleet_cgroup.CgroupV2Unit.create(run)
    directory = root / "build/fleet_runs" / run
    try:
        directory.mkdir(parents=True)
        (directory / "brief.txt").write_bytes(body)
        head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=root, capture_output=True, text=True)
        record_path = directory / "record.json"
        record = dict(id=run, engine=engine, seat=seat, source_head=head.stdout.strip(),
                      brief_sha256=hashlib.sha256(body).hexdigest(), targets=targets,
                      start=time.time(), status="starting", legacy_log=str(legacy_log),
                      cgroup_path=str(unit.path), cgroup_empty_verified=False,
                      touch_tracking=True, launch_phase="starting",
                      usage=None, usage_note="No token or cost attribution from plain-text output")
        save(record_path, record)
    except BaseException:
        if unit.populated() is False:
            unit.remove()
        raise

    record_lock = threading.RLock()

    def save_record():
        with record_lock:
            save(record_path, record)

    claimed = False
    child = None
    bootstrap = None
    timer = None
    timeout_errors = []
    try:
        lease_expires = time.time() + LEASE_SECONDS
        record["lease_expires"] = lease_expires
        save_record()
        claim(root, run, targets, cgroup_path=str(unit.path), expires_at=lease_expires)
        claimed = True
        validate_targets(root, targets)
        record["status"] = "running"
        save_record()
        # The compatibility path becomes a pointer; preserve any old transcript.
        pointer = Path(legacy_log)
        pointer.parent.mkdir(parents=True, exist_ok=True)
        if pointer.exists():
            pointer.rename(pointer.with_name(pointer.name + ".before-" + run))
        pointer.write_text(f"run={run}\n{directory / 'output.log'}\n", encoding="utf-8")
        print(f"fleet run {run}: {directory}", flush=True)
        with (directory / "output.log").open("w", encoding="utf-8") as log:
            command, cap, kill_after = strip_timeout(command)
            if not command:
                raise ValueError("worker command must not be empty")
            # Resolve in the supervisor so a missing executable remains a
            # pre-exec launch failure instead of a worker exit from bootstrap.
            resolved = shutil.which(command[0])
            if not resolved:
                raise FileNotFoundError(f"worker executable not found: {command[0]}")
            command = [resolved] + list(command[1:])
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
            record["launch_phase"] = "preexec"
            save_record()
            env = dict(os.environ, BFME_RUN_ID=run, BFME_RUN_DIR=str(directory))
            model = launched_model(command)
            if model:
                env["BFME_MODEL"] = model
            bootstrap = fleet_cgroup.BlockedBootstrap(
                command, cwd=root, env=env,
                stdin=subprocess.PIPE if feed else subprocess.DEVNULL,
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            child = bootstrap.child
            record["pid"] = child.pid
            record["launch_phase"] = "bootstrap"
            record["cap_seconds"] = cap
            save_record()
            unit.attach(child.pid)
            set_pid(root, run, child.pid, expected=len(targets))
            record["launch_phase"] = "contained"
            save_record()
            if cap is not None:
                def expire():
                    if unit.populated() is False:
                        return
                    try:
                        unit.kill()
                    except BaseException as error:
                        timeout_errors.append(str(error))
                    try:
                        with record_lock:
                            record["timed_out"] = True
                            if timeout_errors:
                                record["cgroup_timeout_error"] = timeout_errors[-1]
                            save(record_path, record)
                    except BaseException as error:
                        timeout_errors.append(f"cannot save timeout record: {error}")
                timer = threading.Timer(cap, expire)
                # Keep the owning supervisor alive until its cap action runs
                # if an exception leaves the unit populated.
                timer.daemon = False
                timer.start()
            bootstrap.release()
            record["launch_phase"] = "released"
            save_record()
            if feed:
                try:
                    child.stdin.write(feed)
                finally:
                    child.stdin.close()
            # Bound memory even if a tool emits a multi-megabyte single line.
            with child.stdout:
                while chunk := child.stdout.readline(65536):
                    line = chunk.decode("utf-8", errors="replace")
                    if keep_transcript_line(line):
                        log.write(line.rstrip("\r\n")[:400] + "\n")
                        log.flush()
            code = child.wait()
            # A direct CLI exit does not release ownership: wait for every
            # contained descendant before freezing touches or stopping timer.
            while True:
                if timeout_errors:
                    raise fleet_cgroup.CgroupStateUnavailable(timeout_errors[-1])
                state = unit.populated()
                if state is False:
                    break
                if state is None:
                    raise fleet_cgroup.CgroupStateUnavailable(
                        f"cannot read cgroup.events for {unit.path}")
                time.sleep(0.05)
            if timer:
                timer.cancel()
                timer.join()
                timer = None
        record.update(status="finished", exit_code=code)
        return code
    except BaseException as error:
        with record_lock:
            record.update(status="interrupted" if child and child.poll() is None else "failed",
                          error=str(error))
        save_record()
        raise
    finally:
        if bootstrap is not None and not bootstrap._released:
            try:
                bootstrap.abort()
            except BaseException as error:
                record["bootstrap_abort_error"] = str(error)
        state = unit.populated()
        empty = state is False
        if timer and empty:
            timer.cancel()
            timer.join()
            timer = None
        with record_lock:
            record["end"] = time.time()
            record["seconds"] = record["end"] - record["start"]
            record["touched"] = touched_rvas(directory)
            record["cgroup_empty_verified"] = empty
            if empty:
                record["launch_phase"] = "complete"
            if state is True:
                record["cgroup_state"] = "populated"
            elif state is None:
                record["cgroup_state"] = "unknown"
            if timeout_errors:
                record["cgroup_timeout_error"] = timeout_errors[-1]
            if record.get("status") == "finished" and aborted(record):
                record["status"] = "aborted"
            save(record_path, record)
        # Release only after a positive empty observation. The record carries
        # that evidence before the DB row is removed; then remove only our unit.
        if claimed and empty:
            release(root, run, "contained worker unit empty")
        if empty:
            unit.remove()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--coordination-status", action="store_true")
    ap.add_argument("--init-coordination", action="store_true")
    ap.add_argument("--stopped-fleet", action="store_true")
    ap.add_argument("--state-sha")
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
    if a.coordination_status:
        print(json.dumps(coordination_status(ROOT), indent=2))
        return
    if a.init_coordination:
        print(json.dumps(initialize_coordination(
            ROOT, stopped_fleet=a.stopped_fleet, expected_sha=a.state_sha), indent=2))
        return
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
        release(ROOT, a.release, a.reason, stopped_fleet=a.stopped_fleet,
                expected_state_sha=a.state_sha)
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
