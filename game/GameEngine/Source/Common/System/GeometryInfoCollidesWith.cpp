// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// GeometryInfo contact bodies, one retail unit (BFME 2 donor layout:
// inputs/reference/open-bfme-2 rev beed8a16,
// Code/GameEngine/Source/Common/System/GeometryInfoCollidesWith.cpp):
//   0x0087E900 shape-offset transform (132 B)
//   0x0087F0F0 BfmeObjF0::set, the placed-shape record fill (101 B)
//   0x0087F2F0 GeometryInfo::bfmeIntersects (480 B, RET 0x14)
//   0x0087F590 GeometryInfo::getBestContactPoint (1066 B, RET 0x18)
//
// BFME 1 target evidence: the two intersection-test sites in
// getBestContactPoint pass a stack coordinate by reference, and VC7.1 only
// schedules its copy like retail (all three loads before the stores) when it
// can see that bfmeIntersects keeps no pointer to it. That holds only while
// the transform and set bodies are defined in this unit too: with either one
// merely declared, bfmeIntersects keeps a six-byte reload swap at +0x1BD and
// getBestContactPoint a sixteen-byte copy schedule at +0x2EE. The four bodies
// therefore shared one translation unit in retail.
//
// The trace text names getBestContactPoint and its arguments; the
// Object::bfmeGeometryIntersects wrapper (0x001BE980) calls bfmeIntersects.
// Layout (BFME 1 retail, as in the donor): shapes +0x2C/+0x30 (0x24-byte
// records: type, height, major radius, minor radius, offset, name, enabled),
// labelled contact points +0x38/+0x3C (0x10-byte records), preferred point
// +0x44, innermost point +0x50.

#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// ------------------------------------------------------------------------
// 0x0087E900: rotate a shape's offset by the angle and add the position.

extern "C" double __cdecl sin(double angle);
extern "C" double __cdecl cos(double angle);
struct Rva0087E900Coord { float x; float y; float z; };
struct Rva0087E900Shape { char pad[0x10]; Rva0087E900Coord m_field0x10; };
void Rva0087E900(Rva0087E900Coord *out,
    const Rva0087E900Coord *position,
    const Rva0087E900Shape *shape,
    float angle)
{
    // Volatile accesses preserve retail x87 scheduling; storage itself is ordinary.
    float raw[6];
    volatile float *scratch = raw;
    float sine = (float)sin(angle);
    scratch[1] = shape->m_field0x10.y;
    scratch[2] = shape->m_field0x10.z;
    float cosine = (float)cos(angle);
    float shapeX = shape->m_field0x10.x;
    volatile float &angleRef = angle;
    angleRef = shapeX;
    float rotatedX = cosine * shapeX;
    rotatedX -= scratch[1] * sine;
    scratch[4] = position->y;
    raw[5] = position->z;
    scratch[0] = rotatedX;
    float rotatedY = angleRef * sine + scratch[1] * cosine;
    float outputX = position->x;
    outputX += scratch[0];
    scratch[3] = outputX;
    float outputY = rotatedY + scratch[4];
    float outputZ = scratch[5] + raw[2];
    out->x = scratch[3];
    out->y = outputY;
    out->z = outputZ;
}

// ------------------------------------------------------------------------
// Shape and placed-shape records.

// The shape name: retail destroys it with a direct StringBase<char>::releaseBuffer call.
extern "C" void __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ")();
extern "C" void __identifier("??0?$StringBase@D@@AAE@ABV0@@Z")();
struct BfmeShapeName
{
	void *m_data;
	~BfmeShapeName()
	{
		union
		{
			void (*raw)();
			void (BfmeShapeName::*member)();
		} release;
		release.raw = __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ");
		(this->*release.member)();
	}
};

struct BfmePosF0
{
	Real x;
	Real y;
	Real z;
};

struct BfmeShapeF0
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	BfmePosF0 m_offset;
	BfmeShapeName m_name;
	Bool m_enabled;
	unsigned char m_unmodelled021[0x03];
};

// A shape placed at a position and angle (0x34 bytes); the collision
// helpers read it.
class BfmeObjF0
{
public:
	~BfmeObjF0()
	{
	}

	BfmeObjF0 *set(const BfmePosF0 *position, const BfmeShapeF0 *shape, int angle);

	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	BfmePosF0 m_offset;
	BfmeShapeName m_name;
	Bool m_enabled;
	unsigned char m_unmodelled021[0x03];
	BfmePosF0 m_position;
	int m_angle;
};

