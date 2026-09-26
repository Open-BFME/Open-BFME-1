// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Recovered from the Zero Hour PeerThread.h request layout.
// Copyright 2025 Electronic Arts Inc. Licensed under GPL-3.0-or-later.
//
// The matched PeerRequest deque push_back_aux (RVA 0x00648810) calls this
// copy constructor twice through ILT0x0003C308 -> 0x00647470, while allocating
// 0x194-byte elements. GameSpyPeerMessageQueue::getRequest at 0x0064C840
// names assignment through ILT0x000336A4 -> 0x00648C00. The string/vector prefix and opaque union copy spans
// reproduce that BFME layout without assigning meanings to unknown payloads.
// Keeping these views local leaves the shared reference headers unchanged.

#include <new>
#include <string>
#include <vector>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
static const Int MAX_SLOTS = 8;

class PeerRequest
{
public:

	int peerRequestType;
	std::string nick;
	std::wstring text;
	std::string password;
	std::string email;
	std::string id;
	std::string options;
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[MAX_SLOTS];
	std::vector<bool> qmMaps;

	union
	{
		struct { Int value; } payload0;
		struct { Int value; } payload1;
		struct { Int value; } payload2;
		struct { Bool value; } payload3;
		struct { Bool value; } payload4;
		struct { Int value; } payload5;
		struct { Int words[8]; } payload32;
		struct { Int words[44]; } payload176;
		struct { Bool value; } payload9;
		struct { Int words[23]; } payload92;
		struct { Int words[7]; } payload28;
		struct { Int words[2]; } payload8;
	};
};

typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 0x194 ? 1 : -1];

// forcePeerRequestCopy absent-from-retail: emission anchor for the implicit constructor.
PeerRequest *forcePeerRequestCopy(PeerRequest *destination, const PeerRequest &source)
{
    return new (destination) PeerRequest(source);
}

// Emit the implicit assignment without introducing a wrapper function.
PeerRequest &(PeerRequest::*forcePeerRequestAssignment)(const PeerRequest &) =
    &PeerRequest::operator=;
