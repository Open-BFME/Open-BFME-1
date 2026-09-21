"""Operator instructions must name scripts and lanes that exist.

Picker docstrings said `python build/pick_*.py` long after seat.sh moved to the
tracked tools/fleet copies, and launch_fleet.sh never launched the class lane
the README recommends. A worker pays for every instruction that is wrong.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
FLEET = ROOT / "tools" / "fleet"
SCRIPT = re.compile(r"python3?\s+((?:tools|build)/[\w/.-]+\.py)")


def fleet_texts():
    for path in sorted(FLEET.glob("*.py")) + sorted(FLEET.glob("*.sh")) + [FLEET / "README.md"]:
        yield path, path.read_text(encoding="utf-8", errors="replace")


def test_every_script_an_instruction_runs_exists():
    # build/ is untracked scratch: a copy there exists on the host that made it
    # and nowhere else, so an instruction naming one is wrong even when it runs
    missing = [(path.name, script) for path, text in fleet_texts()
               for script in set(SCRIPT.findall(text))
               if script.startswith("build/") or not (ROOT / script).exists()]
    assert not missing, missing


def test_no_instruction_points_at_the_retired_build_copies():
    stale = [path.name for path, text in fleet_texts() if re.search(r"python3?\s+build/pick_", text)]
    assert not stale, stale


def test_retired_claim_files_are_not_used():
    # leases + the touched cooldown replaced append-only claim files; a picker
    # that still reads one excludes its bodies for ever
    users = [path.name for path in FLEET.glob("pick_*.py")
             if re.search(r"fleet_\w+_claimed\.txt['\"]", path.read_text(encoding="utf-8"))]
    assert not users, users


def test_launcher_starts_every_lane_the_seat_documents():
    seat = (FLEET / "seat.sh").read_text(encoding="utf-8")
    launcher = (FLEET / "launch_fleet.sh").read_text(encoding="utf-8")
    documented = set(re.findall(r"^#\s+(luna[a-z]+)\s+->", seat, re.M))
    launched = set(re.findall(r"launch (luna[a-z]*) ", launcher))
    assert documented and documented <= launched, sorted(documented - launched)


def test_readme_lists_every_picker():
    readme = (FLEET / "README.md").read_text(encoding="utf-8")
    missing = [p.name for p in FLEET.glob("pick_*.py") if p.name not in readme]
    assert not missing, missing
