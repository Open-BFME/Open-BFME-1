// ?d_00762380@@YAXXZ
// partial score=0.9 date=2026-09-02
// candidate for retail 0x00762380 (173B), currently ?d_00762380@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /O2 /Ireference/shims/stringinline
// Sibling of 0x007622C0: const accessor returning AsciiString by value
// (hidden pointer, thiscall(int index), ret 8). Same inline AsciiString
// array at +0x28(begin)/+0x2c(end). Empty -> AsciiString("") (literal
// 0x0107301C); a single element returns it directly; otherwise wraps the
// caller's index with count via unsigned division and returns that element.

#include "StringInline.h"

class Gen_00762380
{
public:
    AsciiString method(int index) const;
private:
    unsigned char m_unreconstructed_00[0x28];
    AsciiString *m_begin; // +0x28
    AsciiString *m_end;   // +0x2c
};

AsciiString Gen_00762380::method(int index) const
{
    AsciiString *begin = m_begin;
    int count = m_end - begin;
    if (count == 0) {
        AsciiString temp("");
        return temp;
    }
    if (count == 1)
        return m_begin[0];
    return m_begin[(unsigned int)index % (unsigned int)count];
}
