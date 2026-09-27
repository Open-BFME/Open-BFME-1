# Publishing to `master`

Publish from a clean worktree with the repository hooks enabled. The pre-push
hook checks the destination tip supplied by Git before starting expensive work;
if it reports `PUSH RACE`, fetch/rebase and retry. Do not use `--no-verify` or a
force push.

The hook keeps global ledger, identity, naming, pin, conversion, and target
checks authoritative on every attempt. Successful scoped byte checks are reused
only when their source and transitive dependency contents, compiler/toolchain
and options, target bytes, relevant ledger/pin resolution, and checker rules
are unchanged. A missing or invalid receipt runs the normal `build.sh` check.

The fleet publishers (`tools/fleet/harvest.py`, `astra_seats.py`, and
`seat_replay.py`) already retry ordinary remote races with bounded backoff.
Rebase conflicts and validation failures stop for review; they are not silently
discarded or diagnosed as races.
