// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: retail 0x001A6520 (35 bytes) is the twin of the thiscall adapter at
// 0x001A64F0 (TerrainLogicP48Adapter.cpp) whose third argument is a BYTE: it is
// loaded with mov al and stored to its home slot with mov [esp+N],al before its
// address is passed on.
//
// The call goes through ILT 0x00002C39 to the matched grid visit at 0x001A55E0
// (callees.py); its first two arguments are passed through unchanged.

struct Coord3D;

class Rva001A55E0GridVisitByte
{
public:
	void visit(const Coord3D *pos, float radius, const unsigned char *payload, unsigned char z1, int z2);
};

class TerrainLogicP48B
{
public:
	void adapter(int a1, int a2, unsigned char a3);
};

void TerrainLogicP48B::adapter(int a1, int a2, volatile unsigned char a3)
{
	a3 = a3;
	((Rva001A55E0GridVisitByte *)this)->visit((const Coord3D *)a1, *(float *)&a2, (const unsigned char *)&a3, 0, 0);
}
