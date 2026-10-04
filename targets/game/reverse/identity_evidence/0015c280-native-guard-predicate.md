# Native guard callback at RVA 0015C280

The matched AIGuardMachine constructor 0015D1D0 stores body VA 0055C280
in its guarded condition table at 012EF260, with state ID 5005 and null
userdata. Its native StateConditionInfo and the reference guard predicate
independently establish bool __cdecl(State*, void*). The existing
_Rva0015C280Predicate pin records that proof; this conversion retains the
address-qualified name. See 0015d1d0-native-guard-machine.md.

The callback reads its first stack argument, follows State + 1C to machine
+ 10, and returns its boolean in AL with plain RET. It never reads userdata.
The final RET is at 0015C300, followed by INT3 padding: the complete body
is 129 bytes. Its early returns and direct call boundaries agree with the
retail image; no adjacent function or exception region is borrowed.

Canonical object.h supplies the verified body pointer at +200 and private
status byte at +344. Its existing OBJECT_TU_MEMBERS interface declares the
three retail callees without changing the header. GameLogicObjectLookup.h
supplies the existing declaration-only BFME lookup; exposing the unrelated
Zero Hour lookup inline would change the function. command_source_type.h
supplies the independently established AI command value 2.

State and StateMachine retain partial BFME storage views because vendor
StateMachine.h uses the incompatible Zero Hour offsets +20/+14. The
matched AIExitState::onExit independently uses +1C/+10; name_oracle witnesses
m_machine and m_owner at confidence 0.99 and 1.00. The BodyModuleInterface
view retains the +48 virtual call already consumed by the matched
AIGuardRetaliateReturnState::update. The canonical Object body-pointer type,
reference predicate and matched sibling establish its last-attacker role.
No State, machine, Object or body-interface object is constructed here, and
no virtual table is defined by this callback-only TU.

Direct retail routes are 0001F253 -> GameLogic::findObjectByID at 0009A510,
0004A719 -> Object::getRelationship at 001C7950,
00001FD7 -> Object::isAbleToAttack at 001C9C10, and
00034C93 -> Object::getAbleToAttackSpecificObject at 001C77B0.
Existing typed providers and independently matched callers establish their
signatures. No new callee pin or global definition is introduced.

The native body caches the single virtual last-attacker result, rejects
zero, looks up the target, checks relationship and its dead flag, then
checks general and target-specific attack eligibility. It accepts result
3 or 2. Unlike the reference Zero Hour predicate it makes no second virtual
last-attacker call and no clearLastAttacker call.

The initial canonical-header scratch build reproduced all 129 bytes after
normal relocation resolution, with no masks or unresolved references.
The production whole-TU gate then passed its one matched row and one
DIR32 reference, with no string or float references requiring verification.
A separate production-object check reasserted all 129 relocated bytes, no
masks or unresolved targets, the complete RET/INT3 boundary, and no emitted
virtual-table COMDATs. Focused Ghidra output independently reported the
129-byte extent, constructor data reference and the same four direct
callee routes; its inferred names/types were not used as identity proof.
