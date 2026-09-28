// cl: /DNDEBUG /MD /O2
// Retail 0x00887040 (narrow _vsnprintf) and 0x00887060 (wide vswprintf):
// file-static va_list forwarders. File-static scope is what keeps the
// incoming va_list in EAX (push eax / mov eax,[esp+8]).

#include <stdarg.h>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *buffer, unsigned int size, const char *format, va_list args);
extern "C" __declspec(dllimport) int __cdecl vswprintf(unsigned short *buffer, unsigned int size, const unsigned short *format, va_list args);

static int Rva00887040Narrow(char *buffer, unsigned int size, const char *format, va_list args)
{
	return _vsnprintf(buffer, size, format, args);
}

static int Rva00887060Wide(unsigned short *buffer, unsigned int size, const unsigned short *format, va_list args)
{
	return vswprintf(buffer, size, format, args);
}

// Visible call sites so both statics are emitted; not claimed.
void Rva00887040Keep(char *buffer, unsigned int size, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	Rva00887040Narrow(buffer, size, format, args);
	Rva00887060Wide((unsigned short *)buffer, size, (const unsigned short *)format, args);
	va_end(args);
}
