struct BfmePointFD
{
	float m_bfmeXFD;
	float m_bfmeYFD;
};

struct BfmeEntryFD
{
	unsigned short m_bfmeAFD;
	unsigned short m_bfmeBFD;
	unsigned short m_bfmeCFD;
};

class BfmeCellFD
{
public:
	unsigned char m_bfmeHeadFD[4];
	BfmeEntryFD m_bfmeEntriesFD[16];
};

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(float x, float y) const;
	int bfmeCheckFD(int index, const BfmePointFD *point);
};

int Gen_008F7CD0::bfmeCheckFD(int index, const BfmePointFD *point)
{
	if (index < 0 || index >= 0x10)
		return 2;

	BfmeCellFD *cell = bfmeAt(point->m_bfmeXFD, point->m_bfmeYFD);

	if (cell == 0)
		return 2;

	unsigned short value = cell->m_bfmeEntriesFD[index].m_bfmeAFD;

	if (value == 0xffff)
		return 2;

	return value == 0;
}
