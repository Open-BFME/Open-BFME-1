struct BfmeRecord6BE90
{
	unsigned char m_bfmeBodyAAJ[0xbc];
};

class BfmeRecordHook6BE90
{
public:
	void bfmeSelect6BE90(BfmeRecord6BE90 *rec, int a, int b);
};

struct BfmeOwnerAAJ
{
	unsigned char m_bfmeHeadAAJ[0x24];
	BfmeRecord6BE90 *m_bfmeBeginAAJ;
	BfmeRecord6BE90 *m_bfmeEndAAJ;
};

class BfmeViewAAJ
{
public:
	void bfmePrevAAJ();

	unsigned char m_bfmeHeadVAAJ[8];
	BfmeRecord6BE90 *m_bfme08AAJ;
	unsigned char m_bfmeGapAAJ[0x224 - 0xc];
	char m_bfme224AAJ;
};

void BfmeViewAAJ::bfmePrevAAJ()
{
	BfmeOwnerAAJ *o = *(BfmeOwnerAAJ **)((char *)this - 8);
	BfmeRecord6BE90 *prev = 0;
	BfmeRecord6BE90 *p = o->m_bfmeBeginAAJ;
	BfmeRecord6BE90 *e = o->m_bfmeEndAAJ;

	if (p == e)
		return;

	BfmeRecord6BE90 *target = m_bfme08AAJ;

	do
	{
		if (p == target)
		{
			if (prev != 0)
			{
				m_bfme224AAJ = 1;
				((BfmeRecordHook6BE90 *)((char *)this - 0xc))->bfmeSelect6BE90(prev, 1, 0);
			}

			return;
		}

		prev = p;
		++p;
	}
	while (p != e);
}
