// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/GameType.h"
#include "GameLogic/ObjectIter.h"

class Object;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int mode, Bool match)
		: m_obj(object), m_flags(mode), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

struct Rva0028C050Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0028C050ResultData
{
	std::vector<Rva0028C050Entry> entries;
	Rva0028C050Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0028C050ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult()
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

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern GameLogic *TheBfmeGameLogic;

class DelayedLuaEventList
{
	public:
	unsigned char m_data[0x4c];
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B(int, Object *, DelayedLuaEventList *);
};

extern BfmeOwnerBR *g_bfmeOwnerBR;

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// The vtable at the interface subobject (+0x10) points at the body below.
// Keeping this TU's receiver as that interface view reproduces the retail
// adjusted-this ABI; the concrete update fields are consequently at +0x10,
// +0x60, +0x64, and +0x65 from this receiver.
class DelayedLuaEventUpdate
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_pad04[0x0c];
	Int m_eventIndex;
	DelayedLuaEventList m_events;
	Int m_radius;
	Bool m_relationshipMode;
	Bool m_relationshipMatch;
};

// ?update@DelayedLuaEventUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DelayedLuaEventUpdate::update()
{
	Object *object = *(Object **)((char *)this - 8);
	Int relationshipFlags = 2;
	if (m_relationshipMode)
		relationshipFlags = 6;
	if (m_relationshipMatch)
		relationshipFlags |= 1;

	BfmeWideResult iterator =
		ThePartitionManager->bfmeForwardWideC(
			(int)&object->m_position, m_radius, 0,
			(int)PartitionFilterRelationship(object, relationshipFlags, false).link(
				Rva0025ED50RootFilter().link(
					&Rva0025ED50ObjectFilter(object))), 1);

	Object *other;
	while (iterator.next(other))
	{
		if (other == object)
			continue;
		g_bfmeOwnerBR->bfmeGo939B(
			m_eventIndex, other, &m_events);
	}

	Object *destroyedObject = *(Object **)((char *)this - 8);
	TheBfmeGameLogic->destroyObject(destroyedObject);
	return UPDATE_SLEEP_NONE;
}
