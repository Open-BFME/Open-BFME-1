#!/usr/bin/env python3
"""Apply the ILT oracle's safe renames (tools/ilt_oracle.py repair) by tool, never by hand.

A repair lands only when (a) the oracle confirms the new name and contradicts the old one at the
row's address, (b) its search's expected-false count is within BOUND (per row; the run's total is
printed), and (c) every source file the rename touches still passes `python3 tools/build.py`.
Each renamed row's notes get `ilt-verified=<method>`; its baseline key is pruned. Kinds:

  pin        symbols.csv pin whose old name no source, data or relocation ledger mentions:
             a ledger-only rename, nothing compiles differently
  tu-access  a member whose class is declared in its own .cpp (a TU-scoped shim): the tool moves
             the declaration to the new access section or toggles `const`, in every .cpp that
             declares the class, then byte-verifies each edited file
Everything else is reported with the reason it cannot land mechanically: sources under
game/gen_small or game/gen_asm (AGENTS.md forbids editing them; recover the body in clean C++),
classes declared in a header (a header change costs the full gate), class changes on
hand-written bodies (the C++ itself must be re-identified), and referenced pins.

    python3 tools/ilt_repair.py plan [--repairs CSV]
    python3 tools/ilt_repair.py apply --kind pin|tu-access [--limit N]
"""
import argparse
import collections
import io
import csv
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import ilt_oracle as O  # noqa: E402

REPAIRS = ROOT / "build/ilt/repairs.csv"
FUNCTIONS, SYMBOLS = O.REVERSE / "functions.csv", O.REVERSE / "symbols.csv"
TOMBSTONES = O.REVERSE / "deleted_rows.csv"
BOUND = 0.01        # per-row expected false fits; research 24/31 total ~5-12 over 3,986 rows
GENERATED = ("game/gen_small/", "game/gen_asm/")
ACCESS = {"Q": "public", "U": "public", "S": "public", "I": "protected", "M": "protected", "K": "protected",
          "A": "private", "E": "private", "C": "private"}
STRUCTOR = re.compile(r"^\?\?(?:_[GE]|1)([A-Za-z_]\w*)@@([A-Z]{3})")
MEMBER = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@([A-Z][A-Z]?)")
ABSENT = "absent"      # the file declares the class without this member: nothing to edit
SKIP_LEDGERS = {"functions.csv", "symbols.csv", "ilt_windows.tsv", "ilt_contradicted_baseline.txt"}


def tokens(name):
    """Identifiers a source must spell to reference this symbol (None: too complex to tell)."""
    if "?$" in name:
        return None
    core = re.sub(r"^\?\?(?:_[A-Z0-9]|[0-9A-Z])", "", name.lstrip("_@")).lstrip("?")
    head = core.split("@@")[0]
    parts = [p for p in head.split("@") if p]
    return parts if parts and all(re.fullmatch(r"[A-Za-z_]\w*", p) for p in parts) else None


def mention_index(words):
    """{word: [files]} over game/ sources and the data/relocation ledgers."""
    hits = collections.defaultdict(list)
    files = [p for p in (ROOT / "game").rglob("*") if p.suffix.lower() in (".cpp", ".c", ".h", ".hpp", ".inl", ".asm", ".inc")]
    files += [p for p in O.REVERSE.glob("*") if p.suffix in (".csv", ".tsv", ".txt") and p.name not in SKIP_LEDGERS]
    for p in files:
        try:
            text = p.read_text("latin1")
        except OSError:
            continue
        for w in set(re.findall(r"[A-Za-z_]\w*", text)) & words:
            hits[w].append(p.relative_to(ROOT).as_posix())
    return hits


def load_rows():
    rows = collections.defaultdict(list)
    for src, path, col in (("functions", FUNCTIONS, "target_rva"), ("pins", SYMBOLS, "address")):
        with open(path, encoding="utf-8", errors="replace", newline="") as f:
            for r in csv.DictReader(f):
                try:
                    rows[(src, int(r[col], 16), r["name"])].append(r)
                except (TypeError, ValueError):
                    pass
    return rows


