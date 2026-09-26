// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: retail 0x001A6520 (35 bytes) is the twin of the thiscall adapter at
// 0x001A64F0 (TerrainLogicP48Adapter.cpp) whose third argument is a BYTE: it is
// loaded with mov al and stored to its home slot with mov [esp+N],al before its
// address is passed on.

class TerrainLogicP48B;

class TerrainLogicP48B
{
public:
	void fiveArg(int a1, int a2, unsigned char *a3, int z1, int z2);
	void adapter(int a1, int a2, unsigned char a3);
};

void TerrainLogicP48B::adapter(int a1, int a2, volatile unsigned char a3)
{
	a3 = a3;
	fiveArg(a1, a2, (unsigned char *)&a3, 0, 0);
}
