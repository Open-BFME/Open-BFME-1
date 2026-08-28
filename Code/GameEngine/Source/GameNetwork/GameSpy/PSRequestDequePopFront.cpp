// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: deque<PSRequest>::pop_front, retail 0x00656B60, 80 bytes.
//
// STLport's own body out of the real header: destroy the front element, and
// when that empties the block, hand the block back and step the map on. The
// element is 0x210 bytes -- both cursor arithmetics carry it -- and the
// destructor call at 0x00656B71 goes through the ILT at 0x0001658B to
// ??1PSRequest@@QAE@XZ, which is what names the instantiation.
//
// The ledger had this body under the placeholder ?popFront@BFMENetworkQueue,
// and had ?pop_front@?$deque@VPSRequest@@... aliased onto the PeerRequest
// deque at 0x006486F0, whose element is 0x194 and whose destructor is
// PeerRequest's. This is the body that name belongs to.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSRequest
{
public:
	~PSRequest();						// ILT 0x0001658B

private:
	char m_bfmeBody[0x210];					// the stride the cursors step by
};

void BfmePSRequestDequeAnchor(_STL::deque<PSRequest> &d)
{
	d.pop_front();
}
