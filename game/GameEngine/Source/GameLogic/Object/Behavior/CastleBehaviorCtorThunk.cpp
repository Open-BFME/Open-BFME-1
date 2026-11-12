// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0CastleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00376250 (661 B,
// ret 8 at +0x290 then INT3).
//
// BFME 1 retail evidence: the body runs the matched FoundationAIUpdate
// constructor (0x002BA040), stores the four CastleBehavior vtables the matched
// destructor (0x003728E0, CastleBehaviorDestructorThunk.cpp) restores, and
// builds the members that destructor tears down, in its layout: scalars
// +0x9C..+0xB4, five pointer vectors at +0xB8..+0xE8, the set at +0xF4, the
// string at +0x100 and the map<int, unsigned int> at +0x108. It then gives the
// object a 10-high, 50 x 50 cylinder footprint through a temporary GeometryInfo
// (constructor 0x00100580, Object::lazySet 0x001D5C20, destructor 0x000FFCA0),
// clears the first three vectors and the set, runs the shared owned-object
// clear 0x00371120, marks +0xA4 when the module data's +0x1C string is
// non-empty, and wakes the module next frame.
//
// [BFME 2 donor] open-bfme-2 76f0baefa6
// Code/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorCtor.cpp
// (BFME 2 0x003983D4, 329 B) supplied the statement order: initialiser list,
// vector clears, set reset, the owned-object clear, the pre-built-player flag,
// then setWakeFrame. BFME 1 adds the GeometryInfo footprint, which BFME 2 lacks.
//
// Codegen notes: the cleared vectors hold ObjectID (an enum, so STLport's
// clear copies element by element as retail does; a pointer element type
// takes the trivial-copy path), and the Object pointer is read into a local
// before the lazySet call, which loads ECX ahead of the &geometry argument
// as retail does.

#include <map>
#include <set>
#include <vector>

class Thing;
class ModuleData;
class Object;

typedef float Real;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height, Real majorRadius, Real minorRadius);
	virtual ~GeometryInfo();

private:
	unsigned char m_data[0x58];
};

// The ledger names the 0x001D5C20 GeometryInfo install on Object lazySet.
class Object
{
public:
	void lazySet(void *geometry);
};

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

protected:
	const void *m_moduleData;
};

class ObjectModule : public Gen_dtor_00113f20
{
protected:
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class FoundationAIUpdateIface3
{
public:
	virtual void interface3Anchor() = 0;
};

class Gen_dtor_000b33c0
{
public:
	virtual ~Gen_dtor_000b33c0();

private:
	unsigned char m_data[0x6c];
};

class FoundationAIUpdate : public UpdateModule, public FoundationAIUpdateIface3
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~FoundationAIUpdate();

private:
	Gen_dtor_000b33c0 m_member;
	void *m_pendingFoundation;
	bool m_pendingFlag;
};

struct Gen_t_000ef440_k4
{
	int a[1];
	Gen_t_000ef440_k4();
	Gen_t_000ef440_k4(const Gen_t_000ef440_k4&);
	~Gen_t_000ef440_k4();
	Gen_t_000ef440_k4& operator=(const Gen_t_000ef440_k4&);
};

bool operator==(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
bool operator<(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);

class Gen_00371120
{
public:
	void bfmeClear();
};

class CastleOwnedObject;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0), m_length(-1) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
	int m_length;
};

// The module data's +0x1C AsciiString: empty when it has no buffer or the
// buffer's length word is zero.
struct CastleBehaviorStringData
{
	int m_refCount;
	unsigned short m_length;
};

struct CastleBehaviorModuleData
{
	unsigned char m_pad00[0x1c];
	CastleBehaviorStringData *m_preBuiltPlayer;

	bool isPreBuiltPlayerEmpty() const { return !m_preBuiltPlayer || !m_preBuiltPlayer->m_length; }
};

class CastleBehavior : public FoundationAIUpdate
{
public:
	CastleBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~CastleBehavior();

private:
	int m_at9c;
	int m_ata0;
	unsigned char m_ata4;
	unsigned char m_ata5;
	int m_ata8;
	unsigned char m_atac;
	int m_atb0;
	int m_atb4;
	_STL::vector<ObjectID> m_vectorB8;
	_STL::vector<ObjectID> m_vectorC4;
	_STL::vector<ObjectID> m_vectorD0;
	_STL::vector<CastleOwnedObject *> m_vectorDC;
	_STL::vector<CastleOwnedObject *> m_vectorE8;
	_STL::set<Gen_t_000ef440_k4> m_setF4;
	BFMERetailAsciiString m_string100;
	_STL::map<int, unsigned int> m_map108;
};

CastleBehavior::CastleBehavior(Thing *thing, const ModuleData *moduleData)
	: FoundationAIUpdate(thing, moduleData),
	  m_at9c(0),
	  m_ata0(0),
	  m_ata4(false),
	  m_ata5(true),
	  m_ata8(0),
	  m_atac(false),
	  m_atb0(-1),
	  m_atb4(0)
{
	GeometryInfo geometry(GEOMETRY_CYLINDER, false, 10.0f, 50.0f, 50.0f);
	Object *obj = m_object;
	obj->lazySet(&geometry);

	m_vectorB8.clear();
	m_vectorC4.clear();
	m_vectorD0.clear();
	m_setF4.clear();
	reinterpret_cast<Gen_00371120 *>(this)->bfmeClear();

	if (!((const CastleBehaviorModuleData *)m_moduleData)->isPreBuiltPlayerEmpty())
		m_ata4 = true;

	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
