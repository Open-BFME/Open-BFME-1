// ?d_001676a0@@YAXXZ
// partial score=0.26 date=2026-09-23
// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

struct Rva001676A0Coord3D
{
	float x;
	float y;
	float z;
};

class Rva001676A0Object;
class Rva001676A0DozerAI;
class Rva001676A0Pathfinder;
class Rva001676A0LocomotorSet
{
};

class Rva001676A0BodyModule
{
public:
#define RVA001676A0_BODY_SLOT(n) virtual void bodySlot##n(void);
	RVA001676A0_BODY_SLOT(00) RVA001676A0_BODY_SLOT(01)
	RVA001676A0_BODY_SLOT(02) RVA001676A0_BODY_SLOT(03)
	RVA001676A0_BODY_SLOT(04) RVA001676A0_BODY_SLOT(05)
	RVA001676A0_BODY_SLOT(06) RVA001676A0_BODY_SLOT(07)
#undef RVA001676A0_BODY_SLOT
	virtual int getDamageState(void);
};

class Rva001676A0AICommand
{
public:
	virtual void commandSlot(void);
	void aiRepair(Rva001676A0Object *, int);
	void aiMoveToPosition(const Rva001676A0Coord3D *, int);
};

class Rva001676A0AIUpdate
{
public:
#define RVA001676A0_AI_SLOT(n) virtual void aiSlot##n(void);
	RVA001676A0_AI_SLOT(00) RVA001676A0_AI_SLOT(01)
	RVA001676A0_AI_SLOT(02) RVA001676A0_AI_SLOT(03)
	RVA001676A0_AI_SLOT(04) RVA001676A0_AI_SLOT(05)
	RVA001676A0_AI_SLOT(06) RVA001676A0_AI_SLOT(07)
	RVA001676A0_AI_SLOT(08) RVA001676A0_AI_SLOT(09)
	RVA001676A0_AI_SLOT(10) RVA001676A0_AI_SLOT(11)
	RVA001676A0_AI_SLOT(12) RVA001676A0_AI_SLOT(13)
	RVA001676A0_AI_SLOT(14) RVA001676A0_AI_SLOT(15)
	RVA001676A0_AI_SLOT(16) RVA001676A0_AI_SLOT(17)
	RVA001676A0_AI_SLOT(18) RVA001676A0_AI_SLOT(19)
	RVA001676A0_AI_SLOT(20) RVA001676A0_AI_SLOT(21)
	RVA001676A0_AI_SLOT(22) RVA001676A0_AI_SLOT(23)
	RVA001676A0_AI_SLOT(24) RVA001676A0_AI_SLOT(25)
	RVA001676A0_AI_SLOT(26) RVA001676A0_AI_SLOT(27)
	RVA001676A0_AI_SLOT(28) RVA001676A0_AI_SLOT(29)
	RVA001676A0_AI_SLOT(30) RVA001676A0_AI_SLOT(31)
	RVA001676A0_AI_SLOT(32) RVA001676A0_AI_SLOT(33)
	RVA001676A0_AI_SLOT(34) RVA001676A0_AI_SLOT(35)
	RVA001676A0_AI_SLOT(36) RVA001676A0_AI_SLOT(37)
	RVA001676A0_AI_SLOT(38) RVA001676A0_AI_SLOT(39)
	RVA001676A0_AI_SLOT(40) RVA001676A0_AI_SLOT(41)
	RVA001676A0_AI_SLOT(42) RVA001676A0_AI_SLOT(43)
	RVA001676A0_AI_SLOT(44) RVA001676A0_AI_SLOT(45)
	RVA001676A0_AI_SLOT(46) RVA001676A0_AI_SLOT(47)
	RVA001676A0_AI_SLOT(48) RVA001676A0_AI_SLOT(49)
	RVA001676A0_AI_SLOT(50) RVA001676A0_AI_SLOT(51)
	RVA001676A0_AI_SLOT(52) RVA001676A0_AI_SLOT(53)
	RVA001676A0_AI_SLOT(54) RVA001676A0_AI_SLOT(55)
	RVA001676A0_AI_SLOT(56) RVA001676A0_AI_SLOT(57)
	RVA001676A0_AI_SLOT(58) RVA001676A0_AI_SLOT(59)
	RVA001676A0_AI_SLOT(60) RVA001676A0_AI_SLOT(61)
	RVA001676A0_AI_SLOT(62) RVA001676A0_AI_SLOT(63)
	RVA001676A0_AI_SLOT(64) RVA001676A0_AI_SLOT(65)
	RVA001676A0_AI_SLOT(66) RVA001676A0_AI_SLOT(67)
	RVA001676A0_AI_SLOT(68) RVA001676A0_AI_SLOT(69)
	RVA001676A0_AI_SLOT(70) RVA001676A0_AI_SLOT(71)
	RVA001676A0_AI_SLOT(72) RVA001676A0_AI_SLOT(73)
	RVA001676A0_AI_SLOT(74) RVA001676A0_AI_SLOT(75)
	RVA001676A0_AI_SLOT(76) RVA001676A0_AI_SLOT(77)
	RVA001676A0_AI_SLOT(78)
#undef RVA001676A0_AI_SLOT
	virtual Rva001676A0DozerAI *getDozerAIInterface(void);

private:
	char m_pad04[0x1c];

public:
	Rva001676A0AICommand m_commands;
	char m_pad24[0x184];
	Rva001676A0LocomotorSet m_locomotorSet;
};

