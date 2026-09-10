// ?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.18 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
//
// LargeGroupBonusUpdate is reached through UpdateModule's secondary
// UpdateModuleInterface.  The receiver is therefore the +0x10 subobject,
// while the fields below are the complete-object offsets established by the
// constructor at 0x00297640.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int UpdateSleepTime;

enum
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Player;
class AsciiString;

class Thing
{
public:
	Bool isKindOf(enum KindOfType kind) const;
};

enum KindOfType
{
	KINDOF_LARGE_GROUP_BONUS_OBJECT = 9
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Bool applyAttributeModifier(const AsciiString &name, int duration);
};

class Overridable
{
public:
	Overridable *getFinalOverride();
	Overridable *m_nextOverride;
};

struct LargeGroupBonusThingTemplate : Overridable
{
	char m_pad08[0xc0];
	UnsignedInt m_kindOf;
};

struct LargeGroupBonusModuleData
{
	char m_pad00[0x10];
	UnsignedInt m_requiredMembers;
	UnsignedInt m_searchDistance;
	char m_pad18[4];
	float m_radius;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_vptr(0x01083b80), m_next(0) {}
	~PartitionFilter() { m_vptr = 0x01083b5c; }
	PartitionFilter *link(PartitionFilter *next);

	UnsignedInt m_vptr;
	PartitionFilter *m_next;
};

class SameMapFilter : public PartitionFilter
{
public:
	SameMapFilter(Object *object) : m_object(object)
	{
		m_vptr = 0x01085dd0;
	}

	Object *m_object;
};

class PlayerFilter : public PartitionFilter
{
public:
	PlayerFilter(Player *player) : m_player(player)
	{
		m_vptr = 0x01097144;
	}

	Player *m_player;
};

class GameLogic;

class LogicFilter : public PartitionFilter
{
public:
	LogicFilter(GameLogic *logic) : m_logic(logic), m_match(1)
	{
		m_vptr = 0x010bfab8;
	}

	GameLogic *m_logic;
	Bool m_match;
};

struct WidePair
{
	Object *m_object;
	UnsignedInt m_distance;
};

struct WidePayload
{
	WidePair *m_begin;
	WidePair *m_end;
	WidePair *m_capacity;
	WidePair *m_cursor;
	int m_refCount;
};

struct BfmeWideResult
{
	WidePayload *m_value;
};

