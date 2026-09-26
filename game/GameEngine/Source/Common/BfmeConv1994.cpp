class BfmeSrcEVC;

class BfmeNodeEVC
{
public:
	BfmeNodeEVC(BfmeSrcEVC *src);

	unsigned char m_bfmeBodyEVC[0x170];
};

class BfmeHostEVC
{
public:
	virtual void bfmeSlot00EVC();
	virtual void bfmeSlot01EVC();
	virtual void bfmeSlot02EVC();
	virtual void bfmeSlot03EVC();
	virtual void bfmeSlot04EVC();
	virtual void bfmeSlot05EVC();
	virtual void bfmeSlot06EVC();
	virtual void bfmeSlot07EVC();
	virtual void bfmeSlot08EVC();
	virtual void bfmeSlot09EVC();
	virtual char bfmeReadyEVC();
	virtual void bfmePrepareEVC();

	BfmeNodeEVC *bfmeMakeEVC();

	unsigned char m_bfmeHeadEVC[0x10];
	BfmeSrcEVC *m_bfmeSrcEVC;
};

BfmeNodeEVC *BfmeHostEVC::bfmeMakeEVC()
{
	if (!bfmeReadyEVC())
		bfmePrepareEVC();

	if (m_bfmeSrcEVC == 0)
		return 0;

	return new BfmeNodeEVC(m_bfmeSrcEVC);
}
