// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define TRUE true

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_SPAWNS_ARE_THE_WEAPONS = 83
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE,
	ATTACKRESULT_INVALID_SHOT,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING,
	ATTACKRESULT_POSSIBLE
};

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

typedef void (*BfmeContainIterateFunc)( Object *obj, void *userData );

// BFME's ContainModuleInterface places iterateContained at vtable +0xfc.
// Only that slot is named; the preceding entries preserve the ABI slice.
class BfmeContainModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e(); virtual void slot0f();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1a(); virtual void slot1b();
	virtual void slot1c(); virtual void slot1d(); virtual void slot1e(); virtual void slot1f();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2a(); virtual void slot2b();
	virtual void slot2c(); virtual void slot2d(); virtual void slot2e(); virtual void slot2f();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot3a(); virtual void slot3b();
	virtual void slot3c(); virtual void slot3d(); virtual void slot3e();
	virtual void iterateContained( BfmeContainIterateFunc func, void *userData, Bool reverse );
};

class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Object *getClosestSlave( const Coord3D *pos );
};

class Object : public Thing
{
public:
	Bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}

	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject( AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource ) const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	BfmeContainModule *getContain() const
	{
		return *(BfmeContainModule **)((const char *)this + 0x1fc);
	}
};

class ActionManager;

struct BfmeContainedAttackContext
{
	CanAttackResult result;
	ActionManager *manager;
	const Object *target;
	CommandSourceType commandSource;
	AbleToAttackType attackType;
};

class ActionManager
{
public:
	CanAttackResult bfmeGetCanAttackContained( const Object *obj,
		const Object *objectToAttack, CommandSourceType commandSource,
		AbleToAttackType attackType );
	CanAttackResult getCanAttackObject( const Object *obj,
		const Object *objectToAttack, CommandSourceType commandSource,
		AbleToAttackType attackType );
};

void bfmeContainedAttackVisitor( Object *obj, void *userData )
{
	BfmeContainedAttackContext *context =
		(BfmeContainedAttackContext *)userData;
	CanAttackResult result = context->manager->getCanAttackObject(
		obj, context->target, context->commandSource, context->attackType);
	if (result == ATTACKRESULT_POSSIBLE)
		context->result = result;
}

// ?bfmeGetCanAttackContained@ActionManager@@QAE?AW4CanAttackResult@@PBVObject@@0W4CommandSourceType@@W4AbleToAttackType@@@Z
CanAttackResult ActionManager::bfmeGetCanAttackContained( const Object *obj,
	const Object *objectToAttack, CommandSourceType commandSource,
	AbleToAttackType attackType )
{
	BfmeContainedAttackContext context;
	if ((*(const unsigned char *)((const char *)obj + 0x90) & 2) != 0)
	{
		BfmeContainModule *contain = obj->getContain();
		if (contain)
		{
		context.manager = this;
		context.target = objectToAttack;
		context.commandSource = commandSource;
		context.attackType = attackType;
		context.result = ATTACKRESULT_NOT_POSSIBLE;
		contain->iterateContained( bfmeContainedAttackVisitor, &context, TRUE );
		return context.result;
		}
	}
	return ATTACKRESULT_NOT_POSSIBLE;
}

// ?getCanAttackObject@ActionManager@@QAE?AW4CanAttackResult@@PBVObject@@0W4CommandSourceType@@W4AbleToAttackType@@@Z
CanAttackResult ActionManager::getCanAttackObject( const Object *obj,
	const Object *objectToAttack, CommandSourceType commandSource,
	AbleToAttackType attackType )
{
	if (!obj || !objectToAttack || obj->isEffectivelyDead()
		|| objectToAttack->isEffectivelyDead() || objectToAttack == obj)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (!obj->isAbleToAttack())
		return ATTACKRESULT_NOT_POSSIBLE;

	if ((*(const unsigned char *)((const char *)obj + 0x1a4) & 0x10)
		&& attackType == ATTACK_NEW_TARGET)
		return ATTACKRESULT_NOT_POSSIBLE;

	CanAttackResult result;
	if (obj->isKindOf(KINDOF_STRUCTURE))
	{
		result = bfmeGetCanAttackContained(obj, objectToAttack, commandSource, attackType);
		if (result != ATTACKRESULT_NOT_POSSIBLE)
			return result;
	}

	result = obj->getAbleToAttackSpecificObject(attackType, objectToAttack, commandSource);
	if (result != ATTACKRESULT_NOT_POSSIBLE)
		return result;

	if (obj->isKindOf(KINDOF_SPAWNS_ARE_THE_WEAPONS))
	{
		SpawnBehaviorInterface *spawnInterface = obj->getSpawnBehaviorInterface();
		if (spawnInterface)
		{
			Object *slave = spawnInterface->getClosestSlave(objectToAttack->getPosition());
			if (slave)
			{
				result = slave->getAbleToAttackSpecificObject(
					attackType, objectToAttack, commandSource);
				if (result != ATTACKRESULT_NOT_POSSIBLE)
					return result;
			}
		}
	}

	return ATTACKRESULT_NOT_POSSIBLE;
}
