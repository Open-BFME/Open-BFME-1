// ?translateGameMessage@HintSpyTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.79 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/MessageStream.h"
#include "GameClient/HintSpy.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"

// The BFME message values are witnessed by message_stream_commandName.cpp;
// Zero Hour's HintSpy switch predates its extra messages and has lower values.
GameMessageDisposition HintSpyTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	switch (static_cast<int>(msg->getType()))
	{
	case 148: // MSG_MOUSEOVER_DRAWABLE_HINT
		{
			TheInGameUI->createMouseoverHint(msg);
			disp = DESTROY_MESSAGE;
		}
		break;
	case 149: // MSG_MOUSEOVER_LOCATION_HINT
		{
			TheInGameUI->createMouseoverHint(msg);
			disp = DESTROY_MESSAGE;
		}
		break;
	case 173: // MSG_DEFECTOR_HINT
		disp = DESTROY_MESSAGE;
	case 165: // MSG_DO_MOVETO_HINT
	case 166: // MSG_DO_ATTACKMOVETO_HINT
	case 153: // MSG_DO_ATTACK_OBJECT_HINT
	case 178: // MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT
	case 155: // MSG_DO_FORCE_ATTACK_OBJECT_HINT
	case 156: // MSG_DO_FORCE_ATTACK_GROUND_HINT
	case 167: // MSG_ADD_WAYPOINT_HINT
	case 157: // MSG_GET_REPAIRED_HINT
	case 163: // MSG_DOCK_HINT
	case 158: // MSG_GET_HEALED_HINT
	case 159: // MSG_DO_REPAIR_HINT
	case 160: // MSG_RESUME_CONSTRUCTION_HINT
	case 161: // MSG_ENTER_HINT
	case 168: // MSG_HIJACK_HINT
	case 170: // MSG_CONVERT_TO_CARBOMB_HINT
	case 150: // MSG_VALID_GUICOMMAND_HINT
	case 151: // MSG_INVALID_GUICOMMAND_HINT
	case 171: // MSG_CAPTUREBUILDING_HINT
	case 174: // MSG_SET_RALLY_POINT_HINT
	case 175: // MSG_IMPOSSIBLE_ATTACK_HINT
	case 176: // MSG_DO_SALVAGE_HINT
	case 177: // MSG_DO_INVALID_HINT
	case 154:
	case 162: // MSG_CONTEST_HINT
	case 164: // MSG_HARVEST_HINT
	case 2006: case 2007: case 2008:
		TheInGameUI->createCommandHint(msg);
		disp = DESTROY_MESSAGE;
		break;
	case 152: // MSG_AREA_SELECTION_HINT
		TheInGameUI->beginAreaSelectHint(msg);
		break;
	case 1059: // MSG_AREA_SELECTION
		TheInGameUI->endAreaSelectHint(msg);
		break;
	case 1070: case 1071: case 1072:
		TheInGameUI->createMoveHint(msg);
		break;
	case 1060: // MSG_DO_ATTACK_OBJECT
		TheInGameUI->createAttackHint(msg);
		break;
	case 1061: case 1062:
		TheInGameUI->createForceAttackHint(msg);
		break;
	case 1067: // MSG_ENTER
		TheInGameUI->createGarrisonHint(msg);
		break;
	}
	return disp;
}
