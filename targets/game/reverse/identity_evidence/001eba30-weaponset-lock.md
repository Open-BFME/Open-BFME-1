# RVA 0x001EBA30: WeaponSet lock candidate

Retail extent is 214 bytes: the final `ret 8` begins at RVA 0x001EBB03,
ends at 0x001EBB06, then INT3 begins. The other exit returns at +0xC9.
ILT RVA 0x0004705F jumps to this body.

The byte-matched Object::setWeaponLock wrapper at RVA 0x001CEA50 forwards
two integer arguments to this ILT, using its receiver +0x264 as the callee
receiver. Its source is
`game/GameEngine/Source/GameLogic/Object/Object_rva001CEA50_setWeaponLock.cpp`.
That source uses an address-derived member-function adapter for the final
call, so its call site establishes the route and receiver offset, not an
independent decorated WeaponSet name.

The target reads ObjectID from receiver +0x34 and calls matched
GameLogic::findObjectByID through ILT 0x0001F253. It rejects lock argument
zero or a null weapon at receiver +8+slot*4. Argument 2 permanently stores
lock state 2; argument 1 stores state 1 only if the existing state is not 2.
Successful locking stores the current weapon slot and updates the owner's
model conditions using BitFlags<304>, indexes 0x88,0x89,0x8A. The BFME
name-oracle witnesses `WeaponSet::m_weapons` at +8 and +0x10 and
`m_hasPitchLimit` at +0x2C.

GeneralsMD's WeaponSet.h declares the two-argument Bool-returning
setWeaponLock, and its WeaponSet.cpp has the same unique three-way lock
semantics. These BFME state operations and receiver evidence support that
candidate more strongly than an address or source-adjacency guess, but the
matched wrapper's synthetic adapter must not be presented as a native-name
call-site proof. This session changes no game source or pin.

The saved C++ probe is 214 bytes with four aligned relocations and 31
non-relocation byte differences: receiver/owner ESI/EDI allocation is
reversed, and notifier receiver setup moves ahead of the condition store.
Replacing raw ILT/member-function casts with typed GameLogic and Object
calls leaves the same differences. Inline owner-ID access and an inline
condition-mask method also leave them; removing barriers increases the
residue to 41 bytes. The typed version is banked as an alternate attempt.
