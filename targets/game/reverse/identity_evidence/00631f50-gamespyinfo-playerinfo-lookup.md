# RVA 0x00631F50 belongs to GameSpyInfo

The current row `?bfmeFindFZ_00631F50@BfmeMapFZ@@QAEPAHH@Z` is a
byte-matched address-qualified lookup. Its owner and returned record can now
be identified independently, but **the original method spelling is not proven**.
Do not promote a guessed `findPlayerInfo` name from this evidence.

All addresses below were checked against
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, image base
0x00400000, using pefile and capstone. GhidraMCP's byte search for
`FA 77 42 00` independently returns VA 0x01118920, and its 112-byte read at
VA 0x011188E0 agrees with retail.

## Native owner and slot

ILT RVA 0x000277FA (`E9`) targets VA 0x00A31F50, the body at RVA
0x00631F50. Its pointer occurs at VA 0x01118920, slot 20 (+0x50) of the table
beginning at VA 0x011188D0. The constructor at RVA 0x00636D90 writes that
exact table to `[esi]` at VA 0x00A36DB1. The table has these independently
named neighbours (followed through the retail E9 stubs):

| Slot | Body RVA | Existing BFME name |
|---|---|---|
| 4 | 0x00636650 | GameSpyInfo::addGroupRoom |
| 6 | 0x00634BF0 | GameSpyInfo::joinGroupRoom |
| 7 | 0x00634CE0 | GameSpyInfo::leaveGroupRoom |
| 10 | 0x006374D0 | GameSpyInfo::setCurrentGroupRoom |
| 16 | 0x00636C60 | GameSpyInfo::updatePlayerInfo |
| 17 | 0x00633F80 | GameSpyInfo::playerLeftGroupRoom |
| 18 | 0x00637100 | GameSpyInfo::getPlayerInfoMap |
| 19 | 0x00632850 | Address-qualified lookup by narrow string |
| **20** | **0x00631F50** | **This lookup by integer** |
| 24 | 0x00632810 | GameSpyInfo::isBuddy |
| 25 | 0x00637240 | GameSpyInfo::setLocalName |

The owner follows from the constructor-installed table and the independently
named neighbouring methods, rather than from a guessed destructor name.

## Record and key contract

The 58-byte body starts with `mov esi,ecx`, loads the tree header at `this+0x4C`,
walks it through the matched `_Rb_global<bool>::_M_increment` at RVA 0x0082B870,
compares the input integer with node+0x28, and returns node+0x14 on a hit.
It returns null on exhaustion and ends with `ret 4` at RVA 0x00631F87,
followed by INT3 padding at 0x00631F8A. Thus the record-relative compared field
is +0x14. `tools/name_oracle.py` identifies GameSpyInfo+0x4C as
`m_playerInfoMap` and PlayerInfo+0x14 as `m_profileID`.

The already matched `GameSpyInfo::playerLeftGroupRoom` at 0x00633F80 uses the
same map at +0x4C and 0x34-byte PlayerInfo records; its string-keyed traversal
corroborates the map identity. `getPlayerInfoMap` at 0x00637100 returns
`this+0x4C`. These facts establish a GameSpyInfo member returning a pointer to
a PlayerInfo whose profile ID equals its one integer argument. The ledger's
`int *` result describes the same machine ABI but not the semantic record type.

## Remaining limitation

Zero Hour's `GeneralsMD/.../GameNetwork/GameSpy/PeerDefs.h` has
`getPlayerInfoMap`, followed by the buddy-map accessors; it has neither of BFME's
extra slots 19 and 20. It therefore cannot supply their original names or
prove an overload relationship. No BFME export, EA-name entry or named matched
caller was found that names slot 20. Keep the address in the method name until
such evidence exists. This finding does not authorize a new alias pin or a
second identity at the same address.
