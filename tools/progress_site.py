#!/usr/bin/env python3
"""The progress page: a decomp.dev-style report built from the repository.

  python3 tools/progress_site.py history --backfill   # one point per day since the first commit
  python3 tools/progress_site.py history --today      # append today's point (the daily job)
  python3 tools/progress_site.py render [OUT]         # write the page (default build/site/index.html)

History lives in targets/game/reverse/progress_history.csv: BYTE-MATCHED and
DECOMPILED measured on each day's last commit with today's definitions
(progress.real_split), so the whole series is comparable. LINKED history is
the link census's own rows (link_census_history.csv).
"""
import argparse
import csv
import html
import json
import subprocess
import sys
from datetime import date, datetime, timedelta, timezone
from pathlib import Path

import progress

HISTORY = progress.ROOT / "targets/game/reverse/progress_history.csv"
FIELDS = ["date", "commit", "total", "byte_matched", "decompiled"]


def git(*args):
    return subprocess.run(["git", *args], cwd=progress.ROOT, capture_output=True, text=True, check=True).stdout.strip()


def measure(ref):
    """(total, byte-matched, decompiled) real-code bytes at one commit."""
    matched, notes = progress.matched_at(ref), progress.notes_at(ref)
    start, size = progress.retail_text()
    split = progress.real_split(matched, notes, start, size, progress.naked_cpp_rows_at(matched, ref))
    _, total = progress.real_code_denominator(start, size)
    return total, progress.rebuildable(split), progress.decompiled(split)


def read_history():
    if not HISTORY.exists():
        return []
    with HISTORY.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def write_history(rows):
    rows = sorted({row["date"]: row for row in rows}.values(), key=lambda row: row["date"])
    with HISTORY.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def point(day, ref):
    total, matched, decompiled = measure(ref)
    return {"date": day.isoformat(), "commit": git("rev-parse", "--short=10", ref),
            "total": total, "byte_matched": matched, "decompiled": decompiled}


def backfill(branch="origin/master"):
    """One point per UTC day: that day's last commit on the branch."""
    first = date.fromisoformat(git("log", "--reverse", "--format=%cs", branch).splitlines()[0])
    have = {row["date"] for row in read_history()}
    rows = read_history()
    day = first
    today = datetime.now(timezone.utc).date()
    while day <= today:
        if day.isoformat() not in have:
            end = datetime(day.year, day.month, day.day, tzinfo=timezone.utc) + timedelta(days=1)
            ref = git("rev-list", "-1", f"--before={end.isoformat()}", branch)
            if ref:
                try:
                    rows.append(point(day, ref))
                    print(f"{day} {rows[-1]['commit']} {100 * rows[-1]['byte_matched'] / rows[-1]['total']:.2f}%",
                          flush=True)
                except (subprocess.CalledProcessError, KeyError, ValueError, SystemExit) as exc:
                    print(f"{day} {ref[:10]} not measurable: {exc}", file=sys.stderr, flush=True)
                write_history(rows)
        day += timedelta(days=1)


def today_point():
    rows = read_history()
    rows.append(point(datetime.now(timezone.utc).date(), "HEAD"))
    write_history(rows)


# --- the page --------------------------------------------------------------

LINKED, OWN, OTHER = "#56d364", "#2ea043", "#196c2e"  # the README card's three greens
CATEGORIES = (  # (key, label, path prefixes); first match wins, the rest is "Other"
    ("engine", "Game engine", ("game/GameEngine/", "game/GameNetwork/", "game/Main/")),
    ("device", "Device & graphics", ("game/GameEngineDevice/",)),
    ("libraries", "Libraries", ("game/Libraries/", "game/stlport/", "inputs/")),
    ("generated", "Generated C++", ("game/gen_small/",)),
    ("dumps", "Dumps", ("game/gen_asm/", "game/masm_dumps/", "dumps/")),
)


LABELS = {"dumps": "Dumps", "game/gen_asm": "Dumps", "game/gen_small": "Generated C++", "game/masm_dumps": "MASM dumps",
          "inputs/vendor/d3dx9": "d3dx9 (Microsoft)", "inputs/vendor/dxerr9": "dxerr9 (Microsoft)",
          "inputs/toolchains": "C runtime (Microsoft)", "unclaimed": "Unclaimed"}


CATEGORY_LABELS = {key: label for key, label, _ in CATEGORIES}


