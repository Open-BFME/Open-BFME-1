#!/usr/bin/env python3
"""Nearest already-matched neighbours of a retail function, across BFME1/BFME2/RotWK.

Agents learn a class layout, an inlined helper or a codegen idiom on one body and
reuse it on the next; the queues served work by address or size, so the next body
was rarely the one that lesson applied to. This indexes every retail function by
its masked instruction n-grams and serves, per unmatched function, the matched
functions it most resembles -- with their source files as the lead.

Features: capstone disassembly of the function's retail bytes; each instruction
becomes `mnemonic operands` with general registers masked to R (register
allocation must not separate two bodies), constants >= 0x100 masked to I
(addresses and relocations), and branch/call targets dropped. 2- and 3-grams of
those tokens are hashed; n-grams present in more than 1% of a game's functions
are stop-words (prologues, epilogues). Similarity is the Jaccard index of the
remaining n-gram sets, retrieved through a bottom-k sketch index.

Games: the home game comes from this repo; other games are added with
--game NAME=EXE,FUNCTIONS[,LEDGER] (FUNCTIONS: rva,size,name CSV or a
tools/ghidra_refdb.py snapshot) or the SIMILAR_GAMES environment variable
(the same specs joined with ';'). Features are cached in build/similar/.

Usage:
  python3 tools/similar.py near 0x00448352 [--k 5] [--json]
  python3 tools/similar.py queue [--limit 20] [--min-score 0.5] [--json]
  python3 tools/similar.py build             (warm the feature cache)
"""
import argparse
import array
import bisect
import collections
import concurrent.futures
import csv
import hashlib
import json
import os
import pickle
import re
import sqlite3
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CACHE = ROOT / "build" / "similar"
FEATURE_VERSION = 1
SKETCH = 32
STOP_SHARE = 0.01
MIN_TOKENS = 3
GENERATED = re.compile(r"(?:^|/)gen_\w+/")
MASK64 = (1 << 64) - 1


def _layout():
    """(game, exe, ghidra_functions.csv, functions.csv) for this checkout."""
    if (ROOT / "targets" / "game" / "reverse").is_dir():
        reverse = ROOT / "targets" / "game" / "reverse"
        exe = ROOT / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
        return "bfme1", exe, reverse / "ghidra_functions.csv", reverse / "functions.csv"
    reverse = ROOT / "reverse"
    exe = ROOT / "baselines/bfme2/workshop-vanilla-1.06/files/game.dat"
    return "bfme2", exe, reverse / "ghidra_functions.csv", reverse / "functions.csv"


HOME, HOME_EXE, HOME_FUNCTIONS, HOME_LEDGER = _layout()


class Game:
    def __init__(self, name, exe, functions, ledger=None):
        self.name, self.exe, self.functions = name, Path(exe), Path(functions)
        self.ledger = Path(ledger) if ledger else None

    @classmethod
    def parse(cls, spec):
        name, _, rest = spec.partition("=")
        parts = rest.split(",")
        if not name or len(parts) not in (2, 3):
            raise SystemExit(f"bad game spec {spec!r}: NAME=EXE,FUNCTIONS[,LEDGER]")
        return cls(name, *parts)


def default_games():
    games = [Game(HOME, HOME_EXE, HOME_FUNCTIONS, HOME_LEDGER)]
    peer = ROOT / "reference" / "open-bfme-1"
    if HOME == "bfme2" and (peer / "targets/game/reverse/ghidra_functions.csv").exists():
        exe = peer / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
        if exe.exists():
            games.append(Game("bfme1", exe, peer / "targets/game/reverse/ghidra_functions.csv",
                              peer / "targets/game/reverse/functions.csv"))
    for spec in filter(None, os.environ.get("SIMILAR_GAMES", "").split(";")):
        game = Game.parse(spec)
        games = [g for g in games if g.name != game.name] + [game]
    return games


# ----------------------------------------------------------------- features

def pe_sections(blob):
    """[(rva, size, file_offset)] for each section of a PE image."""
    lfanew = struct.unpack_from("<I", blob, 0x3C)[0]
    count = struct.unpack_from("<H", blob, lfanew + 6)[0]
    optional = struct.unpack_from("<H", blob, lfanew + 20)[0]
    table = lfanew + 24 + optional
    out = []
    for i in range(count):
        vsize, rva, raw_size, raw = struct.unpack_from("<IIII", blob, table + 40 * i + 8)
        out.append((rva, min(vsize or raw_size, raw_size), raw))
    return out


