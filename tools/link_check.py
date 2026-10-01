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
  python3 tools/link_check.py near [--max K] [--shared]   # files that link once calls use the row names

THE QUEUE. The daily census publishes --next's ranking as link_queue.csv (no
index needed to read it), and `next` serves its best row that is not claimed,
not landed since the census (a Claim-Lease trailer for its key) and whose
files have not changed since the census. Names in a family (FAMILIES) have one
owner each and are served only with `next --family F`.
"""
import argparse
import collections
import csv
import hashlib
import json
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
COMMON_SCHEMA = 1
WEAK_SCHEMA = 4
ALIAS_SCHEMA = 1
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


def write_index(present, facts, blockers, excuses, meta, selection, *, publish=True, aliases=None):
    """Called by link_census.write_status: what a per-file check needs from the
    census, in one pickle. `facts` is link_census.read_facts(present);
    `selection` holds link_census.selection_verdicts' results, holder
    exceptions and ledger owners; `aliases` link_census.alias_blockers'
    {alias: [(object index, target)]} (read from the objects when None)."""
    index = {"meta": meta, **index_tables(present, facts, selection, aliases), "blockers": blockers,
             "excuses": excuses, "bytes": source_bytes(set(blockers))}
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
    if index.get("common_schema") != COMMON_SCHEMA or not isinstance(index.get("common"), dict):
        raise SystemExit("link_check: census index lacks complete COMMON providers; rebuild it with "
                         "python3 tools/link_census.py --build --history")


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


def refresh(index, objects, truth):
    """Replace the census's definitions of `objects` with their current
    object files', so a fix in one file (a removed duplicate, a new datum) is
    seen when checking the others. Blockers of files not passed stay as the
    census saw them."""
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


def check_object(obj, index, truth, source=None, judge=None):
    """{unresolved, duplicates, comdat, addresses, selected, alias_target} for one object against the index."""
    import alias_guard
    import link_debt
    require_common_index(index)
    data = _object_bytes(obj)
    common = link_census.common_definitions(obj, data=data)
    copies, defined, undefined, weaks = link_census.object_facts(
        obj, truth, data=data, weak_context=weak_context(index, truth))
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
    alias_why = {}
    if judged:
        judge = judge or alias_judge()
        for alias, target in judged:
            verdict, why = judge.verdict(alias, target)
            if verdict == "wrong":
                alias_why[f"{alias}={target}"] = why
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
            "selected": wrong_selected(obj, (copies, defined, undefined, weaks), own, position, index,
                                       common_names=common),
            "alias_target": sorted(alias_why), "alias_why": alias_why}


def wrong_selected(obj, fact, own, position, index, *, common_names=()):
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
    clean = not any(result.get(kind) for kind in ("unresolved", "duplicates", "comdat", "addresses", "selected",
                                                   "alias_target"))
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
    for name in result.get("alias_target", ()):
        print(f"  alias_target {name}  (/alternatename binds the call to another body: "
              f"{result.get('alias_why', {}).get(name, '')})")
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
                 | set(entry.get("wrong_selected", ())) | set(entry.get("alias_target", ())))
        if entry["addresses"]:
            names.add(ADDRESSES)
        if len(names) == 1:
            name = names.pop()
            gain[name] += index["bytes"].get(source, 0)
            files[name].append(source)
    kinds = {}
    for entry in index["blockers"].values():
        for kind in ("unresolved", "duplicates", "losers", "wrong_selected", "alias_target"):
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


NEAR_BLOCKING = ("duplicates", "losers", "wrong_selected", "alias_target")


def near_rows(index, judge, most=None, under=""):
    """Unlinked files whose every blocker is an unresolved call name a
    respelling fixes: the name is pinned, and the ledger row at its pinned
    address (alias_guard.Judge.respell) is a C++ definition that passes the
    alias check. Largest first: [{source, bytes, fixes: [(name, row name, note)]}]."""
    rows = []
    for source, entry in index["blockers"].items():
        if entry["linked"] or not source.startswith(under) or entry["addresses"]:
            continue
        if any(entry.get(kind) for kind in NEAR_BLOCKING):
            continue
        names = entry["unresolved"]
        if not names or (most and len(names) > most):
            continue
        fixes = []
        for name in names:
            target, note = judge.respell(name)
            if target is None:
                break
            fixes.append((name, target, note))
        else:
            rows.append({"source": source, "bytes": index["bytes"].get(source, 0), "fixes": fixes})
    rows.sort(key=lambda row: (-row["bytes"], row["source"]))
    return rows


def near(argv):
    """`link_check.py near`: files that link once their calls are respelled to
    the ledger's row names (the call-by-row-name lane), with each respelling.
    Every respelling comes from this tree's symbols.csv and functions.csv:
    the row at the call name's pinned address. Declare that row's function
    and call it; never alias it (/alternatename) unless an ABI shape forces it."""
    ap = argparse.ArgumentParser(prog="link_check.py near", description=near.__doc__)
    ap.add_argument("--max", type=int, default=0, help="only files with at most this many blockers")
    ap.add_argument("--under", default="", help="only sources under this path prefix")
    ap.add_argument("--limit", type=int, default=30)
    ap.add_argument("--shared", action="store_true",
                    help="rank respellings by the near files' bytes they appear in (a shared declaration fix)")
    args = ap.parse_args(argv)
    index = load_index()
    census = index["meta"].get("commit", "")
    changed = set(_git("diff", "--name-only", census, "HEAD").split()) if census else set()
    rows = near_rows(index, alias_judge(), args.max, args.under)
    print(f"files every blocker of which a call respelling fixes (census {index['meta'].get('date', '?')} at "
          f"{census or '?'}): {len(rows):,} files, {sum(r['bytes'] for r in rows):,} bytes")
    if args.shared:
        gain, files = collections.Counter(), collections.Counter()
        for row in rows:
            for fix in row["fixes"]:
                gain[fix[:2]] += row["bytes"] / len(row["fixes"])
                files[fix[:2]] += 1
        for (name, target), value in gain.most_common(args.limit):
            print(f"  {int(value):>8,} {files[name, target]:>4} files  {name}\n      -> {target}")
        return 0
    for row in rows[:args.limit]:
        stale = "  (changed since the census: recheck)" if row["source"] in changed else ""
        print(f"  {row['bytes']:>7,}  {row['source']}{stale}")
        for name, target, note in row["fixes"]:
            print(f"      {name}\n        -> {target}{f'  [{note}]' if note else ''}")
    return 0


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if argv[:1] == ["next"]:
        return serve(argv[1:])
    if argv[:1] == ["near"]:
        return near(argv[1:])
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
    require_common_index(index)
    truth = link_census.RetailTruth(link_census.ledger())
    resolved = list({obj.resolve(): (source, obj) for source, obj in
                     (resolve(path, index) for path in args.paths)}.values())  # a file named twice counts once
    outside = sorted(source or obj.name for source, obj in resolved if obj.name not in index["objects"])
    if outside:
        # Its link position is unknown, so neither its own duplicates nor what
        # it provides to others can be judged: two new objects defining one
        # exclusive symbol both looked clean while link.exe fails LNK2005.
        raise SystemExit(f"link_check: not in census {index['meta'].get('commit', '?')}, so not previewable "
                         f"(the next census measures it): {', '.join(outside)}")
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
