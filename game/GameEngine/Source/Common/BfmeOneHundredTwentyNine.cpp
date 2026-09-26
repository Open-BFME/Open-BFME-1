// One more: a copy constructor that carries forty-three fields.

class Gen_0071CD80
{
public:
	Gen_0071CD80(const Gen_0071CD80 &other);
private:
	int m_bfmeHead[17];						// +0x00
	unsigned char m_bfmeFlagA;				// +0x44
	unsigned char m_bfmeFlagB;				// +0x45
	unsigned char m_bfmeFlagC;				// +0x46
	unsigned char m_bfmeGap;				// +0x47
	int m_bfmeTail[23];						// +0x48
};

Gen_0071CD80::Gen_0071CD80(const Gen_0071CD80 &other)
{
	m_bfmeHead[0] = other.m_bfmeHead[0];
	m_bfmeHead[1] = other.m_bfmeHead[1];
	m_bfmeHead[2] = other.m_bfmeHead[2];
	m_bfmeHead[3] = other.m_bfmeHead[3];
	m_bfmeHead[4] = other.m_bfmeHead[4];
	m_bfmeHead[5] = other.m_bfmeHead[5];
	m_bfmeHead[6] = other.m_bfmeHead[6];
	m_bfmeHead[7] = other.m_bfmeHead[7];
	m_bfmeHead[8] = other.m_bfmeHead[8];
	m_bfmeHead[9] = other.m_bfmeHead[9];
	m_bfmeHead[10] = other.m_bfmeHead[10];
	m_bfmeHead[11] = other.m_bfmeHead[11];
	m_bfmeHead[12] = other.m_bfmeHead[12];
	m_bfmeHead[13] = other.m_bfmeHead[13];
	m_bfmeHead[14] = other.m_bfmeHead[14];
	m_bfmeHead[15] = other.m_bfmeHead[15];
	m_bfmeHead[16] = other.m_bfmeHead[16];

	m_bfmeFlagA = other.m_bfmeFlagA;
	m_bfmeFlagB = other.m_bfmeFlagB;
	m_bfmeFlagC = other.m_bfmeFlagC;

	m_bfmeTail[0] = other.m_bfmeTail[0];
	m_bfmeTail[1] = other.m_bfmeTail[1];
	m_bfmeTail[2] = other.m_bfmeTail[2];
	m_bfmeTail[3] = other.m_bfmeTail[3];
	m_bfmeTail[4] = other.m_bfmeTail[4];
	m_bfmeTail[5] = other.m_bfmeTail[5];
	m_bfmeTail[6] = other.m_bfmeTail[6];
	m_bfmeTail[7] = other.m_bfmeTail[7];
	m_bfmeTail[8] = other.m_bfmeTail[8];
	m_bfmeTail[9] = other.m_bfmeTail[9];
	m_bfmeTail[10] = other.m_bfmeTail[10];
	m_bfmeTail[11] = other.m_bfmeTail[11];
	m_bfmeTail[12] = other.m_bfmeTail[12];
	m_bfmeTail[13] = other.m_bfmeTail[13];
	m_bfmeTail[14] = other.m_bfmeTail[14];
	m_bfmeTail[15] = other.m_bfmeTail[15];
	m_bfmeTail[16] = other.m_bfmeTail[16];
	m_bfmeTail[17] = other.m_bfmeTail[17];
	m_bfmeTail[18] = other.m_bfmeTail[18];
	m_bfmeTail[19] = other.m_bfmeTail[19];
	m_bfmeTail[20] = other.m_bfmeTail[20];
	m_bfmeTail[21] = other.m_bfmeTail[21];
	m_bfmeTail[22] = other.m_bfmeTail[22];
}
