// cl: /DNDEBUG /MD /EHsc
// readable body of ?addGame@LANAPI@@IAEXPAVLANGameInfo@@@Z: game/GameEngine/Source/GameNetwork/lanapi.cpp

// The two LANAPI bodies that work on a LANGameInfo rather than on a message.
//
// addGame (0x00686DF0, 376 bytes) is the browser side: a sorted insert into
// m_games at this+0x0C, walking m_next at +0x398 and ordering by
// LANGameInfo::getName().compareNoCase(). It is named from its callers --
// RequestGameCreate (0x00687E90) and handleGameAnnounce (0x0068C110) both reach
// it, and addGame is the one thing the reference has them both call -- and it is
// the reference's body unchanged, including the reference's own asymmetry: the
// head comparison tests < 0 and the walk tests > 0.
//
// handleHasMap (0x0068B540, 280 bytes) is the setup side: CRC the portable path
// of the game we are in and, when a peer's CRC agrees, forward its flag for the
// slot whose address pair matches the sender.
//
// compareNoCase is declared nothrow, and that is the whole difference between
// addGame at 376 bytes and 412. Each block builds two UnicodeString temporaries
// and destroys them again; with compareNoCase able to throw, MSVC has to bump
// the unwind state after the second temporary is constructed and again after it
// is destroyed, four extra stores per block. Retail has neither, so its compiler
// knew the compare could not throw: one state covers the pair and the two-bit
// liveness mask in ebx tells the funclet which of them to destroy. Nothing else
// -- optimisation flags included -- collapses those states.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	// Declared nothrow, and that is load-bearing -- see the note at the top.
	Int compareNoCase(const StringBase<T> &other) const throw();	// retail 0x0009EFE0

private:
	void releaseBuffer();					// retail 0x008881D0

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { ((StringBase<WideChar> *)this)->releaseBuffer(); }

	Int compareNoCase(const UnicodeString &other) const
	{
		return ((const StringBase<WideChar> *)this)->compareNoCase(*(const StringBase<WideChar> *)&other);
	}

private:
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
	UnsignedByte m_bfmeHead[0x88];

public:
	AsciiString getMap(void) const;				// ?getMap@GameInfo@@QBE?AVAsciiString@@XZ
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public GameInfo
{
public:
	UnicodeString getName(void);				// ILT thunk 0x00041FC9

	LANGameInfo *getNext(void) { return m_next; }
	void setNext(LANGameInfo *next) { m_next = next; }

	UnsignedByte m_bfmeGap[0x398 - 0x88];
	LANGameInfo *m_next;					// +0x398
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

// handleHasMap walks eight 0x68-byte participant records from LANGameInfo+0x88,
// which runs to +0x3C8 and would swallow m_next at +0x398 that addGame threads
// the browser list through. Both offsets are byte-proven from the bodies here,
// so the two readings of +0x88 cannot both be members of one class; the walk
// keeps its own view rather than either reading being quietly dropped.
class BfmeLANGameInfoSlots
{
public:
	UnsignedByte m_bfmeHead[0x88];
	BfmeLANSlot m_slot[8];					// +0x88
};

struct LANMessage
{
	UnsignedByte m_bfmeHead[0x44];
	UnsignedInt mapCRC;					// +0x44
	Bool hasMap;						// +0x48
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
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
	virtual void OnHasMap(BfmeNetAddress *sender, Bool status) = 0;	// slot 34, vtable+0x88
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
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
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;		// slot 55, vtable+0xDC

protected:
	void addGame(LANGameInfo *game);
	void handleHasMap(LANMessage *msg, UnsignedInt senderIP);

	UnsignedByte m_bfmeHeadA[0x0C - 4];
	LANGameInfo *m_games;					// +0x0C
	UnsignedByte m_bfmeHeadB[0x3D - 0x10];
	Bool m_inLobby;						// +0x3D
	UnsignedByte m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;				// +0x40
};

// ?addGame@LANAPI@@IAEXPAVLANGameInfo@@@Z
void LANAPI::addGame( LANGameInfo *game )
{
	if (!m_games)
	{
		m_games = game;
		game->setNext(NULL);
		return;
	}
	else
	{
		if (game->getName().compareNoCase(m_games->getName()) < 0)
		{
			game->setNext(m_games);
			m_games = game;
			return;
		}
		else
		{
			LANGameInfo *g = m_games;
			while (g->getNext() && g->getNext()->getName().compareNoCase(game->getName()) > 0)
			{
				g = g->getNext();
			}
			game->setNext(g->getNext());
			g->setNext(game);
			return;
		}
	}
}

// ?handleHasMap@LANAPI@@IAEXPAULANMessage@@I@Z
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
			BfmeNetAddress *slot = &reinterpret_cast<BfmeLANGameInfoSlots *>(
				m_currentGame)->m_slot[player].m_address;
			if (slot->m_ip == sender->m_ip && slot->m_port == sender->m_port)
			{
				OnHasMap(sender, msg->hasMap);
				break;
			}
		}
	}
}
