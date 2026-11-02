# 0x001CEFC0 (1493 B): ledgered as ??1InactiveBody, really Object::onDie

Status: partial 0.983 (identity proven; rename refused by conversion_gate; C++ bank
targets/game/reverse/attempts/0x001cefc0.cpp, 1483 B of 1493).

## Identity (BFME 1 target evidence)
- Retail ILT 0x0003369F = `E9 1C B9 19 00` -> 0x001CEFC0.
  `tools/ilt_oracle.py check '?onDie@Object@@QAEXPAVDamageInfo@@@Z' 0x3369F`
  -> CONFIRMED p_false=7.18e-04; the `PBVDamageInfo` spelling is CONTRADICTED.
- symbols.csv pins that name at 0x3369F (callee of matched
  InactiveBody::attemptDamage 0x00213E40); ActiveBody_attemptDamage.cpp and
  RespawnBodyInternalChangeHealth.cpp call it with this=Object.
- Body ends `ret 4`: no destructor. The real ??1InactiveBody ILT 0x0003C867
  jumps to 0x00213B70 (currently ??1Rva00213B70NestedDtor, ilt_oracle says
  ??1InactiveBody@@UAE@XZ is CONTRADICTED there, so that one is not simple either).

## Link effect
link_queue #13 (`?onDie@Object@@QAEXPAVDamageInfo@@@Z`, losers, 528 B in
InactiveBody.cpp, census 3d3b068129): the selected definition is the
present-unmatched Zero Hour copy in Object.cpp (probe score 0.20, 760 B vs 1493 B).

## What was tried (session 457, claude-opus-5-5)
Renaming the naked lift in Body/InactiveBodyDestructorThunk.cpp to
`__declspec(naked) void Object::onDie(DamageInfo *)` with
`add_match --replace-rva 0x1CEFC0 --correct-identity '??1InactiveBody@@UAE@XZ'`
byte-verified and Object.cpp (with the ZH copy removed) built 190/190, but
the pre-commit conversion gate (Rule A) counts a renamed naked line as a new
lift and refuses it. Not retried another way.

## Way forward
Write Object::onDie as real C++ in Object.cpp (replacing the ZH copy) and
land with `add_match --replace-rva 0x1CEFC0 --correct-identity
'??1InactiveBody@@UAE@XZ'`, deleting the lift file and its hatch_baseline
emit line. Retail shape notes: SEH frame, 0xBC locals; bool
`damageInfo->m_sourceID(+8) == m_id(+0x74)` saved first; die-module loop over
m_behaviors(+0x1F0) slot +0x18 then onDie; TheVictorySystem(0x12EF734)
rva001DFC10(this,damageInfo); an inline DamageInfo built on the stack (vtable
0x1085DE4/0x1085DE0, 1.0f at +0x48) passed to slot +0x34 of the container at
+0x214; status bit edits through setStatus-like inline (+0x110 BitFlags, calls
0x41343f replaceModelConditionState and 0x43611a); a 3x24 B
DelayedLuaEventList array (eh vector ctor/dtor iterators, vtable 0x1085E10)
passed to bfmeGo939B (0x2E7650) on 0x12F060C; tail calls d_000ee7f0 on the
+0x23C team. All 22 callees are matched rows.

## C++ reconstruction (session 457, same day)
Bank: `targets/game/reverse/attempts/0x001cefc0.cpp`, meant for
`game/GameEngine/Source/GameLogic/Object/Object_onDie.cpp` (cl line as in
SpawnBehaviorOnDie.cpp: `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB`, stlport,
GameLogicObjectLookup.h). probe: 1483 B vs 1493, shape 0.983, 0xBC frame, EH
states and every call/reloc in place. Default flags are best (flag_sweep: 90
variants, /G7 drops to 0.919).

Levers that worked (each measured):
- inline `GameLogic::findObjectByID` in the TU: the producer lookup inlines
  and the killer lookup stays out of line, as retail (0.879 -> 0.945).
