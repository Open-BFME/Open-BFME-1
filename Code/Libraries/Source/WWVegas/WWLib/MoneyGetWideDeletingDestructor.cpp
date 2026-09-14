// cl: /DNDEBUG /MD /EHsc /O2

// STLport 4.5.3 money_get<wchar_t, istreambuf_iterator<wchar_t> > destructor
// and compiler-emitted scalar-deleting wrapper. Retail RTTI identifies vtable
// 0x0112E9D8 as this exact specialization; slot zero is the 30-byte wrapper
// at 0x008323C0. Its adjacent 7-byte destructor at 0x008323E0 restores the
// locale::facet vtable before returning.

typedef unsigned short wchar_t;

namespace _STL
{

template<class CHAR>
class char_traits
{
};

template<class CHAR, class TRAITS>
class istreambuf_iterator
{
};

class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
	};
};

template<class CHAR, class ITERATOR>
class money_get : public locale::facet
{
	protected:
		virtual ~money_get();
		virtual void getLong() = 0;
		virtual void getDouble() = 0;
};

template<>
money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::~money_get()
{
}

} // namespace _STL
