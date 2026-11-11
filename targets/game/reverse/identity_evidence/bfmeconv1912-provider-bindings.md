# BfmeConv1912: native status-name lookup and host-state calls

Consumer: game/GameEngine/Source/Common/BfmeConv1912.cpp, existing rows
001CB4E0/471B and00297040/178B. Three obsolete references are replaced by
existing public/static provider names; neither caller identity nor extent
changes. No provider/header/global/data/pin/alias/baseline/ledger changes.

## Primary target contracts

| Old reference | Existing native provider | ILT -> body | Contract |
| --- | --- | --- | --- |
| bfmeLookup_001c6340(void*) | BitFlags<86>::getSingleBitFromName(const char*) | 00026A3F -> 001C09C0 | cdecl one pointer, caller cleanup4, int EAX |
| BfmeHostBH::bfmeOffBH() | BfmeE988::bfmeGo988A() | 00018151 -> 00296280 | thiscall same ECX, no stack arguments |
| BfmeHostBH::bfmeOnBH() | Gen00296F90::handle() | 00046722 -> 00296F90 | thiscall same ECX, no stack arguments |

* The71B lookup lives in game/GameEngine/Source/GameLogic/Object/Object.cpp.
  bitflags-name-lookup-family.md independently establishes its348B pointer
  table at VA012A6670,86entries, the transfer loop bound56hex and the caller's
  one-pointer argument/cleanup. This is not width inference from a same-byte
  lookup or a donor enum count. The existing consumer already declares its
  BitFlags template and uses86-bit storage/table; adding only the native static
  method does not alter that class's data/virtual layout. The obsolete
  const_cast disappears because the native input is const char*.
* The44B off helper remains in Common/BfmeConv988.cpp. Its existing opaque
  BfmeE988 spelling is retained, not promoted to an EA class identity. It tests
  and clears byte65hex, with its existing registry/drop calls. Its similarly
  shaped sibling is at a DIFFERENT address; no ICF alias is introduced.
* The131B on helper remains in
  GameLogic/Object/Update/Gen00296F90Handle.cpp. Its original source establishes
  the existing initialized byte65hex and owner/module fields, random wake time,
  position and condition-word copy. The consumer passes the unchanged original
  object address. The address-derived Gen name remains unchanged.

No suitable shared header declares either opaque helper class. The new
consumer declarations expose only the already-existing public members; no
fields, inheritance, virtual dispatch, construction, sizeof or member offset
is imported. Pointer casts keep the same ECX without a base adjustment. The
existing Xfer/BitFlags/payload views and all their fields are unchanged. There
is no protected-access bridge, raw member-pointer union, wrapper or assembly.

## Exact roots and definition footprint

The verified original object was saved before editing. Its external definition
set is IDENTICAL to the new object's. Its undefined set changes only by these
three native-name substitutions; no new helper or COMDAT is emitted.

Both complete caller rows pass strict, unmasked byte equality with no unresolved
patch references. Every changed REL32 operand preserves its native route:

| Root | Operand offset | Unchanged physical route |
| --- | --- | --- |
| 001CB4E0 | 167hex | 00026A3F -> 001C09C0 |
| 00297040 | 89hex | 00046722 -> 00296F90 |
| 00297040 | 94hex | 00018151 -> 00296280 |

The route check asserts each5B E9 thunk and independently verifies/decode-covers
all71/44/131provider bytes. All normal returns are RET (two in the lookup, one
in each member helper). Existing direct calls, throw path, Xfer slots, string
ownership, callback/data roots and both receiver/argument sequences remain
unchanged; no provider or C++ identity is inferred from a census winner.

## Validation and reference sweep

Normal consumer baseline:2/2functions,3DIR32 references, one empty-string ref,
zero body-guard findings. Normal consumer plus all three provider TUs:
197/197functions,7literals, one empty-string ref,27float constants and100DIR32
references, zero baselined body findings. Exact diagnostic:
`python3 build/sol12h-bindings/check_conv1912_routes.py`.
Private before-state source/object and gate, callee, route and actual link
preview logs are under build/sol12h-bindings/conv1912-*; diagnostic objects are
not substituted for normal verified receipts.

BFME2 pin76f0baefa6f285d54bc1ca922397674312a5913f was inspected read-only at
Code/GameEngine/Include/Common/BitFlagsTemplate.h,
Code/GameEngine/Source/GameLogic/Object/Object.cpp, and
Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupAudioUpdate.cpp.
Its static lookup contract agrees, but its101/104/etc. widths and LargeGroup
layout/transfer differ (state at8C/8D and additional90hex field versus this
BFME1 host's64/65hex tail). No donor name, count, layout, ICF rule, include,
compiler flag or body is imported. Available shallow history exposes only the
pinned census snapshot, not a separate historical donor fix. Primary BFME1
row/target/width evidence suffices; the donor gitlink remains unchanged.

Existing source //cl flags are unchanged. All builds use MSVC7.1 in the
supervisor-approved lane-private Wine11.16 WoW64 prefix, WINEARCH=win64,
BUILD_POOL=2. Actual before-preview covers the consumer and all three provider
units; currentness gaps and any surviving independent debt are not linked
coverage. This repair earns no new matched bytes or inferred closure credit.

Actual previews:before0/4clean in217.4seconds; after0/4clean in207.3seconds.
Consumer and Gen helper are UNKNOWN (22780current objects unavailable/changed);
BfmeConv988 and Object retain independent debt. Historical131->131coverage is
unchanged, NOT131newbytes and not a current confirmed linked unit. Explicit
diagnostic comparison removes exactly the three obsolete unresolved names and
adds zero new diagnostics. Independent parent review decoded all three native
routes/providers and approved this bounded caller-edge repair, not closure.
