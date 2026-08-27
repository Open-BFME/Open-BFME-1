// Another part asking its whole to act, a word remembered and passed on, and a
// check made before the last word is handed over.

struct BfmeOwnerCH
{
	unsigned char m_bfmeHead[0x258];	// 0x000
	unsigned char m_bfmeReady;		// 0x258
};

class BfmeSubCH
{
public:
	void bfmeGoCH(void);

	unsigned char m_bfmeHead[4];		// 0x0
};


class BfmeHostCH
{
public:
	virtual void bfmeSpare000CH(void) = 0;
	virtual void bfmeSpare001CH(void) = 0;
	virtual void bfmeSpare002CH(void) = 0;
	virtual void bfmeSpare003CH(void) = 0;
	virtual void bfmeSpare004CH(void) = 0;
	virtual void bfmeSpare005CH(void) = 0;
	virtual void bfmeSpare006CH(void) = 0;
	virtual void bfmeSpare007CH(void) = 0;
	virtual void bfmeSpare008CH(void) = 0;
	virtual void bfmeSpare009CH(void) = 0;
	virtual void bfmeSpare010CH(void) = 0;
	virtual void bfmeSpare011CH(void) = 0;
	virtual void bfmeSpare012CH(void) = 0;
	virtual void bfmeSpare013CH(void) = 0;
	virtual void bfmeSpare014CH(void) = 0;
	virtual void bfmeDoCH(void) = 0;

	BfmeOwnerCH *m_bfmeOwner;		// 0x004
	unsigned char m_bfmeGap[0xe0];		// 0x008
	BfmeSubCH m_bfmeSub;			// 0x0e8
};

void BfmeSubCH::bfmeGoCH(void)
{
	if (((const BfmeHostCH *)((const char *)this - 0xe8))->m_bfmeOwner->m_bfmeReady == 0)
		return;

	((BfmeHostCH *)((char *)this - 0xe8))->bfmeDoCH();
}

class BfmeTargetCF
{
public:
	virtual void bfmeSpare000CF(void) = 0;
	virtual void bfmeSpare001CF(void) = 0;
	virtual void bfmeSpare002CF(void) = 0;
	virtual void bfmeSpare003CF(void) = 0;
	virtual void bfmeSpare004CF(void) = 0;
	virtual void bfmeSpare005CF(void) = 0;
	virtual void bfmeSpare006CF(void) = 0;
	virtual void bfmeSpare007CF(void) = 0;
	virtual void bfmeSpare008CF(void) = 0;
	virtual void bfmeSpare009CF(void) = 0;
	virtual void bfmeSpare010CF(void) = 0;
	virtual void bfmeSpare011CF(void) = 0;
	virtual void bfmeSpare012CF(void) = 0;
	virtual void bfmeSpare013CF(void) = 0;
	virtual void bfmeSpare014CF(void) = 0;
	virtual void bfmeSpare015CF(void) = 0;
	virtual void bfmeSpare016CF(void) = 0;
	virtual void bfmeSpare017CF(void) = 0;
	virtual void bfmeSpare018CF(void) = 0;
	virtual void bfmeSpare019CF(void) = 0;
	virtual void bfmeDoCF(void *what) = 0;
};

class BfmeThingCF
{
public:
	void bfmeSendCF(void *what);

private:
	unsigned char m_bfmeHead[0x150];	// 0x000
	BfmeTargetCF **m_bfmeSlot;		// 0x150
	unsigned char m_bfmeGap[0x264];		// 0x154
	void *m_bfmeLast;			// 0x3b8
};

void BfmeThingCF::bfmeSendCF(void *what)
{
	if (what == 0)
		return;

	m_bfmeLast = what;

	BfmeTargetCF *target = *m_bfmeSlot;

	if (target == 0)
		return;

	target->bfmeDoCF(what);
}

class BfmeTargetCG
{
public:
	virtual void bfmeSpare000CG(void) = 0;
	virtual void bfmeSpare001CG(void) = 0;
	virtual int bfmeDoCG(void) = 0;
};

class BfmeThingCG
{
public:
	virtual void bfmeSpare000CI(void) = 0;
	virtual void bfmeSpare001CI(void) = 0;
	virtual void bfmeSpare002CI(void) = 0;
	virtual void bfmeSpare003CI(void) = 0;
	virtual void bfmeSpare004CI(void) = 0;
	virtual void bfmeSpare005CI(void) = 0;
	virtual void bfmeSpare006CI(void) = 0;
	virtual void bfmeSpare007CI(void) = 0;
	virtual void bfmeSpare008CI(void) = 0;
	virtual void bfmeSpare009CI(void) = 0;
	virtual unsigned char bfmeAskCG(void) = 0;
	virtual void bfmeFixCG(void) = 0;

	int bfmeGoCG(void);

private:
	unsigned char m_bfmeHead[0x10];		// 0x04
	BfmeTargetCG *m_bfmeTarget;		// 0x14
};

int BfmeThingCG::bfmeGoCG(void)
{
	if (bfmeAskCG() == 0)
		bfmeFixCG();

	if (m_bfmeTarget == 0)
		return 0;

	return m_bfmeTarget->bfmeDoCG();
}

