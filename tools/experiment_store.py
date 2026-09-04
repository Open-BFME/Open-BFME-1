"""Persistent compiler experiments; cached objects are never acceptance receipts.

Source, compiler binaries, flags and header-search inventory select the object.
The build's dependency hashes must also agree before reuse. Results include the
target and relocation symbols; source changes producing the same instructions
are recorded as repeated outcomes. All writes are confined to build/.
"""
import hashlib
import json
import os
from pathlib import Path
import sqlite3
import time
import uuid

import build
from portable_lock import lock, unlock


def digest(data):
    return hashlib.sha256(data).hexdigest()


def compiler_identity(source):
    root = build.vc71_root()
    binaries = sorted((root / "Vc7/bin").glob("*"))
    return digest(json.dumps([(str(p), build._hash_file(str(p))) for p in binaries
                              if p.suffix.lower() in (".exe", ".dll")]).encode())


def search_inventory(source, command, env):
    """Directory changes invalidate additions/removals that could shadow a header."""
    roots = {source.parent}
    roots.update(Path(p) for p in env.get("INCLUDE", "").split(";") if p)
    for arg in command:
        if arg.startswith(("-I", "/I")) and len(arg) > 2:
            raw = arg[2:]
            roots.add(Path(raw) if os.path.isabs(raw) else build.ROOT / raw)
    directories = []
    for root in sorted(roots, key=str):
        # INCLUDE is in host spelling on Windows. Wine command flags may use
        # drive spelling; unresolvable roots make reuse conservative.
        if not root.exists():
            # An unknown search root is not evidence that its contents agree.
            return None
        for directory, subdirs, _ in os.walk(root):
            subdirs.sort()
            directories.append((directory, os.stat(directory).st_mtime_ns))
    return digest(json.dumps(directories).encode())


def compile_cached(source):
    source = Path(source).resolve()
    root = build.ROOT / "build" / "experiments"
    root.mkdir(parents=True, exist_ok=True)
    placeholder = root / "object.obj"
    command, env = build.compiler_command(source, placeholder)
    key = digest(json.dumps([str(source), digest(source.read_bytes()),
                             compiler_identity(source), command,
                             {k: env.get(k, "") for k in ("INCLUDE", "CL", "_CL_", "PATH")}]).encode())
    directory = root / key
    directory.mkdir(exist_ok=True)
    receipt = directory / "cache.json"
    with (directory / "compile.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        try:
            inventory = search_inventory(source, command, env)
            try:
                meta = json.loads(receipt.read_text()) if receipt.exists() else {}
            except (ValueError, OSError):
                meta = {}
            obj = directory / meta.get("path", "missing.obj")
            if (inventory is not None and not env.get("CL") and not env.get("_CL_")
                    and obj.exists() and meta.get("inventory") == inventory
                    and meta.get("object") == digest(obj.read_bytes())
                    and build.compile_is_current(source, obj)):
                return obj, True
            # Never replace an object another probe may still be reading.
            obj = directory / ("object-" + uuid.uuid4().hex + ".obj")
            try:
                build.compile_source(source, obj)
            except (Exception, SystemExit) as error:
                # Keep negative evidence, but never reuse a failed compile:
                # /showIncludes may not have disclosed all dependencies yet.
                (directory / ("failure-" + str(time.time_ns()) + ".json")).write_text(
                    json.dumps({"error": str(error), "source": str(source), "key": key}))
                receipt.unlink(missing_ok=True)
                raise
            # Capture AFTER compiling: some toolchains create header directories.
            receipt.write_text(json.dumps({"inventory": search_inventory(source, command, env),
                                           "path": obj.name, "object": digest(obj.read_bytes())}))
            return obj, False
        finally:
            unlock(handle)


def record_result(source, symbol, rva, target, compiled, relocs, db_path=None):
    holes = bytearray(compiled)
    for off, kind, name in relocs:
        width = build.RELOC_WIDTH.get(kind)
        if width is None or off < 0 or off + width > len(holes):
            raise ValueError("invalid relocation extent in experiment")
        holes[off:off + width] = bytes(width)
    # Symbols and addends must survive deduplication: identical opcodes calling
    # different functions are different hypotheses.
    shape = digest(bytes(holes) + json.dumps(relocs).encode()
                   + b"".join(compiled[o:o + build.RELOC_WIDTH[k]] for o, k, _ in relocs))
    target_key = digest(target + str(rva).encode())
    path = db_path or build.ROOT / "build" / "experiments.sqlite"
    with sqlite3.connect(path, timeout=60) as db:
        db.execute("CREATE TABLE IF NOT EXISTS outcomes (target TEXT, shape TEXT, source_hash TEXT, source TEXT, symbol TEXT, at REAL, run TEXT)")
        seen = db.execute("SELECT count(*) FROM outcomes WHERE target=? AND shape=?", (target_key, shape)).fetchone()[0]
        db.execute("INSERT INTO outcomes VALUES (?,?,?,?,?,?,?)",
                   (target_key, shape, digest(Path(source).read_bytes()), str(source), symbol,
                    time.time(), os.environ.get("BFME_RUN_ID", "")))
    return {"shape": shape, "seen_before": seen, "target": target_key}
