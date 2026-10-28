#!/usr/bin/env python3
"""Rank COMDAT repair hypotheses; never rewrite source, ledgers or link order.

A family is ONE exact decorated template/member name and ALL its definers and
consumers, not a ledger row. Different names are never merged because their
bytes agree (COMDAT selection is not ICF). ``next`` uses link_check's name claim
key, sharing its lease with the ordinary linking queue. Owner-held families
are report-only. Reports are census diagnostics, never LINKED verdicts.

  python3 tools/comdat_families.py ranked --index build/link_census/link_index.pkl
  python3 tools/comdat_families.py next --index ... --bfme2 /read/only/bfme2

JSON goes to stdout; redirect it to build/comdat_families/ if desired. The only
mutation is an explicitly requested ``next`` lease through claims.py. Pickles
must be trusted local BFME1 census artifacts. No compiler/linker is invoked.
Byte agreement does not prove a name: frozen ILT contradictions at claimed
real-name homes veto provider recommendations. Fits are only corroboration;
opaque spellings deliberately do not claim retail's original symbol name.
"""
import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import pickle
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import link_check
import link_census
import progress

BLOCKER_KINDS = ("unresolved", "duplicates", "losers", "wrong_selected", "alias_target", "alias_unknown")
HYPOTHESIS = ("Declaration-only explicit specialization may suppress a wrong local COMDAT and bind "
              "consumers to the retail-proven provider. Review identity, ABI and selected copy, then gate; "
              "never reorder the ledger or change a matched body to make linking green.")


def merge_intervals(intervals):
    return progress.merge_intervals(intervals)


def interval_bytes(intervals):
    return sum(high - low for low, high in merge_intervals(intervals))


def blocked_names(entry):
    return {name for kind in BLOCKER_KINDS for name in entry.get(kind, ())}


def candidate_names(index):
    return {name for entry in index["blockers"].values() if not entry["linked"]
            for kind in ("losers", "wrong_selected", "duplicates")
            for name in entry.get(kind, ()) if name in index["comdat"]}


