// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common/Thing
// stlport
#define _STLP_USE_STATIC_LIB 1
//
// Object::~Object, retail 0x001D4010 (1049 bytes, RET at +0x418 then INT3).
//
// Identity: the matched protected scalar-deleting destructor ??_GObject@@MAEPAXI@Z
// (0x001D5CF0, primary vftable 0x00C9EE58 slot 7) calls this body through ILT
// 0x0000207C. The body installs Object's own five vftables (0x0109EE58 at +0x00,
// 0x0109EE44 at +0x60, 0x0109EE28 at +0x64, 0x0109EE00 at +0x6C, 0x0109EDD0 at
// +0x70), the virtual base's 0x0109EDB8 through the vbptr at +0x68, and the
// vtordisp at vbase-4, exactly as the matched constructor 0x001D29A0 does.
// Statement order follows Zero Hour's Object::~Object with BFME's additions.
//
// Bases. +0x60 is Snapshot: after the members are gone retail stores Snapshot's
// vftable 0x01073744 there, and last calls Thing's destructor (0x001320E0). The
// bases at +0x64/+0x6C/+0x70 and the virtual base get no destructor work, so
// they are modelled as interfaces; their names carry the address of the vftable
// Object installs for them, because their real names are not proven.
//
// Members. Fifteen EH states: Thing (0), Snapshot (1), m_name, m_geometryInfo
// (two internal states for its vectors), m_originalTeamName, +0x248, m_weaponSet,
// the +0x310 list, +0x328, +0x32C, the +0x34C vector and the +0x374 pair (one
// internal state). m_geometryInfo is the 0x5C-byte geometry ObjectGeometry.cpp
// proves; its two vectors are the element types whose out-of-line destructors
// are 0x000FF700 (+0x2C) and 0x000FF7D0 (+0x38).
//
// Template lookup goes through Zero Hour's OVERRIDE<ThingTemplate>::operator->
// and the recursive inline Overridable::getFinalOverride; with that native
// model retail keeps &m_geometryInfo in EBX and zero in EBP. The flag tests are
// KINDOF bits 143/89/25/88 of the template's bit set at +0xC8, named here by
// position only.
//
// Callee spellings are the ledger's: 0x0037CBC0 is matched as
// BfmeObjectIdOwner::removeObject and is reached on TheEmotionSystem; 0x001BF300
// is matched as BfmeQ1086::bfmeGo1086A but runs on this Object; 0x00595160 is
// matched as Rva00595160::update and receives this Object.

enum Rva001D4010Kind { kind143 = 143, kind89 = 89, kind25 = 25, kind88 = 88 };
struct Rva001D4010Template;
#define THING_TU_MEMBERS const Rva001D4010Template *getTemplate() const; bool isKindOf(Rva001D4010Kind kind) const;
#include "thing.h"
#include "snapshot.h"
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
#include <vector>
#include <list>
#include <bitset>

class Object;
class Team;

// upstream: GeneralsMD/Code/GameEngine/Include/Common/Overridable.h and Override.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vtable;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	const T *m_overridable;
};

template<int N> struct Rva001D4010Flags
{
	std::bitset<N> bits;
	bool test(int i) const { return bits.test(i); }
};

struct Rva001D4010Template : Overridable
{
	char bytes008[0xc0];
	Rva001D4010Flags<160> m_kindOf;				// +0xC8
	bool isKindOf(Rva001D4010Kind kind) const { return m_kindOf.test(kind); }
};

inline const Rva001D4010Template *Thing::getTemplate() const
{
	return ((const OVERRIDE<Rva001D4010Template> *)&m_template)->operator->();
}
inline bool Thing::isKindOf(Rva001D4010Kind kind) const { return getTemplate()->isKindOf(kind); }

// Base subobjects Object installs vftables for.
struct Rva00C9EDB8VirtualBase
{
	virtual void vbaseSlot0(); virtual void vbaseSlot1(); virtual void vbaseSlot2(); virtual void vbaseSlot3(); virtual void vbaseSlot4();
};
struct Rva00C9EE28Base : virtual Rva00C9EDB8VirtualBase { virtual void base064Slot0(); };
struct Rva00C9EE00Base { virtual void base06CSlot0(); };
struct Rva00C9EDD0Base { virtual void base070Slot0(); };

