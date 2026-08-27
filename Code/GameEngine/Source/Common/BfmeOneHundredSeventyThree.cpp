// Four questions passed straight on to whatever is holding the answer, each
// stopping short and giving a plain reply when there is nothing to ask.

class BfmeTargetBC
{
public:
	virtual void bfmeSpare00BC(void) = 0;
	virtual void bfmeSpare01BC(void) = 0;
	virtual void bfmeSpare02BC(void) = 0;
	virtual void bfmeSpare03BC(void) = 0;
	virtual void bfmeSpare04BC(void) = 0;
	virtual void bfmeSpare05BC(void) = 0;
	virtual void bfmeSpare06BC(void) = 0;
	virtual void bfmeSpare07BC(void) = 0;
	virtual void bfmeSpare08BC(void) = 0;
	virtual void bfmeSpare09BC(void) = 0;
	virtual void bfmeSpare10BC(void) = 0;
	virtual void bfmeSpare11BC(void) = 0;
	virtual void bfmeSpare12BC(void) = 0;
	virtual void bfmeSpare13BC(void) = 0;
	virtual unsigned char bfmeDoBC(void) = 0;
};

struct BfmeHolderBC
{
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeTargetBC *m_bfmeTarget;		// 0x1c
};

class BfmeThingBC
{
public:
	unsigned char bfmeAskBC(void);

private:
	unsigned char m_bfmeHead[0x30];		// 0x00
	BfmeHolderBC *m_bfmeHolder;		// 0x30
};

unsigned char BfmeThingBC::bfmeAskBC(void)
{
	BfmeHolderBC *holder = m_bfmeHolder;

	if (holder != 0 && holder->m_bfmeTarget != 0)
		return holder->m_bfmeTarget->bfmeDoBC();

	return 0;
}

class BfmeTargetBD
{
public:
	virtual void bfmeSpare00BD(void) = 0;
	virtual void bfmeSpare01BD(void) = 0;
	virtual void bfmeSpare02BD(void) = 0;
	virtual void bfmeSpare03BD(void) = 0;
	virtual void bfmeSpare04BD(void) = 0;
	virtual void bfmeSpare05BD(void) = 0;
	virtual void bfmeSpare06BD(void) = 0;
	virtual unsigned char bfmeDoBD(void) = 0;
};

struct BfmeHolderBD
{
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeTargetBD *m_bfmeTarget;		// 0x1c
};

class BfmeThingBD
{
public:
	unsigned char bfmeAskBD(void);

private:
	unsigned char m_bfmeHead[0x28];		// 0x00
	BfmeHolderBD *m_bfmeHolder;		// 0x28
};

unsigned char BfmeThingBD::bfmeAskBD(void)
{
	BfmeHolderBD *holder = m_bfmeHolder;

	if (holder != 0)
	{
		if (holder->m_bfmeTarget != 0)
			return holder->m_bfmeTarget->bfmeDoBD();

		return 1;
	}

	return 0;
}

class BfmeTargetBE
{
public:
	virtual void bfmeSpare00BE(void) = 0;
	virtual void bfmeSpare01BE(void) = 0;
	virtual void bfmeDoBE(void *what) = 0;
};

class BfmeThingBE
{
public:
	void bfmeSendBE(void *what);

private:
	unsigned char m_bfmeHead[0x74];		// 0x00
	BfmeTargetBE *m_bfmeTarget;		// 0x74
};

void BfmeThingBE::bfmeSendBE(void *what)
{
	if (m_bfmeTarget == 0)
		return;

	if (what == 0)
		return;

	m_bfmeTarget->bfmeDoBE(what);
}