def read_rva(blob, sections, rva, size):
    for start, length, raw in sections:
        if start <= rva < start + length:
            end = min(rva + size, start + length)
            return blob[raw + rva - start: raw + end - start]
    return b""


HEX = re.compile(r"0x[0-9a-f]+")
GPR = re.compile(r"\b(?:e?[abcd]x|[abcd][lh]|e?[sd]i)\b")
BRANCH = re.compile(r"^(?:j\w+|call|loop\w*)$")
_TOKEN_HASH = {}


def normalise(mnemonic, ops):
    if BRANCH.match(mnemonic):
        return mnemonic if not ops.startswith(("dword", "e", "[")) else mnemonic + " *"
    ops = HEX.sub(lambda m: m[0] if int(m[0], 16) < 0x100 else "I", ops)
    return mnemonic + " " + GPR.sub("R", ops)


def _h(token):
    value = _TOKEN_HASH.get(token)
    if value is None:
        value = int.from_bytes(hashlib.blake2b(token.encode(), digest_size=8).digest(), "little")
        _TOKEN_HASH[token] = value
    return value


def shingles(tokens):
    """Sorted unique 64-bit hashes of the token 2- and 3-grams (1-grams if shorter)."""
    hashed = [_h(t) for t in tokens]
    out = set()
    if len(hashed) < 2:
        out.update(hashed)
    for i in range(len(hashed) - 1):
        out.add((hashed[i] * 0x9E3779B97F4A7C15 + hashed[i + 1]) & MASK64)
        if i + 2 < len(hashed):
            out.add((hashed[i] * 0xC2B2AE3D27D4EB4F + hashed[i + 1] * 0x165667B19E3779F9
                     + hashed[i + 2]) & MASK64)
    return array.array("Q", sorted(out))


def tokens_of(code):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return [normalise(m, o) for _, _, m, o in md.disasm_lite(code, 0)]


_WORKER = {}


def _init_worker(exe):
    blob = Path(exe).read_bytes()
    _WORKER["blob"], _WORKER["sections"] = blob, pe_sections(blob)


def _features(chunk):
    out = []
    for rva, size in chunk:
        code = read_rva(_WORKER["blob"], _WORKER["sections"], rva, size)
        tokens = tokens_of(code)
        out.append((rva, size, len(tokens), shingles(tokens)))
    return out


def read_functions(path):
    """[(rva, size, name)] from a rva,size,name CSV or a ghidra_refdb snapshot."""
    path = Path(path)
    if path.suffix == ".sqlite":
        db = sqlite3.connect(f"file:{path.as_posix()}?mode=ro", uri=True)
        try:
            rows = db.execute("SELECT rva, max_rva - rva + 1, name FROM functions "
                              "WHERE thunk = 0 AND ranges = 1").fetchall()
        finally:
            db.close()
        return sorted(rows)
    with path.open(encoding="utf-8", newline="") as handle:
        return sorted((int(r["rva"], 16), int(r["size"]), r["name"])
                      for r in csv.DictReader(handle) if r.get("size"))


def _digest(*paths):
    h = hashlib.sha256(f"v{FEATURE_VERSION}".encode())
    for path in paths:
        st = Path(path).stat()
        h.update(f"{Path(path).resolve()}|{st.st_size}|{st.st_mtime_ns}".encode())
    return h.hexdigest()[:16]


def game_features(game, jobs=None):
    """{rva: (size, ntokens, shingles)} for every function of a game, cached."""
    key = _digest(game.exe, game.functions)
    path = CACHE / f"{game.name}-{key}.pkl"
    if path.exists():
        with path.open("rb") as handle:
            return pickle.load(handle)
    functions = [(rva, size) for rva, size, name in read_functions(game.functions)
                 if size >= 6 and not name.startswith("thunk_")]
    chunks = [functions[i:i + 2000] for i in range(0, len(functions), 2000)]
    feats = {}
    if jobs == 1 or len(chunks) <= 1:
        _init_worker(game.exe)
        results = map(_features, chunks)
    else:
        pool = concurrent.futures.ProcessPoolExecutor(
            max_workers=jobs or min(16, os.cpu_count() or 1),
            initializer=_init_worker, initargs=(str(game.exe),))
        results = pool.map(_features, chunks)
    for result in results:
        for rva, size, ntokens, sh in result:
            feats[rva] = (size, ntokens, sh)
    CACHE.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(".tmp")
    with tmp.open("wb") as handle:
        pickle.dump(feats, handle, protocol=pickle.HIGHEST_PROTOCOL)
    os.replace(tmp, path)
    return feats


