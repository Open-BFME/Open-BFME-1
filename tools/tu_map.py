#!/usr/bin/env python3
"""Which original source file (TU) each retail function and data range came from.

The ledger records where a body sits in THIS tree, which is mostly one file per
function. Retail was linked from real translation units, and a TU's functions
sit next to each other in .text in the order the linker took the objects. This
tool recovers that structure from evidence and writes it to `tu_map.csv` next to
the ledger, so the skeleton generator (tools/tu_skeleton.py) and the ownership
invariant (tools/tu_ownership.py) work from one table instead of a guess each.

Signals, strongest first (one letter each in the `by` and `evidence` columns):

  F  the function references a `__FILE__` string naming a .cpp (assert/debug
     paths survive in retail); the string IS the TU.
  Z  `Class::method(` is defined in that file of the Zero Hour reference.
  S  every ZH definition of `Class::` sits in one .cpp: the class's site.
  N  naming convention `<dir>/<Class>.cpp` (ModuleData suffix stripped); used
     only inside the address cluster an F/Z/S anchor or a run of N rows forms.
  C  address contiguity: the nearest assigned rows on both sides agree and are
     within 0x3000 bytes (retail object order keeps a TU contiguous).
  K  placeholder-class propagation (`??1Rva...` follows its `??_GRva...`).
  X  data: every function that references the item is assigned to one TU.

Class name alone is not a TU key: repo-wide only 42% of rows agree between Z and
N, and header-inline bodies (??_G, friend_new*, *ModuleData ctors) are emitted as
COMDATs in whichever TU used them first. A naming hint outside its TU's main
address cluster is therefore `displaced`, never assigned.

Confidence:
  approved  the TU's main cluster holds at least one F/Z/S anchor, the row is
            assigned by F/Z/S/N or bracketed (C) by approved rows, and no row
            approved for a different TU sits inside the TU's address span
            (a TU that is not contiguous in retail is not trusted).
  proposed  assigned, but by N/K only, by brackets that are not approved, or in
            a non-contiguous span. The queue for investigation.
  displaced a naming hint sat outside its TU's cluster (COMDAT pile).
Rows with no signal are not written; they have no TU.

The output is a pure function of the ledger, ghidra_functions.csv,
string_xrefs.tsv, data_xrefs.tsv and the ZH tree: rerunning on unchanged inputs
writes the same bytes. Never edit tu_map.csv by hand; regenerate it.

Usage:
  python3 tools/tu_map.py                write tu_map.csv, print a summary
  python3 tools/tu_map.py --check        exit 1 when tu_map.csv is stale
  python3 tools/tu_map.py --dir PREFIX   summary for one directory's rows
"""
import argparse
import bisect
import collections
import csv
import io
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAP = 0x3000          # max distance between bracketing anchors (C)
UNION_SPAN = 0x2000   # clusters this small that interleave are one TU
COLUMNS = ["rva", "size", "kind", "tu", "confidence", "by", "evidence", "source"]


class Layout:
    """Where this repo keeps its ledger, sources and reference tree."""

    def __init__(self, root):
        self.root = Path(root)
        if (self.root / "targets/game/reverse/functions.csv").exists():
            self.reverse = "targets/game/reverse"   # Open-BFME-1
            self.src = "game/"
            self.zh = self.root / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
        else:
            self.reverse = "reverse"                # Open-BFME-2
            self.src = "Code/"
            self.zh = self.root / ("reference/open-bfme-1/inputs/reference/"
                                   "CnC_Generals_Zero_Hour/GeneralsMD/Code")

    def path(self, name):
        return self.root / self.reverse / name

    @property
    def out(self):
        return self.path("tu_map.csv")


def read_csv(path):
    if not path.exists():
        return []
    return list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8", errors="replace"), newline="")))


CTOR = re.compile(r"^\?\?(_G|_E|0|1)([A-Za-z_]\w*)@@")
METHOD = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
PLACEHOLDER = re.compile(r"^(Rva|rva|Gen|gen|Sub|sub|FUN_)[0-9A-Fa-f_]")
COMDAT = re.compile(r"^\?\?_[GE]|^\?friend_new|^\?\?[01]\w*ModuleData@@")
ZH_DEF = re.compile(r"^[^\s#/][^;(){}]*?\b([A-Za-z_]\w*)\s*::\s*(~?[A-Za-z_]\w*)\s*\(", re.M)