class Rva001676A0Object
{
private:
	char m_pad00[0x38];

public:
	Rva001676A0Coord3D m_position;

private:
	char m_pad44[0x30];

public:
	int m_id;

private:
	char m_pad78[0x188];

public:
	Rva001676A0BodyModule *m_body;
	Rva001676A0AIUpdate *m_ai;

public:
	Rva001676A0Coord3D *getPosition(void) { return &m_position; }
	Rva001676A0BodyModule *getBodyModule(void) { return m_body; }
	int getID(void) { return m_id; }
	Rva001676A0AIUpdate *getAI(void) { return m_ai; }
};

class Rva001676A0DozerAI
{
public:
#define RVA001676A0_DOZER_SLOT(n) virtual void dozerSlot##n(void);
	RVA001676A0_DOZER_SLOT(00) RVA001676A0_DOZER_SLOT(01)
	RVA001676A0_DOZER_SLOT(02) RVA001676A0_DOZER_SLOT(03)
	RVA001676A0_DOZER_SLOT(04) RVA001676A0_DOZER_SLOT(05)
	RVA001676A0_DOZER_SLOT(06) RVA001676A0_DOZER_SLOT(07)
#undef RVA001676A0_DOZER_SLOT
	virtual bool isAnyTaskPending(void);
};

class Rva001676A0GameLogic
{
public:
	Rva001676A0Object *findObjectByID(int);
};

class Rva001676A0Pathfinder
{
public:
	void adjustToPossibleDestination(Rva001676A0Object *, const Rva001676A0LocomotorSet &, Rva001676A0Coord3D *);
};

class Rva001676A0AI
{
private:
	char m_pad00[0xc];
	Rva001676A0Pathfinder *m_pathfinder;

public:
	Rva001676A0Pathfinder *pathfinder(void) { return m_pathfinder; }
};

extern Rva001676A0GameLogic *TheGameLogic;
extern Rva001676A0AI *TheAI;