def classify(reps, rows, o, scan_pins=True):
    """[(repair, kind or None, reason)]. scan_pins=False skips the (minutes-long) reference scan
    and leaves every pin unclassified."""
    words = set()
    for x in reps:
        words.update(tokens(x["old"]) or ())
    mentions = mention_index(words) if scan_pins else None
    pins_by_name = collections.defaultdict(set)
    funcs_by_name = collections.defaultdict(set)
    for (src, rva, name) in rows:
        (pins_by_name if src == "pins" else funcs_by_name)[name].add(rva)
    out = []
    for x in reps:
        rva = int(x["rva"], 16)
        k = (x["src"], rva, x["old"])
        if k not in rows:
            out.append((x, None, "row no longer in the ledger"))
            continue
        if float(x["expected_false"]) > BOUND:
            out.append((x, None, f"expected false {x['expected_false']} above bound {BOUND}"))
            continue
        if not o.fit_slots(x["new"], rva) or o.check(x["old"], rva)[0] != O.CONTRADICTED:
            out.append((x, None, "oracle no longer confirms the new name / contradicts the old"))
            continue
        first = o.first_thunk - O.IMAGE_BASE
        same = {rva} | {first + 5 * s for s in o.slots_of(rva)} | {o.target[s] for s in o.slots_of(rva)}
        elsewhere = (pins_by_name[x["new"]] | funcs_by_name[x["new"]]) - same   # a thunk pin and its body agree
        if elsewhere:
            out.append((x, None, f"new name already claimed at 0x{min(elsewhere):08X} (one identity per name)"))
            continue
        if x["src"] == "pins":
            t = tokens(x["old"])
            if mentions is None:
                out.append((x, None, "pin: reference scan skipped"))
            elif t is None:
                out.append((x, None, "pin: template name, references cannot be ruled out"))
            elif any(mentions.get(w) for w in t) and x["method"] == "T1-access":
                out.append((x, "tu-access", "referenced pin: renamed with its member's source edit"))
            elif any(mentions.get(w) for w in t):
                out.append((x, None, "pin: old name referenced by " + ", ".join(sorted({f for w in t for f in mentions.get(w, ())})[:2])))
            else:
                out.append((x, "pin", "unreferenced pin"))
            continue
        source = rows[k][0]["source"]
        if source.startswith(GENERATED):
            out.append((x, None, "source under game/gen_small or game/gen_asm (no hand or tool edits; recover in clean C++)"))
            continue
        if x["method"] != "T1-access":
            out.append((x, None, "class change on a hand-written body: the C++ class itself must be re-identified"))
            continue
        out.append((x, "tu-access", source))
    return out


# ---------------------------------------------------------------- C++ edits for access / const
def match_brace(text, i):
    depth = 0
    for j in range(i, len(text)):
        if text[j] == "{":
            depth += 1
        elif text[j] == "}":
            depth -= 1
            if depth == 0:
                return j
    return -1


def match_paren(text, i):
    depth = 0
    for j in range(i, len(text)):
        if text[j] == "(":
            depth += 1
        elif text[j] == ")":
            depth -= 1
            if depth == 0:
                return j
    return -1


def class_body(text, cls):
    ms = list(re.finditer(rf"\b(class|struct)\s+{re.escape(cls)}\b[^;{{()]*\{{", text))
    if len(ms) != 1:
        return None
    start = ms[0].end() - 1
    end = match_brace(text, start)
    return (ms[0].group(1), start, end) if end > 0 else None


def toggle_const(text, close, add):
    """Add or drop `const` after the parameter list closing at `close`."""
    m = re.compile(r"\s*const\b").match(text, close + 1)
    if add and not m:
        return text[:close + 1] + " const" + text[close + 1:]
    if not add and m:
        return text[:close + 1] + text[m.end():]
    return None


