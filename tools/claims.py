#!/usr/bin/env python3
"""Shared body claims on origin: one ref per body, visible to every host.

WHY. Every lane kept its claims locally -- fleet_run's lease database, the
astra seats' seats.json, each contributor's own build/ -- so nobody saw anyone
else's work in progress. On 2026-09-27 three bodies were converted twice
(0x003CA480 landed upstream at the very path a seat was writing, 0x001C4CC0,
and a bank that appeared at 0x008FA4B0 mid-seat), and each duplicate threw a
seat's work away.

HOW. A claim is the ref `refs/claims/0xRVA` on origin, pointing at a tiny
parentless commit whose message is JSON {owner, host, run, nonce, created,
expires}. Creating a ref that already exists is refused by a non-forced push,
so a claim is atomic across hosts with no server to run; `--atomic` makes a
multi-body claim all-or-nothing per attempt. An expired claim is taken over
with `--force-with-lease=<ref>:<old>` (compare-and-swap), and a release deletes
a ref only if it is still the owner's. Refs under refs/claims/ are not
branches: nobody checks them out or merges them, and nothing about pushing to
master changes.

eligibility.busy_rvas() includes every live claim, so every picker that asks
it (next_work, brief, pick_anon, pick_big, gap_seats, astra_seats, ...) skips
claimed bodies. fleet_run and astra_seats claim what they serve.

  python3 tools/claims.py list                 # live claims
  python3 tools/claims.py whoami               # this worker's owner string
  python3 tools/claims.py claim 0xRVA [...]    # claim for this worker (TTL 4 h)
  python3 tools/claims.py release 0xRVA [...]  # release your own claims
  python3 tools/claims.py release --landed [SHA]
      # release claims whose rows are ON origin/master (SHA: that commit's rows)

FAIL-CLOSED (2026-09-29, linking_plan.md workstream G). claim() used to
return ([], []) when origin was unreachable, which a caller cannot tell from
"nothing to claim", and fleet_run started work either way. Now:
  * claim() raises ClaimsUnavailable when origin cannot be fetched, and lists
    a body as claimed only when origin accepted the push. A body whose push
    failed is re-read from origin: held by another worker -> refused; not
    held by anyone -> refused AND listed in result.unconfirmed.
  * WORKER IDENTITY is BFME_CLAIM_OWNER, else `fleet:<BFME_RUN_ID>` inside a
    fleet run, else `<user>@<host>/<checkout hash>` -- one per worktree, never
    one string shared by every seat on a host.
  * FENCING: the claim commit's sha is the token (result.tokens). renew()
    (the heartbeat) and release(tokens=...) compare-and-swap on it, so a
    worker whose claim expired and was taken over learns it lost the body
    instead of overwriting or deleting the successor's claim. holds() asks
    origin whether a token is still current.
  * add_match no longer releases on LOCAL verification: it queues the row in
    build/claims/landed_pending.jsonl and `release --landed` (fleet_run runs
    it when a seat ends) releases a claim only once origin/master holds that
    exact row. Anything never settled expires with its TTL.
Readers (active(), eligibility.busy_rvas) still warn and serve without shared
claims when origin is unreachable: a picker only proposes, the claim decides.
"""
import argparse
import hashlib
import json
import os
import socket
import subprocess
import sys
import threading
import time
import uuid
from contextlib import contextmanager
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NS = "refs/claims/"
SEEN = "refs/claims-seen/"          # local mirror; never pushed
TTL_HOURS = float(os.environ.get("BFME_CLAIM_TTL_HOURS", "4"))
REMOTE = os.environ.get("BFME_CLAIM_REMOTE", "origin")
PENDING = Path("build") / "claims" / "landed_pending.jsonl"
LEDGER = "targets/game/reverse/functions.csv"


class ClaimsUnavailable(RuntimeError):
    """Origin could not be reached or read back: nothing is known to be
    claimed. `claimed` lists bodies origin DID accept before the failure (the
    caller should release them or let them expire)."""

    def __init__(self, message, claimed=()):
        super().__init__(message)
        self.claimed = list(claimed)


