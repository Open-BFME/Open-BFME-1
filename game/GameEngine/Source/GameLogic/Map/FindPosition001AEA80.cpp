// Retail RVA 001AEA80, 1102 bytes. The findPositionAround caller at
// 001AF610 calls this free five-argument cdecl helper through an ILT.
// ZH PartitionManager::tryPosition supplies the control-flow reference, but
// BFME moved this to a free helper; retain the address-derived identity.
// GeometryInfo uses BFME's 0x5C layout witnessed by GeometryInfoConstructor.cpp,
// not the smaller ZH geometry.h layout. Its two owned vectors are at 2C/38.
// The filter constructor at FBCB0 copies three words and two pointers plus a
// byte flag; its semantic type remains unproved. The result iterator has a
// null-object sentinel, and the native KindOf accessor supplies the test shape.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

#define Overridable Rva001AEA80ReferenceOverridable
#include "PreRTS.h"
#include "Common/GameCommon.h"
#include "Common/GameType.h"
#include "Common/KindOf.h"
#include "Lib/trig.h"
#undef Overridable

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Rva001AEA80GeometryShape
{
	unsigned char bytes[0x28];
};

struct Rva001AEA80GeometryRecord
{
	unsigned char bytes[0x14];
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

enum FindPositionFlags
{
	FPF_NONE = 0x00000000,
	FPF_IGNORE_WATER = 0x00000001,
	FPF_WATER_ONLY = 0x00000002,
	FPF_IGNORE_ALL_OBJECTS = 0x00000004,
	FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS = 0x00000008,
	FPF_IGNORE_ALLY_OR_NEUTRAL_STRUCTURES = 0x00000010,
	FPF_IGNORE_ENEMY_UNITS = 0x00000020,
	FPF_IGNORE_ENEMY_STRUCTURES = 0x00000040,
	FPF_USE_HIGHEST_LAYER = 0x00000080,
	FPF_CLEAR_CELLS_ONLY = 0x00000100
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();

	GeometryInfo(GeometryType, Bool, Real, Real, Real);

	operator void *()
	{
		return this;
	}

	Bool m_isSmall;
	Int m_scalar08;
	Int m_scalar0c;
	Int m_scalar10;
	Real m_boundingSphereRadius;
	Int m_scalar18;
	Int m_scalar1c;
	Int m_scalar20;
	Int m_scalar24;
	Int m_scalar28;
	std::vector<Rva001AEA80GeometryShape> m_shapes;
	std::vector<Rva001AEA80GeometryRecord> m_records;
	Int m_cached44;
	Int m_cached48;
	Real m_cached4c;
	Int m_cached50;
	Int m_cached54;
	Int m_cached58;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

class Rva001AEA80ThingTemplateView {
public:
 void *m_vptr;
 Rva001AEA80ThingTemplateView *m_nextOverride;
 UnsignedInt m_pad08[0xC8 / sizeof(UnsignedInt)-2];
 KindOfMaskType m_kindof;
 Bool isKindOf(KindOfType kind)const {return m_kindof.test(kind);}
};

class Object
{
public:
	Relationship getRelationship(const Object *) const;

	const Rva001AEA80ThingTemplateView *getTemplate() const
	{
		const Rva001AEA80ThingTemplateView *tmpl =
			*(const Rva001AEA80ThingTemplateView * const *)
			((const char *)this + 4);
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = (const Rva001AEA80ThingTemplateView *)
				((const Overridable *)tmpl->m_nextOverride)->getFinalOverride();
		return tmpl;
	}

