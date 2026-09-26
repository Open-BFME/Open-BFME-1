# W3D auto progress

## Checkpoint: 2026-09-16 10:35 EDT

- Branch: `w3d-auto`, based on the current `origin/master` at session start.
- Commits pushed: none yet; the handoff/docs commit is being prepared.
- Bodies landed: 0 byte-exact bodies in this session.
- Bodies added to `targets/game/reverse/unlocked.txt`: 59 of 61 family-1-through-12 members,
  tagged `w3d-render`.
- Evidence: `tools/callees.py` reports zero unnamed direct callees for those
  59 members. `0x00907960` and `0x0090AB60` each retain one unnamed target.
- Strongest bank: `0x007171F0`, 445/445 bytes and score 0.991, with four
  non-relocation register-selection mismatches in the filter-4 clear path.
- Receiver candidate: `0x006D4690` compiled under the `bfmeTwoBKE` hypothesis;
  the best scratch result was 314/326 with branch/layout drift. Its identity
  remains opaque and no pin was added.
- Next: publish the recipe and unlock list, then let the anonymous lane drain
  the 59 unlocked members while continuing the two unnamed-callee blockers and
  the unresolved receiver/layout candidate.

## Pool audit: 2026-09-16 10:37 EDT

- All 61 pool addresses now have a five-field verdict in
  `targets/game/reverse/re_attempts.log`. The three previously unlogged large generated
  bodies (`0x007C34E0`, `0x007C3FD0`, `0x007C5690`) were recorded as blocked
  after callee sweeps found 0 unnamed targets; no speculative source claims
  were added.
