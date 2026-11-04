# OneRing movement-provider link cleanup investigation

The fetched official census index is now available: aafdf413e9, 2026-11-03
13:29, workflow41632099709. It identifies seven current aiMoveToPosition
emitters: six equal a49d2f1ceb11/unknown, plus OneRingTrajectory00299400's
71edda0c2bdb/wrong. The strong ledger owner is MovementOrders; the kept
ScriptActions instance still conflicts with owner selection. The existing
real-name pin names ILT0x3436A, whose native thunk row targets0xD86C0. No
identity, pin, alias, register or source is changed in this investigation.

Read the earlier ScriptActions and TU-local handoffs, the Nov2 caller-register
trials, and OneRing's own landing log first. They concern different caller
boundaries. This source's existing377-byte caller needs the visible method
body for alias analysis, although it calls out of line. Its extra180-byte
method copy is not the219-byte owner. Native callees are recorded separately.
BFME2's reviewed AICommandInterfaceAttackCommands and AIGroupMoveFormation
provide an out-of-line declaration and semantic context; their target layouts,
command buffer and allocator context differ and are not imported. The pinned
reference check is still within72h; RefHandle donor input remains hash-equal.

All experiments are private, compiler-generated objects under build/. The
baseline reproduces both complete original code bodies/relocations. Private
include paths resolve to the same actual source headers. The scratch include
inventory is not reusable, so these objects are never acceptance receipts.

- /EHsc alone, __forceinline alone and enabling the STLport exception context
  keep the377-byte caller and wrong180-byte provider unchanged.
- The owner's static-lib context keeps the caller but gives a139-byte provider;
  it is not a verified replacement for219B.
- Declaring the method out of line removes the copy but changes16 bytes in the
 377-byte caller: the terrain-vptr load moves from before the y-store to after
 it. Its external relocation list stays exact. This is a scheduling mismatch,
 not evidence that the required native caller can be dropped.
- Split-y with the virtual call gives381B/63 differing raw bytes; explicit
 cached-slot fastcall variants give381B/50 and393B/69, with changed relocation
 positions. The attempted free __thiscall function pointer is unsupported by
 MSVC7.1 (C4234). None is accepted or copied into production.

Remaining: preserve the caller's terrain-vptr scheduling while removing or
 independently verifying the extra provider; also reconcile kept ScriptActions
 versus the strong owner. The earlier broad link family remains open. New
 evidence is retained; no disproven ScriptActions register sweep is repeated.
The original source is byte-for-byte unchanged and its normal scoped gate
passes. This handoff is not counted among completed source repairs or new
coverage. No full-link, runtime, RAM/leak/crash/FPS or multicore claim.
