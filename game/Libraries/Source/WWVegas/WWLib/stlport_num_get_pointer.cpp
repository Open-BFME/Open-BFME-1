// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3
//
// The vtable at VA 0x0112E97C sits behind an RTTI complete object locator
// spelling the narrow num_get and 0x0112E9F8 spells the wide one.  Each table
// runs the do_get overload set of inputs/vendor/stlport/stl/_num_get.h in reverse
// declaration order, which the landed rows confirm: slot 3 is the long double
// reader, slot 5 the double, slot 6 the float and slot 10 the long.  That puts
// the void pointer reader at slot 4 of both tables.  It reads an unsigned
// __int64 through the same _M_do_get_integer instantiation slot 1 uses, then
// stores the low dword through its reference argument unless the error state
// picked up bit 2.

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
	                         int &err, void *&p) const;
};

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(InputIter in, InputIter end,
                                            ios_base &str, int &err,
                                            void *&p) const
{
	unsigned __int64 val;
	InputIter result = _M_do_get_integer(in, end, str, err, val, (CharT *)0);
	if ((err & 4) == 0)
		p = (void *)(unsigned long)val;
	return result;
}

template class num_get<char, istreambuf_iterator<char, char_traits<char> > >;
template class num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;

} // namespace _STL
