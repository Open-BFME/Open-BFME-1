// Open-BFME5 conversions.

class BfmeStrNVSQ
{
public:
	~BfmeStrNVSQ() { bfmeReleaseNVSQ(); }
	char *m_bfme00;

private:
	void bfmeReleaseNVSQ();
};

class BfmeStrWVSQ
{
public:
	~BfmeStrWVSQ() { bfmeReleaseWVSQ(); }
	unsigned short *m_bfme00;

private:
	void bfmeReleaseWVSQ();
};

class BfmePairVSQ
{
public:
	BfmeStrWVSQ m_bfme00;
	BfmeStrNVSQ m_bfme04;
};

class BfmeHolderVSQ
{
public:
	~BfmeHolderVSQ();
	int m_bfme00;
	BfmePairVSQ m_bfme04;
};

BfmeHolderVSQ::~BfmeHolderVSQ()
{
}
