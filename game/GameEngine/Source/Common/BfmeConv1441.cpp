// cl: /Od

struct BfmeItVMU
{
	BfmeItVMU() {}
	int m;
};

BfmeItVMU bfmeImplVMU(BfmeItVMU a, BfmeItVMU b, char c, char *p);
BfmeItVMU bfmeFwdVMU(BfmeItVMU a, BfmeItVMU b, char c);

BfmeItVMU bfmeFwdVMU(BfmeItVMU a, BfmeItVMU b, char c)
{
	char n;
	char z0[55];

	__asm
	{
		lea eax, n
		push eax
		mov cl, byte ptr c
		push ecx
		push ecx
		mov dword ptr [ebp-0x10], esp
		mov edx, dword ptr [ebp-0x10]
		mov eax, dword ptr b
		mov dword ptr [edx], eax
		push ecx
		mov dword ptr [ebp-0x14], esp
		mov ecx, dword ptr [ebp-0x14]
		mov edx, dword ptr a
		mov dword ptr [ecx], edx
		mov eax, dword ptr [ebp+8]
		push eax
		call bfmeImplVMU
		add esp, 0x14
		mov eax, dword ptr [ebp+8]
	}
}
