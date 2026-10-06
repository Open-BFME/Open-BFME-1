#!/usr/bin/env python3
"""Escape-hatch counters: a keyed, shrink-only register of every way around the byte gate.

Each hatch below lets a row match without the source saying what retail's
source said: a selectany definition, a hand `/alternatename`, a symbols.csv
pin, an `object-symbol=` alias row, a global named after its address, a
`class-gate: allow`, a `present-unmatched` marker, a `#pragma optimize`, an
`__emit` line, a `db` byte in an .asm dump. None is wrong on its own; growth
of any of them is how a fleet routes around a check it cannot pass.

The baseline (BASELINE below) has one line per occurrence key:

    hatch <TAB> path <TAB> token <TAB> count [<TAB> allow=<blob>]

RULES (the commit gate, --staged):
  1. A staged file may not hold more occurrences of a key than the staged
     baseline grants it.
  2. A baseline line may only shrink by hand. A lower count is re-verified:
     the staged file must really hold no more than that.
  3. A baseline line may grow only (a) as a move, when the hatch+token total
     over the whole baseline does not grow (a renamed file, a function moved
     between units; `--update` writes it), or (b) through a tool-written
     allowance, `--allow PATH --reason TEXT`, whose allow=<blob> is the git
     blob of the staged file it describes.
  4. Anomaly freeze: if a hatch's baseline total would exceed twice its total
     24 h ago (and by at least FREEZE_MIN), allowances for that hatch are
     refused until a commit carrying the trailer
         Verifier-Change: hatch-freeze-lift <hatch|all> <reason>
     lands; the lift commit's total becomes the new reference.
  5. The retail inventories (tools/retail_inventory.py) are tool-owned: a
     staged change to them is regenerated and must match byte for byte.
  6. A register line `# mode: shadow` reports rule 1-4 findings without
     refusing (the 48 h shadow before enforcement). `# mode: enforce` (also
     the default) refuses; enforce may never go back to shadow. Rule 5, a
     deleted register and a wrong first register are refused in both modes.

Usage:
  python3 tools/hatch_counters.py --staged              the commit gate
  python3 tools/hatch_counters.py --report              per-hatch totals (HEAD baseline vs tree)
  python3 tools/hatch_counters.py --update              rewrite the baseline from the tree;
                                                        shrinks and moves only
  python3 tools/hatch_counters.py --allow PATH... --reason TEXT
                                                        also admit growth in PATHs (tool allowance)
  python3 tools/hatch_counters.py --write-baseline      first baseline only (refuses if one exists)
"""
import argparse
import collections
import csv
import io
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(os.environ.get("HATCH_ROOT") or Path(__file__).resolve().parent.parent)

if (ROOT / "targets" / "game" / "reverse").is_dir():      # Open-BFME-1
    BASELINE = "targets/game/reverse/hatch_baseline.tsv"
    SOURCE_ROOTS = ("game/", "worldbuilder/")
    PIN_FILE = re.compile(r"^targets/[^/]+/reverse/symbols\.csv$")
    LEDGER_FILE = re.compile(r"^targets/[^/]+/reverse/functions\.csv$")
    INVENTORY_DIR = "targets/game/reverse/retail_inventory/"
else:                                                       # Open-BFME-2
    BASELINE = "reverse/hatch_baseline.tsv"
    SOURCE_ROOTS = ("Code/", "reference/shims/")
    PIN_FILE = re.compile(r"^reverse/symbols\.csv$")
    LEDGER_FILE = re.compile(r"^reverse/functions\.csv$")
    INVENTORY_DIR = "reverse/retail_inventory/"

