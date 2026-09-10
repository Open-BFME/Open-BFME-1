// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 num_get<char, istreambuf_iterator<char>>::do_get(double&)
// at 0x00838AE0 (247B).  The retail body calls the matched narrow
// _M_read_float<char>, the matched bfmeGo1128B double conversion wrapper,
// and the matched narrow iterator equal specialization.  The wrapper's
// proven one-pointer input ABI is the narrow basic_string representation used
// here; calling its existing named body avoids adding a new helper pin.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_locale.h>

struct BfmeS1128
{
	const char *m_bfme00;
};

void bfmeGo1128B(BfmeS1128 *, double *);

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
		ios_base::iostate &err, double &value) const
	{
		string buffer;
		bool ok = _M_read_float(buffer, in, end, str, (CharT *)0);
		bfmeGo1128B((BfmeS1128 *)&buffer, &value);
		err = (ios_base::iostate)(ok ? ios_base::goodbit : ios_base::failbit);
		if (in.equal(end))
			err |= ios_base::eofbit;
		return in;
	}
};

typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;
template class num_get<char, NarrowIterator>;

_STLP_END_NAMESPACE
