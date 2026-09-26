// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::basic_string<char>::basic_string(const basic_string &),
// retail 0x004FB1B0, 86 bytes. The body carried only a machine byte-dump row.
// Twin of the wide copy constructor at 0x004FB220.
//
// Three zero stores at +0, +4 and +8 are the _String_base subobject, whose
// members are the start and finish pointers and an allocator proxy holding the
// end-of-storage pointer. Then one call passes the source's start and finish
// and an iterator-category tag, which is the forward-iterator overload of
// _M_range_initialize being picked for a plain pointer.
//
// The frame carries one unwind state around that call, so the base has a
// destructor to run if the initialisation throws; it is declared and left
// undefined, since nothing here calls it.
//
// The tag temporary is passed as the address of the incoming parameter's own
// stack slot. It is an empty class, so the compiler needs an address and never
// writes through it, and it reuses the nearest one rather than reserving.

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

	T *_M_start;						// +0x00
	T *_M_finish;						// +0x04
	_STLP_alloc_proxy<T *, T, allocator_type> _M_end_of_storage;	// +0x08
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef allocator<CharT> allocator_type;

	basic_string(const basic_string<CharT, Traits, Alloc> &s);

	allocator_type get_allocator(void) const { return allocator_type(); }

private:
	void _M_range_initialize(const CharT *f, const CharT *l, const forward_iterator_tag &);

	void _M_range_initialize(const CharT *f, const CharT *l)
	{
		_M_range_initialize(f, l, random_access_iterator_tag());
	}
};

// ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@ABV01@@Z
template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(const basic_string<CharT, Traits, Alloc> &s)
	: _String_base<CharT, Alloc>(s.get_allocator())
{
	_M_range_initialize(s._M_start, s._M_finish);
}

}

// Placement new declared here rather than including <new>: the anchor only
// needs a way to run the constructor without also pulling in a destructor.
inline void *operator new(unsigned int, void *place) { return place; }

void BfmeNarrowStringCopyAnchor(void *storage,
	const _STL::basic_string<char, _STL::char_traits<char>,
		_STL::allocator<char> > &other)
{
	new (storage) _STL::basic_string<char,
		_STL::char_traits<char>, _STL::allocator<char> >(other);
}
