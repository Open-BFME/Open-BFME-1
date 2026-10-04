// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// MapMetaData::bfme_getDisplayName, retail 0x00451240 (212 bytes).
// The matched map-preview and quickmatch callers establish this identity.
// The count at +0x20 is the player count; append the retail L" (%d)" suffix.
// See targets/game/reverse/identity_evidence/map_display_name_00451240.md.

#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

inline UnicodeString::UnicodeString(void)
{
    m_text = 0;
}

inline UnicodeString::UnicodeString(const wchar_t *text)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(text);
}

inline UnicodeString::UnicodeString(const UnicodeString &other)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
        *(const StringBase<wchar_t> *)&other);
}

inline UnicodeString::~UnicodeString(void)
{
    ((StringBase<wchar_t> *)this)->releaseBuffer();
}

class MapMetaData
{
public:
    UnicodeString bfme_getBaseDisplayName(void);
    UnicodeString bfme_getDisplayName(void);

    char m_bfmePadAP[0x20];
    int m_numPlayers;
};

UnicodeString MapMetaData::bfme_getDisplayName(void)
{
    UnicodeString name = bfme_getBaseDisplayName();
    int count = m_numPlayers;
    if (count >= 2)
    {
        UnicodeString suffix;
        suffix.format(UnicodeString(L" (%d)"), count);
        const StringBase<unsigned short> *suffixBuffer =
            (const StringBase<unsigned short> *)&suffix;
        ((StringBase<unsigned short> *)&name)->concat(
            suffixBuffer->str(), suffixBuffer->getLength());
    }
    return name;
}
