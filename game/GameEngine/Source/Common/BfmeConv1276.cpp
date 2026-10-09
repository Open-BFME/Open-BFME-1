// Open-BFME5 conversions.
// Callees (tools/callees.py 0x1A6320 57): ILT 0x2DE20 -> 0x001A3250 Rva001A3250::set,
// ILT 0x2400 -> 0x001A4A00 Rva001A4A00RecordGridScan::scan.

struct Coord3D;
class BfmeHostEZ;

class Rva001A3250
{
public:
	Rva001A3250 &set(int a);
	char m_bfmePad00[0x14];
	int m_bfme14;
	int m_bfme18;
};

class Rva001A4A00RecordGridScan
{
public:
	void scan(const Coord3D *position, float radius, BfmeHostEZ *result, bool flag, int mode);
};

class BfmeA1276
{
public:
	int bfmeGo1276(int a1, int a2, int a3);
};

int BfmeA1276::bfmeGo1276(int a1, int a2, int a3)
{
	Rva001A3250 q;
	q.set(a1);

	reinterpret_cast<Rva001A4A00RecordGridScan *>(this)->scan(
		(const Coord3D *)a2, *reinterpret_cast<float *>(&a3),
		reinterpret_cast<BfmeHostEZ *>(&q), false, 2);
	return q.m_bfme14;
}
