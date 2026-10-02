// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

namespace _STL
{
template <class T> class char_traits;
template <class T> class allocator;

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	void reserve(unsigned int size);
};
}

static const unsigned &bfmeMaxVLT(const unsigned &a, const unsigned &b)
{
	return a < b ? b : a;
}

class BfmeStrVLT
{
public:
	BfmeStrVLT *bfmeAppendVLT(unsigned n, char c);
	char *m_bfme00;
	char *m_bfme04;
	char *m_bfme08;
};

BfmeStrVLT *BfmeStrVLT::bfmeAppendVLT(unsigned n, char c)
{
	if ((unsigned)(m_bfme04 - m_bfme00) + n > (unsigned)(m_bfme08 - m_bfme00) - 1)
		((_STL::basic_string<char, _STL::char_traits<char>,
			_STL::allocator<char> > *)this)->reserve((unsigned)(m_bfme04 - m_bfme00)
			+ bfmeMaxVLT((unsigned)(m_bfme04 - m_bfme00), n));
	if (n > 0)
	{
		memset(m_bfme04 + 1, (unsigned char)c, n - 1);
		m_bfme04[n] = 0;
		m_bfme04[0] = c;
		m_bfme04 += n;
	}
	return this;
}
