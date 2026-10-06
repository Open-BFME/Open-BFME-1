#!/usr/bin/env python3
"""Turn an approved TU from tu_map.csv into the one source file retail built it from.

The skeleton of a TU is every function tu_map.csv approves for it, in retail
address order. Matched bodies are pulled in from the one-function files that
hold them today; everything else is an explicit placeholder comment:

    // tu-skeleton: 0x004A1230 88B ?foo@Bar@@QAEXXZ -- unmatched, no code, never credited
    // tu-skeleton: 0x004A1290 40B ?baz@Bar@@QAEXXZ -- matched in Die/Baz.cpp (not merged yet)

A placeholder is a comment, so it compiles to nothing and no gate or progress
figure can count it. Retail-byte stubs (`__emit`) are deliberately not emitted:
conversion_gate refuses them outside Code/gen_small/ and they would be the one
kind of placeholder a progress figure could mistake for a match.

Merging is verified, never assumed. Each donor file is compiled alone first and
the rows that match there are the baseline. Donors are then accreted in three
deterministic orders (address, row count, text size); a donor is accepted only
if the TU still compiles and NO baseline row is lost, and the best order wins.
Duplicate declarations are emitted once; a type that two donors spell
differently gets one spelling (first, else longest) and the byte check decides
whether that was safe. A donor that also holds rows of another TU is never
split here ("mixed"): it stays a satellite and is reported.

Applying a merge writes the TU file (`// cl:` line chosen from the donors' own
flag sets by the same verification), repoints every ledger row of each absorbed
donor at it, deletes the absorbed donors and stages the result. The commit hook
then byte-verifies it again; this tool never commits.

Usage:
  python3 tools/tu_skeleton.py --list PREFIX       approved TUs under PREFIX
  python3 tools/tu_skeleton.py --plan TU           the skeleton, row by row
  python3 tools/tu_skeleton.py --merge TU [--dry-run]
"""
import argparse
import collections
import contextlib
import csv
import hashlib
import io
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_map  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
LAYOUT = tu_map.Layout(ROOT)
LEDGER = LAYOUT.path("functions.csv")
MARK = "// tu-skeleton:"


# ---------------------------------------------------------------- chunking
def chunks(text):
    """Top-level items as (kind, text); comments stay with the item after them.

    kind is 'pp' (a preprocessor line), 'def' (a function body), 'decl'
    (anything ending in ';', class bodies included) or 'tail' (trailing
    comments). Braces inside comments, strings and character literals are
    skipped, which is what the earlier comment-stripping chunker could not do.
    """
    out, n, i, start, depth, code = [], len(text), 0, 0, 0, False
    while i < n:
        c = text[i]
        if text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
            continue
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        if c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i, code = j + 1, True
            continue
        if c == "#" and depth == 0 and not code and text[text.rfind("\n", 0, i) + 1:i].strip() == "":
            j = i
            while True:
                k = text.find("\n", j)
                if k < 0:
                    k = n
                    break
                if text[k - 1:k] != "\\" and not text[j:k].rstrip("\r").endswith("\\"):
                    break
                j = k + 1
            lead = text[start:text.rfind("\n", 0, i) + 1]
            if lead.strip():
                out.append(("tail", lead))
            out.append(("pp", text[i:k].rstrip()))
            i = start = min(k + 1, n)
            continue
        if not c.isspace():
            code = True
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                body = strip(text[start:i + 1]).strip()
                head = body.split("{")[0]
                aggregate = re.match(r"^(template\s*<[^>]*>\s*)?(typedef\s+)?(class|struct|enum|union)\b", body) \
                    and not re.search(r"\)\s*(const)?\s*$", head.strip())
                if not aggregate:
                    out.append(("def" if not re.match(r"^(namespace|extern\s+\"C\")", body) else "decl",
                                text[start:i + 1]))
                    start, code = i + 1, False
        elif c == ";" and depth == 0:
            out.append(("decl", text[start:i + 1]))
            start, code = i + 1, False
        i += 1
    if text[start:].strip():
        out.append(("tail" if not strip(text[start:]).strip() else "decl", text[start:]))
    return out


