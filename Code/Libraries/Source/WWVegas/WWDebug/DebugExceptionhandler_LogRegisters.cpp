// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Open-BFME: DebugExceptionhandler::LogRegisters, converted from the
// verified GeneralsMD debug exception implementation.

#include "windows.h"

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
        SetPrefixAndRadix((const char *)0x01132DD4, 16);
        return *this;
    }

    Debug &operator<<(const Dec &)
    {
        SetPrefixAndRadix((const char *)0x0107301C, 10);
        return *this;
    }

    Debug &operator<<(const Bin &)
    {
        SetPrefixAndRadix((const char *)0x01134280, 2);
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
        << (const char *)0x011343E4 << Debug::Width(8) << ctx.Eax
        << (const char *)0x011343DC << Debug::Width(8) << ctx.Ebx
        << (const char *)0x011343D4 << Debug::Width(8) << ctx.Ecx
        << (const char *)0x01080294
        << (const char *)0x011343CC << Debug::Width(8) << ctx.Edx
        << (const char *)0x011343C4 << Debug::Width(8) << ctx.Esi
        << (const char *)0x011343BC << Debug::Width(8) << ctx.Edi
        << (const char *)0x01080294
        << (const char *)0x011343B4 << Debug::Width(8) << ctx.Eip
        << (const char *)0x011343AC << Debug::Width(8) << ctx.Esp
        << (const char *)0x011343A4 << Debug::Width(8) << ctx.Ebp
        << (const char *)0x01080294
        << (const char *)0x0113439C << Debug::Bin() << Debug::Width(32) << ctx.EFlags
        << Debug::Hex() << (const char *)0x01080294
        << (const char *)0x01134398 << Debug::Width(4) << ctx.SegCs
        << (const char *)0x01134390 << Debug::Width(4) << ctx.SegDs
        << (const char *)0x01134388 << Debug::Width(4) << ctx.SegSs
        << (const char *)0x01134380 << Debug::Width(4) << ctx.SegEs
        << (const char *)0x01134378 << Debug::Width(4) << ctx.SegFs
        << (const char *)0x01134370 << Debug::Width(4) << ctx.SegGs
        << (const char *)0x01080294 << Debug::FillChar() << Debug::Dec();
}
