"""Persistent progress message behavior; no network requests."""
import io
import json
import re
import sys
from pathlib import Path
from urllib.error import URLError

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import readme_progress as daily


def sample(linked=10):
    return {"total": 100, "linked": linked,
            "authored": 40, "vendored": 5, "generated": 10, "library": 5,
            "census": None}


def setup_state(tmp_path, monkeypatch, state=None):
    (tmp_path / "docs").mkdir()
    monkeypatch.setattr(daily.progress, "ROOT", tmp_path)
    path = tmp_path / "docs/discord-main-progress.json"
    if state:
        path.write_text(json.dumps(state), encoding="utf-8")
    return path


def payload_of(request):
    return json.loads(request.data)


def test_retry_does_not_duplicate_post(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "run-123")
    state = {"rebuilt": 50, "total": 100, "message_id": "123", "run_id": "run-123"}
    setup_state(tmp_path, monkeypatch, state)
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    daily.notify(sample())


def test_success_posts_the_bars_and_disables_mentions(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token\n")

    def send(request, timeout):
        assert request.full_url.endswith("token?wait=true")
        payload = payload_of(request)
        assert payload["allowed_mentions"] == {"parse": []}
        assert "**60.00%**  Byte-matched" in payload["embeds"][0]["description"]
        return io.BytesIO(b'{"id":"123"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify(sample())
    assert json.loads(path.read_text())["message_id"] == "123"


@pytest.mark.parametrize("previous_count", [40, 50])
def test_each_run_posts_new_message_even_if_unchanged(tmp_path, monkeypatch, previous_count):
    monkeypatch.setenv("GITHUB_RUN_ID", "new-run")
    path = setup_state(tmp_path, monkeypatch, {"rebuilt": previous_count, "total": 100, "message_id": "123", "run_id": "old-run"})
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")

    def send(request, timeout):
        assert request.method == "POST"
        assert request.full_url.endswith("?wait=true")
        return io.BytesIO(b'{"id":"456"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify(sample())
    assert json.loads(path.read_text())["linked_total"] == 10
    assert json.loads(path.read_text())["message_id"] == "456"


def test_failed_post_does_not_advance_state_or_leak_url(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/secret")

    def fail(*args, **kwargs):
        raise URLError("secret")
    monkeypatch.setattr(daily, "urlopen", fail)
    with pytest.raises(SystemExit, match="^Discord update failed: connection error$"):
        daily.notify(sample())
    assert not path.exists()


def test_change_is_percentage_points_and_only_shown_when_it_moved():
    previous = {"total": 100, "matched_total": 55, "linked_total": 10}
    svg = daily.render(sample(), previous)
    assert svg.count(">\u25b2 5.00<") == 1  # byte-matched moved; linked did not
    dropped = daily.render(sample(), {"total": 100, "matched_total": 61, "linked_total": 10})
    assert 'class="down"' in dropped and ">\u25bc 1.00<" in dropped
    assert "\u25b2" not in daily.render(sample(), {"total": 99, "matched_total": 55, "linked_total": 1})


def test_card_follows_the_github_theme_and_states_both_definitions():
    svg = daily.render(sample())
    assert "prefers-color-scheme: light" in svg
    assert all(text in svg for text in daily.DEFINITIONS)


def test_whole_game_bar_ends_at_its_number_and_its_parts_add_up_to_100():
    # 60% byte-matched, 10% linked: linked 10 + matched-only 50 at half = 35; 65 steps to do.
    svg = daily.render(sample())
    assert "BFME 1: 60.00% byte-matched, 10.00% linked" in svg
    assert 'width="{:.2f}" height="18" fill="{}"'.format(824 * 0.35, daily.MATCHED) in svg
    assert "linked 10.00%" in svg and "byte-matched, not linked yet 50.00%" in svg
    with pytest.raises(ValueError):
        daily.render(sample(linked=61))


def test_discord_draws_the_cards_three_bars_in_green_blocks():
    previous = {"total": 100, "matched_total": 55, "linked_total": 10}
    embed = daily.announcement(sample(), previous)["embeds"][0]
    L, M, R = daily.LINKED_BLOCK, daily.MATCHED_BLOCK, daily.REST_BLOCK
    assert embed["description"].split("\n") == [
        f"{M * 6}{R * 4}  **60.00%**  Byte-matched  \u25b2 5.00",
        f"{L * 1}{R * 9}  **10.00%**  Code linked",
        f"{L * 1}{M * 3}{R * 6}  **35.00%**  Whole game",
        f"{L} linked 10.00%  \u00b7  {M} byte-matched, not linked yet 50.00%",
        f"[Full progress report: chart and map]({daily.REPORT})"]
    assert "footer" not in embed  # no definitions, no extra measures: the card and the report have them


@pytest.mark.parametrize("parts", [[(1, 0)], [(1, 1), (2, 1)], [(1, 33), (2, 34)], [(2, 100)], [(1, 49), (2, 1)],
                                   [(1, 4), (2, 1)], [(1, 96), (2, 4)]])
def test_blocks_always_fill_exactly_ten(parts):
    L, M = daily.LINKED_BLOCK, daily.MATCHED_BLOCK
    text = daily.blocks([(L if kind == 1 else M, value) for kind, value in parts], 100)
    assert sum(text.count(b) for b in (L, M, daily.REST_BLOCK)) == 10


def test_nothing_claims_the_game_is_100_percent_done():
    previous = {"total": 100, "matched_total": 55, "linked_total": 10}
    text = daily.announcement(sample(), previous)["embeds"][0]["description"] + daily.render(sample(), previous)
    assert "100%" not in text


def test_whole_game_counts_two_steps_per_byte():
    # 60% byte-matched, 10% linked: 70 of 200 steps done.
    svg = daily.render(sample())
    assert ">35.00%<" in svg
    previous = {"total": 100, "matched_total": 55, "linked_total": 10, "whole_total": 32.5}
    embed = daily.announcement(sample(), previous)["embeds"][0]
    assert "**35.00%**  Whole game  \u25b2 2.50" in embed["description"]
    assert daily.whole(100, 100) == 100  # only everything matched and linked is the whole game

