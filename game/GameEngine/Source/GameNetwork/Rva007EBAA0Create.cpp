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
extern void Rva007EB820PrintMessage(void *context, const char *message);
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
		*((int *)p + 1) = (int)&Rva007EB820PrintMessage;
		g_Va0130A5A0 = (Rva007EB810Diag *)p;
	}
	else
		g_Va0130A5A0 = 0;
}

// 0x007EBA60: the getter twin directly above the creator.  Same lazy
// allocation of the 0x0130A5A0 singleton, but it returns the cell.  Retail
// keeps one result variable (the loaded cell or the allocation) in EAX across
// both paths, so the failed-allocation arm stores the zero register and still
// returns the allocator's null.  No reference to this address survives in
// retail, so the name keeps the address.
Rva007EB810Diag *Rva007EBA60Get(void)
{
	Rva007EB810Diag *p = g_Va0130A5A0;
	if (!p)
	{
		p = (Rva007EB810Diag *)Gen007F0130::operator new(0x14);
		if (p)
		{
			*((int *)p + 2) = 0;
			*((int *)p + 3) = 0;
			*((int *)p + 4) = 0;
			*(int *)p = (int)g_bfmeVftTDA;
			*((int *)p + 1) = (int)&Rva007EB820PrintMessage;
			g_Va0130A5A0 = p;
		}
		else
			g_Va0130A5A0 = 0;
	}
	return p;
}
