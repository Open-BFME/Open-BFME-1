// Open-BFME5 conversions.

class BfmeStrWVSX
{
public:
	~BfmeStrWVSX() { bfmeClearWVSX(); }
	unsigned short *m_bfme00;

private:
	void bfmeClearWVSX();
};

class BfmeSinkVSX
{
public:
	virtual void bfmeSlot0VSX(int flags);
};

class BfmeOwnVSX
{
public:
	~BfmeOwnVSX();
	char m_bfmePad00[0x14];
	BfmeStrWVSX m_bfme14;
	BfmeSinkVSX *m_bfme18;
};

BfmeOwnVSX::~BfmeOwnVSX()
{
	BfmeSinkVSX *sink = m_bfme18;

	if (sink != 0)
		sink->bfmeSlot0VSX(1);
}
