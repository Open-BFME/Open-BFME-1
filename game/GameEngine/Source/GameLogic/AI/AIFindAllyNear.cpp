// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// AI::findAllyNear, retail 0014AF50, 256 bytes.
// Matched caller AIFindNearTargetRandomOrder.cpp names this three-argument
// method at both calls through ILT 4650B. Retail returns with ret 0xC.
// Local filter sizes 8/12/12/12/16/20 follow their stores and stack slots;
// PartitionFilterRejectBuildings' matched constructor independently fixes its layout.
// The other filters retain retail vtable addresses while their owners remain opaque.
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

static __forceinline void setFilterVptr(void *filter, UnsignedInt value)
{
	*reinterpret_cast<UnsignedInt *>(filter) = value;
}

class __declspec(novtable) Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter()
	{
		setFilterVptr(this, 0x01083B80);
	}
	virtual ~Rva0025ED50RootFilter() {}
};

class __declspec(novtable) Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *object)
	{
		setFilterVptr(this, 0x01095724);
		m_object = object;
	}
	virtual ~Rva00260180SelfFilter() {}

	Object *m_object;
};

class __declspec(novtable) Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object)
	{
		setFilterVptr(this, 0x01085DD0);
		m_object = object;
	}
	virtual ~Rva0025ED50ObjectFilter() {}

	Object *m_object;
};

class __declspec(novtable) BfmeObjEQT : public PartitionFilter
{
public:
	BfmeObjEQT(Object *object)
	{
		setFilterVptr(this, 0x010956B0);
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

class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
	{
		setFilterVptr(this, 0x01085DC0);
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