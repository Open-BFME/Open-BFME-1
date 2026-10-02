// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameLogic/Module/UpdateModule.h"

// AODCrushCollide update-interface receiver at complete-object +0x10.
// Identity: targets/game/reverse/identity_evidence/update-slot0.md.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged();
	char m_unmodelled_000[ 0x114 ];
	unsigned int m_modelConditions;
};

struct GameLogicFrameSlice
{
	char m_unmodelled_000[ 0x3c ];
	unsigned int m_frame;
};

class GameLogic;
extern GameLogic *TheGameLogic;

class Rva00216100TimedCondition
{
public:
	char m_unmodelled_000[ 0x14 ];
	unsigned int m_expirationFrame;
	char m_unmodelled_018[ 4 ];
	bool m_active;
};

// No complete AODCrushCollide header exists; only this interface receiver
// and the pre-existing address-kept state view are declared here.
class AODCrushCollide
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime AODCrushCollide::update()
{
	Rva00216100TimedCondition *state = reinterpret_cast<Rva00216100TimedCondition *>(this);
	if( state->m_active )
	{
		if( state->m_expirationFrame < ((GameLogicFrameSlice *)TheGameLogic)->m_frame )
		{
			Object *object = *(Object **)( (char *)this - 8 );
			if( object->m_modelConditions & 0x100 )
			{
				object->m_modelConditions &= ~0x100;
				object->notifyModelConditionChanged();
			}
			state->m_active = false;
		}
		return UPDATE_SLEEP_NONE;
	}
	return UPDATE_SLEEP_FOREVER;
}
