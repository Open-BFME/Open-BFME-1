// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport deque map initializer for the BFME PeerResponse payload.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <string>

class PeerResponse
{
public:
	int peerResponseType;
	std::string groupRoomName;
	std::string nick;
	std::string oldNick;
	std::wstring text;
	std::string locale;
	std::string stagingServerGameOptions;
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;
	union
	{
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

namespace _STL
{
template void _Deque_base<PeerResponse,
	allocator<PeerResponse> >::_M_initialize_map(unsigned int);
}
