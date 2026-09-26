// ?getHealthBoxDimensions@Object@@QBE_NAAM0@Z
// partial score=0.98 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ de-lift of the __emit MASM thunk.
//
// The ledger's original 166-byte extent at 0x001C9E64 is a MID-FUNCTION
// continuation, not a callable entry: its first bytes read a value already
// established by earlier code (this+4's second-level chain pointer sitting
// in ECX), which no fresh thiscall entry can supply. Ghidra independently
// sees one function spanning 0x001C9E20-0x001C9F0A (234 B, FUN_005c9e20),
// and 0x001C9E20 is reached by a real external caller (ILT ?j_00042aff@@YAXXZ
// -> ?b_001c9e20@@YAXXZ). This body lands at the true start, 0x001C9E20/234.

typedef float Real;
typedef bool Bool;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

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

// Address-derived: the same per-template override chain object body 1's
// canCrushOrSquish reads (there at +0x499..+0x49c); this body reads two more
// of its fields, a KindOf-style flag dword and a geometry-size float.
class BfmeHealthBoxTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_08[0xcc - 8];
	unsigned int m_flags2;					///< retail this+0xcc: bit 23 gates the early "ignored" return
	unsigned char m_unreconstructed_d0[0x410 - 0xd0];
	Real m_geometrySize;					///< retail this+0x410
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool getHealthBoxDimensions(Real &healthBoxHeight, Real &healthBoxWidth) const;

	unsigned char m_unreconstructed_00[4];
	const BfmeHealthBoxTemplate *m_template;	///< retail this+0x04 (an Overridable chain head)
	unsigned char m_unreconstructed_08[0xbc - 8];
	Real m_scale;								///< retail this+0xbc
};

// Every use site walks the override chain independently (mirrors the retail
// call pattern: three separate one-inlined-level expansions, not one shared
// local), so this stays a small helper called at each site rather than a
// cached variable.
static const BfmeHealthBoxTemplate *bfmeFinalHealthBoxTemplate(const Object *obj)
{
	const BfmeHealthBoxTemplate *d = obj->m_template;
	if (d == 0)
		return d;
	return reinterpret_cast<const BfmeHealthBoxTemplate *>(d->m_nextOverride
		? d->m_nextOverride->getFinalOverride()
		: d);
}

// ?getHealthBoxDimensions@Object@@QBE_NAAM0@Z
Bool Object::getHealthBoxDimensions(Real &healthBoxHeight, Real &healthBoxWidth) const
{
	if ((bfmeFinalHealthBoxTemplate(this)->m_flags2 >> 16) & 0x80)
	{
		healthBoxHeight = 0;
		healthBoxWidth = 0;
		return false;
	}

	Real baseValue;
	if (!bfmeFinalHealthBoxTemplate(this))
		baseValue = 1.5f;
	else
		baseValue = bfmeFinalHealthBoxTemplate(this)->m_geometrySize;

	Real size = MAX(20.0f, MIN(150.0f, baseValue * m_scale));

	healthBoxHeight = 3.0f;
	healthBoxWidth = MAX(20.0f, size * 2.0f);
	return true;
}
