# Pathfind zone-block provider binding

This is a caller declaration repair, not a rename of either existing provider.
The descriptive `PathfindZoneBlock` spelling remains as a local typedef. No
function ledger row, pin, shared header, or provider implementation changes.

The matched `PathfindZoneManager::allocateBlocks` body at RVA 0x00403D50,
size 287, passes the following arguments to the array constructor iterator:

- RVA 0x00403DDF pushes destructor VA 0x00440138. That five-byte ILT at
  RVA 0x00040138 jumps to RVA 0x004029F0.
- RVA 0x00403DE4 pushes constructor VA 0x0044A4E4. That five-byte ILT at
  RVA 0x0004A4E4 jumps to RVA 0x00402930.
- RVA 0x00403DED pushes element stride 0x228; the iterator call is at
  RVA 0x00403DF5 and targets 0x009F6EE4.

The existing ledger providers in `PathfindZoneManager_freeBlocks.cpp` are
`Rva004029F0::Rva004029F0` at 0x00402930 (148 bytes) and
`Rva004029F0::~Rva004029F0` at 0x004029F0 (105 bytes). Their 0x228-byte
layout matches the caller allocation and the cleanup at RVA 0x00403760.
The earlier caller declarations emitted unresolved `PathfindZoneBlock`
constructor/destructor symbols instead of these already-proven providers.
The aliases do not assert a new EA identity for either address.

The compiler also emits a vector-deleting destructor for array cleanup.
Retail RVA 0x00402D40 (87 bytes) calls scalar delete at 0x00881EB0 and
array delete at 0x00881EF0. Declaring array delete in this TU, as in the
existing provider TU, prevents the compiler from substituting scalar delete
for its array branch. The final link preview has no helper COMDAT failure.

Both sources verify 5/5 ledger bodies. Under frozen census a23092df4e with
current AIPathfind and free-list providers refreshed, caller diagnostics fall
4 to 2; only its own duplicate and selected-body diagnostics remain. The
already linked cleanup TU stays 345 bytes; this repair claims no new linked
bytes. The exact-snapshot name correction documents a class-declaration
binding while retaining the descriptive typedef, not a provider rename.
