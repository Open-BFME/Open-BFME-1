// cl: /O2 /DNDEBUG /MD

class Rva008A48D0Item
{
public:
	virtual void unused0();
	virtual void release();
};

extern Rva008A48D0Item *g_rva008A48D0_0;
extern Rva008A48D0Item *g_rva008A48D0_1;
extern Rva008A48D0Item *g_rva008A48D0_2;
extern Rva008A48D0Item *g_rva008A48D0_3;
extern Rva008A48D0Item *g_rva008A48D0_4;
extern Rva008A48D0Item *g_rva008A48D0_5;

void rva008A48D0ReleaseGlobals()
{
	Rva008A48D0Item *z = 0;
	if (g_rva008A48D0_0 != z)
	{
		g_rva008A48D0_0->release();
		g_rva008A48D0_0 = z;
	}
	if (g_rva008A48D0_1 != z)
	{
		g_rva008A48D0_1->release();
		g_rva008A48D0_1 = z;
	}
	if (g_rva008A48D0_2 != z)
	{
		g_rva008A48D0_2->release();
		g_rva008A48D0_2 = z;
	}
	if (g_rva008A48D0_3 != z)
	{
		g_rva008A48D0_3->release();
		g_rva008A48D0_3 = z;
	}
	if (g_rva008A48D0_4 != z)
	{
		g_rva008A48D0_4->release();
		g_rva008A48D0_4 = z;
	}
	if (g_rva008A48D0_5 != z)
	{
		g_rva008A48D0_5->release();
		g_rva008A48D0_5 = z;
	}
}
