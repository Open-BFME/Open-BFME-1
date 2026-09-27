// ?getHealthBoxDimensions@Object@@QBE_NAAM0@Z
// cl: /DNDEBUG /MD /EHsc
// The matched Drawable::drawIconUI caller reaches this method through ILT 0x00042AFF.
//
// The previous 166-byte row began 0x44 bytes into this method. Retail
// returns at RVA 0x001C9F07, ending the corrected 234-byte extent.

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

// Address-derived layout view for the object reached from the +0x04 field.
class BfmeObjectView_001c9e20 : public Overridable
{
public:
	unsigned char m_unreconstructed_08[0xcc - 8];
	unsigned int m_unreconstructed_0cc;					///< retail this+0xcc
	unsigned char m_unreconstructed_d0[0x410 - 0xd0];
	Real m_unreconstructed_410;					///< retail this+0x410
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool getHealthBoxDimensions(Real &healthBoxHeight, Real &healthBoxWidth) const;

	unsigned char m_unreconstructed_00[4];
	const BfmeObjectView_001c9e20 *m_unreconstructed_004;	///< retail this+0x04
	unsigned char m_unreconstructed_08[0xbc - 8];
	Real m_unreconstructed_0bc;								///< retail this+0xbc
};

// Every use site walks the override chain independently (mirrors the retail
// call pattern: three separate one-inlined-level expansions, not one shared
// local), so this stays a small helper called at each site rather than a
// cached variable.
static const BfmeObjectView_001c9e20 *bfmeFinalOverrideView_001c9e20(const Object *obj)
{
	const BfmeObjectView_001c9e20 *d = obj->m_unreconstructed_004;
	if (d == 0)
		return d;
	return reinterpret_cast<const BfmeObjectView_001c9e20 *>(d->m_nextOverride
		? d->m_nextOverride->getFinalOverride()
		: d);
}

// ?getHealthBoxDimensions@Object@@QBE_NAAM0@Z
Bool Object::getHealthBoxDimensions(Real &healthBoxHeight, Real &healthBoxWidth) const
{
	if ((bfmeFinalOverrideView_001c9e20(this)->m_unreconstructed_0cc & 0x8000) != 0)
	{
		healthBoxHeight = 0;
		healthBoxWidth = 0;
		return false;
	}

	Real baseValue;
	if (!bfmeFinalOverrideView_001c9e20(this))
		baseValue = 1.5f;
	else
		baseValue = bfmeFinalOverrideView_001c9e20(this)->m_unreconstructed_410;

	Real size = MAX(20.0f, MIN(150.0f, baseValue * m_unreconstructed_0bc));

	healthBoxHeight = 3.0f;
	healthBoxWidth = MAX(20.0f, size * 2.0f);
	return true;
}
