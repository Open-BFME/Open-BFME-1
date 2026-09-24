#!/usr/bin/env python3
"""Fail-closed Linux cgroup-v2 containment for fleet workers.

The caller creates a run unit and stores ``unit.path`` with its SQLite claim
before spawning anything. ``BlockedBootstrap`` starts a tiny Python bootstrap
which waits on a private pipe; it cannot exec the requested command until the
caller has moved and verified it in the unit. Descendants inherit membership,
including children which call setsid() or close their standard streams.

This is protection against accidental detachment, not hostile same-UID code:
the worker contract must prohibit deliberate migration to another writable
cgroup or use of an external manager to do so.
"""
from __future__ import annotations

import json
import os
from pathlib import Path
import re
import select
import signal
import subprocess
import sys
import time


class ContainmentUnavailable(RuntimeError):
    """The host cannot provide the required Linux process containment."""


class CgroupStateUnavailable(RuntimeError):
    """The run's cgroup state cannot be read safely."""


class BootstrapError(RuntimeError):
    """The blocked worker bootstrap failed before workload execution."""


def _unescape_proc_path(value: str) -> str:
    return re.sub(r"\\([0-7]{3})", lambda match: chr(int(match.group(1), 8)), value)


def _cgroup2_mount() -> tuple[Path, str]:
    """Return (mountpoint, mount-root) for the current unified cgroup."""
    if not sys.platform.startswith("linux"):
        raise ContainmentUnavailable("fleet workers require Linux cgroup v2 containment")
    try:
        membership = Path("/proc/self/cgroup").read_text(encoding="ascii")
        group = next(line.split("::", 1)[1] for line in membership.splitlines()
                     if line.startswith("0::"))
        group = _unescape_proc_path(group)
        mountinfo = Path("/proc/self/mountinfo").read_text(encoding="ascii")
    except (OSError, StopIteration, IndexError) as error:
        raise ContainmentUnavailable("cannot identify the process cgroup-v2 path") from error

    for line in mountinfo.splitlines():
        left, separator, right = line.partition(" - ")
        if not separator:
            continue
        before, after = left.split(), right.split()
        if not after or after[0] != "cgroup2" or len(before) < 5:
            continue
        mount_root = _unescape_proc_path(before[3])
        mountpoint = Path(_unescape_proc_path(before[4]))
        if mount_root == "/":
            suffix = group.lstrip("/")
        elif group == mount_root:
            suffix = ""
        elif group.startswith(mount_root.rstrip("/") + "/"):
            suffix = group[len(mount_root.rstrip("/")):].lstrip("/")
        else:
            continue
        current = (mountpoint / suffix).resolve()
        try:
            current.relative_to(mountpoint.resolve())
        except ValueError:
            continue
        if (current / "cgroup.events").is_file() and (current / "cgroup.procs").is_file():
            return mountpoint.resolve(), mount_root
    raise ContainmentUnavailable("no mounted cgroup-v2 filesystem contains this process")


def cgroup_populated(path: str | os.PathLike[str] | None) -> bool | None:
    """Read ``cgroup.events``; None means unknown and must be treated as busy."""
    if not path:
        return None
    try:
        contents = (Path(path) / "cgroup.events").read_text(encoding="ascii")
    except OSError:
        return None
    for line in contents.splitlines():
        fields = line.split()
        if len(fields) == 2 and fields[0] == "populated" and fields[1] in ("0", "1"):
            return fields[1] == "1"
    return None


def _process_cgroup(pid: int) -> str | None:
    try:
        lines = Path(f"/proc/{int(pid)}/cgroup").read_text(encoding="ascii").splitlines()
    except (OSError, ValueError):
        return None
    for line in lines:
        if line.startswith("0::"):
            return _unescape_proc_path(line[3:])
    return None


