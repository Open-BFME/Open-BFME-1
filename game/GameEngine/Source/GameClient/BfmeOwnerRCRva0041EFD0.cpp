// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva0041EFD0@BfmeOwnerRC@@QAEDPAX0@Z
//
// Rva0041EFD0 follows the owner's +0xfc pointer to the unit.
// It reads the unit's +0x204 state pointer and the state's +0x1cc holder.
// When the override kind at +0x70 is 1, it forwards both input arguments and
// the two coordinate accessors to BfmeOwnerRC::bfmeSendRC.
// Drawable::calcPhysicsXform at 0x004213F0 reads the same pointer chain.
//
// Retail keeps the +0x204 call inside the null ternary, preserving the xor
// eax,eax null arm. The nullable kind accessor and one-level override walk
// produce retail's assignment: this=EDI, holder=EBX, first result=ESI.
#define THING_TU_MEMBERS const Coord3D *getUnitDirectionVector2D() const;
#include "../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

#define OBJECT_TU_MEMBERS Int getLayer() const;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

// Thing and rope callers use Coord3D struct symbols, so this TU keeps the struct form.
struct Coord3DBase { Coord3DBase &operator=(const Coord3DBase &that); float x, y, z; };
struct Coord2DBase { Coord2DBase &operator=(const Coord2DBase &that); float x, y; };
struct Coord3D : Coord3DBase { Coord3D(); ~Coord3D(); };

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
#include <math.h>

class Overridable
{
public:
	void *m_rva00;
	const Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class BfmeThingRC
{
public:
	BfmeThingRC *getFinalRC()
	{
		if (m_bfmeInnerRC)
			return (BfmeThingRC *)m_bfmeInnerRC->getFinalOverride();
		return this;
	}

	unsigned char m_bfmeHeadRC[4];
	Overridable *m_bfmeInnerRC;
	unsigned char m_bfmeGapRC[0x68];
	int m_bfmeKindRC;
};

class BfmeHolderRC
{
public:
	BfmeThingRC *getThingRC() const
	{
		if (!m_bfmeThingRC)
			return 0;
		return m_bfmeThingRC->getFinalRC();
	}

	int m_bfmeSpareRC;
	BfmeThingRC *m_bfmeThingRC;
};

class BfmeStateRC
{
public:
	unsigned char m_bfmeHeadRC[0x1cc];
	BfmeHolderRC *m_bfmeHolderRC;
};

class BfmeUnitRC
{
public:
	BfmeStateRC *getStateRC() const { return m_bfmeStateRC; }

	unsigned char m_bfmeHeadRC[0x204];
	BfmeStateRC *m_bfmeStateRC;
};

class BfmeOwnerRC
{
public:
	char Rva0041EFD0(void *first, void *second);
	char bfmeSendRC(BfmeUnitRC *unit, BfmeHolderRC *holder, void *posArg, void *dirArg,
		void *pitchArg, void *rollArg);

	unsigned char m_bfmeHeadRC[0xfc];
	BfmeUnitRC *m_bfmeUnitRC;
};

char BfmeOwnerRC::Rva0041EFD0(void *first, void *second)
{
	BfmeUnitRC *unit = m_bfmeUnitRC;
	BfmeStateRC *state = unit ? unit->getStateRC() : 0;

	if (state)
	{
		BfmeHolderRC *holder = state->m_bfmeHolderRC;

		if (holder)
		{
			if (holder->getThingRC()->m_bfmeKindRC == 1)
			{
				const Coord3D *a = ((const BFMERopeDrawable *)this)->getPosition();
				const Coord3D *b = ((const Thing *)this)->getUnitDirectionVector2D();

				return this->bfmeSendRC(unit, holder, (void *)a, (void *)b, first, second);
			}
		}
	}

	return 0;
}

class BfmeGeometryInfo
{
public:
	float boxMajorRadius() const;
	float boxMinorRadius() const;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad08[0xE9 - 8];
	bool m_fieldE9;
};

class Locomotor
{
public:
	void *m_rva00;
	const LocomotorTemplate *m_template;

