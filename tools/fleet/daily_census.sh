#!/usr/bin/env bash
# Daily link census: build + link of every matched object, recorded in
# targets/game/reverse/link_census_history.csv (LINKED) and link_status.csv, so
# the README and the daily Discord post show a measured figure. Schedule it on
# a host with the MSVC toolchain before the daily README job (12:37 UTC); the
# deps cache keeps the daily compile incremental. Runs in its own worktree (build/wt_link) so
# no lane's checkout is disturbed; commits ONLY the history and status files.
# The worktree is the census's own: tracked edits in it are build products
# (reloc_names.csv) and are discarded.
#
#   bash tools/fleet/daily_census.sh             # from any checkout of the repo
#   bash tools/fleet/daily_census.sh --no-push   # record in build/wt_link only (testing)
#
# The full build's gate may be red for reasons unrelated to linking (a baseline
# that improved and was not lowered yet); the census only needs the objects, so
# it continues whenever every object exists and compiled, and stops if any is
# missing or a compile failed (cl.exe leaves the previous .obj behind).
set -uo pipefail
no_push=0
case "${1:-}" in
    "") ;;
    --no-push) no_push=1 ;;
    *) echo "usage: daily_census.sh [--no-push]" >&2; exit 2 ;;
esac
main=$(git -C "$(dirname "$0")" rev-parse --path-format=absolute --git-common-dir)
main=$(dirname "$main")
wt="$main/build/wt_link"
[ -d "$wt" ] || git -C "$main" worktree add -q --detach "$wt" origin/master || exit 1
# One census at a time: a second run's checkout would swap sources under the
# first one's compile and record. mkdir is atomic on every platform we run on.
lock="$wt.census-lock"
mkdir "$lock" 2>/dev/null || { echo "daily census: another run holds $lock" >&2; exit 1; }
trap 'rmdir "$lock"' EXIT
cd "$wt" || exit 1
git fetch -q origin master && git checkout -q --force --detach origin/master || exit 1
mkdir -p build
echo "$(date '+%F %T') daily census at $(git rev-parse --short=10 HEAD)"
# Compile only what changed (all cores but two), then link and record. The
# full gate's byte verification is not needed to measure linking and took
# two thirds of the old run. A failed compile stops the census: no record.
PYTHONUNBUFFERED=1 python3 tools/link_census.py --build --history || exit 1
if [ "$no_push" = 1 ]; then
    echo "$(date '+%F %T') daily census recorded in $wt (not committed: --no-push)"
    tail -1 targets/game/reverse/link_census_history.csv
    exit 0
fi
git add targets/game/reverse/link_census_history.csv targets/game/reverse/link_status.csv
git commit -q -m "link_census: daily census $(date +%F)" \
    -m "Co-Authored-By: Claude Opus 5.5 (1M context) <noreply@anthropic.com>" || exit 1
git reset -q --hard HEAD  # drop build products so the rebase can run
for attempt in 1 2 3 4 5; do
    git fetch -q origin master
    git rebase -q origin/master || { git rebase --abort; exit 1; }
    git push -q origin HEAD:master && { echo "daily census pushed"; exit 0; }
done
echo "daily census: push lost five races; this run's record is not on origin (the next run starts from origin again)" >&2
exit 1