def category(source):
    for key, _, prefixes in CATEGORIES:
        if source.startswith(prefixes):
            return key
    return "other"


def _subtract(start, end, claimed, starts):
    """Parts of [start, end) outside the sorted, merged `claimed` intervals."""
    import bisect
    pieces, at = [], start
    index = max(0, bisect.bisect_right(starts, start) - 1)
    while at < end and index < len(claimed):
        lo, hi = claimed[index]
        if hi <= at:
            index += 1
            continue
        if lo >= end:
            break
        if lo > at:
            pieces.append((at, lo))
        at = max(at, hi)
        index += 1
    if at < end:
        pieces.append((at, end))
    return pieces


def per_source(matched, notes, text_start, text_size, naked_rows):
    """{source: {lane: real bytes}} that sums exactly to progress.real_split:
    lanes claim bytes in priority order, and within a lane the earliest row
    (by address) owns an overlap."""
    import collections
    image_start, image = progress._text_image()
    text_end = text_start + text_size
    naked_rows = set(naked_rows)
    lanes = {name: [] for name in progress.SOURCE_LANES}
    for key, (size, source) in matched.items():
        start, end = max(int(key[1], 16), text_start), min(int(key[1], 16) + size, text_end)
        if start < end:
            lanes[progress.source_lane(source, notes[key], key in naked_rows)].append((start, end, source))
    out = collections.defaultdict(collections.Counter)
    claimed = []
    for lane in progress.SOURCE_LANES:
        starts = [lo for lo, _ in claimed]
        reach = 0
        for start, end, source in sorted(lanes[lane]):
            start = max(start, reach)
            reach = max(reach, end)
            for lo, hi in _subtract(start, end, claimed, starts) if start < end else ():
                out[source][lane] += hi - lo - image[lo - image_start:hi - image_start].count(0xCC)
        claimed = progress.merge_intervals(claimed + [(s, e) for s, e, _ in lanes[lane]])
    return out


def block_of(source):
    """The treemap block a source file belongs to: a folder, a few levels down."""
    parts = source.split("/")
    if "/".join(parts[:2]) in ("game/gen_asm", "game/masm_dumps"):
        return "dumps"  # every dump file, MASM or generated, is one block
    depth = {"game/gen_small": 2, "game/gen_asm": 2, "game/masm_dumps": 2,
             "inputs/toolchains": 2, "inputs/reference": 2}.get("/".join(parts[:2]), 5 if parts[0] == "game" else 3)
    return "/".join(parts[:min(depth, len(parts) - 1)]) or source


def squarify(items, x, y, w, h):
    """Squarified treemap (Bruls et al.): [(item, x, y, w, h)] for [(item, size)]."""
    items = [(item, size) for item, size in items if size > 0]
    total = sum(size for _, size in items)
    if not items or total <= 0:
        return []
    scale = w * h / total
    rects, row, rest = [], [], [(item, size * scale) for item, size in items]

    def worst(row, side):
        s = sum(a for _, a in row)
        return max(max(side * side * a / (s * s), s * s / (side * side * a)) for _, a in row)

    while rest:
        side = min(w, h)
        candidate = row + [rest[0]]
        if not row or worst(candidate, side) <= worst(row, side):
            row, rest = candidate, rest[1:]
            if rest:
                continue
        s = sum(a for _, a in row)
        if w >= h:
            col, oy = s / h, y
            for item, a in row:
                rects.append((item, x, oy, col, a / col))
                oy += a / col
            x, w = x + col, w - col
        else:
            line, ox = s / w, x
            for item, a in row:
                rects.append((item, ox, y, a / line, line))
                ox += a / line
            y, h = y + line, h - line
        row = []
    return rects


def _pct(part, whole):
    return 100.0 * part / whole if whole else 0.0


