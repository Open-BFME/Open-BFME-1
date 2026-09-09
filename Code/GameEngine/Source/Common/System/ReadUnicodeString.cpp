// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stringinline

#include "StringInline.h"

#define EOF (-1)

struct _iobuf
{
};

extern "C" __declspec(dllimport) unsigned short __cdecl fgetwc(_iobuf *stream);

UnicodeString readUnicodeString(_iobuf *file)
{
	unsigned short str[1024] = L"";
	int index = 0;

	int c = fgetwc(file);
	if (c == EOF) {
		str[index] = 0;
	}
	str[index] = c;

	while (index < 1023 && str[index] != 0) {
		++index;
		int c = fgetwc(file);
		if (c == 0xffff) {
			str[index] = 0;
			break;
		}
		str[index] = c;
	}
	str[1023] = L'\0';

	UnicodeString retval(str);
	return retval;
}
