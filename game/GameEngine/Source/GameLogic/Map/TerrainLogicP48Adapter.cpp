// cl: /DNDEBUG /MD /EHsc

// Open-BFME: thiscall adapter at 0x001A64F0.  Retail is 35 bytes, ret 0xC,
// and the five-argument callee at 0x001A51F0 is itself thiscall (uses ecx).
// The third argument is stored into its own home slot so its address can be
// passed; the two trailing arguments are immediate zeros.

class TerrainLogicP48;

class TerrainLogicP48
{
public:
	void fiveArg(int a1, int a2, int *a3, int z1, int z2);
	void adapter(int a1, int a2, int a3);
};

void TerrainLogicP48::adapter(int a1, int a2, volatile int a3)
{
	a3 = a3;
	fiveArg(a1, a2, (int *)&a3, 0, 0);
}
