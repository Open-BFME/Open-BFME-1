// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x001FF360 is slot 1 of GettingBuiltBehavior's secondary vtable
// 0x010A45E0.  The matched constructor places that subobject at owner+0x20,
// so its reads at this-0x1C and this-0x18 are the module data and Object.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

template <Int NUMBITS>
class BitFlags
{
public:
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object;
class Team;
class ThingTemplate;

enum CommandSourceType
{
	COMMANDSOURCE_RVA_2 = 2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <typename T>
struct StringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T>
class StringBase
{
friend class AsciiString;

private:
	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	Bool isEmpty() const { return !m_data || m_data->m_length == 0; }
};

class PlayerTemplateView
{
public:
	unsigned char m_unreconstructed00[0x118];
	Bool m_field118;
};

class Player
{
public:
	Bool isPlayableSide() const;

	__forceinline PlayerTemplateView *getPlayerTemplate() const
	{
		return m_template;
	}

	__forceinline Team *getDefaultTeam() const
	{
		return m_defaultTeam;
	}

private:
	void *m_vtable;
	PlayerTemplateView *m_template;
	unsigned char m_unreconstructed08[0x230 - 0x08];
	Team *m_defaultTeam;
};

class Gen_00410d20
{
public:
	void m();
};

class Thing
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Gen_00410d20 *rvaSlot10();

	void setPosition(const Coord3D *position);
};

class AICommandInterface
{
public:
	void aiRepair(Object *object, CommandSourceType source);
	void aiResumeConstruction(Object *object, CommandSourceType source);
};

class AIUpdateInterface
{
public:
	unsigned char m_unreconstructed00[0x20];
	AICommandInterface m_commands;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setProducer(const Object *producer);
	void setBuilder(const Object *builder);
	void setEffectivelyDead(Bool dead);
	void setStatusBit(Int status, Bool set);
	Bool testStatus(Int status) const;
	void notifyModelConditionChanged();

	__forceinline const Coord3D *getPosition() const { return &m_position; }
	__forceinline AIUpdateInterface *getAIUpdateInterface() const { return m_aiUpdate; }

