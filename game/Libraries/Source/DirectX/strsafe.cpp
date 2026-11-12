// cl: /O1 /G6 /MT /DNDEBUG
// Independent C++ reconstruction of the Summer2003 DXErr9 strsafe routines.
// The VS2003 SDK header supplies the public ABI/control-flow cross-check only;
// no SDK header or implementation is included. Native archive proof:
// targets/game/reverse/identity_evidence/dxerr9-summer2003-strsafe.md
#include <stddef.h>
#include <stdarg.h>

long __stdcall StringCopyWorkerW(wchar_t* destination, unsigned int capacity,
                               const wchar_t* source)
{
    long result = 0;
    if (capacity == 0)
        result = (long)0x80070057;
    else {
        for (; capacity && *source; --capacity)
            *destination++ = *source++;
        if (capacity == 0) {
            --destination;
            result = (long)0x8007007a;
        }
        *destination = 0;
    }
    return result;
}

long __stdcall StringCopyWorkerA(char*, unsigned int, const char*);
long __stdcall StringVPrintfWorkerA(char*, unsigned int, const char*, va_list);
long __stdcall StringVPrintfWorkerW(wchar_t*, unsigned int, const wchar_t*, va_list);

long __stdcall StringCchCopyA(char* destination, unsigned int capacity, const char* source)
{
    if (capacity > 0x7fffffffU)
        return (long)0x80070057;
    return StringCopyWorkerA(destination, capacity, source);
}

long __stdcall StringCchCopyW(wchar_t* destination, unsigned int capacity, const wchar_t* source)
{
    if (capacity > 0x7fffffffU)
        return (long)0x80070057;
    return StringCopyWorkerW(destination, capacity, source);
}

long __cdecl StringCchPrintfA(char* destination, unsigned int capacity, const char* format, ...)
{
    if (capacity > 0x7fffffffU)
        return (long)0x80070057;
    va_list arguments;
    va_start(arguments, format);
    long result = StringVPrintfWorkerA(destination, capacity, format, arguments);
    va_end(arguments);
    return result;
}

long __cdecl StringCchPrintfW(wchar_t* destination, unsigned int capacity, const wchar_t* format, ...)
{
    if (capacity > 0x7fffffffU)
        return (long)0x80070057;
    va_list arguments;
    va_start(arguments, format);
    long result = StringVPrintfWorkerW(destination, capacity, format, arguments);
    va_end(arguments);
    return result;
}
