// Open-BFME5 conversions.

class BfmeStrNVUN
{
public:
	~BfmeStrNVUN() { bfmeClearNVUN(); }
	char *m_bfme00;

private:
	void bfmeClearNVUN();
};

class BfmeStrWVUN
{
public:
	~BfmeStrWVUN() { bfmeClearWVUN(); }
	unsigned short *m_bfme00;

private:
	void bfmeClearWVUN();
};

class BfmeOwnVUN
{
public:
	~BfmeOwnVUN();
	BfmeStrNVUN m_bfme00;
	BfmeStrNVUN m_bfme04;
	BfmeStrNVUN m_bfme08;
	char m_bfmePad0c[0x10];
	BfmeStrNVUN m_bfme1c;
	char m_bfmePad20[4];
	BfmeStrWVUN m_bfme24;
	char m_bfmePad28[4];
	BfmeStrNVUN m_bfme2c;
};

BfmeOwnVUN::~BfmeOwnVUN()
{
}