// 0x0087F0F0: copy the shape (its name through the StringBase copy
// constructor 0x00887B60), then the position and the angle bits.
BfmeObjF0 *BfmeObjF0::set(const BfmePosF0 *pos, const BfmeShapeF0 *src, int extra)
{
	const int *v = (const int *)src;
	int *d = (int *)this;
	d[0] = v[0];
	d[1] = v[1];
	d[2] = v[2];
	d[3] = v[3];
	d[4] = v[4];
	d[5] = v[5];
	d[6] = v[6];
	union
	{
		void (*raw)();
		void (StringBase<char>::*member)(const StringBase<char> &);
	} copy;
	copy.raw = __identifier("??0?$StringBase@D@@AAE@ABV0@@Z");
	(((StringBase<char> *)&m_name)->*copy.member)(*(const StringBase<char> *)&src->m_name);
	m_enabled = src->m_enabled;
	const int *p = (const int *)pos;
	int *q = (int *)&m_position;
	q[0] = p[0];
	q[1] = p[1];
	q[2] = p[2];
	m_angle = extra;
	return this;
}

struct Rva00880D10Subject;
struct Rva00880D10Info;
struct BfmeCollisionShape;
Bool rva00880C30(Rva00880D10Info *first, Rva00880D10Info *second);			// box against box
Bool rva00880D10(Rva00880D10Subject *subject, Rva00880D10Info *info);		// round shape against box
Bool bfmeSphereOverlap(const BfmeCollisionShape *first, const BfmeCollisionShape *second);

// ------------------------------------------------------------------------

struct GeometryContactRecord
{
	Coord3D position;
	AsciiString label;
};

struct GeometryContactVector
{
	GeometryContactRecord *_M_start, *_M_finish, *_M_end_of_storage;
	const GeometryContactRecord *begin() const { return _M_start; }
	const GeometryContactRecord *end() const { return _M_finish; }
	unsigned int size() const { return (unsigned int)(end() - begin()); }
	const GeometryContactRecord &operator[](unsigned int n) const { return *(begin() + n); }
};

class GeometryInfo
{
public:
	Bool getBestContactPoint(Coord3D *out, const Coord3D *caller, const char *label,
		Int preference, Int seed, Bool ignoreCollision) const;
	Real getMaxHeightAbovePosition() const;
	Bool bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition, Real otherAngle) const;

private:
	void *m_vtbl;
	char pad04[0x28];
	BfmeShapeF0 *m_shapes;				// +0x2C
	BfmeShapeF0 *m_shapesEnd;			// +0x30
	BfmeShapeF0 *m_shapesLimit;			// +0x34
	GeometryContactVector m_contacts;	// +0x38
	Coord3D m_preferredPosition;		// +0x44
	Coord3D m_innermostContactPoint;	// +0x50
};

static __forceinline Real topExtent(const BfmeShapeF0 *shape)
{
	Real height = 0.0f;
	switch (shape->m_type)
	{
		case GEOMETRY_SPHERE:
			height = shape->m_majorRadius;
			break;
		case GEOMETRY_CYLINDER:
		case GEOMETRY_BOX:
			height = shape->m_height;
			break;
	}
	return height + shape->m_offset.z;
}

// 0x0087F2F0
Bool GeometryInfo::bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
	const GeometryInfo &otherGeometry, const Coord3D &otherPosition, Real otherAngle) const
{
	Bool result = false;
	for (const BfmeShapeF0 *thisShape = m_shapes; thisShape != m_shapesEnd; ++thisShape)
	{
		if (!thisShape->m_enabled)
			continue;
		if (result)
			break;

		BfmePosF0 thisCenter;
		Rva0087E900((Rva0087E900Coord *)&thisCenter, (const Rva0087E900Coord *)&thisPosition,
			(const Rva0087E900Shape *)thisShape, thisAngle);

		for (const BfmeShapeF0 *thatShape = otherGeometry.m_shapes;
			thatShape != otherGeometry.m_shapesEnd; ++thatShape)
		{
			if (!thatShape->m_enabled)
				continue;
			if (result)
				break;

			BfmePosF0 thatCenter;
			Rva0087E900((Rva0087E900Coord *)&thatCenter, (const Rva0087E900Coord *)&otherPosition,
				(const Rva0087E900Shape *)thatShape, otherAngle);

			// Retail compares the own top against the other position's z
			// and the own centre against the other placed top.
			if (otherPosition.z > topExtent(thisShape) + thisCenter.z)
				continue;
			if (thisCenter.z > topExtent(thatShape) + thatCenter.z)
				continue;

			BfmeObjF0 thisObject;
			BfmeObjF0 thatObject;
			thisObject.set(&thisCenter, thisShape, *(const int *)&thisAngle);
			thatObject.set(&thatCenter, thatShape, *(const int *)&otherAngle);

			switch (thisObject.m_type)
			{
				case GEOMETRY_BOX:
					if (thatObject.m_type == GEOMETRY_BOX)
						result = rva00880C30((Rva00880D10Info *)&thisObject, (Rva00880D10Info *)&thatObject);
					else
						result = rva00880D10((Rva00880D10Subject *)&thatObject, (Rva00880D10Info *)&thisObject);
					break;
				case GEOMETRY_SPHERE:
				case GEOMETRY_CYLINDER:
					if (thatObject.m_type == GEOMETRY_BOX)
						result = rva00880D10((Rva00880D10Subject *)&thisObject, (Rva00880D10Info *)&thatObject);
					else
						result = bfmeSphereOverlap((const BfmeCollisionShape *)&thisObject,
							(const BfmeCollisionShape *)&thatObject);
					break;
			}
		}
	}
	return result;
}

