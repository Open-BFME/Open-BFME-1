// Open-BFME: DebugExceptionhandler::LogFPURegisters, retail 0x0088D9B0.
// ExceptionFilter at 0x0088E5F0 calls this after LogRegisters. The Zero Hour
// source names the method and confirms the FPU fields and print order.
// BFME calls Debug stream methods through vtable offsets +0x38 and +0x50.
// Zero Hour's debug.h declares those methods nonvirtual and omits RawHex, so
// this file declares the Debug interface used by the retail body.
// cl: /DNDEBUG /MD /EHs-c- /Oy-

#include "windows.h"

// This shim declares the BFME virtual slots and manipulator fields used below.
class Debug
{
public:
    class Hex {};
    class RawHex {};
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
    // MSVC places this overload group at the first overload's slot and fills
    // it in reverse declaration order, so these are the retail slots +0x1C
    // through +0x38.
    virtual Debug &operator<<(const char *);
    virtual Debug &operator<<(int);
    virtual Debug &operator<<(unsigned);
    virtual Debug &operator<<(long);
    virtual Debug &operator<<(unsigned long);
    virtual Debug &operator<<(short);
    virtual Debug &operator<<(float);
    virtual Debug &operator<<(double);
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

    Debug &operator<<(const RawHex &)
    {
        SetPrefixAndRadix((const char *)0x0107301C, 16);
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

#include "internal_except.h"

// ?LogFPURegisters@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
void DebugExceptionhandler::LogFPURegisters(Debug &dbg, struct _EXCEPTION_POINTERS *exptr)
{
    struct _CONTEXT &ctx = *exptr->ContextRecord;

    if ((ctx.ContextFlags & (CONTEXT_i386 | CONTEXT_FLOATING_POINT)) == 0)
    {
        dbg << (const char *)0x011342E0;
        return;
    }

    dbg << Debug::Bin() << Debug::FillChar('0')
        << (const char *)0x011342DC << Debug::Width(16) << (ctx.FloatSave.ControlWord & 0xffff)
        << (const char *)0x01080294
        << (const char *)0x011342D8 << Debug::Width(16) << (ctx.FloatSave.StatusWord & 0xffff)
        << (const char *)0x01080294
        << (const char *)0x011342D4 << Debug::Width(16) << (ctx.FloatSave.TagWord & 0xffff)
        << (const char *)0x01080294
        << Debug::Hex()
        << (const char *)0x011342C4 << Debug::Width(8) << ctx.FloatSave.ErrorOffset
        << (const char *)0x011342B8 << Debug::Width(8) << ctx.FloatSave.ErrorSelector
        << (const char *)0x01080294
        << (const char *)0x011342A8 << Debug::Width(8) << ctx.FloatSave.DataOffset
        << (const char *)0x0113429C << Debug::Width(8) << ctx.FloatSave.DataSelector
        << (const char *)0x01080294
        << (const char *)0x0113428C << Debug::Width(8) << ctx.FloatSave.Cr0NpxState
        << (const char *)0x01080294;

    for (unsigned reg = 0; reg < 8; ++reg)
    {
        dbg << Debug::Dec() << (const char *)0x01134288 << reg << (const char *)0x01134284;
        dbg << Debug::RawHex();

        unsigned char *loaded = ctx.FloatSave.RegisterArea + reg * 10;

        for (unsigned byte = 0; byte < 10; ++byte)
            dbg << Debug::Width(2) << loaded[byte];

        // Windows stores each FPU value in 80 bits.
        // MSVC 7.1 treats long double as 64 bits.
        double value;
        _asm
        {
            mov eax, loaded
            fld tbyte ptr [eax]
            fstp value
        }

        dbg << (const char *)0x0108ED1C << value << (const char *)0x01080294;

    }

    dbg << Debug::FillChar() << Debug::Dec();
}
