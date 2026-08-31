// ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z
// partial score=0.91 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHs-c-
// stlport
// Open-BFME: GeometryInfo::set, retail 0x008804E0.
//
// ThingTemplate::initForLTA calls this body directly with its GeometryInfo at
// +0x60.  The retail code keeps exactly one 0x24-byte GeometryShape in the
// first vector at +0x2C, assigns the requested dimensions to that shape, and
// finishes through GeometryInfo::calcBoundingStuff.

#define _STLP_NO_EXCEPTIONS 1
typedef bool Bool;
typedef float Real;
typedef unsigned int RealBits;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

template <typename T>
class StringBase
{
public:
	StringBase() {}
	void init() { m_data = 0; }
	void set(const StringBase<T> &other);
	void releaseBuffer();

private:
	void *m_data;
};

class AsciiString
{
public:
	AsciiString() {}
	void init() { m_string.init(); }
	~AsciiString() { m_string.releaseBuffer(); }
	AsciiString &operator=(const AsciiString &other)
	{
		m_string.set(other.m_string);
		return *this;
	}

private:
	StringBase<char> m_string;
};

struct GeometryShape
{
	GeometryShape()
		: m_type(GEOMETRY_SPHERE),
		  m_height(0x3F800000u),
		  m_majorRadius(0x3F800000u),
		  m_minorRadius(0x3F800000u),
		  m_unmodelled10(0),
		  m_unmodelled14(0),
		  m_unmodelled18(0),
		  m_name(),
		  m_enabled(true)
	{
		m_name.init();
	}

	GeometryShape(GeometryType type, RealBits height, RealBits majorRadius,
		RealBits minorRadius)
		: m_type(type),
		  m_height(height),
		  m_majorRadius(majorRadius),
		  m_minorRadius(minorRadius),
		  m_unmodelled10(0),
		  m_unmodelled14(0),
		  m_unmodelled18(0),
		  m_name(),
		  m_enabled(true)
	{
		m_name.init();
	}

	GeometryShape(const GeometryShape &other);

	GeometryShape &operator=(const GeometryShape &other)
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_unmodelled10 = other.m_unmodelled10;
		m_unmodelled14 = other.m_unmodelled14;
		m_unmodelled18 = other.m_unmodelled18;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
		return *this;
	}

	int m_type;
	RealBits m_height;
	RealBits m_majorRadius;
	RealBits m_minorRadius;
	int m_unmodelled10;
	int m_unmodelled14;
	int m_unmodelled18;
	AsciiString m_name;
	Bool m_enabled;
	char m_padding21[3];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

namespace _STL
{
	template <typename Type>
	class allocator {};

	template <typename Type, typename Allocator = allocator<Type> >
	class vector
	{
	public:
		typedef unsigned int size_type;

		void resize(size_type newSize, Type value = Type());

		__forceinline Type &operator[](size_type index) { return m_start[index]; }
		__forceinline size_type size() const { return (size_type)(m_finish - m_start); }

	private:
		Type *m_start;
		Type *m_finish;
		Type *m_endOfStorage;
	};
}

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
	_STL::vector<GeometryShape> m_shapes;
	_STL::vector<GeometryRecord> m_records;
};

// ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z
void GeometryInfo::set(GeometryType type, Bool isSmall, Real height,
	Real majorRadius, Real minorRadius)
{
	RealBits heightBits = *(const RealBits *)&height;
	RealBits majorBits = *(const RealBits *)&majorRadius;
	RealBits minorBits = *(const RealBits *)&minorRadius;
	GeometryShape shape(type, heightBits, majorBits,
		type == GEOMETRY_BOX ? minorBits : majorBits);
	m_isSmall = isSmall;

	if (m_shapes.size() != 1)
		m_shapes.resize(1);
	m_shapes[0] = shape;
	calcBoundingStuff();
}
