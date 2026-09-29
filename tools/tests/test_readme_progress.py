"""README card and daily Discord post; no network requests."""
import io
import json
import sys
from pathlib import Path
from urllib.error import URLError

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import readme_progress as daily

UP = "▲"


def sample(authored=40, linked_authored=9, linked_game_code=90):
    # rebuilt 60 of 100; game's own code = 100 - 5 vendored - 5 library = 90;
    # our C++ 40; the census measured 9 of it linked, over its tree's 90.
    return {"total": 100, "linked": 12, "linked_authored": linked_authored, "linked_game_code": linked_game_code,
            "authored": authored, "vendored": 5, "generated": 50 - authored, "library": 5, "census": None}


def previous(**changes):
    """A saved post state: the figures the last post was drawn from."""
    return {**sample(), **changes, "message_id": "1", "run_id": "old"}


def setup_state(tmp_path, monkeypatch, state=None):
    (tmp_path / "docs").mkdir()
    monkeypatch.setattr(daily.progress, "ROOT", tmp_path)
    path = tmp_path / daily.STATE
    if state:
        path.write_text(json.dumps(state), encoding="utf-8")
    return path


def test_retry_does_not_duplicate_post(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "run-123")
    setup_state(tmp_path, monkeypatch, {"total": 100, "message_id": "123", "run_id": "run-123"})
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    daily.notify(sample())


def test_success_posts_the_bars_and_saves_the_figures(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token\n")

    def send(request, timeout):
        assert request.full_url.endswith("token?wait=true")
        payload = json.loads(request.data)
        assert payload["allowed_mentions"] == {"parse": []}
        assert "**Rebuilt from source: 60.00%**" in payload["embeds"][0]["description"]
        return io.BytesIO(b'{"id":"123"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify(sample())
    state = json.loads(path.read_text())
    assert state["message_id"] == "123"
    assert daily.measures(state) == daily.measures(sample())  # the next post's arrows start from these


def test_each_run_posts_new_message_even_if_unchanged(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "new-run")
    path = setup_state(tmp_path, monkeypatch, previous())
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: io.BytesIO(b'{"id":"456"}'))
    daily.notify(sample())
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


def test_discord_posts_three_measures_and_links_the_readme():
    embed = daily.announcement(sample(), previous(authored=36, generated=14))["embeds"][0]
    M, C, L = (daily.BLOCK[key] for key in ("matched", "cpp", "linked"))
    R = daily.REST_BLOCK
    assert embed["description"].split("\n") == [
        "**Rebuilt from source: 60.00%**",
        f"{M * 6}{R * 4}",
        f"60 / 100 bytes rebuilt without copying {daily.EXE}",
        "",
        f"**Game code in C++: 44.44%**  {UP} 4.44",
        f"{C * 4}{R * 6}",
        "40 / 90 bytes of the game's own code, now C++ (libraries not counted)",
        "",
        "**Linking: 10.00%**",
        f"{L * 1}{R * 9}",
        "9 / 90 bytes of the game's own code linked (not measured yet)",
        "",
        f"[What each bar measures, with charts: README]({daily.README})"]
    assert "footer" not in embed and "Whole game" not in embed["description"]


def test_card_shows_the_same_three_measures():
    svg = daily.render(sample(), previous(authored=36, generated=14))
    for text in (">Rebuilt from source<", ">60.00%<", ">Game code in C++<", ">44.44%<", ">Linking<", ">10.00%<",
                 f"60 / 100 bytes rebuilt without copying {daily.EXE}", f">{UP} 4.44<",
                 "60.00% rebuilt from source, 44.44% game code in C++, 10.00% linking"):
        assert text in svg
    assert "prefers-color-scheme: light" in svg and "Whole game" not in svg


def test_linking_is_one_census_snapshot():
    # The census tree's game code (80) is the denominator, not today's (90).
    current = sample(linked_authored=8, linked_game_code=80)
    assert daily.measures(current)["linked"] == (8, 80)
    assert "8 / 80 bytes of the game's own code linked" in daily.announcement(current, None)["embeds"][0]["description"]
    with pytest.raises(ValueError):
        daily.measures(sample(linked_game_code=None))  # bytes without their denominator
    with pytest.raises(ValueError):
        daily.measures(sample(linked_authored=91))  # more linked than there is code


def test_linking_without_a_census_figure_says_so():
    current = sample(linked_authored=None, linked_game_code=None)
    assert "**Linking:** not measured yet" in daily.announcement(current, None)["embeds"][0]["description"]
    assert ">not measured<" in daily.render(current)


def test_arrow_is_the_change_in_the_bars_percentage():
    # Linking went from 9/90 = 10.00% to 8/80 = 10.00%: same share, no arrow,
    # though the bytes and the denominator both moved.
    text = daily.announcement(sample(linked_authored=8, linked_game_code=80), previous())["embeds"][0]["description"]
    assert UP not in text and "▼" not in text
    # 9/90 -> 12/90: +3.33 points.
    assert f"**Linking: 13.33%**  {UP} 3.33" in daily.announcement(sample(linked_authored=12), previous())[
        "embeds"][0]["description"]
    # A move that rounds to 0.00 shows nothing.
    assert UP not in daily.announcement(sample(), previous(authored=39.999, generated=10.001))["embeds"][0][
        "description"]


def test_old_state_without_figures_gives_no_arrow():
    old = {"total": 100, "matched_total": 55, "message_id": "1", "run_id": "old"}  # before these figures existed
    assert UP not in daily.announcement(sample(), old)["embeds"][0]["description"]
    # A state from before the census stored Linking: the other bars still compare.
    text = daily.announcement(sample(), previous(authored=36, generated=14, linked_authored=None,
                                                 linked_game_code=None))["embeds"][0]["description"]
    assert f"44.44%**  {UP} 4.44" in text and "**Linking: 10.00%**\n" in text


def test_nothing_claims_the_game_is_100_percent_done():
    text = daily.announcement(sample(), previous())["embeds"][0]["description"] + daily.render(sample(), previous())
    assert "100%" not in text


@pytest.mark.parametrize("value", [0, 1, 4, 5, 49, 50, 95, 96, 100])
def test_blocks_always_fill_exactly_ten(value):
    text = daily.blocks(value, 100, daily.BLOCK["matched"])
    assert text.count(daily.BLOCK["matched"]) + text.count(daily.REST_BLOCK) == 10
