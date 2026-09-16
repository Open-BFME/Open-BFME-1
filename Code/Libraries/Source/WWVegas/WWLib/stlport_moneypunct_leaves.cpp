// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// Four vtables carry an RTTI complete object locator naming a moneypunct
// instantiation: 0x0112FADC is moneypunct<char, true>, 0x0112FB08 is
// moneypunct<char, false>, 0x0112FB34 is moneypunct<wchar_t, true> and
// 0x0112FB60 is moneypunct<wchar_t, false>.  Slot 3 of every one of them
// returns a narrow basic_string while slots 4 to 6 return the facet's own
// character type, which is the do_grouping, do_curr_symbol, do_positive_sign,
// do_negative_sign run of STLport 4.5.3.  That pins slots 1 and 2 as
// do_decimal_point and do_thousands_sep and slot 7 as do_frac_digits.

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

template <class CharT, bool International>
class moneypunct : public locale::facet
{
protected:
	virtual ~moneypunct();
	virtual CharT do_decimal_point() const;
	virtual CharT do_thousands_sep() const;
	virtual int do_frac_digits() const;
};

template <class CharT, bool International>
CharT moneypunct<CharT, International>::do_decimal_point() const
{
	return (CharT)' ';
}

template <class CharT, bool International>
CharT moneypunct<CharT, International>::do_thousands_sep() const
{
	return (CharT)' ';
}

template <class CharT, bool International>
int moneypunct<CharT, International>::do_frac_digits() const
{
	return 0;
}

template class moneypunct<char, true>;
template class moneypunct<char, false>;
template class moneypunct<wchar_t, true>;
template class moneypunct<wchar_t, false>;

} // namespace _STL
