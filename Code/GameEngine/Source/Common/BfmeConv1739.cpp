class BfmeTargetAM
{
public:
	virtual void bfmeSlot00AM(void);
	virtual void bfmeSlot01AM(void);
	virtual void bfmeSlot02AM(void);
	virtual void bfmeSlot03AM(void);
	virtual void bfmeSlot04AM(void);
	virtual void bfmeSlot05AM(void);
	virtual bool bfmeTestAM(void *value);
};

class BfmeOwnAM
{
public:
	bool bfmeCheckAM(void *value);

	unsigned char m_bfmeHeadAM[8];
	BfmeTargetAM *m_bfmeTargetAM;
	char m_bfmeInvertAM;
};

bool BfmeOwnAM::bfmeCheckAM(void *value)
{
	if (m_bfmeTargetAM == 0)
		return 1;

	if (m_bfmeInvertAM)
		return m_bfmeTargetAM->bfmeTestAM(value);

	return !m_bfmeTargetAM->bfmeTestAM(value);
}
