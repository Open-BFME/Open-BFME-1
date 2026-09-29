// Retail 0x00C4FB46 is an anonymous MSVC 7.1 cleanup body
// (Ghidra Unwind@0104FB46).  No parent identity survives the retail image.
//
// The body clears bit 1 of the dword at 0x01305A78.  The adjacent anonymous
// body at 0x00C4FB38 clears bit 0, while the retail setter at 0x00B73AD5 and
// its sibling at 0x00B73BED set those two bits.  Keep the proven global
// address and leave the compiler-generated cleanup boundary anonymous.

class AnonymousGlobalFlagCleanup_00C4FB46
{
public:
	void clear();
};

// Retail global 0x01305A78 (targets/game/reverse/dir32_addresses.csv records
// ?g_Va01305A78@@3IA).
extern unsigned int g_Va01305A78;

// ?clear@AnonymousGlobalFlagCleanup_00C4FB46@@QAEXXZ
void AnonymousGlobalFlagCleanup_00C4FB46::clear()
{
	// The mask result is dead here, so a plain read-modify-write folds into
	// memory; the volatile access keeps retail's load/mask/store.
	*reinterpret_cast<volatile unsigned int *>(&g_Va01305A78) &= 0xFFFFFFFDu;
}
