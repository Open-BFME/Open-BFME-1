// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: deque<PSResponse>::pop_front, retail 0x00656BD0, 80 bytes. The
// ledger had it under the placeholder ?popFront@BFMENetworkQueue1.
//
// The element is 0x1F0 bytes and its destructor is the eight-byte compiler
// thunk at 0x000A5640, which adds four to `this` and tail-jumps to
// ??1PSPlayerStats@@QAE@XZ. That is the reference's PSResponse exactly: a
// response-type enum, then the PSPlayerStats it carries, then the preorder
// flag -- destroying a PSResponse means destroying the stats at +4 and nothing
// else.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	~PSPlayerStats();					// retail 0x000A5150

private:
	char m_bfmeBody[0x1E8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSResponse
{
public:
	enum
	{
		PSRESPONSE_PLAYERSTATS,
		PSRESPONSE_COULDNOTCONNECT,
		PSRESPONSE_PREORDER,
		PSRESPONSE_MAX
	} responseType;

	PSPlayerStats player;

	Bool preorder;
};

void BfmePSResponseDequeAnchor(_STL::deque<PSResponse> &d)
{
	d.pop_front();
}
