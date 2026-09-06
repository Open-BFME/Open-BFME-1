// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/turretai /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME7: near-miss twin of TurretAIHoldTurretState::onEnter (dump
// target 0x0018CD60, near copy in the already-landed TurretAI.cpp: same
// file, same field offsets, only two operands differ). The in-file
// present-unmatched onEnter body reaches TurretStateMachine through
// TurretState::getTurretAI() -> ((TurretStateMachine*)getMachine())->
// getTurretAI(), which resolves to this tree's State::m_machine offset
// (+0x20) and this tree's TurretStateMachine::m_turretAI offset (+0x38).
// Retail keeps State::m_machine at +0x1c (same delta already fixed for
// AIDock.cpp's bfmeRetailMachine helper) and TurretStateMachine::m_turretAI
// at +0x44 (same +0xc delta as AIDockMachine::m_approachPosition). This is
// a byte-exact twin under an address-tagged name so it does not collide
// with the real mangled symbol already defined (with the wrong offsets) in
// TurretAI.cpp.
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

// Same static helper as TurretAI.cpp's own file-local frameToSleepTime;
// duplicated here since it is file-local (static) in the tracked TU.
static StateReturnType Rva0018CD60_frameToSleepTime(
	UnsignedInt frame1,
	UnsignedInt frame2 = FOREVER,
	UnsignedInt frame3 = FOREVER,
	UnsignedInt frame4 = FOREVER
)
{
	if (frame1 > frame2) frame1 = frame2;
	if (frame1 > frame3) frame1 = frame3;
	if (frame1 > frame4) frame1 = frame4;
	UnsignedInt now = TheGameLogic->getFrame();
	if (frame1 > now)
	{
		return STATE_SLEEP(frame1 - now);
	}
	else
	{
		return STATE_CONTINUE;
	}
}

// Retail-offset replica of TurretStateMachine: only m_turretAI (at +0x44,
// not this tree's +0x38) is needed here.
class Rva0018CD60TurretStateMachine
{
public:
	TurretAI *getTurretAI() const { return m_turretAI; }
private:
	char m_pad_00[0x44];
	TurretAI *m_turretAI;	// +0x44
};

static Rva0018CD60TurretStateMachine *Rva0018CD60GetMachine( const State *state )
{
	// retail: State::m_machine is at +0x1c, not this tree's +0x20.
	return *(Rva0018CD60TurretStateMachine **)((char *)state + 0x1C);
}

class Rva0018CD60State : public State
{
public:
	StateReturnType onEnter();
protected:
	UnsignedInt m_timestamp;	///< frame this state was last entered
};

StateReturnType Rva0018CD60State::onEnter()
{
	m_timestamp = Rva0018CD60GetMachine( this )->getTurretAI()->getRecenterTime() + TheGameLogic->getFrame();

	TurretAI *turret = Rva0018CD60GetMachine( this )->getTurretAI();

	// friend_getNextIdleMoodTargetFrame() is defined in the tracked
	// TurretAI.cpp TU, so calling it here would always be a real
	// cross-TU call (no LTCG in this pipeline); inline its body by hand
	// (same retail Object::m_ai at +0x204, AIUpdateInterface::
	// m_nextMoodCheckTime at +0x1fc as that function already documents).
	const Object *obj = turret->getOwner();
	const void *ai = *(const void * const *)((const char *)obj + 0x204);
	UnsignedInt nextIdleMoodTargetFrame = ai ? *(const UnsignedInt *)((const char *)ai + 0x1fc) : TheGameLogic->getFrame();

	return Rva0018CD60_frameToSleepTime( nextIdleMoodTargetFrame, m_timestamp );
}
