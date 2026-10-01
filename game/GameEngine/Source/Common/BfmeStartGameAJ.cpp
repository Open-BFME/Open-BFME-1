// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: the start-game announcement at retail 0x00649DB0, 177 bytes.
// The room is marked closed, then the peer library is told to start with the
// game number as its message.

#include "ascii_string.h"

extern "C" void peerStartGameA(void *peer, const char *message, int reportIntention);

class BfmeRoomAJ
{
public:
	void bfmeSetAJ(const char *key, const char *value);

	char m_bfmePadRAJ[4];
};

class BfmeSessionAJ
{
public:
	void bfmeStartAJ(void *peer);

	char m_bfmePadAAJ[0x90];
	int m_bfmeNumberAJ;
	char m_bfmePadBAJ[0x2c];
	BfmeRoomAJ m_bfmeRoomAJ;
	char m_bfmePadCAJ[788];
	char m_bfmeStartedAJ;
};

void BfmeSessionAJ::bfmeStartAJ(void *peer)
{
	AsciiString message;

	message.format(AsciiString("%d"), m_bfmeNumberAJ);

	m_bfmeRoomAJ.bfmeSetAJ("closedplaying", "");

	peerStartGameA(peer, message.str(), 2);

	m_bfmeStartedAJ = 1;
}
