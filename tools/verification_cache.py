#!/usr/bin/env python3
"""Reuse successful scoped byte-verification without trusting a commit SHA.

This is an optimization around ``tools/build.py``, not a second verifier.  A
cache entry is usable only when the hook can reconstruct the same verification
inputs and the current object still reproduces the recorded result.  A missing,
malformed, old, or incomplete entry is a miss and the normal build gate runs.

The cache deliberately lives below ``build/``: it is local to one worktree,
never published, and cannot make a different checkout's objects look current.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time
import uuid

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402
from portable_lock import lock, unlock  # noqa: E402


ROOT = Path(__file__).resolve().parents[1]
CACHE = ROOT / "build" / "verification-cache"
VERSION = 1
ZERO = "0" * 40

# These are the inputs a compiler or a publication checker can read.  The
# comparison is against the pushed commit, not merely HEAD, so a hook cannot
# accidentally certify a dirty neighbouring tree.
TREE_PATHS = ("game", "worldbuilder", "inputs", "targets", "tools", ".githooks",
              "build.sh", "build.cmd", "build.ps1")
BOUNDARY_ENV = ("ADDMATCH_BOUNDARY_NAME", "ADDMATCH_BOUNDARY_RVA",
                "ADDMATCH_BOUNDARY_SOURCE", "ADDMATCH_BOUNDARY_BATCH_FILE")


def git(*args, check=True):
    result = subprocess.run(["git", "-C", str(ROOT), *args],
                            capture_output=True, text=True)
    if check and result.returncode:
        raise RuntimeError(result.stderr.strip() or "git command failed")
    return result


def _pathspecs():
    return ["--", *TREE_PATHS]


def exact_worktree(commit):
    """Refuse to verify if compiler/checker inputs differ from ``commit``."""
    if git("cat-file", "-e", f"{commit}^{{commit}}", check=False).returncode != 0:
        raise RuntimeError(f"pushed commit {commit} is unavailable locally")
    for cached in (False, True):
        args = ["diff"]
        if cached:
            args.append("--cached")
        args.extend(["--quiet", commit, *_pathspecs()])
        if git(*args, check=False).returncode:
            raise RuntimeError(
                f"working tree or index differs from pushed commit {commit}; "
                "commit or stash relevant changes before publishing")
    # Ignored generated sweep headers are included by the dependency receipt
    # below.  Non-ignored files in a compiler input directory are never allowed
    # to influence a supposedly clean candidate.
    untracked = git("ls-files", "--others", "--exclude-standard", "-z",
                    *_pathspecs(), check=True).stdout
    if untracked:
        names = [name for name in untracked.split("\0") if name]
        raise RuntimeError("untracked verification input(s): " + ", ".join(names[:8]))


def _sha256(path):
    digest = hashlib.sha256()
    with Path(path).open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def _normal_path(path):
    path = Path(path)
    try:
        return "@ROOT@/" + path.relative_to(ROOT).as_posix()
    except ValueError:
        return str(path.resolve())


def _file_receipt(path):
    path = Path(path)
    if not path.is_file():
        raise RuntimeError(f"verification input disappeared: {path}")
    return [_normal_path(path), _sha256(path)]


def _tool_receipt(command):
    """Hash compiler executables and DLLs, not only their path names."""
    paths = set()
    for item in command:
        path = Path(item)
        if path.is_file() and (path.suffix.lower() in {".exe", ".dll"}
                               or os.access(path, os.X_OK)):
            paths.add(path)
    try:
        root = B.vc71_root()
        for directory in (root / "Vc7" / "bin", root):
            if directory.is_dir():
                paths.update(path for path in directory.iterdir()
                             if path.is_file() and path.suffix.lower() in {".exe", ".dll"})
    except (OSError, RuntimeError, SystemExit):
        # The command's own receipt still gives a useful miss key, but without
        # a toolchain digest a prior result must not be accepted.
        return None
    try:
        return sorted(_file_receipt(path) for path in paths)
    except (OSError, RuntimeError):
        return None


def _rules_receipt():
    """Content-address every tracked tool and hook used by publication."""
    names = []
    for root in ("tools", ".githooks"):
        names.extend(git("ls-files", "-z", "--", root).stdout.split("\0"))
    names.extend(name for name in ("build.sh", "build.cmd", "build.ps1")
                 if git("ls-files", "--error-unmatch", name, check=False).returncode == 0)
    result = []
    for name in sorted(set(name for name in names if name)):
        path = ROOT / name
        if not path.is_file():
            return None
        result.append([name, _sha256(path)])
    return result


def _live_build_marker():
    directory = B.INFLIGHT_DIR
    if not directory.is_dir():
        return None
    for marker in directory.iterdir():
        try:
            pid = int(marker.name)
        except ValueError:
            return str(marker)
        alive = B.pid_alive(pid)
        if alive is not False:
            return str(marker)
    return None


def _boundary_request_active():
    return any(os.environ.get(name) is not None for name in BOUNDARY_ENV)


def _row_selector(row):
    return (f"row:0x{int(row['target_rva'], 16):08X}:"
            f"{int(row['target_size'])}:{row['name']}")


def _row_identity(row):
    return sorted((str(key), str(value)) for key, value in row.items())


def _rows():
    return B.load_function_rows()


def _rows_for_selectors(selectors, rows):
    selected = []
    seen = set()
    for selector in selectors:
        if selector.startswith("source:"):
            # The hook's typed source selector is the source-claim check only;
            # delta_sources supplies exact row selectors alongside it.  Do not
            # turn a cheap source check into a whole-TU compile on every retry.
            continue
        exact = B.parse_row_selector(selector)
        if exact is not None:
            matches = [row for row in rows if B.selector_matches_row(selector, row)]
        else:
            matches = [row for row in rows if B.selector_matches_row(selector, row)]
        for row in matches:
            identity = tuple(_row_identity(row))
            if identity not in seen:
                seen.add(identity)
                selected.append(row)
    return selected


def _source_selectors(selectors):
    output = []
    seen = set()
    for selector in selectors:
        if selector.startswith("row:"):
            continue
        source = selector[len("source:"):] if selector.startswith("source:") else selector
        # A raw edited-source selector is intentionally narrowed to an exact
        # source check.  The row expansion happens separately, so source claims
        # remain cheap on cache hits.
        value = "source:" + source
        if value not in seen:
            seen.add(value)
            output.append(value)
    return output


def _read_meta(obj):
    sidecar = B._deps_sidecar(obj)
    if not obj.is_file() or not sidecar.is_file():
        return None
    try:
        meta = json.loads(sidecar.read_text(encoding="utf-8"))
    except (OSError, ValueError, TypeError):
        return None
    if not isinstance(meta, dict) or not isinstance(meta.get("deps", {}), dict):
        return None
    return meta


def _body_and_relocs(row, obj, target, symbol_map):
    symbol = B.ledger_object_symbol(row)
    if B.is_funclet_row(row, symbol):
        body, relocs, _note = B.read_funclet(row, symbol, obj, target)
    else:
        body, relocs = B.read_object_symbol_bytes(obj, symbol, len(target))
    return body, relocs


def _payload(row, symbol_map, inventory_cache):
    obj = B.row_object(row)
    source = ROOT / row["source"]
    target = B.read_target_bytes(int(row["target_rva"], 16), int(row["target_size"]))
    meta = _read_meta(obj)
    if meta is None or not source.is_file() or not obj.is_file():
        return None
    if source.suffix.lower() != B.LIB_SUFFIX:
        try:
            current = B.compile_is_current(source, obj, inventory_cache=inventory_cache)
        except (OSError, RuntimeError, SystemExit):
            current = False
        if not current:
            return None
    try:
        command, env = B.compiler_command(source, obj)
    except (OSError, RuntimeError, SystemExit):
        command, env = [], {}
    toolchain = _tool_receipt(command) if command else []
    if command and toolchain is None:
        return None
    dependencies = []
    for dep in sorted(meta.get("deps", {})):
        path = Path(dep) if os.path.isabs(dep) else ROOT / dep
        try:
            dependencies.append(_file_receipt(path))
        except (OSError, RuntimeError):
            return None
    try:
        body, relocs = _body_and_relocs(row, obj, target, symbol_map)
    except (OSError, ValueError, SystemExit):
        return None
    try:
        result = B.compile_function(row, symbol_map, obj)
    except (OSError, ValueError, SystemExit):
        return None
    if result["bytes"] != target or (result["masked"] and
                                      result["concrete"] < B.MIN_LIB_CONCRETE):
        # A stale or manually corrupted object is a miss.  The normal build
        # invocation then decides whether the candidate is genuinely invalid.
        return None
    names = sorted({symbol for offset, rtype, symbol in relocs
                    if rtype == B.REL32 and offset < len(target)})
    resolutions = {name: symbol_map.get(name) for name in names}
    # The compiled object and sidecar are receipts as well as inputs.  This
    # catches a concurrent writer even when the file remains parseable.
    try:
        object_receipt = _file_receipt(obj)
        sidecar_receipt = _file_receipt(B._deps_sidecar(obj))
        source_receipt = _file_receipt(source)
    except (OSError, RuntimeError):
        return None
    return {
        "row": _row_identity(row),
        "source": source_receipt,
        "deps": dependencies,
        "sidecar": meta,
        "command": B._cmd_fingerprint(command, env) if command else "archive-member",
        "environment": {key: env.get(key, "") for key in
                         ("INCLUDE", "LIB", "WINEPATH", "WINEPREFIX")},
        "toolchain": toolchain,
        "target": hashlib.sha256(target).hexdigest(),
        "object": object_receipt,
        "object-sidecar": sidecar_receipt,
        "relocations": [[offset, rtype, symbol] for offset, rtype, symbol in relocs],
        "resolutions": resolutions,
        "rules": _rules_receipt(),
        "python": [sys.executable, sys.version, os.name],
        "version": VERSION,
        # A successful record stores the bytes that the ordinary gate compared.
        "resolved": hashlib.sha256(result["bytes"]).hexdigest(),
        "body": hashlib.sha256(body).hexdigest(),
    }


def _key(payload):
    if payload is None or payload.get("rules") is None:
        return None
    encoded = json.dumps(payload, sort_keys=True, separators=(",", ":")).encode()
    return hashlib.sha256(encoded).hexdigest()


def _entry_path(key):
    return CACHE / f"{key}.json"


def _load_entry(key):
    try:
        entry = json.loads(_entry_path(key).read_text(encoding="utf-8"))
    except (OSError, ValueError, TypeError):
        return None
    if not isinstance(entry, dict) or entry.get("version") != VERSION:
        return None
    if entry.get("key") != key or entry.get("payload", {}).get("version") != VERSION:
        return None
    return entry


def _write_entry(key, payload):
    CACHE.mkdir(parents=True, exist_ok=True)
    lock_path = CACHE / ".lock"
    with lock_path.open("a+b") as handle:
        lock(handle, exclusive=True)
        try:
            tmp = CACHE / f".{key}.{os.getpid()}.{uuid.uuid4().hex}.tmp"
            tmp.write_text(json.dumps({"version": VERSION, "key": key,
                                       "payload": payload, "recorded": time.time()},
                                      sort_keys=True), encoding="utf-8")
            os.replace(tmp, _entry_path(key))
        finally:
            tmp.unlink(missing_ok=True)
            unlock(handle)


def _entry_is_valid(entry, payload):
    same_payload = (entry is not None and
                    json.dumps(entry.get("payload"), sort_keys=True,
                               separators=(",", ":")) ==
                    json.dumps(payload, sort_keys=True, separators=(",", ":")))
    return (same_payload and
            entry.get("payload", {}).get("resolved") is not None)


def prepare(commit, selectors, manifest):
    exact_worktree(commit)
    if marker := _live_build_marker():
        raise RuntimeError(f"build {marker} is running; retry publishing after it exits")
    rows = _rows()
    selected = _rows_for_selectors(selectors, rows)
    rules = _rules_receipt()
    if rules is None:
        raise RuntimeError("checker/rules inputs are incomplete; cannot cache verification")
    symbol_map = B.load_symbol_map()
    inventory_cache = {}
    misses, hits = [], []
    cache_disabled = _boundary_request_active()
    for row in selected:
        payload = None if cache_disabled else _payload(row, symbol_map, inventory_cache)
        key = _key(payload)
        entry = _load_entry(key) if key else None
        if not cache_disabled and key and _entry_is_valid(entry, payload):
            hits.append(_row_selector(row))
        else:
            misses.append(row)
    data = {"version": VERSION, "commit": commit,
            "rows": misses, "hits": hits, "selectors": selectors}
    Path(manifest).write_text(json.dumps(data, sort_keys=True), encoding="utf-8")
    output = _source_selectors(selectors)
    output.extend("source:" + row["source"] for row in selected)
    output.extend(_row_selector(row) for row in misses)
    # The pre-push hook reads these with `mapfile -t`: force LF-only output, or
    # Windows text-mode stdout appends CR to every selector and each row
    # selector then matches no ledger row (delta_sources.py does the same).
    sys.stdout.reconfigure(newline="\n")
    for selector in dict.fromkeys(output):
        print(selector)
    suffix = " (boundary request active; cache disabled)" if cache_disabled else ""
    print(f"publish-verify: {len(hits)} cache hit(s), {len(misses)} expensive row check(s){suffix}",
          file=sys.stderr)


def record(manifest):
    data = json.loads(Path(manifest).read_text(encoding="utf-8"))
    if data.get("version") != VERSION:
        raise RuntimeError("verification manifest version is incompatible")
    exact_worktree(data["commit"])
    if marker := _live_build_marker():
        raise RuntimeError(f"build {marker} started during verification; evidence discarded")
    symbol_map = B.load_symbol_map()
    inventory_cache = {}
    saved = skipped = 0
    for row in data.get("rows", []):
        payload = _payload(row, symbol_map, inventory_cache)
        key = _key(payload)
        if key is None:
            # The build gate has just verified this row; evidence that cannot be
            # keyed (e.g. uncacheable dependencies) is only a miss next time.
            print(f"publish-verify: not recording {row['name']}: its evidence cannot be keyed",
                  file=sys.stderr)
            skipped += 1
            continue
        target = B.read_target_bytes(int(row["target_rva"], 16), int(row["target_size"]))
        obj = B.row_object(row)
        try:
            result = B.compile_function(row, symbol_map, obj)
        except (OSError, ValueError, SystemExit) as exc:
            raise RuntimeError(f"post-verification evidence cannot be read for {row['name']}: {exc}")
        if result["bytes"] != target or (result["masked"] and
                                          result["concrete"] < B.MIN_LIB_CONCRETE):
            raise RuntimeError(f"post-verification evidence failed for {row['name']}")
        _write_entry(key, payload)
        saved += 1
    print(f"publish-verify: recorded {saved} successful row verification(s)"
          + (f", {skipped} not recordable" if skipped else ""), file=sys.stderr)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    prep = sub.add_parser("prepare")
    prep.add_argument("--commit", required=True)
    prep.add_argument("--selectors-file", required=True)
    prep.add_argument("--manifest", required=True)
    rec = sub.add_parser("record")
    rec.add_argument("--manifest", required=True)
    args = parser.parse_args(argv)
    try:
        if args.command == "prepare":
            selectors = [line.rstrip("\r\n") for line in
                         Path(args.selectors_file).read_text(encoding="utf-8").splitlines()
                         if line.strip()]
            prepare(args.commit, selectors, args.manifest)
        else:
            record(args.manifest)
    except (OSError, RuntimeError, ValueError, SystemExit) as exc:
        print(f"verification-cache: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
