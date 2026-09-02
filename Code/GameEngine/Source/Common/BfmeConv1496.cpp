// cl: /Od

class BfmeStrV52
{
public:
	void bfmeInsertV52(char *a, char *b, char *c, char *d, char *e);
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeWrapInsertV52(char *pos, char *first, char *other)
{
	char pad[160];

	__asm
	{
		mov dword ptr [ebp-0xA0], ecx
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [eax+0x4]
		mov dword ptr [ebp-0x98], ecx
		mov edx, dword ptr [ebp+0x10]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x9C], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x1], cl
		lea edx, [ebp-0x2]
		push edx
		mov eax, dword ptr [ebp-0x98]
		push eax
		mov ecx, dword ptr [ebp-0x9C]
		push ecx
		mov edx, dword ptr [ebp+0xC]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0xA0]
		call BfmeStrV52::bfmeInsertV52
	}
}
