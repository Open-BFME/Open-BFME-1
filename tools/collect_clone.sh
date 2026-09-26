#!/usr/bin/env bash
# Collect one clone's local commits into the hub and land them on origin/master.
#
# Usage: tools/collect_clone.sh <clone-path>
#
# One clone at a time, so a conflict in one seat's range never poisons another's.
# targets/game/reverse/*.csv are merge=union and CRLF, so a ledger clash is taken from the
# clone and repaired wholesale afterwards with tools/ledger_repair.py rather than
# resolved by hand per commit.
#
# Small batches on purpose: origin/master takes a commit roughly every minute
# from other contributors, and the push gate byte-verifies every source the
# OUTGOING RANGE touches. A handful of commits gates in seconds and lands; a
# couple of hundred gates for minutes and loses the ref race every time.
set -uo pipefail
cd "$(dirname "$0")/.."
CLONE="${1:?usage: collect_clone.sh <clone-path>}"
: "${BUILD_POOL:=4}"; export BUILD_POOL

git diff --quiet || { echo "hub working tree is dirty; commit or clean it first"; exit 2; }
git fetch -q "$CLONE" HEAD || { echo "cannot fetch $CLONE"; exit 3; }

picked=0
# git cherry compares patch ids, so a commit already collected under a
# different hash is correctly excluded; git rev-list would re-offer it and
# every re-pick would come back empty and be reported as a conflict.
for c in $(git cherry HEAD FETCH_HEAD | sed -n 's/^+ //p'); do
    if git cherry-pick -x "$c" >/dev/null 2>&1; then
        picked=$((picked+1))
    elif git checkout --theirs -- targets/game/reverse/functions.csv targets/game/reverse/symbols.csv 2>/dev/null \
         && git add targets/game/reverse/functions.csv targets/game/reverse/symbols.csv 2>/dev/null \
         && git -c core.editor=true cherry-pick --continue >/dev/null 2>&1; then
        picked=$((picked+1))
    else
        git cherry-pick --abort >/dev/null 2>&1
        echo "    SKIPPED ${c:0:9} $(git log -1 --format=%s "$c" | cut -c1-60)"
    fi
done
echo "picked $picked commit(s) from $CLONE"
[ "$picked" -eq 0 ] && exit 0

python3 tools/ledger_repair.py | tail -2
git add -A targets/game/reverse/ 2>/dev/null
git diff --cached --quiet || git commit -q -m "Repair the ledger after collecting a clone batch

Co-Authored-By: Claude Opus 5 (1M context) <noreply@anthropic.com>"

for try in 1 2 3 4 5; do
    git fetch -q origin master || { sleep 10; continue; }
    if [ "$(git rev-list --count HEAD..origin/master)" != "0" ]; then
        git rebase origin/master >/dev/null 2>&1 || { git rebase --abort; echo "REBASE CONFLICT"; exit 8; }
        python3 tools/ledger_repair.py >/dev/null 2>&1
        git add -A targets/game/reverse/ 2>/dev/null
        git diff --cached --quiet || git commit -q -m "Repair the ledger after rebasing onto upstream

Co-Authored-By: Claude Opus 5 (1M context) <noreply@anthropic.com>" >/dev/null 2>&1
    fi
    # git push exits non-zero on rejection; do NOT grep its output, because a
    # REJECTED push prints the same "<branch> -> master" string after a "!".
    if git push origin HEAD:master > /tmp/collect_push.log 2>&1; then
        echo "PUSHED $picked commit(s) on try $try"; exit 0
    fi
    echo "  try $try failed:"
    grep -E '^  FAIL |Functions: FAIL|PRE-PUSH FAILED|PRE-COMMIT FAILED|rejected' /tmp/collect_push.log | head -4
done
echo "could not land after 5 tries; hub is $(git rev-list --count origin/master..HEAD) ahead"
exit 1
