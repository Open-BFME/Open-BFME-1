// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 num_get<char, istreambuf_iterator<char>>::do_get(float&) at
// 0x00838BE0. The adjacent double specialization uses the same parser body,
// while the retail call to bfmeGo1128A identifies this specialization.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_locale.h>

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

void _STLP_CALL __string_to_float(const string &, float &);

template <class CharT, class InputIter>
class num_get : public locale::facet
{
protected:
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, float &value) const
	{
		string buffer;
		bool ok = _M_read_float(buffer, in, end, str, (CharT *)0);
		__string_to_float(buffer, value);
		err = (ios_base::iostate)(ok ? ios_base::goodbit : ios_base::failbit);
		if (in.equal(end))
			err |= ios_base::eofbit;
		return in;
	}
};

typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;
template class num_get<char, NarrowIterator>;

_STLP_END_NAMESPACE
