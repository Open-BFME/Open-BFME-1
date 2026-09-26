// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /G6 /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: GeometryInfo method at retail 0x0087E650, 636 bytes; the method's
// name is not proven, so it keeps its address.
//
// The owner is GeometryInfo: the matched GeometryInfo::calcBoundingStuff
// (0x0087EE60, call at +0x81) passes this and one stack bounds buffer, and the
// body walks the 0x24-byte shape vector at this+0x2C/+0x30 the landed
// GeometryInfo parsers read. It clears the buffer, then takes the min corner
// and max corner over every enabled shape: a sphere spans its major radius on
// all three axes, a cylinder and a box sit on their offset z and rise by their
// height, and a box uses its minor radius across y.
//
// The two Coord3D halves and their zero() calls are load-bearing: six scalar
// stores give 631 bytes and a different register set (ebp stays &hi).

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
	AsciiString m_unmodelled1C;
	Bool m_enabled;
	char m_unmodelled21[3];
};

// Min corner then max corner; filled by the body below.
struct Rva0087E650Bounds
{
	Coord3D lo, hi;
};

// Reference-returning, so MSVC selects the address of the winner and reloads
// through it, as retail does.
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
	bounds->lo.zero();
	bounds->hi.zero();

	for (std::vector<GeometryShape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		if (!it->m_enabled)
			continue;

		switch (it->m_type)
		{
		case GEOMETRY_SPHERE:
			bounds->lo.x = bfmeMin(bounds->lo.x, it->m_offset.x - it->m_majorRadius);
			bounds->lo.y = bfmeMin(bounds->lo.y, it->m_offset.y - it->m_majorRadius);
			bounds->lo.z = bfmeMin(bounds->lo.z, it->m_offset.z - it->m_majorRadius);
			bounds->hi.x = bfmeMax(bounds->hi.x, it->m_offset.x + it->m_majorRadius);
			bounds->hi.y = bfmeMax(bounds->hi.y, it->m_offset.y + it->m_majorRadius);
			bounds->hi.z = bfmeMax(bounds->hi.z, it->m_offset.z + it->m_majorRadius);
			break;
		case GEOMETRY_CYLINDER:
			bounds->lo.x = bfmeMin(bounds->lo.x, it->m_offset.x - it->m_majorRadius);
			bounds->lo.y = bfmeMin(bounds->lo.y, it->m_offset.y - it->m_majorRadius);
			bounds->lo.z = bfmeMin(bounds->lo.z, it->m_offset.z);
			bounds->hi.x = bfmeMax(bounds->hi.x, it->m_offset.x + it->m_majorRadius);
			bounds->hi.y = bfmeMax(bounds->hi.y, it->m_offset.y + it->m_majorRadius);
			bounds->hi.z = bfmeMax(bounds->hi.z, it->m_offset.z + it->m_height);
			break;
		case GEOMETRY_BOX:
			bounds->lo.x = bfmeMin(bounds->lo.x, it->m_offset.x - it->m_majorRadius);
			bounds->lo.y = bfmeMin(bounds->lo.y, it->m_offset.y - it->m_minorRadius);
			bounds->lo.z = bfmeMin(bounds->lo.z, it->m_offset.z);
			bounds->hi.x = bfmeMax(bounds->hi.x, it->m_offset.x + it->m_majorRadius);
			bounds->hi.y = bfmeMax(bounds->hi.y, it->m_offset.y + it->m_minorRadius);
			bounds->hi.z = bfmeMax(bounds->hi.z, it->m_offset.z + it->m_height);
			break;
		}
	}
}
