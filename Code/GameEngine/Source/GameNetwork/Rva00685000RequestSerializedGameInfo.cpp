// cl: /DNDEBUG /MD /GX
//
// Retail 0x00685000, LANAPI vtable slot 21.  This is a BFME-only request
// between Zero Hour's RequestGameOptions and RequestGameCreate slots.  Its
// callers pass a flag and a TransportAddress pointer; the flag is unused.
// Message type 0x12 carries BFME's fixed-size serialized LAN game-info block
// and is paired with BFME-only callback slot 39.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum
{
	LANMSG_SERIALIZED_GAME_INFO = 0x12,
	LAN_SERIALIZED_GAME_INFO_LENGTH = 0x196,
	LAN_MAX_SLOTS = 8
};

struct LANMessage
{
	Int m_type;
	unsigned char m_bfmeHeader[0x22 - 4];
	char m_serializedGameInfo[LAN_SERIALIZED_GAME_INFO_LENGTH];
	unsigned char m_bfmeTail[0x1DC - 0x22 - LAN_SERIALIZED_GAME_INFO_LENGTH];
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct BfmeLANSlot
{
	TransportAddress m_address;
	unsigned char m_bfmeRest[0x68 - 8];
};

class LANGameInfo
{
public:
	unsigned char m_bfmeHead[0x88];
	BfmeLANSlot m_slot[LAN_MAX_SLOTS];
};

void __cdecl _bfme_fillCurrentLANGameInfo_0068E630(char *buffer, UnsignedInt size);

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
	virtual void _bfme_requestSerializedGameInfo_00685000(Bool unused, TransportAddress *destination);
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
	virtual void _bfme_onSerializedGameInfo_00689170(TransportAddress *from, Int playerSlot,
		char *buffer, UnsignedInt size) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *message) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual TransportAddress *_bfme_localAddress(void) = 0;

protected:
	void sendMessage(LANMessage *message, UnsignedInt destination);

	unsigned char m_bfmeHead[0x40 - 4];
	LANGameInfo *m_currentGame;
};

// ?_bfme_requestSerializedGameInfo_00685000@LANAPI@@UAEX_NPAUTransportAddress@@@Z
void LANAPI::_bfme_requestSerializedGameInfo_00685000(Bool unused, TransportAddress *destination)
{
	if (!m_currentGame)
		return;

	LANMessage message;
	fillInLANMessage(&message);
	message.m_type = LANMSG_SERIALIZED_GAME_INFO;
	_bfme_fillCurrentLANGameInfo_0068E630(message.m_serializedGameInfo,
		LAN_SERIALIZED_GAME_INFO_LENGTH);
	sendMessage(&message, (UnsignedInt)destination);

	Int playerSlot;
	for (playerSlot = 0; playerSlot < LAN_MAX_SLOTS; ++playerSlot)
	{
		TransportAddress *slotAddress = &m_currentGame->m_slot[playerSlot].m_address;
		TransportAddress *localAddress = _bfme_localAddress();
		if (slotAddress->m_ip == localAddress->m_ip &&
			slotAddress->m_port == localAddress->m_port)
		{
			_bfme_onSerializedGameInfo_00689170(_bfme_localAddress(), playerSlot,
				message.m_serializedGameInfo, LAN_SERIALIZED_GAME_INFO_LENGTH);
			break;
		}
	}
}
