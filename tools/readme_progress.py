#!/usr/bin/env python3
"""Render the README card and the daily Discord post: three measures, three bars.

Each measure has its own stated denominator:

  REBUILT FROM SOURCE  everything that rebuilds to the original's exact bytes
                       (our C++, library source, generated C++, attached
                       prebuilt libraries: progress.py's REBUILDS, counted
                       without 0xCC), over all code.
  GAME CODE IN C++     our own C++ (progress.py's authored lane), over the
                       game's own code: all code minus vendored library source
                       and prebuilt libraries.
  LINKING              the part of that C++ in files that link cleanly, over
                       the same game's-own-code denominator. The link census
                       (tools/link_census.py) stores it as linked_authored; it
                       is never recomputed here, so it holds still between
                       censuses.

The card and the post draw the same numbers. The change shown beside a number
is against the last posted state (docs/discord-main-progress.json), and only
when that post used the same denominator, so output depends only on the
repository: no clock enters the card. progress.py prints the full breakdown.
"""
import argparse
import json
import os
from datetime import datetime, timezone
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

import progress

STATE = "docs/discord-main-progress.json"
EXE = "the original game exe (v1.03)"
TITLE = "BFME 1"
README = "https://github.com/Open-BFME/Open-BFME-1#readme"

# (key, label, what the bytes are); the denominator is stated beside each value.
ROWS = (("matched", "Rebuilt from source", f"rebuilt without copying {EXE}"),
        ("cpp", "Game code in C++", "of the game's own code, now C++ (libraries not counted)"),
        ("linked", "Linking", "of the game's own code linked"))
# Where the last post keeps each value and its denominator.
PREVIOUS_KEYS = {"matched": ("matched_total", "total"), "cpp": ("cpp_total", "game_total"),
                 "linked": ("linked_game_total", "game_total")}
CARD_FILL = {"matched": "#2ea043", "cpp": "#388bfd", "linked": "#d29922"}
# Discord draws each bar as ten square emoji (a wider row wraps on a phone).
BLOCK = {"matched": "\U0001f7e9", "cpp": "\U0001f7e6", "linked": "\U0001f7e8"}
REST_BLOCK = "⬛"
WIDTH = 10
UP, DOWN, DOT = "▲", "▼", "·"


def game_code(current):
    """The game's own code: all code minus vendored library source and prebuilt libraries."""
    return progress.game_code(current, current["total"])


def measures(current):
    """{key: (bytes, denominator)}; linked bytes are None when the last census
    stored no linked_authored."""
    total, game = current["total"], game_code(current)
    matched, cpp, linked = progress.rebuildable(current), current["authored"], current.get("linked_authored")
    if not 0 <= cpp <= game <= total or not 0 <= matched <= total or (
            linked is not None and not 0 <= linked <= cpp):
        raise ValueError("Invalid progress split")
    return {"matched": (matched, total), "cpp": (cpp, game), "linked": (linked, game)}


def measured(current):
    census = current.get("census")
    return f"measured {census['date'][:10]}" if census else "not measured yet"


def detail(current, key, value, denominator, what):
    text = f"{value:,} / {denominator:,} bytes {what}"
    return f"{text} ({measured(current)})" if key == "linked" else text


def delta_since(previous, key, value, denominator):
    """Percentage-point change since the last post over the same denominator,
    or None when not comparable or when it rounds to 0.00."""
    value_key, denominator_key = PREVIOUS_KEYS[key]
    if not previous or previous.get(denominator_key) != denominator or previous.get(value_key) is None:
        return None
    delta = progress.percent(value - previous[value_key], denominator)
    return delta if round(abs(delta), 2) else None


def arrow(delta):
    """UP 0.21 / DOWN 0.05: the change since the last post, in percentage points."""
    return f"{UP if delta > 0 else DOWN} {abs(delta):.2f}"


