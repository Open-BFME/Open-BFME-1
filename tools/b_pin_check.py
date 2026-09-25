#!/usr/bin/env python3
"""Every `b_<rva>()` a compiled source calls needs its `?b_<rva>@@YAXXZ` pin.

A generated ILT thunk is `void j_<rva>() { b_<target>(); }`: the gate resolves
the call's rel32 from the ?b_<target>@@YAXXZ row in reverse/symbols.csv, so the
bytes prove the target. Commit a8ad18240f (pushed without the pre-push hook)
REPLACED that pin with the target's new real name instead of adding the name
beside it; j_0002efbe in Code/gen_small/gthunks_052.cpp lost its target and
the full gate went red (fixed in 0a34e68a0f). check_csv, pin_consistency and
one_identity all passed on that commit. This check needs no compiler and no
retail image, so it also runs in CI, which a skipped local hook cannot skip.

  python3 tools/b_pin_check.py              # working tree
  python3 tools/b_pin_check.py --staged     # the index (pre-commit)
  python3 tools/b_pin_check.py --ref SHA    # a commit (pre-push, CI)

Only sources that a matched functions.csv row compiles are read. A pin whose
address disagrees with the address in its own name is reported too.
"""
import argparse
import csv
import io
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CALL = re.compile(r"\bb_([0-9a-fA-F]{8})\s*\(\s*\)")
DECL = re.compile(r"\bvoid\s+b_([0-9a-fA-F]{8})\s*\(\s*(?:void)?\s*\)\s*;")
PIN = re.compile(r"^\?b_([0-9a-fA-F]{8})@@YAXXZ$")


def git(*args, stdin=None):
    return subprocess.run(["git", *args], cwd=ROOT, input=stdin, capture_output=True, check=True).stdout


def read(ref, path):
    """Text of `path` in the working tree (ref None), the index (":"), or a commit."""
    if ref is None:
        return (ROOT / path).read_text(encoding="utf-8", errors="replace")
    spec = f":{path}" if ref == ":" else f"{ref}:{path}"
    return git("show", spec).decode("utf-8", errors="replace")


def candidates(ref):
    """Paths under Code/ that mention b_<8 hex>( at this state."""
    args = ["grep", "-l"]
    if ref == ":":
        args.append("--cached")     # an option: before the pattern, or git reads a revision
    args += ["-E", r"b_[0-9a-fA-F]{8}[[:space:]]*\("]
    if ref not in (None, ":"):
        args.append(ref)
    proc = subprocess.run(["git", *args, "--", "Code"], cwd=ROOT, capture_output=True)
    if proc.returncode not in (0, 1):
        raise SystemExit(f"b_pin_check: git grep failed: {proc.stderr.decode(errors='replace').strip()}")
    out = []
    for line in proc.stdout.decode("utf-8", errors="replace").splitlines():
        if ref not in (None, ":") and line.startswith(f"{ref}:"):
            line = line[len(ref) + 1:]
        out.append(line)
    return out


def batch(ref, paths):
    """{path: text} read in one git cat-file call (commit or index)."""
    if ref is None:
        return {p: read(None, p) for p in paths}
    prefix = ":" if ref == ":" else f"{ref}:"
    request = "".join(f"{prefix}{p}\n" for p in paths).encode()
    data = git("cat-file", "--batch", stdin=request)
    texts, offset = {}, 0
    for path in paths:
        end = data.index(b"\n", offset)
        header = data[offset:end].decode(errors="replace").rsplit(" ", 2)
        offset = end + 1
        if len(header) != 3 or header[1] != "blob":
            continue
        size = int(header[2])
        texts[path] = data[offset:offset + size].decode("utf-8", errors="replace")
        offset += size + 1
    return texts


def problems(ref=None):
    functions = csv.DictReader(io.StringIO(read(ref, "reverse/functions.csv")))
    compiled = {row["source"].replace("\\", "/") for row in functions if row.get("status") == "matched"}
    pins = {}
    bad = []
    for row in csv.reader(io.StringIO(read(ref, "reverse/symbols.csv"))):
        if len(row) < 2:
            continue
        m = PIN.match(row[0])
        if not m:
            continue
        pins.setdefault(m.group(1).lower(), set()).add(row[1].strip().lower())
    for name_rva, addresses in sorted(pins.items()):
        wrong = sorted(a for a in addresses if a.startswith("0x") and int(a, 16) != int(name_rva, 16))
        if wrong:
            bad.append(f"reverse/symbols.csv: ?b_{name_rva}@@YAXXZ is pinned at {', '.join(wrong)}, "
                       f"not the 0x{name_rva.upper()} its name says")
    paths = [p for p in candidates(ref) if p in compiled]
    for path, text in sorted(batch(ref, paths).items()):
        decls = list(DECL.finditer(text))
        declared = {m.group(1).lower() for m in decls}
        # the b_ token inside a declaration is not a call
        in_decl = {m.start(1) for m in decls}
        called = {m.group(1).lower() for m in CALL.finditer(text) if m.start(1) not in in_decl}
        for target in sorted(called & declared):
            if not any(a.startswith("0x") and int(a, 16) == int(target, 16) for a in pins.get(target, ())):
                bad.append(f"{path}: calls b_{target}() but reverse/symbols.csv has no "
                           f"?b_{target}@@YAXXZ pin at 0x{target.upper()} -- add the real name BESIDE "
                           f"the b_ pin, never in place of it")
    return bad


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    group = ap.add_mutually_exclusive_group()
    group.add_argument("--staged", action="store_true", help="check the index")
    group.add_argument("--ref", help="check a commit")
    args = ap.parse_args(argv)
    ref = ":" if args.staged else args.ref
    found = problems(ref)
    for line in found:
        print(f"  {line}")
    print(f"b_pin_check: {len(found)} problem(s)")
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main())
