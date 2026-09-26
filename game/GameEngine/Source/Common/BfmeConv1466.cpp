// cl: /Od

void *bfmeImplV26(int a, int b, int c, int d, char ch);

void *bfmeFwdV26(int a, int b, int c, int d, int e, int f, char ch)
{
	char pad[60];

	__asm
	{
		mov eax, dword ptr [ebp+8]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-8], ecx
		mov dl, byte ptr [ebp+0x20]
		push edx
		push ecx
		mov dword ptr [ebp-0x24], esp
		mov eax, dword ptr [ebp-0x24]
		mov ecx, dword ptr [ebp-8]
		mov dword ptr [eax], ecx
		mov edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x28], edx
		push ecx
		mov dword ptr [ebp-0x2C], esp
		mov eax, dword ptr [ebp-0x2C]
		mov ecx, dword ptr [ebp-0x28]
		mov dword ptr [eax], ecx
		push ecx
		mov dword ptr [ebp-0x30], esp
		mov edx, dword ptr [ebp-0x30]
		mov eax, dword ptr [ebp-0x0C]
		mov dword ptr [edx], eax
		push ecx
		mov dword ptr [ebp-0x34], esp
		mov ecx, dword ptr [ebp-0x34]
		mov edx, dword ptr [ebp+0xC]
		mov dword ptr [ecx], edx
		lea eax, [ebp-4]
		push eax
		call bfmeImplV26
		add esp, 0x18
		mov ecx, dword ptr [ebp-4]
		mov dword ptr [ebp-0x38], ecx
		mov edx, dword ptr [ebp-0x38]
		sub edx, dword ptr [ebp-0x0C]
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz other
		mov eax, dword ptr [ebp+0xC]
		jmp done
	other:
		mov ecx, dword ptr [ebp-4]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp+0x14]
		sub edx, dword ptr [ebp+0x10]
		neg edx
		add edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x10], edx
		mov eax, dword ptr [ebp-0x10]
	done:
	}
}