class ClaimResult(tuple):
    """(claimed, refused) -- still unpacks and compares like the old tuple --
    plus `tokens` {rva: claim sha} for fencing, `unconfirmed` (the part of
    refused whose push failed while nobody else held the body) and `worker`,
    the owner string written into each claim."""

    def __new__(cls, claimed, refused, tokens=None, unconfirmed=(), worker="", leases=None):
        self = tuple.__new__(cls, (list(claimed), list(refused)))
        self.tokens = dict(tokens or {})
        # the LEASE id survives renewals (the token rotates every heartbeat),
        # so it is what a queued unit refers to; see lease_holder()
        self.leases = dict(leases or {})
        self.unconfirmed = list(unconfirmed)
        self.worker = worker
        return self

    @property
    def claimed(self):
        return self[0]

    @property
    def refused(self):
        return self[1]


def _git(*args, cwd=None, input_text=None, timeout=60):
    cwd = cwd or ROOT
    hooks = Path(cwd) / ".githooks"
    # Run THIS checkout's hooks, not whatever core.hooksPath points at: a host
    # whose hooksPath names an older checkout would run a pre-push that tries
    # to verify a claim marker as if it were code. The hooks still run.
    extra = ["-c", f"core.hooksPath={hooks.as_posix()}"] if args[:1] == ("push",) and hooks.is_dir() else []
    # Never let git discover a repository ABOVE `cwd`: a fixture directory
    # inside a real checkout (pytest's basetemp under build/) otherwise
    # inherits that checkout's origin, and a "no remote" test created real
    # claims on Open-BFME-1 (review 2026-09-29). Every caller passes a
    # checkout root, so discovery may start there and nowhere else.
    env = dict(os.environ, GIT_CEILING_DIRECTORIES=str(Path(cwd).resolve().parent))
    try:
        return subprocess.run(["git", *extra, *args], cwd=cwd, capture_output=True, text=True,
                              input=input_text, timeout=timeout, env=env)
    except subprocess.TimeoutExpired as error:
        return subprocess.CompletedProcess(error.cmd, 124, "", f"timed out after {timeout}s")


def owner(root=None):
    """The worker that holds a claim. BFME_CLAIM_OWNER wins; a fleet run is
    `fleet:<BFME_RUN_ID>` (the owner fleet_run claims under, so a tool the
    seat runs acts as the same worker); otherwise `<user>@<host>/<checkout>`
    with a short hash of the checkout path. The old `<user>@<host>` was shared
    by every seat on a host, so any seat could renew or release another's."""
    explicit = os.environ.get("BFME_CLAIM_OWNER")
    if explicit:
        return explicit
    run = os.environ.get("BFME_RUN_ID", "")
    if run:
        return f"fleet:{run}"
    name = _git("config", "user.name", cwd=root).stdout.strip() or "unknown"
    top = _git("rev-parse", "--show-toplevel", cwd=root).stdout.strip() or str(root or ROOT)
    tag = hashlib.sha1(os.path.normcase(os.path.abspath(top)).encode("utf-8")).hexdigest()[:8]
    return f"{name}@{socket.gethostname()}/{tag}"


def ref_of(rva):
    return f"{NS}0x{int(rva, 16) if isinstance(rva, str) else rva:08X}"


def _ints(rvas):
    return sorted({int(r, 16) if isinstance(r, str) else int(r) for r in rvas})


def _record(who, ttl_hours, note="", root=None, lease=None):
    """A parentless commit carrying the claim JSON; returns its sha, which is
    the claim's fencing token (the nonce makes every claim's sha unique).
    `lease` is kept across renewals; a fresh claim starts a new one."""
    tree = _git("mktree", input_text="", cwd=root).stdout.strip()
    now = time.time()
    nonce = uuid.uuid4().hex
    body = json.dumps({"owner": who, "host": socket.gethostname(), "note": note,
                       "run": os.environ.get("BFME_RUN_ID", ""), "nonce": nonce,
                       "lease": lease or nonce,
                       "created": int(now), "expires": int(now + ttl_hours * 3600)}, sort_keys=True)
    made = _git("-c", "user.name=claims", "-c", "user.email=claims@localhost",
                "commit-tree", tree, "-m", body, cwd=root)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    return made.stdout.strip()


