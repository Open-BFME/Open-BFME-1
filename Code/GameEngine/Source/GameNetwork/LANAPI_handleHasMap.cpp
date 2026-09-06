// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class AsciiString
{
protected:
	void releaseBuffer();

private:
	void *m_data;

public:
	~AsciiString()
	{
		releaseBuffer();
	}

	const char *str() const
	{
		static const char TheNullChr = 0;
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : &TheNullChr;
	}

	int getLength() const
	{
		return m_data ? *reinterpret_cast<const UnsignedShort *>(
			reinterpret_cast<const UnsignedByte *>(m_data) + 4) : 0;
	}
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
};

extern GameState *TheGameState;
extern unsigned long CRC_Memory(const unsigned char *data, unsigned long length, unsigned long crc);

class GameInfo
{
	UnsignedByte m_bfmeHead[0x88];

public:
	AsciiString getMap(void) const;
};

struct LANMessage
{
	UnsignedByte m_bfmeHead[0x44];
	UnsignedInt mapCRC;
	Bool hasMap;
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

class LANGameInfo : public GameInfo
{
public:
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
	virtual void OnHasMap(BfmeNetAddress *sender, Bool status) = 0;

protected:
	UnsignedByte m_bfmeHead[0x3d - 4];
	Bool m_inLobby;
	LANGameInfo *m_currentGame;
	void handleHasMap(LANMessage *msg, UnsignedInt senderIP);
};

void LANAPI::handleHasMap(LANMessage *msg, UnsignedInt senderIP)
{
	if (!m_inLobby && m_currentGame)
	{
		AsciiString portableMapName = TheGameState->realMapPathToPortableMapPath(m_currentGame->getMap());
		if (msg->mapCRC != CRC_Memory(
			reinterpret_cast<const unsigned char *>(portableMapName.str()),
			portableMapName.getLength(), 0))
		{
			return;
		}

		BfmeNetAddress *sender = reinterpret_cast<BfmeNetAddress *>(senderIP);
		int player;
		for (player = 0; player < 8; ++player)
		{
			BfmeNetAddress *slot = &m_currentGame->m_slot[player].m_address;
			if (slot->m_ip == sender->m_ip && slot->m_port == sender->m_port)
			{
				OnHasMap(sender, msg->hasMap);
				break;
			}
		}
	}
}