def source_intervals(root, sources):
    """Stream/filter the ledger; retain only requested matched source rows.

    Reuse BFME1's provenance and naked-body classification; clip to retail
    .text and remove 0xCC padding. Counts are diagnostic authored/vendored
    bytes affected, not an additive prediction of bytes that will link.
    """
    rows = []
    with (root / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["source"] in sources and row["status"] == "matched":
                rows.append(row)
    matched = {(r["name"], r["target_rva"]): (int(r["target_size"]), r["source"]) for r in rows}
    texts = {s: (root / s).read_text(encoding="utf-8", errors="replace") for s in sources
             if (root / s).is_file() and Path(s).suffix.lower() in progress.CPP_SUFFIXES}
    naked = progress.naked_cpp_rows(matched, texts)
    start, image = progress._text_image()
    out = collections.defaultdict(list)
    for row in rows:
        key = row["name"], row["target_rva"]
        if progress.source_lane(row["source"], row.get("notes", ""), key in naked) not in progress.DECOMPILED_LANES:
            continue
        low = max(int(row["target_rva"], 16), start)
        high = min(int(row["target_rva"], 16) + int(row["target_size"]), start + len(image))
        # Represent real bytes as intervals so overlaps across rows AND families
        # are still removed by the same union operation.
        for match in re.finditer(b"[^\\xcc]+", image[low - start:high - start] if low < high else b""):
            out[row["source"]].append((low + match.start(), low + match.end()))
    return {source: merge_intervals(parts) for source, parts in out.items()}


def _signature(text):
    """Conservative lexical normalization, not a C++ parser or identity proof."""
    text = re.sub(r"\b(public|private|protected):|\b(class|struct|enum|__thiscall|__cdecl|__stdcall|__fastcall)\b", "", text)
    # MSVC's demangler repeats template arguments on ctor/dtor names; C++
    # explicit-specialization declarations spell only vector::~vector().
    for match in reversed(list(re.finditer(r"::~?[A-Za-z_]\w*<", text))):
        begin = text.index("<", match.start())
        depth, end = 1, begin + 1
        while end < len(text) and depth:
            depth += (text[end] == "<") - (text[end] == ">")
            end += 1
        if not depth:
            text = text[:begin] + text[end:]
    return re.sub(r"\s+", "", text).replace("(void)", "()")


def bfme2_patterns(root, names):
    """Find exact decorated annotations or unambiguous decl-only signatures.

    Truncated decorated comments are NOT prefix matches. Marker-only files
    can be recognized with llvm-undname, a native read-only demangler. If it
    is unavailable those cases remain unknown, rather than guessed.
    """
    if root is None:
        return {}, {"status": "not supplied", "demangler": False}
    code = root / "Code"
    if not code.is_dir():
        raise ValueError(f"BFME2 Code directory does not exist: {code}")
    signatures = collections.defaultdict(set)
    demangler = shutil.which("llvm-undname")
    demangle_errors = 0
    if demangler and names:
        ordered = sorted(names)
        done = subprocess.run([demangler], input="\n".join(ordered) + "\n", capture_output=True, text=True, check=False)
        # llvm-undname returns 1 if even one input has unsupported/malformed
        # decoration. Its other output is still usable; never invent that name.
        if done.returncode not in (0, 1):
            raise ValueError(f"llvm-undname failed: {done.stderr.strip()}")
        demangle_errors = done.stderr.count("error:")
        lines = done.stdout.splitlines()
        for i, line in enumerate(lines[:-1]):
            if line in names and lines[i + 1].strip() and not lines[i + 1].startswith("error"):
                signatures[_signature(lines[i + 1])].add(line)
    result = collections.defaultdict(list)
    marker_files = 0
    for path in sorted(code.rglob("*.cpp")):
        text = path.read_text(encoding="utf-8", errors="replace")
        if "decl-only" not in text and "declaration-only" not in text:
            continue
        marker_files += "bfme link decl-only" in text
        lines = text.splitlines()
        active = False
        for number, line in enumerate(lines, 1):
            if "bfme link decl-only begin" in line:
                active = True
            elif "bfme link decl-only end" in line:
                active = False
            # Full decorated-name comments must be followed by a declaration,
            # not a template body. These also cover specializations outside blocks.
            if "non-retail copy of " in line:
                symbol = line.split("non-retail copy of ", 1)[1].rstrip().rstrip(":")
                following = []
                for candidate in lines[number:number + 4]:
                    if candidate.lstrip().startswith("//") or not candidate.strip():
                        continue
                    following.append(candidate)
                    if "template" in candidate or "{" in candidate:
                        break
                declaration = " ".join(following)
                if symbol in names and re.search(r"template\s*<>[^;{}]+;", declaration):
                    result[symbol].append({"file": path.relative_to(root).as_posix(), "line": number,
                                           "evidence": "exact decorated-name annotation + declaration"})
            if not active or "template" not in line:
                continue
            # Only complete one-line declarations in an explicit namespace are
            # recognized. Keep all qualification: no type-name substitution.
            match = re.fullmatch(r"\s*namespace (\w+)\s*\{\s*template\s*<>\s*([^{};]+);\s*\}\s*", line)
            if not match:
                continue
            namespace, declaration = match.groups()
            # Add scope to the owner, retaining return type and argument types.
            # Restrict to builtin-only declarations: unqualified user types or
            # nested template argument scopes cannot be resolved lexically.
            if namespace != "_STL":
                continue
            tokens = set(re.findall(r"[A-Za-z_]\w*", declaration))
            allowed = {"void", "bool", "char", "short", "int", "long", "unsigned", "signed", "float", "double", "const",
                       "vector", "allocator", "_Vector_base", "_STLP_alloc_proxy"}
            if tokens - allowed:
                continue
            qualified = re.sub(r"\b(vector|allocator|_Vector_base|_STLP_alloc_proxy)(?=\s*<)", r"_STL::\1", declaration)
            sig = _signature(qualified)
            # An ambiguous signature is not an exact-name hit.
            hits = signatures.get(sig, set())
            if len(hits) == 1:
                result[next(iter(hits))].append({"file": path.relative_to(root).as_posix(), "line": number,
                                                "evidence": "exact normalized builtin specialization signature"})
    return dict(result), {"status": "scanned", "marker_files": marker_files, "demangler": bool(demangler), "demangle_errors": demangle_errors,
                          "scope": "exact annotations and builtin-only one-line marker declarations; other cases unknown"}


def census_consumers(index, names, objects_dir=None):
    """Read hash-bound COFF symbol tables when available, never build objects.

    The portable index has blockers but no full reference graph. Missing or
    changed object payloads are explicitly incomplete evidence, not empty
    reference sets. Relocated objects must match the census inventory hash.
    """
    refs = collections.defaultdict(set)
    counts = collections.Counter()
    for obj in index["objects"]:
        record = index.get("weak_inventory", {}).get(obj)
        if not record:
            counts["missing_inventory"] += 1
            continue
        original, digest = record
        path = objects_dir / obj if objects_dir else Path(original)
        try:
            data = path.read_bytes()
        except OSError:
            counts["missing_objects"] += 1
            continue
        if hashlib.sha256(data).hexdigest() != digest:
            counts["changed_objects"] += 1
            continue
        for symbol in link_census._coff_symbols(data):
            if symbol["section"] == 0 and symbol["storage"] in (2, 105) and symbol["name"] in names:
                refs[symbol["name"]].add(obj)
        counts["verified_objects"] += 1
    return refs, {"complete": counts["verified_objects"] == len(index["objects"]), **dict(counts)}


def model_tier(name, provider, pattern, selected_verdict, strong):
    if re.match(r"^\?\?(_[GE]|1)", name) or re.search(r"unwind|ehvec|catch|dtor", name, re.I):
        return "Astra XHigh", "destructor/EH/deleting-destructor emission needs specialist review"
    if provider is None:
        return "Sol High", "provider analysis needed"
    if strong or selected_verdict == "unknown" or name.startswith(("??_", "__")):
        return "Astra High", "compiler/ABI or mixed strong/COMDAT question"
    if pattern:
        return "Luna Medium", "established decl-only pattern; repair remains a hypothesis"
    return "Sol High", "provider/consumer specialization analysis needed"


def retail_homes(root, names):
    """Read only the requested identities; pins alone are not proven homes."""
    homes = collections.defaultdict(set)
    if not names:
        return homes
    with (root / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row.get("status") != "matched" or "icf-owner=" in (row.get("notes") or ""):
                continue
            identities = {row["name"]}
            if "gen-alias" not in (row.get("notes") or ""):
                identities.add(link_census.build.ledger_object_symbol(row))
            for name in identities & names:
                homes[name].add(int(row["target_rva"], 16))
    data = root / "targets/game/reverse/data_rows.csv"
    if data.is_file():
        with data.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                if row.get("status") == "matched" and row["name"] in names:
                    address = int(row["address"], 16)
                    homes[row["name"]].add(address - 0x400000 if row["address_kind"] == "va" else address)
    return homes


def identity_checks(root, homes):
    """Check names at their claimed homes, independently of matching bytes.

    An ILT fit is corroboration, never identity proof. A contradiction prevents
    offering that name's byte-matching copy as a canonical repair provider.
    """
    from ilt_oracle import Oracle, tier
    path = root / "targets/game/reverse/ilt_windows.tsv"
    oracle = Oracle(path) if path.is_file() else None
    result = {}
    for name, addresses in homes.items():
        checks = []
        for rva in sorted(addresses):
            if tier(name) != "real":
                verdict, chance, reason = "NOT_APPLICABLE", None, "opaque/invented spelling does not claim a retail symbol name"
            else:
                verdict, chance, reason = (oracle.check(name, rva) if oracle else
                                          ("UNAVAILABLE", None, "frozen ILT windows missing"))
            checks.append({"rva": f"0x{rva:08X}", "verdict": verdict,
                           "p_false": chance, "reason": reason})
        result[name] = checks
    return result


def analyze(index, intervals, patterns=None, references=None, reference_scan=None, homes=None,
            identities=None):
    """Pure analysis over the BFME1 census tables. Does not open/write files."""
    patterns = patterns or {}
    references = references or {}
    homes = homes or {}
    identities = identities or {}
    sources = collections.defaultdict(list)
    affected = collections.defaultdict(set)
    for source, entry in index["blockers"].items():
        sources[entry["object"]].append(source)
        if not entry["linked"]:
            for name in blocked_names(entry):
                affected[name].add(source)
    families = []
    selection = index.get("selection", {})
    for name in sorted(candidate_names(index)):
        copies = sorted(index["comdat"][name])  # numeric object indices ARE link order
        loses, rule = link_census.keep_rule(copies)
        exclusive = set(index["strong"].get(name, ()))
        definers = {i for i, _, _ in copies} | exclusive
        # Unlike kept_definition's preview fallback, preserve a missing actual
        # MAP holder (exception None) as unknown for judge_selected.
        selected = selection.get("exceptions", {}).get(name, min(definers))
        selected_verdict = link_census.judge_selected(
            selected, {i: (digest, verdict) for i, digest, verdict in copies}, definers, exclusive,
            {i for i in definers if index["objects"][i] in selection.get("owners", {}).get(name, ())})

        def unit(i, digest=None, verdict=None):
            obj = index["objects"][i]
            return {"object": obj, "sources": sorted(sources[obj]), "link_order": i,
                    "digest": digest, "retail_verdict": verdict}

        proven = [unit(i, d, v) for i, d, v in copies if v == "retail"]
        # RetailTruth's verdict is existential over candidate homes. Distinct
        # retail digests cannot establish one provider, even without the ledger
        # on an offline reader. Several proven addresses are ambiguous even
        # when their bytes happen to agree (retail did not use ICF).
        ambiguous = len({p["digest"] for p in proven}) > 1 or len(homes.get(name, ())) > 1
        checks = identities.get(name, [])
        contradicted = any(c["verdict"] == "CONTRADICTED" for c in checks)
        # Prefer the proven ledger owner's TU, then the first proven copy.
        proven.sort(key=lambda p: (p["object"] not in selection.get("owners", {}).get(name, ()), p["link_order"]))
        provider = proven[0] if proven and not ambiguous and not contradicted else None
        if provider:
            provider = {**provider, "evidence": "census RetailTruth: bytes and relocations match a claimed home; name identity needs independent evidence",
                        "ledger_owner": provider["object"] in selection.get("owners", {}).get(name, ()),
                        "truth_fingerprint": index.get("weak_truth"), "census": index.get("meta", {})}
        wrong = [unit(i, d, v) for i, d, v in copies if v == "wrong"]
        owner = link_check.family_of(name)
        spans = merge_intervals([part for source in affected[name] for part in intervals.get(source, ())])
        # A family must cover ALL other blockers to call bytes conditional gain.
        ready = {s for s in affected[name] if blocked_names(index["blockers"][s]) <= {name}
                 and not index["blockers"][s].get("addresses")}
        ready_spans = merge_intervals([part for s in ready for part in intervals.get(s, ())])
        status = ("identity contradicted — needs analysis" if contradicted else
                  "ambiguous provider — needs analysis" if ambiguous else "owner-held" if owner
                  else "needs provider analysis" if not provider else "provider proven")
        pattern = patterns.get(name, [])
        consumer_objects = sorted(references.get(name, ()))
        consumers = affected[name] | {s for obj in consumer_objects for s in sources[obj]}
        tier, reason = model_tier(name, provider, pattern, selected_verdict, exclusive)
        families.append({"family": name, "claim_key": f"0x{link_check.claim_key(name):08X}",
                         "status": status, "owner_family": owner or None,
                         "retail_homes": [f"0x{rva:08X}" for rva in sorted(homes.get(name, ()))],
                         "ambiguous_provider": ambiguous,
                         "identity_oracle": checks, "identity_contradicted": contradicted,
                         "identity_note": "ILT fits corroborate names; they do not prove identity. Contradictions veto provider recommendations.",
                         "canonical_provider": provider, "proven_copies": proven,
                         "definers": [unit(i, d, v) for i, d, v in copies] + [unit(i, verdict="strong") for i in sorted(exclusive - {j for j, _, _ in copies})],
                         "wrong_emitters": wrong,
                         "keep_rule": rule, "losing_objects": [index["objects"][i] for i in sorted(loses) if loses[i]],
                         "selected_object": index["objects"][selected] if selected in definers else None,
                         "selected_verdict": selected_verdict,
                         "consumer_units": sorted(consumers), "consumer_objects": consumer_objects,
                         "unmapped_consumer_objects": [o for o in consumer_objects if not sources[o]],
                         "consumer_scope": "census blocker participants plus hash-verified COFF undefined references; includes emitters",
                         "affected_units": sorted(affected[name]),
                         "bytes_blocked": interval_bytes(spans), "blocked_intervals": spans,
                         "conditional_single_family_bytes": interval_bytes(ready_spans),
                         "bfme2_pattern": bool(pattern), "bfme2_evidence": pattern,
                         "bfme2_pattern_status": "exact evidence found" if pattern else "not established by bounded lookup",
                         "repair_applicability": "template specialization hypothesis" if "?$" in name else "non-template name; decl-only applicability unestablished",
                         "confidence": status if ambiguous or contradicted else "needs provider analysis" if not provider else "established pattern" if pattern else "provider proven; repair unestablished",
                         "suggested_model_tier": tier, "tier_reason": reason,
                         "servable": bool(provider and wrong and "?$" in name and not owner and not exclusive and selected_verdict != "unknown"),
                         "hypothesis": ("Resolve the contradicted name/home identity before selecting a provider; "
                                        "matching bytes cannot establish ownership." if contradicted else HYPOTHESIS)})
    families.sort(key=lambda f: (-f["bytes_blocked"], f["family"]))
    total = interval_bytes([span for f in families for span in f["blocked_intervals"]])
    return {"schema": "bfme1-comdat-families-1", "census": index.get("meta", {}),
            "diagnostic_only": True, "consumer_scan": reference_scan or {"complete": False, "status": "not supplied"},
            "bytes_blocked_unique": total,
            "bytes_note": "authored/vendored retail .text excluding 0xCC; affected bytes, not guaranteed gain; family counts overlap",
            "families": families}


def serve(report, *, no_claim=False):
    """Claim an entire exact-name family using the existing queue lease.

    Fail closed on relevant source/header/ledger/tool movement since census,
    including unstaged and untracked inputs. Fresh census provenance and a
    normal gate remain required before any repair can land.
    """
    import claims
    commit = report["census"].get("commit")
    if not commit:
        raise ValueError("next needs a census commit")
    tip = claims._fetch_master()
    if not tip:
        raise ValueError("cannot fetch origin/master; nothing claimed")
    changed = set()
    for args in (("diff", "--name-only", commit, tip), ("diff", "--name-only", commit, "HEAD"),
                 ("diff", "--name-only", "HEAD"), ("ls-files", "--others", "--exclude-standard")):
        changed.update(link_check._git(*args, check=True).splitlines())
    # Shared inputs can change all copies, not just a single consumer TU.
    if any(p.startswith(("game/", "inputs/", "tools/", "targets/game/reverse/")) or Path(p).suffix.lower() in
           (".h", ".hpp", ".inl", ".inc") for p in changed):
        raise ValueError("shared inputs changed since census; refresh before serving")
    linked, _, _ = link_check.linked_since(commit)
    landed = {int(k, 16) for k, _ in claims.LEASE_TRAILER.findall(link_check._git(
        "log", "--format=%B", "--grep=^Claim-Lease:", f"{commit}..{tip}", check=True))}
    held = claims.active()
    for family in report["families"]:
        if not family["servable"]:
            continue
        units = {s for d in family["definers"] for s in d["sources"]} | set(family["consumer_units"])
        if any(not d["sources"] for d in family["definers"]) or units & changed or units & set(linked):
            continue
        key = int(family["claim_key"], 16)
        if key in held or key in landed:
            continue
        result = {**family}
        if not no_claim:
            got = claims.claim([key], note=f"comdat family:{family['family']}")
            if key not in got.claimed:
                continue
            result["claim_trailer"] = claims.trailer(key, got.leases[key])
        return result
    return None


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("ranked", "next"))
    parser.add_argument("--index", type=Path, default=link_check.INDEX)
    parser.add_argument("--bfme2", type=Path, help="read-only BFME2 clone for exact-name pattern evidence")
    parser.add_argument("--objects-dir", type=Path, help="read-only relocated census objects, verified by inventory hash")
    parser.add_argument("--limit", type=int, default=10, help="ranked families to print; 0 means all")
    parser.add_argument("--no-claim", action="store_true", help="next: inspect without writing any claim")
    args = parser.parse_args(argv)
    if args.limit < 0:
        parser.error("--limit must be nonnegative")
    try:
        with args.index.open("rb") as handle:
            index = pickle.load(handle)
        names = candidate_names(index)
        wanted = {source for source, e in index["blockers"].items() if not e["linked"] and blocked_names(e) & names}
        intervals = source_intervals(ROOT, wanted)
        patterns, scan = bfme2_patterns(args.bfme2, names)
        references, reference_scan = census_consumers(index, names, args.objects_dir)
        homes = retail_homes(ROOT, names)
        report = analyze(index, intervals, patterns, references, reference_scan, homes,
                         identity_checks(ROOT, homes))
        report["bfme2_lookup"] = scan
        report["index"] = str(args.index.resolve())
        if args.command == "next":
            picked = serve(report, no_claim=args.no_claim)
            print(json.dumps({"census": report["census"], "family": picked}, indent=2))
            return 0 if picked else 1
        report["family_count"] = len(report["families"])
        if args.limit:
            report["families"] = report["families"][:args.limit]
        print(json.dumps(report, indent=2))
        return 0
    except (OSError, ValueError, KeyError, pickle.UnpicklingError) as exc:
        parser.exit(2, f"comdat_families: {exc}\n")


if __name__ == "__main__":
    raise SystemExit(main())
