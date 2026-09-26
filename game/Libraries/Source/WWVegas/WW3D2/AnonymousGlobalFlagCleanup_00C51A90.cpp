// Retail 0x00C51A90 is an anonymous MSVC 7.1 cleanup body
// (Ghidra Unwind@01051A90).  No parent identity survives the retail image.
//
// The body clears bit 0 of the dword at 0x01306D4C.  The adjacent anonymous
// bodies at 0x00C51AA6 and 0x00C51ABC clear bits 1 and 2 of that same global.
// Keep the proven global address and leave the compiler-generated cleanup
// boundary anonymous.

class AnonymousGlobalFlagCleanup_00C51A90
{
public:
	void clear();
};

// ?clear@AnonymousGlobalFlagCleanup_00C51A90@@QAEXXZ absent-from-retail
void AnonymousGlobalFlagCleanup_00C51A90::clear()
{
	*reinterpret_cast<unsigned int *>(0x01306D4C) &= 0xFFFFFFFEu;
}
