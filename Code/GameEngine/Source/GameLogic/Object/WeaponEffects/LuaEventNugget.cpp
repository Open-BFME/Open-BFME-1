// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: LuaEventNugget slot-6 body, retail 0x002DCF70, 428 bytes.
//
// Identity: the Weapon FieldParse key LuaEventNugget reaches
// parseLuaEventNugget (0x001E6240), which allocates the nugget whose
// constructor (0x002DD190) installs vtable 0x010CEDE4; slot 6 (+0x18) of that
// vtable is ILT 0x00007AD1 -> this body.  Slot 5 (0x002DCEE0) forwards its
// first argument and Object+0x38 (the position) here.  The nugget FieldParse
// table at 0x010CED70 names the members this body reads: LuaEvent +0x58,
// Radius +0x5C, SendToEnemies +0x60, SendToAllies +0x61, SendToNeutral +0x62.
// The method name is not recovered and stays address-labelled.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef Int ObjectID;

struct Coord3D;

enum IterOrderType
{
	ITER_FASTEST,
	ITER_SORTED_NEAR_TO_FAR
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

class Object
{
public:
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	ObjectID getID() const { return m_id; }

	unsigned char m_00_to_74[0x74];
	ObjectID m_id;
	unsigned char m_78_to_344[0x344 - 0x78];
	unsigned char m_privateStatus;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *obj, Int flags, Bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType,
		PartitionFilter *, Bool);
};

extern PartitionManager *ThePartitionManager;

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;


struct BfmeDelayedLuaEvent
{
	unsigned char m_00_to_0c[0x0c];
	ObjectID m_objectID;
	unsigned char m_10_to_14[0x04];
	Int m_type;
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	virtual ~BfmeDelayedLuaEventList();

	BfmeDelayedLuaEvent m_events[3];
};

// GameEngine::init hands VA 0x012F060C to initSubsystem<LuaScriptEngine>.
// Its event lookup (0x002E4CA0) and event dispatch (0x002E5790, reached
// through ILT 0x0003D4E7) keep their ledger spellings.
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class Rva002E4CA0
{
public:
	void *rva002E4CA0(Int key) const;
};

class BfmeObjectEventDispatch
{
public:
	void invoke(void *event, void *object, BfmeDelayedLuaEventList *eventList);
};

// First argument: opaque; the body reads only the object ID at +8.
struct Rva002DCF70Source
{
	UnsignedInt dword_0;
	UnsignedInt dword_4;
	ObjectID dword_8;
};

class LuaEventNugget
{
public:
	virtual ~LuaEventNugget();
	void rva002DCF70(Rva002DCF70Source *source, const Coord3D *pos);

	unsigned char m_04_to_58[0x54];
	AsciiString m_luaEvent;
	Real m_radius;
	Bool m_sendToEnemies;
	Bool m_sendToAllies;
	Bool m_sendToNeutral;
};

// ?rva002DCF70@LuaEventNugget@@QAEXPAURva002DCF70Source@@PBUCoord3D@@@Z
void LuaEventNugget::rva002DCF70(Rva002DCF70Source *source, const Coord3D *pos)
{
	void *event = ((const Rva002E4CA0 *)TheLuaScriptEngine)->rva002E4CA0(
		TheNameKeyGenerator->nameToKey(m_luaEvent.str()));
	if (!event)
		return;

	ObjectID id = source->dword_8;
	Object *obj = TheGameLogic->findObjectByID(id);
	if (!obj)
		return;

	// PartitionFilterRelationship ALLOW_ENEMIES / ALLOW_ALLIES / ALLOW_NEUTRAL.
	Int flags = 0;
	if (m_sendToEnemies == true)
		flags = 1;
	if (m_sendToAllies == true)
		flags |= 4;
	if (m_sendToNeutral == true)
		flags |= 2;

	PartitionFilterRelationship filter(obj, flags, false);
	Rva0025ED50WideResult iter = ThePartitionManager->iterate(pos, m_radius,
		ITER_SORTED_NEAR_TO_FAR, &filter, true);

	BfmeDelayedLuaEventList eventList;
	eventList.m_events[0].m_objectID = obj->getID();
	eventList.m_events[0].m_type = 3;

	Object *other;
	while (iter.next(other))
	{
		if (other->isEffectivelyDead())
			continue;
		((BfmeObjectEventDispatch *)TheLuaScriptEngine)->invoke(event, other, &eventList);
	}
}
