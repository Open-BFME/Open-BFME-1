// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3
//
// The vtable at VA 0x0112EAE8 sits behind an RTTI complete object locator
// spelling '.?AV?$collate@G@_STL@@'.  inputs/vendor/stlport/stl/_collate.h declares
// do_compare, do_transform and do_hash in that order, and slot 3 already holds
// the wide hash, so slot 1 is do_compare.  The body forwards the two ranges to
// __lexicographical_compare_3way, whose wide instantiation is the row at
// 0x00844280.

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

template <class InputIter1, class InputIter2>
int __lexicographical_compare_3way(InputIter1 first1, InputIter1 last1,
                                   InputIter2 first2, InputIter2 last2);

template <class CharT>
class collate : public locale::facet
{
protected:
	virtual ~collate();
	virtual int do_compare(const CharT *low1, const CharT *high1,
	                       const CharT *low2, const CharT *high2) const;
};

template <class CharT>
int collate<CharT>::do_compare(const CharT *low1, const CharT *high1,
                               const CharT *low2, const CharT *high2) const
{
	return __lexicographical_compare_3way(low1, high1, low2, high2);
}

template class collate<wchar_t>;

} // namespace _STL
