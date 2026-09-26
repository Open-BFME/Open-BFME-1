class BfmeNodeEY
{
public:
	unsigned char m_bfmeHeadEY[0x14];
	int m_bfmeX0EY;
	int m_bfmeY0EY;
	int m_bfmeX1EY;
	int m_bfmeY1EY;
};

class BfmeIterEY
{
public:
	BfmeIterEY();

	BfmeNodeEY *m_bfmeNodeEY;
};

class BfmeMapEY
{
public:
	BfmeIterEY bfmeFindEY(void *key) const;

	BfmeNodeEY *m_bfmeEndEY;
};

class BfmeVec2EY
{
public:
	float m_bfmeXEY;
	float m_bfmeYEY;
};

class BfmeHostEY
{
public:
	char bfmeLookupEY(void *key, BfmeVec2EY *size, BfmeVec2EY *origin);
	void bfmeRefreshEY();

	unsigned char m_bfmeHeadEY[8];
	BfmeMapEY m_bfmeMapEY;
	unsigned char m_bfmeGapEY[0x10];
	unsigned char m_bfmeDirtyEY;
	unsigned char m_bfmePadEY[3];
	float m_bfmeSxEY;
	float m_bfmeSyEY;
};

char BfmeHostEY::bfmeLookupEY(void *key, BfmeVec2EY *size, BfmeVec2EY *origin)
{
	BfmeIterEY it = m_bfmeMapEY.bfmeFindEY(key);
	BfmeNodeEY *n = it.m_bfmeNodeEY;

	if (n == m_bfmeMapEY.m_bfmeEndEY)
	{
		size->m_bfmeXEY = 1.0f;
		size->m_bfmeYEY = 1.0f;
		origin->m_bfmeXEY = 0.0f;
		origin->m_bfmeYEY = 0.0f;

		return 0;
	}

	if (m_bfmeDirtyEY)
		bfmeRefreshEY();

	origin->m_bfmeXEY = n->m_bfmeX0EY * m_bfmeSxEY;
	origin->m_bfmeYEY = n->m_bfmeY0EY * m_bfmeSyEY;

	size->m_bfmeXEY = (n->m_bfmeX1EY - n->m_bfmeX0EY) * m_bfmeSxEY;
	size->m_bfmeYEY = (n->m_bfmeY1EY - n->m_bfmeY0EY) * m_bfmeSyEY;

	return 1;
}
