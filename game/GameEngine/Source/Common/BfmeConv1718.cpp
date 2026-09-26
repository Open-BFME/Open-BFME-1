class BfmeThingGK;

class BfmePrimaryGK
{
public:
	virtual void bfmeSlot00GK(void);
	virtual void bfmeSlot01GK(void);
	virtual void bfmeSlot02GK(void);
	virtual void bfmeSlot03GK(void);
	virtual void bfmeSlot04GK(void);
	virtual void bfmeSlot05GK(void);
	virtual void bfmeSlot06GK(void);
	virtual void bfmeSlot07GK(void);
	virtual void bfmeSlot08GK(void);
	virtual void bfmeSlot09GK(void);
	virtual char bfmeCheckGK(void);
};

class BfmeArgGK
{
public:
	unsigned char m_bfmeHeadGK[0x74];
	int m_bfmeKindGK;
};

class BfmeSubGK
{
public:
	void bfmeFirstGK(BfmeThingGK *thing);
	void bfmeSecondGK(BfmeThingGK *thing, int kind, BfmeArgGK *arg, int flag);
};

class BfmeSecondGK
{
public:
	void bfmeGoGK(BfmeArgGK *arg, int unusedA, int unusedB);

	unsigned char m_bfmeHeadGK[4];
	BfmeSubGK *m_bfmeSubGK;
};

void BfmeSecondGK::bfmeGoGK(BfmeArgGK *arg, int unusedA, int unusedB)
{
	if (arg == 0)
		return;

	char *base = (char *)this;
	BfmeThingGK *thing = *(BfmeThingGK **)(base - 8);

	if (((BfmePrimaryGK *)(base - 0x10))->bfmeCheckGK() == 0)
		return;

	m_bfmeSubGK->bfmeFirstGK(thing);
	m_bfmeSubGK->bfmeSecondGK(thing, arg->m_bfmeKindGK, arg, 0);
}
