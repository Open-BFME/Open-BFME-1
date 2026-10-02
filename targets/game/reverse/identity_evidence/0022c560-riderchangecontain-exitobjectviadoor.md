# RVA 0x0022C560 occupies exitObjectViaDoor in two concrete ExitInterface tables

Proven interface method: `exitObjectViaDoor(Object*, ExitDoorType)`.
Concrete body owner remains unresolved; do not pin a RiderChangeContain name.
Extent: 1253 bytes. Native receiver is the module's ExitInterface at +0x30.
This is a BFME table target missing from Zero Hour's RiderChangeContain
header; absence in that donor is not evidence against the BFME slot.
All addresses were checked against retail-1.03-unpacked lotrbfme.exe,
base 0x00400000, with pefile and capstone.

## BFME literal and concrete constructor settle the class

Matched RiderChangeContain constructor RVA 0x00229FB0 (124 bytes,
RiderChangeContainCtorThunk.cpp) installs primary table VA 0x010ACAF0 at
0x00229FDE and ExitInterface table VA 0x010AC804 at receiver +0x30 at
0x0022A00E. It also installs table 0x010AC7F0 at +0xD4; searching the
shared target's pointer without retaining subobject offsets hid this evidence.

Primary slot 2 stores ILT 0x0000B1DB -> 0x0022A090. That native accessor
returns VA 0x01090A00, the exact BFME literal RiderChangeContain. Thus the
class identity is binary evidence, not just the matched constructor's label.

The actual ExitInterface table at VA 0x010AC804 is:
- slot 0: ILT 0x00028F5B -> 0x0022A130, bool false;
- slot 1: ILT 0x00007158 -> route 0x0022A120 -> 0x000204FA -> 0x0022CD00;
- slot 2: ILT 0x0003B674 -> target 0x0022C560;
- slot 3: ILT 0x00026670 -> 0x0022A060.

## Same slot in the independently matched base names the interface operation

OpenContain's ExitInterface table VA 0x010AAD14 stores ILT 0x00047690
at slot 2 (VA 0x010AAD1C), reaching the matched 1039-byte
OpenContain::exitObjectViaDoor(Object*,ExitDoorType), RVA 0x002284D0,
in OpenContainExitObjectViaDoor.cpp. Its clean source documents the native
module+0x30 receiver and RET 8 contract. DefaultProductionExitUpdate and
GarrisonContain independently place their named exitObjectViaDoor in
ExitInterface slot 2, corroborating the interface identity.

RiderChangeContain's table replaces that slot with the new 1253-byte body.
The target reads its two stack arguments and eventually calls base
OpenContain::exitObjectViaDoor through ILT 0x00047690 at RVA 0x0022CA2B.
This final base call, path/obstacle operations and two-word ABI independently
corroborate the table-slot proof; they do not alone supply the method name.

## Cross-check prevents a unique concrete-owner claim

The matched SiegeEngineContain constructor 0x0022BC50 first calls ILT
0x000023A1 -> 0x0022D010 at 0x0022BC7A. That native body is the matched
TransportContain constructor, not RiderChangeContain 0x00229FB0. It then
installs table VA 0x010ACD98 at +0x30 at 0x0022BCB1; this table also stores
target 0x0022C560 in slot 2. Native TransportContain's table 0x010AD1FC,
however, retains base OpenContain 0x002284D0 in slot 2.

Thus the earlier inference that SiegeEngineContain directly inherits this
body from RiderChangeContain was wrong. These two concrete table contexts
and their matched labels do not establish which unique class owns the shared
body. The constructor source's HordeTransportContainBase label at the
0x0022D010 route also conflicts with that route's ledger identity; this needs
an independent hierarchy audit. Retail has no identical-COMDAT folding, so
do not assign a second identity or guess a concrete owner to explain sharing.
The slot method is proven; a RiderChangeContain mangled name is not.

## Extent and remaining work

Final RET 8 at 0x0022CA42 ends at 0x0022CA45, followed by INT3, confirming
1253 bytes from 0x0022C560. Earlier returns remain inside this extent.
The old no-vtable verdict is superseded by these concrete subobject
routes, but a unique concrete owner remains unresolved. There is no clean candidate to bank; conversion still needs full
BFME field/callee/SEH reconstruction. No production function rename, pin,
source body or byte credit is changed in this evidence-only commit.

## Owner resolved by the SiegeEngineContain note

`0022c560-siegeenginecontain-exitobjectviadoor.md` closes the owner question
this note left open. The missing link is RiderChangeContain's base:
constructor 0x00229FB0 calls ILT 0x00449378 -> **0x0022BC50**
(SiegeEngineContain's constructor) at 0x00229FBF, before it installs its own
tables. The chain is TransportContain <- SiegeEngineContain <-
RiderChangeContain. Table 0x010AD1FC (TransportContain) keeps OpenContain's
0x002284D0 in slot 2, and 0x010ACD98 (SiegeEngineContain) is the first to
hold 0x0022C560. So SiegeEngineContain introduces the body and
RiderChangeContain inherits it. The owner is SiegeEngineContain, not
RiderChangeContain.
