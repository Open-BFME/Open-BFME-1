// ?bfmeDoPE@BfmeThingPE@@QAEIPBDII@Z
// partial score=0.98 date=2026-09-04
// ?bfmeDoPE@BfmeThingPE@@QAEXPADPAXH@Z
// partial score=0.98 date=2026-08-31
// stlport
// cl: /O2
// The worker is the BFME-shaped basic_string<char>::find body: its two
// pointers are the string range, while the caller supplies the pattern, start
// offset, and pattern length. STLport's already matched search instantiation
// supplies the comparison loop below.

#include <algorithm>
#include <string>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeRangePE
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPE
{
public:
	void bfmeGoPE(const BfmeRangePE *span, void *what);

	unsigned int bfmeDoPE(const char *at, unsigned int what, unsigned int many);

	const char *m_bfmeAt;          // 0x0
	const char *m_bfmeEnd;         // 0x4

	unsigned int size(void) const { return m_bfmeEnd - m_bfmeAt; }
};

#pragma optimize("", off)
void BfmeThingPE::bfmeGoPE(const BfmeRangePE *span, void *what)
{
	bfmeDoPE(span->m_bfmeAt, (unsigned int)what,
		span->m_bfmeEnd - span->m_bfmeAt);
}

#pragma optimize("gty", on)
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
		return result != last ? result - first : npos;
	}
}
#pragma optimize("", off)
