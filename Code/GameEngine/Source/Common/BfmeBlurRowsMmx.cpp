// MMX sibling of bfmeBlurRowsSse: first/last row memcpy, middle rows
// (prev + 2*cur + next + 2) >> 2 eight bytes at a time.

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

namespace
{
	__declspec(align(8)) const unsigned short g_bfmeBlurBiasMmx[4] = { 2, 2, 2, 2 };
}

// ?bfmeBlurRowsMmx@@YAXPAX0IHH@Z
void __declspec(naked) __cdecl bfmeBlurRowsMmx(void *src, void *dst, unsigned int width, int count, int stride)
{
	__asm
	{
		push ebp
		mov ebp, esp
		mov ecx, width
		mov eax, dst
		mov edx, ecx
		push ebx
		push esi
		mov esi, src
		shr ecx, 2
		push edi
		mov src, esi
		mov edi, eax
		rep movsd
		mov ecx, edx
		and ecx, 3
		rep movsb
		mov ecx, count
		dec ecx
		cmp ecx, 1
		jle bfmeTail
		dec ecx
		mov count, ecx
	bfmeLoop:
		add eax, stride
		mov dst, eax
		mov esi, src
		mov edi, dst
		xor ecx, ecx
		mov edx, stride
		lea eax, [esi+edx]
		lea edx, [eax+edx]
		mov ebx, width
		pxor mm7, mm7
	bfmeInner:
		movq mm0, qword ptr [esi+ecx]
		movq mm1, qword ptr [eax+ecx]
		movq mm3, mm0
		punpcklbw mm0, mm7
		movq mm2, qword ptr [edx+ecx]
		punpckhbw mm3, mm7
		movq mm4, mm1
		punpcklbw mm1, mm7
		paddw mm0, g_bfmeBlurBiasMmx
		paddw mm3, g_bfmeBlurBiasMmx
		punpckhbw mm4, mm7
		psllw mm1, 1
		psllw mm4, 1
		movq mm5, mm2
		punpcklbw mm2, mm7
		paddw mm0, mm1
		paddw mm3, mm4
		punpckhbw mm5, mm7
		paddw mm0, mm2
		paddw mm3, mm5
		psraw mm0, 2
		psraw mm3, 2
		packuswb mm0, mm3
		movq qword ptr [edi+ecx], mm0
		add ecx, 8
		cmp ecx, ebx
		jl bfmeInner

		mov eax, stride
		mov ecx, src
		add ecx, eax
		dec count
		mov eax, dst
		mov src, ecx
		jnz bfmeLoop

	bfmeTail:
		mov ecx, stride
		mov esi, src
		add esi, ecx
		add eax, ecx
		mov ecx, width
		mov edx, ecx
		shr ecx, 2
		mov edi, eax
		rep movsd
		mov ecx, edx
		and ecx, 3
		rep movsb
		pop edi
		pop esi
		pop ebx
		pop ebp
		ret
	}
}
