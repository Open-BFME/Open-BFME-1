# RVA 0x0076B980 is W3DScriptedModelDraw::replaceModelConditionState

Retail constructor **0x00773360** installs primary table **0x01123D38**
at VA 0x00B73398 and final secondary table **0x01123C68 at +0x0C** at
VA **0x00B7339E**. Primary slots 2 and 4 route respectively to literal
getter **0x007739E0** and matched name-key getter **0x00773950**. Both use
literal **0x0111D2C0**, whose retail/Ghidra bytes spell
`W3DScriptedModelDraw`. The native owner is proven even though some existing
constructor/destructor labels inconsistently say W3DModelDraw.

Secondary slot **19 (+0x4C)** at **0x01123CB4** stores ILT
**0x0043AA5D** -> body **0x0076B980**. The same ILT occurs in six other
derived secondary tables, including constructor-installed W3DHordeModelDraw
table 0x011223A0. Those are inherited copies of this implementation.
The first six slots are independently named native render-object/bone
queries; later neighbors include handleWeaponFireFX, setSelectable and
setAnimationLoopDuration. ObjectDrawInterface's declaration agrees on
the replaceModelConditionState position.

Matched native **Drawable::updateDrawable**, RVA **0x0041BE60**, obtains
its ObjectDrawInterface, then at VA **0x0081BECE..0x0081BED3** pushes
zero, zero and the condition-flags pointer and calls virtual **+0x4C**.
This is the matched source's replaceModelConditionState call and confirms
the **BFME three-argument** interface, extending Zero Hour's declaration.
The implementation receives the +0x0C subobject: ECX-8 is full-object +4,
the module data pointer. It selects condition state and associated visual
effects. Complete retail extent is 953 bytes: RET 12 at +0x3B6 and INT3
at +0x3B9. No direct caller names the implementation.

The native owner/method and stack count are resolved, but independently
typing the lookup helpers remains necessary. tools/callees.py still reports
inferred thiscall one-pointer signatures at 0x00765B70 and 0x00765DC0,
whose existing candidate names/ABIs conflict. This commit records identity
and the extended interface without changing source, pins or ledger names.
