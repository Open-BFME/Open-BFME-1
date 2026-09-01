// ?scanClosestTarget@AutoFindHealingUpdate@@QAEPAVObject@@XZ
// partial score=0.62 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "GameLogic/Module/AutoFindHealingUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectIter.h"
#include "GameLogic/PartitionManager.h"

Object *AutoFindHealingUpdate::scanClosestTarget()
{
	const AutoFindHealingUpdateModuleData *data =
		*reinterpret_cast<const AutoFindHealingUpdateModuleData **>(
			reinterpret_cast<char *>(this) + 4);
	Object *me = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 8);
	Object *bestTarget = NULL;
	Real closestDistSqr = 0;

	SimpleObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(
		me->getPosition(), data->m_scanRange, FROM_CENTER_2D);
	MemoryPoolObjectHolder hold(iter);

	for (Object *other = iter->first(); other; other = iter->next()) {
		if (!other->isKindOf(KINDOF_HEAL_PAD))
			continue;

		Real distSqr = ThePartitionManager->getDistanceSquared(me, other, FROM_CENTER_2D);
		if (bestTarget == NULL || distSqr < closestDistSqr) {
			bestTarget = other;
			closestDistSqr = distSqr;
		}
	}

	return bestTarget;
}
