// ?RelayCommandsToCommandList@Network@@IAEXXZ
// partial score=0.92 date=2026-09-03
// cl: /DNDEBUG /MD /GX
//
// Network::RelayCommandsToCommandList, 0x00682A90, 375 bytes.
//
// Named by the already-matched Network::update (0x00682C70) which calls this
// at 0x00682CBC, and by the reloc-named pin. Zero Hour's
// RelayCommandsToCommandList(frame) with the frame read from TheGameLogic+0x3C
// and processFrameSynchronizedNetCommand inlined. Type 4 GAMECOMMAND appends
// constructGameMessage; type 10 PLAYERLEAVE records the router's own leave
// frame at Network+0x38 or beginPlayerLeave; type 11 DESTROYPLAYER is
// processDestroyPlayerCommand. The BFME tail fires the router's own leave
// once every connected player has reached that frame.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

enum NetLocalStatus
{
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT
};

enum NetCommandType
{
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11
};

class GameMessage;

class CommandList
{
public:
	virtual void _cl0(void) = 0;
	virtual void _cl1(void) = 0;
	virtual void _cl2(void) = 0;
	virtual void _cl3(void) = 0;
	virtual void _cl4(void) = 0;
	virtual void _cl5(void) = 0;
	virtual void _cl6(void) = 0;
	virtual void _cl7(void) = 0;
	virtual void _cl8(void) = 0;
	virtual void appendMessage(GameMessage *msg) = 0;	// slot 9, +0x24
};

class ConnectionManager
{
public:
	class NetCommandList *getFrameCommandList(UnsignedInt frame);
};

class BFMEConnectionManager : public ConnectionManager
{
public:
	void clearLeaveRequestTime(void);
	int beginPlayerLeave(void *playerId);
	bool haveAllConnectedPlayersReachedFrame(UnsignedInt frame);
};

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();

	NetCommandType getNetCommandType(void) { return m_commandType; }
	UnsignedInt getExecutionFrame(void) { return m_executionFrame; }

	UnsignedInt m_pad04;				// +0x04
	UnsignedInt m_executionFrame;			// +0x08
	UnsignedInt m_playerID;				// +0x0C
	unsigned short m_id;				// +0x10
	NetCommandType m_commandType;			// +0x14
};

class NetGameCommandMsg : public NetCommandMsg
{
public:
	GameMessage *constructGameMessage(void);
};

class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getLeavingPlayerID(void);
};

class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
};

class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_command; }
	NetCommandRef *getNext(void) { return m_next; }

	NetCommandMsg *m_command;			// +0x00
	NetCommandRef *m_next;				// +0x04
};

class NetCommandList
{
public:
	virtual ~NetCommandList();

	NetCommandRef *getFirstMessage(void) { return m_first; }

	NetCommandRef *m_first;				// +0x04
};

class GameLogic
{
public:
	void bfme_setPlayerLeaveStatus(Int slot, Int status);

	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;				// +0x3C
};

extern CommandList *TheCommandList;
extern GameLogic *TheGameLogicForNet;

