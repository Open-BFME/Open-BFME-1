// ?scriptPlayers002EE4B0Set295@@YGXH@Z
// cl: /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/Errors.h"
#include "Common/DataChunk.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/Team.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
class ScriptEngine;
extern ScriptEngine* TheScriptEngine;
class AsciiString;
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name, bool *found);
};
typedef int (BfmeScriptEngine_getPlayerMaskFromAsciiString::*
	BfmePlayerMaskResolver)(const AsciiString &name, bool *found);
struct Rva002EE330Player { char m_pad[0x294]; unsigned char m_flag294; unsigned char m_flag295;  };
void __stdcall scriptPlayers002EE4B0Set295(int param)
{
	param = (((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)->*
		(BfmePlayerMaskResolver)&BfmeScriptEngine_getPlayerMaskFromAsciiString::getPlayerMaskFromAsciiString)(
			*(const AsciiString *)param, 0);
	while ((unsigned short)param) {
		Rva002EE330Player* player = (Rva002EE330Player *)ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&param);
		if (player)
			player->m_flag295 = 1;
	}
}
