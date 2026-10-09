// ?getBestContactPoint@GeometryInfo@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z
// partial score=0.2936 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Evidence: targets/game/reverse/identity_evidence/0087f590-contact-point-retry.md

#include <vector>
extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier, _ReadWriteBarrier)
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

#ifndef NULL
#define NULL 0
#endif

#include "../../../../game/Libraries/Include/Lib/Coord3D.h"

// ?scale@@YAXPAUCoord3D@@M@Z absent-from-retail
static __forceinline void scale(Coord3D *point, Real s)
{
	point->x *= s; point->y *= s; point->z *= s;
}

// ?add@@YAXPAUCoord3D@@PBU1@@Z absent-from-retail
static __forceinline void add(Coord3D *point, const Coord3D *other)
{
	point->x += other->x; point->y += other->y; point->z += other->z;
}

// ?rva0087F590Set@@YAXPAUCoord3D@@PBU1@@Z absent-from-retail
static __forceinline void rva0087F590Set(Coord3D *point, const Coord3D *other)
{
	point->x = other->x; point->y = other->y; point->z = other->z;
}

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct GeometryShape
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	AsciiString m_unmodelled1C;
	Bool m_enabled;
	char m_unmodelled21[3];
};

// One labelled point of the +0x38 list.
struct Rva0087F590LabeledPoint
{
	Coord3D m_pos;
	AsciiString m_label;
};

class GeometryInfo
{
public:
	Bool getBestContactPoint(Coord3D *pointOut, const Coord3D *callerPos,
		const char *label, Int preference, Int seed, Bool skipCollideTest) const;
	Real getMaxHeightAbovePosition() const;					///< 0x0087E000
	// 0x0087F2F0
	Bool bfmeIntersects(const Coord3D &thisPos, Real thisAngle,
		const GeometryInfo &that, const Coord3D &thatPos, Real thatAngle) const;

private:
	void *m_vtbl;
	char pad04[0x28];
	std::vector<GeometryShape> m_shapes;					///< +0x2C
	std::vector<Rva0087F590LabeledPoint> m_rva38Points;	///< +0x38
	Coord3D m_rva44Point;									///< +0x44
	Coord3D m_innermostContactPoint;						///< +0x50
};

// The point geometry at the origin every collide test runs against.
extern const Coord3D g_rva0130E908Origin;
extern const GeometryInfo g_bfmeStaticAAO;

extern Bool g_contactPointDebug;
class CRCParameterCheck;
extern CRCParameterCheck *g_contactPointDebugSink;
extern "C" void __cdecl fprintf(CRCParameterCheck *sink, const char *format, ...);

// ?getBestContactPoint@GeometryInfo@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z
Bool GeometryInfo::getBestContactPoint(Coord3D *pointOut, const Coord3D *callerPos,
	const char *label, Int preference, Int seed, Bool skipCollideTest) const
{
	if (g_contactPointDebug && callerPos && g_contactPointDebugSink)
		fprintf(g_contactPointDebugSink,
			"        GeometryInfo::getBestContactPoint, callerPos=%g,%g,%g, label=%s, pref=%d, seed=%d, skipCollideTest=%d, m_innermostContactPoint=%g,%g,%g",
			callerPos->x, callerPos->y, callerPos->z, label ? label : "NONE",
			preference, seed, skipCollideTest ? "TRUE" : "FALSE",
			m_innermostContactPoint.x, m_innermostContactPoint.y, m_innermostContactPoint.z);

	*pointOut = m_innermostContactPoint;

	switch (preference)
	{
		case 3:
		{
			Int count = m_rva38Points.size();
			if (count >= 2)
			{
				Int index = seed % (count - 1);
				Coord3D first;
				rva0087F590Set(&first, &m_rva38Points[index].m_pos);
				Coord3D second;
				rva0087F590Set(&second, &m_rva38Points[index + 1].m_pos);
				Real t = ((seed >> 8) & 0xff) * (1.0f / 255.0f);
				scale(&first, t);
				scale(&second, 1.0f - t);
				add(&first, &second);
				*pointOut = first;
			}
			if (pointOut->z > getMaxHeightAbovePosition())
				pointOut->z = getMaxHeightAbovePosition();

			if (!skipCollideTest &&
				!bfmeIntersects(g_rva0130E908Origin, 0.0f, g_bfmeStaticAAO, *pointOut, 0.0f))
			{
				for (std::vector<GeometryShape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
				{
					if (it->m_enabled)
					{
						pointOut->x = it->m_offset.x;
						pointOut->y = it->m_offset.y;
						break;
					}
				}
			}

			if (pointOut->z > getMaxHeightAbovePosition())
			{
				pointOut->z = getMaxHeightAbovePosition();
				_WriteBarrier();
				_WriteBarrier();
				return true;
			}
			if (pointOut->z < getMaxHeightAbovePosition() * 0.1f)
				pointOut->z = getMaxHeightAbovePosition() * 0.1f;
			_WriteBarrier();
			return true;
		}

		case 1:
		{
			*pointOut = m_rva44Point;
			if (pointOut->z > getMaxHeightAbovePosition())
				pointOut->z = getMaxHeightAbovePosition();
			return true;
		}

		case 0:
		{
			if (callerPos == NULL)
				break;

			Int count = m_rva38Points.size();
			Int bestIndex = count;
			Real bestDistSqr = 3.402823466e+38f;
			for (Int i = 0; i < count; ++i)
			{
				if (m_rva38Points[i].m_label.compare(label ? label : "") != 0)
					continue;

				Coord3D pos = m_rva38Points[i].m_pos;
				if (pos.z > getMaxHeightAbovePosition())
					pos.z = getMaxHeightAbovePosition();

				if (!skipCollideTest &&
					!bfmeIntersects(g_rva0130E908Origin, 0.0f, g_bfmeStaticAAO, pos, 0.0f))
					continue;

				Real dx = pos.x - callerPos->x;
				Real dy = pos.y - callerPos->y;
				Real dz = pos.z - callerPos->z;
				Real distSqr = dx * dx + dy * dy + dz * dz;
				if (distSqr < bestDistSqr)
				{
					bestDistSqr = distSqr;
					bestIndex = i;
				}
			}

			if (bestIndex == count)
				break;

			*pointOut = m_rva38Points[bestIndex].m_pos;
			if (pointOut->z > getMaxHeightAbovePosition())
			{
				pointOut->z = getMaxHeightAbovePosition();
				_ReadWriteBarrier();
				_ReadWriteBarrier();
				return true;
			}
			if (pointOut->z < getMaxHeightAbovePosition() * 0.1f)
				pointOut->z = getMaxHeightAbovePosition() * 0.1f;
			_ReadWriteBarrier();
			return true;
		}
	}

	return false;
}
