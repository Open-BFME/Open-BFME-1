// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// FILE: DozerAIUpdate_privateResumeConstructionTwin.cpp /////////////////////////////////////////////
// Desc:   Twin body for DozerAIUpdate::privateResumeConstruction: BFME's layout puts
//         m_object at module+0x08 and the DozerAIInterface base at this+0x340 (same
//         pattern DozerAIUpdate::privateRepair uses a few lines above it in the
//         landed DozerAIUpdate.cpp), rather than the ZH-layout getObject()/newTask()
//         virtual-call shape the tracked TU still carries (marked present-unmatched
//         there; left untouched).
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/Team.h"
#include "Common/StateMachine.h"
#include "Common/BuildAssistant.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/Money.h"
#include "Common/Radar.h"
#include "Common/RandomValue.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/Xfer.h"
#include "vector3.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/Module/CreateModule.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameClient/InGameUI.h"

// ------------------------------------------------------------------------------------------------
/** Resume construction on a building (BFME layout twin) */
// ------------------------------------------------------------------------------------------------
// ?privateResumeConstruction@DozerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z
void DozerAIUpdate::privateResumeConstruction( Object *obj, CommandSourceType cmdSource )
{

	// sanity
	if( obj == NULL )
		return;

	// Same BFME layout as privateRepair(): m_object at module+0x08, and the
	// DozerAIInterface base at this+0x340 (newTask is slot 12 of that base).
	Object *dozer = *(Object **)((char *)this + 0x08);
	if( TheActionManager->canResumeConstructionOf( dozer, obj, cmdSource ) == FALSE )
		return;

	// start the new task for construction
	((DozerAIInterface *)((char *)this + 0x340))->newTask( DOZER_TASK_BUILD, obj );

}  // end privateResumeConstruction
