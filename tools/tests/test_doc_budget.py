#!/usr/bin/env python3
"""doc_budget refuses net doc growth, an oversized AGENTS.md and long mod READMEs."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import doc_budget as db  # noqa: E402


def test_net_growth_is_refused_and_a_paid_addition_passes():
    grown = db.problems(["docs/matching.md"], {"docs/matching.md": 700}, {"docs/matching.md": 710})
    assert len(grown) == 1 and "10 net words" in grown[0]
    paid = ["docs/matching.md", "AGENTS.md"]
    assert db.problems(paid, {"docs/matching.md": 700, "AGENTS.md": 1300},
                       {"docs/matching.md": 710, "AGENTS.md": 1290}) == []


def test_a_new_doc_counts_as_growth_and_a_deleted_one_pays_for_it():
    assert db.problems(["docs/new.md"], {}, {"docs/new.md": 50})
    assert db.problems(["docs/new.md", "docs/old.md"], {"docs/old.md": 60}, {"docs/new.md": 50}) == []


def test_catalogs_and_records_are_outside_the_budget():
    assert db.problems(["docs/shape_levers.md"], {"docs/shape_levers.md": 100},
                       {"docs/shape_levers.md": 900}) == []
    assert not db.budgeted("targets/game/reverse/analysis/0x00172600.md")


def test_agents_cap_and_mod_readme_cap():
    over = db.problems(["AGENTS.md"], {"AGENTS.md": db.AGENTS_CAP + 10}, {"AGENTS.md": db.AGENTS_CAP + 5})
    assert len(over) == 1 and "cap" in over[0]
    readme = "mods/features/033-retrytime/README.md"
    assert db.problems([readme], {}, {readme: db.MOD_README_CAP + 1})
    assert db.problems([readme], {}, {readme: db.MOD_README_CAP}) == []


def test_the_tree_is_within_its_caps():
    agents = len((ROOT / "AGENTS.md").read_text(encoding="utf-8").split())
    assert agents <= db.AGENTS_CAP, f"AGENTS.md is {agents} words"
    for readme in [ROOT / "mods/README.md", *sorted((ROOT / "mods/features").glob("*/README.md"))]:
        words = len(readme.read_text(encoding="utf-8").split())
        assert words <= db.MOD_README_CAP, f"{readme.relative_to(ROOT)} is {words} words"
