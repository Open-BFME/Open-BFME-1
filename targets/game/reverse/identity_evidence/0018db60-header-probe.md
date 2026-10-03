# TurretStateMachine constructor: exact parent, queued shared headers

The full retail extent is RVA 0018DB60..0018DE16 (694 bytes, RET 12).
Ghidra decompilation and direct retail decode agree. Identity comes from the
Zero Hour constructor twin and the matched TurretAI constructor 0018DED0
calling this body with the turret, Object, and AsciiString. The table installed
is VA 0109B828; the native scalar deleting destructor at 0018CF30 independently
anchors this same family. No new name or pin is required.

The old two-argument StateMachine declaration is ABI-incomplete. Its matched
constructor at 000A1BD0 and StateMachineCtorThunk.cpp prove a third bool argument,
stored at receiver+42, and size44. The new parent passes false, stores the turret
at +44, and uses canonical StringBase-backed AsciiString lifetime.

The State base constructor 000A19E0 and matched StateConstructor.cpp establish
one vptr, the transition vector at +10, machine at +1C, byte at +20, size24.
TurretState constructor 0018D890 is called out of line by five inline child
constructors. The native children use sizes24/28; the old header adds a second
vptr store to each inlined child. AIAttackFireWeaponState stores its notification
interface at +24 and clears a byte at +28, size2C. The byte has no witnessed
semantic name (name_oracle reports none), so the patch keeps m_rva28.

Measured controls:
- Canonical AsciiString with unchanged class headers: 739/694 bytes,429 diffs.
- Third base argument, StateMachine size44, outlined TurretState: 733/694,343 diffs.
- State single-base layout plus byte20: 691/694,188 diffs,shape0.995.
- FireWeapon byte28 initialization: 694/694 exact,54 relocation slots.
The byte initialization also selects retail's EBX zero/EBP turret allocation.

Strict add_match verification passed 1/1, all six string literals, and eight
DIR32 references; no new symbol pins. The native complete/deleting destructor
and constructor callees retain their existing identities. This is only a scoped
parent verification: the shared-header full gate has NOT run. In particular,
other State/StateMachine users and generated virtual table layouts require
coordinated integration checking; a parent match alone does not validate every
virtual slot affected by merging the bases. The patch is queued, not committed
as production progress. Its measured score1.0 bank requires applying that patch.

Fresh remote master a859ea8e1d65a1e410890b513a00d2f63c81c718 still carries the
694-byte assembly row. Fetch remained stalled on a519850-object pack; the live
raw ledger was streamed at the pinned SHA, and the fetch issue was reported.
