// cl: /Od

class BfmeStrV23
{
public:
	BfmeStrV23 *bfmeInsertV23(unsigned pos, BfmeStrV23 *s);

	char *b;
	char *e;
};

// Retail's length-error call at 0x00830FC8 targets the 5-byte ILT thunk at
// 0x00042DC0, whose ledger row is ?j_00042dc0@@YAXXZ (game/gen_small/
// thunks_032.cpp), not a BfmeStrV23 member.  The receiver still goes into ecx
// because the thunk's target body is the thiscall length-error raise.
extern void j_00042dc0();

// Retail's range-insert call at 0x00830FA8 targets 0x008300B0, defined in
// game/GameEngine/Source/Common/BfmeConv1493.cpp as
// ?bfmeInsertRangeV50@@YGXPAD000@Z -- a free __stdcall function, not a member.
extern void __stdcall bfmeInsertRangeV50(char *pos, char *first, char *last, char *tag);

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

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
		call Gen_006434c0::m
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
		call j_00042dc0
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
		call bfmeInsertRangeV50
		mov eax, this
	}
}
