// ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@ABV01@IIABV?$allocator@D@1@@Z
// partial score=0.96 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Od /Ob2

namespace _STL
{

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T>
class allocator {};

template <class T>
class char_traits {};

template <class T>
__forceinline const T &min(const T &left, const T &right)
{
	return right < left ? right : left;
}

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

	__forceinline _String_base(const allocator_type &a)
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

	basic_string(const basic_string<CharT, Traits, Alloc> &s,
		size_type pos, size_type n, const allocator_type &a);

	__forceinline size_type size(void) const
	{
		return (size_type)(this->_M_finish - this->_M_start);
	}

private:
	void _M_throw_out_of_range(void);

	void _M_range_initialize(const CharT *f, const CharT *l,
		const forward_iterator_tag &);

	__forceinline void _M_range_initialize(const CharT *f, const CharT *l)
	{
		_M_range_initialize(f, l, random_access_iterator_tag());
	}
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(
	const basic_string<CharT, Traits, Alloc> &s,
	size_type pos, size_type n, const allocator_type &a)
	: _String_base<CharT, Alloc>(a)
{
	char scratch[16];
	if (pos > s.size())
		this->_M_throw_out_of_range();
	else
		_M_range_initialize(s._M_start + pos,
			s._M_start + pos + (min)(n, s.size() - pos));
}

}

inline void *operator new(unsigned int, void *place) { return place; }

void BfmeNarrowStringSubstringAnchor(void *storage,
	const _STL::basic_string<char, _STL::char_traits<char>,
		_STL::allocator<char> > &source,
	unsigned pos, unsigned count,
	const _STL::allocator<char> &alloc)
{
	new (storage) _STL::basic_string<char,
		_STL::char_traits<char>, _STL::allocator<char> >(
		source, pos, count, alloc);
}
