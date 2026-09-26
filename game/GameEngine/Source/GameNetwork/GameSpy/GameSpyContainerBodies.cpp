// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The STLport container bodies retail instantiated for the GameSpy worker
// queues, and the staging-room set the lobby sorts with. None of them is code
// anyone wrote: each is STLport's own body out of the real header, and all any
// file here supplies is the element type whose size and destructor the
// instantiation bakes in. That is why they belong together -- ten rows, seven
// element types, one prelude:
//
//   deque<PeerRequest>::pop_front            0x006486F0   stride 0x194
//   deque<PeerRequest>::_M_pop_front_aux     0x00647A30
//   deque<PSRequest>::pop_front              0x00656B60   stride 0x210
//   deque<PSResponse>::pop_front             0x00656BD0   stride 0x1F0
//   deque<PSResponse>::_M_pop_front_aux      0x006551E0
//   queue<PeerResponse>::push                0x0064CB30   stride 0x330
//   deque<PingRequest>::_M_push_back_aux_v   0x00660750   stride 0x14
//   deque<PingResponse>::_M_push_back_aux_v  0x00660880   stride 0x14
//   deque<PingRequest>::_M_reallocate_map    0x008FAA40
//   deque<GameResultsRequest>::_M_push_back_aux_v  0x006420E0  stride 0x1C
//
// Every one of these element classes is a stand-in: only the stride, the
// destructor and whether the copy is out of line are proven, so each keeps the
// note that says which of those its own body pins.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <queue>
#include <set>
#include <string>

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerRequest
{
public:
	~PeerRequest();						// ILT 0x00016BD5

private:
	char m_bfmeBody[0x194];					// the stride the cursors step by
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerResponse
{
	char m_bfmeBody[0x330];					// the stride the cursor steps by
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSRequest
{
public:
	~PSRequest();						// ILT 0x0001658B

private:
	char m_bfmeBody[0x210];					// the stride the cursors step by
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	~PSPlayerStats();					// retail 0x000A5150

private:
	char m_bfmeBody[0x1E8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PingThread.h
class PingRequest
{
	_STL::string m_bfmeText;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PingThread.h
class PingResponse
{
	_STL::string m_bfmeText;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GameResultsThread.h
class GameResultsRequest
{
public:
	GameResultsRequest(const GameResultsRequest &other);
	~GameResultsRequest();

private:
	char m_bfmeBody[0x1C];					// what the frame reserves, less the state slot
};

class GameSpyStagingRoom;

struct GameSortStruct
{
	bool operator()(GameSpyStagingRoom *left, GameSpyStagingRoom *right) const;
};

namespace _STL
{
// Not inlined in this build: the element is built through a call.
template <>
void _Construct(PeerResponse *p, const PeerResponse &val);

class DequePingRequestThunkShim
{
public:
	void push_back_aux(void const *x);
};

class DequePingResponseThunkShim
{
public:
	void push_back_aux(void const *x);
};

class DequePushBackAuxValueThunksShim
{
public:
	void push_back_aux(void const *x);
};

class Rva0002F6A3PingRequestThunk
{
public:
	void _M_push_back_aux_v(PingRequest const &value);
};

class Rva0003C650PingResponseThunk
{
public:
	void _M_push_back_aux_v(PingResponse const &value);
};

class Rva0002217EGameResultsRequestThunk
{
public:
	void _M_push_back_aux_v(GameResultsRequest const &value);
};

void Rva0002F6A3PingRequestThunk::_M_push_back_aux_v(PingRequest const &value)
{
	((DequePingRequestThunkShim *)this)->push_back_aux((void const *)&value);
}

void Rva0003C650PingResponseThunk::_M_push_back_aux_v(PingResponse const &value)
{
	((DequePingResponseThunkShim *)this)->push_back_aux((void const *)&value);
}

void Rva0002217EGameResultsRequestThunk::_M_push_back_aux_v(
	GameResultsRequest const &value)
{
	((DequePushBackAuxValueThunksShim *)this)->push_back_aux(
		(void const *)&value);
}
}

// deque<PeerRequest>::pop_front, retail 0x006486F0, 80 bytes: destroy the front
// element, and if that emptied the block, hand the block back and step the map
// on. The destructor call at 0x00648701 goes through the ILT at 0x00016BD5 to
// ??1PeerRequest@@QAE@XZ, which is what names the instantiation. The PSRequest
// name the ledger also carried here belongs to 0x00656B60 instead: that body
// steps by 0x210 and calls ??1PSRequest.
void BfmePeerRequestDequeAnchor(_STL::deque<PeerRequest> &d)
{
	d.pop_front();
}

// deque<PSRequest>::pop_front, retail 0x00656B60, 80 bytes. Its destructor call
// at 0x00656B71 goes through the ILT at 0x0001658B to ??1PSRequest@@QAE@XZ.
// The ledger had this body under the placeholder ?popFront@BFMENetworkQueue,
// and had ?pop_front@?$deque@VPSRequest@@... aliased onto the PeerRequest deque
// at 0x006486F0, whose element is 0x194 and whose destructor is PeerRequest's.
void BfmePSRequestDequeAnchor(_STL::deque<PSRequest> &d)
{
	d.pop_front();
}

// deque<PSResponse>::pop_front, retail 0x00656BD0, 80 bytes. The ledger had it
// under the placeholder ?popFront@BFMENetworkQueue1. The element's destructor
// is the eight-byte compiler thunk at 0x000A5640, which adds four to `this` and
// tail-jumps to ??1PSPlayerStats@@QAE@XZ -- the reference's PSResponse exactly:
// a response-type enum, then the PSPlayerStats it carries, then the preorder
// flag, so destroying one means destroying the stats at +4 and nothing else.
void BfmePSResponseDequeAnchor(_STL::deque<PSResponse> &d)
{
	d.pop_front();
}

// queue<PeerResponse>::push, retail 0x0064CB30, 64 bytes. The name was parked
// on the 5-byte thunk at 0x0003CE07. One line -- the queue forwards to its
// deque's push_back -- and STLport inlines that: if the last block still has
// room, construct in place and bump the cursor, otherwise hand off to
// _M_push_back_aux_v.
void BfmePeerResponseQueueAnchor(_STL::queue<PeerResponse> &q, const PeerResponse &value)
{
	q.push(value);
}

// deque<PingRequest>::_M_push_back_aux_v (236B at 0x00660750) and its
// PingResponse twin (236B at 0x00660880). Both names were parked on 5-byte
// thunks, at 0x0002F6A3 and 0x0003C650. The element's shape is in the copy the
// body takes: basic_string<char>'s copy constructor over the object's front,
// then two dwords from +0x0C and +0x10 -- a twelve-byte STLport string followed
// by two ints, exactly the twenty-byte temporary the frame reserves.
void BfmePingRequestDequeAnchor(_STL::deque<PingRequest> &d, const PingRequest &value)
{
	d.push_back(value);
}

void BfmePingResponseDequeAnchor(_STL::deque<PingResponse> &d, const PingResponse &value)
{
	d.push_back(value);
}

// deque<GameResultsRequest>::_M_push_back_aux_v, retail 0x006420E0, 188 bytes;
// the name was parked on the 5-byte thunk at 0x0002217E. The element is 0x1C
// bytes -- the frame reserves 0x20 and the four over the element are the unwind
// state the temporary's destructor needs -- and it has a user-declared copy
// constructor: the call at 0x006420FE takes the copy and the one at 0x0064215A
// builds the element in the new block, where a plain aggregate would have been
// a block move.
void BfmeGameResultsRequestDequeAnchor(_STL::deque<GameResultsRequest> &d, const GameResultsRequest &value)
{
	d.push_back(value);
}

// _Rb_tree<GameSpyStagingRoom *, GameSortStruct>::_M_insert, retail 0x0053F7E0,
// 191 bytes; the name was parked on a 5-byte thunk. The element is a pointer,
// so the value goes into the node with a plain store rather than the
// out-of-line _Construct the class-typed trees need, and the comparison is a
// call on the tree's own comparator subobject at this+8.
typedef _STL::set<GameSpyStagingRoom *, GameSortStruct> BfmeStagingRoomSet;

void BfmeStagingRoomSetAnchor(BfmeStagingRoomSet &rooms, GameSpyStagingRoom *room)
{
	rooms.insert(room);
}
