// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: queue<PeerResponse>::push, retail 0x0064CB30, 64 bytes. The name
// was parked on the 5-byte thunk at 0x0003CE07.
//
// One line -- the queue forwards to its deque's push_back -- and STLport
// inlines that: if the last block still has room, construct in place and bump
// the cursor, otherwise hand off to _M_push_back_aux_v. The element stride is
// 0x330, which is what sizes PeerResponse here.
#define _STLP_NO_EXCEPTIONS 1
#include <queue>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerResponse
{
	char m_bfmeBody[0x330];					// the stride the cursor steps by
};

namespace _STL
{
// Not inlined in this build: the element is built through a call.
template <>
void _Construct(PeerResponse *p, const PeerResponse &val);
}

void BfmePeerResponseQueueAnchor(_STL::queue<PeerResponse> &q, const PeerResponse &value)
{
	q.push(value);
}
