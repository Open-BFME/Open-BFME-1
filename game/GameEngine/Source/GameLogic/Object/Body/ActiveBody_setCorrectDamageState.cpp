// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
//
// ActiveBody::setCorrectDamageState(Bool), retail 0x00210BF0 (1574 bytes, RET 4 then INT3).
//
// Identity: the matched constructor ??0ActiveBody@@QAE@PAVThing@@PBVModuleData@@@Z
// (0x00211A50, ActiveBody_Constructor.cpp) ends with setCorrectDamageState(false)
// through ILT 0x0000F777, and the pinned name is the one that caller resolves. The
// body is Zero Hour's ActiveBody::setCorrectDamageState expanded by BFME. The
// damage state comes from the two threshold ratios at +0x24/+0x28 times the max
// health at +0x20, and the rubble arm (template rubble height, falling back to
// GlobalData, then setGeometryInfoZ, pathfind remove+add and a status bit) is Zero
// Hour's block. The layout is the matched constructor's: health at +0x18/+0x1C/+0x20,
// damage state at +0x30, four per-stage values at +0xAC with their flags at +0xBC,
// and the stage/creation-list vector at +0xC0.
//
// BFME additions, read off the bytes: a vcall (primary slot 11) when the state
// changes; two KindOf branches (bits 59 and 7) that switch the geometry's
// "Bookend" shape through 0x0087FA50 and adjust status bits and pathfinding; and,
// when model-condition bit 4 is set, a four-stage threshold at
// 0.75 * (max health * 0.25) whose first newly reached stage fires the matching
// ObjectCreationLists. The KindOf bits and status bits are named by position only.
//
// Callee spellings are the ledger's: BfmeObjE15::bfmeAtE15 and
// BfmeObjF9::rva0087FA50 act on Object's geometry at +0xAC, BfmeHostCL::bfmeResetCL
// and BfmeThingAFB::bfmeGoAFB run on the Object, and BfmeC1058::bfmeGo1058C runs on
// the pointer at Object+0x210.
#include "ascii_string.h"
#include <vector>
#include <bitset>

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

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

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	char m_bytes[0x5c];
};

class ThingTemplate : public Overridable
{
public:
	char m_bytes008[0x58];
	GeometryInfo m_geometryInfo;				// +0x60
	char m_bytes0bc[0xc];
	std::bitset<160> m_kindOf;					// +0xC8
	char m_bytes0dc[0x497 - 0xdc];
	signed char m_structureRubbleHeight;		// +0x497
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	Real getStructureRubbleHeight() const { return (Real)m_structureRubbleHeight; }
	Bool isKindOf(Int k) const { return m_kindOf.test(k); }
};

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };
	BitFlags() { }
	BitFlags(_dummy_kInit, Int idx1) { m_bits.set(idx1); }
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<86> ObjectStatusMaskType;
#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

enum ObjectStatusTypes { OBJECT_STATUS_4 = 4 };

struct BfmeShapeE15 { char m_bytes000[0x1c]; AsciiString m_name; char m_bytes020[4]; };
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);
	char m_bytes000[0x2c];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
	char m_bytes034[0x28];
	int getNumShapes() const { return m_finish - m_start; }
};
class BfmeStrF9;
class BfmeObjF9 { public: void rva0087FA50(const BfmeStrF9 &name, char flag); };
class BfmeHostCL { public: void bfmeResetCL(char flag); };
class BfmeThingAFB { public: void bfmeGoAFB(); };
class BfmeC1058 { public: void bfmeGo1058C(); };

struct ModelConditionFlags
{
	UnsignedInt m_bits[10];
	UnsignedInt test(Int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
};

class Object
{
public:
	void *m_vtable;
	OVERRIDE<ThingTemplate> m_template;
	char m_bytes008[0xa4];
	BfmeObjE15 m_geometryInfo;					// +0xAC
	char m_bytes108[8];
	ModelConditionFlags m_modelConditionFlags;	// +0x110
	char m_bytes138[0x210 - 0x138];
	BfmeC1058 *m_experienceTracker;				// +0x210

