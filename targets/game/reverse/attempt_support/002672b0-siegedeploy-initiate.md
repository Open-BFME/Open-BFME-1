# 0x002672B0 SiegeDeploySpecialPower interface slot 0 (650 B) — session 493 bank

BFME 1 target evidence: ILT 0x000199C0 is slot 0 of the +0x20 interface
vtable 0x00CB7468 installed by the matched constructor 0x00266240; ret 0x14
(five stack arguments); module data at this-0x1C, object at this-0x18.
Donor (open-bfme-2 20a0cb6173, Code/GameEngine/Source/GameLogic/Object/
SpecialPower/SiegeDeploySpecialPower.cpp, initiateIntentToDoSpecialPower,
568 B matched there) gives the same control flow: dock search through
SiegeDockingBehavior (+0x20 dock interface slot 3), partition scan with the
BitFlags<192>(kInit,0x3B) / Rva00251980 filter, computeApproachPoint
(BFME 1 0x002666A0, still a gen dump), transition(1) / clearStatusBit63, push
point from the X axis at object+8/+0x18/+0x28, setWakeFrame.
Name: ilt_oracle CONTRADICTED for 3456 initiateIntentToDoSpecialPower
signature variants, so the bank uses ?rva002672B0@SiegeDeploySpecialPower@@...

Bank (attempts/0x002672b0.cpp): 650/650 B, every difference a relocation
except one pair at +0x224/+0x22B: retail `lea eax,[esp+0x20]` (&p) precedes
the `mov [esp+0x28],edx` (p.z) store; ours stores first.
Levers that got here: `Int selfID` local for the first dock test and an inner
`Int id` after a `continue` null test in the scan loop (self in EDI, ai spill
slot); getData() accessor for the radius bits (ECX data / EDX radius);
Coord3D with a user copy-ctor `pos(targetObj->m_position)` and forward.z kept
(x87 consumes pos.x via fxch like retail).
Inert for the last pair: p.z position anywhere in the block, p/pos
declaration order, const pos, copy-init, compound p.x/p.y, pointer dest,
body-assignment copy ctor (other orders worse), inline pushPoint helper,
forward via 3-arg ctor or getXVector (worse), single-call dest form (worse).
To land: pin the 0x002666A0 callee (ILT 0x00020455) or land it first.
