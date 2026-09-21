#!/usr/bin/env python3
"""Is this tree's compiled object cache trustworthy, or only probably?

WHY THIS IS A DETECTOR AND NOT A WARNING. tools/identity_guard.py already says
that multi_name reads this tree's .obj files and so an interrupted build can
move its numbers. That sentence is true and it is not enough: it tells a reader
to SUSPECT a poisoned tree, never that they have one, so the reader still has to
guess -- and the guess that costs is "probably fine". A killed ./build.sh in
this clone produced multi_name.different findings at 0x00042D1B and 0x002136E0
that vanished the moment the two translation units were rebuilt, after the tree
had already been reported upstream as red and a translation unit had nearly been
deleted on the strength of them. A check that cannot distinguish its own noise
from a finding is the failure class this repository keeps paying for.

TWO MECHANISMS, BECAUSE ONE MISSES THE CASE THAT ACTUALLY HAPPENED.

  INTERRUPTED   tools/build.py drops a marker naming its pid on entry and
                removes it on the way out, including when the gate fails --
                a red gate ran to completion and its objects are consistent.
                What does NOT remove it is dying: SIGKILL, and SIGTERM too,
                since CPython's default handler terminates without unwinding
                `finally`. So a marker whose pid is gone is proof that a build
                stopped partway, which no comparison of file contents can see
                -- a half-written .obj is exactly as fresh as a whole one.

  STALE         build.compile_is_current already answers, soundly and by
                content rather than by mtime, whether one object still matches
                the source, the compile command and every header /showIncludes
                recorded when it was built. Running it over the objects that
                exist catches the wider class: a source or header edited with
                no rebuild behind it. It is also what caught the incident above
                -- the rebuild reported `Compile: 1 of 2`, meaning one of those
                two objects had not been current all along.

An object that is ABSENT is not stale. Nothing reads it, and the detectors
already report an unreadable object as unreadable rather than clean.

IT MUST BE ABLE TO SAY IT DOES NOT KNOW. A detector that reports "clean" when it
cannot tell is the third silent-success check, not the fix for the first two, so
there are three verdicts and not two. A marker whose pid is still ALIVE means a
build is running right now and the objects are being rewritten underneath the
question: that is UNKNOWN, never clean. So is any failure to evaluate.

  python3 tools/object_cache.py            # verdict for every claimed source
  python3 tools/object_cache.py a.cpp b.c  # verdict for these sources only
  python3 tools/object_cache.py --clear    # forget markers whose pid is gone

Exit status is 0 for clean and 1 for dirty or unknown, so a script can gate on
it; the verdict and its reasons go to stdout either way.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402

INFLIGHT = B.BUILD_DIR / ".inflight"
CLEAN, DIRTY, UNKNOWN = "clean", "dirty", "unknown"


def pid_alive(pid):
    """True if the pid exists, None when the question cannot be answered."""
    return B.pid_alive(pid)


def markers():
    """(dead, live, unreadable) pids holding in-flight build markers."""
    dead, live, unreadable = [], [], []
    if not INFLIGHT.is_dir():
        return dead, live, unreadable
    for entry in sorted(INFLIGHT.iterdir()):
        try:
            pid = int(entry.name)
        except ValueError:
            unreadable.append(entry.name)
            continue
        alive = pid_alive(pid)
        (live if alive else dead if alive is False else unreadable).append(pid)
    return dead, live, unreadable


def claimed_sources():
    """Every source the ledger holds a matched row for, deduplicated."""
    seen = {}
    for row in B.load_all_function_rows():
        if row.get("status") == "matched":
            seen.setdefault(row["source"], row)
    return seen


def stale_objects(selectors=None):
    """([sources whose present object is not current], [sources not evaluated]).

    Absent objects are neither: nothing reads them.
    """
    stale, unevaluated = [], []
    for source_text, row in sorted(claimed_sources().items()):
        if selectors and not any(sel in source_text for sel in selectors):
            continue
        try:
            # row_object, not obj_path: a row whose "source" is a .lib names one
            # archive member, and its object is per (source, member).
            output = B.row_object(row)
            if not output.exists():
                continue
            if not B.compile_is_current(B.ROOT / source_text, output):
                stale.append(source_text)
        except Exception as exc:                     # noqa: BLE001
            unevaluated.append(f"{source_text}: {type(exc).__name__}: {exc}")
    return stale, unevaluated


def sources_for_names(names):
    """Ledger sources for rows matching these (possibly truncated) symbol names.

    Callers pass names lifted from another tool's report, and reports elide long
    manglings, so a printed name is a PREFIX of the row's. Matching on prefix is
    deliberately over-inclusive: widening the set of objects to check can only
    make the answer more conservative, while missing one would let the object
    behind a finding go unexamined, which is the whole failure being fixed.
    """
    rows = [r for r in B.load_all_function_rows() if r.get("status") == "matched"]
    out = set()
    for name in names:
        for row in rows:
            if row["name"].startswith(name):
                out.add(row["source"])
    return sorted(out)


def status(selectors=None):
    """(verdict, [reason]). Never reports clean on a question it cannot answer."""
    dead, live, unreadable = markers()
    reasons = []
    if unreadable:
        reasons.append(f"{len(unreadable)} in-flight marker(s) could not be read: "
                       f"{unreadable[:4]}")
    if live:
        reasons.append(f"a build is running now (pid {', '.join(map(str, live[:4]))}); "
                       f"objects are being rewritten underneath this question")
    if dead:
        reasons.append(f"{len(dead)} interrupted build(s) left a marker whose process "
                       f"is gone (pid {', '.join(map(str, dead[:4]))}); objects from a "
                       f"partial run can be half-written and still look fresh")
    stale, unevaluated = stale_objects(selectors)
    if stale:
        reasons.append(f"{len(stale)} object(s) do not match their source, compile "
                       f"command or recorded headers: {stale[:4]}")
    if unevaluated:
        reasons.append(f"{len(unevaluated)} source(s) could not be evaluated: "
                       f"{unevaluated[:2]}")
    if dead or stale:
        return DIRTY, reasons
    if live or unreadable or unevaluated:
        return UNKNOWN, reasons
    return CLEAN, ["no interrupted build, and every object present matches its inputs"]


def clear_dead_markers():
    dead, _live, _unreadable = markers()
    for pid in dead:
        (INFLIGHT / str(pid)).unlink(missing_ok=True)
    return dead


def main(argv):
    if "--clear" in argv:
        cleared = clear_dead_markers()
        print(f"object_cache: cleared {len(cleared)} dead marker(s): {cleared}")
        argv = [a for a in argv if a != "--clear"]
    verdict, reasons = status(argv or None)
    print(f"object_cache: {verdict.upper()}")
    for reason in reasons:
        print(f"    {reason}")
    return 0 if verdict == CLEAN else 1


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