- DelayedLuaEventList: base class NOT novtable with `virtual ~Base() {}`,
  derived with an inline ctor and NO user dtor. This gives retail's EH
  states 0/1/2 and no vptr stores at the end (dead-store eliminated).
- setStatus mask: ZH `BitFlags<86>(kInit, 70)` temp over `_STL::bitset<86>`.
- DamageInfoInput: the late byte store is m_kill at +0x20 (offsets after
  the push are +4); +0x24 is a float (imm 0 store, not ebx).
- `ObjectID killerID = damageInfo->in.m_sourceID;` before findObjectByID,
  `getID()` accessor for onSpawnDeath, `getContain()` accessor for the
  spawner's contain branch, `owner = getControllingPlayer()` before reading
  ThePlayerList->m_local, `m_id == m_sourceID` operand order.

Residue (all register allocation / scheduling):
1. VC7.1 caches 0x20000000 in EBP (`mov ebp,0x20000000` at +0x78) for the
   +0x94 status test and the model-condition bit 61 test/or; retail keeps
   three immediates and uses EBP as the bit-87 clear temp instead (ours ECX).
   Retail's un-CSE'd `test [r+disp],imm` ... `or r,imm` pair is unique in the
   whole image. Tried without effect: Bool vs mask-returning tests, bitset
   flags (worse 0.941), volatile flags, bitfield or 64-bit status word,
   test-inside set/clear helpers, shift-form status test, no container local.
2. Die-module loop: ours `mov edx,[eax+0xC]; lea ecx,[eax+0xC]; call [edx+18h]`,
   retail `lea ecx,[eax+0xC]; mov eax,[ecx]; call [eax+18h]` (the spawner loop,
   written as an inline Object member, already matches). Tried a module
   local, a forceinline member loop (worse), a while loop (worse).
3. The setStatus temp's third word is stored before the pushes (retail
   after `push 1`).

Diagnostic (same session): changing only the +0x94 test's constant (to
0x40000000, wrong on purpose) makes the size exact (1493) and moves the
bit-87 clear temp to EBP as in retail; the bit-61 test/or pair then CSEs
locally (`mov ecx,0x20000000; test ecx,eax; ... or edi,ecx`), where retail
keeps `test [esi+0x114],imm` and `or edi,imm`. So two things block: the
shared constant across the status test and the flag edit, and the test/or
pair itself. Set spellings tried without effect: `(w & ~m) | m`,
`set(i, val=1)`, `1u << i`, `unsigned long` mask; 64-bit flag words (worse,
0.943). The die-loop register residue is probably a consequence of the same
allocation.
Further inert spellings for the bit-61 pair (with the +0x94 constant dummied
to isolate it): explicit `ModelConditionFlags &` local, a static forceinline
setBit(ModelConditionFlags *, int), raw `m_bits[1] & / |= 0x20000000`, a
word pointer, a `ModelConditionFlags *f` used for the notify push, and a
ZH-style mask temporary (`mask.set(61); m_bits[1] |= mask.m_bits[1]`; the
temp is eliminated but the constant is still shared). For +0x94:
signed/unsigned casts, a Bool accessor (gives shr/test al,1), bitfield.
Other inert toggles: draw declared then assigned, Player* if-form (worse),
pathfinder accessor, notify via locals, 10-word flags. Note that sibling
0x001C7CF0 in the same Object family DOES share its constant
(`mov eax,0x1000000; test eax,ecx; or ecx,eax`), so whatever stops it in
onDie is local to this body.

Rebank (same session): the setStatus mask is now a named
`BitFlags<86> status; status.set(70);` over `_STL::bitset` `_Unchecked_set`,
the spelling of matched Object::rva001CE530 (0x001CE530). It reproduces
retail's `xor eax,eax / two zero stores / push 1 / lea edx / or eax,0x40`
schedule (residue 3 gone). 0x001CE530 also tests [esi+0x94] and ORs the same
constant through `_Unchecked_set` without sharing it, but using
`_Unchecked_set/_Unchecked_reset` for the model-condition flags made the
flag tests reuse the loaded word (0.958). Two this-load orders are left:
tryEvent (retail loads TheRadar before `lea eax,[esi+0x38]`) and the killer
findObjectByID (retail pushes the ID before loading TheGameLogic).

