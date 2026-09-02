// stlport
// Open-BFME5: STLport deque<PSRequest> destruction helper.

#include <deque>

class PSRequest
{
public:
	~PSRequest();

private:
	unsigned char m_data[0x210];
};

template class _STL::deque<PSRequest>;
