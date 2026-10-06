#!/usr/bin/env python3
"""Blinded, stratified sample of landed commits/rows for the nightly judge panel.

At thousands of BFME2 commits a day, thirty uniform picks see under 1% and
almost never the risky ones, so the budget is split:

  - UNIFORM_SHARE of it is a plain uniform random draw over every eligible
    commit (the unbiased estimate of the defect rate);
  - the rest is spread round-robin over risk strata, each drawn at random:
      bytes:small|mid|large   matched bytes the commit added or changed
      deps:low|high           headers touched / #includes in touched units
      header, alias, global, eh, comdat, large   risk flags (see flags())

Each picked commit contributes one row (the row that put it in its stratum,
else a random changed row). The RNG seed is derived from the date and the
window tip and recorded, so a night can be replayed exactly.

Blinding: the packet a judge sees is the row's function as landed plus retail
evidence. It carries no commit id, diff, author, date, commit
message or ledger notes (the author's own explanation), and model/agent
identities in the source text are redacted. The source is untrusted data:
it is fenced between per-packet random markers and the rubric tells the judge
that instructions inside the fence are themselves a finding.

  python3 tools/audit/sampler.py --last 200 --n 10 [--seed S] [--json]
"""
import argparse
import json
import random
import re
import secrets
import sys

import common

UNIFORM_SHARE = 0.3
BYTES = ((64, "bytes:small"), (512, "bytes:mid"), (1 << 62, "bytes:large"))
RISK = ("header", "alias", "global", "eh", "comdat", "large")
LARGE = 1024
EXCERPT_LINES = 160
PREAMBLE_LINES = 60
IDENTITY = re.compile(
    r"(?i)\b(?:gpt-[\w.\-]+|o\d-[\w.\-]+|claude[\w.\-]*|opus[\w.\-]*|sonnet[\w.\-]*|haiku[\w.\-]*|fable[\w.\-]*"
    r"|codex[\w.\-]*|gemini[\w.\-]*|kimi[\w.\-]*|qwen[\w.\-]*|deepseek[\w.\-]*|glm[\w.\-]*|grok[\w.\-]*"
    r"|minimax[\w.\-]*|model\s*[=:]\s*\S+|seat[\-_ ]?\w+|co-authored-by:.*|signed-off-by:.*)")


def window(last=None, since=None, ref=None):
    args = ["log", "--no-merges", "--format=%H", ref or common.REF]
    if since:
        args.append(f"--since={since}")
    if last:
        args.append(f"-{last}")
    return common.git(*args).split()


def flags(files, rows, diff_text):
    out = set()
    if any(f.lower().endswith((".h", ".hpp", ".inl")) for f in files):
        out.add("header")
    notes = " ".join((r.get("notes") or "") + " " + r.get("name", "") for r in rows)
    if re.search(r"(?i)alias|object-symbol|alternatename", notes + diff_text) or common.SYMBOLS in files:
        out.add("alias")
    if re.search(r"(?i)\bg_?rva[0-9a-f]{6,8}|\bDAT_|^\+\s*(?:extern|static)\s+\w[\w\s\*]*\bg_\w+", diff_text, re.M) or \
            any("data_rows" in f for f in files):
        out.add("global")
    if re.search(r"(?i)funclet|unwind|\beh\b|\btry\b|\bcatch\b|__except|__finally", notes + diff_text):
        out.add("eh")
    if re.search(r"(?i)comdat|selectany|\binline\b", notes + diff_text):
        out.add("comdat")
    if any(int(r.get("target_size") or 0) >= LARGE for r in rows):
        out.add("large")
    return out


def describe(sha, files, ledger_lines, diff_text, header):
    """One commit's sampling unit (None when it landed no matched row)."""
    rows = [r for r in common.read_rows("\n".join([header, *ledger_lines]))
            if r.get("status") == "matched" and common.parse_rva(r.get("target_rva")) is not None]
    if not rows:
        return None
    size = sum(int(r.get("target_size") or 0) for r in rows)
    includes = len(re.findall(r"^\+\s*#\s*include", diff_text, re.M))
    headers = sum(f.lower().endswith((".h", ".hpp", ".inl")) for f in files)
    strata = {next(label for limit, label in BYTES if size < limit),
              "deps:high" if headers or includes >= 4 else "deps:low"} | flags(files, rows, diff_text)
    return {"sha": sha, "files": files, "rows": rows, "bytes": size, "strata": sorted(strata)}


def units(shas):
    """Sampling units for commits, from ONE `git log -p` pass (thousands of commits a night)."""
    if not shas:
        return []
    header = (common.show(shas[0], common.LEDGER) or "").split("\n", 1)[0]
    wanted = set(shas)
    out = []
    # --stdin keeps a long commit list off the command line
    proc = common.subprocess.run(
        ["git", "log", "--no-walk=unsorted", "--stdin", "-p", "-U0", "--no-renames", "--format=%x00%H"],
        cwd=common.ROOT, input="\n".join(shas), capture_output=True, text=True, encoding="utf-8",
        errors="replace")
    for chunk in proc.stdout.split("\x00")[1:]:
        sha, _, body = chunk.partition("\n")
        if sha not in wanted:
            continue
        files, ledger_lines, diff_lines, current = [], [], [], None
        for line in body.splitlines():
            if line.startswith("diff --git "):
                current = line.split(" b/", 1)[-1]
                files.append(current)
            elif line.startswith(("+++", "---", "index ", "@@", "new file", "deleted file")):
                continue
            elif current == common.LEDGER:
                if line.startswith("+"):
                    ledger_lines.append(line[1:])
            elif current and common.is_source(current) and len(diff_lines) < 4000:
                diff_lines.append(line)
        unit = describe(sha, files, ledger_lines, "\n".join(diff_lines), header)
        if unit:
            out.append(unit)
    return out


