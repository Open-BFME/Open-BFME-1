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
  alias_target  an /alternatename alias A=B the object declares or resolves a
              call through, whose B is not the body at A's pinned address
              (tools/alias_guard.py). A name an alias resolves is not unresolved
  alias_unknown  an alias A=B the object resolves a call through that
              alias_guard cannot judge (no single pinned body for A, or no
              address for B): not counted resolved

It prints the file's LINKED bytes (its own authored + vendored bytes, 0xCC out,
as progress.real_split counts them) at the census and now. The census is the
record: this is a preview, and its answer is only as fresh as the index (a
blocker another file fixed since then still shows). Replayed over every object
of the 3361d5aec5 census it gave the census's verdict for 21,233 of 21,337
files; the other 104 it calls blocked where the census does not, because it
also counts names referenced only from a COMDAT copy link.exe discards.

  python3 tools/link_check.py game/path/File.cpp [...]   # check files
  python3 tools/link_check.py --refresh game/path/File.cpp  # judge against current objects (clean tree)
  python3 tools/link_check.py --compile-limit 300 game/path/File.cpp  # build more definers for a real answer

THE LINKED-CLAIM RULE (2026-10-16, apply_selection_rule). A name a checked
file touches whose definers or ownership changed since the census -- in the
checked file, in any other definer's source or headers, or by objects added
or dropped since -- is judged only on every definer re-read with current
retail truth. A definer that is not built here is compiled (up to
--compile-limit objects, default 50); past that the file says LINKED PREVIEW
UNKNOWN instead of LINKS. A worktree that has built few objects (most worker
worktrees) gets PREVIEW UNKNOWN for such names: raise --compile-limit, or
build first (./build.sh), to get a real answer.
  python3 tools/link_check.py --next [--limit 30]         # names that unlock the most bytes
  python3 tools/link_check.py --publish                   # write targets/game/reverse/link_queue.csv
  python3 tools/link_check.py next [--no-claim]           # serve + claim the top open queue row
  python3 tools/link_check.py near [--max K] [--shared] [--all]  # files that link once calls use the row names
  python3 tools/link_check.py near --packet game/path/File.cpp   # one near file's repair packet
  python3 tools/link_check.py fetch-index                        # the daily workflow's index, for --census-only previews

THE QUEUE. The daily census publishes --next's ranking as link_queue.csv (no
index needed to read it), and `next` serves its best row that is not claimed,
not landed since the census (a Claim-Lease trailer for its key) and that still
has a file neither changed since the census nor linked at a later one (the
tracked link_status.csv, linked_since). Names in a family (FAMILIES) have one
owner each and are served only with `next --family F`. `near` drops the files
a later census saw link and those a re_attempts.log verdict blocked at the
current census (re_log adds census= to link-lane verdicts), and gives each
other file a serve/skip/escalate verdict from its packet.
"""
import argparse
import collections
import csv
import hashlib
import json
import os
import pickle
import re
import subprocess
import sys
import tempfile
import time
import zlib
from collections.abc import Mapping
from pathlib import Path
from types import MappingProxyType
from weakref import WeakKeyDictionary

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census  # noqa: E402

INDEX = link_census.OUT / "link_index.pkl"
COMMON_SCHEMA = 1
WEAK_SCHEMA = 4
ALIAS_SCHEMA = 2  # 2: blockers carry alias_unknown
_WEAK_PREVIEW_TOKEN = object()
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


def write_index(present, facts, blockers, excuses, meta, selection, *, publish=True, aliases=None,
                referenced=None):
    """Called by link_census.write_status: what a per-file check needs from the
    census, in one pickle. `facts` is link_census.read_facts(present);
    `selection` holds link_census.selection_verdicts' results, holder
    exceptions and ledger owners; `aliases` link_census.alias_blockers'
    {alias: [(object index, target)]} (read from the objects when None);
    `referenced` link_census.link_references: `unreferenced` keeps the COMDAT
    names outside it, so a per-file check applies keep_rule's unreferenced
    rule the way the census did (an index without the key judges every name
    as referenced, the rule before 2026-10-25)."""
    index = {"meta": meta, **index_tables(present, facts, selection, aliases), "blockers": blockers,
             "excuses": excuses, "bytes": source_bytes(set(blockers))}
    if referenced is not None:
        index["unreferenced"] = {name for name in index["comdat"] if name not in referenced}
    if publish:
        publish_index(index)
    return index


def publish_index(index):
    link_census.OUT.mkdir(parents=True, exist_ok=True)
    temp = INDEX.with_suffix(".tmp")
    with temp.open("wb") as handle:
        pickle.dump(index, handle, protocol=pickle.HIGHEST_PROTOCOL)
    temp.replace(INDEX)


def selected_receipt_digest(selection):
    """Canonical actual-MAP receipt; incomplete or corrupt provenance is unknown."""
    actual = selection.get("weak_kept")
    addresses, locations = selection.get("weak_addresses"), selection.get("weak_locations")
    ambiguous = selection.get("weak_ambiguous")
    valid = (isinstance(actual, dict) and isinstance(addresses, dict) and isinstance(locations, dict)
             and isinstance(ambiguous, (set, frozenset, list, tuple))
             and all(isinstance(name, str) and isinstance(holder, str) for name, holder in actual.items())
             and set(addresses) == set(locations) == set(actual)
             and all(type(address) is int and 0 <= address <= 0xFFFFFFFF for address in addresses.values())
             and all(isinstance(locations[name], str) and locations[name].split(":")[-1] == holder
                     for name, holder in actual.items())
             and all(isinstance(name, str) and name in actual for name in ambiguous))
    if not valid:
        return None
    payload = {"kept": sorted(actual.items()), "addresses": sorted(addresses.items()),
               "locations": sorted(locations.items()), "ambiguous": sorted(set(ambiguous))}
    return hashlib.sha256(json.dumps(payload, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def index_tables(present, facts, selection, aliases=None):
    """The index's definition tables: every object's exclusive definitions and
    COMDAT copies by name, its /alternatename aliases, and the census's
    selection (holder exceptions, ledger owners)."""
    if len(present) != len(facts):
        raise ValueError("index needs facts for every census object")
    selection = {**selection, "weak_receipt": selected_receipt_digest(selection)}
    strong = collections.defaultdict(list)
    comdat = collections.defaultdict(list)
    common = collections.defaultdict(list)
    common_facts = [fact.common if isinstance(fact, link_census.ObjectFacts) else
                    link_census.common_definitions(obj) for obj, fact in zip(present, facts)]
    for index, (copies, defined, _, _) in enumerate(facts):
        for name in defined:
            strong[name].append(index)
        for name, digest, _, verdict in copies:
            comdat[name].append((index, digest, verdict))
        for name, size in common_facts[index].items():
            common[name].append((index, size))
    if aliases is None:
        import alias_guard
        aliases = collections.defaultdict(list)
        for index, (obj, fact) in enumerate(zip(present, facts)):
            data = getattr(fact, "data", None)
            found = (alias_guard.drectve_aliases(data) if isinstance(data, bytes)
                     else alias_guard.object_aliases(obj))
            for alias, target in found:
                aliases[alias].append((index, target))
    return {"objects": [obj.name for obj in present], "strong": dict(strong), "comdat": dict(comdat),
            "aliases": dict(aliases), "alias_schema": ALIAS_SCHEMA,
            "selection": selection, "common": dict(common), "common_schema": COMMON_SCHEMA,
            "weak_schema": WEAK_SCHEMA, "weak_root": str(ROOT.resolve()),
            "weak_inventory": {obj.name: (str(obj), hashlib.sha256(fact.data).hexdigest())
                               for obj, fact in zip(present, facts) if isinstance(fact, link_census.ObjectFacts)},
            "weak_truth": facts[0].truth if facts and all(isinstance(f, link_census.ObjectFacts) and
                           f.truth == facts[0].truth for f in facts) else None}


def require_common_index(index):
    if type(index) is FrozenPredictionIndex:
        index._tables()  # An exact-type instance must also be factory-issued.
        return
    if index.get("common_schema") != COMMON_SCHEMA or not isinstance(index.get("common"), dict):
        raise SystemExit("link_check: census index lacks complete COMMON providers; rebuild it with "
                         "python3 tools/link_census.py --build --history")


INDEX_WORKFLOW = "link-census.yml"   # .github/workflows: uploads INDEX as the `link-census-index` artifact


def fetch_index():
    """fetch-index: download the last successful daily census's index artifact.
    Objects are not included: previews on this host need --census-only."""
    run = subprocess.run(["gh", "run", "list", "--workflow", INDEX_WORKFLOW, "--status", "success",
                          "--limit", "1", "--json", "databaseId,createdAt"],
                         cwd=ROOT, capture_output=True, text=True)
    if run.returncode:
        raise SystemExit(f"link_check: gh run list failed (gh installed and `gh auth login` done?):\n{run.stderr}")
    runs = json.loads(run.stdout)
    if not runs:
        raise SystemExit(f"link_check: no successful {INDEX_WORKFLOW} run to fetch from")
    INDEX.parent.mkdir(parents=True, exist_ok=True)
    # gh refuses to extract over an existing file. Keep the current index
    # available until its replacement has been downloaded and read.
    with tempfile.TemporaryDirectory(prefix="fetch-", dir=INDEX.parent) as directory:
        download = subprocess.run(["gh", "run", "download", str(runs[0]["databaseId"]), "-n", "link-census-index",
                                   "-D", directory], cwd=ROOT, capture_output=True, text=True)
        staged_index = Path(directory) / INDEX.name
        if download.returncode or not staged_index.is_file():
            raise SystemExit(f"link_check: artifact download failed (expired after 7 days?):\n{download.stderr}")
        with staged_index.open("rb") as handle:
            meta = pickle.load(handle)["meta"]
        staged_index.replace(INDEX)
    print(f"link_check: fetched census index {meta.get('date')} at {meta.get('commit')} "
          f"(workflow run {runs[0]['databaseId']}, {runs[0]['createdAt']}) into {INDEX.relative_to(ROOT).as_posix()}")
    return 0


def load_index():
    if not INDEX.exists():
        common = _git("rev-parse", "--path-format=absolute", "--git-common-dir").strip()
        census = Path(common).parent / "build" / "wt_link" / INDEX.relative_to(ROOT)
        raise SystemExit(
            f"link_check: no census index at {INDEX.relative_to(ROOT).as_posix()} (134 MB, never tracked).\n"
            "  fetch the daily workflow's:  python3 tools/link_check.py fetch-index   (then preview with --census-only)\n"
            f"  or copy a local census's:   mkdir -p build/link_census && cp '{census.as_posix()}' build/link_census/\n"
            "  or build one (~35 min):   python3 tools/link_census.py --build --history\n"
            "  `link_check.py next` needs neither: it reads targets/game/reverse/link_queue.csv")
    with INDEX.open("rb") as handle:
        return pickle.load(handle)


RECEIPTS = "evaluated"  # beside INDEX: one receipt per (row, source) of a checked file (re_log.EVALUATED)


def receipt_name(rva, name, source):
    """A receipt's file: its RVA, then its row's own identity (name and
    source), so rows of two sources at one RVA never share one."""
    return f"0x{rva:08x}-{hashlib.sha1(f'{name}{chr(0)}{source}'.encode('utf-8')).hexdigest()[:16]}.json"


def note_evaluated(rows, census):
    """Record, per ledger row of a file just judged, the census of the index
    that judged it -- read from the loaded index itself, never from a file's
    metadata -- so a re_log verdict on that row carries the census it was
    judged against and the file it was judged in (re_log.evaluated_census).
    Keyed by RVA, row name and source: 385 RVAs have rows in several sources
    (GPT-6.1-Sol, round 3). A re-check of the same file replaces its receipt."""
    rows = list(rows)
    if not census or not rows:
        return
    folder = INDEX.parent / RECEIPTS
    try:
        folder.mkdir(parents=True, exist_ok=True)
        for row in rows:
            note = {"census": census, "name": row["name"], "source": row["source"]}
            path = folder / receipt_name(int(row["target_rva"], 16), row["name"], row["source"])
            temp = path.with_name(f"{path.name}.{os.getpid()}.tmp")
            temp.write_text(json.dumps(note), encoding="utf-8")
            temp.replace(path)
    except (OSError, ValueError):
        pass  # bookkeeping: a verdict without a census is served again, never hidden


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


def weak_context(index, truth=None):
    """Use the refreshed complete definition tables and recorded keeper policy."""
    definers, copies = collections.defaultdict(set), collections.defaultdict(dict)
    objects = index["objects"]
    positions_of = {obj: position for position, obj in enumerate(objects)}
    for name, positions in index["strong"].items():
        if positions:
            definers[name].update(objects[position] for position in positions)
    for name, entries in index["comdat"].items():
        for position, digest, verdict in entries:
            definers[name].add(objects[position])
            copies[name][objects[position]] = (digest, verdict)
    selection = index.get("selection", {})
    exceptions = selection.get("exceptions", {})
    kept = {}
    for name, found in definers.items():
        positions = {positions_of[obj] for obj in found}
        holder = exceptions.get(name, min(positions))
        if holder in positions:
            kept[name] = objects[holder]
    # Keep foreign selected names too: a library/stub primary may be absent
    # from source facts, while a genuine weak alias shares the default's address.
    actual = selection.get("weak_kept")
    addresses, locations = selection.get("weak_addresses"), selection.get("weak_locations")
    ambiguous = selection.get("weak_ambiguous")
    receipt = selected_receipt_digest(selection)
    actual_valid = receipt is not None and receipt == selection.get("weak_receipt")
    if actual_valid:
        kept = link_census.SelectedDefinitions(actual)
        kept.addresses, kept.locations, kept.ambiguous = addresses, locations, ambiguous
    context = link_census.weak_selection_context(
        definers, copies, selection.get("owners", {}), kept,
        {name for name, entries in index["common"].items() if entries})
    fingerprint = link_census.truth_fingerprint(truth)
    # An old or partly refreshed context cannot prove absence of a primary or
    # competing default elsewhere. Require the complete frozen selected input set.
    inventory = index.get("weak_inventory", {})
    complete = (actual_valid and fingerprint and getattr(truth, "_weak_inputs", None) == link_census.truth_inputs_fingerprint()
                and index.get("weak_schema") == WEAK_SCHEMA and
                index.get("weak_root") == str(ROOT.resolve()) and
                index.get("weak_truth") == fingerprint and isinstance(inventory, dict) and
                len(set(objects)) == len(objects) and set(inventory) == set(objects))
    if complete:
        for holder, entry in inventory.items():
            if not isinstance(entry, (tuple, list)) or len(entry) != 2 or not all(isinstance(v, str) for v in entry):
                complete = False
                break
            path, digest = entry
            try:
                owned_path = Path(path).resolve()
                if owned_path.name != holder or not owned_path.is_relative_to(ROOT.resolve()):
                    complete = False
                    break
                if hashlib.sha256(_object_bytes(owned_path)).hexdigest() != digest:
                    complete = False
                    break
            except (link_census.MissingObject, OSError, RuntimeError):
                complete = False
                break
    if not complete:
        context["defaults"] = {}
        return context
    current = index.get("_weak_current_objects", {}) if index.get("_weak_token") is _WEAK_PREVIEW_TOKEN else {}
    valid = {}
    for holder, proof in current.items():
        if not isinstance(proof, (tuple, list)) or len(proof) != 5 or not isinstance(proof[4], dict):
            continue
        if (fingerprint and proof[0] == fingerprint and proof[2] == link_census.policy_fingerprint(fresh=True)
                and Path(str(proof[3])).resolve() == Path(inventory.get(holder, ("", ""))[0]).resolve()
                and hashlib.sha256(_object_bytes(proof[3])).hexdigest() == proof[1]):
            valid[holder] = proof[4]
    context["defaults"] = {name: proof for name, proof in context["defaults"].items()
                           if valid.get(proof[0], {}).get(name) == proof[1]}
    return context


def _object_bytes(obj):
    try:
        return obj.read_bytes()
    except OSError as exc:
        raise link_census.MissingObject(f"{obj}: cannot read object ({exc})") from exc


# --refresh compiles at most this many stale or missing objects unless
# --refresh-compile says so: a worktree without a warm build has ~22,000 of
# them (about 3 h under build.py's host-wide compile lock).
REFRESH_COMPILE_LIMIT = 50
# --refresh's own compile-input proofs (census_receipts), kept across runs.
# The ~500 TUs whose include roots no normal build cache can vouch for
# (macro includes, the checkout root) are current only with such a proof;
# the census keeps its own in build/link_census/compile_inputs.json.
REFRESH_RECEIPTS = link_census.OUT / "refresh_inputs.json"
REFRESH_RUN = "link_check-refresh"


def repo_path(path, base=None):
    """A path as git status prints it: repo-root relative, posix. A relative
    path is relative to `base`, default ROOT (a build sidecar's keys; round 4
    N3: never the current directory). Callers holding a command-line argument
    pass base=Path.cwd()."""
    path = Path(path)
    if not path.is_absolute():
        path = Path(base if base is not None else ROOT) / path
    try:
        return path.resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        return Path(path).as_posix()


def refresh_dirty(paths):
    """Paths under game/ or inputs/reference/ that differ from HEAD (staged,
    unstaged or untracked), other than the files being checked: the objects
    a refreshed index reads must be one commit's, not a mix. The ledgers
    (targets/game/reverse/) are not checked: add_match and re_log edit them
    between a before and an after preview, and the index reads them as they
    are."""
    paths = {repo_path(p, Path.cwd()) for p in paths}
    out = _git("status", "--porcelain=v1", "-z", "--untracked-files=all", "--",
               "game", "inputs/reference", check=True)
    dirty, entries = [], out.split("\0")
    i = 0
    while i < len(entries):
        entry = entries[i]
        i += 1
        if len(entry) < 4:
            continue
        status, path = entry[:2], entry[3:]
        if "R" in status or "C" in status:
            i += 1                      # -z: a rename's or copy's source path follows
        if path not in paths:
            dirty.append(path)
    return sorted(dirty)


def kept_definition(index, name):
    """(object, body) the link keeps for `name` by the index's tables: the
    census /MAP holder while it still defines the name, else the first definer
    in link order; body is "strong" or the COMDAT digest. None: no definer."""
    copies = {i: digest for i, digest, _ in index["comdat"].get(name, ())}
    exclusive = set(index["strong"].get(name, ()))
    definers = set(copies) | exclusive
    if not definers:
        return None
    exceptions = index.get("selection", {}).get("exceptions", {})
    holder = exceptions.get(name, min(definers))
    if holder is None or holder not in definers:
        holder = min(definers)
    return index["objects"][holder], "strong" if holder in exclusive else copies[holder]


def kept_verdict(index, name):
    """The retail-truth verdict of the COMDAT copy the link keeps ("strong"
    for an exclusive definition, None when nothing defines it)."""
    kept = kept_definition(index, name)
    if kept is None:
        return None
    holder, body = kept
    if body == "strong":
        return "strong"
    position = index["objects"].index(holder)
    return next((v for i, _, v in index["comdat"].get(name, ()) if i == position), None)


def definer_signature(objects, strong, comdat, name):
    """Who defines `name`, how, and with which body: (object, kind[, digest])."""
    entries = [(objects[i], "strong") for i in strong.get(name, ())]
    entries += [(objects[i], "comdat", digest) for i, digest, _ in comdat.get(name, ())]
    return sorted(entries)


def changed_definers(old, new):
    """Names whose definers (object, kind, body digest) differ between the
    census index `old` and the refreshed tables `new`."""
    names = set(old["strong"]) | set(old["comdat"]) | set(new["strong"]) | set(new["comdat"])
    return {name for name in names
            if definer_signature(old["objects"], old["strong"], old["comdat"], name)
            != definer_signature(new["objects"], new["strong"], new["comdat"], name)}


def census_kept(selection):
    """The census's actual /MAP holders (link_census.SelectedDefinitions), or
    None when its receipt does not verify."""
    receipt = selected_receipt_digest(selection)
    if receipt is None or receipt != selection.get("weak_receipt"):
        return None
    kept = link_census.SelectedDefinitions(selection["weak_kept"])
    kept.addresses, kept.locations = selection["weak_addresses"], selection["weak_locations"]
    kept.ambiguous = set(selection["weak_ambiguous"])
    return kept


def drop_definitions(index, names):
    """Remove every definition the census recorded for objects `names` (no
    longer in the current ledger, so no longer linked). Their positions stay,
    empty, so no other position moves."""
    positions = {index["objects"].index(name) for name in names if name in index["objects"]}
    if not positions:
        return
    for table in ("strong", "comdat", "common"):
        for symbol, entries in list(index.get(table, {}).items()):
            kept = [e for e in entries if (e if isinstance(e, int) else e[0]) not in positions]
            if kept != entries:
                index[table][symbol] = kept


def _refresh_receipts():
    import census_receipts
    return (census_receipts.Receipts.load(REFRESH_RECEIPTS, REFRESH_RUN)
            or census_receipts.Receipts(REFRESH_RECEIPTS, run=REFRESH_RUN))


def _object_is_current(obj, sources, receipts):
    """The object exists and matches its source: the build cache's proof, or
    a compile-input receipt (TUs whose include roots no cache can vouch for)."""
    if not obj.exists():
        return False
    source = sources.get(obj)
    if source is None:
        return True                       # no ledger source to be stale against (e.g. a .lib member)
    return link_census.object_current(source, obj) or bool(receipts and receipts.current(source, obj))


class Changed(set):
    """Repo paths changed since the census; `.added` holds the new ones and
    `.removed` the deleted ones (both may shadow or unshadow a same-name
    header); `.tracked` every path git tracks now (None: ask git)."""
    added = frozenset()
    removed = frozenset()
    tracked = None


_TRACKED = None


def tracked_files():
    """Every path git tracks in this checkout (memoised)."""
    global _TRACKED
    if _TRACKED is None:
        listed = subprocess.run(["git", "ls-files", "-z"], cwd=ROOT, capture_output=True, text=True)
        _TRACKED = frozenset(p for p in listed.stdout.split("\0") if p) if listed.returncode == 0 else frozenset()
    return _TRACKED


def changed_since(commit):
    """Repo paths that differ between `commit` and the working tree (committed,
    staged, unstaged; renames as a deletion plus an addition) plus untracked
    files; `.added` lists the added and untracked ones (a new header may
    shadow an old one). None when `commit` cannot be read."""
    if not commit:
        return None
    diff = subprocess.run(["git", "diff", "--name-status", "--no-renames", "-z", commit, "--"], cwd=ROOT,
                          capture_output=True, text=True)
    untracked = subprocess.run(["git", "ls-files", "-z", "--others", "--exclude-standard"], cwd=ROOT,
                               capture_output=True, text=True)
    if diff.returncode or untracked.returncode:
        return None
    fields = diff.stdout.split("\0")
    changed, added, removed = Changed(), set(), set()
    for status, path in zip(fields[0::2], fields[1::2]):
        if path:
            changed.add(path)
            if status.startswith("A"):
                added.add(path)
            elif status.startswith("D"):
                removed.add(path)
    new = {path for path in untracked.stdout.split("\0") if path}
    changed |= new
    changed.added = frozenset(added | new)
    changed.removed = frozenset(removed)
    changed.tracked = tracked_files()
    return changed


_SHA256 = {}


def _sha256(path):
    try:
        stat = os.stat(path)
        key = (str(path), stat.st_size, stat.st_mtime_ns)
        if key not in _SHA256:
            _SHA256[key] = hashlib.sha256(Path(path).read_bytes()).hexdigest()
        return _SHA256[key]
    except OSError:
        return None


def _current_command(source, obj):
    try:
        return list(build.compiler_command(Path(source), Path(obj))[0])
    except (Exception, SystemExit):  # noqa: BLE001
        return None


def _current_fingerprint(source, obj):
    """The sidecar `cmd` today's build.py would record (round 5 F1: a sidecar
    built with another command is not this tree's build)."""
    try:
        return build._cmd_fingerprint(*build.compiler_command(Path(source), Path(obj)))
    except (Exception, SystemExit):  # noqa: BLE001
        return None