def configured(root=None):
    """Whether `root` is itself a checkout (not a directory inside one) with
    the claims remote configured. A fixture directory without one has nobody
    to coordinate with; a real checkout whose origin is unreachable is
    configured and fails closed."""
    top = _git("rev-parse", "--show-toplevel", cwd=root)
    same = os.path.normcase(os.path.realpath(top.stdout.strip() or "?")) == \
        os.path.normcase(os.path.realpath(str(root or ROOT)))
    return top.returncode == 0 and same and _git("remote", "get-url", REMOTE, cwd=root).returncode == 0


def fetch(root=None):
    """Mirror origin's claims locally (refs/claims-seen/*); False on failure."""
    got = _git("fetch", "-q", "--prune", "--no-tags", REMOTE, f"+{NS}*:{SEEN}*", cwd=root, timeout=120)
    return got.returncode == 0


def _read_local(root=None):
    """{rva: (sha, info)} from the local mirror."""
    out = _git("for-each-ref", "--format=%(refname)%09%(objectname)%09%(contents:subject)", SEEN,
               cwd=root).stdout
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


def active(root=None):
    """{rva: info} of every unexpired claim on the origin of `root` (this
    checkout by default), fetched once per process per root. Empty (with a
    warning) when that origin cannot be reached: a fixture repository with no
    remote sees no claims, so a picker under test never inherits this
    checkout's live shared claims."""
    return dict(_active(str(Path(root).resolve()) if root else None))


@lru_cache(maxsize=8)
def _active(root):
    if not fetch(root):
        print("claims: could not fetch refs/claims/* from origin; serving without shared claims",
              file=sys.stderr)
        return {}
    return {rva: info for rva, (_, info) in live(_read_local(root)).items()}


active.cache_clear = _active.cache_clear


