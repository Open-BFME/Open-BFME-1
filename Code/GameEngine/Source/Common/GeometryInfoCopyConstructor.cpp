// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: GeometryInfo copy constructor, retail 0x000FFD10.
//
// BFME's GeometryInfo is larger than the older reference declaration: it has
// two STL vectors at +0x2C and +0x38, followed by the cached extent fields.
// The first vector's 0x24-byte element contains a StringBase<char> at +0x1C;
// the second vector's 0x10-byte element contains one at +0x0C.  These are the
// two member-copy calls visible in the retail constructor.

#include <vector>

typedef bool Bool;

template <typename T>
class StringBase
{
private:
	void *m_data;
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	char m_unmodelled00c[0x0C];
	float m_offsetZ;
	StringBase<char> m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	StringBase<char> m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void unknown();
	virtual const char *getName() const;
};

class GeometryInfo : public Snapshot
{
public:
private:
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

// Force emission of GeometryInfo's compiler-generated copy constructor.
GeometryInfo copyGeometryInfo(const GeometryInfo &other)
{
	return other;
}
