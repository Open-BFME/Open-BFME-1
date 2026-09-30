#!/usr/bin/env python3
"""Per-file LINKED check in seconds, without link.exe.

The link census (tools/link_census.py) links every object and takes minutes.
This answers the same question for one file against the last census: would
this source's object link cleanly, and what stops it? It compiles the source
(build.py's compile path, skipped when the object is current), reads its COFF
and checks it against the index the census wrote
(build/link_census/link_index.pkl: every object's strong definitions and
COMDAT copies with their retail-truth verdicts, and every file's blockers):

  unresolved  a name the object references that no other object defines and
              the real link would not find in an import library (excused())
  duplicate   a strong definition another object also defines
  comdat      a COMDAT copy that is not retail's body (link_census.keep_rule:
              retail truth where the symbol has a retail address, else the
              first copy in link order)
  addresses   hard-coded image addresses in the source (link_debt.addresses)
  selected    a name the object defines or references whose definition the
              link keeps is proven not retail's (link_census.judge_selected:
              the kept COMDAT copy is wrong, or the kept one of several
              definitions is not the ledger owner's). The holder is the one
              the census's /MAP showed, else the first definer in link order

It prints the file's LINKED bytes (its own authored + vendored bytes, 0xCC out,
as progress.real_split counts them) at the census and now. The census is the
record: this is a preview, and its answer is only as fresh as the index (a
blocker another file fixed since then still shows). Replayed over every object
of the 3361d5aec5 census it gave the census's verdict for 21,233 of 21,337
files; the other 104 it calls blocked where the census does not, because it
also counts names referenced only from a COMDAT copy link.exe discards.

  python3 tools/link_check.py game/path/File.cpp [...]   # check files
  python3 tools/link_check.py --next [--limit 30]         # names that unlock the most bytes
  python3 tools/link_check.py --publish                   # write targets/game/reverse/link_queue.csv
  python3 tools/link_check.py next [--no-claim]           # serve + claim the top open queue row

THE QUEUE. The daily census publishes --next's ranking as link_queue.csv (no
index needed to read it), and `next` serves its best row that is not claimed,
not landed since the census (a Claim-Lease trailer for its key) and whose
files have not changed since the census. Names in a family (FAMILIES) have one
owner each and are served only with `next --family F`.
"""
import argparse
import collections
import csv
import pickle
import re
import subprocess
import sys
import time
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census  # noqa: E402

INDEX = link_census.OUT / "link_index.pkl"
ADDRESSES = "<hard-coded image addresses>"


def source_bytes(sources=None):
    """{source: real bytes of its authored + vendored rows}, counted the way
    progress.real_split counts LINKED (0xCC out). Per file: a byte two files
    claim counts in both."""
    import progress
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    start, size = progress.retail_text()
    naked = set(progress.naked_cpp_rows_at(matched, None))
    image_start, image = progress._text_image()
    intervals = collections.defaultdict(list)
    for key, (length, source) in matched.items():
        if sources is not None and source not in sources:
            continue
        if progress.source_lane(source, notes[key], key in naked) not in progress.DECOMPILED_LANES:
            continue
        low, high = max(int(key[1], 16), start), min(int(key[1], 16) + length, start + size)
        if low < high:
            intervals[source].append((low, high))
    return {source: sum(high - low - image[low - image_start:high - image_start].count(0xCC)
                        for low, high in progress.merge_intervals(found))
            for source, found in intervals.items()}


def write_index(present, facts, blockers, excuses, meta, selection):
    """Called by link_census.write_status: what a per-file check needs from the
    census, in one pickle. `facts` is link_census.read_facts(present);
    `selection` holds link_census.selection_verdicts' results, holder
    exceptions and ledger owners."""
    index = {"meta": meta, **index_tables(present, facts, selection), "blockers": blockers, "excuses": excuses,
             "bytes": source_bytes(set(blockers))}
    link_census.OUT.mkdir(parents=True, exist_ok=True)
    temp = INDEX.with_suffix(".tmp")
    with temp.open("wb") as handle:
        pickle.dump(index, handle, protocol=pickle.HIGHEST_PROTOCOL)
    temp.replace(INDEX)


def index_tables(present, facts, selection):
    """The index's definition tables: every object's exclusive definitions and
    COMDAT copies by name, and the census's selection (holder exceptions,
    ledger owners)."""
    strong = collections.defaultdict(list)
    comdat = collections.defaultdict(list)
    for index, (copies, defined, _, _) in enumerate(facts):
        for name in defined:
            strong[name].append(index)
        for name, digest, _, verdict in copies:
            comdat[name].append((index, digest, verdict))
    return {"objects": [obj.name for obj in present], "strong": dict(strong), "comdat": dict(comdat),
            "selection": selection}


