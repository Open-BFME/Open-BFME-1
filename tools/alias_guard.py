#!/usr/bin/env python3
"""Check every /alternatename alias against the ledger.

`#pragma comment(linker, "/alternatename:A=B")` tells link.exe: when nothing
defines A, use B. A call spelled A was byte-matched against the address A is
pinned to, so the alias is only right when B is the body at that address. A
wrong one links and runs the neighbouring body: BFME2's 9749a9b46a aliases
??3Rva00803080Request to ??3Gen007F0170, but BFME1 pins that placeholder at
0x007F0190 (row ??3Gen007F0190). Until this check, the link census counted a
file linked through any alias, and nothing compared the two addresses.

Each alias A=B gets one verdict:

  ok       A's pinned address (symbols.csv route=, else its first pin, else
           its ledger row or data row) and B's address (its functions.csv
           row, else its pin, else its data row) are one body. Both are
           followed through ILT stub rows (target=) and any leading JMP
           rel32 in the retail image, so an alias to ?j_XXXXXXXX of the
           pinned body is ok.
  wrong    both are known and differ: callers of A would run B's body.
  unknown  A has no address (e.g. a data alias to a vftable) or B has none:
           nothing to compare. Reported, not charged.

cl.exe emits some directives itself (a member template call falls back to
the non-template member of the same signature); the census and link_check
read objects, so they judge those too.

The census (link_census.write_status) and link_check charge a wrong alias as
an `alias_target` blocker to the object that declares it and to any object
that references A while nothing defines A. The commit hook (--staged) fails
on a wrong alias in a staged source unless alias_target_baseline.txt lists
it; that baseline may only shrink (protected_paths.py).

  python3 tools/alias_guard.py --staged     # commit hook
  python3 tools/alias_guard.py --report     # every alias in the tree, by verdict
"""
import argparse
import collections
import csv
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

BASELINE = ROOT / "targets/game/reverse/alias_target_baseline.txt"
BASELINE_HEADER = ("# /alternatename aliases whose target is not the body at the alias's pinned address\n"
                   "# (tools/alias_guard.py). Shrink-only: fix the alias, never add a line. 'source: A=B'.\n")
SCANNED = ("game/", "inputs/")
SUFFIXES = (".c", ".cpp", ".h", ".hpp", ".inl")
LEDGERS = ("targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv",
           "targets/game/reverse/data_rows.csv")
# The pragma as written in a source, and the directive cl.exe copies into .drectve.
PRAGMA = re.compile(r'#\s*pragma\s+comment\s*\(\s*linker\s*,\s*"\s*/alternatename:([^"=\s]+)=([^"\s]+)\s*"\s*\)',
                    re.I)
DIRECTIVE = re.compile(r'"?/alternatename:"?([^\s"=]+)"?="?([^\s"]+?)"?(?=\s|$)', re.I)
COMMENTS = re.compile(r'//[^\n]*|/\*.*?\*/', re.S)
BASE = 0x400000


def source_aliases(text):
    """[(alias, target)] of the alternatename pragmas in a source's text."""
    return PRAGMA.findall(COMMENTS.sub(" ", text or ""))


def drectve_aliases(data):
    """[(alias, target)] of the /alternatename directives in a COFF object's
    .drectve sections (what link.exe actually reads)."""
    if len(data) < 20:
        return []
    count = struct.unpack_from("<H", data, 2)[0]
    optional = struct.unpack_from("<H", data, 16)[0]
    found = []
    for index in range(count):
        header = 20 + optional + index * 40
        if header + 40 > len(data) or data[header:header + 8].rstrip(b"\0") != b".drectve":
            continue
        size, pointer = struct.unpack_from("<II", data, header + 16)
        text = data[pointer:pointer + size].decode("latin-1")
        found.extend(DIRECTIVE.findall(text))
    return found


def object_aliases(obj):
    try:
        return drectve_aliases(Path(obj).read_bytes())
    except OSError:
        return []


