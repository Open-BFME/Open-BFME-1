#!/usr/bin/env python3
"""Progress under rules=v2, published NEXT TO the existing bars (which do not change).

The old bars answer "how much rebuilds to retail's bytes". Every one of them was
moved by things that are not recovered source (FIX_PLAN_v2 rules 2, 3, 8, 9), so
v2 shows what each is made of and puts a counter beside each headline:

  rebuilt from source  = recovered source (authored C++ + vendored library source)
                       + generator-written C++ + attached prebuilt .lib
                       (the old "Rebuilt from source" bar, exactly: the parts sum to it)
                       dumps (MASM `db`, __emit, naked lifts) are shown on their own and
                       were never in the bar
  game code in C++     the authored lane split by what its names rest on: EA name
                       evidence (BFME1: ea_evidence.csv agrees with the row's
                       Class::method), a readable name, or an address-derived name
  link cycle           BFME2: placed at retail RVA / placed + self-strict / closed-strict
                       credit, read from the committed receipt (reverse/link_cycle/
                       receipt.json, stored with --store-receipt); "pending" without one
  counters             escape hatches from the hatch register (tools/hatch_counters.py):
                       pins and pins per matched row, object-symbol alias rows,
                       /alternatename, __emit lines, .asm `db` bytes; and keyed gate
                       debt (baseline lines a repair removes -- repairs are credited here)

History: <reverse>/progress_v2_history.csv, one row per day, `rules` = v2 on every row
(the link census's convention); progress_history.csv is untouched.

  python3 tools/progress_v2.py                       # worktree
  python3 tools/progress_v2.py --ref REF             # one commit
  python3 tools/progress_v2.py --svg OUT.svg         # also render the v2 card
  python3 tools/progress_v2.py --today               # append/replace today's history row
  python3 tools/progress_v2.py --store-receipt build/link_cycle/receipt.json
"""
import argparse
import csv
import io
import json
import re
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import progress  # noqa: E402

RULES = "v2"
ROOT = progress.ROOT
BFME1 = (ROOT / "targets" / "game" / "reverse").is_dir()
REV = "targets/game/reverse" if BFME1 else "reverse"
HISTORY = f"{REV}/progress_v2_history.csv"
RECEIPT = f"{REV}/link_cycle/receipt.json"
HATCHES = f"{REV}/hatch_baseline.tsv"
EVIDENCE = f"{REV}/ea_evidence.csv"
GATE_DEBT = ((f"{REV}/body_guard_baseline.csv", "csv"), (f"{REV}/full_gate_baseline.txt", "lines")) if BFME1 \
    else ((f"{REV}/gate_baseline.txt", "lines"),)
TITLE = "BFME 1" if BFME1 else "BFME 2"

FIELDS = ["date", "commit", "rules", "total", "byte_matched", "recovered", "authored", "vendored",
          "generated", "library", "dump", "cpp_evidence", "cpp_readable", "cpp_address",
          "link_receipt", "link_placed", "link_self_strict", "link_closed_strict",
          "matched_rows", "pins", "alias_rows", "alternatename", "emit", "asm_bytes", "gate_debt"]

# Address-derived names: Rva00C70890…, ?d_00c6bc20@@, sub_/FUN_/dup_/Gen…, ji_…
ADDRESS_NAME = re.compile(r"(?i)(?<![a-z])(?:rva|gen|sub|fun|dup|nullsub|loc|ji|j|d|uw|eh|tg|g_?va|dat)"
                          r"_?[0-9a-f]{5,8}")
LINK_SERIES = (("placed", "placed"), ("self_strict", "placed_self_strict"),
               ("closed_strict", "placed_closed_strict"))


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace").stdout.strip()


def text_at(ref, path):
    return progress._text_at(ref, path)


