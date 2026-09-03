// Open-BFME5 conversions.

class BfmeStrNVSR
{
public:
	~BfmeStrNVSR() { bfmeReleaseNVSR(); }
	char *m_bfme00;

private:
	void bfmeReleaseNVSR();
};

class BfmeStrWVSR
{
public:
	~BfmeStrWVSR() { bfmeReleaseWVSR(); }
	unsigned short *m_bfme00;

private:
	void bfmeReleaseWVSR();
};

class BfmeHolderVSR
{
public:
	~BfmeHolderVSR();
	BfmeStrNVSR m_bfme00;
	int m_bfme04;
	BfmeStrWVSR m_bfme08;
};

BfmeHolderVSR::~BfmeHolderVSR()
{
	m_bfme04 = 0;
}
