// ?d_00100580@@YAXXZ
// partial score=0.98 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: GeometryInfo five-argument constructor, retail 0x00100580.
//
// The retail BFME object extends the older reference class with shape and
// record vectors.  Their element layouts are the same ones proven by the
// adjacent implicit copy constructor at 0x000FFD10.

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

extern "C" void __stdcall geometryRecordErase(GeometryRecord *first,
	GeometryRecord *last);

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void unknown();
	virtual const char *getName() const;

protected:
	Bool m_isSmall;
	Real m_scalar08;
	Real m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
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
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	Real m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

// ??0GeometryInfo@@QAE@W4GeometryType@@_NMMM@Z
GeometryInfo::GeometryInfo(GeometryType type, Bool isSmall, Real height,
Real majorRadius, Real minorRadius)
{
	m_scalar08 = 0.0f;
	m_scalar0c = 0.0f;
	std::vector<GeometryRecord> *records = &m_records;
	set(type, isSmall, height, majorRadius, minorRadius);
	__asm {
		fld dword ptr [esp+28h]
		fmul dword ptr [g_geometryHeightScale]
	}
	m_cached44 = 0;
	m_cached48 = 0;
	__asm {
		mov ecx, edi
		fstp dword ptr [esi+4ch]
	}
	m_cached50 = 0;
	m_cached54 = 0;
	m_cached58 = 0;
	records->erase(records->begin(), records->end());
}
