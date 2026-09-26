// ?d_005cad10@@YAXXZ
// partial score=0.32 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The two anonymous bodies are STLport 4.5.3's non-member basic_string
// concatenation operators emitted by ParticleSystemTemplate::writeINI.

namespace _STL
{

template <class T>
class allocator
{
public:
	allocator() throw() {}
	allocator(const allocator &) throw() {}
	unsigned int m_dummy;
};

template <class T>
class char_traits
{
};

struct forward_iterator_tag
{
};

struct _String_reserve_t
{
};

template <bool threads, int instance>
class __node_alloc;

class Gen_005C46C0
{
public:
	Gen_005C46C0(void *allocator, unsigned int count);

	char *m_start;
	char *m_finish;
	char *m_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : protected Gen_005C46C0
{
public:
	typedef CharT *pointer;
	typedef unsigned int size_type;
	typedef Alloc allocator_type;
	typedef _String_reserve_t _Reserve_t;

	basic_string(_Reserve_t, size_type count, const allocator_type &allocator)
		: Gen_005C46C0((void *)&allocator, count + 1)
	{
		*this->m_finish = 0;
	}

	basic_string(const basic_string &);

	allocator_type get_allocator() const throw();

	~basic_string()
	{
		const unsigned int bytes =
			(unsigned int)(this->m_end_of_storage - this->m_start);
		if (this->m_start)
		{
			if (bytes > 128)
				::operator delete(this->m_start);
			else
				__node_alloc<true, 0>::_M_deallocate(this->m_start, bytes);
		}
	}

	size_type size() const
	{
		return (size_type)(this->m_finish - this->m_start);
	}

	basic_string &append(const basic_string &other)
	{
		return append(other.m_start, other.m_finish, forward_iterator_tag());
	}

	template <class InputIterator>
	basic_string &append(InputIterator first, InputIterator last,
		const forward_iterator_tag &tag);

	void push_back(CharT value);
};

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *memory, unsigned int bytes);
};

typedef basic_string<char, char_traits<char>, allocator<char> > BfmeNarrowString;

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc> __cdecl operator+(
	const basic_string<CharT, Traits, Alloc> &source, const CharT value)
{
	typedef basic_string<CharT, Traits, Alloc> String;
	typedef typename String::_Reserve_t Reserve;
	String result(Reserve(), source.size() + 1, source.get_allocator());
	result.append(source);
	result.push_back(value);
	return result;
}

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc> __cdecl operator+(
	const basic_string<CharT, Traits, Alloc> &source, const CharT *text)
{
	typedef basic_string<CharT, Traits, Alloc> String;
	typedef typename String::_Reserve_t Reserve;
	unsigned int length = 0;
	while (text[length] != 0)
		++length;
	String result(Reserve(), source.size() + length, source.get_allocator());
	result.append(source);
	result.append(text, text + length, forward_iterator_tag());
	return result;
}

template BfmeNarrowString __cdecl operator+(
	const BfmeNarrowString &, const char);

template BfmeNarrowString __cdecl operator+(
	const BfmeNarrowString &, const char *);

}
