// One more: a copy constructor carrying twenty-two words, a block and a flag.

class BfmeQuadUB
{
public:
	int m_bfmeWords[4];
};

class Gen_001A1F30
{
public:
	Gen_001A1F30(const Gen_001A1F30 &other);
private:
	int m_bfmeWords[22];						// +0x00
	BfmeQuadUB m_bfmeQuad;					// +0x58
	unsigned char m_bfmeFlag;				// +0x68
};

Gen_001A1F30::Gen_001A1F30(const Gen_001A1F30 &other)
{
	m_bfmeWords[0] = other.m_bfmeWords[0];
	m_bfmeWords[1] = other.m_bfmeWords[1];
	m_bfmeWords[2] = other.m_bfmeWords[2];
	m_bfmeWords[3] = other.m_bfmeWords[3];
	m_bfmeWords[4] = other.m_bfmeWords[4];
	m_bfmeWords[5] = other.m_bfmeWords[5];
	m_bfmeWords[6] = other.m_bfmeWords[6];
	m_bfmeWords[7] = other.m_bfmeWords[7];
	m_bfmeWords[8] = other.m_bfmeWords[8];
	m_bfmeWords[9] = other.m_bfmeWords[9];
	m_bfmeWords[10] = other.m_bfmeWords[10];
	m_bfmeWords[11] = other.m_bfmeWords[11];
	m_bfmeWords[12] = other.m_bfmeWords[12];
	m_bfmeWords[13] = other.m_bfmeWords[13];
	m_bfmeWords[14] = other.m_bfmeWords[14];
	m_bfmeWords[15] = other.m_bfmeWords[15];
	m_bfmeWords[16] = other.m_bfmeWords[16];
	m_bfmeWords[17] = other.m_bfmeWords[17];
	m_bfmeWords[18] = other.m_bfmeWords[18];
	m_bfmeWords[19] = other.m_bfmeWords[19];
	m_bfmeWords[20] = other.m_bfmeWords[20];
	m_bfmeWords[21] = other.m_bfmeWords[21];

	m_bfmeQuad = other.m_bfmeQuad;
	m_bfmeFlag = other.m_bfmeFlag;
}
