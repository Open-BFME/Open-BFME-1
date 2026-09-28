# InGameUI snapshot transfer at RVA 0x0044C250

The existing 1453-byte scaffold boundary is retained. Retail ends after two
nonreturning XferException throw paths; the following int3 is padding.

## Owner and method

- InGameUI constructor 0x0044B800 and destructor 0x0044AE70 install Snapshot
  vtable VA 0x010F5B24 at complete-object +8.
- Its slot 3 is ILT RVA 0x00049107, which jumps to 0x0044C250.
- W3DInGameUI constructor 0x006FBE10 installs VA 0x0112057C with the same slot.
- The established snapshot.h interface names slot 3 DoXfer(Xfer&).
- Zero Hour GeneralsMD InGameUI.cpp::xfer independently corroborates timer and
  superweapon loops, their field order, lookup, insertion and error paths.
- The compiler emits the secondary-base override with Snapshot-relative this,
  corroborated by the -8 adjustment before addNamedTimer.

BFME differences: a two-byte version (1,1), a tactical-view float during CRC,
a light-CRC early return, 32 players and no evaReadyPlayed field.
The constructor-backed complete-object offsets and SuperweaponInfo size are
compile-time checked in the source.

## One missing typed callee pin: superweapon map operator[]

Pin: STLport map<AsciiString,list<SuperweaponInfo*> >::operator[]
The pin names the real body RVA 0x0044C120. The resolver discovers its ILT
at RVA 0x00015FCD automatically. Decoding that five-byte ILT independently
yields exactly the pinned body. A route pin was not used because the body
remains a scaffold and the route guard requires a named body ledger row.

The 242-byte body at 0x0044C120:
- Receives tree in ECX and a const key reference in one stack word; ret 4.
- Calls lower_bound at 0x0044C142 through ILT 0x0000EDEA.
- Compares the candidate's AsciiString key at node+0x10 against the input.
- If absent, allocates a 12-byte list sentinel, initializes its next/previous
  pointers to itself, copies the AsciiString, constructs the list-containing
  pair, and inserts at the lower-bound hint.
- Both paths return the mapped list by address at node+0x14.

Independent named caller: InGameUI::addSuperweapon at 0x0044C970 builds a
SuperweaponInfo through the known constructor, computes the per-player map
at complete-object +0x5CC with stride 12, calls ILT 0x00015FCD at 0x0044CA86,
and appends the SuperweaponInfo pointer to the returned list with 12-byte
list nodes. This proves both mapped type and ABI independently of DoXfer's
byte agreement. The official ZH addSuperweapon implementation uses exactly
m_superweapons[playerIndex][powerName].push_back(info).

The other initial unresolved call was a declaration-access error, fixed by
using the existing protected findSpecialPowerTemplatePrivate signature.
No pin was added for that call.
