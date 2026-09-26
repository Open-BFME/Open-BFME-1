class BfmeResBO
{
public:
	void bfmeUseBO(void *arg);
};

class BfmeSubBO
{
public:
	virtual void bfmeSlot00S();
	virtual void bfmeSlot01S();
	virtual void bfmeSlot02S();
	virtual void bfmeSlot03S();
	virtual void bfmeSlot04S();
	virtual void bfmeSlot05S();
	virtual void bfmeSlot06S();
	virtual void bfmeSlot07S();
	virtual void bfmeSlot08S();
	virtual void bfmeSlot09S();
	virtual void bfmeSlot10S();
	virtual void bfmeSlot11S();
	virtual void bfmeSlot12S();
	virtual void bfmeSlot13S();
	virtual void bfmeSlot14S();
	virtual void bfmeSlot15S();
	virtual void bfmeSlot16S();
	virtual void bfmeSlot17S();
	virtual void bfmeStartBO(int mode);
};

class BfmePeerBO
{
public:
	virtual void bfmeSlot00P();
	virtual void bfmeSlot01P();
	virtual void bfmeSlot02P();
	virtual void bfmeSlot03P();
	virtual void bfmeSlot04P();
	virtual void bfmeSlot05P();
	virtual void bfmeSlot06P();
	virtual void bfmeSlot07P();
	virtual void bfmeSlot08P();
	virtual void bfmeSlot09P();
	virtual BfmeResBO *bfmeGetBO();

	void bfmeFeedBO(void *first, void *second);
};

class BfmeHostBO
{
public:
	virtual void bfmeSlot00H();
	virtual void bfmeSlot01H();
	virtual void bfmeSlot02H();
	virtual void bfmeSlot03H();
	virtual void bfmeSlot04H();
	virtual void bfmeSlot05H();
	virtual void bfmeSlot06H();
	virtual void bfmeSlot07H();
	virtual void bfmeSlot08H();
	virtual void bfmeSlot09H();
	virtual void bfmeFinishBO();

	void bfmeRunBO();

	unsigned char m_bfmeHeadBO[0x1c];
	void *m_bfmeABO;
	void *m_bfmeBBO;
};

void BfmeHostBO::bfmeRunBO()
{
	if ((*(BfmePeerBO **)((char *)this - 8))->bfmeGetBO() == 0)
		return;

	BfmeSubBO *s = (BfmeSubBO *)((char *)this - 0x10);

	for (int i = 0; i < 3; i++)
	{
		s->bfmeStartBO(1);
		(*(BfmePeerBO **)((char *)this - 8))->bfmeFeedBO(m_bfmeABO, m_bfmeBBO);
		(*(BfmePeerBO **)((char *)this - 8))->bfmeGetBO()->bfmeUseBO(0);
	}

	bfmeFinishBO();
}