class BfmeWideForwardC
{
	char m_pad00[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

class PartitionManager : public BfmeWideForwardC
{
};

class GameLogic
{
	char m_pad00[0x3c];

public:
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;
extern PartitionManager *ThePartitionManager;

class BfmeOwnerXI
{
public:
	void bfmeSendXI(void *message);
};

static UnsignedInt relationWeight(void *relation, GameLogic *logic)
{
	if (relation == 0)
		return 0;

	typedef UnsignedInt (__thiscall *RelationWeight)(void *, GameLogic *);
	void **vtable = *reinterpret_cast<void ***>(relation);
	return reinterpret_cast<RelationWeight>(vtable[84])(relation, logic);
}

static Bool relationApplies(void *relation)
{
	if (relation == 0)
		return 0;

	typedef Bool (__thiscall *RelationApplies)(void *);
	void **vtable = *reinterpret_cast<void ***>(relation);
	return reinterpret_cast<RelationApplies>(vtable[2])(relation);
}

static void releaseWideResult(BfmeWideResult &result)
{
	WidePayload *payload = result.m_value;
	if (payload == 0)
		return;

	--payload->m_refCount;
	if (payload->m_refCount == 0)
	{
		if (payload->m_begin != 0)
			::operator delete(payload->m_begin);
		::operator delete(payload);
	}
}

class LargeGroupBonusUpdate
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime LargeGroupBonusUpdate::update()
{
	char *subobject = reinterpret_cast<char *>(this);
	LargeGroupBonusModuleData *moduleData =
		reinterpret_cast<LargeGroupBonusModuleData *>(subobject - 0x0c);
	Object *object = *reinterpret_cast<Object **>(subobject - 0x08);
	Bool oldActive = *reinterpret_cast<Bool *>(subobject + 0x08);

	if (object == 0)
		return UPDATE_SLEEP_NONE;

	LargeGroupBonusThingTemplate *thing =
		*reinterpret_cast<LargeGroupBonusThingTemplate **>(reinterpret_cast<char *>(object) + 4);
	if (thing != 0 && thing->m_nextOverride != 0)
		thing = reinterpret_cast<LargeGroupBonusThingTemplate *>(
			thing->m_nextOverride->getFinalOverride());
	if (thing != 0 && (thing->m_kindOf & 0x100) != 0)
		return UPDATE_SLEEP_NONE;
	if (object->isKindOf(KINDOF_LARGE_GROUP_BONUS_OBJECT))
		return UPDATE_SLEEP_NONE;

	GameLogic *logic = TheBfmeGameLogic;
	UnsignedInt frame = logic->m_frame;
	if (frame <= *reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(object) + 8) +
			*reinterpret_cast<UnsignedInt *>(subobject + 4))
		return UPDATE_SLEEP_NONE;
	*reinterpret_cast<UnsignedInt *>(subobject + 4) = frame;

	PartitionFilter baseFilter;
	SameMapFilter mapFilter(object);
	PlayerFilter playerFilter(object->getControllingPlayer());
	LogicFilter logicFilter(logic);
	PartitionFilter *filters =
		logicFilter.link(playerFilter.link(mapFilter.link(&baseFilter)));

	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		reinterpret_cast<int>(reinterpret_cast<char *>(object) + 0x38),
		static_cast<int>(moduleData->m_searchDistance), 3,
		reinterpret_cast<int>(filters), 0);
	WidePayload *payload = result.m_value;
	UnsignedInt weight = 0;

	if (payload != 0)
	{
		for (WidePair *entry = payload->m_cursor; entry != payload->m_end; ++entry)
		{
			Object *candidate = entry->m_object;
			if (candidate == 0)
				continue;
			void *relation = *reinterpret_cast<void **>(reinterpret_cast<char *>(candidate) + 0x1f0);
			if (relation != 0)
				weight += relationWeight(relation, logic);
		}
	}

	Bool active = 0;
	if (weight < moduleData->m_requiredMembers - 1)
		active = 1;

	if (active == 0)
	{
		for (WidePair *entry = payload == 0 ? 0 : payload->m_cursor;
			entry != 0 && entry != payload->m_end; ++entry)
		{
			Object *candidate = entry->m_object;
			if (candidate == 0)
				continue;
			void *relation = *reinterpret_cast<void **>(reinterpret_cast<char *>(candidate) + 0x1f0);
			if (relation != 0 && relationApplies(relation))
			{
				float dx = *reinterpret_cast<float *>(reinterpret_cast<char *>(candidate) + 0x38) -
					*reinterpret_cast<float *>(reinterpret_cast<char *>(object) + 0x38);
				float dy = *reinterpret_cast<float *>(reinterpret_cast<char *>(candidate) + 0x3c) -
					*reinterpret_cast<float *>(reinterpret_cast<char *>(object) + 0x3c);
				if (dx * dx + dy * dy <= moduleData->m_radius * moduleData->m_radius)
					active = 1;
			}
		}
	}

	if (active != oldActive)
	{
		if (active)
			object->applyAttributeModifier(*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(object) + 0x2c), 0);
		else
			reinterpret_cast<BfmeOwnerXI *>(object)->bfmeSendXI(reinterpret_cast<void *>(reinterpret_cast<char *>(object) + 0x2c));
		*reinterpret_cast<Bool *>(subobject + 0x08) = active;
	}

	releaseWideResult(result);
	return (*reinterpret_cast<Bool *>(reinterpret_cast<char *>(object) + 0x344) & 1) != 0
		? UPDATE_SLEEP_FOREVER : UPDATE_SLEEP_NONE;
}
