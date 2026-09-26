// cl: /DNDEBUG /MD /EHsc

// _STL::basic_string<wchar>::basic_string(const wchar *, const allocator &),
// retail 0x00661750, 98 bytes.

class Gen_006616A0
{
public:
	void bfmeAssign(const short *first, const short *last, void *tag);
};

namespace _STL
{

template <class T>
class allocator
{
};

template <class T>
class char_traits
{
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const Alloc &, Pointer p) : m_data(p) {}

	Pointer m_data;
};

template <class T, class Alloc>
class _String_base
{
public:
	typedef Alloc allocator_type;

	_String_base(const allocator_type &a)
		: m_start(0), m_finish(0), m_end_of_storage(a, (T *)0)
	{
	}

	~_String_base(void);

	T *m_start;
	T *m_finish;
	_STLP_alloc_proxy<T *, T, allocator_type> m_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef Alloc allocator_type;

	basic_string(const CharT *text, const allocator_type &allocator);
};

// ??0?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@PBGABV?$allocator@G@1@@Z
template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(
	const CharT *text, const allocator_type &allocator)
	: _String_base<CharT, Alloc>(allocator)
{
	int length = 0;
	while (text[length] != 0)
		++length;
	const CharT *last = text + length;

	reinterpret_cast< ::Gen_006616A0 *>(this)->bfmeAssign(
		reinterpret_cast<const short *>(text),
		reinterpret_cast<const short *>(last), (void *)&text);
}

}

inline void *operator new(unsigned int, void *place)
{
	return place;
}

typedef _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>,
	_STL::allocator<unsigned short> > BfmeWideString;

void BfmeWideStringFromPointerAnchor(const unsigned short *text,
	const _STL::allocator<unsigned short> &allocator, void *storage)
{
	new (storage) BfmeWideString(text, allocator);
}
