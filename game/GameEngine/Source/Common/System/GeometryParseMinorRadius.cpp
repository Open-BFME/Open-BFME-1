// cl: /EHsc /O2 /Ob2 /G6
// stlport
// Open-BFME: GeometryInfo::parseGeometryMinorRadius, retail 0x0087F220.

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
	static void parseGeometryMinorRadius(INI *ini, void *instance, void *store, const void *userData);

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

/*static*/ void GeometryInfo::parseGeometryMinorRadius(INI *ini, void *, void *store, const void *)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (geometry->m_shapes.size() != 0)
		geometry->m_shapes.back().m_minorRadius = INI::scanReal(ini->getNextToken());
	geometry->calcBoundingStuff();
}