// Owned objects deleted through their virtual scalar-deleting destructor (slot 0).
struct Rva001D4010Owned { virtual ~Rva001D4010Owned(); };

// Vector element types; their vector destructors are matched at 0x000FF700 / 0x000FF7D0.
struct Gen000FF700 { char bytes000[0x1c]; AsciiString m_name; char bytes020[4]; };
struct Gen000FF7D0 { char bytes000[0xc]; AsciiString m_name; };

// The 0x5C-byte geometry at Object+0xAC (see ObjectGeometry.cpp).
struct Rva001D4010Geometry : Snapshot
{
	char bytes004[0x28];
	std::vector<Gen000FF700> m_shapes;			// +0x2C
	std::vector<Gen000FF7D0> m_records;			// +0x38
	char bytes044[0x18];
	virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
};

class WeaponSet { public: ~WeaponSet(); char bytes[0x18]; };	// ??1WeaponSet@@QAE@XZ 0x001EAD40
class Rva001DB3E0List { public: ~Rva001DB3E0List(); void *m_current; void *m_head; };

struct Rva001D4010ListValue { unsigned m_value; AsciiString m_text; };
struct Rva001D4010VectorValue { char bytes[0x5c]; };
struct Rva001D4010StringPair { char bytes[0x14]; UnicodeString m_wide; AsciiString m_narrow; };

class BfmeObjectIdOwner { public: bool removeObject(Object *); };
class EmotionSystem;
extern EmotionSystem *TheEmotionSystem;			// 0x012F0878

// upstream: GameLogic::updateObjectsChangedTriggerAreas copies m_frame.
class GameLogic
{
public:
	void updateObjectsChangedTriggerAreas() { m_rva16c = m_frame; }
	void rva00383440(Object *obj);				// ZH sendObjectDestroyed position
	char bytes000[0x3c];
	unsigned m_frame;							// +0x3C (ZH position)
	char bytes040[0x12c];
	unsigned m_rva16c;							// +0x16C
};
extern GameLogic *TheGameLogic;

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void notifyOfObjectDestruction(Object *obj);	// slot 32 (+0x80), ZH position
	void notifyOfObjectCreationOrDestruction();
};
extern ScriptEngine *TheScriptEngine;

struct Rva00595160Argument;
class Rva00595160 { public: void update(Rva00595160Argument *); };
class AptPalantir { public: char bytes000[0x2b8]; Rva00595160 m_rva2b8; };
extern AptPalantir *TheAptPalantir;

class Radar { public: void removeObject(Object *); };
extern Radar *TheRadar;

class PartitionManager { public: void rva008F73C0(Rva00C9EE28Base *obj); };
extern PartitionManager *TheShroudManager;

class AIGroup { public: bool remove(Object *); };
class BfmeQ1086 { public: void bfmeGo1086A(); };

