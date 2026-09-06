#!/usr/bin/env python3
"""Render the README bar using progress.py's existing headline calculation."""
import argparse
import json
import os
from datetime import datetime, timezone
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

import progress


def render(rebuilt, total):
    if total <= 0 or not 0 <= rebuilt <= total:
        raise ValueError("Invalid rebuild coverage")
    percentage = progress.percent(rebuilt, total)
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="880" height="160" viewBox="0 0 880 160" role="img" aria-labelledby="title desc">
  <title id="title">BFME 1 rebuild progress: {percentage:.2f}%</title>
  <desc id="desc">{rebuilt:,} of {total:,} code bytes rebuild from what we hold. Ledger-derived; not a fresh build verification.</desc>
  <rect x="1" y="1" width="878" height="158" rx="16" fill="#0d1117" stroke="#30363d"/>
  <g font-family="Segoe UI,Arial,sans-serif">
    <text x="28" y="37" fill="#c9d1d9" font-size="14" font-weight="600" letter-spacing="1.4">BFME 1 · REBUILD PROGRESS</text>
    <text x="852" y="43" fill="#f0f6fc" font-size="30" font-weight="700" text-anchor="end">{percentage:.2f}%</text>
    <rect x="28" y="62" width="824" height="20" rx="10" fill="#21262d"/>
    <rect x="28" y="62" width="{824 * percentage / 100:.4f}" height="20" rx="10" fill="#3fb950"/>
    <text x="28" y="111" fill="#c9d1d9" font-size="14">{rebuilt:,} / {total:,} code bytes rebuild from what we hold</text>
    <text x="28" y="137" fill="#8b949e" font-size="12">Updated automatically · Includes source, generators and linked libraries · Excludes retail byte dumps</text>
  </g>
</svg>
'''


def announcement(current, previous):
    percentage = progress.percent(current["rebuilt"], current["total"])
    filled = round(percentage / 10)
    change = ""
    if previous:
        delta = percentage - progress.percent(previous["rebuilt"], previous["total"])
        change = f"\n{delta:+.2f} percentage points since the last update"
    return {
        "allowed_mentions": {"parse": []},
        "embeds": [{
            "title": "BFME 1 · Rebuild progress",
            "url": "https://github.com/Open-BFME/Open-BFME-1",
            "color": 0x3FB950,
            "description": f"**{percentage:.2f}%**\n\n"
                           + "🟩" * filled + "⬛" * (10 - filled)
                           + f"\n{change}\n"
                           + f"{current['rebuilt']:,} / {current['total']:,} code bytes",
        }],
    }


def notify(current):
    state_path = progress.ROOT / "docs" / "discord-progress.json"
    previous = json.loads(state_path.read_text(encoding="utf-8")) if state_path.exists() else None
    today = datetime.now(timezone.utc).date().isoformat()
    if previous and (previous["date"] == today or all(previous[k] == current[k] for k in ("rebuilt", "total"))):
        print("Discord: no new daily update needed")
        return
    webhook = os.environ.get("DISCORD_PROGRESS_WEBHOOK", "").strip()
    if not webhook.startswith("https://discord.com/api/webhooks/"):
        raise SystemExit("DISCORD_PROGRESS_WEBHOOK is missing or invalid")
    request = Request(webhook + "?wait=true", data=json.dumps(announcement(current, previous)).encode("utf-8"),
                      headers={"Content-Type": "application/json", "User-Agent": "OpenBFME-Progress/1.0"}, method="POST")
    try:
        with urlopen(request, timeout=30) as response:
            message = json.load(response)
    except HTTPError as exc:
        raise SystemExit(f"Discord update failed: HTTP {exc.code}") from None
    except URLError:
        raise SystemExit("Discord update failed: connection error") from None
    state_path.write_text(json.dumps({**current, "date": today, "message_id": message["id"]}, indent=2) + "\n", encoding="utf-8")
    print("Discord: daily progress posted")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--discord", action="store_true", help="post changed progress at most once per UTC day")
    parser.add_argument("--refresh-discord", action="store_true", help="refresh the existing message layout without posting again")
    args = parser.parse_args()
    if args.refresh_discord:
        state = json.loads((progress.ROOT / "docs/discord-progress.json").read_text(encoding="utf-8"))
        webhook = os.environ["DISCORD_PROGRESS_WEBHOOK"].strip()
        if not webhook.startswith("https://discord.com/api/webhooks/"):
            raise SystemExit("Invalid webhook URL")
        for url, payload in (
            (webhook, {"name": "BFME 1 Progress"}),
            (webhook + "/messages/" + state["message_id"], announcement(state, None)),
        ):
            request = Request(url, data=json.dumps(payload).encode("utf-8"),
                              headers={"Content-Type": "application/json", "User-Agent": "OpenBFME-Progress/1.0"}, method="PATCH")
            try:
                with urlopen(request, timeout=30) as response:
                    response.read()
            except (HTTPError, URLError):
                raise SystemExit("Discord layout refresh failed") from None
        print("Discord: existing message layout refreshed")
        return
    matched = progress.matched_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    split = progress.source_split(matched, progress.notes_at(None), start, size, naked)
    _, total = progress.real_code_denominator(start, size)
    rebuilt = progress.rebuildable(split)
    output = progress.ROOT / "docs" / "progress.svg"
    output.write_text(render(rebuilt, total), encoding="utf-8", newline="\n")
    print(f"{output.relative_to(progress.ROOT)}: {progress.percent(rebuilt, total):.2f}%")
    if args.discord:
        notify({"rebuilt": rebuilt, "total": total})


if __name__ == "__main__":
    main()
