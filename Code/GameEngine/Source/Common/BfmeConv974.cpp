// Open-BFME5 conversions.

struct BfmeArg974
{
	char m_bfmePad[0x74];
	int m_bfmeVal;
};

class BfmeMgr974
{
public:
	virtual void bfmeV0974();
	virtual void bfmeV1974();
	virtual void bfmeV2974();
	virtual void bfmeV3974();
	virtual void bfmeV4974();
	virtual void bfmeV5974();
	virtual void bfmeV6974();
	virtual void bfmeV7974();
	virtual void bfmeV8974();
	virtual void bfmeV9974();
	virtual void bfmeV10974();
	virtual void bfmeV11974();
	virtual void bfmeV12974();
	virtual void bfmeV13974();
	virtual void bfmeV14974();
	virtual void bfmeV15974();
	virtual void bfmeV16974();
	virtual void bfmeV17974();
	virtual void bfmeV18974();
	virtual void bfmeV19974();
	virtual void bfmeV20974();
	virtual void bfmeV21974();
	virtual void bfmeV22974();
	virtual void bfmeV23974();
	virtual void bfmeV24974();
	virtual void bfmeV25974();
	virtual void bfmeV26974();
	virtual void bfmeV27974();
	virtual void bfmeV28974();
	virtual void bfmeV29974();
	virtual void bfmeV30974();
	virtual void bfmeV31974();
	virtual void bfmeV32974();
	virtual void bfmeV33974();
	virtual void bfmeV34974();
	virtual void bfmeV35974();
	virtual void bfmeV36974();
	virtual void bfmeV37974();
	virtual void bfmeV38974();
	virtual void bfmeV39974();
	virtual void bfmeV40974();
	virtual void bfmeV41974();
	virtual void bfmeV42974();
	virtual void bfmeV43974();
	virtual void bfmeV44974();
	virtual void bfmeV45974();
	virtual void bfmeV46974();
	virtual void bfmeV47974();
	virtual void bfmeV48974();
	virtual void bfmeV49974();
	virtual void bfmeV50974();
	virtual void bfmeV51974();
	virtual void bfmeV52974();
	virtual void bfmeV53974();
	virtual void bfmeV54974();
	virtual void bfmeV55974();
	virtual void bfmeV56974();
	virtual void bfmeV57974();
	virtual void bfmeV58974();
	virtual void bfmeV59974();
	virtual void bfmeV60974();
	virtual void bfmeV61974();
	virtual void bfmeV62974();
	virtual void bfmeReg974(void *cb, void *o, int n);
};

struct BfmeOwner974
{
	char m_bfmePad[0x1fc];
	BfmeMgr974 *m_bfmeMgr;
};

void __stdcall bfmeCb974D(void);

class BfmeD974
{
public:
	void bfmeGo974D();
	void bfmeTail974D();
};

void BfmeD974::bfmeGo974D()
{
	BfmeOwner974 *o = *(BfmeOwner974 **)((char *)this - 8);

	if (o)
		o->m_bfmeMgr->bfmeReg974((void *)bfmeCb974D, o, 1);

	bfmeTail974D();
}

class BfmeE974
{
public:
	void bfmeGo974E(BfmeArg974 *a, int b);
	void bfmeBase974E(BfmeArg974 *a, int b);

	char m_bfmePad[0x400];
	int m_bfmeSlot;
};

void BfmeE974::bfmeGo974E(BfmeArg974 *a, int b)
{
	bfmeBase974E(a, b);

	if (!b && a)
		m_bfmeSlot = a->m_bfmeVal;
}
