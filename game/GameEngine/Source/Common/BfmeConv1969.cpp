class BfmeStateESE
{
public:
	virtual void bfmeSlot00ESE();
	virtual void bfmeSlot01ESE();
	virtual void bfmeSlot02ESE();
	virtual void bfmeSlot03ESE();
	virtual void bfmeSlot04ESE();
	virtual float bfmeSlot05ESE();
};

extern float g_bfmeDefaultESE;

class BfmeThingESE
{
public:
	unsigned char m_bfmeHeadESE[0x74];
	int m_bfme74ESE;
	unsigned char m_bfmeMidESE[0x188];
	BfmeStateESE *m_bfmeStateESE;
};

class BfmeActionsESE
{
public:
	char bfmeCheckESE(void *owner, BfmeThingESE *thing, void *ctx);
};

extern BfmeActionsESE *g_bfmeActionsESE;

class BfmeHostESE
{
public:
	void bfmeStepESE(BfmeThingESE *thing, void *ctx);
	void bfmeDoAESE(BfmeThingESE *thing, void *ctx);
	void bfmeDoBESE(BfmeThingESE *thing, void *ctx);

	unsigned char m_bfmeHeadESE[8];
	void *m_bfme08ESE;
	unsigned char m_bfmeMidESE[0x340];
	int m_bfme34cESE;
};

void BfmeHostESE::bfmeStepESE(BfmeThingESE *thing, void *ctx)
{
	BfmeStateESE *state = thing->m_bfmeStateESE;

	if (state != 0 && state->bfmeSlot05ESE() < g_bfmeDefaultESE)
	{
		void *owner = m_bfme08ESE;

		if (g_bfmeActionsESE->bfmeCheckESE(owner, thing, ctx))
		{
			m_bfme34cESE = thing->m_bfme74ESE;

			bfmeDoAESE(thing, ctx);
		}
	}

	if (m_bfme34cESE == 0)
		bfmeDoBESE(thing, ctx);
}
