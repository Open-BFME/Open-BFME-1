// ?Rva009B4170@@YAXPAXPAF1E@Z
// partial score=0.95 date=2026-09-27
// cl: /O2 /Ob0 /Z7 /DNDEBUG /DWIN32 /D_WINDOWS /MD

void __cdecl Rva009B4170(void *rawState, short *input, short *output,
	unsigned char selector)
{
	unsigned char mode = *((unsigned char *)0x01142608 + selector);
	unsigned char *table = (unsigned char *)rawState + ((unsigned)mode << 8);
	int reciprocal = *(int *)(table + 0x190);
	__declspec(align(16)) short work[64];
	unsigned char *state8 = (unsigned char *)rawState + 8;
	unsigned char *state18 = (unsigned char *)rawState + 0x18;
	int run = 0;

	__asm
	{
		mov esi, dword ptr [ebx + 0Ch]
		xor ecx, ecx
		mov edi, state8
		movq mm2, qword ptr [edi]
		mov edi, state18
		movq mm3, qword ptr [edi]
		lea edi, work
		mov eax, dword ptr [ebx + 10h]
		pxor mm7, mm7
	quantize_loop:
		movq mm0, qword ptr [esi + ecx]
		movq mm1, mm0
		psraw mm1, 0Fh
		pxor mm0, mm1
		psubw mm0, mm1
		paddw mm0, mm2
		pmulhuw mm0, mm3
		pxor mm0, mm1
		psubw mm0, mm1
		movq qword ptr [edi + ecx], mm0
		movq qword ptr [eax + ecx], mm7
		add ecx, 8
		cmp ecx, 80h
		jl quantize_loop

		mov ecx, dword ptr [ebx + 0Ch]
		movsx eax, word ptr [ecx]
		mov ecx, dword ptr [edx + 590h]
		cmp eax, ecx
		mov esi, dword ptr [ebx + 10h]
		jl quantize_first_small
		mov edx, dword ptr [edx + 390h]
		add edx, eax
		imul edx, reciprocal
		sar edx, 10h
		mov word ptr [esi], dx
		jmp quantize_first_done
	quantize_first_small:
		neg ecx
		cmp eax, ecx
		jg quantize_first_run
		sub eax, dword ptr [edx + 390h]
		imul eax, reciprocal
		add eax, 0FFFFh
		sar eax, 10h
		mov word ptr [esi], ax
		jmp quantize_first_done
	quantize_first_run:
		mov run, 1
	quantize_first_done:
		add esi, 6
		mov eax, 4
		mov state18, esi
		mov reciprocal, eax
		jmp quantize_triplet
		lea esp, [esp]
	quantize_triplet:
		mov ecx, dword ptr [eax + 12D8258h]
		movzx esi, word ptr [ebp + ecx * 2 - 0A0h]
		test esi, esi
		jne quantize_first_nonzero
		inc run
		jmp quantize_second
	quantize_first_nonzero:
		mov eax, dword ptr [ebx + 0Ch]
		movsx eax, word ptr [eax + ecx * 2]
		cdq
		mov edi, eax
		mov eax, table
		xor edi, edx
		sub edi, edx
		mov edx, run
		mov edx, dword ptr [eax + edx * 4 + 790h]
		add edx, dword ptr [eax + ecx * 4 + 590h]
		cmp edi, edx
		jge quantize_first_store
		inc run
		jmp quantize_second
	quantize_first_store:
		mov eax, state18
		mov run, 0
		mov word ptr [eax - 4], si
	quantize_second:
		mov ecx, reciprocal
		mov ecx, dword ptr [ecx + 12D825Ch]
		movzx esi, word ptr [ebp + ecx * 2 - 0A0h]
		test esi, esi
		jne quantize_second_nonzero
		inc run
		jmp quantize_third
	quantize_second_nonzero:
		mov edx, dword ptr [ebx + 0Ch]
		movsx eax, word ptr [edx + ecx * 2]
		cdq
		mov edi, eax
		mov eax, table
		xor edi, edx
		sub edi, edx
		mov edx, run
		mov edx, dword ptr [eax + edx * 4 + 790h]
		add edx, dword ptr [eax + ecx * 4 + 590h]
		cmp edi, edx
		jge quantize_second_store
		inc run
		jmp quantize_third
	quantize_second_store:
		mov eax, state18
		mov run, 0
		mov word ptr [eax - 2], si
	quantize_third:
		mov ecx, reciprocal
		mov ecx, dword ptr [ecx + 12D8260h]
		movzx esi, word ptr [ebp + ecx * 2 - 0A0h]
		test esi, esi
		jne quantize_third_nonzero
		inc run
		jmp quantize_triplet_next
	quantize_third_nonzero:
		mov edx, dword ptr [ebx + 0Ch]
		movsx eax, word ptr [edx + ecx * 2]
		cdq
		mov edi, eax
		mov eax, table
		xor edi, edx
		sub edi, edx
		mov edx, run
		mov edx, dword ptr [eax + edx * 4 + 790h]
		add edx, dword ptr [eax + ecx * 4 + 590h]
		cmp edi, edx
		jge quantize_third_store
		inc run
		jmp quantize_triplet_next
	quantize_third_store:
		mov eax, state18
		mov run, 0
		mov word ptr [eax], si
	quantize_triplet_next:
		mov eax, reciprocal
		mov edx, state18
		add eax, 0Ch
		add edx, 6
		cmp eax, 100h
		mov reciprocal, eax
		mov state18, edx
		jb quantize_triplet
	}
}