	const ThingTemplate *getTemplate() const { return m_template.operator->(); }
	Bool isKindOf(Int k) const { return getTemplate()->isKindOf(k); }
	void setGeometryInfo(const GeometryInfo &geom);
	void setGeometryInfoZ(Real z);
	void setStatusBit(Int bit, Bool set);
	void setStatus(const ObjectStatusMaskType &mask, Bool set);
	void clearStatus(ObjectStatusTypes bit);
	void bfmeResetAllUpgrades();
};

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *obj);
	void removeObjectFromPathfindMap(Object *obj);
};
class AI { public: char m_bytes000[0xc]; Pathfinder *m_pathfinder; Pathfinder *pathfinder() { return m_pathfinder; } };
extern AI *TheAI;

class GlobalData { public: char m_bytes000[0xba8]; Real m_defaultStructureRubbleHeight; };
extern GlobalData *TheGlobalData;

class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary, UnsignedInt lifetimeFrames) const;
	static void create(const ObjectCreationList *ocl, const Object *primary, const Object *secondary, UnsignedInt lifetimeFrames = 0)
	{
		if (ocl)
			ocl->createInternal(primary, secondary, lifetimeFrames);
	}
};

struct Rva00210BF0Entry { const ObjectCreationList *m_ocl; Int m_unknown; Int m_stage; };

class ObjectModule
{
public:
	virtual ~ObjectModule();
	virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	const void *m_data;
	Object *m_object;
	Object *getObject() const { return m_object; }
};
class BehaviorModuleInterface { public: virtual void facet(); };
class BodyModuleInterface
{
public:
	virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5();
	virtual Real getMaxHealth() const;			// slot 6 (+0x18)
	Real m_field14;
};

class ActiveBody : public ObjectModule, public BehaviorModuleInterface, public BodyModuleInterface
{
public:
	void setCorrectDamageState(Bool arg);
	Real m_currentHealth, m_prevHealth, m_maxHealth, m_damagedRatio, m_reallyDamagedRatio, m_initialHealth;	// +0x18
	Int m_curDamageState, m_field34;			// +0x30
	char m_bytes038[0xac - 0x38];
	Real m_fieldAC[4];							// +0xAC
	Bool m_fieldBC[4];							// +0xBC
	std::vector<Rva00210BF0Entry> m_entries;	// +0xC0
};

