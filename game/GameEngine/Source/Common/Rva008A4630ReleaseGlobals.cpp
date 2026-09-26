// cl: /O2 /DNDEBUG /MD

// Open-BFME7: release the eighteen ref-counted globals at 0x01337A34 through
// 0x01337A78 through virtual slot +4, then clear each slot.

class Rva008A4630Item
{
public:
	virtual void unused0();
	virtual void release();
};

extern Rva008A4630Item *g_rva008A4630_0;
extern Rva008A4630Item *g_rva008A4630_1;
extern Rva008A4630Item *g_rva008A4630_2;
extern Rva008A4630Item *g_rva008A4630_3;
extern Rva008A4630Item *g_rva008A4630_4;
extern Rva008A4630Item *g_rva008A4630_5;
extern Rva008A4630Item *g_rva008A4630_6;
extern Rva008A4630Item *g_rva008A4630_7;
extern Rva008A4630Item *g_rva008A4630_8;
extern Rva008A4630Item *g_rva008A4630_9;
extern Rva008A4630Item *g_rva008A4630_10;
extern Rva008A4630Item *g_rva008A4630_11;
extern Rva008A4630Item *g_rva008A4630_12;
extern Rva008A4630Item *g_rva008A4630_13;
extern Rva008A4630Item *g_rva008A4630_14;
extern Rva008A4630Item *g_rva008A4630_15;
extern Rva008A4630Item *g_rva008A4630_16;
extern Rva008A4630Item *g_rva008A4630_17;

void rva008A4630ReleaseGlobals()
{
	Rva008A4630Item *z = 0;
	if (g_rva008A4630_0 != z)
	{
		g_rva008A4630_0->release();
		g_rva008A4630_0 = z;
	}
	if (g_rva008A4630_1 != z)
	{
		g_rva008A4630_1->release();
		g_rva008A4630_1 = z;
	}
	if (g_rva008A4630_2 != z)
	{
		g_rva008A4630_2->release();
		g_rva008A4630_2 = z;
	}
	if (g_rva008A4630_3 != z)
	{
		g_rva008A4630_3->release();
		g_rva008A4630_3 = z;
	}
	if (g_rva008A4630_4 != z)
	{
		g_rva008A4630_4->release();
		g_rva008A4630_4 = z;
	}
	if (g_rva008A4630_5 != z)
	{
		g_rva008A4630_5->release();
		g_rva008A4630_5 = z;
	}
	if (g_rva008A4630_6 != z)
	{
		g_rva008A4630_6->release();
		g_rva008A4630_6 = z;
	}
	if (g_rva008A4630_7 != z)
	{
		g_rva008A4630_7->release();
		g_rva008A4630_7 = z;
	}
	if (g_rva008A4630_8 != z)
	{
		g_rva008A4630_8->release();
		g_rva008A4630_8 = z;
	}
	if (g_rva008A4630_9 != z)
	{
		g_rva008A4630_9->release();
		g_rva008A4630_9 = z;
	}
	if (g_rva008A4630_10 != z)
	{
		g_rva008A4630_10->release();
		g_rva008A4630_10 = z;
	}
	if (g_rva008A4630_11 != z)
	{
		g_rva008A4630_11->release();
		g_rva008A4630_11 = z;
	}
	if (g_rva008A4630_12 != z)
	{
		g_rva008A4630_12->release();
		g_rva008A4630_12 = z;
	}
	if (g_rva008A4630_13 != z)
	{
		g_rva008A4630_13->release();
		g_rva008A4630_13 = z;
	}
	if (g_rva008A4630_14 != z)
	{
		g_rva008A4630_14->release();
		g_rva008A4630_14 = z;
	}
	if (g_rva008A4630_15 != z)
	{
		g_rva008A4630_15->release();
		g_rva008A4630_15 = z;
	}
	if (g_rva008A4630_16 != z)
	{
		g_rva008A4630_16->release();
		g_rva008A4630_16 = z;
	}
	if (g_rva008A4630_17 != z)
	{
		g_rva008A4630_17->release();
		g_rva008A4630_17 = z;
	}
}
