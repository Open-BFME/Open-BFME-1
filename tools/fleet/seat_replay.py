#!/usr/bin/env python3
"""Replay one seat commit onto a fresh origin/master, never merging a ledger.

WHY. Seats commit on the master of hours ago. Rebasing that commit through the
union merge driver is what corrupts the ledgers: two deletions meeting in one
hunk resurrect tombstoned rows, a row whose twin differs only in `\\r` is kept
twice, and every further rebase of an already-polluted commit carries other
contributors' rows inside it (2026-09-27: a six-body seat commit grew to 37
added rows and raised one_identity.surplus by 4). Replaying the seat's own
DELTA -- computed once from the commit against its parent -- onto a freshly
reset master cannot do that:

  functions.csv, symbols.csv,   records removed by the seat are removed (first
  deleted_rows.csv,             matching record), records it added are appended
  re_attempts.log               with their own bytes; nothing else moves
  name_corrections.json         entries added/removed as a set (merge_json_list)
  a file the seat added         written from the commit
  a file the seat deleted       deleted
  a file the seat edited        git merge-file against current master; a
                                conflict aborts the replay (the operator merges)

Each attempt resets a dedicated worktree to origin/master, applies the delta,
commits through the normal hooks and pushes; losing a race to another pusher
simply replays again.

  python3 tools/fleet/seat_replay.py <seat-worktree-or-repo> <commit> [--tries 20]
"""
import argparse
import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "fleet"))

LEDGERS = ("targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv",
           "targets/game/reverse/deleted_rows.csv", "targets/game/reverse/re_attempts.log")
JSON_LISTS = ("targets/game/reverse/name_corrections.json",)
RACES = ("fetch first", "non-fast-forward", "cannot lock ref", "stale info")


def git(cwd, *args, check=False, text=True):
    return subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=text, check=check)


def blob(repo, rev, path):
    out = git(repo, "show", f"{rev}:{path}", text=False)
    return out.stdout if out.returncode == 0 else None


def records(raw):
    """[(payload, terminator)]; tolerates a missing final newline."""
    import ledger_io
    if raw and not raw.endswith(b"\n"):
        raw += b"\n"
    return ledger_io.split_records(raw) if raw else []


def record_delta(before, after):
    """(removed payloads with multiplicity, added (payload, term) in order)."""
    from collections import Counter
    old = Counter(p for p, _ in records(before or b""))
    new = Counter(p for p, _ in records(after or b""))
    removed = old - new
    added, budget = [], new - old
    for payload, term in records(after or b""):
        if budget[payload] > 0:
            added.append((payload, term))
            budget[payload] -= 1
    return removed, added


def apply_records(current, removed, added):
    """Drop the first matching record for each removal, append the additions."""
    from collections import Counter
    todo = Counter(removed)
    kept = []
    for payload, term in records(current or b""):
        if todo[payload] > 0:
            todo[payload] -= 1
            continue
        kept.append(payload + term)
    # A record master already holds (another pusher landed the same row) is not
    # appended twice: that duplicate is exactly what union merge produced.
    have = {p for p, _ in records(b"".join(kept))}
    kept.extend(p + t for p, t in added if p not in have)
    return b"".join(kept)


def seat_delta(repo, commit):
    """Everything the commit changed against its first parent."""
    names = git(repo, "diff", "--name-status", "--no-renames", f"{commit}^", commit).stdout.splitlines()
    delta = {"commit": commit, "files": []}
    for line in names:
        status, path = line.split("\t", 1)
        entry = {"status": status[0], "path": path}
        if path in LEDGERS:
            removed, added = record_delta(blob(repo, f"{commit}^", path), blob(repo, commit, path))
            entry.update(kind="ledger", removed=removed, added=added)
        elif path in JSON_LISTS:
            entry.update(kind="json", base=blob(repo, f"{commit}^", path), theirs=blob(repo, commit, path))
        else:
            entry.update(kind="file", base=blob(repo, f"{commit}^", path), theirs=blob(repo, commit, path))
        delta["files"].append(entry)
    return delta


FUNCTIONS = "targets/game/reverse/functions.csv"


