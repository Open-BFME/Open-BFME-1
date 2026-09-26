class BfmeEntryBV
{
public:
	unsigned char m_bfmeHeadBV[8];
	void *m_bfmeKeyBV;
	int m_bfmeKindBV;
	unsigned short m_bfmeIdBV;
	unsigned char m_bfmePadBV[2];
	int m_bfmeTagBV;
};

class BfmeNodeBV
{
public:
	BfmeEntryBV *m_bfmeEntryBV;
	BfmeNodeBV *m_bfmeNextBV;
};

char __cdecl bfmeAllowBV(int tag);

class BfmeOwnBV
{
public:
	BfmeNodeBV *bfmeFindBV(unsigned short id, unsigned char kind, void *key);

	unsigned char m_bfmeHeadBV[4];
	BfmeNodeBV *m_bfmeListBV;
};

BfmeNodeBV *BfmeOwnBV::bfmeFindBV(unsigned short id, unsigned char kind, void *key)
{
	for (BfmeNodeBV *node = m_bfmeListBV; node != 0; node = node->m_bfmeNextBV)
	{
		int tag = node->m_bfmeEntryBV->m_bfmeTagBV;

		if (!bfmeAllowBV(tag))
			continue;

		if (node->m_bfmeEntryBV->m_bfmeIdBV != id)
			continue;

		if (node->m_bfmeEntryBV->m_bfmeKindBV != kind)
			continue;

		if (node->m_bfmeEntryBV->m_bfmeKeyBV == key)
			return node;
	}

	return 0;
}
