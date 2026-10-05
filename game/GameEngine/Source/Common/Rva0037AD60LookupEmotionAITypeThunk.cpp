// The cdecl ILT bridge at RVA 0x000070A9 serves parseEmotionAIType.
// Its target reads six AI-state names at RVA 0x0037AA30.

template<int NUM_BITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

int __cdecl Rva0037AD60LookupEmotionAIType(const char *name)
{
	return BitFlags<6>::getSingleBitFromName(name);
}
