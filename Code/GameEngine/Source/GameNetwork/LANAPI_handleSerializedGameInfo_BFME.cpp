// BFME-only serialized LAN game-info receive handler at retail 0x0068ADE0.
// The matching request at 0x00685000 sends a fixed 0x196-byte block and the
// callback at vtable slot 39 consumes it with the sender address and slot.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum
{
	LAN_SERIALIZED_GAME_INFO_LENGTH = 0x196,
	LAN_MAX_SLOTS = 8
};

struct LANMessage
{
	Int m_type;
	UnsignedByte m_bfmeHeader[0x22 - 4];
	char m_serializedGameInfo[LAN_SERIALIZED_GAME_INFO_LENGTH];
	UnsignedByte m_bfmeTail[0x1DC - 0x22 - LAN_SERIALIZED_GAME_INFO_LENGTH];
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
	UnsignedByte m_bfmeHead[0x0d];
	Bool m_inProgress;
	UnsignedByte m_bfmeBeforeSlots[0x88 - 0x0e];
	BfmeLANSlot m_slot[LAN_MAX_SLOTS];
};

class LANAPI
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
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
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_onSerializedGameInfo_00689170(TransportAddress *from,
		Int playerSlot, char *buffer, UnsignedInt size) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual TransportAddress *_bfme_localAddress(void) = 0;

protected:
	void _bfme_handleSerializedGameInfo_0068ADE0(LANMessage *message,
		const TransportAddress *sender);

	UnsignedByte m_bfmeBeforeLobby[0x3d - 4];
	Bool m_inLobby;
	UnsignedByte m_bfmeBeforeCurrentGame[2];
	LANGameInfo *m_currentGame;
};

// ?_bfme_handleSerializedGameInfo_0068ADE0@LANAPI@@IAEXPAULANMessage@@PBUTTransportAddress@@@Z
void LANAPI::_bfme_handleSerializedGameInfo_0068ADE0(
	LANMessage *message, const TransportAddress *sender)
{
	if (m_inLobby || !m_currentGame || m_currentGame->m_inProgress)
		return;

	Int playerSlot;
	for (playerSlot = 0; playerSlot < LAN_MAX_SLOTS; ++playerSlot)
	{
		TransportAddress *slotAddress = &m_currentGame->m_slot[playerSlot].m_address;
		if (slotAddress->m_ip == sender->m_ip &&
			slotAddress->m_port == sender->m_port)
		{
			_bfme_onSerializedGameInfo_00689170((TransportAddress *)sender, playerSlot,
				message->m_serializedGameInfo, LAN_SERIALIZED_GAME_INFO_LENGTH);
			break;
		}
	}
}
