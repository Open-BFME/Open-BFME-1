#!/usr/bin/env python3
"""The compact fleet log must retain byte-level diagnostic evidence."""
import contextlib
import io
import json
import os
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import fleet_run
import fleet_cgroup


def require_cgroup_v2(test):
    """These tests launch a real worker, and since afea6de317 fleet_run
    contains every worker in a delegated cgroup-v2 unit. GitHub's runners and
    Windows hosts cannot create one, so the tests skip there instead of
    turning the tools workflow red (red on every push since 2026-09-24)."""
    import uuid
    try:
        unit = fleet_cgroup.CgroupV2Unit.create("test-" + uuid.uuid4().hex)
    except fleet_cgroup.ContainmentUnavailable as error:
        test.skipTest(f"host does not delegate writable cgroup-v2 units: {error}")
    unit.remove()


def open_ledger(root, *targets):
    reverse = root / "reverse"
    reverse.mkdir(exist_ok=True)
    rows = ["name,export_rva,target_rva,target_size,source,status,notes"]
    rows += [f"?d_{rva:08X}@@YAXXZ,,0x{rva:08X},{size},Code/gen_asm/test.asm,matched,"
             for rva, size in targets]
    (reverse / "functions.csv").write_text("\n".join(rows) + "\n", encoding="utf-8")


class TranscriptFilterTests(unittest.TestCase):
    def test_retail_instructions_survive(self):
        for line in (
            "+0000 56                       push    esi",
            "+0003 a1 b0 bd 2d 01           mov     eax, dword ptr [0x12dbdb0]",
            "+00c0 e8 bf 5d 1f 00           call    0xdf74f4 ;security_check_cookie",
            "+00c8 c2 04 00                 ret     4",
            "+ABCD 0F B6 04 1E              movzx   eax, byte ptr [esi + ebx]",
            "+10000 90                      nop",
        ):
            with self.subTest(line=line):
                self.assertTrue(fleet_run.keep_transcript_line(line))

    def test_patch_noise_is_still_suppressed(self):
        for line in (
            "diff --git a/test.cpp b/test.cpp",
            "index 1234abcd..5678abcd 100644",
            "--- a/test.cpp", "+++ b/test.cpp", "@@ -1,2 +1,3 @@",
            "+return result;", "-return 0;",
            "+0000 is not disassembly",
        ):
            with self.subTest(line=line):
                self.assertFalse(fleet_run.keep_transcript_line(line))

    def test_ambiguous_instruction_shaped_text_is_kept(self):
        # Logging must not require a decoder dependency or guess which
        # mnemonics are real before allowing evidence into the transcript.
        self.assertTrue(fleet_run.keep_transcript_line("+abcd ef unknown value"))

    def test_other_diagnostics_survive(self):
        for line in ("; retail rva=0x00801670 size=203", "result EXACT",
                     "!!0080 mov ecx, edi", "Functions: FAIL 1/2", ""):
            with self.subTest(line=line):
                self.assertTrue(fleet_run.keep_transcript_line(line))

    def test_worker_log_and_exit_status(self):
        require_cgroup_v2(self)
        with tempfile.TemporaryDirectory() as temporary, contextlib.ExitStack() as cleanup:
            root = Path(temporary)
            open_ledger(root, (0x00123456, 2))
            brief = root / "brief.txt"
            brief.write_text("TARGETS\n- 0x00123456 2B\n", encoding="utf-8")
            pointer = root / "latest.log"
            lines = ["; retail rva=0x00123456 size=2",
                     "+0000 90                       nop",
                     "+0001 c3                       ret",
                     "+return 0;", "diagnostic " + "x" * 600]
            command = [sys.executable, "-c",
                       "import sys; print(" + repr("\n".join(lines)) + "); sys.exit(7)"]
            original_connect = fleet_run.connect

            def connect(path):
                connection = original_connect(path)
                cleanup.callback(connection.close)
                return connection

            with patch.object(fleet_run, "connect", side_effect=connect), \
                    patch.object(fleet_run.subprocess, "run",
                              return_value=SimpleNamespace(stdout="fixture-head\n")), \
                    contextlib.redirect_stdout(io.StringIO()):
                result = fleet_run.execute(root, brief, pointer, "test", "test", command)
            self.assertEqual(result, 7)
            log_path = Path(pointer.read_text(encoding="utf-8").splitlines()[1])
            logged = log_path.read_text(encoding="utf-8").splitlines()
            self.assertEqual(logged[:3], lines[:3])
            self.assertNotIn(lines[3], logged)
            self.assertEqual(len(logged[3]), 400)
            record = json.loads((log_path.parent / "record.json").read_text())
            # a worker that dies at once having worked on nothing is aborted:
            # its targets must not cool down (eligibility.recent_run_rvas)
            self.assertEqual(record["status"], "aborted")
            self.assertEqual(record["touched"], [])
            self.assertTrue(fleet_run.aborted(record))
            self.assertEqual(record["exit_code"], 7)
            with contextlib.closing(original_connect(root)) as database:
                self.assertEqual(database.execute("SELECT rva FROM claims").fetchall(), [])


