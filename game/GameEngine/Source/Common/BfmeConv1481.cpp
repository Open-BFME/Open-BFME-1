// cl: /Od

struct BfmeItVMU
{
	int m;
};

BfmeItVMU bfmeFwdVMU(BfmeItVMU a, BfmeItVMU b, char c);

int __stdcall bfmeRFindChV40(char ch, unsigned pos)
{
	void *at;
	char pad[68];

	__asm
	{
		mov dword ptr [ebp-0x44], ecx
		mov eax, dword ptr [ebp-0x44]
		mov ecx, dword ptr [ebp-0x44]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		mov dword ptr [ebp-4], edx
		cmp dword ptr [ebp-4], 1
		jnb have_len
		or eax, -1
		jmp done
	have_len:
		mov eax, dword ptr [ebp-4]
		sub eax, 1
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0x44]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x24], edx
		mov eax, dword ptr [ebp+0x0C]
		cmp eax, dword ptr [ebp-0x10]
		jnb use_last
		lea ecx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x48], ecx
		jmp got_idx
	use_last:
		lea edx, dword ptr [ebp-0x10]
		mov dword ptr [ebp-0x48], edx
	got_idx:
		mov eax, dword ptr [ebp-0x48]
		mov dword ptr [ebp-0x28], eax
		mov ecx, dword ptr [ebp-0x28]
		mov edx, dword ptr [ecx]
		mov eax, dword ptr [ebp-0x24]
		lea ecx, [eax+edx+1]
		mov dword ptr [ebp-0x0C], ecx
		mov dl, byte ptr [ebp+8]
		mov byte ptr [ebp-0x11], dl
		mov al, byte ptr [ebp-0x11]
		push eax
		push ecx
		mov dword ptr [ebp-0x30], esp
		mov ecx, dword ptr [ebp-0x44]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x2C], edx
		mov eax, dword ptr [ebp-0x30]
		mov ecx, dword ptr [ebp-0x2C]
		mov dword ptr [eax], ecx
		push ecx
		mov dword ptr [ebp-0x34], esp
		mov edx, dword ptr [ebp-0x34]
		mov eax, dword ptr [ebp-0x0C]
		mov dword ptr [edx], eax
		lea ecx, dword ptr [ebp-8]
		push ecx
		call bfmeFwdVMU
		add esp, 0x10
		mov edx, dword ptr [ebp-0x44]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x38], eax
		mov ecx, dword ptr [ebp-0x38]
		mov dword ptr [ebp-0x20], ecx
		mov edx, dword ptr [ebp-8]
		mov dword ptr [ebp-0x3C], edx
		mov eax, dword ptr [ebp-0x3C]
		sub eax, dword ptr [ebp-0x20]
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
		mov eax, dword ptr [ebp-0x44]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x40], ecx
		mov edx, dword ptr [ebp-8]
		sub edx, 1
		sub edx, dword ptr [ebp-0x40]
		mov dword ptr [ebp-0x4C], edx
		jmp ret_idx
	notfound:
		mov dword ptr [ebp-0x4C], 0xFFFFFFFF
	ret_idx:
		mov eax, dword ptr [ebp-0x4C]
	done:
	}
}
