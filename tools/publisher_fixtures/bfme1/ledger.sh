#!/usr/bin/env bash
# The full-ledger comparison `publisher.py promote` runs under the old and the
# new checker on the same head (ledger_cmd = bash tools/publisher_fixtures/bfme1/ledger.sh).
# Every line printed is compared as a set: a promotion that flags or clears a
# row prints a different line and must list it in --accept-diff.
# Exit codes are ignored; the findings are the output.
# PUBLISHER_FULL_GATE=1 adds the byte-verified full gate (40-60 min).
cd "$(git rev-parse --show-toplevel)"
section() { echo "== $1"; }
section check_csv;        python3 tools/check_csv.py --ref HEAD 2>&1
section one_identity;     python3 tools/one_identity.py --list 2>&1
section pin_consistency;  python3 tools/pin_consistency.py --check 2>&1
section identity_guard;   python3 tools/identity_guard.py 2>&1
if [ "${PUBLISHER_FULL_GATE:-0}" = 1 ]; then
    section full_gate;    BUILD_POOL="${BUILD_POOL:-4}" python3 tools/gate_baseline.py --check 2>&1
fi
exit 0