def stratified(units, n, rng, uniform_share=UNIFORM_SHARE):
    """Pick n units: a uniform share first, then round-robin over strata. Returns [(unit, why)]."""
    pool = list(units)
    picked, seen = [], set()
    n_uniform = min(len(pool), max(1, round(n * uniform_share))) if n else 0
    for unit in rng.sample(pool, n_uniform):
        picked.append((unit, "uniform"))
        seen.add(unit["sha"])
    strata = sorted({s for u in pool for s in u["strata"]},
                    key=lambda s: (s not in RISK, s))  # risk strata first
    by = {s: [u for u in pool if s in u["strata"]] for s in strata}
    for members in by.values():
        rng.shuffle(members)
    while len(picked) < min(n, len(pool)) and any(by.values()):
        for s in strata:
            while by[s] and by[s][-1]["sha"] in seen:
                by[s].pop()
            if by[s] and len(picked) < n:
                unit = by[s].pop()
                picked.append((unit, s))
                seen.add(unit["sha"])
    return picked


def pick_row(unit, why, rng):
    rows = unit["rows"]
    if why == "large":
        rows = [r for r in rows if int(r.get("target_size") or 0) >= LARGE] or rows
    elif why in ("eh", "alias", "comdat"):
        key = {"eh": r"(?i)funclet|unwind|eh", "alias": r"(?i)alias|object-symbol", "comdat": r"(?i)comdat|inline"}[why]
        rows = [r for r in rows if re.search(key, r.get("notes") or "")] or rows
    return rng.choice(rows)


def redact(text):
    return IDENTITY.sub("[redacted]", text)


def function_excerpt(text, row):
    """The row's function (by its leaf name, braces balanced) plus the file preamble, capped."""
    lines = text.splitlines()
    leaf = common.leaf_name(row.get("name"))
    start = None
    if leaf:
        pat = re.compile(r"(?<![\w~])~?" + re.escape(leaf) + r"\s*\(")
        for i, line in enumerate(lines):
            if pat.search(line) and not line.rstrip().endswith(";"):
                start = i
                break
    if start is None:
        return "\n".join(lines[:EXCERPT_LINES]), 0, min(len(lines), EXCERPT_LINES)
    depth, end, opened = 0, start, False
    for end in range(start, min(len(lines), start + EXCERPT_LINES)):
        depth += lines[end].count("{") - lines[end].count("}")
        opened = opened or "{" in lines[end]
        if opened and depth <= 0:
            break
    pre = lines[:min(PREAMBLE_LINES, start)]
    body = lines[start:end + 1]
    gap = ["// ... (lines omitted) ..."] if start > PREAMBLE_LINES else []
    return "\n".join(pre + gap + body), start, end + 1


def build_packet(unit, row, salt, rev=None):
    """The blinded packet for one (commit, row). Returns (packet, private) - private never reaches a judge."""
    import evidence
    rev = rev or unit["sha"]
    source = row["source"]
    text = common.show(rev, source) or ""
    excerpt, start, end = function_excerpt(text, row)
    rva, size = common.parse_rva(row["target_rva"]), int(row.get("target_size") or 0)
    packet = {
        "id": common.digest(salt, unit["sha"], row["target_rva"], n=10),
        "repo": common.REPO,
        "row": {"name": row["name"], "readable": common.short_name(row["name"]),
                "rva": f"0x{rva:08X}", "size": size, "source": source},
        "source_excerpt": redact(excerpt),
        "retail": evidence.retail_evidence(rva, size),
    }
    private = {"sha": unit["sha"], "strata": unit["strata"], "notes": row.get("notes", ""),
               "excerpt_lines": [start, end]}
    return packet, private


def sample(shas, n, seed):
    rng = random.Random(seed)
    pool = units(shas)
    picked = stratified(pool, n, rng)
    return [(u, why, pick_row(u, why, rng)) for u, why in picked], len(pool)


def nonce():
    return secrets.token_hex(6)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--last", type=int, default=200)
    ap.add_argument("--since")
    ap.add_argument("--n", type=int, default=10)
    ap.add_argument("--seed", default="manual")
    ap.add_argument("--json", action="store_true", help="print the blinded packets")
    args = ap.parse_args(argv)
    picked, eligible = sample(window(args.last, args.since), args.n, args.seed)
    print(f"{eligible} eligible commits, {len(picked)} sampled (seed {args.seed!r})")
    for unit, why, row in picked:
        print(f"  {unit['sha'][:10]} {why:12} {row['target_rva']} {row['target_size']:>5}B "
              f"{row['source']} [{' '.join(unit['strata'])}]")
        if args.json:
            print(json.dumps(build_packet(unit, row, args.seed)[0], indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
