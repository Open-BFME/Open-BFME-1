// cl: /Od

char **bfmeRSearchV33(char **out, char *last1, char *first1, char *last2, char *first2)
{
	void *at;
	char pad[88];

	__asm
	{
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x14], eax
		mov ecx, dword ptr [ebp-0x14]
		sub ecx, dword ptr [ebp+0x10]
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jnz L1
		mov eax, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp-0x18]
		sub ecx, dword ptr [ebp+0x18]
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jz L2
	L1:
		mov eax, dword ptr [ebp+0x8]
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [eax], ecx
		mov eax, dword ptr [ebp+0x8]
		jmp done
	L2:
		mov edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0xC], edx
		mov eax, dword ptr [ebp-0xC]
		sub eax, 1
		mov dword ptr [ebp-0xC], eax
		mov ecx, dword ptr [ebp-0xC]
		mov dword ptr [ebp-0x1C], ecx
		mov edx, dword ptr [ebp-0x1C]
		sub edx, dword ptr [ebp+0x18]
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz L5
	L3:
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x20], ecx
		mov edx, dword ptr [ebp-0x20]
		sub edx, dword ptr [ebp+0x10]
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz L4
		mov edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x24], edx
		mov eax, dword ptr [ebp-0x24]
		sub eax, 1
		mov dword ptr [ebp-0x24], eax
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x28], ecx
		mov edx, dword ptr [ebp-0x28]
		sub edx, 1
		mov dword ptr [ebp-0x28], edx
		mov eax, dword ptr [ebp-0x24]
		movsx ecx, byte ptr [eax]
		mov edx, dword ptr [ebp-0x28]
		movsx eax, byte ptr [edx]
		sub eax, ecx
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jnz L4
		mov edx, dword ptr [ebp+0xC]
		sub edx, 1
		mov dword ptr [ebp+0xC], edx
		jmp L3
	L4:
		mov eax, dword ptr [ebp+0x8]
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [eax], ecx
		mov eax, dword ptr [ebp+0x8]
		jmp done
	L5:
		mov edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x8], edx
		mov eax, dword ptr [ebp-0x8]
		sub eax, 1
		mov dword ptr [ebp-0x8], eax
	L6:
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x2C], ecx
		mov edx, dword ptr [ebp-0x2C]
		sub edx, dword ptr [ebp+0x10]
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz L16
	L7:
		mov edx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x30], edx
		mov eax, dword ptr [ebp-0x30]
		sub eax, dword ptr [ebp+0x10]
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jz L9
		mov eax, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x34], eax
		mov ecx, dword ptr [ebp-0x34]
		sub ecx, 1
		mov dword ptr [ebp-0x34], ecx
		mov edx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x38], edx
		mov eax, dword ptr [ebp-0x38]
		sub eax, 1
		mov dword ptr [ebp-0x38], eax
		mov ecx, dword ptr [ebp-0x34]
		movsx edx, byte ptr [ecx]
		mov eax, dword ptr [ebp-0x38]
		movsx ecx, byte ptr [eax]
		sub ecx, edx
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jz L8
		jmp L9
	L8:
		mov eax, dword ptr [ebp+0xC]
		sub eax, 1
		mov dword ptr [ebp+0xC], eax
		jmp L7
	L9:
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x3C], ecx
		mov edx, dword ptr [ebp-0x3C]
		sub edx, dword ptr [ebp+0x10]
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz L10
		mov edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x40], edx
		mov eax, dword ptr [ebp-0x40]
		sub eax, 1
		mov dword ptr [ebp-0x40], eax
		mov ecx, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x44], ecx
		mov edx, dword ptr [ebp-0x44]
		sub edx, 1
		mov dword ptr [ebp-0x44], edx
		mov eax, dword ptr [ebp-0x40]
		movsx ecx, byte ptr [eax]
		mov edx, dword ptr [ebp-0x44]
		movsx eax, byte ptr [edx]
		sub eax, ecx
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jnz L10
		mov edx, dword ptr [ebp+0xC]
		sub edx, 1
		mov dword ptr [ebp+0xC], edx
		jmp L9
	L10:
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x48], eax
		mov ecx, dword ptr [ebp-0x48]
		sub ecx, dword ptr [ebp+0x10]
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		test edx, edx
		jz L11
		mov eax, dword ptr [ebp+0x8]
		mov ecx, dword ptr [ebp+0x10]
		mov dword ptr [eax], ecx
		mov eax, dword ptr [ebp+0x8]
		jmp done
	L11:
		mov edx, dword ptr [ebp-0x8]
		mov dword ptr [ebp-0x4], edx
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0x10]
		sub ecx, 1
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x4C], edx
		mov eax, dword ptr [ebp-0x4C]
		sub eax, dword ptr [ebp+0x10]
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz L12
		mov edx, dword ptr [ebp+0x8]
		mov eax, dword ptr [ebp+0x10]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+0x8]
		jmp done
	L12:
		mov ecx, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0x50], ecx
		mov edx, dword ptr [ebp-0x50]
		sub edx, 1
		mov dword ptr [ebp-0x50], edx
		mov eax, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x54], eax
		mov ecx, dword ptr [ebp-0x54]
		sub ecx, 1
		mov dword ptr [ebp-0x54], ecx
		mov edx, dword ptr [ebp-0x50]
		movsx eax, byte ptr [edx]
		mov ecx, dword ptr [ebp-0x54]
		movsx edx, byte ptr [ecx]
		sub edx, eax
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz L15
		mov ecx, dword ptr [ebp-0x4]
		sub ecx, 1
		mov dword ptr [ebp-0x4], ecx
		mov edx, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0x58], edx
		mov eax, dword ptr [ebp-0x58]
		sub eax, dword ptr [ebp+0x18]
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz L13
		mov edx, dword ptr [ebp+0x8]
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+0x8]
		jmp done
	L13:
		mov ecx, dword ptr [ebp-0x10]
		sub ecx, 1
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x5C], edx
		mov eax, dword ptr [ebp-0x5C]
		sub eax, dword ptr [ebp+0x10]
		neg eax
		sbb eax, eax
		inc eax
		movzx ecx, al
		test ecx, ecx
		jz L14
		mov edx, dword ptr [ebp+0x8]
		mov eax, dword ptr [ebp+0x10]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+0x8]
		jmp done
	L14:
		jmp L12
	L15:
		mov ecx, dword ptr [ebp+0xC]
		sub ecx, 1
		mov dword ptr [ebp+0xC], ecx
		jmp L6
	L16:
		mov edx, dword ptr [ebp+0x8]
		mov eax, dword ptr [ebp+0xC]
		mov dword ptr [edx], eax
		mov eax, dword ptr [ebp+0x8]
	done:
	}
}