def edit_member(text, cls, member, old, new):
    """Source with member's declaration (and out-of-line definition) moved from code `old` to
    `new` (two- or three-letter access+cv codes), or None when the shape is not the simple one."""
    body = class_body(text, cls)
    if not body:
        return None
    kind, start, end = body
    inner = text[start + 1:end]
    pat = rf"~\s*{re.escape(cls)}\s*\(" if member is None else rf"(?<![\w~:]){re.escape(member)}\s*\("
    hits = []
    depth = 0
    for m in re.finditer(rf"[{{}}]|{pat}", inner):
        if m.group(0) == "{":
            depth += 1
        elif m.group(0) == "}":
            depth -= 1
        elif depth == 0:
            hits.append(m)
    if not hits:
        return ABSENT
    if len(hits) != 1:
        return None
    pos = start + 1 + hits[0].start()
    close = match_paren(text, text.index("(", pos))
    if close < 0:
        return None
    if old[1:] != new[1:]:                     # const toggle (QAE <-> QBE)
        if old[0] != new[0] or member is None:
            return None
        add = new[1] == "B"
        out = toggle_const(text, close, add)
        if out is None:
            return None
        shift = len(out) - len(text)
        defs = [m for m in re.finditer(rf"\b{re.escape(cls)}\s*::\s*{re.escape(member)}\s*\(", out) if m.start() > end + shift]
        for m in reversed(defs):
            c2 = match_paren(out, out.index("(", m.start()))
            out = toggle_const(out, c2, add) or None
            if out is None:
                return None
        return out
    want, have = ACCESS[new[0]], ACCESS[old[0]]
    seen = list(re.finditer(r"\b(public|protected|private)\s*:(?!:)", text[start:pos]))
    current = seen[-1].group(1) if seen else ("private" if kind == "class" else "public")
    if current != have or want == have:
        return None
    stmt = text.rfind("\n", start, pos) + 1
    after = close + 1
    semi, brace = text.find(";", after), text.find("{", after)
    if brace != -1 and (semi == -1 or brace < semi):
        stop = match_brace(text, brace) + 1
    else:
        stop = semi + 1
    if stop <= 0 or stop > end:
        return None
    label = seen[-1] if seen else None
    sole = label is not None and not text[start + label.end():stmt].strip()   # the label heads this member
    closes = re.compile(r"\s*(?:\}|(?:public|protected|private)\s*:(?!:))").match(text, stop)
    tail = text[stop:] if closes else f"\n{have}:" + text[stop:]
    if sole:
        a = start + label.start(1)
        return text[:a] + want + text[a + len(have):stop] + tail
    return text[:stmt] + f"{want}:\n" + text[stmt:stop] + tail


def member_of(name):
    m = STRUCTOR.match(name)
    if m:
        return m.group(1), None, m.group(2)
    m = MEMBER.match(name)
    if m:
        code = m.group(3)
        return m.group(2), m.group(1), name.split("@@")[1][:3 if code[0] in "AEIMQU" else 1]
    return None


def renamed(name, cls, member, old, new):
    """The ledger name the edit produces from `name`, or None if the edit does not touch it."""
    prefixes = [f"??1{cls}@@", f"??_G{cls}@@", f"??_E{cls}@@"] if member is None else [f"?{member}@{cls}@@"]
    for p in prefixes:
        if name.startswith(p + old):
            return p + new + name[len(p) + len(old):]
    return None


def build(files):
    r = subprocess.run([sys.executable, str(ROOT / "tools/build.py"), *files], cwd=ROOT, capture_output=True,
                       text=True, encoding="utf-8", errors="replace")
    return r.returncode == 0, (r.stdout + r.stderr)[-1500:]


def rewrite_ledger(path, col, renames, note):
    """renames: {(rva, old): new}. Rewrites matching rows in place; returns how many."""
    lines = path.read_bytes().decode("utf-8").split("\n")
    header = next(csv.reader([lines[0].rstrip("\r")]))
    ni, ai, n = header.index("name"), header.index(col), 0
    parsed, present = {}, set()
    for i in range(1, len(lines)):
        if lines[i]:
            cells = next(csv.reader([lines[i].rstrip("\r")]))
            try:
                parsed[i] = (cells, (int(cells[ai], 16), cells[ni]))
                present.add(parsed[i][1])
            except (ValueError, IndexError):
                pass
    for i, (cells, key) in parsed.items():
        if key in renames:
            if (key[0], renames[key]) in present:     # the address already carries the new name
                lines[i] = None
                n += 1
                continue
            present.add((key[0], renames[key]))
            cells[ni] = renames[key]
            if "notes" in header:
                k = header.index("notes")
                tag = note(key)
                cells[k] = (cells[k] + " " + tag).strip() if tag not in cells[k] else cells[k]
            buf = __import__("io").StringIO()
            csv.writer(buf, lineterminator="").writerow(cells)
            lines[i] = buf.getvalue() + ("\r" if lines[i].endswith("\r") else "")
            n += 1
    path.write_bytes("\n".join(l for l in lines if l is not None).encode("utf-8"))
    return n


