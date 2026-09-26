#!/usr/bin/env python3
"""Export or audit WorldBuilder's optional Ghidra inventory without claiming matches."""
import argparse
from collections import Counter
import csv
import hashlib
import json
import os
from pathlib import Path
import subprocess

from targets import load_target
from worldbuilder_inventory import extract_editor_candidates, require, text_sha256


SCRIPTS = ("tools/ghidra/list_functions.java", "tools/ghidra/list_string_xrefs.java",
           "tools/ghidra/worldbuilder_analysis.java")
ARTIFACTS = ("ghidra_functions.csv", "string_xrefs.tsv", "function_ranges.tsv", "calls.tsv",
             "string_references.tsv", "analysis_metadata.tsv")


def table(path):
    with path.open(encoding="utf-8", newline="") as stream:
        yield from csv.DictReader(stream, delimiter="\t", quoting=csv.QUOTE_NONE)


def text_fingerprint(path):
    digest = hashlib.sha256()
    with path.open(encoding="utf-8") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), ""):
            digest.update(chunk.encode("utf-8"))
    return digest.hexdigest()


def script_fingerprints(root):
    return {name: text_sha256(root / name) for name in SCRIPTS}


def export(target, directory, ghidra, analyze):
    require(ghidra is not None, "Export requires --ghidra <installation-directory>")
    launcher = ghidra / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
    require(launcher.is_file(), f"Missing Ghidra launcher: {launcher}")
    project = directory / "project"
    exists = (project / "worldbuilder.gpr").is_file()
    require(not exists if analyze else exists,
            "Project already exists; use --export" if analyze else "Project absent; use --analyze for the first import")
    project.mkdir(parents=True, exist_ok=True)
    command = [str(launcher), str(project), "worldbuilder"]
    if analyze:
        command += ["-import", str(target.image_path), "-max-cpu", "2", "-analysisTimeoutPerFile", "1200"]
    else:
        command += ["-process", "worldbuilder.exe", "-noanalysis", "-readOnly"]
    command += ["-scriptPath", str(target.root / "tools/ghidra"),
                "-postScript", "list_functions.java", str(directory / "ghidra_functions.csv"),
                "-postScript", "list_string_xrefs.java", str(directory / "string_xrefs.tsv"),
                "-postScript", "worldbuilder_analysis.java", str(directory)]
    log = directory / ("analysis.log" if analyze else "export.log")
    print(f"{'Analyzing' if analyze else 'Exporting'} WorldBuilder; log: {log}", flush=True)
    with log.open("w", encoding="utf-8") as stream:
        result = subprocess.run(command, cwd=target.root, stdout=stream, stderr=subprocess.STDOUT)
    require(result.returncode == 0, f"Ghidra exited {result.returncode}; inspect {log}")
    metadata = {r["key"]: r["value"] for r in table(directory / "analysis_metadata.tsv")}
    require(metadata["program_sha256"] == target.expected_sha256, "Ghidra project belongs to a different binary")
    receipt = dict(binary_sha256=target.expected_sha256, scripts=script_fingerprints(target.root),
                   artifacts={name: text_fingerprint(directory / name) for name in ARTIFACTS},
                   ghidra_properties_sha256=text_sha256(ghidra / "Ghidra/application.properties"))
    (directory / "export_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8", newline="\n")


def parse_ranges(value):
    result = [tuple(int(x, 16) for x in part.split(":")) for part in value.split(";")]
    require(all(len(pair) == 2 and pair[0] <= pair[1] for pair in result), "Invalid Ghidra address range")
    require(all(left[1] < right[0] for left, right in zip(result, result[1:])), "Overlapping Ghidra owned ranges")
    return result


def boundary_verdict(rva, size, ranges, owned):
    if ranges is None:
        return "missing_function_start"
    require(sum(end - start + 1 for start, end in ranges) == owned, "Ghidra owned-address count disagrees with exported ranges")
    return "exact_contiguous" if ranges == [(rva, rva + size - 1)] and owned == size else "different_owned_ranges"


