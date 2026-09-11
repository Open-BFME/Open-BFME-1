// cl: /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// stlport
// Open-BFME: vector<GeometryShape> copy constructor, retail 0x000FDE60.
//
// GeometryInfo's exact copy constructor calls this body through ILT
// 0x00027570 for its +0x2C member.  The element layout and memberwise copy are
// independently exact in GeometryShapeCopyConstructor.cpp: seven dwords,
// StringBase<char> at +0x1C, and the enabled byte at +0x20.
// The explicit instantiation also emits the canonical get_allocator,
// allocator-proxy, and vector-base dependencies at 0x000FCB00, 0x000FCCD0,
// and 0x000FD230.

#include <vector>
#include "StringInline.h"

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;

	// Making the aggregate copy explicit preserves retail's inlined
	// source-plus-0x18 cursor while retaining ordinary memberwise semantics.
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_centerOffset;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape();
	GeometryShape(const GeometryShape &other)
		: m_type(other.m_type),
		  m_height(other.m_height),
		  m_majorRadius(other.m_majorRadius),
		  m_minorRadius(other.m_minorRadius),
		  m_centerOffset(other.m_centerOffset),
		  m_name(other.m_name),
		  m_enabled(other.m_enabled),
		  m_unmodelled21()
	{
	}
};

template class _STL::vector<GeometryShape>;
