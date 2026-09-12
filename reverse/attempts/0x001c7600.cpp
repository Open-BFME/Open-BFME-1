// ?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z
// partial score=0.92 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// readable body of ?canCrushOrSquish@Object@@: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// Open-BFME5: clean C++ de-lift of the __emit MASM thunk.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CrushSquishTestType
{
	TEST_CRUSH_ONLY,
	TEST_SQUISH_ONLY,
	TEST_CRUSH_OR_SQUISH
};

enum ObjectID
{
	OBJECT_ID_NONE = 0
};

// Declared, never defined here: the body is matched at 0x00487A80 from
// Code/GameEngine/Source/Common/INI/INIWater.cpp.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;	///< pinned ILT 0x000022BB -> 0x00487A80
	void *m_vtable;								///< retail this+0x00
	const Overridable *m_nextOverride;				///< retail this+0x04
};

// BFME's ThingTemplate carries the crush/squish levels at +0x499..+0x49c on
// the final override object: a base pair and a mounted pair, selected by a
// mounted-condition bit on the Object itself.
class BfmeCrushLevels : public Overridable
{
public:
	unsigned char m_unreconstructed_08[0x499 - 8];
	UnsignedByte m_crusherLevel;			///< retail this+0x499
	UnsignedByte m_crushableLevel;			///< retail this+0x49a (unused here)
	UnsignedByte m_mountedCrusherLevel;		///< retail this+0x49b
	UnsignedByte m_mountedCrushableLevel;		///< retail this+0x49c (unused here)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool slowDoesPathExist(class Object *source, const Coord3D *sourcePosition,
		const Coord3D *targetPosition, ObjectID objectID);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }
	unsigned char m_unreconstructed_00[0x0c];
	Pathfinder *m_pathfinder;				///< retail this+0x0c
};

extern AI *TheAI;								///< ?TheAI@@3PAVAI@@A

// Address-derived: a predicate object hung off AIUpdateInterface::m_owner and
// tested when a formation-refresh guard passes; matched at 0x001B3FE0 from
// Code/GameEngine/Source/Common/Bfme/Rva001B3FE0Predicate.cpp.
class Rva001B3FE0
{
public:
	Bool test() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Bool bfmeBlocksFormationRefresh();		///< pinned ILT 0x00044774 -> 0x00278830
	unsigned char m_unreconstructed_00[0x140];
	Rva001B3FE0 *m_owner;					///< retail this+0x140
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool canCrushOrSquish(Object *otherObj, CrushSquishTestType testType) const;
	UnsignedByte getCrushableLevel() const;	///< pinned ILT 0x00019B23 -> 0x001C74E0 (route)

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}

	unsigned char m_unreconstructed_00[4];
	const BfmeCrushLevels *m_template;			///< retail this+0x04 (an Overridable chain head)
	unsigned char m_unreconstructed_08[0x128 - 8];
	UnsignedInt m_mountedCondition;				///< retail this+0x128
	unsigned char m_unreconstructed_12c[0x1f4 - 0x12c];
	Bool m_squishableFlag;						///< retail this+0x1f4: cached SquishCollide module presence
	unsigned char m_unreconstructed_1f5[0x204 - 0x1f5];
	AIUpdateInterface *m_ai;					///< retail this+0x204
};

// ?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z
Bool Object::canCrushOrSquish(Object *otherObj, CrushSquishTestType testType) const
{
	if (!otherObj)
		return false;

	UnsignedByte crusherLevel;
	{
		const BfmeCrushLevels *d = m_template;
		const BfmeCrushLevels *f;
		if (d == 0)
			f = d;
		else
		{
			f = reinterpret_cast<const BfmeCrushLevels *>(d->m_nextOverride
				? d->m_nextOverride->getFinalOverride()
				: d);
		}
		UnsignedByte mountedLevel = f->m_mountedCrusherLevel;
		if (mountedLevel != 0xff && (m_mountedCondition & 0x800) != 0)
			crusherLevel = mountedLevel;
		else
			crusherLevel = f->m_crusherLevel;
	}

	if (!crusherLevel)
		return false;

	if ((signed char)otherObj->getCrushableLevel() >= (signed char)crusherLevel)
		return false;

	Bool pathOk = false;
	AIUpdateInterface *ai = m_ai;
	if (ai)
	{
		Rva001B3FE0 *owner = ai->m_owner;
		pathOk = ai->bfmeBlocksFormationRefresh() && owner && owner->test();
	}
	if (!pathOk)
	{
		pathOk = TheAI->pathfinder()->slowDoesPathExist(
			const_cast<Object *>(this), getPosition(), otherObj->getPosition(), OBJECT_ID_NONE);
	}
	if (!pathOk)
		return false;

	if (testType == TEST_SQUISH_ONLY || testType == TEST_CRUSH_OR_SQUISH)
	{
		if (otherObj->m_squishableFlag)
			return true;
	}

	if (testType == TEST_CRUSH_ONLY || testType == TEST_CRUSH_OR_SQUISH)
	{
		if ((signed char)crusherLevel > (signed char)otherObj->getCrushableLevel())
			return true;
	}

	return false;
}
