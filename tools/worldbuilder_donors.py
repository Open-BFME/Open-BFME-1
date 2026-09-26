"""Pinned source suggestions for WorldBuilder exports; lookup is always offline."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import csv
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import subprocess
import sys
from urllib.error import URLError
from urllib.parse import quote
from urllib.request import urlopen

from ledger_io import atomic_write_bytes
from targets import load_target


REPOSITORIES = {"bfme1": "Open-BFME/Open-BFME-1", "bfme2": "Open-BFME/Open-BFME-2"}
ASSEMBLY = re.compile(rb"\b(?:__declspec\s*\(\s*naked|__emit|_emit|__asm)\b")
SCHEMA = 1


class DonorError(ValueError):
    pass


def git_blob_hash(data):
    return hashlib.sha1(b"blob " + str(len(data)).encode() + b"\0" + data).hexdigest()


def _sha(value):
    if not isinstance(value, str) or not re.fullmatch(r"[0-9a-f]{40}", value):
        raise DonorError(f"expected an immutable 40-digit Git object ID, got {value!r}")
    return value


def _source(path):
    if (not isinstance(path, str) or "\\" in path or ":" in path
            or PurePosixPath(path).is_absolute() or ".." in PurePosixPath(path).parts
            or not path.startswith(("Code/", "reference/"))):
        raise DonorError(f"invalid donor source path: {path!r}")
    return path


def _command(target, *args):
    result = subprocess.run(args, cwd=target.root, capture_output=True)
    if result.returncode:
        raise DonorError(f"{' '.join(args)} failed: {result.stderr.decode('utf-8', 'replace').strip()}")
    return result.stdout


def _url(reference, path):
    return (f"https://raw.githubusercontent.com/{reference['repository']}/"
            f"{reference['revision']}/{quote(path, safe='/')}")


def _remote_bytes(reference, path):
    try:
        with urlopen(_url(reference, path), timeout=45) as response:
            return response.read()
    except (OSError, URLError) as error:
        raise DonorError(f"fetch {reference['repository']}@{reference['revision']}:{path}: {error}") from error


def _tree(target, name, reference):
    if name == "bfme1":
        data = _command(target, "git", "ls-tree", "-rlz", reference["revision"])
        return {path.decode(): {"sha": metadata.split()[2].decode(), "size": int(metadata.split()[3])}
                for entry in data.split(b"\0") if entry
                for metadata, path in [entry.split(b"\t", 1)] if metadata.split()[1] == b"blob"}
    result = json.loads(_command(target, "gh", "api",
        f"repos/{reference['repository']}/git/trees/{reference['revision']}?recursive=1"))
    if result.get("truncated"):
        raise DonorError("GitHub returned a truncated donor tree; cannot bind all source hashes")
    return {item["path"]: {"sha": item["sha"], "size": item["size"]}
            for item in result["tree"] if item["type"] == "blob"}


def _matching_rows(stream, names):
    for row in csv.DictReader(stream):
        source = row.get("source", "")
        if (row.get("name") in names and row.get("status") == "matched"
                and source.endswith((".cpp", ".c")) and not source.startswith("Code/gen_")
                and not re.match(r"\s*gen-dump(?:$|[;,])", row.get("notes", ""))):
            _source(source)
            yield row


def _ledger_rows(target, name, reference, names, blob):
    digest = hashlib.sha1(b"blob " + str(blob["size"]).encode() + b"\0")
    if name == "bfme1":
        process = subprocess.Popen(["git", "show", reference["revision"] + ":reverse/functions.csv"],
                                   cwd=target.root, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stream = process.stdout
    else:
        process = None
        try:
            stream = urlopen(_url(reference, "reverse/functions.csv"), timeout=45)
        except (OSError, URLError) as error:
            raise DonorError(f"cannot stream {name} ledger: {error}") from error
    try:
        # Hash the exact blob while retaining only the relevant exported names.
        size = 0
        content = hashlib.sha256()
        def lines():
            nonlocal size
            for raw in stream:
                size += len(raw)
                digest.update(raw)
                content.update(raw)
                yield raw.decode("utf-8-sig")
        rows = list(_matching_rows(lines(), names))
    finally:
        stream.close()
        if process is not None:
            stderr = process.stderr.read()
            code = process.wait()
    if process is not None and code:
        raise DonorError(f"cannot stream {name} ledger: {stderr.decode('utf-8', 'replace')}")
    if size != blob["size"] or digest.hexdigest() != blob["sha"]:
        raise DonorError(f"{name}: streamed ledger differs from the pinned Git tree")
    return rows, {"sha256": content.hexdigest(), "size": size}


def _read_source(target, name, reference, source, expected):
    data = (_command(target, "git", "cat-file", "blob", expected) if name == "bfme1"
            else _remote_bytes(reference, source))
    if git_blob_hash(data) != expected:
        raise DonorError(f"{name}@{reference['revision']}:{source}: Git blob hash mismatch")
    return data


def _exports(target):
    return {entry.name: entry.rva for entry in target.exports
            if entry.name and not entry.forwarder
            and target.section_for_rva(entry.rva).characteristics & 0x20000000}


def _json_bytes(value):
    return (json.dumps(value, indent=2, sort_keys=True) + "\n").encode()


def refresh(target, revisions):
    exports, records, references, excluded = _exports(target), [], {}, {}
    for name in REPOSITORIES:
        reference = {"repository": REPOSITORIES[name], "revision": _sha(revisions[name])}
        tree = _tree(target, name, reference)
        if "reverse/functions.csv" not in tree:
            raise DonorError(f"{name}: pinned tree has no function ledger")
        reference["ledger_git_blob_sha1"] = tree["reverse/functions.csv"]["sha"]
        rows, reference["ledger_content"] = _ledger_rows(target, name, reference, exports, tree["reverse/functions.csv"])
        sources = sorted({row["source"] for row in rows})
        missing = set(sources) - tree.keys()
        if missing:
            raise DonorError(f"{name}: ledger cites absent pinned sources: {sorted(missing)}")
        def audit(source):
            data = _read_source(target, name, reference, source, tree[source]["sha"])
            # File-level rejection is conservative: a mixed TU is not an audited donor.
            clean = re.sub(rb"//[^\n]*|/\*.*?\*/", b"", data, flags=re.S)
            return source, not bool(ASSEMBLY.search(clean))
        with ThreadPoolExecutor(max_workers=8) as pool:
            audited = dict(pool.map(audit, sources))
        excluded[name] = sorted(source for source, clean in audited.items() if not clean)
        for row in rows:
            if audited[row["source"]]:
                records.append({"reference": name, "symbol": row["name"],
                    "worldbuilder_export_rva": exports[row["name"]],
                    "donor_rva": int(row["target_rva"], 16), "donor_size": int(row["target_size"]),
                    "source": row["source"], "source_git_blob_sha1": tree[row["source"]]["sha"]})
        references[name] = reference
    config = {"schema_version": SCHEMA, "references": references}
    config_bytes = _json_bytes(config)
    index = {"schema_version": SCHEMA, "target_id": target.target_id,
             "binary_sha256": target.expected_sha256,
             "references_sha256": hashlib.sha256(config_bytes).hexdigest(),
             "target_evidence": "WorldBuilder PE export name; donor source is a hypothesis",
             "source_audit": "Pinned source file contains no naked, emit or inline-assembly code",
             "excluded_assembly_sources": excluded,
             "donors": sorted(records, key=lambda row: (row["symbol"], row["reference"], row["source"], row["donor_rva"]))}
    atomic_write_bytes(target.config_path.parent / "references.json", config_bytes)
    atomic_write_bytes(target.ledger_root / "donors.json", _json_bytes(index))
    return index


def _load(target):
    config_path = target.config_path.parent / "references.json"
    raw = config_path.read_bytes()
    config = json.loads(raw)
    index = json.loads((target.ledger_root / "donors.json").read_bytes())
    if (config.get("schema_version") != SCHEMA or set(config.get("references", {})) != set(REPOSITORIES)
            or index.get("schema_version") != SCHEMA or index.get("target_id") != target.target_id
            or index.get("binary_sha256") != target.expected_sha256
            or index.get("references_sha256") != hashlib.sha256(raw).hexdigest()):
        raise DonorError("donor index/reference/target mismatch; run explicit --refresh with pinned revisions")
    for name, ref in config["references"].items():
        if ref.get("repository") != REPOSITORIES[name]:
            raise DonorError(f"{name}: unexpected donor repository")
        _sha(ref["revision"])
        _sha(ref["ledger_git_blob_sha1"])
    exports = _exports(target)
    for row in index["donors"]:
        if (row["reference"] not in config["references"]
                or exports.get(row["symbol"]) != row["worldbuilder_export_rva"]):
            raise DonorError("donor record has no corresponding WorldBuilder export")
        _source(row["source"])
        _sha(row["source_git_blob_sha1"])
    return config, index


def lookup(target, query="", *, reference=None, source=None, exact=False):
    config, index = _load(target)
    return [dict(row, repository=config["references"][row["reference"]]["repository"],
                 revision=config["references"][row["reference"]]["revision"],
                 target_evidence=index["target_evidence"])
            for row in index["donors"] if (reference is None or row["reference"] == reference)
            and (source is None or source.casefold() in row["source"].casefold())
            and (row["symbol"] == query if exact else query.casefold() in (row["symbol"] + " " + row["source"]).casefold())]


def fetch_source(target, record):
    matches = lookup(target, record["symbol"], reference=record["reference"], exact=True)
    if record not in matches:
        raise DonorError("donor record is stale or does not belong to the selected pin")
    path = target.build_root / "donors" / record["reference"] / record["revision"] / record["source"]
    if not path.resolve().is_relative_to(target.build_root):
        raise DonorError("donor cache path escapes the target scratch directory")
    if path.exists():
        if git_blob_hash(path.read_bytes()) != record["source_git_blob_sha1"]:
            raise DonorError(f"{path}: cached donor Git blob hash mismatch")
        return path
    data = _read_source(target, record["reference"], record, record["source"], record["source_git_blob_sha1"])
    path.parent.mkdir(parents=True, exist_ok=True)
    atomic_write_bytes(path, data)
    return path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("query", nargs="?", default="")
    parser.add_argument("--reference", choices=REPOSITORIES)
    parser.add_argument("--source")
    parser.add_argument("--exact", action="store_true")
    parser.add_argument("--fetch", action="store_true")
    parser.add_argument("--show", action="store_true")
    parser.add_argument("--refresh", action="store_true")
    for name in REPOSITORIES:
        parser.add_argument(f"--{name}-revision")
    args = parser.parse_args()
    if not args.refresh and any(getattr(args, name + "_revision") for name in REPOSITORIES):
        parser.error("revision arguments require --refresh")
    target = load_target("worldbuilder")
    if args.refresh:
        revisions = {name: getattr(args, name + "_revision") for name in REPOSITORIES}
        if not all(revisions.values()):
            parser.error("--refresh requires --bfme1-revision and --bfme2-revision full commit IDs")
        index = refresh(target, revisions)
        print(f"WorldBuilder donors: {len(index['donors'])} pinned source suggestions")
        return
    rows = lookup(target, args.query, reference=args.reference, source=args.source, exact=args.exact)
    if args.fetch or args.show:
        files = {(row["reference"], row["source"]): row for row in rows}
        if not files or len(files) > 8:
            raise DonorError(f"fetch/show selected {len(files)} files; narrow to 1..8 sources")
        for record in files.values():
            path = fetch_source(target, record)
            print(f"{record['repository']}@{record['revision']}:{record['source']} [{record['source_git_blob_sha1']}]\n{path}")
            if args.show:
                print(path.read_text(encoding="utf-8", errors="replace"))
    else:
        print(json.dumps(rows, indent=2))


if __name__ == "__main__":
    try:
        main()
    except (DonorError, OSError, ValueError) as error:
        print(f"worldbuilder donors: {error}", file=sys.stderr)
        sys.exit(1)
