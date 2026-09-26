// Open-BFME5 conversions.

class BfmeStrVUD
{
public:
	~BfmeStrVUD() { bfmeClearVUD(); }
	char *m_bfme00;

private:
	void bfmeClearVUD();
};

class BfmeOwnVUD
{
public:
	~BfmeOwnVUD();
	virtual void bfmeSlot0VUD();
	BfmeStrVUD m_bfme04;
	char m_bfmePad08[0xc];
	BfmeStrVUD m_bfme14;
	BfmeStrVUD m_bfme18;
};

BfmeOwnVUD::~BfmeOwnVUD()
{
}
