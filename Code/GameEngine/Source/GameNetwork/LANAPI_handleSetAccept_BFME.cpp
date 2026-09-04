// cl: /DNDEBUG /MD /EHs-c-
// LANAPI::handleSetAccept, retail 0x0068AC80 (90 bytes).

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef bool Bool;

struct LANMessage
{
	UnsignedByte m_bfmeHead[0x44];
	UnsignedByte m_status; // SET_ACCEPT status at +0x44
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct BfmeLANSlot
{
	BfmeNetAddress m_address;
	UnsignedByte m_bfmeRest[0x68 - 8];
};

class LANGameInfo
{
public:
	UnsignedByte m_bfmeHeadA[0x0d];
	Bool m_inProgress; // +0x0d
	UnsignedByte m_bfmeHeadB[0x88 - 0x0e];
	BfmeLANSlot m_slot[8]; // +0x88
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
	virtual void OnAccept(BfmeNetAddress *from, UnsignedInt status) = 0; // +0x84

protected:
	void handleSetAccept(LANMessage *msg, BfmeNetAddress *sender);

	UnsignedByte m_bfmeHead[0x3d - 4];
	Bool m_inLobby; // +0x3d
	LANGameInfo *m_currentGame; // +0x40
};

// ?handleSetAccept@LANAPI@@IAEXPAULANMessage@@PAUBfmeNetAddress@@@Z
void LANAPI::handleSetAccept(LANMessage *msg, BfmeNetAddress *sender)
{
	if (!m_inLobby && m_currentGame && !m_currentGame->m_inProgress)
	{
		Int player;
		for (player = 0; player < 8; ++player)
		{
			BfmeNetAddress *slot = &m_currentGame->m_slot[player].m_address;
			if (slot->m_ip == sender->m_ip && slot->m_port == sender->m_port)
			{
				OnAccept(sender, msg->m_status);
				break;
			}
		}
	}
}
