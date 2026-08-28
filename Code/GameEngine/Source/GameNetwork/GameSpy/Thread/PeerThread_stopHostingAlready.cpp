// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?stopHostingAlready@PeerThreadClass@@: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp
// Open-BFME: PeerThreadClass::stopHostingAlready, retail 0x0064C9E0, 96 bytes.
//
// The reference's body with one BFME line in the middle: after peerStopGame the
// thread's room name at this+0xC0 is set back to "openstaging", and a flag at
// this+0x3D8 is cleared.
//
// The three globals cleared first are the reference's own isThreadHosting,
// s_lastStateChangedHeartbeat and s_wantStateChangedHeartbeat, in that order and
// with those widths -- two dwords and a byte.
//
// closesocket is an import, so it is an indirect call through the IAT, and
// peerStopGame is cdecl.
#define _STLP_NO_EXCEPTIONS 1
#include <string>

typedef int Int;
typedef bool Bool;
typedef void *PEER;
typedef unsigned int SOCKET;

#define INVALID_SOCKET ((SOCKET)(~0))

extern "C" void peerStopGame(PEER peer);				// 0x00857E50
extern "C" __declspec(dllimport) int __stdcall closesocket(SOCKET s);

static Int isThreadHosting;
static Int s_lastStateChangedHeartbeat;
static Bool s_wantStateChangedHeartbeat;
static SOCKET qr2Sock = INVALID_SOCKET;

class PeerThreadClass
{
public:
	void stopHostingAlready(PEER peer);

private:
	unsigned char m_unmodelled_000[0xC0];
	_STL::string m_bfmeRoomName;					// this+0xC0
	unsigned char m_unmodelled_0d4[0x3D8 - 0xC0 - sizeof(_STL::string)];
	Bool m_bfmeHosting;						// this+0x3D8
};

void PeerThreadClass::stopHostingAlready(PEER peer)
{
	isThreadHosting = 0; // debugging
	s_lastStateChangedHeartbeat = 0;
	s_wantStateChangedHeartbeat = false;
	peerStopGame(peer);
	m_bfmeRoomName = "openstaging";
	m_bfmeHosting = false;
	if (qr2Sock != INVALID_SOCKET)
	{
		closesocket(qr2Sock);
		qr2Sock = INVALID_SOCKET;
	}
}