class Object : public Thing, public Snapshot, public Rva00C9EE28Base, public Rva00C9EE00Base, public Rva00C9EDD0Base
{
public:
	virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
	virtual void reactToTransformChange(const Matrix3D *, const Coord3D *, Real);
	virtual void base064Slot0(); virtual void base06CSlot0(); virtual void base070Slot0();
	virtual void vbaseSlot0(); virtual void vbaseSlot1(); virtual void vbaseSlot2(); virtual void vbaseSlot3(); virtual void vbaseSlot4();
	virtual void setTeam(Team *team);
protected:
	virtual ~Object();
public:
	unsigned m_id, m_producerID, m_builderID;	// +0x74
	void *m_drawable;							// +0x80
	AsciiString m_name;							// +0x84
	Object *m_next, *m_prev;					// +0x88
	unsigned m_status[3];						// +0x90
	char bytes09c[0x10];
	Rva001D4010Geometry m_geometryInfo;			// +0xAC
	Rva001D4010Geometry *m_geometryClone;		// +0x108
	char bytes10c[0x7c];
	AIGroup *m_group;							// +0x188
	char bytes18c[0x48];
	void *m_rva1d4, *m_rva1d8, *m_rva1dc, *m_rva1e0;
	void *m_defectionHelper;					// +0x1E4
	void *m_rva1e8;
	void *m_firingTracker;						// +0x1EC
	Rva001D4010Owned **m_behaviors;				// +0x1F0
	char bytes1f4[8];
	void *m_contain, *m_body, *m_ai, *m_physics, *m_radarData;	// +0x1FC
	Rva001D4010Owned *m_experienceTracker;		// +0x210
	char bytes214[0x2c];
	AsciiString m_originalTeamName;				// +0x240
	unsigned m_indicatorColor;					// +0x244
	AsciiString m_rva248;
	char bytes24c[0x18];
	WeaponSet m_weaponSet;						// +0x264
	char bytes27c[0x3c];
	Rva001D4010Owned *m_rva2b8, *m_rva2bc;
	char bytes2c0[0x50];
	std::list<Rva001D4010ListValue> m_rva310;
	char bytes314[0x14];
	AsciiString m_rva328, m_rva32c;
	char bytes330[0x1c];
	std::vector<Rva001D4010VectorValue> m_rva34c;
	char bytes358[0xc];
	Rva001DB3E0List *m_rva364;
	char bytes368;
	bool m_rva369;
	char bytes36a[0xa];
	Rva001D4010StringPair m_rva374;
	char bytes390[0x20];
	void *m_partitionData;						// +0x3B0
	char bytes3b4[8];
};
BFME_LAYOUT_CHECK(Object, m_id, 0x74);
BFME_LAYOUT_CHECK(Object, m_geometryInfo, 0xac);
BFME_LAYOUT_CHECK(Object, m_geometryClone, 0x108);
BFME_LAYOUT_CHECK(Object, m_group, 0x188);
BFME_LAYOUT_CHECK(Object, m_behaviors, 0x1f0);
BFME_LAYOUT_CHECK(Object, m_radarData, 0x20c);
BFME_LAYOUT_CHECK(Object, m_originalTeamName, 0x240);
BFME_LAYOUT_CHECK(Object, m_weaponSet, 0x264);
BFME_LAYOUT_CHECK(Object, m_rva310, 0x310);
BFME_LAYOUT_CHECK(Object, m_rva369, 0x369);
BFME_LAYOUT_CHECK(Object, m_rva374, 0x374);
BFME_LAYOUT_CHECK(Object, m_partitionData, 0x3b0);

// ??1Object@@MAE@XZ
Object::~Object()
{
	m_rva369 = true;

	if (isKindOf(kind143) || isKindOf(kind89))
		((BfmeObjectIdOwner *)TheEmotionSystem)->removeObject(this);

	if (!isKindOf(kind25) && !isKindOf(kind88))
	{
		TheGameLogic->updateObjectsChangedTriggerAreas();
		if (TheScriptEngine)
			TheScriptEngine->notifyOfObjectCreationOrDestruction();
	}

	if (TheAptPalantir && !(m_status[1] & 0x40000))
		TheAptPalantir->m_rva2b8.update((Rva00595160Argument *)this);

	if (m_radarData)
		TheRadar->removeObject(this);

	TheGameLogic->rva00383440(this);

	setTeam(0);

	((BfmeQ1086 *)this)->bfmeGo1086A();

	if (m_partitionData)
		TheShroudManager->rva008F73C0(this);

	if (m_group)
		m_group->remove(this);

	m_ai = 0;
	m_physics = 0;
	m_contain = 0;
	m_body = 0;

	for (Rva001D4010Owned **b = m_behaviors; *b; ++b)
	{
		delete *b;
		*b = 0;
	}
	delete [] m_behaviors;
	m_behaviors = 0;

	delete m_experienceTracker;
	m_experienceTracker = 0;

	m_firingTracker = 0;
	m_rva1d4 = 0;
	m_rva1d8 = 0;
	m_rva1dc = 0;
	m_rva1e0 = 0;
	m_defectionHelper = 0;
	m_rva1e8 = 0;

	m_id = 0;

	if (TheScriptEngine)
		TheScriptEngine->notifyOfObjectDestruction(this);

	if (m_geometryClone != &m_geometryInfo)
		delete m_geometryClone;

	delete m_rva364;

	delete m_rva2b8;
	m_rva2b8 = 0;
	delete m_rva2bc;
	m_rva2bc = 0;
}
