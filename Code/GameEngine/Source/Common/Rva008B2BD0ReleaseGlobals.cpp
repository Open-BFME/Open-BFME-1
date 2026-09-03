// cl: /O2 /DNDEBUG /MD

class Rva008B2BD0Item
{
public:
	virtual void unused0();
	virtual void release();
};

extern Rva008B2BD0Item *g_rva008B2BD0_0;
extern Rva008B2BD0Item *g_rva008B2BD0_1;
extern Rva008B2BD0Item *g_rva008B2BD0_2;
extern Rva008B2BD0Item *g_rva008B2BD0_3;
extern Rva008B2BD0Item *g_rva008B2BD0_4;
extern Rva008B2BD0Item *g_rva008B2BD0_5;

void rva008B2BD0ReleaseGlobals()
{
	Rva008B2BD0Item *z = 0;
	if (g_rva008B2BD0_0 != z)
	{
		g_rva008B2BD0_0->release();
		g_rva008B2BD0_0 = z;
	}
	if (g_rva008B2BD0_1 != z)
	{
		g_rva008B2BD0_1->release();
		g_rva008B2BD0_1 = z;
	}
	if (g_rva008B2BD0_2 != z)
	{
		g_rva008B2BD0_2->release();
		g_rva008B2BD0_2 = z;
	}
	if (g_rva008B2BD0_3 != z)
	{
		g_rva008B2BD0_3->release();
		g_rva008B2BD0_3 = z;
	}
	if (g_rva008B2BD0_4 != z)
	{
		g_rva008B2BD0_4->release();
		g_rva008B2BD0_4 = z;
	}
	if (g_rva008B2BD0_5 != z)
	{
		g_rva008B2BD0_5->release();
		g_rva008B2BD0_5 = z;
	}
}
