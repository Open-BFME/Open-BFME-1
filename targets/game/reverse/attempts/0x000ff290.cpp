// ?addBibs@BuildAssistant@@UAEXPBUCoord3D@@PBVThingTemplate@@@Z
// partial score=0.95 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>

// BuildAssistant::addBibs, retail 0x000FF290 (452 bytes).
//
// Identity: slot 13 of the BuildAssistant SubsystemInterface table at
// 0x010860D8 (ctor 0x000FDA80), the addBibs position of the Zero Hour
// declaration order, and the body is the Zero Hour one: a KINDOF_STRUCTURE
// accept filter against KINDOFMASK_NONE, range = vision range plus three
// major radii, isRemovableForConstruction inlined, and
// TheTerrainVisual->addFactionBib(them, true) (W3DTerrainVisual slot 23) for
// every immobile survivor.  As in clearRemovableForConstruction the vendored
// headers carry a different Object layout, so the BFME offsets are spelled
// here.  KindOf is a 192-bit mask at ThingTemplate+0xc8: STRUCTURE bit 7 and
// IMMOBILE bit 2 of word 0, SHRUBBERY bit 6 of word 0, CLEARED_BY_BUILD bit 18
// of word 1, INERT bit 24 of word 2.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <Int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int idx)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[idx >> 5] |= 1u << (idx & 31);
	}

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_STRUCTURE = 7
};

enum KindOfWordMask
{
	KINDOF_IMMOBILE_MASK = 0x00000004,
	KINDOF_SHRUBBERY_MASK = 0x00000040,
	KINDOF_CLEARED_BY_BUILD_MASK = 0x00040000,
	KINDOF_INERT_MASK = 0x01000000
};

extern const KindOfMaskType KINDOFMASK_NONE;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GeometryInfo.h
class GeometryInfo
{
public:
	Real getMajorRadius() const
	{
		return m_majorRadius;
	}

private:
	unsigned char m_pad[0x10];
	Real m_majorRadius;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	UnsignedInt getKindOfWord(Int word) const
	{
		return m_kindof[word];
	}

	const GeometryInfo &getTemplateGeometryInfo() const
	{
		return m_geometryInfo;
	}

	Real friend_calcVisionRange() const
	{
		return m_visionRange;
	}

private:
	unsigned char m_pad[0x58];
	GeometryInfo m_geometryInfo;
	unsigned char m_pad2[0x54];
	UnsignedInt m_kindof[6];
	unsigned char m_pad3[0x2c4];
	Real m_visionRange;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = static_cast<const ThingTemplate *>(
				tmpl->m_nextOverride->getFinalOverride());
		return tmpl;
	}

private:
	void *_vptr;
	const ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	UnsignedInt getKindOfWord(Int word) const
	{
		return getTemplate()->getKindOfWord(word);
	}

	UnsignedInt getStatusBits() const
	{
		return *reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const char *>(this) + 0x344);
	}
};

struct SimpleObjectIteratorClump
{
	Int m_valueBits;
	Int m_distanceBits;
};

struct SimpleObjectIterator
{
	_STL::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
public:
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);

	Object *next(void) const
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return NULL;
		SimpleObjectIteratorClump *cursor = m_mpo->m_cursor;
		Object *object = reinterpret_cast<Object *>(cursor->m_valueBits);
		++cursor;
		m_mpo->m_cursor = cursor;
		return object;
	}

	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) { }
	virtual ~PartitionFilter() { }
	virtual Bool allow(Object *obj) = 0;

private:
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() { }
	virtual Bool allow(Object *obj);

	operator Int()
	{
		return (Int)this;
	}

private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1
};

class PartitionManager
{
};

class BfmeWideForwardC
{
private:
	unsigned char m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};

extern PartitionManager *ThePartitionManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h
class TerrainVisual
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
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void addFactionBib(Object *factionBuilding, Bool highlight,
		Real extra = 0);
};

extern TerrainVisual *TheTerrainVisual;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
public:
	virtual void addBibs(const Coord3D *worldPos, const ThingTemplate *build);

protected:
	__forceinline Bool isRemovableForConstruction(Object *obj)
	{
		if (obj->getKindOfWord(2) & KINDOF_INERT_MASK)
			return false;

		if ((obj->getKindOfWord(0) & KINDOF_SHRUBBERY_MASK)
			|| (obj->getKindOfWord(1) & KINDOF_CLEARED_BY_BUILD_MASK)
			|| (obj->getStatusBits() & 1))
			return true;

		return false;
	}
};

// ?addBibs@BuildAssistant@@UAEXPBUCoord3D@@PBVThingTemplate@@@Z
void BuildAssistant::addBibs(const Coord3D *worldPos, const ThingTemplate *build)
{
	Real range = build->friend_calcVisionRange();
	range += 3 * build->getTemplateGeometryInfo().getMajorRadius();

	const BfmeWideResult &found =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)worldPos, *(Int *)&range, FROM_CENTER_3D,
			PartitionFilterAcceptByKindOf(
				KindOfMaskType(KindOfMaskType::kInit, KINDOF_STRUCTURE),
				KINDOFMASK_NONE),
			0);

	Object *them;
	while ((them = found.next()) != NULL)
	{
		if (isRemovableForConstruction(them))
			continue;

		if (them->getKindOfWord(0) & KINDOF_IMMOBILE_MASK)
			TheTerrainVisual->addFactionBib(them, true);
	}
}
