// cl: /DNDEBUG /MD /EHsc /O2

// STLport 4.5.3 money_get<char, istreambuf_iterator<char> > destructor and
// compiler-emitted scalar-deleting wrapper. Retail RTTI identifies vtable
// 0x0112E95C as this exact specialization; slot zero is the 30-byte wrapper
// at 0x00832300. Its adjacent 7-byte destructor at 0x00832320 restores the
// locale::facet vtable before returning.

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
money_get<char, istreambuf_iterator<char, char_traits<char> > >::~money_get()
{
}

} // namespace _STL