def render(current, previous=None):
    rows = measures(current)
    height = 70 + 74 * len(ROWS)
    body = []
    for index, (key, label, what) in enumerate(ROWS):
        value, denominator = rows[key]
        y = 64 + 74 * index
        moved = ""
        if value is None:
            number, width, text = "not measured", 0, "not measured yet"
        else:
            percent = progress.percent(value, denominator)
            number, width, text = f"{percent:.2f}%", 824 * percent / 100, detail(current, key, value, denominator, what)
            delta = delta_since(previous, key, value, denominator)
            if delta is not None:
                moved = (f'<tspan class="{"up" if delta > 0 else "down"}" dx="10" font-size="13" '
                         f'font-weight="600">{arrow(delta)}</tspan>')
        body.append(f'''    <text x="28" y="{y}" class="strong" font-size="15" font-weight="600">{label}{moved}</text>
    <text x="852" y="{y}" class="strong" font-size="20" font-weight="700" text-anchor="end">{number}</text>
    <rect class="track" x="28" y="{y + 10}" width="824" height="14" rx="7"/>
    <rect x="28" y="{y + 10}" width="{width:.2f}" height="14" rx="7" fill="{CARD_FILL[key]}"/>
    <text x="28" y="{y + 44}" class="muted" font-size="12.5">{text}</text>
''')
    (matched, total), (cpp, game), (linked, _) = rows["matched"], rows["cpp"], rows["linked"]
    linking = f"{progress.percent(linked, game):.2f}% linking" if linked is not None else "linking not measured"
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="880" height="{height}" viewBox="0 0 880 {height}" role="img" aria-labelledby="title desc">
  <title id="title">{TITLE}: {progress.percent(matched, total):.2f}% rebuilt from source, {progress.percent(cpp, game):.2f}% game code in C++, {linking}</title>
  <desc id="desc">{matched:,} of {total:,} code bytes rebuild to the original's exact bytes; {cpp:,} of the game's own {game:,} bytes are C++.</desc>
  <style>
    .card {{ fill: #0d1117; stroke: #30363d; }} .track {{ fill: #21262d; }}
    .strong {{ fill: #f0f6fc; }} .muted {{ fill: #8b949e; }} .up {{ fill: #3fb950; }} .down {{ fill: #f85149; }}
    @media (prefers-color-scheme: light) {{
      .card {{ fill: #ffffff; stroke: #d0d7de; }} .track {{ fill: #eaeef2; }}
      .strong {{ fill: #1f2328; }} .muted {{ fill: #59636e; }} .up {{ fill: #1a7f37; }} .down {{ fill: #cf222e; }}
    }}
  </style>
  <rect class="card" x="0.5" y="0.5" width="879" height="{height - 1}" rx="12"/>
  <g font-family="-apple-system,BlinkMacSystemFont,'Segoe UI','Noto Sans',Helvetica,Arial,sans-serif">
    <text x="28" y="30" class="muted" font-size="13" font-weight="600" letter-spacing="1.3">{TITLE} {DOT} REBUILD PROGRESS</text>
{"".join(body)}  </g>
</svg>
'''


def blocks(value, total, block, width=WIDTH):
    """`width` square emoji: the value's share in `block`, the rest dark."""
    count = round(width * value / total)
    return block * count + REST_BLOCK * (width - count)


def announcement(current, previous):
    """The daily post: the card's three measures, then a link to the README."""
    rows = measures(current)
    lines = []
    for key, label, what in ROWS:
        value, denominator = rows[key]
        if lines:
            lines.append("")
        if value is None:
            lines += [f"**{label}:** not measured yet", REST_BLOCK * WIDTH]
            continue
        delta = delta_since(previous, key, value, denominator)
        lines += [f"**{label}: {progress.percent(value, denominator):.2f}%**"
                  + (f"  {arrow(delta)}" if delta is not None else ""),
                  blocks(value, denominator, BLOCK[key]),
                  detail(current, key, value, denominator, what)]
    lines += ["", f"[What each bar measures, with charts: README]({README})"]
    return {"allowed_mentions": {"parse": []},
            "embeds": [{"title": f"{TITLE} {DOT} Rebuild progress", "color": 0x2EA043,
                        "description": "\n".join(lines)}]}


def previous_state():
    path = progress.ROOT / STATE
    return json.loads(path.read_text(encoding="utf-8")) if path.exists() else None


def notify(current):
    state_path = progress.ROOT / STATE
    previous = previous_state()
    run_id = os.environ.get("GITHUB_RUN_ID")
    if run_id and previous and previous.get("run_id") == run_id:
        print("Discord: this run already posted")
        return
    webhook = os.environ.get("DISCORD_PROGRESS_WEBHOOK", "").strip()
    if not webhook.startswith("https://discord.com/api/webhooks/"):
        raise SystemExit("DISCORD_PROGRESS_WEBHOOK is missing or invalid")
    url = webhook + "?wait=true"
    request = Request(url, data=json.dumps(announcement(current, previous)).encode("utf-8"),
                      headers={"Content-Type": "application/json", "User-Agent": "OpenBFME-Progress/1.0"},
                      method="POST")
    try:
        with urlopen(request, timeout=30) as response:
            message = json.load(response)
    except HTTPError as exc:
        raise SystemExit(f"Discord update failed: HTTP {exc.code}") from None
    except URLError:
        raise SystemExit("Discord update failed: connection error") from None
    rows = measures(current)
    state_path.write_text(json.dumps({**current, "matched_total": rows["matched"][0],
                                      "cpp_total": rows["cpp"][0], "game_total": rows["cpp"][1],
                                      "linked_game_total": rows["linked"][0],
                                      "updated_at": datetime.now(timezone.utc).isoformat(),
                                      "message_id": message["id"], "run_id": run_id}, indent=2) + "\n",
                          encoding="utf-8")
    print("Discord: new progress message posted")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--discord", action="store_true", help="post a new main Discord progress message")
    args = parser.parse_args()
    matched = progress.matched_at(None)
    notes = progress.notes_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    split = progress.real_split(matched, notes, start, size, naked)
    census = progress.census_at(None)
    _, total = progress.real_code_denominator(start, size)
    current = {"total": total, "census": census,
               "linked": int(census["linked_bytes"]) if census else None,
               "linked_authored": int(census["linked_authored"]) if census and census.get("linked_authored") else None,
               **{lane: split[lane] for lane in ("authored", "vendored", "generated", "library")}}
    output = progress.ROOT / "docs" / "progress.svg"
    output.write_text(render(current, previous_state()), encoding="utf-8", newline="\n")
    rows = measures(current)
    print(f"{output.relative_to(progress.ROOT)}: " + ", ".join(
        f"{label} {progress.percent(rows[key][0], rows[key][1]):.2f}%" if rows[key][0] is not None
        else f"{label} not measured" for key, label, _ in ROWS))
    if args.discord:
        notify(current)


if __name__ == "__main__":
    main()
