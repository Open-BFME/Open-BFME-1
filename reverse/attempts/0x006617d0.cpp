// ?MultiByteToWideCharSingleLine@@YA?AV?$basic_string@GU?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@PBD@Z
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME: MultiByteToWideCharSingleLine, retail 0x006617D0, 307 bytes.
//
// Named by BuddyThreadCallbacks. ZH ThreadUtils allocates WideChar[len+1];
// retail uses WideChar[2*len+1], CP_UTF8 (0xfde9), and wcschr to turn \n/\r
// into spaces. char_traits is a struct so the decorated name matches the
// callers' GU (not STLport's class GV). Empty allocator is passed via the
// orig parameter slot so it does not grow the frame.

#include <string.h>

namespace _STL
{
template <class T> struct char_traits {};
template <class T> class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const CharT *s, const allocator<CharT> &a = allocator<CharT>());
	basic_string(const basic_string &other);
	~basic_string();

private:
	CharT *m_start;
	CharT *m_finish;
	CharT *m_end;
};

typedef basic_string<unsigned short, char_traits<unsigned short>,
	allocator<unsigned short> > wstring;
}

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
	unsigned int codePage, unsigned long flags, const char *source,
	int sourceBytes, unsigned short *destination, int destinationChars);
extern "C" __declspec(dllimport) unsigned short *__cdecl wcschr(
	const unsigned short *text, unsigned short ch);

void *__cdecl operator new[](unsigned int bytes);
void __cdecl operator delete[](void *block);

enum { kUtf8CodePage = 0xfde9 };

// ?MultiByteToWideCharSingleLine@@YA?AV?$basic_string@GU?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@PBD@Z present-unmatched
_STL::wstring MultiByteToWideCharSingleLine(const char *orig)
{
	const char *text = orig;
	int len = (int)strlen(text);
	unsigned short *dest = (unsigned short *)operator new[](
		(unsigned)(2 * len + 1) * sizeof(unsigned short));
	memset(dest, 0, (unsigned)(2 * len + 1) * sizeof(unsigned short));
	MultiByteToWideChar(kUtf8CodePage, 0, text, -1, dest, 2 * len);

	unsigned short *c;
	do
	{
		c = wcschr(dest, L'\n');
		if (c)
			*c = L' ';
	} while (c != 0);
	do
	{
		c = wcschr(dest, L'\r');
		if (c)
			*c = L' ';
	} while (c != 0);

	_STL::wstring ret(dest, *(_STL::allocator<unsigned short> *)&orig);
	operator delete[](dest);
	return ret;
}