def load_index():
    if not INDEX.exists():
        common = _git("rev-parse", "--path-format=absolute", "--git-common-dir").strip()
        census = Path(common).parent / "build" / "wt_link" / INDEX.relative_to(ROOT)
        raise SystemExit(
            f"link_check: no census index at {INDEX.relative_to(ROOT).as_posix()} (134 MB, never tracked).\n"
            f"  copy the daily census's:  mkdir -p build/link_census && cp '{census.as_posix()}' build/link_census/\n"
            "  or build one (~35 min):   python3 tools/link_census.py --build --history\n"
            "  `link_check.py next` needs neither: it reads targets/game/reverse/link_queue.csv")
    with INDEX.open("rb") as handle:
        return pickle.load(handle)


def duplicate(name, position, exclusive, own, index):
    """Does link.exe report this object's definition of `name` (LNK2005 /
    LNK4006)? It compares every definition with the FIRST one in link order
    and reports the pair when either is exclusive (an ordinary section or a
    NODUPLICATES COMDAT); two SELECT_ANY copies fold silently. The census
    charges both objects of a reported pair. Measured on the 2026-09-29 log:
    2,183 of 2,183 sampled ANY/ANY pairs unreported, every pair with an
    exclusive side reported."""
    others = {i: True for i in index["strong"].get(name, ()) if i != own}
    for i, _, _ in index["comdat"].get(name, ()):
        if i != own:
            others.setdefault(i, False)
    if not others:
        return False
    first = min(others)
    if position < first:  # this object is the first definition: every later one is compared with it
        return exclusive or any(others.values())
    return exclusive or others[first]


def refresh(index, objects, truth):
    """Replace the census's definitions of `objects` with their current
    object files', so a fix in one file (a removed duplicate, a new datum) is
    seen when checking the others. Blockers of files not passed stay as the
    census saw them."""
    positions = {index["objects"].index(obj.name): obj for obj in objects if obj.name in index["objects"]}
    if not positions:
        return
    for table, at in (("strong", lambda entry: entry), ("comdat", lambda entry: entry[0])):
        for name, entries in index[table].items():
            if any(at(entry) in positions for entry in entries):
                index[table][name] = [entry for entry in entries if at(entry) not in positions]
    for position, obj in positions.items():
        copies, defined, _, _ = link_census.object_facts(obj, truth)
        for name in defined:
            index["strong"].setdefault(name, []).append(position)
        for name, digest, _, verdict in copies:
            index["comdat"].setdefault(name, []).append((position, digest, verdict))


def check_object(obj, index, truth, source=None):
    """{unresolved, duplicates, comdat, addresses} for one object against the index."""
    import link_debt
    copies, defined, undefined, weaks = link_census.object_facts(obj, truth)
    own = index["objects"].index(obj.name) if obj.name in index["objects"] else None
    position = own if own is not None else len(index["objects"])
    strong, comdat = index["strong"], index["comdat"]

    def elsewhere(name):
        return (any(i != own for i in strong.get(name, ())) or
                any(i != own for i, _, _ in comdat.get(name, ())))

    mine = set(defined) | {name for name, _, _, _ in copies}
    excuses = index["excuses"]
    unresolved = sorted(name for name in set(undefined) - mine
                        if not elsewhere(name) and not link_census.excused(
                            name, excuses["runtime"], excuses["imported"], excuses["stubs"]))
    duplicates = sorted(name for name in mine if duplicate(name, position, name in set(defined), own, index))
    losers = []
    for name, digest, _, verdict in copies:
        found = [(i, d, v) for i, d, v in comdat.get(name, ()) if i != own]
        found.append((position, digest, verdict))
        found.sort(key=lambda copy: copy[0])
        loses, rule = link_census.keep_rule(found)
        if loses[position]:
            losers.append((name, rule, verdict))
    addresses = []
    if source is not None:
        try:
            addresses = link_debt.addresses((ROOT / source).read_text(encoding="utf-8", errors="replace"))
        except OSError:
            pass
    return {"unresolved": unresolved, "duplicates": duplicates, "comdat": losers, "addresses": addresses,
            "selected": wrong_selected(obj, (copies, defined, undefined, weaks), own, position, index)}


