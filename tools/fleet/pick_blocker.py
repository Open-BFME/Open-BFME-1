#!/usr/bin/env python3
"""Pick one SHARED BLOCKER for the unblock lane: the bodies, not one body.

Workers record `blocker=NAME` when a body stops on something a session cannot
solve alone (register allocation, an EH funclet shape, a class layout). Until
now those rows were only read when a lead happened to look at
fleet_report.py. This picker clusters the open dump bodies whose LATEST
verdict names a blocker, by family (tools/blockers.py), and hands the largest
servable cluster to ONE stronger session. When that session finds the lever,
it lists the bodies in reverse/unlocked.txt and the ordinary lanes finish them.

  python tools/fleet/pick_blocker.py --report          # every family, counts and examples
  python tools/fleet/pick_blocker.py [N] [--family F] [--dry]
Output: first line "RVAS: 0x.. 0x..", then "NOTE: <one paragraph>" (same
contract as pick_class.py, so launch_unblock.sh / brief.py --note-file work).
The attempt cap is NOT applied here: capped bodies are exactly the ones a
shared lever reopens. Leases, the touched cooldown, dead ends and suspect
boundaries still apply.
"""
import sys
import time
from pathlib import Path

sys.path.insert(0, "tools")
from portable_lock import lock  # noqa: E402
import blockers  # noqa: E402
import eligibility  # noqa: E402
import re_log  # noqa: E402

ROOT = Path(".").resolve()


def clusters(rows=None, records=None, latest=None, taken=()):
    """{family: [(size, rva, evidence)]} over open dumps, largest body first."""
    latest = eligibility.latest_verdicts() if latest is None else latest
    records = re_log.latest_records() if records is None else records
    out = {}
    for row in eligibility.open_dumps(rows, latest):
        rva = eligibility.rva_of(row)
        record = records.get(rva)
        if rva in taken or not record or eligibility.boundary_suspect(rva, records):
            continue
        for family in blockers.families(record[4]):
            out.setdefault(family, []).append((int(row.get("target_size") or 0), rva, record[4]))
    for members in out.values():
        members.sort(reverse=True)
    return out


def main():
    family = sys.argv[sys.argv.index("--family") + 1] if "--family" in sys.argv else None
    args = [a for a in sys.argv[1:] if not a.startswith("--") and a != family]
    want = int(args[0]) if args else 12
    handle = (ROOT / "build" / ".fleet_claims.lock").open("a")
    lock(handle, exclusive=True)
    taken = {int(a, 16) for a in eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)}
    found = clusters(taken=taken)
    if "--report" in sys.argv:
        for name, members in sorted(found.items(), key=lambda kv: -len(kv[1])):
            print(f"{name:14} {len(members):4} bodies {sum(m[0] for m in members):7} B   e.g. "
                  + " ".join(f"0x{m[1]:08X}" for m in members[:4]))
        return
    # "other" and "no-lever" name no shared problem; never serve them as one
    ranked = sorted(((n, m) for n, m in found.items() if n not in ("other", "no-lever") and len(m) >= 5
                     and (family is None or n == family)), key=lambda kv: -sum(x[0] for x in kv[1]))
    if not ranked:
        return
    name, members = ranked[0]
    picked = members[:want]
    if "--dry" not in sys.argv:
        with (ROOT / "build" / "fleet_logs" / "seats.log").open("a") as log:
            log.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(f'0x{m[1]:08x}' for m in picked)}\n")
    print("RVAS: " + " ".join(f"0x{m[1]:08X}" for m in picked))
    examples = " | ".join(f"0x{m[1]:08X}: {m[2][:160]}" for m in picked[:3])
    print(f"NOTE: SHARED BLOCKER `{name}`: {len(members)} open bodies ({sum(m[0] for m in members)} B) stop on the same "
          f"family of problem; these {len(picked)} are the largest. Do NOT grind one body. Read the banked stashes and "
          f"evidence of all of them, find what they have in common, and look for ONE lever (a compiler flag, a source "
          f"idiom, a class layout, a declaration) that moves several at once; prove it with probe.py on at least three. "
          f"Land what becomes EXACT with add_match.py. Then append every body the lever applies to -- including ones "
          f"not in this brief -- to reverse/unlocked.txt as `0x%08x {name}`, and record the lever itself in "
          f"docs/shape_levers.md so ordinary seats can finish them. If no shared lever exists, say so in a `blocked` "
          f"verdict with blocker={name}/<what differs between them>. Evidence so far: {examples}")


if __name__ == "__main__":
    main()
