// cl: /Od

// Callees named as their matched rows (tools/callees.py 0x831CE0 277):
// ILT 0x6B9A -> 0x000A30D0 stringLength, ILT 0x42DC0 -> 0x000A34E0
// Gen_000a34e0::m (length error), and 0x008314E0
// Rva008314E0String::replaceRange.
int stringLength(const char *s);

struct Gen_000a34e0 { void m(); };

struct BfmeRangeTag;

class Rva008314E0String
{
public:
	Rva008314E0String &replaceRange(char *first, char *last, char *srcFirst,
		char *srcLast, const BfmeRangeTag &tag);
};

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

void __stdcall bfmeReplaceV55(unsigned pos, unsigned n, char *src)
{
	char pad[176];

	__asm
	{
		mov dword ptr [ebp-0xAC], ecx
		mov eax, dword ptr [ebp-0xAC]
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x8], edx
		jbe L1
		mov ecx, dword ptr [ebp-0xAC]
		call Gen_006434c0::m
	L1:
		mov eax, dword ptr [ebp-0xAC]
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [eax+0x4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x8]
		mov dword ptr [ebp-0xC], edx
		mov eax, dword ptr [ebp-0xC]
		cmp eax, dword ptr [ebp+0xC]
		jae L2
		lea ecx, [ebp-0xC]
		mov dword ptr [ebp-0xB0], ecx
		jmp L3
	L2:
		lea edx, [ebp+0xC]
		mov dword ptr [ebp-0xB0], edx
	L3:
		mov eax, dword ptr [ebp-0xB0]
		mov dword ptr [ebp-0x10], eax
		mov ecx, dword ptr [ebp-0x10]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x4], edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call stringLength
		add esp, 4
		mov dword ptr [ebp-0x8], eax
		cmp dword ptr [ebp-0x8], -0x2
		ja L4
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [ebp-0xAC]
		mov eax, dword ptr [ecx+0x4]
		sub eax, dword ptr [edx]
		sub eax, dword ptr [ebp-0x4]
		mov ecx, 0xFFFFFFFE
		sub ecx, dword ptr [ebp-0x8]
		cmp eax, ecx
		jb L5
	L4:
		mov ecx, dword ptr [ebp-0xAC]
		call Gen_000a34e0::m
	L5:
		mov edx, dword ptr [ebp-0xAC]
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x14], eax
		mov ecx, dword ptr [ebp-0xAC]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x18], edx
		mov eax, dword ptr [ebp+0x10]
		push eax
		call stringLength
		add esp, 4
		add eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0xA8], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x19], cl
		lea edx, [ebp-0x1A]
		push edx
		mov eax, dword ptr [ebp-0xA8]
		push eax
		mov ecx, dword ptr [ebp+0x10]
		push ecx
		mov edx, dword ptr [ebp-0x14]
		add edx, dword ptr [ebp+0x8]
		add edx, dword ptr [ebp-0x4]
		push edx
		mov eax, dword ptr [ebp-0x18]
		add eax, dword ptr [ebp+0x8]
		push eax
		mov ecx, dword ptr [ebp-0xAC]
		call Rva008314E0String::replaceRange
	done:
	}
}
