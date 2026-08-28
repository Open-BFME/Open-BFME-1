// cl: /DNDEBUG /MD /EHsc

// Network::processDestroyPlayerCommand, 0x006827A0, 232 bytes.
//
// Named from the getter it opens with -- getPlayerIndex on
// NetDestroyPlayerCommandMsg, already ledgered at 0x00673B70 -- and the
// reference declares exactly one body that starts that way. Not a vtable slot:
// Network's table (0x0111A968) does not carry this address, and the reference
// has it protected and non-virtual. Its two callers are the two bodies at
// 0x006828D0 and 0x00682A90.
//
// The reference's body with one substitution and one flipped constant.
//
// The substitution is where the player name comes from. Zero Hour formats
// "player%d" off the slot index; BFME copies an AsciiString out of the slot
// itself, at GameSlot+0x2C, and hands that to NameKeyGenerator::nameToKey. The
// rest -- findPlayerWithNameKey, the self-destruct GameMessage with the
// player's index stamped on it, TheCommandList::appendMessage through vtable
// slot 9 -- is the reference's, in the reference's order.
//
// The flipped constant is the boolean argument: retail pushes 1 where the
// reference pushes FALSE.
//
// GameMessage::Type is renumbered wholesale in BFME, so the self-destruct type
// stays the retail literal, the way Network_quitGame.cpp keeps 0x1D for clear
// game data. Everything else is declared only as far as this body touches it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0

enum { MAX_SLOTS = 8 };

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;			// +4
	UnsignedShort m_pad;
};

template <typename T>
class StringBase
{
	friend class GameSlot;
	friend class Network;

public:
	~StringBase() { releaseBuffer(); }

	const T *str() const { return m_data ? (const T *)(m_data + 1) : (const T *)""; }

private:
	StringBase(const StringBase<T> &src);	// ??0?$StringBase@D@@AAE@ABV0@@Z
	void releaseBuffer();			// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	// The name BFME hands NameKeyGenerator for this slot. Zero Hour formats
	// "player%d" from the index here instead.
	UnsignedByte m_bfmeHead[0x2C];
	StringBase<char> m_bfmeSlotNameKeyText;		// +0x2C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot(Int slot);			// ILT thunk 0x0001EC18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// ILT thunk 0x0003ADD7
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex(void) const { return m_playerIndex; }

	UnsignedByte m_bfmeHead[0x24];
	Int m_playerIndex;				// +0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);	// ILT thunk 0x0002F586
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
		// BFME renumbers GameMessage::Type wholesale and nothing in the tree
		// fixes this one to a name yet, so it stays the retail literal.
		MSG_SELF_DESTRUCT = 0x447
	};

	GameMessage(Type type);				// ILT thunk 0x000359E5
	void appendBooleanArgument(Bool arg);		// ILT thunk 0x000032AB

	void friend_setPlayerIndex(Int playerIndex) { m_playerIndex = playerIndex; }

	UnsignedByte m_bfmeHead[0x14];
	Int m_playerIndex;				// +0x14
	UnsignedByte m_bfmeTail[0x24 - 0x18];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class CommandList
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
	virtual void appendMessage(GameMessage *msg) = 0;	// slot 9, vtable+0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDestroyPlayerCommandMsg
{
public:
	UnsignedInt getPlayerIndex(void);		// ILT thunk 0x000058E4
};

extern GameInfo *TheGameInfo;				// retail [0x012F708C]
extern NameKeyGenerator *TheNameKeyGenerator;		// retail [0x012ED600]
extern PlayerList *ThePlayerList;			// retail [0x012ED748]
extern CommandList *TheCommandList;			// retail [0x012ED5F0]

class Network
{
protected:
	void processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg);
};

// ?processDestroyPlayerCommand@Network@@IAEXPAVNetDestroyPlayerCommandMsg@@@Z
void Network::processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg)
{
	UnsignedInt playerIndex = msg->getPlayerIndex();
	if (playerIndex >= MAX_SLOTS)
		return;

	StringBase<char> playerName = TheGameInfo->getSlot(playerIndex)->m_bfmeSlotNameKeyText;
	Player *pPlayer = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName.str()));
	if (pPlayer)
	{
		GameMessage *gmsg = new GameMessage(GameMessage::MSG_SELF_DESTRUCT);
		gmsg->appendBooleanArgument(true);
		gmsg->friend_setPlayerIndex(pPlayer->getPlayerIndex());
		TheCommandList->appendMessage(gmsg);
	}
}
