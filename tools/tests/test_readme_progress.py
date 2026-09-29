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
        assert "**Rebuilt from source: 60.00%**" in payload["embeds"][0]["description"]
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
    assert ">linked<" in svg and ">byte-matched<" in svg and "72.73" not in svg
    with pytest.raises(ValueError):
        daily.render(sample(linked=61))


def test_discord_posts_three_measures_and_links_the_readme():
    # game's own code = 100 - 5 vendored - 5 library = 90; our C++ 40; 9 of it links.
    current = {**sample(), "linked_authored": 9}
    previous = {"total": 100, "matched_total": 55, "game_total": 90, "cpp_total": 40, "linked_game_total": 9}
    embed = daily.announcement(current, previous)["embeds"][0]
    L, M, C, R = daily.LINKED_BLOCK, daily.MATCHED_BLOCK, daily.CPP_BLOCK, daily.REST_BLOCK
    assert embed["description"].split("\n") == [
        "**Rebuilt from source: 60.00%**  \u25b2 5.00",
        f"{M * 6}{R * 4}",
        "60 / 100 bytes rebuilt without copying the original game exe (v1.03)",
        "",
        "**Game code in C++: 44.44%**",
        f"{C * 4}{R * 6}",
        "40 / 90 bytes of the game's own code, now C++ (libraries not counted)",
        "",
        "**Linking: 10.00%**",
        f"{L * 1}{R * 9}",
        "9 / 90 bytes of the game's own code linked (not measured yet)",
        "",
        f"[What each bar measures, with charts: README]({daily.README})"]
    assert "footer" not in embed and "Whole game" not in embed["description"]


def test_discord_linking_without_a_census_figure_says_so():
    lines = daily.announcement(sample(), None)["embeds"][0]["description"].split("\n")
    assert "**Linking:** not measured yet" in lines
    with pytest.raises(ValueError):
        daily.announcement({**sample(), "linked_authored": 41}, None)  # more linked than written


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
    assert daily.whole(100, 100) == 100  # only everything matched and linked is the whole game


def test_discord_change_needs_the_same_denominator():
    current = {**sample(), "linked_authored": 9}
    moved = {"total": 100, "matched_total": 60, "game_total": 90, "cpp_total": 36, "linked_game_total": 9}
    lines = daily.announcement(current, moved)["embeds"][0]["description"].split("\n")
    assert lines[4] == "**Game code in C++: 44.44%**  \u25b2 4.44" and lines[0].endswith("60.00%**")
    rebased = {**moved, "game_total": 91}  # vendored/library split moved: not comparable
    assert "\u25b2" not in daily.announcement(current, rebased)["embeds"][0]["description"]
