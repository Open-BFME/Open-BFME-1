// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// partial score=0.55 date=2026-09-24
// Caller 0x00441EBF supplies DisplayString in ECX, a UnicodeString record at
// [ESP+4], and the line start in EBX; row identity remains address-derived.
#include "string_base.h"

typedef int Int;

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(*(const StringBase<unsigned short> *)&other) {}
    UnicodeString(const UnicodeString &source, int start, int length)
        : StringBase<unsigned short>(*(const StringBase<unsigned short> *)&source, start, length) {}
    ~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

    void *header() const
    {
        return ((const StringBase<unsigned short> *)this)->m_data;
    }
};

class Rva0043E5C0Display
{
public:
    virtual void slot00() = 0;
    virtual void setText(UnicodeString text) = 0;
    virtual UnicodeString getText() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2C() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual void slot38() = 0;
    virtual void getSize(Int *width, Int *height) = 0;
    int __cdecl call(const UnicodeString &source);
};

struct Rva0043E5C0StringHeader
{
    int references;
    unsigned short length;
    unsigned short capacity;
    unsigned short data[1];
};

// ?call@Rva0043E5C0Display@@QAAHABVUnicodeString@@@Z
int __cdecl Rva0043E5C0Display::call(const UnicodeString &source)
{
    Rva0043E5C0Display *display = this;
    register int start;
    __asm {
        mov start, ebx
    }

    const Rva0043E5C0StringHeader *header =
        (const Rva0043E5C0StringHeader *)source.header();
    const unsigned short *cursor = (const unsigned short *)((const char *)header + 8 + start * 2);
    Int end = start;
    Int length = header ? header->length : 0;
    while (end < length && header && *cursor != 10) {
        ++end;
        ++cursor;
    }
    if (end <= start)
        return 0;

    UnicodeString previous = display->getText();
    display->setText(UnicodeString(source, start, end - start));
    Int width;
    Int height;
    display->getSize(&width, &height);
    display->setText(previous);
    return width;
}
