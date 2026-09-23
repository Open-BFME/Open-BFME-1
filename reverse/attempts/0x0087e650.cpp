// ?d_0087e650@@YAXXZ
// partial score=0.9 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /G6 /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Address-derived GeometryInfo body at 0x0087E650.

#include <vector>
#include "coord.h"
#include "ascii_string.h"

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
	AsciiString m_name;
	Bool m_enabled;
	char m_padding[3];
};

typedef char GeometryShape_size_check[sizeof(GeometryShape) == 0x24 ? 1 : -1];

struct Rva0087E650Bounds
{
	Real m_minX;
	Real m_minY;
	Real m_minZ;
	Real m_maxX;
	Real m_maxY;
	Real m_maxZ;
};

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

class GeometryInfo
{
public:
	void rva0087E650(Rva0087E650Bounds *bounds);

private:
	char m_prefix[0x2C];
	std::vector<GeometryShape> m_shapes;
};

// ?rva0087E650@GeometryInfo@@QAEXPAURva0087E650Bounds@@@Z
void GeometryInfo::rva0087E650(Rva0087E650Bounds *bounds)
{
	bounds->m_minX = 0.0f;
	bounds->m_minY = 0.0f;
	bounds->m_minZ = 0.0f;
	bounds->m_maxX = 0.0f;
	bounds->m_maxY = 0.0f;
	bounds->m_maxZ = 0.0f;

	volatile Real value;
	for (std::vector<GeometryShape>::iterator shape = m_shapes.begin(); shape != m_shapes.end(); ++shape)
	{
		if (!shape->m_enabled)
			continue;

		int shapeType = shape->m_type;
		if (shapeType == GEOMETRY_SPHERE)
			goto rvaSphere;
		--shapeType;
		if (shapeType == GEOMETRY_SPHERE)
			goto rvaCylinder;
		--shapeType;
		if (shapeType != GEOMETRY_SPHERE)
			continue;
		rvaBox:
		{
			value = shape->m_offset.x - shape->m_majorRadius;
			if (!(bounds->m_minX < value))
				bounds->m_minX = value;
			value = shape->m_offset.y - shape->m_minorRadius;
			if (!(bounds->m_minY < value))
				bounds->m_minY = value;
			if (!(bounds->m_minZ < shape->m_offset.z))
				bounds->m_minZ = shape->m_offset.z;
			value = shape->m_offset.x + shape->m_majorRadius;
			if (!(bounds->m_maxX > value))
				bounds->m_maxX = value;
			value = shape->m_offset.y + shape->m_minorRadius;
			if (!(bounds->m_maxY > value))
				bounds->m_maxY = value;
			value = shape->m_offset.z + shape->m_height;
			if (!(bounds->m_maxZ > value))
				bounds->m_maxZ = value;
		}
			goto rvaBoundsEnd;
		rvaCylinder:
		{
			value = shape->m_offset.x - shape->m_majorRadius;
			if (!(bounds->m_minX < value))
				bounds->m_minX = value;
			value = shape->m_offset.y - shape->m_majorRadius;
			if (!(bounds->m_minY < value))
				bounds->m_minY = value;
			value = shape->m_offset.z - shape->m_majorRadius;
			if (!(bounds->m_minZ < value))
				bounds->m_minZ = value;
			value = shape->m_offset.x + shape->m_majorRadius;
			if (!(bounds->m_maxX > value))
				bounds->m_maxX = value;
			value = shape->m_offset.y + shape->m_majorRadius;
			if (!(bounds->m_maxY > value))
				bounds->m_maxY = value;
			value = shape->m_offset.z + shape->m_height;
			if (!(bounds->m_maxZ > value))
				bounds->m_maxZ = value;
		}
			goto rvaBoundsEnd;
		rvaSphere:
		{
			value = shape->m_offset.x - shape->m_majorRadius;
			if (!(bounds->m_minX < value))
				bounds->m_minX = value;
			value = shape->m_offset.y - shape->m_majorRadius;
			if (!(bounds->m_minY < value))
				bounds->m_minY = value;
			value = shape->m_offset.z - shape->m_majorRadius;
			if (!(bounds->m_minZ < value))
				bounds->m_minZ = value;
			value = shape->m_offset.x + shape->m_majorRadius;
			if (!(bounds->m_maxX > value))
				bounds->m_maxX = value;
			value = shape->m_offset.y + shape->m_majorRadius;
			if (!(bounds->m_maxY > value))
				bounds->m_maxY = value;
			value = shape->m_offset.z + shape->m_majorRadius;
			if (!(bounds->m_maxZ > value))
				bounds->m_maxZ = value;
		}
		rvaBoundsEnd:
		;
	}
}