	const LocomotorTemplate *getTemplate() const
	{
		const LocomotorTemplate *p = m_template;
		if (p && p->m_nextOverride)
			p = (const LocomotorTemplate *)p->m_nextOverride->getFinalOverride();
		return p;
	}
};

class Rva00413A40TerrainHeightView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3DBase *normal, bool clip);
};

static __forceinline float Rva00413A40Scale(float component, double radius)
{
	return radius * component * 0.5;
}

float ASin(float);

// ILT 0x00036EA3 and callers in Drawable::calcPhysicsXformWheels and Rva0041EFD0 identify this method.
char BfmeOwnerRC::bfmeSendRC(BfmeUnitRC *unit, BfmeHolderRC *holder,
	void *posArg, void *dirArg, void *pitchArg, void *rollArg)
{
	const Object *obj = (const Object *)unit;
	const Locomotor *locomotor = (const Locomotor *)holder;
	const Coord3DBase *pos = (const Coord3DBase *)posArg;
	const Coord3DBase *dir = (const Coord3DBase *)dirArg;
	float *pitch = (float *)pitchArg;
	float *roll = (float *)rollArg;

	Coord3DBase sample;
	Coord3DBase perp;
	perp.x = -dir->y;
	perp.y = dir->x;
	perp.z = 0.0f;

	if (locomotor->getTemplate()->m_fieldE9)
	{
		const BfmeGeometryInfo *geom = (const BfmeGeometryInfo *)obj->m_geometryInfo;
		float major = geom->boxMajorRadius();
		float minor = geom->boxMinorRadius();

		Coord3DBase forward;
		forward.x = *(const volatile float *)&dir->x * major * 0.5;
		forward.y = dir->y * major * 0.5;
		Coord2DBase side;
		side.x = Rva00413A40Scale(perp.x, minor);
		side.y = Rva00413A40Scale(perp.y, minor);

		Coord3D corners[4];
		corners[0].x = pos->x - forward.x + side.x;
		corners[0].y = pos->y - forward.y + side.y;
		corners[0].z = pos->z;
		corners[1].x = pos->x - forward.x - side.x;
		corners[1].y = pos->y - forward.y - side.y;
		corners[1].z = pos->z;
		corners[2].x = pos->x + forward.x + side.x;
		corners[2].y = pos->y + forward.y + side.y;
		corners[2].z = pos->z;

		float *heights = &sample.x;
		for (int i = 0; i < 3; ++i)
			heights[i] = ((Rva00413A40TerrainHeightView *)TheTerrainLogic)->getLayerHeight(
				corners[i].x, corners[i].y, obj->getLayer(), 0, true);

		Coord3DBase edge1;
		edge1.x = corners[1].x - corners[0].x;
		edge1.y = corners[1].y - corners[0].y;
		edge1.z = heights[1] - heights[0];
		Coord3DBase edge2;
		edge2.x = corners[2].x - corners[0].x;
		edge2.y = corners[2].y - corners[0].y;
		edge2.z = heights[2] - heights[0];

		Coord3DBase normal;
		normal.x = edge1.y * edge2.z - edge1.z * edge2.y;
		normal.y = edge1.z * edge2.x - edge1.x * edge2.z;
		normal.z = edge1.x * edge2.y - edge1.y * edge2.x;

		float len = (float)sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		if (len != 0.0f)
		{
			float inv = 1.0f / len;
			normal.x *= inv;
			normal.y *= inv;
			normal.z *= inv;
		}

		float pitchSine = *(const volatile float *)&normal.x * dir->x + normal.y * dir->y + normal.z * dir->z;
		*pitch = ASin(pitchSine);
		float rollSine = normal.x * perp.x + normal.y * perp.y + normal.z * perp.z;
		*roll = ASin(rollSine);
		return true;
	}

	sample.x = 0.0f;
	sample.y = 0.0f;
	sample.z = 1.0f;
	((Rva00413A40TerrainHeightView *)TheTerrainLogic)->getLayerHeight(
		pos->x, pos->y, obj->getLayer(), &sample, true);
	float pitchSine = *(const volatile float *)&sample.x * dir->x + sample.y * dir->y;
	*pitch = ASin(pitchSine);
	float rollSine = sample.x * perp.x + sample.y * perp.y;
	*roll = ASin(rollSine);
	return true;
}