// ?setCorrectDamageState@ActiveBody@@QAEX_N@Z
void ActiveBody::setCorrectDamageState(Bool arg)
{
	Real damagedLimit = m_damagedRatio * m_maxHealth;
	Int oldState = m_curDamageState;
	Real reallyLimit = m_reallyDamagedRatio * m_maxHealth;
	Int state;
	if (m_currentHealth == 0.0f)
		state = 3;
	else if (m_currentHealth <= reallyLimit)
		state = 2;
	else if (m_currentHealth <= damagedLimit)
		state = 1;
	else
		state = 0;
	m_curDamageState = state;
	if (state != oldState)
		slot11();

	Object *obj = getObject();
	if (obj->isKindOf(59))
	{
		if (m_curDamageState < 3)
		{
			if (oldState == 3)
				obj->setGeometryInfo(obj->getTemplate()->getTemplateGeometryInfo());
		}
		else
		{
			obj->setGeometryInfoZ(TheGlobalData->m_defaultStructureRubbleHeight);
		}

		if (m_curDamageState > oldState && m_curDamageState == 3)
		{
			TheAI->pathfinder()->removeObjectFromPathfindMap(getObject());
			getObject()->setStatusBit(4, true);
			getObject()->setStatusBit(0x4c, true);
			BfmeObjE15 &geom = getObject()->m_geometryInfo;
			Int count = geom.getNumShapes();
			for (Int i = 0; i < count; ++i)
			{
				BfmeShapeE15 *shape = geom.bfmeAtE15(i);
				if (shape->m_name.compare("Bookend") == 0)
				{
					((BfmeObjF9 &)geom).rva0087FA50((const BfmeStrF9 &)AsciiString("Bookend"), 0);
					m_curDamageState = 0;
					((BfmeHostCL *)getObject())->bfmeResetCL(1);
					m_curDamageState = 3;
					getObject()->setStatus(MAKE_OBJECT_STATUS_MASK(82), true);
					break;
				}
			}
		}
		else if (m_curDamageState < oldState && m_curDamageState == 0)
		{
			TheAI->pathfinder()->removeObjectFromPathfindMap(getObject());
			getObject()->clearStatus((ObjectStatusTypes)0x4c);
			getObject()->clearStatus((ObjectStatusTypes)0x52);
			TheAI->pathfinder()->addObjectToPathfindMap(getObject());
		}
		else if (m_curDamageState < oldState && oldState == 3)
		{
			getObject()->setStatusBit(0x4c, true);
			getObject()->clearStatus((ObjectStatusTypes)0x52);
			TheAI->pathfinder()->removeObjectFromPathfindMap(getObject());
			BfmeObjE15 &geom = getObject()->m_geometryInfo;
			((BfmeObjF9 &)geom).rva0087FA50((const BfmeStrF9 &)AsciiString("Bookend"), 1);
			((BfmeHostCL *)getObject())->bfmeResetCL(1);
			getObject()->clearStatus((ObjectStatusTypes)4);
		}
		m_field34 = 0;
	}
	else if (obj->isKindOf(7))
	{
		if (m_curDamageState > oldState && m_curDamageState == 3)
		{
			BfmeObjE15 &geom = obj->m_geometryInfo;
			Int count = geom.getNumShapes();
			for (Int i = 0; i < count; ++i)
			{
				BfmeShapeE15 *shape = geom.bfmeAtE15(i);
				if (shape->m_name.compare("Bookend") == 0)
				{
					((BfmeObjF9 &)geom).rva0087FA50((const BfmeStrF9 &)AsciiString("Bookend"), 0);
					m_curDamageState = 0;
					((BfmeHostCL *)getObject())->bfmeResetCL(1);
					m_curDamageState = 3;
					getObject()->setStatusBit(0x52, true);
					break;
				}
			}
		}
		if (m_curDamageState < 3 && oldState == 3)
		{
			obj->setGeometryInfoZ(getObject()->getTemplate()->getTemplateGeometryInfo().getMaxHeightAbovePosition());
			TheAI->pathfinder()->addObjectToPathfindMap(obj);
			obj->clearStatus((ObjectStatusTypes)4);
		}
		else if (m_curDamageState == 3)
		{
			Real rubbleHeight = getObject()->getTemplate()->getStructureRubbleHeight();
			if (rubbleHeight <= 0.0f)
				rubbleHeight = TheGlobalData->m_defaultStructureRubbleHeight;
			obj->setGeometryInfoZ(rubbleHeight);
			TheAI->pathfinder()->removeObjectFromPathfindMap(obj);
			TheAI->pathfinder()->addObjectToPathfindMap(obj);
			Object *self = getObject();
			if (self->m_experienceTracker)
				self->m_experienceTracker->bfmeGo1058C();
			self->bfmeResetAllUpgrades();
			((BfmeThingAFB *)self)->bfmeGoAFB();
			obj->setStatusBit(4, true);
			m_field34 = 0;
			return;
		}
	}

	if (!getObject()->m_modelConditionFlags.test(4))
		return;
	if (oldState != m_curDamageState && !arg)
		return;

	Real threshold = 0.75f * (getMaxHealth() * 0.25f);
	if (!m_fieldBC[0] && m_fieldAC[0] >= threshold)
	{
		m_field34 = 1;
		m_fieldBC[0] = true;
	}
	else if (!m_fieldBC[1] && m_fieldAC[1] >= threshold)
	{
		m_field34 = 2;
		m_fieldBC[1] = true;
	}
	else if (!m_fieldBC[2] && m_fieldAC[2] >= threshold)
	{
		m_field34 = 3;
		m_fieldBC[2] = true;
	}
	else if (!m_fieldBC[3] && m_fieldAC[3] >= threshold)
	{
		m_field34 = 4;
		m_fieldBC[3] = true;
	}
	else
	{
		return;
	}
	if (!arg)
	{
		for (std::vector<Rva00210BF0Entry>::const_iterator it = m_entries.begin(); it != m_entries.end(); ++it)
		{
			Rva00210BF0Entry entry = *it;
			if (entry.m_stage == m_field34)
				ObjectCreationList::create(entry.m_ocl, getObject(), 0);
		}
	}
}
