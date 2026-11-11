# Shrub destructor free-buffer route

Queue71 at census90c15cdeca concerns a wrong selected vtable. Its prior
attempt-log entry identifies incompatible local Snapshot views, which this
repair does not change. A separate relocation issue is safely repairable:
`callees.py 0x007206E0 195` reports ILT0x0000A2C2 -> freeTreeBuffers
0x0071C2D0. The previous member expression references the body name;
unlike clearAllTrees (already pinned through ILT45D72), that name has no
ILT pin. Use the already ledgered j_0000a2c2 via the existing receiver-only
fastcall cast convention. No alias or new signature pin is necessary.

Normal scoped build verifies3/3 rows, including195B destructor, deleting
wrapper and cleanup; all4 DIR32 references pass. The edit renumbers the
existing cleanup label; eh_state_pins.py --fix is the sole repinning tool.
The current linking preview is separately checked and is unknown; do not
claim the historical225B census estimate as new linked bytes.

Reviewed donor76f0baefa6 W3DShrubBuffer.h under Code/GameEngineDevice/Include/
W3DDevice/GameClient and its W3DShrubBuffer.cpp implementation. BFME2 uses
a different field layout and storage-only primary pointer projection; it
does not establish BFME1 virtual ownership. The route repair relies on
BFME1 native call and existing function-ledger267B freeTreeBuffers body,
not donor addresses or layout. Existing compiler flags/includes retained.
