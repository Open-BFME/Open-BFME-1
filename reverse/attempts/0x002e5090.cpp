// ?Rva002E5090ScriptLogMessage@@YAXPBD@Z
// partial score=0.79 date=2026-09-23
// ?Rva002E5090ScriptLogMessage@@YAXPBD@Z
// cl: /O2 /DNDEBUG /MD /EHs-c- /Ob1 /ICode/Libraries/Source/WWVegas/WWLib
#define private public
#include "ascii_string.h"
#undef private

extern void j_00017bd9();
struct Rva002E5090CtorCall {};
typedef void (Rva002E5090CtorCall::*Rva002E5090Ctor)(void);
template<class P> __forceinline P Rva002E5090CtorPointer(void (*function)(void))
{
    union { void (*raw)(void); P member; } pointer;
    pointer.raw = function;
    return pointer.member;
}
class Rva002E5090StaticMessage
{
public:
    __forceinline Rva002E5090StaticMessage()
    {
        (reinterpret_cast<Rva002E5090CtorCall *>(this)->*Rva002E5090CtorPointer<Rva002E5090Ctor>(j_00017bd9))();
    }
    __forceinline ~Rva002E5090StaticMessage()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }
    void *m_data;
};

class ScriptEngine002E5090
{
public:
    void AppendDebugMessage(const AsciiString &message, bool forcePause);
};

typedef void (__cdecl *Rva002E5090VoidCallback)(void);
extern "C" int __cdecl _atexit(Rva002E5090VoidCallback);
extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

__forceinline int Rva002E5090MessageLength(const AsciiString &message)
{
    const StringBase<char> *base = (const StringBase<char> *)&message;
    return base->m_data != 0 ? base->m_data->length : 0;
}

void __cdecl Rva002E5090ScriptLogMessage(const char *input)
{
    unsigned char enabled = (*(unsigned char **)0x012ed5c8)[0xa90];
    if (!enabled)
        return;

    static Rva002E5090StaticMessage storage;
    AsciiString &message = *(AsciiString *)&storage;
    const char *text = input;
    int length = text ? (int)strlen(text) : 0;
    StringBase<char> *base = (StringBase<char> *)&message;
    base->concat(text, length);
    StringBase<char>::Header *data = base->m_data;

    if (Rva002E5090MessageLength(message) > 0x50)
        goto scan;
    if (base->reverseFind('\n') == 0)
        return;

scan:
    const char *start;
    int currentLength;
    if (data != 0)
    {
        currentLength = data->length;
        start = data->data;
    }
    else
    {
        currentLength = 0;
        start = "";
    }

    const char *end = start + currentLength;
    while (end != start)
    {
        --end;
        if (*end == '\n')
        {
            base->removeLastChar();
            break;
        }
    }

    ScriptEngine002E5090 *engine = *(ScriptEngine002E5090 **)0x012f076c;
    engine->AppendDebugMessage(message, false);
    base->releaseBuffer();
}
