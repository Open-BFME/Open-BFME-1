"""The full gate writes reloc names under build/, never over the tracked copy.

2026-09-30: every full gate rewrote targets/game/reverse/reloc_names.csv, the
tree was dirty afterwards, and the push hook's post-gate snapshot check
refused every header-wide push. The tracked copy now changes only through
`tools/reloc_names.py promote` in a separate commit.
"""
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import build  # noqa: E402
import reloc_names  # noqa: E402

ROW = {"name": "?f@@YAXXZ", "target_rva": "0x00001000", "target_size": "16",
       "source": "game/x.cpp", "notes": "reloc-derived;call-sites=2;identity=real"}
HEADER = "name,target_rva,target_size,source,notes\n"


def test_the_gate_writes_the_generated_table_and_leaves_the_tracked_copy(tmp_path, monkeypatch, capsys):
    tracked = tmp_path / "targets/game/reverse/reloc_names.csv"
    tracked.parent.mkdir(parents=True)
    tracked.write_text(HEADER, encoding="utf-8")
    before = tracked.read_bytes()
    generated = tmp_path / "build/reloc_names.generated.csv"
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "RELOC_NAMES", tracked)
    monkeypatch.setattr(build, "RELOC_NAMES_GENERATED", generated)
    monkeypatch.setattr(build, "harvest_reloc_names", lambda patches: [ROW])
    monkeypatch.setattr(build, "select_reloc_names", lambda named: named)
    build.write_reloc_names([])
    assert tracked.read_bytes() == before                      # the tree stays clean
    assert "?f@@YAXXZ" in generated.read_text(encoding="utf-8")
    assert "reloc_names.py promote" in capsys.readouterr().out


def test_the_generated_table_is_not_tracked():
    assert build.RELOC_NAMES_GENERATED.parts[-2] == "build"
    assert build.RELOC_NAMES != build.RELOC_NAMES_GENERATED


def test_promote_copies_the_generated_table_explicitly(tmp_path, monkeypatch):
    tracked = tmp_path / "reloc_names.csv"
    generated = tmp_path / "reloc_names.generated.csv"
    monkeypatch.setattr(reloc_names, "TRACKED", tracked)
    monkeypatch.setattr(reloc_names, "GENERATED", generated)
    monkeypatch.setattr(reloc_names, "ROOT", tmp_path)
    assert reloc_names.main(["status"]) == 1                     # no gate output yet
    tracked.write_text(HEADER, encoding="utf-8")
    generated.write_text(HEADER + ",".join(ROW.values()) + "\n", encoding="utf-8")
    assert reloc_names.diff() == (1, 0)
    assert reloc_names.main(["status"]) == 0 and tracked.read_text() == HEADER
    assert reloc_names.main(["promote"]) == 0
    assert tracked.read_bytes() == generated.read_bytes()
