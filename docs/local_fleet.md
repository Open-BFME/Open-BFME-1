# Local reverse-engineering fleet

This machine can sustain three focused writer/build roots. Create the two
additional roots once:

    python3 tools/setup_local_fleet.py

The primary checkout becomes queue slot 1, the clones under
`~/Projects/open-bfme-local-fleet/` become slots 2 and 3, and slots 4-8 are
reserved for read-only Ghidra scouts. `tools/next_work.py` reads each writer's
private slot configuration automatically. Scouts set `AGENT_SLOT` and
`AGENT_POOL=8` explicitly.

Every writer still follows `AGENTS.md`: one function, focused verification,
specific staging, commit hook, pull/rebase, push, and re-pull. Do not run full
gates concurrently; use one writer as the integrator for those. The clones have
independent build directories, but all writers publish to the same branch, so
serialize the final pull/push step and retry after any rejected push.

The fleet manifest is machine-local at
`~/Projects/open-bfme-local-fleet/fleet.json`. Re-running setup is safe and
refreshes configuration without deleting or resetting an existing clone.
