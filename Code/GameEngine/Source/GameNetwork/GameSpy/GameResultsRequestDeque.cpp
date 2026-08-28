// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: deque<GameResultsRequest>::_M_push_back_aux_v, retail 0x006420E0,
// 188 bytes. The name was parked on the 5-byte thunk at 0x0002217E.
//
// STLport's own body out of the real header: copy the element, reserve one
// more block at the back, construct into it and advance.
//
// The element is 0x1C bytes: the frame reserves 0x20, and the four over the
// element are the unwind state the temporary's destructor needs. It has a
// user-declared copy constructor, too -- the call at 0x006420FE takes the copy
// and the one at 0x0064215A builds the element in the new block, where a plain
// aggregate would have been a block move.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GameResultsThread.h
class GameResultsRequest
{
public:
	GameResultsRequest(const GameResultsRequest &other);
	~GameResultsRequest();

private:
	char m_bfmeBody[0x1C];					// what the frame reserves, less the state slot
};

void BfmeGameResultsRequestDequeAnchor(_STL::deque<GameResultsRequest> &d, const GameResultsRequest &value)
{
	d.push_back(value);
}
