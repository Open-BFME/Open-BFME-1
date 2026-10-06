#!/usr/bin/env python3
"""tools/model_routing.py: measured success per task class and routing cutoffs."""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import model_routing  # noqa: E402

CONFIG = {
    "success": ["landed", "converted"], "failure": ["blocked", "partial", "no-match"],
    "min_attempts": 10, "floor": 0.05,
    "classes": [{"name": "small", "max_size": 100, "prefer": "cheap"},
                {"name": "large", "max_size": None, "models": ["strong"]}],
    "aliases": {"strong-1": "strong"}, "cost": {"cheap": 1, "strong": 5},
}


def write_log(tmp_path, rows):
    path = tmp_path / "re_attempts.log"
    path.write_text("".join(f"sym{i}\t0x{i:08X}\t{size}\t{status}\t{note}\n"
                            for i, (size, status, note) in enumerate(rows)), encoding="utf-8")
    return path


def test_rates_cutoff_and_preference(tmp_path):
    rows = ([(50, "blocked", "x t=3 model=dud")] * 40              # 0/40: cut
            + [(50, "landed", "t=2 model=cheap")] * 8 + [(50, "blocked", "model=cheap")] * 4
            + [(50, "landed", "model=strong-1 t=9")] * 3            # 3/3, below min_attempts
            + [(50, "refuted", "model=dud")] * 50                   # boundary finding: nobody's
            + [(50, "landed", "no model field")])
    stats = model_routing.table(model_routing.outcomes(write_log(tmp_path, rows), CONFIG))
    assert stats[("small", "dud")]["n"] == 40
    assert stats[("small", "cheap")]["wins"] == 8 and stats[("small", "cheap")]["median_t"] == 2
    assert ("small", "strong") in stats  # alias folded
    keep, trial, cut = model_routing.route("small", stats, CONFIG)
    assert "dud" in cut and "dud" not in keep
    assert keep == ["cheap", "strong"]  # cheap class: cost first; strong is a known model


def test_few_attempts_never_trip_the_floor(tmp_path):
    rows = [(50, "blocked", "model=newbie")] * 9
    stats = model_routing.table(model_routing.outcomes(write_log(tmp_path, rows), CONFIG))
    keep, trial, cut = model_routing.route("small", stats, CONFIG)
    assert trial == ["newbie"] and "newbie" not in keep and not cut


def test_large_class_is_allowlisted(tmp_path):
    rows = [(5000, "landed", "model=cheap")] * 20
    stats = model_routing.table(model_routing.outcomes(write_log(tmp_path, rows), CONFIG))
    keep, _, _ = model_routing.route("large", stats, CONFIG)
    assert keep == ["strong"]


def test_campaign_suffixes_fold_into_the_model():
    assert model_routing.canonical("gpt-5.6-luna;campaign=x;lane=mid", CONFIG) == "gpt-5.6-luna"
    assert model_routing.canonical("Strong-1.", CONFIG) == "strong"


def test_runner_field_beats_self_declared_model(tmp_path):
    rows = [(50, "landed", "model=claimed runner=actual")]
    out = model_routing.outcomes(write_log(tmp_path, rows), CONFIG)
    assert out[0][1] == "actual"


def test_judges_come_only_from_the_protected_list(tmp_path):
    assert model_routing.judge_allowed("claude-opus-5-5", tmp_path / "absent.json")
    assert not model_routing.judge_allowed("muse-spark", tmp_path / "absent.json")
    judges = tmp_path / "judges.json"
    judges.write_text(json.dumps({"judges": ["gpt-6.1-sol"]}), encoding="utf-8")
    assert model_routing.judge_allowed("GPT-6.1-sol", judges)
    assert not model_routing.judge_allowed("claude-opus-5-5", judges)


def test_wilson_lower_bound():
    assert model_routing.wilson_lower(0, 0) == 0.0
    assert model_routing.wilson_lower(3, 3) < 0.5 < model_routing.wilson_lower(300, 300)


def test_shipped_config_routes_every_class():
    config = model_routing.load_config()
    for band in config["classes"]:
        keep, _, _ = model_routing.route(band["name"], {}, config)
        assert keep or "*" in band.get("models", ["*"])
