// cl: /EHsc /O2 /Ob2 /G6
// stlport
// Open-BFME: GeometryInfo::parseGeometryActive, retail 0x0087DE10, and
// GeometryInfo::parseGeometryOffset, retail 0x0087DE50.
//
// The object FieldParse table at 0x010913E0 pairs "GeometryActive" with
// 0x0087DE10 and "GeometryOffset" with 0x0087DE50. Both bodies guard on the
// same 0x24-byte shape vector at +0x2C that the landed
// GeometryInfo::parseGeometryMinorRadius at 0x0087F220 reads, and both sit in
// the Geometry.cpp run that holds GeometryInfo::isIntersectedByLineSegment at
// 0x0087DFC0, so the class is GeometryInfo.
//
// Each body forwards to a stock INI parser with the store pointer aimed at
// one member of the last shape. The Coord3D at +0x10 of a shape is the one
// whose z the GeometryParseMinorRadius shim calls m_offsetZ.

#include <vector>

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class INI
{
public:
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	char m_name[0x04];
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void loadPostProcess();
	virtual const char *getSnapshotName();
	virtual void xfer(Xfer *xfer);
};

class GeometryInfo : public Snapshot
{
public:
	static void parseGeometryActive(INI *ini, void *instance, void *store, const void *userData);
	static void parseGeometryOffset(INI *ini, void *instance, void *store, const void *userData);

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
	std::vector<int> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

/*static*/ void GeometryInfo::parseGeometryActive(INI *ini, void *instance, void *store, const void *)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (geometry->m_shapes.size() != 0)
		INI::parseBool(ini, instance, &geometry->m_shapes.back().m_enabled, 0);
}

/*static*/ void GeometryInfo::parseGeometryOffset(INI *ini, void *instance, void *store, const void *userData)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (geometry->m_shapes.size() != 0)
		INI::parseCoord3D(ini, instance, &geometry->m_shapes.back().m_offset, userData);
}
