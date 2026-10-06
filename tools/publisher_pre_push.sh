#!/usr/bin/env bash
# pre-push shim: a push to master becomes a publisher submission
# (tools/publisher.py submit) instead of a push.
#
# Once the admin ruleset restricts master to the publisher bot, a direct push
# is refused by the server anyway; this shim turns that dead end into a queued
# unit. It exits 1 after submitting, so git does not attempt the push itself:
# fleet scripts should call `publisher.py submit` directly and treat the
# `PUBLISHER-SUBMITTED <unit>` line, not the exit code, as the result.
#
# Installed by an operator on a fleet host (never by an agent), e.g. as the
# first command of .git/hooks/pre-push:  bash tools/publisher_pre_push.sh "$@"
# Environment: PUBLISHER_OPERATOR, PUBLISHER_KEY_FILE, and PUBLISHER_INBOX or
# PUBLISHER_REMOTE; optional PUBLISHER_BRANCH (master), PUBLISHER_PY.
set -euo pipefail

ZERO=0000000000000000000000000000000000000000
branch="refs/heads/${PUBLISHER_BRANCH:-master}"
py="${PUBLISHER_PY:-$(git rev-parse --show-toplevel)/tools/publisher.py}"
status=0
while read -r _local_ref local_sha remote_ref remote_sha; do
    remote_sha="${remote_sha%$'\r'}"
    [ "$remote_ref" = "$branch" ] || continue
    if [ "$local_sha" = "$ZERO" ]; then
        echo "pre-push: $branch is publisher-only; it cannot be deleted" >&2
        exit 1
    fi
    if [ "$remote_sha" = "$ZERO" ] || ! git cat-file -e "$remote_sha^{commit}" 2>/dev/null; then
        echo "pre-push: the remote $branch tip is not local; fetch and rebase, then push again" >&2
        exit 1
    fi
    args=(--operator "$PUBLISHER_OPERATOR" --key-file "$PUBLISHER_KEY_FILE")
    [ -n "${PUBLISHER_INBOX:-}" ] && args+=(--inbox "$PUBLISHER_INBOX")
    [ -n "${PUBLISHER_REMOTE:-}" ] && args+=(--remote "$PUBLISHER_REMOTE")
    unit=$(python3 "$py" submit "${args[@]}" "$remote_sha..$local_sha")
    echo "PUBLISHER-SUBMITTED $unit $remote_sha..$local_sha" >&2
    status=1
done
if [ "$status" != 0 ]; then
    echo "pre-push: $branch is publisher-only; the range was submitted, not pushed" >&2
fi
exit "$status"
