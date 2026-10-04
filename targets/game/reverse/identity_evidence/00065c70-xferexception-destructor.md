# Genuine XferException destructor ownership at RVA00065C70

2026-10-04; source base47010692ef3d1d86d5c5164ff95fdaefc4d63d8f.
This corrects one existing10-byte provider identity. It does not repair the
variadic constructor, shared StateMachine declarations, or unrelated RTTI.

## Independent native identity and complete extent

Retail PE SHA256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
The native StateMachine serializer000A1510 has three throw sites that construct
an8-byte object through009D6220 and use ThrowInfoVA011DFE5C. That record is:

-attributes0; unwind pointerVA00440804; forward-compatibility0;
 catchable-arrayVA011DFE54.
-ILT00440804 jumps toVA00465C70.
-CatchableArray011DFE54 has one member, CatchableType011DFE34.
-CatchableType properties0; descriptorVA012A704C; PMD(0,-1,0); size8;
 copy pointerILT0044A26E -> bodyVA00465C50.
-TypeDescriptorVA012A704C contains `.?AVXferException@@`, a class.

Those graph records and routes independently name the unwind body as the genuine
XferException destructor. Their addresses are not inferred from a ledger pin.
The existing canonical XferException copy constructor at00065C50 and the natural
class graph emitted by XferVersionTransfer.cpp agree with the same identity.

The entire10-byte body is:

`8B 01 50 E8 78 C2 81 00 59 C3`

It reads `[ECX]`, pushes the owned text pointer, callsVA00C81EF0, pops the
cdecl argument, and returns at00465C79. Subsequent bytes are alignment padding.
No scalar-delete call, tag cleanup, virtual dispatch, extra null guard, explicit
result or hidden destructor argument exists.

The call target00881EF0 is the existing21-byte `operator delete[]` provider
`??_V@YAXPAX@Z` in WWLib/mem_ops.cpp. That body guards null and forwards category2
to the memory-manager free callback. The destructor therefore preserves the
native direct `::operator delete[](text)` operation, including its null behavior.

## Correction and bounded ownership

The previous selected identity was
`?release@Rva00065C70@@QAEXXZ`, in Common/Rva00065C70Release.cpp. It modeled the
same pointer load/free but did not supply the destructor named by native EH.
No authored source caller or pin uses that old name. A read-only census alias
screen found no /alternatename endpoint referring to it. Its only authored
source occurrence was the provider definition, so that orphan source can retire.
Generated b_00065c70/j_00040804 route names are not semantic identities.

The corrected destructor is defined beside the existing authentic class and copy
constructor in Common/System/XferVersionTransfer.cpp. No new TU-local class,
shared header, provider wrapper, pin, runtime alias, cast or throw bridge is
introduced. The existing destructor pin00065C70 remains unchanged. The old row
is replaced/tombstoned through add_match's identity-correction workflow.

The existing25-byte copy constructor and176-byte Version transfer in the same TU
must remain unchanged. Natural ThrowInfo/catchable-array/catchable-type/descriptor
bytes and their relocations must also remain unchanged. Current source/census
inventory finds15 natural-throw consumer TUs/32 matched source rows with the
canonical destructor reference; none needs a declaration or body edit for this
provider correction.

## Explicit remaining limits

The genuine variadic constructor is still pinned but lacks a selected canonical
compiled definition; its current C-factory provider and72 caller-TU migration
are a separate task. This correction does not claim complete consumer linking.
BuffTransfer0040A260.cpp and DrawableXfer.cpp still spell XferException as struct,
with a distinct copy-constructor/RTTI spelling; no alias is added for that debt.
A strict preview uses supported in-memory refresh of freshly compiled target
objects against the unchanged historical census. It is not a new full link or
permission to discard unrelated blockers.
