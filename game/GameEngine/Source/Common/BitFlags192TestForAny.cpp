// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x001FBFF0 is the 192-bit BitFlags::testForAny specialization.
// UpgradeMux callers pass two six-dword upgrade masks to this body.
#include <bitset>

typedef bool Bool;

template <size_t NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	Bool testForAny( const BitFlags &that ) const;

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
Bool BitFlags<NUMBITS>::testForAny( const BitFlags &that ) const
{
	BitFlags tmp = *this;
	tmp.m_bits &= that.m_bits;
	return tmp.m_bits.any();
}

// ?testForAny@?$BitFlags@$0MA@@@QBE_NABV1@@Z
template Bool BitFlags<192>::testForAny( const BitFlags<192>& ) const;