def demangle(name):
    m = CTOR.match(name)
    if m:
        return m.group(2), {"0": m.group(2), "1": "~" + m.group(2)}.get(m.group(1), "?" + m.group(1))
    m = METHOD.match(name)
    if m:
        return m.group(2), m.group(1)
    return None, name


class Paths:
    """Map a reference path onto this tree's spelling (case-insensitive)."""

    def __init__(self, layout, sources):
        self.layout = layout
        self.dirs = {}
        for s in sorted(sources):
            parts = s.split("/")
            for i in range(1, len(parts)):
                self.dirs.setdefault("/".join(parts[:i]).lower(), "/".join(parts[:i]))
        self.files = {s.lower(): s for s in sorted(sources)}

    def repo(self, code_rel):
        """`GameEngine/Source/X/Y.cpp` (relative to a Code/ root) -> repo path."""
        rel = (self.layout.src + code_rel.replace("\\", "/").lstrip("/"))
        if rel.lower() in self.files:
            return self.files[rel.lower()]
        parts = rel.split("/")
        for i in range(len(parts) - 1, 0, -1):
            hit = self.dirs.get("/".join(parts[:i]).lower())
            if hit:
                return hit + "/" + "/".join(parts[i:])
        return rel


def zh_index(layout, paths):
    meth, sites = {}, collections.defaultdict(set)
    if not layout.zh.exists():
        return meth, {}
    for dp, dn, fn in sorted(os.walk(layout.zh)):
        dn.sort()
        for f in sorted(fn):
            if not f.lower().endswith(".cpp"):
                continue
            p = Path(dp) / f
            rel = paths.repo(p.relative_to(layout.zh).as_posix())
            try:
                text = p.read_text(encoding="latin-1")
            except OSError:
                continue
            for c, m in ZH_DEF.findall(text):
                meth.setdefault((c, m), rel)
                sites[c].add(rel)
    return meth, {c: next(iter(v)) for c, v in sites.items() if len(v) == 1}


def file_strings(layout, paths, owner):
    out = {}
    path = layout.path("string_xrefs.tsv")
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        text, _, refs = line.rpartition("\t")
        m = re.search(r"[\\/]Code[\\/](.+\.(?:cpp|c))$", text, re.I)
        if not m or not refs.startswith("0x"):
            continue
        tu = paths.repo(m.group(1))
        for ref in refs.split(","):
            try:
                o = owner(int(ref, 16))
            except ValueError:
                continue
            if o is not None:
                out.setdefault(o, tu)
    return out


