// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: GameSpyGroupRoom dtor. AsciiString @+0 then UnicodeString @+4.

#include "ascii_string.h"

#include "unicode_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyGroupRoom
{
public:
	~GameSpyGroupRoom();

private:
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

// ??1GameSpyGroupRoom@@QAE@XZ
GameSpyGroupRoom::~GameSpyGroupRoom()
{
}
