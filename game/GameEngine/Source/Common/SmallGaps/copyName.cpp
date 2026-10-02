// ?copyName@@YGXPAURva00808C20Entry@@PBU1@@Z

// Retail's call lands on the 0x009F70BA import thunk, which the ledger defines
// as ?ji_009f70ba@@YAXXZ (game/gen_small/imports_000.cpp).  That stub is
// declared with no arguments because it is one, yet its caller supplies
// strncpy's three dwords on the stack, so the call is made through a typed
// function pointer exactly as game/GameEngine/Source/GameNetwork/
// Y4FeslFavGameAddress.cpp does.  Only the referenced symbol name changed; the
// three pushes and their order are unchanged.
void __cdecl ji_009f70ba();
typedef char *(__cdecl *Rva009F70BACopy)(char *dest, const char *src, unsigned count);

struct Rva00808C20Entry {
	char m_pad[0x10];
	char* m_name;
	unsigned int m_capacity;
	int m_18;
	int m_1c;
	unsigned int m_20;
};
void __stdcall copyName(Rva00808C20Entry* dst, const Rva00808C20Entry* src)
{
	dst->m_1c = src->m_1c;
	dst->m_20 = 0xc0000000;
	reinterpret_cast<Rva009F70BACopy>(&ji_009f70ba)(dst->m_name, src->m_name, dst->m_capacity);
}
