// cl: /DNDEBUG /MD /GX

// Retail 0x00681DF0, the last slot -- 57 -- of Network's vtable at 0x0111A968,
// past everything Zero Hour's NetworkInterface declares. It forwards to
// ILT 0x0001F136 -> 0x00662A50, the matched
// BFMEConnectionManager::isPlayerConnectedDefaultTimeout (native_connection_timing.cpp);
// this method name still describes the body rather than recovering it.

typedef int Int;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class BFMEConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(Int slot);		// ILT thunk 0x0001F136
};

class Network
{
public:
	virtual Bool _bfme_isSlotLocalOrLive(Int slot);

protected:
	void *m_subsystemName;				// SubsystemInterface::m_name, +0x04
	BFMEConnectionManager *m_conMgr;			// +0x08
};

Bool Network::_bfme_isSlotLocalOrLive(Int slot)
{
	if (m_conMgr != 0)
		return m_conMgr->isPlayerConnectedDefaultTimeout(slot);

	return false;
}
