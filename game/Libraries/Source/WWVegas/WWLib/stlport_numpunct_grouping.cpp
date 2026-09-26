// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// Slot 3 of the narrow numpunct vtable at VA 0x0112EAFC and slot 3 of the wide
// one at 0x0112EB18.  inputs/vendor/stlport/stl/_numpunct.h declares do_decimal_point,
// do_thousands_sep, do_grouping, do_truename and do_falsename in that order for
// both specializations, and slots 1 and 2 already carry the landed punctuation
// leaves.  do_grouping returns a narrow basic_string for the wide facet too,
// which is why both bodies call the same narrow default constructor.

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class allocator {};

template <class T>
class char_traits {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string();
	~basic_string();
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

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
	virtual string do_grouping() const;
};

template <class CharT>
string numpunct<CharT>::do_grouping() const
{
	return string();
}

template class numpunct<char>;
template class numpunct<wchar_t>;

} // namespace _STL
