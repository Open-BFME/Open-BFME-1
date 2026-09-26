// Open-BFME5 conversions.

class BfmeStrVSW
{
public:
	BfmeStrVSW() { m_bfme00 = 0; }
	~BfmeStrVSW() { bfmeClearVSW(); }
	void bfmeClearVSW();
	char *m_bfme00;
};

class BfmeOwnVSW
{
public:
	BfmeOwnVSW();
	void bfmeInitVSW();
	virtual void bfmeSlot0VSW() = 0;
	char m_bfmePad04[0x24];
	BfmeStrVSW m_bfme28;
	BfmeStrVSW m_bfme2c;
	int m_bfme30;
	short m_bfme34;
};

BfmeOwnVSW::BfmeOwnVSW()
	: m_bfme30(0), m_bfme34(0)
{
	bfmeInitVSW();
}