def landed_upstream(tree, delta):
    """Bodies someone else landed while the seat worked: {rva: (name, source)}.

    A seat replaces a dump row at R with its own row. When master no longer
    holds that dump row and another row claims R, the body is taken: replaying
    the seat's row would put a second identity on R (one_identity.surplus) and
    its new source file may collide with the winner's (2026-09-27: 0x003CA480
    landed upstream at the same path while a seat was converting it)."""
    entry = next((e for e in delta["files"] if e["path"] == FUNCTIONS), None)
    if not entry:
        return {}
    master = blob(tree, "HEAD", FUNCTIONS) or b""
    have = {p for p, _ in records(master)}
    claimed = {}
    for payload, _ in records(master):
        row = fields(payload)
        if len(row) > 4 and row[2].startswith("0x"):
            claimed.setdefault(int(row[2], 16), []).append(row[0])
    removed_at = {}
    for payload in entry["removed"]:
        row = fields(payload)
        if len(row) > 4 and row[2].startswith("0x"):
            removed_at.setdefault(int(row[2], 16), []).append(payload)
    taken = {}
    for payload, _ in entry["added"]:
        row = fields(payload)
        if len(row) <= 4 or not row[2].startswith("0x"):
            continue
        rva = int(row[2], 16)
        gone = removed_at.get(rva) and not any(p in have for p in removed_at[rva])
        # any claim counts: upstream may have landed the SAME name (0x003CA480)
        if gone and claimed.get(rva):
            taken[rva] = (row[0], row[4])
    return taken


def fields(payload):
    import ledger_io
    return ledger_io.fields(payload)


def apply_delta(tree, delta):
    """Apply onto the commit checked out in `tree`; returns a problem or None.

    Every "current" version is read from that commit's blob, not the working
    file: under core.autocrlf the working copy is CRLF while every blob delta
    was computed on LF, and merge-file then sees every line as changed.
    Bodies someone else landed meanwhile are skipped (delta["skipped"])."""
    import merge_json_list
    taken = landed_upstream(tree, delta)
    delta["skipped"] = taken
    kept_sources = set()
    for entry in delta["files"]:
        if entry["path"] == FUNCTIONS:
            for payload, _ in entry["added"]:
                row = fields(payload)
                if len(row) > 4 and row[2].startswith("0x") and int(row[2], 16) not in taken:
                    kept_sources.add(row[4])
    lost_sources = {source for _, source in taken.values()} - kept_sources
    for entry in delta["files"]:
        path = tree / entry["path"]
        current = blob(tree, "HEAD", entry["path"])
        if entry["kind"] == "ledger":
            added = entry["added"]
            if entry["path"] == FUNCTIONS and taken:
                added = [(p, t) for p, t in added
                         if not (len(fields(p)) > 4 and fields(p)[2].startswith("0x")
                                 and int(fields(p)[2], 16) in taken)]
            path.write_bytes(apply_records(current or b"", entry["removed"], added))
        elif entry["kind"] == "file" and entry["path"] in lost_sources:
            continue                         # the winner's file (or none) stays as master has it
        elif entry["kind"] == "file" and entry["status"] == "A" and current is not None \
                and current != entry["theirs"]:
            return f"{entry['path']}: the seat added it but master now has a different file there"
        elif entry["kind"] == "json":
            ours = current or b"[]\n"
            base = json.loads(entry["base"] or b"[]")
            merged = merge_json_list.merge(base, json.loads(ours), json.loads(entry["theirs"] or b"[]"))
            path.write_bytes(merge_json_list.render(merged, ours))
        elif entry["status"] == "D":
            if path.exists():
                path.unlink()
        elif entry["status"] == "A" or current is None:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(entry["theirs"])
        else:
            if current == entry["base"]:
                path.write_bytes(entry["theirs"])
                git(tree, "add", "-A", "--", entry["path"])
                continue
            with tempfile.TemporaryDirectory() as tmp:
                ours, base, theirs = (Path(tmp) / n for n in ("ours", "base", "theirs"))
                ours.write_bytes(current)
                base.write_bytes(entry["base"] or b"")
                theirs.write_bytes(entry["theirs"])
                merged = subprocess.run(["git", "merge-file", "-p", str(ours), str(base), str(theirs)],
                                        capture_output=True)
            if merged.returncode:
                return f"{entry['path']}: edited upstream too and the edits conflict; merge by hand"
            path.write_bytes(merged.stdout)
        git(tree, "add", "-A", "--", entry["path"])
    # A body the replay lands must not leave a banked attempt behind: someone
    # may have banked one on master after the seat started (check_csv refuses
    # a stash beside real C++; add_match deletes it when it lands).
    for entry in delta["files"]:
        if entry["path"] != FUNCTIONS:
            continue
        for payload, _ in entry["added"]:
            row = fields(payload)
            if len(row) > 4 and row[2].startswith("0x") and int(row[2], 16) not in taken:
                stash = f"targets/game/reverse/attempts/0x{int(row[2], 16):08x}.cpp"
                if blob(tree, "HEAD", stash) is not None:
                    git(tree, "rm", "-q", "--", stash)
    return None


