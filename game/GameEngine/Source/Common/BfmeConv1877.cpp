class BfmeTargetZJ
{
public:
	virtual void bfmeT0ZJ();
	virtual void bfmeT1ZJ();
	virtual void bfmeDoneZJ(int how);
};

class BfmeHostZJ
{
public:
	BfmeTargetZJ *bfmeTopZJ();

	unsigned char m_bfmeHeadZJ[0x204];
	void *m_bfmeThingZJ;
};

class BfmeBaseZJ
{
public:
	void bfmeStopZJ();
	void bfmeClearZJ();

	unsigned char m_bfmeHeadZJ[8];
	BfmeHostZJ *m_bfmeHostZJ;
};

class BfmeOwnerZJ
{
public:
	virtual void bfmeV0ZJ();
	virtual void bfmeV1ZJ();
	virtual void bfmeV2ZJ();
	virtual void bfmeV3ZJ();
	virtual void bfmeV4ZJ();
	virtual void bfmeV5ZJ();
	virtual void bfmeV6ZJ();
	virtual void bfmeV7ZJ();
	virtual void bfmeHideZJ(int how);

	void bfmeCloseZJ();
};

void BfmeOwnerZJ::bfmeCloseZJ()
{
	bfmeHideZJ(0);

	((BfmeBaseZJ *)((char *)this - 0x10))->bfmeStopZJ();
	((BfmeBaseZJ *)((char *)this - 0x10))->bfmeClearZJ();

	BfmeHostZJ *host = ((BfmeBaseZJ *)((char *)this - 0x10))->m_bfmeHostZJ;

	if (host->m_bfmeThingZJ != 0)
	{
		BfmeTargetZJ *target = host->bfmeTopZJ();

		if (target != 0)
			target->bfmeDoneZJ(0);
	}
}