## Session 2026-11-01 (muse-spark-1.3, link #25, owner spark30-20261101-b)

Baseline re-verified by probe: 1483/1493 B, shape 0.983, 11 structural
diffs, first at +0x43. The bank file is current (setStatus-temp schedule
confirmed fixed in the emitted code). All 10 missing bytes are accounted
for: EBP-CSE net -7 (+5 `mov ebp,imm`, -12 across the three
register-operand sites), die loop +1 (`mov`+`lea`+`call` is 9 B vs
retail's 8 B `lea`+`mov`+`call`), missing `lea esp,[esp]` align pad -4
(retail aligns the spawner loop at +0x340). The pad should appear on its
own once the upstream bytes close.

Linking half is done externally: Object.cpp's ZH onDie was dropped by
ddcdb01426, so no second strong definition remains; what is left is pure
byte recovery of the 1493 B body under its proven onDie name.

New failed trials (private path build/ondie-trial/, each probed; do not repeat):
- T1 flipped selfInflicted to `m_sourceID == m_id`: folds to
  `mov eax,[ebp+8]; cmp eax,[esi+0x74]`, 0.979/1481 B. Worse; current
  operand order stands (the +0x2d `cmp eax,edx` vs `cmp edx,eax` stays a
  pure rename).
- T2 die loop through an explicit `BehaviorModuleInterface *behavior = *d`
  local: compiler forwards it away, byte-identical 0.983.
- T2b die interface declared in the `if` condition: byte-identical 0.983.
- T3 `Radar *radar = TheRadar;` ahead of tryEvent: the scheduler emits
  `lea ecx` first anyway, byte-identical 0.983. Downstream scheduling is
  context-driven, not source-order-driven; fix upstream first.
- T4 die loop as an implicit-inline member mirroring
  getSpawnBehaviorInterface: catastrophic 0.884/1395 B. The die loop must
  stay inline in onDie.
- T5 die loop as do-while with pre-check: 0.931/1430 B, producer still
  mov-first. The mov-first scheduling is invariant across loop forms.

Coupling notes: the spawner loop (inlined member, slot +0x74,
return-consumer) matches retail's lea-first exactly while the die loop
(same layout, slot +0x18, call-consumer) stays mov-first under every
tried form; the EBP-CSE hoist sits above the `je` with EBP dead in both
versions, so it is a pure heuristic choice, likely sensitive to the same
upstream state. Retrying downstream orderings (tryEvent, killer push)
before the CSE/die-loop move is wasted effort.

Donor: BFME 2 6584c19 Code/GameEngine/Source/GameLogic/Object/ObjectOnDie.cpp
read (798 B, /O1 /G7 /arch:SSE; check-inside setStatusBit/clearStatusBit
over raw m_bits[4]; Team canonical header 8c0120e29c). No transferable
lever for these residues: BFME 1's body is 1493 B with a different flag
layout, and the check-inside-helpers family was already tried inert.

## Session a1 s543 (2026-11-02): 0.983 -> 0.986
- `unsigned myID = m_id; Bool selfInflicted = (damageInfo->in.m_sourceID == myID);`
  fixes the opening compare (`cmp edx,eax` with both in registers) AND residue 2,
  the die-module loop (`lea ecx,[eax+0xC]; mov eax,[ecx]; call [eax+18h]`): first
  diff moves from +0x2D to +0x77 (the EBP constant). Spelling the loop through a
  `BehaviorModuleInterface *` or `BehaviorModule *` local alone was inert; the
  reversed compare without the local was worse (memory operand).
- Residue 1 is now the first difference: ours `mov ebp,0x20000000` at +0x77.
  Retail keeps EBP for the inlined spawner lookup result (`mov ebp,[eax+8]` at
  +0x329, then `[ebp+0x1F0]`, `[ebp+0x1FC]`) and the bit-87 clear temp. Inert:
  int vs unsigned m_status94, signed ModelConditionFlags words/masks, `L` suffix.
