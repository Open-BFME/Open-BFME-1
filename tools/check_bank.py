#!/usr/bin/env python3
"""Say whether a banked attempt body can be measured as it is saved.

  python3 tools/check_bank.py 0x0048ACF0 [0xRVA ...]
  python3 tools/check_bank.py --all [--min-score 0.5]

A stash under reverse/attempts/ is the starting point of the next attempt on
that body, and its header score ranks it for serving. That score is an author
estimate. This tool reports the two facts the next agent otherwise spends its
first probes finding out:

  ok            the file compiles alone and defines the symbol on its first line;
                prints compiled size, retail size and non-relocation byte diffs
  other-symbol  it compiles, but defines the body under another name (a renamed
                class, a different bool or calling convention); prints that name
  no-compile    it does not compile alone, usually because it is an excerpt of a
                live translation unit; prints the first compiler error

Read-only: it compiles copies under build/ and never touches the ledgers, the
stash or the attempt log. Exit status is 1 when any checked bank is not `ok`.
The diff count compares position by position, so one early extra instruction
makes a close body look distant; read it as a lower bound on closeness.
"""
import argparse
import difflib
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = Path(__file__).resolve().parents[1]
ATTEMPTS = ROOT / "reverse" / "attempts"
WORK = ROOT / "build" / "check-bank"


def header_symbol(text):
    """The mangled symbol that leads a stash's first line, or None; a note may follow it."""
    first = text.splitlines()[0] if text else ""
    match = re.match(r"^//\s*([?@_]\S*)", first)
    return match.group(1) if match else None


def nearest_symbol(defined, wanted):
    """The defined function symbol closest to the wanted one, or None."""
    names = sorted({s for s in defined if s.startswith(("?", "_", "@"))
                    and not s.startswith(("$", ".", "__real", "??_C"))})
    if not names:
        return None
    return max(names, key=lambda n: difflib.SequenceMatcher(None, n, wanted).ratio())


def first_error(message):
    match = re.search(r"\) : (?:fatal )?error (C\d+: [^\r\n]*)", message)
    return match.group(1)[:140] if match else (message.strip().splitlines() or ["compile failed"])[-1][:140]


def compile_quietly(source):
    """Compile through the experiment cache in a child, so the compiler's printout becomes the error text."""
    run = subprocess.run([sys.executable, str(Path(__file__).resolve()), "--compile", str(source)],
                         cwd=ROOT, capture_output=True, text=True, encoding="utf-8", errors="replace")
    lines = run.stdout.strip().splitlines()
    if run.returncode or not lines or not Path(lines[-1]).is_file():
        raise RuntimeError(run.stdout + run.stderr)
    return Path(lines[-1])


def measure(obj, symbol, rva, size):
    """(compiled size, non-relocation byte diffs) of one symbol against retail."""
    from probe import masked
    compiled, relocs = build.read_object_symbol_bytes(obj, symbol)
    compiled = bytes(compiled)
    image = Path(build.EXE).read_bytes()
    offset = build.rva_to_file_offset(build.pe_sections(image), rva)
    retail = image[offset:offset + size]
    ours, theirs = masked(compiled, relocs), masked(retail, relocs)
    return len(compiled), sum(1 for i in range(min(len(ours), len(theirs))) if ours[i] != theirs[i])


def check(rva, size, compile_source=None):
    """(state, detail) for the stash at rva; compile_source is injectable for tests."""
    path = ATTEMPTS / f"0x{rva:08x}.cpp"
    if not path.exists():
        return "missing", "no stash"
    symbol = header_symbol(path.read_text(encoding="utf-8-sig", errors="replace"))
    if not symbol:
        return "bad-header", "line 1 does not name a symbol"
    WORK.mkdir(parents=True, exist_ok=True)
    copy = WORK / path.name
    shutil.copyfile(path, copy)
    # A stash whose `// cl:` line asks for a listing makes the compiler write one into the working directory.
    listings = [ROOT / f"{copy.stem}{suffix}" for suffix in (".cod", ".asm", ".lst")]
    listings = [listing for listing in listings if not listing.exists()]
    try:
        try:
            obj = (compile_source or compile_quietly)(copy)
        except RuntimeError as error:
            return "no-compile", first_error(str(error))
        defined = [s["name"] for s in build.read_object_symbols(obj.read_bytes()) if s["section"] > 0]
        if symbol not in defined:
            return "other-symbol", nearest_symbol(defined, symbol) or "no function symbol defined"
        compiled, diffs = measure(obj, symbol, rva, size)
        return "ok", f"ours={compiled} retail={size} diffs={diffs}"
    finally:
        for leftover in [copy, *listings]:
            leftover.unlink(missing_ok=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("rvas", nargs="*", help="retail RVAs as in the ledger")
    parser.add_argument("--all", action="store_true", help="every open dump row that has a stash")
    parser.add_argument("--min-score", type=float, default=0.0, help="with --all: only stashes at or above this score")
    parser.add_argument("--compile", help=argparse.SUPPRESS)
    args = parser.parse_args()
    if args.compile:
        from experiment_store import compile_cached
        print(compile_cached(Path(args.compile))[0])
        return
    if bool(args.rvas) == args.all:
        parser.error("name RVAs or pass --all")
    import eligibility
    sizes = {eligibility.rva_of(row): int(row.get("target_size") or 0) for row in eligibility.load_rows()}
    if args.all:
        targets = [eligibility.rva_of(row) for row, _path, _score in eligibility.finish_bodies(args.min_score)]
    else:
        targets = [int(text, 16) for text in args.rvas]
    bad = 0
    for rva in targets:
        if not sizes.get(rva):
            state, detail = "no-row", "no ledger row with a size for this RVA"
        else:
            state, detail = check(rva, sizes[rva])
        bad += state != "ok"
        print(f"0x{rva:08X}  {state:<13} {detail}", flush=True)
    print(f"{len(targets) - bad} ok, {bad} not ok of {len(targets)}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