class TouchedTests(unittest.TestCase):
    def test_tools_mark_the_bodies_a_run_worked_on(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            (directory / "record.json").write_text("{}", encoding="utf-8")
            with patch.dict(fleet_run.os.environ, {"BFME_RUN_DIR": str(directory)}):
                fleet_run.mark_touched(0x123456)
                fleet_run.mark_touched("0x00123456")
                fleet_run.mark_touched("not hex")          # never raises
            self.assertEqual(fleet_run.touched_rvas(directory), ["0x00123456"])
            touched = dict(status="finished", exit_code=1, seconds=5, touched=["0x00123456"])
            self.assertFalse(fleet_run.aborted(touched))   # it failed, but it worked first
            self.assertFalse(fleet_run.aborted(dict(status="finished", exit_code=0, seconds=5)))
            self.assertFalse(fleet_run.aborted(dict(status="finished", exit_code=1, seconds=4000)))

    def test_without_a_run_nothing_is_written(self):
        with patch.dict(fleet_run.os.environ, {}, clear=False):
            fleet_run.os.environ.pop("BFME_RUN_DIR", None)
            fleet_run.mark_touched(0x10)                    # manual use: no-op


class LeaseTests(unittest.TestCase):
    """Expired claims need a terminal record as well as a dead PID."""

    def _root(self, stack):
        temporary = stack.enter_context(tempfile.TemporaryDirectory())
        return Path(temporary)

    def test_cgroupless_terminal_claim_stays_busy_and_empty_contained_claim_reclaims(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            targets = [("0x00123456", 2)]
            fleet_run.claim(root, "run-a", targets, pid=None, lease=10)
            with self.assertRaises(RuntimeError):
                fleet_run.claim(root, "run-b", targets, pid=None, lease=10)
            self.assertEqual(fleet_run.active_rvas(root), {"0x00123456"})
            # expired but pid unknown: still live (never reclaim what we cannot check)
            fleet_run.claim(root, "run-c", [("0x00000010", 1)], pid=None, lease=-5)
            self.assertIn("0x00000010", fleet_run.active_rvas(root))

            # A terminal record and dead direct PID cannot prove that an
            # uncontained descendant stopped.
            record = root / "build" / "fleet_runs" / "run-d"
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"status": "finished"}), encoding="utf-8")
            fleet_run.claim(root, "run-d", [("0x00000020", 1)], pid=999999, lease=-5)
            with patch.object(fleet_run, "pid_alive", return_value=False):
                self.assertIn("0x00000020", fleet_run.active_rvas(root))
                with self.assertRaises(RuntimeError):
                    fleet_run.claim(root, "run-e", [("0x00000020", 1)], pid=None, lease=10)

            # A positive empty cgroup is the evidence that permits takeover,
            # and the direct PID must also be absent.
            cgroup_path = "/delegated/bfme-fleet-run-f"
            record = root / "build" / "fleet_runs" / "run-f"
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"id": "run-f", "status": "running", "pid": 999999,
                            "cgroup_path": cgroup_path}), encoding="utf-8")
            fleet_run.claim(root, "run-f", [("0x00000030", 1)], pid=999999,
                            lease=-5, cgroup_path=cgroup_path)
            with patch.object(fleet_run, "cgroup_state", return_value=False):
                self.assertNotIn("0x00000030", fleet_run.active_rvas(root))
                fleet_run.claim(root, "run-g", [("0x00000030", 1)], pid=None, lease=10)
            with contextlib.closing(fleet_run.connect(root)) as db:
                owner = db.execute("SELECT run FROM claims WHERE rva='0x00000030'").fetchone()[0]
                reasons = [r[0] for r in db.execute("SELECT reason FROM releases")]
            self.assertEqual(owner, "run-g")
            self.assertTrue(any("lease expired" in r for r in reasons))

            # A live recorded PID blocks reclaim even if the unit appears empty.
            record = root / "build" / "fleet_runs" / "run-live-contained"
            record.mkdir(parents=True)
            cgroup_path = "/delegated/bfme-fleet-run-live-contained"
            (record / "record.json").write_text(
                json.dumps({"id": "run-live-contained", "status": "running",
                            "pid": os.getpid(), "cgroup_path": cgroup_path}), encoding="utf-8")
            fleet_run.claim(root, "run-live-contained", [("0x00000031", 1)],
                            pid=os.getpid(), lease=-5,
                            cgroup_path=cgroup_path)
            with patch.object(fleet_run, "cgroup_state", return_value=False):
                self.assertIn("0x00000031", fleet_run.active_rvas(root))

            # PID=None is releasable only for a verifiable prelaunch record
            # with no PID written before the bootstrap gate opened.
            record = root / "build" / "fleet_runs" / "run-prelaunch"
            record.mkdir(parents=True)
            cgroup_path = "/delegated/bfme-fleet-run-prelaunch"
            (record / "record.json").write_text(
                json.dumps({"id": "run-prelaunch", "status": "starting",
                            "cgroup_path": cgroup_path, "touch_tracking": True,
                            "launch_phase": "preexec"}), encoding="utf-8")
            fleet_run.claim(root, "run-prelaunch", [("0x00000032", 1)],
                            pid=None, lease=-5,
                            cgroup_path=cgroup_path)
            with patch.object(fleet_run, "cgroup_state", return_value=False):
                self.assertNotIn("0x00000032", fleet_run.active_rvas(root))

    def test_expired_terminal_record_does_not_override_unknown_pid(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            stack.enter_context(contextlib.closing(fleet_run.connect(root)))
            record = root / "build" / "fleet_runs" / "failed-unknown"
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"status": "failed"}), encoding="utf-8")
            fleet_run.claim(root, "failed-unknown", [("0x00000021", 1)],
                            pid=None, lease=-5)
            self.assertIn("0x00000021", fleet_run.active_rvas(root))
            with self.assertRaises(RuntimeError):
                fleet_run.claim(root, "replacement", [("0x00000021", 1)],
                                pid=None, lease=10)

    def test_expired_nonterminal_records_stay_busy_after_pid_exit(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            stack.enter_context(contextlib.closing(fleet_run.connect(root)))
            with patch.object(fleet_run, "pid_alive", return_value=False):
                for index, status in enumerate(("starting", "interrupted")):
                    run = "old-" + status
                    record = root / "build" / "fleet_runs" / run
                    record.mkdir(parents=True)
                    (record / "record.json").write_text(
                        json.dumps({"status": status}), encoding="utf-8")
                    target = [(f"0x{0x30 + index:08x}", 1)]
                    fleet_run.claim(root, run, target, pid=999999, lease=-5)
                    self.assertIn(target[0][0], fleet_run.active_rvas(root))
                    with self.assertRaises(RuntimeError):
                        fleet_run.claim(root, "replacement-" + status, target,
                                        pid=None, lease=10)

    def test_expired_terminal_record_does_not_override_live_pid(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            stack.enter_context(contextlib.closing(fleet_run.connect(root)))
            record = root / "build" / "fleet_runs" / "run-live"
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"status": "finished"}), encoding="utf-8")
            fleet_run.claim(root, "run-live", [("0x00000022", 1)],
                            pid=os.getpid(), lease=-5)
            self.assertIn("0x00000022", fleet_run.active_rvas(root))
            with self.assertRaises(RuntimeError):
                fleet_run.claim(root, "replacement", [("0x00000022", 1)],
                                pid=None, lease=10)

    def test_live_pid_blocks_release_even_when_cgroup_looks_empty(self):
        self.assertTrue(fleet_run.pid_alive(os.getpid()))
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            fleet_run.connect(root).close()
            run = "run-f"
            cgroup_path = f"/delegated/bfme-fleet-{run}"
            record = root / "build" / "fleet_runs" / run
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"status": "running", "pid": os.getpid(),
                            "cgroup_path": cgroup_path}), encoding="utf-8")
            fleet_run.claim(root, run, [("0x00000030", 1)], pid=os.getpid(),
                            lease=-5, cgroup_path=cgroup_path)
            with patch.object(fleet_run, "cgroup_state", return_value=False):
                self.assertIn("0x00000030", fleet_run.active_rvas(root))
                with self.assertRaisesRegex(fleet_run.ClaimConflict, "PID is alive"):
                    fleet_run.release(root, run, "test")
                self.assertEqual(fleet_run.active_rvas(root), {"0x00000030"})

    def test_claim_record_cgroup_mismatch_stays_busy_and_cannot_release(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            fleet_run.connect(root).close()
            run = "run-mismatch"
            record_cgroup = f"/delegated/bfme-fleet-{run}"
            claim_cgroup = "/delegated/bfme-fleet-other-owner"
            record = root / "build" / "fleet_runs" / run
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"id": run, "status": "finished", "pid": 999999,
                            "cgroup_path": record_cgroup}), encoding="utf-8")
            fleet_run.claim(root, run, [("0x00000033", 1)], pid=999999,
                            lease=-5, cgroup_path=claim_cgroup)
            with patch.object(fleet_run, "cgroup_state", return_value=False), \
                    patch.object(fleet_run, "pid_alive", return_value=False):
                self.assertIn("0x00000033", fleet_run.active_rvas(root))
                with self.assertRaisesRegex(fleet_run.ClaimConflict, "paths differ"):
                    fleet_run.release(root, run, "test")
                self.assertEqual(fleet_run.active_rvas(root), {"0x00000033"})

    def test_release_rejects_missing_record_containment_for_claim(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            fleet_run.connect(root).close()
            run = "run-no-record-unit"
            record = root / "build" / "fleet_runs" / run
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"id": run, "status": "finished", "pid": 999999}),
                encoding="utf-8")
            fleet_run.claim(root, run, [("0x00000034", 1)], pid=999999,
                            lease=-5, cgroup_path=f"/delegated/bfme-fleet-{run}")
            with patch.object(fleet_run, "cgroup_state", return_value=False), \
                    patch.object(fleet_run, "pid_alive", return_value=False):
                with self.assertRaisesRegex(fleet_run.ClaimConflict, "paths differ"):
                    fleet_run.release(root, run, "test")
                self.assertEqual(fleet_run.active_rvas(root), {"0x00000034"})

    def test_release_rejects_legacy_claim_with_contained_record(self):
        with contextlib.ExitStack() as stack:
            root = self._root(stack)
            fleet_run.connect(root).close()
            run = "run-record-only-unit"
            record = root / "build" / "fleet_runs" / run
            record.mkdir(parents=True)
            (record / "record.json").write_text(
                json.dumps({"id": run, "status": "finished", "pid": 999999,
                            "cgroup_path": f"/delegated/bfme-fleet-{run}"}),
                encoding="utf-8")
            fleet_run.claim(root, run, [("0x00000035", 1)], pid=999999,
                            lease=-5, cgroup_path=None)
            with patch.object(fleet_run, "cgroup_state", return_value=False), \
                    patch.object(fleet_run, "pid_alive", return_value=False):
                with self.assertRaisesRegex(fleet_run.ClaimConflict, "paths differ"):
                    fleet_run.release(root, run, "test")
                self.assertEqual(fleet_run.active_rvas(root), {"0x00000035"})


