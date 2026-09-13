// BFME 1.03 AIUpdateInterface::privateIdle (RVA 0x0027D670).
// cl: /DNDEBUG /MD /EHsc
//
// TU-local views preserve the retail object offsets and virtual slots. The
// behavior follows the Generals AIUpdate implementation with BFME's rampage,
// horde-containment and model-condition handling recovered from retail.
// The visible recursive override walk is significant: MSVC can retain the
// owning Object across this read-only helper, reproducing retail's registers.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI,
	CMD_FROM_DOZER,
	CMD_DEFAULT_SWITCH_WEAPON
};

typedef UnsignedInt StateID;
enum { BFME_AI_IDLE = 0 };

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum KindOfType { KINDOF_PROJECTILE = 25 };
enum WeaponSetType { WEAPONSET_RAMPAGE = 8 };
enum ModelConditionFlagType
{
	MODELCONDITION_MOVING = 60,
	MODELCONDITION_BACKING_UP = 146
};

struct ModelConditionFlags
{
	UnsignedInt m_words[10];
};

class WeaponSetFlags
{
public:
	Bool test( Int type ) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

// This view emits the same 26-byte chain walk already owned by
// Overridable::getFinalOverride in INIWater.cpp (RVA 0x00087A80).
// Its existing symbol pin reaches that body through ILT 0x000022BB.
class BfmeOverridable
{
public:
	virtual void slot00();
	const BfmeOverridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	BfmeOverridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public BfmeOverridable
{
public:
	unsigned char m_unmodelled_08[0xC8 - 8];
	UnsignedInt m_kindof[1]; // partial view: only the observed first word is modelled
};

// Override.h accessor shape; Thing.h stores this one-pointer wrapper.
template<class T> class OVERRIDE
{
public:
	__forceinline const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}
	__forceinline operator const T *() const { return operator*(); }

	const T *m_overridable;
};

class Thing
{
public:
	virtual void slot00();
	OVERRIDE<ThingTemplate> m_template;
	__forceinline const ThingTemplate *getTemplate() const { return m_template; }
};

class Object;
class AIUpdateInterface;

class HordeContainInterface;

struct BfmeContainedNode
{
	BfmeContainedNode *m_next;
	BfmeContainedNode *m_prev;
	Object *m_object;
};

struct BfmeContainedList
{
	BfmeContainedNode *m_head;
};

#define BFME_CONTAIN_SLOT(N) virtual Int containSlot##N() = 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	BFME_CONTAIN_SLOT(00); BFME_CONTAIN_SLOT(01); BFME_CONTAIN_SLOT(02);
	BFME_CONTAIN_SLOT(03); BFME_CONTAIN_SLOT(04); BFME_CONTAIN_SLOT(05);
	BFME_CONTAIN_SLOT(06); BFME_CONTAIN_SLOT(07); BFME_CONTAIN_SLOT(08);
	BFME_CONTAIN_SLOT(09); BFME_CONTAIN_SLOT(10); BFME_CONTAIN_SLOT(11);
	BFME_CONTAIN_SLOT(12); BFME_CONTAIN_SLOT(13); BFME_CONTAIN_SLOT(14);
	BFME_CONTAIN_SLOT(15); BFME_CONTAIN_SLOT(16); BFME_CONTAIN_SLOT(17);
	BFME_CONTAIN_SLOT(18); BFME_CONTAIN_SLOT(19); BFME_CONTAIN_SLOT(20);
	BFME_CONTAIN_SLOT(21); BFME_CONTAIN_SLOT(22); BFME_CONTAIN_SLOT(23);
	BFME_CONTAIN_SLOT(24); BFME_CONTAIN_SLOT(25);
	virtual HordeContainInterface *getHordeContainInterface() = 0;
	BFME_CONTAIN_SLOT(27); BFME_CONTAIN_SLOT(28); BFME_CONTAIN_SLOT(29);
	BFME_CONTAIN_SLOT(30); BFME_CONTAIN_SLOT(31); BFME_CONTAIN_SLOT(32);
	BFME_CONTAIN_SLOT(33); BFME_CONTAIN_SLOT(34); BFME_CONTAIN_SLOT(35);
	BFME_CONTAIN_SLOT(36); BFME_CONTAIN_SLOT(37); BFME_CONTAIN_SLOT(38);
	BFME_CONTAIN_SLOT(39); BFME_CONTAIN_SLOT(40); BFME_CONTAIN_SLOT(41);
	BFME_CONTAIN_SLOT(42); BFME_CONTAIN_SLOT(43); BFME_CONTAIN_SLOT(44);
	BFME_CONTAIN_SLOT(45); BFME_CONTAIN_SLOT(46); BFME_CONTAIN_SLOT(47);
	BFME_CONTAIN_SLOT(48); BFME_CONTAIN_SLOT(49); BFME_CONTAIN_SLOT(50);
	BFME_CONTAIN_SLOT(51); BFME_CONTAIN_SLOT(52); BFME_CONTAIN_SLOT(53);
	BFME_CONTAIN_SLOT(54); BFME_CONTAIN_SLOT(55); BFME_CONTAIN_SLOT(56);
	BFME_CONTAIN_SLOT(57); BFME_CONTAIN_SLOT(58); BFME_CONTAIN_SLOT(59);
	BFME_CONTAIN_SLOT(60); BFME_CONTAIN_SLOT(61); BFME_CONTAIN_SLOT(62);
	BFME_CONTAIN_SLOT(63); BFME_CONTAIN_SLOT(64);
	virtual const BfmeContainedList *getContainedItemsList() = 0;
};

