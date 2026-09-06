// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/turretai /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Open-BFME7: near-miss twin of TurretAI::removeSelfAsTargeter (dump target
// 0x0018C880, near copy in the already-landed TurretAI.cpp: same file, same
// field offsets, only two operands differ). TurretAI.cpp's own
// present-unmatched removeSelfAsTargeter body calls target->getAI() and
// targetAI->addTargeter(...) through this tree's normal accessors, which
// resolve to this tree's Object::getAI() field offset (+0x19c) and this
// tree's AIUpdateInterface vtable slot for addTargeter (+0x178). Retail
// keeps the AI update interface at Object+0x204 (same delta already fixed
// for AIDock.cpp's bfmeRetailAIUpdate helper) and calls addTargeter through
// vtable+0x1cc (21 extra filler slots ahead of it, same insertion family as
// AIDock.cpp's BFMERetailAIUpdateVTable, which only needed to name a slot at
// +0x144/81 fillers). This is a byte-exact twin under an address-tagged
// name so it does not collide with the real mangled symbol already defined
// (with the wrong offsets) in TurretAI.cpp.
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

// Same private-field layout trick as TurretAI.cpp's own
// BFMETurretTargetAccessor: reinterpret_cast a TurretAI* to reach the
// private m_turretStateMachine/m_target fields without touching the real
// (tracked) class declaration. m_owner is reached through the real,
// already-public TurretAI::getOwner() instead of guessing its offset (this
// tree's TurretAI has extra base-class vtable pointers ahead of its own
// data members, so a hand-counted field offset would not be reliable).
class Rva0018C880RetailAIUpdateVTable
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10c() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11c() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12c() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13c() = 0;
	virtual void slot140() = 0;
	virtual void slot144() = 0;
	virtual void slot148() = 0;
	virtual void slot14c() = 0;
	virtual void slot150() = 0;
	virtual void slot154() = 0;
	virtual void slot158() = 0;
	virtual void slot15c() = 0;
	virtual void slot160() = 0;
	virtual void slot164() = 0;
	virtual void slot168() = 0;
	virtual void slot16c() = 0;
	virtual void slot170() = 0;
	virtual void slot174() = 0;
	virtual void slot178() = 0;
	virtual void slot17c() = 0;
	virtual void slot180() = 0;
	virtual void slot184() = 0;
	virtual void slot188() = 0;
	virtual void slot18c() = 0;
	virtual void slot190() = 0;
	virtual void slot194() = 0;
	virtual void slot198() = 0;
	virtual void slot19c() = 0;
	virtual void slot1a0() = 0;
	virtual void slot1a4() = 0;
	virtual void slot1a8() = 0;
	virtual void slot1ac() = 0;
	virtual void slot1b0() = 0;
	virtual void slot1b4() = 0;
	virtual void slot1b8() = 0;
	virtual void slot1bc() = 0;
	virtual void slot1c0() = 0;
	virtual void slot1c4() = 0;
	virtual void slot1c8() = 0;
	virtual void addTargeter( ObjectID id, Bool add ) = 0;	///< +0x1cc
};

class Rva0018C880TargetAccessor
{
public:
	TurretStateMachine *getTurretStateMachineField() const { return m_turretStateMachine; }
	TurretTargetType getTargetField() const { return m_target; }

private:
	char                    m_pad_00[0x14];			// this+0x00 .. +0x13, untouched
	TurretStateMachine     *m_turretStateMachine;		// this+0x14
	char                    m_pad_18[0x98 - 0x18];
	mutable TurretTargetType m_target;				// this+0x98
};

class Rva0018C880TurretAI
{
public:
	void removeSelfAsTargeter();
};

void Rva0018C880TurretAI::removeSelfAsTargeter()
{
	TurretAI *realSelf = reinterpret_cast<TurretAI *>( this );
	const Rva0018C880TargetAccessor *self = reinterpret_cast<const Rva0018C880TargetAccessor *>( this );

	// be paranoid, in case we are called from dtors, etc.
	if (self->getTargetField() == TARGET_OBJECT && self->getTurretStateMachineField() != NULL)
	{
		Object *selfObj = realSelf->getOwner();
		Object *target = self->getTurretStateMachineField()->getGoalObject();
		if (selfObj != NULL && target != NULL)
		{
			// retail: Object's AI update interface lives at +0x204, not this
			// tree's +0x19c (same fix as AIDock.cpp's bfmeRetailAIUpdate).
			AIUpdateInterface *targetAI = *(AIUpdateInterface **)((char *)target + 0x204);
			if (targetAI)
			{
				// retail: addTargeter is at vtable+0x1cc (116 slots), not
				// this tree's +0x178 (94 slots) -- same filler-vtable
				// technique as AIDock.cpp's BFMERetailAIUpdateVTable.
				reinterpret_cast<Rva0018C880RetailAIUpdateVTable *>( targetAI )->addTargeter( selfObj->getID(), false );
			}
		}
	}
}