class CgroupV2Unit:
    """A per-run delegated child cgroup. Never kills on state reads."""

    def __init__(self, path: Path, kernel_path: str, *, owner: bool):
        self.path = path
        self.kernel_path = kernel_path.rstrip("/") or "/"
        self._owner = owner

    @classmethod
    def create(cls, run: str) -> "CgroupV2Unit":
        if not re.fullmatch(r"[A-Za-z0-9_-]{1,100}", run):
            raise ValueError(f"unsafe run id for cgroup name: {run!r}")
        mountpoint, mount_root = _cgroup2_mount()
        membership = Path("/proc/self/cgroup").read_text(encoding="ascii")
        group = next(line.split("::", 1)[1] for line in membership.splitlines()
                     if line.startswith("0::"))
        group = _unescape_proc_path(group)
        if mount_root == "/":
            suffix = group.lstrip("/")
        elif group == mount_root:
            suffix = ""
        elif group.startswith(mount_root.rstrip("/") + "/"):
            suffix = group[len(mount_root.rstrip("/")):].lstrip("/")
        else:
            raise ContainmentUnavailable("current process is outside the cgroup-v2 mount root")
        parent = (mountpoint / suffix).resolve()
        path = parent / f"bfme-fleet-{run}"
        try:
            path.mkdir()
        except OSError as error:
            raise ContainmentUnavailable(
                f"cannot create a delegated fleet cgroup under {parent}: {error}") from error
        try:
            for required in ("cgroup.events", "cgroup.procs", "cgroup.kill"):
                if not (path / required).is_file():
                    raise ContainmentUnavailable(f"cgroup-v2 lacks required {required}")
            if not os.access(path / "cgroup.procs", os.W_OK):
                raise ContainmentUnavailable("the delegated cgroup.procs file is not writable")
            if not os.access(path / "cgroup.kill", os.W_OK):
                raise ContainmentUnavailable("the delegated cgroup.kill file is not writable")
            kernel_path = ((group.rstrip("/") or "") + "/" + path.name
                           if group != "/" else "/" + path.name)
            unit = cls(path.resolve(), kernel_path, owner=True)
            if unit.populated() is not False:
                raise ContainmentUnavailable("new fleet cgroup is not verifiably empty")
            return unit
        except BaseException:
            try:
                path.rmdir()
            except OSError:
                pass
            raise

    @classmethod
    def from_path(cls, path: str | os.PathLike[str]) -> "CgroupV2Unit":
        """Open a persisted unit path for observation, not creation or killing."""
        unit_path = Path(path)
        if not unit_path.is_absolute():
            raise CgroupStateUnavailable("persisted cgroup path is not absolute")
        try:
            mountpoint, _ = _cgroup2_mount()
            unit_path = unit_path.resolve(strict=True)
            unit_path.relative_to(mountpoint)
        except (ContainmentUnavailable, OSError, ValueError) as error:
            raise CgroupStateUnavailable("persisted cgroup is outside the mounted cgroup-v2 tree") from error
        if (not unit_path.name.startswith("bfme-fleet-")
                or not (unit_path / "cgroup.events").is_file()
                or not (unit_path / "cgroup.procs").is_file()):
            raise CgroupStateUnavailable("persisted cgroup events file is missing")
        return cls(unit_path, "", owner=False)

    def populated(self) -> bool | None:
        return cgroup_populated(self.path)

    def attach(self, pid: int, timeout: float = 5.0) -> None:
        """Move a blocked bootstrap into this unit and verify membership."""
        if not self._owner:
            raise CgroupStateUnavailable("only the creating supervisor may assign a worker")
        try:
            with (self.path / "cgroup.procs").open("w", encoding="ascii") as handle:
                handle.write(f"{int(pid)}\n")
        except OSError as error:
            raise ContainmentUnavailable(f"cannot assign worker PID {pid} to {self.path}: {error}") from error
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            if _process_cgroup(pid) == self.kernel_path and self.populated() is True:
                return
            try:
                os.kill(int(pid), 0)
            except ProcessLookupError as error:
                raise ContainmentUnavailable("blocked worker exited before cgroup assignment") from error
            time.sleep(0.01)
        raise ContainmentUnavailable("cgroup assignment could not be verified")

    def wait_empty(self, timeout: float | None = None, poll: float = 0.05) -> None:
        """Wait until all descendants leave the unit; unknown state is an error."""
        deadline = None if timeout is None else time.monotonic() + timeout
        while True:
            state = self.populated()
            if state is False:
                return
            if state is None:
                raise CgroupStateUnavailable(f"cannot read cgroup.events for {self.path}")
            if deadline is not None and time.monotonic() >= deadline:
                raise TimeoutError(f"cgroup {self.path} is still populated")
            time.sleep(poll)

    def kill(self) -> None:
        """Kill this run's entire cgroup. Call only from its live timeout supervisor."""
        if not self._owner:
            raise CgroupStateUnavailable("only the creating supervisor may kill this cgroup")
        if self.populated() is False:
            return
        try:
            with (self.path / "cgroup.kill").open("w", encoding="ascii") as handle:
                handle.write("1\n")
        except OSError as error:
            raise CgroupStateUnavailable(f"cannot kill cgroup {self.path}: {error}") from error

    def remove(self) -> bool:
        """Remove only an empty unit; a populated or unknown one is retained."""
        if not self._owner:
            raise CgroupStateUnavailable("only the creating supervisor may remove this cgroup")
        if self.populated() is not False:
            return False
        try:
            self.path.rmdir()
            return True
        except OSError:
            return False


