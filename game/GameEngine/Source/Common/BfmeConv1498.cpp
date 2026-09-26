// cl: /Od

class BfmeStrV54
{
public:
	void bfmeThrowV54();
	void bfmeThrow2V54();
	void bfmeInsertV54(char *a, char *b, char *c, char *d, char *e);
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeReplaceV54(unsigned pos, unsigned n, char *other)
{
	char pad[184];

	__asm
	{
		mov dword ptr [ebp-0xB4], ecx
		mov eax, dword ptr [ebp-0xB4]
		mov ecx, dword ptr [ebp-0xB4]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x8], edx
		jbe L1
		mov ecx, dword ptr [ebp-0xB4]
		call BfmeStrV54::bfmeThrowV54
	L1:
		mov eax, dword ptr [ebp-0xB4]
		mov ecx, dword ptr [ebp-0xB4]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x8], edx
		mov eax, dword ptr [ebp-0x8]
		cmp eax, dword ptr [ebp+0xC]
		jae L2
		lea ecx, [ebp-0x8]
		mov dword ptr [ebp-0xB8], ecx
		jmp L3
	L2:
		lea edx, [ebp+0xC]
		mov dword ptr [ebp-0xB8], edx
	L3:
		mov eax, dword ptr [ebp-0xB8]
		mov dword ptr [ebp-0xC], eax
		mov ecx, dword ptr [ebp-0xC]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x4], edx
		mov eax, dword ptr [ebp-0xB4]
		mov ecx, dword ptr [ebp-0xB4]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp-0x4]
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+0x10]
		mov eax, dword ptr [eax+0x4]
		sub eax, dword ptr [ecx]
		mov ecx, 0xFFFFFFFE
		sub ecx, eax
		cmp edx, ecx
		jb L4
		mov ecx, dword ptr [ebp-0xB4]
		call BfmeStrV54::bfmeThrow2V54
	L4:
		mov edx, dword ptr [ebp-0xB4]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0xB4]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x14], edx
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [eax+0x4]
		mov dword ptr [ebp-0xAC], ecx
		mov edx, dword ptr [ebp+0x10]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0xB0], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x15], cl
		lea edx, [ebp-0x16]
		push edx
		mov eax, dword ptr [ebp-0xAC]
		push eax
		mov ecx, dword ptr [ebp-0xB0]
		push ecx
		mov edx, dword ptr [ebp-0x10]
		add edx, dword ptr [ebp+0x8]
		add edx, dword ptr [ebp-0x4]
		push edx
		mov eax, dword ptr [ebp-0x14]
		add eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0xB4]
		call BfmeStrV54::bfmeInsertV54
	done:
	}
}
