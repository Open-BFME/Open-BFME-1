// Callees (tools/callees.py 0x1A6280 52): ILT 0x37EC5 -> 0x001A31B0 Rva001A31B0 ctor,
// ILT 0x23448 -> 0x001A4630 Rva001A4630TerrainRecordQuery::queryPointImplAt001A4630.
struct Coord3D;

class Rva001A31B0
{
public:
	Rva001A31B0();
	int m_00, m_04, m_08, m_0C;
	float m_10;
	int m_bfmeResult;
};

struct Rva001A62D0TerrainQueryResult;

class Rva001A4630TerrainRecordQuery
{
public:
	void queryPointImplAt001A4630(const Coord3D *position, float radius,
		Rva001A62D0TerrainQueryResult *result, bool firstConstraint, int mode);
};

class BfmeThingCME
{
public:
	int bfmeGoCME(void *what);
};

int BfmeThingCME::bfmeGoCME(void *what)
{
	Rva001A31B0 tmp;
	reinterpret_cast<Rva001A4630TerrainRecordQuery *>(this)->queryPointImplAt001A4630(
		(const Coord3D *)what, 10.0f, reinterpret_cast<Rva001A62D0TerrainQueryResult *>(&tmp), false, 0);
	return tmp.m_bfmeResult;
}