	__forceinline void clearModelCondition110Bit20()
	{
		if ((m_modelCondition110Byte & 0x20) != 0)
		{
			m_modelCondition110 &= ~0x20U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void clearModelCondition114Bit20000000()
	{
		if ((m_modelCondition114 & 0x20000000) != 0)
		{
			m_modelCondition114 &= ~0x20000000U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void clearModelCondition114Bit08000000()
	{
		if ((m_modelCondition114 & 0x08000000) != 0)
		{
			m_modelCondition114 &= ~0x08000000U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void setModelCondition118Bit04()
	{
		if ((m_modelCondition118Byte & 0x04) == 0)
		{
			m_modelCondition118 |= 0x04U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void setModelCondition118Bit10()
	{
		if ((m_modelCondition118Byte & 0x10) == 0)
		{
			m_modelCondition118 |= 0x10U;
			notifyModelConditionChanged();
		}
	}

	unsigned char m_unreconstructed04[0x38 - 0x04];
	Coord3D m_position;
	unsigned char m_unreconstructed44[0x110 - 0x44];
	union
	{
		UnsignedInt m_modelCondition110;
		unsigned char m_modelCondition110Byte;
	};
	UnsignedInt m_modelCondition114;
	union
	{
		UnsignedInt m_modelCondition118;
		unsigned char m_modelCondition118Byte;
	};
	unsigned char m_unreconstructed11C[0x204 - 0x11C];
	AIUpdateInterface *m_aiUpdate;
	unsigned char m_unreconstructed208[0x220 - 0x208];
	Real m_field220;
	unsigned char m_unreconstructed224[0x344 - 0x224];
	unsigned char m_field344;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thingTemplate, Team *team,
		const ObjectStatusMaskType &status, UnsignedInt unknown);
};

extern ThingFactory *TheThingFactory;

class ModuleData
{
public:
	virtual ~ModuleData();
};

class GettingBuiltBehaviorModuleData : public ModuleData
{
public:
	virtual ~GettingBuiltBehaviorModuleData();

	unsigned char m_unreconstructed04[0x14 - 0x04];
	AsciiString m_workerName;
	AsciiString m_alternateWorkerName;
	Bool m_useAlternateWorker;
};

class GettingBuiltBehaviorDeepBase
{
public:
	virtual ~GettingBuiltBehaviorDeepBase();

protected:
	__forceinline const ModuleData *getModuleData() const { return m_moduleData; }
	__forceinline Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class GettingBuiltBehaviorInterface1 { public: virtual void slot00() = 0; };
class GettingBuiltBehaviorInterface2 { public: virtual void slot00() = 0; };

class GettingBuiltBehaviorUpdateModule :
	public GettingBuiltBehaviorDeepBase,
	public GettingBuiltBehaviorInterface1,
	public GettingBuiltBehaviorInterface2
{
protected:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_indexInUpdate;
};

class GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void rvaSlot00() = 0;
	virtual void rva001FF360(Object *other) = 0;
	virtual void rvaSlot02() = 0;
	virtual void rvaSlot03(Object *other) = 0;
	virtual void rvaSlot04(Object *other) = 0;
	virtual Bool rvaSlot05() = 0;
};

class GettingBuiltBehavior :
	public GettingBuiltBehaviorUpdateModule,
	public GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void rva001FF360(Object *other);

private:
	__forceinline const GettingBuiltBehaviorModuleData *getGettingBuiltBehaviorModuleData() const
	{
		return static_cast<const GettingBuiltBehaviorModuleData *>(getModuleData());
	}

	UnsignedInt m_audioHandle;
	UnsignedInt m_field28;
	UnsignedInt m_field2C;
	Bool m_field30;
	Bool m_field31;
	Bool m_field32;
	Bool m_field33;
	Bool m_field34;
	Bool m_field35;
	Bool m_field36;
	UnsignedInt m_field38;
};

void GettingBuiltBehavior::rva001FF360(Object *other)
{
	Object *object = getObject();
	const GettingBuiltBehaviorModuleData *data = getGettingBuiltBehaviorModuleData();

	if (data->m_workerName.isEmpty())
	{
		rvaSlot04(other);
		return;
	}

	Player *player = object->getControllingPlayer();
	if (player == 0 || !object->getControllingPlayer()->isPlayableSide())
		return;

	const ThingTemplate *workerTemplate;
	if (data->m_useAlternateWorker &&
		object->getControllingPlayer()->getPlayerTemplate()->m_field118)
	{
		workerTemplate = TheThingFactory->findTemplate(data->m_alternateWorkerName);
	}
	else
	{
		workerTemplate = TheThingFactory->findTemplate(data->m_workerName);
	}
	if (workerTemplate == 0)
		return;

	ObjectStatusMaskType status;
	Object *worker = TheThingFactory->newObject(workerTemplate,
		player->getDefaultTeam(), status, 0);
	if (worker == 0)
		return;

	worker->setPosition(object->getPosition());
	worker->setProducer(object);
	object->setBuilder(worker);

	if ((object->m_field344 & 1) != 0)
	{
		object->setEffectivelyDead(false);
		object->m_field220 = 0.0f;
		object->setStatusBit(2, true);
		object->clearModelCondition110Bit20();
		object->clearModelCondition114Bit20000000();
		object->clearModelCondition114Bit08000000();
		object->setModelCondition118Bit04();
		object->setModelCondition118Bit10();
	}

	AIUpdateInterface *ai = worker->getAIUpdateInterface();
	if (ai != 0)
	{
		if (object->testStatus(2))
			ai->m_commands.aiResumeConstruction(object, COMMANDSOURCE_RVA_2);
		else
			ai->m_commands.aiRepair(object, COMMANDSOURCE_RVA_2);
	}

	Gen_00410d20 *drawable = worker->rvaSlot10();
	if (drawable != 0)
		drawable->m();
}
