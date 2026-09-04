#!/usr/bin/env python3
"""Index landed C++ with similar retail operand shapes, for hypotheses only.

python tools/source_donors.py --refresh [--max-size 1000]
python tools/source_donors.py 0xRVA SIZE

Each lookup checks the retail image and donor source hashes. The index can miss
new landings until refreshed, but changed sources cannot be served as proven
examples. Every target still needs its own constants, callees and identity.
"""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import uuid

import build
import capstone
from family_scan import mask_operands

INDEX = build.ROOT / "build/source_donors.json"


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def shape(rva, size):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    key = mask_operands(build.read_target_bytes(rva, size), md)
    return bytes(key).hex() if key is not None else None


def refresh(max_size=1000):
    index = dict(exe=sha(build.EXE), max_size=max_size, shapes={})
    sources = {}
    with (build.ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            source = row.get("source", "")
            if (row.get("status") != "matched" or not source.startswith("Code/")
                    or source.startswith("Code/gen_") or not source.endswith((".cpp", ".c"))):
                continue
            size = int(row["target_size"])
            if not 8 <= size <= max_size:
                continue
            if source not in sources:
                path = build.ROOT / source
                text = path.read_text(encoding="utf-8-sig", errors="replace")
                sources[source] = None if re.search(r"\b(?:__asm|_asm|__emit|_emit|naked)\b", text) else sha(path)
            if not sources[source]:
                continue
            key = shape(int(row["target_rva"], 16), size)
            if key:
                index["shapes"].setdefault(key, []).append(dict(source=source, name=row["name"],
                    rva=row["target_rva"], size=size, source_sha256=sources[source]))
    INDEX.parent.mkdir(exist_ok=True)
    temporary = INDEX.with_suffix("." + uuid.uuid4().hex + ".tmp")
    temporary.write_text(json.dumps(index), encoding="utf-8")
    temporary.replace(INDEX)
    return index


def lookup(rva, size, limit=3):
    if not INDEX.exists():
        return []
    index = json.loads(INDEX.read_text(encoding="utf-8"))
    if size > index["max_size"] or index["exe"] != sha(build.EXE):
        return []
    hits = index["shapes"].get(shape(rva, size), [])
    result = []
    for entry in hits:
        path = build.ROOT / entry["source"]
        if path.is_file() and sha(path) == entry["source_sha256"]:
            result.append(entry)
            if len(result) == limit:
                break
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("rva", nargs="?", type=lambda s: int(s, 16))
    ap.add_argument("size", nargs="?", type=int)
    ap.add_argument("--refresh", action="store_true")
    ap.add_argument("--max-size", default=1000, type=int)
    a = ap.parse_args()
    if a.refresh:
        index = refresh(a.max_size)
        print(f"Indexed {sum(map(len, index['shapes'].values()))} C++ donor rows at {INDEX}")
    if a.rva is not None:
        if not a.size:
            ap.error("SIZE is required with an RVA")
        print(json.dumps(lookup(a.rva, a.size), indent=2))


if __name__ == "__main__":
    main()
