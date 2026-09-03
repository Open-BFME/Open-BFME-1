// Open-BFME5: BfmeThingHB::bfmeClearHB, retail 0x003C6120.

class BfmeTargetHB
{
public:
	virtual void release(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2C(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3C(void);
	virtual void stop(void);

	int m_refCount;
};

class BfmeThingHB
{
public:
	void bfmeClearHB(void);

private:
	char m_pad00[4];
	BfmeTargetHB *m_targetAt04;
	char m_pad08[0x1C];
	BfmeTargetHB *m_targetAt24;
};

inline void releaseTargetHB(BfmeTargetHB *&target)
{
	BfmeTargetHB *p = target;
	if (p != 0)
	{
		p->stop();
		--p->m_refCount;
		if (p->m_refCount == 0)
			p->release();
			target = 0;
	}
}

// ?bfmeClearHB@BfmeThingHB@@QAEXXZ
void BfmeThingHB::bfmeClearHB(void)
{
	if (m_targetAt24 != 0)
	{
		releaseTargetHB(m_targetAt24);
	}

	m_targetAt24 = 0;
	m_targetAt04 = 0;
}