CODE_EXT = (".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".inl")
FREEZE_WINDOW = 24 * 3600
FREEZE_MIN = 5
LIFT = re.compile(r"^Verifier-Change:[ \t]*hatch-freeze-lift[ \t]+(\S+)", re.MULTILINE)

HATCHES = ("selectany", "alternatename", "pin", "object_symbol", "address_global",
           "class_gate_allow", "present_unmatched", "pragma_optimize", "emit", "asm_bytes")

SELECTANY = re.compile(r"__declspec\s*\(\s*selectany\s*\)")
ALTNAME = re.compile(r"/alternatename:([^=\s\"]+)=([^\s\"]+)", re.IGNORECASE)
PRAGMA_OPT = re.compile(r"^\s*#\s*pragma\s+optimize\s*\(([^)]*)\)")
EMIT = re.compile(r"\b__emit\b")
ADDR_GLOBAL = re.compile(r"(?<![A-Za-z0-9_])g_\w*?(?:Va|VA|Rva|RVA|DAT_?)[0-9A-Fa-f]{6,8}\w*")
CLASS_ALLOW = re.compile(r"class-gate:\s*allow\s+(\S+)")
PRESENT = re.compile(r"(\S+)\s+present-unmatched\b")
DB = re.compile(r"^\s*(?:[A-Za-z_$?@][\w$?@]*\s+)?db\s+(.+)$", re.IGNORECASE)


def git(*args, binary=False, check=False):
    got = subprocess.run(["git", *args], cwd=ROOT, capture_output=True)
    if check and got.returncode:
        sys.exit("hatch_counters: git %s failed: %s" % (" ".join(args), got.stderr.decode(errors="replace")))
    return got.stdout if binary else got.stdout.decode("utf-8", "replace")


def relevant(path):
    if PIN_FILE.match(path) or LEDGER_FILE.match(path):
        return True
    return path.startswith(SOURCE_ROOTS) and path.lower().endswith(CODE_EXT + (".asm",))


def _strip_comment(line):
    i = line.find("//")
    return line if i < 0 else line[:i]


def _db_bytes(arg):
    n = 0
    for item in re.findall(r"'[^']*'|\"[^\"]*\"|[^,]+", arg.split(";", 1)[0]):
        item = item.strip()
        if not item:
            continue
        n += len(item) - 2 if item[0] in "'\"" else 1
    return n


def scan(path, text):
    """Counter of (hatch, path, token) for one file's text."""
    out = collections.Counter()
    if PIN_FILE.match(path) or LEDGER_FILE.match(path):
        pin = bool(PIN_FILE.match(path))
        rows = csv.reader(io.StringIO(text))
        next(rows, None)
        for cells in rows:
            if pin and len(cells) >= 2:
                out[("pin", path, "%s@%s" % (cells[0], cells[1]))] += 1
            elif not pin and len(cells) >= 7 and "object-symbol=" in cells[6]:
                out[("object_symbol", path, "%s@%s" % (cells[0], cells[2]))] += 1
        return out
    if path.lower().endswith(".asm"):
        total = 0
        for line in text.splitlines():
            m = DB.match(line.split(";", 1)[0] if "'" not in line else line)
            if m:
                total += _db_bytes(m.group(1))
        if total:
            out[("asm_bytes", path, "*")] = total
        return out
    for line in text.splitlines():
        m = CLASS_ALLOW.search(line)
        if m:
            out[("class_gate_allow", path, m.group(1))] += 1
        for m in PRESENT.finditer(line):
            out[("present_unmatched", path, m.group(1).lstrip("/?") or "?")] += 1
        code = _strip_comment(line)
        if "__" in code or "#" in code or "/" in code:
            if SELECTANY.search(code):
                out[("selectany", path, " ".join(code.split())[:160])] += 1
            for m in ALTNAME.finditer(code):
                out[("alternatename", path, m.group(1))] += 1
            m = PRAGMA_OPT.match(code)
            if m:
                out[("pragma_optimize", path, "".join(m.group(1).split()))] += 1
            n = len(EMIT.findall(code))
            if n:
                out[("emit", path, "*")] += n
        if "g_" in code:
            for m in ADDR_GLOBAL.finditer(code):
                out[("address_global", path, m.group(0))] += 1
    return out


# ---------------------------------------------------------------- baseline io

def parse(text):
    """{key: count}, {key: allow-blob}. Duplicate keys (a union merge) keep the lowest count."""
    counts, allow = {}, {}
    for line in text.splitlines():
        if not line or line.startswith("#"):
            continue
        cells = line.split("\t")
        if len(cells) < 4 or cells[0] not in HATCHES:
            continue
        key = (cells[0], cells[1], cells[2])
        try:
            n = int(cells[3])
        except ValueError:
            continue
        counts[key] = min(n, counts.get(key, n))
        if len(cells) > 4 and cells[4].startswith("allow="):
            allow[key] = cells[4][6:]
    return counts, allow


MODE = re.compile(r"^# mode: (shadow|enforce)[ \t]*$", re.MULTILINE)
STATE = {"mode": "enforce"}


def mode_of(text):
    """`# mode: shadow` reports growth without refusing it (the 48 h shadow); the default and
    `# mode: enforce` refuse. Shadow -> enforce is one line; enforce -> shadow is refused."""
    m = MODE.search(text or "")
    return m.group(1) if m else "enforce"


def render(counts, allow=None, mode="enforce"):
    allow = allow or {}
    out = ["# Escape-hatch register, shrink-only. Written by tools/hatch_counters.py; you may lower or",
           "# delete lines by hand (re-verified), never raise or add them. hatch\tpath\ttoken\tcount",
           "# mode: %s" % mode]
    for key in sorted(counts):
        if counts[key] <= 0:
            continue
        line = "%s\t%s\t%s\t%d" % (key + (counts[key],))
        if key in allow:
            line += "\tallow=" + allow[key]
        out.append(line)
    return "\n".join(out) + "\n"


def totals(counts):
    t = collections.Counter()
    for (hatch, _, _), n in counts.items():
        t[hatch] += n
    return t


def by_token(counts):
    t = collections.Counter()
    for (hatch, _, token), n in counts.items():
        t[(hatch, token)] += n
    return t


def read_blobs(specs):
    """{spec: text or None} through one `git cat-file --batch`."""
    if not specs:
        return {}
    data = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT, capture_output=True,
                          input=("\n".join(specs) + "\n").encode()).stdout
    out, pos = {}, 0
    for spec in specs:
        nl = data.index(b"\n", pos)
        head = data[pos:nl].split()
        pos = nl + 1
        if len(head) < 3 or head[1] != b"blob":
            out[spec] = None
            continue
        size = int(head[2])
        out[spec] = data[pos:pos + size].decode("utf-8", "replace")
        pos += size + 1
    return out


