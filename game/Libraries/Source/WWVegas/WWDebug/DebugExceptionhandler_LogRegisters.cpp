// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Open-BFME: DebugExceptionhandler::LogRegisters, converted from the
// verified GeneralsMD debug exception implementation.

#include "windows.h"

// Retail string storage. These addresses contain separate NUL-terminated
// strings, not members of the preceding vtables in the address index.
// Match the existing declaration in GameEngine/Source/Common/BfmeConv492.cpp.
extern "C" unsigned char bfmeTextBME[];
extern "C" const char g_01132DD4[];
extern "C" const char g_01134280[];
extern "C" const char g_011343E4[];
extern "C" const char g_011343DC[];
extern "C" const char g_011343D4[];
extern "C" const char g_01080294[];
extern "C" const char g_011343CC[];
extern "C" const char g_011343C4[];
extern "C" const char g_011343BC[];
extern "C" const char g_011343B4[];
extern "C" const char g_011343AC[];
extern "C" const char g_011343A4[];
extern "C" const char g_0113439C[];
extern "C" const char g_01134398[];
extern "C" const char g_01134390[];
extern "C" const char g_01134388[];
extern "C" const char g_01134380[];
extern "C" const char g_01134378[];
extern "C" const char g_01134370[];

// This TU uses the BFME Debug interface as a local ABI view.  The retail
// exception logger dispatches the unsigned-long writer at +0x28, the string
// writer at +0x38, and SetPrefixAndRadix at +0x50.  The fields used by the
// inline manipulators are at +0x9f44/+0x9f48 in the BFME object.
class Debug
{
public:
    class Hex {};
    class Dec {};
    class Bin {};

    class Width
    {
        friend class Debug;
        int m_width;

    public:
        explicit Width(int width): m_width(width) {}
    };

    class FillChar
    {
        friend class Debug;
        char m_fill;

    public:
        explicit FillChar(char fill=' '): m_fill(fill) {}
    };

    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    // MSVC places this overload group in reverse declaration order.  These
    // are the retail slots +0x28 through +0x38; the three middle overloads
    // are part of the existing Debug interface and are not called here.
    virtual Debug &operator<<(const char *);
    virtual Debug &operator<<(int);
    virtual Debug &operator<<(unsigned);
    virtual Debug &operator<<(long);
    virtual Debug &operator<<(unsigned long);
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void SetPrefixAndRadix(const char *, int);

    Debug &operator<<(const Hex &)
    {
        SetPrefixAndRadix(g_01132DD4, 16);
        return *this;
    }

    Debug &operator<<(const Dec &)
    {
        SetPrefixAndRadix((const char *)bfmeTextBME, 10);
        return *this;
    }

    Debug &operator<<(const Bin &)
    {
        SetPrefixAndRadix(g_01134280, 2);
        return *this;
    }

    Debug &operator<<(const Width &width)
    {
        m_width = width.m_width;
        return *this;
    }

    Debug &operator<<(const FillChar &fill)
    {
        m_fillChar = fill.m_fill;
        return *this;
    }

private:
    unsigned char m_pad[0x9f40];
    int m_width;
    char m_fillChar;
};

class DebugExceptionhandler
{
    static void LogRegisters(Debug &, struct _EXCEPTION_POINTERS *);
};

// ?LogRegisters@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
void DebugExceptionhandler::LogRegisters(Debug &dbg, struct _EXCEPTION_POINTERS *exptr)
{
    struct _CONTEXT &ctx = *exptr->ContextRecord;

    dbg << Debug::FillChar('0')
        << Debug::Hex()
        << g_011343E4 << Debug::Width(8) << ctx.Eax
        << g_011343DC << Debug::Width(8) << ctx.Ebx
        << g_011343D4 << Debug::Width(8) << ctx.Ecx
        << g_01080294
        << g_011343CC << Debug::Width(8) << ctx.Edx
        << g_011343C4 << Debug::Width(8) << ctx.Esi
        << g_011343BC << Debug::Width(8) << ctx.Edi
        << g_01080294
        << g_011343B4 << Debug::Width(8) << ctx.Eip
        << g_011343AC << Debug::Width(8) << ctx.Esp
        << g_011343A4 << Debug::Width(8) << ctx.Ebp
        << g_01080294
        << g_0113439C << Debug::Bin() << Debug::Width(32) << ctx.EFlags
        << Debug::Hex() << g_01080294
        << g_01134398 << Debug::Width(4) << ctx.SegCs
        << g_01134390 << Debug::Width(4) << ctx.SegDs
        << g_01134388 << Debug::Width(4) << ctx.SegSs
        << g_01134380 << Debug::Width(4) << ctx.SegEs
        << g_01134378 << Debug::Width(4) << ctx.SegFs
        << g_01134370 << Debug::Width(4) << ctx.SegGs
        << g_01080294 << Debug::FillChar() << Debug::Dec();
}
