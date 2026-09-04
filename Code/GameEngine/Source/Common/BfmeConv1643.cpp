// Open-BFME5 conversions.

class BfmeStrNVUL
{
public:
	~BfmeStrNVUL() { bfmeClearNVUL(); }
	char *m_bfme00;

private:
	void bfmeClearNVUL();
};

class BfmeStrWVUL
{
public:
	~BfmeStrWVUL() { bfmeClearWVUL(); }
	unsigned short *m_bfme00;

private:
	void bfmeClearWVUL();
};

class BfmeOwnVUL
{
public:
	~BfmeOwnVUL();
	char m_bfmePad00[0x20];
	BfmeStrNVUL m_bfme20;
	char m_bfmePad24[4];
	BfmeStrNVUL m_bfme28;
	char m_bfmePad2c[4];
	BfmeStrWVUL m_bfme30;
	char m_bfmePad34[0x10];
	BfmeStrWVUL m_bfme44;
	BfmeStrWVUL m_bfme48;
};

BfmeOwnVUL::~BfmeOwnVUL()
{
}