_BOOTSTRAP = r"""
import json, os, sys
ready_fd, gate_fd, env_fd = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])
command = sys.argv[5:]
with os.fdopen(env_fd, "r", encoding="utf-8") as stream:
    target_env = json.load(stream)
try:
    os.write(ready_fd, b"R")
finally:
    os.close(ready_fd)
token = os.read(gate_fd, 1)
os.close(gate_fd)
if token != b"G":
    os._exit(125)
os.execvpe(command[0], command, target_env)
"""


class BlockedBootstrap:
    """A child that cannot exec its workload until ``release`` is called."""

    def __init__(self, command, cwd, env, stdin, stdout, stderr, ready_timeout=10.0):
        if not sys.platform.startswith("linux"):
            raise ContainmentUnavailable("blocked cgroup bootstrap is Linux-only")
        command = list(command)
        if not command:
            raise ValueError("blocked worker command must not be empty")
        ready_read, ready_write = os.pipe()
        gate_read, gate_write = os.pipe()
        env_read, env_write = os.pipe()
        self._gate_write = gate_write
        self._ready_read = ready_read
        self._released = False
        self._aborted = False
        argv = [sys.executable, "-I", "-S", "-c", _BOOTSTRAP,
                str(ready_write), str(gate_read), str(env_read), "--", *command]
        try:
            # No worker-controlled loader or Python startup variables reach
            # the pre-attach bootstrap. It receives only serialized target
            # environment data over a private pipe and restores it at exec.
            self.child = subprocess.Popen(
                argv, cwd=cwd, env={}, stdin=stdin, stdout=stdout, stderr=stderr,
                start_new_session=True, pass_fds=(ready_write, gate_read, env_read))
        except BaseException:
            for descriptor in (ready_read, ready_write, gate_read, gate_write,
                               env_read, env_write):
                try:
                    os.close(descriptor)
                except OSError:
                    pass
            raise
        os.close(ready_write)
        os.close(gate_read)
        os.close(env_read)
        env_write_open = True
        try:
            payload = json.dumps(dict(env), separators=(",", ":")).encode("utf-8")
            offset = 0
            while offset < len(payload):
                offset += os.write(env_write, payload[offset:])
        except BaseException:
            os.close(env_write)
            env_write_open = False
            os.close(ready_read)
            self._ready_read = None
            self.abort()
            raise
        finally:
            if env_write_open:
                os.close(env_write)
        try:
            deadline = time.monotonic() + ready_timeout
            token = b""
            while time.monotonic() < deadline:
                try:
                    ready, _, _ = select.select(
                        [ready_read], [], [], max(0.0, deadline - time.monotonic()))
                except InterruptedError:
                    continue
                if not ready:
                    break
                token = os.read(ready_read, 1)
                break
        except BaseException:
            os.close(ready_read)
            self._ready_read = None
            self.abort()
            raise
        else:
            os.close(ready_read)
            self._ready_read = None
        if token != b"R":
            self.abort()
            raise BootstrapError("blocked worker did not reach its pre-exec handshake")

    def release(self) -> None:
        if self._released:
            raise BootstrapError("blocked worker was already released")
        if self._aborted:
            raise BootstrapError("blocked worker bootstrap was aborted")
        if self._gate_write is None:
            raise BootstrapError("blocked worker gate is already closed")
        # Mark the transition before the pipe write. If a signal arrives after
        # the byte reaches the child but before this function returns, cleanup
        # must not mistake an already released workload for a blocked bootstrap.
        self._released = True
        try:
            written = os.write(self._gate_write, b"G")
            if written != 1:
                raise BootstrapError("could not release blocked worker")
        finally:
            os.close(self._gate_write)
            self._gate_write = None

    def abort(self, timeout: float = 5.0) -> None:
        """Close the gate (EOF means abort) and stop only the trusted bootstrap."""
        if self._released:
            raise BootstrapError("refusing to abort a released worker")
        if self._aborted:
            return
        if self._gate_write is not None:
            try:
                os.close(self._gate_write)
            except OSError:
                pass
            self._gate_write = None
        self._aborted = True
        if self.child.poll() is None:
            try:
                self.child.wait(timeout=timeout)
            except subprocess.TimeoutExpired:
                # The gate is still closed, so workload code was never released.
                try:
                    os.kill(self.child.pid, signal.SIGKILL)
                except OSError:
                    pass
                self.child.wait(timeout=timeout)
        else:
            self.child.wait()


def remove_empty_cgroup(path: str | os.PathLike[str], run: str) -> bool:
    """Remove a positively empty unit only when its path matches this run ID."""
    try:
        unit = CgroupV2Unit.from_path(path)
        if unit.path.name != f"bfme-fleet-{run}" or unit.populated() is not False:
            return False
        unit.path.rmdir()
        return True
    except (CgroupStateUnavailable, OSError):
        return False
