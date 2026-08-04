// cl: /DNDEBUG /MD /EHs-c-
// Lift the ScriptActions::doGiveMoney __emit thunk to clean C++.
//
// Zero Hour resolves one Player from the name and adjusts its money. BFME
// generalised it: the name resolves to a 16-bit player mask, and the body walks
// every player in that mask. All four callees were already pinned by earlier
// work, and their signatures settle the shape -- getEachPlayerFromMask takes the
// mask by reference (AAG) and consumes it, which is what makes the trailing
// `cmp word ptr [esp+8], 0` the loop condition.
//
// Money sits inline at Player+0x48, so getMoney() is a lea; the null test that
// follows is dead but retail emits it, so the ZH `if (!m) return;` stays.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class AsciiString;

class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, bool playSound);	///< ILT thunk at 0x00041894
	void deposit(UnsignedInt amount, bool playSound);			///< ILT thunk at 0x00027D6D
};

class Player
{
public:
	Money *getMoney(void) { return &m_money; }

private:
	unsigned char m_unreconstructed_00[0x48];
	Money m_money;												///< retail this+0x48
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);			///< ILT thunk at 0x0002EE60
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name, bool *unused);	///< ILT thunk at 0x0004B290
};

extern BfmeScriptEngine_getPlayerMaskFromAsciiString *TheScriptEngine;	///< retail [0x012F076C]
extern PlayerList *ThePlayerList;										///< retail [0x012ED748]

class ScriptActions
{
protected:
	void doGiveMoney(const AsciiString &, Int);
};

// ?doGiveMoney@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doGiveMoney(const AsciiString &playerName, Int money)
{
	UnsignedShort mask = TheScriptEngine->getPlayerMaskFromAsciiString(playerName, 0);
	if (mask == 0)
	{
		return;
	}

	do
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
		{
			Money *m = player->getMoney();
			if (m)
			{
				if (money < 0)
					m->withdraw(-money, true);
				else
					m->deposit(money, true);
			}
		}
	} while (mask != 0);
}