class Judge:
    """Addresses of names from the ledger, and the verdict on one alias."""

    def __init__(self, rows=None, data_rows=None, image=None):
        import link_census
        self._routes = {}
        self._pins = link_census.pins(self._routes)
        rows = link_census.ledger() if rows is None else rows
        self._rows = collections.defaultdict(set)
        self._by_address = collections.defaultdict(list)
        self._stubs = {}
        for row in rows:
            address = int(row["target_rva"], 16)
            self._rows[row["name"]].add(address)
            self._by_address[address].append(row)
            if row["name"].startswith("?j_"):
                target = link_census._thunk_target(row.get("notes"))
                if target is not None:
                    self._stubs.setdefault(address, target)
        self._data = {}
        for row in self._data_rows() if data_rows is None else data_rows:
            try:
                address = int(row["address"], 16)
            except (KeyError, ValueError):
                continue
            self._data[row["name"]] = address - BASE if row.get("address_kind") == "va" else address
        self._image = image
        self._naked = None

    @staticmethod
    def _data_rows():
        path = ROOT / "targets/game/reverse/data_rows.csv"
        if not path.exists():
            return []
        with path.open(newline="", encoding="utf-8") as handle:
            return list(csv.DictReader(handle))

    def _read(self, address, size):
        if self._image is not None:
            return self._image(address, size)
        import build
        try:
            return build.read_target_bytes(address, size)
        except Exception:  # an address outside the image has no bytes to follow
            return b""

    def normal(self, address):
        """The body a call to `address` runs: through ILT stub rows and any
        leading JMP rel32, at most three hops."""
        for _ in range(3):
            if address in self._stubs:
                address = self._stubs[address]
                continue
            head = self._read(address, 5)
            if len(head) == 5 and head[0] == 0xE9:
                address = (address + 5 + struct.unpack("<i", head[1:])[0]) & 0xFFFFFFFF
                continue
            break
        return address

    def pinned(self, name):
        """The address a call spelled `name` was byte-matched against."""
        if name in self._routes:
            return self._routes[name]
        if name in self._pins:
            return self._pins[name]
        rows = self._rows.get(name, ())
        if len(rows) == 1:
            return next(iter(rows))
        return self._data.get(name)

    def addresses(self, name):
        """Where the definition of `name` lives: its ledger rows, else its pin."""
        if self._rows.get(name):
            return set(self._rows[name])
        for table in (self._routes, self._pins, self._data):
            if name in table:
                return {table[name]}
        return set()

    def verdict(self, alias, target):
        """('ok' | 'wrong' | 'unknown', why)."""
        address = self.pinned(alias)
        if address is None:
            return "unknown", "alias has no pin or row"
        found = self.addresses(target)
        if not found:
            return "unknown", "target has no row or pin"
        want = self.normal(address)
        if any(candidate == address or self.normal(candidate) == want for candidate in found):
            return "ok", ""
        return "wrong", (f"alias pinned at 0x{address:08X} (body 0x{want:08X}), target at "
                         f"{', '.join(f'0x{a:08X}' for a in sorted(found))}")

    def respell(self, name):
        """(row name, why) for a pinned call name: the ledger's name for the
        body at its pinned address, the spelling a call must use to link.
        Authored game/ C++ first, then by name (link_census.alias_scaffold's
        rule). None when the address holds no C++ definition."""
        import build
        import link_census
        address = self.pinned(name) if (name in self._routes or name in self._pins) else None
        if address is None:
            return None, "not pinned"
        if self._naked is None:
            self._naked = link_census.naked_rows()
        for at in dict.fromkeys((address, self.normal(address))):
            owners = [row for row in self._by_address.get(at, ())
                      if not row["name"].startswith("?j_") and not link_census.build_dump(row, self._naked)]
            if owners:
                owners.sort(key=lambda r: (not (r["source"].startswith("game/") and not r["source"].startswith(
                    ("game/gen_small/", "game/gen_asm/"))), r["name"]))
                names = sorted({row["name"] for row in owners})
                chosen = build.ledger_object_symbol(owners[0])  # the symbol its object really defines
                if chosen == name:
                    return None, "already the row name"
                if self.verdict(name, chosen)[0] != "ok":
                    return None, "row fails the alias check"
                notes = [] if len(names) == 1 else [f"{len(names)} names at 0x{at:08X}"]
                if not name.startswith("?") and chosen.startswith("?"):
                    notes.append("a C name called as a C++ row: prove which name is right before respelling")
                return chosen, "; ".join(notes)
        return None, f"no C++ row at 0x{address:08X}"


