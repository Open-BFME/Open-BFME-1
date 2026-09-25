// ?rva001e7c30@WeaponTemplate@@QAE?AUCoord3D@@PBVObject@@0U2@@Z
// WeaponTemplate owner proven by 0x001E9380 via ILT 0x00040287; field offsets are witnessed.
// The hidden Coord3D return and live x87 Y offset follow the retail ABI and instruction shape.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

#include <math.h>
#include "wwmath.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
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
	virtual void slot001() = 0;
	virtual void slot002() = 0;
	virtual void slot003() = 0;
	virtual void slot004() = 0;
	virtual void slot005() = 0;
	virtual void slot006() = 0;
	virtual void slot007() = 0;
	virtual void slot008() = 0;
	virtual void slot009() = 0;
	virtual void slot00a() = 0;
	virtual void slot00b() = 0;
	virtual void slot00c() = 0;
	virtual void slot00d() = 0;
	virtual void slot00e() = 0;
	virtual void slot00f() = 0;
	virtual void slot010() = 0;
	virtual void slot011() = 0;
	virtual void slot012() = 0;
	virtual void slot013() = 0;
	virtual void slot014() = 0;
	virtual void slot015() = 0;
	virtual void slot016() = 0;
	virtual void slot017() = 0;
	virtual void slot018() = 0;
	virtual void slot019() = 0;
	virtual void slot01a() = 0;
	virtual void slot01b() = 0;
	virtual void slot01c() = 0;
	virtual void slot01d() = 0;
	virtual void slot01e() = 0;
	virtual void slot01f() = 0;
	virtual void slot020() = 0;
	virtual void slot021() = 0;
	virtual void slot022() = 0;
	virtual void slot023() = 0;
	virtual void slot024() = 0;
	virtual void slot025() = 0;
	virtual void slot026() = 0;
	virtual void slot027() = 0;
	virtual void slot028() = 0;
	virtual void slot029() = 0;
	virtual void slot02a() = 0;
	virtual void slot02b() = 0;
	virtual void slot02c() = 0;
	virtual void slot02d() = 0;
	virtual void slot02e() = 0;
	virtual void slot02f() = 0;
	virtual void slot030() = 0;
	virtual void slot031() = 0;
	virtual void slot032() = 0;
	virtual void slot033() = 0;
	virtual void slot034() = 0;
	virtual void slot035() = 0;
	virtual void slot036() = 0;
	virtual void slot037() = 0;
	virtual void slot038() = 0;
	virtual void slot039() = 0;
	virtual void slot03a() = 0;
	virtual void slot03b() = 0;
	virtual void slot03c() = 0;
	virtual void slot03d() = 0;
	virtual void slot03e() = 0;
	virtual void slot03f() = 0;
	virtual void slot040() = 0;
	virtual void slot041() = 0;
	virtual void slot042() = 0;
	virtual void slot043() = 0;
	virtual void slot044() = 0;
	virtual void slot045() = 0;
	virtual void slot046() = 0;
	virtual void slot047() = 0;
	virtual void slot048() = 0;
	virtual void slot049() = 0;
	virtual void slot04a() = 0;
	virtual void slot04b() = 0;
	virtual void slot04c() = 0;
	virtual void slot04d() = 0;
	virtual void slot04e() = 0;
	virtual void slot04f() = 0;
	virtual void slot050() = 0;
	virtual void slot051() = 0;
	virtual void slot052() = 0;
	virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual void slot055() = 0;
	virtual void slot056() = 0;
	virtual void slot057() = 0;
	virtual void slot058() = 0;
	virtual void slot059() = 0;
	virtual void slot05a() = 0;
	virtual void slot05b() = 0;
	virtual void slot05c() = 0;
	virtual void slot05d() = 0;
	virtual void slot05e() = 0;
	virtual void slot05f() = 0;
	virtual void slot060() = 0;
	virtual void slot061() = 0;
	virtual void slot062() = 0;
	virtual void slot063() = 0;
	virtual void slot064() = 0;
	virtual void slot065() = 0;
	virtual void slot066() = 0;
	virtual void slot067() = 0;
	virtual void slot068() = 0;
	virtual void slot069() = 0;
	virtual void slot06a() = 0;
	virtual void slot06b() = 0;
	virtual void slot06c() = 0;
	virtual void slot06d() = 0;
	virtual void slot06e() = 0;
	virtual void slot06f() = 0;
	virtual void slot070() = 0;
	virtual void slot071() = 0;
	virtual void slot072() = 0;
	virtual void slot073() = 0;
	virtual void slot074() = 0;
	virtual void slot075() = 0;
	virtual void slot076() = 0;
	virtual void slot077() = 0;
	virtual void slot078() = 0;
	virtual void slot079() = 0;
	virtual void slot07a() = 0;
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
	Coord3D rva001e7c30(const Object *source, const Object *victim,
		Coord3D position);

	char m_gap00[0x28];
	Real m_scatterRadius;
	char m_gap2c[0x514 - 0x2c];
	Real m_infantryInaccuracyDist;
};

extern const Real BfmeZeroRange;
extern const Real g_bfmeDefaultEG;
extern char g_bfmeFmt1041[];
extern TerrainLogic *TheTerrainLogic;
extern Real GetGameLogicRandomValueReal(Real low, Real high, char *file,
	Int line);
extern Real Cos(Real radians);
extern Real Sin(Real radians);
extern "C" double __cdecl atan2(double y, double x);

#pragma intrinsic(atan2)

Coord3D WeaponTemplate::rva001e7c30(const Object *source,
	const Object *victim, Coord3D position)
{
	Coord3D temporary;
	Real minimumRadius;
	if (victim)
	{
		minimumRadius = victim->m_fieldbc + 5.0f;
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
			position = *getAimPosition(&temporary, source, victim, 1);
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
		Real normalizedY = temporary.y;
		if (distanceSquared != BfmeZeroRange)
		{
			Real inverseLength = WWMath::Inv_Sqrt(distanceSquared);
			temporary.x *= inverseLength;
			normalizedY = inverseLength * temporary.y;
		}
		Real baseAngle = (Real)atan2(normalizedY, temporary.x);
		angle = GetGameLogicRandomValueReal(baseAngle - g_bfmeDefaultEG, baseAngle + g_bfmeDefaultEG, g_bfmeFmt1041, 1482);
	}
	else
		angle = GetGameLogicRandomValueReal(0.0f, 6.28318530717958647692f, g_bfmeFmt1041, 1486);

	temporary.x = distance * Cos(angle);
	Real yOffset = distance * Sin(angle);
	position.x += temporary.x;
	position.y += yOffset;
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
	return position;
}

