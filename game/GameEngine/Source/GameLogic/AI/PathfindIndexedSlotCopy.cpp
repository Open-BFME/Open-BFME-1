// Hands the indexed Pathfinder-side slot to the destination and then lowers
// the first-live watermark.

struct BfmeSubBRE
{
	char m_bfmeHead[0x10];
	unsigned short m_bfmeCode;
};

class BfmeThingBRE
{
public:
	void bfmeGoBRE(void *what);
	BfmeSubBRE *m_bfmeSub;
};

class Gen_003D6400
{
public:
	void bfmeCopyIndexed(BfmeThingBRE *destination);

private:
	char m_bfmeHead[0x34];
	unsigned int m_bfmeSlots[512];
	int m_bfmeWatermark;
};

// ?bfmeCopyIndexed@Gen_003D6400@@QAEXPAVBfmeThingBRE@@@Z
void Gen_003D6400::bfmeCopyIndexed(BfmeThingBRE *destination)
{
	unsigned int index = destination->m_bfmeSub->m_bfmeCode >> 7;
	destination->bfmeGoBRE(&m_bfmeSlots[index]);
	if ((int)index < m_bfmeWatermark)
		m_bfmeWatermark = index;
}
