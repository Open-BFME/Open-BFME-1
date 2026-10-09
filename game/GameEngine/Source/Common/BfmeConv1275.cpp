// Open-BFME5 conversions.
// Callees (tools/callees.py 0x1A62D0 58): ILT 0x37EC5 -> 0x001A31B0 Rva001A31B0 ctor,
// ILT 0x23448 -> 0x001A4630 Rva001A4630TerrainRecordQuery::queryPointImplAt001A4630.

struct Coord3D;

class Rva001A31B0
{
public:
	Rva001A31B0();
	char m_bfmePad00[0x14];
	int m_bfme14;
};

struct Rva001A62D0TerrainQueryResult;

class Rva001A4630TerrainRecordQuery
{
public:
	void queryPointImplAt001A4630(const Coord3D *position, float radius,
		Rva001A62D0TerrainQueryResult *result, bool firstConstraint, int mode);
};

class BfmeA1275
{
public:
	int bfmeGo1275(int a1, int a2, int a3, int a4);
};

int BfmeA1275::bfmeGo1275(int a1, int a2, int a3, int a4)
{
	Rva001A31B0 q;

	reinterpret_cast<Rva001A4630TerrainRecordQuery *>(this)->queryPointImplAt001A4630(
		(const Coord3D *)a1, *reinterpret_cast<float *>(&a2),
		reinterpret_cast<Rva001A62D0TerrainQueryResult *>(&q), *reinterpret_cast<bool *>(&a3), a4);
	return q.m_bfme14;
}
