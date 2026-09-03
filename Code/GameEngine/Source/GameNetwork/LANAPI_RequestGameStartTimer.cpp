// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?RequestGameStartTimer@LANAPI@@UAEXH@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp
// readable body of ?sendMessage@LANAPI@@IAEXPAULANMessage@@I@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp
//
// Retail 0x00684F30, 165 bytes. Zero Hour's RequestGameStartTimer body in lanapi.cpp
// is present-unmatched at 141 bytes: wrong host test (m_localIP instead of the
// address pair from vtable+0xDC), wrong message type (ZH's MSG_GAME_START_TIMER
// at 12; BFME's literal is 0x0E), and wrong store order (type after
// fillInLANMessage where retail writes 0x0E and StartTimer.seconds first).
//
//   LANAPI      +0x1C  m_gameStartTime = timeGetTime() + 1000
//               +0x20  m_gameStartSeconds = seconds ? seconds - 1 : 0
//               +0x3D  m_inLobby, early out when set
//               +0x40  m_currentGame; host slot at +0x88/+0x8C
//               +0x4C  m_transport->update() after send
//               +0x94  OnGameStartTimer, vtable slot 37
//               +0xC4  fillInLANMessage, vtable slot 49
//               +0xDC  _bfme_localAddress, vtable slot 55
//   LANMessage  size 0x1DC; type 0x0E and StartTimer.seconds at +0x22 land
//               before fillInLANMessage runs.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class BfmeGameSlot;

class BfmeGameInfo
{
public:
	BfmeGameSlot *getSlot(Int slot);
};

class LANGameInfo : public BfmeGameInfo
{
public:
	virtual void bfmeGameInfoSlot01(void) = 0;
	virtual void bfmeGameInfoSlot02(void) = 0;
	virtual void bfmeGameInfoSlot03(void) = 0;
	virtual void bfmeGameInfoSlot04(void) = 0;
	virtual void bfmeGameInfoSlot05(void) = 0;
	virtual Int getLocalSlotNum(void) const = 0;

	Bool getIsDirectConnect(void) const
	{
		return m_isDirectConnect;
	}

private:
	unsigned char m_bfmeGameInfoGap[0x3a4 - 4];
	Bool m_isDirectConnect;
};

class BfmeLANGameInfoHost
{
public:
	unsigned char m_bfmeHead[0x88];
	UnsignedInt m_hostIP;			///< +0x88
	UnsignedShort m_hostPort;		///< +0x8C
};

#pragma pack(push, 1)
struct BfmeTransportAddress
{
	UnsignedInt ip;
	unsigned short port;
};
#pragma pack(pop)

class BfmeGameSlot
{
public:
	virtual void bfmeGameSlotVft(void) = 0;
	Bool isHuman(void) const;
	unsigned char m_bfmeGameSlotGap[0x30 - 4];
	BfmeTransportAddress m_address;
};

class Transport
{
public:
	void update(void);
};

class BfmeTransportQueueShim
{
public:
	Bool queueSend(const BfmeTransportAddress *address,
		const unsigned char *data, Int length);
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;						///< +0x000
	unsigned char m_unreconstructed_04[0x22 - 0x04];

	union
	{
		struct
		{
			Int seconds;					///< +0x022
		} StartTimer;

		unsigned char m_unreconstructed_22[0x1DC - 0x22];
	};
};
#pragma pack(pop)

