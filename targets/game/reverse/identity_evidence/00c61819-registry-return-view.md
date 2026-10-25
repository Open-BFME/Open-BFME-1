# Registry temporary cleanup at 00C61819

## Independent BFME 1 identity and boundary

The byte-matched parent `Rva009EBCE0_GetPrototype` at `009EBCE0` (211 bytes)
pushes handler `00C61832`. That handler selects FuncInfo `00E5106C` and its
two-entry unwind map. State 0 goes to -1 via `00C61800`; state 1 goes to 0
via `00C61819`. The latter tests guard bit 2 in `[ebp-10]`, clears it, takes
the temporary address at `[ebp+8]`, and jumps through ILT `00027C41` to
`0005C640`. Its shared RET at `00C61831` proves the complete 25-byte extent.
This is a compiler cleanup action with an incoming parent frame, not an
ordinary no-argument application function.

The already matched 12-byte `Rva009EBCE0AssetReference` destructor at
`0005C640` is independently proved by the parent's state-0 return lifetime;
see `0005c640-registry-return-lifetime.md`. Both retail actions reach the
same destructor. The nested lookup `AssetManagerImpl::Find_Asset` at
`009EEC60` is an existing 188-byte C++ provider returning one pointer-sized
counted handle through hidden result storage, with one explicit name and
`ret 8`. Its reference count is a ushort at object +4. These are target ABI
and lifetime facts; they do not recover the original handle's C++ spelling.

## Source repair and compilation view

The previous parent source introduced a second nominal `AssetReference`
and converted it to `Rva009EBCE0AssetReference`. Parent instruction bytes
matched, but state 1 then called `??1AssetReference`, which has no proven
binding to this retail destructor. The ILT oracle contradicts that name at
`0005C640`; no destructor alias or second identity is added.

Use the existing address-qualified handle consistently for the lookup result
and both conditional arms. Keep the established AssetReference declaration
and the producer's canonical Find_Asset symbol. A local member-pointer ABI
view invokes that symbol with the address-qualified result type; it adds no
callee pin, linker alias or forwarding body. Both function-pointer signatures
use ECX, one hidden result pointer and one explicit name, and pop eight bytes.
Both result classes are one pointer wide, checked in the translation unit;
the copy/refcount and release behavior are independently established above.
This is a pinned-MSVC x86 ABI view, not a claim that the producer's original
source used the address-qualified type. The producer's C++ type and name are
preserved.

Private MSVC 7.1 trials preserve all 211 parent bytes and nine relocation
positions. The two compiler unwind predecessors remain `[-1, 0]`. The
state-1 native label emits the exact 25-byte action and calls the already
proved address-qualified destructor. A composition wrapper and force-inline
destructor preserve the parent bytes but retain the unsupported nominal
cleanup; those alternatives were discarded.

## Donor provenance

BFME 2 revision `3252f8ecf0ebd738896f2aea4780279ed29538b8`,
`Code/Libraries/Source/WWVegas/WW3D2/RegistryPrototypeLookup.cpp`, uses one
address-qualified handle for both conditional arms. Its `uw_007a7429`
provides an exact unique relocation-aware discovery lead at `00C61819`.
BFME 1's parent, unwind-state ownership, frame offsets, full boundary and
callee identity were established independently above. The BFME 2 path maps
to BFME 1's existing official `game/Libraries/Source/assetmanager/` unit;
the local header and normal BFME 1 compiler flags are retained. No donor
address, private header or compiler override is imported.

## Verification

Normal `build.sh` passes all four rows of RegistryPrototypeLookup.cpp,
including the 211-byte parent, 12-byte destructor and both 25-byte actions.
The unchanged Find_Asset.cpp producer passes its separate 188-byte gate.
`eh_state_pins.py` proves both action labels uniquely by their state indices;
the existing state-0 label was repinned with that tool. Pin consistency and
all existing ABI-view checks pass. The AssetReference contract survey finds six
views, all compiled, with a four-byte pointer representation.

The fetched linking census is dated 2026-10-25 11:21 at `3d3b068129`.
Its current dependency check cannot read 22,653 changed or absent ledger
objects on this host. Linking coverage is therefore unknown; neither the
unchanged parent bytes nor the successful producer gate is a linked-byte
claim. No generated source, destructor alias or verification exception was
introduced. The normal admission tool recorded the new native label in
the object-symbol counter. An initial new-symbol ABI-view pin was removed:
it reproduced the bytes but introduced an unresolved linker name. The final
source references the existing canonical provider directly through its typed
member-pointer view.
