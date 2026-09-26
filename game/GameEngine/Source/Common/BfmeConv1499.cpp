// cl: /Od

unsigned bfmeStrlenV55(char *s);

class BfmeStrV55
{
public:
	void bfmeThrowV55();
	void bfmeThrow2V55();
	void bfmeInsertV55(char *a, char *b, char *c, char *d, char *e);
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeReplaceV55(unsigned pos, unsigned n, char *src)
{
	char pad[176];

	__asm
	{
		mov dword ptr [ebp-0xAC], ecx
		mov eax, dword ptr [ebp-0xAC]
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x8], edx
		jbe L1
		mov ecx, dword ptr [ebp-0xAC]
		call BfmeStrV55::bfmeThrowV55
	L1:
		mov eax, dword ptr [ebp-0xAC]
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0xC], edx
		mov eax, dword ptr [ebp-0xC]
		cmp eax, dword ptr [ebp+0xC]
		jae L2
		lea ecx, [ebp-0xC]
		mov dword ptr [ebp-0xB0], ecx
		jmp L3
	L2:
		lea edx, [ebp+0xC]
		mov dword ptr [ebp-0xB0], edx
	L3:
		mov eax, dword ptr [ebp-0xB0]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0x10]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x4], edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call bfmeStrlenV55
		add esp, 4
		mov dword ptr [ebp-0x8], eax
		cmp dword ptr [ebp-0x8], -0x2
		ja L4
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [ebp-0xAC]
		mov eax, dword ptr [ecx+0x4]
		sub eax, dword ptr [edx]
		sub eax, dword ptr [ebp-0x4]
		mov ecx, 0xFFFFFFFE
		sub ecx, dword ptr [ebp-0x8]
		cmp eax, ecx
		jb L5
	L4:
		mov ecx, dword ptr [ebp-0xAC]
		call BfmeStrV55::bfmeThrow2V55
	L5:
		mov edx, dword ptr [ebp-0xAC]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x14], eax
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x18], edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call bfmeStrlenV55
		add esp, 4
		add eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0xA8], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x19], cl
		lea edx, [ebp-0x1A]
		push edx
		mov eax, dword ptr [ebp-0xA8]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		mov edx, dword ptr [ebp-0x14]
		add edx, dword ptr [ebp+0x8]
		add edx, dword ptr [ebp-0x4]
		push edx
		mov eax, dword ptr [ebp-0x18]
		add eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0xAC]
		call BfmeStrV55::bfmeInsertV55
	done:
	}
}
