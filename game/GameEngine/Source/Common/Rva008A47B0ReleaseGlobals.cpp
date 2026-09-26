// cl: /O2 /DNDEBUG /MD

// Open-BFME7: near-twin of Rva008A48D0ReleaseGlobals.cpp (0x008A48D0, 131 B),
// same shape (release each ref-counted global through vtable slot +4, then
// null it), but with eight globals instead of six and a caller (0x00894A90,
// proven in an earlier attempt) at retail 0x008A47B0, 173 bytes. The eighth
// global (0x01337A88) sits out of address order at the end, matching the
// retail call order exactly.

class Rva008A47B0Item
{
public:
	virtual void unused0();
	virtual void release();
};

extern Rva008A47B0Item *g_rva008A47B0_0;
extern Rva008A47B0Item *g_rva008A47B0_1;
extern Rva008A47B0Item *g_rva008A47B0_2;
extern Rva008A47B0Item *g_rva008A47B0_3;
extern Rva008A47B0Item *g_rva008A47B0_4;
extern Rva008A47B0Item *g_rva008A47B0_5;
extern Rva008A47B0Item *g_rva008A47B0_6;
extern Rva008A47B0Item *g_rva008A47B0_7;

void rva008A47B0ReleaseGlobals()
{
	Rva008A47B0Item *z = 0;
	if (g_rva008A47B0_0 != z)
	{
		g_rva008A47B0_0->release();
		g_rva008A47B0_0 = z;
	}
	if (g_rva008A47B0_1 != z)
	{
		g_rva008A47B0_1->release();
		g_rva008A47B0_1 = z;
	}
	if (g_rva008A47B0_2 != z)
	{
		g_rva008A47B0_2->release();
		g_rva008A47B0_2 = z;
	}
	if (g_rva008A47B0_3 != z)
	{
		g_rva008A47B0_3->release();
		g_rva008A47B0_3 = z;
	}
	if (g_rva008A47B0_4 != z)
	{
		g_rva008A47B0_4->release();
		g_rva008A47B0_4 = z;
	}
	if (g_rva008A47B0_5 != z)
	{
		g_rva008A47B0_5->release();
		g_rva008A47B0_5 = z;
	}
	if (g_rva008A47B0_6 != z)
	{
		g_rva008A47B0_6->release();
		g_rva008A47B0_6 = z;
	}
	if (g_rva008A47B0_7 != z)
	{
		g_rva008A47B0_7->release();
		g_rva008A47B0_7 = z;
	}
}
