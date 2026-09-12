// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/dockupdate /Ireference/shims/moduledata /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// BFME DockUpdate base constructor at RVA 0x002CD4B0 (464 bytes).  The base chain
// stays local so the extra BFME word in UpdateModule is not a shared-header
// claim; the ledger carries the real constructor name.
#include <limits.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

struct Coord3D
{
	// Retail Coord3D has an empty default ctor (0x00083330) and a
	// nontrivial copy ctor (0x0005BC20); this keeps resize fill values in place.
	Coord3D() {}
	Coord3D(const Coord3D &);
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

#include <stl/_bvector.h>

// BFME's resize overload passes its fill value by value.  The vendored
// STLport headers use const references, so only these two element types are
// shadowed in this TU; vector<bool> stays on the witnessed bit-vector class.
namespace _STL
{
template <>
class vector<Coord3D, allocator<Coord3D> > : public _Vector_base<Coord3D, allocator<Coord3D> >
{
public:
	vector() : _Vector_base<Coord3D, allocator<Coord3D> >(allocator<Coord3D>()) {}
	~vector();

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	Coord3D &operator[](unsigned int index)
	{
		return _M_start[index];
	}

	void resize(unsigned int newSize, Coord3D value = Coord3D());

};

template <>
class vector<ObjectID, allocator<ObjectID> >
{
public:
	vector() : m_start(0), m_finish(0), m_endOfStorage(0) {}
	~vector();

	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	ObjectID &operator[](unsigned int index)
	{
		return m_start[index];
	}

	void resize(unsigned int newSize, ObjectID value = (ObjectID)0);

private:
	ObjectID *m_start;
	ObjectID *m_finish;
	ObjectID *m_endOfStorage;
};
}

typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > VecCoord3D;
typedef _STL::vector<ObjectID, _STL::allocator<ObjectID> > ObjectIDVector;
typedef _STL::vector<bool, _STL::allocator<bool> > BoolVector;

class Thing;
class ModuleData;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

	virtual void objectModuleAnchor();

protected:
	void *m_04;
	void *m_08;
};

class BehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class UpdateInterface
{
public:
	virtual void updateAnchor() = 0;
};

class UpdateModule : public ObjectModule,
	public BehaviorInterface, public UpdateInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
		const Int invalid = -1;
		m_nextCallFrameAndPhase = 0;
		m_indexInLogic = invalid;
		m_bfmeReserved = invalid;
	}

	virtual void behaviorAnchor();
	virtual void updateAnchor();

	protected:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_bfmeReserved;
};

class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

class DockUpdateModuleData
{
public:
	void *m_vftable;
	UnsignedInt m_moduleTagNameKey;
	Int m_numberApproachPositionsData;
	Bool m_isAllowPassthrough;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate(Thing *thing, const ModuleData *moduleData);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();

	Coord3D m_enterPosition;
	Coord3D m_dockPosition;
	Coord3D m_exitPosition;
	Int m_numberApproachPositions;
	Int m_numberApproachPositionBones;
	Bool m_positionsLoaded;
	VecCoord3D m_approachPositions;
	ObjectIDVector m_approachPositionOwners;
	BoolVector m_approachPositionReached;
	ObjectID m_activeDocker;
	Bool m_dockerInside;
	Bool m_dockCrippled;
	Bool m_dockOpen;
};

enum
{
	RVA002CD4B0_DEFAULT_APPROACH_VECTOR_SIZE = 10,
	RVA002CD4B0_DYNAMIC_APPROACH_VECTOR_FLAG = -1
};

// ??0DockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DockUpdate::DockUpdate(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_dockOpen = TRUE;
	m_positionsLoaded = FALSE;
	m_numberApproachPositionBones = -1;
	m_activeDocker = INVALID_ID;
	m_dockerInside = FALSE;
	m_dockCrippled = FALSE;

	const DockUpdateModuleData *md =
		(const DockUpdateModuleData *)moduleData;
	m_exitPosition.zero();
	m_dockPosition.zero();
	m_enterPosition.zero();

	m_numberApproachPositions = md->m_numberApproachPositionsData;
	if (m_numberApproachPositions != RVA002CD4B0_DYNAMIC_APPROACH_VECTOR_FLAG)
	{
		m_approachPositions.resize(m_numberApproachPositions);
		m_approachPositionOwners.resize(m_numberApproachPositions);
		m_approachPositionReached.resize(m_numberApproachPositions);
	}
	else
	{
		m_approachPositions.resize(RVA002CD4B0_DEFAULT_APPROACH_VECTOR_SIZE);
		m_approachPositionOwners.resize(RVA002CD4B0_DEFAULT_APPROACH_VECTOR_SIZE);
		m_approachPositionReached.resize(RVA002CD4B0_DEFAULT_APPROACH_VECTOR_SIZE);
	}

	for (Int vectorIndex = 0;
		vectorIndex < m_approachPositions.size(); ++vectorIndex)
	{
		m_approachPositions[vectorIndex].zero();
		m_approachPositionOwners[vectorIndex] = INVALID_ID;
		m_approachPositionReached[vectorIndex] = FALSE;
	}
}
