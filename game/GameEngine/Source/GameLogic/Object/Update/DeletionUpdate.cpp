// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
#include "PreRTS.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/DeletionUpdate.h"

// ?d_0028c6e0@@YAXXZ
void DeletionUpdate::setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames)
{
	UnsignedInt delay = calcSleepDelay(minFrames, maxFrames);
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 0x08);
	setWakeFrame(object, UPDATE_SLEEP(delay));
}

UnsignedInt DeletionUpdate::calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames)
{
#line 55 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\DeletionUpdate.cpp"
	UnsignedInt delay = GameLogicRandomValue(minFrames, maxFrames);
	if (delay < 1)
		delay = 1;
	m_dieFrame = TheGameLogic->getFrame() + delay;
	return delay;
}
