// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
// ?releaseLastExit@QueueProductionExitUpdate@@QAEXXZ

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum KindOfType
{
	KINDOF_AIRCRAFT = 0x09
};

enum ModelConditionFlagType
{
	MODELCONDITION_2 = 2,
	MODELCONDITION_3 = 3
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class GameLogicFrameSlice
{
};

extern GameLogicFrameSlice *TheGameLogic;

class Thing
{
public:
	bool isKindOf(KindOfType k) const;
};

class AICommandInterface
{
public:
	void aiMoveToObject(Object *obj, CommandSourceType cmd);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmd);
};

class HostAI
{
#define QV(n) virtual void slot_##n()
#define QV10(p) \
	QV(p##0); QV(p##1); QV(p##2); QV(p##3); QV(p##4); \
	QV(p##5); QV(p##6); QV(p##7); QV(p##8); QV(p##9)
public:
	QV10(00); QV10(01);
	QV(20); QV(21); QV(22); QV(23); QV(24); QV(25);
	virtual void *getInterface();
};

class HostIface
{
public:
	QV(00); QV(01); QV(02); QV(03);
	virtual void notify(bool flag);
};

class Object
{
public:
	void clearModelConditionState(ModelConditionFlagType flag);
	void setMode(int a, int b);
	void unidentified_000F20F0(int a, int b);

	HostAI *getAltAI() const
	{
		return *reinterpret_cast<HostAI *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x1FC);
	}

	AICommandInterface *getAICommand() const
	{
		unsigned char *ai = *reinterpret_cast<unsigned char *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x204);
		return reinterpret_cast<AICommandInterface *>(ai + 0x20);
	}
};

Object *bfmeQueryRallyOverride(Object *obj, const Coord3D *pos);

class QueueProductionExitUpdate
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual const Coord3D *queryRally();
	void releaseLastExit();

	unsigned m_currentDelay;
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
	float m_creationClearDistance;
	unsigned m_currentBurstCount;
	int m_lastExitId;
};

void QueueProductionExitUpdate::releaseLastExit()
{
	Object *host = reinterpret_cast<GameLogic *>(TheGameLogic)->findObjectByID(m_lastExitId);
	if (!host)
		return;

	m_lastExitId = 0;

	HostIface *iface = reinterpret_cast<HostIface *>(host->getAltAI()->getInterface());
	if (!iface)
	{
		host->clearModelConditionState(MODELCONDITION_3);
		host->clearModelConditionState(MODELCONDITION_2);
		return;
	}

	iface->notify(!reinterpret_cast<Thing *>(host)->isKindOf(KINDOF_AIRCRAFT));
	host->clearModelConditionState(MODELCONDITION_3);
	host->clearModelConditionState(MODELCONDITION_2);

	if (!m_rallyPointExists)
		return;
	if (reinterpret_cast<Thing *>(host)->isKindOf(KINDOF_AIRCRAFT))
		return;

	const Coord3D *q = queryRally();
	Object *creationObject = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 0x18);
	Object *overrideObj = bfmeQueryRallyOverride(creationObject, q);
	if (overrideObj)
	{
		host->setMode(0x4D, 1);
		host->setMode(3, 1);
		host->unidentified_000F20F0(3, 1);
		host->getAICommand()->aiMoveToObject(overrideObj, CMD_FROM_AI);
	}
	else
	{
		host->getAICommand()->aiMoveToPosition(&m_rallyPoint, CMD_FROM_AI);
	}
}
