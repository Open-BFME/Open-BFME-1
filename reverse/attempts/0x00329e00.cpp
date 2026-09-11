// ?evaluateUnitIsAttackedAndCannotRetaliate@ScriptConditions@@IAE_NPAVParameter@@@Z
// partial score=0.75 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?evaluateUnitIsAttackedAndCannotRetaliate@ScriptConditions@@IAE_NPAVParameter@@@Z

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter
{
};

class BodyModuleInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual const void *getLastDamageInfo(void) const = 0;
	virtual UnsignedInt getLastDamageTimestamp(void) const = 0;
};

class AIUpdateInterface
{
public:
#define AI_SLOT(n) virtual void slot##n(void) = 0;
	AI_SLOT(00) AI_SLOT(01) AI_SLOT(02) AI_SLOT(03) AI_SLOT(04)
	AI_SLOT(05) AI_SLOT(06) AI_SLOT(07) AI_SLOT(08) AI_SLOT(09)
	AI_SLOT(10) AI_SLOT(11) AI_SLOT(12) AI_SLOT(13) AI_SLOT(14)
	AI_SLOT(15) AI_SLOT(16) AI_SLOT(17) AI_SLOT(18) AI_SLOT(19)
	AI_SLOT(20) AI_SLOT(21) AI_SLOT(22) AI_SLOT(23) AI_SLOT(24)
	AI_SLOT(25) AI_SLOT(26) AI_SLOT(27) AI_SLOT(28) AI_SLOT(29)
	AI_SLOT(30) AI_SLOT(31) AI_SLOT(32) AI_SLOT(33) AI_SLOT(34)
	AI_SLOT(35) AI_SLOT(36) AI_SLOT(37) AI_SLOT(38) AI_SLOT(39)
	AI_SLOT(40) AI_SLOT(41) AI_SLOT(42) AI_SLOT(43) AI_SLOT(44)
	AI_SLOT(45) AI_SLOT(46) AI_SLOT(47) AI_SLOT(48) AI_SLOT(49)
	AI_SLOT(50) AI_SLOT(51) AI_SLOT(52) AI_SLOT(53) AI_SLOT(54)
	AI_SLOT(55) AI_SLOT(56) AI_SLOT(57) AI_SLOT(58) AI_SLOT(59)
	AI_SLOT(60) AI_SLOT(61) AI_SLOT(62) AI_SLOT(63) AI_SLOT(64)
	AI_SLOT(65) AI_SLOT(66) AI_SLOT(67) AI_SLOT(68) AI_SLOT(69)
	AI_SLOT(70) AI_SLOT(71) AI_SLOT(72) AI_SLOT(73) AI_SLOT(74)
	AI_SLOT(75) AI_SLOT(76) AI_SLOT(77) AI_SLOT(78) AI_SLOT(79)
	AI_SLOT(80) AI_SLOT(81) AI_SLOT(82) AI_SLOT(83) AI_SLOT(84)
	AI_SLOT(85) AI_SLOT(86) AI_SLOT(87) AI_SLOT(88) AI_SLOT(89)
	AI_SLOT(90) AI_SLOT(91) AI_SLOT(92) AI_SLOT(93) AI_SLOT(94)
	AI_SLOT(95)
#undef AI_SLOT
	virtual Bool isIdle(void) const = 0;
	Bool isQuickPathAvailable(const Coord3D *) const;
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface(void) const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x204);
	}

	BodyModuleInterface *getBodyModule(void) const
	{
		return *(BodyModuleInterface **)((const char *)this + 0x200);
	}

	Bool isEffectivelyDead(void) const
	{
		return ((*(const unsigned char *)((const char *)this + 0x344)) & 1) != 0;
	}

	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual Object *getUnitNamed(Parameter *) = 0;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	UnsignedInt getFrame(void) const { return m_frame; }
	UnsignedInt m_unmodelled_00[15];
	UnsignedInt m_frame;
};

class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *what);
};

class RelationshipFilter
{
public:
	__forceinline RelationshipFilter(Object *object)
		: m_next(0)
	{
		m_vptr = (void *)0x010956C4;
		m_object = object;
		m_flags = 2;
		m_state = 0;
	}

	__forceinline ~RelationshipFilter(void)
	{
		m_vptr = (void *)0x01083B5C;
	}

	void *m_vptr;
	void *m_next;
	Object *m_object;
	Int m_flags;
	Bool m_state;
};

class ScriptConditions
{
protected:
	Bool evaluateUnitIsAttackedAndCannotRetaliate(Parameter *);
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheBfmeGameLogic;
extern void j_00018eb2(void);
extern void j_0001f253(void);
extern void j_00004c37(void);

// ?evaluateUnitIsAttackedAndCannotRetaliate@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateUnitIsAttackedAndCannotRetaliate(Parameter *pUnitParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj)
		return false;

	AIUpdateInterface * volatile ai = theObj->getAIUpdateInterface();
	if (!ai)
		return false;
	if (!ai->isIdle())
		return false;

	BodyModuleInterface *body = theObj->getBodyModule();
	if (!body)
		return false;

	if (body->getLastDamageTimestamp() + 0x19 < TheBfmeGameLogic->m_frame)
		return false;

	const unsigned char *lastDamage =
		(const unsigned char *)body->getLastDamageInfo();
	if (!lastDamage)
		return false;

	typedef Object *(GameLogic::*FindObjectCall)(Int);
	union
	{
		void (*raw)(void);
		FindObjectCall member;
	} findObject;
	findObject.raw = j_0001f253;
	Object *attacker = (TheBfmeGameLogic->*findObject.member)(
		*(const Int *)(lastDamage + 8));
	if (!attacker)
		return false;
	if (attacker->isEffectivelyDead())
		return false;

	RelationshipFilter filter(theObj);
	if (!((BfmeThingEQ *)&filter)->bfmeAskEQ(attacker))
		return true;

	typedef Bool (AIUpdateInterface::*QuickPathCall)(const Coord3D *) const;
	union
	{
		void (*raw)(void);
		QuickPathCall member;
	} quickPath;
	quickPath.raw = j_00018eb2;
	if ((ai->*quickPath.member)(attacker->getPosition()))
		return false;

	typedef Bool (__cdecl *CanAttackCall)(void *, void *);
	return !((CanAttackCall)j_00004c37)(attacker, theObj);
}
