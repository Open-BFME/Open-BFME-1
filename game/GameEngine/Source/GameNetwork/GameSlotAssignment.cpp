// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other)
{
    ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&other);
    return *this;
}
// BFME-specific GameSlot layout; ZH omits the narrow string at +2c.
// See identity_evidence/004f08c0-assignment-extent.md.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot {
public:
    virtual void reset();
    GameSlot &operator=(const GameSlot &other);
private:
    int m_state;
    bool m_isAccepted, m_hasMap, m_isMuted;
    int m_color, m_startPos, m_playerTemplate, m_teamNumber;
    int m_origColor, m_origStartPos, m_origPlayerTemplate;
    UnicodeString m_name;
    AsciiString m_rva004F08C0_field2c;
    unsigned int m_IP;
    unsigned int m_rva004F08C0_field34, m_rva004F08C0_field38;
    unsigned int m_lastFrameInGame;
    bool m_disconnected;
};
GameSlot &GameSlot::operator=(const GameSlot &other)
{
    m_state = other.m_state;
    m_isAccepted = other.m_isAccepted;
    m_hasMap = other.m_hasMap;
    m_isMuted = other.m_isMuted;
    m_color = other.m_color;
    m_startPos = other.m_startPos;
    m_playerTemplate = other.m_playerTemplate;
    m_teamNumber = other.m_teamNumber;
    m_origColor = other.m_origColor;
    m_origStartPos = other.m_origStartPos;
    m_origPlayerTemplate = other.m_origPlayerTemplate;
    m_name = other.m_name;
    m_rva004F08C0_field2c = other.m_rva004F08C0_field2c;
    m_IP = other.m_IP;
    m_rva004F08C0_field34 = other.m_rva004F08C0_field34;
    m_rva004F08C0_field38 = other.m_rva004F08C0_field38;
    m_lastFrameInGame = other.m_lastFrameInGame;
    m_disconnected = other.m_disconnected;
    return *this;
}
