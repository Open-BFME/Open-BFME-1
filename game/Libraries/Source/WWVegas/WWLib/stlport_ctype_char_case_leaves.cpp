// The vtable at VA 0x0112F254 carries an RTTI complete object locator spelling
// '.?AV?$ctype@D@_STL@@', so every slot in it belongs to _STL::ctype<char>.
// inputs/vendor/stlport/stl/_ctype.h declares do_toupper(char), do_tolower(char),
// do_toupper(range), do_tolower(range), and MSVC 7.1 lays each overload set
// out in reverse declaration order, which puts the range form of do_toupper at
// slot 1 and the single-character do_tolower at slot 4.  The two landed rows
// in T2CtypeTableFacets.cpp agree: slot 2 reads the upper table for one
// character and slot 3 walks the lower table over a range.
//
// Both bodies here index the same two 256-entry tables those rows use, so the
// table split is checked rather than assumed.

extern const char t2_upper_table[256];
extern const char t2_lower_table[256];

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

class ctype_base
{
public:
	typedef unsigned int mask;
};

template <class CharT>
class ctype;

template <>
class ctype<char> : public locale::facet, public ctype_base
{
public:
	typedef char char_type;

protected:
	~ctype();

	virtual char do_toupper(char c) const;
	virtual char do_tolower(char c) const;
	virtual const char *do_toupper(char *low, const char *high) const;
	virtual const char *do_tolower(char *low, const char *high) const;
};

} // namespace _STL

char _STL::ctype<char>::do_tolower(char c) const
{
	return t2_lower_table[(unsigned char)c];
}

const char *_STL::ctype<char>::do_toupper(char *low, const char *high) const
{
	while (low < high)
	{
		*low = t2_upper_table[(unsigned char)*low];
		++low;
	}
	return high;
}
