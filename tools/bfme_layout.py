#!/usr/bin/env python3
"""Print what retail's layout of a class is known to be, member by member.

    python tools/bfme_layout.py Object            # one class (and its primary base chain)
    python tools/bfme_layout.py --grep Tunnel      # every class whose name matches
    python tools/bfme_layout.py --changed          # only members whose offset moved

Source: reverse/bfme_layouts.json, built by tools/layout_witness.py. Every row is a
WITNESS, not a declaration: a ZH-compiled body aligned instruction-for-instruction
with its retail twin, reading this+zh in ZH and this+bfme in retail. `votes/total`
is how many aligned accesses agreed on the retail offset; `alts` are the dissenting
offsets (a member read through a different base subobject usually explains them).
Members that keep their ZH offset are listed too -- a witnessed "unchanged" is worth
as much as a witnessed move when you are laying out a shim."""
import argparse, json, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
def load():
    return json.load(open(ROOT / 'reverse' / 'bfme_layouts.json', encoding='utf-8'))
def rows_for(rows, cls):
    return [r for r in rows if (r['owner'] or r['fn_class'] or '?') == cls]
def show(rows, cls, changed_only=False):
    rs = sorted(rows_for(rows, cls), key=lambda r: r['zh'])
    if not rs: return False
    print(f"{cls}  ({len(rs)} witnessed members)")
    for r in rs:
        if changed_only and r['bfme'] == r['zh']: continue
        mark = '   ' if r['bfme'] == r['zh'] else '-> '
        alts = ('  alts ' + ','.join(f'{k}x{v}' for k, v in r['alts'].items())) if r['alts'] else ''
        print(f"  {r['member']:36s} zh +0x{r['zh']:<5x} {mark}bfme +0x{r['bfme']:<5x} {r['votes']}/{r['total']}{alts}   e.g. {r['fns'][0][:50]}")
    return True
if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('cls', nargs='?'); ap.add_argument('--grep'); ap.add_argument('--changed', action='store_true')
    a = ap.parse_args(); rows = load()
    classes = sorted({r['owner'] or r['fn_class'] or '?' for r in rows})
    if a.grep: 
        for c in classes:
            if re.search(a.grep, c, re.I): show(rows, c, a.changed)
    elif a.cls:
        if not show(rows, a.cls, a.changed): print(f"{a.cls}: no witnessed members; classes: {len(classes)} (try --grep)")
    else:
        for c in classes: show(rows, c, True)
