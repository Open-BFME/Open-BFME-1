// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: StringBase operator= delegates to set() and returns *this.
// MSVC 7.1 without /Zc:wchar_t: wchar_t is unsigned short (mangle G).

typedef unsigned short wchar_t;

#include "string_base.h"

// ??4?$StringBase@D@@QAEAAV0@ABV0@@Z
template <>
StringBase<char> &StringBase<char>::operator=(const StringBase<char> &src)
{
	set(src);
	return *this;
}

// ??4?$StringBase@G@@QAEAAV0@ABV0@@Z
template <>
StringBase<wchar_t> &StringBase<wchar_t>::operator=(const StringBase<wchar_t> &src)
{
	set(src);
	return *this;
}
