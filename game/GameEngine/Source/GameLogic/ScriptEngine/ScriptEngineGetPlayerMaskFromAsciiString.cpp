// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ScriptEngine's BFME player-selector resolver, retail 0x0034CB60 (635 bytes).
// The ILT used by doGiveMoney/doSetMoney carries the proven two-argument
// thiscall ABI: const AsciiString&, Bool*.  The return is a 16-bit player mask.

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

struct BfmeAsciiStringData
{
	int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &that);
	~StringBase(void);

public:
	Int compare(const T *text) const;

	BfmeAsciiStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString(void) {}

	Int compare(const char *text) const
	{
		return ((const StringBase<char> *)this)->compare(text);
	}

	const char *str(void) const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	void __cdecl format(AsciiString format, ...);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

NameKeyType NAMEKEY(const AsciiString &name);

class Player
{
public:
	Int getPlayerIndex(void) const { return m_playerIndex; }
	UnsignedShort getPlayerMask(void) const
	{
		return (UnsignedShort)(1 << m_playerIndex);
	}

private:
	unsigned char m_beforePlayerIndex[0x24];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Player *getLocalPlayer(void) const { return m_local; }
	UnsignedShort getPlayersWithRelationship(Int playerIndex,
		Int relationshipFlags, Bool includeNeutral);
	Player *findPlayerWithNameKey(NameKeyType key);

private:
	unsigned char m_beforeLocal[0x0C];
	Player *m_local;
	Int m_playerCount;
	Player *m_players[32];
};

// The retail body reaches the already-identified PlayerList mask body through
// this five-byte generated ILT.  Keep its raw ABI local: the thunk has no
// source-level argument list, while the destination is a thiscall method.
extern void j_000033e1(void);

static __forceinline UnsignedShort bfmeGetPlayersMask(PlayerList *players)
{
	typedef UnsignedShort (PlayerList::*Function)(void);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000033e1;
	return (players->*fn.member)();
}

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual Player *getSkirmishEnemyPlayer(void) = 0;
	virtual Player *getCurrentPlayer(void) = 0;

	void AppendDebugMessage(const AsciiString &text, Bool forcePause);
};

// This is the address-derived owner already proven by the ILT call sites.  It
// deliberately keeps ScriptEngine's semantic name out of the new claim.
class BfmeScriptEngine_getPlayerMaskFromAsciiString : public ScriptEngine
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

// ?getPlayerMaskFromAsciiString@BfmeScriptEngine_getPlayerMaskFromAsciiString@@QAEGABVAsciiString@@PA_N@Z
UnsignedShort BfmeScriptEngine_getPlayerMaskFromAsciiString::getPlayerMaskFromAsciiString(
	const AsciiString &name, Bool *found)
{
	if (found)
		*found = true;

	if (!TheScriptEngine->getCurrentPlayer())
		return 0;

	UnsignedShort mask = 0;
	Player *currentPlayer = TheScriptEngine->getCurrentPlayer();
	Int currentIndex = currentPlayer->getPlayerIndex();
	PlayerList *players = ThePlayerList;
	Player *localPlayer = players->getLocalPlayer();
	Int localIndex = localPlayer->getPlayerIndex();

	if (name.compare("<This Player's Enemies>") == 0)
	{
		mask = players->getPlayersWithRelationship(currentIndex, 4, false);
	}
	else if (name.compare("<This Player's Allies incl Self>") == 0)
	{
		mask = players->getPlayersWithRelationship(currentIndex, 3, false);
	}
	else if (name.compare("<This Player's Allies>") == 0)
	{
		mask = players->getPlayersWithRelationship(currentIndex, 2, false);
	}
	else if (name.compare("<This Player>") == 0)
	{
		Player *player = getCurrentPlayer();
		mask = player->getPlayerMask();
	}
	else if (name.compare("<This Player's Enemy>") == 0)
	{
		Player *player = getSkirmishEnemyPlayer();
		mask = player->getPlayerMask();
	}
	else if (name.compare("<Local Player>") == 0)
	{
		mask = localPlayer->getPlayerMask();
	}
	else if (name.compare("<Local Player's Enemies>") == 0)
	{
		mask = players->getPlayersWithRelationship(localIndex, 4, false);
	}
	else if (name.compare("<Local Player's Allies incl Self>") == 0)
	{
		mask = players->getPlayersWithRelationship(localIndex, 3, false);
	}
	else if (name.compare("<Local Player's Allies>") == 0)
	{
		mask = players->getPlayersWithRelationship(localIndex, 2, false);
	}
	else if (name.compare("<All Players>") == 0)
	{
		mask = bfmeGetPlayersMask(players);
	}
	else
	{
		if (found)
			*found = false;

		Player *player = ThePlayerList->findPlayerWithNameKey(NAMEKEY(name));
		if (player)
		{
			mask = player->getPlayerMask();
		}
		else
		{
			AsciiString message;
			message.format(AsciiString("***Invalid Player name: \"%s\"***"),
				name.str());
			AppendDebugMessage(message, false);
		}
	}

	return mask;
}
