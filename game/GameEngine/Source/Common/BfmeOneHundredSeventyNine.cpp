// A question with two short answers of its own, and a piece of tidying that
// only sometimes needs handing on.

class BfmeOwnerCC
{
public:
	virtual void bfmeSpare000CC(void) = 0;
	virtual void bfmeSpare001CC(void) = 0;
	virtual void bfmeSpare002CC(void) = 0;
	virtual void bfmeSpare003CC(void) = 0;
	virtual int bfmeDoCC(void) = 0;

	unsigned char m_bfmeGap[0x18];		// 0x04
	struct BfmeJobCC *m_bfmeJob;		// 0x1c
};

struct BfmeJobCC
{
	unsigned char m_bfmeHead[4];		// 0x0
	int m_bfmeWhen;				// 0x4
};

class BfmeThingCC
{
public:
	int bfmeAskCC(void);

private:
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeOwnerCC *m_bfmeOwner;		// 0x24
};

int BfmeThingCC::bfmeAskCC(void)
{
	BfmeOwnerCC *owner = m_bfmeOwner;

	if (owner == 0)
		return -2;

	BfmeJobCC *job = owner->m_bfmeJob;

	if (job != 0 && job->m_bfmeWhen == 0xF423E)
		return -1;

	return m_bfmeOwner->bfmeDoCC();
}
