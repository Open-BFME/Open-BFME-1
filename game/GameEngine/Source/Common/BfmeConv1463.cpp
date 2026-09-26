// cl: /Od

class BfmeStrV23
{
public:
	BfmeStrV23 *bfmeInsertV23(unsigned pos, BfmeStrV23 *s);
	void bfmeGrowV23();
	void bfmeLenErrV23();
	void bfmeImplV23(char *a, char *b, char *c, char *d);

	char *b;
	char *e;
};

BfmeStrV23 *BfmeStrV23::bfmeInsertV23(unsigned pos, BfmeStrV23 *s)
{
	char pad[160];

	__asm
	{
		mov eax, this
		mov ecx, this
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr pos, edx
		jbe skip_grow
		mov ecx, this
		call bfmeGrowV23
	skip_grow:
		mov eax, this
		mov ecx, this
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		mov eax, dword ptr s
		mov ecx, dword ptr s
		mov eax, dword ptr [eax+4]
		sub eax, dword ptr [ecx]
		mov ecx, 0xFFFFFFFE
		sub ecx, eax
		cmp edx, ecx
		jbe skip_len
		mov ecx, this
		call bfmeLenErrV23
	skip_len:
		mov edx, this
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-4], eax
		mov ecx, dword ptr s
		mov edx, dword ptr [ecx+4]
		mov dword ptr [ebp-0x9C], edx
		mov eax, dword ptr s
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0xA0], ecx
		xor edx, edx
		mov byte ptr [ebp-5], dl
		lea eax, [ebp-6]
		push eax
		mov ecx, dword ptr [ebp-0x9C]
		push ecx
		mov edx, dword ptr [ebp-0xA0]
		push edx
		mov eax, dword ptr [ebp-4]
		add eax, dword ptr pos
		push eax
		mov ecx, this
		call bfmeImplV23
		mov eax, this
	}
}
