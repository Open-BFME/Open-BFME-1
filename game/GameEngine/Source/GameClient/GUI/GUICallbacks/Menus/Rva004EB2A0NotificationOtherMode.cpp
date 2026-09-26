// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob2 /Iinputs/reference/shims/stringinline

// BFME notification renderer selected by game type 5, retail 0x004EB2A0.
// The matched dispatcher at 0x004EBA70 proves the by-value string ABI.  This
// is the in-game-chat fragment also present in Zero Hour's
// ConnectionManager::processChat: recover the player represented by the local
// GameSlot, suppress observer/dead and muted chat, and use that player's color.

#include "StringInline.h"

typedef int Int;
typedef unsigned short WideChar;
typedef bool Bool;

inline const unsigned short *UnicodeString::str() const
{
	return m_data ? m_data->m_text : L"";
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// BFME retains the Unicode display name at +0x28 and adds the narrow internal
// player name at +0x2C.  NetGameCommandMsg::constructGameMessage independently
// proves that the latter is fed to NameKeyGenerator in this same way.
class GameSlot
{
public:
	Bool isMuted() const { return m_isMuted; }
	const AsciiString &getInternalPlayerName() const { return m_internalPlayerName; }

private:
	unsigned char m_head[0x0A];
	Bool m_isMuted;
	unsigned char m_toInternalName[0x2C - 0x0B];
	AsciiString m_internalPlayerName;
};

class GameInfo
{
public:
	virtual Int bfmeSlot00();
	virtual Int bfmeSlot04();
	virtual void reset();
	virtual void startGame(Int gameID);
	virtual Bool amIHost() const;
	virtual Int getLocalSlotNum() const;

	GameSlot *getSlot(Int slot);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Player
{
public:
	Bool isPlayerActive() const;
	Int getPlayerColor() const { return m_playerColor; }

private:
	unsigned char m_head[0x1C4];
	Int m_playerColor;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};

struct RGBColor
{
	float red;
	float green;
	float blue;

	void setFromInt(Int color);
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void messageColor(const RGBColor *rgbColor, UnicodeString format, ...);
	virtual void message(UnicodeString format, ...);
	virtual void message(AsciiString format, ...);
};

extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern InGameUI *TheInGameUI;

void bfme_notificationOtherMode(AsciiString nick, UnicodeString message)
{
	Int playerID = TheGameInfo->getLocalSlotNum();
	AsciiString playerName = TheGameInfo->getSlot(playerID)->getInternalPlayerName();
	Player *player = ThePlayerList->findPlayerWithNameKey(
		TheNameKeyGenerator->nameToKey(playerName.str()));
	if (!player)
	{
		TheInGameUI->message(UnicodeString(L"%s"), message.str());
		return;
	}

	Bool fromObserver = !player->isPlayerActive();
	if (!fromObserver && !TheGameInfo->getSlot(playerID)->isMuted())
	{
		RGBColor rgb;
		rgb.setFromInt(player->getPlayerColor());
		TheInGameUI->messageColor(&rgb, UnicodeString(L"%s"), message.str());
	}
}
