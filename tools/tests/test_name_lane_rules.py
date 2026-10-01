"""The naming lane's landing rule."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane  # noqa: E402


def test_two_vendors_land_an_uncontested_name():
    assert name_lane.wins({"claude-fable", "grok"}, [])


def test_one_vendor_never_lands_a_name():
    assert not name_lane.wins({"claude-opus", "claude-fable"}, [])


def test_a_contested_name_needs_a_two_vote_lead():
    # DoXfer: Fable and Grok agreed while Opus had named the method differently
    assert not name_lane.wins({"claude-fable", "grok"}, [{"claude-opus"}])
    assert name_lane.wins({"claude-fable", "grok", "gpt-5.6-sol"}, [{"claude-opus"}])