def demangled(name):
    """`Class::method` of an MSVC name (ctor/dtor too), or None."""
    m = re.match(r"\?\?([01])(\w+)@", name)
    if m:
        return f"{m[2]}::{'~' if m[1] == '1' else ''}{m[2]}"
    m = re.match(r"\?(\w+)@(\w+)@@", name)
    return f"{m[2]}::{m[1]}" if m else None


def evidence_names(ref):
    """{rva: {Class::method}} from EA name evidence, or None when the repo has none."""
    text = text_at(ref, EVIDENCE)
    if text is None:
        return None
    out = {}
    for row in csv.DictReader(io.StringIO(text)):
        if row.get("kind") == "name":
            out.setdefault(int(row["rva"], 16), set()).add(row["value"])
    return out


def name_tier(name, rva, evidence):
    if evidence is not None and demangled(name) in evidence.get(rva, ()):
        return "evidence"
    return "address" if ADDRESS_NAME.search(name) else "readable"


def hatch_totals(ref):
    text = text_at(ref, HATCHES)
    totals = {}
    for line in (text or "").splitlines():
        cells = line.split("\t")
        if len(cells) >= 4 and not line.startswith("#") and cells[3].isdigit():
            totals[cells[0]] = totals.get(cells[0], 0) + int(cells[3])
    return totals if text is not None else None


def gate_debt(ref):
    total = 0
    for path, kind in GATE_DEBT:
        text = text_at(ref, path) or ""
        lines = [l for l in text.splitlines() if l.strip() and not l.startswith("#")]
        total += max(0, len(lines) - 1) if kind == "csv" else len(lines)
    return total


def load_receipt(ref):
    """The committed link-cycle receipt as {series: (rows, bytes, pct)} + provenance, or None."""
    text = text_at(ref, RECEIPT)
    if not text:
        return None
    receipt = json.loads(text)
    real = receipt.get("series", {}).get("real", {})
    out = {"commit": (receipt.get("commit") or "")[:10], "date": receipt.get("date_utc", ""),
           "rules": receipt.get("rules", "")}
    for key, series in LINK_SERIES:
        if series in real:
            entry = real[series]
            out[key] = (entry["rows"], entry["unique_bytes"], entry["pct_text"])
    return out


def store_receipt(src):
    """Copy a link_cycle.py receipt into the committed location, keeping provenance and
    the series and dropping the bulky per-link detail."""
    receipt = json.loads(Path(src).read_text(encoding="utf-8"))
    if receipt.get("tool") != "link_cycle" or "series" not in receipt or "commit" not in receipt:
        sys.exit(f"progress_v2: {src} is not a link_cycle.py receipt")
    keep = ("tool", "rules", "commit", "dirty", "date_utc", "retail_sha256", "toolchain_sha256",
            "tool_digest", "objects_digest", "objects", "inputs", "iterations", "scaffold", "series",
            "seconds", "commit_inputs", "provenance_note")
    out = ROOT / RECEIPT
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps({k: receipt[k] for k in keep if k in receipt}, indent=1, sort_keys=True) + "\n",
                   encoding="utf-8", newline="\n")
    print(f"progress_v2: stored {RECEIPT} (cycle at {receipt['commit'][:10]}, {receipt.get('date_utc')})")


def measure(ref=None):
    """Every v2 figure at one state (ref None: the worktree)."""
    matched, notes = progress.matched_at(ref), progress.notes_at(ref)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, ref)
    split = progress.real_split(matched, notes, start, size, naked)
    _, total = progress.real_code_denominator(start, size)
    evidence = evidence_names(ref)
    tiers = {key: name_tier(key[0], int(key[1], 16), evidence) for key in matched}
    ev = progress.real_split(matched, notes, start, size, naked,
                             keep=lambda key, _: tiers[key] == "evidence")["authored"] if evidence is not None else None
    named = progress.real_split(matched, notes, start, size, naked,
                                keep=lambda key, _: tiers[key] != "address")["authored"]
    hatches = hatch_totals(ref)
    point = {"total": total, "byte_matched": progress.rebuildable(split),
             "recovered": progress.decompiled(split),
             **{lane: split[lane] for lane in progress.SOURCE_LANES},
             "cpp_evidence": ev, "cpp_readable": named - (ev or 0), "cpp_address": split["authored"] - named,
             "matched_rows": len(matched), "gate_debt": gate_debt(ref), "link": load_receipt(ref),
             "hatches": hatches}
    if point["recovered"] + split["generated"] + split["library"] != point["byte_matched"]:
        raise AssertionError("v2 parts do not sum to the old Rebuilt-from-source bar")
    return point


