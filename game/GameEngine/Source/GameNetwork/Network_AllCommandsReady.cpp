// cl: /DNDEBUG /MD /GX

// Retail 0x006822A0, Network::AllCommandsReady(UnsignedInt frame).
//
// Zero Hour's body returns TRUE when m_conMgr is null, when m_localStatus is
// PREGAME, or when it is POSTGAME (4); BFME parks LEFT (3) in that slot via
// quitGame (0x006822E0) and otherwise delegates to
// BFMEConnectionManager::areFrameCommandsComplete (0x006633E0). The connection
// manager pointer the slow path uses lives at this+0x30, not this+0x08.

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NetLocalStatus
{
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT
};

class BFMEConnectionManager
{
public:
	Bool areFrameCommandsComplete(unsigned int frame, Bool debugSpewage);
};

class Network
{
public:
	Bool AllCommandsReady(UnsignedInt frame);

private:
	void *m_vptr;					// retail vtable at +0x00
	char m_subsystemPad[4];				// SubsystemInterface::m_name at +0x04
	BFMEConnectionManager *m_conMgr;		// +0x08
	NetLocalStatus m_localStatus;			// +0x0C
	char m_perfAndTiming[0x20];			// +0x10 .. +0x2F
	BFMEConnectionManager *m_activeConMgr;		// +0x30
};

Bool Network::AllCommandsReady(UnsignedInt frame)
{
	if (m_activeConMgr == 0)
		return true;

	if (m_localStatus == NETLOCALSTATUS_PREGAME)
		return true;

	if (m_localStatus == NETLOCALSTATUS_LEFT)
		return true;

	return m_activeConMgr->areFrameCommandsComplete(frame, false);
}
