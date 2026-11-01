// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport
//
// BezierProjectileBehavior retail 0x001EFB20, 356 bytes (ret 4 at +0x161).
// The only caller, the matched secondary-interface slot rva001F1CE0, calls it
// on the module with the hit object before projectileFire.  It walks the
// owner in tenths of the way toward the previous flight-path point (12-byte
// path vector at +0x44, step index at +0x70) up to 13 times while the two
// geometries still intersect, then backs off one step and sets the position.
// The semantic name is unproven, so the method keeps the address-derived name
// the caller already declares.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

class GeometryInfo
{
public:
	Bool bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition,
		Real otherAngle) const;
};

class Object
{
public:
	void setPosition(const Coord3D *pos);
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }

private:
	char m_unreconstructed00[0x38];
	Coord3D m_position;
	Real m_orientation;
	char m_unreconstructed48[0xac - 0x48];
	GeometryInfo m_geometryInfo;
};

class BezierProjectileBehavior
{
public:
	void rva001EFB20(Object *victim);

	Object *getObject() const { return m_object; }

private:
	char m_unreconstructed00[8];
	Object *m_object;
	char m_unreconstructed0c[0x44 - 0x0c];
	_STL::vector<Coord3D> m_path;
	char m_unreconstructed50[0x70 - 0x50];
	UnsignedInt m_pathIndex;
};

// ?rva001EFB20@BezierProjectileBehavior@@QAEXPAVObject@@@Z
void BezierProjectileBehavior::rva001EFB20(Object *victim)
{
	if (!victim)
		return;

	Int index = MIN(m_path.size() - 1, m_pathIndex);
	Object *me = getObject();
	Coord3D pos;
	pos.x = me->getPosition()->x;
	pos.y = me->getPosition()->y;
	pos.z = me->getPosition()->z;
	index = MAX(0, index - 1);

	const Coord3D &target = m_path[index];
	Coord3D delta;
	delta.x = target.x;
	delta.y = target.y;
	delta.z = target.z;
	delta.x -= pos.x;
	delta.y -= pos.y;
	delta.z -= pos.z;
	delta.x *= 0.1f;
	delta.y *= 0.1f;
	delta.z *= 0.1f;

	Real angle = me->getOrientation();
	const GeometryInfo &geom = me->getGeometryInfo();
	Int i = 0;
	do
	{
		if (i++ > 12)
			break;
		pos.x += delta.x;
		pos.y += delta.y;
		pos.z += delta.z;
	} while (geom.bfmeIntersects(pos, angle, victim->getGeometryInfo(),
			*victim->getPosition(), victim->getOrientation()));

	pos.x -= delta.x;
	pos.y -= delta.y;
	pos.z -= delta.z;
	me->setPosition(&pos);
}
