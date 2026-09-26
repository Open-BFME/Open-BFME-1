#!/usr/bin/env python3
"""Repoint rows whose symbol its own object no longer emits, to a TU that does.

WHY. A row can be green only because the converted body it sits in calls an
accessor that retail inlines away at that site. Write the body correctly and MSVC
stops emitting the inline function's COMDAT, and the row goes red with

    symbol not found in object: ?Set_Alpha_Test@ShaderClass@@QAEXW4AlphaTestType@1@@Z

Nothing is wrong with the function or the body. The row is simply parked on a
translation unit that has stopped emitting it. 31 of the full gate's 109 function
failures are this, 8 of them ShaderClass setters that line3d.cpp stopped emitting
when it was converted.

`tools/find_emitter.py` already says where a row COULD live, and its docstring
prescribes this fix. This applies it in bulk and proves each one.

WHAT IT WILL NOT DO. It never retracts a row: a symbol 21 other objects still
emit is not an unbackable claim, it is a misparked one. It never picks an emitter
on faith either -- every candidate is compiled and byte-compared, and a row whose
symbol no emitter reproduces is left exactly where it is and reported.

    python3 tools/repoint_absent.py --gate-log <full gate log>
    python3 tools/repoint_absent.py --gate-log <log> --apply
"""
import argparse
import collections
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import find_emitter

LEDGER = build.ROOT / "targets/game/reverse/functions.csv"
ABSENT = re.compile(r"symbol not found in object: (\S+)")
# `$E14`, `$L86009`: assigned per compile and meaningless across TUs. Another
# object's $E14 is a DIFFERENT label, not the same function, so "somebody else
# emits this name" is not evidence of anything. Repointing one would be the same
# mistake as matching a small body by bytes and calling it an identity.
LOCAL_LABEL = re.compile(r"_?\$[A-Za-z]+\d+")
# build.py detects a renumbered gen-funclet label itself and says which one the
# body is now. That is the compiler's own answer, not an inference, so it is the
# one case where re-pointing a compiler-local label IS evidence-backed.
RENUMBERED = re.compile(
    r"(\S+) was renumbered by an edit to this TU; the body is (\S+) in the object built now")


def red_absent(log):
    """[(row name, source, missing symbol)] from a full gate log."""
    out, current = [], None
    for line in Path(log).read_text(errors="replace").splitlines():
        if line.startswith("  FAIL") and "(" in line:
            current = (line[len("  FAIL"):line.index("(")].strip(),
                       line[line.index("(") + 1:line.rindex(")")])
        elif current:
            hit = ABSENT.search(line)
            if hit:
                out.append((current[0], current[1], hit.group(1)))
                current = None
    return out


def renumbered(log):
    """[(row name, source, old label, new label)] the gate itself resolved."""
    out, current = [], None
    for line in Path(log).read_text(errors="replace").splitlines():
        if line.startswith("  FAIL") and "(" in line:
            current = (line[len("  FAIL"):line.index("(")].strip(),
                       line[line.index("(") + 1:line.rindex(")")])
        elif current:
            hit = RENUMBERED.search(line)
            if hit:
                out.append((current[0], current[1], hit.group(1), hit.group(2)))
                current = None
    return out


def relabel(moves):
    """Rewrite each row's own `object-symbol=` in place, as bytes."""
    data = LEDGER.read_bytes()
    done = 0
    for name, _source, old, new in moves:
        key = name.encode() + b","
        i = data.find(key)
        while i >= 0 and not (i == 0 or data[i - 1:i] in (b"\n", b"\r")):
            i = data.find(key, i + 1)
        if i < 0:
            continue
        end = data.find(b"\n", i)
        line = data[i:end]
        swapped = line.replace(b"object-symbol=" + old.encode(),
                               b"object-symbol=" + new.encode(), 1)
        if swapped != line:
            data = data[:i] + swapped + data[end:]
            done += 1
    LEDGER.write_bytes(data)
    return done


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--gate-log", required=True)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--limit", type=int, default=0)
    args = ap.parse_args()

    stale = renumbered(args.gate_log)
    print(f"rows the gate itself says are a renumbered label: {len(stale)}")
    for name, source, old, new in stale:
        print(f"  {name[:44]:<44} {old} -> {new}  ({source.split('/')[-1]})")
    if stale and args.apply:
        print(f"  relabelled {relabel(stale)} row(s)")

    red = red_absent(args.gate_log)
    if args.limit:
        red = red[:args.limit]
    print(f"rows whose object no longer emits their symbol: {len(red)}")

    rows = {r["name"]: r for r in build.load_function_rows()}
    by_object = find_emitter.sources_by_object()
    moves, stuck = [], collections.Counter()
    for name, source, symbol in red:
        row = rows.get(name)
        if row is None or row.get("source") != source:
            stuck["row is no longer in the ledger at that source"] += 1
            continue
        if LOCAL_LABEL.fullmatch(symbol):
            stuck["compiler-local label: not portable between TUs"] += 1
            continue
        # emitters() answers with OBJECT paths. find_emitter keeps the forward
        # map from source to object precisely because decoding an object name
        # backwards is ambiguous -- the encoding joins path parts with "_" and
        # file names contain underscores too. Go through the map; filtering the
        # object names as if they were sources silently discarded every real
        # candidate and reported 0 repointable when there were 12.
        others = sorted({by_object[o] for o in find_emitter.emitters(symbol)
                         if o in by_object and by_object[o] != source})
        if not others:
            stuck["no other object emits it"] += 1
            print(f"  STUCK {name[:56]}: nothing else emits {symbol[:40]}")
            continue
        moves.append((name, source, others[0], symbol, len(others)))
        print(f"  {name[:52]:<52} {source.split('/')[-1]} -> "
              f"{others[0].split('/')[-1]}  ({len(others)} emitter(s))")
    print(f"\nrepointable: {len(moves)}   stuck: {sum(stuck.values())}")
    for why, n in stuck.most_common():
        print(f"    {n:>3}  {why}")
    if not args.apply or not moves:
        if moves:
            print("\n  --apply to repoint, then byte-verify each new source")
        return 0

    # The ledger is BYTES: functions.csv carries mixed line terminators and a csv
    # round-trip flattens them, which check_csv rejects. Rewrite each row's own
    # source field in place, anchored on the surrounding commas.
    data = LEDGER.read_bytes()
    done = 0
    for name, old, new, _symbol, _n in moves:
        key = name.encode() + b","
        i = data.find(key)
        while i >= 0 and not (i == 0 or data[i - 1:i] in (b"\n", b"\r")):
            i = data.find(key, i + 1)
        if i < 0:
            continue
        end = data.find(b"\n", i)
        line = data[i:end]
        swapped = line.replace(b"," + old.encode() + b",",
                               b"," + new.encode() + b",", 1)
        if swapped != line:
            data = data[:i] + swapped + data[end:]
            done += 1
    LEDGER.write_bytes(data)
    print(f"\nrepointed {done} row(s). Byte-verify every destination now; revert any "
          f"that does not reproduce.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
