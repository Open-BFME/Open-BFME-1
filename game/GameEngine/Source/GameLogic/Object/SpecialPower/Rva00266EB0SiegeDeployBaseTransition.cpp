// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

// The dispatcher at RVA 0x00266EB0 calls ILT 0x000298C0 with the integer state.
// The SiegeDeploy constructor installs this interface vtable at offset 0x24.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes { OBJECT_STATUS_PLACEHOLDER };
enum DisabledType { DISABLED_PLACEHOLDER };
enum AttitudeType { ATTITUDE_PLACEHOLDER };
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class ModelConditionFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }
	void reset(Int bit) { m_bits.reset(bit); }
private:
	_STL::bitset<320> m_bits;
};

#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS \
	void clearStatus(ObjectStatusTypes status); \
	void setStatusBit(Int bit, Bool set); \
	void setDisabledUntil(DisabledType type, UnsignedInt frame); \
	void notifyModelConditionChanged(void); \
	Int rva001be010(void);
#include "../object.h"

class AIUpdateInterface
{
public:
	void setAttitude(AttitudeType attitude);
};

class AICommandInterface
{
public:
	void aiEvacuate(Bool evacuate, CommandSourceType source);
	void aiExit(Object *object, CommandSourceType source);
};

class BfmeObjectAI
{
public:
	Int bfmeStateValue();
};

class BfmeSub1CC_EC3
{
public:
	void queryClamp(float limit, void *value);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};
extern GameLogic *TheBfmeGameLogic;

struct Rva00266B50ListNode
{
	Rva00266B50ListNode *m_next;
	Rva00266B50ListNode *m_previous;
	Object *m_object;
};
struct Rva00266B50ObjectList
{
	Rva00266B50ListNode *m_sentinel;
};

class Rva00266B50ContainView
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n() = 0;
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
	CONTAIN_SLOT(44) CONTAIN_SLOT(45) CONTAIN_SLOT(46) CONTAIN_SLOT(47)
	CONTAIN_SLOT(48) CONTAIN_SLOT(49) CONTAIN_SLOT(50) CONTAIN_SLOT(51)
	CONTAIN_SLOT(52) CONTAIN_SLOT(53) CONTAIN_SLOT(54) CONTAIN_SLOT(55)
	CONTAIN_SLOT(56) CONTAIN_SLOT(57) CONTAIN_SLOT(58) CONTAIN_SLOT(59)
	CONTAIN_SLOT(60) CONTAIN_SLOT(61) CONTAIN_SLOT(62) CONTAIN_SLOT(63)
	CONTAIN_SLOT(64)
	virtual Rva00266B50ObjectList *listAt65() = 0;
	virtual Rva00266B50ObjectList *listAt66() = 0;
#undef CONTAIN_SLOT
};

class MemoryPool
{
public:
	~MemoryPool();
};

class SiegeDeploySpecialPowerModuleDataBase
{
public:
	virtual ~SiegeDeploySpecialPowerModuleDataBase();
private:
	unsigned char m_pad[0x1cc];
};

class SiegeDeploySpecialPowerModuleData : public SiegeDeploySpecialPowerModuleDataBase
{
public:
	virtual ~SiegeDeploySpecialPowerModuleData();
	UnsignedInt m_1d0;
	UnsignedInt m_1d4;
	unsigned char m_1d8;
	unsigned char m_1d9;
	unsigned char m_1da;
	unsigned char m_pad1db;
	float m_1dc;
	float m_1e0;
};

class Rva001F96E0Action
{
public:
	void invoke();
};

extern void j_00026044(void);
extern void j_0002fc7a(void);
extern void j_00021017(void);

static __forceinline void setModelCondition(Object *object, Int bit)
{
	if (!object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.set(bit);
		object->notifyModelConditionChanged();
	}
}

static __forceinline void clearModelCondition(Object *object, Int bit)
{
	if (object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.reset(bit);
		object->notifyModelConditionChanged();
	}
}

static __forceinline void *siegeDeployGetPool(Object *object)
{
	union
	{
		void (*raw)(void);
		void *(__cdecl *typed)(Object *);
	} call;
	call.raw = j_0002fc7a;
	return call.typed(object);
}

