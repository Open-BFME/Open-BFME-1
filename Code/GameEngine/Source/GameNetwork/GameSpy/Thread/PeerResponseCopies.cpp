// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Recovered from the PeerResponse layout in the Zero Hour PeerThread.h.
// Copyright 2025 Electronic Arts Inc. Licensed under GPL-3.0-or-later.
//
// The matched GameSpyPeerMessageQueue::getResponse at RVA 0x0064C910 calls
// this assignment through ILT 0x00003E86 -> 0x004F68C0. The complete 537-byte
// body ends at RET 4 (0x004F6AD6), then INT3 padding; Ghidra's 534-byte range
// omitted that return. The string prefix ends at +0xF4. BFME's union members
// differ from Zero Hour: the copy spans below preserve their observed sizes
// and declaration order without assigning meanings to unrecovered payloads.
// The largest member makes sizeof(PeerResponse) 0x330, independently confirmed
// by the matched PeerResponse deque push/pop bodies.
//
// MSVC 7.1's generated assignment visits each union member. Taking its address
// emits the assignment. The separate copy-construction emission anchor below
// is not a claimed retail function. The matched deque push_back_aux at
// RVA 0x00648920 names the 426-byte copy ctor through ILT0x0001E74F.
#include <string>
#include <new>
static const int MAX_SLOTS = 8;
class PeerResponse
{
public:
	int peerResponseType;

	std::string groupRoomName; // can't be in union

	std::string nick;   // can't be in a union
	std::string oldNick;   // can't be in a union
	std::wstring text;  // can't be in a union
	std::string locale; // can't be in a union

	std::string stagingServerGameOptions; // full string from UTMs

	// game opts sent with PEERRESPONSE_STAGINGROOM
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;

	// game opts sent with PEERRESPONSE_STAGINGROOMPLAYERINFO
	std::string stagingRoomPlayerNames[MAX_SLOTS];

	std::string command;
	std::string commandOptions;

    union {
        struct { int value; } payloadWord0;
        struct { int reason; } payloadWord1;
        struct { int words[8]; } payload32;
        struct { int id; bool ok; } payload8a;
        struct { int result; } payload4;
        struct { int id; bool ok; bool isHostPresent; int result; } payload12;
        struct { bool isPrivate; bool isAction; int profileID; } payload8b;
        struct { int words[143]; } payload572;
        struct { int words[53]; } payload212;
        struct { int words[48]; } payload192;
    };
};
typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

PeerResponse & (PeerResponse::*forcePeerResponseAssignment)(const PeerResponse &) = &PeerResponse::operator=;

// forcePeerResponseCopy absent-from-retail: emission anchor for the implicit constructor.
PeerResponse *forcePeerResponseCopy(PeerResponse *where, const PeerResponse &other)
{
    return new (where) PeerResponse(other);
}
