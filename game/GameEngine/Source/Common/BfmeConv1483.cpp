// cl: /Od

struct BfmeRIterVMG
{
	const char *m;
};

BfmeRIterVMG bfmeFindFirstOfVMG(BfmeRIterVMG first1, BfmeRIterVMG last1, const char *first2, const char *last2);

int __stdcall bfmeRFindV41(char *s, unsigned pos, unsigned n)
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
		mov dl, byte ptr [ebp-0x11]
		push edx
		mov eax, dword ptr [ebp+8]
		add eax, dword ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp+8]
		push ecx
		push ecx
		mov dword ptr [ebp-0x30], esp
		mov edx, dword ptr [ebp-0x44]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x2C], eax
		mov ecx, dword ptr [ebp-0x30]
		mov edx, dword ptr [ebp-0x2C]
		mov dword ptr [ecx], edx
		push ecx
		mov dword ptr [ebp-0x34], esp
		mov eax, dword ptr [ebp-0x34]
		mov ecx, dword ptr [ebp-0x0C]
		mov dword ptr [eax], ecx
		lea edx, dword ptr [ebp-8]
		push edx
		call bfmeFindFirstOfVMG
		add esp, 0x18
		mov eax, dword ptr [ebp-0x44]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x38], ecx
		mov edx, dword ptr [ebp-0x38]
		mov dword ptr [ebp-0x20], edx
		mov eax, dword ptr [ebp-8]
		mov dword ptr [ebp-0x3C], eax
		mov ecx, dword ptr [ebp-0x3C]
		sub ecx, dword ptr [ebp-0x20]
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
		mov ecx, dword ptr [ebp-0x44]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x40], edx
		mov eax, dword ptr [ebp-8]
		sub eax, 1
		sub eax, dword ptr [ebp-0x40]
		mov dword ptr [ebp-0x4C], eax
		jmp ret_idx
	notfound:
		mov dword ptr [ebp-0x4C], 0xFFFFFFFF
	ret_idx:
		mov eax, dword ptr [ebp-0x4C]
	done:
	}
}
