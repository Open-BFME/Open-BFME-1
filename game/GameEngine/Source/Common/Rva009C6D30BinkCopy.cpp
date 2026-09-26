// cl: /DNDEBUG /MD /O2
//
// 8x8 pixel block copy by stride, used by the Bink filter dispatch to relay
// an unmodified block.  Retail 0x009C6D30, 110 bytes, esp-relative with no
// ebp frame.  Any parameter referenced by NAME inside the __asm block is
// conservatively spilled to a fresh stack slot before the block (the "push
// ecx" reserves that slot) and reloaded in first-use order; letting the
// compiler own the whole spill/reload/register-save dance -- no push/pop
// written by hand -- reproduces retail exactly, including its single
// (non-doubled) save of ebx.  Named locals mirror retail's spill order
// (source, destination, stride) and the asm block's own instruction order
// mirrors retail's reload order (stride, source, destination).

// ?rva009C6D30BinkCopy@@YAXPBXPAXH@Z
void __cdecl rva009C6D30BinkCopy(const void *source, void *destination, int stride)
{
	const void *src = source;
	void *dst = destination;
	int str = stride;
	__asm
	{
		mov ecx, str
		mov eax, src
		mov ebx, dst
		lea edx, [ecx + ecx*2]
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq mm2, qword ptr [eax + ecx*2]
		movq mm3, qword ptr [eax + edx]
		lea eax, [eax + ecx*4]
		movq qword ptr [ebx], mm0
		movq qword ptr [ebx + ecx], mm1
		movq qword ptr [ebx + ecx*2], mm2
		movq qword ptr [ebx + edx], mm3
		lea ebx, [ebx + ecx*4]
		movq mm0, qword ptr [eax]
		movq mm1, qword ptr [eax + ecx]
		movq mm2, qword ptr [eax + ecx*2]
		movq mm3, qword ptr [eax + edx]
		movq qword ptr [ebx], mm0
		movq qword ptr [ebx + ecx], mm1
		movq qword ptr [ebx + ecx*2], mm2
		movq qword ptr [ebx + edx], mm3
	}
}
