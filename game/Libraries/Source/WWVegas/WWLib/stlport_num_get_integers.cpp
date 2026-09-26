// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3
//
// The vtable at VA 0x0112E97C sits behind an RTTI complete object locator
// spelling the narrow num_get and 0x0112E9F8 spells the wide one.  Each table
// runs the do_get overload set of inputs/vendor/stlport/stl/_num_get.h in reverse
// declaration order, which the landed rows confirm: slot 3 is the long double
// reader, slot 5 the double, slot 6 the float and slot 10 the long.  That puts
// unsigned short at slot 9, unsigned int at slot 8, unsigned long at slot 7,
// __int64 at slot 2 and unsigned __int64 at slot 1, and every one of those ten
// bodies calls the _M_do_get_integer instantiation whose value type matches.
// The wrapper hands the callee both iterators by reference, the three trailing
// arguments by value and a null grouping pointer.

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
	                         int &err, unsigned short &val) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
	                         int &err, unsigned int &val) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
	                         int &err, unsigned long &val) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
	                         int &err, __int64 &val) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
	                         int &err, unsigned __int64 &val) const;
};

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            unsigned short &val) const
{
	return _M_do_get_integer(in, end, str, err, val, (CharT *)0);
}

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            unsigned int &val) const
{
	return _M_do_get_integer(in, end, str, err, val, (CharT *)0);
}

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            unsigned long &val) const
{
	return _M_do_get_integer(in, end, str, err, val, (CharT *)0);
}

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            __int64 &val) const
{
	return _M_do_get_integer(in, end, str, err, val, (CharT *)0);
}

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            unsigned __int64 &val) const
{
	return _M_do_get_integer(in, end, str, err, val, (CharT *)0);
}

template class num_get<char, istreambuf_iterator<char, char_traits<char> > >;
template class num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;

} // namespace _STL
