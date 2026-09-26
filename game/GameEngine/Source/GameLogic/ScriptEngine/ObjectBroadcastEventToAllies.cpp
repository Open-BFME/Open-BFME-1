// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x002E86B0, 534 bytes. The Lua registration at 0x002EC990
// binds ILT 0x000395A9 to this callback as ObjectBroadcastEventToAllies.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

struct lua_State;
extern "C" int lua_type(lua_State *, int);
extern "C" const char *lua_tostring(lua_State *, int);
extern "C" double lua_tonumber(lua_State *, int);

unsigned Rva00990030Lookup(lua_State *, int);

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class Object
{
};

class GameLogic
{
public:
	Object *bfmeFind1011(int id);
};

extern GameLogic *TheGameLogic;

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();

	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

struct BfmeDispatchDelayedLuaEvent
{
	void *m_vtable;
	float m_number;
	unsigned char m_boolean;
	unsigned char m_padding[3];
	unsigned m_objectID;
	UnicodeString m_string;
	unsigned m_type;
};

struct LuaDrawableState
{
	unsigned char m_data[0x78];
};

extern LuaDrawableState *g_obj12F060C;

struct BfmeCallJ63
{
	void *invoke(void *event);
};

struct BfmeObjectEventDispatch
{
	void invoke(void *event, void *object, BfmeDelayedLuaEventList *eventList);
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *) { return false; }
	virtual int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, int flags, bool match)
		: m_object(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual bool allow(Object *);
	virtual int getPlayerMask();

	Object *m_object;
	int m_flags;
	bool m_match;
};

struct Rva002E86B0Entry
{
	Object *object;
	unsigned unknown04;
};

struct Rva002E86B0ResultData
{
	std::vector<Rva002E86B0Entry> entries;
	Rva002E86B0Entry *current;
	int references;
};

struct BfmeWideResult
{
	Rva002E86B0ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

// ?ObjectBroadcastEventToAllies@@YAHPAUlua_State@@@Z
int ObjectBroadcastEventToAllies(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup(state, 1);
	if (!objectID && lua_type(state, 1) != 1)
		return 0;

	Object *object = TheGameLogic->bfmeFind1011(objectID);
	if (object == 0)
		return 0;

	BfmeDelayedLuaEventList eventList;
	const char *eventName = lua_tostring(state, 2);
	if (eventName == 0)
		return 0;

	NameKeyType eventKey = TheNameKeyGenerator->nameToKey(eventName);
	void *eventData = reinterpret_cast<BfmeCallJ63 *>(g_obj12F060C)->invoke(
		(void *)eventKey);
	if (eventData == 0)
		return 0;

	float radius = (float)lua_tonumber(state, 3);
	const char *text = lua_tostring(state, 4);
	BfmeDispatchDelayedLuaEvent *events =
		reinterpret_cast<BfmeDispatchDelayedLuaEvent *>(&eventList.m_events[0]);
	events[0].m_objectID = objectID;
	events[0].m_type = 3;
	if (text != 0)
	{
		BFMERetailAsciiString value(text);
		reinterpret_cast<UnicodeString *>(&events[1].m_string)->set(
			reinterpret_cast<const UnicodeString &>(value));
		events[1].m_type = 4;
	}

	PartitionFilterRelationship relationship(object, 4, false);
	int radiusBits = *(int *)&radius;
	BfmeWideResult iterator =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(int)((char *)object + 0x38), radiusBits, 1,
			(int)&relationship, 1);

	Object *other;
	while (iterator.next(other))
	{
		reinterpret_cast<BfmeObjectEventDispatch *>(g_obj12F060C)->invoke(
			eventData, other, &eventList);
	}

	return 0;
}