def object_inputs(obj, sources, receipts):
    """Repo paths an object was compiled from: its source plus the headers its
    build sidecar (.deps.json) or compile-input receipt records -- only when
    every recorded file still has the digest that build read, so the list is
    this tree's, not a stale build's (round 4 N2). None otherwise, or when
    the object or both records are missing. Digests are memoised per file, so
    a whole-ledger scan reads each shared header once (no compiler runs)."""
    if not Path(obj).exists():
        return None
    source = sources.get(obj)
    try:
        recorded = json.loads(build._deps_sidecar(obj).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        recorded = None
    if isinstance(recorded, dict):
        deps = recorded.get("deps")
        if isinstance(deps, str):
            import ast
            try:
                deps = ast.literal_eval(deps)
            except (ValueError, SyntaxError):
                deps = None
        if (isinstance(deps, dict) and source is not None
                and recorded.get("cmd") is not None and recorded.get("cmd") == _current_fingerprint(source, obj)
                and recorded.get("source") == build._hash_file(str(source))
                and all(build._hash_file(str(ROOT / path if not Path(path).is_absolute() else path)) == md5
                        for path, md5 in deps.items())):
            return {repo_path(source, ROOT)} | {repo_path(path, ROOT) for path in deps}
    entry = getattr(receipts, "entries", {}).get(str(Path(obj).resolve())) if receipts else None
    files = (entry or {}).get("input", {}).get("files") if isinstance((entry or {}).get("input"), dict) else None
    if (isinstance(files, dict) and source is not None and entry.get("command") is not None
            and entry.get("command") == _current_command(source, obj)
            and all(_sha256(path) == sha for path, sha in files.items())):
        inputs = {repo_path(path, ROOT) for path in files}
        return inputs | ({repo_path(source, ROOT)} if source is not None else set())
    return None


def inputs_moved(inputs, since):
    """Did any input change since the census? Also counts as moved: a header
    added or deleted since whose file name matches an input (shadowing either
    way; round 5 F2), and an input git cannot vouch for -- ignored, or
    outside this checkout (round 5 F3). Undeterminable (None) counts too."""
    if inputs is None or since is None:
        return True
    if inputs & since:
        return True
    tracked = getattr(since, "tracked", None)
    tracked = tracked_files() if tracked is None else tracked
    if any(path not in tracked and path not in since for path in inputs):
        return True
    names = {Path(path).name.lower() for path in (*getattr(since, "added", ()), *getattr(since, "removed", ()))}
    return bool(names and any(Path(path).name.lower() in names for path in inputs))


def portable_command(module, source, obj):
    """A host-portable fingerprint of the compile command `module` (a
    tools/build.py) gives `source`: no wine path, no drive map."""
    command, env = module.compiler_command(Path(source), Path(obj))
    if os.name != "nt":
        command = command[1:]               # the host's wine binary
    payload = [[module._portable(str(part)) for part in command], module._portable(env.get("INCLUDE", ""))]
    return hashlib.md5(json.dumps(payload).encode()).hexdigest()


def command_moves(commit, sources):
    """Objects whose compile command differs between the census commit's
    tools/build.py and the current one (a base flag, a -D, an include root;
    round 5 F1). None when that cannot be computed (then nothing is known)."""
    import types
    shown = subprocess.run(["git", "show", f"{commit}:tools/build.py"], cwd=ROOT, capture_output=True, text=True)
    if shown.returncode:
        return None
    census_build = types.ModuleType("build_at_census")
    census_build.__file__ = str(ROOT / "tools" / "build.py")
    try:
        exec(compile(shown.stdout, census_build.__file__, "exec"), census_build.__dict__)
        return {Path(obj).name for obj, source in sources.items()
                if Path(source).suffix.lower() in (".c", ".cpp", ".asm")
                and portable_command(census_build, source, obj) != portable_command(build, source, obj)}
    except (Exception, SystemExit):  # noqa: BLE001 -- unknown means unknown, never "unchanged"
        return None


# Truth inputs (link_census.RetailTruth, alias/route verdicts): which column
# names a row, which holds its address, and that address's space.
TRUTH_LAYOUT = {
    "targets/game/reverse/functions.csv": (0, 2, "rva"),
    "targets/game/reverse/symbols.csv": (0, 1, "rva"),
    "targets/game/reverse/reloc_names.csv": (0, 1, "rva"),
    "targets/game/reverse/data_rows.csv": (0, 1, "va"),
    "targets/game/reverse/dir32_addresses.csv": (0, 1, "va"),
    "targets/game/reverse/ghidra_functions.csv": (None, 0, "rva"),      # route_verdict boundaries
    "targets/game/reverse/derived_boundaries.csv": (None, 0, "rva"),
}
TRUTH_FILES = tuple(TRUTH_LAYOUT)
_OBJECT_SYMBOL = re.compile(r"object-symbol=([^;,\s\"]+)")
_ANON = re.compile(r"\?A0x[0-9a-fA-F]{8}@")


def _anon(text):
    """Anonymous-namespace hashes (?A0x1234abcd@) differ between compiles of
    one name; compare names and rows without them."""
    return _ANON.sub("?A0x@", text)


def _truth_rows(text, layout=(0, None, None)):
    """({name: tuple of the lines naming it, in file order},
    {(space, address): set of lines}) for one truth file's text. A row names
    its name column and any object-symbol= note; anonymous-namespace hashes
    are normalised. Per name the ORDER counts: link_census.pins() takes a
    name's first pin and first route= (round 9), so swapping two pin lines
    moves its truth. An RVA-space address spelled as a VA (>= the 0x400000
    image base) is read as its RVA, as RetailTruth reads it."""
    name_col, address_col, space = layout
    by_name, by_address = collections.defaultdict(list), collections.defaultdict(set)
    for line in text.splitlines()[1:]:
        line = _anon(line.rstrip("\r"))
        if not line:
            continue
        fields = next(csv.reader([line]), [])
        if name_col is not None and len(fields) > name_col:
            for key in {fields[name_col], *_OBJECT_SYMBOL.findall(line)}:
                if key:
                    by_name[key].append(line)
        if address_col is not None and len(fields) > address_col:
            try:
                address = int(fields[address_col], 16)
            except ValueError:
                continue
            if space == "rva" and address >= 0x400000:
                address -= 0x400000
            by_address[(space, address)].add(line)
    return {name: tuple(lines) for name, lines in by_name.items()}, by_address


class AllNames(frozenset):
    """Every name: the census ledger could not be read."""
    def __contains__(self, item):
        return True

    def __and__(self, other):
        return set(other)

    __rand__ = __and__


def truth_changes(commit, since, names=None):
    """Names whose retail truth may have moved since the census commit:
    (1) a row naming them differs in a truth file (functions.csv, symbols.csv
        pins, reloc_names.csv, data_rows.csv, dir32_addresses.csv; name
        column and object-symbol= notes; anonymous-namespace hashes
        normalised) -- a row re-homed in its own source, a new pin;
    (2) any row was added or removed at an ADDRESS one of their rows holds,
        then or now, in any truth file, including the boundary files
        ghidra_functions.csv and derived_boundaries.csv: retiring a
        co-claimant turns a shared "unknown" into "wrong" (round 8 HIGH 2).
    Restricted to `names` when given; names=None gives the full set.
    AllNames() when a truth file the census had cannot be read."""
    touched = [path for path in TRUTH_FILES if since is None or path in since]
    if not touched:
        return set()
    if not commit:
        return set(names) if names is not None else AllNames()
    key = (str(ROOT), commit, tuple(touched))
    if key not in _TRUTH_MEMO:
        _TRUTH_MEMO[key] = _truth_diff(commit, touched)
    changed_names = _TRUTH_MEMO[key]
    if isinstance(changed_names, AllNames):
        return set(names) if names is not None else changed_names
    if names is None:
        return changed_names
    return {name for name in names if _anon(name) in changed_names}


_TRUTH_MEMO = {}


def _truth_diff(commit, touched):
    """truth_changes' full answer for the truth files in `touched`."""
    changed_names, changed_addresses = set(), set()
    for path in touched:
        shown = subprocess.run(["git", "show", f"{commit}:{path}"], cwd=ROOT, capture_output=True, text=True)
        try:
            now_text = (ROOT / path).read_text(encoding="utf-8")
        except OSError:
            now_text = None
        if shown.returncode or now_text is None:
            if (ROOT / path).exists() or shown.returncode == 0:
                return AllNames()
            continue                    # absent then and now
        old_names, old_addresses = _truth_rows(shown.stdout, TRUTH_LAYOUT[path])
        new_names, new_addresses = _truth_rows(now_text, TRUTH_LAYOUT[path])
        changed_names |= {n for n in set(old_names) | set(new_names) if old_names.get(n) != new_names.get(n)}
        changed_addresses |= {a for a in set(old_addresses) | set(new_addresses)
                              if old_addresses.get(a) != new_addresses.get(a)}
    if changed_addresses:
        # every name with a row at a changed address, then or now
        for path, (name_col, address_col, space) in TRUTH_LAYOUT.items():
            if name_col is None:
                continue
            texts = []
            shown = subprocess.run(["git", "show", f"{commit}:{path}"], cwd=ROOT, capture_output=True, text=True)
            if shown.returncode == 0:
                texts.append(shown.stdout)
            try:
                texts.append((ROOT / path).read_text(encoding="utf-8"))
            except OSError:
                pass
            for text in texts:
                _, by_address = _truth_rows(text, TRUTH_LAYOUT[path])
                for address in changed_addresses & set(by_address):
                    for line in by_address[address]:
                        fields = next(csv.reader([line]), [])
                        changed_names.update(k for k in {fields[name_col] if len(fields) > name_col else "",
                                                         *_OBJECT_SYMBOL.findall(line)} if k)
    return changed_names


MOVED_CACHE = link_census.OUT / "moved_cache.json"


def _scan_key(commit, since):
    """What the moved-object scan depends on: census commit, HEAD, the content
    of every file changed since the census, and tools/build.py."""
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True).stdout.strip()
    digest = hashlib.sha256()
    for path in sorted(since or ()):
        digest.update(path.encode() + b"\0" + (_sha256(ROOT / path) or "-").encode() + b"\0")
    ledger = ROOT / "targets" / "game" / "reverse"
    return json.dumps([commit, head, digest.hexdigest(), _sha256(ROOT / "tools" / "build.py"),
                       _sha256(ledger / "functions.csv"), _sha256(ledger / "data_rows.csv")])


