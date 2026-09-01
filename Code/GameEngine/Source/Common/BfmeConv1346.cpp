// Open-BFME5 conversions.

struct BfmeStateUYA
{
	char m_bfmePad[0x24];
	char m_bfmeDirty;
};

extern BfmeStateUYA *g_bfmeStateUYA;

class BfmeStrUYA
{
public:
	void bfmeClearUYA();
	char m_bfmePad[4];
};

class BfmeRecUYA
{
public:
	char m_bfmePad[0x2d4];
	BfmeStrUYA m_bfmeA;
	BfmeStrUYA m_bfmeB;
};

class BfmeOwnerUYA
{
public:
	virtual void bfmeV0UYA() = 0;
	virtual void bfmeV1UYA() = 0;
	virtual void bfmeV2UYA() = 0;
	virtual void bfmeV3UYA() = 0;
	virtual void bfmeV4UYA() = 0;
	virtual void bfmeV5UYA() = 0;
	virtual void bfmeV6UYA() = 0;
	virtual void bfmeV7UYA() = 0;
	virtual void bfmeV8UYA() = 0;
	virtual void bfmeV9UYA() = 0;
	virtual BfmeRecUYA *bfmeFindUYA() = 0;
};

class BfmeThingUYA
{
public:
	virtual char bfmeCheckUYA() = 0;
	virtual void bfmeW1UYA() = 0;
	virtual void bfmeW2UYA() = 0;
	virtual void bfmeW3UYA() = 0;
	virtual void bfmeW4UYA() = 0;
	virtual void bfmeW5UYA() = 0;
	virtual void bfmeW6UYA() = 0;
	virtual void bfmeW7UYA() = 0;
	virtual void bfmeFinishUYA(int f) = 0;
	void bfmeGoUYA();
};

void BfmeThingUYA::bfmeGoUYA()
{
	if (!bfmeCheckUYA())
		return;
	BfmeRecUYA *r = (*(BfmeOwnerUYA **)((char *)this - 8))->bfmeFindUYA();
	if (r) {
		r->m_bfmeA.bfmeClearUYA();
		r->m_bfmeB.bfmeClearUYA();
		g_bfmeStateUYA->m_bfmeDirty = 1;
	}
	bfmeFinishUYA(0);
}
