// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3
//
// The vtable at VA 0x0112E97C sits behind an RTTI complete object locator
// spelling the narrow num_get and 0x0112E9F8 spells the wide one, so the
// twelve forwarders over 0x00832800 to 0x00834B60 are do_get overloads of two
// classes and not ten separate ones.  Slot 10 of each vtable calls the
// _M_do_get_integer instantiation whose value type is long, so slot 10 is
// do_get for a long.  The wrapper hands the callee both iterators by reference,
// the three trailing arguments by value and a null grouping pointer, which is
// what U2PutForwarders.cpp reads off the pushes.

typedef unsigned short wchar_t;

namespace _STL
{

class ios_base;

class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
	};
};

template <class CharT> class char_traits;

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	istreambuf_iterator();
	void *m_buf;
	int m_c;
};

template <class InputIter, class ValueT, class CharT>
InputIter _M_do_get_integer(InputIter &in, InputIter &end, ios_base &str,
                            int &err, ValueT &val, CharT *grouping);

template <class CharT, class InputIter>
class num_get : public locale::facet
{
protected:
	virtual ~num_get();
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
	                         int &err, long &val) const;
};

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            long &val) const
{
	return _M_do_get_integer(in, end, str, err, val, (CharT *)0);
}

template class num_get<char, istreambuf_iterator<char, char_traits<char> > >;
template class num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;

} // namespace _STL