def reorder_to_ledger(index, order):
    """Renumber the index to the CURRENT ledger's link order (round 4 N5: a
    new lower-RVA row moves an object), objects new since the census in their
    places with no definitions yet, then census objects the ledger no longer
    links at the end with their definitions removed (N6: they no longer
    resolve anything). Returns the dropped object names."""
    old = index["objects"]
    current = list(dict.fromkeys(order))
    known = set(current)
    gone = [name for name in old if name not in known]
    objects = current + gone
    position = {name: i for i, name in enumerate(objects)}
    shift = {i: position[name] for i, name in enumerate(old)}
    dropped = {position[name] for name in gone}
    index["objects"] = objects
    index["strong"] = {name: [shift[i] for i in found if shift[i] not in dropped]
                       for name, found in index["strong"].items()}
    for table in ("comdat", "common", "aliases"):
        if table in index:
            index[table] = {name: [(shift[e[0]], *e[1:]) for e in entries if shift[e[0]] not in dropped]
                            for name, entries in index[table].items()}
    selection = index.get("selection")
    if selection and "exceptions" in selection:
        index["selection"] = {**selection, "exceptions": {
            name: None if holder is None else shift[holder]
            for name, holder in selection["exceptions"].items()
            if holder is None or shift[holder] not in dropped}}
    return gone


def _moved_objects(commit, since, order, ledger_objects, census_objects, sources, receipts):
    """({object names new or changed since the census}, unknown?). Cached in
    MOVED_CACHE under _scan_key; a tools/build.py change since the census
    adds every object whose compile command changed (command_moves); if that
    cannot be computed the answer is unknown (every touched name UNKNOWN)."""
    key = _scan_key(commit, since) if since is not None else None
    if key is not None:
        try:
            cached = json.loads(MOVED_CACHE.read_text(encoding="utf-8"))
            if cached.get("key") == key:
                return set(cached["moved"]), bool(cached["unknown"])
        except (OSError, ValueError, KeyError, TypeError):
            pass
    moved = {name for name in order if name in ledger_objects
             and (name not in census_objects
                  or inputs_moved(object_inputs(ledger_objects[name], sources, receipts), since))}
    unknown = False
    if since is None or "tools/build.py" in since:
        by_command = command_moves(commit, sources) if commit else None
        if by_command is None:
            unknown = True
        else:
            moved |= by_command
    if key is not None:
        try:
            MOVED_CACHE.parent.mkdir(parents=True, exist_ok=True)
            MOVED_CACHE.write_text(json.dumps({"key": key, "moved": sorted(moved), "unknown": unknown}))
        except OSError:
            pass
    return moved, unknown


HOOK_DEADLINE = 120.0


HOOK_INPUTS = ("game", "inputs", "tools", "build.sh", "build.cmd", "targets/game/reverse",
               ":(exclude)targets/game/reverse/re_attempts.log", ":(exclude)targets/game/reverse/attempts")
_REPORTED = set()          # files report() has printed a verdict for (hook timeout must not contradict them)
import threading as _threading  # noqa: E402
_REPORT_LOCK = _threading.RLock()  # report() and the hook's timeout print one at a time


def _kill_children(pid=None):
    """Kill every descendant process (a wine cl.exe still compiling)."""
    if os.name == "nt":
        return
    pid = os.getpid() if pid is None else pid
    listed = subprocess.run(["ps", "-o", "pid=", "--ppid", str(pid)], capture_output=True, text=True)
    for child in listed.stdout.split():
        try:
            _kill_children(int(child))
            os.kill(int(child), 9)
        except (ValueError, OSError):
            pass


def hook_unstaged():
    """Paths whose working-tree state differs from the index and can change a
    preview: tracked edits under game/, inputs/, tools/, build scripts and the
    three truth ledgers, and untracked files under game/ and inputs/ (a new
    header can shadow one)."""
    edited = [p for p in _git("diff", "--name-only", "-z", "--", *HOOK_INPUTS).split("\0") if p]
    untracked = [p for p in _git("ls-files", "-z", "--others", "--exclude-standard", "--",
                                 "game", "inputs").split("\0") if p]
    return edited + untracked


def hook_main(args):
    """--hook: the shared LINKED-claim rule under hook settings. Report only:
    exit 0 whatever happens. Compiles the checked files when their objects
    are stale (build.py's normal compile, which takes the host build lock),
    but never a definer (compile_limit 0 unless --compile-limit says
    otherwise). The staged state is what a commit records, so any unstaged
    or untracked path that can change the answer (hook_unstaged) makes every
    file UNKNOWN; so does any error. Past the deadline the files with no
    verdict yet are UNKNOWN (timeout) and running compiles are killed. Never
    LINKS on a guess, never a positive LINKED delta it did not prove."""
    import threading
    paths = list(args.paths)
    deadline = HOOK_DEADLINE if args.deadline is None else args.deadline

    def unknown(why, only=None):
        for path in (only if only is not None else paths):
            print(f"{path}: LINKED PREVIEW UNKNOWN ({why})", flush=True)

    def give_up():
        try:
            _REPORT_LOCK.acquire()        # no verdict starts printing after this
            _kill_children()
            pending = [p for p in paths if repo_path(p, Path.cwd()) not in _REPORTED]
            unknown(f"timeout after {deadline:.0f}s", pending)
        finally:
            sys.stdout.flush()
            os._exit(0)
    timer = threading.Timer(deadline, give_up)
    timer.daemon = True
    try:
        if args.census_only:
            unknown("--census-only is refused under --hook: it ignores the staged objects")
            return 0
        unstaged = hook_unstaged()
        if unstaged:
            unknown(f"unstaged or untracked inputs differ from the staged state, e.g. {unstaged[0]}")
            return 0
        timer.start()
        forwarded = [*paths, "--compile-limit", str(0 if args.compile_limit is None else args.compile_limit)]
        main(forwarded, hook=True)
    except BaseException as error:  # noqa: BLE001 -- a report-only hook never fails the commit
        if isinstance(error, KeyboardInterrupt):
            raise
        pending = [p for p in paths if repo_path(p, Path.cwd()) not in _REPORTED]
        unknown(f"{type(error).__name__}: {str(error)[:200]}", pending)
    finally:
        timer.cancel()
    return 0


