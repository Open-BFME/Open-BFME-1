// cl: /O2
// Layout and ABI evidence: targets/game/reverse/identity_evidence/00749ea0-cliff-height-range.md

extern void j_00027def();

class Rva00749EA0HeightGrid
{
public:
	void setCellCliffFlagFromHeights(int xIndex, int yIndex);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x10];
	int m_dataSize;
	unsigned short *m_data;

	// ?getHeight@Rva00749EA0HeightGrid@@AAEGHH@Z absent-from-retail
	unsigned short getHeight(int xIndex, int yIndex)
	{
		int ndx = yIndex * m_width + xIndex;
		if (ndx >= 0 && ndx < m_dataSize && m_data)
			return m_data[ndx];
		return 0;
	}

	// ?setCliffState@Rva00749EA0HeightGrid@@AAEXHHE@Z absent-from-retail
	void setCliffState(int xIndex, int yIndex, unsigned char isCliff)
	{
		typedef void (Rva00749EA0HeightGrid::*Setter)(int, int, unsigned char);
		union { void (*function)(); Setter method; } call = { j_00027def };
		(this->*call.method)(xIndex, yIndex, isCliff);
	}
};

// ?setCellCliffFlagFromHeights@Rva00749EA0HeightGrid@@QAEXHH@Z
void Rva00749EA0HeightGrid::setCellCliffFlagFromHeights(int xIndex, int yIndex)
{
	float height1 = getHeight(xIndex, yIndex);
	float minZ = height1;
	float maxZ = height1;
	float height2 = getHeight(xIndex + 1, yIndex);
	if (minZ > height2) minZ = height2;
	else if (maxZ < height2) maxZ = height2;
	float height3 = getHeight(xIndex, yIndex + 1);
	if (minZ > height3) minZ = height3;
	else if (maxZ < height3) maxZ = height3;
	float height4 = getHeight(xIndex + 1, yIndex + 1);
	if (minZ > height4) minZ = height4;
	else if (maxZ < height4) maxZ = height4;
	unsigned char isCliff = maxZ - minZ > 250.88f;
	setCliffState(xIndex, yIndex, isCliff);
}
