// stlport
// Open-BFME5: STLport deque<PSResponse> destruction helper.

#include <deque>

class PSResponse
{
public:
	~PSResponse();

private:
	unsigned char m_data[0x1f0];
};

template class _STL::deque<PSResponse>;