def apply_selection_rule(index, objects, truth, rows=None, *, compile_limit=None):
    """THE LINKED-CLAIM RULE (project lead, 2026-10-16), shared by every
    LINKED preview (link_check files, the pre-commit report).

    1. The index is renumbered to the CURRENT ledger's link order: objects
       new since the census take their places, objects that moved move, and
       census objects the ledger no longer links lose their definitions.
    2. Every ledger object that is new since the census, or whose recorded
       inputs (source and headers, or a header added since that could shadow
       one) changed since the census commit -- or cannot be determined here
       -- is re-read, compiling within the budget (`compile_limit` objects in
       total, default REFRESH_COMPILE_LIMIT; 0: never). If any of them cannot
       be read, any name may be defined differently there:
       selection["unknown_definers"] makes every touched name LINKED PREVIEW
       UNKNOWN unless proven wrong.
    3. The checked `objects` are refreshed. A name they touch is CHANGED when
       its definers (object, kind, body digest), its ledger ownership or the
       definition the link keeps differ from the census's.
    4. For every changed name every remaining definer is re-read with current
       retail truth (budget again), else the name is STALE; a changed name
       with a census /MAP holder exception is stale too.

    wrong_selected/check_object report a changed name whose kept definition
    is wrong as `selected`; a stale or still-unprovable changed name as
    LINKED PREVIEW UNKNOWN unless the link keeps the very body the census
    saw it keep; unchanged names keep the census verdict. Returns
    (changed, stale)."""
    rows = (link_census.ledger() if rows is None else rows) or []
    budget = [REFRESH_COMPILE_LIMIT if compile_limit is None else compile_limit]
    index.setdefault("selection", {"exceptions": {}, "owners": {}})
    present, missing = link_census.objects(rows)
    ledger_objects = {obj.name: obj for obj in list(present) + list(missing)}
    order = [obj.name for obj in link_census.link_order(rows, link_census.data_ledger())]
    sources = link_census._object_sources(rows)
    receipts = _refresh_receipts()
    checked = {obj.name for obj in objects}
    census_view = {"objects": list(index["objects"]), "strong": index["strong"], "comdat": index["comdat"],
                   "selection": index["selection"]}
    census_objects = set(index["objects"])

    def readable(objs):
        """(current, not) after compiling what the shared budget allows."""
        ok = [obj for obj in objs if _object_is_current(obj, sources, receipts)]
        behind = [obj for obj in objs if obj not in ok]
        if behind and len(behind) <= budget[0]:
            budget[0] -= len(behind)
            need = sorted({sources[obj] for obj in behind if obj in sources})
            try:
                outputs = build.compile_rows(rows, need, input_proof=receipts)
                link_census._refresh_missing_search_root_receipts(rows, outputs, receipts)
            except SystemExit as error:
                print(f"link_check: compile stopped ({error})", file=sys.stderr)
            receipts.save()
            ok += [obj for obj in behind if _object_is_current(obj, sources, receipts)]
            behind = [obj for obj in behind if obj not in ok]
        return ok, behind

    # what the census had the checked objects define, and every name they touch
    facts = {obj.name: link_census.object_facts(obj, truth) for obj in objects}
    touched = set()
    for obj in objects:
        touched |= link_census.touched_names(facts[obj.name])
        if obj.name in census_view["objects"]:
            position = census_view["objects"].index(obj.name)
            touched |= {n for n, at in census_view["strong"].items() if position in at}
            touched |= {n for n, at in census_view["comdat"].items() if any(i == position for i, _, _ in at)}
    before = {name: definer_signature(census_view["objects"], census_view["strong"], census_view["comdat"], name)
              for name in touched}
    census_kept = {name: kept_definition(census_view, name) for name in touched}
    census_verdict = {name: kept_verdict(census_view, name) for name in touched}
    # 1. current link order (N5, N6, N7)
    if order:                     # no ledger at all (a bare fixture): keep the census's order
        extra = [obj.name for obj in objects if obj.name not in set(order)]
        reorder_to_ledger(index, order + extra)
    # 2. objects new or changed since the census (F3, N1)
    commit = index.get("meta", {}).get("commit")
    since = changed_since(commit)
    moved_names, scan_unknown = _moved_objects(commit, since, order, ledger_objects, census_objects, sources,
                                               receipts)
    moved = [ledger_objects[name] for name in order
             if name not in checked and name in ledger_objects and name in moved_names]
    moved_ok, moved_unreadable = readable(moved)
    refresh(index, list(objects) + moved_ok, truth)
    selection = index["selection"]
    # 3. what changed
    owners_now = link_census.ledger_owners(rows)
    census_owners = selection.get("owners", {})
    changed = {name for name in touched
               if definer_signature(index["objects"], index["strong"], index["comdat"], name) != before[name]
               or set(census_owners.get(name, ())) != set(owners_now.get(name, ()))
               or kept_definition(index, name) != census_kept[name]}
    truth_moved = truth_changes(commit, since, touched)    # retail truth moved without any object
    # One step away (round 7 H1): a shared copy's verdict depends on the names
    # its body references (a call's target row, a pin, a dir32 entry). Without
    # per-copy reference lists, a truth change to any name the checked objects
    # or the kept copies' objects reference changes every touched shared name.
    # every touched name whose kept copy lies outside the checked objects,
    # whatever its definer count (a /Gy single copy is judged too), and every
    # shared one (round 8 HIGH 1)
    shared = {name for name in touched
              if len(definer_signature(index["objects"], index["strong"], index["comdat"], name)) > 1
              or (kept_definition(index, name) or (None,))[0] not in checked | {None}}
    if shared and truth_moved is not None:
        all_moved = truth_changes(commit, since, None)
        if all_moved:
            referenced = set()
            for obj in objects:
                referenced |= {_anon(n) for n in link_census.touched_names(facts[obj.name])}
            holders = {kept_definition(index, name)[0] for name in shared if kept_definition(index, name)}
            unread = False
            for holder in holders - checked:
                obj = ledger_objects.get(holder)
                if obj is None or not _object_is_current(obj, sources, receipts):
                    unread = True
                    continue
                referenced |= {_anon(n) for n in link_census.touched_names(link_census.object_facts(obj, truth))}
            if unread or isinstance(all_moved, AllNames) or (referenced & {_anon(n) for n in all_moved}):
                truth_moved = set(truth_moved) | shared
    changed |= truth_moved
    owners = dict(census_owners)
    owners.update({name: set(owners_now.get(name, ())) for name in changed})
    selection["owners"] = owners
    # 4. every remaining definer of every changed name, with current truth
    done = checked | {obj.name for obj in moved_ok}
    definers = collections.defaultdict(set)       # object name -> changed names it defines
    for name in changed:
        for i in index["strong"].get(name, ()):
            definers[index["objects"][i]].add(name)
        for i, _, _ in index["comdat"].get(name, ()):
            definers[index["objects"][i]].add(name)
    for name in done:
        definers.pop(name, None)
    ok, behind = readable([ledger_objects[name] for name in definers if name in ledger_objects])
    stale = set()
    for obj in behind:
        stale |= definers[obj.name]
    refresh(index, ok, truth)
    stale |= {name for name in changed if name in census_view["selection"].get("exceptions", {})}   # F4
    selection = index["selection"]
    selection["changed"], selection["stale"] = changed, stale
    selection["census_kept"] = {name: census_kept.get(name) for name in changed - truth_moved}
    selection["truth_moved"] = set(truth_moved)
    selection["census_verdict"] = {name: census_verdict.get(name) for name in truth_moved}
    selection["unknown_definers"] = bool(moved_unreadable) or scan_unknown
    if moved_unreadable:
        print(f"link_check: {len(moved_unreadable):,} ledger object(s) new or changed since the census cannot "
              f"be read here (e.g. {moved_unreadable[0].name}); any name may be defined there", file=sys.stderr)
    return changed, stale


def current_selection(old, objects, facts, owners):
    """The census's /MAP holder exceptions remapped to the current object
    order, kept only while a name's definers (object, kind, body digest) are
    what the census measured; every other exception name is `unmeasured`.
    (Open-BFME-2 link_check.current_selection.)"""
    signature = definer_signature
    strong, comdat = collections.defaultdict(list), collections.defaultdict(list)
    for i, (copies, defined, _, _) in enumerate(facts):
        for name in defined:
            strong[name].append(i)
        for name, digest, _, verdict in copies:
            comdat[name].append((i, digest, verdict))
    positions = {name: i for i, name in enumerate(objects)}
    exceptions, unmeasured = {}, set()
    for name, holder in old["selection"].get("exceptions", {}).items():
        if (old["strong"].get(name) or strong.get(name)
                or signature(old["objects"], old["strong"], old["comdat"], name)
                != signature(objects, strong, comdat, name)):
            unmeasured.add(name)
        else:
            exceptions[name] = None if holder is None else positions[old["objects"][holder]]
    selection = {**old["selection"], "exceptions": exceptions, "owners": dict(owners), "unmeasured": unmeasured}
    return selection


def refresh_current(index, checked=(), allow_compile=False):
    """--refresh: replace the census's definition tables with the CURRENT
    ledger's objects, every one re-read and re-judged with current retail
    truth (link_census.read_facts), in current link order: objects rebuilt
    since the census, frozen objects whose COMDAT verdicts the census left
    unjudged, data providers, sources added since the census, and no
    definitions of sources the ledger dropped. Nothing is compared by mtime
    (review 2026-10-15 round 1: the census stamps UTC on its runner).

    Refuses (SystemExit) when game/ or inputs/reference/ files outside
    `checked` differ from HEAD, when more than REFRESH_COMPILE_LIMIT objects
    are stale or missing and `allow_compile` is not set, or when any object
    stays stale. Objects still missing after the compile are left out, as
    the census leaves them out (with a warning).
    The census's blockers and bytes (the "before" figures) are kept, and so
    are its weak_* receipts: a refreshed index is a preview, never a census.
    """
    dirty = refresh_dirty(checked)
    if dirty:
        raise SystemExit(f"link_check --refresh: {len(dirty):,} file(s) outside the checked ones differ from "
                         f"HEAD (e.g. {dirty[0]}); commit or park them first: a refreshed index must "
                         "describe one commit")
    # BUILD_RECOMPILE_ONLY trusts every object it is not told to rebuild
    # (link_census --build pops it for the same reason).
    os.environ.pop("BUILD_RECOMPILE_ONLY", None)
    receipts = _refresh_receipts()
    link_census._INPUT_RECEIPTS = receipts    # stale_objects judges with these proofs
    rows = link_census.ledger() or []
    sources = link_census._object_sources(rows)
    present, missing = link_census.objects(rows)
    stale = link_census.stale_objects(present, sources)
    need = sorted({sources[obj] for obj in list(missing) + list(stale) if obj in sources})
    if len(need) > REFRESH_COMPILE_LIMIT and not allow_compile:
        raise SystemExit(f"link_check --refresh: {len(need):,} ledger object(s) are stale or missing (limit "
                         f"{REFRESH_COMPILE_LIMIT}); build them first (./build.sh) or pass --refresh-compile "
                         "(a cold worktree compiles the whole tree, hours, under the host-wide build lock)")
    if need:
        try:
            outputs = build.compile_rows(rows, need, input_proof=receipts)
            link_census._refresh_missing_search_root_receipts(rows, outputs, receipts)
        except SystemExit as error:     # one unrelated compile error leaves its object missing
            print(f"link_check: compile stopped ({error}); continuing with what was built", file=sys.stderr)
        receipts.save()
        present, missing = link_census.objects(rows)
        stale = link_census.stale_objects(present, sources)
        print(f"link_check: compiled {len(need):,} stale or missing ledger object(s)")
    if stale:
        bad = sorted(obj.name for obj in stale)
        raise SystemExit(f"link_check --refresh: {len(bad):,} object(s) still stale (e.g. {bad[0]}); "
                         "nothing previewed")
    if missing:
        print(f"link_check --refresh: {len(missing):,} ledger object(s) missing (e.g. "
              f"{sorted(o.name for o in missing)[0]}); previewing without them, as the census links "
              "without them", file=sys.stderr)
    link_census.verify_data_objects()
    facts = link_census.read_facts(present, rows)
    owners = link_census.ledger_owners(rows)
    # the census's weak-default rejudge, on its own measured /MAP holders
    kept = census_kept(index["selection"])
    if kept is not None:
        facts = link_census.rejudge_weak_facts(present, facts, rows, kept, owners)
    names = [obj.name for obj in present]
    selection = current_selection(index, names, facts, owners)
    tables = index_tables(present, facts, selection)
    # An unproven kept definition blocks only where its definers changed since
    # the census; elsewhere the census's own (non-blocking) result stands.
    old_owners = index["selection"].get("owners", {})
    owner_changes = {name for name in set(old_owners) | set(owners)
                     if set(old_owners.get(name, ())) != set(owners.get(name, ()))}
    tables["selection"]["changed"] = changed_definers(index, tables) | owner_changes
    # a /MAP holder measured on other definers cannot be recomputed here
    stale = set(tables["selection"].get("unmeasured", ()))
    # round 3 F5: a ledger object that could not be built still links in the
    # real build; the names the census saw it define cannot be judged without
    # it, and one the census never saw might define any name
    gone_here = {obj.name for obj in missing}
    positions = {i for i, name in enumerate(index["objects"]) if name in gone_here}
    stale |= {name for name, at in index["strong"].items() if positions & set(at)}
    stale |= {name for name, at in index["comdat"].items() if any(i in positions for i, _, _ in at)}
    tables["selection"]["stale"] = stale
    tables["selection"]["census_kept"] = {name: kept_definition(index, name)
                                          for name in tables["selection"]["changed"]}
    tables["selection"]["unknown_definers"] = bool(gone_here - set(index["objects"]))
    for key in ("weak_inventory", "weak_root", "weak_truth"):
        tables.pop(key, None)       # the census's /MAP receipts stay the census's
    index.update(tables)
    index["refreshed"] = True
    print(f"link_check: refreshed all {len(present):,} current ledger object(s) against current retail truth")


