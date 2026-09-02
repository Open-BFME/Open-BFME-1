// stlport
// Open-BFME5: STLport deque<PeerResponse> destruction helper.

#include <deque>

class PeerResponse
{
public:
	~PeerResponse();

private:
	unsigned char m_data[0x330];
};

template class _STL::deque<PeerResponse>;
