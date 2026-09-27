#!/usr/bin/env python3
"""Shared body claims on origin: one ref per body, visible to every host.

WHY. Every lane kept its claims locally -- fleet_run's lease database, the
astra seats' seats.json, each contributor's own build/ -- so nobody saw anyone
else's work in progress. On 2026-09-27 three bodies were converted twice
(0x003CA480 landed upstream at the very path a seat was writing, 0x001C4CC0,
and a bank that appeared at 0x008FA4B0 mid-seat), and each duplicate threw a
seat's work away.

HOW. A claim is the ref `refs/claims/0xRVA` on origin, pointing at a tiny
parentless commit whose message is JSON {owner, host, expires}. Creating a ref
that already exists is refused by a non-forced push, so a claim is atomic
across hosts with no server to run; `--atomic` makes a multi-body claim
all-or-nothing per attempt. An expired claim is taken over with
`--force-with-lease=<ref>:<old>` (compare-and-swap), and a release deletes a
ref only if it is still the owner's. Refs under refs/claims/ are not branches:
nobody checks them out or merges them, and nothing about pushing to master
changes.

eligibility.busy_rvas() includes every live claim, so every picker that asks
it (next_work, brief, pick_anon, pick_big, gap_seats, astra_seats, ...) skips
claimed bodies. fleet_run and astra_seats claim what they serve; add_match
releases the landed body's claim.

  python3 tools/claims.py list                 # live claims
  python3 tools/claims.py claim 0xRVA [...]    # claim for this host (TTL 4 h)
  python3 tools/claims.py release 0xRVA [...]  # release your own claims

Network trouble never blocks work: every entry point warns and carries on
without claims, which is exactly today's behaviour.
"""
import argparse
import json
import os
import socket
import subprocess
import sys
import time
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NS = "refs/claims/"
SEEN = "refs/claims-seen/"          # local mirror; never pushed
TTL_HOURS = float(os.environ.get("BFME_CLAIM_TTL_HOURS", "4"))
REMOTE = os.environ.get("BFME_CLAIM_REMOTE", "origin")


def _git(*args, cwd=None, input_text=None, timeout=60):
    return subprocess.run(["git", *args], cwd=cwd or ROOT, capture_output=True, text=True,
                          input=input_text, timeout=timeout)


def owner():
    """Who holds a claim: BFME_CLAIM_OWNER, else `<git user.name>@<host>`."""
    explicit = os.environ.get("BFME_CLAIM_OWNER")
    if explicit:
        return explicit
    name = _git("config", "user.name").stdout.strip() or "unknown"
    return f"{name}@{socket.gethostname()}"


def ref_of(rva):
    return f"{NS}0x{int(rva, 16) if isinstance(rva, str) else rva:08X}"


def _record(who, ttl_hours, note=""):
    """A parentless commit carrying the claim JSON; returns its sha."""
    tree = _git("mktree", input_text="").stdout.strip()
    body = json.dumps({"owner": who, "host": socket.gethostname(), "note": note,
                       "expires": int(time.time() + ttl_hours * 3600)}, sort_keys=True)
    made = _git("-c", "user.name=claims", "-c", "user.email=claims@localhost",
                "commit-tree", tree, "-m", body)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    return made.stdout.strip()


def fetch():
    """Mirror origin's claims locally (refs/claims-seen/*); False on failure."""
    got = _git("fetch", "-q", "--prune", "--no-tags", REMOTE, f"+{NS}*:{SEEN}*", timeout=120)
    return got.returncode == 0


def _read_local():
    """{rva: (sha, info)} from the local mirror."""
    out = _git("for-each-ref", "--format=%(refname)%09%(objectname)%09%(contents:subject)", SEEN).stdout
    claims = {}
    for line in out.splitlines():
        name, sha, subject = (line.split("\t") + ["", ""])[:3]
        try:
            rva = int(name.rsplit("/", 1)[1], 16)
            info = json.loads(subject)
        except (ValueError, IndexError):
            continue
        claims[rva] = (sha, info)
    return claims


