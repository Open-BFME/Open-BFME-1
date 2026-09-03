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
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

	public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);

	private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
	void set(const AsciiString &other) { StringBase<char>::set(other); }
};

struct BfmeElem60
{
	BfmeElem60()
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
	}

	BfmeElem60(GeometryType type, RealBits height, RealBits majorRadius,
		RealBits minorRadius)
		: m_type(type),
		  m_height(height),
		  m_majorRadius(majorRadius),
		  m_minorRadius(type == GEOMETRY_BOX ? minorRadius : majorRadius),
		  m_unmodelled10(0),
		  m_unmodelled14(0),
		  m_unmodelled18(0),
		m_name(),
		  m_enabled(true)
	{
	}

	BfmeElem60(const BfmeElem60 &other);

	BfmeElem60 &operator=(const BfmeElem60 &other)
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_unmodelled10 = other.m_unmodelled10;
		m_unmodelled14 = other.m_unmodelled14;
		m_unmodelled18 = other.m_unmodelled18;
		m_name.set(other.m_name);
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
	StringBase<char> m_name;
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

class BfmeVec60
{
	public:
		void resize(unsigned newSize, BfmeElem60 value = BfmeElem60());

		__forceinline BfmeElem60 &operator[](unsigned index) { return m_start[index]; }
		__forceinline unsigned size() const { return (unsigned)(m_finish - m_start); }

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
	virtual void unknown();
	virtual const char *getName() const;
};

class GeometryInfo
{
public:
	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);

private:
	int m_unknown00;
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
	RawVec m_records;
};

// ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z
void GeometryInfo::set(GeometryType type, Bool isSmall, Real height,
	Real majorRadius, Real minorRadius)
{
	BfmeElem60 shape(type, *(const RealBits *)&height,
		*(const RealBits *)&majorRadius, *(const RealBits *)&minorRadius);
	GeometryInfo *self = this;
	BfmeVec60 *shapes = &self->m_shapes;
	self->m_isSmall = isSmall;

	if (shapes->size() != 1)
		shapes->resize(1);
	(*shapes)[0] = shape;
	self->calcBoundingStuff();
}
