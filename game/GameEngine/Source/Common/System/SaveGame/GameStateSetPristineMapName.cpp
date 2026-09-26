// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// GameLogic::startNewGame calls this through ILT 0x0002A0DB at 0x00394435
// with TheGameState and GlobalData::m_mapName. The reference GameState.h
// setter and retail's char-string calls identify pristineMapName at +0x1C;
// the former NetChatCommandMsg/UnicodeString ledger alias named the wrong owner.

class AsciiString;

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
    ~AsciiString() {}

    AsciiString &operator=(const AsciiString &source)
    {
        StringBase<char>::set(source);
        return *this;
    }
};

class GameState
{
public:
    void setPristineMapName(AsciiString name);

private:
    char m_unrecovered[0x1C];
    AsciiString m_pristineMapName;
};

void GameState::setPristineMapName(AsciiString name)
{
    m_pristineMapName = name;
}
