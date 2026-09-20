// ?d_002e8130@@YAXXZ
// partial score=0.43 date=2026-09-20
// Probe source for the 449-byte ObjectCountNearbyEnemies body.
// The filter and result views follow the independently matched 0x0025ED50 donor.
// This file is scratch evidence and is not a ledger claim.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

struct lua_State;
extern "C" int lua_type(lua_State *, int);
extern "C" double lua_tonumber(lua_State *, int);
extern "C" void lua_pushnil(lua_State *);
extern "C" void lua_pushnumber(lua_State *, double);

unsigned Rva00990030Lookup(lua_State *, int);

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

class GameLogic
{
public:
	Object *findObjectByID(int);
};
extern GameLogic *TheGameLogic;

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

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual bool allow(Object *);
	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual bool allow(Object *);
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

struct Rva002E8130Entry
{
	Object *object;
	unsigned unknown04;
};

struct Rva002E8130ResultData
{
	std::vector<Rva002E8130Entry> entries;
	Rva002E8130Entry *current;
	int references;
};

struct Rva002E8130WideResult
{
	Rva002E8130ResultData *value;
	Rva002E8130WideResult();
	Rva002E8130WideResult(const Rva002E8130WideResult &);
	~Rva002E8130WideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	Rva002E8130WideResult bfmeForwardWideC(int, float, int, int, int);
};
extern BfmeWideForwardC *ThePartitionManager;

int ObjectCountNearbyEnemies(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup(state, 1);
	if (!objectID && lua_type(state, 1) != 1)
	{
		lua_pushnil(state);
		return 0;
	}
	volatile int radius = (int)lua_tonumber(state, 2);
	Object *object = TheGameLogic->findObjectByID((int)objectID);
	if (object == 0)
	{
		lua_pushnumber(state, 0.0);
		return 1;
	}
	Rva002E8130WideResult iterator = ThePartitionManager->bfmeForwardWideC(
		(int)((char *)object + 0x38), radius, 1,
		(int)PartitionFilterRelationship(object, 1, false).link(
			Rva0025ED50RootFilter().link(
				&Rva0025ED50ObjectFilter(object))), 1);
	int count = iterator.value->entries.end() - iterator.value->entries.begin();
	lua_pushnumber(state, (double)count);
	return 1;
}