def relabel(paths, renames):
    """Rewrite decorated-name labels (`// ?f@C@@QAEXXZ` above a definition) in the edited files,
    which tools/find_declared_unmatched.py reads as the definition's claimed symbol."""
    pairs = sorted({(old, new) for m in renames.values() for (_, old), new in m.items()}, key=lambda p: -len(p[0]))
    for p in paths:
        text = p.read_bytes().decode("latin1")
        out = text
        for old, new in pairs:
            out = re.sub(rf"(?<![\w?@$]){re.escape(old)}(?![\w@])", lambda m: new, out)
        if out != text:
            p.write_bytes(out.encode("latin1"))


def tombstone(renames, efp):
    """Record each renamed functions.csv row in deleted_rows.csv, so a union merge of a branch
    forked earlier cannot resurrect the old name (tools/check_csv.py)."""
    if not renames:
        return
    buf = io.StringIO()
    w = csv.writer(buf, lineterminator="\n")
    for (rva, old), new in sorted(renames.items()):
        w.writerow([old, f"0x{rva:08X}", f"ILT oracle repair: renamed to {new} at the same address and "
                    f"extent. Retail's incremental-link thunk table contradicts the old decorated name and "
                    f"confirms the new one (tools/ilt_repair.py; expected false {efp})."])
    raw = TOMBSTONES.read_bytes()
    if not raw.endswith(b"\n"):
        sys.exit(f"ilt_repair: {TOMBSTONES} does not end with a newline")
    TOMBSTONES.write_bytes(raw + buf.getvalue().encode("utf-8"))


def apply_pins(items, limit):
    items = items[:limit] if limit else items
    renames = {(int(x["rva"], 16), x["old"]): x["new"] for x, _, _ in items}
    meth = {(int(x["rva"], 16), x["old"]): (x["method"], x["expected_false"]) for x, _, _ in items}
    n = rewrite_ledger(SYMBOLS, "address", renames, lambda k: f"ilt-verified={meth[k][0]}(efp={meth[k][1]})")
    return n


