// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"

class ScriptEngine;
extern ScriptEngine* TheScriptEngine;
// ILT 0x0004B290 routes to the matched selector resolver at 0x0034CB60.
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString& name, bool* found);
};

// ?scriptPlayers002EE2D0Call11@@YGXH@Z
void __stdcall scriptPlayers002EE2D0Call11(int param)
{
	unsigned short mask = ((BfmeScriptEngine_getPlayerMaskFromAsciiString*)TheScriptEngine)->getPlayerMaskFromAsciiString(*(const AsciiString*)param, 0);
	while (mask) {
		Player* player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->setUnitsShouldHunt(true, CMD_FROM_SCRIPT);
	}
}
