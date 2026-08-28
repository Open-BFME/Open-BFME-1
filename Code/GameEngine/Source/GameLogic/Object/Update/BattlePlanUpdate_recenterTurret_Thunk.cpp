// cl: /DNDEBUG /MD /EHsc
// readable body of ?recenterTurret@BattlePlanUpdate@@IAEXXZ: Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp
// Open-BFME5: BattlePlanUpdate::recenterTurret, retail 0x002858B0.
//
// The Zero Hour body unchanged. Two offsets are BFME's:
//
//   m_object       module+0x08   BattlePlanUpdate.cpp lands it at +0x0c
//   Object::m_ai   Object+0x204  that tree puts it at +0x19c
//
// The first is the BFME_MODULE_NO_MPO layout -- Module without its
// MemoryPoolObject base -- but that define cannot be switched on for
// BattlePlanUpdate.cpp: the members ?getActiveBattlePlan@BattlePlanUpdate@@
// reads are pinned to the wider one, and it stops matching. Pinning the two
// offsets inside that file works for this body but shifts its EH funclet rows
// (uw_00c10d88 and uw_00c10d93), so the body lives here instead.
//
// m_ai at +0x204 is the same offset TurretAI::loadPostProcess and
// friend_getNextIdleMoodTargetFrame reach, and what
// reference/shims/bfmeobject records.

enum WhichTurretType
{
	TURRET_INVALID = -1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon(void) const;		///< ILT 0x000346A3
	void recenterTurret(WhichTurretType tur);					///< ILT 0x0000D0A8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_unreconstructed_00[0x204];
	AIUpdateInterface *m_ai;									///< retail this+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
class BattlePlanUpdate
{
protected:
	void recenterTurret(void);

private:
	char m_unreconstructed_00[8];
	Object *m_object;											///< retail this+0x08
};

// ?recenterTurret@BattlePlanUpdate@@IAEXXZ
void BattlePlanUpdate::recenterTurret()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if( ai )
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if( tur != TURRET_INVALID )
		{
			ai->recenterTurret( tur );
		}
	}
}
