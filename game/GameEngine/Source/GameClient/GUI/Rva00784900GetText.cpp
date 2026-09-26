// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "unicode_string.h"

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
        *(const StringBase<unsigned short> *)&other);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other)
{
    ((StringBase<unsigned short> *)this)->set(
        *(const StringBase<unsigned short> *)&other);
    return *this;
}

class Rva00784900TextSource
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual UnicodeString getText();
};

class Rva00784900
{
public:
    UnicodeString getText();
private:
    unsigned char m_prefix[8];
    Rva00784900TextSource *m_source;
};

UnicodeString Rva00784900::getText()
{
    UnicodeString text;
    if (m_source)
        text = m_source->getText();
    return text;
}
