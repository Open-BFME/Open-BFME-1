// ?scriptPlayers002EF110AllOrMask@@YGXH@Z
// The caller and the player-mask callee chain identify this as the BFME
// player-mask action at the carved 0x002EF110 boundary.  The owner remains
// address-derived because no stronger source identity is witnessed.
typedef int Int;
typedef unsigned short PlayerMaskType;

class ScriptEngine
{
public:
	Int resolvePlayerMask(Int param, Int flag);
};
extern ScriptEngine* TheScriptEngine;

class Player
{
public:
};

class Rva002EE330Player
{
public:
	void onScript002EF110(Int flag);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
	Player *getNthPlayer(Int index);

	Int getPlayerCount() const
	{
		return m_playerCount;
	}

	unsigned char m_beforePlayerCount[0x10];
	Int m_playerCount;
};

extern PlayerList *ThePlayerList;

void __stdcall scriptPlayers002EF110AllOrMask(Int param)
{
	PlayerMaskType playerMask =
		TheScriptEngine->resolvePlayerMask(param, 0);
	if (!playerMask) {
		for (Int i = 0; i < ThePlayerList->getPlayerCount(); ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (!*reinterpret_cast<Int *>(
					reinterpret_cast<unsigned char *>(player) + 0x2c))
				reinterpret_cast<Rva002EE330Player *>(player)->onScript002EF110(1);
		}
		return;
	}

	do
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player)
			reinterpret_cast<Rva002EE330Player *>(player)->onScript002EF110(1);
	} while (playerMask);
}
