// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// The vtable at VA 0x0112EA8C carries an RTTI complete object locator spelling
// '.?AV?$codecvt@DDH@_STL@@' and 0x0112EAB0 spells '.?AV?$codecvt@GDH@_STL@@'.
// vendor/stlport/stl/_codecvt.h declares the protected virtuals as do_out,
// do_in, do_unshift, do_encoding, do_always_noconv, do_length, do_max_length,
// so slot 5 of each vtable is do_always_noconv.  Both bodies return true,
// which is what a codecvt that never converts reports.

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
	virtual bool do_always_noconv() const;
};

template <class InternT, class ExternT, class StateT>
bool codecvt<InternT, ExternT, StateT>::do_always_noconv() const
{
	return true;
}

template class codecvt<char, char, int>;
template class codecvt<wchar_t, char, int>;

} // namespace _STL
