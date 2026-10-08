struct Rva0022A1E0ConstantGetter
{
	void *get();
};

// The weapon-set flag names at VA 0x012AD6B0 are BitFlags<29>::s_bitNameList,
// defined in DamageFX.cpp.
template <int NUMBITS>
class BitFlags
{
	friend struct Rva0022A1E0ConstantGetter;
	static const char *s_bitNameList[];
};

void *Rva0022A1E0ConstantGetter::get()
{
	return (void *)BitFlags<29>::s_bitNameList;
}
