// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x000CE910 is the 192-bit BitFlags::testForAll specialization.
// The six dword loads and the inverted-mask scan match BitFlags.h.
#include <bitset>

typedef bool Bool;

template <size_t NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	Bool testForAll( const BitFlags &that ) const;

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
Bool BitFlags<NUMBITS>::testForAll( const BitFlags &that ) const
{
	BitFlags tmp = *this;

	tmp.m_bits.flip();
	tmp.m_bits &= that.m_bits;

	return !tmp.m_bits.any();
}

// ?testForAll@?$BitFlags@$0MA@@@QBE_NABV1@@Z
template Bool BitFlags<192>::testForAll( const BitFlags<192>& ) const;