def stop_words(feats):
    counts = collections.Counter()
    for _, _, sh in feats.values():
        counts.update(sh)
    floor = max(20, int(len(feats) * STOP_SHARE))
    return {h for h, n in counts.items() if n > floor}


# ----------------------------------------------------------------- ledger

def matched_rows(ledger):
    """{rva: (name, source)} for byte-true rows with a real (non-generated) source."""
    out = {}
    if not ledger or not Path(ledger).exists():
        return out
    with Path(ledger).open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            source = (row.get("source") or "").replace("\\", "/")
            if (row.get("status") != "matched" or not row.get("target_rva")
                    or not source.endswith((".cpp", ".c", ".h", ".inl"))
                    or GENERATED.search(source)):
                continue
            out.setdefault(int(row["target_rva"], 16), (row["name"], source))
    return out


def covered(ledger_rows_with_size):
    ranges = sorted(ledger_rows_with_size)
    starts = [s for s, _ in ranges]

    def inside(point):
        i = bisect.bisect_right(starts, point) - 1
        return i >= 0 and point < ranges[i][1]
    return inside


# ----------------------------------------------------------------- index

class Index:
    """Matched functions of every game, searchable by sketch overlap."""

    def __init__(self, games, jobs=None):
        self.games = games
        self.feats = {g.name: game_features(g, jobs) for g in games}
        self.stop = set()
        for feats in self.feats.values():
            self.stop |= stop_words(feats)
        self.matched = {g.name: matched_rows(g.ledger) for g in games}
        self.names = {}
        for g in games:
            self.names[g.name] = {rva: name for rva, _, name in read_functions(g.functions)}
        self.postings = collections.defaultdict(list)
        self.sets = {}
        for game, rows in self.matched.items():
            feats = self.feats[game]
            for rva in rows:
                if rva in feats:
                    key = (game, rva)
                    kept = self._kept(feats[rva][2])
                    if len(kept) < MIN_TOKENS:
                        continue
                    self.sets[key] = kept
                    for h in sorted(kept)[:SKETCH]:
                        self.postings[h].append(key)

    def _kept(self, sh):
        return frozenset(h for h in sh if h not in self.stop)

    def near(self, game, rva, k=5, exclude_self=True):
        """[(score, game, rva)] best first for one function of one game."""
        feat = self.feats[game].get(rva)
        if feat is None:
            return []
        query = self._kept(feat[2])
        if len(query) < MIN_TOKENS:
            return []
        votes = collections.Counter()
        for h in sorted(query)[:SKETCH]:
            for key in self.postings.get(h, ()):
                votes[key] += 1
        # Bottom-k overlap shortlists; the exact Jaccard index ranks.
        shortlist = [key for key, _ in sorted(votes.items(), key=lambda kv: (-kv[1], kv[0]))[:64]]
        scored = []
        for key in shortlist:
            if exclude_self and key == (game, rva):
                continue
            other = self.sets[key]
            union = len(query | other)
            scored.append((round(len(query & other) / union, 4) if union else 0.0, *key))
        scored.sort(key=lambda t: (-t[0], t[1], t[2]))
        return scored[:k]

    def lead(self, score, game, rva):
        name, source = self.matched[game][rva]
        return {"score": score, "game": game, "rva": f"0x{rva:08X}", "name": name,
                "source": source, "size": self.feats[game][rva][0]}


