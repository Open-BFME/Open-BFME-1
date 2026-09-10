// cl: /O2 /Z7
//
// VP6 SSE2 byte filter installed in the SSE CPU tier's dispatch slot 19.
// Retail builds three aligned 16-byte byte patterns, then applies them with
// psubusb/paddusb/psubusb across the source and destination planes.

struct Rva009BD470PatternFrame
{
	unsigned char patternA[16];
	unsigned char patternB[16];
	unsigned char patternC[16];
	unsigned char padding[32];
};

extern "C" void __cdecl Rva009BD470Vp6FilterSse(
	void *context, void *byteArgumentA, void *byteArgumentB,
	int sourceOffset, int destinationOffset)
{
	__declspec(align(16)) Rva009BD470PatternFrame patterns;

	__asm {
		mov eax, context
		mov ecx, [eax + 90h]
		mov edx, sourceOffset
		shl ecx, 3
		mov dword ptr [ebp - 14h], ecx
		mov ecx, [eax + 78h]
		add edx, ecx
		mov dword ptr [ebp - 4], edx
		mov edx, destinationOffset
		add ecx, edx
		mov dl, byte ptr byteArgumentA
		mov dword ptr [ebp - 8], ecx
		mov esi, [eax + 94h]
		mov eax, [eax + 98h]
		mov dword ptr [ebp - 10h], eax
		mov eax, byteArgumentB
		mov cl, al
		add cl, dl
		mov dl, cl
		mov dh, dl
		shl esi, 3
		mov ecx, edx
		shl ecx, 10h
		mov cx, dx
		mov dword ptr patterns.patternB, ecx
		mov dword ptr patterns.patternB[4], ecx
		mov dword ptr patterns.patternB[8], ecx
		mov dword ptr patterns.patternB[0Ch], ecx
		mov cl, al
		mov ch, cl
		mov eax, ecx
		shl eax, 10h
		mov ax, cx
		mov dword ptr patterns.patternC, eax
		mov dword ptr patterns.patternC[4], eax
		mov dword ptr patterns.patternC[8], eax
		mov dword ptr patterns.patternC[0Ch], eax
		mov eax, byteArgumentA
		mov dl, al
		mov dh, dl
		mov eax, edx
		shl eax, 10h
		test esi, esi
		mov ax, dx
		mov dword ptr patterns.patternA, eax
		mov dword ptr patterns.patternA[4], eax
		mov dword ptr patterns.patternA[8], eax
		mov dword ptr patterns.patternA[0Ch], eax
		jle filter_done
		mov edx, dword ptr [ebp - 10h]
		mov dword ptr [ebp - 0Ch], esi
		mov edi, edi
	filter_outer:
		mov ecx, dword ptr [ebp - 14h]
		mov esi, dword ptr [ebp - 4]
		mov edi, dword ptr [ebp - 8]
		xor eax, eax
	filter_inner:
		movdqa xmm1, xmmword ptr [esi + eax]
		psubusb xmm1, xmmword ptr [patterns.patternA]
		paddusb xmm1, xmmword ptr [patterns.patternB]
		psubusb xmm1, xmmword ptr [patterns.patternC]
		movdqa xmmword ptr [edi + eax], xmm1
		add eax, 10h
		cmp eax, ecx
		jl filter_inner
		mov esi, dword ptr [ebp - 4]
		mov ecx, dword ptr [ebp - 8]
		mov eax, dword ptr [ebp - 0Ch]
		add esi, edx
		add ecx, edx
		dec eax
		mov dword ptr [ebp - 4], esi
		mov dword ptr [ebp - 8], ecx
		mov dword ptr [ebp - 0Ch], eax
		jne filter_outer
	filter_done:
	}
}
