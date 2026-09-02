// cl: /Od

char *bfmeFindChV28(char *first, char *last, char ch)
{
	char pad[8];

	__asm
	{
		mov eax, dword ptr [ebp+0x0C]
		sub eax, dword ptr [ebp+8]
		sar eax, 2
		mov dword ptr [ebp-4], eax
		jmp cmp_n
	dec_n:
		mov ecx, dword ptr [ebp-4]
		sub ecx, 1
		mov dword ptr [ebp-4], ecx
	cmp_n:
		cmp dword ptr [ebp-4], 0
		jle remainder
		movsx edx, byte ptr [ebp+0x10]
		mov eax, dword ptr [ebp+8]
		movsx ecx, byte ptr [eax]
		sub ecx, edx
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz n1
		mov eax, dword ptr [ebp+8]
		jmp done
	n1:
		mov ecx, dword ptr [ebp+8]
		add ecx, 1
		mov dword ptr [ebp+8], ecx
		movsx edx, byte ptr [ebp+0x10]
		mov eax, dword ptr [ebp+8]
		movsx ecx, byte ptr [eax]
		sub ecx, edx
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz n2
		mov eax, dword ptr [ebp+8]
		jmp done
	n2:
		mov ecx, dword ptr [ebp+8]
		add ecx, 1
		mov dword ptr [ebp+8], ecx
		movsx edx, byte ptr [ebp+0x10]
		mov eax, dword ptr [ebp+8]
		movsx ecx, byte ptr [eax]
		sub ecx, edx
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz n3
		mov eax, dword ptr [ebp+8]
		jmp done
	n3:
		mov ecx, dword ptr [ebp+8]
		add ecx, 1
		mov dword ptr [ebp+8], ecx
		movsx edx, byte ptr [ebp+0x10]
		mov eax, dword ptr [ebp+8]
		movsx ecx, byte ptr [eax]
		sub ecx, edx
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz n4
		mov eax, dword ptr [ebp+8]
		jmp done
	n4:
		mov ecx, dword ptr [ebp+8]
		add ecx, 1
		mov dword ptr [ebp+8], ecx
		jmp dec_n
	remainder:
		mov edx, dword ptr [ebp+0x0C]
		sub edx, dword ptr [ebp+8]
		mov dword ptr [ebp-8], edx
		cmp dword ptr [ebp-8], 1
		je rem1
		cmp dword ptr [ebp-8], 2
		je rem2
		cmp dword ptr [ebp-8], 3
		je rem3
		jmp ret_last
	rem3:
		movsx eax, byte ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+8]
		movsx edx, byte ptr [ecx]
		sub edx, eax
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz r3n
		mov eax, dword ptr [ebp+8]
		jmp done
	r3n:
		mov edx, dword ptr [ebp+8]
		add edx, 1
		mov dword ptr [ebp+8], edx
	rem2:
		movsx eax, byte ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+8]
		movsx edx, byte ptr [ecx]
		sub edx, eax
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz r2n
		mov eax, dword ptr [ebp+8]
		jmp done
	r2n:
		mov edx, dword ptr [ebp+8]
		add edx, 1
		mov dword ptr [ebp+8], edx
	rem1:
		movsx eax, byte ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+8]
		movsx edx, byte ptr [ecx]
		sub edx, eax
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz ret_last
		mov eax, dword ptr [ebp+8]
		jmp done
	ret_last:
		mov eax, dword ptr [ebp+0x0C]
	done:
	}
}
