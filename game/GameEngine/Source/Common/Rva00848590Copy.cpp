// cl: /DNDEBUG /MD /EHsc
// Two identical 28-byte plain copies at 0x00848590 and 0x008485B0.
// IDENTITY IS NOT RECOVERED: no caller, string or vtable names the holder,
// so every name is derived from its own address.
//
// WHAT THE BYTES SHOW. Each body reads three stack dwords -- destination at
// [esp+4], source at [esp+8], flag byte pointer at [esp+0xC] -- and copies two
// dwords plus one byte with no call, no branch and no callee:
//
//     mov ecx,[esp+8] / mov edx,[ecx] / mov eax,[esp+4] / mov [eax],edx /
//     mov ecx,[ecx+4] / mov edx,[esp+0xC] / mov [eax+4],ecx /
//     mov cl,[edx] / mov [eax+8],cl / ret
//
// That is a `__cdecl` void copy of a 9-byte value (two words and a flag byte)
// into the caller's destination, not a struct return: a hidden return pointer
// would put the destination first too, but the matching struct-return
// spelling emits a frame and temporaries instead of these nine instructions.
//
// SEPARATE FUNCTIONS, NOT ALIASES. Two distinct addresses that coincide in
// bytes only because a 9-byte copy has nothing else to say.

struct Rva00848590Value
{
	int m_first;
	int m_second;
	unsigned char m_flag;
};

// ?dup_00848590@@YAXPAURva00848590Value@@PBU1@PBE@Z
void dup_00848590(Rva00848590Value *out, const Rva00848590Value *src, const unsigned char *flag)
{
	out->m_first = src->m_first;
	out->m_second = src->m_second;
	out->m_flag = *flag;
}

struct Rva008485B0Value
{
	int m_first;
	int m_second;
	unsigned char m_flag;
};

// ?dup_008485b0@@YAXPAURva008485B0Value@@PBU1@PBE@Z
void dup_008485b0(Rva008485B0Value *out, const Rva008485B0Value *src, const unsigned char *flag)
{
	out->m_first = src->m_first;
	out->m_second = src->m_second;
	out->m_flag = *flag;
}
