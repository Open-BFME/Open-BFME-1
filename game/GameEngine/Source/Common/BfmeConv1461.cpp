// cl: /Od

class BfmeStrV21
{
public:
	BfmeStrV21 *bfmeInsertV21(unsigned pos, char *s, unsigned n);
	void bfmeLenErrV21();
	void bfmeImplV21(char *a, char *b, char *c, char *d);

	char *b;
	char *e;
};

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

BfmeStrV21 *BfmeStrV21::bfmeInsertV21(unsigned pos, char *s, unsigned n)
{
	char pad[128];

	__asm
	{
		mov eax, this
		mov ecx, this
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr pos, edx
		jbe skip_grow
		mov ecx, this
		call Gen_006434c0::m
	skip_grow:
		mov eax, this
		mov ecx, this
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		mov eax, 0xFFFFFFFE
		sub eax, dword ptr n
		cmp edx, eax
		jbe skip_len
		mov ecx, this
		call bfmeLenErrV21
	skip_len:
		mov ecx, this
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-4], edx
		xor eax, eax
		mov byte ptr [ebp-5], al
		lea ecx, [ebp-6]
		push ecx
		mov edx, dword ptr s
		add edx, dword ptr n
		push edx
		mov eax, dword ptr s
		push eax
		mov ecx, dword ptr [ebp-4]
		add ecx, dword ptr pos
		push ecx
		mov ecx, this
		call bfmeImplV21
		mov eax, this
	}
}
