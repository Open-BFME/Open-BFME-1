class BfmeSubCW
{
public:
	int bfmeCheckCW(void *key);

	int m_bfmeDataCW;
};

class BfmeEntryCW
{
public:
	unsigned char m_bfmeHeadCW[8];
	BfmeSubCW m_bfmeSubCW;
	unsigned char m_bfmeTailCW[8];
};

class BfmeVecCW
{
public:
	int bfmeFindCW(void *key);

	int *m_bfmeBeginCW;
	int *m_bfmeEndCW;
	unsigned char m_bfmePadCW[4];
	BfmeEntryCW *m_bfmeEntriesCW;
};

class BfmeOwnCW
{
public:
	int bfmeLookupCW(void *key);

	unsigned char m_bfmeHeadCW[0xc];
	BfmeVecCW m_bfmeVecCW;
};

int BfmeOwnCW::bfmeLookupCW(void *key)
{
	BfmeVecCW *vec = &m_bfmeVecCW;

	int index = vec->bfmeFindCW(key);

	if ((unsigned int)index < (unsigned int)(vec->m_bfmeEndCW - vec->m_bfmeBeginCW))
	{
		int id = vec->m_bfmeBeginCW[index];

		if (vec->m_bfmeEntriesCW[id].m_bfmeSubCW.bfmeCheckCW(key) == 0)
			return id;
	}

	return -1;
}
