// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// Particle::Particle(const BfmeParticleSystemHandle &, const ParticleInfo *),
// retail 0x005CF330, 1044 bytes. ParticleSystem::createParticle (0x005D0040)
// calls it through ILT 0x0001485D; it installs the Particle vtable 0x0110FE8C
// that the matched Particle::~Particle (ParticleDeletingDestructor.cpp,
// 0x005CE990) uses, and member layout follows that destructor: system handle
// at +0x4C, second handle at +0x7C, owned tail at +0x8C. Body order follows
// the Zero Hour Particle constructor (m_system, m_isCulled, m_vel, m_pos,
// m_lastPos, ..., addParticle to the manager then to the system); BFME adds a
// render object built from the system module's model name with a local
// AssetList (AssetListOperatorInsert.cpp) and five random-value fields.
// EH states: base (0), the two handles and the tail (1-3), the returned name
// (4) and the AssetList (5).
#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include "snapshot.h"
#include "string_base.h"

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef bool Bool;

class ParticleSystem;
class Particle;
class RenderObjClass;

// The model-name getter returns an AsciiString by value; its removeLastChar
// and destructor are the matched StringBase<char> bodies.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void removeLastChar() { m_data.removeLastChar(); }
	Bool isEmpty() const { return !m_data.m_data || m_data.m_data->length == 0; }
	const char *str() const { return m_data.m_data ? m_data.m_data->data : ""; }
	StringBase<char> m_data;
};

class Coord3D
{
public:
	Real x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

extern ParticleSystem *Make00001B18();

class ParticleSystemHandle
{
public:
	ParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();
	ParticleSystem *operator->() const { return m_system ? m_system : Make00001B18(); }

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();
};

class ParticleSystemModule
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10();
	virtual AsciiString getModelName();
	virtual UnsignedInt s18();
};

class ParticleSystem
{
public:
	char m_00[0x0c];
	Int m_0c;
	char m_10[0x7c - 0x10];
	Int m_priority;
	char m_80[0x1c8 - 0x80];
	ParticleSystemModule *m_1c8;
};


class GameClient
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18(); virtual void s19();
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;

class RenderObjClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0a();
	virtual void v0b();
	virtual void v0c();
	virtual void v0d();
	virtual void v0e();
	virtual void v0f();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v1a();
	virtual void v1b();
	virtual void v1c();
	virtual void v1d();
	virtual void v1e();
	virtual void v1f();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v2a();
	virtual void v2b();
	virtual void v2c();
	virtual void v2d();
	virtual void v2e();
	virtual void v2f();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v3a();
	virtual void v3b();
	virtual void v3c();
	virtual void v3d();
	virtual void v3e();
	virtual void v3f();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v4a();
	virtual void v4b();
	virtual void v4c();
	virtual void v4d();
	virtual void v4e();
	virtual void v4f();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v5a();
	virtual void v5b();
	virtual void v5c();
	virtual void v5d();
	virtual void v5e();
	virtual void v5f();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void setSlot190(Int value);
};

class BfmeGlobPB
{
public:
	virtual void s00(); virtual void s04();
	virtual void Add_Render_Object(RenderObjClass *obj);
};
extern BfmeGlobPB *g_bfmeGlobPB;

class BfmeDebugReport
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
	virtual void s30(); virtual void s34();
	virtual BfmeDebugReport *addMessage(const char *text);
	virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48();
	virtual void finish(Int level);
};

class BfmeAwakenDebug
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
	virtual void beginReport();
	virtual void s64(); virtual void s68();
	virtual BfmeDebugReport *startReport(Int a, Int b);
};
extern BfmeAwakenDebug *TheBfmeAwakenDebug;

extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);
extern RenderObjClass *Create_Render_Obj(const char *name);
extern void *bfmeGoEMEb(void *name);
extern void Rva009EBAC0(int value);
extern void Rva00739B30(RenderObjClass *obj, bool flag);

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *name);

// The prototype set AssetListOperatorInsert.cpp (0x00141D00) matched: a
// pointer set plus a changed flag, inserted through the same lookup.
class AssetList
{
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}
	AssetList &operator <<(const AsciiString &name)
	{
		if (m_prototypes.insert(((FindPrototypeFn)bfmeGoEMEb)(name.str())).second)
			m_changed = true;
		return *this;
	}

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

class ParticleRandomValue
{
public:
	virtual void s00(); virtual void s04();
	virtual UnsignedInt getValue(Particle *particle) const;
};

class Rva005C8D40Output;

// The matched body at 0x005C8D40 (ILT 0x0002EFEB), called on the info.
class Rva005C8D40
{
public:
	void fill(Rva005C8D40Output *out, void *particle);
};

static inline UnsignedInt randomValueFor(const ParticleRandomValue *value, Particle *particle)
{
	if (value)
		return value->getValue(particle);
	return 0;
}

// The 0x3c-byte base Particle shares with the info it is created from; its
// fields follow the Zero Hour ParticleInfo order.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class Rva005CF330ParticleBase : public Snapshot
{
public:
	Rva005CF330ParticleBase()
	{
		m_04.zero();
		m_emitterPos.zero();
		m_pos.zero();
		m_vel.zero();
		m_lifetime = 0;
		m_particleUpTowardsEmitter = false;
	}

	Coord3D m_04;
	Coord3D m_vel;
	Coord3D m_pos;
	Coord3D m_emitterPos;
	UnsignedInt m_lifetime;
	Bool m_particleUpTowardsEmitter;
};

