// ?d_0087f590@@YAXXZ
// partial score=0.84 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// GeometryInfo::getBestContactPoint, retail 0x0087F590 (1066 bytes).
//
// Identity: the retail trace literal names the method and the member
// ("GeometryInfo::getBestContactPoint, callerPos=... m_innermostContactPoint=")
// and the matched Object::getWorldspaceBestContactPoint calls it on its
// GeometryInfo with this six-argument signature (ret 0x18).
//
// Layout (BFME's 0x5C-byte GeometryInfo): the 0x24-byte shape vector at +0x2C
// (GeometryInfoRva0087E650.cpp), a vector of 0x10-byte labelled points at
// +0x38, a point at +0x44 and m_innermostContactPoint at +0x50. Names that no
// evidence proves keep their offset.

#include <vector>
#include "AsciiString.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

#ifndef NULL
#define NULL 0
#endif

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	Real x, y, z;

	Coord3D() {}
	Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }

	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}

	void scale(Real s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
};

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

extern unsigned char g_contactPointDebug;
extern void *g_contactPointDebugSink;
extern "C" int __cdecl fprintf(void *sink, const char *format, ...);

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
				Coord3D first = m_rva38Points[index].m_pos;
				Coord3D second = m_rva38Points[index + 1].m_pos;
				Real t = ((seed >> 8) & 0xff) * (1.0f / 255.0f);
				first.scale(t);
				second.scale(1.0f - t);
				first.add(&second);
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
				return true;
			}
			if (pointOut->z < getMaxHeightAbovePosition() * 0.1f)
				pointOut->z = getMaxHeightAbovePosition() * 0.1f;
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
				return true;
			}
			if (pointOut->z < getMaxHeightAbovePosition() * 0.1f)
				pointOut->z = getMaxHeightAbovePosition() * 0.1f;
			return true;
		}
	}

	return false;
}
