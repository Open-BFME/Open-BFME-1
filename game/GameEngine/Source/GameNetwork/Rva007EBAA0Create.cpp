// cl: /O2
// 0x007EBAA0: allocate the 0x14-byte FESL diagnostic singleton at
// 0x0130A5A0 if it is still null.

// 0x007F0130 is retail's ILT thunk to ??2Gen007F0130@@SAPAXI@Z, the class
// operator new recovered in game/GameEngine/Source/Common/
// S3AllocatorOperatorNewDelete.cpp.  Same one-size signature.
class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

// The singleton cell is declared and defined with this exact spelling in
// game/GameEngine/Source/GameNetwork/Rva007EB920Assert.cpp, whose type gives
// the mangled name ?g_Va0130A5A0@@3PAURva007EB810Diag@@A.
struct Rva007EB810Diag;

extern void * const g_bfmeVftTDA[6];
extern void Rva007EB820(void);
extern Rva007EB810Diag *g_Va0130A5A0;

void Rva007EBAA0(void)
{
	if (g_Va0130A5A0)
		return;
	void *p = Gen007F0130::operator new(0x14);
	if (p)
	{
		*((int *)p + 2) = 0;
		*((int *)p + 3) = 0;
		*((int *)p + 4) = 0;
		*(int *)p = (int)g_bfmeVftTDA;
		*((int *)p + 1) = (int)&Rva007EB820;
		g_Va0130A5A0 = (Rva007EB810Diag *)p;
	}
	else
		g_Va0130A5A0 = 0;
}