def audit(target, directory):
    receipt_path = directory / "export_receipt.json"
    require(receipt_path.is_file(), "No analysis export receipt; run --export against the existing project, or --analyze on a fresh checkout")
    receipt = json.loads(receipt_path.read_text(encoding="utf-8"))
    require(receipt["binary_sha256"] == target.expected_sha256, "Analysis receipt has the wrong target binary")
    require(receipt["scripts"] == script_fingerprints(target.root), "Ghidra export scripts changed; rerun --export")
    fingerprints = {name: text_fingerprint(directory / name) for name in ARTIFACTS}
    require(receipt["artifacts"] == fingerprints, "Analysis artifacts changed after export; rerun --export")
    metadata = {row["key"]: row["value"] for row in table(directory / "analysis_metadata.tsv")}
    require(metadata["program_sha256"] == target.expected_sha256, "Ghidra project hash disagrees with target")
    candidates = extract_editor_candidates(target)
    expected = {c["target_rva"]: c for c in candidates}
    starts, counts, noncontiguous = {}, Counter(), []
    for row in table(directory / "function_ranges.tsv"):
        rva, owned = int(row["entry_rva"], 16), int(row["owned_bytes"])
        ranges = parse_ranges(row["ranges"])
        require(sum(end - start + 1 for start, end in ranges) == owned, f"Owned-range inconsistency at {rva:#x}")
        counts["functions"] += 1
        counts["sum_owned_address_counts_not_coverage"] += owned
        if len(ranges) > 1:
            counts["noncontiguous_functions"] += 1
            if len(noncontiguous) < 5:
                noncontiguous.append(dict(entry_rva=rva, owned_bytes=owned, range_count=len(ranges),
                                          ranges=ranges[:8], verdict="unverified; owned count must not be used as a contiguous size"))
        if rva in expected:
            starts[rva] = dict(owned_bytes=owned, ranges=ranges)
    boundaries = []
    for rva, candidate in expected.items():
        actual = starts.get(rva)
        verdict = boundary_verdict(rva, candidate["target_size"], actual["ranges"] if actual else None,
                                   actual["owned_bytes"] if actual else None)
        boundaries.append(dict(candidate_id=candidate["id"], entry_rva=rva, proven_size=candidate["target_size"],
                               proof=candidate["boundary"], ghidra=actual, verdict=verdict))
    call_sites = {c["instruction_rva"]: dict(candidate_id=p["id"], evidence=c)
                  for p in candidates for c in p["callee_contract"]}
    for row in table(directory / "calls.tsv"):
        counts["call_rows"] += 1
        counts["resolved_call_rows" if row["target_rva"] else "unresolved_call_rows"] += 1
        site = int(row["instruction_rva"], 16)
        if site in call_sites:
            call_sites[site].setdefault("ghidra", []).append(row)
    strings = {(s["string_rva"], s["operand_rva"] - 1): dict(candidate_id=p["id"], evidence=s)
               for p in candidates for s in p["string_witnesses"]}
    for row in table(directory / "string_references.tsv"):
        counts["string_reference_rows"] += 1
        key = (int(row["string_rva"], 16), int(row["reference_rva"], 16))
        if key in strings:
            strings[key]["ghidra"] = row
    for key in ("functions", "call_rows", "string_reference_rows"):
        require(counts[key] == int(metadata[key]), f"Truncated Ghidra {key} inventory")
    return dict(schema_version=1, target_id=target.target_id, binary_sha256=target.expected_sha256,
                address_convention="All address fields are RVAs; range endpoints are inclusive",
                producer=metadata, artifacts=[dict(path=f"build/worldbuilder-inventory/{name}", sha256=value)
                                              for name, value in fingerprints.items()],
                provenance=dict(scripts=receipt["scripts"], auditor="tools/worldbuilder_analysis.py",
                                auditor_sha256=text_sha256(Path(__file__)),
                                ghidra_properties_sha256=receipt["ghidra_properties_sha256"],
                                text_hash_normalization="CRLF-to-LF",
                                analysis_settings="default analyzers; -max-cpu 2 -analysisTimeoutPerFile 1200"),
                reproduce=dict(fresh="python3 tools/worldbuilder_analysis.py --analyze --ghidra <installation>",
                               reuse="python3 tools/worldbuilder_analysis.py --export --ghidra <installation>",
                               check="python3 tools/worldbuilder_analysis.py --check"),
                counts=dict(counts), boundary_samples=boundaries, noncontiguous_examples=noncontiguous,
                call_samples=[dict(instruction_rva=k, **v) for k, v in sorted(call_sites.items())],
                string_reference_samples=list(strings.values()),
                limitations=["Ghidra names are analysis labels, not independently established identities.",
                             "Owned ranges, even contiguous ones, are candidates for boundary verification, not byte-match claims.",
                             "Indirect call rows without destinations remain unresolved; no destinations are invented.",
                             "Samples are deliberately selected MFC handlers; their detection rate is not a whole-binary accuracy estimate."])


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    operation = parser.add_mutually_exclusive_group()
    operation.add_argument("--analyze", action="store_true", help="First import only; refuse to overwrite an existing project")
    operation.add_argument("--export", action="store_true", help="Reuse existing project without analysis or modification")
    parser.add_argument("--ghidra", type=Path, help="Explicit Ghidra installation directory, required for --analyze/--export")
    parser.add_argument("--check", action="store_true", help="Compare tracked audit without writing it")
    args = parser.parse_args(argv)
    require(not args.check or not (args.analyze or args.export), "--check cannot be combined with an export")
    target = load_target("worldbuilder")
    directory = target.root / "build/worldbuilder-inventory"
    if args.analyze or args.export:
        export(target, directory, args.ghidra.resolve() if args.ghidra else None, args.analyze)
    value = audit(target, directory)
    text = json.dumps(value, indent=2) + "\n"
    path = target.ledger_root / "analysis.json"
    if args.check:
        require(path.is_file() and path.read_text(encoding="utf-8") == text, "Stale WorldBuilder analysis audit")
    else:
        path.write_text(text, encoding="utf-8", newline="\n")
    print(json.dumps(value["counts"], sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
