class BfmeThingERX
{
public:
	char bfmeCheckERX(int what);
};

class BfmeBaseERX
{
public:
	char bfmeAllowERX(BfmeThingERX *thing, int flag);
};

class BfmeHostERX
{
public:
	virtual void bfmeSlot00ERX();
	virtual void bfmeSlot01ERX();
	virtual void bfmeSlot02ERX();
	virtual void bfmeSlot03ERX();
	virtual void bfmeSlot04ERX();
	virtual void bfmeSlot05ERX();
	virtual void bfmeSlot06ERX();
	virtual void bfmeSlot07ERX();
	virtual void bfmeSlot08ERX();
	virtual void bfmeSlot09ERX();
	virtual void bfmeSlot10ERX();
	virtual void bfmeSlot11ERX();
	virtual void bfmeSlot12ERX();
	virtual void bfmeSlot13ERX();
	virtual void bfmeSlot14ERX();
	virtual void bfmeSlot15ERX();
	virtual void bfmeSlot16ERX();
	virtual void bfmeSlot17ERX();
	virtual void bfmeSlot18ERX();
	virtual void bfmeSlot19ERX();
	virtual void bfmeSlot20ERX();
	virtual void bfmeSlot21ERX();
	virtual void bfmeSlot22ERX();
	virtual int bfmeSlot23ERX();
	virtual void bfmeSlot24ERX();
	virtual void bfmeSlot25ERX();
	virtual void bfmeSlot26ERX();
	virtual void bfmeSlot27ERX();
	virtual void bfmeSlot28ERX();
	virtual void bfmeSlot29ERX();
	virtual void bfmeSlot30ERX();
	virtual void bfmeSlot31ERX();
	virtual void bfmeSlot32ERX();
	virtual void bfmeSlot33ERX();
	virtual void bfmeSlot34ERX();
	virtual void bfmeSlot35ERX();
	virtual void bfmeSlot36ERX();
	virtual void bfmeSlot37ERX();
	virtual void bfmeSlot38ERX();
	virtual void bfmeSlot39ERX();
	virtual void bfmeSlot40ERX();
	virtual void bfmeSlot41ERX();
	virtual void bfmeSlot42ERX();
	virtual void bfmeSlot43ERX();
	virtual void bfmeSlot44ERX();
	virtual void bfmeSlot45ERX();
	virtual void bfmeSlot46ERX();
	virtual void bfmeSlot47ERX();
	virtual void bfmeSlot48ERX();
	virtual void bfmeSlot49ERX();
	virtual void bfmeSlot50ERX();
	virtual void bfmeSlot51ERX();
	virtual void bfmeSlot52ERX();
	virtual void bfmeSlot53ERX();
	virtual void bfmeSlot54ERX();
	virtual void bfmeSlot55ERX();
	virtual void bfmeSlot56ERX();
	virtual void bfmeSlot57ERX();
	virtual void bfmeSlot58ERX();
	virtual void bfmeSlot59ERX();
	virtual void bfmeSlot60ERX();
	virtual void bfmeSlot61ERX();
	virtual void bfmeSlot62ERX();
	virtual void bfmeSlot63ERX();
	virtual int bfmeSlot64ERX(int mode);

	bool bfmeCanERX(BfmeThingERX *thing, int flag);
};

bool BfmeHostERX::bfmeCanERX(BfmeThingERX *thing, int flag)
{
	if (thing != 0 &&
		((BfmeBaseERX *)((char *)this - 0x20))->bfmeAllowERX(thing, flag) &&
		!thing->bfmeCheckERX(0x1b))
	{
		if ((char)flag != 0)
		{
			int limit = bfmeSlot23ERX();

			return bfmeSlot64ERX(0) < limit;
		}

		return 1;
	}

	return 0;
}