// ------------------------------------------------------------------------
// 0x0087F590

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool g_bfmeDockingTraceActive;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *sink, const char *format, ...);

// Every collision test runs against the static sphere geometry placed at
// the zero point 0x0130E908, which only this body references.
extern const Coord3D g_Va0130E908;
struct BfmeStaticAAO;
extern BfmeStaticAAO g_bfmeStaticAAO;

struct ContactPoint : Coord3D
{
	ContactPoint(const Coord3D &r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
	}
};

static inline void contactCopy(Coord3D &out, const Coord3D &in)
{
	out = in;
}

Bool GeometryInfo::getBestContactPoint(Coord3D *out, const Coord3D *caller, const char *label,
	Int preference, Int seed, Bool ignoreCollision) const
{
	if (g_bfmeDockingTraceActive && caller && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"        GeometryInfo::getBestContactPoint, callerPos=%g,%g,%g, label=%s, pref=%d, seed=%d, skipCollideTest=%d, m_innermostContactPoint=%g,%g,%g",
			caller->x, caller->y, caller->z, label ? label : "NONE", preference, seed,
			ignoreCollision ? "TRUE" : "FALSE",
			m_innermostContactPoint.x, m_innermostContactPoint.y, m_innermostContactPoint.z);

	contactCopy(*out, m_innermostContactPoint);

	switch (preference)
	{
		case 3:
		{
			int count = (int)m_contacts.size();
			if (count >= 2)
			{
				int index = seed % (count - 1);
				ContactPoint first = m_contacts[index].position;
				ContactPoint second = m_contacts[index + 1].position;
				float t = (float)((seed >> 8) & 255);
				t *= (1.0f / 255.0f);
				first.x *= t;
				first.y *= t;
				first.z *= t;
				float inverse = 1.0f - t;
				second.x *= inverse;
				second.y *= inverse;
				second.z *= inverse;
				first.x += second.x;
				first.y += second.y;
				first.z += second.z;
				contactCopy(*out, first);
			}
			if (out->z > getMaxHeightAbovePosition())
				out->z = getMaxHeightAbovePosition();
			if (!ignoreCollision &&
				!bfmeIntersects(g_Va0130E908, 0.0f, *(const GeometryInfo *)&g_bfmeStaticAAO, *out, 0.0f))
			{
				for (BfmeShapeF0 *shape = m_shapes; shape != m_shapesEnd; ++shape)
				{
					if (!shape->m_enabled)
						continue;
					out->x = shape->m_offset.x;
					out->y = shape->m_offset.y;
					break;
				}
			}
			if (out->z > getMaxHeightAbovePosition())
				out->z = getMaxHeightAbovePosition();
			else if (out->z < getMaxHeightAbovePosition() * 0.1f)
				out->z = getMaxHeightAbovePosition() * 0.1f;
			return true;
		}

		case 1:
			contactCopy(*out, m_preferredPosition);
			if (out->z > getMaxHeightAbovePosition())
				out->z = getMaxHeightAbovePosition();
			return true;

		case 0:
		{
			if (caller)
			{
				int count = (int)m_contacts.size();
				int best = count;
				float bestDistance = 3.402823466e+38f;
				for (int i = 0; i < count; ++i)
				{
					// One label reference and record per arm, as retail.
					const GeometryContactRecord *record;
					if (label)
					{
						const AsciiString &name = m_contacts[i].label;
						record = &m_contacts[i];
						if (name.compare(label) != 0)
							continue;
					}
					else
					{
						const AsciiString &name = m_contacts[i].label;
						record = &m_contacts[i];
						if (name.compare("") != 0)
							continue;
					}
					Coord3D pos = record->position;
					if (pos.z > getMaxHeightAbovePosition())
						pos.z = getMaxHeightAbovePosition();
					if (!ignoreCollision &&
						!bfmeIntersects(g_Va0130E908, 0.0f, *(const GeometryInfo *)&g_bfmeStaticAAO, pos, 0.0f))
						continue;
					float dx = pos.x - caller->x;
					float dy = pos.y - caller->y;
					float dz = pos.z - caller->z;
					float d = dz * dz + (dx * dx + dy * dy);
					if (d < bestDistance)
					{
						bestDistance = d;
						best = i;
					}
				}
				if (best != count)
				{
					contactCopy(*out, m_contacts[best].position);
					if (out->z > getMaxHeightAbovePosition())
						out->z = getMaxHeightAbovePosition();
					else if (out->z < getMaxHeightAbovePosition() * 0.1f)
						out->z = getMaxHeightAbovePosition() * 0.1f;
					return true;
				}
			}
			break;
		}

		default:
			break;
	}
	return false;
}