def refresh(index, objects, truth):
    """Replace the census's definitions of `objects` with their current
    object files', so a fix in one file (a removed duplicate, a new datum) is
    seen when checking the others. Blockers of files not passed stay as the
    census saw them."""
    if type(index) is FrozenPredictionIndex:
        raise TypeError("frozen prediction index cannot be refreshed; rebuild it")
    require_common_index(index)
    positions = {index["objects"].index(obj.name): obj for obj in objects if obj.name in index["objects"]}
    if not positions:
        return
    # Freeze each replacement once. Both passes and COMMON parsing use those
    # same bytes; a failing read or rejudgment cannot partly update the index.
    payloads = {position: _object_bytes(obj) for position, obj in positions.items()}
    replacements = {position: (link_census.common_definitions(obj, data=payloads[position]),
                                link_census.object_facts(obj, truth, data=payloads[position]))
                    for position, obj in positions.items()}
    import alias_guard
    declared = {position: alias_guard.drectve_aliases(payloads[position]) for position in positions}
    updated = {**index, **{table: {name: list(entries) for name, entries in index[table].items()}
                          for table in ("strong", "comdat", "common")}}
    for table, at in (("strong", lambda entry: entry), ("comdat", lambda entry: entry[0]),
                      ("common", lambda entry: entry[0])):
        for name, entries in updated[table].items():
            if any(at(entry) in positions for entry in entries):
                updated[table][name] = [entry for entry in entries if at(entry) not in positions]
    for position, (common, fact) in replacements.items():
        copies, defined, _, _ = fact
        for name in defined:
            updated["strong"].setdefault(name, []).append(position)
        for name, digest, _, verdict in copies:
            updated["comdat"].setdefault(name, []).append((position, digest, verdict))
        for name, size in common.items():
            updated["common"].setdefault(name, []).append((position, size))
    updated["aliases"] = {name: [entry for entry in entries if entry[0] not in positions]
                          for name, entries in index.get("aliases", {}).items()}
    for position, found in declared.items():
        for alias, target in found:
            updated["aliases"].setdefault(alias, []).append((position, target))
    updated["_weak_current_objects"] = dict(index.get("_weak_current_objects", {})) if index.get("_weak_token") is _WEAK_PREVIEW_TOKEN else {}
    for position, (_, fact) in replacements.items():
        updated["_weak_current_objects"][positions[position].name] = (fact.truth if isinstance(fact, link_census.ObjectFacts) else None,
                                                                      hashlib.sha256(payloads[position]).hexdigest(),
                                                                      link_census.policy_fingerprint(), positions[position],
                                                                      fact.independent if isinstance(fact, link_census.ObjectFacts) else {})
    updated["_weak_token"] = _WEAK_PREVIEW_TOKEN
    updated["weak_inventory"] = dict(index.get("weak_inventory", {}))
    for position, obj in positions.items():
        updated["weak_inventory"][obj.name] = (str(obj), hashlib.sha256(payloads[position]).hexdigest())
    context = weak_context(updated, truth)
    for position, (_, fact) in replacements.items():
        if not fact[3]:
            continue
        copies = link_census.object_facts(positions[position], truth, data=payloads[position],
                                          weak_context=context)[0]
        for name, digest, _, verdict in copies:
            updated["comdat"][name] = [(at, digest if at == position else old_digest,
                                         verdict if at == position else old_verdict)
                                        for at, old_digest, old_verdict in updated["comdat"][name]]
    for table in ("strong", "comdat", "common", "aliases", "_weak_current_objects", "_weak_token", "weak_inventory"):
        index[table] = updated[table]


_JUDGE = []


def alias_judge():
    """One alias_guard.Judge per process, built on first use (it reads the ledger)."""
    if not _JUDGE:
        import alias_guard
        _JUDGE.append(alias_guard.Judge())
    return _JUDGE[0]


def _prediction_tables_valid(index):
    """Cheap shape check before skipping the unusable prediction-only context.

    Noncanonical tables still take weak_context's original validation path.
    This does not validate a weak receipt or authorize a fallback route.
    """
    if type(index) is not dict:
        return False
    objects = index.get("objects")
    selection = index.get("selection", {})
    if (type(objects) not in (list, tuple) or any(type(obj) is not str for obj in objects) or
            len(set(objects)) != len(objects) or type(selection) is not dict):
        return False
    owners, exceptions = selection.get("owners", {}), selection.get("exceptions", {})
    tables = (index.get("strong"), index.get("comdat"), index.get("common"), owners, exceptions)
    if any(type(table) is not dict or any(type(name) is not str for name in table) for table in tables):
        return False
    if any(type(found) not in (set, frozenset, list, tuple) or
           any(type(obj) is not str for obj in found) for found in owners.values()):
        return False
    if any(holder is not None and type(holder) is not int for holder in exceptions.values()):
        return False
    if any(type(entries) not in (list, tuple) for entries in index["common"].values()):
        return False
    count = len(objects)
    for positions in index["strong"].values():
        if type(positions) not in (list, tuple):
            return False
        if any(type(position) is not int or not 0 <= position < count for position in positions):
            return False
    for entries in index["comdat"].values():
        if type(entries) not in (list, tuple):
            return False
        for entry in entries:
            if (type(entry) not in (list, tuple) or len(entry) != 3 or
                    type(entry[0]) is not int or not 0 <= entry[0] < count or
                    type(entry[1]) is not str or (entry[2] is not None and type(entry[2]) is not str)):
                return False
    return True


class _NotFreezable(ValueError):
    pass


def _copy_prediction_value(value, active):
    """Copy exact builtins only: no copy hooks, retained containers, or cycles."""
    kind = type(value)
    if kind in (type(None), bool, int, float, str, bytes):
        return value
    if kind not in (dict, list, tuple, set, frozenset) or id(value) in active:
        raise _NotFreezable
    active.add(id(value))
    try:
        if kind is dict:
            return {_copy_prediction_value(key, active): _copy_prediction_value(item, active)
                    for key, item in value.items()}
        return kind(_copy_prediction_value(item, active) for item in value)
    finally:
        active.remove(id(value))


def _prediction_consumers_valid(index):
    """Conservative eligibility for consumers not covered by the native scan."""
    selection = index["selection"]
    if "owners" not in selection or "exceptions" not in selection:
        return False
    # judge_selected uses set intersection; sealing list owners as tuples
    # would change the native TypeError instead of preserving its input path.
    if any(type(found) not in (set, frozenset) for found in selection["owners"].values()):
        return False
    count = len(index["objects"])
    def position(value):
        return type(value) is int and 0 <= value < count
    def strings(values):
        return (type(values) in (set, frozenset, list, tuple) and
                all(type(value) is str for value in values))
    if any(holder is not None and not position(holder) for holder in selection["exceptions"].values()):
        return False
    for entries in index["common"].values():
        for entry in entries:
            if (type(entry) not in (tuple, list) or len(entry) != 2 or not position(entry[0]) or
                    type(entry[1]) is not int or not 0 < entry[1] <= 0xFFFFFFFF):
                return False
    aliases = index.get("aliases", {})
    if type(aliases) is not dict or any(type(name) is not str for name in aliases):
        return False
    for entries in aliases.values():
        if type(entries) not in (tuple, list):
            return False
        if any(type(entry) not in (tuple, list) or len(entry) != 2 or
               not position(entry[0]) or type(entry[1]) is not str for entry in entries):
            return False
    excuses = index.get("excuses")
    if type(excuses) is not dict or not strings(excuses.get("runtime")):
        return False
    imported, stubs = excuses.get("imported"), excuses.get("stubs")
    if any(type(table) is not dict or any(type(name) is not str for name in table)
           for table in (imported, stubs)):
        return False
    if not all(strings(dlls) for dlls in imported.values()):
        return False
    for entries in stubs.values():
        if type(entries) not in (set, frozenset, list, tuple):
            return False
        if any(type(entry) not in (list, tuple) or len(entry) != 2 or
               any(type(value) is not str for value in entry) for entry in entries):
            return False
    return True


def _seal_prediction_value(value):
    if type(value) is dict:
        return MappingProxyType({key: _seal_prediction_value(item) for key, item in value.items()})
    if type(value) in (list, tuple):
        return tuple(_seal_prediction_value(item) for item in value)
    if type(value) in (set, frozenset):
        return frozenset(_seal_prediction_value(item) for item in value)
    return value


def _prediction_index_api():
    # Owned immutable object storage, not a cache of caller dictionaries or
    # validator results. Weak keys release each payload with its issued handle;
    # neither the registry nor an insertion helper is exposed by the API.
    payloads = WeakKeyDictionary()

    class FrozenPredictionIndex(Mapping):
        """Opaque handle to factory-owned, recursively immutable prediction tables.

        Only issued handles can read tables or skip repeated shape validation.
        No instance slot stores a replaceable payload or a validation flag.
        Updates require a new native index and a new factory call.
        """
        __slots__ = ("__weakref__",)
        # Storage keys identify handles, never caller input objects. Mapping's
        # content equality would recurse through this storage lookup.
        __hash__ = object.__hash__
        __eq__ = object.__eq__

        def __new__(cls, *args, **kwargs):
            raise TypeError("use freeze_prediction_index")

        def __init_subclass__(cls, **kwargs):
            raise TypeError("FrozenPredictionIndex cannot be subclassed")

        def __setattr__(self, name, value):
            raise TypeError("frozen prediction index cannot be mutated")

        def __delattr__(self, name):
            raise TypeError("frozen prediction index cannot be mutated")

        def _tables(self):
            try:
                return payloads[self]
            except KeyError:
                raise TypeError("unregistered frozen prediction index") from None

        def __getitem__(self, key):
            return self._tables()[key]

        def __iter__(self):
            return iter(self._tables())

        def __len__(self):
            return len(self._tables())

    def freeze_prediction_index(index):
        """Opt in to a private prediction snapshot, or return an ineligible input unchanged.

        Actual-MAP fields (even invalid/partial ones), receipts and refresh state
        must retain their original native validation path. Only supported exact
        builtins are copied; malformed consumer shapes are never normalized.
        """
        if type(index) is FrozenPredictionIndex:
            index._tables()
            return index
        if type(index) is not dict:
            return index
        try:
            snapshot = _copy_prediction_value(index, set())
        except (_NotFreezable, RecursionError):
            return index
        # Eligibility belongs to the owned copy, not a previously inspected input.
        selection = snapshot.get("selection")
        if (type(selection) is not dict or
                any(name in selection for name in ("weak_kept", "weak_addresses", "weak_locations", "weak_ambiguous")) or
                selection.get("weak_receipt") is not None or
                any(name in snapshot for name in ("_weak_token", "_weak_current_objects"))):
            return index
        try:
            require_common_index(snapshot)
        except SystemExit:
            return index
        if not _prediction_tables_valid(snapshot) or not _prediction_consumers_valid(snapshot):
            return index
        sealed = _seal_prediction_value(snapshot)
        frozen = object.__new__(FrozenPredictionIndex)
        payloads[frozen] = sealed
        return frozen

    return FrozenPredictionIndex, freeze_prediction_index


FrozenPredictionIndex, freeze_prediction_index = _prediction_index_api()
del _prediction_index_api