def history_row(point, day, commit):
    link, hatches = point["link"] or {}, point["hatches"] or {}
    row = {"date": day, "commit": commit, "rules": RULES,
           **{k: point[k] for k in ("total", "byte_matched", "recovered", "authored", "vendored", "generated",
                                    "library", "dump", "cpp_readable", "cpp_address", "matched_rows",
                                    "gate_debt")},
           "cpp_evidence": "" if point["cpp_evidence"] is None else point["cpp_evidence"],
           "link_receipt": link.get("commit", ""),
           **{f"link_{key}": (link[key][1] if key in link else "") for key, _ in LINK_SERIES},
           "pins": hatches.get("pin", ""), "alias_rows": hatches.get("object_symbol", ""),
           "alternatename": hatches.get("alternatename", ""), "emit": hatches.get("emit", ""),
           "asm_bytes": hatches.get("asm_bytes", "")}
    return row


def read_history():
    text = text_at(None, HISTORY)
    return list(csv.DictReader(io.StringIO(text))) if text else []


def write_history(rows):
    rows = sorted({row["date"]: row for row in rows}.values(), key=lambda row: row["date"])
    path = ROOT / HISTORY
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def previous_v2(rows, day):
    """The last earlier history row measured under these rules (a rule change is not progress)."""
    earlier = [r for r in rows if r["date"] < day and r.get("rules") == RULES]
    return earlier[-1] if earlier else None


def pct(part, whole):
    return progress.percent(part, whole)


def delta(now, row, field):
    if not row or row.get(field) in (None, ""):
        return ""
    return f"  ({now - int(row[field]):+,} since {row['date']})"


def report(point, prev=None):
    total, lines = point["total"], []
    add = lines.append
    add(f"{TITLE} progress, rules={RULES} (beside the existing bars; they are unchanged)")
    add(f"REBUILT FROM SOURCE (old bar)  {point['byte_matched']:>10,} B {pct(point['byte_matched'], total):6.2f}% "
        f"= the three parts below")
    for label, key in (("recovered source", "recovered"), ("  authored C++", "authored"),
                       ("  vendored library source", "vendored"), ("generator-written C++", "generated"),
                       ("prebuilt .lib attached", "library")):
        add(f"  {label:<28} {point[key]:>10,} B {pct(point[key], total):6.2f}%{delta(point[key], prev, key)}")
    add(f"  {'dumps (not in the bar)':<28} {point['dump']:>10,} B {pct(point['dump'], total):6.2f}%"
        f"  <- MASM db / __emit / naked lifts")
    add("GAME CODE C++ by name evidence (authored lane)")
    ev = point["cpp_evidence"]
    add(f"  {'EA name evidence':<28} " + (f"{ev:>10,} B {pct(ev, total):6.2f}%" if ev is not None
                                         else "       n/a  (no name-evidence file in this repo)"))
    add(f"  {'readable name':<28} {point['cpp_readable']:>10,} B {pct(point['cpp_readable'], total):6.2f}%")
    add(f"  {'address-derived name':<28} {point['cpp_address']:>10,} B {pct(point['cpp_address'], total):6.2f}%"
        f"{delta(point['cpp_address'], prev, 'cpp_address')}")
    link = point["link"]
    if not link or "placed" not in link:
        add("LINK CYCLE  pending  <- no committed receipt"
            + ("" if BFME1 else f" ({RECEIPT}; tools/progress_v2.py --store-receipt)")
            + (" (BFME1 has no link cycle yet, plan step 9)" if BFME1 else ""))
    else:
        add(f"LINK CYCLE  cycle at {link['commit']} {link['date']} ({link['rules']}), % of retail .text")
        for key, label in (("placed", "placed at retail RVA"), ("self_strict", "placed + self-strict"),
                           ("closed_strict", "closed-strict credit")):
            rows, nbytes, share = link[key]
            add(f"  {label:<28} {nbytes:>10,} B {share:6.2f}%  ({rows:,} rows)")
    hatches = point["hatches"]
    add("COUNTERS (beside the headlines; growth is gaming until a tool proves otherwise)")
    if hatches is None:
        add("  hatch register: not present")
    else:
        pins = hatches.get("pin", 0)
        add(f"  pins {pins:,} ({pins / max(1, point['matched_rows']):.2f} per matched row)"
            f"{delta(pins, prev, 'pins')};  alias rows {hatches.get('object_symbol', 0):,};"
            f"  /alternatename {hatches.get('alternatename', 0):,};  __emit lines {hatches.get('emit', 0):,};"
            f"  .asm db bytes {hatches.get('asm_bytes', 0):,}")
    add(f"  gate debt (keyed baseline lines; a repair removes one) {point['gate_debt']:,}"
        f"{delta(point['gate_debt'], prev, 'gate_debt')}")
    return "\n".join(lines)


