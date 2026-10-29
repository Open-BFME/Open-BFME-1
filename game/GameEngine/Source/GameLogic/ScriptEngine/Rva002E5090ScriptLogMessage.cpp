// cl: /O2 /DNDEBUG /MD /EHs-c- /Ob1 /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// Keep the call while exposing reverseFind's read-only buffer accesses.
// ?reverseFind@?$StringBase@D@@QBEPBDD@Z
template <typename T>
inline __declspec(noinline) const T *StringBase<T>::reverseFind(T c) const
{
    const T *start = m_data ? &m_data->data[0] : (const T *)"";
    const T *p = start + (m_data ? m_data->length : 0);
    while (p != start) {
        --p;
        if (*p == c) {
            return p;
        }
    }
    return 0;
}


extern void j_00017bd9();
class BFMERetailAsciiString
{
public:
    ~BFMERetailAsciiString();
};
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
    // The static's atexit teardown (0x00C6FE40, _$E2) jumps to the
    // out-of-line string destructor through its ILT 0x0000D828.
    __forceinline ~Rva002E5090StaticMessage()
    {
        ((BFMERetailAsciiString *)this)->~BFMERetailAsciiString();
    }
    void *m_data;
};

class ScriptEngine
{
public:
    void AppendDebugMessage(const AsciiString &message, bool forcePause);
};

// Retail 0x012ED5C8 is ?TheWritableGlobalData@@3PAVGlobalData@@A (data_rows.csv,
// Common/GlobalData.cpp); TheGlobalData was only a pin.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ( *(void **)&TheWritableGlobalData )
extern ScriptEngine *TheScriptEngine;

typedef void (__cdecl *Rva002E5090VoidCallback)(void);
extern "C" int __cdecl _atexit(Rva002E5090VoidCallback);
extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

// ?Rva002E5090ScriptLogMessage@@YAXPBD@Z
void __cdecl Rva002E5090ScriptLogMessage(const char *input)
{
    unsigned char enabled = ((unsigned char *)TheGlobalData)[0xa90];
    if (!enabled)
        return;

    static Rva002E5090StaticMessage storage;
    AsciiString &message = *(AsciiString *)&storage;
    const char *text = input;
    int length = text ? (int)strlen(text) : 0;
    StringBase<char> *base = (StringBase<char> *)&message;
    base->concat(text, length);

    if (message.getLength() > 0x50)
        goto scan;
    if (base->reverseFind('\n') == 0)
        return;

scan:
    const char *start = message.str();
    int currentLength = message.getLength();

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

    ScriptEngine *engine = TheScriptEngine;
    engine->AppendDebugMessage(message, false);
    base->clear();
}
