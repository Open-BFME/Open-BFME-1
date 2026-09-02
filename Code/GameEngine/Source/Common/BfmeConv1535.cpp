// Open-BFME5 conversions.

class BfmeObjVOJ
{
public:
	void bfmeSetUntilVOJ(int type, unsigned until);
};

class BfmeMgrVOJ
{
public:
	virtual void bfmeSlot00VOJ();
	virtual void bfmeSlot01VOJ();
	virtual void bfmeSlot02VOJ();
	virtual void bfmeSlot03VOJ();
	virtual void bfmeSlot04VOJ();
	virtual void bfmeSlot05VOJ();
	virtual void bfmeSlot06VOJ();
	virtual void bfmeSlot07VOJ();
	virtual void bfmeSlot08VOJ();
	virtual void bfmeSlot09VOJ();
	virtual void bfmeSlot10VOJ();
	virtual void bfmeSlot11VOJ();
	virtual void bfmeSlot12VOJ();
	virtual void bfmeSlot13VOJ();
	virtual void bfmeSlot14VOJ();
	virtual void bfmeSlot15VOJ();
	virtual void bfmeSlot16VOJ();
	virtual void bfmeSlot17VOJ();
	virtual void bfmeSlot18VOJ();
	virtual void bfmeSlot19VOJ();
	virtual void bfmeSlot20VOJ();
	virtual void bfmeSlot21VOJ();
	virtual void bfmeSlot22VOJ();
	virtual void bfmeSlot23VOJ();
	virtual void bfmeSlot24VOJ();
	virtual void bfmeSlot25VOJ();
	virtual BfmeObjVOJ *bfmeFindVOJ(void *id);
};

extern BfmeMgrVOJ *g_bfmeMgrVOJ;

void __stdcall bfmeSetVOJ(void *id, char flag)
{
	BfmeObjVOJ *o = g_bfmeMgrVOJ->bfmeFindVOJ(id);

	if (o != 0)
		o->bfmeSetUntilVOJ(3, flag != 0 ? 0x3fffffff : 0);
}
