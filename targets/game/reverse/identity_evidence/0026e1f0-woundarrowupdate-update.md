# RVA 0x0026E1F0 is WoundArrowUpdate::update

All addresses below were checked against the retail-1.03-unpacked PE with
pefile and Capstone. GhidraMCP independently confirms the owner literal and
the unique stub-pointer occurrence.

## Owner and secondary interface

Matched WoundArrowUpdate constructor RVA 0x0026DFB0 installs primary table
VA 0x010B9158 at VA 0x0066DFC4, behavior table 0x010B9090 at +0x0C, and
table **0x010B9084 at +0x10** at VA 0x0066DFD1. The destructor reinstalls
the same tables. Primary slot 4 contains ILT 0x004026E4 -> RVA 0x0026E050,
the matched getModuleNameKey body. That body pushes VA 0x0108F8D8, whose
retail bytes spell `WoundArrowUpdate`, into the name-key generator.

Table 0x010B9084 has two entries: ILT VA **0x004195E7** -> body RVA
**0x0026E1F0**, then ILT 0x0044985F -> matched
UpdateModule::getDisabledTypesToProcess at RVA 0x0011A130. Searching the
image for E7 95 41 00 finds only the first table entry.

## The named sibling establishes the slot

Matched DemoTrapUpdate constructor RVA 0x0028C7F0 installs its +0x10 table
0x010BD6D0 at VA 0x0068C833. Its first entry is ILT 0x00441718 -> matched
DemoTrapUpdate::update, RVA 0x0028CAD0; the second is the **same**
getDisabledTypesToProcess ILT 0x0044985F. These BFME tables independently
establish the update-interface position. UpdateModule.h's declaration
order agrees, but is not the sole identity evidence.

The body's early return is 1 and its completion return is 0x3FFFFFFF,
agreeing with UpdateSleepTime. The signature is
`?update@WoundArrowUpdate@@UAE?AW4UpdateSleepTime@@XZ`, with incoming ECX
pointing +0x10 into the full object.

## Boundary and remaining conversion work

There are early RETs and a final plain RET at RVA 0x0026E325 (+0x135).
INT3 begins at +0x136, giving 310 bytes. Earlier logs calling +0x136 the
RET offset included the padding byte.

The identity blocker is resolved. Conversion still needs independently
typed AI virtual calls at +0x180/+0x1FC and the primary callback at +0x3C.
The existing callee at RVA 0x001C9B80 has a synthetic void-pointer argument
despite this body pushing integer 2; its decoded tail calls matched
WeaponSet::releaseWeaponLock at RVA 0x001EBB40 on Object+0x264. The final
814-byte callee at RVA 0x002A8540 remains a dump. Repairing these contracts
is a separate source task; this commit changes no source, pins or ledger
identity.
