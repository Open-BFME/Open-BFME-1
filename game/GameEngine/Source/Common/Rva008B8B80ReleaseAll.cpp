// Open-BFME5 conversion.

class Rva008B8B80Releasable
{
public:
	virtual void unused(void) = 0;
	virtual void release(void) = 0;
};

extern Rva008B8B80Releasable *g_rva008B8B80_0;
extern Rva008B8B80Releasable *g_rva008B8B80_1;
extern Rva008B8B80Releasable *g_rva008B8B80_2;
extern Rva008B8B80Releasable *g_rva008B8B80_3;
extern Rva008B8B80Releasable *g_rva008B8B80_4;
extern Rva008B8B80Releasable *g_rva008B8B80_5;
extern Rva008B8B80Releasable *g_rva008B8B80_6;
extern Rva008B8B80Releasable *g_rva008B8B80_7;
extern Rva008B8B80Releasable *g_rva008B8B80_8;
extern Rva008B8B80Releasable *g_rva008B8B80_9;
extern Rva008B8B80Releasable *g_rva008B8B80_10;

void rva008B8B80ReleaseAll(void)
{
	if (g_rva008B8B80_0 != 0)
	{
		g_rva008B8B80_0->release();
		g_rva008B8B80_0 = 0;
	}
	if (g_rva008B8B80_1 != 0)
	{
		g_rva008B8B80_1->release();
		g_rva008B8B80_1 = 0;
	}
	if (g_rva008B8B80_2 != 0)
	{
		g_rva008B8B80_2->release();
		g_rva008B8B80_2 = 0;
	}
	if (g_rva008B8B80_3 != 0)
	{
		g_rva008B8B80_3->release();
		g_rva008B8B80_3 = 0;
	}
	if (g_rva008B8B80_4 != 0)
	{
		g_rva008B8B80_4->release();
		g_rva008B8B80_4 = 0;
	}
	if (g_rva008B8B80_5 != 0)
	{
		g_rva008B8B80_5->release();
		g_rva008B8B80_5 = 0;
	}
	if (g_rva008B8B80_6 != 0)
	{
		g_rva008B8B80_6->release();
		g_rva008B8B80_6 = 0;
	}
	if (g_rva008B8B80_7 != 0)
	{
		g_rva008B8B80_7->release();
		g_rva008B8B80_7 = 0;
	}
	if (g_rva008B8B80_8 != 0)
	{
		g_rva008B8B80_8->release();
		g_rva008B8B80_8 = 0;
	}
	if (g_rva008B8B80_9 != 0)
	{
		g_rva008B8B80_9->release();
		g_rva008B8B80_9 = 0;
	}
	if (g_rva008B8B80_10 != 0)
	{
		g_rva008B8B80_10->release();
		g_rva008B8B80_10 = 0;
	}
}
