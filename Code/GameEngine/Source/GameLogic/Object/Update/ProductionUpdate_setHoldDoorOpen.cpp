// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"

#include "Common/ModelState.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/ProductionUpdate.h"

static const ModelConditionFlagType theOpeningFlags[DOOR_COUNT_MAX] =
{
	MODELCONDITION_DOOR_1_OPENING,
	MODELCONDITION_DOOR_2_OPENING,
	MODELCONDITION_DOOR_3_OPENING,
	MODELCONDITION_DOOR_4_OPENING
};

void ProductionUpdate::setHoldDoorOpen(ExitDoorType exitDoor, Bool holdIt)
{
	struct BfmeDoorInfo
	{
		UnsignedInt m_doorOpenedFrame;
		UnsignedInt m_doorWaitOpenFrame;
		UnsignedInt m_doorClosedFrame;
		Bool m_holdOpen;
		UnsignedByte m_padding[3];
	};
	struct BfmeModelConditionFlags
	{
		UnsignedInt m_bits[10];
		__forceinline void set(ModelConditionFlagType flag)
		{
			m_bits[(UnsignedInt)flag >> 5] |= 1 << ((UnsignedInt)flag & 31);
		}
	};
	struct BfmeProductionUpdateLayout
	{
		UnsignedByte m_padding0[0x3c];
		BfmeDoorInfo m_doors[DOOR_COUNT_MAX];
		BfmeModelConditionFlags m_clearFlags;
		BfmeModelConditionFlags m_setFlags;
		Bool m_flagsDirty;
	};

	if (exitDoor >= DOOR_1 && exitDoor < DOOR_COUNT_MAX)
	{
		BfmeProductionUpdateLayout *update = reinterpret_cast<BfmeProductionUpdateLayout *>(this);
		BfmeDoorInfo& door = update->m_doors[exitDoor];
		door.m_holdOpen = holdIt;
		if (holdIt && door.m_doorOpenedFrame == 0 && door.m_doorWaitOpenFrame == 0 && door.m_doorClosedFrame == 0)
		{
			door.m_doorOpenedFrame = TheGameLogic->getFrame();
			update->m_setFlags.set( theOpeningFlags[exitDoor] );
			update->m_flagsDirty = TRUE;
		}
	}
}
