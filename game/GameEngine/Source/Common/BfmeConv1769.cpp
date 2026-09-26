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

class BfmeOwnCJ
{
public:
	virtual void bfmeSlot00CJ(void);
	virtual void bfmeSlot01CJ(void);
	virtual void bfmeSlot02CJ(void);
	virtual void bfmeSlot03CJ(void);
	virtual void bfmeSlot04CJ(void);
	virtual void bfmeSlot05CJ(void);
	virtual void bfmeSlot06CJ(void);
	virtual void bfmeSlot07CJ(void);
	virtual void bfmeSlot08CJ(void);
	virtual void bfmeSlot09CJ(void);
	virtual void bfmeSlot10CJ(void);
	virtual void bfmeSlot11CJ(void);
	virtual void bfmeSlot12CJ(void);
	virtual void bfmeSlot13CJ(void);
	virtual void bfmeSlot14CJ(void);
	virtual void bfmeSlot15CJ(void);
	virtual void bfmeSlot16CJ(void);
	virtual void bfmeSlot17CJ(void);
	virtual void bfmeSlot18CJ(void);
	virtual void bfmeSlot19CJ(void);
	virtual void bfmeSlot20CJ(void);
	virtual void bfmeSlot21CJ(void);
	virtual void bfmeSlot22CJ(void);
	virtual void bfmeSlot23CJ(void);
	virtual void bfmeSlot24CJ(void);
	virtual void bfmeSlot25CJ(void);
	virtual void bfmeSlot26CJ(void);
	virtual void bfmeSlot27CJ(void);
	virtual void bfmeSlot28CJ(void);
	virtual void bfmeSlot29CJ(void);
	virtual void bfmeSlot30CJ(void);
	virtual void bfmeSlot31CJ(void);
	virtual void bfmeSlot32CJ(void);
	virtual void bfmeSlot33CJ(void);
	virtual void bfmeSlot34CJ(void);
	virtual void bfmeSlot35CJ(void);
	virtual void bfmeSlot36CJ(void);
	virtual void bfmeSlot37CJ(void);
	virtual void bfmeSlot38CJ(void);
	virtual void bfmeSlot39CJ(void);
	virtual void bfmeSlot40CJ(void);
	virtual void bfmeSlot41CJ(void);
	virtual void bfmeSlot42CJ(void);
	virtual void bfmeSlot43CJ(void);
	virtual void bfmeSlot44CJ(void);
	virtual void bfmeSlot45CJ(void);
	virtual void bfmeSlot46CJ(void);
	virtual void bfmeSlot47CJ(void);
	virtual void bfmeSlot48CJ(void);
	virtual void bfmeSlot49CJ(void);
	virtual void bfmeSlot50CJ(void);
	virtual void bfmeSlot51CJ(void);
	virtual void *bfmeRunCJ(void *first, void *second);

	void *bfmeMakeCJ(void *first, void *second, void *third);

	unsigned char m_bfmeHeadCJ[0x17084];
	BfmeThingCJ m_bfmeThingCJ;
};

void *BfmeOwnCJ::bfmeMakeCJ(void *first, void *second, void *third)
{
	BfmeGuardCJ guard(&m_bfmeThingCJ, first);

	return bfmeRunCJ(second, third);
}
