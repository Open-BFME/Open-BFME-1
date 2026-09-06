// ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@ABV?$allocator@D@1@@Z
// partial score=0.98 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Od /Ob2

namespace _STL
{

template <class T>
class allocator {};

template <class T>
class char_traits {};

struct true_type {};

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
	void _M_allocate_block(unsigned n);

	__forceinline _String_base(const allocator_type &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (T *)0) {}

	~_String_base(void);

	private:
	T *_M_start;
	protected:
	T *_M_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef allocator<CharT> allocator_type;

	basic_string(const allocator_type &a);

	__forceinline void _M_terminate_string_aux(const true_type &)
	{
		*(this->_M_finish) = 0;
	}

	__forceinline void _M_terminate_string(void)
	{
		_M_terminate_string_aux(true_type());
	}

};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(const allocator_type &a)
	: _String_base<CharT, Alloc>(a)
{
	_M_allocate_block(8);
	_M_terminate_string();
}

}

inline void *operator new(unsigned int, void *place) { return place; }

void BfmeNarrowStringAllocatorAnchor(void *storage,
	const _STL::allocator<char> &alloc)
{
	new (storage) _STL::basic_string<char, _STL::char_traits<char>,
		_STL::allocator<char> >(alloc);
}