def wrong_selected(obj, fact, own, position, index):
    """Names this object defines or references whose kept definition is proven
    not retail's, judged as the census judges them (link_census.judge_selected)
    with this object's current definitions in place of the census's. The
    holder is the census's /MAP holder while it still defines the name, else
    the first definer in link order."""
    copies, defined, _, _ = fact
    selection = index["selection"]
    exceptions, owners, objects = selection["exceptions"], selection["owners"], index["objects"]
    mine_copies = {name: (digest, verdict) for name, digest, _, verdict in copies}
    mine_strong = set(defined)
    found = []
    for name in sorted(link_census.touched_names(fact)):
        found_copies = {i: (d, v) for i, d, v in index["comdat"].get(name, ()) if i != own}
        exclusive = {i for i in index["strong"].get(name, ()) if i != own}
        if name in mine_copies:
            found_copies[position] = mine_copies[name]
        if name in mine_strong:
            exclusive.add(position)
        definers = set(found_copies) | exclusive
        if not definers:
            continue
        if name in exceptions:
            holder = exceptions[name]
            holder = holder if holder in definers else (min(definers) if holder is not None else None)
        else:
            holder = min(definers)
        label = {i: objects[i] if i < len(objects) else obj.name for i in definers}
        result = link_census.judge_selected(
            label[holder] if holder is not None else None,
            {label[i]: copy for i, copy in found_copies.items()}, set(label.values()),
            {label[i] for i in exclusive}, owners.get(name, set()))
        if result == "wrong":
            found.append(name)
    return found


def resolve(argument, index):
    """(source or None, object path) for a source path or an object path. A
    source is compiled when its object is not current (build.compile_rows); an
    object given directly must be current for its source
    (link_census.object_current): a stale object is last week's code, never
    evidence."""
    path = Path(argument)
    if path.suffix.lower() == ".obj":
        obj = path if path.is_absolute() else ROOT / path
        if not obj.is_file():
            raise SystemExit(f"link_check: {argument} does not exist; nothing to check (never LINKS)")
        by_object = {entry["object"]: source for source, entry in index["blockers"].items()}
        source = by_object.get(obj.name)
        if source is not None and not link_census.object_current(ROOT / source, obj):
            raise SystemExit(f"link_check: {obj.name} is not current for {source}; "
                             f"check the source instead (it recompiles)")
        return source, obj
    source = (path if path.is_absolute() else ROOT / path).resolve().relative_to(ROOT.resolve()).as_posix()
    outputs = build.compile_rows([], [ROOT / source])
    return source, outputs[ROOT / source]


def report(source, obj, result, index, now_bytes):
    census = index["blockers"].get(source or "", {})
    before = index["bytes"].get(source, 0) if census.get("linked") else 0
    clean = not any(result[kind] for kind in ("unresolved", "duplicates", "comdat", "addresses", "selected"))
    after = now_bytes if clean else 0
    print(f"{source or obj.name}: {'LINKS' if clean else 'does not link'}  "
          f"LINKED {before:,} -> {after:,} bytes (census {index['meta'].get('date', '?')} at "
          f"{index['meta'].get('commit', '?')}; file's own bytes {now_bytes:,})")
    for name in result["unresolved"]:
        print(f"  unresolved  {name}")
    for name in result["duplicates"]:
        print(f"  duplicate   {name}")
    for name, rule, verdict in result["comdat"]:
        why = {"wrong": "not retail's body", "unknown": "unproven and differs from the kept copy",
               None: "differs from the first copy in link order (no retail address)"}.get(verdict, verdict)
        print(f"  comdat      {name}  ({rule}: {why})")
    for name in result["selected"]:
        print(f"  selected    {name}  (the definition the link keeps is not retail's)")
    if result["addresses"]:
        print(f"  addresses   {len(result['addresses'])} hard-coded image address(es), e.g. {result['addresses'][0]}")
    return clean


QUEUE = ROOT / "targets" / "game" / "reverse" / "link_queue.csv"
QUEUE_FIELDS = ["rank", "name", "kind", "family", "bytes_unlocked", "files", "hint", "census"]
QUEUE_LIMIT = 500  # measured 2026-09-30: past ~500 names a fix unlocks under 100 B
# One owner each (AGENTS.md): `next` serves these only with --family, which claims the family.
# Matched on the name's own scope, not its parameter types. `plain` is a
# function of a global or non-STL class scope, whatever its arguments.
FAMILIES = (("stlport", re.compile(r"_STL@")),
            ("strings", re.compile(r"^\?(\?[0-9A-Z_]|\w+@)(\?\$StringBase@|\w*(AsciiString|UnicodeString)@)")),
            ("globals", re.compile(r"^\?The[A-Z]\w*@@3")))
