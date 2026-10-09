// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: GameState::isInSaveDirectory at retail RVA 0x0010F1E0.

#include "ascii_string.h"

// Retail inlines this prefix overload and the AsciiString/base destructors.
template <>
inline bool StringBase<char>::startsWithNoCase(const StringBase<char> &other) const
{
    const int length = other.m_data ? other.m_data->length : 0;
    const char *text = other.m_data ? &other.m_data->data[0] : "";
    return startsWithNoCase(text, length);
}

class GameState
{
public:
    AsciiString getSaveDirectory() const;
    bool isInSaveDirectory(const AsciiString &path) const;
};

bool GameState::isInSaveDirectory(const AsciiString &path) const
{
    return static_cast<const StringBase<char> &>(path).startsWithNoCase(getSaveDirectory());
}
