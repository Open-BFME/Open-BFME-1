// cl: /DNDEBUG /MD /EHsc-
// BFME reconstruction of AIMoveToPositionAndDieState::update at 0x0017F000.
// The state shares the retail move-state layout with AIMoveAndDeleteState, but
// on completion it reports the body's last damage source before killing its
// owner.

typedef int ObjectID;

enum StateReturnType
{
	STATE_FAILURE = -2,
	STATE_CONTINUE = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class Path
{
public:
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};

class TerrainLogic
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) = 0;
};

extern TerrainLogic *TheTerrainLogic;

struct BFMEDamageInfo
{
	unsigned char m_unreconstructed_00[8];
	ObjectID m_sourceID;
};

class BFMEBodyDamageSource
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual BFMEDamageInfo *getLastDamageInfo() = 0;
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);

private:
	unsigned char m_unreconstructed_000[0x200];
	BFMEBodyDamageSource *m_body;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;
extern void j_0001b94b(void);

class BFMEReportDamageSource
{
public:
	void report(Object *owner, int setting);
};

typedef void (BFMEReportDamageSource::*BFMEReportDamageSourceFunction)(Object *, int);

struct BfmeMoveStateMachineFields
{
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;
};

struct BfmeMoveStateFields
{
	unsigned char m_unreconstructed_000[0x1c];
	BfmeMoveStateMachineFields *m_machine;
	unsigned char m_unreconstructed_020[4];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_030[0x4c - 0x30];
	unsigned char m_adjustDestinations;
	unsigned char m_unreconstructed_04d[0x50 - 0x4d];
	unsigned char m_appendGoalPosition;
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

class AIMoveToPositionAndDieState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

// ?update@AIMoveToPositionAndDieState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveToPositionAndDieState::update()
{
	char *obj = *(char **)(*(char **)((char *)this + 0x1c) + 0x10);
	if ((*(unsigned char *)(obj + 0x344) & 1) != 0)
	{
		return STATE_FAILURE;
	}

	char *ai = *(char **)(obj + 0x204);
	char *locomotor = *(char **)(ai + 0x1cc);
	if (locomotor)
	{
		*(unsigned int *)(locomotor + 0x40) |= 2;
	}
	BfmeMoveStateFields *self = (BfmeMoveStateFields *)this;
	if (self->m_appendGoalPosition)
	{
		Path *thePath = *(Path **)(ai + 0x140);
		if (*(unsigned char *)(ai + 0x31e) == 0 && thePath)
		{
			self->m_goalPosition.z = ((TerrainLogic *)TheTerrainLogic)->getGroundHeight(
				self->m_goalPosition.x, self->m_goalPosition.y);
			thePath->appendNode(&self->m_goalPosition, LAYER_GROUND);
			self->m_appendGoalPosition = 0;
		}
	}

	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *owner = *(Object **)(*(char **)((char *)this + 0x1c) + 0x10);
		BFMEBodyDamageSource *body = *(BFMEBodyDamageSource **)((char *)owner + 0x200);
		BFMEDamageInfo *damageInfo = body->getLastDamageInfo();
		ObjectID sourceID;
		if (damageInfo)
		{
			body = *(BFMEBodyDamageSource **)((char *)owner + 0x200);
			damageInfo = body->getLastDamageInfo();
			sourceID = damageInfo->m_sourceID;
		}
		else
		{
			sourceID = 0;
		}

		Object *source = TheGameLogic->findObjectByID(sourceID);
		if (source)
		{
			union
			{
				void (*raw)(void);
				BFMEReportDamageSourceFunction member;
			} report;
			report.raw = j_0001b94b;
			(reinterpret_cast<BFMEReportDamageSource *>(source)->*report.member)(owner, 1);
		}
		owner->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
	return status;
}