class ParticleInfo : public Rva005CF330ParticleBase
{
public:
	ParticleRandomValue *m_3c;
	ParticleRandomValue *m_40;
	ParticleRandomValue *m_44;
	ParticleRandomValue *m_48;
	char m_4c[8];
	ParticleRandomValue *m_54;
};

class Rva005CE920
{
public:
	Rva005CE920() : m_8c(0), m_90(0), m_94(0), m_98(0), m_a4(0), m_a8(0), m_ac(0), m_b0(0) {}
	~Rva005CE920();
	UnsignedInt m_8c, m_90, m_94, m_98;
	UnsignedInt m_9c, m_a0;
	UnsignedInt m_a4;
	UnsignedInt m_a8, m_ac, m_b0;
};

class Particle : public Rva005CF330ParticleBase
{
public:
	Particle(const BfmeParticleSystemHandle &system, const ParticleInfo *info);
	virtual ~Particle();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &);

	Particle *m_systemNext;                 // +0x3c
	Particle *m_systemPrev;                 // +0x40
	Particle *m_overallNext;                // +0x44
	Particle *m_overallPrev;                // +0x48
	BfmeParticleSystemHandle m_system;      // +0x4c
	UnsignedInt m_personality;              // +0x58
	Coord3D m_lastPos;                      // +0x5c
	UnsignedInt m_lifetimeLeft;             // +0x68
	UnsignedInt m_createTimestamp;          // +0x6c
	RenderObjClass *m_renderObject;
	UnsignedInt m_74;
	Bool m_isCulled;                        // +0x78
	Bool m_inSystemList;                    // +0x79
	Bool m_inOverallList;                   // +0x7a
	BfmeParticleSystemHandle m_destroySystem;
	UnsignedInt m_destroySystemID;
	Rva005CE920 m_tail;
};


class ParticleSystemManager
{
public:
	void addParticle(Particle *particleToAdd, Int priority)
	{
		if (particleToAdd->m_inOverallList)
			return;
		if (!m_allParticlesHead[priority])
			m_allParticlesHead[priority] = particleToAdd;
		if (m_allParticlesTail[priority])
		{
			m_allParticlesTail[priority]->m_overallNext = particleToAdd;
			particleToAdd->m_overallPrev = m_allParticlesTail[priority];
		}
		else
			particleToAdd->m_overallPrev = 0;
		m_allParticlesTail[priority] = particleToAdd;
		particleToAdd->m_overallNext = 0;
		particleToAdd->m_inOverallList = true;
		++m_particleCount;
	}
	// The ledger's spelling of the body at 0x005BE1B0 (ILT 0x000338E8); this
	// call site passes the particle system as `this` and the particle.
	void friend_addParticleSystem(ParticleSystem *particleSystemToAdd);
	char m_00[0x0c];
	Particle *m_allParticlesHead[14];
	Particle *m_allParticlesTail[14];
	char m_7c[8];
	Int m_particleCount;
};
extern ParticleSystemManager *TheParticleSystemManager;

Particle::Particle(const BfmeParticleSystemHandle &system, const ParticleInfo *info)
	: m_renderObject(0), m_74(1), m_destroySystemID(0)
{
	m_system = system;
	m_isCulled = false;
	m_vel = info->m_vel;
	m_pos = info->m_pos;
	m_lastPos.zero();
	m_particleUpTowardsEmitter = info->m_particleUpTowardsEmitter;
	m_emitterPos = info->m_emitterPos;
	m_lifetime = info->m_lifetime;
	m_lifetimeLeft = info->m_lifetime;
	m_createTimestamp = TheGameClient->getFrame();
	m_personality = 0;

	if (system->m_0c == 2)
	{
		AsciiString name = system->m_1c8->getModelName();
		if (!name.isEmpty())
		{
			for (Int i = 4; i; --i)
				name.removeLastChar();
			AssetList assets;
			assets << name;
			Rva009EBAC0((int)&assets);
			m_renderObject = Create_Render_Obj(name.str());
			m_74 = system->m_1c8->s18();
			if (m_renderObject)
			{
				m_renderObject->setSlot190(1);
				Rva00739B30(m_renderObject, false);
				g_bfmeGlobPB->Add_Render_Object(m_renderObject);
			}
			else if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->beginReport();
				BfmeDebugReport *report = TheBfmeAwakenDebug->startReport(0, 0)
					->addMessage("Particle system: could not create render object named '");
				report->addMessage(name.str());
				report->addMessage("'")->finish(2);
			}
		}
	}

	m_inOverallList = false;
	m_inSystemList = false;
	m_overallNext = 0;
	m_overallPrev = 0;
	m_systemNext = 0;
	m_systemPrev = 0;

	TheParticleSystemManager->addParticle(this, system->m_priority);
	reinterpret_cast<ParticleSystemManager *>(m_system.operator->())
		->friend_addParticleSystem(reinterpret_cast<ParticleSystem *>(this));

	m_tail.m_8c = randomValueFor(info->m_3c, this);
	m_tail.m_90 = randomValueFor(info->m_40, this);
	m_tail.m_94 = randomValueFor(info->m_44, this);
	m_tail.m_98 = randomValueFor(info->m_48, this);
	m_tail.m_a4 = randomValueFor(info->m_54, this);
	reinterpret_cast<Rva005C8D40 *>(const_cast<ParticleInfo *>(info))
		->fill((Rva005C8D40Output *)&m_tail.m_a8, this);
}
