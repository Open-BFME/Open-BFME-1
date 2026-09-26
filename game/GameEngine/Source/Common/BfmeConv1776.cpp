class BfmeSubCX
{
public:
	int bfmeCheckCX(void *key);

	int m_bfmeDataCX;
};

class BfmeEntryCX
{
public:
	unsigned char m_bfmeHeadCX[8];
	BfmeSubCX m_bfmeSubCX;
	unsigned char m_bfmeTailCX[8];
};

class BfmeVecCX
{
public:
	int bfmeFindCX(void *key);

	int *m_bfmeBeginCX;
	int *m_bfmeEndCX;
	unsigned char m_bfmePadCX[4];
	BfmeEntryCX *m_bfmeEntriesCX;
};

class BfmeOwnCX
{
public:
	int bfmeLookupCX(void *key);

	unsigned char m_bfmeHeadCX[0x2c];
	BfmeVecCX m_bfmeVecCX;
};

int BfmeOwnCX::bfmeLookupCX(void *key)
{
	BfmeVecCX *vec = &m_bfmeVecCX;

	int index = vec->bfmeFindCX(key);

	if ((unsigned int)index < (unsigned int)(vec->m_bfmeEndCX - vec->m_bfmeBeginCX))
	{
		int id = vec->m_bfmeBeginCX[index];

		if (vec->m_bfmeEntriesCX[id].m_bfmeSubCX.bfmeCheckCX(key) == 0)
			return id;
	}

	return -1;
}
