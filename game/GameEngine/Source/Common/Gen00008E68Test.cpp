// 0x001DD7B0 is the second predicate used by the matched Y1 range-dispatch
// overloads at 0x003D08F0 and 0x003D09A0.  The 0x3FFFFF top-word mask and the
// three-word object/argument layout identify Zero Hour's canonical
// BitFlags<86>::testSetAndClear implementation: the first argument supplies
// required bits and the second supplies forbidden bits.  The Y1 callers still
// use an address-derived view because the surrounding BFME owner has no public
// identity recovered; this TU restores the known BitFlags ABI without claiming
// a subsystem-specific name.

// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

template <size_t NUMBITS>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet,
		const BitFlags &mustBeClear) const;

private:
	_STL::bitset<NUMBITS> m_bits;
};

// ?testSetAndClear@?$BitFlags@$0FG@@@QBE_NABV1@0@Z
template <size_t NUMBITS>
bool BitFlags<NUMBITS>::testSetAndClear(const BitFlags &mustBeSet,
	const BitFlags &mustBeClear) const
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

template bool BitFlags<86>::testSetAndClear(const BitFlags<86> &,
	const BitFlags<86> &) const;
