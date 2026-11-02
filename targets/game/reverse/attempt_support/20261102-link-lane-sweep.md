# Link-lane sweep 2026-11-02: packet verdicts and DelayedLuaEventList plan

Donor revision for all packets below: BFME 2 beed8a1679 (worktree checkout;
see build/bfme2-last-check.txt). Census bb53b24f2b is stale — every packet was
re-verified against HEAD with fresh `compile_source` + `objdump -t` before any
edit. Rule learned the hard way: a declaration-only suppression that changes
inlining in the consumer's own matched body breaks its gate (see #4).

## Landed

- Packet #10, `?_M_insert_overflow@?$vector@EV...` (uchar, __true_type).
  Rva0074E620.cpp emitted a duplicate; suppressed with a declaration-only
  explicit specialization (BFME 2 pod-vector-bodies pattern). The suppressed
  symbol is out-of-line-only in the consumer, so its own method body is
  byte-identical (gate 1/1). Owner row 26197 (0x0074D6F0, 263B) untouched.
  Commit e7404dd285 (rebased to 80e54f46a7). PUSH BLOCKED, see below.

## Stale / benign — no edit (verified, do not re-attempt without a new census)

- Packet #17, `??4ExperienceLevel`: neither TU defines it (both sec-0
  external refs in fresh objects). Queue entry predates the fix.
- Packet #23, `??4vector<PAX>`: Bfme5DropAndHandOver.cpp only references it;
  `_STLP_LINK_TIME_INSTANTIATION` already prevents emission. Owner row 9420.
- Packet #25, `??4MapMetaData`: single emitter = owner row 9583 (229B
  matched). Queue entry predates the match.
- Packet #4, `?erase@?$vector@PAX` (3 files): the two RvaHash copies are
  BYTE-IDENTICAL to the owner row 51791 (0x000CF750, 59B) — verified by
  disassembling both objects. Suppression was tried and REVERTED: the
  consumers inline erase through clear() into their matched _M_copy_from
  bodies, so suppression breaks their gates. Benign identical-COMDAT fold;
  nothing to do.
- Packet #54, UnicodeString `_M_insert_dispatch`: the TU's copy serves its own
  matched operator= (row 9414); suppressing it would leave an unresolvable
  extern (retail has no same-named body; 0x0049F340 is a different element
  instantiation). Benign; nothing to do.

## Ready to execute: packet #12, `??1DelayedLuaEventList@@UAE@XZ`

- Real body EXISTS: 0x000EDC40, 77 bytes, row 7958 — but under the wrong name
  `??1Rva000EDC40@@QAE@XZ` (non-virtual spelling). True name is virtual (UAE):
  deleting dtor 0x000EDCA0 calls it via thunk 0x00013156; symbols pin 5142
  assigns the UAE name to 0xEDC40; ctor row 2986 installs the named vtable.
- Consumers (`Rva002BCEE0DelayedLuaDispatch.cpp`, `GameLogicSendObjectCreated.cpp`,
  rows 38835/132469, both matched) each emit a local-view copy; both call the
  dtor only through `??_M` out-of-line plus EH-unwind refs, so declaration-only
  suppression is codegen-neutral for their bodies (verify with the scoped gate
  after edit).
- Steps: (1) rewrite `Rva000EDC40Destructor.cpp` with faithful views so the 77B
  reproduce under the UAE name; (2) land with `add_match.py
  ??1DelayedLuaEventList@@UAE@XZ 0xEDC40 77 <src> --correct-identity
  ??1Rva000EDC40@@QAE@XZ` + identity evidence; (3) suppress both consumers;
  (4) link-check the three TUs. Donor: BFME 2 `DelayedLuaEventList.cpp`
  (58B, rev 961d0becd9) with ctor/vtable/deleting-dtor/event-dtor evidence.

## Push blocked (repo-wide, pre-existing)

`git push` fails in `verification_cache.py exact_worktree`: the staged submodule
pointer `inputs/reference/open-bfme-2` (index beed8a1679) differs from HEAD
(59e3f8f825). The worktree checkout beed8a16 is OLDER than HEAD's pointer
(verified donor rev from 2026-10-25; upstream has since moved on). Committing it
would regress the pointer; reverting it would disturb whoever staged it. Left
untouched — needs owner decision. All commits below are local until resolved.
