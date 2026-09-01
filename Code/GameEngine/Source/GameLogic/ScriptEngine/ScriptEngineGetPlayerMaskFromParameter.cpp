// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of the player-parameter mask resolver at retail RVA
// 0x0034DB40.  The address-derived name is intentional: the call site proves
// the owning ScriptEngine object and Parameter * ABI, but no surviving source
// proves the original member name.
//
// Parameter's BFME layout differs from Zero Hour here.  Its selector string is
// at +0x10 and a cached concrete player mask lives at +0x20.  Dynamic selectors
// such as "<This Player>" must not be cached, because ScriptEngine's current
// player can change between calls.

typedef bool Bool;
typedef unsigned short PlayerMaskType;

template <typename Char>
class StringBase
{
public:
	int compare(const Char *) const;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &);
	~AsciiString();

private:
	void *m_data;
};

class Player
{
public:
	PlayerMaskType getPlayerMask() const
	{
		return (PlayerMaskType)(1 << m_playerIndex);
	}

private:
	unsigned char m_pad00[0x24];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType);
};

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned int getCachedPlayerMask() const { return m_cachedPlayerMask; }
	void setCachedPlayerMask(PlayerMaskType mask) { m_cachedPlayerMask = mask; }

private:
	unsigned char m_pad00[0x10];
	AsciiString m_string;
	unsigned char m_pad14[0x0c];
	unsigned int m_cachedPlayerMask;
};

class ScriptEngine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual Player *getCurrentPlayer();

	PlayerMaskType unidentified_0034DB40(Parameter *);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &, Bool *);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *g_mgr12ED748;

PlayerMaskType ScriptEngine::unidentified_0034DB40(Parameter *parameter)
{
	if (!TheScriptEngine->getCurrentPlayer()) {
		return 0;
	}

	PlayerMaskType mask = 0;
	if (parameter->getCachedPlayerMask()) {
		Player *player = g_mgr12ED748->getPlayerFromMask(
			(PlayerMaskType)parameter->getCachedPlayerMask());
		if (player) {
			mask = player->getPlayerMask();
		}
	} else {
		AsciiString playerName = parameter->getString();
		Bool matchedSpecialName;
		mask = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(playerName, &matchedSpecialName);
		if (!matchedSpecialName &&
			((const StringBase<char> *)&playerName)->compare("<This Player>") != 0) {
			parameter->setCachedPlayerMask(mask);
		}
	}

	return mask;
}
