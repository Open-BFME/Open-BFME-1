// cl: /DNDEBUG /MD /EHsc
#include <stdarg.h>

__declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned, const char *, va_list);

// ?Rva00783210Format@@YAXPBDZZ
void Rva00783210Format(const char *format, ...)
{
	char text[0x100];
	va_list args;
	va_start(args, format);
	_vsnprintf(text, sizeof text, format, args);
	va_end(args);
}
