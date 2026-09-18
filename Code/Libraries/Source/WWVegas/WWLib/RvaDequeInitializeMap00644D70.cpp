// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport deque map initializer for the BFME PeerRequest payload.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
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

namespace _STL
{
template void _Deque_base<PeerRequest,
	allocator<PeerRequest> >::_M_initialize_map(unsigned int);
}