def render(out, svg_dir=None):
    import collections
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    split = progress.real_split(matched, notes, start, size, naked)
    by_source = per_source(matched, notes, start, size, naked)
    for lane in progress.SOURCE_LANES:  # the map must add up to the headline, byte for byte
        assert sum(c[lane] for c in by_source.values()) == split[lane], lane
    _, total = progress.real_code_denominator(start, size)
    census = progress.census_at(None)
    linked = int(census["linked_bytes"]) if census else 0
    byte_matched = progress.rebuildable(split)
    status_text = progress._text_at(None, progress.LINK_STATUS) or ""
    clean = {r["source"] for r in csv.DictReader(status_text.splitlines()) if r["linked"] == "yes"}
    commit = git("log", "-1", "--format=%h%x09%cs%x09%s", "HEAD").split("\t")

    # Per category and per map block: total claimed, byte-matched, linked-at-census.
    cats = collections.defaultdict(collections.Counter)
    blocks = collections.defaultdict(collections.Counter)
    for source, lanes in by_source.items():
        rebuilt = sum(lanes[l] for l in ("authored", "vendored", "generated", "library"))
        own = sum(lanes[l] for l in progress.DECOMPILED_LANES)
        joined = sum(lanes[l] for l in progress.DECOMPILED_LANES) if source in clean else 0
        for bucket in (cats[category(source)], blocks[block_of(source)]):
            bucket["total"] += sum(lanes.values())
            bucket["matched"] += rebuilt
            bucket["own"] += own
            bucket["linked"] += joined
    unclaimed = total - sum(split[l] for l in progress.SOURCE_LANES)
    blocks["unclaimed"]["total"] += unclaimed  # no function boundary proven yet

    tabs = [{"key": "all", "label": "All", "total": total, "matched": byte_matched, "linked": linked,
             "own": progress.decompiled(split)}]
    for key, label, _ in CATEGORIES + (("other", "Other", ()),):
        if cats[key]["total"] >= total / 200:  # under 0.5% of the code is noise, not a category
            tabs.append({"key": key, "label": label, **dict(cats[key])})

    # Map. A folder under 0.5% of the code is too small to carry its name, so
    # each category's small folders become one named block ("Game engine: 23
    # smaller folders"); every block on the map is then labelled.
    W, H = 1100, 340
    kinds = {name: category(name + "/") for name in blocks}
    small = collections.defaultdict(list)
    for name, c in list(blocks.items()):
        if c["total"] < total / 200 and name != "unclaimed":
            small[kinds[name]].append(name)
    names = dict(CATEGORY_LABELS)
    for kind, members in small.items():
        if len(members) < 2:
            continue
        merged = f"{names.get(kind, 'Other')}: {len(members)} smaller folders"
        for name in members:
            blocks[merged].update(blocks.pop(name))
        kinds[merged] = kind
        LABELS[merged] = merged
    order = sorted(blocks.items(), key=lambda kv: -kv[1]["total"])
    tiles, svg_tiles = [], []
    for (name, c), x, y, w, h in squarify([((n, c), c["total"]) for n, c in order], 0, 0, W, H):
        lp, op, mp = (_pct(c[k], c["total"]) for k in ("linked", "own", "matched"))
        fill = (f"linear-gradient(to right,{LINKED} 0 {lp:.2f}%,{OWN} {lp:.2f}% {op:.2f}%,"
                f"{OTHER} {op:.2f}% {mp:.2f}%,var(--rest) {mp:.2f}% 100%)")
        short = LABELS.get(name, name.split("/")[-1])
        # Every block is named: small ones in smaller type, long names wrap onto
        # as many lines as the block has room for (the map is ~0.87 px per unit).
        size = 11 if w > 70 and h > 22 else 9.5
        if " " not in short:  # a single word cannot wrap: shrink it to fit instead
            size = max(7.5, min(size, (w * 0.87 - 6) / (0.58 * len(short))))
        lines = max(1, int((h * 0.87 - 2) // (size * 1.35)))
        label = f'<span style="font-size:{size:.1f}px;-webkit-line-clamp:{lines}">{html.escape(short)}</span>'
        tip = (f"{name}\n{c['total']:,} bytes\nbyte-matched {mp:.1f}% (own source {op:.1f}%)\n"
               f"linked (last census) {lp:.1f}%")
        svg_tiles.append((short, tip, x, y, w, h, lp, op, mp))
        dots = f'<i class="lk" style="width:{lp:.2f}%"></i>' if lp else ""
        tiles.append(f'<div class="tile" data-cat="{kinds.get(name, category(name + "/"))}" title="{html.escape(tip)}" '
                     f'style="left:{100 * x / W:.3f}%;top:{100 * y / H:.3f}%;width:{100 * w / W:.3f}%;'
                     f'height:{100 * h / H:.3f}%;background:{fill}">{dots}{label}</div>')

    # Chart.
    history = read_history()
    census_rows = [r for r in csv.DictReader((progress._text_at(None, progress.LINK_HISTORY) or "").splitlines())
                   if r.get("linked_authored") and r.get("game_code")]
    chart = _chart(history, census_rows)

    data = json.dumps({t["key"]: t for t in tabs})
    tab_buttons = "".join(f'<button data-key="{t["key"]}"{" class=on" if t["key"] == "all" else ""}>'
                          f'{html.escape(t["label"])}</button>' for t in tabs)
    census_note = f"link census {census['date'][:10]} at {census['commit']}" if census else "no link census yet"
    data_total = progress.data_denominator()
    page = PAGE.format(
        matched_pct=f"{_pct(byte_matched, total):.2f}", linked_pct=f"{_pct(linked, total):.2f}",
        code_mb=f"{total / 1e6:.2f}", data_mb=f"{data_total / 1e6:.2f}",
        matched_w=f"{_pct(byte_matched, total):.3f}", linked_w=f"{_pct(linked, total):.3f}",
        own_w=f"{_pct(progress.decompiled(split), total):.3f}",
        commit=html.escape(commit[0]), commit_date=commit[1], subject=html.escape(commit[2][:90]),
        census=html.escape(census_note), tabs=tab_buttons, tiles="\n".join(tiles), chart=chart, data=data,
        linked_c=LINKED, own_c=OWN, other_c=OTHER)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(page, encoding="utf-8", newline="\n")
    if svg_dir is not None:
        # The README cannot run a page, so it shows the chart and the map as
        # images, regenerated with the card every day.
        svg_dir.mkdir(parents=True, exist_ok=True)
        (svg_dir / "progress_chart.svg").write_text(chart_svg(chart), encoding="utf-8", newline="\n")
        (svg_dir / "progress_map.svg").write_text(map_svg(svg_tiles, W, H), encoding="utf-8", newline="\n")
    print(f"{out}: {_pct(byte_matched, total):.2f}% byte-matched, {_pct(linked, total):.2f}% linked, "
          f"{len(tiles)} map blocks, {len(history)} history points")


SVG_STYLE = """  <style>
    .card {{ fill: #0d1117; stroke: #30363d; }} .muted {{ fill: #8b949e; }} .grid {{ stroke: #30363d; }}
    .axis {{ fill: #8b949e; font-size: 12px; }} .rest {{ fill: #30363d; }} .edge {{ stroke: #0d1117; }}
    .hit {{ fill: transparent; }}
    @media (prefers-color-scheme: light) {{
      .card {{ fill: #ffffff; stroke: #d0d7de; }} .muted {{ fill: #59636e; }} .grid {{ stroke: #d0d7de; }}
      .axis {{ fill: #59636e; }} .rest {{ fill: #d0d7de; }} .edge {{ stroke: #ffffff; }}
    }}
  </style>"""
FONT = "-apple-system,BlinkMacSystemFont,'Segoe UI','Noto Sans',Helvetica,Arial,sans-serif"
DOTS = (f'<pattern id="dots" width="5" height="5" patternUnits="userSpaceOnUse">'
        f'<rect width="5" height="5" fill="{LINKED}"/><circle cx="2.5" cy="2.5" r="1.1" fill="{OTHER}"/></pattern>')


def _frame(width, height, title, legend, body, label):
    key = "".join(f'<rect x="{x}" y="20" width="10" height="10" rx="2" fill="{fill}"/>'
                  f'<text x="{x + 16}" y="29" class="muted" font-size="12.5">{html.escape(text)}</text>'
                  for x, fill, text in legend)
    return (f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
            f'viewBox="0 0 {width} {height}" role="img" aria-label="{html.escape(label)}">\n'
            + SVG_STYLE.format() + f'\n  <defs>{DOTS}</defs>\n'
            f'  <rect class="card" x="0.5" y="0.5" width="{width - 1}" height="{height - 1}" rx="12"/>\n'
            f'  <g font-family="{FONT}">\n'
            f'    <text x="28" y="29" class="muted" font-size="13" font-weight="600" letter-spacing="1.3">{title}</text>\n'
            f'    {key}\n{body}\n  </g>\n</svg>\n')


def chart_svg(chart):
    """The page's chart as a standalone, theme-aware image for the README."""
    inner = chart.replace('class="chart" ', "").replace("<svg ", '<svg x="28" y="44" width="824" height="144" ', 1)
    return _frame(880, 202, "BFME 1 \u00b7 OVER TIME",
                  [(200, OWN, "byte-matched, daily"), (360, "url(#dots)", "linking, per census")], inner,
                  "BFME 1 progress over time")


def _wrap(text, width, size):
    """Greedy word wrap by estimated glyph width; (lines, size)."""
    per_line = max(1, int(width / (0.56 * size)))
    if " " not in text and len(text) > per_line:
        size = max(7.0, width / (0.56 * len(text)))
        return [text], size
    lines, line = [], ""
    for word in text.split():
        candidate = f"{line} {word}".strip()
        if len(candidate) <= per_line or not line:
            line = candidate
        else:
            lines.append(line)
            line = word
    return lines + [line], size


def map_svg(tiles, W, H):
    """The page's map as a standalone image: every block named, linked dotted."""
    top, left, body = 44, 28, []
    scale = 824 / W  # the README images share the card width, 880 px
    for index, (label, tip, x, y, w, h, lp, op, mp) in enumerate(tiles):
        x, y, w, h = left + x * scale, top + y * scale, w * scale, h * scale
        body.append(f'    <g><title>{html.escape(tip)}</title>'
                    f'<clipPath id="t{index}"><rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}"/></clipPath>'
                    f'<g clip-path="url(#t{index})"><rect class="rest" x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}"/>')
        for share, fill in ((mp, OTHER), (op, OWN), (lp, "url(#dots)")):
            if share:
                body.append(f'<rect x="{x:.1f}" y="{y:.1f}" width="{w * share / 100:.1f}" height="{h:.1f}" fill="{fill}"/>')
        size = 11 if w > 60 and h > 22 else 9
        lines, size = _wrap(label, w - 8, size)
        room = max(1, int((h - 4) // (size * 1.3)))
        if len(lines) > room:
            lines = lines[:room]
            lines[-1] = lines[-1][:max(1, len(lines[-1]) - 1)] + "\u2026"
        for row, text in enumerate(lines):
            body.append(f'<text x="{x + 4:.1f}" y="{y + 3 + size * (1.05 + 1.3 * row):.1f}" font-size="{size:.1f}" '
                        f'fill="#ffffff" style="paint-order:stroke" stroke="#0008" stroke-width="2">{html.escape(text)}</text>')
        body.append(f'</g><rect class="edge" x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}" fill="none"/></g>')
    height = int(top + H * scale + 20)
    return _frame(880, height, "BFME 1 \u00b7 MAP",
                  [(150, "url(#dots)", "linked"), (222, OWN, "byte-matched: our own source"),
                   (420, OTHER, "generated code, Microsoft libraries"), (660, "#6e7681", "still original")],
                  "\n".join(body), "Map of BFME 1's code by folder")


def _chart(history, census_rows):
    """An SVG line chart: byte-matched per day (blue) and, per census, Linking
    (green): the game's own linked C++ over that census tree's game code, the
    README card's Linking bar."""
    if not history:
        return '<p class="muted">No history yet.</p>'
    W, H, L, R, T, B = 1100, 190, 40, 8, 10, 24
    days = [date.fromisoformat(r["date"]) for r in history]
    first, last = days[0], max(days[-1], *(date.fromisoformat(r["date"][:10]) for r in census_rows)) if census_rows else days[-1]
    span = max((last - first).days, 1)

    def px(day, pct):
        return L + (W - L - R) * (day - first).days / span, T + (H - T - B) * (1 - pct / 100)

    grid = "".join(f'<line x1="{L}" x2="{W - R}" y1="{px(first, p)[1]:.1f}" y2="{px(first, p)[1]:.1f}" class="grid"/>'
                   f'<text x="{L - 8}" y="{px(first, p)[1] + 4:.1f}" class="axis" text-anchor="end">{p}%</text>'
                   for p in (0, 25, 50, 75, 100))
    months, day = "", date(first.year, first.month, 1)
    while day <= last:
        if day >= first:
            x = px(day, 0)[0]
            months += f'<text x="{x:.1f}" y="{H - 8}" class="axis">{day.strftime("%b")}</text>'
        day = date(day.year + (day.month == 12), day.month % 12 + 1, 1)
    line = " ".join(f"{x:.1f},{y:.1f}" for x, y in
                    (px(d, 100 * int(r["byte_matched"]) / int(r["total"])) for d, r in zip(days, history)))
    x0, y0 = px(days[0], 0)
    xn, _ = px(days[-1], 0)
    area = f"{x0:.1f},{y0:.1f} {line} {xn:.1f},{y0:.1f}"
    def linking(r):
        return 100 * int(r["linked_authored"]) / int(r["game_code"])
    points = [(px(date.fromisoformat(r["date"][:10]), linking(r)), r) for r in census_rows]
    linked_line = " ".join(f"{x:.1f},{y:.1f}" for (x, y), _ in points)
    dots = (f'<polyline points="{linked_line}" fill="none" stroke="{LINKED}" stroke-width="2.5" '
            f'stroke-dasharray="0.1 6" stroke-linecap="round"/>' if len(points) > 1 else "") + "".join(
        f'<circle cx="{x:.1f}" cy="{y:.1f}" r="4" fill="{LINKED}">'
        f'<title>{r["date"][:10]}: linking {linking(r):.2f}%</title></circle>' for (x, y), r in points)
    tips = "".join(f'<circle cx="{x:.1f}" cy="{y:.1f}" r="7" class="hit"><title>{d}: byte-matched '
                   f'{100 * int(r["byte_matched"]) / int(r["total"]):.2f}%</title></circle>'
                   for d, r, (x, y) in ((d, r, px(d, 100 * int(r["byte_matched"]) / int(r["total"])))
                                        for d, r in zip(days, history)))
    return (f'<svg viewBox="0 0 {W} {H}" class="chart" role="img" aria-label="progress over time">{grid}{months}'
            f'<polygon points="{area}" fill="{OWN}" opacity="0.14"/>'
            f'<polyline points="{line}" fill="none" stroke="{OWN}" stroke-width="2.5" stroke-linejoin="round"/>'
            f'{dots}{tips}</svg>')


PAGE = """<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>BFME 1 progress report</title>
<style>
:root{{--bg:#0d1117;--panel:#161b22;--line:#30363d;--text:#e6edf3;--muted:#8b949e;--rest:#30363d;--track:#21262d}}
@media (prefers-color-scheme: light){{:root{{--bg:#ffffff;--panel:#f6f8fa;--line:#d0d7de;--text:#1f2328;--muted:#59636e;--rest:#d0d7de;--track:#eaeef2}}}}
*{{box-sizing:border-box}} body{{margin:0;background:var(--bg);color:var(--text);font:14px/1.5 -apple-system,BlinkMacSystemFont,"Segoe UI","Noto Sans",Helvetica,Arial,sans-serif}}
main{{max-width:960px;margin:0 auto;padding:22px 20px 36px}} a{{color:inherit}}
nav{{color:var(--muted);font-size:13px;margin-bottom:14px}} nav a{{text-decoration:none}}
h1{{font-size:28px;line-height:1.25;margin:0;font-weight:700;letter-spacing:-.2px}}
h1 .b{{color:{own_c}}} h1 .g{{color:{linked_c}}} h1 .sep{{color:var(--muted);font-weight:400;margin:0 6px}}
.track{{height:12px;border-radius:6px;background:var(--track);overflow:hidden;position:relative;margin:14px 0 8px}}
.fill{{position:absolute;inset:0 auto 0 0;transition:width .35s ease}}
.key{{display:flex;gap:16px;flex-wrap:wrap;color:var(--muted);font-size:12.5px;align-items:center}}
.key i{{display:inline-block;width:10px;height:10px;border-radius:2px;margin-right:5px;vertical-align:-1px}}
.tabs{{display:flex;gap:4px;flex-wrap:wrap;margin:14px 0 0}}
.tabs button{{background:none;color:var(--muted);border:1px solid var(--line);border-radius:999px;padding:2px 10px;font:inherit;font-size:12.5px;cursor:pointer}}
.tabs button.on{{background:var(--text);color:var(--bg);border-color:var(--text)}}
.note{{color:var(--muted);font-size:12.5px;margin-top:6px}} .note:empty{{display:none}}
h2{{display:flex;gap:14px;align-items:baseline;font-size:12px;letter-spacing:1.2px;text-transform:uppercase;color:var(--muted);margin:26px 0 8px;font-weight:600}}
h2 .key{{text-transform:none;letter-spacing:0;font-weight:400}}
.chart{{width:100%;height:auto;display:block}} .chart .grid{{stroke:var(--line);stroke-width:1}} .chart .axis{{fill:var(--muted);font-size:12px}}
.chart .hit{{fill:transparent}} .chart .hit:hover{{fill:{own_c};opacity:.35}}
.map{{position:relative;width:100%;aspect-ratio:1100/340;border-radius:6px;overflow:hidden;background:var(--line)}}
.tile{{position:absolute;border:1px solid var(--bg);overflow:hidden;transition:opacity .2s}} .tile span{{position:absolute;left:3px;right:3px;top:1px;color:#fff;text-shadow:0 1px 2px #000c;overflow:hidden;line-height:1.35;display:-webkit-box;-webkit-box-orient:vertical;overflow-wrap:normal}}
.tile.dim{{opacity:.15}} .tile .lk{{position:absolute;left:0;top:0;bottom:0}}
.lk,.dots{{background:radial-gradient(circle,{other_c} 1.1px,transparent 1.3px) 0 0/5px 5px,{linked_c}}}
footer{{margin-top:22px;color:var(--muted);font-size:12px;line-height:1.6}} footer code{{font-size:11.5px}}
</style></head><body><main>
<nav><a href="https://github.com/Open-BFME/Open-BFME-1">Open-BFME</a> / BFME 1 / Progress</nav>
<h1 id="headline"><span id="who">BFME 1</span> is <span class="b" id="mp">{matched_pct}%</span> byte-matched<span class="sep">·</span><span class="g" id="lp">{linked_pct}%</span> linked</h1>
<div class="track"><div class="fill" id="m" style="width:{matched_w}%;background:{other_c}"></div><div class="fill" id="o" style="width:{own_w}%;background:{own_c}"></div><div class="fill dots" id="l" style="width:{linked_w}%"></div></div>
<div class="key"><span><i class="dots"></i>Linked</span><span><i style="background:{own_c}"></i>Byte-matched: our own source</span><span><i style="background:{other_c}"></i>Byte-matched: generated code, Microsoft libraries</span><span><i style="background:var(--rest)"></i>Still original</span><span>Code <b id="codemb">{code_mb} MB</b> · Data {data_mb} MB, not measured yet</span></div>
<div class="tabs" id="tabs">{tabs}</div>
<div class="note" id="note"></div>
<h2>Over time <span class="key"><span><i style="background:{own_c}"></i>byte-matched, daily</span><span><i class="dots"></i>linking, per census</span></span></h2>
{chart}
<h2>Map <span class="key">folders sized by code · hover for numbers</span></h2>
<div class="map" id="map">{tiles}</div>
<footer>Byte-matched: rebuilt to the original exe's exact bytes. Linked: connects into one program.<br>At <a href="https://github.com/Open-BFME/Open-BFME-1/commit/{commit}"><code>{commit}</code></a> ({commit_date}) · {census} · built by <code>tools/progress_site.py</code></footer>
</main>
<script>
const DATA={data};
const pct=(a,b)=>(b?100*a/b:0).toFixed(2);
document.querySelectorAll('#tabs button').forEach(b=>b.onclick=()=>{{
  document.querySelectorAll('#tabs button').forEach(x=>x.classList.toggle('on',x===b));
  const d=DATA[b.dataset.key], all=b.dataset.key==='all';
  document.getElementById('who').textContent=all?'BFME 1':d.label;
  document.getElementById('mp').textContent=pct(d.matched,d.total)+'%';
  document.getElementById('lp').textContent=pct(d.linked,d.total)+'%';
  document.getElementById('m').style.width=pct(d.matched,d.total)+'%';
  document.getElementById('l').style.width=pct(d.linked,d.total)+'%';
  document.getElementById('o').style.width=pct(d.own,d.total)+'%';
  document.getElementById('codemb').textContent=(d.total/1e6).toFixed(2)+' MB';
  document.getElementById('note').textContent=all?'':'This folder only (linked as of the last census). Its unconverted code sits in Dumps.';
  document.querySelectorAll('.tile').forEach(t=>t.classList.toggle('dim',!all&&t.dataset.cat!==b.dataset.key));
}});
</script>
</body></html>
"""


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    hist = sub.add_parser("history")
    hist.add_argument("--backfill", action="store_true")
    hist.add_argument("--today", action="store_true")
    rend = sub.add_parser("render")
    rend.add_argument("out", nargs="?", default=str(progress.ROOT / "build/site/index.html"))
    rend.add_argument("--svg", metavar="DIR", help="also write progress_chart.svg and progress_map.svg there")
    args = parser.parse_args(argv)
    if args.command == "history":
        if args.backfill:
            backfill()
        if args.today:
            today_point()
    else:
        render(Path(args.out), Path(args.svg) if args.svg else None)
    return 0


if __name__ == "__main__":
    sys.exit(main())
