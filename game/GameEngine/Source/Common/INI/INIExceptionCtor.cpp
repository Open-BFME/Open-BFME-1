// cl: /DNDEBUG /MD /O2
// Retail RVA 0x00850600 is the 103-byte INIException(int, const char *, ...)
// constructor. The formatter writes the retail global at VA 0x0130C650 and
// imports _vsnprintf through IAT VA 0x01359360.
#include <stdarg.h>
#include <string.h>

extern char g_bfmeFormatBuffer[2048];
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
extern "C" void *__cdecl bfmeArrayNew(unsigned int);

class INIException
{
public:
    char *mFailureMessage;
    int m_argCount;
    INIException(int argCount, const char *format, ...);
};

INIException::INIException(int argCount, const char *format, ...)
{
    m_argCount = argCount;
    mFailureMessage = 0;
    if (format != 0) {
        va_list args;
        va_start(args, format);
        int length = _vsnprintf(g_bfmeFormatBuffer, 2047, format, args);
        mFailureMessage = static_cast<char *>(bfmeArrayNew(length + 1));
        memcpy(mFailureMessage, g_bfmeFormatBuffer, length);
        mFailureMessage[length] = 0;
        va_end(args);
    }
}
