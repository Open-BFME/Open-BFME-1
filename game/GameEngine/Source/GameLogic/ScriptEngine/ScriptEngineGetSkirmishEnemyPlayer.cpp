// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/scriptenginevtable /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ScriptEngine::getSkirmishEnemyPlayer, RVA 0x0034C430, 69 bytes.
// Identity: ScriptEngine table 0x010E7A30 slot 18 -> ILT 0x00006E6F;
// native <This Player's Enemy> parser and the GeneralsMD ScriptEngine.cpp twin.
// See reverse/identity_evidence/0034c430-scriptengine-skirmishenemyplayer.md.
// Adopt the existing virtual declaration; its ZH data layout differs from BFME,
// so only independently witnessed retail offsets are read below.
#include "GameLogic/ScriptEngine.h"
#include "Common/PlayerList.h"

// Existing matched spelling for Player::getCurrentEnemy at RVA 0x000C9420.
class Rva000C9420 { public: int call(); };

Player *ScriptEngine::getSkirmishEnemyPlayer()
{
    // Same +0x170AC field as the independently identified getCurrentPlayer.
    Player *currentPlayer = *(Player **)((char *)this + 0x170ac);
    if (currentPlayer) {
        Player *enemy = (Player *)((Rva000C9420 *)currentPlayer)->call();
        if (enemy == 0) {
            for (int i = 0; i < ThePlayerList->getPlayerCount(); ++i) {
                enemy = ThePlayerList->getNthPlayer(i);
                // BFME +0x2C is the twin's human-player test; retain the offset
                // because no shared Player layout witness names this field.
                if (*(int *)((char *)enemy + 0x2c) == 0)
                    return enemy;
                // Keep the result live through the loop, as in the ZH twin.
                enemy = 0;
            }
        }
        return enemy;
    }
    return 0;
}
