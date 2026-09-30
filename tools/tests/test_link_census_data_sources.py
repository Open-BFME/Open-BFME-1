"""Data providers enter the census without becoming function ledger rows."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows
import link_census as census


def test_current_data_only_providers_are_compile_inputs():
    rows = [{"name": "code", "source": "game/GameEngine/Source/Common/SmallGaps/spreadTable.cpp"}]
    before = [dict(row) for row in rows]
    sources = census.compile_sources(rows)
    assert census.ROOT / "game/GameEngine/Source/Common/Language.cpp" in sources
    assert census.ROOT / "game/GameEngine/Source/Common/GlobalData.cpp" in sources
    assert len(sources) == len(set(sources))
    assert rows == before  # Global sizes and addresses never enter function metrics.
    assert sources.count(census.ROOT / rows[0]["source"]) == 1


def test_data_objects_are_linked_once_and_checked_for_currency(monkeypatch, tmp_path):
    rows = [{"name": "code", "source": "game/shared.cpp"}]
    providers = [{"source": "game/shared.cpp"}, {"source": "game/data.cpp"}, {"source": "game/data.cpp"}]
    monkeypatch.setattr(data_rows, "load", lambda: providers)
    monkeypatch.setattr(census.build, "extract_lib_members", lambda rows: None)
    path = lambda source: tmp_path / (Path(source).stem + ".obj")
    monkeypatch.setattr(census.build, "obj_path", path)
    monkeypatch.setattr(census.build, "row_object", lambda row: path(row["source"]))
    path("shared").touch()
    path("data").touch()
    present, missing = census.objects(rows)
    assert present == [path("shared"), path("data")]
    assert missing == []
    assert census._object_sources(rows)[path("data")] == census.ROOT / "game/data.cpp"
    path("data").unlink()
    assert census.objects(rows) == ([path("shared")], [path("data")])


def test_data_provider_byte_failure_is_not_ignored(monkeypatch, tmp_path):
    monkeypatch.setattr(data_rows, "DATA_ROWS", tmp_path / "no_rows.csv")
    monkeypatch.setattr(census, "data_sources", lambda: [])
    def fail(*, compile):
        assert compile is False  # Never rebuild an object after the selected map.
        raise SystemExit("data bytes differ")
    monkeypatch.setattr(data_rows, "verify", fail)
    with pytest.raises(SystemExit, match="data bytes differ"):
        census.verify_data_objects()


def test_stale_data_provider_is_refused_before_byte_verification(monkeypatch, tmp_path):
    monkeypatch.setattr(data_rows, "DATA_ROWS", tmp_path / "no_rows.csv")
    monkeypatch.setattr(census, "data_sources", lambda: [census.ROOT / "game/data.cpp"])
    monkeypatch.setattr(census.build, "compile_is_current", lambda source, obj: False)
    monkeypatch.setattr(data_rows, "verify", lambda **kwargs: pytest.fail("reached data byte verification"))
    with pytest.raises(SystemExit, match="data provider objects are missing or stale"):
        census.verify_data_objects()
