// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: deque<PeerRequest>::pop_front, retail 0x006486F0, 80 bytes.
//
// STLport's own body out of the real header: destroy the front element, and if
// that emptied the block, hand the block back and step the map on.
//
// The element is 0x194 bytes -- both cursor arithmetics use it -- and the
// destructor call at 0x00648701 goes through the ILT at 0x00016BD5 to
// ??1PeerRequest@@QAE@XZ, which is what names the instantiation. The PSRequest
// name the ledger also carried here belongs to 0x00656B60 instead: that body
// steps by 0x210 and calls ??1PSRequest.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerRequest
{
public:
	~PeerRequest();						// ILT 0x00016BD5

private:
	char m_bfmeBody[0x194];					// the stride the cursors step by
};

void BfmePeerRequestDequeAnchor(_STL::deque<PeerRequest> &d)
{
	d.pop_front();
}
