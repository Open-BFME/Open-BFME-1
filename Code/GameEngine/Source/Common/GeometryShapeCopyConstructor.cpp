// Open-BFME: GeometryShape copy constructor, retail 0x000FCED0.
//
// The 0x24-byte element layout is proven by GeometryInfo's shape vector:
// scalar fields occupy 0x00..0x18, followed by AsciiString at 0x1c and the
// enabled byte at 0x20.  The retail body is the corresponding memberwise
// copy, including the existing AsciiString copy-constructor call.

typedef bool Bool;

class AsciiString
{
private:
	void *m_data;

public:
	AsciiString(const AsciiString &other);
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	int m_unmodelled00c;
	int m_unmodelled10;
	int m_unmodelled14;
	float m_offsetZ;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape(const GeometryShape &other);
};

// ??0GeometryShape@@QAE@ABV0@@Z
GeometryShape::GeometryShape(const GeometryShape &other)
	: m_type(other.m_type),
	  m_height(other.m_height),
	  m_majorRadius(other.m_majorRadius),
	  m_unmodelled00c(other.m_unmodelled00c),
	  m_unmodelled10(other.m_unmodelled10),
	  m_unmodelled14(other.m_unmodelled14),
	  m_offsetZ(other.m_offsetZ),
	  m_name(other.m_name),
	  m_enabled(other.m_enabled),
	  m_unmodelled21()
{
}
