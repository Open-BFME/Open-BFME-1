// Open-BFME5 conversions.

class BfmeMgr999
{
public:
	virtual void bfmeVX0999();
	virtual void bfmeVX1999();
	virtual void bfmeVX2999();
	virtual void bfmeVX3999();
	virtual void bfmeVX4999();
	virtual void bfmeVX5999();
	virtual void bfmeVX6999();
	virtual void bfmeVX7999();
	virtual void bfmeVX8999();
	virtual void bfmeVX9999();
	virtual void bfmeVX10999();
	virtual void bfmeVX11999();
	virtual void bfmeVX12999();
	virtual void bfmeVX13999();
	virtual void bfmeVX14999();
	virtual void bfmeVX15999();
	virtual void bfmeVX16999();
	virtual void bfmeVX17999();
	virtual void bfmeVX18999();
	virtual void bfmeVX19999();
	virtual void bfmeVX20999();
	virtual void bfmeVX21999();
	virtual void bfmeVX22999();
	virtual void bfmeVX23999();
	virtual void bfmeVX24999();
	virtual void bfmeVX25999();
	virtual void bfmeVX26999();
	virtual void bfmeVX27999();
	virtual void bfmeVX28999();
	virtual void bfmeVX29999();
	virtual void bfmeVX30999();
	virtual void bfmeVX31999();
	virtual void bfmeVX32999();
	virtual void bfmeVX33999();
	virtual void bfmeVX34999();
	virtual void bfmeVX35999();
	virtual void bfmeVX36999();
	virtual void bfmeVX37999();
	virtual void bfmeVX38999();
	virtual void bfmeVX39999();
	virtual void bfmeVX40999();
	virtual void bfmeVX41999();
	virtual void bfmeVX42999();
	virtual void bfmeVX43999();
	virtual void bfmeVX44999();
	virtual void bfmeVX45999();
	virtual void bfmeVX46999();
	virtual void bfmeVX47999();
	virtual void bfmeVX48999();
	virtual void bfmeVX49999();
	virtual void bfmeVX50999();
	virtual void bfmeVX51999();
	virtual void bfmeVX52999();
	virtual void bfmeVX53999();
	virtual void bfmeVX54999();
	virtual void bfmeVX55999();
	virtual void bfmeVX56999();
	virtual void bfmeVX57999();
	virtual void bfmeVX58999();
	virtual void bfmeVX59999();
	virtual void bfmeVX60999();
	virtual void bfmeVX61999();
	virtual void bfmeVX62999();
	virtual void bfmeVX63999();
	virtual void bfmeVX64999();
	virtual void bfmeVX65999();
	virtual void bfmeVX66999();
	virtual void bfmeVX67999();
	virtual void bfmeVX68999();
	virtual void bfmeVX69999();
	virtual void bfmeVX70999();
	virtual void bfmeVX71999();
	virtual void bfmeVX72999();
	virtual void bfmeVX73999();
	virtual void bfmeVX74999();
	virtual void bfmeVX75999();
	virtual void bfmeVX76999();
	virtual void bfmeVX77999();
	virtual void bfmeVX78999();
	virtual void bfmeVX79999();
	virtual void bfmeVX80999();
	virtual void bfmeVX81999();
	virtual void bfmeVX82999();
	virtual void bfmeVX83999();
	virtual void bfmeVX84999();
	virtual void bfmeVX85999();
	virtual void bfmeVX86999();
	virtual void bfmeVX87999();
	virtual void bfmeVX88999();
	virtual void bfmeVX89999();
	virtual void bfmeVX90999();
	virtual void bfmeVX91999();
	virtual void bfmeVX92999();
	virtual void bfmeVX93999();
	virtual void bfmeVX94999();
	virtual void bfmeVX95999();
	virtual char bfmeBusy999();
};

struct BfmeOwner999
{
	char m_bfmePad[0x204];
	BfmeMgr999 *m_bfmeMgr;
};

class BfmeA999
{
public:
	char bfmeGo999A();

	char m_bfmePad[8];
	BfmeOwner999 *m_bfmeOwner;
	char m_bfmePad2[0xd4];
	char m_bfmeWant;
	char m_bfmeDone;
};

char BfmeA999::bfmeGo999A()
{
	BfmeMgr999 *m = m_bfmeOwner->m_bfmeMgr;

	if (!m)
		return 1;
	if (m_bfmeDone)
		return 0;
	if (!m_bfmeWant)
		return 0;
	if (m->bfmeBusy999()) {
		m_bfmeDone = 1;
		return 0;
	}

	return 1;
}
