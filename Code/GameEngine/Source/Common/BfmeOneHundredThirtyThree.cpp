// One more: a block setter that walks its own base.

class BfmeBlockWB
{
public:
	int m_bfmeWords[6];
};

class Gen_001F8440
{
public:
	void bfmeSetBlock(const BfmeBlockWB *src);
private:
	unsigned char m_bfmeGap[0x84];				// +0x00
	unsigned char m_bfmeFlag;					// +0x84
	unsigned char m_bfmeGap2[3];				// +0x85
	BfmeBlockWB m_bfmeBlock;					// +0x88
};

void Gen_001F8440::bfmeSetBlock(const BfmeBlockWB *src)
{
	m_bfmeFlag = 1;
	m_bfmeBlock = *src;
}
