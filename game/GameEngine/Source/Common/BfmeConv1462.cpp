// cl: /Od

int bfmeMakeOX(void *p);

class BfmeStrV22
{
public:
	BfmeStrV22 *bfmeInsertV22(unsigned pos, char *s);
	void bfmeLenErrV22();
	void bfmeImplV22(char *a, char *b, char *c, char *d);

	char *b;
	char *e;
};

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

BfmeStrV22 *BfmeStrV22::bfmeInsertV22(unsigned pos, char *s)
{
	void *at;
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
		mov eax, dword ptr s
		push eax
		call bfmeMakeOX
		add esp, 4
		mov dword ptr [ebp-4], eax
		mov ecx, this
		mov edx, this
		mov eax, dword ptr [ecx+4]
		sub eax, dword ptr [edx]
		mov ecx, 0xFFFFFFFE
		sub ecx, dword ptr [ebp-4]
		cmp eax, ecx
		jbe skip_len
		mov ecx, this
		call bfmeLenErrV22
	skip_len:
		mov edx, this
		mov eax, dword ptr [edx]
		add eax, dword ptr pos
		mov dword ptr at, eax
		xor ecx, ecx
		mov byte ptr [ebp-5], cl
		lea edx, [ebp-6]
		push edx
		mov eax, dword ptr s
		add eax, dword ptr [ebp-4]
		push eax
		mov ecx, dword ptr s
		push ecx
		mov edx, dword ptr at
		push edx
		mov ecx, this
		call bfmeImplV22
		mov eax, this
	}
}
