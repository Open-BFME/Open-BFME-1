# 0x002E9590: LuaScriptEngine ScriptedEvent parser

The owner and XML dispatch role are proven. The original C++ method spelling is
not known, so `rva002E9590ParseScriptedEvent` retains the body address.

## Native caller and tag

All code addresses below are retail RVAs; data addresses labelled VA include
image base 0x00400000. Capstone inspection used the retail-1.03-unpacked PE;
Ghidra read_memory at VA 0x006E9590 independently agrees with its 194-byte body
and padding window.

* Independently matched clean C++ Events dispatcher at `0x002EA5D0` is
  `LuaScriptEngine::rva002EC770ParseTokenEvents`, in
  `game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseTokenEvents.cpp`.
  It is reached by the matched LuaScriptEngine token parser and preserves the
  engine receiver while dispatching XML event entries.
* At `0x002EA643` it loads VA `0x010CFA9C`; the shipped bytes are
  `ScriptedEvent\0`. It compares fourteen bytes at `0x002EA651` and tests the
  comparison result at `0x002EA65A`.
* The equal branch pushes the unchanged parser at `0x002EA65E`, moves the saved
  engine receiver EBP into ECX at `0x002EA65F`, and calls ILT `0x00038C85` at
  `0x002EA661`. The stub reaches this body `0x002E9590`.
* The body's native literal VA `0x0109C094` is `Name\0`. The attribute loop
  reads tags via `0x0035EF60`, values via `0x0035EF90`, and count via
  `0x0035EF50`; it finishes the same parser through `0x0035EE70`.

## Layout and callee ABI

Matched `LuaScriptEngine` constructor `0x002EB4A0` independently places its
four-byte event vector at `+0x7C` (`LuaScriptEngineCtor.cpp`). The candidate reads
current/end at `+0x80/+0x84`, adds `0x7C` to ECX at `0x002E9600`, and invokes
vector overflow insertion through ILT `0x00017C38` at `0x002E9626` only when full.
This confirms the vector receiver, rather than an engine-level insert method.

The four-byte record is zeroed by `0x002DF780`, then populated by matched
`BfmeThingBLC::bfmeGoBLC` at `0x002DFA00`, which calls NameKeyGenerator and stores
its result through the record receiver. The source preserves that established
callee identity and the existing address-bearing template payload
`Gen_t_002e8eb0_m4pod`; it claims no original record type spelling.

## Extent and verification

Final RET 4 at `0x002E9647` and INT3 at `0x002E964A` establish exactly 186 bytes.
The clean draft uses native STLport push_back and an ordinary local record.
VC7.1 places that record in the dead parameter home, without explicit stack-slot
manipulation or thunk casts. Probe reports an exact instruction match modulo
relocations; the scoped gate must establish the resolved call and data bindings.

## Removed bank adapter and hook pairing

The previous bank's `BfmeThingVKT` was a TU-local adapter: its inline
`bfmeBaseVKT()` converted `j_00025e1e` through a union to a member-function
pointer. It had no definition or claimed real type identity outside that bank.
Retail ILT `0x00025E1E` reaches `0x002DF780`, already ledgered as
`Gen_002df780::m`. Independently decoded bytes there are `mov eax,ecx;
mov dword ptr [eax],0; ret`, exactly nine bytes ending at `0x002DF788`,
with INT3 at `0x002DF789`. The clean caller invokes that existing provider
name directly; it does not rename the provider or claim an original record class.

The name-regression hook paired the removed adapter with this existing
address-bearing callee declaration when it paired the deleted bank with its
replacement source. The snapshot-specific correction records that pairing.
Neither `LuaScriptEngine` nor the caller's address-preserving method spelling
has been replaced with an anonymous identity.
