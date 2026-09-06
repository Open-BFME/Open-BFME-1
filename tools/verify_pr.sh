#!/usr/bin/env bash
# Verify an external contributor's PR locally (there is deliberately no CI):
#   tools/verify_pr.sh <pr-number> [--full]
#
# Checks out the PR, validates the ledgers statically, byte-verifies exactly
# the sources whose claims the PR adds or edits, and (with --full) runs the
# whole gate. Leaves you on the PR branch to merge or comment; returns to the
# previous branch on failure.
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel)"
cd "$ROOT"

pr="${1:?usage: tools/verify_pr.sh <pr-number> [--full]}"
full="${2:-}"

prev_ref="$(git rev-parse --abbrev-ref HEAD)"
restore() { git checkout -q "$prev_ref"; }

git fetch origin master
gh pr checkout "$pr"

if ! python3 tools/check_csv.py; then
    echo "PR #$pr FAILED ledger validation" >&2
    restore
    exit 1
fi

base="$(git merge-base HEAD origin/master)"

# PR commits were made under the contributor's hooks, or none: re-run the
# conversion-direction gate over the whole PR range before spending build time.
if ! python3 tools/conversion_gate.py "$base" HEAD; then
    echo "PR #$pr FAILED conversion-direction gate" >&2
    restore
    exit 1
fi

mapfile -t delta < <(python3 tools/delta_sources.py --range "$base" HEAD)

# The third gate with the same blind spot the hooks had: a reverse/symbols.csv
# PIN DELETION changes no functions.csv row, so the delta above is empty for it
# while claimed rows across the tree lose their REL32 candidate and go red.
# d27ae4b7b reached master with 1,599 deletions and a two-file byte-verify.
if ! git diff --quiet "$base" HEAD -- reverse/symbols.csv; then
    mapfile -t pin_delta < <(python3 tools/delta_sources.py --range "$base" HEAD --pins)
    mapfile -t delta < <(printf '%s\n' "${delta[@]}" "${pin_delta[@]}" | sed '/^$/d' | sort -u)
fi

if [ "${#delta[@]}" -ne 0 ] && [ -n "${delta[0]}" ]; then
    echo "byte-verifying ${#delta[@]} source(s) changed by PR #$pr..."
    if ! BUILD_POOL="${BUILD_POOL:-4}" ./build.sh "${delta[@]}"; then
        echo "PR #$pr FAILED byte-verification" >&2
        restore
        exit 1
    fi
else
    echo "PR #$pr adds no ledger claims; static checks only"
fi

if [ "$full" = "--full" ]; then
    BUILD_POOL="${BUILD_POOL:-8}" ./build.sh
fi

echo "PR #$pr VERIFIED — you are on its branch; merge with: gh pr merge $pr"
