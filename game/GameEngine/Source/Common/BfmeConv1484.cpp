// cl: /Od

struct BfmeItVMV
{
	int m;
};

BfmeItVMV bfmeFwdVMV(BfmeItVMV a, BfmeItVMV b, char c);

int __stdcall bfmeRFindChV42(char ch, unsigned pos)
{
	char pad[80];

	__asm
	{
		mov dword ptr [ebp-0x48], ecx
		mov eax, dword ptr [ebp-0x48]
		mov ecx, dword ptr [ebp-0x48]
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
		mov dword ptr [ebp-0x14], eax
		mov ecx, dword ptr [ebp-0x48]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x28], edx
		mov eax, dword ptr [ebp+0x0C]
		cmp eax, dword ptr [ebp-0x14]
		jnb use_last
		lea ecx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x4C], ecx
		jmp got_idx
	use_last:
		lea edx, dword ptr [ebp-0x14]
		mov dword ptr [ebp-0x4C], edx
	got_idx:
		mov eax, dword ptr [ebp-0x4C]
		mov dword ptr [ebp-0x2C], eax
		mov ecx, dword ptr [ebp-0x2C]
		mov edx, dword ptr [ecx]
		mov eax, dword ptr [ebp-0x28]
		lea ecx, [eax+edx+1]
		mov dword ptr [ebp-0x0C], ecx
		mov edx, dword ptr [ebp-0x0C]
		mov dword ptr [ebp-0x10], edx
		mov al, byte ptr [ebp+8]
		mov byte ptr [ebp-0x15], al
		mov cl, byte ptr [ebp-0x15]
		push ecx
		push ecx
		mov dword ptr [ebp-0x34], esp
		mov edx, dword ptr [ebp-0x48]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x30], eax
		mov ecx, dword ptr [ebp-0x34]
		mov edx, dword ptr [ebp-0x30]
		mov dword ptr [ecx], edx
		push ecx
		mov dword ptr [ebp-0x38], esp
		mov eax, dword ptr [ebp-0x38]
		mov ecx, dword ptr [ebp-0x10]
		mov dword ptr [eax], ecx
		lea edx, dword ptr [ebp-8]
		push edx
		call bfmeFwdVMV
		add esp, 0x10
		mov eax, dword ptr [ebp-0x48]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x3C], ecx
		mov edx, dword ptr [ebp-0x3C]
		mov dword ptr [ebp-0x24], edx
		mov eax, dword ptr [ebp-8]
		mov dword ptr [ebp-0x40], eax
		mov ecx, dword ptr [ebp-0x40]
		sub ecx, dword ptr [ebp-0x24]
		neg ecx
		sbb ecx, ecx
		inc ecx
		movzx edx, cl
		neg edx
		sbb edx, edx
		inc edx
		movzx eax, dl
		test eax, eax
		jz notfound
		mov ecx, dword ptr [ebp-0x48]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x44], edx
		mov eax, dword ptr [ebp-8]
		sub eax, 1
		sub eax, dword ptr [ebp-0x44]
		mov dword ptr [ebp-0x50], eax
		jmp ret_idx
	notfound:
		mov dword ptr [ebp-0x50], 0xFFFFFFFF
	ret_idx:
		mov eax, dword ptr [ebp-0x50]
	done:
	}
}
