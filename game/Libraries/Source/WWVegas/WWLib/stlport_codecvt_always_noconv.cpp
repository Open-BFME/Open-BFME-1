// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// The vtable at VA 0x0112EA8C carries an RTTI complete object locator spelling
// '.?AV?$codecvt@DDH@_STL@@' and 0x0112EAB0 spells '.?AV?$codecvt@GDH@_STL@@'.
// inputs/vendor/stlport/stl/_codecvt.h declares the protected virtuals as do_out,
// do_in, do_unshift, do_encoding, do_always_noconv, do_length, do_max_length,
// so slot 4 is do_encoding, slot 5 do_always_noconv and slot 7 do_max_length.
// The always_noconv bodies return true, which is what a codecvt that never
// converts reports, and the other four return 1, which is the fixed width such
// a codecvt reads and writes.

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

template <class InternT, class ExternT, class StateT>
class codecvt : public locale::facet
{
protected:
	virtual ~codecvt();
	virtual int do_encoding() const;
	virtual bool do_always_noconv() const;
	virtual int do_max_length() const;
};

template <class InternT, class ExternT, class StateT>
int codecvt<InternT, ExternT, StateT>::do_encoding() const
{
	return 1;
}

template <class InternT, class ExternT, class StateT>
int codecvt<InternT, ExternT, StateT>::do_max_length() const
{
	return 1;
}

template <class InternT, class ExternT, class StateT>
bool codecvt<InternT, ExternT, StateT>::do_always_noconv() const
{
	return true;
}

template class codecvt<char, char, int>;
template class codecvt<wchar_t, char, int>;

} // namespace _STL
