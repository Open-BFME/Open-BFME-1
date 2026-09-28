#!/usr/bin/env python3
"""EA's own names and source files for game functions, read from WorldBuilder internal builds.

BFME1's and BFME2's WorldBuilders are internal builds of the game engine. Their code references
`Class::method` strings and EA source paths (`Z:\\LOTR\\Code\\GameEngine\\...\\File.cpp`) from
inside the function they describe; the release game has neither. This pairs game functions with
WorldBuilder functions and writes what each partner says to targets/game/reverse/ea_evidence.csv:

  rva,kind,value,route,basis
  name   Class::method from a label that names exactly one WorldBuilder function. route: wb1
         (BFME1's own label), chain (game -> WB1 -> WB2), direct (game -> WB2); an address whose
         routes disagree gets no name. A BFME2 label is evidence, not truth: BFME2 renamed members.
  file   Code-relative source path. route: wb1 (the partner references its own path), wb1-run
         (the partner sits between two functions of one file in BFME1 WorldBuilder's order), then
         zh (Zero Hour defines the ledger's Class::method out of line in exactly one .cpp), then
         wb2/wb2-run; zh and wb2 disagreeing gives no file. retail-run fills a function between
         two same-file neighbours in retail order. A run-filled inline or template body gets the
         TU that emitted it, not its home, so tools/placement_queue.py moves files on wb1/zh only.
  basis  strong when every pairing leg is a shared export, a unique shared string or a BSim
         unique top-1 match; aligned when a leg came from alignment or call-graph propagation.

Pairing: seeds, then anchored alignment -- both builds keep an object's functions in source order
but link objects in a different order, so between two pairs that step forward together by at most
32 KB the unpaired functions are aligned in order by instruction similarity -- alternating with
call-graph gap fill and callee fingerprints. Every run hides half the export/string seeds, scores
the pairing on them, and refuses to write below FLOORS. Measured 2026-09-29 with BSim seeds:
game-WB1 23,881 pairs 98.5%, WB1-WB2 18,942 94.3%, game-WB2 11,777 90.4%.

    python3 tools/ea_evidence.py --wb1 DIR --wb2 DIR --wb2-exe PATH [--bsim DIR]

--wb1/--wb2 are export directories written by tools/ghidra/worldbuilder_analysis.java
(function_ranges.tsv, calls.tsv, string_references.tsv). --bsim holds game_wb1.tsv, game_wb2.tsv
and wb1_wb2.tsv from tools/ghidra/bsim_query.java; they add about a quarter more pairs. The
analysis write-up is targets/game/reverse/analysis/worldbuilder_evidence.md.
"""
import argparse
import bisect
import collections
import csv
import difflib
import random
import re
import struct
import sys
from pathlib import Path

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

