// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <size_t NUMBITS>
class BitFlags
{
public:
	Bool testSetAndClear(const BitFlags& mustBeSet, const BitFlags& mustBeClear) const;

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
Bool BitFlags<NUMBITS>::testSetAndClear(const BitFlags& mustBeSet, const BitFlags& mustBeClear) const
{
	BitFlags tmp = *this;
	tmp.m_bits &= mustBeClear.m_bits;
	if (tmp.m_bits.any())
		return false;

	tmp = *this;
	tmp.m_bits.flip();
	tmp.m_bits &= mustBeSet.m_bits;
	if (tmp.m_bits.any())
		return false;

	return true;
}

template Bool BitFlags<192>::testSetAndClear(const BitFlags<192>&, const BitFlags<192>&) const;
