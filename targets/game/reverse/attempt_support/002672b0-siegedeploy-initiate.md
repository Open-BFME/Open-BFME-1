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

## 0x002666A0 approach-point helper (725 B) — same session

Bank attempts/0x002666a0.cpp: 723/725 B, shape 0.976. Everything matches
except the normalize block: retail keeps 1/len live on the x87 stack to the
end (`fld [y]; fmul st(2)`, `fld [z]; fmul st(2)`, final `fstp st(0)`),
ours consumes it at z (`fld st(1); fmul [y]`, `fxch; fmul [z]`), which also
shifts the loop-head pad by 3. Got here with: targetPosition pointer local at
the top, STLport bitset<86> BitFlags(kInit,63), `position = copyAt(index)`
(Rva002060B0Triple float view with a user copy ctor), `*(Rva00206100Point*)
dockPosition = point(index)`, struct copy `position = *targetPosition` before
the `+= offset` adds. Inert for the normalize: operand order, statement
order permutations (worse), named length/lengthSqr, const or function-scope
inverse, inline normalize/scale members, free inline normalize helper, dead
reuse of inverse; a separate step vector reproduces the y pattern but moves
the stores (0.986, 726 B). The retail idiom is unique in .text (regex search).
Pins needed to land: callers use Coord3D class spelling; bfmeGroundCellThreshold
is ledgered with PBUCoord3D (needs an alias pin at ILT 0x0003CE25).

## Session 494: the last pair is an escape-analysis effect

When AICommandInterface::aiMoveToPosition is visible in the same TU as a
non-capturing noinline stub, the bank probes EXACT 650/650. Retail calls it
through ILT 0x0003436A, and its body is 0x000D86C0 (matched in
AICommandInterfaceMovementOrders.cpp). Without that visibility there are 6
diffs: the lea &p / p.z store pair at +0x224. The real aiMoveToPosition only
copies *pos into its command parms, so it does not capture the pointer, and
retail's unit probably saw it. Two obstacles remain before landing:
(1) the matched aiMoveToPosition row is spelled with a struct Coord3D (PBU),
while this body's own name and its callers need class Coord3D (PBV). One TU
cannot spell both, so rehoming needs the two spellings reconciled first.
(2) The 0x002666A0 callee pin (ILT 0x00020455) is still open. Diagnostic
source: build-only stub, see docs/shape_levers.md "Callees must share the
TU".