class Network
{
public:
	virtual void _s00(void) = 0;
	virtual void _s01(void) = 0;
	virtual void _s02(void) = 0;
	virtual void _s03(void) = 0;
	virtual void _s04(void) = 0;
	virtual void _s05(void) = 0;
	virtual void _s06(void) = 0;
	virtual void _s07(void) = 0;
	virtual void _s08(void) = 0;
	virtual void _s09(void) = 0;
	virtual void _s10(void) = 0;
	virtual void _s11(void) = 0;
	virtual void _s12(void) = 0;
	virtual void _s13(void) = 0;
	virtual void _s14(void) = 0;
	virtual void _s15(void) = 0;
	virtual void _s16(void) = 0;
	virtual void _s17(void) = 0;
	virtual void _s18(void) = 0;
	virtual void _s19(void) = 0;
	virtual void _s20(void) = 0;
	virtual void _s21(void) = 0;
	virtual void _s22(void) = 0;
	virtual void _s23(void) = 0;
	virtual void _s24(void) = 0;
	virtual void _s25(void) = 0;
	virtual void _s26(void) = 0;
	virtual void _s27(void) = 0;
	virtual void _s28(void) = 0;
	virtual void _s29(void) = 0;
	virtual void _s30(void) = 0;
	virtual void _s31(void) = 0;
	virtual void _s32(void) = 0;
	virtual void _s33(void) = 0;
	virtual void _s34(void) = 0;
	virtual bool isPacketRouter(void) = 0;			// slot 35, +0x8C
	virtual void _s36(void) = 0;
	virtual void _s37(void) = 0;
	virtual UnsignedInt getLocalPlayerID(void) = 0;		// slot 38, +0x98
	virtual void _s39(void) = 0;
	virtual void _s40(void) = 0;
	virtual void _s41(void) = 0;
	virtual void _s42(void) = 0;
	virtual void _s43(void) = 0;
	virtual void _s44(void) = 0;
	virtual void _s45(void) = 0;
	virtual void _s46(void) = 0;
	virtual void _s47(void) = 0;
	virtual void _s48(void) = 0;
	virtual void _s49(void) = 0;
	virtual void _s50(void) = 0;
	virtual void _s51(void) = 0;
	virtual void _s52(void) = 0;
	virtual void _s53(void) = 0;
	virtual void _s54(void) = 0;
	virtual bool _bfme_isRouterLeavePending(void) = 0;	// slot 55, +0xDC

protected:
	void RelayCommandsToCommandList(void);
	void processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg);

	void *m_subsystemName;				// +0x04
	BFMEConnectionManager *m_conMgr;		// +0x08
	NetLocalStatus m_localStatus;			// +0x0C
	unsigned char m_pad10[0x38 - 0x10];
	Int m_routerLeaveFrame;				// +0x38
};

void Network::RelayCommandsToCommandList(void)
{
	if (m_conMgr == 0)
		return;
	if (m_localStatus == NETLOCALSTATUS_PREGAME)
		return;

	UnsignedInt frame = TheGameLogicForNet->m_frame;
	NetCommandList *netcmdlist = m_conMgr->getFrameCommandList(frame);
	if (TheGameLogicForNet->m_frame <= 1)
	{
		if (netcmdlist != 0)
			delete netcmdlist;
		return;
	}

	NetCommandRef *msg = netcmdlist->getFirstMessage();
	while (msg != 0)
	{
		NetCommandMsg *cmd = msg->getCommand();
		if (cmd != 0)
		{
			switch (cmd->getNetCommandType())
			{
			case NETCOMMANDTYPE_GAMECOMMAND:
				TheCommandList->appendMessage(((NetGameCommandMsg *)cmd)->constructGameMessage());
				break;
			case NETCOMMANDTYPE_PLAYERLEAVE:
			{
				UnsignedByte leaver = ((NetPlayerLeaveCommandMsg *)cmd)->getLeavingPlayerID();
				if (isPacketRouter() && (UnsignedInt)leaver == getLocalPlayerID())
				{
					m_routerLeaveFrame = (Int)cmd->getExecutionFrame();
					m_conMgr->clearLeaveRequestTime();
				}
				else if (m_conMgr->beginPlayerLeave((void *)(UnsignedInt)leaver) == 1)
					m_localStatus = NETLOCALSTATUS_LEAVING;
				TheGameLogicForNet->bfme_setPlayerLeaveStatus((Int)leaver, 1);
				break;
			}
			case NETCOMMANDTYPE_DESTROYPLAYER:
				processDestroyPlayerCommand((NetDestroyPlayerCommandMsg *)cmd);
				break;
			}
		}
		msg = msg->getNext();
	}

	delete netcmdlist;

	if (_bfme_isRouterLeavePending())
	{
		if (m_conMgr->haveAllConnectedPlayersReachedFrame((UnsignedInt)m_routerLeaveFrame))
		{
			m_conMgr->beginPlayerLeave((void *)getLocalPlayerID());
			m_localStatus = NETLOCALSTATUS_LEAVING;
			m_routerLeaveFrame = -1;
		}
	}
}