REVERSE = ROOT / "targets/game/reverse"
OUT = REVERSE / "ea_evidence.csv"
WB1_EXE = ROOT / "inputs/baselines/bfme1/workshop-vanilla-1.03/files/worldbuilder.exe"
ZH = ROOT / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
FLOORS = {("game", "wb1"): 0.95, ("wb1", "wb2"): 0.90, ("game", "wb2"): 0.85}
MAX_GAP, MIN_SCORE, MAX_CELLS, RUN = 0x8000, 0.6, 4000, 40
STRONG = frozenset(("export", "string", "bsim"))
LABEL = re.compile(r"([A-Za-z_]\w*)::(~?[A-Za-z_]\w*)(?:\(\))?")
PATH = re.compile(r"\\Code\\((?:[^\\\s]+\\)*[^\\\s]+?\.(?:cpp|h))\b", re.I)
MEMBER = re.compile(r"\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
STRUCTOR = re.compile(r"\?\?([01])([A-Za-z_]\w*)@")
MD = Cs(CS_ARCH_X86, CS_MODE_32)


def fail(message):
    sys.exit(f"ea_evidence: {message}")


def unescape(value):
    """Undo worldbuilder_analysis.java's text() escaping."""
    return re.sub(r"\\(.)", lambda m: {"t": "\t", "n": "\n", "r": "\r"}.get(m.group(1), m.group(1)), value)


def tsv(path):
    with open(path, encoding="utf-8", errors="replace", newline="") as f:
        yield from csv.DictReader(f, delimiter="\t", quoting=csv.QUOTE_NONE)


def plain(mangled):
    """Class::method of a simple MSVC member symbol (constructors and destructors too), else None."""
    m = STRUCTOR.match(mangled or "")
    if m:
        return f"{m.group(2)}::{'~' if m.group(1) == '1' else ''}{m.group(2)}"
    m = MEMBER.match(mangled or "")
    return f"{m.group(2)}::{m.group(1)}" if m else None


class Side:
    """One image: function sizes, call lists, strings, exports, labels, paths, shapes."""

    def __init__(self, kind):
        self.kind = kind
        self.size, self.calls, self.exports = {}, {}, {}
        self.strings = collections.defaultdict(set)
        self.labels = collections.defaultdict(set)
        self.paths = collections.defaultdict(set)
        self.funcs, self._shapes = [], {}

    def shape(self, a):
        if a not in self._shapes:
            body = self.read(a, min(self.size[a], 20000))
            self._shapes[a] = tuple(i.mnemonic for _, i in zip(range(1500), MD.disasm(body, a)))
        return self._shapes[a]


def game_side():
    g = Side("game")
    g.name, g.vendored = {}, set()
    for r in csv.DictReader(open(REVERSE / "functions.csv", encoding="utf-8", errors="replace", newline="")):
        try:
            a, n = int(r["target_rva"], 16), int(r["target_size"], 0)
        except ValueError:
            continue
        if r["status"] == "matched" or a not in g.size:
            g.size[a], g.name[a] = n, r["name"]
            if "vendored=" in (r["notes"] or ""):
                g.vendored.add(a)
    for r in csv.DictReader(open(REVERSE / "ghidra_functions.csv", encoding="utf-8", errors="replace", newline="")):
        a = int(r["rva"], 16)
        if a not in g.size:
            g.size[a], g.name[a] = int(r["size"]), ""

    def read(a, n):
        try:
            return build.read_target_bytes(a, n)
        except ValueError:
            return b""
    g.read = read
    thunks = {}
    for a, n in g.size.items():
        if n == 5 and g.name[a].startswith("?j_"):
            b = read(a, 5)
            if b[:1] == b"\xe9":
                thunks[a] = a + 5 + struct.unpack_from("<i", b, 1)[0]
    g.funcs = sorted(a for a, n in g.size.items() if a not in thunks and n >= 8)
    for a in g.funcs:
        if g.size[a] <= 200000:
            g.calls[a] = [thunks.get(t, t) for t in (i.address + 5 + struct.unpack_from("<i", i.bytes, 1)[0]
                          for i in MD.disasm(read(a, g.size[a]), a) if i.size == 5 and i.bytes[0] == 0xE8)]
    for line in open(REVERSE / "string_xrefs.tsv", encoding="utf-8", errors="replace"):
        value, _, sites = line.rstrip("\n").partition("\t")
        for site in filter(None, sites.split(",")):
            g.strings[int(site, 16)].add(value)
    for e in csv.DictReader(open(REVERSE / "exports.csv", encoding="utf-8", newline="")):
        if e["kind"] == "code":
            t = int(e["target_rva"] or e["rva"], 16)
            g.exports[e["name"]] = thunks.get(t, t)
    return g


def wb_side(kind, directory, exe, internal):
    """internal: both sides are internal builds, so paths (sans line) and labels are shared strings."""
    d = Path(directory)
    for name in ("function_ranges.tsv", "calls.tsv", "string_references.tsv"):
        if not (d / name).is_file():
            fail(f"{d / name} missing: export {kind} with tools/ghidra/worldbuilder_analysis.java")
    if not Path(exe).is_file():
        fail(f"{exe} missing")
    w = Side(kind)
    thunk = {}
    for r in tsv(d / "function_ranges.tsv"):
        a = int(r["entry_rva"], 16)
        w.size[a] = int(r["owned_bytes"])
        if r["thunk_target_rva"]:
            thunk[a] = int(r["thunk_target_rva"], 16)
    per = collections.defaultdict(list)
    for r in tsv(d / "calls.tsv"):
        if r["caller_rva"] and r["target_rva"]:
            t = int(r["target_rva"], 16)
            per[int(r["caller_rva"], 16)].append((int(r["instruction_rva"], 16), thunk.get(t, t)))
    w.calls = {a: [t for _, t in sorted(v)] for a, v in per.items()}
    for r in tsv(d / "string_references.tsv"):
        if not r["function_rva"]:
            continue
        a, v = int(r["function_rva"], 16), unescape(r["value"])
        label, path = LABEL.fullmatch(v), PATH.search(v)
        if label:
            w.labels[a].add(f"{label.group(1)}::{label.group(2)}")
        elif path:
            w.paths[a].add(path.group(1).replace("\\", "/"))
        if internal:
            w.strings[a].add(("PATH:" + path.group(1).lower() + re.sub(r"\(\d+\)", "", v[path.end():]))
                             if path and not label else v)
        elif not label and not path:
            w.strings[a].add(v)
    pe = pefile.PE(str(exe), fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"]])
    for s in getattr(getattr(pe, "DIRECTORY_ENTRY_EXPORT", None), "symbols", []):
        if s.name:
            w.exports[s.name.decode("ascii", "replace")] = thunk.get(s.address, s.address)
    w.base = pe.OPTIONAL_HEADER.ImageBase
    secs = [(s.VirtualAddress, s.Misc_VirtualSize, s.PointerToRawData) for s in pe.sections]
    data = pe.__data__

    def read(a, n):
        for v, vs, p in secs:
            if v <= a < v + vs:
                return bytes(data[p + a - v:p + a - v + n])
        return b""
    w.read = read
    w.funcs = sorted(a for a, n in w.size.items() if a not in thunk and n >= 8)
    return w


def align(xs, ys, score):
    """Order-preserving alignment maximising the summed (score - MIN_SCORE) of aligned pairs."""
    n, m = len(xs), len(ys)
    sc = [[score(x, y) for y in ys] for x in xs]
    best = [[0.0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):
            take = best[i + 1][j + 1] + sc[i][j] - MIN_SCORE if sc[i][j] >= MIN_SCORE else -1.0
            best[i][j] = max(take, best[i + 1][j], best[i][j + 1])
    out, i, j = [], 0, 0
    while i < n and j < m:
        if sc[i][j] >= MIN_SCORE and best[i][j] == best[i + 1][j + 1] + sc[i][j] - MIN_SCORE:
            out.append((xs[i], ys[j])); i += 1; j += 1
        elif best[i][j] == best[i + 1][j]:
            i += 1
        else:
            j += 1
    return out


class Pairing:
    def __init__(self, A, B):
        self.A, self.B = A, B
        self.pairs, self.back, self.why = {}, {}, {}

    def add(self, a, b, why):
        if a in self.pairs or b in self.back or a not in self.A.size or b not in self.B.size:
            return False
        self.pairs[a], self.back[b], self.why[a] = b, a, why
        return True

    def seed(self, hidden=frozenset(), bsim=None):
        A, B = self.A, self.B
        for n, a in A.exports.items():
            if a not in hidden and n in B.exports:
                self.add(a, B.exports[n], "export")
        aby, bby = collections.defaultdict(set), collections.defaultdict(set)
        for a, ss in A.strings.items():
            if a not in hidden:
                for s in ss:
                    aby[s].add(a)
        for b, ss in B.strings.items():
            for s in ss:
                bby[s].add(b)
        votes = collections.defaultdict(collections.Counter)
        for s, xs in aby.items():
            if len(s) >= 6 and len(xs) == 1 and len(bby.get(s, ())) == 1:
                votes[next(iter(xs))][next(iter(bby[s]))] += 1
        for a, c in votes.items():
            (b, n), = c.most_common(1)
            if n == sum(c.values()):
                self.add(a, b, "string")
        for a, b in (bsim or {}).items():
            self.add(a, b, "bsim")

    def propagate(self):
        """Call-graph gap fill and callee fingerprints until neither grows."""
        A, B, pairs, back = self.A, self.B, self.pairs, self.back
        for _ in range(6):
            grew = 0
            for a, b in list(pairs.items()):
                xs, ys = A.calls.get(a, []), B.calls.get(b, [])
                if not xs or not ys:
                    continue
                anchors, j0 = [], 0
                for i, t in enumerate(xs):
                    if t in pairs:
                        for j in range(j0, len(ys)):
                            if ys[j] == pairs[t]:
                                anchors.append((i, j)); j0 = j + 1
                                break
                # a gap at either end of the call list is too loose; WorldBuilder's extra assert
                # calls sit in gaps of their own, so a one-to-one gap is still informative
                for (i1, j1), (i2, j2) in zip(anchors, anchors[1:]):
                    ga = {t for t in xs[i1 + 1:i2] if t not in pairs}
                    gb = {t for t in ys[j1 + 1:j2] if t not in back}
                    if len(ga) == 1 and len(gb) == 1:
                        x, y = next(iter(ga)), next(iter(gb))
                        sx, sy = A.size.get(x, 0), B.size.get(y, 0)
                        if sx and sy and 0.3 <= sx / sy <= 1.5:
                            grew += self.add(x, y, "gap")
            callers = collections.defaultdict(set)
            for b, ts in B.calls.items():
                if b not in back:
                    for t in set(ts):
                        callers[t].add(b)
            for a, ts in A.calls.items():
                if a in pairs:
                    continue
                mapped = {pairs[t] for t in set(ts) if t in pairs}
                if len(mapped) < 3:
                    continue
                ranked = collections.Counter(b for t in mapped for b in callers.get(t, ())).most_common(2)
                if ranked and ranked[0][1] >= max(3, 0.8 * len(mapped)) and (len(ranked) == 1 or ranked[1][1] < ranked[0][1]):
                    grew += self.add(a, ranked[0][0], "fingerprint")
            if not grew:
                return

    def align_pass(self):
        A, B = self.A, self.B

        def score(a, b):
            if not 0.33 <= A.size[a] / max(1, B.size[b]) <= 3:
                return 0.0
            x, y = A.shape(a), B.shape(b)
            return difflib.SequenceMatcher(None, x, y, autojunk=False).ratio() if x and y else 0.0
        grew = 0
        items = sorted(self.pairs.items())
        for (a1, b1), (a2, b2) in zip(items, items[1:]):
            if not (0 < a2 - a1 <= MAX_GAP and 0 < b2 - b1 <= MAX_GAP):
                continue
            xs = [a for a in A.funcs[bisect.bisect_right(A.funcs, a1):bisect.bisect_left(A.funcs, a2)] if a not in self.pairs]
            ys = [b for b in B.funcs[bisect.bisect_right(B.funcs, b1):bisect.bisect_left(B.funcs, b2)] if b not in self.back]
            if xs and ys and len(xs) * len(ys) <= MAX_CELLS:
                for a, b in align(xs, ys, score):
                    grew += self.add(a, b, "aligned")
        return grew


def pair(A, B, bsim=None, hidden=frozenset()):
    P = Pairing(A, B)
    P.seed(hidden, bsim)
    P.propagate()
    while P.align_pass():
        P.propagate()
    return P


def bsim_seeds(path, A, B):
    """BSim unique top-1: similarity >= 0.5, >= 0.05 ahead of the runner-up, claimed once, >= 16 B."""
    cand = collections.defaultdict(list)
    for r in csv.DictReader(open(path, encoding="utf-8", newline=""), delimiter="\t"):
        cand[int(r["game_rva"], 16)].append((int(r["match_va"], 16) - B.base, float(r["similarity"])))
    top = {}
    for a, v in cand.items():
        v.sort(key=lambda t: -t[1])
        second = next((s for b, s in v[1:] if b != v[0][0]), 0.0)
        if A.size.get(a, 0) >= 16 and v[0][1] >= 0.5 and v[0][1] - second >= 0.05:
            top[a] = v[0][0]
    claims = collections.Counter(top.values())
    return {a: b for a, b in top.items() if claims[b] == 1}


def measured_pair(A, B, bsim):
    """Pair A with B; refuse when half the export/string seeds, hidden, are not recovered precisely."""
    probe = Pairing(A, B)
    probe.seed()
    trusted = sorted(a for a, w in probe.why.items() if w in ("export", "string"))
    random.Random(1).shuffle(trusted)
    test = {a: probe.pairs[a] for a in trusted[len(trusted) // 2:]}
    held = pair(A, B, bsim, frozenset(test))
    hit = [a for a in test if a in held.pairs]
    precision = sum(held.pairs[a] == test[a] for a in hit) / max(1, len(hit))
    floor = FLOORS[(A.kind, B.kind)]
    print(f"{A.kind}-{B.kind}: held-out precision {precision:.1%} on {len(hit):,} of {len(test):,} hidden seeds (floor {floor:.0%})")
    if precision < floor:
        fail(f"{A.kind}-{B.kind} held-out precision {precision:.1%} is below {floor:.0%}; inputs are "
             f"mismatched or the matcher regressed, so nothing was written")
    full = pair(A, B, bsim)
    print(f"{A.kind}-{B.kind}: {len(full.pairs):,} pairs {dict(collections.Counter(full.why.values()))}")
    return full


def unique_labels(side):
    count = collections.Counter(next(iter(v)) for v in side.labels.values() if len(v) == 1)
    return {w: next(iter(v)) for w, v in side.labels.items() if len(v) == 1 and count[next(iter(v))] == 1}


def names(p1, p12, p2, labels1, labels2):
    """{rva: (label, route, basis)}; an address whose routes disagree is dropped."""
    out = {}
    for g in set(p1.pairs) | set(p2.pairs):
        found = {}
        w1 = p1.pairs.get(g)
        if w1 in labels1:
            found["wb1"] = (labels1[w1], [p1.why[g]])
        if p12.pairs.get(w1) in labels2:
            found["chain"] = (labels2[p12.pairs[w1]], [p1.why[g], p12.why[w1]])
        if p2.pairs.get(g) in labels2:
            found["direct"] = (labels2[p2.pairs[g]], [p2.why[g]])
        if found and len({lab for lab, _ in found.values()}) == 1:
            legs = [w for _, ws in found.values() for w in ws]
            out[g] = (next(iter(found.values()))[0], "+".join(sorted(found)),
                      "strong" if set(legs) <= STRONG else "aligned")
    return out


def wb_files(w):
    """WorldBuilder function -> its one .cpp path, filling runs between same-file functions."""
    def cpp(a):
        c = {p for p in w.paths.get(a, ()) if p.lower().endswith(".cpp")}
        return next(iter(c)) if len(c) == 1 else None
    order = sorted(w.size)
    known = [(i, cpp(a)) for i, a in enumerate(order) if cpp(a)]
    out = {order[i]: (f, "direct") for i, f in known}
    for (i1, f1), (i2, f2) in zip(known, known[1:]):
        if f1 == f2 and 1 < i2 - i1 <= 30:
            for k in range(i1 + 1, i2):
                if not w.paths.get(order[k]):
                    out[order[k]] = (f1, "filled")
    return out


def zh_files():
    """Class::method -> Code-relative .cpp for members Zero Hour defines out of line in one file."""
    where = collections.defaultdict(set)
    for path in ZH.rglob("*.cpp"):
        rel = path.relative_to(ZH).as_posix()
        if rel.startswith("Tools/"):
            continue
        # definitions start in column 0; an indented Class::method( is a call
        for m in re.finditer(r"^(?:[\w:<>,]+[ \t*&]+)*?([A-Z]\w+)::(~?\w+)[ \t]*\(", path.read_text(encoding="latin1"), re.M):
            where[f"{m.group(1)}::{m.group(2)}".lower()].add(rel)
    return {k: next(iter(v)) for k, v in where.items() if len(v) == 1}


def files(G, p1, p2, f1, f2, zh):
    """{rva: (path, route)}: direct evidence by precedence, then retail-order runs between it."""
    own = [a for a in G.funcs if a not in G.vendored and not re.match(r"(uw|eh)_[0-9a-f]{8}$", G.name.get(a) or "")]
    out = {}
    for g in own:
        w1 = f1.get(p1.pairs.get(g))
        w2 = f2.get(p2.pairs.get(g))
        z = zh.get((plain(G.name.get(g)) or "").lower())
        if w1:
            out[g] = (w1[0], "wb1" if w1[1] == "direct" else "wb1-run")
        elif z and w2 and z.lower() != w2[0].lower():
            continue
        elif z:
            out[g] = (z, "zh")
        elif w2:
            out[g] = (w2[0], "wb2" if w2[1] == "direct" else "wb2-run")
    anchors = [(i, out[a][0]) for i, a in enumerate(own) if a in out]
    for (i1, f1_), (i2, f2_) in zip(anchors, anchors[1:]):
        if f1_.lower() == f2_.lower() and 1 < i2 - i1 <= RUN:
            for k in range(i1 + 1, i2):
                out[own[k]] = (f1_, "retail-run")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--wb1", required=True, help="BFME1 WorldBuilder export directory")
    ap.add_argument("--wb2", required=True, help="BFME2 WorldBuilder export directory")
    ap.add_argument("--wb2-exe", required=True, help="BFME2 worldbuilder.exe (not shipped in this repo)")
    ap.add_argument("--bsim", help="directory with game_wb1.tsv, game_wb2.tsv, wb1_wb2.tsv")
    args = ap.parse_args()
    sys.stdout.reconfigure(line_buffering=True)
    G = game_side()
    W1 = wb_side("wb1", args.wb1, WB1_EXE, internal=False)
    W2 = wb_side("wb2", args.wb2, args.wb2_exe, internal=False)
    V1 = wb_side("wb1", args.wb1, WB1_EXE, internal=True)
    V2 = wb_side("wb2", args.wb2, args.wb2_exe, internal=True)
    bsim = {}
    for key, (a, b) in {"game_wb1": (G, W1), "game_wb2": (G, W2), "wb1_wb2": (V1, V2)}.items():
        if args.bsim:
            path = Path(args.bsim) / f"{key}.tsv"
            if not path.is_file():
                fail(f"{path} missing")
            bsim[key] = bsim_seeds(path, a, b)
            print(f"BSim seeds {key}: {len(bsim[key]):,}")
    p1 = measured_pair(G, W1, bsim.get("game_wb1"))
    p12 = measured_pair(V1, V2, bsim.get("wb1_wb2"))
    p2 = measured_pair(G, W2, bsim.get("game_wb2"))
    named = names(p1, p12, p2, unique_labels(W1), unique_labels(W2))
    placed = files(G, p1, p2, wb_files(W1), wb_files(W2), zh_files())
    rows = [(g, "name", *v) for g, v in named.items()] + [(g, "file", f, route, "") for g, (f, route) in placed.items()]
    rows.sort(key=lambda r: (r[0], r[1]))
    with open(OUT, "w", encoding="utf-8", newline="") as f:
        out = csv.writer(f, lineterminator="\n")
        out.writerow(["rva", "kind", "value", "route", "basis"])
        for g, kind, value, route, basis in rows:
            out.writerow([f"0x{g:08X}", kind, value, route, basis])
    by = collections.Counter((r[1], r[3]) for r in rows)
    print(f"wrote {OUT.relative_to(ROOT)}: {len(named):,} names, {len(placed):,} files; {dict(sorted(by.items()))}")


if __name__ == "__main__":
    main()
