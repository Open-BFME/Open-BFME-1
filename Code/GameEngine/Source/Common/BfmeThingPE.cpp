// stlport
// cl: /O2
// The worker behind the BfmeThingPE::bfmeDoPE call pinned by the
// BfmeTwoHundredSixtyFive.cpp wrapper: a basic_string<char>::find-shaped
// body whose two members are the string range, while the caller supplies
// the pattern, start offset, and pattern length. STLport's already matched
// search instantiation supplies the comparison loop.
//
// _WriteBarrier inside the search-miss arm keeps MSVC 7.1 from tail-merging
// the two identical npos epilogues retail carries; it emits no instruction.

#include <algorithm>
#include <string>

extern "C" void _ReadWriteBarrier(void);
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_WriteBarrier)

class BfmeThingPE
{
public:
	unsigned int bfmeDoPE(const char *at, unsigned int what, unsigned int many);

	const char *m_bfmeAt;          // 0x0
	const char *m_bfmeEnd;         // 0x4

	unsigned int size(void) const { return m_bfmeEnd - m_bfmeAt; }
};

unsigned int BfmeThingPE::bfmeDoPE(const char *at, unsigned int what, unsigned int many)
{
	const unsigned int npos = (unsigned int)-1;
	const char *first = m_bfmeAt;
	const char *last = m_bfmeEnd;

	if (what + many > size())
	{
		_ReadWriteBarrier();
		return npos;
	}
	else
	{
		const char *result = _STL::search(
				first + what, last, at, at + many,
				_STL::_Eq_traits<_STL::char_traits<char> >());
		if (result != last)
		{
			return result - first;
		}
		_WriteBarrier();
		return npos;
	}
}
