// cl: /Od

class BfmeStrV57
{
public:
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeTermV57(char *tag)
{
	char pad[12];

	__asm
	{
		mov dword ptr [ebp-0xC], ecx
		mov eax, dword ptr [ebp-0xC]
		mov ecx, dword ptr [eax+0x4]
		mov dword ptr [ebp-0x8], ecx
		xor edx, edx
		mov byte ptr [ebp-0x1], dl
		mov eax, dword ptr [ebp-0x8]
		mov byte ptr [eax], 0
	}
}