def check_object(obj, index, truth, source=None, judge=None):
    """{unresolved, duplicates, comdat, addresses, selected, alias_target, alias_unknown} for one object
    against the index."""
    import alias_guard
    import link_debt
    require_common_index(index)
    data = _object_bytes(obj)
    common = link_census.common_definitions(obj, data=data)
    context = None
    if type(index) is FrozenPredictionIndex:
        pass  # Prediction-only by construction; all per-object checks below still run.
    elif not _prediction_tables_valid(index):
        context = weak_context(index, truth)
    else:
        selection = index.get("selection", {})
        receipt = selected_receipt_digest(selection)
        # Only actual-MAP receipts can authorize a weak fallback. Their full
        # inventory, truth and current-provider validation must still run.
        if receipt is not None and receipt == selection.get("weak_receipt"):
            context = weak_context(index, truth)
    copies, defined, undefined, weaks = link_census.object_facts(
        obj, truth, data=data, weak_context=context)
    own = index["objects"].index(obj.name) if obj.name in index["objects"] else None
    position = own if own is not None else len(index["objects"])
    strong, comdat = index["strong"], index["comdat"]

    def elsewhere(name):
        return (any(i != own for i in strong.get(name, ())) or
                any(i != own for i, _, _ in comdat.get(name, ())) or
                any(i != own for i, _ in index["common"].get(name, ())))

    mine = set(defined) | {name for name, _, _, _ in copies}
    excuses = index["excuses"]

    def resolves(name):
        return (name in mine or name in common or elsewhere(name) or link_census.excused(
            name, excuses["runtime"], excuses["imported"], excuses["stubs"]))

    missing = {name for name in set(undefined) - mine - set(common) if not resolves(name)}
    # /alternatename:A=B resolves A when nothing defines it and B resolves: this
    # object's own directives and every other census object's (they are global).
    declared = alias_guard.drectve_aliases(data)
    targets = collections.defaultdict(set)
    for alias, entries in index.get("aliases", {}).items():
        if alias in missing:
            targets[alias].update(target for i, target in entries if i != own)
    for alias, target in declared:
        targets[alias].add(target)
    through = {name for name in missing if any(resolves(target) for target in targets.get(name, ()))}
    unresolved = sorted(missing - through)
    judged = [(alias, target) for alias, target in declared] + [
        (name, target) for name in through for target in targets[name]]
    alias_why, verdicts = {}, {}
    if judged:
        judge = judge or alias_judge()
        for alias, target in dict.fromkeys(judged):
            verdicts[alias, target] = verdict, why = judge.verdict(alias, target)
            if verdict == "wrong":
                alias_why[f"{alias}={target}"] = why
    # A call resolved through an alias nothing can judge is not counted
    # resolved: the census charges it as alias_unknown (alias_blockers).
    unknown_why = {}
    for name in through:
        pairs = [(name, target) for target in targets[name]]
        if any(verdicts[pair][0] == "wrong" for pair in pairs):
            continue
        # a directive whose target nothing defines (cl.exe's member-template
        # fallback) cannot bind the call: it is inert, not an unproven binding
        for pair in [(name, target) for target in targets[name] if resolves(target)]:
            if verdicts[pair][0] == "unknown":
                unknown_why["=".join(pair)] = verdicts[pair][1]
    duplicates = sorted(name for name in mine if duplicate(name, position, name in set(defined), own, index))
    losers = []
    for name, digest, _, verdict in copies:
        found = [(i, d, v) for i, d, v in comdat.get(name, ()) if i != own]
        found.append((position, digest, verdict))
        found.sort(key=lambda copy: copy[0])
        loses, rule = link_census.keep_rule(found, name not in index.get("unreferenced", ()))
        if loses[position]:
            losers.append((name, rule, verdict))
    addresses = []
    if source is not None:
        try:
            addresses = link_debt.addresses((ROOT / source).read_text(encoding="utf-8", errors="replace"))
        except OSError:
            pass
    preview_unknown = []
    selected = wrong_selected(obj, (copies, defined, undefined, weaks), own, position, index,
                              common_names=common, unknown=preview_unknown)
    # a copy judged against definers that could not be refreshed proves nothing either way
    stale = index["selection"].get("stale", set())
    preview_unknown += [name for name, _, _ in losers if name in stale]
    losers = [loser for loser in losers if loser[0] not in stale]
    return {"unresolved": unresolved, "duplicates": duplicates, "comdat": losers, "addresses": addresses,
            "selected": selected, "preview_unknown": sorted(set(preview_unknown)),
            "alias_target": sorted(alias_why), "alias_unknown": sorted(unknown_why),
            "alias_why": {**unknown_why, **alias_why}}


def wrong_selected(obj, fact, own, position, index, *, common_names=(), unknown=None):
    """Names this object defines or references whose kept definition is proven
    not retail's, judged as the census judges them (link_census.judge_selected)
    with this object's current definitions in place of the census's. The
    holder is the census's /MAP holder while it still defines the name, else
    the first definer in link order.

    THE LINKED-CLAIM RULE (project lead, 2026-10-16; apply_selection_rule
    prepares it): a name whose definers or ledger ownership changed since the
    census (selection["changed"]) is judged on refreshed definers with
    current retail truth; if it is still unprovable ("unknown"), or its
    definers could not be refreshed (selection["stale"]), it is appended to
    `unknown` -- LINKED PREVIEW UNKNOWN, never LINKS. A name that did not
    change keeps the census's verdict: "unknown" there blocks nothing."""
    copies, defined, _, _ = fact
    selection = index["selection"]
    exceptions, owners, objects = selection["exceptions"], selection["owners"], index["objects"]
    changed = selection.get("changed", set())
    stale = selection.get("stale", set())
    hidden = selection.get("unknown_definers", False)
    census_kept = selection.get("census_kept", {})
    truth_moved = selection.get("truth_moved", set())
    census_verdict = selection.get("census_verdict", {})
    unknown = [] if unknown is None else unknown
    mine_copies = {name: (digest, verdict) for name, digest, _, verdict in copies}
    mine_strong = set(defined)
    found = []
    # A normal definition can override a TU's own COMMON. Its selected
    # strong/COMDAT body still needs the existing retail-truth check.
    for name in sorted(link_census.touched_names(fact) | set(common_names)):
        found_copies = {i: (d, v) for i, d, v in index["comdat"].get(name, ()) if i != own}
        exclusive = {i for i in index["strong"].get(name, ()) if i != own}
        if name in mine_copies:
            found_copies[position] = mine_copies[name]
        if name in mine_strong:
            exclusive.add(position)
        definers = set(found_copies) | exclusive
        if not definers:
            if hidden:
                unknown.append(name)
            continue
        if name in stale:
            unknown.append(name)
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
        elif hidden:
            unknown.append(name)
        elif name in truth_moved and holder is not None and holder not in exclusive \
                and found_copies[holder][1] != census_verdict.get(name):
            # retail truth moved under the kept copy: the census's proof of it
            # no longer holds, and nothing here proves it again
            unknown.append(name)
        elif result == "unknown" and name in changed:
            # The definers changed, yet the link keeps the very body the census
            # saw it keep (same object, same copy) and nothing proves it either
            # way: that is the census's own non-blocking verdict, unchanged.
            kept_now = (label[holder], "strong" if holder in exclusive else found_copies[holder][0]) \
                if holder is not None else None
            if kept_now is None or kept_now != census_kept.get(name, False):
                unknown.append(name)
    return found


def place_new(index, names, order):
    """Insert objects the census never saw into index["objects"] at their
    place in `order` (current link order, object names): after the nearest
    census object that precedes them there. Every position the index stores
    (definition tables, aliases, /MAP exceptions) is renumbered to match."""
    known = {name: i for i, name in enumerate(index["objects"])}
    after = {}
    for name in dict.fromkeys(names):
        at = order.index(name)
        before = next((known[o] for o in reversed(order[:at]) if o in known), -1)
        after.setdefault(before, []).append((at, name))
    objects, moved = [], {}
    for old in range(-1, len(index["objects"])):
        if old >= 0:
            moved[old] = len(objects)
            objects.append(index["objects"][old])
        objects.extend(name for _, name in sorted(after.get(old, ())))
    shift = moved.__getitem__
    index["objects"] = objects
    index["strong"] = {name: [shift(i) for i in found] for name, found in index["strong"].items()}
    for table in ("comdat", "common", "aliases"):
        if table in index:
            index[table] = {name: [(shift(entry[0]), *entry[1:]) for entry in entries]
                            for name, entries in index[table].items()}
    selection = index.get("selection")
    if selection and "exceptions" in selection:
        index["selection"] = {**selection, "exceptions": {name: None if holder is None else shift(holder)
                                                          for name, holder in selection["exceptions"].items()}}


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
        if source is None and obj.name not in index["objects"]:
            raise SystemExit(f"link_check: {argument} is in no census and no source is known for it, so it "
                             f"cannot be shown current; check its source instead")
        if source is not None and not link_census.object_current(ROOT / source, obj):
            raise SystemExit(f"link_check: {obj.name} is not current for {source}; "
                             f"check the source instead (it recompiles)")
        return source, obj
    source = (path if path.is_absolute() else ROOT / path).resolve().relative_to(ROOT.resolve()).as_posix()
    outputs = build.compile_rows([], [ROOT / source])
    return source, outputs[ROOT / source]


def report(source, obj, result, index, now_bytes):
    """Print one file's verdict (see _report) under the report lock, so a
    hook timeout never prints UNKNOWN for a file mid-verdict."""
    with _REPORT_LOCK:
        return _report(source, obj, result, index, now_bytes)


def _report(source, obj, result, index, now_bytes):
    census = index["blockers"].get(source or "", {})
    before = index["bytes"].get(source, 0) if census.get("linked") else 0
    blocked = any(result.get(kind) for kind in ("unresolved", "duplicates", "comdat", "addresses", "selected",
                                                "alias_target", "alias_unknown"))
    unknown = result.get("preview_unknown") or []
    clean = not blocked and not unknown
    # LINKED PREVIEW UNKNOWN never claims a gain: at most the census's figure
    after = now_bytes if clean else (min(before, now_bytes) if not blocked else 0)
    result["after_bytes"] = after
    verdict = "LINKS" if clean else ("does not link" if blocked else "LINKED PREVIEW UNKNOWN")
    if source:
        _REPORTED.add(repo_path(source, ROOT))
    print(f"{source or obj.name}: {verdict}  "
          f"LINKED {before:,} -> {after:,} bytes (census {index['meta'].get('date', '?')} at "
          f"{index['meta'].get('commit', '?')}"
          f"{' -> this checkout, refreshed' if index.get('refreshed') else ''}; file's own bytes {now_bytes:,})")
    if unknown:
        print(f"  LINKED PREVIEW UNKNOWN \u2014 selection census stale for: {', '.join(unknown)}")
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
    for name in result.get("alias_target", ()):
        print(f"  alias_target {name}  (/alternatename binds the call to another body: "
              f"{result.get('alias_why', {}).get(name, '')})")
    for name in result.get("alias_unknown", ()):
        print(f"  alias_unknown {name}  (the call resolves only through an /alternatename alias nothing can "
              f"judge: {result.get('alias_why', {}).get(name, '')})")
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
    "alias_target": "an /alternatename alias binds a call to another body than its pin's: respell the call to the "
                    "row name at the pinned address (link_check.py near) or fix the pin (tools/alias_guard.py)",
    "alias_unknown": "a call resolves only through an /alternatename alias nothing can judge: call the row name at "
                     "the pinned address, or prove and pin the alias's address (tools/alias_guard.py)",
}


def family_of(name):
    return next((family for family, pattern in FAMILIES
                 if pattern.search(name) and not (family == "stlport" and PLAIN.match(name))), "")


def same_commit(a, b):
    """Two commit spellings, full or abbreviated (7+ hex digits), name one commit."""
    width = min(len(a or ""), len(b or ""))
    return width >= 7 and a[:width].lower() == b[:width].lower()


def _is_ancestor(old, new):
    """True when `old` is `new` or an ancestor of it; None when git cannot say."""
    code = subprocess.run(["git", "merge-base", "--is-ancestor", old, new], cwd=ROOT,
                          capture_output=True).returncode
    return {0: True, 1: False}.get(code)


def linked_since(census):
    """(sources, status census, note): the files the tracked link_status.csv
    says link, when its census is `census` or a later one. The local index
    and the published queue are only as fresh as their census; the daily
    census rewrites link_status.csv, and measured 2026-10-10 150 of 371 `near`
    files from the 10-09 index already linked at 10-10. A status older than
    `census`, or a census git cannot order, filters nothing (and says why)."""
    history = link_census.read_history()
    status = history[-1]["commit"] if history else ""
    if not status or not link_census.STATUS.exists():
        return frozenset(), "", "no tracked link census to freshen it"
    if census and not same_commit(census, status):
        newer = _is_ancestor(census, status)
        if newer is None:
            return frozenset(), status, f"git cannot order census {census} against link_status.csv's {status}"
        if not newer:
            return frozenset(), status, f"link_status.csv measured {status}, not after census {census}"
    with link_census.STATUS.open(newline="", encoding="utf-8") as handle:
        linked = frozenset(row["source"] for row in csv.DictReader(handle) if row["linked"] == "yes")
    return linked, status, ""


