class BfmeStateERI
{
public:
	unsigned char m_bfmeHeadERI[0xcc];
	unsigned char m_bfmeFlagsERI;
};

class BfmeBERI
{
public:
	BfmeStateERI *bfmeStateERI();
};

class BfmeAERI
{
public:
	unsigned char m_bfmeHeadERI[4];
	BfmeBERI *m_bfmeBERI;
};

class BfmeModuleERI
{
public:
	void bfmeSetERI(int mode, int flag);
};

class BfmeThingERI
{
public:
	BfmeModuleERI *bfmeFindERI(int key);

	unsigned char m_bfmeHeadERI[4];
	BfmeAERI *m_bfmeAERI;
};

class BfmeNodeERI
{
public:
	BfmeNodeERI *m_bfmeNextERI;
	unsigned char m_bfmeMidERI[4];
	BfmeThingERI *m_bfmeThingERI;
};

class BfmeKeyGenERI
{
public:
	int bfmeNameToKeyERI(const char *name);
};

extern BfmeKeyGenERI *g_bfmeKeyGenERI;

class BfmeHostERI
{
public:
	void bfmeSweepERI();

	unsigned char m_bfmeHeadERI[0x99c];
	BfmeNodeERI *m_bfmeListERI;
};

void BfmeHostERI::bfmeSweepERI()
{
	BfmeNodeERI *n = m_bfmeListERI->m_bfmeNextERI;

	while (n != m_bfmeListERI)
	{
		BfmeThingERI *thing = n->m_bfmeThingERI;

		n = n->m_bfmeNextERI;
		BfmeAERI *a = thing->m_bfmeAERI;
		BfmeStateERI *st = (BfmeStateERI *)a;

		if (a != 0)
		{
			BfmeBERI *b = a->m_bfmeBERI;

			if (b != 0)
				st = b->bfmeStateERI();
		}

		if ((st->m_bfmeFlagsERI & 2) == 0)
			continue;

		static int s_bfmeKeyERI =
			g_bfmeKeyGenERI->bfmeNameToKeyERI("StealthUpdate");

		BfmeModuleERI *mod = thing->bfmeFindERI(s_bfmeKeyERI);

		if (mod != 0)
			mod->bfmeSetERI(0, 1);
	}
}
