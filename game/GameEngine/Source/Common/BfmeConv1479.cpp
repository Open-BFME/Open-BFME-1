// cl: /Od

// The fill-or-insert helper at 0x00830030 is matched and owned by
// ?bfmeAssignV14@BfmeStrV14@@QAEPAV1@PAD0ID@Z in BfmeConv1453.cpp, so the
// receiver type has to carry that class name, not a private stand-in.
class BfmeStrV14
{
public:
	BfmeStrV14 *bfmeAssignV14(char *a, char *b, unsigned n, char ch);

	char *b;
	char *e;
};

// Retail reaches the length-error helper through the five-byte ILT thunk at
// 0x00042DC0, which the ledger owns as ?j_00042dc0@@YAXXZ
// (game/gen_small/thunks_032.cpp).  Several ?bfmeLenErrVxx pins name that same
// folded thunk; the definition is the only spelling that resolves, so the call
// has to name it.
extern void j_00042dc0();

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

void __stdcall bfmeInsertChV38(int pos, int n, unsigned count, char ch)
{
	char pad[28];

	__asm
	{
		mov dword ptr [ebp-0x18], ecx
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+8], edx
		jbe skip_throw
		mov ecx, dword ptr [ebp-0x18]
		call Gen_006434c0::m
	skip_throw:
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+8]
		mov dword ptr [ebp-8], edx
		mov eax, dword ptr [ebp-8]
		cmp eax, dword ptr [ebp+0x0C]
		jnb use_n
		lea ecx, dword ptr [ebp-8]
		mov dword ptr [ebp-0x1C], ecx
		jmp got_n
	use_n:
		lea edx, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x1C], edx
	got_n:
		mov eax, dword ptr [ebp-0x1C]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp-0x0C]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-4], edx
		cmp dword ptr [ebp+0x10], -2
		ja len_err
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp-4]
		mov eax, 0xFFFFFFFE
		sub eax, dword ptr [ebp+0x10]
		cmp edx, eax
		jb do_ins
	len_err:
		mov ecx, dword ptr [ebp-0x18]
		call j_00042dc0
	do_ins:
		mov ecx, dword ptr [ebp-0x18]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x10], edx
		mov eax, dword ptr [ebp-0x18]
		mov ecx, dword ptr [eax]
		mov dword ptr [ebp-0x14], ecx
		mov dl, byte ptr [ebp+0x14]
		push edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		mov ecx, dword ptr [ebp-0x10]
		add ecx, dword ptr [ebp+8]
		add ecx, dword ptr [ebp-4]
		push ecx
		mov edx, dword ptr [ebp-0x14]
		add edx, dword ptr [ebp+8]
		push edx
		mov ecx, dword ptr [ebp-0x18]
		call BfmeStrV14::bfmeAssignV14
	}
}
