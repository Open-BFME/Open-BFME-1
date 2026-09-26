// Clean C++ reconstruction of the BFME position range condition at retail RVA 0x0016AEE0 (109 bytes).

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON
};

class Weapon;
class AIUpdateInterface;
class Pathfinder;

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x1c0];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	char m_pad000[0x10];
	Object *m_owner;
	char m_pad014[0x10];
	Coord3D m_goalPosition;
};

class State
{
public:
	char m_pad000[0x1c];
	StateMachine *m_machine;
};

class AIUpdateInterface
{
public:
	virtual void slot000() = 0;
	virtual void slot001() = 0;
	virtual void slot002() = 0;
	virtual void slot003() = 0;
	virtual void slot004() = 0;
	virtual void slot005() = 0;
	virtual void slot006() = 0;
	virtual void slot007() = 0;
	virtual void slot008() = 0;
	virtual void slot009() = 0;
	virtual void slot010() = 0;
	virtual void slot011() = 0;
	virtual void slot012() = 0;
	virtual void slot013() = 0;
	virtual void slot014() = 0;
	virtual void slot015() = 0;
	virtual void slot016() = 0;
	virtual void slot017() = 0;
	virtual void slot018() = 0;
	virtual void slot019() = 0;
	virtual void slot020() = 0;
	virtual void slot021() = 0;
	virtual void slot022() = 0;
	virtual void slot023() = 0;
	virtual void slot024() = 0;
	virtual void slot025() = 0;
	virtual void slot026() = 0;
	virtual void slot027() = 0;
	virtual void slot028() = 0;
	virtual void slot029() = 0;
	virtual void slot030() = 0;
	virtual void slot031() = 0;
	virtual void slot032() = 0;
	virtual void slot033() = 0;
	virtual void slot034() = 0;
	virtual void slot035() = 0;
	virtual void slot036() = 0;
	virtual void slot037() = 0;
	virtual void slot038() = 0;
	virtual void slot039() = 0;
	virtual void slot040() = 0;
	virtual void slot041() = 0;
	virtual void slot042() = 0;
	virtual void slot043() = 0;
	virtual void slot044() = 0;
	virtual void slot045() = 0;
	virtual void slot046() = 0;
	virtual void slot047() = 0;
	virtual void slot048() = 0;
	virtual void slot049() = 0;
	virtual void slot050() = 0;
	virtual void slot051() = 0;
	virtual void slot052() = 0;
	virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual void slot055() = 0;
	virtual void slot056() = 0;
	virtual void slot057() = 0;
	virtual void slot058() = 0;
	virtual void slot059() = 0;
	virtual void slot060() = 0;
	virtual void slot061() = 0;
	virtual void slot062() = 0;
	virtual void slot063() = 0;
	virtual void slot064() = 0;
	virtual void slot065() = 0;
	virtual void slot066() = 0;
	virtual void slot067() = 0;
	virtual void slot068() = 0;
	virtual void slot069() = 0;
	virtual void slot070() = 0;
	virtual void slot071() = 0;
	virtual void slot072() = 0;
	virtual void slot073() = 0;
	virtual void slot074() = 0;
	virtual void slot075() = 0;
	virtual void slot076() = 0;
	virtual void slot077() = 0;
	virtual void slot078() = 0;
	virtual void slot079() = 0;
	virtual void slot080() = 0;
	virtual void slot081() = 0;
	virtual void slot082() = 0;
	virtual void slot083() = 0;
	virtual void slot084() = 0;
	virtual void slot085() = 0;
	virtual void slot086() = 0;
	virtual void slot087() = 0;
	virtual void slot088() = 0;
	virtual void slot089() = 0;
	virtual void slot090() = 0;
	virtual void slot091() = 0;
	virtual void slot092() = 0;
	virtual void slot093() = 0;
	virtual void slot094() = 0;
	virtual void slot095() = 0;
	virtual void slot096() = 0;
	virtual void slot097() = 0;
	virtual void slot098() = 0;
	virtual void slot099() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void setLocomotorGoalNone() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
};

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *source,
		const Coord3D &sourcePosition, const Object *target,
		const Coord3D &targetPosition);
};

class AI
{
public:
	char m_pad000[0x0c];
	Pathfinder *m_pathfinder;
};

#define TheAI (*(AI *volatile *)0x012EF214)

static __forceinline AI &getGlobalAI()
{
	return *TheAI;
}
static __forceinline Pathfinder *getPathfinder(AI &ai)
{
	return ai.m_pathfinder;
}

class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Coord3D *position,
		int extra) const;
};

Bool Rva0016AEE0WeaponRangePosition(State *thisState, void *userData)
{
	StateMachine *machine = thisState->m_machine;
	Object *object = machine->m_owner;
	const Coord3D *position = &machine->m_goalPosition;
	Weapon *weapon = object->getCurrentWeapon((WeaponSlotType *)0);

	if (!weapon || !position)
		goto falseResult;

	AIUpdateInterface *ai = object->m_ai;
	if (ai && ai->isDoingGroundMovement() &&
		getPathfinder(getGlobalAI())->isAttackViewBlockedByObstacle(
			object, *object->getPosition(), 0, *position))
		goto trueResult;

	if (weapon->isWithinAttackRange(object, position, 0))
		goto falseResult;

trueResult:
	return true;

falseResult:
	return false;
}
