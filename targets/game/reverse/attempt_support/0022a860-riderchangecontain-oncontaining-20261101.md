# 0x0022A860 RiderChangeContain::onContaining — s521 donor port (partial)

Inputs: BFME 1 retail 0x0022A860 (739 B, ret 8 at +0x2E0); Open BFME 2
45afcff3 `Code/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainOnContaining.cpp`
(its retail 0x0047E5D4, /O1 /G7 there; BFME 1 TU built with default /O2).

Facts from the BFME 1 body: receiver is the contain interface at +0x20
(object this-0x18, module data this-0x1C, m_containing this+0xEC); riders
at module data +0x24C stride 0x18 (template +0, weapon set +4, model
condition +8, status +0xC, command set +0x10, locomotor +0x14); base call
is ILT 0x116EE -> ?onContaining@SiegeEngineContain@@ (0x0022B3E0); Object
+0x28 vslot getDrawable, +0x110 model-condition words, +0x204 AI, +0x210
experience tracker, +0x328 command-set override (by-value AsciiString
setter: copy ctor / set / releaseBuffer); rider gets status bit 39.

Best source (bank): 738/739 B, 344 non-reloc diffs, shape 0.968. Levers that
helped: real STLport bitset BitFlags (unfolded `mov eax,ecx; or eax,0x80`
mask build), inline recursive Overridable::getFinalOverride +
`if (t) t = t->getFinalOverride()` template null flow, forceinline
setModelConditionState, `getObject()->setModelConditionState` in the found
block (keeps `this` in EBX through the loop as retail and adds the loop-head
alignment pad).

Remaining: a register permutation. Retail obj=ESI, rider=EDI (prologue),
i=EBP, rider-slot pointer=EDI; ours obj=EBP, rider=ESI, i=ESI. Ruled out
(all worse): RiderInfo reference in the found block, data local declared
earlier/inside found block, found block moved after the loop (`if (i<8)`),
`Int i` hoisted, getObject() on any other single found-block statement,
obj declared after the relationship test.
