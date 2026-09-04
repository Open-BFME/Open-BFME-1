// cl: /DNDEBUG /MD /EHs-c-
// LANAPI::handleRequestLobbyLeave, retail 0x0068AC20 (75 bytes).

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct LANMessage
{
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// BFME's lobby player keeps its linked-list pointer at +0x10 and the address
// pair at +0x14.  The pair is the sender parameter used by the handlers.
class LANPlayer
{
public:
	UnsignedByte m_bfmeHead[0x10];
	LANPlayer *m_next;
	BfmeNetAddress m_address;
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
	virtual void OnPlayerList(LANPlayer *players) = 0; // vtable +0x70

protected:
	void handleRequestLobbyLeave(LANMessage *msg, BfmeNetAddress *sender);
	void removePlayer(LANPlayer *player);

	UnsignedByte m_bfmeHead[4];
	LANPlayer *m_lobbyPlayers; // +0x08
	UnsignedByte m_bfmeBeforeLobbyFlag[0x3d - 0x0c];
	Bool m_inLobby; // +0x3d
};

// ?handleRequestLobbyLeave@LANAPI@@IAEXPAULANMessage@@PAVBfmeNetAddress@@@Z
void LANAPI::handleRequestLobbyLeave(LANMessage *msg, BfmeNetAddress *sender)
{
	if (m_inLobby)
	{
		LANPlayer *player = m_lobbyPlayers;
		while (player)
		{
			if (player->m_address.m_ip == sender->m_ip &&
				player->m_address.m_port == sender->m_port)
			{
				removePlayer(player);
				OnPlayerList(m_lobbyPlayers);
				break;
			}
			player = player->m_next;
		}
	}
}
