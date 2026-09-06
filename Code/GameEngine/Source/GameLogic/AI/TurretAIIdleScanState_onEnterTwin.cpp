// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/turretai /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME7: near-miss twin of TurretAIIdleScanState::onEnter (dump target
// 0x0018CC60, near copy in the already-landed TurretAI.cpp: same file, same
// field offsets, only two operands + two __LINE__ immediates differ).
// TurretAI.cpp's own present-unmatched onEnter body resolves getTurretAI()
// through this tree's State::m_machine (+0x20) and TurretStateMachine::
// m_turretAI (+0x38) instead of retail's +0x1c/+0x44 (same shape as
// TurretAIHoldTurretState::onEnter, and the same struct-shim technique
// TurretAI.cpp's own TurretAIIdleState::resetIdleScan already uses for this
// exact offset pair). The two GameLogicRandomValue*() calls also push
// __LINE__ (1343, 1344 in retail) as a debug-log argument; this tree's
// current line numbering for those two statements is 1560/1561, so a
// #line pair (same trick as TurretAI.cpp's own resetIdleScan) restores
// retail's numbers and retail's __FILE__ string for just those two calls.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

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

// Same retail-offset shim technique as TurretAI.cpp's own
// TurretAIIdleState::resetIdleScan: State::m_machine at +0x1c (not this
// tree's +0x20), TurretStateMachine::m_turretAI at +0x44 (not +0x38).
// TurretAIData is a real, fully public class (GameLogic/TurretAI.h), so it
// is used as-is once reached through the retail-offset m_data pointer at
// TurretAI+0x08 (private in the real class, read here by raw offset).
struct Rva0018CC60TurretAI
{
	const TurretAIData *getData( void ) const { return m_data; }

	unsigned char m_pad_00[ 8 ];
	const TurretAIData *m_data;			///< retail this+0x08
};

struct Rva0018CC60TurretStateMachine
{
	Rva0018CC60TurretAI *getTurretAI( void ) const { return m_turretAI; }

	unsigned char m_pad_00[ 0x44 ];
	Rva0018CC60TurretAI *m_turretAI;			///< retail this+0x44
};

struct Rva0018CC60State
{
	Rva0018CC60TurretAI *getTurretAI( void ) const { return m_machine->getTurretAI(); }

	unsigned char m_unreconstructed_000[ 0x1c ];
	Rva0018CC60TurretStateMachine *m_machine;	///< retail this+0x1c
};

class Rva0018CC60IdleScanState : public State
{
public:
	StateReturnType onEnter();
protected:
	Real m_desiredAngle;
};

StateReturnType Rva0018CC60IdleScanState::onEnter()
{
	const Rva0018CC60State *self = reinterpret_cast<const Rva0018CC60State *>( this );

	Real minA = self->getTurretAI()->getData()->m_minIdleScanAngle;
	Real maxA = self->getTurretAI()->getData()->m_maxIdleScanAngle;
	if (minA == 0.0f && maxA == 0.0f)
		return STATE_SUCCESS;

#line 1343 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\TurretAI.cpp"
	m_desiredAngle = minA + GameLogicRandomValueReal(0, maxA - minA);
	if (GameLogicRandomValue( 0, 1 ) == 0)
#line 1631
		m_desiredAngle = -m_desiredAngle;

	return STATE_CONTINUE;
}
