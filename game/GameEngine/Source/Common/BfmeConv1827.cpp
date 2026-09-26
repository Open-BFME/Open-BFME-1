struct BfmeItemNM
{
	unsigned char m_bfmeRawNM[60];
};

struct BfmeVecNM
{
	BfmeItemNM *m_bfmeBeginNM;
	BfmeItemNM *m_bfmeEndNM;
	BfmeItemNM *m_bfmeCapNM;
};

class BfmeHolderNM
{
public:
	unsigned char m_bfmeHeadNM[0x7c];
	BfmeVecNM m_bfmeListsNM[4];
	unsigned char m_bfmeFlagsNM;
};

class BfmeOwnerNM
{
public:
	int bfmeCountNM(int index);

	unsigned char m_bfmeHeadNM[8];
	BfmeHolderNM *m_bfmeMainNM;
	unsigned char m_bfmeGapNM[0x15b];
	char m_bfmeFlagNM;
	BfmeHolderNM *m_bfmeAltNM;
};

int BfmeOwnerNM::bfmeCountNM(int index)
{
	BfmeHolderNM *holder = m_bfmeFlagNM ? m_bfmeAltNM : m_bfmeMainNM;

	if (holder != 0)
	{
		if (holder->m_bfmeFlagsNM & 8)
		{
			BfmeVecNM *vec = &holder->m_bfmeListsNM[index];

			return vec->m_bfmeEndNM - vec->m_bfmeBeginNM;
		}
	}

	return 0;
}
