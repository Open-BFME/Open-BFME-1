// ??1SpecialEnemySenseUpdate@@UAE@XZ
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// A clean C++ reconstruction attempt for retail 0x002AB0F0.  The direct
// vtable entry receives the secondary UpdateModule interface (ECX is the
// object plus 0x10), which is why the two owning fields are read backwards
// from that interface.  The complete body remains banked until its truncated
// 543-byte ledger boundary and the compiler's SEH cleanup are reconciled.
// stlport

#include <list>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class Player;
class Object;

class SESU_ModuleData
{
public:
	void *m_vptr;
	int m_04;
	unsigned char m_08[4];
	int m_0c;
	int m_10;
};

typedef _STL::list<Object *> ObjectList;

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);

	UnsignedInt m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterBase : public PartitionFilter
{
public:
	PartitionFilterBase()
	{
		m_vptr = 0x01083B80;
		m_next = 0;
	}
};

class BfmeThingRJ : public PartitionFilter
{
public:
	BfmeThingRJ(void *sub, Player *player)
	{
		m_vptr = 0x010A5158;
		m_next = 0;
		m_sub = sub;
		m_player = player;
		m_enabled = true;
	}

	void *m_sub;
	Player *m_player;
	Bool m_enabled;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(const Object *object)
	{
		m_vptr = 0x01085DC0;
		m_next = 0;
		m_object = object;
		m_flags = 1;
		m_state = false;
	}

	const Object *m_object;
	int m_flags;
	Bool m_state;
};

class PartitionManager
{
public:
	Object *getClosestObject(const void *position, Real distance,
		int distanceMode, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

class HordeContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0;
	virtual void slot51() = 0; virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0; virtual void slot56() = 0;
	virtual void slot57() = 0; virtual void slot58() = 0;
	virtual const ObjectList &slot59() = 0;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class Object
{
public:
	void *m_vptr;
	unsigned char m_pad04[0x38 - 4];
	float m_position[3];
	unsigned char m_pad44[0x12c - 0x44];
	UnsignedInt m_modelCondition;
	unsigned char m_pad130[0x1fc - 0x130];
	ContainModuleInterface *m_contain;

	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();
};

class SpecialEnemySenseUpdate
{
public:
	virtual ~SpecialEnemySenseUpdate();
};

// ??1SpecialEnemySenseUpdate@@UAE@XZ
SpecialEnemySenseUpdate::~SpecialEnemySenseUpdate()
{
	const char *secondary = reinterpret_cast<const char *>(this);
	Object *object = *reinterpret_cast<Object *const *>(secondary - 8);
	SESU_ModuleData *moduleData = *reinterpret_cast<SESU_ModuleData *const *>(secondary - 12);

	PartitionFilterRelationship relationship(object);
	BfmeThingRJ playerFilter(&moduleData->m_08,
		object->getControllingPlayer());
	PartitionFilterBase baseFilter;
	PartitionFilter *filters = baseFilter.link(
		playerFilter.link(&relationship));

	Object *found = ThePartitionManager->getClosestObject(
		&object->m_position, (Real)moduleData->m_0c, 0, filters);
	if (found != 0)
	{
		ContainModuleInterface *contain = object->m_contain;
		if (contain != 0)
		{
			HordeContainInterface *horde = contain->getHordeContainInterface();
			if (horde != 0)
			{
				const ObjectList &source = horde->slot59();
				ObjectList members(source);
				for (ObjectList::iterator it = members.begin();
					it != members.end(); ++it)
				{
					Object *member = *it;
					if ((member->m_modelCondition & 0x00800000) == 0)
					{
						member->m_modelCondition |= 0x00800000;
						member->notifyModelConditionChanged();
					}
				}
			}
		}
	}
}
