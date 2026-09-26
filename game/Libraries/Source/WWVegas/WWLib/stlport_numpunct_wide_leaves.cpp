// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// The vtable at VA 0x0112EB18 carries an RTTI complete object locator whose
// type descriptor spells `.?AV?$numpunct@G@_STL@@`, so every slot in it belongs
// to _STL::numpunct<wchar_t>.  Slot 0 is the deleting destructor already landed
// in stlport_locale_facet_destructors.cpp.  Slots 1 and 2 are the two bodies
// here, and slots 3 to 5 return a basic_string, which is the do_grouping,
// do_truename, do_falsename tail of the same facet.  The narrow table at
// 0x0112EAFC runs the same order and its slots 1 and 2 already carry
// do_decimal_point and do_thousands_sep.

typedef unsigned short wchar_t;

namespace _STL
{

class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
	};
};

template <class CharT>
class numpunct : public locale::facet
{
protected:
	virtual ~numpunct();
	virtual CharT do_decimal_point() const;
	virtual CharT do_thousands_sep() const;
};

template <class CharT>
CharT numpunct<CharT>::do_decimal_point() const
{
	return '.';
}

template <class CharT>
CharT numpunct<CharT>::do_thousands_sep() const
{
	return ',';
}

template class numpunct<wchar_t>;

} // namespace _STL
