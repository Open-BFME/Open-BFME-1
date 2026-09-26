// Open-BFME: STLport basic_string<char>::substr, retail 0x006550F0, 122 bytes.
// The four parsePlayerKVPairs callers and the range-constructor ILT at 0x0002648B
// identify this body. The empty out-of-range helper matches the retail build's
// no-op exception configuration and lets the compiler retain the min calculation.
// cl: /O2 /MD /EHsc

namespace _STL
{

struct input_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <class T>
class allocator {};

template <class T>
class char_traits {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const Alloc &, Pointer p) : _M_data(p) {}

	Pointer _M_data;
};

template <class T, class Alloc>
class _String_base
{
public:
	typedef allocator<T> allocator_type;

	_String_base(const allocator_type &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0) {}

	~_String_base(void);

	T *_M_start;
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef allocator<CharT> allocator_type;
	typedef unsigned size_type;

	__forceinline basic_string(const CharT *first, const CharT *last)
		: _String_base<CharT, Alloc>(allocator_type())
	{
		_M_range_initialize(first, last);
	}

	size_type size(void) const
	{
		return (size_type)(this->_M_finish - this->_M_start);
	}

	basic_string<CharT, Traits, Alloc> substr(size_type position,
		size_type count) const;

private:
	__forceinline void _M_throw_out_of_range(void) const {}
	void _M_range_initialize(const CharT *first, const CharT *last,
		const forward_iterator_tag &tag);

	__forceinline void _M_range_initialize(const CharT *first,
		const CharT *last)
	{
		_M_range_initialize(first, last, random_access_iterator_tag());
	}
};

template <class T>
inline const T &min(const T &left, const T &right)
{
	return right < left ? right : left;
}

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>
basic_string<CharT, Traits, Alloc>::substr(size_type position,
	size_type count) const
{
	if (position > size())
		this->_M_throw_out_of_range();
	return basic_string<CharT, Traits, Alloc>(
		this->_M_start + position,
		this->_M_start + position + (min)(count, size() - position));
}

}

template _STL::basic_string<char, _STL::char_traits<char>,
	_STL::allocator<char> > _STL::basic_string<char,
	_STL::char_traits<char>, _STL::allocator<char> >::substr(unsigned,
	unsigned) const;
