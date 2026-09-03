// Open-BFME5 conversion.

class Rva008A98B0Releasable
{
public:
	virtual void unused(void) = 0;
	virtual void release(void) = 0;
};

extern Rva008A98B0Releasable *g_rva008A98B0_0;
extern Rva008A98B0Releasable *g_rva008A98B0_1;
extern Rva008A98B0Releasable *g_rva008A98B0_2;
extern Rva008A98B0Releasable *g_rva008A98B0_3;
extern Rva008A98B0Releasable *g_rva008A98B0_4;
extern Rva008A98B0Releasable *g_rva008A98B0_5;
extern Rva008A98B0Releasable *g_rva008A98B0_6;
extern Rva008A98B0Releasable *g_rva008A98B0_7;
extern Rva008A98B0Releasable *g_rva008A98B0_8;
extern Rva008A98B0Releasable *g_rva008A98B0_9;
extern Rva008A98B0Releasable *g_rva008A98B0_10;
extern Rva008A98B0Releasable *g_rva008A98B0_11;

void rva008A98B0ReleaseAll(void)
{
	if (g_rva008A98B0_0 != 0)
	{
		g_rva008A98B0_0->release();
		g_rva008A98B0_0 = 0;
	}
	if (g_rva008A98B0_1 != 0)
	{
		g_rva008A98B0_1->release();
		g_rva008A98B0_1 = 0;
	}
	if (g_rva008A98B0_2 != 0)
	{
		g_rva008A98B0_2->release();
		g_rva008A98B0_2 = 0;
	}
	if (g_rva008A98B0_3 != 0)
	{
		g_rva008A98B0_3->release();
		g_rva008A98B0_3 = 0;
	}
	if (g_rva008A98B0_4 != 0)
	{
		g_rva008A98B0_4->release();
		g_rva008A98B0_4 = 0;
	}
	if (g_rva008A98B0_5 != 0)
	{
		g_rva008A98B0_5->release();
		g_rva008A98B0_5 = 0;
	}
	if (g_rva008A98B0_6 != 0)
	{
		g_rva008A98B0_6->release();
		g_rva008A98B0_6 = 0;
	}
	if (g_rva008A98B0_7 != 0)
	{
		g_rva008A98B0_7->release();
		g_rva008A98B0_7 = 0;
	}
	if (g_rva008A98B0_8 != 0)
	{
		g_rva008A98B0_8->release();
		g_rva008A98B0_8 = 0;
	}
	if (g_rva008A98B0_9 != 0)
	{
		g_rva008A98B0_9->release();
		g_rva008A98B0_9 = 0;
	}
	if (g_rva008A98B0_10 != 0)
	{
		g_rva008A98B0_10->release();
		g_rva008A98B0_10 = 0;
	}
	if (g_rva008A98B0_11 != 0)
	{
		g_rva008A98B0_11->release();
		g_rva008A98B0_11 = 0;
	}
}
