// ?bfmeSendRC@BfmeOwnerRC@@QAEDPAVBfmeUnitRC@@PAVBfmeHolderRC@@PAX222@Z
// partial score=1.0 date=2026-10-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// ?bfmeSendRC@BfmeOwnerRC@@QAEDPAVBfmeUnitRC@@PAVBfmeHolderRC@@PAX222@Z, retail 0x00413A40, 922 bytes.

// Terrain tilt for the wheel suspension. Drawable::calcPhysicsXformWheels
// (0x00421xxx) and BfmeOwnerRC::Rva0041EFD0 call it through ILT 0x00036EA3
// with (object, locomotor, position, unit direction, &pitch, &roll); it never
// reads ECX. When the locomotor template flag at +0xE9 is set it samples the
// terrain under three corners of the object's geometry box and takes the
// plane normal; otherwise it asks the terrain for the normal under the
// position. Pitch and roll are the arcsines of the normal against the
// direction and its perpendicular.

// The corner array is a Coord3D[4], whose out-of-line constructor and
// destructor give the EH frame.

#include "coord3d.h"
#include <math.h>

class BfmeGeometryInfo
{
public:
	float boxMajorRadius(void) const;
	float boxMinorRadius(void) const;
};

class Overridable
{
public:
	void *m_vtable;
	const Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad08[0xE9 - 8];
	bool m_flagE9;
};

class Locomotor
{
public:
	void *m_vtable;
	const LocomotorTemplate *m_template;

	const LocomotorTemplate *getTemplate() const
	{
		const LocomotorTemplate *p = m_template;
		if (p && p->m_nextOverride)
			p = (const LocomotorTemplate *)p->m_nextOverride->getFinalOverride();
		return p;
	}
};

class Object
{
public:
	int getLayer() const;

	char m_pad00[0xAC];
	BfmeGeometryInfo m_geometryInfo;
};

class TerrainLogic
{
public:
	virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc();
	virtual void s10(); virtual void s14(); virtual void s18();
	virtual float getLayerHeight(float x, float y, int layer, Coord3DBase *normal, bool clip);
};
extern TerrainLogic *TheTerrainLogic;

float ASin(float);

static __forceinline float Rva00413A40Scale(float component, double radius) { return radius * component * 0.5; }
class BfmeUnitRC;
class BfmeHolderRC;

class BfmeOwnerRC
{
public:
	char bfmeSendRC(BfmeUnitRC *unit, BfmeHolderRC *holder, void *posArg, void *dirArg,
		void *pitchArg, void *rollArg);
};

char BfmeOwnerRC::bfmeSendRC(BfmeUnitRC *unit, BfmeHolderRC *holder, void *posArg, void *dirArg,
	void *pitchArg, void *rollArg)
{
	const Object *obj = (const Object *)unit;
	const Locomotor *locomotor = (const Locomotor *)holder;
	const Coord3DBase *pos = (const Coord3DBase *)posArg;
	const Coord3DBase *dir = (const Coord3DBase *)dirArg;
	float *pitch = (float *)pitchArg;
	float *roll = (float *)rollArg;

	// Heights under three box corners on the sampled path, the terrain normal
	// on the flat path: one object, which is why both sit on one retail slot.
	Coord3DBase sample;
	Coord3DBase perp;
	perp.x = -dir->y;
	perp.y = dir->x;
	perp.z = 0.0f;

	if (locomotor->getTemplate()->m_flagE9)
	{
		const BfmeGeometryInfo *geom = &obj->m_geometryInfo;
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
			heights[i] = TheTerrainLogic->getLayerHeight(corners[i].x, corners[i].y, obj->getLayer(), 0, true);

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
	TheTerrainLogic->getLayerHeight(pos->x, pos->y, obj->getLayer(), &sample, true);
	float pitchSine = *(const volatile float *)&sample.x * dir->x + sample.y * dir->y;
	*pitch = ASin(pitchSine);
	float rollSine = sample.x * perp.x + sample.y * perp.y;
	*roll = ASin(rollSine);
	return true;
}
