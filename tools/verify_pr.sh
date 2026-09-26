#!/usr/bin/env bash
# Verify an external contributor's PR locally (there is deliberately no CI):
#   tools/verify_pr.sh <pr-number> [--full]
#
# Checks out the PR, validates the ledgers statically, byte-verifies exactly
# the rows whose claims the PR adds or whose resolver candidates disappear,
# and (with --full) runs the
# whole gate. Leaves you on the PR branch to merge or comment; returns to the
# previous branch on failure.
set -euo pipefail

# Publication verifies every affected target; worker selection must not redirect its checks.
unset BFME_TARGET BFME_TARGET_SHA256

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

if ! git diff --quiet HEAD -- tools/target_hooks.py \
   || ! python3 tools/target_hooks.py --range "$base" HEAD; then
    echo "PR #$pr FAILED WorldBuilder target verification" >&2
    restore
    exit 1
fi

# PR commits were made under the contributor's hooks, or none: re-run the
# conversion-direction gate over the whole PR range before spending build time.
if ! python3 tools/conversion_gate.py "$base" HEAD; then
    echo "PR #$pr FAILED conversion-direction gate" >&2
    restore
    exit 1
fi

# mapfile cannot see the exit status of a process substitution, so a
# delta_sources crash used to read as "no ledger claims" and the PR was
# reported VERIFIED with nothing byte-verified. Run it to a file first, as
# .githooks/pre-push does.
delta_out=$(mktemp)
if ! python3 tools/delta_sources.py --range "$base" HEAD --selectors > "$delta_out"; then
    rm -f "$delta_out"
    echo "PR #$pr FAILED: delta_sources could not list the changed claims" >&2
    restore
    exit 1
fi
mapfile -t delta_raw < "$delta_out"
rm -f "$delta_out"
delta_sources=()
delta_rows=()
for selector in "${delta_raw[@]}"; do
    case "$selector" in
        source:*) delta_sources+=("${selector#source:}") ;;
        row:*) delta_rows+=("$selector") ;;
        *) echo "PR #$pr FAILED: untyped selector $selector" >&2; restore; exit 1 ;;
    esac
done

# The third gate with the same blind spot the hooks had: a targets/game/reverse/symbols.csv
# PIN DELETION changes no functions.csv row, so the delta above is empty for it
# while claimed rows across the tree lose their REL32 candidate and go red.
# d27ae4b7b reached master with 1,599 deletions and a two-file byte-verify.
if ! git diff --quiet "$base" HEAD -- targets/game/reverse/symbols.csv; then
    pin_delta_out=$(mktemp)
    if ! python3 tools/delta_sources.py --range "$base" HEAD --pins --selectors > "$pin_delta_out"; then
        rm -f "$pin_delta_out"
        echo "PR #$pr FAILED: delta_sources --pins could not list the affected sources" >&2
        restore
        exit 1
    fi
    mapfile -t pin_delta_raw < "$pin_delta_out"
    rm -f "$pin_delta_out"
    for selector in "${pin_delta_raw[@]}"; do
        case "$selector" in
            source:*) delta_sources+=("${selector#source:}") ;;
            row:*) delta_rows+=("$selector") ;;
            *) echo "PR #$pr FAILED: untyped pin selector $selector" >&2; restore; exit 1 ;;
        esac
    done
fi

delta=()
declare -A seen_sources=() seen_rows=()
for source in "${delta_sources[@]}"; do
    [ -n "${seen_sources[$source]:-}" ] && continue
    seen_sources["$source"]=1
    [ -f "$source" ] || { echo "PR #$pr FAILED: missing source $source" >&2; restore; exit 1; }
    git diff --quiet HEAD -- "$source" || { echo "PR #$pr FAILED: $source differs from checked-out PR" >&2; restore; exit 1; }
    delta+=("source:$source")
done
for row in "${delta_rows[@]}"; do
    [ -n "${seen_rows[$row]:-}" ] && continue
    seen_rows["$row"]=1
    delta+=("$row")
done

if [ "${#delta[@]}" -ne 0 ]; then
    echo "checking ${#delta_rows[@]} exact row(s) and ${#delta_sources[@]} source claim(s) changed by PR #$pr..."
    # Keep below Windows' 32,767 UTF-16 command-line limit with ample room
    # for the executable, inherited command prefix and quoting. Row selectors
    # contain full mangled names, so selector count alone is not a safe bound.
    measure_verify_argument() {
        local LC_ALL=C
        verify_argument_bytes=$((2 * ${#1} + 3))
    }
    verify_chunk=()
    verify_bytes=0
    for selector in "${delta[@]}"; do
        measure_verify_argument "$selector"
        if [ "$verify_argument_bytes" -gt 24000 ]; then
            echo "PR #$pr FAILED: verification selector exceeds argument limit: $selector" >&2
            restore
            exit 1
        fi
        if [ "${#verify_chunk[@]}" -ne 0 ] \
           && [ "$((verify_bytes + verify_argument_bytes))" -gt 24000 ]; then
            if ! BUILD_POOL="${BUILD_POOL:-4}" ./build.sh "${verify_chunk[@]}"; then
                echo "PR #$pr FAILED byte-verification" >&2
                restore
                exit 1
            fi
            verify_chunk=()
            verify_bytes=0
        fi
        verify_chunk+=("$selector")
        verify_bytes=$((verify_bytes + verify_argument_bytes))
    done
    if [ "${#verify_chunk[@]}" -ne 0 ] \
       && ! BUILD_POOL="${BUILD_POOL:-4}" ./build.sh "${verify_chunk[@]}"; then
        echo "PR #$pr FAILED byte-verification" >&2
        restore
        exit 1
    fi
else
    echo "PR #$pr has no affected matched rows; static checks only"
fi

if [ "$full" = "--full" ]; then
    BUILD_POOL="${BUILD_POOL:-8}" ./build.sh
fi

echo "PR #$pr VERIFIED — you are on its branch; merge with: gh pr merge $pr"