def live(claims, now=None):
    now = now or time.time()
    return {rva: v for rva, v in claims.items() if v[1].get("expires", 0) > now}


@lru_cache(maxsize=1)
def active():
    """{rva: info} of every unexpired claim on origin, fetched once per process.
    Empty (with a warning) when origin cannot be reached."""
    if not fetch():
        print("claims: could not fetch refs/claims/* from origin; serving without shared claims",
              file=sys.stderr)
        return {}
    return {rva: info for rva, (_, info) in live(_read_local()).items()}


def claim(rvas, who=None, ttl_hours=TTL_HOURS, note=""):
    """Claim `rvas` on origin. Returns (claimed, refused) lists of ints.

    Tries all-or-nothing first (--atomic); if another host holds one, claims
    the rest individually. A claim of ours is renewed; an expired claim is
    taken over by compare-and-swap. Raises nothing on network trouble: the
    bodies come back as claimed=[] and refused=[] with a warning."""
    who = who or owner()
    rvas = sorted({int(r, 16) if isinstance(r, str) else int(r) for r in rvas})
    if not rvas:
        return [], []
    if not fetch():
        print("claims: origin unreachable; claiming nothing", file=sys.stderr)
        return [], []
    current = _read_local()
    now = time.time()
    held = {r for r in rvas if r in current and current[r][1].get("expires", 0) > now
            and current[r][1].get("owner") != who}
    wanted = [r for r in rvas if r not in held]
    sha = _record(who, ttl_hours, note)

    def spec(rva):
        old = current.get(rva)
        return (f"--force-with-lease={ref_of(rva)}:{old[0]}" if old else None,
                f"{sha}:{ref_of(rva)}" if not old else f"+{sha}:{ref_of(rva)}")

    def push(batch):
        leases = [s[0] for s in map(spec, batch) if s[0]]
        refspecs = [spec(r)[1] for r in batch]
        return _git("push", "-q", "--atomic", *leases, REMOTE, *refspecs, timeout=120).returncode == 0

    claimed = []
    if wanted and push(wanted):
        claimed = wanted
    else:
        for rva in wanted:              # somebody raced us for part of the batch
            if push([rva]):
                claimed.append(rva)
    refused = sorted(set(rvas) - set(claimed))
    active.cache_clear()
    return claimed, refused


def release(rvas, who=None, force=False):
    """Delete claims we own (or any, with force). Returns released ints."""
    who = who or owner()
    if not fetch():
        print("claims: origin unreachable; releasing nothing (claims expire on their own)", file=sys.stderr)
        return []
    current = _read_local()
    done = []
    for rva in sorted({int(r, 16) if isinstance(r, str) else int(r) for r in rvas}):
        entry = current.get(rva)
        if not entry or (entry[1].get("owner") != who and not force):
            continue
        gone = _git("push", "-q", f"--force-with-lease={ref_of(rva)}:{entry[0]}", REMOTE,
                    f":{ref_of(rva)}", timeout=120)
        if gone.returncode == 0:
            done.append(rva)
    active.cache_clear()
    return done


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["list", "claim", "release"])
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--note", default="")
    ap.add_argument("--force", action="store_true", help="release: also claims owned by others")
    args = ap.parse_args(argv)
    if args.action == "list":
        claims = active()
        for rva, info in sorted(claims.items()):
            left = (info.get("expires", 0) - time.time()) / 3600
            print(f"0x{rva:08X}  {info.get('owner', '?'):30} {left:5.1f} h left  {info.get('note', '')}")
        print(f"{len(claims)} live claim(s)")
        return 0
    if args.action == "claim":
        got, refused = claim(args.rvas, note=args.note)
        print(f"claimed {len(got)}: {' '.join(f'0x{r:08X}' for r in got)}")
        if refused:
            print(f"held by someone else: {' '.join(f'0x{r:08X}' for r in refused)}")
        return 0 if not refused else 1
    done = release(args.rvas, force=args.force)
    print(f"released {len(done)}: {' '.join(f'0x{r:08X}' for r in done)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