class LegacyAndTimeoutTests(unittest.TestCase):
    def test_legacy_claim_without_pid_needs_explicit_release(self):
        with contextlib.ExitStack() as stack:
            root = Path(stack.enter_context(tempfile.TemporaryDirectory()))
            with contextlib.closing(fleet_run.connect(root)) as db, db:
                db.execute("INSERT INTO claims (rva, run, started) VALUES ('0x00000040','old-run',0)")
            # No record cannot prove death; an ambiguous old claim stays busy.
            self.assertEqual(fleet_run.active_rvas(root), {"0x00000040"})
            rec = root / "build" / "fleet_runs" / "old-run"
            rec.mkdir(parents=True)
            (rec / "record.json").write_text(json.dumps({"status": "running"}), encoding="utf-8")
            self.assertEqual(fleet_run.active_rvas(root), {"0x00000040"})
            (rec / "record.json").write_text(json.dumps({"status": "interrupted"}), encoding="utf-8")
            self.assertEqual(fleet_run.active_rvas(root), {"0x00000040"})
            (rec / "record.json").write_text(json.dumps({"status": "finished"}), encoding="utf-8")
            # A terminal record alone cannot prove a detached child stopped.
            self.assertEqual(fleet_run.active_rvas(root), {"0x00000040"})
            with self.assertRaises(fleet_run.ClaimConflict):
                fleet_run.claim(root, "new-run", [("0x00000040", 1)])
            with self.assertRaisesRegex(fleet_run.ClaimConflict, "stopped-fleet"):
                fleet_run.release(root, "old-run", "worker independently verified stopped")
            with self.assertRaisesRegex(fleet_run.ClaimConflict, "state changed"):
                fleet_run.release(root, "old-run", "worker independently verified stopped",
                                  stopped_fleet=True, expected_state_sha="wrong")
            report = fleet_run.coordination_status(root)
            fleet_run.release(root, "old-run", "worker independently verified stopped",
                              stopped_fleet=True,
                              expected_state_sha=report["snapshot_sha256"])
            self.assertEqual(fleet_run.active_rvas(root), set())

    def test_timeout_prefix_is_stripped_and_parsed(self):
        cmd, cap, kill = fleet_run.strip_timeout(["timeout", "-k", "60", "2700", "codex", "exec"])
        self.assertEqual((cmd, cap, kill), (["codex", "exec"], 2700.0, 60.0))
        cmd, cap, kill = fleet_run.strip_timeout(["timeout", "45m", "prog"])
        self.assertEqual((cmd, cap, kill), (["prog"], 2700.0, None))
        self.assertEqual(fleet_run.strip_timeout(["python", "-c", "1"]), (["python", "-c", "1"], None, None))

    def test_cap_kills_a_runaway_worker(self):
        require_cgroup_v2(self)
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            open_ledger(root, (0x00123457, 2))
            brief = root / "brief.txt"
            brief.write_text("TARGETS" + chr(10) + "- 0x00123457 2B" + chr(10), encoding="utf-8")
            command = ["timeout", "-k", "1", "2", sys.executable, "-c",
                       "import time; print('started', flush=True); time.sleep(60)"]
            head = SimpleNamespace(stdout="fixture-head")
            with patch.object(fleet_run.subprocess, "run", return_value=head), contextlib.redirect_stdout(io.StringIO()):
                started = __import__("time").time()
                fleet_run.execute(root, brief, root / "latest.log", "test", "test", command)
                elapsed = __import__("time").time() - started
            self.assertLess(elapsed, 30)
            record = json.loads(next((root / "build" / "fleet_runs").glob("*/record.json")).read_text())
            self.assertTrue(record.get("timed_out"))
            self.assertEqual(record["cap_seconds"], 2.0)


class BriefOverStdinTests(unittest.TestCase):
    def test_brief_argument_is_replaced_by_stdin(self):
        require_cgroup_v2(self)
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            open_ledger(root, (0x00123458, 2))
            brief = root / "brief.txt"
            text = "TARGETS" + chr(10) + "- 0x00123458 2B" + chr(10) + "x" * 20000 + chr(10)
            brief.write_text(text, encoding="utf-8")
            command = [sys.executable, "-c",
                       "import sys; d=sys.stdin.read(); print('stdin-bytes', len(d)); print('argv', sys.argv[1])", text]
            head = SimpleNamespace(stdout="fixture-head")
            with patch.object(fleet_run.subprocess, "run", return_value=head), contextlib.redirect_stdout(io.StringIO()):
                fleet_run.execute(root, brief, root / "latest.log", "test", "test", command)
            log = next((root / "build" / "fleet_runs").glob("*/output.log")).read_text(encoding="utf-8")
            self.assertIn("stdin-bytes " + str(len(text.encode("utf-8"))), log)
            self.assertIn("argv -", log)
