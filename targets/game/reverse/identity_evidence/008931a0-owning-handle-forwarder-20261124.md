# 0x008931A0: forward the existing counted handle

Old identity: `?bfmeMakeEVB@@YA?AUBfmeResultEVB@@PBD@Z`.
Corrected identity: `?bfmeMakeEVB@@YA?AVRefHandle008958D0@@PBD@Z`.
The neutral pre-existing `bfmeMakeEVB` label is retained; this is no EA-name claim.
The exact existing start and 133-byte extent are unchanged. The existing 25-byte
conditional cleanup at 0x00C56D28 retains its identity and extent.

The complete retail forwarder pushes its pooled-string address at 0x008931D7,
loads manager VA0x013377D4 into ECX, then pushes caller-owned return storage
at 0x008931DE and calls 0x00895A00. It returns that storage in EAX. Both direct
targets are independently owned real bodies: the unchanged pooled-string setter
at 0x0089E680 and the 274-byte manager builder at 0x00895A00.

The complete builder writes one owning pointer to its hidden return storage
at 0x00895A48 or 0x00895AC6 and returns with RET8. The independent 115-byte
lookup and 35-byte handle destructor establish one four-byte counted pointer.
The destructor reads [ECX], decrements through 0x00894D90 and calls 0x00895320
on the last reference. Those complete target facts, not the old sixteen-byte
stand-in, determine the layout. See the already tracked
`00895a00-bfme2-handle-builder.md` and `00784a70-refhandle008958d0-dtor.md`.

This forwarder's cleanup tests and clears mask `1` (bit0) in [EBP-0x10], takes the same
returned-object receiver from [EBP+4], and tail-jumps via ILT0x000463AD to
0x00784A70. It therefore destroys the same existing RefHandle008958D0 owner.
The new source declares the already established owning-handle API and calls
the already owned manager method. It defines no new constructor/destructor,
vtable, helper, data, routing pin or linker alias.
Constructor prototypes are reused from the existing provider as declarations
only. They introduce no emitted bodies and do not establish original EA names.

The older failed typedef attempt preserved an incorrect main row name. This
transaction instead uses normal add_match --correct-identity plus its verified
same-source/same-range atomic compiler-funclet-parent maintenance. Labels remain
the responsibility of the normal EH writer. Every row in the source must pass
the unmodified whole-source byte, relocation, EH, DIR32 and body checks.

Historical BFME2 donor: e2e99959950e6eebfe1ced5663aa05de320afc52,
Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp (counted-owner declarations
and 0x006D0B40 builder/0x006CE110 wrapper), docs/recipes.md, and provider-call
repair b8ecb5c9c7cad94028b142bfff08cdf6f61b00de. The selected source/recipes
are unchanged from the previous `1e864b34e0` reference. BFME2's payload is28B and
its names/addresses/layout are not imported. Local ABI evidence above decides.
There is no existing canonical RefHandle header in BFME1; its current provider
declarations are reused. No external/nested donor include is added.

Reproduction and immutable original/control records are in
W:/OpenBFME/diagnostics/one-per-project-20261124/bfme1.
This repairs existing source/provider consistency. It creates zero new exact
body bytes; a per-file link preview is separate from a new census or runtime.
