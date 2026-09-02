// cl: /Od

int bfmePredV30(int a, int b, char ch);

char *bfmeFindIfV30(char *first, char *last, int a, int b)
{
	char pad[24];

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
		mov edx, dword ptr [ebp+8]
		mov al, byte ptr [edx]
		mov byte ptr [ebp-6], al
		mov cl, byte ptr [ebp-6]
		mov byte ptr [ebp-5], cl
		mov dl, byte ptr [ebp-5]
		push edx
		mov eax, dword ptr [ebp+0x14]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
		neg eax
		sbb eax, eax
		inc eax
		movzx edx, al
		test edx, edx
		jz n1
		mov eax, dword ptr [ebp+8]
		jmp done
	n1:
		mov eax, dword ptr [ebp+8]
		add eax, 1
		mov dword ptr [ebp+8], eax
		mov ecx, dword ptr [ebp+8]
		mov dl, byte ptr [ecx]
		mov byte ptr [ebp-8], dl
		mov al, byte ptr [ebp-8]
		mov byte ptr [ebp-7], al
		mov cl, byte ptr [ebp-7]
		push ecx
		mov edx, dword ptr [ebp+0x14]
		push edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz n2
		mov eax, dword ptr [ebp+8]
		jmp done
	n2:
		mov edx, dword ptr [ebp+8]
		add edx, 1
		mov dword ptr [ebp+8], edx
		mov eax, dword ptr [ebp+8]
		mov cl, byte ptr [eax]
		mov byte ptr [ebp-0x0A], cl
		mov dl, byte ptr [ebp-0x0A]
		mov byte ptr [ebp-9], dl
		mov al, byte ptr [ebp-9]
		push eax
		mov ecx, dword ptr [ebp+0x14]
		push ecx
		mov edx, dword ptr [ebp+0x10]
		push edx
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
		neg eax
		sbb eax, eax
		inc eax
		movzx eax, al
		test eax, eax
		jz n3
		mov eax, dword ptr [ebp+8]
		jmp done
	n3:
		mov ecx, dword ptr [ebp+8]
		add ecx, 1
		mov dword ptr [ebp+8], ecx
		mov edx, dword ptr [ebp+8]
		mov al, byte ptr [edx]
		mov byte ptr [ebp-0x0C], al
		mov cl, byte ptr [ebp-0x0C]
		mov byte ptr [ebp-0x0B], cl
		mov dl, byte ptr [ebp-0x0B]
		push edx
		mov eax, dword ptr [ebp+0x14]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
		neg eax
		sbb eax, eax
		inc eax
		movzx edx, al
		test edx, edx
		jz n4
		mov eax, dword ptr [ebp+8]
		jmp done
	n4:
		mov eax, dword ptr [ebp+8]
		add eax, 1
		mov dword ptr [ebp+8], eax
		jmp dec_n
	remainder:
		mov ecx, dword ptr [ebp+0x0C]
		sub ecx, dword ptr [ebp+8]
		mov dword ptr [ebp-0x18], ecx
		cmp dword ptr [ebp-0x18], 1
		je rem1
		cmp dword ptr [ebp-0x18], 2
		je rem2
		cmp dword ptr [ebp-0x18], 3
		je rem3
		jmp ret_last
	rem3:
		mov edx, dword ptr [ebp+8]
		mov al, byte ptr [edx]
		mov byte ptr [ebp-0x0E], al
		mov cl, byte ptr [ebp-0x0E]
		mov byte ptr [ebp-0x0D], cl
		mov dl, byte ptr [ebp-0x0D]
		push edx
		mov eax, dword ptr [ebp+0x14]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
		neg eax
		sbb eax, eax
		inc eax
		movzx edx, al
		test edx, edx
		jz r3n
		mov eax, dword ptr [ebp+8]
		jmp done
	r3n:
		mov eax, dword ptr [ebp+8]
		add eax, 1
		mov dword ptr [ebp+8], eax
	rem2:
		mov ecx, dword ptr [ebp+8]
		mov dl, byte ptr [ecx]
		mov byte ptr [ebp-0x10], dl
		mov al, byte ptr [ebp-0x10]
		mov byte ptr [ebp-0x0F], al
		mov cl, byte ptr [ebp-0x0F]
		push ecx
		mov edx, dword ptr [ebp+0x14]
		push edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
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
		mov eax, dword ptr [ebp+8]
		mov cl, byte ptr [eax]
		mov byte ptr [ebp-0x12], cl
		mov dl, byte ptr [ebp-0x12]
		mov byte ptr [ebp-0x11], dl
		mov al, byte ptr [ebp-0x11]
		push eax
		mov ecx, dword ptr [ebp+0x14]
		push ecx
		mov edx, dword ptr [ebp+0x10]
		push edx
		call bfmePredV30
		add esp, 0x0C
		sub eax, dword ptr [ebp+0x14]
		neg eax
		sbb eax, eax
		inc eax
		movzx eax, al
		test eax, eax
		jz ret_last
		mov eax, dword ptr [ebp+8]
		jmp done
	ret_last:
		mov eax, dword ptr [ebp+0x0C]
	done:
	}
}
