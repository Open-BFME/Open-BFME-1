// Open-BFME: GeometryInfo::parseGeometryType, retail 0x00880480.
//
// ThingTemplate registers this callback for both Geometry fields.  The body
// parses through the canonical GeometryNames table, grows GeometryInfo's
// 0x24-byte shape vector at +0x2C, writes the selected type into its first
// element, and tail-calls calcBoundingStuff.
//
// Modeling the real nested Coord3D and string members is material here.  Their
// inline default construction preserves retail's constant/load schedule; a
// flat collection of volatile scalar fields emits the same stores in a
// different order around the saved scan result.

extern "C" const char *const GeometryNames[];

class INI
{
public:
	const char *getNextToken(const char *separators) throw();
	static int scanIndexList(const char *token, const char *const *names) throw();
};

struct BfmeCoord3D
{
	__forceinline BfmeCoord3D() throw() : x(0.0f), y(0.0f), z(0.0f) {}

	float x;
	float y;
	float z;
};

class BfmeAsciiString
{
public:
	__forceinline BfmeAsciiString() throw() : m_data(0) {}

private:
	char *m_data;
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
		: m_type(0), m_height(1.0f), m_majorRadius(1.0f),
		  m_minorRadius(1.0f), m_center(), m_name(), m_enabled(true)
	{
	}

	__forceinline BfmeElem60(const BfmeElem60 &other) throw()
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_center = other.m_center;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
	}

	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	BfmeCoord3D m_center;
	BfmeAsciiString m_name;
	unsigned char m_enabled;
	unsigned char m_padding[3];
};

class BfmeVec60
{
public:
	void resize(unsigned int count, BfmeElem60 value) throw();

	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

class GeometryInfo
{
public:
	static void parseGeometryType(INI *, void *, void *, const void *);

private:
	unsigned char m_head[0x2C];
	BfmeVec60 m_shapes;

	void calcBoundingStuff() throw();
};

void GeometryInfo::parseGeometryType(INI *ini, void *, void *store, const void *)
{
	int type = INI::scanIndexList(ini->getNextToken(0), GeometryNames);
	GeometryInfo *geometry = (GeometryInfo *)store;
	geometry->m_shapes.resize(1, BfmeElem60());
	geometry->m_shapes.m_begin->m_type = type;
	geometry->calcBoundingStuff();
}
