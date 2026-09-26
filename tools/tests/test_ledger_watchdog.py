"""The watchdog must execute ledger checks from either supported location."""
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]


class WatchdogLocationTests(unittest.TestCase):
    def test_active_draft_is_not_repaired(self):
        with tempfile.TemporaryDirectory() as tmp:
            repo = Path(tmp)
            (repo / "tools/fleet").mkdir(parents=True)
            (repo / "targets/game/reverse/attempts").mkdir(parents=True)
            (repo / "tools/check_csv.py").write_text("", encoding="utf-8")
            for helper in ("ledger_io.py", "portable_lock.py"):
                (repo / "tools" / helper).write_text("", encoding="utf-8")
            (repo / "tools/eligibility.py").write_text(
                "def busy_rvas(root): return {'0x003e8e10'}\n", encoding="utf-8")
            draft = repo / "targets/game/reverse/attempts/0x003e8e10.cpp"
            content = b"// unfinished active draft\nvoid candidate() {}\n"
            draft.write_bytes(content)
            target = repo / "tools/fleet/ledger_watchdog.py"
            shutil.copy2(ROOT / "tools/fleet/ledger_watchdog.py", target)
            result = subprocess.run(
                [sys.executable, str(target), "--once"], cwd=repo,
                capture_output=True, text=True,
            )
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(draft.read_bytes(), content)

    def test_tracked_and_deployed_watchdog_check_the_repository(self):
        for location in ("tools/fleet", "build"):
            with self.subTest(location=location), tempfile.TemporaryDirectory() as tmp:
                repo = Path(tmp)
                (repo / "tools").mkdir()
                (repo / "tools/check_csv.py").write_text(
                    "from pathlib import Path\n"
                    "Path('checked.txt').write_text('checked')\n",
                    encoding="utf-8",
                )
                for helper in ("ledger_io.py", "portable_lock.py"):
                    (repo / "tools" / helper).write_text("", encoding="utf-8")
                target = repo / location / "ledger_watchdog.py"
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(ROOT / "tools/fleet/ledger_watchdog.py", target)
                result = subprocess.run(
                    [sys.executable, str(target), "--once"],
                    cwd=repo, capture_output=True, text=True,
                )
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertTrue((repo / "checked.txt").exists(), result.stderr)


if __name__ == "__main__":
    unittest.main()