def index_blob_ids(paths):
    out = {}
    if not paths:
        return out
    for line in git("ls-files", "-s", "--", *paths).splitlines():
        meta, _, path = line.partition("\t")
        out[path] = meta.split()[1]
    return out


def tree_scan():
    """Occurrences over every tracked relevant file, read from the work tree."""
    counts = collections.Counter()
    for path in git("ls-files", "-z").split("\0"):
        if path and relevant(path):
            try:
                text = (ROOT / path).read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            counts.update(scan(path, text))
    return counts


# ---------------------------------------------------------------- freeze

def _commit_at_or_before(when, tip="HEAD"):
    return git("rev-list", "-1", "--first-parent", "--before=%d" % when, tip).strip() or None


def reference_totals(now=None):
    """{hatch: total} the freeze compares against: the baseline 24 h ago, or at the latest
    commit since then that lifted the freeze for that hatch. {} when there is no history."""
    now = now or int(os.environ.get("HATCH_NOW") or time.time())
    ref = _commit_at_or_before(now - FREEZE_WINDOW)
    if not ref:
        return {}
    texts = read_blobs(["%s:%s" % (ref, BASELINE)])
    base = texts["%s:%s" % (ref, BASELINE)]
    if base is None:
        return {}
    ref_totals = dict(totals(parse(base)[0]))
    for hatch in HATCHES:
        ref_totals.setdefault(hatch, 0)
    lifts = git("log", "--first-parent", "--format=%H%x00%B%x01", "%s..HEAD" % ref)
    lifted = {}
    for entry in lifts.split("\x01"):           # newest first
        sha, _, body = entry.strip().partition("\x00")
        for m in LIFT.finditer(body):
            for hatch in (HATCHES if m.group(1) == "all" else (m.group(1),)):
                lifted.setdefault(hatch, sha)
    for hatch, sha in lifted.items():
        text = read_blobs(["%s:%s" % (sha, BASELINE)])["%s:%s" % (sha, BASELINE)]
        if text is not None:
            ref_totals[hatch] = totals(parse(text)[0]).get(hatch, 0)
    return ref_totals


def frozen(hatch, new_total, ref_totals):
    old = ref_totals.get(hatch)
    return old is not None and new_total > 2 * old and new_total - old >= FREEZE_MIN


# ---------------------------------------------------------------- the gate

def check_staged():
    """(errors, warnings, hard): `errors` are reported only while the register is in
    `# mode: shadow`; `hard` (inventory edits, a deleted or downgraded register) always fail."""
    hard = []
    errors, warnings = _check_staged(hard)
    return errors, warnings, hard


