// cl: /DNDEBUG /MD /EHsc

// Open-BFME: thiscall adapter at 0x001A64F0.  Retail is 35 bytes, ret 0xC,
// and the five-argument callee at 0x001A51F0 is itself thiscall (uses ecx).
// The third argument is stored into its own home slot so its address can be
// passed; the two trailing arguments are immediate zeros.

struct Coord3D;

// The callee at 0x001A51F0 is matched as Rva001A51F0GridVisitInt::visit
// (Rva001A51F0GridVisitInt.cpp; callees.py).
class Rva001A51F0GridVisitInt
{
public:
	void visit(const Coord3D *pos, float radius, const int *value, unsigned char flag, int extra);
};

class TerrainLogicP48
{
public:
	void adapter(int a1, int a2, int a3);
};

void TerrainLogicP48::adapter(int a1, int a2, volatile int a3)
{
	a3 = a3;
	((Rva001A51F0GridVisitInt *)this)->visit((const Coord3D *)a1, *(float *)&a2, (const int *)&a3, 0, 0);
}