def read_baseline(text=None):
    if text is None:
        text = BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else ""
    return {line.strip() for line in text.splitlines() if line.strip() and not line.startswith("#")}


def key(source, alias, target):
    return f"{source}: {alias}={target}"


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, encoding="utf-8",
                          errors="replace")


def scanned(path):
    return path.startswith(SCANNED) and path.endswith(SUFFIXES)


def tree_aliases():
    """{source: [(alias, target)]} for every tracked source holding one."""
    found = {}
    listed = git("grep", "-l", "-I", "-i", "alternatename", "--", *SCANNED).stdout.split("\n")
    for path in filter(None, listed):
        if not scanned(path):
            continue
        try:
            aliases = source_aliases((ROOT / path).read_text(encoding="utf-8", errors="replace"))
        except OSError:
            continue
        if aliases:
            found[path] = aliases
    return found


def judge_all(found, judge):
    """[(source, alias, target, verdict, why)]."""
    return [(source, alias, target, *judge.verdict(alias, target))
            for source, aliases in sorted(found.items()) for alias, target in aliases]


def staged(judge_factory=Judge):
    """Commit hook: a wrong alias in a staged source, or anywhere when a
    ledger is staged, fails unless the baseline lists it."""
    names = git("diff", "--cached", "--name-only", "--diff-filter=ACMR").stdout.split("\n")
    ledger_staged = any(path in LEDGERS for path in names)
    found = {}
    if ledger_staged:
        found = tree_aliases()
    for path in filter(None, names):
        if not scanned(path):
            continue
        text = git("show", f":{path}").stdout
        aliases = source_aliases(text)
        if aliases:
            found[path] = aliases
        else:
            found.pop(path, None)
    if not found:
        return 0
    baseline = read_baseline(git("show", ":" + BASELINE.relative_to(ROOT).as_posix()).stdout
                             if BASELINE.exists() else "")
    results = judge_all(found, judge_factory())
    bad = [r for r in results if r[3] == "wrong" and key(*r[:3]) not in baseline]
    unknown = [r for r in results if r[3] == "unknown"]
    if unknown:
        print(f"alias_guard: {len(unknown)} staged alias(es) cannot be judged (no pin for the alias or no "
              "address for the target); pin the alias so the census can check it", file=sys.stderr)
    if not bad:
        return 0
    print(f"alias_guard: {len(bad)} /alternatename alias(es) bind a call to a body other than the one it was "
          "matched against:", file=sys.stderr)
    for source, alias, target, _, why in bad:
        print(f"  {source}: {alias}={target}\n      {why}", file=sys.stderr)
    print("  Respell the call to the row name at the alias's pinned address (`link_check.py near` prints it), "
          "or fix the pin. Never add the line to the baseline.", file=sys.stderr)
    return 1


def report(write_baseline=False):
    results = judge_all(tree_aliases(), Judge())
    files = collections.defaultdict(set)
    for source, _, _, verdict, _ in results:
        files[verdict].add(source)
    counts = collections.Counter(r[3] for r in results)
    for source, alias, target, verdict, why in results:
        if verdict == "wrong":
            print(f"  wrong    {source}: {alias}={target}\n           {why}")
    print(f"alias_guard: {len(results):,} aliases in {len({r[0] for r in results}):,} sources: "
          f"{counts['ok']:,} ok, {counts['wrong']:,} wrong ({len(files['wrong'])} sources), "
          f"{counts['unknown']:,} unknown ({len(files['unknown'])} sources)")
    if write_baseline:
        if BASELINE.exists():
            raise SystemExit("alias_guard: the baseline exists and may only shrink; edit it by hand")
        lines = sorted(key(*r[:3]) for r in results if r[3] == "wrong")
        BASELINE.write_text(BASELINE_HEADER + "".join(line + "\n" for line in lines), encoding="utf-8")
        print(f"alias_guard: wrote {len(lines)} line(s) to {BASELINE.relative_to(ROOT).as_posix()}")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--report", action="store_true")
    mode.add_argument("--seed-baseline", action="store_true", help="write the first baseline (refused once it exists)")
    args = ap.parse_args(argv)
    if args.staged:
        return staged()
    return report(write_baseline=args.seed_baseline)


if __name__ == "__main__":
    sys.exit(main())
