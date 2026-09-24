// cl: /DNDEBUG /MD /EHsc
// Retail 0x0015F420, 527 bytes: vtable 0x010965C8 slot 4 (onEnter), table installed by
// Rva0015F070GuardState. Zero Hour twin: AIGuardRetaliateAttackAggressorState::onEnter.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum Relationship
{
	ENEMIES = 0
};

enum KindOfType
{
	KINDOF_0x6C = 0x6c
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

struct Coord0015F420
{
	Real x, y, z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class BfmeSubBIAR0015F420 : public Overridable
{
};

class FlagsObjR0015F420 : public Overridable
{
public:
	const FlagsObjR0015F420 *getFinal(void) const
	{
		if (m_field4 == 0) return this;
		return static_cast<const FlagsObjR0015F420 *>(m_field4->getFinalOverride());
	}

	char m_pad0[4];
	BfmeSubBIAR0015F420 *m_field4;
	char m_pad1[0xD4 - 8];
	Int m_field0xD4;
};

class Weapon;

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class BfmeX1011R0015F420 : public Object
{
public:
	char m_pad0[4];
	FlagsObjR0015F420 *m_field4;
	char m_pad1[0x74 - 8];
	Int m_field74;
};

class BfmeLook1011R0015F420 : public GameLogic
{
public:
	char m_pad[0x3C];
	UnsignedInt m_field3C;

	UnsignedInt getFrame(void) const { return m_field3C; }
};

class QueryResultR0015F420
{
public:
	char m_pad0[8];
	Int m_field8;
	char m_pad1[0x10 - 0xC];
	Int m_field0x10;
};

class QueryVtblR0015F420
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual QueryResultR0015F420 *v3CCall(void);
};

class Rva001E1770ByteField
{
public:
	unsigned char get(void) const;
};

class WeaponTmplR0015F420 : public Rva001E1770ByteField
{
};

class Weapon
{
};

class Weapon0015F420 : public Weapon
{
public:
	char m_pad0[4];
	WeaponTmplR0015F420 *m_field4;

	const WeaponTmplR0015F420 *getTemplate(void) const { return m_field4; }
};

class ObjectR0015F420 : public Object
{
public:
	char m_pad0[0x200];
	QueryVtblR0015F420 *m_field0x200;
};

class StateMachine
{
};

class AIGuardRetaliateMachine
{
public:
	static Real getStdGuardRange(const Object *obj);
};

class ContainerR0015F420 : public StateMachine
{
public:
	char m_pad0[0x10];
	ObjectR0015F420 *m_field0x10;
	char m_pad1[0x44 - 0x14];
	Coord0015F420 m_field44;
	Int m_field50;

	void setNemesisID(Int id) { m_field50 = id; }
	Int getNemesisID(void) const { return m_field50; }
};

struct FactorsR0015F420
{
	char m_pad[0x3C];
	UnsignedInt m_field3C;
};

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *obj, Int factorsToConsider);
};

struct AIRootR0015F420 : public AI
{
	char m_pad[0x14];
	FactorsR0015F420 *m_factors;

	FactorsR0015F420 *getAiData(void) const { return m_factors; }
};

class QVtblR0015F420
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38Call(BfmeX1011R0015F420 *goal);
};

class TailR0015F420
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual Int v10Call(void);
	char m_pad[0x18];
	QVtblR0015F420 *m_tail;
};

class AttackExitConditionsInterface;

class Rva002BD020AIAttackState : public TailR0015F420
{
public:
	Rva002BD020AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject,
		Bool forceAttacking, AttackExitConditionsInterface *attackParameters);
	char m_body[0x54 - 0x20];
};

extern "C" BfmeLook1011R0015F420 *g_bfmeClockBK;		// 0x012F0898
extern "C" AIRootR0015F420 *TheAIParseDefinitionAI;		// 0x012EF214

class Rva0015EBE0State
{
public:
	int queryGuardContain();
};

class SelfR0015F420 : public Rva0015EBE0State
{
public:
	Int run(void);

	ContainerR0015F420 *getMachine(void) { return m_machine; }

	char m_pad0[0x1C];
	ContainerR0015F420 *m_machine;
	char m_pad20[0x28 - 0x20];
	Int m_conditions;
	Coord0015F420 m_center;
	Real m_radiusSqr;
	UnsignedInt m_giveUpFrame;
	TailR0015F420 *m_attackState;
	Int m_field44;
};

static inline Real sqr0015F420(Real x) { return x * x; }

// ?run@SelfR0015F420@@QAEHXZ
Int SelfR0015F420::run(void)
{
	ObjectR0015F420 *obj = m_machine->m_field0x10;
	Int nemID = 0;
	m_field44 = 0;

	BfmeX1011R0015F420 *nemesis = static_cast<BfmeX1011R0015F420 *>(
		g_bfmeClockBK->findObjectByID(m_machine->getNemesisID()));

	QueryVtblR0015F420 *body = obj->m_field0x200;
	if (!nemesis && body && body->v3CCall()->m_field8 && body->v3CCall()->m_field0x10 != 7)
	{
		nemID = obj->m_field0x200->v3CCall()->m_field8;
		nemesis = static_cast<BfmeX1011R0015F420 *>(g_bfmeClockBK->findObjectByID(nemID));
		if (nemesis && obj->getRelationship(nemesis) == ENEMIES)
			m_machine->setNemesisID(nemID);
	}

	if (!nemesis)
		return -1;

	FlagsObjR0015F420 *tmpl = nemesis->m_field4;
	if ((tmpl == 0 ? tmpl : tmpl->getFinal())->m_field0xD4 & 0x1000)
	{
		if (!obj->isKindOf(KINDOF_0x6C))
		{
			m_field44 = nemesis->m_field74;
			nemesis = reinterpret_cast<BfmeX1011R0015F420 *>(queryGuardContain());
			if (!nemesis)
				return -2;
			m_machine->setNemesisID(nemesis->m_field74);
		}
	}

	Coord0015F420 pos;
	pos.x = m_machine->m_field44.x;
	pos.y = m_machine->m_field44.y;
	pos.z = m_machine->m_field44.z;

	Real range = AIRootR0015F420::getAdjustedVisionRangeForObject(obj, 3);

	UnsignedInt frames = TheAIParseDefinitionAI->getAiData()->m_field3C;
	if (obj->getCurrentWeapon() &&
		static_cast<Weapon0015F420 *>(obj->getCurrentWeapon())->getTemplate()->get())
		frames += frames >> 1;

	m_center = pos;
	m_giveUpFrame = g_bfmeClockBK->getFrame() + frames;
	m_radiusSqr = sqr0015F420(range + AIGuardRetaliateMachine::getStdGuardRange(obj));
	m_conditions = 7;

	m_attackState = new Rva002BD020AIAttackState(getMachine(), false, true, false, 0);
	m_attackState->m_tail->v38Call(nemesis);

	Int returnVal = m_attackState->v10Call();
	if (returnVal == 0)
		return 0;
	return -1;
}
