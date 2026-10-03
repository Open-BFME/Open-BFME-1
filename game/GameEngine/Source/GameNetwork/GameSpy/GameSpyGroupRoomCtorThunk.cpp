// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: GameSpyGroupRoom default ctor. AsciiString @+0 then
// UnicodeString @+4 (no gap between them in this ctor's own evidence -- the
// UnicodeString::set() call below runs with this==&m_name+4), then five
// zero-initialised Int fields packed at +8..+0x18.
#include "ascii_string.h"
#include "unicode_string.h"

// The retail constructor inlines these canonical wide-string operations.
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
	((StringBase<unsigned short> *)this)->set(
		*(const StringBase<unsigned short> *)&that);
	return *this;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom();
private:
	AsciiString m_name;
	UnicodeString m_translatedName;
	int m_groupID;
	int m_numWaiting;
	int m_maxWaiting;
	int m_numGames;
	int m_numPlaying;
};

// ??0GameSpyGroupRoom@@QAE@XZ
GameSpyGroupRoom::GameSpyGroupRoom()
{
	m_name = AsciiString::TheEmptyString;
	m_translatedName = UnicodeString::TheEmptyString;
	m_groupID = m_numWaiting = m_maxWaiting = m_numGames = m_numPlaying = 0;
}
