// cl: /DNDEBUG /MD
//
// The one-argument body at retail 0x002EEDA0, a complete carved extent.
//
// WHAT THE BYTES SHOW.  `ret 4` with the argument read from [esp+4] and ecx
// never used as a receiver: __stdcall taking one reference.  It asks
// TheScriptEngine for a sixteen-bit player mask, and the mask decides the
// shape.  A zero mask walks every player by index through the matched
// PlayerList::getNthPlayer and reveals for the INDEX; a non-zero mask consumes
// itself through the matched PlayerList::getEachPlayerFromMask, which takes the
// mask BY REFERENCE -- that is why the mask lives in a stack slot -- and
// reveals for each returned player's own +0x24 field instead.  Both arms call
// the matched PartitionManager::revealMapForPlayer.
//
// THE GLOBALS KEEP THE NAMES THE LEDGER ALREADY PINS at their addresses.  The
// player-list global is retail's, so it uses EA's own spelling and type
// (ThePlayerList); the shroud manager's is address-derived
// (Rva002EEDA0TheShroudManager), so that receiver is cast rather than renamed.
// The calls prove what those objects are -- a PlayerList and a
// PartitionManager -- and renaming the address-derived global is a separate
// change.
//
// IDENTITY IS NOT RECOVERED for the function itself; the name is derived from
// its address.

class AsciiString;

class Player
{
public:
	char m_lead[0x24];
	int m_playerIndex;
	char m_gap28[4];
	int m_field2c;
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name, bool *matchedAll);
};

class PartitionManager
{
public:
	void revealMapForPlayer(int playerIndex);
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

// Rva002EE330PlayerList is this TU's view of retail's player-list global at
// 0x012ED748 (its +0x10 player count).  The global itself carries its
// canonical spelling, so this TU links against
// game/GameEngine/Source/Common/RTS/PlayerList.cpp's definition.
struct Rva002EE330PlayerList
{
	char m_lead[0x10];
	int m_playerCount;
};

extern PlayerList *ThePlayerList;

struct Rva002EEDA0ShroudManager;
class ShroudManager;
extern ShroudManager *TheShroudManager;


// ?rva002EEDA0@@YGXABVAsciiString@@@Z
void __stdcall rva002EEDA0(const AsciiString &name)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(name, 0);

	if (mask == 0)
	{
		for (int i = 0; i < ((Rva002EE330PlayerList *)ThePlayerList)->m_playerCount; i++)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->m_field2c == 0)
				((PartitionManager *)(*reinterpret_cast<Rva002EEDA0ShroudManager **>(&TheShroudManager)))->revealMapForPlayer(i);
		}
	}
	else
	{
		while (mask != 0)
		{
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (player != 0)
				((PartitionManager *)(*reinterpret_cast<Rva002EEDA0ShroudManager **>(&TheShroudManager)))
					->revealMapForPlayer(player->m_playerIndex);
		}
	}
}
