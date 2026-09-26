class BfmeThingERU
{
public:
	void bfmeStartERU();
	void bfmeStopERU();
};

BfmeThingERU *bfmeDefaultERU();

class BfmeHandleERU
{
public:
	~BfmeHandleERU() throw();

	BfmeThingERU *m_bfmePtrERU;
	unsigned char m_bfmeTailERU[8];
};

class BfmeMgrERU
{
public:
	BfmeHandleERU bfmeGetERU(int id);
};

extern BfmeMgrERU *g_bfmeMgrERU;

class BfmeHostERU
{
public:
	void bfmeClearERU();

	unsigned char m_bfmeHeadERU[4];
	int m_bfmeIdERU;
	char m_bfmeActiveERU;
};

void BfmeHostERU::bfmeClearERU()
{
	int id = m_bfmeIdERU;

	if (id != 0 && m_bfmeActiveERU != 0)
	{
		BfmeHandleERU handle = g_bfmeMgrERU->bfmeGetERU(id);

		if (handle.m_bfmePtrERU != 0)
		{
			handle.m_bfmePtrERU->bfmeStartERU();

			BfmeThingERU *thing = handle.m_bfmePtrERU;

			if (thing == 0)
				thing = bfmeDefaultERU();

			thing->bfmeStopERU();
		}
	}

	m_bfmeIdERU = 0;
}
