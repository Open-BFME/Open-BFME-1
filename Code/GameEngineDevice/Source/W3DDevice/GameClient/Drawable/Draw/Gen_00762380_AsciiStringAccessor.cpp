// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// 0x00762380, 173 bytes, ret 8: return an element from the inline
// AsciiString range at +0x28/+0x2c, wrapping indices for a range larger than
// one element.  The retail owner and source-level method name are not
// recovered; this address-derived class preserves the proven layout.

#include "StringInline.h"

class Gen_00762380_AsciiStringVector
{
public:
    int size() const { return m_end - m_begin; }
    AsciiString &operator[](unsigned int index) const { return m_begin[index]; }

    AsciiString *m_begin;
    AsciiString *m_end;
};

class Gen_00762380
{
public:
    AsciiString method(int index) const;

private:
    unsigned char m_unreconstructed_00[0x28];
    Gen_00762380_AsciiStringVector m_items; // +0x28
};

AsciiString Gen_00762380::method(int index) const
{
    int count = m_items.size();
    if (count == 0)
    {
        AsciiString temp("");
        return temp;
    }
    if (count == 1)
        return m_items[0];
    return m_items[(unsigned int)index % (unsigned int)count];
}
