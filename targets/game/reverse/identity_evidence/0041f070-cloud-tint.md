# Opaque cloud/tint helper at RVA 0x0041F070

Complete441B retail extent endsRET4 at41F226; following bytes areINT3. ILTD364 reaches it, but no named caller or stored pointer proves its member name or owner. Therefore retain opaque Rva0041F070::method(bool), with receiver offsets8C and11C.

Callee inventory: operator new881F30 allocates50h bytes; ILT37475->412140 is the established71B Rva00412140 constructor storing TintEnvelope vptr and zeroing its80B layout. It has no calls or throwing operations, so throw() is justified. We retain its existing address-qualified80B storage view, and include canonical Drawable/TintEnvelope headers rather than redeclare TintEnvelope. Position ILT3EE55->41D150 is existing BFMERopeDrawableGetPositionShim::getPositionLinear, a borrowed three-float pointer.

Global VA12F1104 is existing g_bfmeGlobCC0, also read by native parseCloudEffect. Address-qualified dispatch view only: slot28 returns AL flag; slots40/44 consume12B coordinates and return ST0; receiver+A8 values1/2 select40,3/4 select44. Retail uses nontrivial coordinate copy construction (including saved ESP); a12B view derives from canonical Vector3 and owns an empty lifetime. The +2C color copy is plain RGBColor, from the canonical header.

Both tint calls go through ILT1F636->415A10. Full53B independently decoded: loads three stack dwords, stores them to+1C/+20/+24, copies to+28/+2C/+30, sets byte38=3 and dword34=-2, RET0C. The existing BfmeRange970::bfmeSet970(int,int,int) declaration covers that exact bitwise ABI. Checked4B member-pointer bridge passes native RGBColor by value without adding a false named member or a new pin.

fcom against-25 followed by TEST AH,41 implements <=-25, not <; fcomp against+25 with TEST AH,1 selects >=25. Flags1/2/4/8 and guarded calls follow retail directly. Explicit labels preserve the independently witnessed first/second virtual-call block ordering; ordinary if/else reordered the blocks, leaving52 differences at identical441B size. No ASM or guessed semantic name.
