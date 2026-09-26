// cl: /DNDEBUG /MD /EHsc
// Network::RelayCommandsToCommandList, RVA 0x00682A90, 375 bytes.
// The matched Network::update calls this at RVA 0x00682CBC.
// Delivers synchronized game orders and player-leave commands to game logic.
// BFME waits for all connected players to reach the router's leave frame.
// beginPlayerLeave takes a byte player ID: its retail entry at 0x00667320
// zero-extends byte [esp+0x28]. Modeling that as a pointer changed register
// allocation and the stack frame in the prior banked reconstruction.
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
	virtual void appendMessage(GameMessage *msg) = 0;
};

class NetCommandList;

class ConnectionManager
{
public:
	NetCommandList *getFrameCommandList(UnsignedInt frame);
};

class BFMEConnectionManager : public ConnectionManager
{
public:
	void clearLeaveRequestTime(void);
	int beginPlayerLeave(UnsignedByte playerId);
	bool haveAllConnectedPlayersReachedFrame(UnsignedInt frame);
};

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();

	NetCommandType getNetCommandType(void) { return m_commandType; }
	UnsignedInt getExecutionFrame(void) { return m_executionFrame; }

	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	unsigned short m_id;
	NetCommandType m_commandType;
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

	NetCommandMsg *m_command;
	NetCommandRef *m_next;
};

class NetCommandList
{
public:
	virtual ~NetCommandList();

	NetCommandRef *getFirstMessage(void) { return m_first; }

	NetCommandRef *m_first;
};

class GameLogic
{
public:
	void setPlayerLeaveStatus(Int slot, Int status);

	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;
};

extern CommandList *TheCommandList;
extern GameLogic *TheGameLogic;

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
	virtual bool isPacketRouter(void) = 0;
	virtual void _s36(void) = 0;
	virtual void _s37(void) = 0;
	virtual UnsignedInt getLocalPlayerID(void) = 0;
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
	virtual bool _bfme_isRouterLeavePending(void) = 0;

protected:
	void RelayCommandsToCommandList(void);
	void processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg);

	void *m_subsystemName;
	BFMEConnectionManager *m_conMgr;
	NetLocalStatus m_localStatus;
	unsigned char m_pad10[0x38 - 0x10];
	Int m_routerLeaveFrame;
};

void Network::RelayCommandsToCommandList(void)
{
	if (m_conMgr == 0)
		return;
	if (m_localStatus == NETLOCALSTATUS_PREGAME)
		return;

	UnsignedInt frame = TheGameLogic->m_frame;
	NetCommandList *netcmdlist = m_conMgr->getFrameCommandList(frame);
	if (TheGameLogic->m_frame <= 1)
	{
		if (netcmdlist != 0)
			delete netcmdlist;
		return;
	}

	NetCommandRef *ref = netcmdlist->getFirstMessage();
	while (ref != 0)
	{
		NetCommandMsg *cmd = ref->getCommand();
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
				else if (m_conMgr->beginPlayerLeave(leaver) == 1)
					m_localStatus = NETLOCALSTATUS_LEAVING;
				TheGameLogic->setPlayerLeaveStatus((Int)leaver, 1);
				break;
			}
			case NETCOMMANDTYPE_DESTROYPLAYER:
				processDestroyPlayerCommand((NetDestroyPlayerCommandMsg *)cmd);
				break;
			}
		}
		ref = ref->getNext();
	}

	delete netcmdlist;

	if (_bfme_isRouterLeavePending())
	{
		if (m_conMgr->haveAllConnectedPlayersReachedFrame((UnsignedInt)m_routerLeaveFrame))
		{
			m_conMgr->beginPlayerLeave((UnsignedByte)getLocalPlayerID());
			m_localStatus = NETLOCALSTATUS_LEAVING;
			m_routerLeaveFrame = -1;
		}
	}
}
