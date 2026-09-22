// ?rva0088D9B0@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
// partial score=0.998 date=2026-09-22
//
// 634 of the 635 retail bytes. ONE byte differs, at +0x20C: retail encodes the
// inner byte read as `movzx eax, byte ptr [edi + ebx]` (SIB base EDI, index
// EBX) and MSVC 7.1 emits `[ebx + edi]` (0f b6 04 3b against retail's
// 0f b6 04 1f). Register ROLES are already retail's -- EDI is the ten-byte
// slot pointer that `add edi,0xa` advances, EBX the 0..9 counter that
// `cmp ebx,0xa` bounds -- so this is the SIB base/index preference alone, the
// family docs/sib_lea_experiments.md measures and AGENTS.md warns may stay
// compiler-internal.
//
// Everything else is exact, including the 0xC frame, the dead `exptr` slot
// reused for the register counter, the [ebp-4] home the `_asm` forces for the
// slot pointer, both loop shapes, every manipulator store and all twenty-six
// Debug calls.
//
// Spent without moving that byte: slot[byte], *(slot+byte), *(loaded+byte),
// *(unsigned char *)(byte + (unsigned)slot), *((unsigned char *)((unsigned)slot
// + byte)), *(slot + (int)byte), loaded[byte & 0xff], a second copy indexed
// instead of the original, an `unsigned index = byte` intervening touch (the
// lever docs/sib_lea_experiments.md isolates), a `const unsigned char *at`
// reload inside the body, int / unsigned / unsigned long counters, `!=` and
// do-while loop forms, a 10-byte struct slot with `slot++` and
// `slot->m_bytes[byte]`, splitting `dbg << Width(2)` into its own statement,
// moving the asm copy above and below the loop, and the
// /G5 /G6 /G7 /Ot /Os flag sweep. tools/shape_family_levers.py --families sib
// reports no applicable source-level lever for this body.
//
// Land it by fixing that one byte; do not rewrite the body.
//
// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Open-BFME: retail 0x0088D9B0, the FPU half of the debug exception dump.
//
// Same private static ABI as the landed LogRegisters at 0x0088E340 -- cdecl,
// a Debug reference and an EXCEPTION_POINTERS pointer -- and the same Debug
// interface view: the double writer at +0x1C, the unsigned-long writer at
// +0x28, the unsigned writer at +0x30, the int writer at +0x34, the string
// writer at +0x38 and SetPrefixAndRadix at +0x50, with the manipulator fields
// at +0x9F44/+0x9F48. The body prints the control, status and tag words in
// binary, the error and data pointers and Cr0NpxState in hex, then each of the
// eight ST slots as its ten raw bytes followed by its value.
//
// Nothing in the image names the method, so the address stays in the name.
//
// The one `_asm` block is a codegen blocker, not a lift: an ST slot is an
// 80-bit extended double and MSVC 7.1's `long double` is 64 bits, so no C++
// expression loads it. The rest of the body is ordinary C++.

#include "windows.h"

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

class DebugExceptionhandler
{
    static void rva0088D9B0(Debug &, struct _EXCEPTION_POINTERS *);
};

// ?rva0088D9B0@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
void DebugExceptionhandler::rva0088D9B0(Debug &dbg, struct _EXCEPTION_POINTERS *exptr)
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

    unsigned reg = 0;
    unsigned char *slot = ctx.FloatSave.RegisterArea;

    while (reg < 8)
    {
        dbg << Debug::Dec() << (const char *)0x01134288 << reg << (const char *)0x01134284;
        dbg << Debug::RawHex();

        unsigned char *loaded = slot;

        for (unsigned byte = 0; byte < 10; byte++)
            dbg << Debug::Width(2) << *(loaded + byte);

        double value;
        _asm
        {
            mov eax, loaded
            fld tbyte ptr [eax]
            fstp value
        }

        dbg << (const char *)0x0108ED1C << value << (const char *)0x01080294;

        reg++;
        slot += 10;
    }

    dbg << Debug::FillChar() << Debug::Dec();
}
