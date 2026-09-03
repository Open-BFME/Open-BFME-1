// stlport
// Open-BFME5: STLport deque<PSResponse> destruction helper.

#include <deque>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSResponse
{
public:
	~PSResponse();

private:
	unsigned char m_data[0x1f0];
};

template class _STL::deque<PSResponse>;