static __forceinline void siegeDeployDoAction(void *object)
{
	union
	{
		void (*raw)(void);
		void (Rva001F96E0Action::*member)(void);
	} call;
	call.raw = j_00026044;
	(((Rva001F96E0Action *)object)->*call.member)();
}

static __forceinline BfmeSub1CC_EC3 *siegeDeployGetClamp(Object *object)
{
	union
	{
		void (*raw)(void);
		Int (Object::*member)(void);
	} call;
	call.raw = j_00021017;
	return (BfmeSub1CC_EC3 *)(UnsignedInt)(object->*call.member)();
}

class Rva00266EB0SiegeDeployBase
{
public:
	void transition(Int state);
private:
	unsigned char m_pad00[4];
	SiegeDeploySpecialPowerModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x2c];
	volatile Int m_state;
	volatile UnsignedInt m_3c;
	volatile UnsignedInt m_40;
};

// ?transition@Rva00266EB0SiegeDeployBase@@QAEXH@Z
void Rva00266EB0SiegeDeployBase::transition(Int state)
{
	Int oldState = m_state;
	if (state == oldState)
		return;

	Object *object = m_object;
	switch (oldState)
	{
	case 2:
		clearModelCondition(object, 95);
		break;
	case 3:
	{
		object->clearStatus((ObjectStatusTypes)0x3a);
		clearModelCondition(object, 99);
		void *pool = siegeDeployGetPool(m_object);
		if (pool != 0)
			((MemoryPool *)pool)->~MemoryPool();
		break;
	}
	case 4:
		m_40 = 0;
		clearModelCondition(object, 93);
		break;
	}

	m_state = state;
	m_3c = 0;

	switch (state)
	{
	case 4:
		setModelCondition(object, 93);
		object->setDisabledUntil((DisabledType)8,
			TheBfmeGameLogic->m_frame + m_moduleData->m_1d4);
		return;
	case 3:
	{
		object->setStatusBit(58, true);
		setModelCondition(object, 99);
		clearModelCondition(object, 60);

		void *pool = siegeDeployGetPool(object);
		if (pool != 0)
			siegeDeployDoAction(pool);

		if (m_moduleData->m_1d8)
		{
			AIUpdateInterface *ai = object->m_ai;
			if (ai != 0)
			{
				AICommandInterface *command =
					(AICommandInterface *)((unsigned char *)ai + 0x20);
				command->aiEvacuate(false, CMD_FROM_AI);
			}
		}

		if (m_moduleData->m_1d9)
		{
			Rva00266B50ContainView *contain =
				(Rva00266B50ContainView *)m_object->m_contain;
			if (contain != 0)
			{
				Rva00266B50ObjectList *list = contain->listAt66();
				if (list != 0)
				{
					list = contain->listAt66();
					Rva00266B50ListNode *node = list->m_sentinel->m_next;
					if (node != contain->listAt66()->m_sentinel)
					{
						do
						{
							Object *member = node->m_object;
							node = node->m_next;
							AIUpdateInterface *memberAI = member->m_ai;
							if (memberAI != 0)
							{
								Int attitude = ((BfmeObjectAI *)m_object->m_ai)->bfmeStateValue();
								memberAI->setAttitude((AttitudeType)attitude);
								((AICommandInterface *)((unsigned char *)member->m_ai + 0x20))
									->aiExit(m_object, CMD_FROM_AI);
							}
						} while (node != contain->listAt66()->m_sentinel);
					}
				}
			}
		}
		return;
	}
	case 2:
		break;
	default:
		return;
	}

	setModelCondition(object, 95);
	if (siegeDeployGetClamp(object) != 0)
		siegeDeployGetClamp(object)->queryClamp(0.0f, object);

	Rva00266B50ContainView *contain =
		(Rva00266B50ContainView *)object->m_contain;
	if (contain != 0)
	{
		Rva00266B50ObjectList *list = contain->listAt65();
		Rva00266B50ListNode *node = list->m_sentinel->m_next;
		while (node != list->m_sentinel)
		{
			setModelCondition(node->m_object, 95);
			node = node->m_next;
		}
	}
}
