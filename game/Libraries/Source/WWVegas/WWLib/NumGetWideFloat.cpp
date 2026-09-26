// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 num_get<wchar_t, istreambuf_iterator<wchar_t>>::do_get(float&)
// at 0x0083AAE0 (247B).  The retail body calls the matched wide
// _M_read_float<unsigned short>, the matched global bfmeGo1128A float
// conversion wrapper, and the matched wide iterator equal specialization.
// BFME's wchar_t ABI is unsigned short.  The wrapper's proven one-pointer
// input ABI is the narrow basic_string representation used here; calling its
// existing named body avoids adding a new helper pin.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_locale.h>

struct BfmeS1128
{
	const char *m_bfme00;
};

void bfmeGo1128A(BfmeS1128 *, float *);

_STLP_BEGIN_NAMESPACE

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	istreambuf_iterator(basic_streambuf<CharT, Traits> * = 0);
	__declspec(noinline) bool equal(const istreambuf_iterator &other) const;

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
		ios_base::iostate &err, float &value) const
	{
		string buffer;
		bool ok = _M_read_float(buffer, in, end, str, (CharT *)0);
		bfmeGo1128A((BfmeS1128 *)&buffer, &value);
		err = (ios_base::iostate)(ok ? ios_base::goodbit : ios_base::failbit);
		if (in.equal(end))
			err |= ios_base::eofbit;
		return in;
	}
};

typedef istreambuf_iterator<unsigned short,
	char_traits<unsigned short> > WideIterator;
template class num_get<unsigned short, WideIterator>;

_STLP_END_NAMESPACE