PLAIN = re.compile(r"^\?(\?[0-9A-Z_])?\w+@(?!_STL@)(\w+@)?@")
HINTS = {
    "unresolved": "nothing defines it: define the datum once (add_data_match.py), map the import to retail's "
                  "IAT name, or fix the callee's name",
    "duplicates": "two strong definitions: keep the retail-proven one, remove the definition nothing verified needs",
    "losers": "a COMDAT copy that is not retail's body: fix or remove the wrong emitter",
    "wrong_selected": "the link keeps a non-retail definition: fix or remove the wrong emitter ahead of retail's copy",
    "addresses": "hard-coded image addresses: name them (tools/link_debt.py)",
}


def family_of(name):
    return next((family for family, pattern in FAMILIES
                 if pattern.search(name) and not (family == "stlport" and PLAIN.match(name))), "")


def queue_rows(index):
    """The one linking queue: every blocker name that is some unlinked file's
    ONLY blocker, ranked by the bytes those files would link."""
    gain, files = collections.Counter(), collections.defaultdict(list)
    for source, entry in index["blockers"].items():
        if entry["linked"]:
            continue
        names = (set(entry["unresolved"]) | set(entry["duplicates"]) | set(entry["losers"])
                 | set(entry.get("wrong_selected", ())))
        if entry["addresses"]:
            names.add(ADDRESSES)
        if len(names) == 1:
            name = names.pop()
            gain[name] += index["bytes"].get(source, 0)
            files[name].append(source)
    kinds = {}
    for entry in index["blockers"].values():
        for kind in ("unresolved", "duplicates", "losers", "wrong_selected"):
            for name in entry.get(kind, ()):
                kinds.setdefault(name, kind)
    census = index["meta"].get("commit", "")
    return [{"rank": rank, "name": name, "kind": kinds.get(name, "addresses"), "family": family_of(name),
             "bytes_unlocked": count, "files": ";".join(sorted(files[name])),
             "hint": HINTS[kinds.get(name, "addresses")], "census": census}
            for rank, (name, count) in enumerate(sorted(gain.items(), key=lambda kv: (-kv[1], kv[0])), 1)]


def next_names(index, limit):
    """Print the head of the queue (queue_rows)."""
    rows = queue_rows(index)
    print(f"blocker names that are some file's only blocker (census {index['meta'].get('date', '?')} at "
          f"{index['meta'].get('commit', '?')}):")
    print(f"  {'bytes':>9} {'files':>5}  kind        name")
    for row in rows[:limit]:
        family = f"  [family {row['family']}]" if row["family"] else ""
        print(f"  {row['bytes_unlocked']:>9,} {row['files'].count(';') + 1:>5}  {row['kind']:<10}  {row['name']}{family}")
    print(f"  {len(rows):,} names in all, {sum(row['bytes_unlocked'] for row in rows):,} bytes")


def publish(index, path=QUEUE, limit=QUEUE_LIMIT):
    """Write the queue's top `limit` rows as the tracked CSV every host serves from."""
    rows = queue_rows(index)[:limit]
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, QUEUE_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    print(f"link_check: {len(rows)} queue rows, {sum(r['bytes_unlocked'] for r in rows):,} bytes, "
          f"census {index['meta'].get('commit', '?')} -> {path}")


def claim_key(name):
    """The claims.py key for a queue name: refs are keyed by a 32-bit number,
    and 0xF0000000 and up is far past any image RVA, so a name never shares a
    ref with a body."""
    return 0xF0000000 | (zlib.crc32(name.encode("utf-8")) & 0x0FFFFFFF)


def _git(*args, check=False):
    done = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
    if check and done.returncode:
        raise SystemExit(f"link_check next: `git {' '.join(args)}` failed ({done.stderr.strip()}); nothing claimed")
    return done.stdout


