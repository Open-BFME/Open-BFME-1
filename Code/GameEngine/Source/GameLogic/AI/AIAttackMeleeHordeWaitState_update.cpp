// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -1,
	STATE_SUCCESS = -2
};

enum KindOfType
{
	KINDOF_MELEE_HORDE_TARGET = 92
};

struct Coord3D
{
	float x, y, z;
};

class Player;
class Object;

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

#define HORDE_SLOT(N) virtual int slot##N() = 0

class HordeContainInterface
{
public:
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55);
	HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58); HORDE_SLOT(59);
	HORDE_SLOT(60); HORDE_SLOT(61); HORDE_SLOT(62); HORDE_SLOT(63);
	HORDE_SLOT(64); HORDE_SLOT(65); HORDE_SLOT(66); HORDE_SLOT(67);
	virtual void beginMelee(Object *member) = 0;
	virtual void endMelee() = 0;
	HORDE_SLOT(70);
	virtual void updateMeleeTarget(Object *target) = 0;
	HORDE_SLOT(72);
	virtual Bool isMeleeTargetReady(Object *target) = 0;
	HORDE_SLOT(74); HORDE_SLOT(75); HORDE_SLOT(76);
	virtual void prepareMeleeTarget(Object *target) = 0;
	virtual void setMeleeFormation(unsigned int formation) = 0;
};

class ContainModuleInterface
{
public:
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25);
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

#undef HORDE_SLOT

class Thing
{
public:
	float bfmeRelativeAngleTo(const Coord3D *position) const;
	Bool bfmeIsKindOf(KindOfType kind) const;
	void setOrientation(float angle);

	const Coord3D *getPosition() const { return &m_position; }
	float getOrientation() const { return m_orientation; }

private:
	unsigned char m_pad_000[0x38];
	Coord3D m_position;
	float m_orientation;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Object *bfmeResolveMeleeTarget(int index);
	int getLayer() const;
	float getDistanceSquared(const Object *other) const;
	ContainModuleInterface *getContain() const { return m_contain; }
	unsigned int getMeleeFormation() const { return m_meleeFormation; }
	Bool isMeleeHordeTarget() const { return (m_kindFlags & 0x20) != 0; }

private:
	unsigned char m_pad_048[0x2c];
	unsigned int m_meleeFormation;
	unsigned char m_pad_078[0x1c];
	unsigned char m_kindFlags;
	unsigned char m_pad_095[0x167];
	ContainModuleInterface *m_contain;
};

class StateMachine
{
public:
	Bool isGoalObjectDestroyed() const;
	Object *getGoalObject();

	unsigned char m_pad_000[0x10];
	Object *m_owner;
};

class GameLogic
{
public:
	unsigned char m_pad_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;
Bool bfmeMeleeHordeTargetInvalid(Object *source, Object *target);

class AIAttackMeleeHordeWaitState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();

private:
	unsigned char m_pad_004[0x18];
	StateMachine *m_machine;
	unsigned char m_pad_020[4];
	UnsignedInt m_waitUntil;
};

StateReturnType AIAttackMeleeHordeWaitState::onEnter()
{
	Object *source = m_machine->m_owner;
	if (m_machine->isGoalObjectDestroyed())
		return STATE_FAILURE;

	Object *target = m_machine->getGoalObject();
	if (target == 0)
		return STATE_FAILURE;

	ContainModuleInterface *contain = source->getContain();
	if (contain != 0)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde == 0)
			return STATE_FAILURE;

		unsigned int formation = target->getMeleeFormation();
		if (target->isMeleeHordeTarget())
		{
			Object *resolved = target->bfmeResolveMeleeTarget(0);
			if (resolved != 0)
			{
				formation = resolved->getMeleeFormation();
				target = resolved;
			}
		}

		if (bfmeMeleeHordeTargetInvalid(source, target))
			return STATE_SUCCESS;

		if (!horde->isMeleeTargetReady(target))
		{
			int maximumDistance = 40;
			if (target->bfmeIsKindOf(KINDOF_MELEE_HORDE_TARGET) &&
				source->getLayer() != 1)
				maximumDistance = 60;

			if (source->getDistanceSquared(target) <
				(float)(maximumDistance * maximumDistance))
				horde->prepareMeleeTarget(target);
			else
				return STATE_SUCCESS;
		}

		horde->setMeleeFormation(formation);
		m_waitUntil = TheGameLogic->m_frame + 15;
		horde->beginMelee(target);
	}

	return STATE_CONTINUE;
}

StateReturnType AIAttackMeleeHordeWaitState::update()
{
	Object *source = m_machine->m_owner;
	if (m_machine->isGoalObjectDestroyed())
		return STATE_FAILURE;

	Object *target = m_machine->getGoalObject();
	if (target == 0)
		return STATE_FAILURE;

	if (((BFMEObjectStealthQuery *)target)->isStealthedAndUndetected(
			(const Object *)source->getControllingPlayer()))
		return STATE_SUCCESS;

	ContainModuleInterface *contain = source->getContain();
	if (contain != 0)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde == 0)
			return STATE_FAILURE;

		if (bfmeMeleeHordeTargetInvalid(source, target))
			return STATE_SUCCESS;

		if (horde->isMeleeTargetReady(target))
			m_waitUntil = TheGameLogic->m_frame + 15;
		else if (TheGameLogic->m_frame >= m_waitUntil)
			return STATE_SUCCESS;

		horde->updateMeleeTarget(target);
	}

	float angle = source->getOrientation();
	angle += source->bfmeRelativeAngleTo(target->getPosition());
	source->setOrientation(angle);
	return STATE_CONTINUE;
}
