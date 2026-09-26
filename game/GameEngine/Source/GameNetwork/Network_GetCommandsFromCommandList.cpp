// cl: /DNDEBUG /MD /EHsc
//
// Network::GetCommandsFromCommandList, 0x006828D0, 352 bytes.
//
// Named by the already-matched Network::update (0x00682C70) which calls this
// at 0x00682C87, and by the reloc-named pin. Zero Hour's walk of
// TheCommandList with processCommand inlined: network-range GameMessage types
// 0x3E9..0x7CE go to sendGameCommand when status is INGAME and the packet
// router is not already leaving; MSG_CLEAR_GAME_DATA (0x1D) goes to
// sendPlayerLeaveCommands when TheGameLogic+0x6C is clear. The BFME tail
// forces beginPlayerLeave + a NetDestroyPlayerCommandMsg when the leave
// timer on the connection manager has been up for 10 s.

typedef int Int;
typedef unsigned int UnsignedInt;

enum NetLocalStatus
{
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT
};

enum { BFME_MSG_CLEAR_GAME_DATA = 0x1D };

class GameMessage
{
public:
	virtual ~GameMessage();

	GameMessage *m_next;				// +0x04
	unsigned char m_pad08[0x10 - 0x08];
	Int m_type;					// +0x10
};

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
	virtual void _cl9(void) = 0;
	virtual void _cl10(void) = 0;
	virtual void removeMessage(GameMessage *msg) = 0;	// slot 11, +0x2C

	void *m_pad04;
	GameMessage *m_first;				// +0x08
};

class ConnectionManager
{
public:
	bool isPacketRouter(void);
};

class BFMEConnectionManager : public ConnectionManager
{
public:
	void sendGameCommand(void *msg);
	void sendPlayerLeaveCommands(void);
	bool hasLeaveRequestTimedOut(void);
	void beginPlayerLeave(void *playerId);
};

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
	void detach(void);

	UnsignedInt m_timestamp;			// +0x04
	UnsignedInt m_executionFrame;			// +0x08
	UnsignedInt m_playerID;				// +0x0C
	unsigned short m_id;				// +0x10
	Int m_commandType;				// +0x14
	Int m_referenceCount;				// +0x18
};

class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	NetDestroyPlayerCommandMsg();
	void setPlayerIndex(UnsignedInt v);
	UnsignedInt m_playerIndex;			// +0x1C, object is 0x20
};

class GameLogicNetView
{
public:
	unsigned char m_pad[0x6C];
	unsigned char m_sawCRCMismatch;			// +0x6C
};

extern CommandList *TheCommandList;
extern GameLogicNetView *TheGameLogic;

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
	void GetCommandsFromCommandList(void);
	void processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg);

	void *m_subsystemName;				// +0x04
	BFMEConnectionManager *m_conMgr;		// +0x08
	NetLocalStatus m_localStatus;			// +0x0C
};

void Network::GetCommandsFromCommandList(void)
{
	GameMessage *msg = TheCommandList->m_first;
	if (msg != 0)
	{
		do
		{
			Int type = msg->m_type;
			GameMessage *next = msg->m_next;
			if (type > 0x3E8 && type < 0x7CF)
			{
				if (m_localStatus == NETLOCALSTATUS_INGAME)
				{
					if (m_conMgr != 0)
					{
						if (!m_conMgr->isPacketRouter() || !_bfme_isRouterLeavePending())
							m_conMgr->sendGameCommand(msg);
					}
				}
				TheCommandList->removeMessage(msg);
				delete msg;
			}
			else if (type == BFME_MSG_CLEAR_GAME_DATA)
			{
				if (TheGameLogic->m_sawCRCMismatch == 0 && m_localStatus == NETLOCALSTATUS_INGAME)
				{
					m_conMgr->sendPlayerLeaveCommands();
					TheCommandList->removeMessage(msg);
					delete msg;
				}
			}
			msg = next;
		} while (msg != 0);
	}

	if (m_conMgr != 0 && m_conMgr->hasLeaveRequestTimedOut())
	{
		if (m_conMgr != 0)
			m_conMgr->beginPlayerLeave((void *)getLocalPlayerID());
		NetDestroyPlayerCommandMsg *netmsg = new NetDestroyPlayerCommandMsg;
		netmsg->m_playerID = getLocalPlayerID();
		netmsg->setPlayerIndex(getLocalPlayerID());
		processDestroyPlayerCommand(netmsg);
		netmsg->detach();
		m_localStatus = NETLOCALSTATUS_LEAVING;
	}
}
