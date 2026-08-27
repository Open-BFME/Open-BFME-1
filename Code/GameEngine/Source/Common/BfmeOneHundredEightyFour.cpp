// Four more errands: a chain let go of one link at a time, a value handed out
// and taken back, a hook called before the real work, and four of five numbers
// passed along.

class BfmeNodeCR
{
public:
	virtual void bfmeDoCR(int how) = 0;

	BfmeNodeCR *m_bfmeNext;			// 0x4
};

class BfmeThingCR
{
public:
	void bfmeClearCR(void);

private:
	BfmeNodeCR *m_bfmeFirst;		// 0x0
};

void BfmeThingCR::bfmeClearCR(void)
{
	BfmeNodeCR *at = m_bfmeFirst;

	while (at != 0)
	{
		BfmeNodeCR *next = at->m_bfmeNext;

		at->bfmeDoCR(1);

		at = next;
	}
}


class BfmeTargetCS
{
public:
	virtual void bfmeSpare000CS(void) = 0;
	virtual void bfmeSpare001CS(void) = 0;
	virtual void bfmeSpare002CS(void) = 0;
	virtual void bfmeSpare003CS(void) = 0;
	virtual void bfmeSpare004CS(void) = 0;
	virtual void bfmeSpare005CS(void) = 0;
	virtual void bfmeSpare006CS(void) = 0;
	virtual void bfmeSpare007CS(void) = 0;
	virtual void bfmeSpare008CS(void) = 0;
	virtual void bfmeSpare009CS(void) = 0;
	virtual void bfmeSpare010CS(void) = 0;
	virtual void bfmeSpare011CS(void) = 0;
	virtual void bfmeSpare012CS(void) = 0;
	virtual void bfmeSpare013CS(void) = 0;
	virtual void bfmeSpare014CS(void) = 0;
	virtual void bfmeSpare015CS(void) = 0;
	virtual void bfmeSpare016CS(void) = 0;
	virtual void bfmeSpare017CS(void) = 0;
	virtual void bfmeSpare018CS(void) = 0;
	virtual void bfmeSpare019CS(void) = 0;
	virtual void bfmeSpare020CS(void) = 0;
	virtual void bfmeSpare021CS(void) = 0;
	virtual void bfmeSpare022CS(void) = 0;
	virtual void bfmeSpare023CS(void) = 0;
	virtual void bfmeSpare024CS(void) = 0;
	virtual void bfmeSpare025CS(void) = 0;
	virtual void bfmeSpare026CS(void) = 0;
	virtual void bfmeSpare027CS(void) = 0;
	virtual void bfmeSpare028CS(void) = 0;
	virtual void bfmeSpare029CS(void) = 0;
	virtual void bfmeSpare030CS(void) = 0;
	virtual void bfmeSpare031CS(void) = 0;
	virtual void bfmeSpare032CS(void) = 0;
	virtual void bfmeSpare033CS(void) = 0;
	virtual void bfmeSpare034CS(void) = 0;
	virtual void bfmeSpare035CS(void) = 0;
	virtual void bfmeSpare036CS(void) = 0;
	virtual void bfmeSpare037CS(void) = 0;
	virtual void bfmeSpare038CS(void) = 0;
	virtual void bfmeSpare039CS(void) = 0;
	virtual void bfmeSpare040CS(void) = 0;
	virtual void bfmeSpare041CS(void) = 0;
	virtual void bfmeSpare042CS(void) = 0;
	virtual void bfmeSpare043CS(void) = 0;
	virtual void bfmeSpare044CS(void) = 0;
	virtual void bfmeSpare045CS(void) = 0;
	virtual void bfmeSpare046CS(void) = 0;
	virtual void bfmeSpare047CS(void) = 0;
	virtual void bfmeSpare048CS(void) = 0;
	virtual void bfmeSpare049CS(void) = 0;
	virtual void bfmeSpare050CS(void) = 0;
	virtual void bfmeSpare051CS(void) = 0;
	virtual void bfmeSpare052CS(void) = 0;
	virtual void bfmeSpare053CS(void) = 0;
	virtual void bfmeSpare054CS(void) = 0;
	virtual void bfmeSpare055CS(void) = 0;
	virtual void bfmeSpare056CS(void) = 0;
	virtual void bfmeSpare057CS(void) = 0;
	virtual void bfmeSpare058CS(void) = 0;
	virtual void bfmeSpare059CS(void) = 0;
	virtual void bfmeSpare060CS(void) = 0;
	virtual void bfmeSpare061CS(void) = 0;
	virtual void bfmeSpare062CS(void) = 0;
	virtual void bfmeSpare063CS(void) = 0;
	virtual void bfmeSpare064CS(void) = 0;
	virtual void bfmeSpare065CS(void) = 0;
	virtual void bfmeSpare066CS(void) = 0;
	virtual void bfmeSpare067CS(void) = 0;
	virtual void bfmeSpare068CS(void) = 0;
	virtual void bfmeSpare069CS(void) = 0;
	virtual void bfmeSpare070CS(void) = 0;
	virtual void bfmeSpare071CS(void) = 0;
	virtual void bfmeSpare072CS(void) = 0;
	virtual void bfmeSpare073CS(void) = 0;
	virtual void bfmeSpare074CS(void) = 0;
	virtual void bfmeSpare075CS(void) = 0;
	virtual void bfmeSpare076CS(void) = 0;
	virtual void bfmeSpare077CS(void) = 0;
	virtual void bfmeSpare078CS(void) = 0;
	virtual void bfmeSpare079CS(void) = 0;
	virtual void bfmeSpare080CS(void) = 0;
	virtual void bfmeSpare081CS(void) = 0;
	virtual void bfmeSpare082CS(void) = 0;
	virtual void bfmeSpare083CS(void) = 0;
	virtual void bfmeSpare084CS(void) = 0;
	virtual void bfmeSpare085CS(void) = 0;
	virtual void bfmeSpare086CS(void) = 0;
	virtual void bfmeSpare087CS(void) = 0;
	virtual void bfmeSpare088CS(void) = 0;
	virtual void bfmeSpare089CS(void) = 0;
	virtual void bfmeSpare090CS(void) = 0;
	virtual void bfmeSpare091CS(void) = 0;
	virtual void bfmeSpare092CS(void) = 0;
	virtual void bfmeSpare093CS(void) = 0;
	virtual void bfmeSpare094CS(void) = 0;
	virtual void bfmeSpare095CS(void) = 0;
	virtual void bfmeSpare096CS(void) = 0;
	virtual void bfmeSpare097CS(void) = 0;
	virtual void bfmeSpare098CS(void) = 0;
	virtual void bfmeSpare099CS(void) = 0;
	virtual void bfmeSpare100CS(void) = 0;
	virtual void bfmeSpare101CS(void) = 0;
	virtual void bfmeSpare102CS(void) = 0;
	virtual void bfmeSpare103CS(void) = 0;
	virtual void bfmeSpare104CS(void) = 0;
	virtual void bfmeSpare105CS(void) = 0;
	virtual void bfmeSpare106CS(void) = 0;
	virtual void bfmeSpare107CS(void) = 0;
	virtual void bfmeSpare108CS(void) = 0;
	virtual void bfmeSpare109CS(void) = 0;
	virtual void bfmeSpare110CS(void) = 0;
	virtual void bfmeSpare111CS(void) = 0;
	virtual void bfmeSpare112CS(void) = 0;
	virtual void bfmeSpare113CS(void) = 0;
	virtual void bfmeSpare114CS(void) = 0;
	virtual void bfmeSpare115CS(void) = 0;
	virtual void bfmeSpare116CS(void) = 0;
	virtual void bfmeSpare117CS(void) = 0;
	virtual void bfmeSpare118CS(void) = 0;
	virtual void bfmeSpare119CS(void) = 0;
	virtual void bfmeSpare120CS(void) = 0;
	virtual void bfmeSpare121CS(void) = 0;
	virtual void bfmeSpare122CS(void) = 0;
	virtual void bfmeSpare123CS(void) = 0;
	virtual void bfmeSpare124CS(void) = 0;
	virtual void bfmeSpare125CS(void) = 0;
	virtual void bfmeSpare126CS(void) = 0;
	virtual void bfmeSpare127CS(void) = 0;
	virtual void bfmeSpare128CS(void) = 0;
	virtual void bfmeSpare129CS(void) = 0;
	virtual void bfmeSpare130CS(void) = 0;
	virtual void bfmeSpare131CS(void) = 0;
	virtual void bfmeSpare132CS(void) = 0;
	virtual void bfmeSpare133CS(void) = 0;
	virtual void bfmeSpare134CS(void) = 0;
	virtual void bfmeSpare135CS(void) = 0;
	virtual void bfmeSpare136CS(void) = 0;
	virtual void bfmeSpare137CS(void) = 0;
	virtual void bfmeSpare138CS(void) = 0;
	virtual void bfmeSpare139CS(void) = 0;
	virtual void bfmeSpare140CS(void) = 0;
	virtual void bfmeSpare141CS(void) = 0;
	virtual int bfmeDoCS(int value) = 0;
};

