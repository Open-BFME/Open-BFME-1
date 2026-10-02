// cl: /Od
// stlport

#include <string>

typedef _STL::basic_string<char> StlString;
extern template int _STL::basic_string<char>::_M_compare(
	const char *, const char *, const char *, const char *);

class BfmeVecV35
{
public:
	char *b;
	char *e;
};

// The range-check helper retail reaches through the 0x000132CD thunk, whose
// body is the one-byte function at 0x006434C0; that body is the
// ?m@Gen_006434c0@@QAEXXZ gen-shim in game/gen_small/fun_004.cpp, so the call
// has to name that class, not a private stand-in.
struct Gen_006434c0 { void m(); };

void __stdcall bfmeCopyOverlapV35(int dstOff, int dstN, BfmeVecV35 *other, int srcOff, int srcN)
{
	char pad[44];

	__asm
	{
		mov dword ptr [ebp-0x24], ecx
		mov eax, dword ptr [ebp-0x24]
		mov ecx, dword ptr [ebp-0x24]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+8], edx
		ja grow
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+0x10]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x14], edx
		jbe skip_grow
	grow:
		mov ecx, dword ptr [ebp-0x24]
		call Gen_006434c0::m
	skip_grow:
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [ebp+0x10]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-4], edx
		mov eax, dword ptr [ebp-0x24]
		mov ecx, dword ptr [ebp-0x24]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+8]
		mov dword ptr [ebp-8], edx
		mov eax, dword ptr [ebp-4]
		cmp eax, dword ptr [ebp+0x18]
		jnb use_srcN
		lea ecx, dword ptr [ebp-4]
		mov dword ptr [ebp-0x28], ecx
		jmp got_n1
	use_srcN:
		lea edx, dword ptr [ebp+0x18]
		mov dword ptr [ebp-0x28], edx
	got_n1:
		mov eax, dword ptr [ebp-0x28]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp-8]
		cmp ecx, dword ptr [ebp+0x0C]
		jnb use_dstN
		lea edx, dword ptr [ebp-8]
		mov dword ptr [ebp-0x2C], edx
		jmp got_n2
	use_dstN:
		lea eax, dword ptr [ebp+0x0C]
		mov dword ptr [ebp-0x2C], eax
	got_n2:
		mov ecx, dword ptr [ebp-0x2C]
		mov dword ptr [ebp-0x10], ecx
		mov edx, dword ptr [ebp+0x10]
		mov eax, dword ptr [edx]
		add eax, dword ptr [ebp+0x14]
		mov ecx, dword ptr [ebp-0x0C]
		add eax, dword ptr [ecx]
		push eax
		mov edx, dword ptr [ebp+0x10]
		mov eax, dword ptr [edx]
		add eax, dword ptr [ebp+0x14]
		push eax
		mov ecx, dword ptr [ebp-0x24]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+8]
		mov eax, dword ptr [ebp-0x10]
		add edx, dword ptr [eax]
		push edx
		mov ecx, dword ptr [ebp-0x24]
		mov edx, dword ptr [ecx]
		add edx, dword ptr [ebp+8]
		push edx
		call StlString::_M_compare
		add esp, 0x10
	}
}
