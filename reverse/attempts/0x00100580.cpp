// ??0GeometryInfo@@QAE@W4GeometryType@@_NMMM@Z
// partial score=0.985 date=2026-09-11
// ??0GeometryInfo@@QAE@W4GeometryType@@_NMMM@Z
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

typedef bool Bool;
typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class AsciiString
{
private:
	void *m_data;

public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	char m_unmodelled00c[0x0C];
	Real m_offsetZ;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

extern Real g_geometryHeightScale;

class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);
	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);

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
	Real m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;

};

GeometryInfo::GeometryInfo(GeometryType type, Bool isSmall, Real height,
	Real majorRadius, Real minorRadius)
{
	m_scalar08 = 0;
	m_scalar0c = 0;
	set(type, isSmall, height, majorRadius, minorRadius);
	m_cached4c = *(volatile Real *)&height * g_geometryHeightScale;
	m_cached44 = 0;
	m_cached48 = 0;
	m_cached50 = 0;
	m_cached54 = 0;
	m_cached58 = 0;
	m_records.clear();
}