def add_corrections(tree, evidence, reason):
    """Document every name_regression finding of the staged replay with the
    operator's evidence file (which must be part of the replayed change).
    Findings exist only against CURRENT master, so they are computed here."""
    import dataclasses
    import name_regression
    findings, _ = name_regression.check(tree.resolve(), "HEAD", ":")
    if not findings:
        return 0
    path = tree / JSON_LISTS[0]
    raw = path.read_bytes()
    data = json.loads(raw)
    for finding in findings:
        entry = dataclasses.asdict(finding)
        entry.update(evidence=evidence, reason=reason)
        data.append(entry)
    newline = "\r\n" if b"\r\n" in raw else "\n"
    path.write_bytes((json.dumps(data, indent=1, ensure_ascii=False).replace("\n", newline) + newline)
                     .encode("utf-8"))
    git(tree, "add", "--", JSON_LISTS[0])
    return len(findings)


def replay(repo, commit, tree, tries=20, correct=None):
    """Push `commit`'s delta from `repo` as a fresh commit on origin/master, via `tree`.

    correct=(evidence, reason): document the renames name_regression reports
    against current master, citing that evidence (reviewed by the operator)."""
    # One replay worktree serves every harvest; two resetting it at once would
    # commit each other's half-applied deltas.
    from portable_lock import lock
    with (Path(tree).parent / "wt_replay.lock").open("a+b") as handle:
        lock(handle, exclusive=True, wait_notice="seat_replay: waiting for another harvest")
        return _replay(repo, commit, tree, tries, correct)


def _replay(repo, commit, tree, tries, correct):
    delta = seat_delta(repo, commit)
    message = git(repo, "log", "-1", "--format=%B", commit).stdout
    for _ in range(tries):
        git(tree, "fetch", "-q", "origin", "master", check=True)
        git(tree, "reset", "-q", "--hard", "origin/master", check=True)
        problem = apply_delta(tree, delta)
        if problem:
            return problem
        for rva, (name, source) in sorted(delta["skipped"].items()):
            print(f"  skipped 0x{rva:08X} {name}: landed upstream meanwhile (seat source {source})")
        if correct:
            print(f"  documented {add_corrections(tree, *correct)} name correction(s)")
        if git(tree, "diff", "--cached", "--quiet").returncode == 0:
            return None                      # master already holds every change
        made = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=tree, input=message,
                              capture_output=True, text=True)
        if made.returncode:
            return "commit refused by the hooks:\n" + (made.stdout + made.stderr)[-2500:]
        # Files were written from LF blobs; under autocrlf the checkout form
        # differs, and pre-push refuses a working file that differs from HEAD.
        git(tree, "reset", "-q", "--hard", "HEAD")
        pushed = git(tree, "push", "-q", "origin", "HEAD:master")
        if pushed.returncode == 0:
            return None
        if not any(k in pushed.stdout + pushed.stderr for k in RACES):
            return "push refused:\n" + (pushed.stdout + pushed.stderr)[-2500:]
    return f"not pushed after {tries} replays"


def replay_tree():
    """The dedicated, reset-at-will worktree replays run in."""
    import astra_seats
    base = astra_seats.main_root()
    tree = base / "build" / "wt_replay"
    if not tree.exists():
        git(base, "fetch", "-q", "origin", "master", check=True)
        git(base, "worktree", "add", "-q", "--detach", str(tree), "origin/master", check=True)
    return tree


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("repo", type=Path)
    ap.add_argument("commit")
    ap.add_argument("--tries", type=int, default=20)
    ap.add_argument("--correct", nargs=2, metavar=("EVIDENCE", "REASON"))
    args = ap.parse_args(argv)
    problem = replay(args.repo, args.commit, replay_tree(), args.tries,
                     correct=tuple(args.correct) if args.correct else None)
    if problem:
        print(problem)
        return 1
    print("pushed", git(replay_tree(), "log", "--oneline", "-1").stdout.strip())
    return 0


if __name__ == "__main__":
    sys.exit(main())
