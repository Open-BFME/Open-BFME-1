// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// BezierProjectileBehavior module constructor, retail 0x001F1470, 297 bytes.
//
// Identity: the class's only instance factory,
// ?friend_newModuleInstance@BezierProjectileBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
// (matched, 0x001F1CE0 -> 0x001F1B90) news up exactly this constructor, and the
// matched destructor 0x001F0240 plus the vtable 0x010A253C installed here agree.
// Member offsets come from the matched xfer 0x001F1860 and calcFlightPath
// 0x001EF5E0; the names the evidence does not fix keep their address token.
//
// Two shaping facts the bytes pin, both found by probing this file:
//  - Module carries a virtual, non-trivial destructor.  It is what makes the
//    base subobjects need unwinding, and that is the THIRD exception state:
//    retail stores the try level 0 between the vector's second and third
//    pointer store, 1 before the list allocation and 2 before the __copy from
//    clear().  With a trivial base destructor MSVC folds the first two states
//    together and the body comes out five bytes short at +0x7B.
//  - setWakeFrame is the LAST statement of the body.  Retail evaluates
//    getObject() early but sinks the call below the trailing five member
//    stores; written before them, MSVC keeps the call in place.

#include <list>
#include <vector>

typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;
typedef int Int;
typedef float Real;
typedef bool Bool;

class Thing;
class ModuleData;
class Object;
class WeaponTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// The vptr has to be here: retail passes `this` unchanged to the out-of-line
// ObjectModule constructor, so the derived object starts with a vptr at 0x00.
class Module
{
public:
	Module(const ModuleData *moduleData) : m_moduleData(moduleData) {}
	virtual ~Module() {}						///< non-trivial: see the header note on the unwind states
	virtual void moduleAnchor() = 0;

private:
	const ModuleData *m_moduleData;
};

class ObjectModule : public Module
{
public:
	ObjectModule(Thing *, const ModuleData *);

protected:
	Object *getObject() const { return m_object; }

private:
	Object *m_object;
};

// upstream layout: .../Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: .../Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
};

// upstream: .../Include/GameLogic/Module/UpdateModule.h
enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum SleepyUpdatePhase
{
	PHASE_INVALID = -1
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data)
		: BehaviorModule(thing, data),
		  m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1),
		  m_currentUpdatePhase(PHASE_INVALID)
	{
	}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);

private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	SleepyUpdatePhase m_currentUpdatePhase;		///< out to sizeof() == 0x20
};

// Plain virtuals rather than virtual destructors, as in the matched destructor:
// retail gives these subobjects a vptr write and no unwind of their own
// (this+0x20 and this+0x24).  The third unwind state comes from Module above.
template <int Number>
class BezierProjectileBehaviorSecondaryBase
{
public:
	virtual void secondarySlot();
};

// vector elements: retail copies them 12 bytes at a time (__copy instantiates on
// Coord3D*), so only the size reaches the bytes.
struct Coord3D
{
	Real x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class BezierProjectileBehavior
	: public UpdateModule,
	  public BezierProjectileBehaviorSecondaryBase<1>,
	  public BezierProjectileBehaviorSecondaryBase<2>
{
public:
	BezierProjectileBehavior(Thing *, const ModuleData *);

private:
	ObjectID m_launcherID;						///< retail this+0x28
	Coord3D m_at2C;								///< retail this+0x2C
	ObjectID m_victimID;							///< retail this+0x38
	const WeaponTemplate *m_at3C;
	const WeaponTemplate *m_at40;
	_STL::vector<Coord3D> m_flightPath;			///< retail this+0x44
	Coord3D m_flightPathStart;					///< retail this+0x50
	Coord3D m_flightPathEnd;						///< retail this+0x5C
	Real m_flightPathSpeed;						///< retail this+0x68
	Int m_flightPathSegments;					///< retail this+0x6C
	Int m_currentFlightPathStep;				///< retail this+0x70
	UnsignedInt m_extraBonusFlags;				///< retail this+0x74
	Int m_altCurve;								///< retail this+0x78
	_STL::list<int> m_at7C;						///< retail this+0x7C
	Bool m_hasDetonated;						///< retail this+0x80
	char m_pad81[3];
	Real m_heightScale;							///< retail this+0x84
};

// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BezierProjectileBehavior::BezierProjectileBehavior(Thing *thing, const ModuleData *data)
	: UpdateModule(thing, data)
{
	m_launcherID = 0;
	m_at2C.zero();
	m_victimID = 0;
	m_at3C = 0;
	m_at40 = 0;
	m_flightPath.clear();
	m_flightPathSegments = 0;
	m_flightPathSpeed = 0;
	m_flightPathStart.zero();
	m_flightPathEnd.zero();
	m_currentFlightPathStep = 0;
	m_extraBonusFlags = 0;
	m_hasDetonated = false;
	m_altCurve = 0;
	m_heightScale = 1.0f;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
