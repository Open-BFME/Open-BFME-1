class BfmeItemAH
{
public:
	virtual void bfmeI00AH();
	virtual void bfmeI01AH();
	virtual void bfmeI02AH();
	virtual void bfmeI03AH();
	virtual void bfmeI04AH();
	virtual void bfmeI05AH();
	virtual void bfmeI06AH();
	virtual void bfmeI07AH();
	virtual void bfmeI08AH();
	virtual void bfmeI09AH();
	virtual void bfmeI10AH();
	virtual void bfmeI11AH();
	virtual void bfmeI12AH();
	virtual void bfmeI13AH();
	virtual void bfmeI14AH();
	virtual void bfmeI15AH();
	virtual void bfmeDetachAH();
};

class BfmeNodeAH
{
public:
	virtual void bfmeDeleteAH(int flags);

	BfmeItemAH *m_bfmeItemAH;
	BfmeNodeAH *m_bfmeNextAH;
};

class BfmeGhostAH
{
public:
	unsigned char m_bfmeHeadAH[4];
	int m_bfmeIndexAH;
};

extern BfmeGhostAH *TheBfmeGhostAH;

class BfmeOwnerAH
{
public:
	void bfmeClearAH();

	void bfmeFinishAH();

	unsigned char m_bfmeHeadAH[0xc];
	void *m_bfmeFlagAH;
	unsigned char m_bfmeMidAH[0x70];
	BfmeNodeAH *m_bfmeListsAH[1];
};

void BfmeOwnerAH::bfmeClearAH()
{
	int index = TheBfmeGhostAH->m_bfmeIndexAH;
	BfmeNodeAH *node = m_bfmeListsAH[index];

	if (node == 0)
		return;

	do
	{
		node->m_bfmeItemAH->bfmeDetachAH();
		node = node->m_bfmeNextAH;
	}
	while (node != 0);

	if (m_bfmeFlagAH != 0)
		bfmeFinishAH();

	BfmeNodeAH *p = m_bfmeListsAH[index];

	while (p != 0)
	{
		BfmeNodeAH *next = p->m_bfmeNextAH;

		p->bfmeDeleteAH(1);

		p = next;
	}

	m_bfmeListsAH[index] = 0;
}
