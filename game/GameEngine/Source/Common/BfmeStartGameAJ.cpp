// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: the start-game announcement at retail 0x00649DB0, 177 bytes.
// The room is marked closed, then the peer library is told to start with the
// game number as its message. The room field at +0xC0 is an STLport string:
// retail pushes "closedplaying" and its end (+13) and calls ILT 0x0002B297 ->
// 0x000A5810, basic_string<char>::assign(const char *, const char *), which is
// what operator=(const char *) inlines to.

#include "ascii_string.h"
#include <string>

extern "C" void peerStartGameA(void *peer, const char *message, int reportIntention);

class BfmeSessionAJ
{
public:
	void bfmeStartAJ(void *peer);

	char m_bfmePadAAJ[0x90];
	int m_bfmeNumberAJ;
	char m_bfmePadBAJ[0x2c];
	_STL::string m_bfmeRoomAJ;				// +0xC0
	char m_bfmePadCAJ[780];
	char m_bfmeStartedAJ;
};

void BfmeSessionAJ::bfmeStartAJ(void *peer)
{
	AsciiString message;

	message.format(AsciiString("%d"), m_bfmeNumberAJ);

	m_bfmeRoomAJ = "closedplaying";

	peerStartGameA(peer, message.str(), 2);

	m_bfmeStartedAJ = 1;
}
