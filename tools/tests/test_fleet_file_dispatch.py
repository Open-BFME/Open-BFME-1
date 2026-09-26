"""The file picker must not serve a file that its matching brief cannot use."""
import csv
import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest

ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools"
PICKER = TOOLS / "fleet/pick_file.py"


def _fixture(root, *, dead=0, oversized=0):
    (root / "targets/game/reverse").mkdir(parents=True)
    (root / "build/fleet_logs").mkdir(parents=True)
    (root / "build/fleet_logs/seats.log").write_text("")
    (root / "targets/game/reverse/symbols.csv").write_text("name,address,notes\n")
    (root / "tools").mkdir()
    # This is the production entry point, copied only so its ROOT is the
    # temporary fixture. Imports still resolve to the checked-out tools.
    shutil.copy2(TOOLS / "brief.py", root / "tools/brief.py")
    with (root / "targets/game/reverse/functions.csv").open("w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(("name", "export_rva", "target_rva", "target_size",
                         "source", "status", "notes"))
        for index in range(12):
            rva = 0x1000 + index * 0x10
            size = 2501 if index < oversized else 100
            writer.writerow((f"?d_{rva:08x}@@YAXXZ", "", f"0x{rva:08X}", size,
                             "game/gen_asm/retired.asm", "matched", "gen-dump"))
    (root / "targets/game/reverse/re_attempts.log").write_text("".join(
        f"?d_{0x1000 + index * 0x10:08x}@@YAXXZ\t"
        f"0x{0x1000 + index * 0x10:08X}\t100\tno-match\trefuted boundary\n"
        for index in range(dead)))
    return dict(os.environ, PYTHONPATH=str(TOOLS))


def _pick(root, env):
    return subprocess.run([sys.executable, str(PICKER), "12", "2500"],
                          cwd=root, env=env, capture_output=True, text=True,
                          check=True).stdout.strip()


@pytest.mark.parametrize("dead,oversized", [(12, 0), (0, 12), (1, 0)])
def test_file_picker_uses_live_briefable_body_count(tmp_path, dead, oversized):
    env = _fixture(tmp_path, dead=dead, oversized=oversized)
    assert _pick(tmp_path, env) == ""
    assert (tmp_path / "build/fleet_logs/seats.log").read_text() == ""


def test_rejected_file_would_make_real_brief_fail(tmp_path):
    env = _fixture(tmp_path, dead=12)
    brief = subprocess.run(
        [sys.executable, str(tmp_path / "tools/brief.py"), "--dump",
         "game/gen_asm/retired.asm", "--limit", "40", "--max-size", "2500"],
        cwd=tmp_path, env=env, capture_output=True, text=True)
    assert brief.returncode != 0
    assert "brief: no live dump targets" in brief.stderr


def test_file_with_twelve_live_bodies_remains_servable(tmp_path):
    env = _fixture(tmp_path)
    assert _pick(tmp_path, env) == "game/gen_asm/retired.asm"
    assert "seat pick selected" in (tmp_path / "build/fleet_logs/seats.log").read_text()


def test_active_file_stays_excluded_when_owned_row_is_no_longer_briefable(tmp_path):
    env = _fixture(tmp_path)
    with (tmp_path / "targets/game/reverse/functions.csv").open("a", newline="") as handle:
        csv.writer(handle).writerow(("?d_00002000@@YAXXZ", "", "0x00002000",
                                     2501, "game/gen_asm/retired.asm", "matched", "gen-dump"))
    sys.path.insert(0, str(TOOLS))
    import fleet_run
    fleet_run.claim(tmp_path, "active", [("0x00002000", 2501)])
    assert _pick(tmp_path, env) == ""


def test_alias_rows_do_not_inflate_file_body_count(tmp_path):
    env = _fixture(tmp_path)
    ledger = tmp_path / "targets/game/reverse/functions.csv"
    with ledger.open(newline="") as handle:
        rows = list(csv.reader(handle))
    rows[-1][0] = "?alias@@YAXXZ"
    rows[-1][2] = rows[-2][2]
    with ledger.open("w", newline="") as handle:
        csv.writer(handle).writerows(rows)
    assert _pick(tmp_path, env) == ""
