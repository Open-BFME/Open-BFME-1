# One native State-map find identity at000A0E20

Original BFME1 retail1.03 PE SHA256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
All addresses below are RVA unless explicitly VA. This evidence corrects
selected ownership, not the identical71-byte instruction shape. No new pins,
runtime aliases, types, helper bodies, checkers or baseline allowances are used.

## Actual State-map home

Native StateMachine ctor000A1BD0 writes vtableVA01080710 and allocates a24-byte
red-black header at this+4. Getter000A12A0 returns the literalVA0108075C
`StateMachine`. The transition body000A1360 forms map=this+4 and obtains its
key from the scalar StateID argument or default-ID slot+18. At000A13A4 it calls
ILT0004833D ->000A0E20. It loads node+14 into EDI at000A13C8, writes EDI as
currentState+1C at000A13DB, and dispatches virtual slots+10/+14 on this State
address. Native setter000A12B0 and lookup000A1310 use the same map and route.

The helper000A0E20..000A0E66 is71 bytes. ECX is the map header; stack arguments
are one-word iterator output and const unsigned key reference. Node keys are
at+10, compared with JB/JAE. It writes exactly one output node pointer,
returns that output address in EAX and RET8. The original byte SHA256 is
`17277ec0dfe14b75623094218409d6bf0f3572217eaa339440f4ed344913e367`.
The lookup TU naturally emits this complete relocation-free unsigned State*
_STL::_Rb_tree::find specialization. This is the selected provider atA0E20.

All decoded direct calls outside the ILT are:
-000A0F2B in22-byte wrapper000A0F20 ->0004833D
-000A12C4 in69-byte setter000A12B0 ->0004833D
-000A1321 in63-byte lookup000A1310 ->0004833D
-000A13A4 in200-byte transition000A1360 ->0004833D
The wrapper and transition currently retain generated scaffolds and are not
renamed here. The two selected C++ callers name the same unsigned State* find.

## Why the seven inherited homes are wrong

The preceding real State* name at002A1D40 actually selected the Image* helper
object symbol from Image.cpp. Six dup_* rows claimed the StateMachine.cpp
State* helper as object-symbol homes. The selected-identity checker correctly
preferred those ledger homes over the A0E20 candidate pin, rejecting the
otherwise exact new lookup. Byte equality does not justify these identities:

-002A1D40, ILT0003994B: RespawnUpdate level-record set at module-data+A0.
 Native call002A2B54 is followed by copying five inline words node+10..20 at
 002A2B84..002A2BA2. LiteralVA010C2598 names RespawnUpdate::iniParseNewRuleForLevel;
 literalVA010C1F68 names its default-rule diagnostic. Payload is an inline
 level record, not a mapped State pointer.
-00404A70, ILT000369BC: packed unsigned-short pair ->32-byte inline value map.
 004063D6..004063DF packs `(min<<16)|max`; call004063F7 uses receiver+235FC.
 Success00406407 returns node+14 itself, while0040648F..00406492 frees34-hex
 bytes per node. Four-byte State* mapped value is excluded.
-004B0530, ILT00046A10: GUI flash-animation pointer map at receiver+44.
 Call004B1F65 miss allocates14-hex bytes at004B1F74 and constructs004B02A0;
 that constructor uses literalVA010FD1C0 `Flash%d`. Refcount is+4 and animation
 floats are+C/+10, independently consumed by caller004B0D40. Not State objects.
-004D4AF0, ILT0002BF35: local used-ladder pointer set. Caller004D5D90 references
 GUI:NoLadder;004D6420 references GUI:ChooseLadder. Insertion004D4A10 allocates
14-hex-byte nodes and copies only the pointer payload at node+10, with no
 mapped slot+14. Exact LadderInfo nominal spelling is not claimed.
-00586260, ILT00037DE9: receiver+18 map to generated scalar IDs. In00587E40,
00587E5E loads globalVA012F4B7C,00587E68 increments it, and0058800D stores the
 old scalar through the receiver+18 map-index result. Node size18-hex alone
 could fit State*, but the generated-ID value flow disproves it.
-0094C5E0, direct: ref-counted-handle -> inline four-coordinate map at receiver+8.
0094CB86..0094CB89 frees24-hex-byte nodes. Caller0094D940 reads node+14/+18/+1C/+20
 to compute scaled origin and size. Pair constructor0094C5A0 copies one handle
 plus16-byte value. Exact handle/class names remain unknown.
-009EC290, direct: asset-key membership sets at receiver+190/+1A4. Calls009F100B
 and009F16CD use entry+8 solely for membership. Constructor009F2140 creates
14-hex-byte headers for those sets; literalVA011457C0 is `[info] Demand load: `.
 There is no mapped State* slot. Pointer-versus-unsigned-ID key remains unknown.

These conclusions were checked at36 original calls and five ILT jumps, with
instruction-boundary validation and related allocation/insertion/value flows.
They do not infer absence of indirect calls or establish every original C++
container spelling. Address-qualified gen-alias coverage records preserve the
seven71-byte bodies without asserting that they own the shared State* symbol.
Existing signed-map pins/rows are separate contracts and stay unchanged.

## Current callers and bounded impact

The exact unsigned State* tree-find name occurs in current compiled objects for
StateMachine.cpp, StateMachineSetDefaultState.cpp and the corrected lookup TU.
The only selected C++ callsites are setterA12C4 and lookupA1321, both toA0E20.
StateMachine.cpp also emits unselected internalGetState and std::map::find
wrappers; these have no selected native homes. No selected caller of this exact
mangling truthfully binds one of the seven refuted addresses. The seven aliases
keep their original source/object-symbol/extent solely for byte coverage.

A bounded source scan and22149-object discovery pass were followed by fresh
compilation of the unchanged StateMachine/setter sources (55 selected rows)
and Image.cpp (27 rows). Their helper payloads equal the same71 native bytes.
Alias demotion therefore changes selected identity accounting, not code bytes.
The source/header/lookup identity repair must still pass its complete source
gates, strict multi-source preview and the normal full-header commit gate.
