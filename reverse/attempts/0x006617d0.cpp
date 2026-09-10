// ?MultiByteToWideCharSingleLine@@YA?AV?$basic_string@GU?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@PBD@Z
// partial score=0.94 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// GameSpy's UTF-8-to-wide single-line conversion utility.
// Retail RVA 0x006617D0, 301 bytes.  The two BuddyThread callback bodies and
// the upstream ThreadUtils implementation identify this entry; the adjacent
// wide-string constructor at 0x00661750 is a separate matched body.

typedef unsigned short WideChar;

namespace _STL
{
template <class Character>
struct char_traits
{
};

template <class Character>
class allocator
{
};

template <class Pointer, class Value, class Allocator>
class _STLP_alloc_proxy : public Allocator
{
public:
	_STLP_alloc_proxy(const Allocator &allocator, Pointer pointer)
		: Allocator(allocator), m_data(pointer) {}

	Pointer m_data;
};

template <class Character, class Allocator>
class _String_base
{
public:
	typedef Allocator allocator_type;

	_String_base(const allocator_type &allocator)
		: m_start(0), m_finish(0), m_end_of_storage(allocator, (Character *)0) {}

	~_String_base() __declspec(nothrow) {}

	Character *m_start;
	Character *m_finish;
	_STLP_alloc_proxy<Character *, Character, allocator_type> m_end_of_storage;
};

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *memory, unsigned int bytes);
};

template <class Character, class Traits, class Allocator>
class basic_string : public _String_base<Character, Allocator>
{
public:
	typedef Allocator allocator_type;

	basic_string(const Character *text,
		const allocator_type &allocator = allocator_type());
	basic_string(const basic_string &other);

	~basic_string()
	{
		if (this->m_start)
		{
			unsigned int bytes =
				(unsigned int)(this->m_end_of_storage.m_data - this->m_start)
					* sizeof(Character);
			if (bytes > 128)
				::operator delete(this->m_start);
			else
				__node_alloc<true, 0>::_M_deallocate(this->m_start, bytes);
		}
	}

	const Character *c_str() const { return this->m_start; }
};

typedef basic_string<WideChar, char_traits<WideChar>, allocator<WideChar> >
	wide_string;
}

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
	unsigned int codePage,
	unsigned long flags,
	const char *source,
	int sourceCharacters,
	WideChar *destination,
	int destinationCharacters);
extern "C" __declspec(dllimport) WideChar *__cdecl wcschr(
	const WideChar *text, WideChar value);
extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" void *__cdecl memset(void *destination, int value,
	unsigned int bytes);
#pragma intrinsic(memset)

void __cdecl operator delete(void *block);
void __cdecl operator delete[](void *block);

enum
{
	kUtf8CodePage = 0xfde9
};

_STL::wide_string MultiByteToWideCharSingleLine(const char *orig)
{
	const char *text = orig;
	int len = strlen(text);
	int wideLength = len + len;
	WideChar *dest = new WideChar[wideLength + 1];
	memset(dest, 0, (wideLength + 1) * sizeof(WideChar));

	MultiByteToWideChar(kUtf8CodePage, 0, text, -1, dest, wideLength);
	WideChar *c = 0;
	do
	{
		c = wcschr(dest, L'\n');
		if (c)
		{
			*c = L' ';
		}
	}
	while (c != 0);
	do
	{
		c = wcschr(dest, L'\r');
		if (c)
		{
			*c = L' ';
		}
	}
	while (c != 0);

	_STL::wide_string ret(dest,
		*(_STL::allocator<WideChar> *)&orig);
	delete dest;
	return ret;
}
