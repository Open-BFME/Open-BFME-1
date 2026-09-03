// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?isWithinAttackRange@Weapon@@: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
//
// BFME Weapon::isWithinAttackRange overloads. Named callers
// (AIAttackAimAtTargetState::onEnter, AIAttackApproachTargetState::updateInternal,
// AIAttackSquadState::chooseVictim / onEnter) set ecx to the weapon and push
// (source, victim-or-pos, extra) -- ZH's two-argument form plus a trailing int
// that is forwarded into isGoalPosWithinAttackRange. The bodies themselves never
// touch ecx, so the inner thiscall reuses the incoming this pointer; that is
// why retail parks the extra argument in esi rather than ecx.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position; // retail +0x38 (x / y / z at +0x38 / +0x3c / +0x40)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	bool isGoalPosWithinAttackRange(const Object *source, const Coord3D *goalPos,
		const Object *target, const Coord3D *targetPos, int extra) const;

	bool isWithinAttackRange(const Object *source, const Coord3D *pos, int extra) const;
	bool isWithinAttackRange(const Object *source, const Object *target, int extra) const;
};

bool Weapon::isWithinAttackRange(const Object *source, const Coord3D *pos, int extra) const
{
	if (source && pos)
		return isGoalPosWithinAttackRange(source, &source->m_position, 0, pos, extra);
	return false;
}

bool Weapon::isWithinAttackRange(const Object *source, const Object *target, int extra) const
{
	if (source && target)
		return isGoalPosWithinAttackRange(source, &source->m_position, target, &target->m_position, extra);
	return false;
}
