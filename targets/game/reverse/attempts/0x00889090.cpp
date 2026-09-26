// ??0AsciiString@@QAE@ABVUnicodeString@@@Z
// partial score=1.0 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <wchar.h>
#include "string_base.h"

template <>
inline StringBase<char>::StringBase()
{
    m_data = 0;
}

class UnicodeString
{
public:
    struct Header
    {
        int refs;
        unsigned short length;
        unsigned short capacity;
        wchar_t data[1];
    };
    Header *m_data;
    const wchar_t *str() const { return m_data ? &m_data->data[0] : L""; }
};

class AsciiString : public StringBase<char>
{
public:
    AsciiString(const char *str) : StringBase<char>(str) {}
    AsciiString(const UnicodeString &str);
    ~AsciiString();
    void __cdecl format(AsciiString fmt, ...);
};

AsciiString::AsciiString(const UnicodeString &str) : StringBase<char>()
{
    format(AsciiString("%ls"), str.str());
}