def svg(point):
    """The v2 card: the old bar as its stacked parts, the C++ bar by name evidence, the
    link-cycle series (or pending), and the counters line."""
    total, width = point["total"], 824
    colors = {"recovered": "#2ea043", "generated": "#7ee2a8", "library": "#3d5a45", "evidence": "#1f6feb",
              "readable": "#388bfd", "address": "#a5c8ff", "link": "#d29922"}

    def stack(y, parts):
        x, out = 28.0, []
        for value, color in parts:
            w = width * (value or 0) / total
            out.append(f'<rect x="{x:.2f}" y="{y}" width="{w:.2f}" height="14" fill="{color}"/>')
            x += w
        return "".join(out)

    rows = []
    y = 64
    rows.append(f'<text x="28" y="{y}" class="strong" font-size="15" font-weight="600">Rebuilt from source, '
                f'by kind</text><text x="852" y="{y}" class="strong" font-size="18" font-weight="700" '
                f'text-anchor="end">{pct(point["byte_matched"], total):.2f}%</text>'
                f'<rect class="track" x="28" y="{y + 10}" width="{width}" height="14"/>'
                + stack(y + 10, [(point["recovered"], colors["recovered"]), (point["generated"], colors["generated"]),
                                 (point["library"], colors["library"])])
                + f'<text x="28" y="{y + 44}" class="muted" font-size="12.5">recovered source '
                f'{pct(point["recovered"], total):.2f}% + generator C++ {pct(point["generated"], total):.2f}% + '
                f'prebuilt .lib {pct(point["library"], total):.2f}%; dumps {pct(point["dump"], total):.2f}% '
                f'not counted</text>')
    y += 74
    ev = point["cpp_evidence"]
    rows.append(f'<text x="28" y="{y}" class="strong" font-size="15" font-weight="600">Authored C++, by name'
                f'</text><text x="852" y="{y}" class="strong" font-size="18" font-weight="700" text-anchor="end">'
                f'{pct(point["authored"], total):.2f}%</text>'
                f'<rect class="track" x="28" y="{y + 10}" width="{width}" height="14"/>'
                + stack(y + 10, [(ev, colors["evidence"]), (point["cpp_readable"], colors["readable"]),
                                 (point["cpp_address"], colors["address"])])
                + f'<text x="28" y="{y + 44}" class="muted" font-size="12.5">'
                + (f"EA name evidence {pct(ev, total):.2f}%, " if ev is not None else "")
                + f'readable name {pct(point["cpp_readable"], total):.2f}%, address-derived name '
                f'{pct(point["cpp_address"], total):.2f}% (of all code)</text>')
    y += 74
    link = point["link"]
    if link and "placed" in link:
        text = (f'placed {link["placed"][2]:.2f}%, placed + self-strict {link["self_strict"][2]:.2f}%, '
                f'closed-strict credit {link["closed_strict"][2]:.2f}% (cycle at {link["commit"]})')
        number = f'{link["closed_strict"][2]:.2f}%'
        bar = stack(y + 10, [(link["closed_strict"][1], colors["link"])])
    else:
        text, number, bar = "pending: no committed link-cycle receipt", "pending", ""
    rows.append(f'<text x="28" y="{y}" class="strong" font-size="15" font-weight="600">Real link, '
                f'closed-strict</text><text x="852" y="{y}" class="strong" font-size="18" font-weight="700" '
                f'text-anchor="end">{number}</text><rect class="track" x="28" y="{y + 10}" width="{width}" '
                f'height="14"/>{bar}<text x="28" y="{y + 44}" class="muted" font-size="12.5">{text}</text>')
    y += 74
    h = point["hatches"] or {}
    rows.append(f'<text x="28" y="{y - 10}" class="muted" font-size="12.5">counters: pins {h.get("pin", 0):,} '
                f'({h.get("pin", 0) / max(1, point["matched_rows"]):.2f}/row), alias rows '
                f'{h.get("object_symbol", 0):,}, /alternatename {h.get("alternatename", 0):,}, __emit '
                f'{h.get("emit", 0):,}, asm db bytes {h.get("asm_bytes", 0):,}, gate debt {point["gate_debt"]:,}'
                f'</text>')
    height = y + 10
    body = "\n    ".join(rows)
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="880" height="{height}" viewBox="0 0 880 {height}" role="img">
  <title>{TITLE} rules={RULES}: {pct(point["recovered"], total):.2f}% recovered source</title>
  <style>
    .card {{ fill: #0d1117; stroke: #30363d; }} .track {{ fill: #21262d; }}
    .strong {{ fill: #f0f6fc; }} .muted {{ fill: #8b949e; }}
    @media (prefers-color-scheme: light) {{
      .card {{ fill: #ffffff; stroke: #d0d7de; }} .track {{ fill: #eaeef2; }}
      .strong {{ fill: #1f2328; }} .muted {{ fill: #59636e; }}
    }}
  </style>
  <rect class="card" x="0.5" y="0.5" width="879" height="{height - 1}" rx="12"/>
  <g font-family="-apple-system,BlinkMacSystemFont,'Segoe UI','Noto Sans',Helvetica,Arial,sans-serif">
    <text x="28" y="30" class="muted" font-size="13" font-weight="600" letter-spacing="1.3">{TITLE} · RULES V2 · WHAT THE BARS ARE MADE OF</text>
    {body}
  </g>
</svg>
'''


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ref", help="measure this commit instead of the worktree")
    ap.add_argument("--svg", metavar="OUT", help="also write the v2 card")
    ap.add_argument("--today", action="store_true", help="append/replace today's row in the v2 history")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--store-receipt", metavar="RECEIPT")
    args = ap.parse_args(argv)
    if args.store_receipt:
        store_receipt(args.store_receipt)
        return 0
    point = measure(args.ref)
    day = datetime.now(timezone.utc).date().isoformat()
    rows = read_history()
    if args.json:
        print(json.dumps(point, indent=1))
    else:
        print(report(point, previous_v2(rows, day)))
    if args.svg:
        Path(args.svg).write_text(svg(point), encoding="utf-8", newline="\n")
    if args.today:
        commit = git("rev-parse", "--short=10", args.ref or "HEAD")
        write_history(rows + [history_row(point, day, commit)])
    return 0


if __name__ == "__main__":
    sys.exit(main())
