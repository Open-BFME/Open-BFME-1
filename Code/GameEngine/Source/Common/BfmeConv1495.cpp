// cl: /Od

unsigned bfmeStrlenV51(char *s);

class BfmeStrV51
{
public:
	void bfmeInsertV51(char *a, char *b, char *c, char *d, char *e);
	char *b;
	char *e;
	char *c;
};

void __stdcall bfmeWrapInsertV51(char *pos, char *first, char *last)
{
	void *at;
	char pad[140];

	__asm
	{
		mov dword ptr [ebp-0x94], ecx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call bfmeStrlenV51
		add esp, 4
		add eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0x90], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x1], cl
		lea edx, [ebp-0x2]
		push edx
		mov eax, dword ptr [ebp-0x90]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		mov edx, dword ptr [ebp+0xC]
		push edx
		mov eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0x94]
		call BfmeStrV51::bfmeInsertV51
	}
}
