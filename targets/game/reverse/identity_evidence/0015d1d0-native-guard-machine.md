# Native AIGuardMachine constructor at 0015D1D0

The existing identity proof `0x0015d1d0-aiguard-constructor-signature.md`
independently names the two-argument BFME constructor from matched
AIStateMachine and GiantBirdGuardMachine callers. This conversion retains
that corrected identity and removes the historical one-argument emitter alias.
Both raw PE and Ghidra establish691 bytes, ending RET8 at0015D480..482,
with INT3 immediately after. The Zero Hour twin is AIGuard.cpp:166; BFME
registers RETURN, IDLE, INNER, OUTER, CRATE, AGGRESSOR in that order using
IDs5003,5001,5000,5002,5004,5005. Transitions are read from retail pushes.

## Header and layout boundaries

Canonical StringInline.h and Lib/BaseType.h supply AsciiString and Coord3D.
The existing ZH AIGuard.h declares only Object* and uses the older
StateMachine layout; it cannot declare the independently proved BFME
constructor. StateMachine's BFME base is0x44 as independently established by
the matched AIDockMachineCtor.cpp and base constructor000A1BD0. The matched
factory0016FAA0 allocates0x78 for this constructor. Partial local BFME views
therefore express the actual ABI without modifying shared/vendor headers.
StateConditionInfo uses the established callback/id/data triple already
consumed by the matched defineState000A2030 and sibling constructors.

Unknown scalar members remain address-qualified. Zero stores and the two
Coord3D zero operations are literal BFME offsets; no guessed semantic field
names are asserted. The view occupies0x78 bytes. New-state sizes are witnessed
by retail allocations54,34,4C,48,54,48. State and AIInternalMoveToState base
constructors are independently matched000A19E0/0014F280 and agree with
existing AIDock declarations. Inner/Outer/AttackAggressor constructor calls
reuse their matched canonical names at0015CE00/0015CED0/0015D090.

Return and Idle use the literal constructors in ZH AIGuard.h, with their
retail vptrs10962C8/10961E0 and lengths54/34. PickUpCrate's inherited base
constructor uses the actual AIAttackPickUpCrateState literal1096128 and base layout50 plus
its zeroed +50 dword; the final guard-crate vptr is1096348. ZH AIStateMachine.h:551 and
matched AIPickUpCrateStateConstructor.cpp confirm this differently spelled
base literal; AIGuard.h supplies the derived inheritance. The mapped
vptrs, actual strings and all direct call targets require strict verification.

## Callback address and ABI

The retail static condition table at VA012EF260 contains callback0055C280,
ID5005 and zero userdata, then a zero sentinel. Its guarded initialization
at0015D257 stores that exact callback address (a direct body, not an ILT).
The callback remains address-derived as Rva0015C280Predicate.

Raw callback0015C280 reads its first cdecl stack argument atESP+4, follows
State+1C to machine+10, tests the owner's body at+200 and its slot+48,
then calls object lookup, relationship and attack-eligibility operations.
All returns leave a boolean in AL and use plain RET; it never reads the
second callback parameter. The native StateConditionInfo contract and the
ZH static predicate at AIGuard.cpp:64 independently specify
bool(State*,void*). This proves the storage/calling convention, not a new
semantic callback name. The complete129B extent ends RET0015C300 beforeCC.
The BFME predicate differs from ZH (no explicit clearLastAttacker call), so
no callback source or additional coverage is claimed from their similarity.

## Cleanup ownership

Parent handler operand+3 selects00C051A2 -> FuncInfo00DF370C. Eight native
predecessor entries agree with retail: state0 handles incoming by-value name,
state1 the constructed StateMachine base, states2..7 the six allocations.
Served action00C05181 is state5/predecessor1 (fourth allocation). It loads
saved allocation atEBP+4, calls canonical scalar delete00881EB0, popsECX,
and ends RET00C0518B; independent next action begins00C0518C. Full11B.

Both minimal and canonical-Coord3D scratch variants reproduce all691 bytes
modulo46 relocation sites. The production conversion is conditioned on the
ordinary strict source/callee/literal/reference gate, with any callback pin
supported by the independent ABI and physical-address evidence above.

The explicit address-only callback pin `_Rva0015C280Predicate` retains this
independently established body address for linking. It adds no callback
provider or conversion claim. Canonical Coord3D retained the exact691B shape;
all three strings (including AIAttackPickUpCrateState), vptr references and
all direct callee bindings pass strict verification.
