// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 num_get<char, istreambuf_iterator<char>>::do_get(long double&)
// at 0x00838560 (270B).  The generated row is identified by the vendor
// long-double overload, its exact narrow-reader call at 0x00838670, the
// existing bfmeGo1128C converter at 0x00847CD0, and the inline narrow iterator
// equality cleanup.  The adjacent named narrow double and float
// specializations at 0x00838AE0 and 0x00838BE0 establish the same num_get
// family and char iterator ABI.  VC7 uses the eight-byte double representation
// for long double, and the existing converter's proven decorated ABI takes
// double *; the cast below preserves that retail call ABI without adding a
// helper claim.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_locale.h>

struct BfmeS1128
{
	const char *m_bfme00;
};

void bfmeGo1128C(BfmeS1128 *, double *);

_STLP_BEGIN_NAMESPACE

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	istreambuf_iterator(basic_streambuf<CharT, Traits> * = 0);
	void _M_getc() const;

	bool equal(const istreambuf_iterator &other) const
	{
		if (m_buf)
			_M_getc();
		if (other.m_buf)
			other._M_getc();
		return m_eof == other.m_eof;
	}

	basic_streambuf<CharT, Traits> *m_buf;
	mutable CharT m_c;
	mutable unsigned char m_eof;
	mutable unsigned char m_have_c;
};

template <class InputIter, class CharT>
bool _STLP_CALL _M_read_float(string &, InputIter &, InputIter &,
	ios_base &, CharT *);

template <class CharT, class InputIter>
class num_get : public locale::facet
{
protected:
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, long double &value) const
	{
		string buffer;
		bool ok = _M_read_float(buffer, in, end, str, (CharT *)0);
		bfmeGo1128C((BfmeS1128 *)&buffer, (double *)&value);
		err = (ios_base::iostate)(ok ? ios_base::goodbit : ios_base::failbit);
		if (in.equal(end))
			err |= ios_base::eofbit;
		return in;
	}
};

typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;
template class num_get<char, NarrowIterator>;

_STLP_END_NAMESPACE
