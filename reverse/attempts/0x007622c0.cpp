// ?d_007622c0@@YAXXZ
// partial score=0.9 date=2026-09-02
// candidate for retail 0x007622C0 (148B), currently ?d_007622c0@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// W3DModelDraw-family const accessor returning AsciiString by value (hidden
// pointer, thiscall, ret 4). Field pair at +0x28/+0x2c is an inline
// AsciiString array (begin/end, stride 4 == sizeof(AsciiString)). Empty ->
// AsciiString("") using the shared empty literal 0x0107301C; else the first
// element is copy-returned.

#include "StringInline.h"

class Gen_007622C0
{
public:
    AsciiString method() const;
private:
    unsigned char m_unreconstructed_00[0x28];
    int m_beginRaw; // +0x28
    int m_endRaw;   // +0x2c

    AsciiString *begin() const { return (AsciiString *)m_beginRaw; }
};

AsciiString Gen_007622C0::method() const
{
    int count = (m_endRaw - m_beginRaw) >> 2;
    if (count == 0) {
        AsciiString temp("");
        return temp;
    }
    return begin()[0];
}
