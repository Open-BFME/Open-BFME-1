// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?resetIdleScan@TurretAIIdleState@@AAEXXZ: Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// Open-BFME5: TurretAIIdleState::resetIdleScan, retail 0x0018CAF0,
// zh_sweep packet 0018caf0.
//
// The reference body unchanged. Three things separated it from retail inside
// TurretAI.cpp, and the third is the interesting one:
//
//  - getTurretAI() reads [this+0x1C], not the vendored +0x20;
//  - the turret's data pointer is at [turret+0x44], not +0x38; from there the
//    chain is unchanged, +0x08 to the module data and +0x48 / +0x4C for the
//    minimum and maximum idle scan intervals;
//  - retail pushes 1278 as the __LINE__ argument of the random-value call
//    where the ported file supplies 1319. That is not a BFME difference at all,
//    just a line number: the reference file and the port have drifted apart by
//    41 lines above this function. A #line directive restores it, which is how
//    every retail __FILE__/__LINE__ immediate has to be handled.
//
// Its own TU because the first two are class layout, and because #line here
// would renumber everything below it in a shared file.

typedef int Int;
typedef unsigned int UnsignedInt;

Int GetGameLogicRandomValue( Int lo, Int hi, char *file, Int line );
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), (char *)__FILE__, __LINE__)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame( void ) const { return m_frame; }

private:
	unsigned char m_unreconstructed_00[0x3C];
	UnsignedInt m_frame;									///< +0x3C
};

extern GameLogic *TheGameLogic;

// The two hops between the turret and its module data are unnamed: retail
// proves the offsets, not what lives at them.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAIData
{
public:
	unsigned char m_unreconstructed_00[0x48];
	Int m_minIdleScanInterval;								///< +0x48
	Int m_maxIdleScanInterval;								///< +0x4C
};

class TurretAIModuleHolder
{
public:
	unsigned char m_unreconstructed_00[0x08];
	const TurretAIData *m_data;								///< +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAI
{
public:
	Int getMinIdleScanInterval( void ) const { return m_holder->m_data->m_minIdleScanInterval; }
	Int getMaxIdleScanInterval( void ) const { return m_holder->m_data->m_maxIdleScanInterval; }

private:
	unsigned char m_unreconstructed_00[0x44];
	TurretAIModuleHolder *m_holder;							///< +0x44
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAIIdleState
{
private:
	void resetIdleScan( void );

	TurretAI *getTurretAI( void ) const { return m_turretAI; }

	unsigned char m_unreconstructed_00[0x1C];
	TurretAI *m_turretAI;									///< +0x1C
	unsigned char m_unreconstructed_20[0x24 - 0x20];
	UnsignedInt m_nextIdleScan;								///< +0x24
};

//----------------------------------------------------------------------------------------------------------
// ?resetIdleScan@TurretAIIdleState@@AAEXXZ
#line 1275 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\TurretAI.cpp"
void TurretAIIdleState::resetIdleScan()
{
	UnsignedInt now = TheGameLogic->getFrame();
	UnsignedInt delay = GameLogicRandomValue(getTurretAI()->getMinIdleScanInterval(), getTurretAI()->getMaxIdleScanInterval());
	m_nextIdleScan = now + delay;
}