def _check_staged(hard):
    errors, warnings = [], []
    changed = git("diff", "--cached", "--name-only", "--no-renames", "-z").split("\0")
    inv = [p for p in changed if p.startswith(INVENTORY_DIR)]
    if inv:
        hard += check_inventory(inv)
    touched = [p for p in changed if relevant(p)]
    if not touched and BASELINE not in changed:
        return errors, warnings                     # nothing this gate reads was staged
    staged_base = read_blobs([":" + BASELINE])[":" + BASELINE]
    STATE["mode"] = mode_of(staged_base)
    parents = ["HEAD"]
    merge_head = git("rev-parse", "-q", "--verify", "MERGE_HEAD").strip()
    if merge_head:
        parents.append(merge_head)
    if BASELINE in changed or merge_head:
        parent_texts = read_blobs(["%s:%s" % (p, BASELINE) for p in parents])
    else:                                           # register untouched: it is its own parent
        parent_texts = {"HEAD": staged_base}
    introduced = all(t is None for t in parent_texts.values())
    if staged_base is None:
        if not introduced:
            hard.append("%s deleted; the register may shrink line by line, never disappear" % BASELINE)
        return errors, warnings                     # register not introduced yet
    if STATE["mode"] == "shadow" and any(MODE.search(t or "") and mode_of(t) == "enforce" for t in parent_texts.values()):
        hard.append("%s: '# mode: enforce' may not go back to shadow" % BASELINE)
    if BASELINE not in changed and not merge_head:
        # Only the touched files' lines matter: filter before parsing the 40k-line register.
        want = set(touched)
        staged_base = "\n".join(l for l in staged_base.splitlines() if l.split("\t", 2)[1:2] and
                                l.split("\t", 2)[1] in want)
        parent_texts = {"HEAD": staged_base}
    b1, allow1 = parse(staged_base)
    if introduced:
        # The commit that introduces the register must record the tree exactly (one full scan, once).
        if b1 != dict(tree_scan()):
            hard.append("%s does not match the tree; write it with --write-baseline" % BASELINE)
        return errors, warnings
    b0 = {}
    for text in parent_texts.values():
        for key, n in parse(text or "")[0].items():
            b0[key] = max(n, b0.get(key, 0))
    lowered = sorted({k[1] for k in set(b0) | set(b1) if b1.get(k, 0) < b0.get(k, 0)})
    paths = sorted(set(touched) | set(lowered))
    texts = read_blobs([":" + p for p in paths])
    actual = collections.Counter()
    for p in paths:
        if texts[":" + p] is not None:
            actual.update(scan(p, texts[":" + p]))
    seen = {k for k in actual} | {k for k in b1 if k[1] in set(paths)}
    for key in sorted(seen):
        if key[1] not in set(paths):
            continue
        a, g = actual.get(key, 0), b1.get(key, 0)
        if a > g:
            errors.append("%s +%d in %s: %s (register grants %d)" % (key[0], a - g, key[1], key[2], g))
        elif a < g and key[1] in set(touched):
            warnings.append("%s: %s in %s is down to %d (register says %d)" % (key[0], key[2], key[1], a, g))
    # growth of the register itself
    tok0, tok1 = by_token(b0), by_token(b1)
    grown = sorted(k for k in b1 if b1[k] > b0.get(k, 0) and tok1[(k[0], k[2])] > tok0.get((k[0], k[2]), 0))
    if grown:
        blobs = index_blob_ids(sorted({k[1] for k in grown}))
        need_freeze = set()
        for key in grown:
            if allow1.get(key) and allow1[key] == blobs.get(key[1]):
                need_freeze.add(key[0])
            else:
                errors.append("register line raised by hand: %s %s %s %d -> %d (only "
                              "`tools/hatch_counters.py --allow` may raise a line)"
                              % (key[0], key[1], key[2], b0.get(key, 0), b1[key]))
        if need_freeze:
            ref = reference_totals()
            t1 = totals(b1)
            for hatch in sorted(need_freeze):
                if frozen(hatch, t1[hatch], ref):
                    errors.append("hatch '%s' is FROZEN: register total %d is more than twice its "
                                  "24 h reference %d; no new allowances until a commit with "
                                  "'Verifier-Change: hatch-freeze-lift %s <reason>' lands"
                                  % (hatch, t1[hatch], ref[hatch], hatch))
    return errors, warnings


def check_inventory(paths):
    sys.path.insert(0, str(ROOT / "tools"))
    try:
        import retail_inventory
    except ImportError as exc:
        return ["retail inventory changed but tools/retail_inventory.py is unavailable: %s" % exc]
    return retail_inventory.verify_staged(paths)


