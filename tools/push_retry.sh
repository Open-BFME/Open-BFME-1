#!/bin/sh
# Push HEAD to origin/master, rebasing over the other lanes, and report success
# ONLY when the commit is provably in origin/master.
#
# Two traps this exists to avoid, both observed live:
#   * `git log origin/master..HEAD` is empty when you are pushed AND when a
#     half-finished rebase has left HEAD detached on origin's tip with your
#     commit only in the reflog. It cannot tell success from that failure, and
#     a position check (is HEAD an ancestor?) passes in the failure too --
#     so this matches the commit SUBJECT in origin/master's log instead.
#   * `git push | grep -q rejected` misses the real error text, which is
#     "a pushed branch tip is behind its remote counterpart".
# A silenced `git pull --rebase` hides the conflict that causes both, so the
# pull here is never silenced and a conflict stops the script.
set -eu

subject=$(git log -1 --format=%s)
[ -n "$subject" ] || { echo "push_retry: HEAD has no commit" >&2; exit 1; }

if [ -e "$(git rev-parse --git-path rebase-merge)" ] || \
   [ -e "$(git rev-parse --git-path rebase-apply)" ]; then
    echo "push_retry: a rebase is already in progress -- finish it first" >&2
    exit 1
fi

i=0
while [ "$i" -lt 5 ]; do
    i=$((i + 1))
    if ! git pull --rebase origin master; then
        echo "push_retry: rebase stopped and needs hands; NOTHING was pushed" >&2
        git status --short | head -20 >&2
        exit 1
    fi
    if git push origin HEAD:master; then
        break
    fi
    sleep 5
done

git fetch -q origin master
if git log origin/master --format=%s -200 | grep -Fxq "$subject"; then
    echo "push_retry: OK -- \"$subject\" is in origin/master"
else
    echo "push_retry: FAILED -- \"$subject\" is NOT in origin/master" >&2
    echo "push_retry: your commit may be in the reflog only; check 'git reflog'" >&2
    exit 1
fi