def strip(t):
    t = re.sub(r"/\*.*?\*/", " ", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def norm(t):
    return re.sub(r"\s+", " ", strip(t)).strip()


def key_of(kind, text):
    s = norm(text)
    m = re.match(r"^(?:template\s*<[^>]*>\s*)?(class|struct|enum|union)\s+(?:__declspec\([^)]*\)\s*)?"
                 r"([A-Za-z_]\w*)\s*(?::[^{]*)?\{", s)
    if m:
        return ("type", m.group(2))
    m = re.match(r"^typedef\b.*?\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;$", s)
    if m:
        return ("typedef", m.group(1))
    if kind == "def":
        return ("func", s.split("{")[0].strip())
    return ("decl", s)


ACCESS = re.compile(r"^\s*(public|protected|private)\s*:(?!:)")


def members(text):
    """(head, [(access, member text)], tail) of one class body; comments stripped."""
    text = strip(text)
    i, j = text.index("{"), text.rindex("}")
    head, body, tail = text[:i + 1], text[i + 1:j], text[j:]
    acc = "public" if re.match(r"^\s*(template\s*<[^>]*>\s*)?(struct|union)\b", head) else "private"
    out, buf, depth, par = [], "", 0, 0
    for ch in body:
        buf += ch
        m = ACCESS.match(buf)
        if m and depth == 0 and par == 0:
            acc, buf = m.group(1), buf[m.end():]
            continue
        if ch == "(":
            par += 1
        elif ch == ")":
            par -= 1
        elif ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0 and par == 0 and "(" in buf.split("{")[0] \
                    and not re.match(r"^\s*(enum|struct|class|union)\b", buf):
                out.append((acc, buf.strip()))
                buf = ""
        elif ch == ";" and depth == 0 and par == 0:
            out.append((acc, buf.strip()))
            buf = ""
    return head, [(a, m) for a, m in out if m and m != ";"], tail


def member_key(m):
    """(key, 'safe'|'layout'): safe members cannot change size, offsets or vtable."""
    s = re.sub(r"\s+", " ", re.sub(r"\{.*\}$", "", m, flags=re.S)).strip().rstrip(";")
    if re.match(r"^(enum|struct|class|union|typedef)\b", s):
        names = re.findall(r"[A-Za-z_]\w*", s)
        return ("type", names[-1] if s.startswith("typedef") else names[1] if len(names) > 1 else s), "safe"
    f = re.search(r"(~?[A-Za-z_]\w*|operator\s*\S+)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(const)?", s)
    if f and not re.search(r"\(\s*\*", s[:f.start() + 3]):
        return ("fn", f.group(1), bool(f.group(3))), ("layout" if re.search(r"\bvirtual\b", s) else "safe")
    names = re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*$", s)
    return ("data", names[0] if names else s), ("safe" if s.startswith("static ") else "layout")


def union_view(base, others):
    """`base` plus the layout-safe members only the others declare (access kept:
    MSVC mangles it). Virtual functions and data members are never added."""
    try:
        head, mem, tail = members(base)
    except ValueError:
        return base
    have = {member_key(m)[0] for _, m in mem}
    add = []
    for v in others:
        try:
            _, vm, _ = members(v)
        except ValueError:
            continue
        for a, m in vm:
            k, kind = member_key(m)
            if kind == "safe" and k not in have:
                have.add(k)
                add.append((a, m))
    if not add:
        return base
    extra = "".join(f"\n{a}:\n\t{m}{'' if m.endswith(('}', ';')) else ';'}" for a, m in add)
    return head + "".join(f"\n{a}:\n\t{m};" if not m.endswith(("}", ";")) else f"\n{a}:\n\t{m}"
                          for a, m in mem) + extra + "\n" + tail


# ---------------------------------------------------------------- inputs
def ledger_rows():
    return list(csv.DictReader(io.StringIO(LEDGER.read_text(encoding="utf-8", errors="replace"), newline="")))


def skeleton(tu):
    """Approved rows of `tu` in retail order, each with its ledger row (or None)."""
    m = tu_map.read_csv(LAYOUT.out)
    want = [r for r in m if r["tu"].lower() == tu.lower() and r["confidence"] == "approved"
            and r["kind"].startswith("code")]
    led = {}
    for r in ledger_rows():
        if "gen-alias" not in (r["notes"] or "") and r["target_rva"].startswith("0x"):
            led.setdefault(int(r["target_rva"], 16), r)
    return [(r, led.get(int(r["rva"], 16))) for r in sorted(want, key=lambda r: int(r["rva"], 16))]


def donors(tu, sk):
    """donor file -> its rows; and the files that also hold rows of another (or no) TU.

    A candidate is the file of an approved row, or the TU path itself. It may be
    absorbed only when every matched row it owns is assigned to this TU (any
    confidence); anything else would move a row the map does not put here.
    """
    rows = ledger_rows()
    assigned = {int(r["rva"], 16): r["tu"].lower() for r in tu_map.read_csv(LAYOUT.out)
                if r["kind"].startswith("code") and r["tu"]}
    by_file = collections.defaultdict(list)
    for r in rows:
        by_file[r["source"]].append(r)
    cands = {led["source"] for t, led in sk
             if led and led["status"] == "matched" and led["source"].endswith(".cpp")}
    if by_file.get(tu):
        cands.add(tu)
    out, mixed = {}, {}
    for f in sorted(cands):
        own = [r for r in by_file[f] if r["status"] == "matched" and "gen-alias" not in (r["notes"] or "")]
        foreign = [r for r in own if assigned.get(int(r["target_rva"], 16)) != tu.lower()]
        if foreign:
            mixed[f] = len(foreign)
        elif own:
            out[f] = own
    return out, mixed


def flags_of(text):
    for line in text.splitlines():
        if line.startswith("// cl:"):
            return line[len("// cl:"):].split()
    return []


# ---------------------------------------------------------------- compose
def compose(tu, sk, files, texts, flags, strategy):
    """Declarations first (donor order, one spelling each), then bodies in retail order.

    `files` is in donor order with the seed first. A type two donors spell
    differently is emitted once, from the donor whose spelling is chosen and at
    that donor's own position, so whatever it depends on is already declared.
    """
    parsed = {f: chunks("\n".join(l for l in texts[f].lstrip("\ufeff").splitlines()
                                  if not l.startswith("// cl:") and l.strip() != "// stlport") + "\n")
              for f in files}
    variants = collections.defaultdict(list)
    for f in files:
        for kind, c in parsed[f]:
            if kind == "decl":
                k = key_of(kind, c)
                if k[0] in ("type", "typedef") and norm(c) not in [norm(v) for v, _ in variants[k]]:
                    variants[k].append((c, f))
    chosen = {}
    for k, v in variants.items():
        if len(v) > 1:
            pick = v[0] if strategy.endswith("first") else max(v, key=lambda x: len(norm(x[0])))
            if strategy.startswith("union") and k[0] == "type":
                # emitted where the LAST donor declares it: members added from
                # other donors may name types those donors declare first
                pick = (union_view(pick[0], [x[0] for x in v if x is not pick]), v[-1][1])
            chosen[k] = pick
    pps, decls, seen = [], [], set()
    for f in files:
        for kind, c in parsed[f]:
            if kind == "pp":
                if c.strip() not in pps:
                    pps.append(c.strip())
            elif kind == "decl":
                k = key_of(kind, c)
                if k in seen or (k in chosen and chosen[k][1] != f):
                    continue
                seen.add(k)
                decls.append((chosen[k][0] if k in chosen else c).strip("\n"))
    body, done, bodies = [], set(), set()
    for t, led in sk:
        f = led["source"] if led else None
        if f in files:
            if f in done:
                continue
            done.add(f)
            body.append(f"// ---- from {f}")
            for kind, c in parsed[f]:
                if kind == "def" and norm(c) not in bodies:
                    bodies.add(norm(c))
                    body.append(c.strip("\n"))
                elif kind == "tail":
                    body.append(c.strip("\n"))
            continue
        name = (led or {}).get("name") or "(unledgered)"
        why = (f"matched in {f} (not merged yet)" if led and led["status"] == "matched"
               else "unmatched, no code, never credited")
        body.append(f"{MARK} {t['rva']} {t['size']}B {name} -- {why}")
    for f in files:   # a donor none of whose rows is approved here (cannot happen today)
        if f not in done:
            body.extend(c.strip("\n") for kind, c in parsed[f] if kind == "def")
    head = [f"// cl: {' '.join(flags)}"] if flags else []
    if any("// stlport" in texts[f] for f in files):
        head.append("// stlport")
    head.append(f"// TU {tu}: generated by tools/tu_skeleton.py from tu_map.csv (approved rows, retail order)")
    return "\n".join(head + pps) + "\n\n" + "\n\n".join(decls + body) + "\n"


# ---------------------------------------------------------------- verify
class Verifier:
    def __init__(self, tu):
        import build as B
        self.B = B
        self.sm = B.load_symbol_map()
        self.tu = ROOT / tu
        self.tmp = ROOT / "build" / "tu_skeleton"   # build.py wants objects inside the tree
        self.tmp.mkdir(parents=True, exist_ok=True)
        self.cache = {}
        self.errors = []

    def matched(self, text, rows):
        key = hashlib.sha1(text.encode()).hexdigest()[:16]
        if key not in self.cache:
            src = self.tu.parent / f".{self.tu.stem}.{key}.tu_skeleton.cpp"
            obj = self.tmp / f"{key}.obj"
            src.write_text(text, encoding="utf-8", newline="")
            try:
                with contextlib.redirect_stdout(io.StringIO()):
                    ok, msg, _ = self.B.try_compile_source(src, obj)
            finally:
                src.unlink()
            self.cache[key] = obj if ok else None
            if not ok:
                self.errors = [l.strip() for l in (msg or "").splitlines() if " error " in l][:3]
        obj, out = self.cache[key], set()
        if obj is None:
            return None
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            for r in rows:
                try:
                    res = self.B.compile_function(r, self.sm, obj)
                    if res["bytes"] == res["target"]:
                        out.add(r["target_rva"])
                except BaseException:   # build.py reports misses by SystemExit
                    pass
        return out


def merge(tu, dry_run=False, log=print):
    sk = skeleton(tu)
    don, mixed = donors(tu, sk)
    report = {"tu": tu, "approved": len(sk), "mixed": mixed, "accepted": [], "rejected": {}}
    if tu in mixed or ((ROOT / tu).exists() and tu not in don):
        report["blocked"] = "TU path exists and holds rows of another TU (split it first)"
        return report
    if len(don) < 2 and not (len(don) == 1 and tu not in don):
        report["blocked"] = "fewer than two donors"
        return report
    v = Verifier(tu)
    texts = {f: (ROOT / f).read_text(encoding="utf-8-sig", errors="replace") for f in don}
    base = {}
    for f in don:
        got = v.matched(texts[f], don[f])
        base[f] = got or set()
    good = [f for f in don if base[f]]
    weight = collections.Counter()
    cands = {}
    for f in good:
        fl = flags_of(texts[f])
        k = tuple(x for x in fl if not x.lower().startswith(("/i", "-i")))
        weight[k] += len(base[f])
        cands.setdefault(k, None)
    incs = []
    for f in good:
        for x in flags_of(texts[f]):
            if x.lower().startswith(("/i", "-i")) and x not in incs:
                incs.append(x)
    flag_sets = [list(k) + incs for k, _ in weight.most_common()]

    def attempt(files, flags):
        best = None
        for st in ("union-first", "union-longest", "first", "longest"):
            text = compose(tu, sk, files, texts, flags, st)
            got = v.matched(text, [r for f in files for r in don[f]])
            need = set().union(*(base[f] for f in files))
            if got is not None and need <= got:
                return text
            best = best or ("compile" if got is None else "bytes")
        return best

    def greedy(order, flags):
        acc, rej = [], {}
        for f in order:
            res = attempt(acc + [f], flags)
            if res in ("compile", "bytes"):
                rej[f] = res + ("" if res == "bytes" else ": " + " | ".join(v.errors)[:300])
            else:
                acc.append(f)
        return acc, rej

    first = {f: min(int(r["target_rva"], 16) for r in don[f]) for f in good}
    orders = [sorted(good, key=first.get), sorted(good, key=lambda f: (-len(base[f]), first[f])),
              sorted(good, key=lambda f: (-len(texts[f]), first[f]))]
    if tu in good:   # an existing file at the TU path is always the seed
        orders = [[tu] + [f for f in o if f != tu] for o in orders]
    best = None
    for flags in flag_sets[:3]:
        for o in orders:
            acc, rej = greedy(o, flags)
            score = sum(len(base[f]) for f in acc)
            if (tu in good and tu not in acc):
                continue
            if best is None or score > best[0]:
                best = (score, acc, rej, flags)
    report["rejected"].update({f: "no baseline match" for f in don if f not in good})
    if not best or len(best[1]) < 2 and not (len(best[1]) == 1 and best[1][0] != tu):
        report["rejected"].update(best[2] if best else {})
        report["blocked"] = "no verified merge of two or more donors"
        return report
    score, acc, rej, flags = best
    text = attempt(acc, flags)
    report.update(accepted=acc, flags=flags, rows=score)
    report["rejected"].update(rej)
    if dry_run:
        report["text"] = text
        return report
    apply(tu, acc, text)
    return report


# ---------------------------------------------------------------- apply
def repoint(raw, donors_, tu):
    """Rewrite the `source` field of every row owned by an absorbed donor."""
    out, moved = [], 0
    for line in raw.splitlines(keepends=True):
        body = line.rstrip("\r\n")
        try:
            fields = next(csv.reader([body]))
        except (StopIteration, csv.Error):
            out.append(line)
            continue
        if len(fields) >= 5 and fields[4] in donors_ and fields[4] != tu:
            needle = "," + fields[4] + ","
            if body.count(needle) == 1:
                line = line.replace(needle, "," + tu + ",", 1)
                moved += 1
        out.append(line)
    return "".join(out), moved


def apply(tu, accepted, text):
    raw = LEDGER.read_bytes().decode("utf-8")
    new, moved = repoint(raw, set(accepted), tu)
    LEDGER.write_bytes(new.encode("utf-8"))
    (ROOT / tu).write_text(text, encoding="utf-8", newline="\n")
    gone = [f for f in accepted if f != tu]
    if gone:
        subprocess.run(["git", "rm", "-q", "--", *gone], cwd=ROOT, check=True)
    subprocess.run(["git", "add", "--", tu, str(LEDGER.relative_to(ROOT))], cwd=ROOT, check=True)
    return moved


def plan(tu):
    sk = skeleton(tu)
    don, mixed = donors(tu, sk)
    for t, led in sk:
        state = ("pull " + led["source"] if led and led["source"] in don else
                 "mixed " + led["source"] if led and led["source"] in mixed else
                 "placeholder (" + (led["status"] if led else "unledgered") + ")")
        print(f"{t['rva']} {int(t['size']):6d} {t['by']} {(led or {}).get('name', '')[:60]:60s} {state}")
    print(f"{len(sk)} approved rows, {len(don)} donor files, {len(mixed)} mixed files")


def list_tus(prefix):
    c = collections.defaultdict(set)
    for r in tu_map.read_csv(LAYOUT.out):
        if r["confidence"] == "approved" and r["tu"].startswith(prefix) and r["kind"].startswith("code"):
            c[r["tu"]].add(r["source"])
    for tu, files in sorted(c.items()):
        print(f"{len(files - {''}):3d} files  {tu}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--list", metavar="PREFIX")
    g.add_argument("--plan", metavar="TU")
    g.add_argument("--merge", metavar="TU")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args(argv)
    if a.list is not None:
        list_tus(a.list)
    elif a.plan:
        plan(a.plan)
    else:
        rep = merge(a.merge, a.dry_run)
        text = rep.pop("text", None)
        for k, val in rep.items():
            print(f"{k}: {val}")
        if text and a.dry_run:
            print(text)
        return 0 if rep.get("accepted") else 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