#undef BFME_CONTAIN_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle( CommandSourceType cmdSource );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	const WeaponSetFlags &getWeaponSetFlags() const;
	void notifyModelConditionChanged();
	void adjustModelConditionForWeaponStatus();
	void clearModelConditionState( ModelConditionFlagType flag )
	{
		const UnsignedInt mask = 1U << (flag & 31);
		UnsignedInt &word = m_modelConditionFlags.m_words[flag >> 5];
		if (word & mask)
		{
			word &= ~mask;
			notifyModelConditionChanged();
		}
	}

	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_unmodelled_008[0x108];
	ModelConditionFlags m_modelConditionFlags; // Object + 0x110
	unsigned char m_unmodelled_138[0xB8];
	void *m_behaviors;
	unsigned char m_unmodelled_1F4[8];
	ContainModuleInterface *m_contain;
	unsigned char m_unmodelled_200[4];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void clear() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual StateReturnType setState( StateID state ) = 0;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

#define BFME_AI_SLOT(N) virtual Int aiSlot##N() = 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	BFME_AI_SLOT(00); BFME_AI_SLOT(01); BFME_AI_SLOT(02); BFME_AI_SLOT(03);
	BFME_AI_SLOT(04); BFME_AI_SLOT(05); BFME_AI_SLOT(06); BFME_AI_SLOT(07);
	BFME_AI_SLOT(08); BFME_AI_SLOT(09); BFME_AI_SLOT(10); BFME_AI_SLOT(11);
	BFME_AI_SLOT(12); BFME_AI_SLOT(13); BFME_AI_SLOT(14); BFME_AI_SLOT(15);
	BFME_AI_SLOT(16); BFME_AI_SLOT(17); BFME_AI_SLOT(18); BFME_AI_SLOT(19);
protected:
	virtual void privateIdle( CommandSourceType cmdSource ); // slot 20
