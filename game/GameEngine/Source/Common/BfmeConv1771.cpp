class BfmeThingCJ
{
public:
	int m_bfmeDataCJ;
};

class BfmeGuardCJ
{
public:
	BfmeGuardCJ(BfmeThingCJ *thing, void *value);
	~BfmeGuardCJ();

	unsigned char m_bfmeHeadCJ[0xc];
};

class BfmeOwnCM
{
public:
	virtual void bfmeSlot00CM(void);
	virtual void bfmeSlot01CM(void);
	virtual void bfmeSlot02CM(void);
	virtual void bfmeSlot03CM(void);
	virtual void bfmeSlot04CM(void);
	virtual void bfmeSlot05CM(void);
	virtual void bfmeSlot06CM(void);
	virtual void bfmeSlot07CM(void);
	virtual void bfmeSlot08CM(void);
	virtual void bfmeSlot09CM(void);
	virtual void bfmeSlot10CM(void);
	virtual void bfmeSlot11CM(void);
	virtual void bfmeSlot12CM(void);
	virtual void bfmeSlot13CM(void);
	virtual void bfmeSlot14CM(void);
	virtual void bfmeSlot15CM(void);
	virtual void bfmeSlot16CM(void);
	virtual void bfmeSlot17CM(void);
	virtual void bfmeSlot18CM(void);
	virtual void bfmeSlot19CM(void);
	virtual void bfmeSlot20CM(void);
	virtual void bfmeSlot21CM(void);
	virtual void bfmeSlot22CM(void);
	virtual char bfmeRunCM(void *first, void *second, void *third);

	char bfmeGuardedCM(void *first, void *second, void *third, void *fourth);

	unsigned char m_bfmeHeadCM[0x17084];
	BfmeThingCJ m_bfmeThingCM;
};

char BfmeOwnCM::bfmeGuardedCM(void *first, void *second, void *third, void *fourth)
{
	BfmeGuardCJ guard(&m_bfmeThingCM, first);

	return bfmeRunCM(second, third, fourth);
}
