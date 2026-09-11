// Clean C++ owner for the Open-BFME7 incremental-link thunk at RVA 0x000070A9.
// The retail front is the cdecl bridge used by parseEmotionAIType; its target
// is the existing 38-bit BitFlags name lookup at 0x0037AA30.

template<int NUM_BITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

int __cdecl Rva0037AD60LookupEmotionAIType(const char *name)
{
	return BitFlags<38>::getSingleBitFromName(name);
}
