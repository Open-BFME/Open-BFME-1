// cl: /DNDEBUG /MD /EHsc
// Object::canCrushOrSquish, retail 0x001C7600 (223 bytes).
// Zero Hour twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/
// Source/GameLogic/Object/Object.cpp (Object::canCrushOrSquish). BFME drops
// the unmanned and ally tests, inlines the template crusher-level read, adds a
// path check before the squish/crush tests, and compares the levels signed.
//
// Shape note: the path predicate is a Bool assigned from `path->test()` inside
// the guard (not folded into one && chain). That spelling is what gives the
// path pointer ESI and leaves `this` in EDI, as retail has it; every && spelling
// mirrors the two registers.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;	///< ILT 0x000022BB -> 0x00087A80 (INIWater.cpp)
	void *m_vtable;								///< retail this+0x00
	const Overridable *m_nextOverride;				///< retail this+0x04
};

// Thing::m_template's final override. +0x499/+0x49a are witnessed by the
// ThingTemplate FieldParse table (reverse/field_names.csv).
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled08[0x499 - 8];
	UnsignedByte m_crusherLevel;				///< retail this+0x499
	UnsignedByte m_crushableLevel;				///< retail this+0x49a
	UnsignedByte m_altCrusherLevel49b;			///< retail this+0x49b: used instead of +0x499 when not 0xff and Object+0x128 bit 0x800 is set
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool slowDoesPathExist(class Object *source, const Coord3D *sourcePosition,
		const Coord3D *targetPosition, ObjectID objectID);	///< ILT 0x0004A327
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }
	unsigned char m_unmodelled00[0x0c];
	Pathfinder *m_pathfinder;					///< retail this+0x0c
};

extern AI *TheAI;								///< ?TheAI@@3PAVAI@@A 0x012EF214

// Matched at 0x001B3FE0 in Code/GameEngine/Source/Common/Bfme/Rva001B3FE0Predicate.cpp.
class Rva001B3FE0
{
public:
	Bool test() const;							///< ILT 0x00006DCF -> 0x001B3FE0
};

class AIUpdateInterface
{
public:
	Bool bfmeBlocksFormationRefresh();			///< ILT 0x00044774 -> 0x00278830
	unsigned char m_unmodelled00[0x140];
	Rva001B3FE0 *m_path;						///< retail this+0x140 (layout witness names m_path)
};

class Object
{
public:
	Bool canCrushOrSquish(Object *otherObj, CrushSquishTestType testType) const;
	UnsignedByte getCrushableLevel() const;		///< ILT 0x00019B23 -> 0x001C74E0

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}

	unsigned char m_unmodelled00[4];
	const ThingTemplate *m_template;			///< retail this+0x04 -- Thing::m_template, an override chain head
	unsigned char m_unmodelled08[0x128 - 8];
	UnsignedInt m_flags128;						///< retail this+0x128: bit 0x800 selects ThingTemplate+0x49b
	unsigned char m_unmodelled12c[0x1f4 - 0x12c];
	Bool m_squishable1f4;						///< retail this+0x1f4: stands where the ZH twin tests for a SquishCollide module
	unsigned char m_unmodelled1f5[0x204 - 0x1f5];
	AIUpdateInterface *m_ai;					///< retail this+0x204
};

// ?canCrushOrSquish@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z
Bool Object::canCrushOrSquish(Object *otherObj, CrushSquishTestType testType) const
{
	if (!otherObj)
		return false;

	UnsignedByte crusherLevel;
	{
		const ThingTemplate *d = m_template;
		const ThingTemplate *f;
		if (d == 0)
			f = d;
		else
		{
			f = reinterpret_cast<const ThingTemplate *>(d->m_nextOverride
				? d->m_nextOverride->getFinalOverride()
				: d);
		}
		UnsignedByte altLevel = f->m_altCrusherLevel49b;
		if (altLevel != 0xff && (m_flags128 & 0x800) != 0)
			crusherLevel = altLevel;
		else
			crusherLevel = f->m_crusherLevel;
	}

	if (!crusherLevel)
		return false;

	if ((signed char)otherObj->getCrushableLevel() >= (signed char)crusherLevel)
		return false;

	AIUpdateInterface *ai = m_ai;
	Bool pathOk = false;
	if (ai)
	{
		Rva001B3FE0 *path = ai->m_path;
		if (ai->bfmeBlocksFormationRefresh() && path)
			pathOk = path->test();
	}
	if (!pathOk)
		pathOk = TheAI->pathfinder()->slowDoesPathExist(
			const_cast<Object *>(this), getPosition(), otherObj->getPosition(), OBJECT_ID_NONE);
	if (!pathOk)
		return false;

	if (testType == TEST_SQUISH_ONLY || testType == TEST_CRUSH_OR_SQUISH)
	{
		if (otherObj->m_squishable1f4)
			return true;
	}

	if (testType == TEST_CRUSH_ONLY || testType == TEST_CRUSH_OR_SQUISH)
	{
		if ((signed char)crusherLevel > (signed char)otherObj->getCrushableLevel())
			return true;
	}

	return false;
}
