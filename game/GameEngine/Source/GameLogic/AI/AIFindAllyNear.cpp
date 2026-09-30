// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// AI::findAllyNear, retail 0014AF50, 256 bytes.
// Matched caller AIFindNearTargetRandomOrder.cpp names this three-argument
// method at both calls through ILT 4650B. Retail returns with ret 0xC.
// Local filter sizes 8/12/12/12/16/20 follow their stores and stack slots;
// PartitionFilterRejectBuildings' matched constructor independently fixes its layout.
// The other filters store retail vtables through bfmeVft aliases while their owners remain opaque.
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

extern "C" void *bfmeVftRva0025ED50RootFilter[];
extern "C" void *bfmeVftRva00260180SelfFilter[];
extern "C" void *bfmeVftRva0025ED50ObjectFilter[];
extern "C" void *bfmeVftBfmeObjEQT[];
extern "C" void *bfmeVftPartitionFilterRelationship[];
#pragma comment(linker, "/alternatename:_bfmeVftRva0025ED50RootFilter=??_7Rva0025ED50RootFilter@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftRva00260180SelfFilter=??_7Rva00260180SelfFilter@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftRva0025ED50ObjectFilter=??_7Rva0025ED50ObjectFilter@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftBfmeObjEQT=??_7BfmeObjEQT@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftPartitionFilterRelationship=??_7PartitionFilterRelationship@@6B@")

static __forceinline void setFilterVptr(void *filter, UnsignedInt value)
{
	*reinterpret_cast<UnsignedInt *>(filter) = value;
}

class __declspec(novtable) Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter()
	{
		setFilterVptr(this, (UnsignedInt)bfmeVftRva0025ED50RootFilter);
	}
	virtual ~Rva0025ED50RootFilter() {}
};

class __declspec(novtable) Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *object)
	{
		setFilterVptr(this, (UnsignedInt)bfmeVftRva00260180SelfFilter);
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
		setFilterVptr(this, (UnsignedInt)bfmeVftRva0025ED50ObjectFilter);
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
		setFilterVptr(this, (UnsignedInt)bfmeVftBfmeObjEQT);
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
		setFilterVptr(this, (UnsignedInt)bfmeVftPartitionFilterRelationship);
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