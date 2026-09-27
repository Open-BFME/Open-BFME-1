// ?Rva009B3F40Vp6Reconstruct@@YAXPAXPAF1E@Z
// partial score=0.1 date=2026-09-27
// ?Rva009B3F40Vp6Reconstruct@@YAXPAXPAFPAFE@Z
// cl: /O2 /Z7

void Rva009B3F40Vp6Reconstruct(void *context, short *source, short *destination, unsigned char selector)
{
	volatile __declspec(align(16)) unsigned char frame[0xa0];

	__asm
	{
		movzx eax, byte ptr [ebx + 14h]
		movzx eax, byte ptr [eax + 01142608h]
		mov ecx, dword ptr [ebx + 8]
		shl eax, 8
		lea edx, [eax + ecx]
		mov eax, dword ptr [edx + 190h]
		mov dword ptr [ebp - 8], eax
	}

	__asm
	{
		lea eax, [ecx + 8]
		push esi
		add ecx, 18h
		push edi
		mov dword ptr [ebp - 10h], edx
		mov dword ptr [ebp - 14h], eax
		mov dword ptr [ebp - 0ch], ecx
		mov dword ptr [ebp - 4], 0
		mov esi, dword ptr [ebx + 0ch]
		xor ecx, ecx
		mov edi, dword ptr [ebp - 14h]
		movdqu xmm2, xmmword ptr [edi]
		mov edi, dword ptr [ebp - 0ch]
		movdqu xmm3, xmmword ptr [edi]
		lea edi, frame
		mov eax, dword ptr [ebx + 10h]
		pxor xmm7, xmm7
	Rva009B3F40Loop:
		movdqa xmm0, xmmword ptr [esi + ecx]
		movdqa xmm1, xmm0
		psraw xmm1, 0fh
		pxor xmm0, xmm1
		psubw xmm0, xmm1
		paddw xmm0, xmm2
		pmulhuw xmm0, xmm3
		pxor xmm0, xmm1
		psubw xmm0, xmm1
		movdqa xmmword ptr [edi + ecx], xmm0
		movdqa xmmword ptr [eax + ecx], xmm7
		add ecx, 10h
		cmp ecx, 80h
		jl Rva009B3F40Loop
		mov ecx, dword ptr [ebx + 0ch]
		movsx eax, word ptr [ecx]
		mov ecx, dword ptr [edx + 590h]
		cmp eax, ecx
		mov esi, dword ptr [ebx + 10h]
		jl Rva009B3F40Neg0
		mov edx, dword ptr [edx + 390h]
		add edx, eax
		imul edx, dword ptr [ebp - 8]
		sar edx, 10h
		mov word ptr [esi], dx
		jmp Rva009B3F40After0
	Rva009B3F40Neg0:
		neg ecx
		cmp eax, ecx
		jg Rva009B3F40Small0
		sub eax, dword ptr [edx + 390h]
		imul eax, dword ptr [ebp - 8]
		add eax, 0ffffh
		sar eax, 10h
		mov word ptr [esi], ax
		jmp Rva009B3F40After0
	Rva009B3F40Small0:
		mov dword ptr [ebp - 4], 1
	Rva009B3F40After0:
		add esi, 6
		mov eax, 4
		mov dword ptr [ebp - 0ch], esi
		mov dword ptr [ebp - 8], eax
		jmp Rva009B3F40Outer
	Rva009B3F40Pad:
		lea esp, [esp]
		mov edi, edi
	Rva009B3F40Outer:
		mov ecx, dword ptr [eax + 012D8258h]
		movzx esi, word ptr [ebp + ecx * 2 - 0a0h]
		test esi, esi
		jne Rva009B3F40Write1
		inc dword ptr [ebp - 4]
		jmp Rva009B3F40Next1
	Rva009B3F40Write1:
		mov eax, dword ptr [ebx + 0ch]
		movsx eax, word ptr [eax + ecx * 2]
		cdq
		mov edi, eax
		mov eax, dword ptr [ebp - 10h]
		xor edi, edx
		sub edi, edx
		mov edx, dword ptr [ebp - 4]
		mov edx, dword ptr [eax + edx * 4 + 790h]
		add edx, dword ptr [eax + ecx * 4 + 590h]
		cmp edi, edx
		jge Rva009B3F40Store1
		inc dword ptr [ebp - 4]
		jmp Rva009B3F40Next1
	Rva009B3F40Store1:
		mov eax, dword ptr [ebp - 0ch]
		mov dword ptr [ebp - 4], 0
		mov word ptr [eax - 4], si
	Rva009B3F40Next1:
		mov ecx, dword ptr [ebp - 8]
		mov ecx, dword ptr [ecx + 012D825Ch]
		movzx esi, word ptr [ebp + ecx * 2 - 0a0h]
		test esi, esi
		jne Rva009B3F40Write2
		inc dword ptr [ebp - 4]
		jmp Rva009B3F40Next2
	Rva009B3F40Write2:
		mov edx, dword ptr [ebx + 0ch]
		movsx eax, word ptr [edx + ecx * 2]
		cdq
		mov edi, eax
		mov eax, dword ptr [ebp - 10h]
		xor edi, edx
		sub edi, edx
		mov edx, dword ptr [ebp - 4]
		mov edx, dword ptr [eax + edx * 4 + 790h]
		add edx, dword ptr [eax + ecx * 4 + 590h]
		cmp edi, edx
		jge Rva009B3F40Store2
		inc dword ptr [ebp - 4]
		jmp Rva009B3F40Next2
	Rva009B3F40Store2:
		mov eax, dword ptr [ebp - 0ch]
		mov dword ptr [ebp - 4], 0
		mov word ptr [eax - 2], si
	Rva009B3F40Next2:
		mov ecx, dword ptr [ebp - 8]
		mov ecx, dword ptr [ecx + 012D8260h]
		movzx esi, word ptr [ebp + ecx * 2 - 0a0h]
		test esi, esi
		jne Rva009B3F40Write3
		inc dword ptr [ebp - 4]
		jmp Rva009B3F40Next3
	Rva009B3F40Write3:
		mov edx, dword ptr [ebx + 0ch]
		movsx eax, word ptr [edx + ecx * 2]
		cdq
		mov edi, eax
		mov eax, dword ptr [ebp - 10h]
		xor edi, edx
		sub edi, edx
		mov edx, dword ptr [ebp - 4]
		mov edx, dword ptr [eax + edx * 4 + 790h]
		add edx, dword ptr [eax + ecx * 4 + 590h]
		cmp edi, edx
		jge Rva009B3F40Store3
		inc dword ptr [ebp - 4]
		jmp Rva009B3F40Next3
	Rva009B3F40Store3:
		mov eax, dword ptr [ebp - 0ch]
		mov dword ptr [ebp - 4], 0
		mov word ptr [eax], si
	Rva009B3F40Next3:
		mov eax, dword ptr [ebp - 8]
		mov edx, dword ptr [ebp - 0ch]
		add eax, 0ch
		add edx, 6
		cmp eax, 100h
		mov dword ptr [ebp - 8], eax
		mov dword ptr [ebp - 0ch], edx
		jb Rva009B3F40Outer
		pop edi
		pop esi
	}
}
