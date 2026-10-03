// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <vector>

namespace _STL
{
template <> vector<AsciiString> &vector<AsciiString>::operator=(
	const vector<AsciiString> &);
}

struct BfmeElemVOW
{
	StringBase<char> m_bfme00;
	_STL::vector<AsciiString> m_bfme04;
};

BfmeElemVOW *bfmeCopyBackVOW(const BfmeElemVOW *first, const BfmeElemVOW *last, BfmeElemVOW *dest)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			--last;
			--dest;
			dest->m_bfme00.set(last->m_bfme00);
			dest->m_bfme04 = last->m_bfme04;
		} while (--i);
	}
	return dest;
}