def claim(rvas, who=None, ttl_hours=TTL_HOURS, note="", root=None):
    """Claim `rvas` on origin. Returns a ClaimResult (claimed, refused).

    Tries all-or-nothing first (--atomic); if that fails, claims the rest one
    by one. A claim of ours is renewed; an expired claim is taken over by
    compare-and-swap. A body counts as claimed only when origin accepted it.
    Raises ClaimsUnavailable when origin cannot be fetched, or when no push
    succeeded and nobody else holds the bodies (network trouble, not a race)."""
    who = who or owner(root)
    rvas = _ints(rvas)
    if not rvas:
        return ClaimResult([], [], worker=who)
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/* from origin; nothing claimed")
    current = _read_local(root)
    now = time.time()
    held = {r for r in rvas if r in current and current[r][1].get("expires", 0) > now
            and current[r][1].get("owner") != who}
    wanted = [r for r in rvas if r not in held]
    lease = uuid.uuid4().hex
    sha = _record(who, ttl_hours, note, root, lease=lease)

    def spec(rva):
        old = current.get(rva)
        return (f"--force-with-lease={ref_of(rva)}:{old[0]}" if old else None,
                f"{sha}:{ref_of(rva)}" if not old else f"+{sha}:{ref_of(rva)}")

    def push(batch):
        leases = [s[0] for s in map(spec, batch) if s[0]]
        refspecs = [spec(r)[1] for r in batch]
        return _git("push", "-q", "--atomic", *leases, REMOTE, *refspecs,
                    cwd=root, timeout=120).returncode == 0

    claimed, failed = [], []
    if wanted and push(wanted):
        claimed = list(wanted)
    else:
        for rva in wanted:              # somebody raced us for part of the batch
            (claimed if push([rva]) else failed).append(rva)
    unconfirmed = []
    if failed:
        # A failed push is either a lost race or network trouble; origin says which.
        if not fetch(root):
            active.cache_clear()
            raise ClaimsUnavailable("claims: push failed and origin cannot be re-read; "
                                    "only the bodies in .claimed are held", claimed=claimed)
        after = _read_local(root)
        for rva in failed:
            entry = after.get(rva)
            if entry and entry[0] == sha:               # accepted; the reply was lost
                claimed.append(rva)
            elif not (entry and entry[1].get("expires", 0) > time.time()
                      and entry[1].get("owner") != who):
                unconfirmed.append(rva)
        if unconfirmed and not claimed and len(unconfirmed) == len(wanted):
            active.cache_clear()
            raise ClaimsUnavailable("claims: origin accepted no claim push and nobody else holds "
                                    "the bodies; nothing claimed")
    claimed = sorted(claimed)
    refused = sorted(set(rvas) - set(claimed))
    active.cache_clear()
    return ClaimResult(claimed, refused, tokens={r: sha for r in claimed},
                       leases={r: lease for r in claimed},
                       unconfirmed=sorted(unconfirmed), worker=who)


def renew(tokens, who=None, ttl_hours=TTL_HOURS, note="", root=None):
    """Heartbeat: extend claims we still hold. `tokens` is {rva: sha} from a
    ClaimResult or an earlier renew. Each ref is compare-and-swapped against
    its token, so a claim that expired and was taken over is reported lost,
    never overwritten. Returns (renewed {rva: new sha}, lost [rva]); raises
    ClaimsUnavailable when origin cannot be read."""
    who = who or owner(root)
    tokens = {int(r, 16) if isinstance(r, str) else int(r): t for r, t in tokens.items()}
    if not tokens:
        return {}, []
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/* to renew")
    current = _read_local(root)
    renewed, lost = {}, []
    for rva, token in sorted(tokens.items()):
        entry = current.get(rva)
        if not entry or entry[0] != token or entry[1].get("owner") != who:
            lost.append(rva)
            continue
        sha = _record(who, ttl_hours, note or entry[1].get("note", ""), root,
                      lease=entry[1].get("lease") or token)
        pushed = _git("push", "-q", f"--force-with-lease={ref_of(rva)}:{token}", REMOTE,
                      f"+{sha}:{ref_of(rva)}", cwd=root, timeout=120)
        if pushed.returncode == 0:
            renewed[rva] = sha
            continue
        if not fetch(root):
            raise ClaimsUnavailable("claims: renew push failed and origin cannot be re-read")
        entry = _read_local(root).get(rva)
        if entry and entry[0] == sha:
            renewed[rva] = sha
        elif entry and entry[0] == token:
            raise ClaimsUnavailable(f"claims: origin did not accept the renewal of {ref_of(rva)}")
        else:
            lost.append(rva)
    active.cache_clear()
    return renewed, lost


def lease_holder(rva, lease, root=None):
    """The CURRENT token of the live claim on `rva` that belongs to `lease`
    (a lease id from ClaimResult.leases, or a claim sha from any renewal of
    it), else None. A publisher reads this right before its atomic push and
    leases the ref at the returned token, so a heartbeat's rotation neither
    invalidates a queued unit nor lets a taken-over claim publish. Raises
    ClaimsUnavailable when origin cannot be read."""
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/*")
    entry = _read_local(root).get(int(rva, 16) if isinstance(rva, str) else int(rva))
    if not entry or entry[1].get("expires", 0) <= time.time():
        return None
    return entry[0] if lease in (entry[0], entry[1].get("lease")) else None


def holds(rva, token, root=None):
    """True when origin's claim ref for `rva` is still exactly `token` (the
    fencing check a publisher makes before landing). Raises ClaimsUnavailable
    when origin cannot be asked."""
    got = _git("ls-remote", REMOTE, ref_of(rva), cwd=root, timeout=120)
    if got.returncode:
        raise ClaimsUnavailable(f"claims: cannot ask origin about {ref_of(rva)}")
    return any(line.split("\t")[0] == token for line in got.stdout.splitlines())


def release(rvas, who=None, force=False, root=None, tokens=None):
    """Delete claims we own (or any, with force). Returns released ints.

    With `tokens` ({rva: sha}) a ref is deleted only while it still carries
    that token, so a successor's claim survives a late release. Network
    trouble releases nothing (with a warning): claims expire on their own."""
    who = who or owner(root)
    if not fetch(root):
        print("claims: origin unreachable; releasing nothing (claims expire on their own)", file=sys.stderr)
        return []
    current = _read_local(root)
    tokens = {int(r, 16) if isinstance(r, str) else int(r): t for r, t in (tokens or {}).items()}
    done = []
    for rva in _ints(rvas):
        entry = current.get(rva)
        if not entry or (entry[1].get("owner") != who and not force):
            continue
        if rva in tokens and entry[0] != tokens[rva]:
            continue                    # taken over since: not ours to delete
        gone = _git("push", "-q", f"--force-with-lease={ref_of(rva)}:{entry[0]}", REMOTE,
                    f":{ref_of(rva)}", cwd=root, timeout=120)
        if gone.returncode == 0:
            done.append(rva)
    active.cache_clear()
    return done


# ---- release on authoritative landing -------------------------------------

def _pending_path(root=None):
    return Path(root or ROOT) / PENDING


DEP_PREFIXES = ("game/", "inputs/reference/")
DEP_LIMIT = 200
_QUEUE_THREADS = threading.Lock()


@contextmanager
def _queue_lock(root=None):
    """Serialize queue rewrites across threads and processes (fcntl locks do
    not exclude threads of one process, hence the thread lock as well)."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from portable_lock import lock, unlock
    path = _pending_path(root)
    path.parent.mkdir(parents=True, exist_ok=True)
    with _QUEUE_THREADS, open(path.with_suffix(".lock"), "a+b") as handle:
        lock(handle, exclusive=True)
        try:
            yield path
        finally:
            unlock(handle)


def _read_queue(path):
    try:
        text = path.read_text(encoding="utf-8")
    except OSError:
        return []
    out = []
    for line in text.splitlines():
        try:
            out.append(json.loads(line))
        except ValueError:
            continue
    return out


def _write_queue(path, entries):
    tmp = path.with_name(f"{path.name}.{os.getpid()}.{threading.get_ident()}.tmp")
    tmp.write_text("".join(json.dumps(e, sort_keys=True) + "\n" for e in entries), encoding="utf-8")
    os.replace(tmp, path)


def _blobs(root, paths):
    """{path: blob sha of the working file as git would store it, '' if absent}."""
    base = Path(root or ROOT)
    present = [p for p in paths if (base / p).is_file()]
    out = {p: "" for p in paths}
    if present:
        got = _git("hash-object", "--", *present, cwd=root)
        if got.returncode:
            raise RuntimeError(got.stderr.strip())
        out.update(zip(present, got.stdout.split()))
    return out


def landing_deps(source, root=None):
    """What a landing's verification read that origin/master must also hold
    before its claim is released: the row's source plus every changed game/
    or inputs/reference/ file of this checkout (uncommitted, untracked, or
    committed but not on the local origin/master). ({path: blob}, truncated)."""
    changed = set()
    for args in (("diff", "--name-only", "HEAD"),
                 ("ls-files", "--others", "--exclude-standard"),
                 ("diff", "--name-only", "refs/remotes/origin/master", "HEAD")):
        got = _git(*args, "--", *DEP_PREFIXES, cwd=root)
        if got.returncode == 0:
            changed.update(line.strip() for line in got.stdout.splitlines() if line.strip())
    changed.discard(source)
    changed = sorted(changed)
    truncated = len(changed) > DEP_LIMIT
    return _blobs(root, [source] + changed[:DEP_LIMIT]), truncated


def queue_landed(rva, row, who=None, root=None, deps=None):
    """add_match calls this after LOCAL verification: remember the exact
    ledger row AND the blobs of the source and changed dependencies it
    verified, so the claim is released only once origin/master carries all
    of them -- an old published row with the same key is not this landing
    (review 2026-09-29). Never raises: bookkeeping must not fail a landing."""
    try:
        fields = row.strip().split(",")
        source = fields[4] if len(fields) >= 6 else ""
        truncated = False
        if deps is None:
            deps, truncated = landing_deps(source, root) if source else ({}, True)
        now = int(time.time())
        entry = {"rva": f"0x{int(rva):08X}", "row": row.strip(), "owner": who or owner(root),
                 "queued": now, "deps": deps, "deps_truncated": truncated,
                 "id": uuid.uuid4().hex}
        with _queue_lock(root) as path:
            # a checkout nobody settles must not grow the queue forever: entries
            # past two days describe claims that have long expired
            keep = [e for e in _read_queue(path) if now - e.get("queued", 0) < 2 * 86400]
            _write_queue(path, keep + [entry])
    except Exception as error:  # noqa: BLE001
        print(f"claims: could not queue landed body {rva}: {error}", file=sys.stderr)


def pending(root=None):
    """Queued landings of this checkout (see queue_landed)."""
    return _read_queue(_pending_path(root))


def _row_key(row):
    """(name, rva, size, source, status) of a ledger row: what landed, not its notes."""
    fields = row.strip().split(",")
    return tuple(fields[i] for i in (0, 2, 3, 4, 5)) if len(fields) >= 6 else None


def _fetch_master(root=None):
    """origin/master's sha after a fetch, or None."""
    if _git("fetch", "-q", "--no-tags", REMOTE, "master", cwd=root, timeout=300).returncode:
        return None
    return _git("rev-parse", "FETCH_HEAD", cwd=root).stdout.strip() or None


def _rows_at(rev, root=None):
    shown = _git("show", f"{rev}:{LEDGER}", cwd=root, timeout=120)
    if shown.returncode:
        return None
    return {k for k in map(_row_key, shown.stdout.splitlines()) if k}


def landed_rvas(sha, root=None, tip=None):
    """RVAs of the matched rows commit `sha` adds, if `sha` is on origin/master.
    Raises ClaimsUnavailable when origin cannot be fetched, ValueError when the
    commit is not (yet) on origin/master."""
    tip = tip or _fetch_master(root)
    if not tip:
        raise ClaimsUnavailable("claims: cannot fetch origin/master")
    if _git("merge-base", "--is-ancestor", sha, tip, cwd=root).returncode:
        raise ValueError(f"{sha} is not on origin/master ({tip[:10]}): not landed yet")
    diff = _git("diff", f"{sha}^", sha, "--", LEDGER, cwd=root).stdout
    out = set()
    for line in diff.splitlines():
        if line.startswith("+") and not line.startswith("+++"):
            fields = line[1:].strip().split(",")
            if len(fields) >= 6 and fields[5] == "matched":
                try:
                    out.add(int(fields[2], 16))
                except ValueError:
                    continue
    return sorted(out)


def release_landed(sha=None, root=None, who=None, keep_days=1.0):
    """Release claims for bodies that have landed on origin/master.

    Every queued landing (queue_landed) whose exact row origin/master now
    holds is released under the owner that queued it and dropped from the
    queue; with `sha`, the matched rows that commit adds are released under
    `who` -- except any body that still has an unsettled queued landing,
    which stays claimed whatever selected it. Unsettled entries older than `keep_days` are dropped (their claims
    have long expired). Returns (released, still_pending) lists of ints.
    Raises ClaimsUnavailable when origin/master cannot be read."""
    queue = pending(root)
    if not queue and sha is None:
        return [], []
    tip = _fetch_master(root)
    if not tip:
        raise ClaimsUnavailable("claims: cannot fetch origin/master")
    rows = _rows_at(tip, root) if queue else set()
    if rows is None:
        raise ClaimsUnavailable("claims: cannot read origin/master's ledger")
    wanted = sorted({p for e in queue for p in (e.get("deps") or {})})
    published = {}
    if wanted:
        listed = _git("ls-tree", "-r", tip, "--", *wanted, cwd=root, timeout=120)
        if listed.returncode:
            raise ClaimsUnavailable("claims: cannot read origin/master's tree")
        for line in listed.stdout.splitlines():
            meta, _, path = line.partition("\t")
            published[path] = meta.split()[2]

    def landed(entry):
        deps = entry.get("deps")
        if entry.get("deps_truncated") or not deps or _row_key(entry.get("row", "")) not in rows:
            return False
        # a source missing locally proves nothing about what was verified
        if not deps.get(entry["row"].split(",")[4]):
            return False
        return all(published.get(path, "") == blob for path, blob in deps.items())
    extra = landed_rvas(sha, root, tip) if sha else []
    by_owner, waiting, keep, unsettled = {}, [], [], set()
    now = time.time()
    for entry in queue:
        try:
            rva = int(entry["rva"], 16)
        except (KeyError, ValueError):
            continue
        if landed(entry):
            by_owner.setdefault(entry.get("owner") or who or owner(root), set()).add(rva)
        else:
            unsettled.add(rva)
            if now - entry.get("queued", 0) < keep_days * 86400:
                keep.append(entry)
                waiting.append(rva)
    if extra:
        by_owner.setdefault(who or owner(root), set()).update(extra)
    # A body with ANY queued landing whose row and blobs are not all on
    # origin/master stays claimed, however it was selected: an older commit
    # that adds the same RVA (release --landed SHA), or an earlier queued
    # landing of the same body, never overrides a pending one (review
    # 2026-09-29: `release --landed <old sha>` freed a body whose replacement
    # source was still local).
    released = []
    for holder, rvas in by_owner.items():
        rvas -= unsettled
        if rvas:
            released += release(sorted(rvas), who=holder, root=root)
    if queue:
        # drop only the entries settled here: ones queued while we were on
        # the network survive the rewrite
        kept = {json.dumps(e, sort_keys=True) for e in keep}
        settled = {json.dumps(e, sort_keys=True) for e in queue} - kept
        with _queue_lock(root) as path:
            _write_queue(path, [e for e in _read_queue(path)
                                if json.dumps(e, sort_keys=True) not in settled])
    return sorted(set(released)), sorted(set(waiting))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["list", "claim", "release", "whoami"])
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--note", default="")
    ap.add_argument("--force", action="store_true", help="release: also claims owned by others")
    ap.add_argument("--landed", nargs="?", const="", default=None, metavar="SHA",
                    help="release: claims whose rows origin/master holds (this checkout's queued "
                         "landings; with SHA also the matched rows that commit adds)")
    args = ap.parse_args(argv)
    if args.action == "whoami":
        print(owner())
        return 0
    if args.action == "list":
        claims = active()
        for rva, info in sorted(claims.items()):
            left = (info.get("expires", 0) - time.time()) / 3600
            print(f"0x{rva:08X}  {info.get('owner', '?'):30} {left:5.1f} h left  {info.get('note', '')}")
        print(f"{len(claims)} live claim(s)")
        return 0
    if args.action == "claim":
        try:
            result = claim(args.rvas, note=args.note)
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            if error.claimed:
                print(f"claimed before the failure: {' '.join(f'0x{r:08X}' for r in error.claimed)}")
            return 2
        got, refused = result
        print(f"claimed {len(got)}: {' '.join(f'0x{r:08X}' for r in got)}")
        if refused:
            print(f"not claimed: {' '.join(f'0x{r:08X}' for r in refused)}"
                  + (f" (unconfirmed, origin trouble: {' '.join(f'0x{r:08X}' for r in result.unconfirmed)})"
                     if result.unconfirmed else " (held by someone else)"))
        return 0 if not refused else 1
    if args.action == "release" and args.landed is not None:
        try:
            done, waiting = release_landed(args.landed or None)
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            return 2
        except ValueError as error:
            print(f"claims: {error}", file=sys.stderr)
            return 1
        print(f"released {len(done)} landed: {' '.join(f'0x{r:08X}' for r in done)}")
        if waiting:
            print(f"still waiting for origin/master: {' '.join(f'0x{r:08X}' for r in waiting)}")
        return 0
    done = release(args.rvas, force=args.force)
    print(f"released {len(done)}: {' '.join(f'0x{r:08X}' for r in done)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