def apply_tu(items, limit, rows, skip=0):
    groups = collections.defaultdict(list)
    for x, _, src in items:
        m = member_of(x["old"])
        n = member_of(x["new"])
        if not m or not n or m[:2] != n[:2]:
            continue
        groups[(m[0], m[1], m[2], n[2])].append(x)
    landed, rejected = [], []
    all_names = collections.defaultdict(set)
    for (src, rva, name) in rows:
        all_names[name].add((src, rva))
    order = sorted(groups.items(), key=lambda g: (g[0][0], g[0][1] or ""))
    for gi, ((cls, member, old, new), xs) in enumerate(order[skip:skip + limit] if limit else order[skip:]):
        word = member or f"~{cls}"
        files = subprocess.run(["git", "grep", "-l", "-w", "-F", "-e", cls, "--", "game"], cwd=ROOT,
                               capture_output=True, text=True).stdout.split()
        users = [f for f in files if (member or "~") in Path(ROOT / f).read_text("latin1")]
        if any(not f.endswith((".cpp", ".c")) for f in users):
            rejected.append((xs, "class declared or used in a header (full gate)"))
            continue
        if len(users) > 12:
            rejected.append((xs, f"{len(users)} files use the member"))
            continue
        originals, ok = {}, True
        for f in users:
            p = ROOT / f
            text = p.read_bytes().decode("latin1")
            out = edit_member(text, cls, member, old, new)
            if out is ABSENT:
                continue
            if out is None:
                defines = (rf"\b{re.escape(cls)}\s*::\s*~\s*{re.escape(cls)}\s*\(" if member is None
                           else rf"\b{re.escape(cls)}\s*::\s*{re.escape(member)}\s*\(")
                if class_body(text, cls) is None and not re.search(defines, text):
                    continue                   # mentions the class only; no declaration to change
                ok = False
                break
            originals[p] = text
            p.write_bytes(out.encode("latin1"))
        renames = {}
        for name, keys in all_names.items():
            nn = renamed(name, cls, member, old, new)
            if nn:
                for src, rva in keys:
                    renames.setdefault(src, {})[(rva, name)] = nn
        clash = [f"0x{rva:08X}" for m in renames.values() for (rva, _), nn in m.items()
                 if O.tier(nn) == "real" and O.oracle().check(nn, rva)[0] == O.CONTRADICTED]
        if not ok or not originals or clash:
            for p, t in originals.items():
                p.write_bytes(t.encode("latin1"))
            rejected.append((xs, f"edit would rename rows the oracle contradicts at {', '.join(clash[:3])}"
                             if clash and ok and originals else "declaration shape not editable mechanically"))
            continue
        saved = {p: p.read_bytes() for p in (FUNCTIONS, SYMBOLS, TOMBSTONES)}
        tag = lambda k: f"ilt-verified=T1-access(efp={xs[0]['expected_false']})"
        rewrite_ledger(FUNCTIONS, "target_rva", renames.get("functions", {}), tag)
        tombstone(renames.get("functions", {}), xs[0]["expected_false"])
        relabel(originals, renames)
        rewrite_ledger(SYMBOLS, "address", renames.get("pins", {}), tag)
        good, log = build(sorted(p.relative_to(ROOT).as_posix() for p in originals))
        if good:
            landed.append((xs, renames, sorted(p.relative_to(ROOT).as_posix() for p in originals)))
            print(f"landed {cls}::{word} {old}->{new} ({len(originals)} file(s))", flush=True)
        else:
            for p, t in originals.items():
                p.write_bytes(t.encode("latin1"))
            for p, b in saved.items():
                p.write_bytes(b)
            reason = (re.findall(r"(?m)^.*(?:FAIL|MISMATCH|mismatch|error|unresolved).*$", log) or [log[-200:]])[0][:160]
            rejected.append((xs, "gate: " + reason.strip()))
            with open(ROOT / "build/ilt/gate_failures.log", "a", encoding="utf-8") as f:
                f.write(f"==== {cls}::{word} {old}->{new}\n{log}\n")
            print(f"rejected {cls}::{word}: {reason.strip()}", flush=True)
    return landed, rejected


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("cmd", choices=("plan", "apply"))
    ap.add_argument("--repairs", default=str(REPAIRS))
    ap.add_argument("--kind", choices=("pin", "tu-access"))
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--skip", type=int, default=0, help="tu-access: skip the first N member groups")
    args = ap.parse_args(argv)
    with open(args.repairs, encoding="utf-8", newline="") as f:
        reps = list(csv.DictReader(f))
    o, rows = O.oracle(), load_rows()
    plan = classify(reps, rows, o)
    if args.cmd == "plan":
        c = collections.Counter((x["method"], x["src"], kind or re.sub(r" by .*|0x[0-9A-F]+", "", why)) for x, kind, why in plan)
        for k, v in sorted(c.items(), key=lambda kv: -kv[1]):
            print(v, *k, sep="\t")
        efp = sum(float(x["expected_false"]) for x, kind, _ in plan if kind)
        print(f"{sum(1 for p in plan if p[1])} landable of {len(plan)}; expected false among landable {efp:.2f}")
        return 0
    items = [p for p in plan if p[1] == args.kind]
    if args.kind == "pin":
        print(f"renamed {apply_pins(items, args.limit)} pins")
    else:
        landed, rejected = apply_tu(items, args.limit, rows, args.skip)
        print(f"tu-access: {len(landed)} groups landed ({sum(len(x[0]) for x in landed)} repairs), "
              f"{len(rejected)} rejected")
        for xs, why in rejected:
            print(f"  rejected {len(xs)} {xs[0]['old'][:70]}: {why}")
    subprocess.run([sys.executable, str(ROOT / "tools/ilt_guard.py"), "--prune-baseline"], cwd=ROOT, check=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