class BfmeThingCS
{
public:
	void bfmeGoCS(BfmeTargetCS *target);

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	int m_bfmeValue;			// 0x18
};

void BfmeThingCS::bfmeGoCS(BfmeTargetCS *target)
{
	m_bfmeValue = target->bfmeDoCS(m_bfmeValue);
}

class BfmeThingCT
{
public:
	virtual void bfmeDoCT(int how) = 0;

	void bfmeGoCT(void);

private:
	unsigned char m_bfmeHead[0xc];		// 0x04
	void (__cdecl *m_bfmeHook)(BfmeThingCT *thing);	// 0x10
};

void BfmeThingCT::bfmeGoCT(void)
{
	if (m_bfmeHook != 0)
		m_bfmeHook(this);

	bfmeDoCT(1);
}

class BfmeThingCV
{
public:
	virtual void bfmeSpare000CV(void) = 0;
	virtual void bfmeSpare001CV(void) = 0;
	virtual void bfmeSpare002CV(void) = 0;
	virtual void bfmeDoCV(int first, int second, int third, int fifth) = 0;

	void bfmeGoCV(int first, int second, int third, int spare, int fifth);
};

void BfmeThingCV::bfmeGoCV(int first, int second, int third, int spare, int fifth)
{
	bfmeDoCV(first, second, third, fifth);
}

