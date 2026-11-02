// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: GameSpyGroupRoom dtor. AsciiString @+0 then UnicodeString @+4.

#include "ascii_string.h"

#include "unicode_string.h"

// Retail inlines ~UnicodeString at every scope exit and calls
// StringBase<unsigned short>::releaseBuffer (0x008881D0) directly, never
// the 0x0005EEA0 jmp body the out-of-line declaration would bind to.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

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
