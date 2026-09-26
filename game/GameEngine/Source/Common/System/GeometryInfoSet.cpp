// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: GeometryInfo::set, retail 0x008804E0.
//
// ThingTemplate::initForLTA and the five-argument GeometryInfo constructor
// call this body; the Zero Hour twin GeometryInfo::set has the same signature.
// BFME keeps the dimensions in the first 0x24-byte element of the vector at
// +0x2C: it builds one element from the arguments, resizes the vector to one
// element when needed, copies the element in and recomputes the bounds.
//
// Retail stores the four dimension fields and selects the minor radius with
// a branch BEFORE the element's +0x1C string is constructed, and zeroes the
// +0x10 triple with immediates before the string is nulled.  That order is
// base-then-members construction: the dimensions live in a base part whose
// constructor holds the if/else, and the triple has its own zeroing
// constructor.  The retail default element (resize's by-value argument)
// stores the triple before the string for the same reason.

#include "ascii_string.h"

typedef bool Bool;
typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// Three dwords at element +0x10, copied as one unit by the element's
// assignment (retail addresses them through lea edx, [esi+0x10]).
struct Triple10
{
	Triple10() : dword_0(0.0f), dword_4(0.0f), dword_8(0.0f) {}

	Real dword_0;
	Real dword_4;
	Real dword_8;
};

// Element +0x00..+0x0C.  The four fields take GeometryInfo::set's type,
// height, majorRadius and minorRadius arguments, as the Zero Hour twin's
// GeometryInfo members of the same names do.
struct BfmeElem60Head
{
	BfmeElem60Head(int type, Real height, Real majorRadius,
		Real minorRadius)
	{
		m_type = type;
		m_height = height;
		m_majorRadius = majorRadius;
		if (type == GEOMETRY_BOX)
			m_minorRadius = minorRadius;
		else
			m_minorRadius = majorRadius;
	}

	BfmeElem60Head()
		: m_type(GEOMETRY_SPHERE),
		  m_height(1.0f),
		  m_majorRadius(1.0f),
		  m_minorRadius(1.0f)
	{
	}

	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
};

// 0x24-byte element of the vector at GeometryInfo+0x2C (BfmeVec60, whose
// resize at 0x00880260 takes it by value).
struct BfmeElem60 : public BfmeElem60Head
{
	BfmeElem60(int type, Real height, Real majorRadius,
		Real minorRadius)
		: BfmeElem60Head(type, height, majorRadius, minorRadius),
		  m_name(),
		  m_enabled(true)
	{
	}

	BfmeElem60()
		: m_name(),
		  m_enabled(true)
	{
	}

	BfmeElem60 &operator=(const BfmeElem60 &other)
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_triple10 = other.m_triple10;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
		return *this;
	}

	Triple10 m_triple10;
	AsciiString m_name;
	Bool m_enabled;
	char m_padding21[3];
};

class BfmeVec60
{
public:
	void resize(unsigned newSize, BfmeElem60 value = BfmeElem60());

	BfmeElem60 &operator[](unsigned index) { return m_start[index]; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }

private:
	BfmeElem60 *m_start;
	BfmeElem60 *m_finish;
	BfmeElem60 *m_endOfStorage;
};

struct RawVec
{
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class GeometryInfo : public Snapshot
{
public:
	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);

private:
	void calcBoundingStuff();

	Bool m_isSmall;
	char m_padding05[3];
	int m_scalar08;
	int m_scalar0C;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1C;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	BfmeVec60 m_shapes;
	RawVec m_38;
};

// ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z
void GeometryInfo::set(GeometryType type, Bool isSmall, Real height,
	Real majorRadius, Real minorRadius)
{
	BfmeElem60 shape(type, height, majorRadius, minorRadius);
	m_isSmall = isSmall;

	if (m_shapes.size() != 1)
		m_shapes.resize(1);
	m_shapes[0] = shape;
	calcBoundingStuff();
}