def queue_rows(index, linked=frozenset()):
    """The one linking queue: every blocker name that is some unlinked file's
    ONLY blocker, ranked by the bytes those files would link. `linked`
    (linked_since) are files a later census saw link."""
    gain, files = collections.Counter(), collections.defaultdict(list)
    for source, entry in index["blockers"].items():
        if entry["linked"] or source in linked:
            continue
        names = (set(entry["unresolved"]) | set(entry["duplicates"]) | set(entry["losers"])
                 | set(entry.get("wrong_selected", ())) | set(entry.get("alias_target", ()))
                 | set(entry.get("alias_unknown", ())))
        if entry["addresses"]:
            names.add(ADDRESSES)
        if len(names) == 1:
            name = names.pop()
            gain[name] += index["bytes"].get(source, 0)
            files[name].append(source)
    kinds = {}
    for entry in index["blockers"].values():
        for kind in ("unresolved", "duplicates", "losers", "wrong_selected", "alias_target", "alias_unknown"):
            for name in entry.get(kind, ()):
                kinds.setdefault(name, kind)
    census = index["meta"].get("commit", "")
    return [{"rank": rank, "name": name, "kind": kinds.get(name, "addresses"), "family": family_of(name),
             "bytes_unlocked": count, "files": ";".join(sorted(files[name])),
             "hint": HINTS[kinds.get(name, "addresses")], "census": census}
            for rank, (name, count) in enumerate(sorted(gain.items(), key=lambda kv: (-kv[1], kv[0])), 1)]


def next_names(index, limit):
    """Print the head of the queue (queue_rows)."""
    linked, status, note = linked_since(index["meta"].get("commit", ""))
    rows = queue_rows(index, linked)
    print(f"blocker names that are some file's only blocker (census {index['meta'].get('date', '?')} at "
          f"{index['meta'].get('commit', '?')}; {_freshness(linked, status, note)}):")
    print(f"  {'bytes':>9} {'files':>5}  kind        name")
    for row in rows[:limit]:
        family = f"  [family {row['family']}]" if row["family"] else ""
        print(f"  {row['bytes_unlocked']:>9,} {row['files'].count(';') + 1:>5}  {row['kind']:<10}  {row['name']}{family}")
    print(f"  {len(rows):,} names in all, {sum(row['bytes_unlocked'] for row in rows):,} bytes")


def _freshness(linked, status, note):
    return note or f"files linked at census {status} dropped"


def publish(index, path=QUEUE, limit=QUEUE_LIMIT):
    """Write the queue's top `limit` rows as the tracked CSV every host serves from."""
    rows = queue_rows(index, linked_since(index["meta"].get("commit", ""))[0])[:limit]
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
    linked, status, note = linked_since(census)
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
        # A file another census saw link, or one changed since this census,
        # is no longer the census's evidence; the row stands for the rest.
        # Skipping a row for ANY changed file lost row 1 (115 files) on 10-10.
        still = [source for source in files if source not in linked and source not in changed]
        if row["family"] != (args.family or ""):
            skipped[f"family {row['family']}" if row["family"] else "not in family"] += 1
        elif key in landed:
            skipped["landed since the census"] += 1
        elif all(source in linked for source in files):
            skipped[f"linked at census {status}"] += 1
        elif not still:
            skipped["every file linked or changed since the census"] += 1
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
            gone = (f"; {len(files) - len(still)} other(s) linked or changed since the census"
                    if len(still) < len(files) else "")
            print(f"link queue #{row['rank']} (census {census}; {_freshness(linked, status, note)}): {row['name']}\n"
                  f"  {row['kind']}; unlocked {int(row['bytes_unlocked']):,} B in {len(files)} file(s) at the census\n"
                  f"  fix: {row['hint']}\n  files: {len(still)} open{gone}: "
                  f"{' '.join(still[:8])}{' ...' if len(still) > 8 else ''}")
            if lease:
                print(f"  claimed 0x{key:08X}. Commit-message trailer:  Claim-Lease: 0x{key:08X}={lease}\n"
                      f"  after the push: python3 tools/claims.py release --landed <sha>")
            print(f"  ({', '.join(f'{n} {why}' for why, n in skipped.items()) or 'nothing'} skipped)")
            return 0
    if shown:
        return 0
    print(f"link_check next: no open row in {len(rows)} ({dict(skipped)}); the next census refreshes the queue")
    return 1


NEAR_BLOCKING = ("duplicates", "losers", "wrong_selected", "alias_target", "alias_unknown")
GUARDED = "a real name would be lost or doubled"
LINKED_LATER = "linked at a later census"
BLOCKED_NOW = "blocked at this census (re_attempts.log)"


def row_verdict(records, row, source, shared=frozenset()):
    """The latest re_attempts.log verdict about this ledger row in this file,
    or None: the later of the one judged here (re_log census-source=) and
    one naming no file -- the latter only when no other source has a row of
    that name at that RVA. A verdict judged in another file is not this
    file's; unsure is none (fail open). `records` is
    re_log.latest_link_records()."""
    rva, name = int(row["target_rva"], 16), row["name"]
    found = [records.get((rva, name, source))]
    if (rva, name) not in shared:
        found.append(records.get((rva, name, "")))
    found = [entry for entry in found if entry]
    return max(found, key=lambda entry: entry[0])[1] if found else None


def blocked_files(callers, records, census, shared=frozenset()):
    """{source: why} for the files a caller row of which has, as its latest
    verdict about that row in that file (row_verdict), a deferral or dead end
    recorded at `census` (re_log census=): the same evidence would block it
    again. A verdict from an earlier census is stale and blocks nothing.
    `callers` is {source: ledger rows}, `records` re_log.latest_link_records(),
    `shared` the (rva, name) pairs of several sources."""
    import eligibility
    import re_log
    stops = re_log.DEFERRED_STATUSES | re_log.DEAD_END_STATUSES
    released = eligibility.released_rvas()     # a deferral whose blocked-on= blockers landed blocks nothing
    found = {}
    for source, rows in callers.items():
        for row in rows:
            fields = row_verdict(records, row, source, shared)
            if fields and fields[3] in re_log.DEFERRED_STATUSES and int(fields[1], 16) in released:
                continue
            if fields and fields[3] in stops and same_commit(re_log.census_of(fields[4]), census):
                found[source] = f"{fields[3]} {fields[1]} at census {census}"
                break
    return found


def near_rows(index, judge, most=None, under="", every=False, skipped=None, linked=frozenset(), blocked=None):
    """Unlinked files whose every blocker is an unresolved call name a
    respelling fixes: the name is pinned, and the ledger row at its pinned
    address (alias_guard.Judge.respell) is a C++ definition that passes the
    alias check. A file relying on an alias nothing can judge (alias_unknown)
    is not near. A respelling that would put a second real name on a body,
    or turn a real call name into another tree's placeholder
    (alias_guard.two_real_names), skips its file unless `every`; so does a
    file a later census saw link (`linked`, linked_since) or one blocked at
    this census (`blocked`, blocked_files). `skipped` (a Counter) counts the
    skips.
    Largest first: [{source, bytes, fixes: [(name, row name, note)]}]."""
    rows = []
    skipped = collections.Counter() if skipped is None else skipped
    blocked = blocked or {}
    for source, entry in index["blockers"].items():
        if entry["linked"] or not source.startswith(under) or entry["addresses"]:
            continue
        if any(entry.get(kind) for kind in NEAR_BLOCKING):
            continue
        names = entry["unresolved"]
        if not names or (most and len(names) > most):
            continue
        fixes, guarded = [], False
        for name in names:
            target, note, guard = judge.respell(name, source)
            if target is None:
                break
            guarded = guarded or bool(guard)
            fixes.append((name, target, "; ".join(filter(None, (guard, note)))))
        else:
            if source in linked:
                skipped[LINKED_LATER] += 1
            elif source in blocked:
                skipped[BLOCKED_NOW] += 1
            elif guarded and not every:
                skipped[GUARDED] += 1
            else:
                rows.append({"source": source, "bytes": index["bytes"].get(source, 0), "fixes": fixes})
    rows.sort(key=lambda row: (-row["bytes"], row["source"]))
    return rows


GENERATED = (("game/gen_small/", "gen_small"), ("game/gen_asm/", "gen_asm"))
CONVENTIONS = {"A": "cdecl", "E": "thiscall", "G": "stdcall", "I": "fastcall"}
STATIC_OR_FREE = frozenset("CDKLSTYZ")  # no `this` cv letter before the convention
MEMBER = frozenset("ABEFIJMNQRUV")       # a cv letter, then the convention
# G H O P W X are adjustor thunks: an encoded adjustment precedes the cv letter
# (?f@C@@W3AEXXZ is a thiscall thunk, not cdecl; GPT-6.1-Sol, review round 1).


def convention(name):
    """The calling convention a link name spells: a C name by its decoration,
    a C++ name by the letter after its scope. '' for data, a thunk, or a name
    whose scope is a template (its first `@@` may close a template argument)."""
    if not name.startswith("?"):
        return ("stdcall" if re.fullmatch(r"_\w+@\d+", name) else
                "fastcall" if re.fullmatch(r"@\w+@\d+", name) else "cdecl")
    import name_regression
    shape = name_regression.declaration_shape(name)
    if shape is not None:   # the full reader, template scopes too: its letter, or '' for data
        return CONVENTIONS.get(shape[3], "") if len(shape) == 6 else ""
    at = name.find("@@")
    if at < 0 or "?$" in name[:at]:
        return ""
    lead = name[at + 2:at + 3]
    if lead in STATIC_OR_FREE:
        letter = at + 3
    elif lead in MEMBER:
        letter = at + 4
    else:
        return ""      # data, a thunk, or a special name
    return CONVENTIONS.get(name[letter:letter + 1], "")


def row_kind(row):
    """authored, gen_small, gen_asm or gen-alias: how far the row is from real source."""
    if row is None:
        return "no row"
    if re.search(r"(?:^|[;\s])gen-alias(?:[;\s=]|$)", row.get("notes") or ""):
        return "gen-alias"
    return next((kind for prefix, kind in GENERATED if row["source"].startswith(prefix)), "authored")


def packet_context(census, changed):
    """What every packet reads once: matched ledger rows by source and RVA,
    the latest re_attempts.log verdicts, the census the verdicts are judged
    against, and the files changed since the index's census."""
    import re_log
    by_source, by_rva = collections.defaultdict(list), collections.defaultdict(list)
    sources = collections.defaultdict(set)
    for row in link_census.ledger():
        by_source[row["source"]].append(row)
        by_rva[int(row["target_rva"], 16)].append(row)
        sources[int(row["target_rva"], 16), row["name"]].add(row["source"])
    shared = frozenset(key for key, found in sources.items() if len(found) > 1)
    return {"by_source": by_source, "by_rva": by_rva, "latest": re_log.latest_link_records(), "census": census,
            "changed": changed, "refused": set(), "shared": shared}


def preflight(rows, ctx):
    """Load name_regression's verdict on every respelling `rows` need, once."""
    import name_regression
    pairs = {pair for row in rows for call, target, _ in row["fixes"]
             for pair in name_regression.symbol_pairs(call, target) or ()}
    ctx["refused"] = name_regression.refused_respellings(pairs)


def packet(row, judge, ctx):
    """The repair packet for one near file: its caller rows, each respelling
    with the row it targets (address, size, source, kind), the conventions
    both names spell, the name_regression preflight, the caller rows' prior
    verdicts (current or stale against the census), and a verdict:
    skip (another lane's or the next census's), escalate (a respelling is not
    enough or a hook would refuse it) or serve."""
    import build
    import name_regression
    import re_log
    source, skip, escalate, fixes = row["source"], [], [], []
    if source in ctx["changed"]:
        skip.append("changed since the index's census: the next census re-judges it")
    for call, target, note in row["fixes"]:
        address = judge.pinned(call)
        places = [] if address is None else list(dict.fromkeys((address, judge.normal(address))))
        owners = [r for at in places for r in ctx["by_rva"].get(at, ()) if not r["name"].startswith("?j_")]
        owner = next((r for r in owners if build.ledger_object_symbol(r) == target), owners[0] if owners else None)
        kind, family = row_kind(owner), family_of(call) or family_of(target)
        spelled = convention(call), convention(target)
        pairs = name_regression.symbol_pairs(call, target)
        refused = sorted(p for p in pairs or () if p in ctx["refused"])
        fixes.append({"call": call, "target": target, "note": note, "row": owner, "kind": kind, "family": family,
                      "conventions": spelled, "refused": refused, "paired": pairs is not None})
        shapes = name_regression.declaration_shape(call), name_regression.declaration_shape(target)
        if pairs is None and None in (name_regression.mangled_identifiers(call),
                                      name_regression.mangled_identifiers(target)):
            escalate.append("a name the preflight cannot read: name_regression decides at commit")
        elif pairs is None or (None not in shapes and shapes[0] != shapes[1]):
            # not a rename: another operator or member kind, return, or parameter list
            # (bfmeDeleteVMP(void*, unsigned) called as operator delete(void*); GPT-6.1-Sol, round 2)
            escalate.append("the call and the row differ in shape (scope, kind, return or parameters): "
                            "a declaration change, not a respelling")
        if family:
            skip.append(f"family {family}: its owner serves it (next --family {family})")
        if kind != "authored":
            escalate.append(f"the row at the pin is {kind}: recover its source first")
        if all(spelled) and spelled[0] != spelled[1]:
            escalate.append(f"{spelled[0]} call to a {spelled[1]} row: a declaration change, not a respelling")
        if refused:
            escalate.append("name_regression refuses " + ", ".join(f"{a} -> {b}" for a, b in refused))
        if "tools/one_identity.py first" in note:
            escalate.append("two names, one body: tools/one_identity.py first")
        if "a C name called as a C++ row" in note:
            escalate.append("a C name called as a C++ row: prove which name is right")
    stops = re_log.DEFERRED_STATUSES | re_log.DEAD_END_STATUSES
    callers = sorted(ctx["by_source"].get(source, ()), key=lambda r: int(r["target_rva"], 16))
    prior = []
    for caller in callers:
        fields = row_verdict(ctx["latest"], caller, source, ctx.get("shared", ()))
        if fields and fields[3] in stops:
            tagged = re_log.census_of(fields[4])
            when = ("current" if same_commit(tagged, ctx["census"]) else
                    f"stale: census {tagged}" if tagged else "no census")
            prior.append({"rva": fields[1], "status": fields[3], "when": when, "evidence": fields[4]})
    reasons = list(dict.fromkeys(skip or escalate))
    return {**row, "verdict": "skip" if skip else "escalate" if escalate else "serve", "reasons": reasons,
            "callers": callers, "packet_fixes": fixes, "prior": prior}


