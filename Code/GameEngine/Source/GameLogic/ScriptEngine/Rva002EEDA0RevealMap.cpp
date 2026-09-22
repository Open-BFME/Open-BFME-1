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
// THE GLOBALS KEEP THE NAMES THE LEDGER ALREADY PINS at their addresses, which
// are address-derived (Rva002EE330ThePlayers, Rva002EEDA0TheShroudManager), so
// the receivers are cast rather than renamed.  The calls prove what those
// objects are -- a PlayerList and a PartitionManager -- but renaming a pinned
// global is a separate change.
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

struct Rva002EE330PlayerList
{
	char m_lead[0x10];
	int m_playerCount;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

struct Rva002EEDA0ShroudManager;
extern Rva002EEDA0ShroudManager *Rva002EEDA0TheShroudManager;

// ?rva002EEDA0@@YGXABVAsciiString@@@Z
void __stdcall rva002EEDA0(const AsciiString &name)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(name, 0);

	if (mask == 0)
	{
		for (int i = 0; i < Rva002EE330ThePlayers->m_playerCount; i++)
		{
			Player *player = ((PlayerList *)Rva002EE330ThePlayers)->getNthPlayer(i);
			if (player->m_field2c == 0)
				((PartitionManager *)Rva002EEDA0TheShroudManager)->revealMapForPlayer(i);
		}
	}
	else
	{
		while (mask != 0)
		{
			Player *player =
				((PlayerList *)Rva002EE330ThePlayers)->getEachPlayerFromMask(mask);
			if (player != 0)
				((PartitionManager *)Rva002EEDA0TheShroudManager)
					->revealMapForPlayer(player->m_playerIndex);
		}
	}
}
