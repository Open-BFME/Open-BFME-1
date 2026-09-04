// Open-BFME5 conversions.

class BfmeStrVVC
{
public:
	~BfmeStrVVC() { bfmeClearVVC(); }
	char *m_bfme00;

private:
	void bfmeClearVVC();
};

class BfmeElemVVC
{
public:
	~BfmeElemVVC();
	int m_bfme00;
	int m_bfme04;
};

class BfmeOwnVVC
{
public:
	~BfmeOwnVVC();
	char m_bfmePad00[0x24];
	BfmeElemVVC m_bfme24[2];
	BfmeElemVVC m_bfme34[2];
	char m_bfmePad44[4];
	BfmeStrVVC m_bfme48;
	BfmeStrVVC m_bfme4c;
	BfmeStrVVC m_bfme50;
	BfmeStrVVC m_bfme54;
};

BfmeOwnVVC::~BfmeOwnVVC()
{
}