# ---------------------------------------------------------------- writers

def write(counts, allow=None, mode="enforce"):
    (ROOT / BASELINE).parent.mkdir(parents=True, exist_ok=True)
    (ROOT / BASELINE).write_text(render(counts, allow, mode), encoding="utf-8", newline="\n")


def update(allow_paths=(), reason=None):
    old_text = (ROOT / BASELINE).read_text(encoding="utf-8") if (ROOT / BASELINE).exists() else None
    if old_text is None:
        sys.exit("hatch_counters: no register yet; --write-baseline creates the first one")
    old, _ = parse(old_text)
    new = tree_scan()
    allow_paths = {p.replace("\\", "/") for p in allow_paths}
    tok_old, tok_new = by_token(old), by_token(new)
    grown = sorted(k for k in new if new[k] > old.get(k, 0) and tok_new[(k[0], k[2])] > tok_old.get((k[0], k[2]), 0))
    refused = [k for k in grown if k[1] not in allow_paths]
    if refused:
        for k in refused[:40]:
            print("  %s +%d in %s: %s" % (k[0], new[k] - old.get(k, 0), k[1], k[2]), file=sys.stderr)
        sys.exit("hatch_counters: %d occurrence key(s) grew; remove them, or admit them with "
                 "--allow PATH --reason TEXT" % len(refused))
    allow = {}
    if grown:
        if not reason or len(reason.strip()) < 8:
            sys.exit("hatch_counters: --allow needs --reason (8+ chars)")
        ref = reference_totals()
        t_new = totals(new)
        for hatch in sorted({k[0] for k in grown}):
            if frozen(hatch, t_new[hatch], ref):
                sys.exit("hatch_counters: hatch '%s' is frozen (total %d vs 24 h reference %d)"
                         % (hatch, t_new[hatch], ref[hatch]))
        ids = {}
        for p in sorted({k[1] for k in grown}):
            ids[p] = git("hash-object", "--", p).strip()
        for k in grown:
            allow[k] = ids[k[1]]
            print("allowed: %s +%d in %s: %s -- %s" % (k[0], new[k] - old.get(k, 0), k[1], k[2], reason))
    write(new, allow, mode_of(old_text))
    t0, t1 = totals(old), totals(new)
    for hatch in HATCHES:
        if t0[hatch] != t1[hatch]:
            print("%-18s %7d -> %7d" % (hatch, t0[hatch], t1[hatch]))


def report():
    head = read_blobs(["HEAD:" + BASELINE])["HEAD:" + BASELINE]
    b = totals(parse(head or "")[0])
    t = totals(tree_scan())
    print("%-18s %10s %10s" % ("hatch", "register", "tree"))
    for hatch in HATCHES:
        print("%-18s %10d %10d" % (hatch, b[hatch], t[hatch]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--staged", action="store_true")
    g.add_argument("--report", action="store_true")
    g.add_argument("--update", action="store_true")
    g.add_argument("--allow", nargs="+", metavar="PATH")
    g.add_argument("--write-baseline", action="store_true")
    ap.add_argument("--reason")
    ap.add_argument("--mode", choices=("shadow", "enforce"), default="enforce",
                    help="--write-baseline only: start in shadow (report, never refuse)")
    args = ap.parse_args(argv)
    if args.staged:
        t = time.time()
        errors, warnings, hard = check_staged()
        if errors and STATE["mode"] == "shadow":
            for e in errors:
                print("hatch_counters: SHADOW (not enforced): " + e, file=sys.stderr)
            errors = []
        errors += hard
        for w in warnings[:20]:
            print("hatch_counters: note: " + w + " -- `tools/hatch_counters.py --update` tightens it",
                  file=sys.stderr)
        for e in errors:
            print("  " + e, file=sys.stderr)
        if errors:
            print("hatch_counters: escape hatches grew (%.2fs). Remove the new occurrence(s); a real "
                  "need is admitted only by `python3 tools/hatch_counters.py --allow PATH --reason TEXT`."
                  % (time.time() - t), file=sys.stderr)
            return 1
        return 0
    if args.report:
        report()
        return 0
    if args.write_baseline:
        if (ROOT / BASELINE).exists():
            sys.exit("hatch_counters: %s exists; use --update (shrink/move) or --allow" % BASELINE)
        write(tree_scan(), mode=args.mode)
        return 0
    update(args.allow or (), args.reason)
    return 0


if __name__ == "__main__":
    sys.exit(main())
