class BfmeObjAS
{
public:
	void bfmeClearAS(int what);
	BfmeObjAS *bfmeParentAS(int which);
};

struct Rva00367E30Logic
{
	BfmeObjAS *bfmeFindAS(int id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeHostAS
{
public:
	void bfmeResetAS(void *a, void *b);
	void bfmeFinishAS(void *a, void *b);

	unsigned char m_bfmeHeadAS[0xac];
	int m_bfmeIdAS;
};

void BfmeHostAS::bfmeResetAS(void *a, void *b)
{
	int id = m_bfmeIdAS;

	if (id != 0)
	{
		BfmeObjAS *o = TheBfmeGameLogic->bfmeFindAS(id);

		if (o != 0)
		{
			o->bfmeClearAS(0x41);

			BfmeObjAS *p = o->bfmeParentAS(0);

			if (p != 0)
				p->bfmeClearAS(0x41);
		}

		m_bfmeIdAS = 0;
	}

	bfmeFinishAS(a, b);
}
