// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// AI::findAllyNear, retail 0014AF50, 256 bytes.
// Matched caller AIFindNearTargetRandomOrder.cpp names this three-argument
// method at both calls through ILT 4650B. Retail returns with ret 0xC.
// Local filter sizes 8/12/12/12/16/20 follow their stores and stack slots;
// PartitionFilterRejectBuildings' matched constructor independently fixes its layout.
// The other filters get their retail vtables straight from the compiler's own
// ??_7X@@6B@ symbols, so no linker alias stands in for them.
// Canonical basetype.h supplies struct Coord3D and the fundamental typedefs.
#include "basetype.h"

class Object;

class Object
{
public:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
};

class AI
{
public:
	Object *findAllyNear(Object *object, Real range, Int flags);
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next);

protected:
	PartitionFilter *m_next;
};

// Each filter below is an ordinary (non-novtable) class, so VC7.1 emits its
// own vftable under the retail name (??_7Rva0025ED50RootFilter@@6B@ and
// friends) and installs that vftable pointer as the first act of the implicit
// constructor. That store is byte for byte the one retail performs, so no
// extern stand-in and no linker alias is needed.

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
};

class Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *object)
	{
		m_object = object;
	}
	virtual ~Rva00260180SelfFilter() {}

	Object *m_object;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object)
	{
		m_object = object;
	}
	virtual ~Rva0025ED50ObjectFilter() {}

	Object *m_object;
};

class BfmeObjEQT : public PartitionFilter
{
public:
	BfmeObjEQT(Object *object)
	{
		m_object = object;
	}
	virtual ~BfmeObjEQT() {}

	Object *m_object;
};

class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	PartitionFilterRejectBuildings(const Object *object);
	virtual ~PartitionFilterRejectBuildings() {}

private:
	const Object *m_self;
	Bool m_acquireEnemies;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
	{
		m_object = object;
		m_flags = flags;
		m_match = match;
	}
	virtual ~PartitionFilterRelationship() {}

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real range,
		Int distanceCalculation, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

Object *AI::findAllyNear(Object *self, Real range, Int flags)
{
	PartitionFilterRejectBuildings rejectBuildings(self);
	PartitionFilterRelationship relationship(self, 4, false);
	Rva0025ED50RootFilter root;
	Rva0025ED50ObjectFilter objectFilter(self);
	BfmeObjEQT losFilter(self);
	Rva00260180SelfFilter selfFilter(self);

	rejectBuildings.link(relationship.link(root.link(objectFilter.link(&selfFilter))));
	if (flags & 1)
		rejectBuildings.link(&losFilter);

	Object *found = ThePartitionManager->getClosestObject(
		&self->m_position, range, 1, &rejectBuildings);
	if (found == self)
		found = 0;
	return found;
}