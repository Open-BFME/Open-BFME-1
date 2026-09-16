// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3
//
// The vtable at VA 0x0112E9B0 sits behind an RTTI complete object locator
// naming the narrow num_put and 0x0112EA2C names the wide one, so their slots
// are do_put overloads of those two classes.  Slot 4 of each table calls the
// _M_do_put_float instantiation whose value type is long double, which is the
// overload these two bodies serve.  The iterator needs a declared constructor
// so MSVC returns it through the hidden pointer retail uses rather than in edx
// and eax.

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
class ostreambuf_iterator
{
public:
	ostreambuf_iterator();
	void *m_buf;
	int m_failed;
};

template <class CharT, class OutputIter, class ValueT>
OutputIter _M_do_put_float(OutputIter s, ios_base &str, CharT fill, ValueT val);

template <class CharT, class OutputIter>
class num_put : public locale::facet
{
protected:
	virtual ~num_put();
	virtual OutputIter do_put(OutputIter s, ios_base &str, CharT fill,
	                          long double val) const;
};

template <class CharT, class OutputIter>
OutputIter num_put<CharT, OutputIter>::do_put(OutputIter s, ios_base &str,
                                              CharT fill, long double val) const
{
	return _M_do_put_float(s, str, fill, val);
}

template class num_put<char, ostreambuf_iterator<char, char_traits<char> > >;
template class num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;

} // namespace _STL