def build(layout):
    ledger = read_csv(layout.path("functions.csv"))
    rows, seen = [], set()
    for r in ledger:
        if "gen-alias" in (r.get("notes") or "") or not r["target_rva"].startswith("0x"):
            continue
        rva = int(r["target_rva"], 16)
        if rva in seen:
            continue                       # one identity per address; first row wins
        seen.add(rva)
        try:
            size = int(r["target_size"])
        except ValueError:
            size = 0
        rows.append(dict(rva=rva, size=size, kind="code", name=r["name"], source=r["source"]))
    for g in read_csv(layout.path("ghidra_functions.csv")):
        try:
            rva = int(g["rva"], 16)
        except (KeyError, ValueError):
            continue
        if rva not in seen and rva >= 0x1000:
            seen.add(rva)
            rows.append(dict(rva=rva, size=int(g.get("size") or 0), kind="code-unledgered", name="", source=""))
    rows.sort(key=lambda r: r["rva"])
    starts = [r["rva"] for r in rows]

    def owner(rva):
        i = bisect.bisect_right(starts, rva) - 1
        if i >= 0 and rva < starts[i] + max(rows[i]["size"], 1):
            return starts[i]
        return None

    paths = Paths(layout, {r["source"] for r in rows if r["source"]})
    zmeth, zsite = zh_index(layout, paths)
    F = file_strings(layout, paths, owner)
    for r in rows:
        r["cls"], r["meth"] = demangle(r["name"]) if r["name"] else (None, None)
        cls = r["cls"]
        r["F"] = F.get(r["rva"])
        r["Z"] = zmeth.get((cls, r["meth"])) if cls else None
        r["S"] = zsite.get(cls) if cls and not COMDAT.match(r["name"]) else None
        base = re.sub(r"ModuleData$", "", cls or "")
        r["N"] = (os.path.dirname(r["source"]) + "/" + base + ".cpp") if base and r["source"] \
            and not PLACEHOLDER.match(base) else None
        r["hard"] = r["F"] or r["Z"] or r["S"]
        r["hint"] = r["hard"] or r["N"]
        r["C"] = r["K"] = None

    # Main address cluster per hinted TU; hints outside it are displaced COMDATs.
    by_hint = collections.defaultdict(list)
    for r in rows:
        if r["hint"]:
            by_hint[r["hint"].lower()].append(r)
    main, anchored = {}, set()
    for key, members in by_hint.items():
        clusters = [[members[0]]]
        for a, b in zip(members, members[1:]):
            if b["rva"] - a["rva"] > GAP:
                clusters.append([])
            clusters[-1].append(b)
        best = max(clusters, key=lambda c: (sum(1 for x in c if x["hard"]),
                                            sum(1 for x in c if not COMDAT.match(x["name"])), len(c)))
        if not any(x["hard"] or not COMDAT.match(x["name"]) for x in best):
            continue
        if any(x["hard"] and x["hard"].lower() == key for x in best):
            anchored.add(key)
        for x in best:
            main[id(x)] = key
    for r in rows:
        key = r["hint"].lower() if r["hint"] else None
        r["A"] = r["hint"] if (r["F"] or (key and main.get(id(r)) == key)) else None
        r["disp"] = bool(r["hint"] and not r["A"])

    # TUs whose small clusters interleave are one TU (one file, several classes).
    span = {}
    for r in rows:
        if r["A"]:
            k = r["A"].lower()
            lo, hi = span.get(k, (r["rva"], r["rva"]))
            span[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
    spelled = {r["A"].lower(): r["A"] for r in rows if r["A"]}
    parent = {k: k for k in span}

    def find(k):
        while parent[k] != k:
            k = parent[k]
        return k
    order = sorted(span, key=lambda k: (span[k][0], k))
    for i, a in enumerate(order):
        for b in order[i + 1:]:
            if span[b][0] > span[a][1]:
                break
            if span[a][1] - span[a][0] > UNION_SPAN or span[b][1] - span[b][0] > UNION_SPAN:
                continue
            ra, rb = find(a), find(b)
            if ra != rb:
                keep, drop = (ra, rb) if (ra in anchored or rb not in anchored) else (rb, ra)
                parent[drop] = keep
                if drop in anchored:
                    anchored.add(keep)
    for r in rows:
        if r["A"]:
            r["A"] = spelled[find(r["A"].lower())]

    # Contiguity (C) and placeholder-class propagation (K), iterated.
    for _ in range(3):
        last = None
        prev = {}
        for r in rows:
            prev[id(r)] = last
            if r["A"]:
                last = r
        nxt = None
        for r in reversed(rows):
            a = prev[id(r)]
            if not r["A"] and not r["disp"] and a and nxt and a["A"] == nxt["A"] \
                    and nxt["rva"] - a["rva"] <= GAP:
                r["A"] = r["C"] = a["A"]
                r["Cvia"] = (a, nxt)
            if r["A"]:
                nxt = r
        votes = collections.defaultdict(collections.Counter)
        for r in rows:
            if r["A"] and r["cls"]:
                votes[r["cls"]][r["A"]] += 1
        for r in rows:
            if not r["A"] and not r["disp"] and r["cls"] and PLACEHOLDER.match(r["cls"]) \
                    and len(votes.get(r["cls"], ())) == 1:
                r["A"] = r["K"] = next(iter(votes[r["cls"]]))

    # Confidence. Retail object order: a TU must be contiguous in .text.
    for r in rows:
        r["by"] = ("F" if r["F"] and r["A"] == r["F"] else "Z" if r["Z"] and r["A"] and r["A"].lower() == r["Z"].lower()
                   else "S" if r["S"] and r["A"] and r["A"].lower() == r["S"].lower() else
                   "C" if r["C"] else "K" if r["K"] else "N" if r["A"] else "")
    assigned = [r for r in rows if r["A"]]
    lo_hi = {}
    for r in assigned:
        k = r["A"].lower()
        lo, hi = lo_hi.get(k, (r["rva"], r["rva"]))
        lo_hi[k] = (min(lo, r["rva"]), max(hi, r["rva"]))
    idx = [r["rva"] for r in assigned]
    broken = set()
    for k, (lo, hi) in lo_hi.items():
        i, j = bisect.bisect_left(idx, lo), bisect.bisect_right(idx, hi)
        if any(x["A"].lower() != k for x in assigned[i:j]):
            broken.add(k)
    roots = {find(k) for k in anchored if k in parent}
    for r in rows:
        k = r["A"].lower() if r["A"] else None
        if not k:
            r["conf"] = "displaced" if r["disp"] else ""
            continue
        ok = k in roots and k not in broken and r["by"] in "FZSN"
        r["conf"] = "approved" if ok and r["by"] else "proposed"
    for _ in range(3):   # C rows inherit approval only from two approved brackets
        for r in rows:
            if r["by"] == "C" and r["conf"] == "proposed":
                a, b = r["Cvia"]
                if a["conf"] == b["conf"] == "approved" and r["A"].lower() not in broken:
                    r["conf"] = "approved"

    out = []
    for r in rows:
        if not r["conf"]:
            continue
        ev = []
        for s in "FZSN":
            if r[s]:
                ev.append(f"{s}={r[s]}")
        if r["C"]:
            a, b = r["Cvia"]
            ev.append(f"C=0x{a['rva']:08X}..0x{b['rva']:08X}")
        if r["K"]:
            ev.append(f"K={r['cls']}")
        if r["A"] and r["A"].lower() in broken:
            ev.append("noncontiguous")
        out.append({"rva": f"0x{r['rva']:08X}", "size": r["size"], "kind": r["kind"],
                    "tu": r["A"] or "", "confidence": r["conf"], "by": r["by"] or "-",
                    "evidence": " ".join(ev), "source": r["source"]})
    out.extend(data_rows(layout, rows))
    out.sort(key=lambda d: (int(d["rva"], 16), d["kind"]))
    return out


def data_rows(layout, rows):
    """A data item belongs to the TU every one of its referencing functions is in."""
    path = layout.path("data_xrefs.tsv")
    if not path.exists():
        return []
    starts = [r["rva"] for r in rows]
    spelled = {r["A"].lower(): r["A"] for r in rows if r["A"]}
    out = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines()[1:]:
        f = line.split("\t")
        if len(f) < 8 or not f[0].startswith("0x"):
            continue
        tus, confs = set(), set()
        for c in filter(None, f[7].split(",")):
            i = bisect.bisect_right(starts, int(c, 16)) - 1
            r = rows[i] if i >= 0 else None
            if not r or not r["A"] or int(c, 16) >= r["rva"] + max(r["size"], 1):
                tus.add(None)
                continue
            tus.add(r["A"].lower())
            confs.add(r["conf"])
        if len(tus) != 1 or None in tus:
            continue
        tu = spelled[next(iter(tus))]
        out.append({"rva": f[0], "size": f[2], "kind": "data:" + f[1], "tu": tu,
                    "confidence": "approved" if confs == {"approved"} else "proposed",
                    "by": "X", "evidence": f"X={len(f[7].split(','))}refs", "source": ""})
    return out


def render(out):
    buf = io.StringIO()
    w = csv.DictWriter(buf, COLUMNS, lineterminator="\n")
    w.writeheader()
    w.writerows(out)
    return buf.getvalue()


def load(root=ROOT):
    """rva -> list of tu_map rows (code first). Empty when no map exists."""
    m = collections.defaultdict(list)
    for r in read_csv(Layout(root).out):
        m[int(r["rva"], 16)].append(r)
    return m


def summary(out, prefix=None):
    rows = [r for r in out if not prefix or r["source"].startswith(prefix)]
    conf = collections.Counter((r["kind"].split(":")[0], r["confidence"]) for r in rows)
    by = collections.Counter(r["by"] for r in rows if r["confidence"] == "approved")
    tus = collections.Counter(r["tu"] for r in rows if r["confidence"] == "approved")
    print(f"rows {len(rows)}  " + "  ".join(f"{k[0]}/{k[1]}={v}" for k, v in sorted(conf.items())))
    print("approved by " + " ".join(f"{k}={v}" for k, v in sorted(by.items())))
    print(f"approved TUs {len(tus)} (with >=2 rows: {sum(1 for v in tus.values() if v > 1)})")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true", help="exit 1 when tu_map.csv is stale")
    ap.add_argument("--dir", help="summarise rows whose current source starts with this prefix")
    ap.add_argument("--root", type=Path, default=ROOT)
    a = ap.parse_args(argv)
    layout = Layout(a.root)
    out = build(layout)
    text = render(out)
    if a.check:
        cur = layout.out.read_text(encoding="utf-8") if layout.out.exists() else ""
        if cur != text:
            print(f"tu_map: {layout.out.relative_to(layout.root).as_posix()} is stale; "
                  "run python3 tools/tu_map.py", file=sys.stderr)
            return 1
        return 0
    if not a.dir:
        layout.out.write_text(text, encoding="utf-8", newline="")
    summary(out, a.dir)
    return 0


if __name__ == "__main__":
    sys.exit(main())
