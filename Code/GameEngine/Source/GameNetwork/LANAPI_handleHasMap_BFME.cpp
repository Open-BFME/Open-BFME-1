// BFME's map-availability receive path at retail 0x0068ACF0.
// Unlike the Zero Hour handler, BFME verifies the setup state and matches a
// participant by the transport address pair before forwarding the byte status
// through its added LANAPI callback slot 52.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct LANMessage
{
	UnsignedByte m_bfmeHead[0x44];
	UnsignedByte m_status;
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct BfmeLANSlot
{
	TransportAddress m_address;
	UnsignedByte m_bfmeRest[0x68 - 8];
};

class LANGameInfo
{
public:
	UnsignedByte m_bfmeHeadA[0x0d];
	Bool m_inProgress;
	UnsignedByte m_bfmeHeadB[0x88 - 0x0e];
	BfmeLANSlot m_slot[8];
};

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot0a(void) = 0;
	virtual void _bfme_slot0b(void) = 0;
	virtual void _bfme_slot0c(void) = 0;
	virtual void _bfme_slot0d(void) = 0;
	virtual void _bfme_slot0e(void) = 0;
	virtual void _bfme_slot0f(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot1a(void) = 0;
	virtual void _bfme_slot1b(void) = 0;
	virtual void _bfme_slot1c(void) = 0;
	virtual void _bfme_slot1d(void) = 0;
	virtual void _bfme_slot1e(void) = 0;
	virtual void _bfme_slot1f(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot2a(void) = 0;
	virtual void _bfme_slot2b(void) = 0;
	virtual void _bfme_slot2c(void) = 0;
	virtual void _bfme_slot2d(void) = 0;
	virtual Bool AmIHost(void) = 0; // +0xb8
	virtual void _bfme_slot2f(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_forwardMapStatus(UnsignedByte status) = 0; // +0xd0
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;

protected:
	void _bfme_handleHasMap_0068ACF0(LANMessage *message,
		const TransportAddress *sender);

	UnsignedByte m_bfmeHead[0x3d - 4];
	Bool m_inLobby;
	LANGameInfo *m_currentGame;
};

// ?_bfme_handleHasMap_0068ACF0@LANAPI@@IAEXPAULANMessage@@PBUTTransportAddress@@@Z
void LANAPI::_bfme_handleHasMap_0068ACF0(
	LANMessage *message, const TransportAddress *sender)
{
	if (!m_currentGame)
		return;
	if (m_currentGame->m_inProgress)
		return;
	if (AmIHost())
		return;
	if (m_inLobby)
		return;

	Int player;
	for (player = 0; player < 8; ++player)
	{
		TransportAddress *slot = &m_currentGame->m_slot[player].m_address;
		if (slot->m_ip == sender->m_ip && slot->m_port == sender->m_port)
		{
			_bfme_forwardMapStatus(message->m_status);
			break;
		}
	}
}
