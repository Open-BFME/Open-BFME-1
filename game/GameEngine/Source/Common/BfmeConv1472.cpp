// cl: /Od

char **bfmeRFindNotChV32(char **out, char *last, char *first, char ch)
{
	char pad[44];

	__asm
	{
		mov eax, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp-8]
		sub ecx, dword ptr [ebp+0x10]
		sar ecx, 2
		mov dword ptr [ebp-4], ecx
		jmp cmp_n
	dec_n:
		mov edx, dword ptr [ebp-4]
		sub edx, 1
		mov dword ptr [ebp-4], edx
	cmp_n:
		cmp dword ptr [ebp-4], 0
		jle remainder
		mov eax, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp-0x0C]
		sub ecx, 1
		mov dword ptr [ebp-0x0C], ecx
		movsx edx, byte ptr [ebp+0x14]
		mov eax, dword ptr [ebp-0x0C]
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
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ebp+0x0C]
		mov dword ptr [ecx], edx
		mov eax, dword ptr [ebp+8]
		jmp done
	n1:
		mov eax, dword ptr [ebp+0x0C]
		sub eax, 1
		mov dword ptr [ebp+0x0C], eax
		mov ecx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp-0x10]
		sub edx, 1
		mov dword ptr [ebp-0x10], edx
		movsx eax, byte ptr [ebp+0x14]
		mov ecx, dword ptr [ebp-0x10]
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
		jz n2
		mov edx, dword ptr [ebp+8]
		mov eax, dword ptr [ebp+0x0C]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+8]
		jmp done
	n2:
		mov ecx, dword ptr [ebp+0x0C]
		sub ecx, 1
		mov dword ptr [ebp+0x0C], ecx
		mov edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x14], edx
		mov eax, dword ptr [ebp-0x14]
		sub eax, 1
		mov dword ptr [ebp-0x14], eax
		movsx ecx, byte ptr [ebp+0x14]
		mov edx, dword ptr [ebp-0x14]
		movsx eax, byte ptr [edx]
		sub eax, ecx
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jz n3
		mov eax, dword ptr [ebp+8]
		mov ecx, dword ptr [ebp+0x0C]
		mov dword ptr [eax], ecx
		mov eax, dword ptr [ebp+8]
		jmp done
	n3:
		mov edx, dword ptr [ebp+0x0C]
		sub edx, 1
		mov dword ptr [ebp+0x0C], edx
		mov eax, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp-0x18]
		sub ecx, 1
		mov dword ptr [ebp-0x18], ecx
		movsx edx, byte ptr [ebp+0x14]
		mov eax, dword ptr [ebp-0x18]
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
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ebp+0x0C]
		mov dword ptr [ecx], edx
		mov eax, dword ptr [ebp+8]
		jmp done
	n4:
		mov eax, dword ptr [ebp+0x0C]
		sub eax, 1
		mov dword ptr [ebp+0x0C], eax
		jmp dec_n
	remainder:
		mov ecx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x1C], ecx
		mov edx, dword ptr [ebp-0x1C]
		sub edx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x2C], edx
		cmp dword ptr [ebp-0x2C], 1
		je rem1
		cmp dword ptr [ebp-0x2C], 2
		je rem2
		cmp dword ptr [ebp-0x2C], 3
		je rem3
		jmp notfound
	rem3:
		mov eax, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x20], eax
		mov ecx, dword ptr [ebp-0x20]
		sub ecx, 1
		mov dword ptr [ebp-0x20], ecx
		movsx edx, byte ptr [ebp+0x14]
		mov eax, dword ptr [ebp-0x20]
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
		jz r3n
		mov ecx, dword ptr [ebp+8]
		mov edx, dword ptr [ebp+0x0C]
		mov dword ptr [ecx], edx
		mov eax, dword ptr [ebp+8]
		jmp done
	r3n:
		mov eax, dword ptr [ebp+0x0C]
		sub eax, 1
		mov dword ptr [ebp+0x0C], eax
	rem2:
		mov ecx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x24], ecx
		mov edx, dword ptr [ebp-0x24]
		sub edx, 1
		mov dword ptr [ebp-0x24], edx
		movsx eax, byte ptr [ebp+0x14]
		mov ecx, dword ptr [ebp-0x24]
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
		mov edx, dword ptr [ebp+8]
		mov eax, dword ptr [ebp+0x0C]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+8]
		jmp done
	r2n:
		mov ecx, dword ptr [ebp+0x0C]
		sub ecx, 1
		mov dword ptr [ebp+0x0C], ecx
	rem1:
		mov edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x28], edx
		mov eax, dword ptr [ebp-0x28]
		sub eax, 1
		mov dword ptr [ebp-0x28], eax
		movsx ecx, byte ptr [ebp+0x14]
		mov edx, dword ptr [ebp-0x28]
		movsx eax, byte ptr [edx]
		sub eax, ecx
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jz notfound
		mov eax, dword ptr [ebp+8]
		mov ecx, dword ptr [ebp+0x0C]
		mov dword ptr [eax], ecx
		mov eax, dword ptr [ebp+8]
		jmp done
	notfound:
		mov edx, dword ptr [ebp+8]
		mov eax, dword ptr [ebp+0x10]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+8]
	done:
	}
}
