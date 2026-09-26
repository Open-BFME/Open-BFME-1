class BfmeSubZB
{
public:
	virtual char bfmeReadyZB();
	virtual void bfmeS1ZB();
	virtual void bfmeS2ZB();
	virtual void bfmeS3ZB();
	virtual void bfmeS4ZB();
	virtual void bfmeS5ZB();
	virtual void bfmeS6ZB();
	virtual void bfmeS7ZB();
	virtual void bfmeFinishZB(int how);
};

class BfmeTargetZB
{
public:
	void bfmeSetZB(unsigned char kind);
};

class BfmeHolderZB
{
public:
	BfmeTargetZB *bfmeGetZB();

	unsigned char m_bfmeHeadZB[0x1a4];
	int m_bfmeBusyZB;
};

class BfmeInfoZB
{
public:
	unsigned char m_bfmeHeadZB[0x70];
	unsigned char m_bfmeKindZB;
};

class BfmeOwnerZB
{
public:
	void bfmeStepZB();

	unsigned char m_bfmeStartZB[4];
	BfmeInfoZB *m_bfmeInfoZB;
	BfmeHolderZB *m_bfmeHolderZB;
	unsigned char m_bfmePadZB[4];
	BfmeSubZB m_bfmeSubZB;
};

void BfmeOwnerZB::bfmeStepZB()
{
	BfmeInfoZB *info = m_bfmeInfoZB;

	if (m_bfmeSubZB.bfmeReadyZB() == 0)
		return;

	if (m_bfmeHolderZB->m_bfmeBusyZB != 0)
		return;

	BfmeTargetZB *target = m_bfmeHolderZB->bfmeGetZB();

	if (target != 0)
		target->bfmeSetZB(info->m_bfmeKindZB);

	m_bfmeSubZB.bfmeFinishZB(0);
}
