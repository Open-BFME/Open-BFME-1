#!/usr/bin/env python3
"""Render the README card and the daily Discord post: two numbers, three bars.

BYTE-MATCHED is everything that rebuilds to the original's exact bytes (our
C++, library source, generated C++, attached prebuilt libraries: progress.py's
REBUILDS, counted without 0xCC). LINKED is the part of it whose files link
cleanly, measured by the daily link census (tools/fleet/daily_census.sh).
progress.py prints the full breakdown.

The change shown beside each number is against the last posted state
(docs/discord-main-progress.json), so card and post always agree, and output
depends only on the repository: no clock enters the card.

The card has a bar for each number and a WHOLE GAME bar: every byte needs two
steps, byte-matched then linked, and WHOLE GAME is the share of steps done
(linked counts in full, byte-matched but not linked counts half), drawn to end at its
number. It is 100% only when everything is matched and linked. (Linked is part
of byte-matched, so the two numbers themselves never add up to anything.)
"""
import argparse
import json
import os
from datetime import datetime, timezone
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

import progress

STATE = "docs/discord-main-progress.json"
# Greens only. Linked = bright and dotted, byte-matched = medium, still
# original = the grey track.
LINKED, MATCHED = "#56d364", "#2ea043"
DEFINITIONS = ("Byte-matched: code rebuilt to the original exe's exact bytes",
               "Linked: the part that connects into one program")


def figures(current):
    """(linked, byte-matched) bytes; linked is a subset of byte-matched."""
    linked, matched = current["linked"], progress.rebuildable(current)
    if not 0 <= linked <= matched <= current["total"]:
        raise ValueError("Invalid progress split")
    return linked, matched


def whole(linked, matched):
    """Whole-game progress in bytes: every byte needs two steps, byte-matched
    and then linked, so this is the steps done over the steps there are (half
    of each). 100% only when everything is matched and linked."""
    return (matched + linked) / 2


def change(value, previous, key, total):
    """Percentage-point change since the last post, or None when there is no
    comparable post or nothing moved (linked moves once per census)."""
    if not previous or previous.get("total") != total or key not in previous or value == previous[key]:
        return None
    return progress.percent(value - previous[key], total)


def measured(current):
    census = current.get("census")
    return f"measured {census['date'][:10]}" if census else "not measured yet"


def arrow(delta):
    """▲ 0.21 / ▼ 0.05: the change since the last post, in percentage points."""
    return f"{'▲' if delta > 0 else '▼'} {abs(delta):.2f}"


def _row(y, label, value, delta, fill_width, fill):
    moved = (f'<tspan class="{"up" if delta > 0 else "down"}" dx="10" font-size="13" font-weight="600">'
             f'{arrow(delta)}</tspan>' if delta is not None else "")
    return f'''    <text x="28" y="{y}" class="strong" font-size="15" font-weight="600">{label}{moved}</text>
    <text x="852" y="{y}" class="strong" font-size="20" font-weight="700" text-anchor="end">{value}</text>
    <rect class="track" x="28" y="{y + 10}" width="824" height="14" rx="7"/>
    <rect x="28" y="{y + 10}" width="{fill_width:.2f}" height="14" rx="7" fill="{fill}"/>
'''