def serve(argv):
    """`link_check.py next`: claim and print the best open queue row."""
    import claims
    ap = argparse.ArgumentParser(prog="link_check.py next", description=serve.__doc__)
    ap.add_argument("--family", choices=[family for family, _ in FAMILIES],
                    help="family owner: claim the family and list its open rows")
    ap.add_argument("--no-claim", action="store_true", help="show the pick without claiming it (dry run)")
    ap.add_argument("--queue", default=str(QUEUE))
    args = ap.parse_args(argv)
    with open(args.queue, newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    if not rows:
        print("link_check next: the queue is empty")
        return 1
    census = rows[0]["census"]
    # Freshness fails closed: a queue whose census or origin/master cannot be
    # read is never served, since nothing could say which rows are stale.
    tip = claims._fetch_master()
    if not tip:
        raise SystemExit("link_check next: cannot fetch origin/master; nothing claimed")
    _git("rev-parse", "--verify", "--quiet", f"{census}^{{commit}}", check=True)
    changed = set(_git("diff", "--name-only", census, tip, check=True).split())
    landed = {int(key, 16) for key, _ in claims.LEASE_TRAILER.findall(
        _git("log", "--format=%B", "--grep=^Claim-Lease:", f"{census}..{tip}", check=True))}
    held = claims.active()
    who = claims.owner()
    if args.family:
        key = claim_key(f"family:{args.family}")
        holder = held.get(key, {}).get("owner", who)
        if holder != who:
            print(f"link_check next: family {args.family} is owned by {holder}; leave its names alone")
            return 1
        if not args.no_claim:
            got = claims.claim([key], note=f"link_queue family:{args.family}")
            if not got.claimed:
                print(f"link_check next: could not claim family {args.family}")
                return 1
            print(f"you own family {args.family} (claim 0x{key:08X}, renew by rerunning within 4 h)")
    skipped = collections.Counter()
    shown = 0
    for row in rows:
        key, files = claim_key(row["name"]), row["files"].split(";")
        if row["family"] != (args.family or ""):
            skipped[f"family {row['family']}" if row["family"] else "not in family"] += 1
        elif key in landed:
            skipped["landed since the census"] += 1
        elif changed.intersection(files):
            skipped["file changed since the census"] += 1
        elif not args.family and key in held:
            skipped["claimed"] += 1
        else:
            if args.family:
                print(f"#{row['rank']} {int(row['bytes_unlocked']):,} B {row['kind']} {row['name']}")
                shown += 1
                continue
            lease = ""
            if not args.no_claim:
                got = claims.claim([key], note=f"link_queue {row['name'][:80]}")
                if not got.claimed:
                    skipped["claimed"] += 1
                    continue
                lease = got.leases[key]
            print(f"link queue #{row['rank']} (census {census}): {row['name']}\n"
                  f"  {row['kind']}; unlocks {int(row['bytes_unlocked']):,} B in {len(files)} file(s)\n"
                  f"  fix: {row['hint']}\n  files: {' '.join(files[:8])}{' ...' if len(files) > 8 else ''}")
            if lease:
                print(f"  claimed 0x{key:08X}. Commit-message trailer:  Claim-Lease: 0x{key:08X}={lease}\n"
                      f"  after the push: python3 tools/claims.py release --landed <sha>")
            print(f"  ({', '.join(f'{n} {why}' for why, n in skipped.items()) or 'nothing'} skipped)")
            return 0
    if shown:
        return 0
    print(f"link_check next: no open row in {len(rows)} ({dict(skipped)}); the next census refreshes the queue")
    return 1


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if argv[:1] == ["next"]:
        return serve(argv[1:])
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("paths", nargs="*", help="sources (compiled when stale) or objects; or `next [-h]`")
    ap.add_argument("--next", action="store_true", help="rank blocker names by the bytes their fix alone unlocks")
    ap.add_argument("--limit", type=int, default=30)
    ap.add_argument("--census-only", action="store_true",
                    help="check against the census's definitions of the given files, not their current objects")
    ap.add_argument("--publish", metavar="CSV", nargs="?", const=str(QUEUE),
                    help=f"write the queue's top {QUEUE_LIMIT} rows (default {QUEUE.relative_to(ROOT).as_posix()})")
    args = ap.parse_args(argv)
    if not args.paths and not args.next and not args.publish:
        ap.error("give sources, --next, --publish or `next`")
    started = time.time()
    index = load_index()
    if args.publish:
        publish(index, Path(args.publish))
    if args.next:
        next_names(index, args.limit)
    if not args.paths:
        return 0
    truth = link_census.RetailTruth(link_census.ledger())
    resolved = [resolve(path, index) for path in args.paths]
    if not args.census_only:
        refresh(index, [obj for _, obj in resolved], truth)
    now = source_bytes({source for source, _ in resolved if source})
    clean, before, after = [], 0, 0
    for source, obj in resolved:
        try:
            result = check_object(obj, index, truth, source)
        except link_census.MissingObject as exc:
            print(f"{source or obj.name}: UNKNOWN ({exc})")
            clean.append(False)
            continue
        clean.append(report(source, obj, result, index, now.get(source, 0)))
        entry = index["blockers"].get(source or "", {})
        before += index["bytes"].get(source, 0) if entry.get("linked") else 0
        after += now.get(source, 0) if clean[-1] else 0
    print(f"link_check: {sum(clean)} of {len(clean)} link cleanly; LINKED {before:,} -> {after:,} bytes "
          f"({time.time() - started:.1f}s)")
    return 0 if all(clean) else 1


if __name__ == "__main__":
    sys.exit(main())
