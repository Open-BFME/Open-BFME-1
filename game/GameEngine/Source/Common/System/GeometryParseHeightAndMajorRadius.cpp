// cl: /EHsc /O2 /Ob2 /G6
// stlport
// Open-BFME: GeometryInfo::parseGeometryHeight, retail 0x0087F180, and
// GeometryInfo::parseGeometryMajorRadius, retail 0x0087F1D0.
//
// The object FieldParse table at 0x010913E0 pairs "GeometryHeight" with
// 0x0087F180 and "GeometryMajorRadius" with 0x0087F1D0. Both bodies sit
// between the landed GeometryInfo::parseGeometryIsSmall at 0x0087F160 and
// GeometryInfo::parseGeometryMinorRadius at 0x0087F220, and all four read the
// same shape vector at +0x2C, so the class is GeometryInfo.
//
// Each body counts the 0x24-byte shapes, parses one token into the last
// shape, and recomputes the bounds. parseGeometryHeight then calls the free
// function at 0x0087EBB0 that scales the max height into the Coord3D at +0x50.

#include <vector>

typedef bool Bool;
typedef float Real;

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	static Real scanReal(const char *token);
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	char m_unmodelled10[0x08];
	Real m_offsetZ;
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
	static void parseGeometryHeight(INI *ini, void *instance, void *store, const void *userData);
	static void parseGeometryMajorRadius(INI *ini, void *instance, void *store, const void *userData);

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

	void calcBoundingStuff();
};

// 0x0087EBB0, already landed in game/GameEngine/Source/Common/Rva0087EBB0Max.cpp.
// That file calls GeometryInfo::getMaxHeightAbovePosition on the pointer it
// receives, so BfmeObjEB is GeometryInfo under an address-derived name.
class BfmeObjEB;
void __cdecl bfmeApplyEB(BfmeObjEB *geometry);

/*static*/ void GeometryInfo::parseGeometryHeight(INI *ini, void *, void *store, const void *)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (geometry->m_shapes.size() != 0)
		geometry->m_shapes.back().m_height = INI::scanReal(ini->getNextToken());
	geometry->calcBoundingStuff();
	bfmeApplyEB((BfmeObjEB *)geometry);
}

/*static*/ void GeometryInfo::parseGeometryMajorRadius(INI *ini, void *, void *store, const void *)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (geometry->m_shapes.size() != 0)
		geometry->m_shapes.back().m_majorRadius = INI::scanReal(ini->getNextToken());
	geometry->calcBoundingStuff();
}