def render(current, previous=None):
    total = current["total"]
    linked, matched = figures(current)
    lp, mp = progress.percent(linked, total), progress.percent(matched, total)
    rest = 100 - mp
    wp = progress.percent(whole(linked, matched), total)
    delta = change(whole(linked, matched), previous, "whole_total", total)
    moved_whole = (f'<tspan class="{"up" if delta > 0 else "down"}" dx="10" font-size="13" font-weight="600">'
                   f'{arrow(delta)}</tspan>' if delta is not None else "")
    height = 262
    split = [("url(#dots)", f"linked {lp:.2f}%"), (MATCHED, f"byte-matched, not linked yet {mp - lp:.2f}%")]
    keys = []
    for index, (colour, label) in enumerate(split):
        x = 28 + 275 * index
        fill = f'fill="{colour}"' if colour else 'class="track"'
        keys.append(f'    <rect x="{x}" y="206" width="10" height="10" rx="2" {fill}/>'
                    f'<text x="{x + 16}" y="215" class="muted" font-size="12.5">{label}</text>')
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="880" height="{height}" viewBox="0 0 880 {height}" role="img" aria-labelledby="title desc">
  <title id="title">BFME 1: {mp:.2f}% byte-matched, {lp:.2f}% linked</title>
  <desc id="desc">{matched:,} of {total:,} code bytes rebuild to the original exe's exact bytes; {linked:,} of them are in files that link cleanly ({measured(current)}). Whole game {wp:.2f}%: {lp:.2f}% linked, {mp - lp:.2f}% byte-matched but not linked yet, {rest:.2f}% still original bytes.</desc>
  <style>
    .card {{ fill: #0d1117; stroke: #30363d; }} .track {{ fill: #21262d; }}
    .strong {{ fill: #f0f6fc; }} .muted {{ fill: #8b949e; }} .up {{ fill: #3fb950; }} .down {{ fill: #f85149; }}
    @media (prefers-color-scheme: light) {{
      .card {{ fill: #ffffff; stroke: #d0d7de; }} .track {{ fill: #eaeef2; }}
      .strong {{ fill: #1f2328; }} .muted {{ fill: #59636e; }} .up {{ fill: #1a7f37; }} .down {{ fill: #cf222e; }}
    }}
  </style>
  <defs>
    <pattern id="dots" width="5" height="5" patternUnits="userSpaceOnUse">
      <rect width="5" height="5" fill="{LINKED}"/><circle cx="2.5" cy="2.5" r="1.1" fill="#196c2e"/>
    </pattern>
    <clipPath id="whole"><rect x="28" y="180" width="824" height="18" rx="9"/></clipPath>
  </defs>
  <rect class="card" x="0.5" y="0.5" width="879" height="{height - 1}" rx="12"/>
  <g font-family="-apple-system,BlinkMacSystemFont,'Segoe UI','Noto Sans',Helvetica,Arial,sans-serif">
    <text x="28" y="30" class="muted" font-size="13" font-weight="600" letter-spacing="1.3">BFME 1 \u00b7 REBUILD PROGRESS</text>
{_row(64, "Byte-matched", f"{mp:.2f}%", change(matched, previous, "matched_total", total), 824 * mp / 100, MATCHED)}{_row(116, "Linked", f"{lp:.2f}%", change(linked, previous, "linked_total", total), 824 * lp / 100, "url(#dots)")}    <text x="28" y="168" class="strong" font-size="15" font-weight="600">Whole game{moved_whole}</text>
    <text x="852" y="168" class="strong" font-size="20" font-weight="700" text-anchor="end">{wp:.2f}%</text>
    <rect class="track" x="28" y="180" width="824" height="18" rx="9"/>
    <g clip-path="url(#whole)">
      <rect x="28" y="180" width="{824 * wp / 100:.2f}" height="18" fill="{MATCHED}"/>
      <rect x="28" y="180" width="{824 * lp / 100:.2f}" height="18" fill="url(#dots)"/>
    </g>
{chr(10).join(keys)}
    <text x="28" y="246" class="muted" font-size="12.5">{DEFINITIONS[0]}. {DEFINITIONS[1]} ({measured(current)}).</text>
  </g>
</svg>
'''


# Discord draws the card's three bars in square emoji, ten to a row (a wider
# row wraps on a phone). Discord draws them with no gap, so each part needs its
# own colour: yellow = linked, green = byte-matched, dark = still original.
LINKED_BLOCK, MATCHED_BLOCK, REST_BLOCK = "\U0001f7e8", "\U0001f7e9", "\u2b1b"
WIDTH = 10
REPORT = "https://open-bfme.github.io/Open-BFME-1/"


def blocks(parts, total, width=WIDTH):
    """[(block, bytes)] as `width` blocks: cumulative rounding, so the parts
    always fill exactly `width`; whatever is left is dark."""
    cells, done, running = [], 0, 0
    for block, value in parts:
        running += value
        count = round(width * running / total) - done
        cells.append(block * count)
        done += count
    return "".join(cells) + REST_BLOCK * (width - done)


def announcement(current, previous):
    """The daily post: the README card's three bars as green blocks, a one-line
    key and the link to the full report. Nothing else: the definitions live on
    the card and the report."""
    total = current["total"]
    linked, matched = figures(current)
    lp, mp = progress.percent(linked, total), progress.percent(matched, total)

    def moved(delta):
        return f"  {arrow(delta)}" if delta is not None else ""

    rows = [
        f"{blocks([(MATCHED_BLOCK, matched)], total)}  **{mp:.2f}%**  Byte-matched"
        + moved(change(matched, previous, "matched_total", total)),
        f"{blocks([(LINKED_BLOCK, linked)], total)}  **{lp:.2f}%**  Code linked"
        + moved(change(linked, previous, "linked_total", total)),
        f"{blocks([(LINKED_BLOCK, linked), (MATCHED_BLOCK, (matched - linked) / 2)], total)}  "
        f"**{progress.percent(whole(linked, matched), total):.2f}%**  Whole game"
        + moved(change(whole(linked, matched), previous, "whole_total", total)),
        "",  # a blank line between the bars and the key
        f"{LINKED_BLOCK} linked {lp:.2f}%  \u00b7  {MATCHED_BLOCK} byte-matched, not linked yet {mp - lp:.2f}%",
        f"[Full progress report: chart and map]({REPORT})",
    ]
    return {"allowed_mentions": {"parse": []},
            "embeds": [{"title": "BFME 1 \u00b7 Daily progress", "color": 0x2EA043, "description": "\n".join(rows)}]}


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
    linked, matched = figures(current)
    state_path.write_text(json.dumps({**current, "linked_total": linked, "matched_total": matched,
                                      "whole_total": whole(linked, matched),
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
    linked = int(census["linked_bytes"]) if census else 0
    _, total = progress.real_code_denominator(start, size)
    current = {"total": total, "linked": linked, "census": census,
               **{lane: split[lane] for lane in ("authored", "vendored", "generated", "library")}}
    previous = previous_state()
    output = progress.ROOT / "docs" / "progress.svg"
    svg = render(current, previous)
    output.write_text(svg, encoding="utf-8", newline="\n")
    print(f"{output.relative_to(progress.ROOT)}: {progress.percent(progress.rebuildable(current), total):.2f}% "
          f"byte-matched, {progress.percent(linked, total):.2f}% linked")
    if args.discord:
        notify(current)


if __name__ == "__main__":
    main()
