# Clarification after the separate owner-path audit

The three-function experiment remains correctly blocked: its non-inline form
changes ANY2 to NODUPLICATES and fails both real input orders, while its inline
form emits no code. Those observations and the archived diagnostic hashes stand.

The earlier suggestion that the complete member necessarily requires moving
the generated C61F80 row was too broad. Existing `tools/link_cycle.py` already
verifies an actual parent's local EH handler through its strict owner-EH,
dependency and shifted-image paths. Original comutil has a STATIC3 handler and
ASSOCIATIVE5 metadata belonging to the 343-byte parent. The generated anchor
uses a different STATIC3 symbol; it can remain unchanged. Separately claiming
the ten handler bytes as new authored code remains unsupported and earns no
credit. No verifier change or replacement exception is proposed.

The remaining full-member prerequisites are authentic emission/COMDAT context,
one correctly typed vtMissing datum, coherent original E1/E2/CRT lifetime and
all ordinary byte, metadata, EH, dependency and link checks. A real vtMissing
construction is a testable source hypothesis, not an already verified result.
The full-member experiment is centrally reserved and still private. The
read-only owner-path proof and its limits are retained beside this clarification.