class LANAPI
{
public:
	virtual void bfmeRetailSlot00(void) = 0;
	virtual void bfmeRetailSlot01(void) = 0;
	virtual void bfmeRetailSlot02(void) = 0;
	virtual void bfmeRetailSlot03(void) = 0;
	virtual void bfmeRetailSlot04(void) = 0;
	virtual void bfmeRetailSlot05(void) = 0;
	virtual void bfmeRetailSlot06(void) = 0;
	virtual void bfmeRetailSlot07(void) = 0;
	virtual void bfmeRetailSlot08(void) = 0;
	virtual void bfmeRetailSlot09(void) = 0;
	virtual void bfmeRetailSlot10(void) = 0;
	virtual void bfmeRetailSlot11(void) = 0;
	virtual void bfmeRetailSlot12(void) = 0;
	virtual void bfmeRetailSlot13(void) = 0;
	virtual void bfmeRetailSlot14(void) = 0;
	virtual void bfmeRetailSlot15(void) = 0;
	virtual void bfmeRetailSlot16(void) = 0;
	virtual void bfmeRetailSlot17(void) = 0;
	virtual void bfmeRetailSlot18(void) = 0;
	virtual void bfmeRetailSlot19(void) = 0;
	virtual void bfmeRetailSlot20(void) = 0;
	virtual void bfmeRetailSlot21(void) = 0;
	virtual void bfmeRetailSlot22(void) = 0;
	virtual void bfmeRetailSlot23(void) = 0;
	virtual void bfmeRetailSlot24(void) = 0;
	virtual void bfmeRetailSlot25(void) = 0;
	virtual void bfmeRetailSlot26(void) = 0;
	virtual void bfmeRetailSlot27(void) = 0;
	virtual void bfmeRetailSlot28(void) = 0;
	virtual void bfmeRetailSlot29(void) = 0;
	virtual void bfmeRetailSlot30(void) = 0;
	virtual void bfmeRetailSlot31(void) = 0;
	virtual void bfmeRetailSlot32(void) = 0;
	virtual void bfmeRetailSlot33(void) = 0;
	virtual void bfmeRetailSlot34(void) = 0;
	virtual void bfmeRetailSlot35(void) = 0;
	virtual void bfmeRetailSlot36(void) = 0;
	virtual void OnGameStartTimer(Int seconds) = 0;			///< +0x94
	virtual void bfmeRetailSlot38(void) = 0;
	virtual void bfmeRetailSlot39(void) = 0;
	virtual void bfmeRetailSlot40(void) = 0;
	virtual void bfmeRetailSlot41(void) = 0;
	virtual void bfmeRetailSlot42(void) = 0;
	virtual void bfmeRetailSlot43(void) = 0;
	virtual void bfmeRetailSlot44(void) = 0;
	virtual void bfmeRetailSlot45(void) = 0;
	virtual void bfmeRetailSlot46(void) = 0;
	virtual void bfmeRetailSlot47(void) = 0;
	virtual void bfmeRetailSlot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;		///< +0xC4
	virtual void bfmeRetailSlot50(void) = 0;
	virtual void bfmeRetailSlot51(void) = 0;
	virtual void bfmeRetailSlot52(void) = 0;
	virtual void bfmeRetailSlot53(void) = 0;
	virtual void bfmeRetailSlot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;		///< +0xDC

	virtual void RequestGameStartTimer(Int seconds);

protected:
	void sendMessage(LANMessage *msg, UnsignedInt ip);

private:
	unsigned char m_unreconstructed_04[0x1C - 0x04];
	UnsignedInt m_gameStartTime;					///< +0x1C
	Int m_gameStartSeconds;						///< +0x20
	unsigned char m_unreconstructed_24[0x3D - 0x24];
	Bool m_inLobby;							///< +0x3D
	unsigned char m_unreconstructed_3e[0x40 - 0x3E];
	LANGameInfo *m_currentGame;					///< +0x40
	unsigned char m_bfmeHoleBeforeTransport[8];
	Transport *m_transport;						///< +0x4C
	UnsignedInt m_broadcastAddr;
};

void LANAPI::sendMessage(LANMessage *msg, UnsignedInt ip)
{
	BfmeTransportAddress *address =
		reinterpret_cast<BfmeTransportAddress *>(ip);
	if (address != 0 && (address->ip != 0 || address->port != 0))
	{
		reinterpret_cast<BfmeTransportQueueShim *>(m_transport)->queueSend(
			address,
			reinterpret_cast<const unsigned char *>(msg), sizeof(LANMessage));
		return;
	}

	if (m_currentGame != 0 && m_currentGame->getIsDirectConnect())
	{
		Int localSlot = m_currentGame->getLocalSlotNum();
		for (Int i = 0; i < 8; ++i)
		{
			if (i == localSlot)
				continue;
			BfmeGameInfo *gameInfo =
				reinterpret_cast<BfmeGameInfo *>(m_currentGame);
			BfmeGameSlot *slot = gameInfo->getSlot(i);
			if (slot != 0 && slot->isHuman())
			{
				reinterpret_cast<BfmeTransportQueueShim *>(m_transport)->queueSend(
					&slot->m_address,
					reinterpret_cast<const unsigned char *>(msg),
					sizeof(LANMessage));
			}
		}
	}
	else
	{
		BfmeTransportAddress address;
		for (unsigned short port = 8086; port < 8094; ++port)
		{
			address.ip = m_broadcastAddr;
			address.port = port;
			reinterpret_cast<BfmeTransportQueueShim *>(m_transport)->queueSend(
				&address,
				reinterpret_cast<const unsigned char *>(msg),
				sizeof(LANMessage));
		}
	}
}

void LANAPI::RequestGameStartTimer(Int seconds)
{
	if (m_inLobby)
		return;

	BfmeLANGameInfoHost *game =
		reinterpret_cast<BfmeLANGameInfoHost *>(m_currentGame);
	if (game == 0)
		return;

	BfmeNetAddress *me = _bfme_localAddress();
	if (game->m_hostIP != me->m_ip || game->m_hostPort != me->m_port)
		return;

	m_gameStartTime = timeGetTime() + 1000;

	Int timerSeconds = seconds;
	m_gameStartSeconds = timerSeconds ? timerSeconds - 1 : 0;

	LANMessage msg;
	msg.LANMessageType = 14;
	msg.StartTimer.seconds = timerSeconds;
	fillInLANMessage(&msg);
	sendMessage(&msg, 0);
	m_transport->update();
	OnGameStartTimer(timerSeconds);
}
