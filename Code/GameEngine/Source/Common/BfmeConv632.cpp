class BfmeResCRA;
class BfmeSubCRA
{
public:
	virtual void bfmeSpareCRA0();
	virtual void bfmeSpareCRA1();
	virtual void bfmeSpareCRA2();
	virtual void bfmeSpareCRA3();
	virtual void bfmeSpareCRA4();
	virtual void bfmeSpareCRA5();
	virtual void bfmeSpareCRA6();
	virtual void bfmeSpareCRA7();
	virtual void bfmeSpareCRA8();
	virtual void bfmeSpareCRA9();
	virtual void bfmeSpareCRA10();
	virtual void bfmeSpareCRA11();
	virtual void bfmeSpareCRA12();
	virtual void bfmeSpareCRA13();
	virtual void bfmeSpareCRA14();
	virtual void bfmeSpareCRA15();
	virtual void bfmeSpareCRA16();
	virtual void bfmeSpareCRA17();
	virtual void bfmeSpareCRA18();
	virtual void bfmeSpareCRA19();
	virtual void bfmeSpareCRA20();
	virtual void bfmeSpareCRA21();
	virtual void bfmeSpareCRA22();
	virtual void bfmeSpareCRA23();
	virtual void bfmeSpareCRA24();
	virtual void bfmeSpareCRA25();
	virtual BfmeResCRA *bfmeGetCRA();
};

struct BfmeMidCRA
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubCRA *m_bfmeSub;
};

class BfmeTableCRA
{
public:
	BfmeMidCRA *bfmeFindCRA(void *key);
};

extern BfmeTableCRA *bfmeTheCRA;

struct BfmeThingCRA
{
	unsigned char m_bfmeHead[0x78];
	void *m_bfmeKey;
};

BfmeResCRA *__stdcall bfmeGoCRA(BfmeThingCRA *thing)
{
	if (thing == 0)
		return 0;
	BfmeMidCRA *mid = bfmeTheCRA->bfmeFindCRA(thing->m_bfmeKey);
	if (mid == 0)
		return 0;
	BfmeSubCRA *sub = mid->m_bfmeSub;
	if (sub == 0)
		return 0;
	return sub->bfmeGetCRA();
}
