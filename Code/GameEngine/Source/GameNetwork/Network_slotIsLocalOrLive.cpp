// cl: /DNDEBUG /MD /GX

// Retail 0x00681DF0, the last slot -- 57 -- of Network's vtable at 0x0111A968,
// past everything Zero Hour's NetworkInterface declares. It forwards to
// ?_bfme_slotIsLocalOrLive@ConnectionManager@@QAE_NH@Z, itself pinned in
// symbols.csv as "unidentified beyond its shape", so this name describes the
// body rather than recovering it.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool _bfme_slotIsLocalOrLive(Int slot);		// ILT thunk 0x0001F136
};

class Network
{
public:
	virtual Bool _bfme_isSlotLocalOrLive(Int slot);

protected:
	void *m_subsystemName;				// SubsystemInterface::m_name, +0x04
	ConnectionManager *m_conMgr;			// +0x08
};

Bool Network::_bfme_isSlotLocalOrLive(Int slot)
{
	if (m_conMgr != 0)
		return m_conMgr->_bfme_slotIsLocalOrLive(slot);

	return false;
}
