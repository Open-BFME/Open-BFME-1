// ?computeScatter@Rva001E7C30Host@@QAEPAUCoord3D@@PAU2@PBVObject@@1U2@@Z
// partial score=0.51 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x001E7C30: opaque scatter-position helper with a Coord3D value argument.

#include <math.h>
#include "wwmath.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum KindOfType
{
	KINDOF_8 = 8
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
};

struct Rva001E7C30TemplateView
{
    char m_gap00[4];
    const Overridable *m_nextOverride;
    char m_gap08[0xc8 - 8];
    signed char m_kind;
    char m_gapc9[3];
    unsigned int m_flags;
};

class Rva001E7C30AIView
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10c() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11c() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12c() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13c() = 0;
	virtual void slot140() = 0;
	virtual void slot144() = 0;
	virtual void slot148() = 0;
	virtual void slot14c() = 0;
	virtual void slot150() = 0;
	virtual void slot154() = 0;
	virtual void slot158() = 0;
	virtual void slot15c() = 0;
	virtual void slot160() = 0;
	virtual void slot164() = 0;
	virtual void slot168() = 0;
	virtual void slot16c() = 0;
	virtual void slot170() = 0;
	virtual void slot174() = 0;
	virtual void slot178() = 0;
	virtual void slot17c() = 0;
	virtual void slot180() = 0;
	virtual void slot184() = 0;
	virtual void slot188() = 0;
	virtual void slot18c() = 0;
	virtual void slot190() = 0;
	virtual void slot194() = 0;
	virtual void slot198() = 0;
	virtual void slot19c() = 0;
	virtual void slot1a0() = 0;
	virtual void slot1a4() = 0;
	virtual void slot1a8() = 0;
	virtual void slot1ac() = 0;
	virtual void slot1b0() = 0;
	virtual void slot1b4() = 0;
	virtual void slot1b8() = 0;
	virtual void slot1bc() = 0;
	virtual void slot1c0() = 0;
	virtual void slot1c4() = 0;
	virtual void slot1c8() = 0;
	virtual void slot1cc() = 0;
	virtual void slot1d0() = 0;
	virtual void slot1d4() = 0;
	virtual void slot1d8() = 0;
	virtual void slot1dc() = 0;
	virtual void slot1e0() = 0;
	virtual void slot1e4() = 0;
	virtual void slot1e8() = 0;
	virtual Bool querySlot1ec() const = 0;
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const = 0;

	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	char m_gap00[4];
	Rva001E7C30TemplateView *m_template;
	char m_gap08[0x38 - 8];
	Coord3D m_position;
	char m_gap44[0xbc - 0x44];
	Real m_fieldbc;
	char m_gapc0[0x204 - 0xc0];
	Rva001E7C30AIView *m_ai;

	Int getLayer() const;
};

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *out, const Object *source,
		const Object *victim, Int flags);
};

extern const Real BfmeZeroRange;
extern const Real g_bfmeK1266C;
extern const Real g_bfmeDefaultEG;
extern char g_bfmeFmt1041[];
extern TerrainLogic *TheTerrainLogic;
extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file,
	Int line);
extern Real Cos(Real radians);
extern Real Sin(Real radians);
extern "C" double __cdecl atan2(double y, double x);

#pragma intrinsic(atan2)

class Rva001E7C30Host
{
public:
	Coord3D *computeScatter(Coord3D *out, const Object *source,
		const Object *victim, Coord3D position);

	char m_gap00[0x28];
	Real m_scatterRadius;
	char m_gap2c[0x514 - 0x2c];
	Real m_infantryInaccuracyDist;
};

Coord3D *Rva001E7C30Host::computeScatter(Coord3D *out,
    const Object *source, const Object *victim, Coord3D position)
{
    Coord3D temporary;
    Real minimumRadius;
    if (victim)
    {
        minimumRadius = victim->m_fieldbc;
        minimumRadius += g_bfmeK1266C;
    }
    else
        minimumRadius = 0.0f;

    Real scatterRadius = m_scatterRadius;
    PathfindLayerEnum targetLayer;
    if (victim)
    {
        const Rva001E7C30TemplateView *templateValue = victim->m_template;
        if (templateValue && templateValue->m_nextOverride)
            templateValue = reinterpret_cast<const Rva001E7C30TemplateView *>(templateValue->m_nextOverride->getFinalOverride());
        if ((templateValue->m_kind & 0x80) != 0)
            position = *reinterpret_cast<WeaponTemplate *>(this)->getAimPosition(&temporary, source, victim, 1);
        if (m_infantryInaccuracyDist > BfmeZeroRange && victim->isKindOf(KINDOF_8))
            scatterRadius += m_infantryInaccuracyDist;
        targetLayer = (PathfindLayerEnum)victim->getLayer();
    }
    else
        targetLayer = TheTerrainLogic->getLayerForDestination(0, &position);

    Real distance = minimumRadius < scatterRadius ? GetGameLogicRandomValueReal(minimumRadius, scatterRadius, g_bfmeFmt1041, 1468) : scatterRadius;

    Real angle;
    if (victim)
    {
        temporary.x = source->m_position.x - victim->m_position.x;
        temporary.y = source->m_position.y - victim->m_position.y;
        Real distanceSquared = temporary.y * temporary.y + temporary.x * temporary.x;
        if (distanceSquared != BfmeZeroRange)
        {
            Real inverseLength = WWMath::Inv_Sqrt(distanceSquared);
            temporary.x *= inverseLength;
            temporary.y *= inverseLength;
        }
        Real baseAngle = (Real)atan2(temporary.y, temporary.x);
        angle = GetGameLogicRandomValueReal(baseAngle - g_bfmeDefaultEG, baseAngle + g_bfmeDefaultEG, g_bfmeFmt1041, 1482);
    }
    else
        angle = GetGameLogicRandomValueReal(0.0f, 6.28318530717958647692f, g_bfmeFmt1041, 1486);

    temporary.x = distance * Cos(angle);
    temporary.y = distance * Sin(angle);
    position.x += temporary.x;
    position.y += temporary.y;
    if (victim)
    {
        const Rva001E7C30TemplateView *templateValue = victim->m_template;
        if (templateValue && templateValue->m_nextOverride)
            templateValue = reinterpret_cast<const Rva001E7C30TemplateView *>(templateValue->m_nextOverride->getFinalOverride());
        if ((templateValue->m_flags & 0x400000) != 0)
            position.z = victim->m_position.z;
        else
        {
            Rva001E7C30AIView *ai = victim->m_ai;
            if (ai && ai->querySlot1ec())
                position.z = TheTerrainLogic->getLayerHeight(position.x, position.y, targetLayer, 0, true);
        }
    }
    *out = position;
    return out;
}
