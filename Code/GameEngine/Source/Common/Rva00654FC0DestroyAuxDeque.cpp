// stlport
// Open-BFME5: STLport deque<PSRequest> destruction helper.

#include <deque>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSRequest
{
public:
	~PSRequest();

private:
	unsigned char m_data[0x210];
};

template class _STL::deque<PSRequest>;