 Bool isKindOf(KindOfType kind)const {return getTemplate()->isKindOf(kind);}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

struct FindPositionOptions
{
	UnsignedInt flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

class PartitionManager;

class Pathfinder
{
public:
	Int bfmeCellTypeFiveOrOutside(const Coord3D *, PathfindLayerEnum);
	Bool slowDoesPathExist(Object *, const Coord3D *, const Coord3D *, ObjectID);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;

	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}
};

extern AI *TheAI;

class TerrainLogic
{
public:
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *,
		Bool onlyHealthyBridges = FALSE);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real, Real, Coord3D * = 0);
	virtual Real getLayerHeight(Real, Real, PathfindLayerEnum,
		Coord3D * = 0, Bool = TRUE);
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual Bool isUnderwater(Real, Real, Real * = 0, Real * = 0);
	virtual Bool isCliffCell(Real, Real);
};

extern TerrainLogic *TheTerrainLogic;

struct BfmeWideResultEntry
{
	Object *object;
	UnsignedInt unused;
};

struct BfmeWideResultData
{
	std::vector<BfmeWideResultEntry> entries;
	BfmeWideResultEntry *current;
	Int references;
};

struct BfmeWideResult
{
	BfmeWideResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);

	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Bool next(Object *&object)
	{
		if (value->current == value->entries.end())
			return FALSE;
		object = (value->current++)->object;
		return TRUE;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern PartitionManager *ThePartitionManager;

struct VptrZeroMixedBlock12
{
	UnsignedInt m_dword_00;
	UnsignedInt m_dword_04;
	UnsignedInt m_dword_08;
};

extern const unsigned char g_FilterVtable001AEA80[];

class Rva001AEA80FilterBase
{
public:
	UnsignedInt m_vptr;
	Rva001AEA80FilterBase *m_next;
};

class Rva000FBCB0VptrZeroMixedObject : public Rva001AEA80FilterBase
{
public:
	Rva000FBCB0VptrZeroMixedObject(const VptrZeroMixedBlock12 &,
		void *, void *, unsigned char);

	~Rva000FBCB0VptrZeroMixedObject()
	{
		m_vptr = (UnsignedInt)g_FilterVtable001AEA80;
	}

	operator Int()
	{
		return (Int)this;
	}

	UnsignedInt m_dword_08;
	UnsignedInt m_dword_0C;
	UnsignedInt m_dword_10;
	void *m_first;
	void *m_second;
	Bool m_flag;
};

typedef char Rva001AEA80GeometrySizeCheck[(sizeof(GeometryInfo) == 0x5c) ? 1 : -1];
typedef char Rva001AEA80FilterSizeCheck[(sizeof(Rva000FBCB0VptrZeroMixedObject) == 0x20) ? 1 : -1];
typedef char Rva001AEA80ResultSizeCheck[(sizeof(BfmeWideResult) == 4) ? 1 : -1];

Bool Rva001AEA80TryPosition(const Coord3D *center,
	Real dist,
	Real angle,
	const FindPositionOptions *options,
	Coord3D *result)
{
	Coord3D pos;
	pos.x = dist * Cos(angle) + center->x;
	pos.y = dist * Sin(angle) + center->y;

	PathfindLayerEnum layer = LAYER_GROUND;
	if ((options->flags & FPF_USE_HIGHEST_LAYER) != 0)
	{
		pos.z = 99999.0f;
		layer = TheTerrainLogic->getHighestLayerForDestination(&pos);
		pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer);
		if (layer != LAYER_GROUND)
			pos.z += 1.0f;
	}
	else
	{
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
	}

	if (fabs(pos.z - center->z) > options->maxZDelta)
		return FALSE;

	if (TheTerrainLogic->isCliffCell(pos.x, pos.y) && layer == LAYER_GROUND)
		return FALSE;

	if ((unsigned char)TheAI->pathfinder()->bfmeCellTypeFiveOrOutside(&pos, layer))
		return FALSE;

	if (BitTest(options->flags, FPF_IGNORE_WATER) == FALSE)
	{
		Bool isUnderwater = TheTerrainLogic->isUnderwater(pos.x, pos.y);
		if (BitTest(options->flags, FPF_WATER_ONLY) &&
			(isUnderwater == FALSE || layer != LAYER_GROUND))
			return FALSE;
		else if (isUnderwater == TRUE && layer == LAYER_GROUND)
			return FALSE;
	}

	if (BitTest(options->flags, FPF_IGNORE_ALL_OBJECTS) == FALSE)
	{
		BfmeWideResult iterator =
			((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
				(Int)&pos, 0x40B00000, 1,
				(Int)Rva000FBCB0VptrZeroMixedObject(
					*(const VptrZeroMixedBlock12 *)&pos,
					GeometryInfo(GEOMETRY_SPHERE, TRUE, 5.0f, 5.0f, 5.0f),
					*(void **)&angle, TRUE),
				0);

		Object *them;
		while (iterator.next(them))
		{
			if (them == 0)
				break;
			if (them == options->ignoreObject)
				continue;

            if(options->relationshipObject) {
                if(BitTest(options->flags,FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS) &&
                   options->relationshipObject->getRelationship(them)!=ENEMIES &&
                   (them->isKindOf(KINDOF_INFANTRY) || them->isKindOf(KINDOF_VEHICLE))) continue;
                if(BitTest(options->flags,FPF_IGNORE_ALLY_OR_NEUTRAL_STRUCTURES) &&
                   options->relationshipObject->getRelationship(them)!=ENEMIES &&
                   them->isKindOf(KINDOF_STRUCTURE)) continue;
                if(BitTest(options->flags,FPF_IGNORE_ENEMY_UNITS) &&
                   options->relationshipObject->getRelationship(them)==ENEMIES &&
                   (them->isKindOf(KINDOF_INFANTRY) || them->isKindOf(KINDOF_VEHICLE))) continue;
                if(BitTest(options->flags,FPF_IGNORE_ENEMY_STRUCTURES) &&
                   options->relationshipObject->getRelationship(them)==ENEMIES &&
                   them->isKindOf(KINDOF_STRUCTURE)) continue;
            }

			if (them == options->sourceToPathToDest)
				continue;

			return FALSE;
		}
	}

	if (options->sourceToPathToDest)
	{
		
		if (!TheAI->pathfinder()->slowDoesPathExist(
				const_cast<Object *>(options->sourceToPathToDest), options->sourceToPathToDest->getPosition(), &pos, (ObjectID)0))
			return FALSE;
	}

	*result = pos;
	return TRUE;
}
