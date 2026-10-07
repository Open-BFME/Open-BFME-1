// ?scriptPlayers002EF110AllOrMask@@YGXH@Z
// The caller and the player-mask callee chain identify this as the BFME
// player-mask action at the carved 0x002EF110 boundary.  The owner remains
// address-derived because no stronger source identity is witnessed.
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/player /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
#include "Precompiled/PreRTS.h"
#include "Common/Player.h"

typedef int Int;
typedef unsigned short PlayerMaskType;

// Retail ILT 0x0004B290 -> 0x0034CB60; use the thunk ledger owner because
// another emitter currently competes with the player-selector body name.
class ScriptEngine {};
extern void j_0004b290();

extern ScriptEngine* TheScriptEngine;

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
	// The matched callee proves const AsciiString&, bool*, and a 16-bit mask.
	typedef PlayerMaskType (ScriptEngine::*MaskCall)(const AsciiString &, bool *);
	union { void (*entry)(); MaskCall call; } mask = { j_0004b290 };
	PlayerMaskType playerMask = (TheScriptEngine->*mask.call)(
		*reinterpret_cast<const AsciiString *>(param), 0);

	if (!playerMask) {
		for (Int i = 0; i < ThePlayerList->getPlayerCount(); ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (!*reinterpret_cast<Int *>(
					reinterpret_cast<unsigned char *>(player) + 0x2c))
				player->setUnitsShouldIdleOrResume(true);
		}
		return;
	}

	do
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player)
			player->setUnitsShouldIdleOrResume(true);
	} while (playerMask);
}