class Rva001676A0Owner
{
public:
#define RVA001676A0_OWNER_SLOT(n) virtual void ownerSlot##n(void);
	RVA001676A0_OWNER_SLOT(00) RVA001676A0_OWNER_SLOT(01)
	RVA001676A0_OWNER_SLOT(02) RVA001676A0_OWNER_SLOT(03)
	RVA001676A0_OWNER_SLOT(04) RVA001676A0_OWNER_SLOT(05)
	RVA001676A0_OWNER_SLOT(06) RVA001676A0_OWNER_SLOT(07)
	RVA001676A0_OWNER_SLOT(08) RVA001676A0_OWNER_SLOT(09)
	RVA001676A0_OWNER_SLOT(10) RVA001676A0_OWNER_SLOT(11)
	RVA001676A0_OWNER_SLOT(12) RVA001676A0_OWNER_SLOT(13)
	RVA001676A0_OWNER_SLOT(14) RVA001676A0_OWNER_SLOT(15)
	RVA001676A0_OWNER_SLOT(16) RVA001676A0_OWNER_SLOT(17)
	RVA001676A0_OWNER_SLOT(18) RVA001676A0_OWNER_SLOT(19)
#undef RVA001676A0_OWNER_SLOT
	virtual Rva001676A0Object *findDozer(const Rva001676A0Coord3D *);
	virtual void queueDozer(void);
	void processRepair(void);

private:
	char m_pad04[0x30];
	Rva001676A0Coord3D m_baseCenter;
	bool m_baseCenterSet;
	char m_pad41[7];
	int m_structuresToRepair[2];
	int m_repairDozer;
	Rva001676A0Coord3D m_repairDozerOrigin;
	int m_structuresInQueue;
	bool m_dozerQueuedForRepair;
	bool m_dozerIsRepairing;
	char m_pad66[2];
	int m_bridgeTimer;
};

void Rva001676A0Owner::processRepair(void)
{
	if (m_structuresInQueue == 0)
		return;
	m_bridgeTimer--;
	if (m_bridgeTimer > 0)
		return;
	m_bridgeTimer = 5;

	{
	Rva001676A0Object *bridgeObj = 0;
	Rva001676A0Coord3D bridgePos;
	int bridgeState;
	while (bridgeObj == 0 && m_structuresInQueue > 0) {
		bridgeObj = TheGameLogic->findObjectByID(m_structuresToRepair[0]);
		if (bridgeObj == 0) {
			int i;
			for (i = 0; i < m_structuresInQueue - 1; i++)
				m_structuresToRepair[i] = m_structuresToRepair[i + 1];
			m_structuresInQueue--;
		}
	}
	if (m_structuresInQueue == 0)
		return;

	bridgePos.x = bridgeObj->m_position.x;
	bridgePos.y = bridgeObj->m_position.y;
	bridgePos.z = bridgeObj->m_position.z;
	bridgeState = bridgeObj->getBodyModule()->getDamageState();
	Rva001676A0Object *dozer = 0;
	if (m_repairDozer == 0) {
		m_dozerIsRepairing = false;
		if (m_dozerQueuedForRepair)
			return;
		dozer = findDozer(&bridgePos);
		if (dozer != 0) {
			m_repairDozer = dozer->m_id;
			m_repairDozerOrigin.x = dozer->m_position.x;
			m_repairDozerOrigin.y = dozer->m_position.y;
			m_repairDozerOrigin.z = dozer->m_position.z;
			dozer->getAI()->m_commands.aiRepair(bridgeObj, 2);
			m_dozerIsRepairing = true;
			return;
		}
		queueDozer();
		m_dozerQueuedForRepair = true;
		return;
	}

	dozer = TheGameLogic->findObjectByID(m_repairDozer);
	if (dozer == 0) {
		m_repairDozer = 0;
		m_bridgeTimer = 0;
		return;
	}
	Rva001676A0DozerAI *dozerAI = dozer->getAI()->getDozerAIInterface();
	if (m_dozerIsRepairing) {
		if (dozerAI->isAnyTaskPending())
			return;
		if (bridgeState == 0) {
			int i;
			for (i = 0; i < m_structuresInQueue - 1; i++)
				m_structuresToRepair[i] = m_structuresToRepair[i + 1];
			m_structuresInQueue--;
			m_dozerIsRepairing = false;
			if (m_structuresInQueue == 0) {
				Rva001676A0Coord3D pos = m_baseCenter;
				if (!m_baseCenterSet)
					pos = m_repairDozerOrigin;
				Rva001676A0AIUpdate *ai = dozer->getAI();
				TheAI->pathfinder()->adjustToPossibleDestination(dozer, ai->m_locomotorSet, &pos);
				dozer->getAI()->m_commands.aiMoveToPosition(&pos, 2);
				return;
			}
		} else {
			return;
		}
	}
	dozer->getAI()->m_commands.aiRepair(bridgeObj, 2);
	m_dozerIsRepairing = true;
	}
}
