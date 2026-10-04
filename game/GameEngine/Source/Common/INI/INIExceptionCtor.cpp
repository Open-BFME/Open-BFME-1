// cl: /DNDEBUG /MD /O2
// Retail RVA 0x00850600 is the 103-byte INIException(int, const char *, ...)
// constructor. The formatter writes the retail global at VA 0x0130C650 and
// imports _vsnprintf through IAT VA 0x01359360.
#include <stdarg.h>
#include <string.h>

extern char g_bfmeFormatBuffer[2048];
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
// The allocation helper at retail VA 0x00881F70 is operator new[], matched as
// ??_U@YAPAXI@Z in game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp; __identifier
// names that symbol directly instead of a private alias for it.
extern "C" void *__identifier("??_U@YAPAXI@Z")(unsigned int);

void __cdecl operator delete[](void *);

// Retail's ThrowInfo for INIException (RVA 0xDDFC30) names 0x00061BD0 as the
// unwind destructor and its catchable type names 0x00048621 (an ILT to
// 0x00061BB0) as the copy constructor.  The copy constructor zeroes the
// message pointer and hands the source to the one-argument callee at
// 0x00850670, whose identity is not recovered (pinned as
// Rva00061BB0Owner::attach), so it is reached through that class.
class INIException;

class Rva00061BB0Owner
{
    friend class INIException;
    void attach(void *source);
};

class INIException
{
public:
    char *mFailureMessage;
    int m_argCount;
    INIException(int argCount, const char *format, ...);
    INIException(const INIException &that);
    ~INIException();
};

INIException::INIException(int argCount, const char *format, ...)
{
    m_argCount = argCount;
    mFailureMessage = 0;
    if (format != 0) {
        va_list args;
        va_start(args, format);
        int length = _vsnprintf(g_bfmeFormatBuffer, 2047, format, args);
        mFailureMessage = static_cast<char *>(__identifier("??_U@YAPAXI@Z")(length + 1));
        memcpy(mFailureMessage, g_bfmeFormatBuffer, length);
        mFailureMessage[length] = 0;
        va_end(args);
    }
}

INIException::INIException(const INIException &that)
{
    mFailureMessage = 0;
    reinterpret_cast<Rva00061BB0Owner *>(this)->attach(const_cast<INIException *>(&that));
}

INIException::~INIException()
{
    ::operator delete[](mFailureMessage);
}
