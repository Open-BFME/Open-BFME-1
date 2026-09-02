// cl: /Od

class BfmeStrV56
{
public:
	void bfmeThrowV56();
	void bfmeThrow2V56();
	void bfmeInsertV56(char *a, char *b, char *c, char *d, char *e);
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeReplaceV56(unsigned pos, unsigned n, char *other, unsigned opos, unsigned on)
{
	char pad[200];

	__asm
	{
		mov dword ptr [ebp-0xC0], ecx
		mov eax, dword ptr [ebp-0xC0]
		mov ecx, dword ptr [ebp-0xC0]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x8], edx
		ja L1
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+0x10]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x14], edx
		jbe L2
	L1:
		mov ecx, dword ptr [ebp-0xC0]
		call BfmeStrV56::bfmeThrowV56
	L2:
		mov eax, dword ptr [ebp-0xC0]
		mov ecx, dword ptr [ebp-0xC0]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0xC], edx
		mov eax, dword ptr [ebp-0xC]
		cmp eax, dword ptr [ebp+0xC]
		jae L3
		lea ecx, [ebp-0xC]
		mov dword ptr [ebp-0xC4], ecx
		jmp L4
	L3:
		lea edx, [ebp+0xC]
		mov dword ptr [ebp-0xC4], edx
	L4:
		mov eax, dword ptr [ebp-0xC4]
		mov dword ptr [ebp-0x14], eax
		mov ecx, dword ptr [ebp-0x14]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x8], edx
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+0x10]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0x10], edx
		mov eax, dword ptr [ebp-0x10]
		cmp eax, dword ptr [ebp+0x18]
		jae L5
		lea ecx, [ebp-0x10]
		mov dword ptr [ebp-0xC8], ecx
		jmp L6
	L5:
		lea edx, [ebp+0x18]
		mov dword ptr [ebp-0xC8], edx
	L6:
		mov eax, dword ptr [ebp-0xC8]
		mov dword ptr [ebp-0x18], eax
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x4], edx
		mov eax, dword ptr [ebp-0xC0]
		mov ecx, dword ptr [ebp-0xC0]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp-0x8]
		mov eax, 0xFFFFFFFE
		sub eax, dword ptr [ebp-0x4]
		cmp edx, eax
		jb L7
		mov ecx, dword ptr [ebp-0xC0]
		call BfmeStrV56::bfmeThrow2V56
	L7:
		mov ecx, dword ptr [ebp-0xC0]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x1C], edx
		mov eax, dword ptr [ebp-0xC0]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x20], ecx
		mov edx, dword ptr [ebp+0x10]
		mov eax, dword ptr [edx]
		add eax, dword ptr [ebp+0x14]
		add eax, dword ptr [ebp-0x4]
		mov dword ptr [ebp-0xB8], eax
		mov ecx, dword ptr [ebp+0x10]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0xBC], edx
		xor eax, eax
		mov byte ptr [ebp-0x21], al
		lea ecx, [ebp-0x22]
		push ecx
		mov edx, dword ptr [ebp-0xB8]
		push edx
		mov eax, dword ptr [ebp-0xBC]
		push eax
		mov ecx, dword ptr [ebp-0x1C]
		add ecx, dword ptr [ebp+0x8]
		add ecx, dword ptr [ebp-0x8]
		push ecx
		mov edx, dword ptr [ebp-0x20]
		add edx, dword ptr [ebp+0x8]
		push edx
		mov ecx, dword ptr [ebp-0xC0]
		call BfmeStrV56::bfmeInsertV56
	done:
	}
}