def candidates(index, claimed=None, claimed_ranges=None, min_score=0.5, k=3):
    """Unmatched home functions ranked by similarity to matched code (any game).

    `claimed`/`claimed_ranges` are next_work's open-work sets; without them the
    home ledger's matched rows decide what is done."""
    feats = index.feats[HOME]
    names = index.names[HOME]
    if claimed is None:
        claimed = set(index.matched[HOME])
        claimed_ranges = [(rva, rva + feats[rva][0]) for rva in claimed if rva in feats]
    inside = covered(claimed_ranges or [])
    out = []
    for rva in sorted(feats):
        if rva in claimed or inside(rva):
            continue
        hits = index.near(HOME, rva, k)
        if not hits or hits[0][0] < min_score:
            continue
        leads = [index.lead(*hit) for hit in hits]
        out.append({
            "function": names.get(rva, f"FUN_{rva:08X}"),
            "target_rva": f"0x{rva:08X}",
            "size": feats[rva][0],
            "similarity": leads[0]["score"],
            "source": leads[0]["source"],
            "neighbours": leads,
            "command": f"python3 tools/similar.py near 0x{rva:08X}",
        })
    out.sort(key=lambda c: (-c["similarity"], -c["size"], c["target_rva"]))
    return out


QUEUE_MAX_AGE = 6 * 3600


def served_queue(claimed, claimed_ranges, games=None, min_score=0.5, max_age=QUEUE_MAX_AGE):
    """next_work's `similar` tier: the cached ranking, filtered to open work now.

    Ranking every unmatched function costs about a minute, far over next_work's
    budget, so the full queue is cached for `max_age` seconds and only the
    claimed filter runs per call. A neighbour matched after the cache was
    written is missed until the next refresh; a function claimed since is not.
    """
    import time
    games = games or default_games()
    key = hashlib.sha256("|".join(
        f"{g.name}:{_digest(g.exe, g.functions)}" for g in games).encode()).hexdigest()[:16]
    path = CACHE / f"queue-{HOME}-{key}-{min_score}.json"
    if path.exists() and time.time() - path.stat().st_mtime < max_age:
        queue = json.loads(path.read_text(encoding="utf-8"))
    else:
        queue = candidates(Index(games), min_score=min_score)
        CACHE.mkdir(parents=True, exist_ok=True)
        tmp = path.with_suffix(".tmp")
        tmp.write_text(json.dumps(queue), encoding="utf-8")
        os.replace(tmp, path)
    inside = covered(claimed_ranges or [])
    return [c for c in queue
            if int(c["target_rva"], 16) not in claimed and not inside(int(c["target_rva"], 16))]


# ----------------------------------------------------------------- cli

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=("near", "queue", "build"))
    ap.add_argument("rva", nargs="?")
    ap.add_argument("--game", action="append", default=[],
                    help="NAME=EXE,FUNCTIONS[,LEDGER] (repeatable; overrides defaults by name)")
    ap.add_argument("--of", default=HOME, help="game the RVA belongs to (default: this repo's)")
    ap.add_argument("--k", type=int, default=5)
    ap.add_argument("--limit", type=int, default=20)
    ap.add_argument("--min-score", type=float, default=0.5)
    ap.add_argument("--jobs", type=int)
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args(argv)
    games = default_games()
    for spec in args.game:
        game = Game.parse(spec)
        games = [g for g in games if g.name != game.name] + [game]
    index = Index(games, args.jobs)
    if args.cmd == "build":
        for g in games:
            print(f"{g.name}: {len(index.feats[g.name])} functions, "
                  f"{sum(1 for k in index.sets if k[0] == g.name)} matched indexed")
        return
    if args.cmd == "near":
        if not args.rva:
            ap.error("near needs an RVA")
        leads = [index.lead(*hit) for hit in index.near(args.of, int(args.rva, 16), args.k)]
        if args.json:
            print(json.dumps(leads, indent=2))
            return
        for lead in leads:
            print(f"{lead['score']:.3f} {lead['game']} {lead['rva']} {lead['size']:>5}B "
                  f"{lead['name']}\n      {lead['source']}")
        if not leads:
            print("no matched neighbour shares enough n-grams")
        return
    queue = candidates(index, min_score=args.min_score)
    if args.json:
        print(json.dumps(queue[:args.limit], indent=2))
        return
    print(f"{len(queue)} unmatched {HOME} function(s) with a matched neighbour >= {args.min_score}")
    for c in queue[:args.limit]:
        best = c["neighbours"][0]
        print(f"  {c['similarity']:.3f} {c['target_rva']} {c['size']:>5}B {c['function']}"
              f"\n      like {best['game']} {best['rva']} {best['name']} ({best['source']})")


if __name__ == "__main__":
    main()
