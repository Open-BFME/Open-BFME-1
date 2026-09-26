// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: GameSpyInfo::setPingString

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefsImplementation.h
class GameSpyInfo
{
public:
	virtual void setPingString(const AsciiString &ping);

private:
	unsigned char m_pad[0x10];
	AsciiString m_ping;
};

// ?setPingString@GameSpyInfo@@UAEXABVAsciiString@@@Z
void GameSpyInfo::setPingString(const AsciiString &ping)
{
	m_ping = ping;
}
