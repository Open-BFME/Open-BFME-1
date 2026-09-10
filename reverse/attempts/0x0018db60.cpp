// ??0TurretStateMachine@@QAE@PAVTurretAI@@PAVObject@@VAsciiString@@@Z
// partial score=0.4 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/turretai /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
//
// Command & Conquer Generals Zero Hour(tm)
// Copyright 2025 Electronic Arts Inc.
//
// This file is GPLv3-or-later.  The clean body follows the upstream
// GeneralsMD TurretStateMachine constructor, with the BFME TurretAI shim
// supplying the retail layout and vtable declarations.

#include "PreRTS.h"

#define DEFINE_WEAPONSLOTTYPE_NAMES

#include "Common/GameAudio.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"

// ??0TurretStateMachine@@QAE@PAVTurretAI@@PAVObject@@VAsciiString@@@Z
// Retail boundary: 0x0018DB84..0x0018DE15 (658 bytes).  The class owner is
// established by the TurretStateMachine header, the five matched TurretState
// child constructors, and the corresponding GeneralsMD constructor.
TurretStateMachine::TurretStateMachine(TurretAI *tai, Object *obj, AsciiString name) :
	 m_turretAI(tai), StateMachine(obj, name)
{
	static const StateConditionInfo fireConditions[] =
	{
		StateConditionInfo(outOfWeaponRangeObject, TURRETAI_AIM, NULL),
		StateConditionInfo(NULL, NULL, NULL)
	};

	defineState(TURRETAI_IDLE,
		newInstance(TurretAIIdleState)(this), TURRETAI_IDLE, TURRETAI_IDLESCAN);
	defineState(TURRETAI_IDLESCAN,
		newInstance(TurretAIIdleScanState)(this), TURRETAI_HOLD, TURRETAI_HOLD);
	defineState(TURRETAI_AIM,
		newInstance(TurretAIAimTurretState)(this), TURRETAI_FIRE, TURRETAI_HOLD);
	defineState(TURRETAI_FIRE,
		newInstance(AIAttackFireWeaponState)(this, tai),
		TURRETAI_AIM, TURRETAI_AIM, fireConditions);
	defineState(TURRETAI_RECENTER,
		newInstance(TurretAIRecenterTurretState)(this),
		TURRETAI_IDLE, TURRETAI_IDLE);
	defineState(TURRETAI_HOLD,
		newInstance(TurretAIHoldTurretState)(this),
		TURRETAI_RECENTER, TURRETAI_RECENTER);
}
