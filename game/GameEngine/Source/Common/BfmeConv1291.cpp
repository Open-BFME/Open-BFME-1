// Open-BFME5 conversions.

struct BfmeCellSHA
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeMakerSHA
{
public:
	void bfmeFillSHA(BfmeCellSHA *out, int *key);
};

class BfmeStoreSHA
{
public:
	void bfmeUseSHA(int *key);
};

class BfmeThingSHA
{
public:
	void bfmeGoSHA(int key);
	char m_bfmePad[0x10];
	BfmeStoreSHA m_bfmeStore;
	char m_bfmePad2[0xb];
	BfmeMakerSHA m_bfmeMaker;
};

void BfmeThingSHA::bfmeGoSHA(int key)
{
	BfmeCellSHA cell;
	m_bfmeMaker.bfmeFillSHA(&cell, &key);
	m_bfmeStore.bfmeUseSHA(&key);
}
