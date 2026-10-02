// cl: /Od

class BfmeStrV53
{
public:
	void bfmeThrow2V53();
	void bfmeInsertV53(char *a, char *b, char *c, char *d, char *e);
	char *b;
	char *e;
	char *c;
};

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

void __stdcall bfmeReplaceV53(unsigned pos, unsigned n, char *src, unsigned slen)
{
	char pad[168];

	__asm
	{
		mov dword ptr [ebp-0xA4], ecx
		mov eax, dword ptr [ebp-0xA4]
		mov ecx, dword ptr [ebp-0xA4]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x8], edx
		jbe L1
		mov ecx, dword ptr [ebp-0xA4]
		call Gen_006434c0::m
	L1:
		mov eax, dword ptr [ebp-0xA4]
		mov ecx, dword ptr [ebp-0xA4]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0x8], edx
		mov eax, dword ptr [ebp-0x8]
		cmp eax, dword ptr [ebp+0xC]
		jae L2
		lea ecx, [ebp-0x8]
		mov dword ptr [ebp-0xA8], ecx
		jmp L3
	L2:
		lea edx, [ebp+0xC]
		mov dword ptr [ebp-0xA8], edx
	L3:
		mov eax, dword ptr [ebp-0xA8]
		mov dword ptr [ebp-0xC], eax
		mov ecx, dword ptr [ebp-0xC]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x4], edx
		cmp dword ptr [ebp+0x14], -0x2
		ja L4
		mov eax, dword ptr [ebp-0xA4]
		mov ecx, dword ptr [ebp-0xA4]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp-0x4]
		mov eax, 0xFFFFFFFE
		sub eax, dword ptr [ebp+0x14]
		cmp edx, eax
		jb L5
	L4:
		mov ecx, dword ptr [ebp-0xA4]
		call BfmeStrV53::bfmeThrow2V53
	L5:
		mov ecx, dword ptr [ebp-0xA4]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x10], edx
		mov eax, dword ptr [ebp-0xA4]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x14], ecx
		xor edx, edx
		mov byte ptr [ebp-0x15], dl
		lea eax, [ebp-0x16]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		add ecx, dword ptr [ebp+0x14]
		push ecx
		mov edx, dword ptr [ebp+0x10]
		push edx
		mov eax, dword ptr [ebp-0x10]
		add eax, dword ptr [ebp+0x8]
		add eax, dword ptr [ebp-0x4]
		push eax
		mov ecx, dword ptr [ebp-0x14]
		add ecx, dword ptr [ebp+0x8]
		push ecx
		mov ecx, dword ptr [ebp-0xA4]
		call BfmeStrV53::bfmeInsertV53
	done:
	}
}