def print_packet(item, census):
    source = item["source"]
    print(f"FILE {source} ({item['bytes']:,} B, {len(item['fixes'])} blocker(s), census {census})")
    print(f"  verdict: {item['verdict']}" + (f" ({'; '.join(item['reasons'])})" if item["reasons"] else ""))
    for caller in item["callers"]:
        print(f"  caller  {caller['name']} {caller['target_rva']} {caller['target_size']} B")
    for fix in item["packet_fixes"]:
        owner = fix["row"]
        where = (f"{owner['target_rva']} {owner['target_size']} B {fix['kind']} {owner['source']}"
                 if owner else "no matched row")
        print(f"  call    {fix['call']}\n    ->    {fix['target']}\n          row {where}; convention "
              f"{fix['conventions'][0] or '?'} -> {fix['conventions'][1] or '?'}"
              + (f"; family {fix['family']}" if fix["family"] else "")
              + (f"\n          name_regression refuses {fix['refused']}" if fix["refused"] else "")
              + (f"\n          [{fix['note']}]" if fix["note"] else ""))
    for verdict in item["prior"]:
        print(f"  prior   {verdict['status']} {verdict['rva']} ({verdict['when']}): {verdict['evidence'][:160]}")
    first = item["callers"][0] if item["callers"] else None
    print(f"  before  python3 tools/link_check.py {source}\n"
          f"  edit    declare each row's function and call it by the row name (never /alternatename)\n"
          f"  after   ./build.sh {source}   (every row still matches)\n"
          f"          python3 tools/link_check.py {source}   (LINKS, LINKED 0 -> {item['bytes']:,})")
    if first:
        print(f"  blocked {record_command(first, census)}")


def record_command(caller, census):
    """The re_log command that blocks this file at `census` (the index near served it from)."""
    tag = f" census={census} census-source={caller['source']}" if census else ""
    return (f"python3 tools/re_log.py record '{caller['name']}' {caller['target_rva']} {caller['target_size']} "
            f"blocked \"link_check near: <what stopped it> blocker=<family>/<detail>{tag} t=<min> model=<model>\"")


def near(argv):
    """`link_check.py near`: files that link once their calls are respelled to
    the ledger's row names (the call-by-row-name lane), with each respelling.
    Every respelling comes from this tree's symbols.csv and functions.csv:
    the row at the call name's pinned address. Declare that row's function
    and call it; never alias it (/alternatename) unless an ABI shape forces it.
    Files a later census saw link, and files blocked at this census, are
    dropped; the rest get a verdict (packet()) and only `serve` is listed
    unless --verdict says otherwise. --packet FILE prints one file's packet."""
    ap = argparse.ArgumentParser(prog="link_check.py near", description=near.__doc__)
    ap.add_argument("--max", type=int, default=0, help="only files with at most this many blockers")
    ap.add_argument("--under", default="", help="only sources under this path prefix")
    ap.add_argument("--limit", type=int, default=30)
    ap.add_argument("--shared", action="store_true",
                    help="rank respellings by the near files' bytes they appear in (a shared declaration fix)")
    ap.add_argument("--all", action="store_true",
                    help="also serve files whose respelling puts two real names on one body or turns a real call "
                         "name into another tree's placeholder (run tools/one_identity.py first)")
    ap.add_argument("--verdict", choices=("serve", "skip", "escalate", "any"), default="serve",
                    help="list files with this packet verdict (default serve)")
    ap.add_argument("--packet", metavar="FILE", help="print the full repair packet for one near file")
    args = ap.parse_args(argv)
    index = load_index()
    census = index["meta"].get("commit", "")
    changed = set(_git("diff", "--name-only", census, "HEAD").split()) if census else set()
    if index.get("alias_schema", 0) < ALIAS_SCHEMA:
        print("link_check near: this census index predates alias_unknown, so a file relying on an alias nothing "
              "can judge may be listed; the next census fixes that", file=sys.stderr)
    linked, status, note = linked_since(census)
    # A verdict stands while near serves from the index it was judged against
    # (re_log tags the census link_check loaded): the same evidence again.
    ctx = packet_context(census, changed)
    skipped = collections.Counter()
    judge = alias_judge()
    blocked = blocked_files(ctx["by_source"], ctx["latest"], census, ctx["shared"])
    rows = near_rows(index, judge, args.max, args.under, args.all or bool(args.packet), skipped, linked, blocked)
    preflight(rows, ctx)
    items = [packet(row, judge, ctx) for row in rows]
    if args.packet:
        found = [item for item in items if item["source"] == args.packet]
        if not found:
            why = (f"linked at census {status}" if args.packet in linked else
                   f"blocked: {blocked[args.packet]} (re_attempts.log)" if args.packet in blocked else
                   "not every blocker is a call a respelling fixes")
            print(f"link_check near: {args.packet} is not a near file at census {census or '?'}: {why}")
            return 1
        note_evaluated(found[0]["callers"], census)
        print_packet(found[0], census)
        return 0
    tally = collections.Counter(item["verdict"] for item in items)
    hints = {GUARDED: ": run tools/one_identity.py first (--all lists them)"}
    print(f"files every blocker of which a call respelling fixes (census {index['meta'].get('date', '?')} at "
          f"{census or '?'}; {_freshness(linked, status, note)}): {len(items):,} files, "
          f"{sum(r['bytes'] for r in items):,} bytes; "
          + ", ".join(f"{tally[v]:,} {v}" for v in ("serve", "skip", "escalate"))
          + "".join(f"; {n:,} skipped: {why}{hints.get(why, '')}" for why, n in skipped.items()))
    shown = [item for item in items if args.verdict in ("any", item["verdict"])]
    if args.shared:
        gain, files = collections.Counter(), collections.Counter()
        for row in shown:
            for fix in row["fixes"]:
                gain[fix[:2]] += row["bytes"] / len(row["fixes"])
                files[fix[:2]] += 1
        for (name, target), value in gain.most_common(args.limit):
            print(f"  {int(value):>8,} {files[name, target]:>4} files  {name}\n      -> {target}")
        return 0
    for item in shown[:args.limit]:
        why = f" ({'; '.join(item['reasons'])})" if item["reasons"] else ""
        print(f"  {item['bytes']:>7,}  {item['source']}  [{item['verdict']}{why}]")
        for name, target, note in item["fixes"]:
            print(f"      {name}\n        -> {target}{f'  [{note}]' if note else ''}")
    if shown:
        print("  full packet: python3 tools/link_check.py near --packet <file>")
    return 0


def main(argv=None, hook=False):
    argv = sys.argv[1:] if argv is None else argv
    if argv[:1] == ["next"]:
        return serve(argv[1:])
    if argv[:1] == ["near"]:
        return near(argv[1:])
    if argv == ["fetch-index"]:
        return fetch_index()
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("paths", nargs="*", help="sources (compiled when stale) or objects; or `next [-h]`")
    ap.add_argument("--next", action="store_true", help="rank blocker names by the bytes their fix alone unlocks")
    ap.add_argument("--limit", type=int, default=30)
    ap.add_argument("--census-only", action="store_true",
                    help="check against the census's definitions of the given files, not their current objects")
    ap.add_argument("--refresh", action="store_true",
                    help="judge against the CURRENT ledger's objects, all re-read with current retail truth, "
                         "instead of the census's definitions (refuses a dirty tree; an unprovable kept "
                         "definition counts as a blocker; ~minutes; never a census verdict)")
    ap.add_argument("--hook", action="store_true",
                    help="report-only mode for a git hook: compiles only the checked files (never a definer: "
                         "--compile-limit 0), gives up after --deadline seconds with LINKED PREVIEW UNKNOWN "
                         "(timeout), says LINKED PREVIEW UNKNOWN when unstaged or untracked inputs differ from the "
                         "staged state or on any error, always exits 0")
    ap.add_argument("--deadline", type=float, default=None, metavar="S",
                    help=f"with --hook: wall-clock limit in seconds (default {HOOK_DEADLINE:.0f})")
    ap.add_argument("--compile-limit", type=int, default=None, metavar="N",
                    help=f"compile at most N missing or stale definers of changed names (default "
                         f"{REFRESH_COMPILE_LIMIT}; 0 never); past it those names are LINKED PREVIEW UNKNOWN")
    ap.add_argument("--refresh-compile", action="store_true",
                    help=f"with --refresh: compile more than {REFRESH_COMPILE_LIMIT} stale or missing objects "
                         "(a cold worktree: the whole tree)")
    ap.add_argument("--publish", metavar="CSV", nargs="?", const=str(QUEUE),
                    help=f"write the queue's top {QUEUE_LIMIT} rows (default {QUEUE.relative_to(ROOT).as_posix()})")
    if "--hook" in argv:
        # report-only: a usage error is UNKNOWN and exit 0, never argparse's exit 2
        try:
            args = ap.parse_args(argv)
        except SystemExit as error:
            if error.code in (0, None):
                return 0
            files = [a for a in argv if not a.startswith("-")]
            for path in files or ["link_check --hook"]:
                print(f"{path}: LINKED PREVIEW UNKNOWN (bad arguments: {' '.join(argv)})")
            return 0
        if not args.paths:
            print("link_check --hook: LINKED PREVIEW UNKNOWN (no files given)")
            return 0
        return hook_main(args)
    args = ap.parse_args(argv)
    if not args.paths and not args.next and not args.publish:
        ap.error("give sources, --next, --publish or `next`")
    # BUILD_RECOMPILE_ONLY trusts every object it is not told to rebuild: a
    # stale checked object would be judged as current; CL/_CL_ would change
    # the compile itself (the pre-commit hook unsets all three)
    for name in ("BUILD_RECOMPILE_ONLY", "CL", "_CL_"):
        os.environ.pop(name, None)
    if args.deadline is not None:
        ap.error("--deadline needs --hook")
    started = time.time()
    index = load_index()
    if args.publish:
        publish(index, Path(args.publish))
    if args.next:
        next_names(index, args.limit)
    if not args.paths:
        return 0
    require_common_index(index)
    ledger = link_census.ledger()
    truth = link_census.RetailTruth(ledger)
    if args.refresh_compile and not args.refresh:
        ap.error("--refresh-compile needs --refresh")
    if args.refresh:
        if args.census_only:
            ap.error("--refresh and --census-only are opposites")
        refresh_current(index, args.paths, allow_compile=args.refresh_compile)
    rows_of = collections.defaultdict(list)
    for row in ledger or ():
        rows_of[row["source"]].append(row)
    resolved = list({obj.resolve(): (source, obj) for source, obj in
                     (resolve(path, index) for path in args.paths)}.values())  # a file named twice counts once
    outside = sorted(source or obj.name for source, obj in resolved if obj.name not in index["objects"])
    if outside:
        # A file added after the census goes where the census would link it
        # (link_census.link_order: the lowest retail RVA of its matched rows),
        # since which definition is first decides duplicates and COMDAT
        # selection. Then it is judged like a census file.
        order = [path.name for path in link_census.link_order(ledger or (), link_census.data_ledger())]
        unplaced = sorted(source or obj.name for source, obj in resolved
                          if obj.name not in index["objects"] and obj.name not in order)
        if unplaced:
            raise SystemExit(f"link_check: new since census {index['meta'].get('commit', '?')} and no matched "
                             f"ledger or data row places it in link order, so not previewable: "
                             f"{', '.join(unplaced)}")
        place_new(index, [obj.name for _, obj in resolved if obj.name not in index["objects"]], order)
        print(f"link_check: new since census {index['meta'].get('commit', '?')}, previewed at its link-order "
              f"place: {', '.join(outside)}")
    if not args.census_only:
        # the LINKED-claim rule: refresh what the checked files' changed names need
        if index.get("refreshed"):
            refresh(index, [obj for _, obj in resolved], truth)
        else:
            apply_selection_rule(index, [obj for _, obj in resolved], truth, ledger,
                                 compile_limit=args.compile_limit)
    elif outside:
        # The census holds no definitions for a new file: its current object is all there is.
        refresh(index, [obj for source, obj in resolved if (source or obj.name) in outside], truth)
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
        if not index.get("refreshed") and not hook:     # a refreshed or hook preview is not the census's verdict
            note_evaluated(rows_of.get(source, ()), index["meta"].get("commit", ""))
        entry = index["blockers"].get(source or "", {})
        before += index["bytes"].get(source, 0) if entry.get("linked") else 0
        after += result.get("after_bytes", now.get(source, 0) if clean[-1] else 0)
    print(f"link_check: {sum(clean)} of {len(clean)} link cleanly; LINKED {before:,} -> {after:,} bytes "
          f"({time.time() - started:.1f}s)")
    return 0 if all(clean) else 1


if __name__ == "__main__":
    sys.exit(main())
