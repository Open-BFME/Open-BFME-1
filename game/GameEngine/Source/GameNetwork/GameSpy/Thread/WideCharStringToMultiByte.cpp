// cl: /DNDEBUG /MD /EHsc
// BFME's wide-to-narrow GameSpy utility at retail 0x00661950.

#include <string.h>

typedef unsigned short WideChar;

namespace _STL
{
template <class Character>
class char_traits
{
};

template <class Character>
class allocator
{
};

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

template <class Character, class Traits, class Allocator>
class basic_string
{
public:
	 basic_string();
	 basic_string(const basic_string &other);
	 ~basic_string()
	 {
		unsigned int bytes =
			(unsigned int)(m_end - m_start) * sizeof(Character);
		if (m_start)
		{
			if (bytes > 128)
				::operator delete(m_start);
			else
				_STL::nodePoolDeallocate(m_start, bytes);
		}
	}
	 basic_string &assign(const Character *first, const Character *last);

private:
	Character *m_start;
	Character *m_finish;
	Character *m_end;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
	unsigned int codePage,
	unsigned long flags,
	const WideChar *source,
	int sourceCharacters,
	char *destination,
	int destinationCharacters,
	const char *defaultCharacter,
	int *usedDefaultCharacter);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const WideChar *text);

void *__cdecl operator new[](unsigned int bytes);
void __cdecl operator delete(void *block);
void __cdecl operator delete[](void *block);

enum
{
	kUtf8CodePage = 0xfde9
};

_STL::string WideCharStringToMultiByte(const WideChar *orig)
{
	_STL::string ret;
	int len = WideCharToMultiByte(kUtf8CodePage, 0, orig, wcslen(orig), 0, 0, 0, 0) + 1;
	if (len > 0)
	{
		char *dest = (char *)operator new[](len);
		WideCharToMultiByte(kUtf8CodePage, 0, orig, -1, dest, len, 0, 0);
		dest[len - 1] = 0;
		ret.assign(dest, dest + strlen(dest));
		delete[] dest;
	}
	return ret;
}
