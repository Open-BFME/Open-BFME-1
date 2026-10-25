# Registry enumeration temporary cleanup at 00C61840

## BFME 1 identity and extent

The existing 175-byte parent `Rva009EBDC0` at `009EBDC0` pushes handler
`00C61872`, which selects FuncInfo `00E51098`. Its unwind map is state
0 -> -1 at `00C61859`, state 1 -> 0 at `00C61840`. This establishes the
parent and temporary lifetime independently of adjacency or byte similarity.
The action tests guard bit 1 in `[ebp-14]`, clears it, addresses the inner
temporary at `[ebp-10]`, and tail-jumps through ILT `00027C41` to the
already matched destructor `0005C640`. The shared RET at `00C61858`
completes its 25-byte extent. It requires the parent frame; the ledger's
address-qualified cleanup name is not an application-level function ABI.

The destructor's address-qualified counted-handle identity is established
by the independent registry return lifetime; see
`0005c640-registry-return-lifetime.md`. Its pointer representation and ushort
reference count at object +4 agree with this parent's explicit copying and
release operations. `EnumAssets@AssetManagerImpl` at `009EEF10` is the
existing canonical 224-byte provider. The wrapper and provider use ECX and
one hidden result pointer, and the callee pops four bytes.

## Source and donor evidence

Apply the repair recorded in `00c61819-registry-return-view.md` to the inner conditional
temporary, retaining the wrapper's `AssetReference` return type. A typed
member-pointer union references the existing canonical provider with the
proven one-word handle result view. Both result widths are checked in the
TU. The conversion into the public result preserves the witnessed pointer
copy and ushort increment. No symbol pin, linker alias or forwarding
function is added. This is the pinned MSVC 7.1 x86 ABI view; the original
handle spelling remains unknown.

BFME 2 revision `3252f8ecf0ebd738896f2aea4780279ed29538b8`,
`Code/Libraries/Source/WWVegas/WW3D2/RegistryPrototypeLookup.cpp`, supplies
the consistent inner-handle lifetime pattern. Its sibling
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva009EBDC0.cpp` was
reviewed too: it still uses the nominal AssetReference and an older
Get_Current_Asset provider name. That name and its linker alias are not
imported. BFME 1's existing `game/GameEngineDevice/Source/W3DDevice/GameClient/`
unit, provider declaration, compiler settings and release call are retained.
All addresses, state ownership, layout facts and the full boundary above
come from BFME 1 evidence, not donor RVAs.

## Verification scope

Private trials preserved all 175 parent bytes and eight relocation sites,
and the state-1 action's 25 bytes with the proven destructor relocation.
Admission uses the normal production build and the actual state's compiler
label, followed by `eh_state_pins.py`; label numbers from private paths are
not assumed stable. Verify the unchanged 224-byte producer independently.
The normal two-source build passes the 175-byte parent and 224-byte producer.
Normal admission then passes both rows in the wrapper TU, including the new
25-byte action. The production state-1 label is `$L393`;
`eh_state_pins.py` reports it proven and unique, with no repinning needed.
The outer action `00C61859` still names the unproved nominal AssetReference
destructor and is not recovered by this change.

The available linking census has missing or stale dependency objects, so
linked coverage is unknown. Exact parent bytes and provider verification do
not establish a linked-byte gain.
