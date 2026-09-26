// ?d_00880020@@YAXXZ
// partial score=0.9 date=2026-09-16
// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

typedef bool Bool;
typedef float Real;

extern float g_bfmeDefaultBU;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString( const AsciiString &other );
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer( void );
	void *m_data;
};

class INI
{
public:
	static int scanIndexList( const char *token, const char *const *values );
	const char *getNextToken( const char *seps = 0 );
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	AsciiString m_name;
	Bool m_enabled;
	char m_pad[3];
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void loadPostProcess();
	virtual const char *getSnapshotName();
	virtual void xfer( Xfer *xfer );
};

class GeometryInfo : public Snapshot
{
public:
	static void parseAdditionalGeometry( INI *ini, void *instance, void *store, const void *userData );

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
	_STL::vector<GeometryShape> m_shapes;
	_STL::vector<int> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;

	void calcBoundingStuff();
};

static const char *const geometryNames[] = { "SPHERE", "CYLINDER", "BOX", 0 };

/*static*/ void GeometryInfo::parseAdditionalGeometry( INI *ini, void *, void *store, const void * )
{
	int type = INI::scanIndexList( ini->getNextToken(), geometryNames );

	GeometryShape shape;
	Real defaultSize = g_bfmeDefaultBU;
	shape.m_height = defaultSize;
	shape.m_majorRadius = defaultSize;
	shape.m_minorRadius = defaultSize;
	shape.m_type = type;
	shape.m_offset.x = 0.0f;
	shape.m_offset.y = 0.0f;
	shape.m_offset.z = 0.0f;
	shape.m_enabled = true;

	GeometryInfo *geometry = (GeometryInfo *)store;
	geometry->m_shapes.push_back( shape );
	geometry->calcBoundingStuff();
}
