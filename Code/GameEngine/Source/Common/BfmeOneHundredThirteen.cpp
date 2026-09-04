// Two more: a twelve word block carried in with a flag cleared behind it, and
// a constructor that starts two scales at one and everything else at nothing.

class BfmeBlockTA
{
public:
	int m_bfmeWords[12];
};

class Gen_005BDE40
{
public:
	void bfmeSetBlock(const BfmeBlockTA *src);
private:
	unsigned char m_bfmeGap[0xc0];				// +0x000
	int m_bfmeBlock[12];						// +0x0c0
	unsigned char m_bfmeGap2[0x1a4 - 0xf0];		// +0x0f0
	unsigned char m_bfmeDirty;					// +0x1a4
};

void Gen_005BDE40::bfmeSetBlock(const BfmeBlockTA *src)
{
	m_bfmeBlock[0] = src->m_bfmeWords[0];
	m_bfmeBlock[1] = src->m_bfmeWords[1];
	m_bfmeBlock[2] = src->m_bfmeWords[2];
	m_bfmeBlock[3] = src->m_bfmeWords[3];
	m_bfmeBlock[4] = src->m_bfmeWords[4];
	m_bfmeBlock[5] = src->m_bfmeWords[5];
	m_bfmeBlock[6] = src->m_bfmeWords[6];
	m_bfmeBlock[7] = src->m_bfmeWords[7];
	m_bfmeBlock[8] = src->m_bfmeWords[8];
	m_bfmeBlock[9] = src->m_bfmeWords[9];
	m_bfmeBlock[10] = src->m_bfmeWords[10];
	m_bfmeBlock[11] = src->m_bfmeWords[11];

	m_bfmeDirty = 0;
}
