# Registry named-lookup temporary cleanup at 00C61880

## Independent BFME 1 identity and extent

The existing 196-byte `Rva009EBEC0` at `009EBEC0` pushes handler `00C618B2`.
It selects FuncInfo `00E510C4`, whose unwind entries are state 0 -> -1 at
`00C61899` and state 1 -> 0 at `00C61880`. The latter is the guarded inner
conditional temporary, independently identified by this EH graph. It tests
and clears bit 1 in `[ebp-14]`, addresses the temporary at `[ebp-10]`, and
tail-jumps through ILT `00027C41` to the already proved 12-byte destructor
at `0005C640`. Its RET at `00C61898` completes the 25-byte extent. It uses
the incoming parent frame; its ledger name is an address-qualified compiler
action, not an ordinary no-argument application ABI.

The native destructor's owner and counted-pointer representation are proved
independently in `0005c640-registry-return-lifetime.md`. The existing
`Find_Asset@AssetManagerImpl` provider at `009EEC60` returns one pointer-sized
counted handle, with a ushort reference count at object +4. It uses ECX,
one hidden result pointer, one explicit name and `ret 8`. These facts also
agree with this parent's copying and release operations. The source-level
spelling of the original handle remains unknown.

## Source reconciliation and provenance

Apply the temporary-lifetime repair recorded in
`00c61819-registry-return-view.md` and `00c61840-registry-temporary.md`, while
keeping the wrapper's public AssetReference result. A local typed
member-pointer union calls the existing canonical Find_Asset symbol with
the proven one-word handle view. A compile-time width check and the
pointer-copy/ushort-increment conversion preserve the result representation.
The canonical provider declaration, AssetName input and global owner stay
intact. No pin, alias, public signature change or forwarding body is added.
This is a pinned MSVC 7.1 x86 result view, not a recovered EA type name.

BFME 2 revision `3252f8ecf0ebd738896f2aea4780279ed29538b8`,
`Code/Libraries/Source/WWVegas/WW3D2/RegistryPrototypeLookup.cpp`, supplied
the consistent conditional handle pattern. The donor sibling
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva009EBEC0.cpp` was
reviewed: its older AssetRegistry owner and nominal temporary are not
imported. The BFME 1 ledger's existing official unit is instead
`game/Libraries/Source/assetmanager/assetmanager.cpp`. Its relative
`../WWVegas/WW3D2/texture.h` include, compiler flags and global definition
are preserved; the private trial's short texture.h include is not copied.
Target addresses, state ownership, extent, callee identity and layout facts
above are independently established in BFME 1.

## Verification scope

The private trial preserves all 196 parent bytes and nine relocation sites,
and the cleanup's 25 bytes with the proven destructor relocation. Production
admission must use the actual state-1 compiler label, with the normal
byte/relocation gate and `eh_state_pins.py` proof. Verify the unchanged
188-byte Find_Asset provider separately and reconcile the counted-handle
class contract across its provider and consumers.

The normal two-source build passes the 196-byte parent and 188-byte producer.
Normal admission passes both rows in the wrapper TU, including the new
25-byte action. Its production label is `$L3960`; `eh_state_pins.py`
reports it proven and unique, with no repinning needed. The counted-handle
contract survey reports 18 compiled views, all four bytes with no bases;
there is no existing header definition of this opaque type to adopt.

The outer action `00C61899` still depends on the unproved nominal
AssetReference destructor and is not converted here. The linking census
has missing or stale dependencies, so linked coverage remains unknown;
unchanged parent bytes alone do not establish linking.
