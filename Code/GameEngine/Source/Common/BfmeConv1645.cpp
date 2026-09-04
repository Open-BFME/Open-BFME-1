// Open-BFME5 conversions.

class BfmeStrNVUM
{
public:
	~BfmeStrNVUM() { bfmeClearNVUM(); }
	char *m_bfme00;

private:
	void bfmeClearNVUM();
};

class BfmeStrWVUM
{
public:
	~BfmeStrWVUM() { bfmeClearWVUM(); }
	unsigned short *m_bfme00;

private:
	void bfmeClearWVUM();
};

class BfmeOwnVUM
{
public:
	~BfmeOwnVUM();
	virtual void bfmeSlot0VUM();
	BfmeStrNVUM m_bfme04;
	char m_bfmePad08[0x44];
	BfmeStrNVUM m_bfme4c;
	char m_bfmePad50[0x28];
	BfmeStrWVUM m_bfme78;
	char m_bfmePad7c[0x30];
	BfmeStrNVUM m_bfmeac;
	BfmeStrNVUM m_bfmeb0;
};

BfmeOwnVUM::~BfmeOwnVUM()
{
}