public:
	BFME_AI_SLOT(21); BFME_AI_SLOT(22); BFME_AI_SLOT(23);
	BFME_AI_SLOT(24); BFME_AI_SLOT(25); BFME_AI_SLOT(26); BFME_AI_SLOT(27);
	BFME_AI_SLOT(28); BFME_AI_SLOT(29); BFME_AI_SLOT(30); BFME_AI_SLOT(31);
	BFME_AI_SLOT(32); BFME_AI_SLOT(33); BFME_AI_SLOT(34); BFME_AI_SLOT(35);
	BFME_AI_SLOT(36); BFME_AI_SLOT(37); BFME_AI_SLOT(38); BFME_AI_SLOT(39);
	BFME_AI_SLOT(40); BFME_AI_SLOT(41); BFME_AI_SLOT(42); BFME_AI_SLOT(43);
	BFME_AI_SLOT(44); BFME_AI_SLOT(45); BFME_AI_SLOT(46); BFME_AI_SLOT(47);
	BFME_AI_SLOT(48); BFME_AI_SLOT(49); BFME_AI_SLOT(50); BFME_AI_SLOT(51);
	BFME_AI_SLOT(52); BFME_AI_SLOT(53); BFME_AI_SLOT(54); BFME_AI_SLOT(55);
	BFME_AI_SLOT(56); BFME_AI_SLOT(57); BFME_AI_SLOT(58); BFME_AI_SLOT(59);
	BFME_AI_SLOT(60); BFME_AI_SLOT(61); BFME_AI_SLOT(62); BFME_AI_SLOT(63);
	BFME_AI_SLOT(64); BFME_AI_SLOT(65); BFME_AI_SLOT(66); BFME_AI_SLOT(67);
	BFME_AI_SLOT(68); BFME_AI_SLOT(69); BFME_AI_SLOT(70); BFME_AI_SLOT(71);
	BFME_AI_SLOT(72); BFME_AI_SLOT(73); BFME_AI_SLOT(74); BFME_AI_SLOT(75);
	BFME_AI_SLOT(76); BFME_AI_SLOT(77); BFME_AI_SLOT(78); BFME_AI_SLOT(79);
	BFME_AI_SLOT(80); BFME_AI_SLOT(81); BFME_AI_SLOT(82); BFME_AI_SLOT(83);
	BFME_AI_SLOT(84); BFME_AI_SLOT(85); BFME_AI_SLOT(86); BFME_AI_SLOT(87);
	BFME_AI_SLOT(88); BFME_AI_SLOT(89); BFME_AI_SLOT(90); BFME_AI_SLOT(91);
	BFME_AI_SLOT(92); BFME_AI_SLOT(93); BFME_AI_SLOT(94); BFME_AI_SLOT(95);
	BFME_AI_SLOT(96);
#undef BFME_AI_SLOT
	virtual Bool isAttacking() const = 0;

	Object *getObject() const { return m_object; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	void setLastCommandSource( CommandSourceType source ) { m_lastCommandSource = source; }

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x40 - 0x34];
	ObjectID m_currentVictimID;
	unsigned char m_unmodelled_44[0x48 - 0x44];
	CommandSourceType m_lastCommandSource;
};

void AIUpdateInterface::privateIdle( CommandSourceType cmdSource )
{
	if (getObject()->getTemplate()->m_kindof[0] & (1U << KINDOF_PROJECTILE))
		return;

	if (getObject()->getWeaponSetFlags().test(WEAPONSET_RAMPAGE))
		return;

	ContainModuleInterface *contain = getObject()->getContain();
	Bool idleContained = false;
	if (contain)
	{
		if (contain->getHordeContainInterface() == 0)
			idleContained = true;

		if (isAttacking())
			idleContained = true;
		else if (m_currentVictimID &&
			TheGameLogic->findObjectByID(m_currentVictimID) != 0)
			idleContained = true;

		if (idleContained)
		{
			const BfmeContainedList *items = contain->getContainedItemsList();
			if (items)
			{
				BfmeContainedNode *sentinel = items->m_head;
				for (BfmeContainedNode *node = sentinel->m_next;
					node != items->m_head; node = node->m_next)
				{
					Object *member = node->m_object;
					AIUpdateInterface *ai = member ? member->getAI() : 0;
					if (ai)
						reinterpret_cast<AICommandInterface *>(
							reinterpret_cast<char *>(ai) + 0x20)->aiIdle(cmdSource);
				}
			}
		}
	}

	getStateMachine()->clear();
	getStateMachine()->setState(BFME_AI_IDLE);

	getObject()->clearModelConditionState(MODELCONDITION_MOVING);
	getObject()->clearModelConditionState(MODELCONDITION_BACKING_UP);
	getObject()->adjustModelConditionForWeaponStatus();
	setLastCommandSource(cmdSource);
}
