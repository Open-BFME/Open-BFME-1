// stlport
// Open-BFME5: STLport deque<PeerResponse> destruction helper.

#include <deque>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerResponse
{
public:
	~PeerResponse();

private:
	unsigned char m_data[0x330];
};

template class _STL::deque<PeerResponse>;
