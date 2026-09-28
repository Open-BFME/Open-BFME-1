#!/usr/bin/env bash
# Weekly link census: full build + link of every matched object, appended to
# targets/game/reverse/link_census_history.csv so the distance to a linked game
# is a measured trend, not a guess. Runs in its own worktree (build/wt_link) so
# no lane's checkout is disturbed; commits ONLY the history file.
#
#   bash tools/fleet/weekly_census.sh            # from any checkout of the repo
#
# The full build's gate may be red for reasons unrelated to linking (a baseline
# that improved and was not lowered yet); the census only needs the objects, so
# it continues whenever every object exists and stops if any is missing.
set -uo pipefail
main=$(git -C "$(dirname "$0")" rev-parse --path-format=absolute --git-common-dir)
main=$(dirname "$main")
wt="$main/build/wt_link"
[ -d "$wt" ] || git -C "$main" worktree add -q --detach "$wt" origin/master || exit 1
cd "$wt" || exit 1
git fetch -q origin master && git checkout -q --detach origin/master || exit 1
mkdir -p build
echo "$(date '+%F %T') weekly census: full build at $(git rev-parse --short=10 HEAD)"
BUILD_POOL="${BUILD_POOL:-12}" ./build.sh > build/full_build.log 2>&1
echo "$(date '+%F %T') build exit $? (gate result does not stop the census)"
python3 tools/link_census.py --scaffold --history || exit 1
git add targets/game/reverse/link_census_history.csv
git commit -q -m "link_census: weekly census $(date +%F)" \
    -m "Co-Authored-By: Claude Opus 5.5 (1M context) <noreply@anthropic.com>" || exit 1
for attempt in 1 2 3 4 5; do
    git fetch -q origin master
    git rebase -q origin/master || { git rebase --abort; exit 1; }
    git push -q origin HEAD:master && { echo "weekly census pushed"; exit 0; }
done
echo "weekly census: push lost five races; the commit stays in $wt" >&2
exit 1
