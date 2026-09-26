// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /G6 /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: const method at retail 0x0087E370, 734 bytes; callers pass Coord3D const&, an angle and Region2D&.
// Its owner and name are not proven, so it keeps its address.

#include <vector>
#include "coord.h"
#include "ascii_string.h"

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct BfmeVecVNB
{
	Real m_bfme00;
	Real m_bfme04;
	Real m_bfme08;
};

class BfmeXformVNB
{
public:
	void bfmeApplyVNB(BfmeVecVNB *out, Real angle);

private:
	char m_bfmePad00[0x10];
	Real m_bfme10;
	Real m_bfme14;
	Real m_bfme18;
};

struct GeometryShape
{
	GeometryType m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_centerOffset;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[3];
};

typedef char GeometryShape_size_check[sizeof(GeometryShape) == 0x24 ? 1 : -1];

template <class T>
inline const T &bfmeMin(const T &a, const T &b)
{
	return (a < b) ? a : b;
}

template <class T>
inline const T &bfmeMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

class Rva0087E370
{
public:
	void method(const Coord3D &geomCenter, Real angle, Region2D &bounds) const;

private:
	char m_prefix[0x2C];
	std::vector<GeometryShape> m_shapes;
};

// ?method@Rva0087E370@@QBEXABUCoord3D@@MAAURegion2D@@@Z
void Rva0087E370::method(const Coord3D &geomCenter, Real angle, Region2D &bounds) const
{
	Real *upperX = &bounds.hi.x;
	Real *lowerY = &bounds.lo.y;
	bounds.lo.x = geomCenter.x;
	*lowerY = geomCenter.y;
	*upperX = geomCenter.x;
	upperX[1] = geomCenter.y;

	for (std::vector<GeometryShape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		if (!it->m_enabled)
			continue;

		BfmeVecVNB center;
		center.m_bfme00 = geomCenter.x;
		center.m_bfme04 = geomCenter.y;
		center.m_bfme08 = geomCenter.z;
		((BfmeXformVNB *)it)->bfmeApplyVNB(&center, angle);

		switch (it->m_type)
		{
		case GEOMETRY_SPHERE:
		case GEOMETRY_CYLINDER:
		{
			bounds.lo.x = bfmeMin(bounds.lo.x, center.m_bfme00 - it->m_majorRadius);
			*lowerY = bfmeMin(*lowerY, center.m_bfme04 - it->m_majorRadius);
			*upperX = bfmeMax(*upperX, center.m_bfme00 + it->m_majorRadius);
			bounds.hi.y = bfmeMax(bounds.hi.y, center.m_bfme04 + it->m_majorRadius);
			break;
		}

		case GEOMETRY_BOX:
		{
			Real c = (Real)cos(angle);
			Real s = (Real)sin(angle);
			Real exc = it->m_majorRadius * c;
			Real eyc = it->m_minorRadius * c;
			Real exs = it->m_majorRadius * s;
			Real eys = it->m_minorRadius * s;
			Real x, y;

			x = center.m_bfme00 - exc - eys;
			y = center.m_bfme04 + eyc - exs;
			if (bounds.lo.x > x) bounds.lo.x = x;
			if (*lowerY > y) *lowerY = y;
			if (*upperX < x) *upperX = x;
			if (bounds.hi.y < y) bounds.hi.y = y;

			x = center.m_bfme00 + exc - eys;
			y = center.m_bfme04 + eyc + exs;
			if (bounds.lo.x > x) bounds.lo.x = x;
			if (*lowerY > y) *lowerY = y;
			if (*upperX < x) *upperX = x;
			if (bounds.hi.y < y) bounds.hi.y = y;

			x = center.m_bfme00 + exc + eys;
			y = center.m_bfme04 - eyc + exs;
			if (bounds.lo.x > x) bounds.lo.x = x;
			if (*lowerY > y) *lowerY = y;
			if (*upperX < x) *upperX = x;
			if (bounds.hi.y < y) bounds.hi.y = y;

			x = center.m_bfme00 - exc + eys;
			y = center.m_bfme04 - eyc - exs;
			if (bounds.lo.x > x) bounds.lo.x = x;
			if (*lowerY > y) *lowerY = y;
			if (*upperX < x) *upperX = x;
			if (bounds.hi.y < y) bounds.hi.y = y;
			break;
		}
		}
	}
}
